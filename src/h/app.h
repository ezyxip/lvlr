#ifndef APP_H
#define APP_H

#include <string>
#include <sndfile.h>
#include <iostream>
#include <vector>
#include <CLI/CLI.hpp>
#include <portaudio.h>

namespace lvlr
{
    struct AudioData
    {
        std::vector<float> buffer;
        size_t position;
        size_t totalFrames;
        int sampleRate;
        int channels;
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
}

#endif