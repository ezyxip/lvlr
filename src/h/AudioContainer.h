#ifndef FILEAUDIOSOURCE_H
#define FILEAUDIOSOURCE_H

#include <vector>

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

#endif