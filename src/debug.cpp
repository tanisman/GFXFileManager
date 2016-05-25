#include "debug.h"
#include <stdio.h>
#include <stdarg.h>


int debug(const char *format, ...) {
	va_list vl;
	char buffer[512];

	va_start(vl, format);

	//vsnprintf_s(buffer, sizeof(buffer), format, vl);

	vprintf(format, vl);


	va_end(vl);

	return 0;
}
