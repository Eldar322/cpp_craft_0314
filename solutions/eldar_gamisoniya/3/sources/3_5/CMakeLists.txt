find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader binary_writer Boost )

