cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create compile_commands.json (For clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_STATIC_LIBRARY_PREFIX "")
#set(CMAKE_SHARED_LIBRARY_PREFIX "")

project(LuaHotKey)

option(TEST "Use google test" OFF)

set(LibSourceFiles
	"src/Definitions.h"
	"src/KeyboardHook.cpp"
	"src/KeyboardHook.h"
	"src/KeyStroke.cpp"
	"src/KeyStroke.h"
	"src/KeyStrokeLua.cpp"
	"src/KeyStrokeLua.h"
	"src/KeyboardSubHook.cpp"
	"src/KeyboardSubHook.h"
	"src/Keyboard.cpp"
	"src/Keyboard.h"
	"src/Dll.cpp"
	"src/Dll.h"
	"src/AttributeTree.h"
	"src/Modifiers.cpp"
	"src/Modifiers.h"
	"src/Flags.cpp"
	"src/Flags.h"
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
	add_library(LuaHotKey SHARED ${LibSourceFiles})
	set_target_properties(LuaHotKey PROPERTIES WIN32_EXECUTABLE ON)
	set_target_properties(LuaHotKey PROPERTIES PREFIX "")

	target_include_directories(LuaHotKey PUBLIC "${LuaDirectory}/include")
	target_link_libraries(LuaHotKey "${LuaDirectory}/lua5.1.lib")
endif()

add_custom_command(
	TARGET LuaHotKey POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	        ${LuaDirectory}/lua5.1.dll
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/lua5.1.dll
	)

