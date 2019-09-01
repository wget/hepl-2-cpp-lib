// #include "HeplList.hpp"
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
