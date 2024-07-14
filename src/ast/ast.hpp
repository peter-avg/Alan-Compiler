#ifndef __AST_HPP__
#define __AST_HPP__

#include <llvm/IR/Value.h>

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
            virtual bool sem(sym::Table &table) { return false; };
            virtual llvm::Value* llvm() const;
            virtual int run() const { return 0; };
            virtual int eval() const { return 0; }
            types::TypePtr type;
            virtual types::TypePtr getType() const {
                return type; 
            }
            virtual std::string getId() const { return ""; };
            virtual sym::PassType getPass() const { return sym::value; }
            virtual void addGlobalVariables(ASTPtr global) {};
            virtual ASTPtr getExpr() const { return nullptr; };

            sym::PassType pass;
            int line;
    };

    inline std::ostream & operator << (std::ostream &out, const AST &ast){
        ast.printOn(out);
        return out;
    }
    
    class Stmt: public AST {
        public:
            virtual int run() const override { return 0; }
            virtual llvm::Value* llvm() const override { return nullptr; }
            virtual types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type;
    };

    class Expr: public AST {
        public:
            virtual int eval() const override { return 0; }
            virtual llvm::Value* llvm() const override { return nullptr; }
            virtual types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type;
    };

    class Param : public Expr {
        public:
            Param(std::string id, std::string pass_string, types::TypePtr t) : id(id), type(t){
                if (pass_string == "reference") pass = sym::reference;
                else if (pass_string == "value") pass = sym::value;

                if (type->isArray()) {
                    if (t->getArrayType()->getTypeName() == "IntType") {
                        this->type = types::IarrayType;
                    } else  if (t->getArrayType()->getTypeName() == "ByteType"){
                        this->type = types::BarrayType;
                    }
                }
            }
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override { return 0; }
            bool sem(sym::Table &table) override ;
            types::TypePtr getType() const override {
                return type; 
            }
            std::string getId() const override { return id; }

            sym::PassType getPass() const override {
                return pass;
            }

        private:
            types::TypePtr type;
            types::TypePtr new_type;
            std::string id;
            sym::PassType pass;
    };

    class Block: public Stmt {
        public:
            Block() {}
            Block(ASTList ast) : list(ast) {};
            void append(ASTPtr s) { list.push_back(s); }
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int run() const override;
            bool sem(sym::Table &table) override;

        private:
            ASTList list;
    };

    class Func : public Stmt {
        public:
            Func(std::string id,ASTList p,
                    types::TypePtr ret, ASTList local_def,
                    ASTPtr compound, bool main = false) : id(id), param_list(p),
            type(ret), def_list(local_def), compound(compound), main(main)  {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int run() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }

            void addGlobalVariables(ASTPtr global) override {
                globals_list.push_back(global);
            }

            std::string getId() const override { return id; }

            types::TypePtr type;
        protected:
            std::string id;
            ASTList param_list;
            ASTList def_list;
            ASTPtr compound;
            ASTList globals_list;
            bool main;
    };

    class Const: public Expr {
        public:
            Const(int n): num(n){}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                 return type; 
            }
            types::TypePtr type = types::intType;

        private:
            int num;
    };

    class VarDef: public Stmt {
        public:
            VarDef(std::string id, types::TypePtr t, int c = INT_MAX) : id(id), type(t), indeces(c) {
                if (c != INT_MAX) {
                    if (t->getTypeName() == "IntType") {
                        this->type = types::IarrayType;
                    } else if (t->getTypeName() == "ByteType"){
                        this->type = types::BarrayType;
                    }
                }

            }
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int run() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }
        private: 
            types::TypePtr type;
            types::TypePtr t;
            std::string id;
            int indeces;
    };

    class Cond: public Expr {
        public: 
            Cond(std::string op, ASTPtr first = nullptr, ASTPtr second = nullptr): operation(op), first(first), second(second)  {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type;

        private:
            std::string operation;
            ASTPtr first;
            ASTPtr second;
    };

    class While: public Stmt {
        public: 
            While(ASTPtr c, ASTPtr s): cond(c), stmt(s) {}
            llvm::Value* llvm() const override; 
            void printOn(std::ostream &out) const override;
            int run() const override;
            bool sem(sym::Table &table) override;

        private: 
            ASTPtr cond;
            ASTPtr stmt;
    };

    class If: public Stmt {
        public:
            If(ASTPtr c, ASTPtr s1, ASTPtr s2 = nullptr): cond(c), stmt1(s1), stmt2(s2) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int run() const override;
            bool sem(sym::Table &table) override;
            ASTPtr stmt1;
            ASTPtr stmt2;

        private:
            ASTPtr cond;
    };

    class Return: public Stmt {
        public: 
            Return(ASTPtr e = nullptr): expr(e) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int run() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr type;
            types::TypePtr getType() const override {
                return type; 
            }


            void setType (types::TypePtr t) {
                type = t;
            }

        private:
            ASTPtr expr;
    };


    class Char: public Expr {
        public:
            Char(unsigned char v): var(v) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override { return 0; }
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type = types::byteType;

        private:
            unsigned char var;
    };


    class BinOp: public Expr {
        public: 
            BinOp(char o, ASTPtr e1 = nullptr, ASTPtr e2 = nullptr): expr1(e1), expr2(e2), op(o) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override;
            bool sem(sym::Table &table) override;

        private:
            ASTPtr expr1;
            ASTPtr expr2;
            char op;
    };


    class String : public Expr {
        public:
            String(std::string s) : str(s) {}
            void printOn(std::ostream &out) const override;
            bool sem(sym::Table &table) override;
            int eval() const override;
            llvm::Value* llvm() const override; 
        private:
            std::string str;
    };


    class LValue : public Expr {
        public:
            LValue(std::string id, ASTPtr e = nullptr) : id(id), expr(e) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override; 
            int eval() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type;
            std::string getId() const override { return id; }
            ASTPtr getExpr() const override { return expr; }

        private:
            std::string id;
            ASTPtr expr;
    };


    class Call : public Expr{
        public:
            Call(std::string id, ASTList block) : id(id), block(block) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override;
            int eval() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr getType() const override {
                return type; 
            }
            types::TypePtr type;
            void addGlobalVariables(ASTPtr global) override {
                globals_list.push_back(global);
            }
        private:
            std::string id;
            ASTList globals_list;
            ASTList block;
    };

    class Assign : public Stmt {
        public:
            Assign(ASTPtr l, ASTPtr e) : lvalue(l), expr(e) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override;
            int run() const override;
            bool sem(sym::Table &table) override;
            types::TypePtr type;

        private: 
            ASTPtr lvalue;
            ASTPtr expr;
    };

    class Print : public Stmt {
        public:
            Print(ASTPtr e) : expr(e) {}
            void printOn(std::ostream &out) const override;
            llvm::Value* llvm() const override;
            int run() const override;
            bool sem(sym::Table &table) override;
        private:
            ASTPtr expr;
    };

}


#endif
