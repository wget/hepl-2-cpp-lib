#ifndef HEPLSTRING_HPP_INCLUDED
#define HEPLSTRING_HPP_INCLUDED

// For check against NULL
#include <cstddef>
#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>

template<class T>
class HeplList;

class HeplString {

    private:
        // For ease of use, we **are** storing a null string ending character.
        char *m_stringArray;
        // The size is returning the number of chars **without** taking into
        // account the null string ending character.
        size_t m_size;
        void itoaStringArray(int n);
        void kmpBuildFailureFunction(HeplString pattern, int f[]);

    public:
        // Constructors/destructors
        HeplString();
        HeplString(const char *newString);
        HeplString(const int number);
        HeplString(const HeplString& other);
        HeplString(HeplString* const other);
        ~HeplString();

        // Other methods
        char *c_str() const;
        size_t size() const;
        bool empty() const;
        HeplString itoa(const int n) const;
        int atoi() const;
        HeplString ftoa(const float f, const int afterpoint = 4);
        bool isNumber() const;
        HeplString& reverse();
        void clear();
        HeplString substr(const size_t pos = 0, const size_t len = -1) const;
        HeplList<HeplString> explode(const HeplString& delimiter, const int limit = 0);

        // Operators
        const HeplString& operator=(const HeplString& rhs);
        const HeplString& operator+=(const HeplString& rhs);
        const HeplString& operator+=(const char *rhs);
        HeplString operator+(const HeplString& rhs);
        HeplString operator+(const char *rhs);
        HeplString operator+(int rhs);
        char operator[](const size_t i) const;
        char& operator[](const size_t i);
        bool operator==(const HeplString& rhs) const;
        bool operator!=(const HeplString& rhs) const;
        bool operator<(const HeplString& rhs) const;
        bool operator>(const HeplString& rhs) const;
        bool operator<=(const HeplString& rhs) const;
        bool operator>=(const HeplString& rhs) const;

        // Stream management
        const HeplString& operator<<(const HeplString& rhs);
        friend HeplString operator+(const char *lhs, const HeplString& rhs);
        friend HeplString operator<<(const char *lhs, const HeplString& rhs);
        friend std::ostream& operator<<(std::ostream& lhs, const HeplString& rhs);
        friend const std::istream& operator>>(std::istream& lhs, HeplString& rhs);
        void save(std::ofstream& out) const;
        void load(std::ifstream& in);
};

#endif // HEPLSTRING_HPP_INCLUDED
