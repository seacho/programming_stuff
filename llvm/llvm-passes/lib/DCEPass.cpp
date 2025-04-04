#include "AddConst.h"

#include "llvm/Support/Casting.h"
using namespace llvm;

namespace MyPass{
PreservedAnalyses DCEPass::run(Function &F, FunctionAnalysisManager &FAM)
{
    bool Changed = false;
    int cnt = 0;
    // 迭代删除死代码直到收敛
    do {
      Changed = false;
      for (BasicBlock& bb: F)
      {
           for (Instruction &I: bb)
           {
               // 跳过不可删除的指令：有副作用、Terminator指令、非空的
               if (I.mayHaveSideEffects() || I.isTerminator() || !I.use_empty())
                 continue;

               // 删除指令
               llvm::outs() << "delete 1 ins\n";
               I.eraseFromParent();
               Changed = true;

           }

      }
      if (Changed)
      {
          outs() << "changed " << cnt << "times";
          cnt++;
      }
    } while (Changed);

    return PreservedAnalyses::none();
}
}
