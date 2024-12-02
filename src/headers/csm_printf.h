/*
 *  'Include Guard' ->
 *   make sure that the headers do not get conflicts,
 *   with extra-calling by defining a macro
 */

#ifndef CSM_PRINTF_MAIN
 
#define CSM_PRINTF_MAIN

#include "csm_printf_count.h"
#include <unistd.h>
#include <stdarg.h>

/*
 *   For every char checks if it's a format specifier and calls printf_format,
 *   writes the char otherwise
 */

int csm_printf (const char *str, ...)
{
	va_list ap;
	int wrtbytes = 0, frmtspec = 0;
	va_start(ap, str);
	for (int i = 0; str[i]; ++i) {	
		if(str[i] == '%') {
			while (str[i + 1] == ' ')
				++i;
			if (str[i + 1] != '%') {
				frmtspec = cnt_specifier(str, i + 1, ap);
			} else {
				writechar(str[i + 1]);
				++i;	
			}
				
		} else { 
			if (frmtspec == 1)
				continue;
			else if (frmtspec == 2)
				continue;
			wrtbytes += writechar((int)str[i]);
		}

	}
	va_end(ap);
	return wrtbytes + frmtspec;
}
#endif
