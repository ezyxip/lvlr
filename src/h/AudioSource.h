#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <memory>
#include <DSPFilter.h>

namespace lvlr
{
    class AudioSource
    {
    public:
        virtual void run() = 0;
        virtual void setFilter(std::shared_ptr<lvlr::Filter> filter) = 0;
    };
}

#endif