#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "../types/types.hpp"

namespace sym {

    /**************************************************************************/
    /*                                                                        */
    /*                          Entry Class                                   */
    /*                                                                        */
    /**************************************************************************/

    class Entry;

    typedef std::shared_ptr<Entry> EntryPtr;

    class Entry {
        public:
            Entry() {};
            Entry(const std::string &id, int level) : id(id), level(level) {};
            std::string getId() const;
            int getLevel() const;

        private:
            std::string id;
            int level;
    };

    class ParamEntry : public Entry {
        public:
            ParamEntry(const std::string &id, int level, types::TypePtr type) : id(id), level(level), type(type) {};

        private:
            std::string id;
            int level;
            types::TypePtr type;
    };


    /**************************************************************************/
    /*                                                                        */
    /*                          Scope Class                                   */
    /*                                                                        */
    /**************************************************************************/

    class Scope;

    typedef std::shared_ptr<Scope> ScopePtr;

    class Scope {
        public:
            Scope(int level, EntryPtr root);
            int getLevel() const;

        private:
            int level;
            EntryPtr root;
    };

    /**************************************************************************/
    /*                                                                        */
    /*                          Table Class                                   */
    /*                                                                        */
    /**************************************************************************/

    typedef std::vector<ScopePtr> ScopeStack;
    typedef std::vector<EntryPtr> EntryStack;
    typedef std::map<std::string, EntryStack> HashTable;

    class Table {
        public:
            void openScope(EntryPtr root);
            void closeScope();
            void insertEntry(EntryPtr entry);
            EntryPtr lookupEntry(EntryPtr entry);
            void removeEntry(EntryPtr entry);

        private:
            HashTable table;
            ScopeStack scopeStack;
    };

}

#endif // __SYMBOL_HPP__
