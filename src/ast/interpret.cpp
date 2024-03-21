#include "ast.hpp"

namespace ast {

    /********************************************************
    *                                                       *
    *                      Evaluation                       *
    *                                                       *
    ********************************************************/

    int Cond::eval() const {
        if (first == nullptr && second == nullptr) {
            if (operation == "true") {
                return true;
            }
            return false;
        }
        if (operation == "<") return first->eval() < second->eval();
        if (operation == ">") return first->eval() > second->eval();
        if (operation == "==") return first->eval() == second->eval();
        if (operation == "!=") return first->eval() != second->eval();
        if (operation == ">=") return first->eval() >= second->eval();
        if (operation == "<=") return first->eval() <= second->eval();
        if (operation == "&") return first->eval() && second->eval();
        if (operation == "|") return first->eval() || second->eval();
        return false;
    }

    int BinOp::eval() const {

        if (expr2 != nullptr) {
            switch(op) {
                case '+': return expr1->eval() + expr2->eval();
                case '-': return expr1->eval() - expr2->eval();
                case '*': return expr1->eval() * expr2->eval();
                case '/': return expr1->eval() / expr2->eval();
                case '%': return expr1->eval() % expr2->eval();
            }
        }
        switch(op) {
            case '+': return expr1->eval();
            case '-': return -expr1->eval();
        }
        return 0;
    }

    int Const::eval() const {
        return num;
    }

    int Var::eval() const {
        return value;
    }

    int LValue::eval() const {
        return expr->eval();
    }

    int Return::eval() const {
        return expr->eval();
    }

    /********************************************************
    *                                                       *
    *                      Running                          *
    *                                                       *
    ********************************************************/


    void Block::run() const {
        for (auto &stmt : list) {
            stmt->run();
        }
    }

    void Func::run() const {
        compound->run();
    }


    void While::run() const {
        while (cond->eval()) {
            stmt->run();
        }
    }

    void If::run() const {
        if (stmt2 != nullptr) {
            if (cond->eval()) {
                stmt1->run();
            } else {
                stmt2->run();
            }
        } else {
            if (cond->eval()) {
                stmt1->run();
            }
        }
    }


    void Call::run() const {
        for (auto &item : block) {
            item->run();
        }
    }

    void Assign::run() const {

    }

}
