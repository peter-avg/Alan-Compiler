#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <iostream>
#include <memory>
#include <type_traits>
namespace types {

#define INT_SIZE 4
#define BYTE_SIZE 1

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
            virtual std::string getTypeName() const {
                return typeName;
            }
            virtual TypePtr getArrayType() const{ 
                return type;
            };
            virtual bool isArray() {
                return false;
            }
        private: 
            TypePtr type;
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
            virtual std::string getTypeName() const override {
                return typeName;
            }
            std::string typeName; 
            virtual bool isArray() override {
                return false;
            }
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
            int getSize() const {
                return size;
            };
            std::string getTypeName() const override {
                return typeName;
            }
            std::string typeName ;
            virtual bool isArray() override {
                return false;
            }
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
            int getSize() const {
                return size;
            };
            std::string getTypeName() const override {
                return typeName;
            }
            std::string typeName;
            
            virtual bool isArray() override {
                return false;
            }
        private:
            int size = BYTE_SIZE;
    };


    class ArrayType : public Type { 
        public:
            ArrayType(TypePtr type = nullptr, int size = 0) : type(type), size(size) {}
            virtual ~ArrayType() = default;
            virtual void printOn(std::ostream &out) const override {
                out << "Type(Array(";
                out << *type;
                out << ":Size( " << size << ")))";
            };
            virtual TypePtr getArrayType() const  override { 
                return type;
            };
            std::string getTypeName() const override {
                if (type->getTypeName() == "IntType") 
                    return "IArrayType";
                else if (type->getTypeName() == "ByteType"){
                    return "BArrayType";
                }
                else return "ArrayType";
            }

            int getSize() const {
                return size;
            };

            virtual bool isArray() override {
                return true;
            }
            
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
    
    extern TypePtr voidType;
    extern TypePtr intType;
    extern TypePtr byteType;
    extern TypePtr BarrayType;
    extern TypePtr IarrayType;

    bool sameType(std::string a, std::string b); 
}
#endif 
