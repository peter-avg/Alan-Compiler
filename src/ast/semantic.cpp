#include "ast.hpp"
#include "../errors/errors.hpp"
#include "../symbol/symbol.hpp"
#include <iostream>
#include <memory>
#include <typeinfo>

namespace ast {

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/

    sym::Table vars;
    bool main_func = false;

    void Param::sem(sym::Table table) {
        sym::EntryPtr exists = table.lookupEntry(id, sym::LOCAL);
        if (exists != nullptr) {
            std::cerr << "Error: " << id << " already exists in the current scope" << std::endl;
            return;
        }
        sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, 1 /* level */, type);
        table.insertEntry(entry);
    };

    void Block::sem(sym::Table table) {
        for (auto item : list) {
            item->sem(table);
        }
    };

    void Func::sem(sym::Table table) {
        /* Check if the function already exists */
        sym::EntryPtr funcentry =  std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), retType);
        if (funcentry != nullptr) {
            std::cerr << "Error: " << id << "already exists in the current scope" << std::endl;
        }
        /* Check if this function is the main */               
             
        if (!main_func) {
            this->main = true;
            main_func = true;
        }
        
        /* Add the function in the Table */
        funcentry->addLocaldefs(def_list);
        funcentry->addCompound(compound); 

        vars.insertEntry(funcentry);
        vars.openScope(funcentry);

        for (auto param: param_list) {
            param->sem(vars);
            std::string par_id = std::static_pointer_cast<Param>(param)->getId();
            sym::EntryPtr paramentry = std::make_shared<sym::ParamEntry>(par_id, vars.getCurrentScope(), nullptr);
            funcentry->addParameters(paramentry);
            vars.insertEntry(paramentry);
        }

        for (auto local: def_list) {
            local->sem(vars);
        }

        compound->sem(vars);
        vars.closeScope();

    };

    void Const::sem(sym::Table table) {
        if (!types::sameType(num, types::intType)) {
            std::cerr << "Error: Condition is not of byte type" << std::endl;
        }

    };

    void VarDef::sem(sym::Table table) {
        if (value != INT_MAX) {
            if (!types::sameType(value, types::intType)) {
                std::cerr << "Error: array index must be an integer" << std::endl; 
            }

            sym::EntryPtr varentry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), type);
            varentry = vars.lookupEntry(varentry, sym::LOCAL);
            if (varentry != nullptr) {
                RaiseSemanticError(variableExistsError_c, FATAL);
            }
            vars.insertEntry(varentry);

        }
    };

    void Cond::sem(sym::Table table) {
        
        if (operation == "true" || operation == "false")
            type = types::byteType;

        else if (operation == "NOT") {
            first->sem(vars);
            if (!types::sameType(first, types::byteType)) 
                std::cerr << "Error: Condition is not of byte type" << std::endl;
        }

        else if (operation == "AND" || operation == "OR"){
            first->sem(vars);
            second->sem(vars);
            if (!types::sameType(first->type, types::byteType)) {
                if (!types::sameType(second, types::byteType)) {
                    std::cerr << "Error: Condition is not of byte type" << std::endl;
                }
            }
        }
        else {
            first->sem(vars);
            second->sem(vars);
            if (!types::sameType(first, second))
                std::cerr << "Error: Expressions don't have the same type" << std::endl;
        }
    };

    void While::sem(sym::Table table) {
          cond->sem(vars);
          if (!types::sameType(cond, types::byteType)){
              std::cerr << "Error: Condition in While Statement is not of Boolean type" << std::endl;
          }
    };
    
    void If::sem(sym::Table table) {
       cond->sem(vars);

      if (!types::sameType(cond, types::byteType)){
          std::cerr << "Error: Condition in If Statement is not of Boolean type" << std::endl;
      }

      stmt1->sem(vars);
      if (stmt2 != nullptr)
          stmt2->sem(vars);
    };

    void Return::sem(sym::Table table) {
        expr->sem(vars);
        type  = expr->type;
        
        if (!types::sameType(this->type, scopeType)) {
            std::cerr << "Error: Type of function does not match type of Return statement" << std::endl;
        }

        // Maybe add the Returns as something in each scope 
    };

    void Char::sem(sym::Table table) {
        
    };

    void BinOp::sem(sym::Table table) {
        expr1->sem(vars);
        expr2->sem(vars);

        if (!types::sameType(expr1->type, expr2->type))
            std::cerr << "Error: Binary operation expressions don't have the same type" << std::endl;
    };


    void String::sem(sym::Table table) {
            
    };

    void LValue::sem(sym::Table table) {
        if (expr != nullptr) {
            expr->sem(vars);
            if (!types::sameType(expr->type, types::intType)){
                std::cerr << "Error: Index of array must be of type int" << std::endl;
            }
        }
        sym::EntryPtr varentry = std::make_shared<sym::VarEntry>(id, vars.getCurrentScope(), nullptr);
        varentry = vars.lookupEntry(varentry);

        if (varentry == nullptr) 
            std::cerr << "Error: Variable not found in this scope" << std::endl;
    };

    void Call::sem(sym::Table table) {
       int scope = vars.getCurrentScope();
       sym::EntryPtr funcentry = std::make_shared<sym::FuncEntry>(id, vars.getCurrentScope(), nullptr);
       funcentry = vars.lookupEntry(funcentry, sym::GLOBAL);
       if (funcentry == nullptr) 
           std::cerr << "Error: No function " << id << " found in this scope" <<  std::endl;

       if (block.size() < funcentry->parameters.size()) 
           std::cerr << "Error: Not enough arguments" << std::endl;
       else if (block.size() > funcentry->parameters.size())
           std::cerr << "Error: Too many arguments" << std::endl;

       for(auto &item: block) {
           item->sem(vars);
       }
        int i = 0;
       for (auto &item: block) {

            if (!types::sameType(item->type, funcentry->parameters[i++]->type)){
                std::cerr << "Error: type of argument does not parse type of parameter" << std::endl;
            }
            // type = funcentry->type; or something  
       }
    };


    void Assign::sem(sym::Table table) {
        lvalue->sem(vars); 
        expr->sem(vars);
        if (!types::sameType(lvalue->type, expr->type))
            std::cerr << "Error: type of expression does not match type of LValue" << std::endl;

        type = lvalue->type;
    };

    void Print::sem(sym::Table table) {
        
    };

}
