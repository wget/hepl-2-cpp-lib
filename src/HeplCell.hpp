#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <iostream>

template<class T>
class HeplCell {

    private:
        T m_value;
        HeplCell<T> *m_pNext;
    public:
        HeplCell<T>();
        HeplCell<T>(T value, HeplCell<T> *pNext);
        T* getValue();
        HeplCell<T>* getNext() const;
        void setValue(T newValue);
        void setNext(HeplCell<T> *newNext);
        void display() const;
};

#include "HeplCell.ipp"

#endif // CELL_HPP_INCLUDED
