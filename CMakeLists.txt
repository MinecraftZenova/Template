cmake_minimum_required(VERSION 3.10)

set(ModName Example)

set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT DEFINED CMAKE_ASM_NASM_COMPILER)
    if(DEFINED ENV{ASM_NASM})
        set(CMAKE_ASM_NASM_COMPILER $ENV{ASM_NASM})
    elseif(DEFINED ENV{NASMPATH}) # https://github.com/ShiftMediaProject/VSNASM
        set(CMAKE_ASM_NASM_COMPILER $ENV{NASMPATH})
    elseif(EXISTS "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/nasm.exe")
        set(CMAKE_ASM_NASM_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/nasm.exe")
    # add more cases in the future (like the other visual studios)
    endif()

    if(DEFINED CMAKE_ASM_NASM_COMPILER)
        string(REPLACE "\\" "/" CMAKE_ASM_NASM_COMPILER ${CMAKE_ASM_NASM_COMPILER})
    endif()
endif()

project(${ModName} CXX ASM_NASM)
enable_language(ASM_NASM)

if(MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "$ENV{ZENOVA_DATA}/mods/${ModName}")
    endforeach(OUTPUTCONFIG)
endif()

include_directories("$ENV{ZENOVA_DATA}/dev/inc")
include_directories("src")

file(GLOB_RECURSE INCLUDE_LIST
    "src/*.hpp"
    "src/*.h"
)

file(GLOB_RECURSE SOURCE_LIST
    "src/*.cpp"
    "src/*.cxx"
    "src/*.cc"
)

add_library(${ModName} SHARED
    ${INCLUDE_LIST}
    ${SOURCE_LIST}
)

target_link_libraries(${ModName} 
    $ENV{ZENOVA_DATA}/dev/lib/ZenovaAPI.lib
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/resources/modinfo.json" "$ENV{ZENOVA_DATA}/mods/${ModName}/modinfo.json" COPYONLY)

foreach(resource assets;data)
    FILE(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/${resource}" src)
    FILE(TO_CMAKE_PATH "$ENV{ZENOVA_DATA}/mods/${ModName}/${resource}" dest)

    if(NOT EXISTS ${dest})
        add_custom_command(TARGET ${ModName}
            POST_BUILD
            COMMAND py -3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/add_security.py ${src}
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}
            DEPENDS ${src}
        )
    endif()
endforeach(resource)

add_custom_command(TARGET ${ModName}
    PRE_BUILD
    COMMAND py -3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/process_headers.py -a x64 -p windows -d ${CMAKE_CURRENT_SOURCE_DIR}/src/generated ${CMAKE_CURRENT_SOURCE_DIR}/maps/*.json
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/process_headers.py
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Header Files//" FILES ${INCLUDE_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files//" FILES ${SOURCE_LIST})