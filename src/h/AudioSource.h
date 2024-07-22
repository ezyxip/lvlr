#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

class AudioSource{
    public:
    virtual int getSampleRate() = 0;
    virtual int getChannels() = 0;
    virtual float nextSample() = 0;
};

#endif