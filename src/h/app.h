#ifndef APP_H
#define APP_H

#include <string>
#include <sndfile.h>
#include <iostream>
#include <vector>

#include <biquad.h>

#include <CLI/CLI.hpp>
#include <portaudio.h>

class AudioData
{
public:
    AudioData(
        size_t position,
        long long int totalFrames,
        int sampleRate,
        int channels
    )
    {
        this->position = position;
        this->totalFrames = totalFrames;
        this->sampleRate = sampleRate;
        this->channels = channels;

        // filter = BiquadFilter(bq_type_lowshelf, 1000.0 / sampleRate, 1, -20);
        filter = BiquadFilter();
        filter.setBiquad(bq_type_lowpass, 1000.0 / sampleRate, 1.3, 50);
        
    }
    std::vector<float> buffer;
    size_t position;
    size_t totalFrames;
    int sampleRate;
    int channels;
    BiquadFilter filter;
};

void conf_options(std::map<std::string, std::string> &keys, CLI::App &app);

bool check_input_file(std::string filepath);
bool check_output_file(std::string filepath);
bool check_filter_file(std::string filepath);

AudioData read_audio_file(std::string input_file);

int pa_stream_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData);
#endif