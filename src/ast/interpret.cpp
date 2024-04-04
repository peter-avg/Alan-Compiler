#include "../symbol/symbol.hpp"
#include "ast.hpp"
#include "../errors/errors.hpp"
#include <memory>
#include <typeinfo>

namespace ast {

    sym::Table vars;
    bool main_func = false;
    /********************************************************
    *                                                       *
    *                      Evaluation                       *
    *                                                       *
    ********************************************************/

    int LValue::eval() const {
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), nullptr);
        entry = vars.lookupEntry(entry, sym::LOCAL);
        //std::cout << "In LValue, entry I just looked up with id: " << id << " in the scope " << vars.getCurrentScope() << std::endl;
        if (entry == nullptr) {
            sym::EntryPtr funcentry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);
            funcentry = vars.lookupEntry(funcentry, sym::LOCAL);
             if (entry == nullptr) 
                 RaiseSemanticError(variableNotFoundError_c, FATAL);
        }
        //std::cout << "In LValue, Variable of the name " << entry->getId() << " in the scope " << vars.getCurrentScope() << " has value " << entry->getValue() << std::endl;
        return entry->getValue();
    }

    int Cond::eval() const {
        //std::cout << "Cond" << std::endl;

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
        //std::cout << "BinOp" << std::endl;
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
        //std::cout << "Const " << num << std::endl;
        return num;
    }

    /* TODO: Implement this function */
    int Return::run() const {
        int result = expr->eval();
        //std::cout << "Return:" << result << std::endl;
        return result;
    }


    /* TODO: Implement this function */
    int Call::eval() const {
        //std::cout << "Call" << std::endl;
        //std::cout << "Call: Trying to find the func " << id << std::endl;
        int scope = vars.getCurrentScope();
        sym::EntryPtr funcentry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);
        funcentry = vars.lookupEntry(funcentry, sym::GLOBAL);
        if (funcentry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }
        int i = 0;
        int paramscope = funcentry->getLevel();
        //std::cout << "The scope of the function " << funcentry->getId() << " called is " << paramscope << std::endl;
        //std::cout << "The current scope, the scope of the call, is " << vars.getCurrentScope() << std::endl;
        for(auto &item: block) {
            if (!funcentry->parameters.empty()) {
                std::string paramid = funcentry->parameters[i++]->getId();
                // Get the id and add the parameter now in the  new scope with the correct value, maybe add it as a variable, not sure 
                sym::EntryPtr paramentry = std::make_shared<sym::VarEntry>(paramid, vars.getCurrentScope()+1, nullptr);
                vars.insertEntry(paramentry);
                //std::cout << "Level of the variable entry " << paramentry->getId() << " I just made: " << paramentry->getLevel() << std::endl;
                paramentry->setValue(item->eval());
                //std::cout << "The value I'm trying to pass is " << item->eval() << std::endl;;
                //std::cout << "Parameter " << funcentry->parameters[i-1]->getId() << " = " << paramentry->getValue() << std::endl;
            }
            else 
                break;
        }
        vars.openScope(funcentry);
        
        for (auto local: funcentry->getLocaldefs()){
                local->run(); 
        }
        
        //std::cout << "Now going to run the compound statements of the function " << funcentry->getId() << std::endl; 
        /*if (funcentry->getCompound())
            std::cout << "Function " << funcentry->getId() << " has compound statements" << std::endl;
        */
        int result = funcentry->getCompound()->run();
        //std::cout << "Call n." << vars.getCurrentScope() << " has return =  " << result << std::endl;
        vars.closeScope();
        //std::cout << "The result of the call of the function " << funcentry->getId() << " is: " << result << std::endl;
        return result;
       // sym::EntryPtr ReturnEntry = std::make_shared<sym::ReturnEntry>();
    //  TODO: Add the values of the call to the right Parameters and run the block of the function 
    //     for (auto &item : block) {
    //         item->run();
    //     }
    //     return 0;
     }

    /********************************************************
    *                                                       *
    *                      Running                          *
    *                                                       *
    ********************************************************/

    int VarDef::run() const {
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), nullptr);
        //std::cout << "Variable here " << std::endl;

        if (vars.lookupEntry(entry, sym::LOCAL) != nullptr) {
            RaiseSemanticError(variableExistsError_c, FATAL);
        }

        vars.insertEntry(entry);
        return 0;
    }


    int Block::run() const {
        //std::cout << "In Block of function, running" << std::endl;
        int result;
        for (auto stmt : list) {
            //std::cout << "Block: running " << stmt->run() << std::endl;
            result = stmt->run();
        }
        //std::cout << "Block result = " << result << std::endl;
        return result;
    }

    /* TODO: Implement this function */
    /* TODO: Maybe don't create a new scope regardless of whether the function is the main or not. 
     * just add the function to the current scope and add its parameters in the parameter vector. 
     * Then, when the function is called, do the open Scope then */
    int Func::run() const {
        //std::cout << "Func " << id << " here" << std::endl;
        sym::EntryPtr entry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);
        entry->addLocaldefs(def_list);
        entry->addCompound(compound);
        /*if (compound)
            std::cout << "Function " << entry->getId() << " has compound statements" << std::endl;
        if (entry->getCompound())
            std::cout << "And they have been passed in the entry" << std::endl ;
        if (!entry->getLocaldefs().empty()) 
            std::cout << "Function " << entry->getId() << " has local definitions" << std::endl;
        */
        //std::cout << "Func: The scope is: " << vars.getCurrentScope() << std::endl;
        vars.insertEntry(entry);
        //vars.openScope(entry);
        //std::cout << "Func: The scope I created is: " << vars.getCurrentScope() << std::endl;
        for (auto param: param_list) {
            std::string par_id = std::static_pointer_cast<Param>(param)->getId();
            //std::cout << "Par_id = " << par_id << std::endl; 
            sym::EntryPtr paramentry = std::make_shared<sym::ParamEntry>(par_id, vars.getCurrentScope(), nullptr);
            //vars.insertEntry(paramentry);
            //std::cout << "The parameter " << paramentry->getId() << " I added is in the scope: " << vars.getCurrentScope() << std::endl;
            entry->addParameters(paramentry);
        }
        //std::cout << "Current scope is: " << vars.getCurrentScope() << std::endl; 
        
        if (!main_func) {
            main_func = true;
            //std::cout << "I'm in the main function " << std::endl;
            for (auto local: def_list){
                local->run();
            }
            compound->run();
            //vars.closeScope();
        } 
        return 0;
    }

    int While::run() const {
        //std::cout << "While" << std::endl;
        while (cond->eval()) {
            stmt->run();
        }
        return 0;
    }

    int If::run() const {
        if (stmt2 != nullptr) {
            if (cond->eval()) {
                //std::cout << "The condition is true" <<  std::endl;
                return stmt1->run();
            } else {
                //std::cout << "The condition is false" <<  std::endl;
                return stmt2->run();
            }
        } else {
            if (cond->eval()) {
                //std::cout << "The condition is false" <<  std::endl;
                return stmt1->run();
            }
        }
        return 0;
    }

    int Print::run() const {
        //std::cout << "Print here" << std::endl;
        std::cout << expr->eval() << std::endl;
        return 0;
    }

    /* TODO: Possibly remove this function and implement eval() for Call */
    /*int Call::run() const {
        for (auto &item : block) {
            item->run();
        }
    }*/


    int Assign::run() const {
        //std::cout << "Assign: in level-scope: " << vars.getCurrentScope() << std::endl;
        std::string var_id = std::static_pointer_cast<LValue>(lvalue)->getId();
        sym::EntryPtr entry = std::make_shared<sym::VarEntry>(var_id, vars.getCurrentScope(), nullptr);
        
        entry = vars.lookupEntry(entry, sym::LOCAL);
        
        if (entry == nullptr) {
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }

        entry->setValue(expr->eval());
        //std::cout << "Assign of " << var_id << " = " << entry->getValue() << std::endl;
        return 0;
    }


}
