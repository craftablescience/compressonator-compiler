# Compressonator Compiler
A GitHub Actions workflow to compile Compressonator's core library. The SDK, CLI, and GUI are *not* compiled.

Releases come bundled with a CMake file to allow for easy usage of the compiled library. To use it, do something like the following:

```cmake
# Set the path to the downloaded+unzipped release
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/path/to/compressonator/release")

# Say we have a library called "sample_lib"... Link to Compressonator using the given function.
# This function will link to the correct libraries and make the "Compressonator.h" header file available.
target_link_compressonator(sample_lib)
```
