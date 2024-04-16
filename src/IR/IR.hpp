#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <map>
#include <deque>

#include "../ast/ast.hpp"

namespace IR {

    void gen(ast::ASTPtr root);
    void libgen();

    class FunctionBlock;

    typedef std::shared_ptr<FunctionBlock> BlockPtr;
    typedef std::deque<BlockPtr> BlockList;
    typedef std::map<std::string, llvm::Function*> functionTable;
    typedef std::map<std::string, llvm::AllocaInst*> valueTable;

    class FunctionBlock {
        public:
            FunctionBlock();
            ~FunctionBlock();

            llvm::BasicBlock* getCurrentBlock();
            void setCurrentBlock(llvm::BasicBlock* block);

        private:
            llvm::Function* function;
            llvm::BasicBlock* currentBlock;
            BlockList blocks;
            valueTable values;
            valueTable addresses;
    };

    class FunctionScope {
        public:
            FunctionScope();
            ~FunctionScope();

            void openScope();
            void closeScope();
            void insertFunction(std::string name, llvm::Function* function);
            llvm::Function * getFunction(std::string name);

        private:
            std::deque<functionTable> functions;
    };

}
