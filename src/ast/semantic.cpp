#include "../symbol/symbol.hpp"
#include "ast.hpp"
#include "../errors/errors.hpp"
#include "../library/library.hpp"
#include <csignal>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>

namespace ast {
    /* TODO: Probably have to do something with the uninitialized Variables*/
    /* TODO: Also turns out expressions aren't really needed */

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/

    bool main_func = false;
    

    bool Param::sem(sym::Table &table) {
        sym::EntryPtr exists = table.lookupEntry(id, sym::LOCAL);
        if (exists != nullptr) {
            RaiseSemanticError(parameterExistsError_c, FATAL);
            return false;
        }
        sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, table.getCurrentScope(), type, pass, true);
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
        /* Check if the function already exists */
        sym::EntryPtr funcentry =  std::make_shared<sym::FuncEntry>(id, table.getCurrentScope(), type);
        funcentry = table.lookupEntry(id, sym::GLOBAL);
        if (funcentry != nullptr) {
            RaiseSemanticError(functionExistsError_c, FATAL);
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

        if (funcentry->getType()->getTypeName() == "VoidType") {
            if (hasReturns) {
                RaiseSemanticError(voidFunctionWrongReturnError_c, FATAL);
            }
        }

        else if (funcentry->getType()->getTypeName() == "IntType" || funcentry->getType()->getTypeName() == "ByteType"){
            if (!hasReturns) {
                RaiseSemanticError(functionRequiresMoreParamsError_c, FATAL);
            }
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
            type = types::byteType;
        }
        return false;
    };

    bool While::sem(sym::Table &table) {
        bool hasReturn = false;  
        cond->sem(table);
        if (!types::sameType(cond->getType()->getTypeName(), "ByteType")){
              RaiseSemanticError(conditionTypeError_c, FATAL);
        }

        hasReturn = stmt->sem(table);
        
        return hasReturn;
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
        if (expr != nullptr) {
            expr->sem(table);
            type  = expr->getType();
        
            if (!types::sameType(this->type->getTypeName(), table.getScopeType()->getTypeName())){
                RaiseSemanticError(returnTypeMismatchError_c, FATAL);
            }
            return true;
        }
        if (!types::sameType(table.getScopeType()->getTypeName(), "VoidType")) {
            RaiseSemanticError(returnTypeMismatchError_c, FATAL);
        }
        type = types::voidType;
        table.addReturn();
        return false;
        
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

    
    bool LValue::sem(sym::Table &table) {
        sym::EntryPtr varentry = table.lookupEntry(id, sym::GLOBAL);
        if (varentry == nullptr){ 
            RaiseSemanticError(variableNotFoundError_c, FATAL);
        }
        if (!varentry->isInitialized()) {
            std::cerr << "Warning: Variable \"" << id << "\" may be used uninitialized!" << std::endl;
        }
        if (expr != nullptr) {
            if (!types::sameType(varentry->getType()->getTypeName(), "IArrayType")){
                if(!types::sameType(varentry->getType()->getTypeName(), "BArrayType")) {
                    RaiseSemanticError(nonArrayWrongIndexing_c, FATAL);
                }
            }  
            expr->sem(table);
            if (!types::sameType(expr->getType()->getTypeName(), "IntType")){
                RaiseSemanticError(arrayindexTypeError_c, FATAL);
            }
            type = varentry->getType()->getArrayType();
        }
        else
            this->type = varentry->getType();
        
        if (varentry->getLevel() < table.getCurrentScope()) {
            table.addGlobalVariables(varentry);
        }

        return false;
    };

 bool Call::sem(sym::Table &table) {
        int scope = table.getCurrentScope();
        sym::EntryPtr funcentry = std::make_shared<sym::FuncEntry>(id, table.getCurrentScope(), nullptr);
        funcentry = table.lookupEntry(id, sym::GLOBAL);
        if (funcentry == nullptr) {
           RaiseLLVMError(FunctionNotFoundError_c);
        }
        if (funcentry->getEType() != sym::FUNC) {
           RaiseSemanticError(idnotfunctionError_c, FATAL);
        }
        if (block.size() < funcentry->parameters.size()) {
            RaiseSemanticError(notenoughparamsError_c, FATAL);
        }
        else if (block.size() > funcentry->parameters.size()) {
            RaiseSemanticError(toomanyparamsError_c, FATAL);
        }

        for(auto &item: block) {
           item->sem(table);
        }
        int i = 0;
        for (auto &item: block) {
            if (!types::sameType(item->getType()->getTypeName(), funcentry->parameters[i++]->getType()->getTypeName())){
                RaiseSemanticError(argumentTypeMismatchError_c, FATAL);
            }
        }
        
        for (auto global: funcentry->getGlobals()) {
            ast::ASTPtr globalVar = std::make_shared<ast::LValue>(global->getId());
            this->addGlobalVariables(globalVar);

        }

        this->type = funcentry->getType();
        return false;
    };


    bool Assign::sem(sym::Table &table) {
        expr->sem(table);
        sym::EntryPtr lvalEntry = table.lookupEntry(lvalue->getId(), sym::GLOBAL);
        lvalEntry->initializeVariable();
        lvalue->sem(table);
        if (!types::sameType(lvalue->getType()->getTypeName(), expr->getType()->getTypeName())) {
            RaiseSemanticError(expressionsDiffTypeError_c, FATAL);
        }           
         
        
        type = lvalue->getType();
        return false;
        
    };

    bool Print::sem(sym::Table &table) {
       return false; 
    };

}
