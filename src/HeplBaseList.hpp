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

template<class T>
HeplBaseList<T>::HeplBaseList()
    : m_pHead(nullptr) {
}

template<class T>
HeplBaseList<T>::HeplBaseList(HeplBaseList& baseList)
    : m_pHead(nullptr) {

    if (baseList.m_pHead == nullptr) {
        return;
    }

    m_pHead = new HeplCell<T>();
    m_pHead->setValue(*(baseList.m_pHead->getValue()));
    m_pHead->setNext(nullptr);

    HeplCell<T> *currentHeplCell = nullptr;
    HeplCell<T> *nextHeplCell = nullptr;

    currentHeplCell = m_pHead;
    nextHeplCell = baseList.m_pHead->getNext();

    // Inspiration taken from: https://stackoverflow.com/q/7811893/3514658
    while (nextHeplCell != nullptr) {
        currentHeplCell->setNext(new HeplCell<T>());
        currentHeplCell = currentHeplCell->getNext();

        currentHeplCell->setValue(*(nextHeplCell->getValue()));
        nextHeplCell = nextHeplCell->getNext();
    }
    currentHeplCell->setNext(nullptr);
}

template<class T>
void HeplBaseList<T>::erase() {
    HeplCell<T> *baseListHeplCell = m_pHead;
    HeplCell<T> *baseListHeplCellCurrent = nullptr;
    while (baseListHeplCell != nullptr) {
        baseListHeplCellCurrent = baseListHeplCell;
        baseListHeplCell = baseListHeplCell->getNext();
        delete baseListHeplCellCurrent;
    }
    m_pHead = nullptr;
}

template<class T>
HeplBaseList<T>::~HeplBaseList() {
    erase();
}

template<class T>
bool HeplBaseList<T>::isEmpty() const {
    return m_pHead == nullptr ? true : false;
}

template<class T>
size_t HeplBaseList<T>::getNumberItems() const {

    HeplCell<T> *baseListHeplCell = m_pHead;
    size_t i = 0;
    while (baseListHeplCell != nullptr) {
        baseListHeplCell = baseListHeplCell->getNext();
        i++;
    }
    return i;
}

template<class T>
void HeplBaseList<T>::display() const {
    HeplCell<T> *baseListHeplCell = m_pHead;
    for (size_t i = 0; baseListHeplCell != nullptr; i++) {
        baseListHeplCell->display();
        baseListHeplCell = baseListHeplCell->getNext();
    }
}

template<class T>
HeplBaseList<T>& HeplBaseList<T>::operator=(HeplBaseList const& baseList) {

    erase();

    if (baseList.m_pHead == nullptr) {
        return *this;
    }

    HeplCell<T> *baseListCell = baseList.m_pHead;
    HeplCell<T> *newCell = new HeplCell<T>();
    m_pHead = newCell;

    while (baseListCell != nullptr) {
        newCell->setValue(*(baseListCell->getValue()));
        if (baseListCell->getNext() == nullptr) {
            newCell->setNext(nullptr);
            break;
        }
        newCell->setNext(new HeplCell<T>());
        newCell = newCell->getNext();
        baseListCell = baseListCell->getNext();
    }

    return *this;
}

template<class T>
T& HeplBaseList<T>::operator[](size_t itemNumber) {
    HeplCell<T> *baseListHeplCell = m_pHead;
    for (size_t i = 0; baseListHeplCell != nullptr && i != itemNumber; i++) {
        baseListHeplCell = baseListHeplCell->getNext();
    }

    if (baseListHeplCell == nullptr) {
        throw HeplBaseListItemNotFoundException();
    }
    return *(baseListHeplCell->getValue());
}

#include "HeplBaseListIterator.hpp"

#endif // BASELIST_HPP_INCLUDED
