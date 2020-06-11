#ifndef BASELISTITERATOR_HPP_INCLUDED
#define BASELISTITERATOR_HPP_INCLUDED

#include <cstddef>
#include "HeplBaseList.hpp"
#include "HeplList.hpp"
#include "HeplSortedList.hpp"
#include "HeplCell.hpp"

template<class T>
class HeplBaseListIterator {

    private:
        HeplBaseList<T>& m_list;
        HeplCell<T> *m_currentCell;

    public:
        HeplBaseListIterator(HeplBaseList<T>& list);
        bool end() const;
        void reset();
        bool operator++();
        bool operator++(int);
        operator T() const;
        T* operator&(void);
        T* operator*(void);
        T remove();
};

template<class T>
HeplBaseListIterator<T>::HeplBaseListIterator(HeplBaseList<T>& list)
    : m_list(list), m_currentCell(list.m_pHead) {
}

template<class T>
bool HeplBaseListIterator<T>::end() const {
    return m_currentCell == nullptr ? true : false;
}

template<class T>
void HeplBaseListIterator<T>::reset() {
    m_currentCell = m_list.m_pHead;
}

template<class T>
bool HeplBaseListIterator<T>::operator++() {
    if (m_currentCell == nullptr) {
        return false;
    }

    m_currentCell = m_currentCell->getNext();
    return true;
}

template<class T>
bool HeplBaseListIterator<T>::operator++(int) {
    return operator++();
}

template<class T>
HeplBaseListIterator<T>::operator T() const {
    return *(m_currentCell->getValue());
}

template<class T>
T* HeplBaseListIterator<T>::operator&(void) {
    return m_currentCell->getValue();
}

template<class T>
T* HeplBaseListIterator<T>::operator*(void) {
    return m_currentCell->getValue();
}

template<class T>
T HeplBaseListIterator<T>::remove() {
    HeplCell<T> *cell = m_list.m_pHead;
    HeplCell<T> *previousCell = m_list.m_pHead;
    while (cell != nullptr) {
        if (*(cell->getValue()) == *(m_currentCell->getValue())) {
            previousCell->setNext(cell->getNext());
            T cellValue = *(m_currentCell->getValue());
            (*this)++;
            delete cell;
            return cellValue;
        }
        previousCell = cell;
        cell = cell->getNext();
    }

    HeplCell<T> newCell;
    return *(newCell.getValue());
}

#endif // BASELISTITERATOR_HPP_INCLUDED
