#include <stdexcept>
#include <functional>
#include <ContainerAudioSource.h>
#include <portaudio.h>

lvlr::ContainerAudioSource::ContainerAudioSource(std::shared_ptr<lvlr::Filter> filter, lvlr::AudioContainer containter, PaStreamCallback callback)
    : filter(filter),
      containter(containter),
      callback(callback)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio init exception: " + std::string(Pa_GetErrorText(err)));
    }
    auto stream = pa_stream.get();

    err = Pa_OpenDefaultStream(
        &stream,
        0,
        containter.getChannels(),
        paFloat32,
        containter.getSampleRate(),
        paFramesPerBufferUnspecified,
        callback,
        this);

    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio stream creating exception: " + std::string(Pa_GetErrorText(err)));
    }
}

void lvlr::ContainerAudioSource::setFilter(std::shared_ptr<lvlr::Filter> filter)
{
    this->filter = filter;
}

void lvlr::ContainerAudioSource::run()
{
    PaError err = Pa_StartStream(pa_stream.get());
    if (err != paNoError)
    {
        throw std::runtime_error("PortAudio stream starting exception: " + std::string(Pa_GetErrorText(err)));
    }
}

bool lvlr::ContainerAudioSource::isDone()
{
    return Pa_IsStreamActive(pa_stream.get()) != 1;
}

void lvlr::ContainerAudioSource::wait()
{
    while (!isDone())
    {
        Pa_Sleep(100);
    }
}

lvlr::ContainerAudioSource::~ContainerAudioSource()
{
    Pa_StopStream(pa_stream.get());
    Pa_CloseStream(pa_stream.get());
    Pa_Terminate();
}

int lvlr::container_to_std_dinamic_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *audioManager)
{
    ContainerAudioSource* data = static_cast<ContainerAudioSource*>(audioManager);
    AudioContainer* audioData = &data->containter;
    float *out = static_cast<float *>(output);

    for (size_t i = 0; i < frameCount; ++i)
    {
        if (audioData->getPosition() >= audioData->getTotalFrames())
        {
            return paComplete;
        }
        for (int ch = 0; ch < audioData->getChannels(); ++ch)
        {
            *out++ = audioData->nextSample();
        }
        
    }
    return paContinue;
}