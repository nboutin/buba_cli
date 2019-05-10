##### Target

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/printer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

##### 3rd party

find_package(PkgConfig REQUIRED)
pkg_check_modules(BUBA REQUIRED buba)

target_include_directories(${PROJECT_NAME} PRIVATE ${BUBA_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${BUBA_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${BUBA_LIBRARIES})
