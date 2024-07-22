#ifndef FILEAUDIOSOURCE_H
#define FILEAUDIOSOURCE_H

#include <AudioSource.h>
#include <AudioContainer.h>

#include <portaudio.h>

namespace lvlr
{
    class ContainerAudioSource : public AudioSource
    {
    public:
        ContainerAudioSource(std::shared_ptr<lvlr::Filter> filter, lvlr::AudioContainer containter, PaStreamCallback callback);
        ~ContainerAudioSource();
        void setFilter(std::shared_ptr<lvlr::Filter> filter) override;
        void run() override;
        bool isDone() override;
        void wait() override;

    protected:
        PaStreamCallback *callback;
        std::shared_ptr<lvlr::Filter> filter;
        lvlr::AudioContainer containter;
        std::shared_ptr<PaStream> pa_stream;
    };

    int container_to_std_dinamic_callback(
        const void *input,
        void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);
}

#endif