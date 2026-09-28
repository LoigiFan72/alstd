cmake_minimum_required(VERSION 3.25)

project(alstd VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ALSTD_SOURCES
    sources/basis/alstdNew.cpp
    sources/dev/alstdAssert.cpp
)

add_library(alstd OBJECT ${ALSTD_SOURCES})

target_include_directories(alstd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ALSTD_DEBUG)
    target_compile_definitions(alstd PUBLIC ALSTD_DEBUG=1)
endif()

if(ALSTD_ENABLE_DEBUG_PRINT)
    target_compile_definitions(alstd PUBLIC ALSTD_ENABLE_PRINT=1)
    target_compile_definitions(alstd PUBLIC ALSTD_ENABLE_ASSERT=1)
    target_compile_definitions(alstd PUBLIC ALSTD_ENABLE_WARNING=1)
endif()

if(ALSTD_PLATFORM_WINDOWS)
    target_compile_definitions(alstd PUBLIC ALSTD_PLATFORM_WINDOWS=1)

    target_sources(alstd PRIVATE
        sources/thread/win/alstdCriticalSectionWin.cpp
        sources/thread/win/alstdMutexWin.cpp
    )

elseif(ALSTD_PLATFORM_CTR)
    target_compile_definitions(alstd PUBLIC ALSTD_PLATFORM_CTR=1)
    target_link_libraries(alstd PUBLIC CTR_SDK)

    target_sources(alstd PRIVATE
        sources/thread/ctr/alstdCriticalSectionCtr.cpp
        sources/thread/ctr/alstdMutexCtr.cpp
    )
else()
    message(FATAL_ERROR "Platform is not supported.")
endif()

option(ALSTD_BUILD_TESTS "Build alstd tests" OFF) # test env

if(ALSTD_BUILD_TESTS)
    add_subdirectory(dev/tests/TEST_A)
endif()