#ifndef WAVETABLE_Bank_H_
#define WAVETABLE_Bank_H_

#include "../zic_wavetable_base.h"

class Wavetable_Bank : public Zic_Wavetable_Base
{
protected:
    float _table[16384] = {