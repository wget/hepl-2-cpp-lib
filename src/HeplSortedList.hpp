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

#include "HeplSortedList.ipp"

#endif // HEPLSORTEDLIST_HPP_DEFINED
