#ifndef PACPLUS_WRAP_H
#define PACPLUS_WRAP_H

#include "my_types.h"
#include "to_string.h"
#include "string_utils.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <list>

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

//*********************************  From emucore.h

// useful macros to deal with bit shuffling encryptions
#define BIT(x,n) (((x)>>(n))&1)

#define BITSWAP8(val,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B7) << 7) | (BIT(val,B6) << 6) | (BIT(val,B5) << 5) | (BIT(val,B4) << 4) | \
	 (BIT(val,B3) << 3) | (BIT(val,B2) << 2) | (BIT(val,B1) << 1) | (BIT(val,B0) << 0))

#define BITSWAP16(val,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
	 (BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
	 (BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
	 (BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

#define BITSWAP24(val,B23,B22,B21,B20,B19,B18,B17,B16,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B23) << 23) | (BIT(val,B22) << 22) | (BIT(val,B21) << 21) | (BIT(val,B20) << 20) | \
	 (BIT(val,B19) << 19) | (BIT(val,B18) << 18) | (BIT(val,B17) << 17) | (BIT(val,B16) << 16) | \
	 (BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
	 (BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
	 (BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
	 (BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

#define BITSWAP32(val,B31,B30,B29,B28,B27,B26,B25,B24,B23,B22,B21,B20,B19,B18,B17,B16,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B31) << 31) | (BIT(val,B30) << 30) | (BIT(val,B29) << 29) | (BIT(val,B28) << 28) | \
	 (BIT(val,B27) << 27) | (BIT(val,B26) << 26) | (BIT(val,B25) << 25) | (BIT(val,B24) << 24) | \
	 (BIT(val,B23) << 23) | (BIT(val,B22) << 22) | (BIT(val,B21) << 21) | (BIT(val,B20) << 20) | \
	 (BIT(val,B19) << 19) | (BIT(val,B18) << 18) | (BIT(val,B17) << 17) | (BIT(val,B16) << 16) | \
	 (BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
	 (BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
	 (BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
	 (BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

//*********************************

#define DECRYPT_MODE_NONE      0
#define DECRYPT_MODE_BITSWAP8  1
#define DECRYPT_MODE_BITSWAP16 2
#define DECRYPT_MODE_BITSWAP24 3
#define DECRYPT_MODE_BITSWAP32 4
#define DECRYPT_MODE_PATCH     5
#define DECRYPT_MODE_CHKSUM    6

#define CHKSUM_TYPE_NONE     0
#define CHKSUM_TYPE_STANDARD 1
#define CHKSUM_TYPE_EVEN     2
#define CHKSUM_TYPE_ODD      3
#define CHKSUM_TYPE_EVEN_ODD 4

typedef struct
{
    int m_offset;
    UINT8 m_value;
}patch_info_type;

BOOL open_file_disp_err(FILE*& m_arg_fp, std::string m_arg_rd_file_path_name, std::string m_arg_open_mode);
UINT8 check_sum_8(UINT8* m_arg_buf, int m_arg_buf_size);
UINT8 check_sum_8_even(UINT8* m_arg_buf, int m_arg_buf_size);
UINT8 check_sum_8_odd(UINT8* m_arg_buf, int m_arg_buf_size);
UINT8 decrypt_bswap8(int addr, UINT8 e, UINT8* m_arg_swap_xor_table, int* m_arg_picktable);
UINT16 decrypt_bswap16(int addr, UINT16 e, UINT8* swap_xor_table, int* picktable);
UINT32 decrypt_bswap24(int addr, UINT32 e, UINT8* swap_xor_table, int* picktable);
UINT32 decrypt_bswap32(int addr, UINT32 e, UINT8* swap_xor_table, int* picktable);
BOOL read_ini_init(
    std::string m_arg_ini_file_name,
    unsigned int& m_arg_steps
);
BOOL read_ini_mode(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int& m_arg_decrypt_mode
);
BOOL read_ini_swap_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int m_arg_decrypt_mode,
    int& m_arg_swap_start,
    int& m_arg_swap_end,
    UINT8*& m_arg_swap_xor_table,
    int*& m_arg_picktable
);
BOOL read_ini_patch_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    std::list<patch_info_type>& m_arg_patch_info_list
);
BOOL read_ini_check_sum_entries(
    std::string m_arg_ini_file_name,
    std::string m_arg_ini_key_str,
    unsigned int& m_arg_check_sum_type,
    int& m_arg_check_sum_start,
    int& m_arg_check_sum_end,
    std::list<int>& m_arg_check_sum_dest_list
);
BOOL create_tables(UINT8*& m_arg_swap_xor_table, int*& m_arg_picktable);
void cleanup(FILE* m_arg_fp_in, UINT8* m_arg_swap_xor_table, int* m_arg_picktable);
BOOL process_rom(std::string m_arg_in_file_name, unsigned char* m_arg_ram, int m_arg_ram_size, std::string m_arg_ini_file_name);

#endif
