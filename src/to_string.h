#ifndef TO_STRING_H
#define TO_STRING_H

#ifdef OS_WINDOWS
//#if defined(_MSC_VER) || defined(__MINGW32__)
#include "tc_string.h"
#endif

#include <string>
#include <iomanip>
#include <sstream>

//Number to std string convert & formatting routines..

template<class T>
std::string to_string(const T& m_arg_source)
{
    std::ostringstream m_oss;

    m_oss << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string(const T& m_arg_source, std::ios_base::fmtflags m_arg_fmtfl)
{
    std::ostringstream m_oss;

    m_oss << std::setiosflags(m_arg_fmtfl) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string(const T& m_arg_source, std::ios_base::fmtflags m_arg_fmtfl, int m_arg_prec, int m_arg_width, char m_arg_fill_char, int m_arg_base)
{
    std::ostringstream m_oss;

    m_oss << std::setiosflags(m_arg_fmtfl) << std::setprecision(m_arg_prec) << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << std::setbase(m_arg_base) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_left(const T& m_arg_source, int m_arg_width, char m_arg_fill_char)
{
    std::ostringstream m_oss;

    m_oss << std::left << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_prec(const T& m_arg_source, int m_arg_prec)
{
    std::ostringstream m_oss;

    m_oss << std::setprecision(m_arg_prec) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_prec(const T& m_arg_source, int m_arg_prec, std::ios_base::fmtflags m_arg_fmtfl)
{
    std::ostringstream m_oss;

    m_oss << std::setprecision(m_arg_prec) << std::setiosflags(m_arg_fmtfl) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_fixed(const T& m_arg_source, int m_arg_prec)
{
    std::ostringstream m_oss;

    m_oss << std::fixed << std::setprecision(m_arg_prec) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_fixed(const T& m_arg_source, int m_arg_prec, int m_arg_width, char m_arg_fill_char)
{
    std::ostringstream m_oss;

    m_oss << std::fixed << std::left << std::setprecision(m_arg_prec) << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_right(const T& m_arg_source)
{
    std::ostringstream m_oss;

    m_oss << std::right << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_right(const T& m_arg_source, int m_arg_width, char m_arg_fill_char)
{
    std::ostringstream m_oss;

    m_oss << std::right << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_right_hex(const T& m_arg_source, int m_arg_width, char m_arg_fill_char)
{
    std::ostringstream m_oss;

    m_oss << std::right << std::hex << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
std::string to_string_right_hex_up(const T& m_arg_source, int m_arg_width, char m_arg_fill_char)
{
    std::ostringstream m_oss;

    m_oss << std::right << std::hex << std::uppercase << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

//TCHAR versions.

#ifdef OS_WINDOWS
//#if defined(_MSC_VER) || defined(__MINGW32__)

//Number to tc_string convert & formatting routines..

template<class T>
tc_string to_tc_string(const T& m_arg_source)
{
    tc_ostringstream m_oss;

    m_oss << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string(const T& m_arg_source, std::ios_base::fmtflags m_arg_fmtfl)
{
    tc_ostringstream m_oss;

    m_oss << std::setiosflags(m_arg_fmtfl) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string(const T& m_arg_source, std::ios_base::fmtflags m_arg_fmtfl, int m_arg_prec, int m_arg_width, char m_arg_fill_char, int m_arg_base)
{
    tc_ostringstream m_oss;

    m_oss << std::setiosflags(m_arg_fmtfl) << std::setprecision(m_arg_prec) << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << std::setbase(m_arg_base) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_left(const T& m_arg_source, int m_arg_width, TCHAR m_arg_fill_char)
{
    tc_ostringstream m_oss;

    m_oss << std::left << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_prec(const T& m_arg_source, int m_arg_prec)
{
    tc_ostringstream m_oss;

    m_oss << std::setprecision(m_arg_prec) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_prec(const T& m_arg_source, int m_arg_prec, std::ios_base::fmtflags m_arg_fmtfl)
{
    tc_ostringstream m_oss;

    m_oss << std::setprecision(m_arg_prec) << std::setiosflags(m_arg_fmtfl) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_fixed(const T& m_arg_source, int m_arg_prec)
{
    tc_ostringstream m_oss;

    m_oss << std::fixed << std::setprecision(m_arg_prec) << m_arg_source;

    return m_oss.str();
};


template<class T>
tc_string to_tc_string_fixed(const T& m_arg_source, int m_arg_prec, int m_arg_width, TCHAR m_arg_fill_char)
{
    tc_ostringstream m_oss;

    m_oss << std::fixed << std::left << std::setprecision(m_arg_prec) << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_right(const T& m_arg_source)
{
    tc_ostringstream m_oss;

    m_oss << std::right << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_right(const T& m_arg_source, int m_arg_width, TCHAR m_arg_fill_char)
{
    tc_ostringstream m_oss;

    m_oss << std::right << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

template<class T>
tc_string to_tc_string_right_hex_up(const T& m_arg_source, int m_arg_width, TCHAR m_arg_fill_char)
{
    tc_ostringstream m_oss;

    m_oss << std::right << std::hex << std::uppercase << std::setw(m_arg_width) << std::setfill(m_arg_fill_char) << m_arg_source;

    return m_oss.str();
};

#endif

#endif
