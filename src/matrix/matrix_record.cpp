#include "synth_sine.h"
#include "ceammc_factory.h"

using namespace ceammc;

SynthSine::SynthSine(const PdArgs& args)
    : SoundExternal(args)
{
    createSignalOutlet();
};

void SynthSine::processBlock(const t_sample** in, t_sample** out)
{
    synth.process(out[0], blockSize());
}

void SynthSine::onList(const AtomList& l)
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

void SynthSine::m_clear(t_symbol* s, const AtomList& l)
{
    synth.muteActivePartials();
}

// ==========

extern "C" {
void setup_synth0x2esine()
{
    SoundExternalFactory<SynthSine> f("synth.sine~");

    f.addMethod("clear", &SynthSine::m_clear);
}
}
