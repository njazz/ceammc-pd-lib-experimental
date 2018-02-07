#include <m_pd.h>

#include "sdif_lib.h"

extern "C" {

#include <stdlib.h>

extern void setup_sdif0x2efile();
extern void setup_sdif0x2eframe();
extern void setup_sdif0x2ematrix();

extern void setup_synth0x2esine();
extern void setup_synth0x2eres();

extern void setup_sublist();
//extern void setup_sublist0x2eflat();
extern void setup_sublist0x2ellll();
}

extern "C" void setup()
{
    post("%s", "SDIF objects");

    setup_sdif0x2efile();
    setup_sdif0x2eframe();
    setup_sdif0x2ematrix();

    setup_synth0x2esine();
    setup_synth0x2eres();

    setup_sublist();
    //setup_sublist0x2eflat();
    setup_sublist0x2ellll();
}
