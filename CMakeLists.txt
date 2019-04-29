cmake_minimum_required(VERSION 3.0.0)
project(buba_cli VERSION 0.1.0 LANGUAGES CXX)

message(STATUS "CMAKE_SYSTEM_PREFIX_PATH=${CMAKE_SYSTEM_PREFIX_PATH}")
	
##### Configuration

configure_file(config/README.in ${CMAKE_SOURCE_DIR}/README.md)

##### Source

add_subdirectory(source)

##### Test

#add_subdirectory(test)

##### Documentation

#add_subdirectory(doc)

##### Example

#add_subdirectory(example)
