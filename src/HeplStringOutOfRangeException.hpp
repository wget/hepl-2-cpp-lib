#ifndef OUTOFRANGEEXCEPTION_HPP_INCLUDED
#define OUTOFRANGEEXCEPTION_HPP_INCLUDED

#include "HeplString.hpp"

// Inspiration taken from here:
// https://stackoverflow.com/a/8152888/3514658
// http://www.cplusplus.com/reference/stdexcept/out_of_range/
class HeplStringOutOfRangeException : public std::exception {

    protected:
        HeplString msg;

    public:
        HeplStringOutOfRangeException();
        HeplStringOutOfRangeException(const HeplString& msg);
        HeplStringOutOfRangeException(const char* msg);
};

#endif // OUTOFRANGEEXCEPTION_HPP_INCLUDED
