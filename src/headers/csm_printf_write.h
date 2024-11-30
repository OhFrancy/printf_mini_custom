#ifndef PRINTF_WRITE

#define PRINTF_WRITE

#include <unistd.h>

int printf_write_char (int c)
{
	return write(1, &c, sizeof(int));
}

int printf_write_str (char *s)
{
	int bytes = 0;
	while (*s) {
		bytes += write(1, s++, 1);
	}
	return bytes;
}
int printf_write_digit (int n, int base) 
{
	int bytes = 0;
	char *nList = "0123456789";
	if (n < 0) {
		bytes += write(1, "-", 1);
		return printf_write_digit(-n, base);
	}
	if (n < base) {
		return printf_write_char(nList[n]);
	} 
	else { 
	 	bytes = printf_write_digit(n / base, base);
		return bytes + printf_write_digit(n % base, base);
	}	

	return bytes;
}

#endif
