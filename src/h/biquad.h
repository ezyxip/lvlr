#ifndef Biquad_h
#define Biquad_h
#include <filter.h>

enum {
    bq_type_lowpass = 0,
    bq_type_highpass,
    bq_type_bandpass,
    bq_type_notch,
    bq_type_peak,
    bq_type_lowshelf,
    bq_type_highshelf
};

class BiquadFilter : public Filter{
public:
    BiquadFilter();
    BiquadFilter(int type, double Fc, double Q, double peakGainDB);
    ~BiquadFilter();
    void setType(int type);
    void setQ(double Q);
    void setFc(double Fc);
    void setPeakGain(double peakGainDB);
    void setBiquad(int type, double Fc, double Q, double peakGainDB);
    float process(float in) override;
    
protected:
    void calcBiquad(void);

    int type;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
};

#endif // Biquad_h