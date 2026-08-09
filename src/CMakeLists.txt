find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)


file(GLOB SFML_TESTS_SOURCES CONFIGURE_DEPENDS *.cpp **/*.cpp **/**/*.cpp)
add_executable(sfml_tests ${SFML_TESTS_SOURCES})
target_link_libraries(sfml_tests PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)

target_compile_options(sfml_tests PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wno-unused-result>
    $<$<CXX_COMPILER_ID:MSVC>:/wd6031>
)