#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <map>
#include <vector>

#include "../ast/ast.hpp"
#include "../symbol/symbol.hpp"

namespace IR {

    enum class ValueType {
        ADDRESS,
        VALUE,
    };

    struct Value {
        public:
            llvm::Value* value;
            llvm::Type* type;
            ValueType valueType;
    };

    void gen(ast::ASTPtr root, bool optimize);
    void libgen();
    void setupMain(ast::ASTPtr root);

    class FunctionBlock;

    typedef std::shared_ptr<FunctionBlock> BlockPtr;

    class FunctionBlock {
        public:
            FunctionBlock() : function(nullptr), currentBlock(nullptr) {};
            ~FunctionBlock() {};

            // Getters 
            // =======
            llvm::BasicBlock* getCurrentBlock();
            std::vector<llvm::Type*> getParams();
            Value getValue(std::string name);
            
            // Setters
            // =======
            void setFunction(llvm::Function* function);
            void setCurrentBlock(llvm::BasicBlock* block);

            // Adders
            // ======
            void addValue(std::string name, llvm::Value* value, llvm::Type* type, ValueType valueType);
            void addParam(std::string name, llvm::Type* type, sym::PassType pass);

        private:
            llvm::Function* function;
            llvm::BasicBlock* currentBlock;
            std::vector<llvm::Type*> params;
            std::map<std::string, Value> values;
    };

    class FunctionScope {
        public:
            FunctionScope() {};
            ~FunctionScope() {};

            void openScope();
            void closeScope();
            void insertFunction(std::string name, llvm::Function* function);
            void printFunctions();
            llvm::Function * getFunction(std::string name);

        private:
            std::vector<std::map<std::string, llvm::Function*>> functions;
    };

}
