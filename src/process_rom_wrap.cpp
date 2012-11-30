#include "process_rom_wrap.h"

BOOL open_file_disp_err(FILE*& m_arg_fp, std::string m_arg_rd_file_path_name, std::string m_arg_open_mode)
{
    //Open file.
    m_arg_fp = fopen(m_arg_rd_file_path_name.c_str(), m_arg_open_mode.c_str());
    if(m_arg_fp == NULL)
    {
        printf("Error: could not open file %s!\n", m_arg_rd_file_path_name.c_str());
        return FALSE;
    }

    return TRUE;
}

UINT8 check_sum_8(UINT8* m_arg_buf, int m_arg_buf_size)
{
    int m_i;
    UINT8 m_sum;

    m_sum = 0;
    for(m_i = 0; m_i < m_arg_buf_size; ++m_i)
    {
        m_sum += *(m_arg_buf + m_i);
    }

    return m_sum;
}

UINT8 check_sum_8_even(UINT8* m_arg_buf, int m_arg_buf_size)
{
    int m_i;
    UINT8 m_sum;

    m_sum = 0;
    for(m_i = 1; m_i < m_arg_buf_size; m_i += 2)
    {
        m_sum += *(m_arg_buf + m_i);
    }

    return m_sum;
}

UINT8 check_sum_8_odd(UINT8* m_arg_buf, int m_arg_buf_size)
{
    int m_i;
    UINT8 m_sum;

    m_sum = 0;
    for(m_i = 0; m_i < m_arg_buf_size; m_i += 2)
    {
        m_sum += *(m_arg_buf + m_i);
    }

    return m_sum;
}

UINT8 decrypt_bswap8(int addr, UINT8 e, UINT8* swap_xor_table, int* picktable)
{
	UINT32 method = 0;
	UINT8 *tbl;

	/* pick method from bits 0 2 5 7 9 of the address */
	method = picktable[
		(addr & 0x001) |
		((addr & 0x004) >> 1) |
		((addr & 0x020) >> 3) |
		((addr & 0x080) >> 4) |
		((addr & 0x200) >> 5)];

	/* switch method if bit 11 of the address is set */
	if ((addr & 0x800) == 0x800)
		method ^= 1;

	tbl = swap_xor_table + method * 9;
	return
        BITSWAP8(
            e,
            tbl[0],
            tbl[1],
            tbl[2],
            tbl[3],
            tbl[4],
            tbl[5],
            tbl[6],
            tbl[7]
        ) ^ tbl[8];
}

UINT16 decrypt_bswap16(int addr, UINT16 e, UINT8* swap_xor_table, int* picktable)
{
	UINT32 method = 0;
	UINT8 *tbl;

	/* pick method from bits 0 2 5 7 9 of the address */
	method = picktable[
		(addr & 0x001) |
		((addr & 0x004) >> 1) |
		((addr & 0x020) >> 3) |
		((addr & 0x080) >> 4) |
		((addr & 0x200) >> 5)];

	/* switch method if bit 11 of the address is set */
	if ((addr & 0x800) == 0x800)
		method ^= 1;

	tbl = swap_xor_table + method * 17;
	return
        BITSWAP16(
            e,
            tbl[0],
            tbl[1],
            tbl[2],
            tbl[3],
            tbl[4],
            tbl[5],
            tbl[6],
            tbl[7],
            tbl[8],
            tbl[9],
            tbl[10],
            tbl[11],
            tbl[12],
            tbl[13],
            tbl[14],
            tbl[15]
        ) ^ tbl[16];
}

UINT32 decrypt_bswap24(int addr, UINT32 e, UINT8* swap_xor_table, int* picktable)
{
	UINT32 method = 0;
	UINT8 *tbl;

	/* pick method from bits 0 2 5 7 9 of the address */
	method = picktable[
		(addr & 0x001) |
		((addr & 0x004) >> 1) |
		((addr & 0x020) >> 3) |
		((addr & 0x080) >> 4) |
		((addr & 0x200) >> 5)];

	/* switch method if bit 11 of the address is set */
	if ((addr & 0x800) == 0x800)
		method ^= 1;

	tbl = swap_xor_table + method * 25;
	return
        BITSWAP24(
            e,
            tbl[0],
            tbl[1],
            tbl[2],
            tbl[3],
            tbl[4],
            tbl[5],
            tbl[6],
            tbl[7],
            tbl[8],
            tbl[9],
            tbl[10],
            tbl[11],
            tbl[12],
            tbl[13],
            tbl[14],
            tbl[15],
            tbl[16],
            tbl[17],
            tbl[18],
            tbl[19],
            tbl[20],
            tbl[21],
            tbl[22],
            tbl[23]
        ) ^ tbl[24];
}

UINT32 decrypt_bswap32(int addr, UINT32 e, UINT8* swap_xor_table, int* picktable)
{
	UINT32 method = 0;
	UINT8 *tbl;

	/* pick method from bits 0 2 5 7 9 of the address */
	method = picktable[
		(addr & 0x001) |
		((addr & 0x004) >> 1) |
		((addr & 0x020) >> 3) |
		((addr & 0x080) >> 4) |
		((addr & 0x200) >> 5)];

	/* switch method if bit 11 of the address is set */
	if ((addr & 0x800) == 0x800)
		method ^= 1;

	tbl = swap_xor_table + method * 33;
	return
        BITSWAP32(
            e,
            tbl[0],
            tbl[1],
            tbl[2],
            tbl[3],
            tbl[4],
            tbl[5],
            tbl[6],
            tbl[7],
            tbl[8],
            tbl[9],
            tbl[10],
            tbl[11],
            tbl[12],
            tbl[13],
            tbl[14],
            tbl[15],
            tbl[16],
            tbl[17],
            tbl[18],
            tbl[19],
            tbl[20],
            tbl[21],
            tbl[22],
            tbl[23],
            tbl[24],
            tbl[25],
            tbl[26],
            tbl[27],
            tbl[28],
            tbl[29],
            tbl[30],
            tbl[31]
        ) ^ tbl[32];
}

BOOL read_ini_init(
    std::string m_arg_ini_file_name,
    unsigned int& m_arg_steps
)
{
    DWORD m_n_size;
    char m_key_str[255];
    std::string m_str;

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString("INIT", "STEPS", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_arg_steps = (unsigned int)strtol(m_key_str, NULL, 0);

    return TRUE;
}


BOOL read_ini_mode(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int& m_arg_decrypt_mode
)
{
    DWORD m_n_size;
    char m_key_str[255];
    std::string m_str;

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "MODE", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_str = m_key_str;
    to_upper_str(m_str);

    if(m_str == "BITSWAP8")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_BITSWAP8;
    }
    else
    if(m_str == "BITSWAP16")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_BITSWAP16;
    }
    else
    if(m_str == "BITSWAP24")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_BITSWAP24;
    }
    else
    if(m_str == "BITSWAP32")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_BITSWAP32;
    }
    else
    if(m_str == "GENERIC_PATCH")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_PATCH;
    }
    else
    if(m_str == "CHECKSUM")
    {
        m_arg_decrypt_mode = DECRYPT_MODE_CHKSUM;
    }
    else
    {
        m_arg_decrypt_mode = DECRYPT_MODE_NONE;
    }

    return TRUE;
}

BOOL read_ini_swap_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int m_arg_decrypt_mode,
    int& m_arg_swap_start,
    int& m_arg_swap_end,
    UINT8*& m_arg_swap_xor_table,
    int*& m_arg_picktable
)
{
    int m_swap_table_size;
    DWORD m_n_size;
    char m_key_str[255];
    unsigned int m_n_xor_tables;
    unsigned int m_i;
    unsigned int m_j;
    std::string m_str;
    std::string m_table_key_name_str;
    std::list<std::string> m_str_list;
    std::list<std::string>::iterator m_str_list_it;

    switch(m_arg_decrypt_mode)
    {
        case DECRYPT_MODE_BITSWAP8:
        {
            m_swap_table_size = 9;
            break;
        }
        case DECRYPT_MODE_BITSWAP16:
        {
            m_swap_table_size = 17;
            break;
        }
        case DECRYPT_MODE_BITSWAP24:
        {
            m_swap_table_size = 25;
            break;
        }
        case DECRYPT_MODE_BITSWAP32:
        {
            m_swap_table_size = 33;
            break;
        }
        default:
        {
            m_swap_table_size = 0;
        }
    }

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "START", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_arg_swap_start = (int)strtol(m_key_str, NULL, 0);

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "END", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    if(m_key_str[0] == 0)
    {
        m_arg_swap_end = -1;
    }
    else
    {
        m_arg_swap_end = (int)strtol(m_key_str, NULL, 0);
    }

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "PICKTABLE_VALUES", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    //printf("INI: VALUES = %s\n", m_key_str);

    //Split ini string into separate substrings of each value.
    stringsplit(m_str_list, m_key_str, ",");

    if(m_str_list.size() == 0)
    {
        printf("Error: INI: 0 picktable values!\n");
        return FALSE;
    }

    m_arg_picktable = (int*)malloc(sizeof(int) * m_str_list.size());
    if(m_arg_picktable == NULL)
    {
        printf("Error: could not allocate memory for picktable!\n");
        return FALSE;
    }

    //Convert string values into numeric values and store into array buffer.
    //printf("INI: PICKTABLE = ");
    m_i = 0;
    for(m_str_list_it = m_str_list.begin(); m_str_list_it != m_str_list.end(); m_str_list_it++)
    {
        m_arg_picktable[m_i] = (int)strtol(m_str_list_it->c_str(), NULL, 0);
        //if(m_i != 0){ printf(","); }
        //printf("%i", picktable[m_i]);
        m_i++;
    }
    //printf("\n");

    m_n_xor_tables = GetPrivateProfileInt(m_arg_ini_key_str.c_str(), "SWAP_XOR_TABLE_COUNT", 0, m_arg_ini_file_name.c_str());
    //printf("INI: TABLE_COUNT = %i\n", m_n_xor_tables);

    if(m_n_xor_tables == 0)
    {
        printf("Error: INI: 0 tables count!\n");
        return FALSE;
    }

    m_arg_swap_xor_table = (UINT8*)malloc(m_swap_table_size * m_n_xor_tables);
    if(m_arg_swap_xor_table == NULL)
    {
        printf("Error: could not allocate memory for swap_xor_table!\n");
        return FALSE;
    }

    for(m_i = 0; m_i < m_n_xor_tables; m_i++)
    {
        m_key_str[0] = 0;
        m_table_key_name_str = "SWAP_XOR_TABLE_" + to_string(m_i + 1);
        m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), m_table_key_name_str.c_str() , "", m_key_str, 255, m_arg_ini_file_name.c_str());
        //printf("INI: TABLE = %s\n", m_key_str);

        //Split ini string into separate substrings of each value.
        m_str_list.clear();
        stringsplit(m_str_list, m_key_str, ",");

        //Convert string values into numeric values and store into array buffer.
        //printf("  INI: TABLE = ");
        m_j = 0;
        for(m_str_list_it = m_str_list.begin(); m_str_list_it != m_str_list.end(); m_str_list_it++)
        {
           m_arg_swap_xor_table[m_swap_table_size * m_i + m_j] = (UINT8)strtol(m_str_list_it->c_str(), NULL, 0);
           //if(m_j != 0){ printf(","); }
           //printf("%i", swap_xor_table[9*m_i + m_j]);
           m_j++;
        }
        //printf("\n");
    }

    return TRUE;
}

BOOL read_ini_patch_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    std::list<patch_info_type>& m_arg_patch_info_list
)
{
    DWORD m_n_size;
    char m_key_str[255];
    std::string m_offset_key_name_str;
    unsigned int m_offset_total;
    unsigned int m_offset_count;
    std::list<std::string> m_str_list;
    std::list<std::string>::iterator m_str_list_it;
    patch_info_type m_patch_info;

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "COUNT", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_offset_total = (unsigned int)strtol(m_key_str, NULL, 0);

    for(m_offset_count = 0; m_offset_count < m_offset_total; ++m_offset_count)
    {
        m_offset_key_name_str = "OFFSET_" + to_string(m_offset_count + 1);
        m_key_str[0] = 0;
        m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "COUNT", "", m_key_str, 255, m_arg_ini_file_name.c_str());
        //Split ini string into separate substrings of each value.
        m_str_list.clear();
        stringsplit(m_str_list, m_key_str, ",");
        if(m_str_list.size() >= 2)
        {
            m_str_list_it = m_str_list.begin();
            m_patch_info.m_offset = (int)strtol(m_str_list_it->c_str(), NULL, 0);
            ++m_str_list_it;
            m_patch_info.m_value = (UINT8)strtol(m_str_list_it->c_str(), NULL, 0);
            m_arg_patch_info_list.push_back(m_patch_info);
        }
    }

    return TRUE;
}

BOOL read_ini_check_sum_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int& m_arg_check_sum_type,
    int& m_arg_check_sum_start,
    int& m_arg_check_sum_end,
    std::list<int>& m_arg_check_sum_dest_list
)
{
    DWORD m_n_size;
    char m_key_str[255];

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "CHECKSUM_TYPE", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_arg_check_sum_type = (unsigned int)strtol(m_key_str, NULL, 0);

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "CHECKSUM_START", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_arg_check_sum_start = (int)strtol(m_key_str, NULL, 0);

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "CHECKSUM_END", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    if(m_key_str[0] == 0)
    {
        m_arg_check_sum_end = -1;
    }
    else
    {
        m_arg_check_sum_end = (int)strtol(m_key_str, NULL, 0);
    }

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString(m_arg_ini_key_str.c_str(), "CHECKSUM_APPLY", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_arg_check_sum_dest_list.push_back((int)strtol(m_key_str, NULL, 0));

    return TRUE;
}

BOOL create_tables(UINT8*& m_arg_swap_xor_table, int*& m_arg_picktable)
{
	static const UINT8 swap_xor_table[6][9] =
	{
		{ 7,6,5,4,3,2,1,0, 0x00 },
		{ 7,6,5,4,3,2,1,0, 0x28 },
		{ 6,1,3,2,5,7,0,4, 0x96 },
		{ 6,1,5,2,3,7,0,4, 0xbe },
		{ 0,3,7,6,4,2,1,5, 0xd5 },
		{ 0,3,4,6,7,2,1,5, 0xdd }
	};
	static const int picktable[32] =
	{
		0,2,4,2,4,0,4,2,2,0,2,2,4,0,4,2,
		2,2,4,0,4,2,4,0,0,4,0,4,4,2,4,2
	};

    m_arg_picktable = (int*)malloc(sizeof(int) * 32);
    if(m_arg_picktable == NULL)
    {
        printf("Error: could not allocate memory for picktable!\n");
        return FALSE;
    }

    memcpy(m_arg_picktable, picktable, sizeof(int) * 32);

    m_arg_swap_xor_table = (UINT8*)malloc(6 * 9);
    if(m_arg_swap_xor_table == NULL)
    {
        printf("Error: could not allocate memory for swap_xor_table!\n");
        return FALSE;
    }

    memcpy(m_arg_swap_xor_table, swap_xor_table, 6 * 9);

    return TRUE;
}

void cleanup(FILE* m_arg_fp_in, UINT8* m_arg_swap_xor_table, int* m_arg_picktable)
{
    if(m_arg_swap_xor_table != NULL)
    {
        free(m_arg_swap_xor_table);
        m_arg_swap_xor_table = NULL;
    }

    if(m_arg_picktable != NULL)
    {
        free(m_arg_picktable);
        m_arg_picktable = NULL;
    }

    if(m_arg_fp_in != NULL)
    {
        fclose(m_arg_fp_in);
        m_arg_fp_in = NULL;
    }
}

BOOL process_rom(std::string m_arg_in_file_name, unsigned char* m_arg_ram, int m_arg_ram_size, std::string m_arg_ini_file_name)
{
    int i;
    FILE* m_fp_in;
    size_t m_file_bytes_rd;
    unsigned int m_steps;
    unsigned int m_steps_i;
    std::string m_ini_key_mode_str;
    unsigned int m_decrypt_mode;
    UINT8* m_swap_xor_table;
    int* m_picktable;
    int m_swap_start;
    int m_swap_end;
    std::list<patch_info_type> m_patch_info_list;
    std::list<patch_info_type>::iterator m_patch_info_list_it;
    unsigned int m_check_sum_type;
    int m_check_sum_start;
    int m_check_sum_end;
    std::list<int> m_check_sum_dest_list;
    std::list<int>::iterator m_check_sum_dest_list_it;
    UINT8 m_check_sum_even;
    UINT8 m_check_sum_odd;
    UINT8 m_check_sum_even_odd_mod;

    m_fp_in = NULL;
    m_swap_xor_table = NULL;
    m_picktable = NULL;

    //Open file in binary mode.
    if(!open_file_disp_err(m_fp_in, m_arg_in_file_name, "rb"))
    {
        cleanup(m_fp_in, m_swap_xor_table, m_picktable);
        //Exit.
        return FALSE;
    }

    /* CPU ROMs */

    //Read bytes from file.
    m_file_bytes_rd = fread(m_arg_ram, 1, m_arg_ram_size, m_fp_in);
    if(m_file_bytes_rd > 0)
    {
        //Create decrypt tables
        if(m_arg_ini_file_name.size() > 0)
        {
            //Read ini init
            if(!read_ini_init(m_arg_ini_file_name, m_steps))
            {
                cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                //Exit.
                return FALSE;
            }
            //Loop mode steps
            for(m_steps_i = 0; m_steps_i < m_steps; ++m_steps_i)
            {
                m_ini_key_mode_str = "MODE_" + to_string(m_steps_i + 1);
                //Read ini decrypt mode.
                if(!read_ini_mode(m_arg_ini_file_name, m_ini_key_mode_str, m_decrypt_mode))
                {
                    cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                    //Exit.
                    return FALSE;
                }
                //Decrypt mode.
                switch(m_decrypt_mode)
                {
                    case DECRYPT_MODE_BITSWAP8:
                    {
                        if(!read_ini_swap_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_decrypt_mode, m_swap_start, m_swap_end, m_swap_xor_table, m_picktable))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        if(m_swap_end <= -1)
                        {
                            m_swap_end = m_arg_ram_size - 1;
                        }
                        for(i = m_swap_start; i <= m_swap_end; ++i)
                        {
                            m_arg_ram[i] = decrypt_bswap8(i, m_arg_ram[i], m_swap_xor_table, m_picktable);
                        }
                        break;
                    }
                    case DECRYPT_MODE_BITSWAP16:
                    {
                        if(!read_ini_swap_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_decrypt_mode, m_swap_start, m_swap_end, m_swap_xor_table, m_picktable))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        if(m_swap_end <= -1)
                        {
                            m_swap_end = m_arg_ram_size - 1;
                        }
                        for(i = m_swap_start; i <= m_swap_end; ++i)
                        {
                            ((UINT16*)m_arg_ram)[i] = decrypt_bswap16(i, ((UINT16*)m_arg_ram)[i], m_swap_xor_table, m_picktable);
                        }
                        break;
                    }
                    case DECRYPT_MODE_BITSWAP24:
                    {
                        if(!read_ini_swap_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_decrypt_mode, m_swap_start, m_swap_end, m_swap_xor_table, m_picktable))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        if(m_swap_end <= -1)
                        {
                            m_swap_end = m_arg_ram_size - 1;
                        }
                        for(i = m_swap_start; i <= m_swap_end; ++i)
                        {
                            ((UINT32*)m_arg_ram)[i] = decrypt_bswap24(i, ((UINT32*)m_arg_ram)[i], m_swap_xor_table, m_picktable);
                        }
                        break;
                    }
                    case DECRYPT_MODE_BITSWAP32:
                    {
                        if(!read_ini_swap_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_decrypt_mode, m_swap_start, m_swap_end, m_swap_xor_table, m_picktable))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        if(m_swap_end <= -1)
                        {
                            m_swap_end = m_arg_ram_size - 1;
                        }
                        for(i = m_swap_start; i <= m_swap_end; ++i)
                        {
                            ((UINT32*)m_arg_ram)[i] = decrypt_bswap32(i, ((UINT32*)m_arg_ram)[i], m_swap_xor_table, m_picktable);
                        }
                        break;
                    }
                    case DECRYPT_MODE_PATCH:
                    {
                        if(!read_ini_patch_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_patch_info_list))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        for(m_patch_info_list_it = m_patch_info_list.begin(); m_patch_info_list_it != m_patch_info_list.end(); ++m_patch_info_list_it)
                        {
                            m_arg_ram[m_patch_info_list_it->m_offset] = m_patch_info_list_it->m_value;
                        }
                        break;
                    }
                    case DECRYPT_MODE_CHKSUM:
                    {
                        if(!read_ini_check_sum_entries(m_arg_ini_file_name, m_ini_key_mode_str, m_check_sum_type, m_check_sum_start, m_check_sum_end, m_check_sum_dest_list))
                        {
                            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                            //Exit.
                            return FALSE;
                        }
                        if(m_check_sum_end <= -1)
                        {
                            m_check_sum_end = m_arg_ram_size - 1;
                        }
                        switch(m_check_sum_type)
                        {
                            case CHKSUM_TYPE_EVEN:
                            {
                                m_check_sum_even = check_sum_8_even(m_arg_ram + m_check_sum_start, m_check_sum_end - m_check_sum_start + 1);
                                m_check_sum_odd = m_check_sum_even;
                                break;
                            }
                            case CHKSUM_TYPE_ODD:
                            {
                                m_check_sum_odd = check_sum_8_odd(m_arg_ram + m_check_sum_start, m_check_sum_end - m_check_sum_start + 1);
                                m_check_sum_even = m_check_sum_odd;
                                break;
                            }
                            case CHKSUM_TYPE_EVEN_ODD:
                            {
                                m_check_sum_even = check_sum_8_even(m_arg_ram + m_check_sum_start, m_check_sum_end - m_check_sum_start + 1);
                                m_check_sum_odd = check_sum_8_odd(m_arg_ram + m_check_sum_start, m_check_sum_end - m_check_sum_start + 1);
                            }
                            case CHKSUM_TYPE_STANDARD:
                            {
                                m_check_sum_even = check_sum_8(m_arg_ram + m_check_sum_start, m_check_sum_end - m_check_sum_start + 1);
                                m_check_sum_odd = m_check_sum_even;
                                break;
                            }
                            default:
                            {
                                m_check_sum_dest_list.clear();
                            }
                        }
                        m_check_sum_even_odd_mod = 0;
                        for(m_check_sum_dest_list_it = m_check_sum_dest_list.begin(); m_check_sum_dest_list_it != m_check_sum_dest_list.end(); ++m_check_sum_dest_list_it)
                        {
                            if(m_check_sum_even_odd_mod == 0)
                            {
                                m_arg_ram[*m_check_sum_dest_list_it] = m_check_sum_even;
                            }
                            else
                            {
                                m_arg_ram[*m_check_sum_dest_list_it] = m_check_sum_odd;
                            }
                            m_check_sum_even_odd_mod = m_check_sum_even_odd_mod % 2;
                        }
                        break;
                    }
                }
            }
        }
        else
        {
            //Default decrypt mode when no ini file specified.

            if(!create_tables(m_swap_xor_table, m_picktable))
            {
                cleanup(m_fp_in, m_swap_xor_table, m_picktable);
                //Exit.
                return FALSE;
            }
            m_decrypt_mode = DECRYPT_MODE_BITSWAP8;
            //Decrypt 8 bit swap.
            for(i = 0; i < m_arg_ram_size; ++i)
            {
                m_arg_ram[i] = decrypt_bswap8(i, m_arg_ram[i], m_swap_xor_table, m_picktable);
            }
        }
    }
    else
    {
        //File error?
        if(ferror(m_fp_in))
        {
            //Display error message.
            perror("Error");
        }
    }

    cleanup(m_fp_in, m_swap_xor_table, m_picktable);

    return TRUE;
}
