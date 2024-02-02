#include <string>
#include <sstream>

// reference: http://www.c-jump.com/bcc/c155c/modules/cis155_Ch11a_format/L11_160_string_stream_and_flo.htm

std::string Formatter(double val, const char precision)
{
    std::stringstream ss;
    ss.precision(precision);
    ss << val;
    return ss.str();
}