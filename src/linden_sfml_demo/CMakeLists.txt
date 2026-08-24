find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)

file(GLOB LINDEN_SFML_DEMO_SOURCES CONFIGURE_DEPENDS *.cpp **/*.cpp **/**/*.cpp)
add_executable(linden_sfml_demo ${LINDEN_SFML_DEMO_SOURCES})
target_link_libraries(linden_sfml_demo PRIVATE
    linden::linden
    SFML::System
    SFML::Window
    SFML::Graphics
)

target_compile_options(linden_sfml_demo PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wno-unused-result>
    $<$<CXX_COMPILER_ID:MSVC>:/wd6031>
)