cmake_minimum_required( VERSION 3.0 )
project( example1 )

add_executable( example1 main.cpp )
target_link_libraries( example1 Antic_Engine ${ANTIC_LIBRARIES} )