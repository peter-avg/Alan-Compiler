#include "ast.hpp"
#include <iomanip>

namespace ast {

    int ntabs = 0;

    void printTabs(std::ostream &out) {
        for (int i = 0; i < ntabs; i++) {
            out << "\t";
        }
    }

    /**********************************************************************************
     *                                                                                *
     *                                  Print On                                      *
     *                                                                                *
     **********************************************************************************/

    void Param::printOn(std::ostream &out) const {
        out << "Param(Id: " << id << ", Passed as: " << pass << ", " << *type << ")";
    }

    void Block::printOn(std::ostream &out) const {
        out << "Block {\n";
        ntabs++;
        bool first = true;
        for (const auto& stmt : list) {
            if (!first) {
                out << ",\n";
            }
            printTabs(out);
            out << *stmt;
            first = false;
        }
        ntabs--;
        out << "\n";
        printTabs(out);
        out << "}";
    }

    void Func::printOn(std::ostream &out) const {
        out << "Func [\n";
        ntabs++;
        printTabs(out);
        out << "Name: " << id << ",\n";

        printTabs(out);
        out << "Params: ";
        if (param_list.empty()) {
            out << "None";
        } else {
            for (const auto& p : param_list) {
                out << *p << ", ";
            }
        }
        out << ",\n";

        printTabs(out);
        out << "Return Type: " << *type << ",\n";

        printTabs(out);
        out << "Defs: ";
        if (def_list.empty()) {
            out << "None";
        } else {
            for (const auto& d : def_list) {
                out << *d << ", ";
            }
        }
        out << ",\n";

        printTabs(out);
        out << "Body: ";
        out << *compound;
        ntabs--;
        out << "\n";
        printTabs(out);
        out << "]";
    }

    void Const::printOn(std::ostream &out) const {
        out << "Const(" << num << ")";
    }

    void VarDef::printOn(std::ostream &out) const {
        if (indeces == INT_MAX) {
            out << "Var(" << id << ": " << *type << ")";
        } else {
            out << "Var(" << id << ": " << *type << " = " << indeces << ")";
        }
    }

    void Cond::printOn(std::ostream &out) const {
        out << "Cond(";
        if (first) {
            out << *first << " ";
        }
        out << operation << " ";
        if (second) {
            out << *second;
        }
        out << ")";
    }

    void While::printOn(std::ostream &out) const {
        out << "While(" << *cond << ", " << *stmt << ")";
    }

    void If::printOn(std::ostream &out) const {
        out << "If(" << *cond << ", " << *stmt1;
        if (stmt2) {
            out << ", " << *stmt2;
        }
        out << ")";
    }

    void Return::printOn(std::ostream &out) const {
        out << "Return(" << *expr << ")";
    }

    void Char::printOn(std::ostream &out) const {
        out << "Char(" << static_cast<int>(var) << ")";
    }

    void BinOp::printOn(std::ostream &out) const {
        out << op << "(" << *expr1;
        if (expr2) {
            out << ", " << *expr2;
        }
        out << ")";
    }

    void String::printOn(std::ostream &out) const {
        out << "String(" << std::quoted(str) << ")";
    }

    void LValue::printOn(std::ostream &out) const {
        out << "LValue(" << id;
        if (expr) {
            out << ", " << *expr;
        }
        out << ")";
    }

    void Call::printOn(std::ostream &out) const {
        out << "Call(" << id << ", ";
        bool first = true;
        for (const auto& arg : block) {
            if (!first) {
                out << ", ";
            }
            out << *arg;
            first = false;
        }
        out << ")";
    }

    void Assign::printOn(std::ostream &out) const {
        out << "Assign(" << *lvalue << ", " << *expr << ")";
    }

    void Print::printOn(std::ostream &out) const {
        out << "Print(" << *expr << ")";
    }

} // namespace ast

