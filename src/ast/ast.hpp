#ifndef __AST_HPP__
#define __AST_HPP__

// #include <cmath>
#include <iostream>
// #include <iterator>
// #include <string.h>
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


class Array : public Type {
    public: 
        Array(Type *t) : type(t) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Array(" << *type << ")";
        }

    private:
        Type *type;
};

class Stmt: public AST {
    public:
};

class Expr: public AST {
    public:
};

class Param : public AST {
    public:
        Param(std::string *id, std::string *pass, Type *t) : id(id), pass(pass), type(t) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Param(" << *id << ", " << *pass << ", " << *type << ")" ;
        }

    private:
        std::string *id;
        std::string *pass;
        Type *type;
};


class Block: public AST {
    public:
        Block() {}
        Block(std::vector<AST *> list) : list(list) {}
        void append(AST *s) { list.push_back(s); }
        virtual void printOn(std::ostream &out) const override {
            out << "Block(";
            bool first = true;
            for (AST *s : list){
                if (!first)
                    out << " ,";
                first = false;
                out << *s; 
            }
            out << ")";
        }
    private:
        std::vector<AST *> list;
};

class Func : public AST {
    public:
        Func(std::string *id,Block *p,
                Type *ret, Block *local_def,
                Block *compound) : id(id), param_list(p),
                retType(ret), def_list(local_def), compound(compound)  {}
        virtual void printOn(std::ostream &out) const override {
            out << "Func(" << *id << ",";
            out << *param_list << ",";
            out << *retType << ",";
            out << *def_list << "," << *compound << ")";
        }

    private:
        std::string *id;
        Block *param_list;
        Type *retType;
        Block *def_list;
        Block *compound;
};



class DataType : public AST {
    public:
        DataType(std::string *T_id) : id(T_id) {}
        virtual void printOn(std::ostream &out) const override {
            out << "DataType(" << *id << ")";
        }
    private:
        std::string *id;
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
        Var(std::string *id, DataType *t, Const *c = nullptr) : id(id), type(t), value(c) {}
        virtual void printOn(std::ostream &out) const override {
            if (value == nullptr) { 
                out << "Var(" << *id << ", " << *type << ")";
            } else {
                out << "Var(" << *id << ", " << *type << ", " << *value << ")";
            }
        }

    private: 
        std::string *id;
        DataType *type;
        Const *value;
};

class Cond: public AST {
    public: 

        Cond(std::string *op, AST *first = nullptr, AST *second = nullptr): operation(op), first(first), second(second)  {}
        virtual void printOn(std::ostream &out) const override {
            if( second == nullptr) {
                out << "Cond (" << *operation << ")";
            }
            else {
                if (first != nullptr) {
                    out << "Cond (" << *first << *operation << *second << ")";
                }
                else {
                    out << "Cond (" << *operation << *second <<")";
                }
            }
        }
    private:
        std::string *operation;
        AST *first;
        AST *second;
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
        BinOp(Expr *e1=0, char o=0, Expr *e2=0): expr1(e1), expr2(e2), op(o) {}
        virtual void printOn(std::ostream &out) const override {
            out << op << "(" << *expr1 << ", " << *expr2 << ")";
        }
    private:
        Expr *expr1;
        Expr *expr2;
        char op;
};




class Int : public AST {
    public:

    private:
};

class String : public AST {
    public:
        String(std::string *s) : str(s) {}
        virtual void printOn(std::ostream &out) const override {
            out << "String(" << *str << ")";
        }

    private:
        std::string *str;
};


class LValue : public AST {
    public:
        LValue(std::string *id, Expr *e = nullptr) : id(id), expr(e) {}
        virtual void printOn(std::ostream &out) const override {
            if (expr == nullptr) {
                out << "LValue(" << *id << ")";
            } else {
                out << "LValue(" << *id << ", " << *expr << ")";
            }
        }

    private:
        std::string *id;
        Expr *expr;
};


class Call : public AST {
    public:
        Call(std::string *id, Block *block) : id(id), block(block) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Call(" << *id << ", " << *block << ")";
        }

    private:
        std::string *id;
        Block *block;

};


class Assign : public AST {
    public:
        Assign(LValue *l, Expr *e) : lvalue(l), expr(e) {}
        virtual void printOn(std::ostream &out) const override {
            out << "Assign(" << *lvalue << ", " << *expr << ")";
        }

    private: 
        LValue *lvalue;
        Expr *expr;

};

#endif
