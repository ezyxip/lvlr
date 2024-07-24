#include <stdexcept>
#include <functional>
#include <ConToDefProcess.h>
#include <Biquad.h>
#include <portaudio.h>

lvlr::ConToDefProcess::ConToDefProcess(std::shared_ptr<lvlr::Filter> filter, std::shared_ptr<lvlr::AudioContainer> containter)
    : filter(filter),
      containter(containter)
{
    this->data = lvlr::ConToDefProcessData{filter, containter};

    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio init exception: " + std::string(Pa_GetErrorText(err)));
    }

    err = Pa_OpenDefaultStream(
        &pa_stream,
        0,
        1,
        paFloat32,
        containter->getSampleRate(),
        paFramesPerBufferUnspecified,
        container_to_def_callback,
        &data);

    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio stream creating exception: " + std::string(Pa_GetErrorText(err)));
    }
}

void lvlr::ConToDefProcess::setFilter(std::shared_ptr<lvlr::Filter> filter)
{
    this->filter = filter;
}

void lvlr::ConToDefProcess::run()
{
    PaError err = Pa_StartStream(pa_stream);
    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio stream starting exception: " + std::string(Pa_GetErrorText(err)));
    }
}

bool lvlr::ConToDefProcess::isDone()
{
    return Pa_IsStreamActive(pa_stream) != 1;
}

void lvlr::ConToDefProcess::wait()
{
    while (Pa_IsStreamActive(pa_stream) == 1)
    {
        Pa_Sleep(100);
    }
}

lvlr::ConToDefProcess::~ConToDefProcess()
{
    Pa_StopStream(pa_stream);
    Pa_CloseStream(pa_stream);
    Pa_Terminate();
}

int lvlr::container_to_def_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *audioManager)
{
    ConToDefProcessData* data = static_cast<ConToDefProcessData*>(audioManager);
    auto audioData = data->containter;
    auto filter = data->filter;
    float *out = static_cast<float *>(output);

    for (size_t i = 0; i < frameCount; ++i)
    {
        if (audioData->getPosition() >= audioData->getTotalFrames() * audioData->getChannels() - 1)
        {
            return paComplete;
        }
        float sample = 0;
        for(int j = 0; j < audioData->getChannels(); j++){
            sample += audioData->nextSample();
        }
        *out++ = filter->process(sample);
    }
    return paContinue;
}