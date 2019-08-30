template<class T>
HeplBaseList<T>::HeplBaseList()
    : m_pHead(nullptr) {
}

template<class T>
HeplBaseList<T>::HeplBaseList(HeplBaseList& baseList)
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
    size_t i = 0;
    while (baseListHeplCell != nullptr) {
        baseListHeplCell->display();
        baseListHeplCell = baseListHeplCell->getNext();
        i++;
    }
}

template<class T>
HeplBaseList<T>& HeplBaseList<T>::operator=(HeplBaseList const& baseList) {

    erase();
    if (baseList.m_pHead == nullptr) {
        return *this;
    }

    HeplCell<T> *newHeplCell = new HeplCell<T>();
    HeplCell<T> *newHeplCellStart = newHeplCell;
    HeplCell<T> *baseListHeplCell = baseList.m_pHead;

    while (baseListHeplCell != nullptr) {
        newHeplCell->setValue(*(baseListHeplCell->getValue()));
        if (baseListHeplCell->getNext() == nullptr) {
            newHeplCell->setNext(baseListHeplCell->getNext());
        } else {
            newHeplCell->setNext(new HeplCell<T>());
        }
        newHeplCell = newHeplCell->getNext();
        baseListHeplCell = baseListHeplCell->getNext();
    }
    m_pHead = newHeplCellStart;
    return *this;
}

template<class T>
T& HeplBaseList<T>::operator[](size_t itemNumber) {
    HeplCell<T> *baseListHeplCell = m_pHead;
    size_t i = 0;
    while (baseListHeplCell != nullptr && i != itemNumber) {
        baseListHeplCell = baseListHeplCell->getNext();
        i++;
    }

    if (baseListHeplCell == nullptr) {
        throw HeplBaseListItemNotFoundException();
    }
    return *(baseListHeplCell->getValue());
}
