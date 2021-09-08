#include "HeplString.hpp"
#include "HeplStringOutOfRangeException.hpp"
#include "HeplList.hpp"
#include "HeplStack.hpp"

HeplString::HeplString()
    : m_stringArray(nullptr),
    m_size(0) {
#ifdef WITH_DEBUG
    std::cout << "In initialization constructor: HeplString::HeplString()" << std::endl;
#endif
}

HeplString::HeplString(const char *newString) {
#ifdef WITH_DEBUG
    std::cout << "In initialization constructor: HeplString::HeplString(const char *newString)" << std::endl;
#endif
    m_size = 0;
    if (!newString) {
        m_stringArray = new char[0];
        return;
    }
    while (newString[m_size] != '\0') {
        m_size++;
    }
    m_stringArray = new char[m_size + 1];
    size_t i = 0;
    for (i = 0; i < m_size; i++) {
        m_stringArray[i] = newString[i];
    }
    m_stringArray[m_size] = '\0';
}

HeplString::HeplString(const int number) {
#ifdef WITH_DEBUG
    std::cout << "In initialization constructor: HeplString::HeplString(int number)" << std::endl;
#endif
    itoaStringArray(number);
    reverse();
}

HeplString::HeplString(const HeplString& other) {
#ifdef WITH_DEBUG
    std::cout << "In copy constructor: HeplString::HeplString(HeplString const& other)" << std::endl;
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

HeplString::HeplString(HeplString* const other) {
#ifdef WITH_DEBUG
    std::cout << "In copy constructor: HeplString::HeplString(HeplString const& other)" << std::endl;
#endif
    m_size = other->m_size;
    m_stringArray = new char[m_size + 1];
    // We should have used memcpy here, but since it is contained in cstring,
    // we are prohibited to use it.
    for (size_t i = 0; i < m_size; i++) {
        m_stringArray[i] = other->m_stringArray[i];
    }
    m_stringArray[m_size] = '\0';
}

char *HeplString::c_str() const {
    return m_stringArray;
}

size_t HeplString::size() const {
    return m_size;
}

bool HeplString::empty() const {
    return (m_size == 0) ? true: false;
}
    
HeplString::~HeplString() {
#ifdef WITH_DEBUG
    std::cout << "In destructor: HeplString::~HeplString()" << std::endl;
#endif
    if (m_stringArray != nullptr) {
        delete[] m_stringArray;
    }
}

const HeplString& HeplString::operator=(const HeplString& rhs) {
    // Avoid copy when assigned to same object.
    if (this == &rhs) {
        return *this;
    }
    delete[] m_stringArray;
    m_stringArray = new char[rhs.m_size + 1];
    for (size_t i = 0; i < rhs.m_size; i++) {
        m_stringArray[i] = rhs.m_stringArray[i];
    }
    m_size = rhs.m_size;
    m_stringArray[m_size] = '\0';

    return *this;
}

const HeplString& HeplString::operator+=(const HeplString& rhs) {

    char *oldStringArray = m_stringArray;
    m_stringArray = new char[m_size + rhs.m_size + 1];

    // Copy existing string to new memory space
    for (size_t i = 0; i < m_size; i++) {
        m_stringArray[i] = oldStringArray[i];
    }

    delete[] oldStringArray;

    // Copy rhs rvalue string to same new memory space
    for (size_t j = 0; j < rhs.m_size; j++) {
        m_stringArray[m_size + j] = rhs.m_stringArray[j];
    }

    m_stringArray[m_size + rhs.m_size] = '\0';

    m_size += rhs.m_size;

    return *this;
}

const HeplString& HeplString::operator+=(const char *rhs) {
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

HeplString HeplString::operator+(const int rhs) {
    HeplString newString(*this);
    newString += HeplString(rhs);
    return newString;
}

char HeplString::operator[](const size_t i) const {
    if (i >= m_size) {
        throw 1;
    }
    return m_stringArray[i];
}

char& HeplString::operator[](const size_t i) {
    if (i >= m_size) {
        throw 1;
    }
    return m_stringArray[i];
}

bool HeplString::operator==(HeplString const& rhs) const {
    if (size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < size(); i++) {
        if (m_stringArray[i] != rhs.m_stringArray[i]) {
            return false;
        }
    }
    return true;
}

bool HeplString::operator==(const char& rhs) const {
    if (size() > 1) {
        return false;
    }

    if (m_stringArray[0] == rhs) {
        return true;
    }
    return false;
}

bool HeplString::operator!=(const HeplString& rhs) const {
    return !(*this == rhs);
}

bool HeplString::operator>(const HeplString& rhs) const {
    if (size() > rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator<(const HeplString& rhs) const {
    if (size() < rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator>=(const HeplString& rhs) const {
    if (size() >= rhs.size()) {
        return true;
    }
    return false;
}

bool HeplString::operator<=(const HeplString& rhs) const {
    if (size() <= rhs.size()) {
        return true;
    }
    return false;
}

const HeplString& HeplString::operator<<(const HeplString& rhs) {
    return HeplString(*this) += rhs;
}

HeplString operator+(const char *lhs, const HeplString& rhs) {
    return HeplString(lhs) += rhs;
}

HeplString operator<<(const char *lhs, const HeplString& rhs) {
    return HeplString(lhs) += rhs;
}

std::ostream& operator<<(std::ostream& lhs, const HeplString& rhs) {
    for (size_t i = 0; i < rhs.m_size; i++) {
        lhs << rhs.m_stringArray[i];
    }
    return lhs;
}

const std::istream& operator>>(std::istream& lhs, HeplString& rhs) {

    // istream is not like fstream, we cannot read back in the stream, reading
    // is destructive, so using a linked list seems mandatory here (or smarter,
    // a stack :p)
    HeplStack<char> stack;
    char charRead;
    char charReadPrevious;
    while (lhs.get(charRead)) {

        // We need to detect \r\n (DOS) and \n (UNIX)
        if (charRead == '\n') {
            if (charReadPrevious == '\r') {
                stack.pop();
            }
            break;
        }

        stack.push(charRead);
        charReadPrevious = charRead;
    }

    size_t i = stack.getNumberItems();

    // We cannot detect based on the payload or the nullptr because of the CRLF
    // detection from above
    char *newArrayList = new char[i + 1];
    for (size_t j = 0; j < i; j++) {
        newArrayList[j] = stack.pop();
    }
    newArrayList[i] = '\0';

    // The \0 end of string is copied to the constructor
    HeplString string(newArrayList);
    delete[] newArrayList;

    // We reverse the string because of the usage of the stack we used before
    // whose pop() processes values in LIFO.
    rhs = string.reverse();

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

HeplString HeplString::itoa(const int n) const {
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
// src.: https://stackoverflow.com/a/16575025/3514658
bool HeplString::isNumber() const {
    char* p;
    strtod(m_stringArray, &p);
    return *p == 0;
}

HeplString& HeplString::reverse() {
    size_t halfSize = m_size / 2;
    char temp;
    for (size_t i = 0; i < halfSize; i++) {
        temp = m_stringArray[i];
        m_stringArray[i] = m_stringArray[m_size - 1 - i];
        m_stringArray[m_size - 1 - i] = temp;
    }
    return *this;
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

HeplList<HeplString> HeplString::explode(const HeplString& delimiter, int limit) {

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

void HeplString::save(std::ofstream& out) const {
    out.write((char*)&m_size, sizeof(m_size));
    out.write((char*)m_stringArray, m_size);
}

void HeplString::load(std::ifstream& in) {
    in.read((char*)&m_size, sizeof(m_size));
    m_stringArray = new char[m_size];
    in.read((char*)m_stringArray, m_size);
}
