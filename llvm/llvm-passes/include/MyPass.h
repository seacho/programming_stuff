
#ifndef MY_PASS_H
#define MY_PASS_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
namespace MyPass {


// 死代码消除pass，DeadCodeElimination
struct DCEPass: public llvm::PassInfoMixin<DCEPass>{

    llvm::PreservedAnalyses run(llvm::Function &F,
                                llvm::FunctionAnalysisManager &FAM);
};

}

#endif
