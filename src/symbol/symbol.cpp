#include "symbol.hpp"
#include <iterator>
#include <memory>
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
    void Table::addLibrary() {
        EntryPtr writeInteger = std::make_shared<FuncEntry>("writeInteger", 0, types::voidType);
        sym::EntryPtr write_integer = std::make_shared<sym::ParamEntry>("write_integer", 0, types::intType, value);
        writeInteger->addParameters(write_integer);
        this->insertEntry(writeInteger);

        EntryPtr writeByte = std::make_shared<FuncEntry>("writeByte", 0, types::voidType);
        sym::EntryPtr write_byte = std::make_shared<sym::ParamEntry>("write_byte", 0, types::byteType, value);
        writeByte->addParameters(write_byte);
        this->insertEntry(writeByte);

        EntryPtr writeChar = std::make_shared<FuncEntry>("writeChar", 0, types::voidType);
        sym::EntryPtr character = std::make_shared<sym::ParamEntry>("character", 0, types::byteType, value);
        writeChar->addParameters(character);
        this->insertEntry(writeChar);
        
        EntryPtr writeString= std::make_shared<FuncEntry>("writeString", 0, types::voidType);
        sym::EntryPtr refbyte = std::make_shared<sym::ParamEntry>("refbyte", 0, types::BarrayType, reference);
        writeString->addParameters(refbyte);
        this->insertEntry(writeString);
        
        EntryPtr readInteger= std::make_shared<FuncEntry>("readInteger", 0, types::intType);
        this->insertEntry(readInteger);
        
        EntryPtr readByte = std::make_shared<FuncEntry>("readByte", 0, types::intType);
        this->insertEntry(readByte);
        
        EntryPtr readChar = std::make_shared<FuncEntry>("readChar", 0, types::byteType);
        this->insertEntry(readChar);
        
        EntryPtr readString = std::make_shared<FuncEntry>("readString", 0, types::voidType);
        sym::EntryPtr n = std::make_shared<sym::ParamEntry>("n", 0, types::BarrayType, value);
        sym::EntryPtr read_refbyte = std::make_shared<sym::ParamEntry>("refbyte", 0, types::intType, reference);
        readString->addParameters(n);
        readString->addParameters(read_refbyte);
        this->insertEntry(readString);
        
        EntryPtr extend = std::make_shared<FuncEntry>("writeString", 0, types::intType);
        sym::EntryPtr extend_byte = std::make_shared<sym::ParamEntry>("extend_byte", 0, types::BarrayType, value);
        extend ->addParameters(extend_byte);
        this->insertEntry(extend);
        
        EntryPtr shrink = std::make_shared<FuncEntry>("shrink", 0, types::intType);
        sym::EntryPtr shrink_integer = std::make_shared<sym::ParamEntry>("shrink_integer", 0, types::intType, value);
        shrink->addParameters(shrink_integer);
        this->insertEntry(shrink);
        
        EntryPtr strlen = std::make_shared<FuncEntry>("strlen", 0, types::intType);
        sym::EntryPtr s = std::make_shared<sym::ParamEntry>("s", 0, types::BarrayType, reference);
        strlen->addParameters(s);
        this->insertEntry(strlen);
        
        EntryPtr strcmp= std::make_shared<FuncEntry>("strcmp", 0, types::intType);
        sym::EntryPtr s1 = std::make_shared<sym::ParamEntry>("s1", 0, types::BarrayType, reference);
        sym::EntryPtr s2 = std::make_shared<sym::ParamEntry>("s2", 0, types::BarrayType, reference);
        strcmp->addParameters(s1);
        strcmp->addParameters(s2);
        this->insertEntry(strcmp);
        
        EntryPtr strcpy = std::make_shared<FuncEntry>("strcpy", 0, types::voidType);
        sym::EntryPtr cpy_trg = std::make_shared<sym::ParamEntry>("cpy_trg", 0, types::BarrayType, reference);
        sym::EntryPtr cpy_src = std::make_shared<sym::ParamEntry>("cpysrc", 0, types::BarrayType, reference);
        strcpy->addParameters(cpy_trg);
        strcpy->addParameters(cpy_src);
        this->insertEntry(strcpy);

        EntryPtr strcat = std::make_shared<FuncEntry>("strcat", 0, types::voidType);
        sym::EntryPtr cat_trg = std::make_shared<sym::ParamEntry>("cat_trg", 0, types::BarrayType, reference);
        sym::EntryPtr cat_src = std::make_shared<sym::ParamEntry>("cat_src", 0, types::BarrayType, reference);
        strcat->addParameters(cat_trg);
        strcat->addParameters(cat_src);
        this->insertEntry(strcat);
    }

    Table initializeSymbolTable() {
        Table vars;
        vars.addLibrary();
        return vars;
    }
};
