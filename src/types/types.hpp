#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <iostream>
#include <memory>
namespace types {

    #define INT_SIZE 4
    #define BYTE_SIZE 1

    enum class TypeEnum {
        INT,
        BYTE,
        VOID,
        ARRAY,
        ARRAYI
    };

    class Type;
    class IntType;
    class ByteType;
    class VoidType;

    typedef std::shared_ptr<Type> TypePtr;

    class Type {
        public:
            Type() {}
            virtual ~Type() = default;
            virtual void printOn(std::ostream &out) const = 0;
            std::string typeName;
            virtual std::string getTypeName() {
                return typeName;
            }

            virtual int getSize() const {
                return 0;
            };
    };

    inline std::ostream &operator<<(std::ostream &out, const Type &type) {
        type.printOn(out);
        return out;
    }

    class VoidType : public Type { 
        public:
            VoidType() {
                typeName = "VoidType";
            }
            virtual ~VoidType() = default;
            virtual void printOn(std::ostream &out) const override {
                out << "Void";
            };
            virtual std::string getTypeName() override {
                return typeName;
            }
            std::string typeName; 
    };

    class IntType : public Type { 
        public:
            IntType() {
                typeName = "IntType";
            }
            virtual ~IntType() = default;
            virtual void printOn(std::ostream &out) const override {
                out << "Int";
            };
            int getSize() const override {
                return size;
            };
            std::string getTypeName() override {
                return typeName;
            }
            std::string typeName ;
        private:
            int size = INT_SIZE;
    };

    class ByteType : public Type { 
        public:
            ByteType() {
                typeName = "ByteType";
            }
            virtual ~ByteType() = default;
            virtual void printOn(std::ostream &out) const override {
                out << "Byte";
            };
            int getSize() const override {
                return size;
            };
            std::string getTypeName() override {
                return typeName;
            }
            std::string typeName;
        private:
            int size = BYTE_SIZE;
    };


    class ArrayType : public Type { 
        public:
            ArrayType(TypePtr type = nullptr, int size = 0) : type(type), size(size) {
                if (type->getTypeName() == "IntType") {
                    typeName = "IarrayType";
                } else {
                    typeName = "BarrayType";
                }
            }
            virtual ~ArrayType() = default;
            virtual void printOn(std::ostream &out) const override {
                out << "Type(Array(";
                out << *type;
                out << ":Size( " << size << ")))";
            };
            TypePtr getType() const { 
                return type;
            };

            int getSize() const override {
                return size;
            };
            
        private:
            TypePtr type;
            int size;
    };

    class ArrayIType : public Type { 
        public:
            ArrayIType(TypePtr type = nullptr) : type(type) {}
            virtual ~ArrayIType() = default;

            virtual void printOn(std::ostream &out) const {
                out << "Type(ArrayI(";
                out << *type;
                out << "))";
            };

            TypePtr getType() const { 
                return type;
            };
            
        private:
            TypePtr type;
    };
    
    extern TypePtr intType;
    extern TypePtr byteType;
    extern TypePtr voidType;
    extern TypePtr BarrayType;
    extern TypePtr IarrayType;

    bool sameType(std::string a, std::string b); 
}
#endif 
