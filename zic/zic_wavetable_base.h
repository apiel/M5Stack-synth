#ifndef ZIC_WAVETABLE_BASE_H_
#define ZIC_WAVETABLE_BASE_H_

class Zic_Wavetable_Base
{
public:
    float *table;
    uint16_t size;
    uint16_t sampleCount;

    Zic_Wavetable_Base(float *_table, uint16_t _sampleCount, uint16_t _size)
    {
        table = _table;
        size = _size;
        sampleCount = _sampleCount;
    }
};

#endif
