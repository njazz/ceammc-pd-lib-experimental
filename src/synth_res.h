#ifndef SYNTH_SINE_H
#define SYNTH_SINE_H

#include "ceammc_object.h"

#include "ResSynth.hpp"

using namespace ceammc;

class SynthRes : public SoundExternal {
    ResSynth synth;

public:
    SynthRes(const PdArgs& args)
        : SoundExternal(args)
    {
        createSignalOutlet();
    };

    virtual void processBlock(const t_sample** in, t_sample** out) override
    {
        synth.process(in[0], out[0], blockSize());
    }

    virtual void onList(const AtomList& l) override
    {
        if (l.size() < 3)
            return;

        int list_size_2 = int(floor(l.size() / 3.0f));
        ResPartialData d(list_size_2);

        for (int i = 0; i < list_size_2; i++) {
            d.freq[i] = l.at(i * 3).asFloat();
            d.decay[i] = l.at(i * 3 + 1).asFloat();
            d.gain[i] = l.at(i * 3 + 2).asFloat();

        }

        synth.setData(d);
    }

    void m_clear(t_symbol* s, const AtomList& l)
    {
        synth.muteActivePartials();
    }
};

#endif // SYNTH_SINE_H
