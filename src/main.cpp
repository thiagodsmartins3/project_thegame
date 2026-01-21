#include "../include/window/gamewindow.hpp"
#include "../include/exception/exception.hpp"
#include "../utility/paths.hpp"
#include "../include/audio/gameaudio.hpp"
#include <iostream>

int main() {
    GameAudio ga;

    std::vector<std::string> files = {
        Paths::getInstance().AUDIO("sound_test1.wav"),
        Paths::getInstance().AUDIO("sound_test2.wav"),
        Paths::getInstance().AUDIO("sound_test3.wav")
    };

    ga.setAudioFiles(files);
    ga.play();

    // std::cin.get();

    // ga.stop();

    std::unique_ptr<GameWindow> gw;
    GameWindow::GameWindowInfo windowInfo = {
        "Test",
        800,
        600
    };
        
    try {
        gw = std::make_unique<GameWindow>(windowInfo);
        gw->run();
    } catch (const Exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    
    return 0;
}