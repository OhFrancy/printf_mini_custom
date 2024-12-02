
/* Include Guard */

#ifndef PRINTF_WRITE

#define PRINTF_WRITE

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int fltrbyLen(va_list ap, char *fndcase, int bytes);

int writechar (int c)
{
	return write(1, &c, sizeof(char));
}

int writestr (char *s)
{
	int bytes = 0;
	while (*s) {
		bytes = write(1, s, 1);
		++s;
	}
	return bytes;
}
int writedigit (int n, int base) 
{
	int bytes = 0;
	char *list = "0123456789";
	if (n < 0) {
		bytes += write(1, "-", 1);
		return writedigit(-n, base);
	}
	if (n < base) {
		return writechar(list[n]);
	} 
	else { 
	 	bytes = writedigit(n / base, base);
		return writedigit(n % base, base);
	}	
	return bytes;
}

/*
 *   If the format specifier is of length 1, checks and outputs the correspondent value,
 *   If the length is 2, searches for a correspondence with the given format specifier, if found passes that to fltrbyLen();			
 */

int write_specifier (va_list ap, int specnt, ...) 
{
	int bytes = 0;
	va_list ap_1;
	va_start(ap_1, specnt);

	if (specnt == 1) {
		switch (va_arg(ap_1, int)) {
			case 'c' :
				bytes = writechar(va_arg(ap, int));
				break;
			case 'd' :
			case 'i' :
				bytes = writedigit(va_arg(ap, int), 10);
				break;
			case 'u' :
				bytes = writedigit(va_arg(ap, unsigned int), 10);
				break;
			case 's' :
				bytes = 1;
				writestr(va_arg(ap, char*));
				break;  
		}
	}
	va_end(ap_1);
	
	char *dblcases[] = {"ld",
		            "li",			
		            "lu"};
	va_list ap_2;
	if (specnt == 2) {
		for (int i = 0; dblcases[i] != NULL; ++i) {
			va_start(ap_2, specnt);	
			for (int j = 0; dblcases[i][j] != '\0'; ++j) {
				if (va_arg(ap, int) == dblcases[i][j] && va_arg(ap, int) == dblcases[i][j + 1])
					bytes += fltrbyLen(ap, dblcases[i], specnt);
			}
		}
			va_end(ap_2);
	}
	return bytes;
}


int fltrbyLen(va_list ap, char *fndcase, int bytes)
{		
	for (int i = 0; *fndcase; ++i) {
		if (fndcase[i] == 'l')
			switch (fndcase[i + 1]) {
				case 'u' :
					writedigit(va_arg(ap, long unsigned int), 10);
					break;
				case 'd' :
				case 'i' :
					writedigit(va_arg(ap, long signed int), 10);
					break;		
			}	
	}

	return bytes;		
}
#endif
