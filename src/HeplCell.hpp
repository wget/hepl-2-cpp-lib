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

template<class T>
HeplCell<T>::HeplCell()
    : m_pNext(nullptr) {
}

template<class T>
HeplCell<T>::HeplCell(T value, HeplCell<T> *pNext)
    : m_value(value), m_pNext(pNext) {
}

// Needed to be a non const pointer for the add method in the list
template<class T>
T* HeplCell<T>::getValue() {
    return &m_value;
}

template<class T>
HeplCell<T>* HeplCell<T>::getNext() const {
    return m_pNext;
}

template<class T>
void HeplCell<T>::setValue(T newValue) {
    m_value = newValue;
}

template<class T>
void HeplCell<T>::setNext(HeplCell<T> *newNext) {
    m_pNext = newNext;
}

template<class T>
void HeplCell<T>::display() const {
    std::cout << m_value << std::endl;
}

#endif // CELL_HPP_INCLUDED
