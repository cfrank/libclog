cmake_minimum_required(VERSION 3.9)

# Check if clog is being imported with add_subdirectory
if(NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
endif()

project(clog
    VERSION 0.2.0
    DESCRIPTION "A simple C logging library"
    LANGUAGES C
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(clog
    src/clog.c
)

target_include_directories(clog PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Wpedantic \
-Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing")

if (NOT_SUBPROJECT)
    set(CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/clog")

    install(TARGETS clog
        EXPORT clogTargets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    install(EXPORT clogTargets
        DESTINATION ${CMAKE_CONFIG_DESTINATION}
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/clogConfigVersion.cmake"
        COMPATIBILITY SameMajorVersion
    )

    install(
        DIRECTORY "include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )

    configure_file(libclog.pc.in libclog.pc @ONLY)

    install(FILES ${CMAKE_BINARY_DIR}/libclog.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
    )
endif()


export(PACKAGE ${PROJECT_NAME})
