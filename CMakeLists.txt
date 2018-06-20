cmake_minimum_required(VERSION 3.9)

project(clog
    VERSION 0.1.0
    DESCRIPTION "A simple C logging library"
    LANGUAGES C
)

include(GNUInstallDirs)

add_library(clog SHARED
    src/clog.c
)

set_target_properties(clog
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/clog.h
    C_STANDARD 99
    C_EXTENSIONS OFF
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Wpedantic \
-Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing")

configure_file(libclog.pc.in libclog.pc @ONLY)

target_include_directories(clog PRIVATE include)
target_include_directories(clog PRIVATE src)

install(TARGETS clog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/libclog.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
