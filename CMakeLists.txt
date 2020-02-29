cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

if(NOT DEFINED PROJECT_NAME)
    set(CPP_DEEPCOPY_PTR_IS_SUBPROJECT ON)
endif()

set(CPP_DEEPCOPY_PTR_VERSION 0.0.1)

project(deep_ptr LANGUAGES CXX VERSION ${CPP_DEEPCOPY_PTR_VERSION})

include(CTest)
include(FetchContent)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(deep_ptr INTERFACE)
target_include_directories(deep_ptr
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(deep_ptr
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/deep_ptr.h>
)

target_compile_features(deep_ptr
    INTERFACE
        cxx_std_17
)

add_library(deep_ptr::deep_ptr ALIAS deep_ptr)

if (${CPP_DEEPCOPY_PTR_IS_SUBPROJECT})
    if (${BUILD_TESTING})
        FetchContent_Declare(
            catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        )

        FetchContent_GetProperties(catch2)
        if(NOT catch2_POPULATED)
            FetchContent_Populate(catch2)
            add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
        endif()

        add_executable(test_deep_ptr "")
        target_sources(test_deep_ptr
            PRIVATE
                deep_ptr_test.cpp
        )

        target_link_libraries(test_deep_ptr
            PRIVATE
                Catch2::Catch2
                deep_ptr::deep_ptr
        )

        target_compile_options(test_deep_ptr
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/EHsc>
                $<$<CXX_COMPILER_ID:MSVC>:/W4>
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>:-Werror;-Wall>
        )

        set_target_properties(test_deep_ptr PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
        )

        enable_testing()
        add_test(
            NAME test_deep_ptr
            COMMAND test_deep_ptr
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
        include(Catch)
        catch_discover_tests(test_deep_ptr)

    endif(${BUILD_TESTING})

    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/deep_ptr.h"
        DESTINATION
            ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
        DESTINATION
            "${CMAKE_INSTALL_DATAROOTDIR}/licenses/deep_ptr"
    )

    install(
        TARGETS deep_ptr
        EXPORT deep_ptr-target
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(
        EXPORT deep_ptr-target
        NAMESPACE deep_ptr::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/deep_ptr"
    )

    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/deep_ptr-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/deep_ptr-config.cmake
        INSTALL_DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/deep_ptr"
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/deep_ptr-version.cmake
        VERSION ${CPP_INDIRECT_VALUE_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
    )

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/deep_ptr-config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/deep_ptr-version.cmake
        DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/deep_ptr"
    )
endif()