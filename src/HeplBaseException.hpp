#ifndef BASEEXCEPTION_HPP_INCLUDED
#define BASEEXCEPTION_HPP_INCLUDED

#include <ostream>
#include "HeplString.hpp"

class HeplBaseException {

    protected:
        HeplString msg;

    public:
        HeplBaseException();
        HeplBaseException(const HeplString& msg);
        HeplBaseException(const char* msg);
        HeplString what() const;
        friend std::ostream& operator<<(std::ostream& lhs, const HeplBaseException& rhs);
};

#endif // BASEEXCEPTION_HPP_INCLUDED
