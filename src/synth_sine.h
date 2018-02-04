#ifndef SYNTH_SINE_H
#define SYNTH_SINE_H

#include "ceammc_object.h"

#include "SineSynth.hpp"

using namespace ceammc;

class SynthSine : public SoundExternal {
    SineSynth synth;

public:
    SynthSine(const PdArgs& args)
        : SoundExternal(args)
    {
        createSignalOutlet();
    };

    virtual void processBlock(const t_sample** in, t_sample** out) override
    {
        synth.process(out[0], blockSize());
    }

    virtual void onList(const AtomList& l) override
    {
        if (l.size() < 2)
            return;

        int list_size_2 = int(floor(l.size() / 2.0f));
        SinePartialData d(list_size_2);

        for (int i = 0; i < list_size_2; i++) {
            d.freq[i] = l.at(i * 2).asFloat();
            d.amp[i] = l.at(i * 2 + 1).asFloat();
        }

        synth.setData(d);
    }

    void m_clear(t_symbol* s, const AtomList& l)
    {
        synth.muteActivePartials();
    }
};

#endif // SYNTH_SINE_H
