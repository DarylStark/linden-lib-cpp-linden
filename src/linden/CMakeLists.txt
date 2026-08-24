add_library(linden INTERFACE)

target_include_directories(linden INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
	$<INSTALL_INTERFACE:include>
)

add_library(linden::linden ALIAS linden)
