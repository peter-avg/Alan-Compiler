#include "scope.hpp"
#include "entries.hpp"

namespace sem {

    Scope::Scope(int level, EntryPtr root) : level(level), root(root) {};
    int Scope::getLevel() const { return level; }

};
