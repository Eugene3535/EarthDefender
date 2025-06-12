cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(EarthDefender LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(BUILD_SHARED_LIBS OFF)
set(EXTERNAL_SOURCE_DIR $ENV{External})

add_compile_definitions("DEBUG=$<CONFIG:Debug>")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(${EXTERNAL_SOURCE_DIR}/sfml/2.6.2 sfml)

target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${EXTERNAL_SOURCE_DIR}/sfml//2.6.2/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>/openal32.dll
	)
endif()