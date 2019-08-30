#ifndef BASEEXCEPTION_HPP_INCLUDED
#define BASEEXCEPTION_HPP_INCLUDED

#include "HeplString.hpp"

class HeplBaseException {

    protected:
        HeplString msg;

    public:
        HeplBaseException();
        HeplBaseException(const HeplString& msg);
        HeplBaseException(const char* msg);
        HeplString what() const;
};

#endif // BASEEXCEPTION_HPP_INCLUDED
