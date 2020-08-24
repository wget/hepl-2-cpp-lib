#include "HeplBaseException.hpp"

HeplBaseException::HeplBaseException() {
}

HeplBaseException::HeplBaseException(const HeplString& msg)
    : msg(msg) {
}

HeplBaseException::HeplBaseException(const char* msg)
    : msg(msg) {
}

HeplString HeplBaseException::what() const {
    return msg;
}

std::ostream& operator<<(std::ostream& lhs, const HeplBaseException& rhs) {
    lhs << rhs.what();
    return lhs;
}
