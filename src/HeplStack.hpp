#ifndef HEPLSTACK_HPP_DEFINED
#define HEPLSTACK_HPP_DEFINED

#include <iostream>
#include "HeplBaseException.hpp"
#include "HeplBaseList.hpp"
#include "HeplCell.hpp"

template<class T>
class HeplStack : public HeplBaseList<T> {

    public:
        // Default constructor and copy constructor are automatically
        // inherited.
        T* add(const T& val);
        void push(const T& val);
        T top() const;
        T pop();
};

class HeplStackEmptyException: HeplBaseException {
    using HeplBaseException::HeplBaseException;
};

#include "HeplStack.ipp"

#endif // HEPLSTACK_HPP_DEFINED
