cmake_minimum_required( VERSION 2.8 )
project( Antic_Engine )

add_compile_options( --std=c++11 )
add_compile_options( -g )

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )
set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )
link_directories( ${CMAKE_BINARY_DIR}/lib )

find_package( Box2D REQUIRED )
include_directories( ${PROJECT_SOURCE_DIR}/submodules/Antic_Graph/submodules/glfw/include )
add_subdirectory( submodules )

set( ANTIC_INCLUDE_DIR
	${ANTIC_INCLUDE_DIR}
	${AGRAPH_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/submodules/tmxparser/src
	${PROJECT_SOURCE_DIR}/include
	${BOX2D_INCLUDE_DIR}
	CACHE STRING "Antic_Engine include directories"
)

#include_directories( ${AGRAPH_INCLUDE_DIRS} )
#include_directories( ${PROJECT_SOURCE_DIR}/submodules/tmxparser/src )

#include_directories( ${PROJECT_SOURCE_DIR}/include )

include_directories( ${ANTIC_INCLUDE_DIR} )

add_library( Antic_Engine STATIC 
	${PROJECT_SOURCE_DIR}/src/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/StateManager.cpp
	${PROJECT_SOURCE_DIR}/src/GameState.cpp
	${PROJECT_SOURCE_DIR}/src/RenderQueue.cpp
	${PROJECT_SOURCE_DIR}/src/EntityManager.cpp
	${PROJECT_SOURCE_DIR}/src/Entity.cpp
	${PROJECT_SOURCE_DIR}/src/EventSystem.cpp
	${PROJECT_SOURCE_DIR}/src/EMGrid.cpp
	${PROJECT_SOURCE_DIR}/src/TiledLevel.cpp
	${PROJECT_SOURCE_DIR}/src/Physics.cpp
)


set( ANTIC_LIBRARIES ${ANTIC_LIBRARIES} ${AGRAPH_LIBRARIES} tmxparser ${TINYXML_LIBRARIES} ${BOX2D_LIBRARIES} CACHE STRING "Antic_Engine link libraries" )
target_link_libraries( Antic_Engine ${ANTIC_LIBRARIES})

add_subdirectory( examples )