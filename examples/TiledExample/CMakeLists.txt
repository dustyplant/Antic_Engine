cmake_minimum_required( VERSION 3.0 )
project( TiledExample )

configure_file( ${PROJECT_SOURCE_DIR}/res/Test1.tmx 		 		${PROJECT_BINARY_DIR}/res/Test1.tmx 				COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/twilight-tiles.png 		${PROJECT_BINARY_DIR}/res/twilight-tiles.png 		COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/parallaxBG-interior1.png  ${PROJECT_BINARY_DIR}/res/parallaxBG-interior1.png 	COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/exterior-parallaxBG1.png  ${PROJECT_BINARY_DIR}/res/exterior-parallaxBG1.png 	COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/elisa-spritesheet1.png  	${PROJECT_BINARY_DIR}/res/elisa-spritesheet1.png 	COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/elisa.json					${PROJECT_BINARY_DIR}/elisa.json					COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/aldis.json				${PROJECT_BINARY_DIR}/res/aldis.json				COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/res/aldis.png					${PROJECT_BINARY_DIR}/res/aldis.png					COPYONLY )

include_directories( ${PROJECT_SOURCE_DIR}/include )

add_executable( TiledExample ${PROJECT_SOURCE_DIR}/TiledExample.cpp )
target_link_libraries( TiledExample Antic_Engine ${ANTIC_LIBRARIES} )