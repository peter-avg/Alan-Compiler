#ifndef __AST_HPP__
#define __AST_HPP__

// #include <cmath>
#include <iostream>
// #include <iterator>
// #include <string.h>
#include <string>
#include "../symbol/symbol.hpp"
#include "../types/types.hpp"
#include <vector>
#include <memory>

namespace ast {

    class AST;

    typedef std::shared_ptr<AST> ASTPtr;
    typedef std::vector<ASTPtr> ASTList;

    class AST {
        public:
            virtual void printOn(std::ostream &out) const = 0;
            virtual void sem(sym::Table table) {};

        private:
            types::TypePtr type;
            int line;
    };

    inline std::ostream & operator << (std::ostream &out, const AST &ast){
        ast.printOn(out);
        return out;
    }

    class Stmt: public AST {
        public:
    };

    class Expr: public AST {
        public:
    };

    class Param : public AST {
        public:
            Param(std::string id, std::string pass, types::TypePtr t) : id(id), pass(pass), type(t) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override ;

        private:
            std::string id;
            std::string pass;
            types::TypePtr type;
    };

    class Block: public AST {
        public:
            Block() {}
            Block(ASTList ast) : list(ast) {}
            void append(ASTPtr s) { list.push_back(s); }
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            ASTList list;
    };

    class Func : public AST {
        public:
            Func(std::string id,ASTList p,
                    types::TypePtr ret, ASTList local_def,
                    ASTPtr compound) : id(id), param_list(p),
            retType(ret), def_list(local_def), compound(compound)  {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            std::string id;
            ASTList param_list;
            types::TypePtr retType;
            ASTList def_list;
            ASTPtr compound;
    };

    class Const: public Expr {
        public:
            Const(int n): num(n) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            int num;
    };

    class Var: public AST {
        public:
            Var(std::string id, types::TypePtr t, int c = 0) : id(id), type(t), value(c) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private: 
            std::string id;
            types::TypePtr type;
            int value;
    };

    class Cond: public AST {
        public: 
            Cond(std::string op, ASTPtr first = nullptr, ASTPtr second = nullptr): operation(op), first(first), second(second)  {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            std::string operation;
            ASTPtr first;
            ASTPtr second;
    };

    class While: public Stmt {
        public: 
            While(ASTPtr c, ASTPtr s): cond(c), stmt(s) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private: 
            ASTPtr cond;
            ASTPtr stmt;
    };

    class If: public Stmt {
        public:
            If(ASTPtr c, ASTPtr s1, ASTPtr s2 = 0): cond(c), stmt1(s1), stmt2(s2) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            ASTPtr cond;
            ASTPtr stmt1;
            ASTPtr stmt2;
    };

    class Return: public Stmt {
        public: 
            Return(ASTPtr e): expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            ASTPtr expr;
    };


    class Char: public Expr {
        public:
            Char(unsigned char v): var(v) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            unsigned char var;
    };


    class BinOp: public Expr {
        public: 
            BinOp(char o, ASTPtr e1 = nullptr, ASTPtr e2 = nullptr): expr1(e1), expr2(e2), op(o) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            ASTPtr expr1;
            ASTPtr expr2;
            char op;
    };


    class String : public AST {
        public:
            String(std::string s) : str(s) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            std::string str;
    };


    class LValue : public AST {
        public:
            LValue(std::string id, ASTPtr e = nullptr) : id(id), expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            std::string id;
            ASTPtr expr;
    };


    class Call : public AST {
        public:
            Call(std::string id, ASTList block) : id(id), block(block) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private:
            std::string id;
            ASTList block;
    };

    class Assign : public AST {
        public:
            Assign(ASTPtr l, ASTPtr e) : lvalue(l), expr(e) {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;

        private: 
            ASTPtr lvalue;
            ASTPtr expr;
    };

    class Int : public AST {
        public:
            Int() {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;
    };

    class Byte : public AST {
        public:
            Byte() {}
            virtual void printOn(std::ostream &out) const override;
            // virtual void sem(sym::Table table) override;
    };
}

#endif
