cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE CMP_SRCS
        # Lossy Compression
        "apc/*.h"
        "apc/*.cpp"
        "atc/*.h"
        "atc/*.cpp"
        "ati/*.h"
        "ati/*.cpp"
        "ati/*.c"
        "basis/*.h"
        "basis/*.cpp"
        "bc6h/*.h"
        "bc6h/*.cpp"
        "bc7/*.h"
        "bc7/*.cpp"
        "block/*.h"
        "block/*.cpp"
        "buffer/*.h"
        "buffer/*.cpp"
        "dxt/*.h"
        "dxt/*.cpp"
        "dxtc/*.h"
        "dxtc/*.cpp"
        "dxtc/*.c"
        "etc/*.h"
        "etc/*.cpp"
        "etc/etcpack/*.h"
        "etc/etcpack/*.cpp"
        "etc/etcpack/*.cxx"
        "gt/*.h"
        "gt/*.cpp"

        # Common
        "common/*.h"
        "common/*.cpp"
        ${PROJECT_SOURCE_DIR}/cmp_framework/common/*.h
        ${PROJECT_SOURCE_DIR}/cmp_framework/common/*.cpp
        ${PROJECT_SOURCE_DIR}/cmp_framework/common/half/*.h
        ${PROJECT_SOURCE_DIR}/cmp_framework/common/half/*.cpp
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/atiformats.cpp
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/atiformats.h
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/format_conversion.h
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/format_conversion.cpp
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/codec_common.h
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/codec_common.cpp
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/texture_utils.h
        ${PROJECT_SOURCE_DIR}/applications/_plugins/common/texture_utils.cpp
)

function(create_cmp_compressonator_library SUFFIX)
    add_library(Compressonator${SUFFIX}
            STATIC
            version.h
            common.h
            compress.cpp
            compressonator.h
            compressonator.cpp
            ${CMP_SRCS})
    target_include_directories(Compressonator${SUFFIX}
            PUBLIC
            ./
            # Lossy Compression
            apc
            atc
            ati
            basis
            bc6h
            bc7
            block
            buffer
            dxt
            dxtc
            etc
            etc/etcpack/
            gt

            # Common
            common
            ${PROJECT_SOURCE_DIR}/cmp_framework/common
            ${PROJECT_SOURCE_DIR}/cmp_framework/common/half
            ${PROJECT_SOURCE_DIR}/applications/_plugins/common
            ${PROJECT_SOURCE_DIR}/applications/_libs/cmp_math/
    )
    set_target_properties(Compressonator${SUFFIX} PROPERTIES FOLDER ${PROJECT_FOLDER_SDK_LIBS})
    target_link_libraries(Compressonator${SUFFIX} PUBLIC CMP_Core${SUFFIX})
endfunction()

if(NOT WIN32)
    create_cmp_compressonator_library("")
else()
    create_cmp_compressonator_library("_MD")
    create_cmp_compressonator_library("_MT")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set_property(TARGET "Compressonator_MD" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
        set_property(TARGET "Compressonator_MT" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    else()
        set_property(TARGET "Compressonator_MD" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
        set_property(TARGET "Compressonator_MT" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()
