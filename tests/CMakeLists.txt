INCLUDE_DIRECTORIES(.)

#lol:
#set (SDIFLIB
#    ../miniSDIF/src/mSDIFFile.cpp
#    ../miniSDIF/src/mSDIFFrame.cpp
#    ../miniSDIF/src/mSDIFMatrix.cpp
#    ../miniSDIF/src/mSDIFTypes.cpp
#    )

#set (SYNTH
#    ../PartialSynth/src/BasePartial.cpp
#    ../PartialSynth/src/SinePartial.cpp
#    ../PartialSynth/src/ResPartial.cpp
#    ../PartialSynth/src/SineSynth.cpp
#    ../PartialSynth/src/ResSynth.cpp
#    )

#set (SOURCES
#    sdif_lib.cpp
#    )

#set (SRC_SDIF

#    src/sdif/sdif_file.cpp
#    src/sdif/sdif_frame.cpp
#    src/sdif/sdif_matrix.cpp

#    src/sdif/sdif_data_types.cpp

#    src/sdif/sdif_1trc.cpp
#    )

#set (SRC_SYNTH
#    src/synth/synth_sine.cpp
#    src/synth/synth_res.cpp
#    )

set (SRC_MLIST

#    ../src/mlist/mlist_obj.cpp
#    src/mlist/mlist_unpack.cpp

#    src/mlist/mlist_flip.cpp

    ../src/mlist/mlist_data_type.cpp
    )

set (SRC_JSON
    ../src/json/json_data_type.cpp
#    src/json/mstring_data_type.cpp

#    src/json/json_obj.cpp

#    src/json/json_dict.cpp

    )

set (SRC_IMG
#    src/img/image_obj.cpp

    ../src/img/image_data_type.cpp
    )

set (SRC_CONV

#    ../src/conv/mlist_llll.cpp
#    ../src/conv/mlist_flat.cpp
#    ../src/conv/mlist_json.cpp
#    ../src/conv/mlist_image.cpp

#    ../src/conv/image_mlist.cpp

#    ../src/conv/list_json.cpp

#    ../src/conv/json_mlist.cpp
#    ../src/conv/json_list.cpp

    ../src/conv/conv_mlist.cpp
    ../src/conv/conv_image.cpp
    ../src/conv/conv_list.cpp
    ../src/conv/conv_json.cpp

    )


set (HEADERS
    ../miniSDIF/src/mSDIFFile.hpp
    ../miniSDIF/src/mSDIFFrame.hpp
    ../miniSDIF/src/mSDIFMatrix.hpp
)

include_directories(../lib/)
include_directories(../pd/)

include_directories(pd-source/)

file(GLOB LIB_SRC
    "../lib/ceammc_atomlist.cpp"
    "../lib/ceammc_atom.cpp"
    "../lib/ceammc_abstractdata.cpp"
    "../lib/ceammc_dataatom.cpp"
    "../lib/ceammc_data.cpp"
    "../lib/ceammc_datastorage.cpp"
    "../lib/ceammc_log.cpp"

    "pd_mock.c"
)



#add_subdirectory(pd-source)

file(GLOB UTF8
    "../utf8/*.h"
    "../utf8/*.c"
    "../utf8/internal/*.c"
)

########################

#target_link_libraries(test_converters puredata-core)

add_executable(test_converters test_converters.cpp catch.hpp ${SRC_CONV} ${SRC_JSON} ${SRC_MLIST} ${SRC_IMG} ${LIB_SRC} ${UTF8} ${PD_SRC})

SET(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

#target_include_directories(test_converters PRIVATE "pd-source/")
