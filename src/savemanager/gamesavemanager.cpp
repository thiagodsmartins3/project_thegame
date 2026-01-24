#include "../../include/savemanager/gamesavemanager.hpp"
#include "../../include/exception/exception.hpp"
#include "../../utility/paths.hpp"

GameSaveManager::GameSaveManager() {
    createFolderIfNotExists();
}

void GameSaveManager::saveConfig(std::map<std::string, std::string> data) {
    nlohmann::json jsonData;

    for (auto it = data.begin(); it != data.end(); ++it) {
        jsonData[it->first] = it->second;
    }

    std::ofstream saveFile(Paths::getInstance().SAVECONFIG(std::string(GameSaveManager::SaveConfigFile)));
    saveFile << std::setw(4) << jsonData << std::endl;
}

void GameSaveManager::saveGame() {
    // TODO: Add save when the game has first gameplay
    nlohmann::json jsonData;
}

void GameSaveManager::loadConfig() {
    nlohmann::json jsonData;

    if (checkIfFileExists(GameSaveManager::SaveType::CONFIG)) {
        std::ifstream readConfig(Paths::getInstance().SAVECONFIG(std::string(GameSaveManager::SaveConfigFile)));
        readConfig >> jsonData;
        std::cout << jsonData << std::endl;
    } else {
        std::cout << "No config file" << std::endl;
    }
}

void GameSaveManager::loadSaveGame() {
    // TODO: Add save when the game has first gameplay
}

void GameSaveManager::createFolderIfNotExists() {
    try {
        if (std::filesystem::create_directories(Paths::getInstance().SAVE())) {
            std::cout << "Save directory created" << std::endl;
        } else {
            std::cout << "File already exists" << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw Exception("Error: " + std::string(e.what()));
    }
}

bool GameSaveManager::checkIfFileExists(GameSaveManager::SaveType type) {
    switch (type) {
    case GameSaveManager::SaveType::CONFIG:
        if (std::filesystem::exists(Paths::getInstance().SAVECONFIG(GameSaveManager::SaveConfigFile))) {
            return true;
        } else {
            return false;
        }
    case GameSaveManager::SaveType::GAME:
        if (std::filesystem::exists(Paths::getInstance().SAVECONFIG(GameSaveManager::SaveGameFile))) {
            return true;
        } else {
            return false;
        }
    }
}
