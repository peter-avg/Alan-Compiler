#include "../symbol/symbol.hpp"
#include "ast.hpp"
#include "../errors/errors.hpp"
#include <memory>

extern sym::Table vars;

namespace ast {

    bool main_func_ = false;
    /********************************************************
    *                                                       *
    *                      Evaluation                       *
    *                                                       *
    ********************************************************/

    int String::eval() const {
        return 0;
    }

    int LValue::eval() const {
        std::cout << "LValue" << std::endl;
        sym::EntryPtr entry = vars.lookupEntry(this->id, sym::LOCAL);
        if (entry == nullptr) {
            sym::EntryPtr funcentry = vars.lookupEntry(id, sym::LOCAL);
             if (entry == nullptr) 
                 RaiseSemanticError(variableNotFoundError_c, FATAL);
        }
        return entry->getValue();
    }

    int Cond::eval() const {
        std::cout << "Cond" << std::endl;
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
        std::cout << "BinOp" << std::endl;
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
        std::cout << "Const" << std::endl;
        return num;
    }

    int Return::run() const {
        std::cout << "Return" << std::endl;
        int result = expr->eval();
        return result;
    }


    int Call::eval() const {
        std::cout << "Call" << std::endl;
        int scope = vars.getCurrentScope();
        sym::EntryPtr funcentry = vars.lookupEntry(this->id, sym::GLOBAL);
        if (funcentry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }
        int i = 0;
        int paramscope = funcentry->getLevel();
        for(auto &item: block) {
            if (!funcentry->parameters.empty()) {
                std::string paramid = funcentry->parameters[i++]->getId();
                sym::EntryPtr paramentry = std::make_shared<sym::VarEntry>(paramid, vars.getCurrentScope()+1, nullptr);
                vars.insertEntry(paramentry);
                paramentry->setValue(item->eval());
            }
            else 
                break;
        }
        vars.openScope(funcentry);
        
        for (auto local: funcentry->getLocaldefs()){
                local->run(); 
        }
        
        int result = funcentry->getCompound()->run();
        vars.closeScope();
        return result;
     }

    /********************************************************
    *                                                       *
    *                      Running                          *
    *                                                       *
    ********************************************************/

    int VarDef::run() const {
        sym::EntryPtr entry = vars.lookupEntry(this->id, sym::LOCAL);

        if (entry != nullptr) {
            RaiseSemanticError(variableExistsError_c, FATAL);
        }


        vars.insertEntry(entry);
        std::cout << "VarDef" << std::endl;
        return 0;
    }


    int Block::run() const {
        std::cout << "Block" << std::endl;
        int result;
        for (auto stmt : list) {
            result = stmt->run();
        }
        return result;
    }

    /* TODO: Maybe don't create a new scope regardless of whether the function is the main or not. 
     * just add the function to the current scope and add its parameters in the parameter vector. 
     * Then, when the function is called, do the open Scope then */
    int Func::run() const {
        std::cout << "Func" << std::endl;
        std::string id = this->id;
        sym::EntryPtr entry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);
        entry->addLocaldefs(def_list);
        entry->addCompound(compound);
        vars.insertEntry(entry);
        for (auto param: param_list) {
            std::string par_id = std::static_pointer_cast<Param>(param)->getId();
            sym::EntryPtr paramentry = std::make_shared<sym::ParamEntry>(par_id, vars.getCurrentScope(), this->type, sym::PassType::value);
            entry->addParameters(paramentry);
        }
        
        if (!main_func_) {
            main_func_ = true;
            for (auto local: def_list){
                local->run();
            }
            compound->run();
        } 
        return 0;
    }

    int While::run() const {
        std::cout << "While" << std::endl;
        while (cond->eval()) {
            stmt->run();
        }
        return 0;
    }

    int If::run() const {
        std::cout << "If" << std::endl;
        if (stmt2 != nullptr) {
            if (cond->eval()) {
                return stmt1->run();
            } else {
                return stmt2->run();
            }
        } else {
            if (cond->eval()) {
                return stmt1->run();
            }
        }
        return 0;
    }

    int Print::run() const {
        std::cout << "Print" << std::endl;
        std::cout << expr->eval() << std::endl;
        return 0;
    }

    /* TODO: Possibly remove this function and implement eval() for Call */
    // int Call::run() const {
    //     for (auto &item : block) {
    //         item->run();
    //     }
    // }


    int Assign::run() const {
        std::cout << "Assign" << std::endl;
        std::string var_id = std::static_pointer_cast<LValue>(lvalue)->getId();
        // sym::EntryPtr entry = std::make_shared<sym::VarEntry>(var_id, vars.getCurrentScope(), nullptr);
        
        sym::EntryPtr entry = vars.lookupEntry(var_id, sym::LOCAL);
        
        if (entry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }

        entry->setValue(expr->eval());
        return 0;
    }


}
