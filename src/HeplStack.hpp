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
        ~HeplStack();
        T* add(const T& val);
        void push(const T& val);
        T top() const;
        T pop();
};

class HeplStackEmptyException: HeplBaseException {
    using HeplBaseException::HeplBaseException;
};


template<class T>
HeplStack<T>::~HeplStack() {
    this->erase();
}

template<class T>
T* HeplStack<T>::add(const T& val) {

    T newVal(val);
    HeplCell<T> *newHeplCell = new HeplCell<T>();
    newHeplCell->setValue(newVal);
    newHeplCell->setNext(HeplBaseList<T>::m_pHead);
    HeplBaseList<T>::m_pHead = newHeplCell;
    return newHeplCell->getValue();
}

template<class T>
void HeplStack<T>::push(const T& val) {
    add(val);
}

template<class T>
T HeplStack<T>::top() const {

    if (HeplBaseList<T>::m_pHead == nullptr) {
        throw HeplStackEmptyException();
    }
    return *(HeplBaseList<T>::m_pHead->getValue());
}

template<class T>
T HeplStack<T>::pop() {

    if (HeplBaseList<T>::m_pHead == nullptr) {
        throw HeplStackEmptyException();
    }

    T newVal(*(HeplBaseList<T>::m_pHead->getValue()));
    HeplCell<T> *cellToRemove = HeplBaseList<T>::m_pHead;
    HeplBaseList<T>::m_pHead = HeplBaseList<T>::m_pHead->getNext();
    delete cellToRemove;
    return newVal;
}

#endif // HEPLSTACK_HPP_DEFINED
