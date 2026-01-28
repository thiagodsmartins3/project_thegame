#include <iostream>
#include <SDL3_image/SDL_image.h>
#include "../../include/window/gamewindow.hpp"
#include "../../include/texture/gametexture.hpp"
#include "../exception/exception.hpp"
#include "../../utility/paths.hpp"
#include "../../include/menu/gamemainmenu.hpp"
#include "../../include/menu/gamesettingsmenu.hpp"
#include "../../include/savemanager/gamesavemanager.hpp"
#include "../../include/character/gamecharacter.hpp"
#include "../../include/actor/actorcamera.hpp"
#include "../../include/actor/actorcharacter.hpp"
#include "../../include/actor/actorscenario.hpp"

GameWindow::GameWindow() {
    try {
        setupWindow();
    } catch (const Exception& ex) {
        throw;
    }

    gameWindowInfo = GameWindowInfo {
        .title = "The Game",
        .width = 640,
        .height = 480
    };

    window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(
        SDL_CreateWindow(
            gameWindowInfo.title.c_str(), 
            gameWindowInfo.width, 
            gameWindowInfo.height, 
            SDL_WINDOW_OPENGL
        ),
        SDLWindowDeleter()
    );

    if (window == nullptr) {
        throw Exception("Window error:" + std::string(SDL_GetError()));
    }

    windowSurface = std::unique_ptr<SDL_Surface, SDLSurfaceDeleter>(
        SDL_GetWindowSurface(window.get()),
        SDLSurfaceDeleter()
    );

    if (windowSurface == nullptr) {
        throw Exception("Window surface error:" + std::string(SDL_GetError()));
    }

    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(
            window.get(),
            nullptr
        ),
        [](SDL_Renderer* renderer) { SDL_DestroyRenderer(renderer); }
    );
    
    if (renderer == nullptr) {
        throw Exception("Renderer error:" + std::string(SDL_GetError()));
    }

    bool isVSYNCEnable = SDL_SetRenderVSync(renderer.get(), 1);

    #ifdef DEBUG
    if (isVSYNCEnable) {
        std::cout << "VSYNC Enable" << std::endl;
    } else {
        std::cout << "Could not enable VSYNC" << std::endl;
    }
    #endif
}

GameWindow::GameWindow(const GameWindowInfo& windowInfo) {
    try {
        setupWindow();
    } catch (const Exception& ex) {
        throw;
    }

    gameWindowInfo = windowInfo;

    window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(
        SDL_CreateWindow(
            gameWindowInfo.title.c_str(), 
            gameWindowInfo.width, 
            gameWindowInfo.height, 
            SDL_WINDOW_OPENGL
        ),
        SDLWindowDeleter()
    );

    if (window == nullptr) {
        throw Exception("Window error:" + std::string(SDL_GetError()));
    }

    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(
            window.get(),
            nullptr
        ),
        [](SDL_Renderer* renderer) { SDL_DestroyRenderer(renderer); }
    );
    
    if (renderer == nullptr) {
        throw Exception("Renderer error:" + std::string(SDL_GetError()));
    }

    bool isVSYNCEnable = SDL_SetRenderVSync(renderer.get(), 1);

    #ifdef DEBUG
    if (isVSYNCEnable) {
        std::cout << "VSYNC Enable" << std::endl;
    } else {
        std::cout << "Could not enable VSYNC" << std::endl;
    }
    #endif
}

GameWindow::~GameWindow() {
    if (window) {
        SDL_DestroyWindow(window.get());
    }

    if (windowSurface) {
        SDL_DestroySurface(windowSurface.get());
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer.get());
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void GameWindow::run() {
    isRunning = true;
    std::string path = Paths::getInstance().IMAGES("cat_img.png");
    // GameTexture gt(path, renderer);

    GameMainMenu gameMainMenu(renderer.get(), font);
    SDL_Texture* background = IMG_LoadTexture(renderer.get(), Paths::getInstance().IMAGES("background.png").c_str());
    SDL_Texture* character = IMG_LoadTexture(renderer.get(), Paths::getInstance().IMAGES("samurai.png").c_str());
    
    GameSettingsMenu gameSettings;
    GameSaveManager saveManager;

    ActorScenario* Level = new ActorScenario(background, 2000, 2000);
    ActorCharacter* Player = new ActorCharacter(character);
    ActorCamera* Camera = new ActorCamera(500, 500);

    Camera->Target(Player);
    Player->SetPosition({ 100, 100, 64, 64 });

    SDL_FRect RenderView;

    saveManager.saveConfig(std::map<std::string, std::string>({
        {"Test", "10"},
        {"Res", "1024x768"}
    }));

    saveManager.loadConfig();

    const float dt = 0.01f; 
    float accumulator = 0.0f;
    float alpha = 0.0f;

    Uint64 currentTime = SDL_GetPerformanceCounter();
    float frequency = static_cast<float>(SDL_GetPerformanceFrequency());

    while (isRunning) {
        Uint64 newTime = SDL_GetPerformanceCounter();
        float frameTime = (newTime - currentTime) / frequency;
        
        if (frameTime > 0.25f) frameTime = 0.25f; 
        
        currentTime = newTime;
        accumulator += frameTime;

        switch(gameMainMenu.status()) {
            case GameMainMenu::AppState::MainMenu:
                while (SDL_PollEvent(&event)) {
                    gameMainMenu.eventHandler(&event);

                    if (event.type == SDL_EVENT_QUIT) {
                        isRunning = false;
                    }
                }

                SDL_SetRenderDrawColor(renderer.get(), 10, 10, 10, 255);
                SDL_RenderClear(renderer.get());
                gameMainMenu.draw(renderer.get());
                break;

            case GameMainMenu::AppState::Playing:
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_EVENT_QUIT) {
                        isRunning = false;
                        break;
                    } 

                    if (event.type == SDL_EVENT_KEY_DOWN) {
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_SPACE:
                                gameMainMenu.status(GameMainMenu::AppState::MainMenu);
                                break;
                            case SDL_SCANCODE_RIGHT:
                                gameSettings.nextResolution();
                            case SDL_SCANCODE_RETURN:
                                gameSettings.applySettings(window.get(), renderer.get());
                            default:
                                break;
                        }
                    }
                }

                while (accumulator >= dt) {
                    Player->Tick(dt);
                    Level->Constraint(Player);
                    Camera->Tick(dt);
                    Camera->Clamp(Level->ScenarioBounds());

                    accumulator -= dt;
                }

                alpha = accumulator / dt;
                
                SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer.get());
                
                RenderView = Camera->CameraView();

                Level->Render(renderer.get(), RenderView);
                Player->Render(renderer.get(), RenderView);
                
                fps.update(alpha, (int)(1.0f / frameTime), font, renderer.get());
                fps.draw(renderer.get());
                break;

            case GameMainMenu::AppState::Quitting:
                isRunning = false;
                break;
        }

        SDL_RenderPresent(renderer.get());
    }

    delete Level; 
    delete Player;
    delete Camera; 
}

void GameWindow::getAvaliableDisplayResolutions() {
    int count = 0;
    SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    
    SDL_DisplayMode** modes = SDL_GetFullscreenDisplayModes(displayID, &count);

    if (modes) {
        std::cout << "Available Display Resolutions:\n";
        for (int i = 0; i < count; i++) {
            std::cout << i << ":" << modes[i]->w << " x " << "modes[i]->h" << std::endl;
        }
        
        SDL_free(modes);
    }
}

void GameWindow::setupWindow() {
    if (!TTF_Init()) {
        throw Exception("Error initializing fonts");
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw Exception("Video error:" + std::string(SDL_GetError()));
    }

    font = TTF_OpenFont(Paths::getInstance().FONT("leadcoat.ttf").c_str(), 24);

    if (!font) {
        throw Exception("Could not initialize font");
    }
}