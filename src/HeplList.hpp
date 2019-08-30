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

#include "HeplList.ipp"

#endif // HEPLLIST_HPP_INCLUDED
