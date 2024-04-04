#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "../types/types.hpp"
namespace ast {
    class AST; 
    using ASTPtr = std::shared_ptr<AST>;
    using ASTList = std::vector<ASTPtr>;
}
namespace sym {
    typedef enum {
        GLOBAL, 
        LOCAL
    }SearchType;
    /**************************************************************************/
    /*                                                                        */
    /*                          Entry Class                                   */
    /*                                                                        */
    /**************************************************************************/
    

    class Entry;

    typedef std::shared_ptr<Entry> EntryPtr;
    typedef std::vector<EntryPtr> EntriesVector;

    class Entry {
        public:
            Entry() {};
            Entry(const std::string &id, int level) : id(id), level(level) {};
            virtual std::string getId() const;
            virtual int getLevel() const;
            virtual int getValue() const = 0;
            virtual void setValue(int value) {};
            virtual void addParameters(EntryPtr parameter) {}; 
            virtual void addLocaldefs(ast::ASTList local_defs) {}; 
            virtual void addCompound(ast::ASTPtr compound) {};
            virtual ast::ASTPtr getCompound() {
                return compound;
            }
            
            virtual ast::ASTList getLocaldefs() {
                return local_defs;
            }

            ast::ASTPtr compound;
            ast::ASTList local_defs;
            EntriesVector parameters;

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
                id(id), level(level), type(type) {} 

            virtual std::string getId() const override {
                return id;
            }

            virtual int getLevel() const override {
                return level;
            }

            virtual int getValue() const override {
                return result;
            }

            virtual void setValue(int value) override {
                result = value;
            }


            virtual void addParameters(EntryPtr parameter) override{
                parameters.push_back(parameter);
            }
            
            virtual void addLocaldefs(ast::ASTList local_defs) override{
                this->local_defs = local_defs; 
            } 
            virtual void addCompound(ast::ASTPtr comp) override{
                compound = comp;
            }

            virtual ast::ASTList getLocaldefs() override {
                return local_defs;
            }
            virtual ast::ASTPtr getCompound() override {
                return compound;
            }

            ast::ASTList local_defs;
            ast::ASTPtr compound;


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
            EntryPtr lookupEntry(EntryPtr entry, SearchType searchtype);
            void removeEntry(EntryPtr entry);
            int getCurrentScope() const;
            bool isEmpty() const;

        private:
            HashTable table;
            ScopeStack scopeStack;
    };

}

#endif // __SYMBOL_HPP__
