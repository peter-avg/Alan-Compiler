#include "types.hpp"
#include <memory>

namespace types {

    TypePtr intType = std::make_shared<IntType>();
    TypePtr byteType = std::make_shared<ByteType>();
};


