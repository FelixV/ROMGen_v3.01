#include "ProcessROMS.h"

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

static UINT8 decrypt_8(int addr, UINT8 e, UINT8* swap_xor_table, int* picktable)
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
	return BITSWAP8(e,tbl[0],tbl[1],tbl[2],tbl[3],tbl[4],tbl[5],tbl[6],tbl[7]) ^ tbl[8];
}

static void patch_maketrax(UINT8 *data)
{

	//UINT8 *decrypted = data;
	//memcpy(data,data,0x4000);

	// patch rom crc (DOESNT WORK)
	data[0x31] = 0x25;
	data[0x32] = 0x7c;
	data[0x33] = 0xe6;
	data[0x34] = 0xf0;

	// patch make trax
	//data[0x0415] = 0xc9;
	//data[0x1978] = 0x18;
	//data[0x238e] = 0xc9;
	//data[0x3ae5] = 0xe6;
	//data[0x3ae7] = 0x00;
	//data[0x3ae8] = 0xc9;
	//data[0x3aed] = 0x86;
	//data[0x3aee] = 0xc0;
	//data[0x3aef] = 0xb0;

	return;
}


BOOL create_tables_from_ini(std::string m_arg_ini_file_name, unsigned int& m_arg_bit_swap_mode, UINT8*& m_arg_swap_xor_table, int*& m_arg_picktable)
{
    DWORD m_n_size;
    char m_key_str[255];
    unsigned int m_n_xor_tables;
    unsigned int m_i;
    unsigned int m_j;
    std::string m_str;
    std::string m_table_key_name;
    std::list<std::string> m_str_list;
    std::list<std::string>::iterator m_str_list_it;

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString("MODE", "DECRYPT_MODE", "", m_key_str, 255, m_arg_ini_file_name.c_str());
    m_str = m_key_str;
    to_upper_str(m_str);

    m_arg_bit_swap_mode = DECRYPT_MODE_NONE;
    if(m_str == "BITSWAP8")
    {
        m_arg_bit_swap_mode = DECRYPT_MODE_BITSWAP8;
    } else if(m_str == "BITSWAP16") {
        m_arg_bit_swap_mode = DECRYPT_MODE_BITSWAP16;
    } else if(m_str == "BITSWAP24") {
        m_arg_bit_swap_mode = DECRYPT_MODE_BITSWAP24;
    } else if(m_str == "BITSWAP32") {
        m_arg_bit_swap_mode = DECRYPT_MODE_BITSWAP32;
    } else {
        printf("Error: INI: Invalid MODE!\n");
        return FALSE;
    }

    m_key_str[0] = 0;
    m_n_size = GetPrivateProfileString("PICKTABLE", "VALUES", "", m_key_str, 255, m_arg_ini_file_name.c_str());
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

        if(m_i >= 32)
        {
            break;
        }
    }
    //printf("\n");

    m_n_xor_tables = GetPrivateProfileInt("SWAP_XOR_TABLE", "TABLE_COUNT", 0, m_arg_ini_file_name.c_str());
    //printf("INI: TABLE_COUNT = %i\n", m_n_xor_tables);

    if(m_n_xor_tables == 0)
    {
        printf("Error: INI: 0 tables count!\n");
        return FALSE;
    }

    m_arg_swap_xor_table = (UINT8*)malloc(9 * m_n_xor_tables);
    if(m_arg_swap_xor_table == NULL)
    {
        printf("Error: could not allocate memory for swap_xor_table!\n");
        return FALSE;
    }

    for(m_i = 0; m_i < m_n_xor_tables; m_i++)
    {
        m_key_str[0] = 0;
        m_table_key_name = "TABLE_" + to_string(m_i + 1);
        m_n_size = GetPrivateProfileString("SWAP_XOR_TABLE", m_table_key_name.c_str() , "", m_key_str, 255, m_arg_ini_file_name.c_str());
        //printf("INI: TABLE = %s\n", m_key_str);

        //Split ini string into separate substrings of each value.
        m_str_list.clear();
        stringsplit(m_str_list, m_key_str, ",");

        //Convert string values into numeric values and store into array buffer.
        //printf("  INI: TABLE = ");
        m_j = 0;
        for(m_str_list_it = m_str_list.begin(); m_str_list_it != m_str_list.end(); m_str_list_it++)
        {
           m_arg_swap_xor_table[9*m_i + m_j] = (UINT8)strtol(m_str_list_it->c_str(), NULL, 0);
           //if(m_j != 0){ printf(","); }
           //printf("%i", swap_xor_table[9*m_i + m_j]);
           m_j++;
        }
        //printf("\n");
    }

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
    }

    if(m_arg_picktable != NULL)
    {
        free(m_arg_picktable);
    }

    if(m_arg_fp_in != NULL)
    {
        fclose(m_arg_fp_in);
    }
}

BOOL ProcessROMS(std::string m_arg_in_file_name, unsigned char RAM[0x4000], std::string m_arg_ini_file_name)
{
    int i;
    FILE* m_fp_in;
    size_t m_file_bytes_rd;
    unsigned int m_bit_swap_mode;
    UINT8* m_swap_xor_table;
    int* m_picktable;

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

    //Create decrypt tables.
    if(m_arg_ini_file_name.size() > 0)
    {
        if(!create_tables_from_ini(m_arg_ini_file_name, m_bit_swap_mode, m_swap_xor_table, m_picktable))
        {
            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
            //Exit.
            return FALSE;
        }
    }
    else
    {
        if(!create_tables(m_swap_xor_table, m_picktable))
        {
            cleanup(m_fp_in, m_swap_xor_table, m_picktable);
            //Exit.
            return FALSE;
        }
    }

    /* CPU ROMs */

    //Read bytes from file.
    m_file_bytes_rd = fread(RAM, 1, 0x4000, m_fp_in);
    if(m_file_bytes_rd > 0)
    {
        if(m_bit_swap_mode != DECRYPT_MODE_NONE)
        {
			if (m_bit_swap_mode == DECRYPT_MODE_BITSWAP8)
			{
	            for (i = 0; i < 0x4000; i++)
		        {
					if (m_bit_swap_mode == DECRYPT_MODE_BITSWAP8)
					{
						RAM[i] = decrypt_8(i, RAM[i], m_swap_xor_table, m_picktable);
					}
				}
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
