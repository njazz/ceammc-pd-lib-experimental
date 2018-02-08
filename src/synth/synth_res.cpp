#include "synth_res.h"
#include "ceammc_factory.h"

using namespace ceammc;

SynthRes::SynthRes(const PdArgs& args)
    : SoundExternal(args)
{
    createSignalOutlet();
};

 void SynthRes::processBlock(const t_sample** in, t_sample** out)
{
    synth.process(in[0], out[0], blockSize());
}

 void SynthRes::onList(const AtomList& l)
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

void SynthRes::m_clear(t_symbol* s, const AtomList& l)
{
    synth.muteActivePartials();
}

// ==========

extern "C" {
void setup_synth0x2eres()
{
    SoundExternalFactory<SynthRes> f("synth.res~");

        f.addMethod("clear", &SynthRes::m_clear);
}
}
