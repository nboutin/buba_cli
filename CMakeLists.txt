cmake_minimum_required(VERSION 3.1.0)
project(buba_cli VERSION 0.1.0 LANGUAGES CXX)

##### Configuration

set(ENV{PKG_CONFIG_PATH} "/usr/local/pkgconfig")

#configure_file(config/README.in ${CMAKE_SOURCE_DIR}/README.md)

##### Source

add_subdirectory(source)

##### Test

#add_subdirectory(test)

##### Documentation

#add_subdirectory(doc)

##### Example

#add_subdirectory(example)

##### Proof Of Concept

add_subdirectory(poc)