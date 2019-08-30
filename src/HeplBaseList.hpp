#ifndef BASELIST_HPP_INCLUDED
#define BASELIST_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include "HeplCell.hpp"
#include "HeplBaseException.hpp"

template<class T>
class HeplBaseListIterator;

template<class T>
class HeplBaseList {

    protected:
        HeplCell<T> *m_pHead;
        void erase();

    public:
        // Constructors/destructors
        HeplBaseList();
        HeplBaseList(HeplBaseList& baselist);
        virtual ~HeplBaseList();

        // Other methods
        bool isEmpty() const;
        size_t getNumberItems() const;
        virtual void display() const;
        // Pure virtual method
        virtual T* add(T const& val) = 0;

        // Operators
        HeplBaseList& operator=(HeplBaseList const& baseList);
        T& operator[](size_t i);

        // Attributes
        friend class HeplBaseListIterator<T>;
};

class HeplBaseListItemNotFoundException: HeplBaseException {
    using HeplBaseException::HeplBaseException;
};

#include "HeplBaseList.ipp"
#include "HeplBaseListIterator.hpp"

#endif // BASELIST_HPP_INCLUDED
