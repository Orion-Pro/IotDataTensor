#ifndef RANKONETENSORTYPE_H
#define RANKONETENSORTYPE_H

#include "BaseTensor.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class RankOneTensorType : public BaseTensor<T> {
    private:
        std::vector<T> data;

    public:
        RankOneTensorType(): data(0) {} //Default constructor
        RankOneTensorType(int size): data(size) {} //Parameter based constructor
        RankOneTensorType(const RankOneTensorType& other): data(other.data) {} //Copy Constructor
        virtual ~RankOneTensorType() = default; //Virtual destructor set to default.

        virtual void loadData() override; //Function signature for overriding function based on data type.

        const T& operator[](const int index) const { //read values [] operator.
            if (index > data.size())
                throw std::invalid_argument("Index is out of bounds.");
            return data[index];
        }

        T& operator[](const int index) { //Read/Write values [] operator.
            if (index > data.size())
                throw std::invalid_argument("Index is out of bounds.");
            return data[index];
        }
        
        RankOneTensorType& operator=(const RankOneTensorType& other) { //Assignment operator
            if (data.size() != other,data.size())
                throw std::invalid_argument("The size of the tensors do not match.");
            data = other.data;
            return *this;
        }

        bool operator==(const RankOneTensorType& other) const { //not required by the assignment, comparison operator.
            if (this->data.size() != other->data.size())
                throw std::invalid_argument("The size of the tensors do not match.");
            
            for (int i = 0; i < other.data.size(); i++) {
                if (other.data[i] != data[i]) {
                    std::string message = "The items at index " + std::to_string(i) + " have different values.";
                    throw std::invalid_argument(message);
                }
            }
            return true;
        }

        friend RankOneTensorType operator+(const RankOneTensorType<T>& left, const RankOneTensorType<T>& right) {
            if (left.data.size() != right.data.size())
                throw std::invalid_argument("The size of the tensors do not match.");
            
            RankOneTensorType<T> result(left.data.size()); //Doesn't matter which tensor size you use as long as they are eequal.
            for (int i = 0; i < left.data.size(); i++) {
                result[i] = left.data[i] + right.data[i];
            }
            return result;
        }

        RankOneTensorType operator+(double scalar) { //+ scalar addition operator
            RankOneTensorType result(data.size());
            for (size_t i = 0; i < data.size(); ++i)
                result.data[i] = data[i] + scalar;
            return result;
        }

        RankOneTensorType& operator++() { //prefix increment operator //assignment only requires prefix
            for (auto& item : data)
                ++item;
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& os, const RankOneTensorType<T>& t) { //Output operator.
            os << "[";
            for (int i = 0; i < t.data.size(); ++i) {
                os << t.data[i];
                if (i != t.data.size())
                    os << " ";
            }
            os << "]";
            return os;
        }
        
        friend std::istream& operator>>(std::istream& is, RankOneTensorType<T>& t) { //Input operator.
            for (int i = 0; i < t.data.size(); i++)
                is >> t.data[i];
            return is;
        }                
        

};

template<>
void RankOneTensorType<double>::loadData() { //Double cab just use the base class valueGen function
    std::fill(this->data.begin(), this->data.end(), this->valueGen());
}

template<>
void RankOneTensorType<std::string>::loadData() { //String needs to convert the output of valueGen to a string.
    std::fill(this->data.begin(), this->data.end(), std::to_string(this->valueGen()));
}

#endif