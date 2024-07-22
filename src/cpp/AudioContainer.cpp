#include <AudioContainer.h>

using namespace lvlr;

AudioContainer::AudioContainer(int sample_rate, int channels, long long int total_frames, std::vector<float> data)
    : sample_rate(sample_rate),
      channels(channels),
      total_frames(total_frames),
      data(data)
{
}

AudioContainer::~AudioContainer()
{
}

int AudioContainer::getSampleRate()
{
    return sample_rate;
}

int AudioContainer::getChannels(){
    return channels;
}

long long int AudioContainer::getTotalFrames(){
    return total_frames;
}

float AudioContainer::nextSample(){
    return data[currentSample++];
}