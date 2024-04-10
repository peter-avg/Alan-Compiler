#include "symbol.hpp"
namespace sym {
    bool main_func = false;
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

    Scope::Scope(EntryPtr root, int level, types::TypePtr type) : root(root), level(level), type(type) {};

    int Scope::getLevel() const { 
        return level; 

    }

    void Scope::addReturn() {
        returns++;
    }

    int Scope::getReturns() {
        return returns;
    }

    /**************************************************************************/
    /*                                                                        */
    /*                          Table Class                                   */
    /*                                                                        */
    /**************************************************************************/

    void Table::openScope(EntryPtr root) {
        scopeStack.push_back(std::make_shared<Scope>(root, this->getCurrentScope()+1, root->getType()));
    };

    void Table::closeScope() {
        scopeStack.pop_back();
    };

    void Table::insertEntry(EntryPtr entry) {
        table[entry->getId()].push_back(entry);
        /*std::cout << "insertEntry: id of Entry -> \"" << entry->getId() << "\" of EType -> ";
        switch(entry->getEType()){
            case VAR: std::cout << "VAR"; break;
            case FUNC: std::cout << "FUNC"; break;
            case PARAM: std::cout << "PARAM"; break;
        }
        std::cout << " in scope -> " << entry->getLevel() << std::endl; */
    };

    EntryPtr Table::lookupEntry(std::string entry_id, SearchType searchtype) {
        auto it = table.find(entry_id);
        EntryPtr result;
        if (it != table.end()) {
            for (auto e : it->second) {
                if (searchtype == GLOBAL && e->getLevel() <= this->getCurrentScope()) {
                    result = e;
                }
                else if (searchtype == LOCAL && e->getLevel() == this->getCurrentScope()){
                    result = e;
                }
            }
            return result;
        }
        return nullptr;
    };


    void Table::removeEntry(EntryPtr entry) {
        auto it = table.find(entry->getId());
        if (it != table.end()) {
            for (auto e : it->second) {
                if (e->getLevel() <= this->getCurrentScope()) {
                    it->second.erase(std::find(it->second.begin(), it->second.end(), e));
                    return;
                }
            }
        }
    };

    int Table::getCurrentScope() const {
        if (scopeStack.empty())
            return 0;
        else
            return scopeStack.back()->getLevel();
    }
    
    bool Table::isEmpty() const {
        return table.empty();
    }
    
    void Table::addReturn() {
       this->scopeStack.back()->addReturn(); 
    }

    int Table::getReturns() {
       return this->scopeStack.back()->getReturns();
    }
    types::TypePtr Table::getScopeType() {
        return this->scopeStack.back()->root->getType();
    }
};
