/*
    This is for Windows which helps alot for converting between std::string vs TCHAR strings.
*/

#ifdef OS_WINDOWS
//#if defined(_MSC_VER) || defined(__MINGW32__)

#ifndef TC_STRING_H
#define TC_STRING_H

#include <tchar.h>
#include <string>
#include <sstream>
#include <iomanip>

//TCHAR versions of std::string and std::ostringstream.
typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tc_string;
typedef std::basic_ostringstream< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tc_ostringstream;

tc_string str_to_tc(std::string m_arg_str);
std::string tc_to_str(tc_string m_arg_tc_str);

#endif

#endif
