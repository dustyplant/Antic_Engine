cmake_minimum_required( VERSION 2.6 )
project( Antic_Engine )

set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++11" )
set( CMAKE_STATIC_LINKER_FLAGS "${CMAKE_CXX_FLAGS} --static")

set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )

include_directories( ${CMAKE_SOURCE_DIR}/include )

#add_subdirectory( ${CMAKE_SOURCE_DIR}/src )

add_library( Antic_Engine STATIC 
	src/Engine.cpp
	src/StateManager.cpp
	src/GameState.cpp
)

if( WIN32 )
	target_link_libraries( Antic_Engine mingw32 SDL2main )
endif( WIN32 )

target_link_libraries( Antic_Engine SDL2 SDL2_image SDL2_ttf )