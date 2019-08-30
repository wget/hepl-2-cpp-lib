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

#include "HeplBaseListIterator.ipp"

#endif // BASELISTITERATOR_HPP_INCLUDED
