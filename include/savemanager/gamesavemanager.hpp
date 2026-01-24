#ifndef GAMESAVEMANAGER_HPP
#define GAMESAVEMANAGER_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <map>

class GameSaveManager {
    static constexpr char SaveConfigFile[] = "configs.json";
    static constexpr char SaveGameFile[] = "saves.json";
    
    public:
        enum class SaveType {
            CONFIG,
            GAME
        };

    public:
        GameSaveManager();
        void saveConfig(std::map<std::string, std::string> data);
        void loadConfig();
        void saveGame();
        void loadSaveGame();

    private:
        void createFolderIfNotExists();
        bool checkIfFileExists(GameSaveManager::SaveType type);
    
    // private:
    //     nlohmann::json saveFile;
    //     nlohmann::json saveConfigFile;
};

#endif