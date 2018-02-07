cmake_minimum_required (VERSION 2.8)

#set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

set (CMAKE_PREFIX_PATH ~/Qt/5.8/clang_64)
set (CMAKE_CXX_STANDARD 11)
# set (QMAKE_MACOSX_DEPLOYMENT_TARGET 10.10)

if (APPLE)
	set(CMAKE_MACOSX_RPATH FALSE)
endif()

#fixes warning for app name
cmake_policy(SET CMP0037 OLD)

project(sdif_library)

add_definitions(-DHAVE_UNISTD_H)

file(GLOB TL_LIB_SOURCES
    "lib/*.h"
    "lib/*.cpp"
    "lib/*.c"
)

file(GLOB UTF8
    "utf8/*.h"
    "utf8/*.c"
    "utf8/internal/*.c"
)

set(TL_LIB_SOURCES_PLUS

#    lib/ceammc_timeline.cpp

)

set (CICM

    CICMWrapper/ebox.c
    CICMWrapper/eclass.c
    CICMWrapper/ecommon.c
    CICMWrapper/egraphics.c
    CICMWrapper/eobj.c
    CICMWrapper/epopup.c

    )

set (SDIFLIB
    ../miniSDIF/src/mSDIFFile.cpp
    ../miniSDIF/src/mSDIFFrame.cpp
    ../miniSDIF/src/mSDIFMatrix.cpp
    ../miniSDIF/src/mSDIFTypes.cpp
    )

set (SYNTH
    ../PartialSynth/src/BasePartial.cpp
    ../PartialSynth/src/SinePartial.cpp
    ../PartialSynth/src/ResPartial.cpp
    ../PartialSynth/src/SineSynth.cpp
    ../PartialSynth/src/ResSynth.cpp
    )

set (SOURCES
    sdif_lib.cpp

    src/sdif_file.cpp
    src/sdif_frame.cpp
    src/sdif_matrix.cpp

    src/sdif_data_types.cpp

    src/synth_sine.cpp
    src/synth_res.cpp

    src/sublist_obj.cpp
    src/sublist_llll.cpp

    src/sublist_data_type.cpp

#    tl/tl_cue.cpp
#    tl/tl_bang.cpp
#    tl/tl_transport.cpp

#    tl/tl_parameter.cpp
#    tl/tl_toggle.cpp
#    tl/tl_value.cpp

#    tl/tl_delay.cpp
)

set (HEADERS
    ../miniSDIF/src/mSDIFFile.hpp
    ../miniSDIF/src/mSDIFFrame.hpp
    ../miniSDIF/src/mSDIFMatrix.hpp
)

find_package(Boost 1.47.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories( ${CMAKE_BINARY_DIR} )

include_directories(.)
include_directories(./tl/)
include_directories(./lib/)
include_directories(./pd/)
include_directories(./utf8/)
include_directories(./CICMWrapper/)

include_directories(../miniSDIF/src/)
include_directories(../PartialSynth/src/)

add_library(sdif_lib SHARED ${TL_LIB_SOURCES} ${TL_LIB_SOURCES_PLUS} ${SOURCES} ${CICM} ${UTF8} ${SDIFLIB} ${SYNTH})
target_link_libraries(sdif_lib "-undefined dynamic_lookup")
SET_TARGET_PROPERTIES(sdif_lib PROPERTIES PREFIX "")
set_target_properties(sdif_lib PROPERTIES SUFFIX ".pd_darwin")

#install(TARGETS timeline LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../bin)


