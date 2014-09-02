cmake_minimum_required( VERSION 2.6 )
project( Antic_Engine )

set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g --std=c++11" )

set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )

include_directories( ${CMAKE_SOURCE_DIR}/include )


#add_subdirectory( ${CMAKE_SOURCE_DIR}/src )

add_library( Antic_Engine STATIC 
	${CMAKE_SOURCE_DIR}/src/Engine.cpp
	${CMAKE_SOURCE_DIR}/src/StateManager.cpp
	${CMAKE_SOURCE_DIR}/src/GameState.cpp
	${CMAKE_SOURCE_DIR}/src/Antic_Graph.cpp
	${CMAKE_SOURCE_DIR}/src/RenderQueue.cpp
	${CMAKE_SOURCE_DIR}/src/EntityManager.cpp
	${CMAKE_SOURCE_DIR}/src/Entity.cpp
	${CMAKE_SOURCE_DIR}/src/EventSystem.cpp
	${CMAKE_SOURCE_DIR}/src/EMGrid.cpp
)

if( WIN32 )
	target_link_libraries( Antic_Engine mingw32 glew32 SDL2main )
endif( WIN32 )

if( UNIX )
	target_link_libraries( Antic_Engine )
endif( UNIX )

target_link_libraries( Antic_Engine SDL2 SDL2_image SDL2_ttf )