#include "MyPass.h"
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Operator.h>
#include <llvm/ADT/SetVector.h>
using namespace llvm;

namespace MyPass{
PreservedAnalyses DCEPass::run(Function &F, FunctionAnalysisManager &FAM)
{
    bool Changed = false;

    do{
        SetVector<Value*> setValueRef;
        for (Instruction &I : llvm::make_early_inc_range(instructions(F))){
            if ((I.isSafeToRemove()) && (I.use_begin() == I.use_end())) {
                outs() << "delete " << I << "\n";
                I.eraseFromParent();
            }

        }
    }while(Changed);

    return PreservedAnalyses::none();
}

}
