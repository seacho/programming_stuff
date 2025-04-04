add_executable(passdemo
    Main.cpp
    ../lib/DCEPass.cpp
    )

target_link_libraries(passdemo
    LLVMCore
    LLVMIRReader
    LLVMPasses
    LLVMSupport)
target_include_directories(passdemo PRIVATE "../include")
