#include "MyPass.h"
#include <llvm/IR/InstIterator.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/IR/IRBuilder.h>
#include "llvm/IR/Module.h"
using namespace llvm;

namespace MyPass{
PreservedAnalyses AddWrapperPass::run(Function &F, FunctionAnalysisManager &FAM)
{
    for (auto& B : F) {
        // We modified the code.
        insertBeforeBlock(B);
    }

    return PreservedAnalyses::none();
}
    void AddWrapperPass::insertBeforeBlock(BasicBlock &BB){
    // 创建IRBuilder，插入到基本块第一条指令前
    IRBuilder<> Builder(&BB, BB.getFirstInsertionPt());

    Module *M = BB.getModule();
    LLVMContext& Ctx = BB.getContext();
    FunctionCallee logFunc = M->getOrInsertFunction(
        "log_func", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx)
        );

    // 生成随机数或唯一标识（示例用基本块地址）
    Value *BlockID = Builder.getInt32(reinterpret_cast<intptr_t>(&BB));

    // 插入调用指令
    Builder.CreateCall(logFunc, {BlockID});
    }
}
