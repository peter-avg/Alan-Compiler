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
            virtual std::string getId() const;
            virtual int getLevel() const;
            virtual int getValue() const = 0;
            virtual void setValue(int value) {};

        private:
            std::string id;
            int level;
    };

    class ParamEntry : public Entry {
        public:
            ParamEntry(const std::string &id, int level, types::TypePtr type) :
                id(id), level(level), type(type) {};

            virtual std::string getId() const override {
                return id;
            }

            virtual int getLevel() const override {
                return level;
            }

        private:
            std::string id;
            int level;
            types::TypePtr type;
    };

    class VarEntry : public Entry {
        public:
            VarEntry(const std::string &id, int level, types::TypePtr type) :
                id(id), level(level), type(type) {};

            virtual std::string getId() const override {
                return id;
            }

            virtual int getLevel() const override {
                return level;
            }

            int getValue() const override {
                return value;
            }

            void setValue(int value) override {
                this->value = value;
            }

        private:
            int value;
            std::string id;
            int level;
            types::TypePtr type;
    };

    class FuncEntry : public Entry {
        public:
            FuncEntry(const std::string &id, int level, types::TypePtr type) :
                id(id), level(level), type(type) {};

            virtual std::string getId() const override {
                return id;
            }

            virtual int getLevel() const override {
                return level;
            }

            int getValue() const override {
                return result;
            }

            void setValue(int value) override {
                result = value;
            }
        private:
            std::string id;
            types::TypePtr type;
            int level;
            int result;
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
            Scope(EntryPtr root, int level);
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
            int getCurrentScope() const;

        private:
            HashTable table;
            ScopeStack scopeStack;
    };

}

#endif // __SYMBOL_HPP__
