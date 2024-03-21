#include "ast.hpp"
#include "../symbol/symbol.hpp"

namespace ast {

    /**********************************************************************************
     *                                                                                *
     *                                  Semantic                                      *
     *                                                                                *
     * ********************************************************************************/


    void Param::sem(sym::Table table) {
        sym::EntryPtr entry = std::make_shared<sym::ParamEntry>(id, 1 /* level */, type);
        sym::EntryPtr exists = table.lookupEntry(entry);
        if (exists != nullptr) {
            std::cerr << "Error: " << id << " already exists in the current scope" << std::endl;
            return;
        }
        table.insertEntry(entry);
    };

    void Block::sem(sym::Table table) {
        for (auto item : list) {
            item->sem(table);
        }
    };


}
