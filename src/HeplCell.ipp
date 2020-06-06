template<class T>
HeplCell<T>::HeplCell()
    : m_pNext(nullptr) {
}

template<class T>
HeplCell<T>::HeplCell(T value, HeplCell<T> *pNext)
    : m_value(value), m_pNext(pNext) {
}

template<class T>
HeplCell<T>::~HeplCell() {
    delete m_pNext;
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
