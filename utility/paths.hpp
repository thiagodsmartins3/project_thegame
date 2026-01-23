#ifndef PATHS_HPP
#define PATHS_HPP

#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_stdinc.h>
#include <string>
#include <iostream>

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

        std::string IMAGES(const std::string path) {
            return getBasePath() + "images/" + path;
        }

        std::string AUDIO() {
            return getBasePath() + "audio/";
        }

        std::string AUDIO(const std::string path) {
            return getBasePath() + "audio/" + path;
        }

        std::string FONT() {
            return getBasePath() + "font/";
        }
        
        std::string FONT(const std::string path) {
            return getBasePath() + "font/" + path;
        }

    private:
        Paths() {} 

        std::string getBasePath() {
            const char *path = SDL_GetBasePath();
            std::string basePath;

            if (path) {
                basePath = path;
            } else {
                std::cout << SDL_GetError() << std::endl;
                return "";
            }

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