#ifndef GAMETEXTURE_HPP
#define GAMETEXTURE_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <memory>
#include "../../utility/sdldeleters.hpp"

class GameTexture {
    public:
        GameTexture(std::string& path, std::shared_ptr<SDL_Renderer>& rendererPtr);
        ~GameTexture();
        void loadFromFile(std::string path);
        void textureWidth(const float w);
        void textureHeight(const float h);
        float textureWidth() const;
        float textureHeight() const;
        void render(float x, float y);

    private:
        std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture;
        std::weak_ptr<SDL_Renderer> renderer;
        float width;
        float height;
};

#endif