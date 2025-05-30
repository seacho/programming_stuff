#===============================================================================
# See: https://github.com/banach-space/llvm-tutor/blob/master/CMakeLists.txt
#===============================================================================
#如果不用苹果自带的clang，就得加很多的参数：
#cmake -DLLVM_INSTALL_DIR=/usr/local/Cellar/llvm/20.1.1/ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_FLAGS="-I/usr/local/Cellar/llvm/20.1.1/include/  -I/usr/local/Cellar/llvm/20.1.1/include/c++/v1/ -nostdinc++ -L/usr/local/lib" ..

cmake_minimum_required(VERSION 3.13.4)
project(llvm-pass-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#===============================================================================
# 1. VERIFY LLVM INSTALLATION DIR
#===============================================================================
# Set this to a valid LLVM installation dir:
set(LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

# A bit of a sanity checking:
set(LLVM_INSTALL_INCLUDE "${LLVM_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${LLVM_INSTALL_INCLUDE}")
message(FATAL_ERROR
    " LLVM_INSTALL_INCLUDE (${LLVM_INSTALL_INCLUDE}) is invalid.")
endif()

set(LLVM_INSTALL_CMAKE "${LLVM_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake")
if(NOT EXISTS "${LLVM_INSTALL_CMAKE}")
message(FATAL_ERROR
    " LLVM_INSTALL_CMAKE (${LLVM_INSTALL_CMAKE}) is invalid.")
endif()

#===============================================================================
# 2. LOAD LLVM CONFIGURATION
#    For more: http://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
#===============================================================================
# Add the location of LLVMConfig.cmake to CMake search paths (so that
# find_package can locate it):
list(APPEND CMAKE_PREFIX_PATH "${LLVM_INSTALL_DIR}/lib/cmake/")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_INSTALL_DIR}")

message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)

# Set the LLVM header and library paths
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

#===============================================================================
# 3. BUILD CONFIGURATION
#===============================================================================
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# Build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE
      STRING "Build type (default Debug):" FORCE)
endif()
#cmake -DLLVM_INSTALL_DIR=/usr/local/Cellar/llvm/19.1.7_1/ ..
# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall\
    -fdiagnostics-color=always")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# -fvisibility-inlines-hidden is set when building LLVM and on
# Darwin warnings are triggered if the project is built without
# this flag (though otherwise it builds fine). For consistency,
# add it here too.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fvisibility-inlines-hidden" SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
if (${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()
# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#===============================================================================
# 4. ADD SUB-TARGETS
# Doing this at the end so that all definitions and link/include paths are
# available for the sub-projects.
#===============================================================================
add_subdirectory(lib)
add_subdirectory(tool)
