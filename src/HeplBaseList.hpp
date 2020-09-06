#ifndef BASELIST_HPP_INCLUDED
#define BASELIST_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include "HeplCell.hpp"
#include "HeplBaseException.hpp"

template<class T>
class HeplBaseListIterator;

// Forward declaration needed to make the operator considered as 'introvert'
// https://stackoverflow.com/a/4661372/3514658

template<class T>
class HeplBaseList;

template<class T>
std::ostream& operator<<(std::ostream& lhs, const HeplBaseList<T>& rhs);

template<class T>
class HeplBaseList {

    protected:
        HeplCell<T> *m_pHead;
        void erase();

    public:
        // Constructors/destructors
        HeplBaseList();
        HeplBaseList(const HeplBaseList& baselist);
        virtual ~HeplBaseList();

        // Other methods
        bool isEmpty() const;
        size_t getNumberItems() const;
        virtual void display() const;
        bool find(T const& val) const;
        // Pure virtual method
        virtual T* add(T const& val) = 0;

        // Operators
        HeplBaseList& operator=(HeplBaseList const& baseList);
        friend std::ostream& operator<<<T>(std::ostream& lhs, const HeplBaseList<T>& rhs);
        T& operator[](size_t i);
        const T& operator[](size_t i) const;

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
HeplBaseList<T>::HeplBaseList(const HeplBaseList& baseList)
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
    while (baseListHeplCell != nullptr) {
        baseListHeplCell->display();
        baseListHeplCell = baseListHeplCell->getNext();
    }
}

template<class T>
bool HeplBaseList<T>::find(T const& val) const {
    HeplCell<T> *baseListHeplCell = m_pHead;
    while (baseListHeplCell != nullptr) {
        // Implies the == operator has been implemented in the class' object we
        // want to compare.
        if (val == *(baseListHeplCell->getValue())) {
            return true;
        }
        baseListHeplCell = baseListHeplCell->getNext();
    }

    return false;
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
std::ostream& operator<<(std::ostream& lhs, const HeplBaseList<T>& rhs) {

    lhs << "[ ";

    HeplCell<T> *baseListHeplCell = rhs.m_pHead;
    while (baseListHeplCell != nullptr) {
        lhs << baseListHeplCell->getValue();
        baseListHeplCell = baseListHeplCell->getNext();
        if (baseListHeplCell != nullptr) {
            lhs << ", ";
        }
    }

    lhs << " ]";

    return lhs;
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

template<class T>
const T& HeplBaseList<T>::operator[](size_t itemNumber) const {
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
