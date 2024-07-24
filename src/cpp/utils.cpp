#include <app.h>
#include <fstream>

using namespace lvlr;

bool checkfile(std::string filepath)
{
    std::ifstream file(filepath);
    return file.good();
}

bool lvlr::check_input_file(std::string filepath)
{
    return checkfile(filepath);
}

bool lvlr::check_output_file(std::string filepath)
{
    return checkfile(filepath);
}

bool lvlr::check_filter_file(std::string filepath)
{
    return checkfile(filepath);
}

AudioContainer lvlr::read_audio_file(std::string input_file)
{
    SF_INFO info;
    info.format = 0;
    SNDFILE *file = sf_open(input_file.c_str(), SFM_READ, &info);

    if (!file)
    {
        std::cerr << "error";
        std::cerr << "Error: " << sf_strerror(file) << std::endl;
        throw std::runtime_error("Something went wrong");
    }

    int num_samples = info.frames * info.channels;

    AudioData audioData;
    audioData.sampleRate = info.samplerate;
    audioData.channels = info.channels;
    audioData.totalFrames = info.frames;
    audioData.position = 0;

    audioData.buffer.resize(num_samples);

    sf_count_t read_count = sf_read_float(file, audioData.buffer.data(), num_samples);

    if (read_count != num_samples)
    {
        std::cerr << "Warning: read " << read_count << " samples, expected " << num_samples << std::endl;
    }

    return AudioContainer(
        audioData.sampleRate,
        audioData.channels,
        audioData.totalFrames,
        audioData.buffer);
}

void lvlr::conf_options(std::map<std::string, std::string> &keys, CLI::App &app)
{
    app.add_option("--file-input", [&](std::vector<std::string> strs) -> bool
                   {
        bool res = true;
        keys["finput"] = strs[0];
        return check_input_file(strs[0]); }, "Input audiofile path")
        ->required();

    app.add_option("--file-output", [&](std::vector<std::string> strs) -> bool
                   {
        bool res = true;
        keys["foutput"] = strs[0];
        return check_output_file(strs[0]); }, "Output audiofile path");

    app.add_option("--filter", [&](std::vector<std::string> strs) -> bool
                   {
        bool res = true;
        keys["ffilter"] = strs[0];
        return check_filter_file(strs[0]); }, "Filter .yaml file path");

    app.add_option("--db", [&](std::vector<std::string> strs) -> bool
                   {
        bool res = true;
        keys["db"] = strs[0];
        return true; }, "Gain, dB")
        ->required();
}
