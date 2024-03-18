#include "table.hpp"
#include "entries.hpp"

namespace sem {

    void Table::openScope(EntryPtr root) {};

    void Table::closeScope() {};

    void Table::insertEntry(EntryPtr entry) {};

    EntryPtr Table::lookupEntry(const std::string &name) {
        return nullptr;
    };

    void Table::removeEntry(const std::string &name) {};

    TablePtr initTable() {
        return nullptr;
    };

};
