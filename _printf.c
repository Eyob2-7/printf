#include <unistd.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;
	char c;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			/* Regular character, print directly */
			c = *format;
			write(1, &c, 1);
			printed_chars++;
		}
		else
		{
			/* Handle the conversion specifier */
			format++;
			switch (*format)
			{
				case 'c':
					/* Print character */
					c = va_arg(args, int);
					write(1, &c, 1);
					printed_chars++;
					break;
				case 's':
					/* Print string */
					{
						char *str = va_arg(args, char *);

						int len = 0;
						while (str[len])
							len++;
						write(1, str, len);
						printed_chars += len;
					}
					break;
				case '%':
					/* Print a literal '%' character */
					write(1, "%", 1);
					printed_chars++;
					break;
				default:
					/* Unsupported conversion specifier, ignore */
					break;
			}
		}
		format++;
	}

	va_end(args);

	return (printed_chars);
}
