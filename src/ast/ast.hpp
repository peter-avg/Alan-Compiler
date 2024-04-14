#ifndef __AST_HPP__
#define __AST_HPP__

#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/Value.h"

#include <iostream>
#include <string>
#include "../symbol/symbol.hpp"
#include "../types/types.hpp"
#include <vector>
#include <memory>
#include <limits.h>
namespace ast {

    class AST;

    typedef std::shared_ptr<AST> ASTPtr;
    typedef std::vector<ASTPtr> ASTList;

    class AST {
        public:
            virtual void printOn(std::ostream &out) const = 0;
            virtual void sem(sym::Table &table) {};
            virtual llvm::Value* llvm() const;
            //virtual int run() const { return 0; };
            //virtual int eval() const { return 0; }
            types::TypePtr type;
            virtual types::TypePtr getType() {
                return type; 
            }
            sym::PassType pass;

            int line;
    };

    inline std::ostream & operator << (std::ostream &out, const AST &ast){
        ast.printOn(out);
        return out;
    }
    
    class Stmt: public AST {
        public:
            virtual llvm::Value* llvm() const override { return nullptr; }
    };

    class Expr: public AST {
        public:
            virtual llvm::Value* llvm() const override { return nullptr; }
    };

    class Param : public Expr {
        public:
            Param(std::string id, std::string pass_string, types::TypePtr t) : id(id), type(t) {
                if (pass_string == "reference") pass = sym::reference;
                else if (pass_string == "value") pass = sym::value;
            }
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override { return 0; }
            std::string getId() const { return id; }
            virtual void sem(sym::Table &table) override ;
            virtual types::TypePtr getType() override {
                return type; 
            }

        private:
            types::TypePtr type;
            std::string id;
            sym::PassType pass;
    };

    class Block: public Stmt {
        public:
            Block() {}
            Block(ASTList ast) : list(ast) {};
            void append(ASTPtr s) { list.push_back(s); }
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;

        private:
            ASTList list;
    };

    class Func : public Stmt {
        public:
            Func(std::string id,ASTList p,
                    types::TypePtr ret, ASTList local_def,
                    ASTPtr compound) : id(id), param_list(p),
            type(ret), def_list(local_def), compound(compound)  {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;
            virtual types::TypePtr getType() override {
                return type; 
            }

            private:
            types::TypePtr type;
            std::string id;
            ASTList param_list;
            ASTList def_list;
            ASTPtr compound;
            bool main = false;
    };

    class Const: public Expr {
        public:
            Const(int n): num(n){}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override;
            virtual void sem(sym::Table &table) override;

        private:
            int num;
    };

    class VarDef: public Stmt {
        public:
            VarDef(std::string id, types::TypePtr t, int c = INT_MAX) : id(id), type(t), value(c) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;
            virtual types::TypePtr getType() override {
                return type; 
            }
        private: 
            types::TypePtr type;
            std::string id;
            int value;
    };

    class Cond: public Expr {
        public: 
            Cond(std::string op, ASTPtr first = nullptr, ASTPtr second = nullptr): operation(op), first(first), second(second)  {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override;
            virtual void sem(sym::Table &table) override;
            //types::TypePtr type;

        private:
            std::string operation;
            ASTPtr first;
            ASTPtr second;
    };

    class While: public Stmt {
        public: 
            While(ASTPtr c, ASTPtr s): cond(c), stmt(s) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;

        private: 
            ASTPtr cond;
            ASTPtr stmt;
    };

    class If: public Stmt {
        public:
            If(ASTPtr c, ASTPtr s1, ASTPtr s2 = 0): cond(c), stmt1(s1), stmt2(s2) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;

        private:
            ASTPtr cond;
            ASTPtr stmt1;
            ASTPtr stmt2;
    };

    class Return: public Stmt {
        public: 
            Return(ASTPtr e): expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;
            //types::TypePtr type;

        private:
            ASTPtr expr;
    };


    class Char: public Expr {
        public:
            Char(unsigned char v): var(v) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override { return 0; }
            virtual void sem(sym::Table &table) override;
            //types::TypePtr type = types::byteType;

        private:
            unsigned char var;
    };


    class BinOp: public Expr {
        public: 
            BinOp(char o, ASTPtr e1 = nullptr, ASTPtr e2 = nullptr): expr1(e1), expr2(e2), op(o) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override;
            virtual void sem(sym::Table &table) override;

        private:
            ASTPtr expr1;
            ASTPtr expr2;
            char op;
    };


    class String : public AST {
        public:
            String(std::string s) : str(s) {}
            virtual void printOn(std::ostream &out) const override;
            virtual void sem(sym::Table &table) override;
            virtual llvm::Value* llvm() const override; 
        private:
            std::string str;
    };


    class LValue : public Expr {
        public:
            LValue(std::string id, ASTPtr e = nullptr) : id(id), expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override; 
            //virtual int eval() const override;
            //types::TypePtr type;
            std::string getId() const { return id; }
            virtual void sem(sym::Table &table) override;

        private:
            std::string id;
            ASTPtr expr;
    };


    class Call : public Expr{
        public:
            Call(std::string id, ASTList block) : id(id), block(block) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override;
            //virtual int eval() const override;
            virtual void sem(sym::Table &table) override;
            //types::TypePtr type;
        private:
            std::string id;
            ASTList block;
    };

    class Assign : public Stmt {
        public:
            Assign(ASTPtr l, ASTPtr e) : lvalue(l), expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override;
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;
            //types::TypePtr type;

        private: 
            ASTPtr lvalue;
            ASTPtr expr;
    };

    class Print : public Stmt {
        public:
            Print(ASTPtr e) : expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            virtual llvm::Value* llvm() const override;
            //virtual int run() const override;
            virtual void sem(sym::Table &table) override;

        private:
            ASTPtr expr;
    };

    void llvm(ASTPtr ast);
    void libvm();

}


#endif
