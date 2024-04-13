#include "types.hpp"
#include <memory>

namespace types {

    TypePtr intType = std::make_shared<IntType>();
    TypePtr byteType = std::make_shared<ByteType>();
    TypePtr BarrayType = std::make_shared<ArrayType>(types::byteType);
    TypePtr IarrayType = std::make_shared<ArrayType>(types::intType);
    
    // Check if the types are the same
    bool sameType(std::string a, std::string b) {

        if (a == b) {
            //std::cout << "These are the same types: " << a << std::endl;
            return true;
        } else {
            //std::cout << "These are different types: " << a << " and " << b << std::endl;
            return false;
        }
    }

};


