cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Tests)

set(TestSourceFiles
	"pch.cpp"
	"pch.h"
	"test.cpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests ${TestSourceFiles})
target_include_directories(Tests PUBLIC 
	"${LuaDirectory}/include"
	"${LuaHotKey_SOURCE_DIR}/src")
target_link_libraries(Tests
	"${LuaDirectory}/lua5.1.lib"
	LuaHotKey
	GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)
