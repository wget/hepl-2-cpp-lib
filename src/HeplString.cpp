#include "HeplString.hpp"
#include "HeplStringOutOfRangeException.hpp"
#include "HeplList.hpp"

using namespace std;

HeplString::HeplString()
    : m_stringArray(nullptr),
    m_size(0) {
#ifdef WITH_DEBUG
    cout << "In initialization constructor: HeplString::HeplString()" << endl;
#endif
}

HeplString::HeplString(const char *newString) {
#ifdef WITH_DEBUG
    cout << "In initialization constructor: HeplString::HeplString(const char *newString)" << endl;
#endif
    if (!newString) {
        m_size = 0;
        m_stringArray = new char[0];
        return;
    }
    size_t i = 0;
    while (newString[i] != '\0') {
        i++;
    }
    m_size = i;
    m_stringArray = new char[m_size + 1];
    for (i = 0; i < m_size; i++) {
        m_stringArray[i] = newString[i];
    }
    m_stringArray[m_size] = '\0';
}

HeplString::HeplString(int number) {
#ifdef WITH_DEBUG
    cout << "In initialization constructor: HeplString::HeplString(int number)" << endl;
#endif
    itoaStringArray(number);
    reverse();
}

HeplString::HeplString(const HeplString& other) {
#ifdef WITH_DEBUG
    cout << "In copy constructor: HeplString::HeplString(HeplString const& other)" << endl;
#endif
    m_size = other.m_size;
    m_stringArray = new char[m_size + 1];
    // We should have used memcpy here, but since it is contained in cstring,
    // we are prohibited to use it.
    for (size_t i = 0; i < other.m_size; i++) {
        m_stringArray[i] = other.m_stringArray[i];
    }
    m_stringArray[m_size] = '\0';
}

HeplString::HeplString(HeplString* other) {
#ifdef WITH_DEBUG
    cout << "In copy constructor: HeplString::HeplString(HeplString const& other)" << endl;
#endif
    m_size = other->m_size;
    m_stringArray = new char[m_size];
    // We should have used memcpy here, but since it is contained in cstring,
    // we are prohibited to use it.
    for (size_t i = 0; i < other->m_size; i++) {
        m_stringArray[i] = other->m_stringArray[i];
    }
}

char *HeplString::c_str() const {
    return m_stringArray;
}

size_t HeplString::size() const {
    return m_size;
}

bool HeplString::empty() const {
    return (m_size == 0)? true: false;
}
    
HeplString::~HeplString() {
#ifdef WITH_DEBUG
    cout << "In destructor: HeplString::~HeplString()" << endl;
#endif
    if (m_stringArray != nullptr) {
        delete[] m_stringArray;
    }
}

HeplString& HeplString::operator=(const HeplString& rhs) {
    // Avoid copy when assigned to same object.
    if (this == &rhs) {
        return *this;
    }
    delete[] m_stringArray;
    m_stringArray = new char[rhs.m_size];
    for (size_t i = 0; i < rhs.m_size; i++) {
        m_stringArray[i] = rhs.m_stringArray[i];
    }
    m_size = rhs.m_size;

    return *this;
}

HeplString& HeplString::operator+=(const HeplString& rhs) {

    char *oldStringArray = m_stringArray;
    m_stringArray = new char[m_size + rhs.m_size];
    size_t i = 0;
    // Copy existing string to new memory space
    while (i < m_size) {
        m_stringArray[i] = oldStringArray[i];
        i++;
    }
    delete[] oldStringArray;

    // Copy rhs rvalue string to same new memory space
    for (size_t j = 0; j < rhs.m_size; j++) {
        m_stringArray[i + j] = rhs.m_stringArray[j];
    }

    m_size += rhs.m_size;

    return *this;
}

HeplString& HeplString::operator+=(const char *rhs) {
    HeplString rhsString(rhs);
    *this += rhsString;
    return *this;
}

HeplString HeplString::operator+(const HeplString& rhs) {
    HeplString newString(*this);
    newString += rhs;
    return newString;
}

HeplString HeplString::operator+(const char *rhs) {
    HeplString newString(*this);
    newString += rhs;
    return newString;
}

HeplString HeplString::operator+(int rhs) {
    HeplString newString(*this);
    newString += HeplString(rhs);
    return newString;
}

char HeplString::operator[](size_t i) const {
    if (i >= m_size) {
        throw 1;
    }
    return m_stringArray[i];
}

char& HeplString::operator[](size_t i) {
    if (i >= m_size) {
        throw 1;
    }
    return m_stringArray[i];
}

bool HeplString::operator==(HeplString const& rhs) const {
    if (size() == rhs.size()) {
        for (size_t i = 0; i < size(); i++) {
            if (m_stringArray[i] != rhs.m_stringArray[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool HeplString::operator!=(HeplString const& rhs) const {
    return !(*this == rhs);
}

bool HeplString::operator>(HeplString const& rhs) const {
    if (size() > rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator<(HeplString const& rhs) const {
    if (size() < rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator>=(HeplString const& rhs) const {
    if (size() >= rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator<=(HeplString const& rhs) const {
    if (size() <= rhs.size()) {
        return true;
    }
    return false;
}

HeplString& HeplString::operator<<(const HeplString& rhs) {
    return HeplString(*this) += rhs;
}

HeplString operator+(const char *lhs, const HeplString& rhs) {
    return HeplString(lhs) += rhs;
}

HeplString& operator<<(const char *lhs, const HeplString& rhs) {
    return HeplString(lhs) += rhs;
}

ostream& operator<<(ostream& lhs, const HeplString& rhs) {
    for (size_t i = 0; i < rhs.m_size; i++) {
        lhs << rhs.m_stringArray[i];
    }
    return lhs;
}

istream& operator>>(istream& lhs, HeplString& rhs) {
    // Structures inside functions are new since c++11.
    struct LinkedChar {
        char payload;
        LinkedChar *pNext;
    };
    LinkedChar *linkedChar = new LinkedChar();
    LinkedChar *linkedCharStart = linkedChar;
    // istream is not like fstream, we cannot read back in the stream, reading
    // is destructive, so using a linked list seems mandatory here.
    char charRead;
    while (lhs.get(charRead) && charRead != '\n') {
        linkedChar->payload = charRead;
        linkedChar->pNext = new LinkedChar();
        linkedChar = linkedChar->pNext;
    }
    linkedChar->payload = '\0';
    linkedChar->pNext = nullptr;

    // Count number of characters
    linkedChar = linkedCharStart;
    size_t size = 0;
    while (linkedChar != nullptr) {
        linkedChar = linkedChar->pNext;
        size++;
    }

    linkedChar = linkedCharStart;
    char *newArrayList = new char[size];
    for (size_t i = 0; linkedChar != nullptr; i++) {
        newArrayList[i] = linkedChar->payload;
        linkedChar = linkedChar->pNext;
    }

    // Delete linked list
    linkedChar = linkedCharStart;
    linkedCharStart = nullptr;
    LinkedChar *linkedCharCurrent = nullptr;
    while (linkedChar != nullptr) {
        linkedCharCurrent = linkedChar;
        linkedChar = linkedChar->pNext;
        delete linkedCharCurrent;
    }
    linkedChar = nullptr;

    // The \0 end of string is copied to the constructor
    HeplString string(newArrayList);
    rhs = string;
    return lhs;
}

void HeplString::itoaStringArray(int n) {
    int i, sign, nBack;

    // Keep track of sign
    if ((sign = n) < 0) {
        // Force abs of number
        n = -n;
    }
    nBack = n;
    i = 0;
    /* generate digits in reverse order */
    // Count number of digits
    do {
        i++;
    } while ((n /= 10) > 0);

    m_size = i;
    // Increase size for negative sign
    if (sign < 0) {
        m_size++;
    }
    m_stringArray = new char[m_size];

    i = 0;
    do {
        // Get next digit
        m_stringArray[i++] = nBack % 10 + '0';
    } while ((nBack /= 10) > 0);

    // Recover sign
    if (sign < 0) {
        m_stringArray[i++] = '-';
    }
}

HeplString HeplString::itoa(int n) {
    HeplString newString;
    newString.itoaStringArray(n);
    newString.reverse();
    return newString;
}

int HeplString::atoi() const {

    int integer = 0;
    int sign = 1;
    size_t i = 0;

    if (m_stringArray[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Inspiration taken from https://stackoverflow.com/q/28919861/3514658 for
    // the algorithmic part.
    while (i < m_size) {
        integer = integer * 10 + m_stringArray[i] - '0';
        i++;
    }

    integer *= sign;
    return integer;
}

HeplString HeplString::ftoa(float f, int afterpoint) {
    // Extract integer part
    float ipart = (int)f;

    // Extract floating part
    float fpart = f - ipart;

    HeplString string = itoa(ipart);

    if (fpart != 0) {
        string += ".";
        fpart = fpart * pow(10, afterpoint);
        string += itoa(fpart);
    }
    *this = string;
    return string;
}

// src.: http://www.cplusplus.com/reference/cctype/isdigit/
bool HeplString::isNumber() const {
    for (unsigned int i = 0; i < m_size; i++) {
        if (m_stringArray[i] < 48 || m_stringArray[i] > 57) {
            return false;
        }
    }
    return true;
}

void HeplString::reverse() {
    size_t halfSize = m_size / 2;
    char temp;
    for (size_t i = 0; i < halfSize; i++) {
        temp = m_stringArray[i];
        m_stringArray[i] = m_stringArray[m_size - 1 - i];
        m_stringArray[m_size - 1 - i] = temp;
    }
}

void HeplString::clear() {
    delete[] m_stringArray;
    m_stringArray = nullptr;
    m_size = 0;
}

HeplString HeplString::substr(size_t pos, size_t len) const {
    if (pos == m_size) {
        return *this;
    }

    if (pos > m_size) {
        throw HeplStringOutOfRangeException();
    }

    if (len > m_size - pos) {
        throw HeplStringOutOfRangeException();
    }

    char *newStringArray = new char[m_size - pos + 1];
    size_t i = 0;
    while (i < len) {
        newStringArray[i] = m_stringArray[pos];
        pos++;
        i++;
    }
    newStringArray[i] = '\0';

    return HeplString(newStringArray);
}

// Inspiration for the reference to the int array taken from:
// https://www.sanfoundry.com/cpp-program-implement-kruth-morris-patt-algorithm-kmp/
// Algorithm ported from a previous implementation I made in pure Bash
// scripting:
// https://github.com/wget/shut/blob/master/utils.sh
void HeplString::kmpBuildFailureFunction(HeplString pattern, int f[]) {

    if (!pattern.size()) {
        f[0] = -1;
        return;
    }

    size_t i = 0;
    size_t j = 0;
    size_t len = pattern.size();

    f[0] = 0;
    f[1] = 0;

    for (i = 2; i < len; i++) {

        j = f[i - 1];
        while (true) {

            if (pattern[j] == pattern[i - 1]) {
                f[i] = j + 1;
                break;
            }

            if (j == 0) {
                f[i] = 0;
            }

            j = f[j];
        }
    }
}

HeplList<HeplString> HeplString::explode(HeplString delimiter, int limit) {

    HeplList<HeplString> explodedList;

    if (!delimiter.size()) {
        explodedList.add(HeplString(*this));
        return explodedList;
    }

    enum ExplodeLimit { NO_LIMIT, POSITIVE, NEGATIVE };
    ExplodeLimit explodeLimit;
    if (limit < 0) {
        explodeLimit = ExplodeLimit::NEGATIVE;
        limit += -2 * limit;
        limit--;
    } else if (limit == 0) {
        explodeLimit = ExplodeLimit::NO_LIMIT;
    } else {
        explodeLimit = ExplodeLimit::POSITIVE;
    }

    size_t n = size();
    size_t m = delimiter.size();
    if (m > n) {
        explodedList.add(HeplString(*this));
        return explodedList;
    }

    int f[m];
    kmpBuildFailureFunction(delimiter, f);
    size_t i = 0;
    size_t j = 0;
    size_t matchLoc = 0;
    size_t numberOfMatch = 0;

    while (true) {

        if (j == n) {
            explodedList.add(this->substr(matchLoc, j - matchLoc));
            break;
        }

        if (m_stringArray[j] == delimiter.c_str()[i]) {
            i++;
            j++;
            if (i == m) {
                explodedList.add(this->substr(matchLoc, j - i - matchLoc));
                matchLoc = j;
                numberOfMatch++;
            }
        } else if (i > 0) {
            i = f[i];
        } else {
            j++;
        }
    }

    if (explodeLimit == ExplodeLimit::NO_LIMIT) {
        return explodedList;
    }

    i = 0;
    HeplList<HeplString> toKeepList;

    for (i = 0; i < explodedList.getNumberItems(); i++) {
        toKeepList.add(HeplString(explodedList[i]));
    }

    if (explodeLimit == ExplodeLimit::POSITIVE) {
        if ((size_t)limit >= explodedList.getNumberItems()) {
            return explodedList;
        }
        toKeepList[i - 1] = HeplString(explodedList[limit - 1]) + this->substr(matchLoc - m);
    }

    return toKeepList;
}

void HeplString::save(ofstream& out) const {
    out.write((char*)&m_size, sizeof(m_size));
    out.write((char*)m_stringArray, m_size);
}

void HeplString::load(ifstream& in) {
    in.read((char*)&m_size, sizeof(m_size));
    m_stringArray = new char[m_size];
    in.read((char*)m_stringArray, m_size);
}
