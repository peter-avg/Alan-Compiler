#ifndef __AST_HPP__
#define __AST_HPP__ 

#include <iostream>


class AST {
    public:
        virtual void printOn(std::ostream &out) const = 0;
};

inline std::ostream & operator << (std::ostream &out, const AST &ast){
    ast.printOn(out);
    return out;
}

class Stmt : public AST {
    public:
};

class Expr : public AST {
    public:
};


#endif
