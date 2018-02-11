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

    src/mlist/mlist_flip.cpp

    src/mlist/mlist_data_type.cpp
    )

set (SRC_JSON
    src/json/json_data_type.cpp
    src/json/mstring_data_type.cpp

    src/json/json_obj.cpp

    src/json/json_dict.cpp

    )

set (SRC_IMG
    src/img/image_obj.cpp

    src/img/image_data_type.cpp
    )

set (SRC_MAT
    src/matrix/matrix_obj.cpp

    src/matrix/matrix_data_type.cpp
    )

set (SRC_CONV

    src/conv/mlist_llll.cpp
    src/conv/mlist_flat.cpp
    src/conv/mlist_json.cpp
    src/conv/mlist_image.cpp

    src/conv/image_mlist.cpp
    src/conv/image_matrix.cpp

    src/conv/list_json.cpp

    src/conv/json_mlist.cpp
    src/conv/json_list.cpp

    src/conv/conv_mlist.cpp
    src/conv/conv_image.cpp
    src/conv/conv_list.cpp
    src/conv/conv_json.cpp
    src/conv/conv_matrix.cpp

    src/conv/matrix_image.cpp

    )

set (HEADERS
    ../miniSDIF/src/mSDIFFile.hpp
    ../miniSDIF/src/mSDIFFrame.hpp
    ../miniSDIF/src/mSDIFMatrix.hpp
)

file(GLOB LIB_SRC
    "lib/ceammc_atomlist.cpp"
    "lib/ceammc_atom.cpp"
    "lib/ceammc_abstractdata.cpp"
    "lib/ceammc_dataatom.cpp"
    "lib/ceammc_data.cpp"
    "lib/ceammc_datastorage.cpp"
    "lib/ceammc_log.cpp"


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
include_directories(../miniSDIF/src/conv)

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
    ${SRC_MAT}
    ${SRC_CONV}

    ${LIB_SRC}
    )

target_link_libraries(sdif_lib "-undefined dynamic_lookup")
SET_TARGET_PROPERTIES(sdif_lib PROPERTIES PREFIX "")
set_target_properties(sdif_lib PROPERTIES SUFFIX ".pd_darwin")

FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
  INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(sdif_lib ${JPEG_LIBRARIES})
ENDIF()

add_subdirectory(tests)


#######
enable_testing()

macro(add_unit_test target target_test)
    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${target_test})
    add_test(target ${CMAKE_BINARY_DIR}/tests/${target_test})
endmacro(add_unit_test)

add_unit_test (all_tests test_converters)

add_custom_target( all_tests ALL
                   DEPENDS ${UNIT_TEST_TARGETS}
)

add_custom_command(TARGET all_tests
                   COMMENT "Running tests..."
                   POST_BUILD
                   COMMAND ${CMAKE_CTEST_COMMAND}
                   ARGS --output-on-failure -fprofile-arcs -ftest-coverage
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   )


#install(TARGETS timeline LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../bin)


