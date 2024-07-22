#include <app.h>
#include <fstream>

bool checkfile(std::string filepath)
{
    std::ifstream file(filepath);
    return file.good();
}

bool check_input_file(std::string filepath)
{
    return checkfile(filepath);
}

bool check_output_file(std::string filepath)
{
    return checkfile(filepath);
}

bool check_filter_file(std::string filepath)
{
    return checkfile(filepath);
}

AudioData read_audio_file(std::string input_file)
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

    AudioData audioData = {
        0, info.frames, info.samplerate, info.channels
    };
    

    audioData.buffer.resize(num_samples);

    sf_count_t read_count = sf_read_float(file, audioData.buffer.data(), num_samples);

    if (read_count != num_samples)
    {
        std::cerr << "Warning: read " << read_count << " samples, expected " << num_samples << std::endl;
    }

    return audioData;
}

void conf_options(std::map<std::string, std::string> &keys, CLI::App &app)
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
}

int pa_stream_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    AudioData *audioData = static_cast<AudioData *>(userData);
    float *out = static_cast<float *>(output);

    for (size_t i = 0; i < frameCount; ++i)
    {
        if (audioData->position >= audioData->totalFrames)
        {
            return paComplete;
        }
        for (int ch = 0; ch < audioData->channels; ++ch)
        {
            *out++ = audioData->filter.process(audioData->buffer[audioData->position * audioData->channels + ch]);
            // *out++ = audioData->buffer[audioData->position * audioData->channels + ch];
        }
        ++audioData->position;
    }
    return paContinue;
}