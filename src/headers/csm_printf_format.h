#ifndef PRINTF_FORMAT

#define PRINTF_FORMAT

#include "csm_printf_write.h"
#include <stdarg.h>

int printf_format (char specifier, va_list ap) 
{
	int bytes = 0;
	switch (specifier) {
		case 'c' :
			bytes = printf_write_char(va_arg(ap, int));
			break;
		case 'd' :
		case 'i' :
			bytes = printf_write_digit(va_arg(ap, int), 10);
			break;
		case 's' :
			bytes = printf_write_str(va_arg(ap, char*));
			break;
		default :
			bytes += write(1, &specifier, 1);
			break;
	}
	return bytes;
}

#endif


