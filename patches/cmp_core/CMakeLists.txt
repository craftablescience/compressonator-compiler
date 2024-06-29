cmake_minimum_required(VERSION 3.10)

function(create_cmp_core_library SUFFIX)
    add_library(CMP_Core${SUFFIX} STATIC)

    target_sources(CMP_Core${SUFFIX}
            PRIVATE
            shaders/bc1_encode_kernel.h
            shaders/bc1_common_kernel.h
            shaders/bc1_encode_kernel.cpp
            shaders/bc2_encode_kernel.h
            shaders/bc2_encode_kernel.cpp
            shaders/bc3_encode_kernel.h
            shaders/bc3_encode_kernel.cpp
            shaders/bc4_encode_kernel.h
            shaders/bc4_encode_kernel.cpp
            shaders/bc5_encode_kernel.h
            shaders/bc5_encode_kernel.cpp
            shaders/bc6_encode_kernel.h
            shaders/bc6_encode_kernel.cpp
            shaders/bc7_encode_kernel.h
            shaders/bc7_common_encoder.h
            shaders/bc7_encode_kernel.cpp
            shaders/bcn_common_kernel.h
            shaders/bcn_common_api.h
            shaders/common_def.h

            source/cmp_core.h
            source/cmp_core.cpp
            source/cmp_math_vec4.h
            source/cmp_math_func.h

            ../applications/_libs/cmp_math/cpu_extensions.cpp
            ../applications/_libs/cmp_math/cmp_math_common.cpp
    )

    target_include_directories(CMP_Core${SUFFIX}
            PUBLIC
            shaders
            source
            ../applications/_libs/cmp_math/
    )

    if (UNIX)
        target_compile_definitions(CMP_Core${SUFFIX} PRIVATE _LINUX)
        if(NOT APPLE)
            target_compile_definitions(CMP_Core${SUFFIX} PRIVATE ASPM_GPU)
        endif()
    endif()

    set_target_properties(CMP_Core${SUFFIX} PROPERTIES FOLDER ${PROJECT_FOLDER_SDK_LIBS})

    # Core SIMD options
    if(NOT APPLE)

        # SSE
        add_library(CMP_Core${SUFFIX}_SSE STATIC)
        target_sources(CMP_Core${SUFFIX}_SSE PRIVATE source/core_simd_sse.cpp)
        target_include_directories(CMP_Core${SUFFIX}_SSE PRIVATE source shaders)

        if (UNIX)
            target_compile_options(CMP_Core${SUFFIX}_SSE PRIVATE -march=nehalem)
        endif()

        set_target_properties(CMP_Core${SUFFIX}_SSE PROPERTIES FOLDER ${PROJECT_FOLDER_SDK_LIBS})

        # AVX
        add_library(CMP_Core${SUFFIX}_AVX STATIC)
        target_sources(CMP_Core${SUFFIX}_AVX PRIVATE source/core_simd_avx.cpp)
        target_include_directories(CMP_Core${SUFFIX}_AVX PRIVATE source shaders)

        if (WIN32)
            target_compile_options(CMP_Core${SUFFIX}_AVX PRIVATE /arch:AVX2)
        else()
            target_compile_options(CMP_Core${SUFFIX}_AVX PRIVATE -march=haswell)
        endif()

        set_target_properties(CMP_Core${SUFFIX}_AVX PROPERTIES FOLDER ${PROJECT_FOLDER_SDK_LIBS})

        # AVX-512
        add_library(CMP_Core${SUFFIX}_AVX512 STATIC)
        target_sources(CMP_Core${SUFFIX}_AVX512 PRIVATE source/core_simd_avx512.cpp)
        target_include_directories(CMP_Core${SUFFIX}_AVX512 PRIVATE source shaders)

        if (WIN32)
            target_compile_options(CMP_Core${SUFFIX}_AVX512 PRIVATE /arch:AVX-512)
        else()
            target_compile_options(CMP_Core${SUFFIX}_AVX512 PRIVATE -march=knl)
        endif()

        set_target_properties(CMP_Core${SUFFIX}_AVX512 PROPERTIES FOLDER ${PROJECT_FOLDER_SDK_LIBS})

        # Link SIMD libraries to CMP_Core${SUFFIX}
        target_link_libraries(CMP_Core${SUFFIX} PRIVATE CMP_Core${SUFFIX}_SSE CMP_Core${SUFFIX}_AVX CMP_Core${SUFFIX}_AVX512)

    endif()
endfunction()

if(NOT WIN32)
    create_cmp_core_library("")
else()
    create_cmp_core_library("_MD")
    create_cmp_core_library("_MT")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set_property(TARGET "CMP_Core_MD" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
        set_property(TARGET "CMP_Core_MT" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    else()
        set_property(TARGET "CMP_Core_MD" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
        set_property(TARGET "CMP_Core_MT" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()
