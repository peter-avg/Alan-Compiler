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
    } SearchType;

    typedef enum {
        VAR, 
        PARAM, 
        FUNC
    } EntryType;

    typedef enum {
        value, 
        reference
    } PassType;
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
            Entry(const std::string &id, int level, types::TypePtr type) : id(id), level(level), type(type) {};
            virtual std::string getId() const;
            virtual int getLevel() const;
            virtual int getValue() const = 0;
            virtual void setValue(int value) {};
            virtual void addParameters(EntryPtr parameter) {}; 
            virtual void addLocaldefs(ast::ASTList local_defs) {}; 
            virtual void addCompound(ast::ASTPtr compound) {};
            virtual ast::ASTPtr getCompound() const {
                return compound;
            }
            
            virtual ast::ASTList getLocaldefs() const {
                return local_defs;
            }
            virtual types::TypePtr getType() const {
                return type;
            }

            virtual EntryType getEType() const {
                return etype;
            }

            types::TypePtr getScopeType() const;

            ast::ASTPtr compound;
            ast::ASTList local_defs;
            EntriesVector parameters;
            types::TypePtr type;

        private:
            std::string id;
            int level;
            EntryType etype;
    };

    class ParamEntry : public Entry {
        public:
            ParamEntry(const std::string &id, int level, types::TypePtr type, PassType mode) :
                id(id), level(level), type(type), mode(mode) {};

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

            types::TypePtr getType() const override {
                return type;
            }
            EntryType getEType() const override {
                return etype;
            }
            types::TypePtr type;
        private:
            int value;
            std::string id;
            int level;
            PassType mode;
            EntryType etype = PARAM;
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

            types::TypePtr getType() const override {
                return type;
            }
            EntryType getEType() const override {
                return etype;
            }
            types::TypePtr type;
        private:
            int value;
            std::string id;
            int level;
            EntryType etype = VAR;
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

            virtual ast::ASTList getLocaldefs() const override {
                return local_defs;
            }
            virtual ast::ASTPtr getCompound() const override {
                return compound;
            }

            types::TypePtr getType() const override {
                return type;
            }
            
            EntryType getEType() const override {
                return etype;
            }
            ast::ASTList local_defs;
            ast::ASTPtr compound;

            types::TypePtr type;

        private:
            std::string id;
            int level;
            int result;
            EntryType etype = FUNC;
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
            Scope(EntryPtr root, int level, types::TypePtr type);
            int getLevel() const;
            EntryPtr root;
            void addReturn();
            int getReturns();
        private:
            types::TypePtr type;
            int returns = 0;
            int level;
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
            EntryPtr lookupEntry(std::string entry_id, SearchType searchtype);
            void removeEntry(EntryPtr entry);
            int getCurrentScope() const;
            bool isEmpty() const;
            void addReturn();
            int getReturns();
            void addLibrary();
            types::TypePtr getScopeType();

        private:
            HashTable table;
            ScopeStack scopeStack;
    };

    Table initializeSymbolTable();

}

#endif // __SYMBOL_HPP__
