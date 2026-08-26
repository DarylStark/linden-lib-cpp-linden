add_library(
	linden INTERFACE
)

target_include_directories(
		linden
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(
	linden
	INTERFACE
		cxx_std_26
)

add_library(linden::linden ALIAS linden)

install(
	TARGETS
		linden
	EXPORT
		lindenTargets
)

install(
	DIRECTORY
		${PROJECT_SOURCE_DIR}/include/
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}
)