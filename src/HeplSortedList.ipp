template<class T>
T* HeplSortedList<T>::add(T const& val) {

    T *newVal = new T(val);
    HeplCell<T> *newHeplCell = new HeplCell<T>();
    newHeplCell->setValue(*newVal);
    newHeplCell->setNext(nullptr);

    if (HeplBaseList<T>::m_pHead == nullptr) {
        HeplBaseList<T>::m_pHead = newHeplCell;
        return newVal;
    }

    if (*newVal <= *(HeplBaseList<T>::m_pHead->getValue())) {
        newHeplCell->setNext(HeplBaseList<T>::m_pHead);
        HeplBaseList<T>::m_pHead = newHeplCell;
        return newVal;
    }

    HeplCell<T> *listHeplCell = HeplBaseList<T>::m_pHead;
    HeplCell<T> *listHeplCellPrevious = HeplBaseList<T>::m_pHead;
    while (listHeplCell->getNext() != nullptr && val > *(listHeplCell->getValue())) {
        listHeplCellPrevious = listHeplCell;
        listHeplCell = listHeplCell->getNext();
    }

    if (val > *(listHeplCell->getValue())) {
        listHeplCell->setNext(newHeplCell);
        return newVal;
    }

    listHeplCellPrevious->setNext(newHeplCell);
    newHeplCell->setNext(listHeplCell);

    return newVal;
}
