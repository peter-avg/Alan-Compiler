#ifndef __AST_HPP__
#define __AST_HPP__

#include <cmath>
#include <iostream>
#include <iterator>
#include <string.h>
#include <string>
#include <vector>

class AST {
    public:
        virtual void printOn(std::ostream &out) const = 0;
};

inline std::ostream & operator << (std::ostream &out, const AST &ast){
    ast.printOn(out);
    return out;
}

class Func: public AST {
    public:
        Func(T)
};
class Stmt: public AST {
    public:
        virtual void run() const = 0;
};

class Expr: public AST {
    public:
        virtual int eval() const = 0;
};

class Cond: public AST {
    public: 
        Cond(std::string *val): value(val), left(nullptr), right(nullptr)  {}
        Cond(Expr *e1, std::string *op, Expr *e2): value(op), left(e1), right(e2)  {}  
        Cond(std::string *op, Expr *e): value(op), left(nullptr), right(e) {}  
        virtual void printOn(std::ostream &out) const override {
            if( right == nullptr) {
                out << "Cond (" << *value << ")";
            }
            else {
                if (left != nullptr) {
                    out << "Cond (" << *left << *value << *right << ")";
                }
                else {
                    out << "Cond (" << *value << *right <<")";
                }
            }
        }
    private:
        std::string *value;
        Expr *left;
        Expr *right;
};

class While: public Stmt {
    public: 
        While(Cond *c, Stmt *s): cond(c), stmt(s) {}
        virtual void printOn(std::ostream &out) const override {
            out << "While(" << *cond << ", " << *stmt << ")";
        }
    private: 
        Cond *cond;
        Stmt *stmt;
};



class If: public Stmt {
    public:
        If(Cond *c, Stmt *s1, Stmt *s2 = 0): cond(c), stmt1(s1), stmt2(s2) {}
        virtual void printOn(std::ostream &out) const override {
        out << "If(" << *cond << ", " << *stmt1;
        if (stmt2 != nullptr ) out << ", " << *stmt2;
        out << ")"; 
        }
    private:
        Cond *cond;
        Stmt *stmt1;
        Stmt *stmt2;
};

class Return: public Stmt {
    public: 
        Return(Expr *e): expr(e) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Return(" << *expr  << ")"; 
        }
    private:
        Expr *expr;
};

class Block: public Stmt {
    public:
        Block() : stmt_list() {}
        void append(Stmt *s) { stmt_list.push_back(s); }
        virtual void printOn(std::ostream &out) const override {
            out << "Block(";
            bool first = true;
            for (Stmt *s : stmt_list){
                if (!first)
                    out << " ,";
                first = false;
                out << *s; 
            }
            out << ")";
        }
    private:
        std::vector<Stmt *> stmt_list;
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

class Const: public Expr {
    public:
        Const(int n): num(n) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Const(" << num << ")";
        }
    private:
        int num;
};

class BinOp: public Expr {
    public: 
        BinOp(Expr *e1=0, char o=0, Expr *e2=0): expr1(e1), op(o), expr2(e2) {}
        virtual void printOn(std::ostream &out) const override {
            out << op << "(" << *expr1 << ", " << *expr2 << ")";
        }
    private:
        Expr *expr1;
        Expr *expr2;
        char op;
};

class Var: public 
class Int: public Var {

}
#endif
