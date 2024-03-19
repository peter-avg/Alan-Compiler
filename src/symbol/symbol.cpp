#include "symbol.hpp"

namespace sym {

    /**************************************************************************/
    /*                                                                        */
    /*                          Entry Class                                   */
    /*                                                                        */
    /**************************************************************************/

    std::string Entry::getId() const { return id; }
    int Entry::getLevel() const { return level; }

    /**************************************************************************/
    /*                                                                        */
    /*                          Scope Class                                   */
    /*                                                                        */
    /**************************************************************************/

    Scope::Scope(int level, EntryPtr root) : level(level), root(root) {};

    int Scope::getLevel() const { return level; }

    /**************************************************************************/
    /*                                                                        */
    /*                          Table Class                                   */
    /*                                                                        */
    /**************************************************************************/
    
    void Table::openScope(EntryPtr root) {
        scopeStack.push_back(std::make_shared<Scope>(0, root));
    };

    void Table::closeScope() {
        scopeStack.pop_back();
    };

    void Table::insertEntry(EntryPtr entry) {
        table[entry->getId()].push_back(entry);
    };

    EntryPtr Table::lookupEntry(EntryPtr entry) {
        auto it = table.find(entry->getId());
        if (it != table.end()) {
            for (auto e : it->second) {
                if (e->getLevel() != scopeStack.back()->getLevel()) {
                    return e;
                }
            }
        }

        return nullptr;
    };

    void Table::removeEntry(EntryPtr entry) {
        auto it = table.find(entry->getId());
        if (it != table.end()) {
            for (auto e : it->second) {
                if (e->getLevel() <= scopeStack.back()->getLevel()) {
                    it->second.erase(std::find(it->second.begin(), it->second.end(), e));
                    return;
                }
            }
        }
    };

};
