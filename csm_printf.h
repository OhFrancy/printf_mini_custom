#ifndef CSM_PRINTF

#define CSM_PRINTF

#include "csm_printf_format.h"
#include <unistd.h>
#include <stdarg.h>

int csm_printf (const char *str, ...)
{
	va_list ap;
	int bytes = 0;
	va_start(ap, str);
	while (*str) 
	{																
		if(*str == '%') {
			bytes += printf_format(*(++str), ap);
		}
		else { 
			bytes += write(1, str, 1);
		}
		++str;
	}
	va_end(ap);
	return bytes;
}

#endif

	







