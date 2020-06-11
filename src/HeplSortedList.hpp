#ifndef HEPLSORTEDLIST_HPP_DEFINED
#define HEPLSORTEDLIST_HPP_DEFINED

#include <cstddef>
#include "HeplBaseList.hpp"
#include "HeplCell.hpp"

template<class T>
class HeplSortedList: public HeplBaseList<T> {

    public:
        // Default constructor and copy constructor are automatically
        // inherited.

        T* add(T const& val);
};

template<class T>
T* HeplSortedList<T>::add(T const& val) {

    HeplCell<T> *newHeplCell = new HeplCell<T>();
    newHeplCell->setValue(val);
    newHeplCell->setNext(nullptr);

    // If this is the very first item in the list (the list is currently empty)
    if (HeplBaseList<T>::m_pHead == nullptr) {
        HeplBaseList<T>::m_pHead = newHeplCell;
        return newHeplCell->getValue();
    }

    // If below than the first list item
    if (val <= *(HeplBaseList<T>::m_pHead->getValue())) {
        newHeplCell->setNext(HeplBaseList<T>::m_pHead);
        HeplBaseList<T>::m_pHead = newHeplCell;
        return newHeplCell->getValue();
    }

    // Iterate if greater
    HeplCell<T> *listHeplCell = HeplBaseList<T>::m_pHead;
    HeplCell<T> *listHeplCellPrevious = HeplBaseList<T>::m_pHead;
    while (listHeplCell->getNext() != nullptr && val > *(listHeplCell->getValue())) {
        listHeplCellPrevious = listHeplCell;
        listHeplCell = listHeplCell->getNext();
    }

    if (val > *(listHeplCell->getValue())) {
        listHeplCell->setNext(newHeplCell);
        return newHeplCell->getValue();
    }

    listHeplCellPrevious->setNext(newHeplCell);
    newHeplCell->setNext(listHeplCell);

    return newHeplCell->getValue();
}

#endif // HEPLSORTEDLIST_HPP_DEFINED
