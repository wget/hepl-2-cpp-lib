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
        char *m_stringArray;
        // The class does not have a zero end string character. Only char
        // arrays passed as argument to this string constructor have it, but
        // are not taken into account to make the string array internal.
        size_t m_size;
        void itoaStringArray(int n);
        void kmpBuildFailureFunction(HeplString pattern, int f[]);

    public:
        // Constructors/destructors
        HeplString();
        HeplString(const char *newString);
        HeplString(int number);
        HeplString(const HeplString& other);
        HeplString(HeplString* other);
        ~HeplString();

        // Other methods
        char *c_str() const;
        size_t size() const;
        bool empty() const;
        HeplString itoa(int n);
        int atoi() const;
        HeplString ftoa(float f, int afterpoint = 4);
        bool isNumber() const;
        void reverse();
        void clear();
        HeplString substr(size_t pos = 0, size_t len = -1) const;
        HeplList<HeplString> explode(HeplString delimiter, int limit = 0);

        // Operators
        HeplString& operator=(const HeplString& rhs);
        HeplString& operator+=(const HeplString& rhs);
        HeplString& operator+=(const char *rhs);
        HeplString operator+(const HeplString& rhs);
        HeplString operator+(const char *rhs);
        HeplString operator+(int rhs);
        char operator[](size_t i) const;
        char& operator[](size_t i);
        bool operator==(HeplString const& rhs) const;
        bool operator!=(HeplString const& rhs) const;
        bool operator<(HeplString const& rhs) const;
        bool operator>(HeplString const& rhs) const;
        bool operator<=(HeplString const& rhs) const;
        bool operator>=(HeplString const& rhs) const;

        // Stream management
        HeplString& operator<<(HeplString const& rhs);
        friend HeplString operator+(const char *lhs, const HeplString& rhs);
        friend HeplString& operator<<(const char *lhs, const HeplString& rhs);
        friend std::ostream& operator<<(std::ostream& lhs, const HeplString& rhs);
        friend std::istream& operator>>(std::istream& lhs, HeplString& rhs);
        void save(std::ofstream& out) const;
        void load(std::ifstream& in);
};

#endif // HEPLSTRING_HPP_INCLUDED
