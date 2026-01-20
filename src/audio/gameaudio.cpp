#include "../../include/audio/gameaudio.hpp"
#include "../../include/exception/exception.hpp"
#include "../../utility/paths.hpp"
#include <iostream>
#include <cstdlib>

GameAudio::GameAudio() {
    try {
        initAudioData();
        initAudioBuffer();
    } catch (const Exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

GameAudio::~GameAudio() {
    PaError error = Pa_Terminate();

    if (error != paNoError) {
        std::cout << "Error terminating audio" << std::endl;
    }
}

void GameAudio::play() {
    PaError error;

    error = Pa_StartStream(stream);

    if (error != paNoError) {
        throw Exception("PortAudio error:" + std::string(Pa_GetErrorText(error)));
    }

    while (Pa_IsStreamActive(stream) == 1) {
        #ifdef DEBUG
        audioProgress(audioData.currentPos, audioData.audioInfo.frames);
        #endif

        Pa_Sleep(100); 
    }

    Pa_CloseStream(stream);
    sf_close(audioData.audioFile);
}

void GameAudio::initAudioBuffer() {
    PaError error = Pa_Initialize();
    stream = nullptr;
    std::string message;

    if (error != paNoError) {
        throw Exception("PortAudio error:" + std::string(Pa_GetErrorText(error)));
    }

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

void GameAudio::initAudioData() {
    std::string path = Paths::getInstance().AUDIO("sound_test.wav");
    audioData.audioFile = sf_open(path.c_str(), SFM_READ, &audioData.audioInfo);

    if (audioData.audioFile == nullptr) {
        throw Exception("Sound file error:" + std::string(sf_strerror(audioData.audioFile)));
    }

    audioData.volume = 1.0f;

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