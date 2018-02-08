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



file(GLOB UTF8
    "utf8/*.h"
    "utf8/*.c"
    "utf8/internal/*.c"
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


    )

set (SRC_SDIF

    src/sdif/sdif_file.cpp
    src/sdif/sdif_frame.cpp
    src/sdif/sdif_matrix.cpp

    src/sdif/sdif_data_types.cpp

    src/sdif/sdif_1trc.cpp
    )

set (SRC_SYNTH

    src/synth/synth_sine.cpp
    src/synth/synth_res.cpp
    )

set (SRC_MLIST

    src/mlist/mlist_obj.cpp
    src/mlist/mlist_unpack.cpp
    src/mlist/mlist_llll.cpp
    src/mlist/mlist_flat.cpp
    src/mlist/mlist_flip.cpp

    src/mlist/mlist_data_type.cpp
    )

set (SRC_JSON
    src/json/json_data_type.cpp
    src/json/mstring_data_type.cpp

    src/json/json_obj.cpp
    )

set (SRC_IMG
    src/img/mlist_image.cpp
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

include_directories(../miniSDIF/src/mlist)
include_directories(../miniSDIF/src/json)

include_directories(../miniSDIF/src/img)

add_library(sdif_lib SHARED
    ${SOURCES}
    ${UTF8}
    ${SDIFLIB}
    ${SYNTH}
    ${SRC_SDIF}
    ${SRC_SYNTH}
    ${SRC_MLIST}
    ${SRC_JSON}
    ${SRC_IMG}
    )

target_link_libraries(sdif_lib "-undefined dynamic_lookup")
SET_TARGET_PROPERTIES(sdif_lib PROPERTIES PREFIX "")
set_target_properties(sdif_lib PROPERTIES SUFFIX ".pd_darwin")

FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
  INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(sdif_lib ${JPEG_LIBRARIES})
ENDIF()

#install(TARGETS timeline LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../bin)


