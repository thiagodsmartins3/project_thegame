#include "../include/window/gamewindow.hpp"
#include "../include/exception/exception.hpp"
#include "../utility/paths.hpp"
#include "../include/audio/gameaudio.hpp"
#include <iostream>

int main() {
    GameAudio ga;
    ga.play();
    // std::unique_ptr<GameWindow> gw;
    // GameWindow::GameWindowInfo windowInfo = {
    //     "Test",
    //     800,
    //     600
    // };
        
    // try {
    //     gw = std::make_unique<GameWindow>(windowInfo);
    //     gw->run();
    // } catch (const Exception& ex) {
    //     std::cout << ex.what() << std::endl;
    // }

    return 0;
}