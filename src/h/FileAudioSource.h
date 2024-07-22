#ifndef FILEAUDIOSOURCE_H
#define FILEAUDIOSOURCE_H

#include <vector>
#include <AudioSource.h>

class FileAudioSource : public AudioSource
{
public:
    FileAudioSource(int sample_rate, int channels, long long int total_frames, std::vector<float> data);
    ~FileAudioSource();
    int getSampleRate() override;
    int getChannels() override;
    long long int getTotalFrames();
    float nextSample() override;

protected:
    int currentSample;
    int sample_rate;
    int channels;
    long long int total_frames;
    std::vector<float> data;
};

#endif