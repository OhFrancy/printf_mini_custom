#ifndef PRINTF_CNT

#define PRINTF_CNT

#include "csm_printf_write.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* 
 *  Counts every format specifier, if they are equal to one of the cases,
 *  passes the count to the function in the write header <csm_printf_write.h>
 */
int cnt_specifier (const char *str, int spec, va_list ap)
{
	int bytes = 0;
	const char cases[] = {'c', 'd', 'i', 'u', 'l', 's'};

	int k = 0, cnt = 0;
	for (int j = spec; str[j - 1]; ++j) { 
		while (cases[k]) {
			if (str[j] == cases[k]) {	
				++cnt;	
				if (str[j + 1] == '%')
					goto out;
				break;
			}
			++k;
		}
		k = 0;
	}
	out :
		
	switch (cnt) {
		case 1 :
			bytes = write_specifier(ap, cnt, str[spec]);
			break;
		case 2 :
			bytes = write_specifier(ap, cnt, str[spec], str[spec + 1]);
			break;
		default :	
			break;
	}
	return bytes;
}

#endif
