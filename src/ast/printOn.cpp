#include "ast.hpp"


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
     * ********************************************************************************/

    void Param::printOn(std::ostream &out) const {
        out << "Param(Id:" << id << ",Passed as: " << pass << ", " << *type << ")" ;
    }

    void Block::printOn(std::ostream &out) const {
        bool flag = true;
        out << "Block{\n";
        ntabs++;
        for (ASTPtr s : list){
            if (!flag)
                out << ", ";
            printTabs(out);
            out << *s;


            out << "\n";

            flag = false;
        }
        ntabs--;
        printTabs(out);
        out << "}";
    }

    void Func::printOn(std::ostream &out) const {
        printTabs(out);
        out << "Func[\n";
        ntabs++;
        printTabs(out);
        out << "Name:" << id << ",\n";
        printTabs(out);
        out << "Params: ";

        for (auto p : param_list) {
            out << *p << ", ";
        }

        if (param_list.size() == 0) {
            out << "None, ";
        }

        out << "\n";

        printTabs(out);

        out << "Return Type: " << *type << ",\n";
        printTabs(out);
        out <<  "Defs: ";

        for (auto p : def_list) {
            out << *p << ", ";
        }

        out << ",\n";
        printTabs(out);
        out << "Body: ";

        ntabs--;
        printTabs(out);
        out << *compound << "\n]";
        ntabs--;
    }

    void Const::printOn(std::ostream &out) const {
        out << "Const(" << num << ")";
    }

    void VarDef::printOn(std::ostream &out) const {
        if (value == INT_MAX) { 
            out << "Var(" << id << ": " << *type << ")";
        } else {
            out << "Var(" << id << ": " << *type << " = " << value << ")";
        }
    }

    void Cond::printOn(std::ostream &out) const {
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

    void While::printOn(std::ostream &out) const {
        out << "While (" << *cond << *stmt << ")";
    }

    void If::printOn(std::ostream &out) const {
        out << "If(" << *cond << ", " << *stmt1;
        if (stmt2 != nullptr ) out << ", " << *stmt2;
        out << ")"; 
    }

    void Return::printOn(std::ostream &out) const {
        out << "Return(" << *expr  << ")"; 
    }

    void Char::printOn(std::ostream &out) const {
        out << "Char(" << static_cast<int>(var) << ")";
    }

    void BinOp::printOn(std::ostream &out) const {
        out << op << "(" << *expr1 ;
        if (expr2 != nullptr)
            std::cout << ", " << *expr2 << ")";
    }

    void String::printOn(std::ostream &out) const {
        out << "String(" << str << ")";
    }

    void LValue::printOn(std::ostream &out) const {
        if (expr == nullptr) {
            out << "LValue(" << id << ")";
        } else {
            out << "LValue(" << id << ", " << *expr << ")";
        }
    }

    void Call::printOn(std::ostream &out) const {
        out << "Call(" << id << ", ";
        for (auto p : block) {
            out << *p << ", ";
        };
        out << ")";
    }

    void Assign::printOn(std::ostream &out) const {
        out << "Assign(" << *lvalue << ", " << *expr << ")";
    }

    void Print::printOn(std::ostream &out) const {
        out << "Print(" << *expr << ")";
    }

    
    typedef std::shared_ptr<AST> ASTPtr;
    typedef std::vector<ASTPtr> ASTList;

}
