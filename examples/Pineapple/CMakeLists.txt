cmake_minimum_required( VERSION 3.0 )
project( Pineapple )


configure_file( ${PROJECT_SOURCE_DIR}/res/Test2.tmx 		 		${PROJECT_BINARY_DIR}/res/Test2.tmx COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/twilight-tiles.png 		${PROJECT_BINARY_DIR}/res/twilight-tiles.png COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/parallaxBG-interior1.png  ${PROJECT_BINARY_DIR}/res/parallaxBG-interior1.png COPYONLY )

include_directories( 
	${PROJECT_SOURCE_DIR}/include 
)

set(SRC
	${SRC}
	${PROJECT_SOURCE_DIR}/src/TiledExample.cpp
	${PROJECT_SOURCE_DIR}/src/DemoState.cpp
	${PROJECT_SOURCE_DIR}/src/Rectangle.cpp
	${PROJECT_SOURCE_DIR}/src/EntityBox.cpp
)

add_executable( Pineapple ${SRC} )
target_link_libraries( Pineapple Antic_Engine ${ANTIC_LIBRARIES} )