#include <m_pd.h>

#include "sdif_lib.h"

extern "C" {

#include <stdlib.h>

extern void setup_sdif0x2efile();
extern void setup_sdif0x2eframe();
extern void setup_sdif0x2ematrix();

extern void setup_sdif0x2e1trc();
extern void setup_sdif0x2e1trc_merge();

extern void setup_synth0x2esine();
extern void setup_synth0x2eres();

extern void setup_list0x2edo();

extern void setup_mlist();
extern void setup_mlist_unpack();

extern void setup_mlist0x2ellll();
extern void setup_mlist0x2eflat();

extern void setup_mlist0x2eflip();

extern void setup_json();
extern void setup_json_dict();

extern void setup_json_recorder();

extern void setup_image();

extern void setup_conv_image_mlist();
extern void setup_conv_mlist_image();

extern void setup_conv_json_mlist();
extern void setup_conv_mlist_json();

extern void setup_conv_json_list();
extern void setup_conv_list_json();

extern void setup_conv_matrix_image();
extern void setup_conv_image_matrix();

extern void setup_matrix();
}

extern "C" void setup()
{
    post("%s", "[SDIF library]");

    setup_sdif0x2efile();
    setup_sdif0x2eframe();
    setup_sdif0x2ematrix();

    setup_sdif0x2e1trc();
    setup_sdif0x2e1trc_merge();

    setup_synth0x2esine();
    setup_synth0x2eres();

    setup_list0x2edo();

    setup_mlist();
    setup_mlist_unpack();

    setup_mlist0x2ellll();
    setup_mlist0x2eflat();

    setup_mlist0x2eflip();

    setup_json();
    setup_json_dict();

    setup_json_recorder();

    setup_image();

    setup_conv_image_mlist();
    setup_conv_mlist_image();

    setup_conv_json_mlist();
    setup_conv_mlist_json();

    setup_conv_json_list();
    setup_conv_list_json();

    setup_conv_matrix_image();
    setup_conv_image_matrix();

    setup_matrix();
}
