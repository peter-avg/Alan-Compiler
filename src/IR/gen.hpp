#ifndef __GEN_HPP__
#define __GEN_HPP__

#include <llvm/IR/Value.h>
#include <map>
#include <vector>
#include <string>

#include "../ast/ast.hpp"
#include "../symbol/symbol.hpp"

namespace IR {

    struct Value {
        public:
            llvm::Value* value;
            llvm::Type* type;
            sym::PassType valueType;
    };

    void setupMain(ast::ASTPtr root);
    void optimise();
    void gen(ast::ASTPtr root);
    void libgen();

    class Variables {
        public:
            Variables() {
                variables.push_back(std::map<std::string, Value>());
            }

            void openScope() {
                variables.push_back(std::map<std::string, Value>());
            }

            void closeScope() {
                if (variables.size() == 1) {
                    return;
                }
                variables.pop_back();
            }

            void addVariable(std::string name, Value value) {
                variables.back()[name] = value;
            }

            Value getVariable(std::string name) {
                for (int i = variables.size() - 1; i >= 0; i--) {
                    if (variables[i].find(name) != variables[i].end()) {
                        return variables[i][name];
                    }
                }
                return Value();
            }

        private:
            std::vector<std::map<std::string, Value>> variables;

    };

}



#endif // __GEN_HPP__
