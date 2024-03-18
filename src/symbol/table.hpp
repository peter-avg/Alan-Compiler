#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include <deque>
#include <map>
#include "entries.hpp"
#include "scope.hpp"

namespace sem {

    typedef std::deque<ScopePtr> ScopeStack;
    typedef std::deque<EntryPtr> EntryStack;
    typedef std::map<std::string, sem::EntryStack> HashTable;

    class Table {
        public:
            void openScope(EntryPtr root);
            void closeScope();
            void insertEntry(EntryPtr entry);
            EntryPtr lookupEntry(const std::string &name);
            void removeEntry(const std::string &name);

        private:
            HashTable table;
            ScopeStack scopeStack;
    };

    typedef std::shared_ptr<Table> TablePtr;

    TablePtr initTable();

}

#endif // __TABLE_HPP__
