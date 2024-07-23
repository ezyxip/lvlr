#ifndef DSPFILTER_H
#define DSPFILTER_H

namespace lvlr
{
    class Filter
    {
    public:
        virtual float process(float sample) = 0;
    };
}

#endif