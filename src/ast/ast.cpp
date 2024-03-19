#include "ast.hpp"

#include "../symbol/symbol.hpp"

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
        ntabs++;
        bool flag = true;
        printTabs(out);
        out << "Block{\n";
        for (ASTPtr s : list){
            if (!flag)
                out << ", ";
            out << *s;

            ntabs++;
            printTabs(out);
            ntabs--;

            out << "\n";

            flag = false;
        }
        out << "\n}";
        ntabs--;
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

        out << "Return Type: " << *retType << ",\n";
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

    void Var::printOn(std::ostream &out) const {
        if (value == 0) { 
            out << "Var(" << id << ": " << *type << ")";
        } else {
            out << "Var(" << id << ": " << *type << "= " << value << ")";
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
        out << op << "(" << *expr1 << ", " << *expr2 << ")";
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
    }

    void Assign::printOn(std::ostream &out) const {
        out << "Assign(" << *lvalue << ", " << *expr << ")";
    }

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/


    // void Param::sem(sym::Table table) {
    //     sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, 1 /* level */, type);
    //     sym::EntryPtr exists = table.lookupEntry(entry);
    //     if (exists != nullptr) {
    //         std::cerr << "Error: " << id << " already exists in the current scope" << std::endl;
    //         return;
    //     }
    //     table.insertEntry(entry);
    // };
    //
    // void Block::sem(sym::Table table) {
    //     for (auto item : list) {
    //         item->sem(table);
    //     }
    // };

    
    typedef std::shared_ptr<AST> ASTPtr;
    typedef std::vector<ASTPtr> ASTList;

}
