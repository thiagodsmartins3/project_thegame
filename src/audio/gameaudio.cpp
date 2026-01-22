#include "../../include/audio/gameaudio.hpp"
#include "../../include/exception/exception.hpp"
#include "../../utility/paths.hpp"
#include <iostream>
#include <cstdlib>

GameAudio::GameAudio() {
    PaError error = Pa_Initialize();

    if (error != paNoError) {
        throw Exception("PortAudio error:" + std::string(Pa_GetErrorText(error)));
    }

    #ifdef DEBUG
    std::cout << "Audio initialized" << std::endl;
    #endif
}

GameAudio::~GameAudio() {
    PaError error = Pa_Terminate();

    if (error != paNoError) {
        std::cout << "Error terminating audio" << std::endl;
    }
}

void GameAudio::play() {
    if (audioFiles.empty()) {
        std::cout << "No files set to play" << std::endl;
    } else {
        audioWorkThread = std::thread(&GameAudio::playAudio, this);
    }
}

void GameAudio::pause() {
    // TODO: Will be implemented soon
}

void GameAudio::stop() {
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
    }
    
    if (audioWorkThread.joinable()) {
        audioWorkThread.join();
    }

    if (audioData.audioFile) {
        sf_close(audioData.audioFile);
    }
}

void GameAudio::setAudioFile(std::string file) {
    audioFiles.push_back(file);
}

void GameAudio::setAudioFiles(std::vector<std::string>& files) {
    if (audioFiles.empty()) {
        audioFiles = files;
    } else {
        for (auto it = files.begin(); it != files.end(); it++) {
            audioFiles.push_back(*it);
        }
    }

    #ifdef DEBUG
    std::cout << "Number of tracks to play: " << audioFiles.size() << std::endl;
    #endif
}

void GameAudio::startStream() {
    PaError error;

    error = Pa_StartStream(stream);

    if (error != paNoError) {
        throw Exception("PortAudio error:" + std::string(Pa_GetErrorText(error)));
    }

    while (Pa_IsStreamActive(stream) == 1) {
        #ifdef DEBUG
        audioProgress(audioData.currentPos, audioData.audioInfo.frames);
        #endif

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    cleanupTrack();
}

void GameAudio::playAudio() {
    for (auto it = audioFiles.begin(); it != audioFiles.end(); ++it) {
        try {
            initAudioData(*it);
        } catch (const Exception& ex) {
            std::cout << ex.what() << std::endl;
            continue;
        }

        try {
            initAudioBuffer();
        } catch (const Exception& ex) {
            std::cout << ex.what() << std::endl;
            continue;
        }

        try {
            std::cout << "Now playing: " << removePath(*it, Paths::getInstance().AUDIO()) << std::endl;
            startStream();
        } catch (const Exception& ex) {
            std::cout << ex.what() << std::endl;
            continue;
        }
    }
}

void GameAudio::initAudioBuffer() {
    stream = nullptr;
    std::string message;

    streamParameters.device = Pa_GetDefaultOutputDevice();
    streamParameters.channelCount = audioData.audioInfo.channels;
    streamParameters.sampleFormat = paFloat32;
    streamParameters.suggestedLatency = Pa_GetDeviceInfo(streamParameters.device)->defaultHighOutputLatency;
    streamParameters.hostApiSpecificStreamInfo = nullptr;

    error = Pa_OpenStream( 
        &stream,
        nullptr,
        &streamParameters,
        audioData.audioInfo.samplerate,
        paFramesPerBufferUnspecified,
        paClipOff,
        &GameAudio::AudioCallback,
        &audioData
    );
    
    if (error != paNoError) {
        throw Exception("PortAudio error:" + std::string(Pa_GetErrorText(error)));
    }
}

void GameAudio::initAudioData(std::string file) {
    audioData.audioFile = sf_open(file.c_str(), SFM_READ, &audioData.audioInfo);
    audioData.volume = 1.0f;
    audioData.isPaused = 0;

    if (audioData.audioFile == nullptr) {
        throw Exception("Sound file error:" + std::string(sf_strerror(audioData.audioFile)));
    }

    #ifdef DEBUG
    std::cout << "Sample Rate = " << audioData.audioInfo.samplerate << " Hz" << std::endl;
    std::cout << "Channels = " << audioData.audioInfo.channels << std::endl;
    std::cout << "Frames = " << audioData.audioInfo.frames << std::endl;
    #endif
}

void GameAudio::audioProgress(sf_count_t current, sf_count_t total) {
    int barWidth = 40;
    float progress = (float)current / total;
    
    std::cout << "\r[";

    int pos = barWidth * progress;

    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }

    std::cout << "] " << (int)(progress * 100) << "%" << std::flush;
}

std::string GameAudio::removePath(std::string filePath, std::string path) {
    std::string file = filePath;
    std::size_t pos = filePath.find(path);
    
    if (pos != std::string::npos) {
        return file.erase(pos, path.length());
    }

    return "";
}

void GameAudio::cleanupTrack() {
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
    }

    if (audioData.audioFile) {
        sf_close(audioData.audioFile);
    }
}