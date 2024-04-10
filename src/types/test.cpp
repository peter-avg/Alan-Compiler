#include <iostream>
#include "types.hpp"
#include <memory>
#include <type_traits>

int main() {
    types::TypePtr intType = std::make_shared<IntType>();
    types::TypePtr byteType = std::make_shared<ByteType>();

    types::sameType(types::intType, types::byteType);
    return 0;
}
