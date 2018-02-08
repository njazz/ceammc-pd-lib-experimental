#include <m_pd.h>

#include "sdif_lib.h"

extern "C" {

#include <stdlib.h>

extern void setup_sdif0x2efile();
extern void setup_sdif0x2eframe();
extern void setup_sdif0x2ematrix();

extern void setup_sdif0x2e1trc();

extern void setup_synth0x2esine();
extern void setup_synth0x2eres();

extern void setup_mlist();
extern void setup_mlist_unpack();

extern void setup_mlist0x2ellll();
extern void setup_mlist0x2eflat();

extern void setup_mlist0x2eflip();

extern void setup_json();

extern void setup_mlist_image();
}

extern "C" void setup()
{
    post("%s", "[SDIF library]");

    setup_sdif0x2efile();
    setup_sdif0x2eframe();
    setup_sdif0x2ematrix();

    setup_sdif0x2e1trc();

    setup_synth0x2esine();
    setup_synth0x2eres();

    setup_mlist();
    setup_mlist_unpack();

    setup_mlist0x2ellll();
    setup_mlist0x2eflat();

    setup_mlist0x2eflip();

    setup_json();

    setup_mlist_image();
}
