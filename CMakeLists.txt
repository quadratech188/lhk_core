cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create compile_commands.json (For clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(lhk_core)

option(TEST "Use google test" OFF)

# Find Lua
if (NOT DEFINED LUA_LIBDIR)
	message("LUA_LIBDIR is not set, this is not being run by luarocks")
	find_package(Lua REQUIRED)
	set(LUA_INCDIR ${LUA_INCLUDE_DIR})
else()
	file(TO_CMAKE_PATH ${LUA_LIBDIR} temp)
	set(LUA_LIBRARIES ${temp}/${LUA_LIBDIR_FILE})
endif()

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
	"src/Layers.cpp"
	"src/Layers.h"
	"src/LayerLua.cpp"
	"src/LayerLua.h"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")


if (TEST)
    # Build LuaHotKey as a library
    add_library(lhk_core ${LibSourceFiles})
    set_target_properties(lhk_core PROPERTIES WIN32_EXECUTABLE ON)

    target_include_directories(lhk_core PUBLIC ${LUA_INCDIR})
    target_link_libraries(lhk_core ${LUA_LIBRARIES})

    add_subdirectory(Tests)
else()
    add_library(lhk_core SHARED ${LibSourceFiles})
    set_target_properties(lhk_core PROPERTIES WIN32_EXECUTABLE ON)
    set_target_properties(lhk_core PROPERTIES PREFIX "")
	set_target_properties(lhk_core PROPERTIES COMPILE_FLAGS "-g")

    target_include_directories(lhk_core PUBLIC ${LUA_INCDIR})
    target_link_libraries(lhk_core ${LUA_LIBRARIES})
	install(TARGETS lhk_core DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
