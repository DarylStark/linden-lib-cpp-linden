cmake_minimum_required(VERSION 3.20)
project(
    linden
    VERSION
        0.0.1
    LANGUAGES
        CXX
)

option(
        LINDEN_BUILD_SFML_DEMO "Build the SFML demo application" OFF
)

# C++ Configuration
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Application source
add_subdirectory(src/linden)

if(LINDEN_BUILD_SFML_DEMO)
    add_subdirectory(examples/linden_sfml_demo)
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(
    cmake/lindenConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/lindenConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/linden
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/lindenConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/lindenConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/lindenConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/linden
)