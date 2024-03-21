#include "ast.hpp"
#include "../errors/errors.hpp"
#include "../symbol/symbol.hpp"

namespace ast {

    sym::Table vars;

    /********************************************************
    *                                                       *
    *                      Evaluation                       *
    *                                                       *
    ********************************************************/

    int LValue::eval() const {
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), nullptr);
        entry = vars.lookupEntry(entry);

        if (entry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }

        return entry->getValue();
    }

    int Cond::eval() const {
        if (first == nullptr && second == nullptr) {
            if (operation == "true") {
                return true;
            }
            return false;
        }
        if (operation == "<") return first->eval() < second->eval();
        if (operation == ">") return first->eval() > second->eval();
        if (operation == "==") return first->eval() == second->eval();
        if (operation == "!=") return first->eval() != second->eval();
        if (operation == ">=") return first->eval() >= second->eval();
        if (operation == "<=") return first->eval() <= second->eval();
        if (operation == "&") return first->eval() && second->eval();
        if (operation == "|") return first->eval() || second->eval();
        return false;
    }

    int BinOp::eval() const {

        if (expr2 != nullptr) {
            switch(op) {
                case '+': return expr1->eval() + expr2->eval();
                case '-': return expr1->eval() - expr2->eval();
                case '*': return expr1->eval() * expr2->eval();
                case '/': return expr1->eval() / expr2->eval();
                case '%': return expr1->eval() % expr2->eval();
            }
        }
        switch(op) {
            case '+': return expr1->eval();
            case '-': return -expr1->eval();
        }
        return 0;
    }

    int Const::eval() const {
        return num;
    }

    /* TODO: Implement this function */
    int Return::eval() const {
        return expr->eval();
    }


    /* TODO: Implement this function */
    // int Call::eval() const {
    //     for (auto &item : block) {
    //         item->run();
    //     }
    //     return 0;
    // }

    /********************************************************
    *                                                       *
    *                      Running                          *
    *                                                       *
    ********************************************************/

    void VarDef::run() const {
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), nullptr);

        if (vars.lookupEntry(entry) != nullptr) {
            RaiseSemanticError(variableExistsError_c, FATAL);
        }

        vars.insertEntry(entry);
    }


    void Block::run() const {
        for (auto stmt : list) {
            stmt->run();
        }
    }

    /* TODO: Implement this function */
    void Func::run() const {

        sym::EntryPtr entry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);

        vars.openScope(entry);
        for (auto stmt : def_list) {
            stmt->run();
        }
        compound->run();
        vars.closeScope();
    }


    void While::run() const {
        while (cond->eval()) {
            stmt->run();
        }
    }

    void If::run() const {
        if (stmt2 != nullptr) {
            if (cond->eval()) {
                stmt1->run();
            } else {
                stmt2->run();
            }
        } else {
            if (cond->eval()) {
                stmt1->run();
            }
        }
    }

    void Print::run() const {
        std::cout << expr->eval() << std::endl;
    }

    /* TODO: Possibly remove this function and implement eval() for Call */
    void Call::run() const {
        for (auto &item : block) {
            item->run();
        }
    }

    void Assign::run() const {
        std::string var_id = std::static_pointer_cast<LValue>(lvalue)->getId();
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(var_id, vars.getCurrentScope(), nullptr);
        
        entry = vars.lookupEntry(entry);

        if (entry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }

        entry->setValue(expr->eval());
    }


}
