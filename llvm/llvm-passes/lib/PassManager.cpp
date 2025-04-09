#include "MyPass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;



// -passes=”{Name}”
bool registerPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {


    if (Name == "DCE"){
        FPM.addPass(MyPass::DCEPass());
        return true;
    }
    if (Name == "AddWrapper"){
        FPM.addPass(MyPass::AddWrapperPass());
        return true;
    }
    return false;
}

PassPluginLibraryInfo getAddConstPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "passdemo", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {

                //PB.registerAnalysisRegistrationCallback(registerAnalyses);

                PB.registerPipelineParsingCallback(registerPipeline);
            }};
}

// The public entry point for a pass plugin:
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getAddConstPluginInfo();
}
