function(target_link_compressonator TARGET)
    if(MSVC)
        get_target_property(TARGET_MSVC_RUNTIME_LIBRARY ${TARGET} MSVC_RUNTIME_LIBRARY)
        if(TARGET_MSVC_RUNTIME_LIBRARY MATCHES "DLL$")
            target_link_libraries(${TARGET} PRIVATE
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/Compressonator_MD$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MD$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MD_AVX$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MD_AVX512$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MD_SSE$<$<CONFIG:Debug>:d>.lib")
        else()
            target_link_libraries(${TARGET} PRIVATE
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/Compressonator_MT$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MT$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MT_AVX$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MT_AVX512$<$<CONFIG:Debug>:d>.lib"
                    "${CMAKE_CURRENT_LIST_DIR}/lib/win_x86_64/CMP_Core_MT_SSE$<$<CONFIG:Debug>:d>.lib")
        endif()
    elseif(APPLE)
        target_link_libraries(${TARGET} PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/lib/osx_arm64/libCompressonator$<$<CONFIG:Debug>:d>.a"
                "${CMAKE_CURRENT_LIST_DIR}/lib/osx_arm64/libCMP_Core$<$<CONFIG:Debug>:d>.a")
    elseif(UNIX)
        target_link_libraries(${TARGET} PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/lib/linux_x86_64/libCompressonator$<$<CONFIG:Debug>:d>.a"
                "${CMAKE_CURRENT_LIST_DIR}/lib/linux_x86_64/libCMP_Core$<$<CONFIG:Debug>:d>.a"
                "${CMAKE_CURRENT_LIST_DIR}/lib/linux_x86_64/libCMP_Core_AVX$<$<CONFIG:Debug>:d>.a"
                "${CMAKE_CURRENT_LIST_DIR}/lib/linux_x86_64/libCMP_Core_AVX512$<$<CONFIG:Debug>:d>.a"
                "${CMAKE_CURRENT_LIST_DIR}/lib/linux_x86_64/libCMP_Core_SSE$<$<CONFIG:Debug>:d>.a")
    else()
        message(FATAL_ERROR "Unable to link to Compressonator library!")
    endif()
    target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
endfunction()
