#ifndef SDLDELETERS_HPP
#define SDLDELETERS_HPP

struct SDLWindowDeleter {
    void operator()(SDL_Window* windowPtr) const {
        if (windowPtr) {
            SDL_DestroyWindow(windowPtr);
        }
    }
};

struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surfacePtr) const {
        if (surfacePtr) {
            SDL_DestroySurface(surfacePtr);
        }
    }
};

struct SDLRendererDeleter {
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

struct SDLTextureDeleter {
    void operator()(SDL_Texture* texture) const {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
};


#endif