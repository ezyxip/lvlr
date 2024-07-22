#ifndef AUDIOCONTAINER_H
#define AUDIOCONTAINER_H

#include <vector>
namespace lvlr
{
    class AudioContainer
    {
    public:
        AudioContainer(int sample_rate, int channels, long long int total_frames, std::vector<float> data);
        ~AudioContainer();
        int getSampleRate();
        int getChannels();
        long long int getTotalFrames();
        float nextSample();

    protected:
        int currentSample;
        int sample_rate;
        int channels;
        long long int total_frames;
        std::vector<float> data;
    };
}

#endif