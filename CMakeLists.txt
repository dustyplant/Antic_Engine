cmake_minimum_required( VERSION 2.8 )
project( Antic_Engine )

add_compile_options( --std=c++11 )
add_compile_options( -g )

set( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/lib )

add_subdirectory( submodules/Antic_Graph )

include_directories( ${AGRAPH_INCLUDE_DIRS} )

include_directories( ${PROJECT_SOURCE_DIR}/include )

add_library( Antic_Engine STATIC 
	${PROJECT_SOURCE_DIR}/src/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/StateManager.cpp
	${PROJECT_SOURCE_DIR}/src/GameState.cpp
	${PROJECT_SOURCE_DIR}/src/RenderQueue.cpp
	${PROJECT_SOURCE_DIR}/src/EntityManager.cpp
	${PROJECT_SOURCE_DIR}/src/Entity.cpp
	${PROJECT_SOURCE_DIR}/src/EventSystem.cpp
	${PROJECT_SOURCE_DIR}/src/EMGrid.cpp
)


set( ANTIC_LIBRARIES ${ANTIC_LIBRARIES} ${AGRAPH_LIBRARIES} CACHE STRING "Antic_Engine link libraries" )
target_link_libraries( Antic_Engine ${ANTIC_LIBRARIES})

#add_subdirectory( examples )