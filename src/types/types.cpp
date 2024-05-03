#include "types.hpp"
#include <memory>

namespace types {

    TypePtr voidType = std::make_shared<VoidType>();
    TypePtr intType = std::make_shared<IntType>();
    TypePtr byteType = std::make_shared<ByteType>();
    TypePtr voidType = std::make_shared<VoidType>();
    TypePtr BarrayType = std::make_shared<ArrayType>(types::byteType);
    TypePtr IarrayType = std::make_shared<ArrayType>(types::intType);
    
    // Check if the types are the same
    bool sameType(std::string a, std::string b) {

        if (a == b) {
            return true;
        } else {
            return false;
        }
    }

};


