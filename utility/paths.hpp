#ifndef PATHS_HPP
#define PATHS_HPP

#include <SDL3/SDL_filesystem.h>
#include <string>

class Paths {
    public:
        Paths(const Paths&) = delete;
        void operator=(const Paths&) = delete;

        static Paths& getInstance() {
            static Paths instance;
            
            return instance;
        }

        std::string ASSETS() {      
            return getBasePath();
        }

        std::string IMAGES() {
            return getBasePath() + "images/";
        }

        std::string SOUND() {
            return getBasePath() + "sound/";
        }

    private:
        Paths() {} 

        std::string getBasePath() {
            std::string basePath = SDL_GetBasePath();
            size_t foundBuild = basePath.find("build");
            size_t foundBin = basePath.find("bin");
            
            if (foundBuild != std::string::npos) {
                return "../../assets/"; 
            } else if (foundBin != std::string::npos) {
                return "../assets/";
            } else {
                return basePath + "assets/";
            }
        }

    private:
        std::string assets;
};

#endif