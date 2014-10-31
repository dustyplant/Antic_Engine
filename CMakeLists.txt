cmake_minimum_required( VERSION 2.8 )
project( Antic_Engine )

#set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g --std=c++11" )
add_compile_options( --std=c++11 )
add_compile_options( -g )

set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )

include_directories( ${PROJECT_SOURCE_DIR}/include )


#add_subdirectory( ${CMAKE_SOURCE_DIR}/src )

add_library( Antic_Engine STATIC 
	${PROJECT_SOURCE_DIR}/src/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/StateManager.cpp
	${PROJECT_SOURCE_DIR}/src/GameState.cpp
	${PROJECT_SOURCE_DIR}/src/Antic_Graph.cpp
	${PROJECT_SOURCE_DIR}/src/RenderQueue.cpp
	${PROJECT_SOURCE_DIR}/src/EntityManager.cpp
	${PROJECT_SOURCE_DIR}/src/Entity.cpp
	${PROJECT_SOURCE_DIR}/src/EventSystem.cpp
	${PROJECT_SOURCE_DIR}/src/EMGrid.cpp
)



if( WIN32 )
	set( ANTIC_LIBS Antic_Engine mingw32 glew32 SDL2main )
endif( WIN32 )

if( UNIX )
	
endif( UNIX )

set( ANTIC_LIBS ${ANTIC_LIBS} SDL2 SDL2_image SDL2_ttf )

target_link_libraries( Antic_Engine ${ANTIC_LIBS} )