#include "string_utils.h"

/*
    Find any characters in the search string and replaces them to the form &HXX, where
    XX is ASCII code of character.

    Example:

    Replaces comma, colon and new line.

    str_chars_replace_to_HXX(m_arg_in_out_str, ",:\n");

    Before: m_arg_in_out_str = "Error: 01, 3746465ABC\nHello"
    After:  m_arg_in_out_str = "Error&H3A 01&H2C 3746465ABC&H0AHello"

    The example replaced the following characters:

    Character  ASCII code  Replaced with
    ,          0x3A        &H3A
    :          0x2C        &H2C
    \n         0x0A        &H0A

*/
void str_chars_replace_to_HXX(std::string& m_arg_in_out_str, std::string m_arg_search_chars)
{
    std::string::size_type m_pos = m_arg_in_out_str.find_first_of(m_arg_search_chars);

    while(m_pos != std::string::npos)
    {
        m_arg_in_out_str.replace(m_pos, 1, "&H" + to_string_right_hex_up((int)(m_arg_in_out_str.at(m_pos)), 2, '0'));
        m_pos = m_arg_in_out_str.find_first_of(m_arg_search_chars, m_pos + 4);
    }
}

void str_replace_HXX_to_char(std::string& m_arg_in_out_str)
{
    std::string::size_type m_pos;
    std::string m_hxx_val_str;
    long m_val;
    std::string m_val_str;
    BOOL m_convert_yn;

    //Find first.
    m_pos = m_arg_in_out_str.find("&H");

    //A valid position?
    while(m_pos != std::string::npos)
    {
        m_convert_yn = TRUE;

        //Check whether we should skip conversion.
        if(m_pos > 0)
        {
            if(m_arg_in_out_str.substr(m_pos - 1, 1) == "&")
            {
                m_convert_yn = FALSE;
                m_pos++;
            }
        }
        
        //Do conversion?
        if(m_convert_yn)
        {
            if((m_pos + 2) < m_arg_in_out_str.size())
            {
                m_hxx_val_str = m_arg_in_out_str.substr(m_pos + 2, 2);
            }
            else
            {
                m_hxx_val_str = m_arg_in_out_str.substr(m_pos + 2, m_arg_in_out_str.size());
            }
            m_val = strtol(m_hxx_val_str.c_str(), NULL, 16);
            m_val_str = (char)m_val;
            m_arg_in_out_str.replace(m_pos, m_hxx_val_str.size() + 2, m_val_str);
        }

        //Find next.
        m_pos = m_arg_in_out_str.find("&H", m_pos + 1);
    }
}

/*
    Find any characters in the search string and replaces them with the replacement string of specified length.

    Example:

    str_chars_replace(m_arg_in_out_str, ",:", 2, "abc");

    Before: m_arg_in_out_str = "Error: 01, 3746465ABC"
    After:  m_arg_in_out_str = "Errorab 01ab 3746465ABC"
*/
void str_chars_replace(std::string& m_arg_in_out_str, std::string m_arg_search_chars, std::string::size_type m_arg_rep_len, std::string m_arg_rep_str)
{
    std::string::size_type m_pos = m_arg_in_out_str.find_first_of(m_arg_search_chars);

    while(m_pos != std::string::npos)
    {
        m_arg_in_out_str.replace(m_pos, m_arg_rep_len, m_arg_rep_str);
        m_pos = m_arg_in_out_str.find_first_of(m_arg_search_chars, m_pos + m_arg_rep_str.size());
    }
}

/*
    Find any characters in the search string and replaces them with the replacement string.

    Example:

    str_chars_replace(m_arg_in_out_str, ",:", "abc");

    Before: m_arg_in_out_str = "Error: 01, 3746465ABC"
    After:  m_arg_in_out_str = "Errorabc 01abc 3746465ABC"
*/
void str_chars_replace(std::string& m_arg_in_out_str, std::string m_arg_search_chars, std::string m_arg_rep_str)
{
    str_chars_replace(m_arg_in_out_str, m_arg_search_chars, 1, m_arg_rep_str);
}

/*
    Find the search string and replaces with the replacement string of specified length.

    Example:

    str_replace(m_arg_in_out_str, "Dave", 5, "Chris Brown");

    Before: m_arg_in_out_str = "Hello Dave, and how are you Dave?"
    After:  m_arg_in_out_str = "Hello Chris, and how are you Chris?"
*/
void str_replace(std::string& m_arg_in_out_str, std::string m_arg_search_str, std::string::size_type m_arg_rep_len, std::string m_arg_rep_str)
{
    std::string::size_type m_pos = m_arg_in_out_str.find(m_arg_search_str);

    while(m_pos != std::string::npos)
    {
        m_arg_in_out_str.replace(m_pos, m_arg_rep_len, m_arg_rep_str);
        m_pos = m_arg_in_out_str.find(m_arg_search_str, m_pos + m_arg_rep_str.size());
    }
}

/*
    Find the search string and replaces with the replacement string.

    Example:

    str_replace(m_arg_in_out_str, "Dave", "Chris Brown");

    Before: m_arg_in_out_str = "Hello Dave, and how are you Dave?"
    After:  m_arg_in_out_str = "Hello Chris Brown, and how are you Chris Brown?"
*/
void str_replace(std::string& m_arg_in_out_str, std::string m_arg_search_str, std::string m_arg_rep_str)
{
    str_replace(m_arg_in_out_str, m_arg_search_str, m_arg_search_str.size(), m_arg_rep_str);
}

/*
    Splits (some call it tokenize) up a given string using any characters found in the given delimiter string.
    This version can create empty strings.

    Example:

    stringsplit_empty(m_arg_in_out_str, "\n\nHello", "\n");

    Above will tokenize into create 2 empty strings and 1 string with Hello.
*/
void stringsplit_empty(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters)
{
    //Find first non delimiter character position.
    std::string::size_type m_pos_1 = m_arg_str.find_first_not_of(m_arg_delimiters, 0);
    //Find first delimiter character position.
    std::string::size_type m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, 0);
    //Empty string.
    std::string m_empty_str;

    m_arg_out_substrs.clear();

    while((m_pos_1 != std::string::npos) || (m_pos_2 != std::string::npos))
    {
        if(m_pos_1 < m_pos_2)
        {
            //Found a sub string, add to list.
            m_arg_out_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_2 - m_pos_1));
            //Find next non delimiter character position.
            m_pos_1 = m_arg_str.find_first_not_of(m_arg_delimiters, m_pos_2);
        }
        else
        {
            //Found a sub string, but it is empty so add an empty string to list.
            m_arg_out_substrs.push_back(m_empty_str);
        }
        if(m_pos_2 != std::string::npos)
        {
            //Find next delimiter character position.
            m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_2 + 1);
        }
    }
}

/*
    Splits (some call it tokenize) up a given string using any characters found in the given delimiter string.
    This version does not create empty strings.

    Example:

    stringsplit(m_arg_in_out_str, "\n\nHello", "\n");

    Above will tokenize into 1 string containing Hello.
*/
void stringsplit(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters)
{
    //Find first non delimiter character position.
    std::string::size_type m_pos_1 = m_arg_str.find_first_not_of(m_arg_delimiters, 0);
    //Find first delimiter character position.
    std::string::size_type m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_1);

    m_arg_out_substrs.clear();

    while((m_pos_1 != std::string::npos) || (m_pos_2 != std::string::npos))
    {
        //Found a sub string, add it for output.
        m_arg_out_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_2 - m_pos_1));
        //Find next non delimiter character position.
        m_pos_1 = m_arg_str.find_first_not_of(m_arg_delimiters, m_pos_2);
        //Find next delimiter character position.
        m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_1);
    }
}

/*
    Splits (some call it tokenize) up a given string using any characters found in the given delimiter string.
    This version ignores delimiters inside the quoted string.
*/
void stringsplit_quoted(std::list<std::string>& m_arg_out_substrs, std::string m_arg_str, std::string m_arg_delimiters, std::string m_arg_quote)
{
    std::string m_delimiters_with_quote = m_arg_delimiters + m_arg_quote;
    //Find first non delimiter character position.
    std::string::size_type m_pos_1 = m_arg_str.find_first_not_of(m_delimiters_with_quote, 0);
    std::string::size_type m_pos_2;

    m_arg_out_substrs.clear();

    if(m_pos_1 != std::string::npos)
    {
        if(m_pos_1 > 0)
        {
            if(m_arg_str.substr(m_pos_1-1, 1).compare(m_arg_quote) == 0)
            {
                m_pos_2 = m_pos_1;
                //Find first non delimiter character position.
                m_pos_1 = m_arg_str.find_first_not_of(m_arg_quote, m_pos_2);
                //Find next delimiter character position.
                m_pos_2 = m_arg_str.find_first_of(m_arg_quote, m_pos_1);
            }
            else
            {
                //Find first delimiter character position.
                m_pos_2 = m_arg_str.find_first_of(m_delimiters_with_quote, m_pos_1);
            }
        }
        else
        {
            //Find first delimiter character position.
            m_pos_2 = m_arg_str.find_first_of(m_delimiters_with_quote, m_pos_1);
        }

        while((m_pos_1 != std::string::npos) || (m_pos_2 != std::string::npos))
        {
            //Found a sub string, add it for output.
            m_arg_out_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_2 - m_pos_1));
            //Find next non delimiter character position.
            m_pos_1 = m_arg_str.find_first_not_of(m_delimiters_with_quote, m_pos_2);
            if(m_pos_1 != std::string::npos)
            {
                if(m_pos_1 > 0)
                {
                    if(m_arg_str.substr(m_pos_1-1, 1).compare(m_arg_quote) == 0)
                    {
                        m_pos_2 = m_pos_1;
                        //Find first non delimiter character position.
                        m_pos_1 = m_arg_str.find_first_not_of(m_arg_quote, m_pos_2);
                        //Find next delimiter character position.
                        m_pos_2 = m_arg_str.find_first_of(m_arg_quote, m_pos_1);
                    }
                    else
                    {
                        //Find first delimiter character position.
                        m_pos_2 = m_arg_str.find_first_of(m_delimiters_with_quote, m_pos_1);
                    }
                }
                else
                {
                    //Find first delimiter character position.
                    m_pos_2 = m_arg_str.find_first_of(m_delimiters_with_quote, m_pos_1);
                }
            }
            else
            {
                m_pos_2 = std::string::npos;
            }
        }
    }
}

/*
    Case insensitive comparison of 2 strings and returns one of the following:
        - Equal returns 0.
        - String 1 is higher than string 2 then returns 1.
        - String 1 is lower than string 2 then returns -1.
    Because it uses standard C toupper function the comparison is affected by the current locale set.
*/
int nocase_cmp(std::string m_arg_str_1, std::string m_arg_str_2)
{
    std::string::const_iterator m_it_1 = m_arg_str_1.begin();
    std::string::const_iterator m_it_2 = m_arg_str_2.begin();

    while((m_it_1 != m_arg_str_1.end()) && (m_it_2 != m_arg_str_2.end()))
    {
        //Does character differ?
        if(toupper(*m_it_1) != toupper(*m_it_2))
        {
            //Return -1 to indicate smaller than, else 1 for bigger.
            return (toupper(*m_it_1) < toupper(*m_it_2)) ? -1 : 1;
        }

        //Next character.
        m_it_1++;
        m_it_2++;
    }
    //Cache lengths.
    size_t m_size_1 = m_arg_str_1.size();
    size_t m_size_2 = m_arg_str_2.size();

    //Return -1, 0 or 1 according to strings' lengths.
    if(m_size_1 == m_size_2)
    {
        return 0;
    }
    return (m_size_1 < m_size_2) ? -1 : 1;
}

/*
    Converts a string to upper case letters.
    Because it uses standard C toupper function it is affected by the current locale set.
*/
void to_upper_str(std::string& m_arg_in_out_str)
{
    std::transform(m_arg_in_out_str.begin(), m_arg_in_out_str.end(), m_arg_in_out_str.begin(), toupper);
}

/*
    Converts a string to lower case letters.
    Because it uses standard C tolower function it is affected by the current locale set.
*/
void to_lower_str(std::string& m_arg_in_out_str)
{
    std::transform(m_arg_in_out_str.begin(), m_arg_in_out_str.end(), m_arg_in_out_str.begin(), tolower);
}

//Converts bytes in a buffer to a hex string.
std::string buf_to_hex_str(const unsigned char* m_arg_buf, size_t m_arg_buf_len)
{
    std::string hex_str;
    size_t i;

    for(i = 0; i < m_arg_buf_len; i++)
    {
        hex_str += to_string_right_hex_up((int)(m_arg_buf[i]), 2, '0');
    }

    return hex_str;
}
