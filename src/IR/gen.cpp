#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <vector>

#include "../ast/ast.hpp"
#include "../symbol/symbol.hpp"
#include "../errors/errors.hpp"
#include "../types/types.hpp"
#include "gen.hpp"

extern char * filename;
extern bool opt;
extern bool llvm_out;

static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);
static std::unique_ptr<llvm::Module> module;
static llvm::legacy::FunctionPassManager *fpm;

static llvm::Type * i32  = llvm::Type::getInt32Ty(context);
static llvm::Type * i8   = llvm::Type::getInt8Ty(context);
static llvm::Type * proc = llvm::Type::getVoidTy(context);
static llvm::Type * i8ptr = llvm::Type::getInt8PtrTy(context);

static llvm::Constant * c32(int n) {
    return llvm::ConstantInt::get(i32, n);
}

static llvm::Constant * c8(unsigned char c) {
    return llvm::ConstantInt::get(i8, c);
}

IR::Variables named_variables;

bool hasReturnInstruction(const llvm::BasicBlock *BB) {
    for (const auto &Inst : *BB) {
        if (llvm::isa<llvm::ReturnInst>(&Inst))
            return true;
    }
    return false;
}

llvm::Type *getLLVMType(types::TypePtr type, sym::PassType pass) {
    llvm::Type *ret = nullptr;
    if (type->getTypeName() == "VoidType") ret = proc;
    if (type->getTypeName() == "IntType") ret = i32;
    if (type->getTypeName() == "ByteType") ret = i8;
    if (type->getTypeName() == "IArrayType") {
        int size = type->getSize();
        if (size == 0) {
            ret = i32;
        } else {
            ret = llvm::ArrayType::get(i32, size);
        }
    }

    if (type->getTypeName() == "BArrayType") {
        int size = type->getSize();
        if (size == 0) {
            ret = i8;
        } else {
            ret = i8ptr;
            return ret;
        }
    }

    if (pass == sym::PassType::reference) {
        ret = ret->getPointerTo();
    }
    return ret;
}

namespace IR {



    void setupOutput() {
        if (llvm_out) {
            if (llvm::verifyModule(*module, &llvm::outs())) {
                RaiseLLVMError(BadIRError_c);
            }
            module->print(llvm::outs(), nullptr);
        }
        FILE *file = fopen("out.ll", "w");

        if (file == nullptr) {
            RaiseFileError(badfileError_c);
        }

        llvm::raw_fd_ostream os(fileno(file), false); 

        module->print(os, nullptr);

        if (llvm::verifyModule(*module, &os)) {
            fclose(file); 
            RaiseLLVMError(BadIRError_c);
        }

        fclose(file);
    }

    void setupMain(ast::ASTPtr root) {
        llvm::FunctionType *mainType = llvm::FunctionType::get(proc, false);
        llvm::Function *mainFunc = llvm::Function::Create(mainType, llvm::Function::ExternalLinkage, "main", module.get());
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
        root->llvm();
        builder.SetInsertPoint(entry);
        if (root->getId() == "main") {
            builder.CreateCall(module->getFunction("main.1"));
        } else {
            builder.CreateCall(module->getFunction(root->getId()));
        }
        builder.CreateRetVoid();
    }
    
    void optimise() {
        if (opt) {
            fpm = new llvm::legacy::FunctionPassManager(module.get());
            fpm->add(llvm::createInstructionCombiningPass());
            fpm->add(llvm::createReassociatePass());
            fpm->add(llvm::createGVNPass());
            fpm->add(llvm::createCFGSimplificationPass());
            fpm->doInitialization();
            for (auto &func : *module) {
                fpm->run(func);
            }
            fpm->doFinalization();
        }
    }

    void libgen() {
        
        // writeInteger
        // =============
        llvm::FunctionType *writeIntegerType = llvm::FunctionType::get(proc, i32, false);
        llvm::Function *writeIntegerFunc =
            llvm::Function::Create(writeIntegerType, llvm::Function::ExternalLinkage, "writeInteger", module.get());

        // writeByte
        // =========
        llvm::FunctionType *writeByteType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeByteFunc =
            llvm::Function::Create(writeByteType, llvm::Function::ExternalLinkage, "writeByte", module.get());
        
        // writeChar
        // =========
        llvm::FunctionType *writeCharType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeCharFunc =
            llvm::Function::Create(writeCharType, llvm::Function::ExternalLinkage, "writeChar", module.get());

        // writeString
        // ===========
        llvm::FunctionType *writeStringType = llvm::FunctionType::get(proc, i8->getPointerTo(), false);
        llvm::Function *writeStringFunc =
            llvm::Function::Create(writeStringType, llvm::Function::ExternalLinkage, "writeString", module.get());
        // readInteger
        // ===========
        llvm::FunctionType *readIntegerType = llvm::FunctionType::get(i32, {}, false);
        llvm::Function *readIntegerFunc =
            llvm::Function::Create(readIntegerType, llvm::Function::ExternalLinkage, "readInteger", module.get());

        // readByte
        // ========
        llvm::FunctionType *readByteType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readByteFunc =
            llvm::Function::Create(readByteType, llvm::Function::ExternalLinkage, "readByte", module.get());

        // readChar
        // ========
        llvm::FunctionType *readCharType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readCharFunc =
            llvm::Function::Create(readCharType, llvm::Function::ExternalLinkage, "readChar", module.get());

        // readString
        // ==========
        llvm::FunctionType *readStringType = llvm::FunctionType::get(proc, {i32, i8->getPointerTo()}, false);
        llvm::Function *readStringFunc =
            llvm::Function::Create(readStringType, llvm::Function::ExternalLinkage, "readString", module.get());

        // extend
        // ======
        llvm::FunctionType *extendType = llvm::FunctionType::get(i32, i8, false);
        llvm::Function *extendFunc =
            llvm::Function::Create(extendType, llvm::Function::ExternalLinkage, "extend", module.get());

        // shrink
        // ======
        llvm::FunctionType *shrinkType = llvm::FunctionType::get(i8, i32, false);
        llvm::Function *shrinkFunc =
            llvm::Function::Create(shrinkType, llvm::Function::ExternalLinkage, "shrink", module.get());

        // strlen
        // ======
        llvm::FunctionType *strlenType = llvm::FunctionType::get(i32, i8->getPointerTo(), false);
        llvm::Function *strlenFunc =
            llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", module.get());

        // strcmp
        // ======
        llvm::FunctionType *strcmpType = llvm::FunctionType::get(i32, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcmpFunc =
            llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", module.get());

        // strcpy
        // ======
        llvm::FunctionType *strcpyType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcpyFunc =
            llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", module.get());

        // strcat
        // ======
        llvm::FunctionType *strcatType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcatFunc =
            llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", module.get());
    }

    void gen(ast::ASTPtr root) {
        module = std::make_unique<llvm::Module>(filename, context);
        libgen();
        setupMain(root);
        optimise();
        setupOutput();
    }
}


namespace ast {


    // TODO: Done 
    llvm::Value* AST::llvm() const {
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Param::llvm() const {
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Block::llvm() const {
        for (auto stmt : list ) {
            stmt->llvm();
        }
        return nullptr;
    }

    // TODO: This one causes scoping issues and seg faults 
    llvm::Value* Func::llvm() const {

        named_variables.openScope();

        std::vector<llvm::Type *> args;
        for (auto param : param_list) {
            args.push_back(getLLVMType(param->getType(), param->getPass()));
        }


        // auto global_vars = named_variables.getPreviousVariables();
        // if (global_vars.size() > 0) {
        //     for (auto var : global_vars) {
        //         args.push_back(var.second.type->getPointerTo());
        //     }
        // }

        llvm::FunctionType *funcType = llvm::FunctionType::get(getLLVMType(type, sym::PassType::value), args, false);
        llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, id, module.get());
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", func);
        builder.SetInsertPoint(entry);
        int count = 0;
        for (auto &arg : func->args()) {
            if (arg.getArgNo() < param_list.size()) {
                count++;
                arg.setName(param_list[arg.getArgNo()]->getId());
                llvm::Value *alloca = builder.CreateAlloca(getLLVMType(param_list[arg.getArgNo()]->getType(), param_list[arg.getArgNo()]->getPass()), nullptr, param_list[arg.getArgNo()]->getId());
                builder.CreateStore(&arg, alloca);
                IR::Value val = {alloca, arg.getType(), param_list[arg.getArgNo()]->getPass()};
                named_variables.addVariable(param_list[arg.getArgNo()]->getId(), val);
            }
            // else {
            //     bool flag = false;
            //     auto var = global_vars[arg.getArgNo() - param_list.size()];
            //     for (auto param : param_list) {
            //         if (var.first == param->getId()) { flag = true; break; }
            //     }
            //     if (flag) continue;
            //     count++;
            //     arg.setName(var.first);
            //     llvm::Value *alloca = builder.CreateAlloca(var.second.type, nullptr, var.first);
            //     builder.CreateStore(&arg, alloca);
            //     IR::Value val = {alloca, var.second.type, sym::PassType::reference};
            //     named_variables.addVariable(var.first, val);
            // }
        }


        for (auto decl : def_list) {
            builder.SetInsertPoint(entry);
            decl->llvm();
        }
        builder.SetInsertPoint(entry);
        compound->llvm();

        for (auto &BB : *func) {
            if (BB.getTerminator() == nullptr) {
                if (getLLVMType(type, sym::PassType::value) == proc) {
                    builder.CreateRetVoid();
                    break;
                } else if (getLLVMType(type, sym::PassType::value) == i32) {
                    builder.CreateRet(c32(0));
                    break;
                } else {
                    builder.CreateRet(c8(0));
                    break;
                }
            }
        }

        named_variables.closeScope();
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Const::llvm() const {
        return c32(num);
    }

    // TODO: Done
    llvm::Value* Char::llvm() const {
        return c8(var);
    }

    // TODO: Done
    llvm::Value* VarDef::llvm() const {
        // Variable
        if (indeces == INT_MAX) {
            llvm::Value* value = builder.CreateAlloca(getLLVMType(type, sym::PassType::value), nullptr, id);
            IR::Value val = {value, getLLVMType(type, sym::PassType::value), sym::PassType::value};
            named_variables.addVariable(id, val);
            // return value;
        // Array
        } else { 
            llvm::Value* value = builder.CreateAlloca(getLLVMType(type, sym::PassType::reference), nullptr, id);
            IR::Value val = {value, getLLVMType(type, sym::PassType::reference), sym::reference};
            named_variables.addVariable(id, val);
        }
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Cond::llvm() const {
        if (first == nullptr && second == nullptr) {
            if (operation == "true") {
                return c32(1);
            }
            return c32(0);
        }
        if (operation == "!") return builder.CreateNot(first->llvm(), "nottmp");
        if (operation == "<") return builder.CreateICmpSLT(first->llvm(), second->llvm(), "lttmp");
        if (operation == ">") return builder.CreateICmpSGT(first->llvm(), second->llvm(), "gttmp");
        if (operation == "==") return builder.CreateICmpEQ(first->llvm(), second->llvm(), "eqtmp");
        if (operation == "!=") return builder.CreateICmpNE(first->llvm(), second->llvm(), "netmp");
        if (operation == ">=") return builder.CreateICmpSGE(first->llvm(), second->llvm(), "getmp"); 
        if (operation == "<=") return builder.CreateICmpSLE(first->llvm(), second->llvm(), "letmp");
        if (operation == "&") return builder.CreateAnd(first->llvm(), second->llvm(), "andtmp");
        if (operation == "|") return builder.CreateOr(first->llvm(), second->llvm(), "ortmp");
        return c32(0);
    }

    // TODO: Probably not done, we should be certain about the previous block and the current block
    llvm::Value* While::llvm() const {
        llvm::Function *function = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(context, "cond", function);
        llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(context, "loop", function);
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(context, "endwhile", function);
        builder.CreateBr(CondBB);
        builder.SetInsertPoint(CondBB);
        llvm::Value *cond = this->cond->llvm();
        builder.CreateCondBr(cond, LoopBB, AfterBB);
        builder.SetInsertPoint(LoopBB);
        stmt->llvm();
        if (!hasReturnInstruction(LoopBB)) {
            builder.CreateBr(CondBB);
        }
        builder.SetInsertPoint(AfterBB);
        return nullptr;
    }

    // TODO: Probably not done, we should be certain about the previous block and the current block
    llvm::Value* If::llvm() const {
        llvm::Value *n = cond->llvm();
        llvm::BasicBlock *PrevBB = builder.GetInsertBlock();
        llvm::Function *function = PrevBB->getParent();
        llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(context, "then", function);
        llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(context, "else", function);
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(context, "endif", function);
        builder.CreateCondBr(n, ThenBB, ElseBB);
        builder.SetInsertPoint(ThenBB);
        llvm::Value *then = stmt1->llvm();
        if (!hasReturnInstruction(ThenBB)) {
            builder.CreateBr(AfterBB);
        }
        llvm::Value *else_;
        builder.SetInsertPoint(ElseBB);
        if (stmt2 != nullptr) {
            else_ = stmt2->llvm();
        }
        if (!hasReturnInstruction(ElseBB)) {
            builder.CreateBr(AfterBB);
        }
        builder.SetInsertPoint(AfterBB);
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Return::llvm() const {
        if (expr != nullptr) {
            builder.CreateRet(expr->llvm());
        } else {
            builder.CreateRetVoid();
        }
        return nullptr;
    }

    // TODO: Done
    llvm::Value* BinOp::llvm() const {
        llvm::Value *exp1 = expr1->llvm();
        llvm::Value *exp2 = expr2->llvm();
        if (expr2 != nullptr) {
            switch(op) {
                case '+': return builder.CreateAdd(exp1, exp2, "addtmp");
                case '-': return builder.CreateSub(exp1, exp2, "subtmp");
                case '*': return builder.CreateMul(exp1, exp2, "multmp");
                case '/': return builder.CreateSDiv(exp1, exp2, "divtmp");
                case '%': return builder.CreateSRem(exp1, exp2, "modtmp");
            }
        }
        switch(op) {
            case '+': return builder.CreateAdd(exp1, c32(0), "addtmp");
            case '!': return builder.CreateNot(exp1, "nottmp");
            case '-': return builder.CreateNeg(exp1, "negtmp");
        }
        return c32(0);
    }

    // TODO: Done
    llvm::Value* String::llvm() const {
        return builder.CreateGlobalStringPtr(str);
    }

    // TODO: Done
    llvm::Value* LValue::llvm() const {
        // Variable
        if (expr == nullptr) {
            IR::Value val = named_variables.getVariable(id);
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value *alloca = builder.CreateLoad(val.value);
                return builder.CreateLoad(alloca);
            // Pass by value
            } else {
                return builder.CreateLoad(val.value);
            }
        }
        // Array
        else {
            llvm::Value * array_index = expr->llvm();
            IR::Value val = named_variables.getVariable(id);
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value *pointer_to = builder.CreateLoad(val.value);
                llvm::Value *alloca = builder.CreateGEP(pointer_to, array_index);
                return builder.CreateLoad(alloca);
            // Pass by value
            } else {
                llvm::Value *alloca = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                return builder.CreateLoad(alloca);
            }
        }
        return nullptr;
    }

    // TODO: This could be a bit of a mess, no sure yet
    llvm::Value* Call::llvm() const {
        llvm::Function *func = module->getFunction(id);
        std::vector<llvm::Value*> llvm_args;
        int i = 0;
        for (auto &arg : func->args()) {
            if (arg.getArgNo() < block.size()) {
                if (arg.getType()->isPointerTy()) {
                    auto variable = std::dynamic_pointer_cast<ast::LValue>(block[i]);
                    // It's a variable of sorts 
                    if (variable != nullptr) {
                        // It's a variable
                        if (variable->getExpr() == nullptr) {
                            IR::Value val = named_variables.getVariable(variable->getId());
                            // Pass by reference
                            if (val.valueType == sym::reference) {
                                llvm::Value *alloca = builder.CreateLoad(val.value);
                                llvm_args.push_back(alloca);
                            // Pass by value
                            } else {
                                llvm_args.push_back(val.value);
                            }
                        // It's an array
                        } else {
                            auto array_index = variable->getExpr()->llvm();
                            IR::Value val = named_variables.getVariable(variable->getId());
                            // Pass by reference
                            if (val.valueType == sym::reference) {
                                llvm::Value *alloca = builder.CreateLoad(val.value);
                                llvm::Value *v = builder.CreateGEP(alloca, array_index);
                                llvm_args.push_back(v);
                            // Pass by value
                            } else {
                                llvm::Value *v = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                                llvm_args.push_back(v);
                            }
                        }
                    }
                    // It's a string 
                    auto string = std::dynamic_pointer_cast<ast::String>(block[i]);
                    if (string != nullptr) {
                        llvm_args.push_back(string->llvm());
                    }

                    i++;

                } else {
                    llvm_args.push_back(block[i]->llvm());
                    i++;
                }
            }
            // else {
            //     // global variable
            //     auto gl = named_variables.getPreviousVariables();
            //     if (gl.size() == 0) {
            //         for (int j = gl.size() - 1; j >= 0; j--) {
            //             if (gl[j].first == block[i]->getId()) {
            //                 llvm_args.push_back(gl[j].second.value);
            //                 break;
            //             }
            //         }
            //     }
            // }
        }
        return builder.CreateCall(func, llvm_args);

    }

    // TODO: Done
    llvm::Value* Assign::llvm() const {
        auto *exp = expr->llvm();
        auto lval = std::static_pointer_cast<ast::LValue>(lvalue);
        // Pass by value Variable
        IR::Value val = named_variables.getVariable(lval->getId());
        if (lval->getExpr() == nullptr) {
            auto possible_string = std::dynamic_pointer_cast<ast::String>(expr);
            if (possible_string != nullptr) {
                return builder.CreateStore(exp, val.value);
            }
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value * alloca = builder.CreateLoad(val.value);
                return builder.CreateStore(exp,alloca);
            // Pass by value
            } else {
                return builder.CreateStore(exp,val.value);
            }
        }
        // Pass by value Array
        else {
            auto *array_index = lval->getExpr()->llvm();
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value * v = builder.CreateLoad(val.value);
                v = builder.CreateGEP(v, array_index);
                return builder.CreateStore(exp, v);
            // Pass by value
            } else {
                llvm::Value * v = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                return builder.CreateStore(exp, v);
            }
        }
        return nullptr;
    }

    // IGNORE
    llvm::Value* Print::llvm() const {
        return nullptr;
    }

}

