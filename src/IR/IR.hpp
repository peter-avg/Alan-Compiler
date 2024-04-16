#include <iostream>
#include <map>
#include <deque>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

namespace IR {


    class Block;

    typedef std::shared_ptr<Block> BlockPtr;
    typedef std::deque<BlockPtr> BlockList;
    typedef std::map<std::string, llvm::Function*> functionTable;
    typedef std::map<std::string, llvm::AllocaInst*> valueTable;

    class Block {
        public:
            Block();
            ~Block();

    };



}
