#ifndef CONTODEFPROCESS_H
#define CONTODEFPROCESS_H

#include <AudioProcess.h>
#include <AudioContainer.h>

#include <portaudio.h>

namespace lvlr
{
    struct ConToDefProcessData{
        std::shared_ptr<lvlr::Filter> filter;
        std::shared_ptr<lvlr::AudioContainer> containter;
    };

    class ConToDefProcess : public AudioProcess
    {
    public:
        std::shared_ptr<lvlr::Filter> filter;
        std::shared_ptr<lvlr::AudioContainer> containter;

        ConToDefProcess(std::shared_ptr<lvlr::Filter> filter, std::shared_ptr<lvlr::AudioContainer> containter);
        ~ConToDefProcess();
        void setFilter(std::shared_ptr<lvlr::Filter> filter) override;
        void run() override;
        bool isDone() override;
        void wait() override;

    protected:
        PaStream* pa_stream;
        ConToDefProcessData data;
    };

    int container_to_def_callback(
        const void *input,
        void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);
};

#endif