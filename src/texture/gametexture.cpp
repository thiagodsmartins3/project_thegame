#include "../../include/texture/gametexture.hpp"
#include "../../include/exception/exception.hpp"
#include <iostream>

GameTexture::GameTexture(std::string& path, std::shared_ptr<SDL_Renderer>& rendererPtr) {
    renderer = rendererPtr;
    loadFromFile(path);
}

GameTexture::~GameTexture() {
    if (texture) {
        SDL_DestroyTexture(texture.get());
    }
}

void GameTexture::loadFromFile(std::string path) {
    if (texture) {
        SDL_DestroyTexture(texture.get());
    }

    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == nullptr) {
        throw Exception("Surface error:" + std::string(SDL_GetError()));
    }

    texture = std::unique_ptr<SDL_Texture, SDLTextureDeleter>(
        SDL_CreateTextureFromSurface((renderer.lock()).get(), surface),
        SDLTextureDeleter()
    );

    if (texture == nullptr) {
        throw Exception("Texture error:" + std::string(SDL_GetError()));
    }
    
    width = surface->w;
    height = surface->h;

    SDL_DestroySurface(surface);
}

void GameTexture::textureWidth(const float w) {
    width = w;
}

void GameTexture::textureHeight(const float h) {
    height = h;
}

float GameTexture::textureWidth() const {
    return  width;
}

float GameTexture::textureHeight() const {
    return height;
}

void GameTexture::render(float x, float y) {
    SDL_FRect dstRect{ x, y, static_cast<float>(width), static_cast<float>(height) };
    SDL_RenderTexture((renderer.lock()).get(), texture.get(), nullptr, &dstRect);
}