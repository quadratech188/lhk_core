
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CONFIGURATION_TYPES Debug Release Test)

project(LuaHotKey)

option(TEST "Use google test" OFF)

set(LibSourceFiles
	"src/Definitions.h"
	"src/KeyboardHook.cpp"
	"src/KeyboardHook.h"
	"src/KeyboardHookLua.cpp"
	"src/KeyboardHookLua.h"
	"src/LuaEnvironment.cpp"
	"src/LuaEnvironment.h"
	"src/Source.cpp"
)

set(LuaDirectory "${PROJECT_SOURCE_DIR}/lua-5.1.5_Win64_dll17_lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if (TEST)
	# Build LuaHotKey as a library
	add_library(LuaHotKey ${LibSourceFiles})
	set_target_properties(LuaHotKey PROPERTIES WIN32_EXECUTABLE ON)

	target_include_directories(LuaHotKey PUBLIC "${LuaDirectory}/include")
	target_link_libraries(LuaHotKey "${LuaDirectory}/lua5.1.lib")

	add_subdirectory(Tests)
else()
	add_executable(LuaHotKey WIN32 ${LibSourceFiles})
	target_include_directories(LuaHotKey PUBLIC "${LuaDirectory}/include")
	target_link_libraries(LuaHotKey "${LuaDirectory}/lua5.1.lib")
endif()

add_custom_command(
	TARGET LuaHotKey POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	        ${LuaDirectory}/lua5.1.dll
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/lua5.1.dll
	)
