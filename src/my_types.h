/*
	gag warnings for fopen_s etc to keep compatibility with 
	gnu compiler on linux system
*/
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#ifndef MY_TYPES_H
#define MY_TYPES_H

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (-1)
#endif

typedef int BOOL;

#endif
