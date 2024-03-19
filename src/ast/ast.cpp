#include "ast.hpp"

#include "../symbol/symbol.hpp"

namespace ast {

    /**********************************************************************************
     *                                                                                *
     *                                  Print On                                      *
     *                                                                                *
     * ********************************************************************************/

    void Param::printOn(std::ostream &out) const {
        out << "Param(" << id << ", " << pass << ", " << *type << ")" ;
    }

    void Block::printOn(std::ostream &out) const {
        bool flag = true;
        out << "Block(";
        for (ASTPtr s : list){
            if (!flag)
                out << ", ";
            out << *s;
            flag = false;
        }
        out << ")";
    }

    void Func::printOn(std::ostream &out) const {
        out << "Func(" << id << ",";

        for (auto p : param_list) {
            out << *p << ", ";
        }

        out << *retType << ",";

        for (auto p : def_list) {
            out << *p << ", ";
        }

        out << *compound << ")";
    }

    void Const::printOn(std::ostream &out) const {
        out << "Const(" << num << ")";
    }

    void Var::printOn(std::ostream &out) const {
        if (value == 0) { 
            out << "Var(" << id << ", " << *type << ")";
        } else {
            out << "Var(" << id << ", " << *type << ", " << value << ")";
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

    void Int::printOn(std::ostream &out) const {
        out << "Int()";
    }

    void Byte::printOn(std::ostream &out) const {
        out << "Byte()";
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
