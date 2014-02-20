cmake_minimum_required( VERSION 2.6 )
project( Antic_Engine )

set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g --std=c++11" )

set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )

include_directories( ${CMAKE_SOURCE_DIR}/include )


#add_subdirectory( ${CMAKE_SOURCE_DIR}/src )

add_library( Antic_Engine STATIC 
	src/Engine.cpp
	src/StateManager.cpp
	src/GameState.cpp
	src/Antic_Graph.cpp
	src/RenderQueue.cpp
	src/EntityManager.cpp
	src/Entity.cpp
	src/EventSystem.cpp
)

if( WIN32 )
	target_link_libraries( Antic_Engine mingw32 glew32 SDL2main )
endif( WIN32 )

if( UNIX )
	target_link_libraries( Antic_Engine )
endif( UNIX )

target_link_libraries( Antic_Engine SDL2 SDL2_image SDL2_ttf )