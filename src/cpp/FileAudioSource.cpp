#include <FileAudioSource.h>

FileAudioSource::FileAudioSource(int sample_rate, int channels, long long int total_frames, std::vector<float> data)
    : sample_rate(sample_rate),
      channels(channels),
      total_frames(total_frames),
      data(data)
{
}

FileAudioSource::~FileAudioSource()
{
}

int FileAudioSource::getSampleRate()
{
    return sample_rate;
}

int FileAudioSource::getChannels(){
    return channels;
}

long long int FileAudioSource::getTotalFrames(){
    return total_frames;
}

float FileAudioSource::nextSample(){
    return data[currentSample++];
}