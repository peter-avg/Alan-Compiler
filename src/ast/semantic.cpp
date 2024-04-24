#include "../symbol/symbol.hpp"
#include "ast.hpp"
#include "../errors/errors.hpp"
#include "../library/library.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <typeinfo>

namespace ast {

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/

    bool main_func = false;
    
    void Param::sem(sym::Table &table) {
        sym::EntryPtr exists = table.lookupEntry(id, sym::LOCAL);
        if (exists != nullptr) {
            std::cerr << "Error: " << id << " already exists in the current scope" << std::endl;
            return;
        }
        sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, table.getCurrentScope(), type, pass);
        table.insertEntry(entry);
    };

    void Block::sem(sym::Table &table) {
        for (auto item : list) {
            item->sem(table);
        }
    };

    void Func::sem(sym::Table &table) {
        /* Check if the function already exists */
        sym::EntryPtr funcentry =  std::make_shared<sym::FuncEntry>(id, table.getCurrentScope(), type);
        funcentry = table.lookupEntry(id, sym::GLOBAL);
        if (funcentry != nullptr) {
            std::cerr << "Error: " << id << "already exists in the current scope" << std::endl;
        }
        /* Check if this function is the main */               
        funcentry =  std::make_shared<sym::FuncEntry>(id, table.getCurrentScope(), type);
        
        if (!main_func) {
            this->main = true;
            main_func = true;
        }
        
        /* Add the function in the Table */

        table.insertEntry(funcentry);
        table.openScope(funcentry);
        for (auto param: param_list) {
            param->sem(table);
            std::string par_id = std::static_pointer_cast<Param>(param)->getId();
            sym::EntryPtr paramentry = std::make_shared<sym::ParamEntry>(par_id, table.getCurrentScope(), param->getType(), param->pass);
            funcentry->addParameters(paramentry);
        }

        for (auto local: def_list) {
            local->sem(table);
        }

        compound->sem(table);

        if (funcentry->getType()->getTypeName() == "VoidType") {
            if (table.getReturns() != 0) 
                std::cerr << "Error: Void function can't have a return statement" << std::endl;
        }

        else if (funcentry->getType()->getTypeName() == "IntType" || funcentry->getType()->getTypeName() == "ByteType"){
            if (table.getReturns() == 0 )
                std::cerr << "Error: " << *(funcentry->getType()) << " function requires one or more return statements" << std::endl;
        }
        table.closeScope();

    };

    void Const::sem(sym::Table &table) {
        type = types::intType;
    };

    void VarDef::sem(sym::Table &table) {
        sym::EntryPtr varentry = table.lookupEntry(id, sym::LOCAL);
        if (varentry != nullptr) {
            RaiseSemanticError(variableExistsError_c, FATAL);
        }

        varentry = std::make_shared<sym::VarEntry>(id, table.getCurrentScope(), type);
        table.insertEntry(varentry);
    };

    void Cond::sem(sym::Table &table) {
        
        if (operation == "true" || operation == "false")
            type = types::byteType;

        else if (operation == "!") {
            first->sem(table);
            if (!types::sameType(first->type->getTypeName(), "byteType")) 
                std::cerr << "Error: Condition is not of byte type" << std::endl;
            type = types::byteType;
        }

        else if (operation == "&" || operation == "|"){
            first->sem(table);
            second->sem(table);
            if (!types::sameType(first->type->getTypeName(), "byteType")) {
                if (!types::sameType(second->type->getTypeName(), "byteType")) {
                    std::cerr << "Error: Condition is not of byte type" << std::endl;
                }
            }
            type = types::byteType;
        }
        else {
            first->sem(table);
            second->sem(table);
            if (!types::sameType(first->type->getTypeName(), second->type->getTypeName()))
                std::cerr << "Error: Expressions don't have the same type" << std::endl;
            type = types::byteType;
        }
    };

    void While::sem(sym::Table &table) {
          cond->sem(table);
          if (!types::sameType(cond->type->getTypeName(), "ByteType")){
              std::cerr << "Error: Condition in While Statement is not of Boolean type" << std::endl;
          }
    };
    
    void If::sem(sym::Table &table) {
       cond->sem(table);

      if (!types::sameType(cond->type->getTypeName(), "ByteType")){
          std::cerr << "Error: Condition in If Statement is not of Boolean type" << std::endl;
      }

      stmt1->sem(table);
      if (stmt2 != nullptr)
          stmt2->sem(table);
    };

    void Return::sem(sym::Table &table) {
        expr->sem(table);
        type  = expr->type;
        
        if (!types::sameType(this->type->getTypeName(), table.getScopeType()->getTypeName())){
            std::cerr << "Error: Type of function does not match type of Return statement" << std::endl;
        }
        
        table.addReturn();
        
    };

    void Char::sem(sym::Table &table) {
        type = types::byteType; 
    };

    void BinOp::sem(sym::Table &table) {
        expr1->sem(table);
        if (expr2 != nullptr) {
            expr2->sem(table);
            if (!types::sameType(expr1->type->getTypeName(), expr2->type->getTypeName()))
                std::cerr << "Error: Binary operation expressions don't have the same type" << std::endl;
        }
        type = expr1->type;
    };


    void String::sem(sym::Table &table) {
        std::cout << "String" << std::endl;
        type = types::BarrayType;
    };

    void LValue::sem(sym::Table &table) {
        sym::EntryPtr varentry = table.lookupEntry(id, sym::GLOBAL);
        if (varentry == nullptr) 
            std::cerr << "Error: Variable \"" << id << "\" not found in scope -> " << table.getCurrentScope() << std::endl;
        if (expr != nullptr) {
            expr->sem(table);
            if (!types::sameType(expr->type->getTypeName(), "IntType")){
                std::cerr << "Error: Index of array must be of type int" << std::endl;
            }
            type = varentry->getType()->getArrayType();
        }
        else 
            type = varentry->getType();
    };

    void Call::sem(sym::Table &table) {
        int scope = table.getCurrentScope();
        sym::EntryPtr funcentry = std::make_shared<sym::FuncEntry>(id, table.getCurrentScope(), nullptr);
        funcentry = table.lookupEntry(id, sym::GLOBAL);
        if (funcentry == nullptr) 
           std::cerr << "Error: No function " << id << " found in this scope" <<  std::endl;
        if (funcentry->getEType() != sym::FUNC) {
           std::cerr << "Error: " << id << " is not a function" <<  std::endl;
        }
        if (block.size() < funcentry->parameters.size()) 
           std::cerr << "Error: Not enough arguments" << std::endl;
        else if (block.size() > funcentry->parameters.size())
           std::cerr << "Error: Too many arguments" << std::endl;

        for(auto &item: block) {
           item->sem(table);
        }
        int i = 0;
        for (auto &item: block) {
            if (!types::sameType(item->getType()->getTypeName(), funcentry->parameters[i++]->getType()->getTypeName())){
                std::cerr << "Error: type of argument " << *item << " does not match type of parameter " << funcentry->parameters[i-1]->getId() << std::endl;
            }
        }
        this->type = funcentry->getType(); 
    };


    void Assign::sem(sym::Table &table) {
        lvalue->sem(table); 
        expr->sem(table);
        if (!types::sameType(lvalue->type->getTypeName(), expr->type->getTypeName()))
            std::cerr << "Error: type of expression does not match type of LValue" << std::endl;

        type = lvalue->type;
    };

    void Print::sem(sym::Table &table) {
        
    };

}
