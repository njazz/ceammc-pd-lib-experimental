#include <m_pd.h>

#include "sdif_lib.h"

extern "C" {

#include <stdlib.h>

extern void setup_sdif0x2efile();
extern void setup_sdif0x2eframe();
extern void setup_sdif0x2ematrix();

extern void setup_synth0x2esine();
}

extern "C" void setup()
{
    post("%s", "SDIF objects");

    setup_sdif0x2efile();
    setup_sdif0x2eframe();
    setup_sdif0x2ematrix();

    setup_synth0x2esine();
}
