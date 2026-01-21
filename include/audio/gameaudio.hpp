#ifndef GAMEAUDIO_HPP
#define GAMEAUDIO_HPP

#include <string>
#include <memory>
#include <iostream>
#include <portaudio.h>
#include <sndfile.h>
#include <vector>

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

        if (data->isPaused) {
            for (int i = 0; i < framesPerBuffer * data->audioInfo.channels; i++) {
                out[i] = 0.0f;
            }
            return paContinue;
        }

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
        void pause();
        void stop();
        void setAudioFile(std::string file);
        void setAudioFiles(std::vector<std::string>& files);

    private:
        typedef struct {
            SNDFILE *audioFile;
            SF_INFO audioInfo;
            float volume;          
            sf_count_t currentPos;
            int isPaused; 
            int skipRequested;
        } AudioData;

        void initAudioBuffer();
        void initAudioData(std::string file);
        void audioProgress(sf_count_t current, sf_count_t total);
        std::string removePath(std::string filePath, std::string path);
        void playAudio();
        void startStream();

    private:
        PaStream* stream;
        PaStreamParameters streamParameters;
        AudioData audioData;
        std::vector<std::string> audioFiles;
};

#endif