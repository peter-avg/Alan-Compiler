#ifndef __AST_HPP__
#define __AST_HPP__

// #include <cmath>
#include <iostream>
// #include <iterator>
// #include <string.h>
#include <iterator>
#include <string>
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
    };


    inline std::ostream & operator << (std::ostream &out, const AST &ast){
        ast.printOn(out);
        return out;
    }

    class Type : public AST {
        public:
            Type (std::string *type = nullptr) : type(type) {}
            virtual void printOn(std::ostream &out) const override {
                if (type == nullptr)
                    out << "Type()";
                else
                    out << "Type(" << *type << ")";
            }

        private:
            std::string *type;
    };


    class Stmt: public AST {
        public:
    };

    class Expr: public AST {
        public:
    };

    class Param : public AST {
        public:
            Param(std::string id, std::string pass, types::TypePtr t) : id(id), pass(pass), type(t) {}
            virtual void printOn(std::ostream &out) const override {
                out << "Param(" << id << ", " << pass << ", " << *type << ")" ;
            }

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
            virtual void printOn(std::ostream &out) const override {
                out << "Block(";
                for (ASTPtr s : list){
                    out << *s << ", ";
                }
                out << ")";
            }
        private:
            ASTList list;
    };

    class Func : public AST {
        public:
            Func(std::string id,ASTList p,
                    types::TypePtr ret, ASTList local_def,
                    ASTPtr compound) : id(id), param_list(p),
            retType(ret), def_list(local_def), compound(compound)  {}
            virtual void printOn(std::ostream &out) const override {
                out << "Func(" << id << ",";

                for (auto p : param_list) {
                    out << *p << ", ";
                };

                out << *retType << ",";

                for (auto p : def_list) {
                    out << *p << ", ";
                };

                out << *compound << ")";

            }

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
            virtual void printOn(std::ostream &out) const override {
                out << "Const(" << num << ")";
            }
        private:
            int num;
    };

    class Var: public AST {
        public:
            Var(std::string id, types::TypePtr t, int c = 0) : id(id), type(t), value(c) {}
            virtual void printOn(std::ostream &out) const override {
                if (value == 0) { 
                    out << "Var(" << id << ", " << *type << ")";
                } else {
                    out << "Var(" << id << ", " << *type << ", " << value << ")";
                }
            }

        private: 
            std::string id;
            types::TypePtr type;
            int value;
    };

    class Cond: public AST {
        public: 

            Cond(std::string op, ASTPtr first = nullptr, ASTPtr second = nullptr): operation(op), first(first), second(second)  {}
            virtual void printOn(std::ostream &out) const override {
                if( second == nullptr) {
                    out << "Cond (" << operation << ")";
                }
                else {
                    if (first != nullptr) {
                        out << "Cond (" << *first << operation << *second << ")";
                    }
                    else {
                        out << "Cond (" << operation << *second <<")";
                    }
                }
            }

        private:
            std::string operation;
            ASTPtr first;
            ASTPtr second;
    };

    class While: public Stmt {
        public: 
            While(ASTPtr c, ASTPtr s): cond(c), stmt(s) {}
            virtual void printOn(std::ostream &out) const override {
                out << "While(" << *cond << ", " << *stmt << ")";
            }
        private: 
            ASTPtr cond;
            ASTPtr stmt;
    };



    class If: public Stmt {
        public:
            If(ASTPtr c, ASTPtr s1, ASTPtr s2 = 0): cond(c), stmt1(s1), stmt2(s2) {}
            virtual void printOn(std::ostream &out) const override {
                out << "If(" << *cond << ", " << *stmt1;
                if (stmt2 != nullptr ) out << ", " << *stmt2;
                out << ")"; 
            }

        private:
            ASTPtr cond;
            ASTPtr stmt1;
            ASTPtr stmt2;
    };

    class Return: public Stmt {
        public: 
            Return(ASTPtr e): expr(e) {}
            virtual void printOn(std::ostream &out) const override {
                out << "Return(" << *expr  << ")"; 
            }
        private:
            ASTPtr expr;
    };


    class Char: public Expr {
        public:
            Char(char v): var(v) {}
            virtual void printOn(std::ostream &out) const override {
                out << "Char(" << var << ")";
            }
        private:
            char var;
    };


    class BinOp: public Expr {
        public: 
            BinOp(char o, ASTPtr e1 = nullptr, ASTPtr e2 = nullptr): expr1(e1), expr2(e2), op(o) {}
            virtual void printOn(std::ostream &out) const override {
                out << op << "(" << *expr1 << ", " << *expr2 << ")";
            }
        private:
            ASTPtr expr1;
            ASTPtr expr2;
            char op;
    };


    class String : public AST {
        public:
            String(std::string s) : str(s) {}
            virtual void printOn(std::ostream &out) const override {
                out << "String(" << str << ")";
            }

        private:
            std::string str;
    };


    class LValue : public AST {
        public:
            LValue(std::string id, ASTPtr e = nullptr) : id(id), expr(e) {}
            virtual void printOn(std::ostream &out) const override {
                if (expr == nullptr) {
                    out << "LValue(" << id << ")";
                } else {
                    out << "LValue(" << id << ", " << *expr << ")";
                }
            }

        private:
            std::string id;
            ASTPtr expr;
    };


    class Call : public AST {
        public:
            Call(std::string id, ASTList block) : id(id), block(block) {}
            virtual void printOn(std::ostream &out) const override {
                out << "Call(" << id << ", ";

                for (auto p : block) {
                    out << *p << ", ";
                };
            }

        private:
            std::string id;
            ASTList block;

    };


    class Assign : public AST {
        public:
            Assign(ASTPtr l, ASTPtr e) : lvalue(l), expr(e) {}
            virtual void printOn(std::ostream &out) const override {
                out << "Assign(" << *lvalue << ", " << *expr << ")";
            }

        private: 
            ASTPtr lvalue;
            ASTPtr expr;
    };

    class Int : public AST {
        public:
            Int() {}
            virtual void printOn(std::ostream &out) const override {
                out << "Int()";
            }
    };


    class Byte : public AST {
        public:
            Byte() {}
            virtual void printOn(std::ostream &out) const override {
                out << "Byte()";
            }
    };
}

#endif
