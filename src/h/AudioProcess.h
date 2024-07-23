#ifndef AUDIOPROCESS_H
#define AUDIOPROCESS_H

#include <memory>
#include <DSPFilter.h>

namespace lvlr
{
    class AudioProcess
    {
    public:
        virtual void run() = 0;
        virtual void setFilter(std::shared_ptr<lvlr::Filter> filter) = 0;
        virtual bool isDone() = 0;
        virtual void wait() = 0;
    };
}

#endif