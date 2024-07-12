#include "../symbol/symbol.hpp"
#include "ast.hpp"
#include "../errors/errors.hpp"
#include "../library/library.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>

namespace ast {

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/

    bool main_func = false;
    std::map<std::string, ASTPtr> globalsMap;
    

    bool Param::sem(sym::Table &table) {
        sym::EntryPtr exists = table.lookupEntry(id, sym::LOCAL);
        if (exists != nullptr) {
            std::cerr << "Error: parameter with id ->" << id << " already exists in the scope of the function -> " << table.getCurrentScope() << std::endl;
            return false;
        }
        sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, table.getCurrentScope(), type, pass);
        table.insertEntry(entry);
        return false;
    };

    bool Block::sem(sym::Table &table) {
        bool hasReturn = false;
        for (auto item : list) {
            hasReturn |= item->sem(table);
        }
        return hasReturn;

    };

    bool Func::sem(sym::Table &table) {
        std::cout << "Func::sem() -> " << this->getId() << std::endl;
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
        
        bool hasReturns = false;

        hasReturns = compound->sem(table);
        
        funcentry = table.lookupEntry(id, sym::GLOBAL);
        for (auto global: funcentry->getGlobals()) {
            this->addGlobalVariables(ast::ASTPtr(std::make_shared<ast::Param>(global->getId(), "reference", global->getType())));
        }

        for (auto global: this->globals_list) {
            std::cout << "Func::sem() -> added global variable in globals with id -> " << global->getId() << std::endl; 
        }

        if (funcentry->getType()->getTypeName() == "VoidType") {
            if (hasReturns) 
                std::cerr << "Error: Void function can't have a return statement" << std::endl;
        }

        else if (funcentry->getType()->getTypeName() == "IntType" || funcentry->getType()->getTypeName() == "ByteType"){
            if (!hasReturns)
                std::cerr << "Error: " << *(funcentry->getType()) << " function requires one or more return statements" << std::endl;
        }
        table.closeScope();
        return hasReturns;

    };

    bool Const::sem(sym::Table &table) {
        type = types::intType;
        return false;
    };

    bool VarDef::sem(sym::Table &table) {
        sym::EntryPtr varentry = table.lookupEntry(id, sym::LOCAL);
        if (varentry != nullptr) {
            RaiseSemanticError(variableExistsError_c, FATAL);
        }

        varentry = std::make_shared<sym::VarEntry>(id, table.getCurrentScope(), type);
        table.insertEntry(varentry);
        return false;
    };

    bool Cond::sem(sym::Table &table) {
        if (operation == "true" || operation == "false") {
            type = types::byteType;
        }
        else if (operation == "!") {
            first->sem(table);
            if (!types::sameType(first->getType()->getTypeName(), "ByteType")) 
                RaiseSemanticError(conditionTypeError_c, FATAL);
            type = types::byteType;
        }

        else if (operation == "&" || operation == "|"){
            first->sem(table);
            second->sem(table);
            if (!types::sameType(first->getType()->getTypeName(), "ByteType")) {
                if (!types::sameType(second->getType()->getTypeName(), "ByteType")) {
                    RaiseSemanticError(operandMismatchType_c, FATAL);
                }
            }
            type = types::byteType;
        }
        else {
            first->sem(table);
            second->sem(table);
            if (!types::sameType(first->getType()->getTypeName(), second->getType()->getTypeName()))
                RaiseSemanticError(operandMismatchType_c, FATAL);
            // std::cerr << "Error: Expressions don't have the same type" << std::endl;
            type = types::byteType;
        }
        return false;
    };

    bool While::sem(sym::Table &table) {
          cond->sem(table);
          if (!types::sameType(cond->getType()->getTypeName(), "ByteType")){
              RaiseSemanticError(conditionTypeError_c, FATAL);
              // std::cerr << "Error: Condition in While Statement is not of Boolean type" << std::endl;
          }
          return false;
    };
    
    bool If::sem(sym::Table &table) {
        bool stmt1Return = false;
        bool stmt2Return = false;
        cond->sem(table);

        if (!types::sameType(cond->getType()->getTypeName(), "ByteType")){
            RaiseSemanticError(conditionTypeError_c, FATAL);
        }

        stmt1Return = stmt1->sem(table);
        if (stmt2 != nullptr)
            stmt2Return = stmt2->sem(table);

        if (stmt2 != nullptr) 
            return (stmt1Return && stmt2Return);

        return stmt1Return;
    };

    bool Return::sem(sym::Table &table) {
        expr->sem(table);
        type  = expr->getType();
        
        if (!types::sameType(this->type->getTypeName(), table.getScopeType()->getTypeName())){
            std::cerr << "Error: Type of function does not match type of Return statement" << std::endl;
        }
        
        table.addReturn();
        return true;
        
    };

    bool Char::sem(sym::Table &table) {
        type = types::byteType; 
        return false;
    };

    bool BinOp::sem(sym::Table &table) {
        expr1->sem(table);
        if (expr2 != nullptr) {
            expr2->sem(table);
            if (!types::sameType(expr1->getType()->getTypeName(), expr2->getType()->getTypeName())){
                RaiseSemanticError(BinOpTypeMismatchError_c, FATAL);
            }
        }
        type = expr1->getType();
        return false;
    };


    bool String::sem(sym::Table &table) {
        type = types::BarrayType;
        return false;
    };

    /* TODO: need to add globals in ast nodes Call, Func, have them 
     * semantically analyzed and then add them in the ast nodes */ 
    
    bool LValue::sem(sym::Table &table) {
        sym::EntryPtr varentry = table.lookupEntry(id, sym::GLOBAL);
        if (varentry == nullptr) 
            std::cerr << "Error: Variable \"" << id << "\" not found!" << std::endl;

        if (expr != nullptr) {
            expr->sem(table);
            if (!types::sameType(expr->getType()->getTypeName(), "IntType")){
                RaiseSemanticError(arrayindexTypeError_c, FATAL);
            }
            type = varentry->getType()->getArrayType();
        }
        else
            this->type = varentry->getType();
        
        if (varentry->getLevel() < table.getCurrentScope()) {
            std::cout << "LValue::sem()-> found global variable with id -> " << this->getId() << " in scope -> " << table.getCurrentScope() << std::endl;
            table.addGlobalVariables(varentry, expr);
        }

        return false;
    };

    bool Call::sem(sym::Table &table) {
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

        for (auto global: funcentry->getGlobals()) {
            std::cout << "Call::sem(): there is a global variable in function with id -> " << funcentry->getId() << std::endl;
            this->addGlobalVariables(ast::ASTPtr(std::make_shared<ast::LValue>(global->getId(), global->getExpression()))); 
        }

        for (auto global: this->globals_list) {
            std::cout << "Call::sem() -> added global variable in globals with id -> " << global->getId() << std::endl; 
        }
        this->type = funcentry->getType();
        return false;
    };


    bool Assign::sem(sym::Table &table) {
        lvalue->sem(table); 
        expr->sem(table);
        if (!types::sameType(lvalue->getType()->getTypeName(), expr->getType()->getTypeName())) {
            RaiseSemanticError(expressionsDiffTypeError_c, FATAL);
        }            // std::cerr << "Error: type of expression does not match type of LValue" << std::endl;

        type = lvalue->getType();
        return false;
        
    };

    bool Print::sem(sym::Table &table) {
       return false; 
    };

}
