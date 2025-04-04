#===============================================================================
# See: https://llvm.org/docs/CMake.html#developing-llvm-passes-out-of-source
#===============================================================================
add_library(PassDemo SHARED

    AddConstPlugin.cpp
    DCEPass.cpp)

target_include_directories(PassDemo PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(PassDemo PRIVATE LLVMPasses)


