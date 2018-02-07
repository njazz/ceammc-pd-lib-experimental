#include "synth_res.h"
#include "ceammc_factory.h"

using namespace ceammc;

extern "C" {
void setup_synth0x2eres()
{
    SoundExternalFactory<SynthRes> f("synth.res~");

        f.addMethod("clear", &SynthRes::m_clear);
}
}
