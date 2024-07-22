#ifndef FILTER_H
#define FILTER_H

namespace lvlr
{
    class Filter
    {
    public:
        virtual float process(float sample);
    };
}

#endif