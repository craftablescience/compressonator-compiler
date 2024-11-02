#
# Patches "CMakeLists.txt"
#

cmake_minimum_required(VERSION 3.10)

# Cmake build examples: for Visual Studio 2017
#
# cmake -G "Visual Studio 15 2017 Win64"   Enable building all apps and libs
# cmake -DOPTION_ENABLE_ALL_APPS=OFF -G "Visual Studio 15 2017 Win64"    Disable all builds except external libs, minimal cmake base setup
# cmake -DOPTION_ENABLE_ALL_APPS=OFF -DOPTION_BUILD_APPS_CMP_CLI=ON -G "Visual Studio 15 2017 Win64"   Enable only CLI app build
# cmake -DOPTION_ENABLE_ALL_APPS=OFF -DOPTION_BUILD_APPS_CMP_GUI=ON -G "Visual Studio 15 2017 Win64"   Enable only GUI app build
#
# Other options are available : see OPTION_BUILDS...
#

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

# Setting version information

if (NOT CMP_VERSION_MAJOR)
    set(CMP_VERSION_MAJOR 4)
endif()

if (NOT CMP_VERSION_MINOR)
    set(CMP_VERSION_MINOR 5)
endif()

if (NOT CMP_VERSION_BUILD_NUMBER)
    set(CMP_VERSION_BUILD_NUMBER 0)
endif()

# Needs to be above project()
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

project(Compressonator VERSION ${CMP_VERSION_MAJOR}.${CMP_VERSION_MINOR})
message("Building Compressonator version ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# ------------------------------
# Helper function for the build
# ------------------------------
include(cmake/helperfunctions.cmake)


# ------------------------------
# Common compiler options
# ------------------------------

if (CMP_HOST_WINDOWS)
    add_compile_options(/W4 /wd4201)
    #    add_compile_options(/W4 /WX /wd4201)

    option(CMP_COMPILE_WITH_ASAN "Compile with ASan" OFF)
elseif(CMP_HOST_LINUX)
    add_compile_options(-Wall)
    #    add_compile_options(-Wall -Werror)
endif()

# ------------------------------------
# Visual Studio project folder names
# ------------------------------------

set(PROJECT_FOLDER_SDK "SDK")
set(PROJECT_FOLDER_SDK_LIBS "${PROJECT_FOLDER_SDK}/Libraries")
set(PROJECT_FOLDER_SDK_EXTERNAL "${PROJECT_FOLDER_SDK}/External Libraries")
set(PROJECT_FOLDER_SDK_PLUGIN_DYNAMIC "${PROJECT_FOLDER_SDK}/Plugins/Dynamic")
set(PROJECT_FOLDER_SDK_PLUGIN_STATIC "${PROJECT_FOLDER_SDK}/Plugins/Static")
set(PROJECT_FOLDER_SDK_EXAMPLES "${PROJECT_FOLDER_SDK}/Examples")

set(PROJECT_FOLDER_APPS "Applications")
set(PROJECT_FOLDER_APPS_LIBS "${PROJECT_FOLDER_APPS}/Libraries")
set(PROJECT_FOLDER_APPS_EXTERNAL "${PROJECT_FOLDER_APPS}/External Libraries")
set(PROJECT_FOLDER_APPS_PLUGIN_DYNAMIC "${PROJECT_FOLDER_APPS}/Plugins/Dynamic")
set(PROJECT_FOLDER_APPS_PLUGIN_STATIC "${PROJECT_FOLDER_APPS}/Plugins/Static")

#----------------------------------------
# Check compiler feature support levels
# For Apple (Mac) default to C++11
#---------------------------------------
if (CMP_HOST_LINUX OR CMP_HOST_WINDOWS)
    if("cxx_std_11" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(COMPILER_SUPPORTS_CXX11 ON)
        message("Compiler Supports cxx_std_11")
    endif()
    if("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(COMPILER_SUPPORTS_CXX14 ON)
        message("Compiler Supports cxx_std_14")
    endif()
    if("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(COMPILER_SUPPORTS_CXX17 ON)
        message("Compiler Supports cxx_std_17")
    endif()
else()
    message("UNIX Build: CHECK_CXX_COMPILER_FLAG defaulted to -std=c++11")
    set(COMPILER_SUPPORTS_CXX11 ON)
endif()

#---------------------------------------------------------------------------------
# Provide default values for each build option
#
# ! Cached variables should not be modified and reflect user's preference
# ! Though regular variables may be subject to change due to requirements, dependencies, etc.
#  Example:
#  do not set(OPTION_BUILD_CMP_SDK ON CACHE BOOL "Build Compressonator SDK" FORCE)
#  do     set(OPTION_BUILD_CMP_SDK ON)
#  so that user preference is $CACHE{OPTION_BUILD_CMP_SDK} and the actual value is ${OPTION_BUILD_CMP_SDK}
#---------------------------------------------------------------------------------
set(OPTION_ENABLE_ALL_APPS          OFF)
set(OPTION_BUILD_CMP_SDK            ON)
set(OPTION_BUILD_APPS_CMP_CLI       OFF)
set(OPTION_BUILD_APPS_CMP_GUI       OFF)
set(OPTION_BUILD_APPS_CMP_UNITTESTS OFF)
set(OPTION_BUILD_APPS_CMP_EXAMPLES  OFF)

# Minimum Lib Dependencies for CLI, GUI, and SDK (GUI has additional lib requirements added later in this cmake)
set(LIB_BUILD_COMPRESSONATOR_SDK    ON)
set(LIB_BUILD_FRAMEWORK_SDK         OFF)
set(LIB_BUILD_IMAGEIO               OFF)
set(LIB_BUILD_ANALYSIS              OFF)
set(LIB_BUILD_COMMON                OFF)
set(LIB_BUILD_CORE                  ON)
set(LIB_BUILD_GPUDECODE             OFF)

# The following options that have been removed
set(LIB_BUILD_MESHCOMPRESSOR OFF)

set(PROJECT_EXTERNAL_LIBDIR ${PROJECT_SOURCE_DIR}/../common/lib/ext)

# ----------------------------------------------------------------------------
# GPUOpen Source Code build options : These options are been revised for v4.2
# ----------------------------------------------------------------------------
set(OPTION_BUILD_KTX2  OFF)
set(OPTION_BUILD_EXR   OFF)
set(OPTION_BUILD_GUI   OFF)
set(OPTION_CMP_DIRECTX OFF)
set(OPTION_CMP_VULKAN  OFF)
set(OPTION_CMP_OPENGL  OFF)
set(OPTION_CMP_QT      OFF)
set(OPTION_CMP_OPENCV  OFF)
set(OPTION_CMP_GTC OFF) # Internal R&D
set(OPTION_BUILD_BROTLIG     OFF)
set(OPTION_BUILD_BROTLIG_GUI OFF) # In development for v4.4
# Internal testing application
set(OPTION_BUILD_INTERNAL_CMP_TEST OFF)
# No longer supported
set(OPTION_BUILD_ASTC  OFF)
set(OPTION_BUILD_DRACO OFF)
# this needs to be removed
set(NO_LEGACY_BEHAVIOR ON)

# -----------------------------------------------------------------------------------
# Code build definitions and features: These options are been revised for v4.2
# -----------------------------------------------------------------------------------
add_compile_definitions(
        USE_ETCPACK                 # Use ETCPack for ETC2 else use CModel code!
        USE_MESH_CLI                # CLI Process Mesh (only support glTF and OBJ files)
        ENABLE_MAKE_COMPATIBLE_API  # Byte<->Float to make all source and dest compatible
        USE_OLD_SWIZZLE             # Remove swizzle flag and abide by CMP_Formats
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration options" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../out")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../out")

# '_DEBUG' is only defined by Visual Studio. Make sure it's defined everywhere
add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)


# -----------------------------------
# Set or get all package requirements
# -----------------------------------
if (COMPILER_SUPPORTS_CXX17 AND CMP_HOST_WINDOWS)
    set(CMAKE_CXX_STANDARD 17)
    add_compile_definitions(_CMP_CPP17_=1)
else()
    # Linux
    if (COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_STANDARD 14)
        add_compile_definitions(_CMP_CPP14_=1)
    else()
        # UNIX or LINUX
        set(CMAKE_CXX_STANDARD 11)
    endif()
endif()

# Configure Externals, they must be added via 'include' before the applications
include(ExternalProject)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(external/cmake/dependencyinfo.cmake)
include(external/cmake/CMakeLists.txt)
include(external/CMakeLists.txt)

if (CMP_HOST_WINDOWS)
    add_compile_definitions(_WIN32)

    set(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL:NO")

    if (CMP_COMPILE_WITH_ASAN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fsanitize=address")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /fsanitize=address")
    endif()
else()
    if (CMP_HOST_LINUX)
        #gltf code needs _LINUX define
        add_compile_definitions(_LINUX=1)
    endif()

    # filesystem support for c++14
    if (COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_STANDARD 14)
        #add_definitions(-std=c++14)
        link_libraries(stdc++fs)
    else()
        if (CMP_HOST_LINUX)
            set(CMAKE_CXX_STANDARD 11)
        endif()
    endif()

    add_definitions(-fPIC -Wno-write-strings)

    # ----------------------------------
    # Package requirements for the Build
    # ----------------------------------
    find_package(Threads REQUIRED)
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()

set(CMAKE_DEBUG_POSTFIX "d")

# These are the minimum build includes for both Windows / Linux / Mac application builds
# Libs common to all OS
add_subdirectory(cmp_core)
add_subdirectory(cmp_compressonatorlib)
