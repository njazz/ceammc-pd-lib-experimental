#ifndef SYNTH_SINE_H
#define SYNTH_SINE_H

#include "ceammc_object.h"

#include "SineSynth.hpp"

using namespace ceammc;

class SynthSine : public SoundExternal {
    SineSynth synth;

public:
    SynthSine(const PdArgs& args);

    virtual void processBlock(const t_sample** in, t_sample** out) override;

    virtual void onList(const AtomList& l) override;
    void m_clear(t_symbol* s, const AtomList& l);
};

#endif // SYNTH_SINE_H
