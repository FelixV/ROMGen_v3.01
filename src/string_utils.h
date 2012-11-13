#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "my_types.h"
#include "to_string.h"
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

void str_chars_replace_to_HXX(std::string& m_arg_in_out_str, std::string m_arg_search_chars);
void str_replace_HXX_to_char(std::string& m_arg_in_out_str);
void str_chars_replace(std::string& m_arg_in_out_str, std::string m_arg_search_chars, std::string::size_type m_arg_rep_len, std::string m_arg_rep_str);
void str_chars_replace(std::string& m_arg_in_out_str, std::string m_arg_search_chars, std::string m_arg_rep_str);
void str_replace(std::string& m_arg_in_out_str, std::string m_arg_search_str, std::string::size_type m_arg_rep_len, std::string m_arg_rep_str);
void str_replace(std::string& m_arg_in_out_str, std::string m_arg_search_str, std::string m_arg_rep_str);
void stringsplit_empty(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters = " ");
void stringsplit(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters = " ");
void stringsplit_quoted(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters = " ", std::string m_arg_quote = "\"");
int nocase_cmp(std::string m_arg_str_1, std::string m_arg_str_2);
void to_upper_str(std::string& m_arg_in_out_str);
void to_lower_str(std::string& m_arg_in_out_str);
std::string buf_to_hex_str(const unsigned char* m_arg_buf, size_t m_arg_buf_len);

/*
    Uses istringstream to convert a string to a number integer value.

    Inputs:
        str = input string to convert
        base = 8, 10 or 16

    Examples:
    
        n = str_to_num<int>("a", 16);  //Converts hex string to decimal.
        n = str_to_num<int>("7", 10);  //Converts dec string to decimal.
*/
template<class T> T str_to_num(std::string m_arg_str, int m_arg_base = 10)
{
    T m_num;
    std::istringstream iss(m_arg_str);
    iss >> std::setbase(m_arg_base) >> m_num;

    return m_num;
}

//Converts number into a string prefixed with unit symbol: k, M, or G.
template<class T> std::string num_to_prefix_str(T m_arg_val)
{
    std::string m_str;
    long m_val_div;

    if(m_arg_val < 1024)
    {
        m_val_div = m_arg_val;
    }
    else
    if(m_arg_val < 1048576)
    {
        m_val_div = m_arg_val / 1024;
        m_str = "k";
    }
    else
    if(m_arg_val < 1073741824)
    {
        m_val_div = m_arg_val / 1048576;
        m_str = "M";
    }
    else
    {
        m_val_div = m_arg_val / 1073741824;
        m_str = "G";
    }

    m_str = to_string(m_val_div) + m_str;

    return m_str;
}

//Converts number into a string prefixed with unit symbol: kx, Mx, or Gx, where x = input symbol.
template<class T> std::string num_to_prefix_str(T m_arg_val, std::string m_arg_trailing_symbol)
{
    std::string m_str;
    long m_val_div;

    if(m_arg_val < 1024)
    {
        m_val_div = m_arg_val;
    }
    else
    if(m_arg_val < 1048576)
    {
        m_val_div = m_arg_val / 1024;
        m_str = "k";
    }
    else
    if(m_arg_val < 1073741824)
    {
        m_val_div = m_arg_val / 1048576;
        m_str = "M";
    }
    else
    {
        m_val_div = m_arg_val / 1073741824;
        m_str = "G";
    }

    m_str = to_string(m_val_div) + m_str + m_arg_trailing_symbol;

    return m_str;
}

#endif
