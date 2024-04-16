#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <map>
#include <vector>

#include "../ast/ast.hpp"
#include "../types/types.hpp"
#include "../symbol/symbol.hpp"

namespace IR {

    void gen(ast::ASTPtr root);
    void libgen();

    class FunctionBlock;

    typedef std::shared_ptr<FunctionBlock> BlockPtr;

    class FunctionBlock {
        public:
            FunctionBlock() : function(nullptr), currentBlock(nullptr) {};
            ~FunctionBlock();

            // Getters 
            // =======
            llvm::BasicBlock* getCurrentBlock();
            std::vector<llvm::Type*> getParams(std::string name);
            llvm::Type* getVar(std::string name);
            llvm::AllocaInst* getValue(std::string name);
            llvm::AllocaInst* getAddress(std::string name);
            
            // Setters
            // =======
            void setFunction(llvm::Function* function);
            void setCurrentBlock(llvm::BasicBlock* block);

            // Adders
            // ======
            void addParam(std::string name, llvm::Type* type, sym::PassType pass);
            void addVar(std::string name, llvm::Type* type, sym::PassType pass);
            void addValue(std::string name, llvm::AllocaInst* value);
            void addAddress(std::string name, llvm::AllocaInst* address);


        private:
            llvm::Function* function;
            llvm::BasicBlock* currentBlock;
            std::vector<llvm::Type*> params;
            std::map<std::string, llvm::Type*> vars;
            std::map<std::string, llvm::AllocaInst*> values;
            std::map<std::string, llvm::AllocaInst*> addresses;
            std::vector<llvm::BasicBlock*> blocks;
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
            std::vector<std::map<std::string, llvm::Function*>> functions;
    };

}
