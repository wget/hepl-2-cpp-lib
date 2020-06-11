#ifndef HEPLLIST_HPP_INCLUDED
#define HEPLLIST_HPP_INCLUDED

#include <cstddef>
#include "HeplBaseList.hpp"
#include "HeplCell.hpp"

template<class T>
class HeplList : public HeplBaseList<T> {

    public:
        // Default constructor and copy constructor are automatically
        // inherited.

        T* add(const T& val);
};

template<class T>
T* HeplList<T>::add(const T& val) {

    HeplCell<T> *newHeplCell = new HeplCell<T>();
    newHeplCell->setValue(val);
    newHeplCell->setNext(nullptr);

    if (HeplBaseList<T>::m_pHead == nullptr) {
        HeplBaseList<T>::m_pHead = newHeplCell;
        return newHeplCell->getValue();
    }

    HeplCell<T> *listHeplCell = HeplBaseList<T>::m_pHead;
    HeplCell<T> *listHeplCellPrevious = nullptr;
    while (listHeplCell != nullptr) {
        listHeplCellPrevious = listHeplCell;
        listHeplCell = listHeplCell->getNext();
    }

    listHeplCellPrevious->setNext(newHeplCell);
    return newHeplCell->getValue();
}

#endif // HEPLLIST_HPP_INCLUDED
