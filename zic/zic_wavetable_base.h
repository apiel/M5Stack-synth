#ifndef ZIC_WAVETABLE_BASE_H_
#define ZIC_WAVETABLE_BASE_H_

class Zic_Wavetable_Base
{
public:
    int16_t *table;
    uint16_t size;
    uint16_t sampleCount;

    Zic_Wavetable_Base(int16_t *_table, uint16_t _sampleCount, uint16_t _size)
    {
        table = _table;
        size = _size;
        sampleCount = _sampleCount;
    }
};

#endif
