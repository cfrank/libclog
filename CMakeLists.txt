cmake_minimum_required(VERSION 3.9)

project(libclog
    VERSION 0.0.1
    DESCRIPTION "A simple C logging library"
    LANGUAGES C
)

include(GNUInstallDirs)

add_library(libclog SHARED
    src/clog.c
)

set_target_properties(libclog
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/clog.h
    C_STANDARD 99
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(libclog.pc.in libclog.pc @ONLY)

target_include_directories(libclog PRIVATE include)
target_include_directories(libclog PRIVATE src)

install(TARGETS libclog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/libclog.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)