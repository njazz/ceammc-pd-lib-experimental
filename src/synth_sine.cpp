#include "synth_sine.h"
#include "ceammc_factory.h"

using namespace ceammc;

extern "C" {
void setup_synth0x2esine()
{
    SoundExternalFactory<SynthSine> f("synth.sine~");

        f.addMethod("clear", &SynthSine::m_clear);
}
}
