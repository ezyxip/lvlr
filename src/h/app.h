#ifndef APP_H
#define APP_H

#include <string>
#include <sndfile.h>
#include <iostream>
#include <vector>

#include <AudioContainer.h>

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

    AudioContainer read_audio_file(std::string input_file);
}

#endif