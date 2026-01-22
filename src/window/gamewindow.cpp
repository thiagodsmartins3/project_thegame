#include "../../include/window/gamewindow.hpp"
#include "../../include/texture/gametexture.hpp"
#include "../exception/exception.hpp"
#include "../../utility/paths.hpp"
#include <iostream>

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

    SDL_Quit();
}

void GameWindow::run() {
    isRunning = true;
    std::string path = Paths::getInstance().IMAGES("cat_img.png");
    GameTexture gt(path, renderer);

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.get());
        gt.render(100, 100);
        SDL_RenderPresent(renderer.get());
    }
}

void GameWindow::setupWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw Exception("Video error:" + std::string(SDL_GetError()));
    }
}