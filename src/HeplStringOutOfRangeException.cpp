#include "HeplStringOutOfRangeException.hpp"

HeplStringOutOfRangeException::HeplStringOutOfRangeException() {
}

HeplStringOutOfRangeException::HeplStringOutOfRangeException(const HeplString& msg)
    : msg(msg) {
}

HeplStringOutOfRangeException::HeplStringOutOfRangeException(const char* msg)
    : msg(msg) {
}
