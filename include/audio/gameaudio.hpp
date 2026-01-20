#ifndef GAMEAUDIO_HPP
#define GAMEAUDIO_HPP

#include <string>
#include <memory>
#include <iostream>
#include <portaudio.h>
#include <sndfile.h>

#define TABLE_SIZE 200

class GameAudio {
    static int AudioCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData) {
        
        AudioData *data = (AudioData*)userData;
        float *out = (float*)outputBuffer;
        sf_count_t framesRead;

        framesRead = sf_readf_float(data->audioFile, out, framesPerBuffer);

        for (int i = 0; i < framesRead * data->audioInfo.channels; i++) {
            out[i] *= data->volume;
        }

        data->currentPos += framesRead;

        if (framesRead < framesPerBuffer) {
            return paComplete; 
        }

        return paContinue;
    }

    public:
        GameAudio();
        ~GameAudio();
        void play();
        void stop();

    private:
        typedef struct {
            SNDFILE *audioFile;
            SF_INFO audioInfo;
            float volume;          
            sf_count_t currentPos;
        } AudioData;

        void initAudioBuffer();
        void initAudioData();
        void audioProgress(sf_count_t current, sf_count_t total);

    private:
        PaStream* stream;
        PaStreamParameters streamParameters;
        AudioData audioData;
};

#endif