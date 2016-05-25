#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

int m_group = DEBUG_FULL;

int debug(debug_group group, const char *format, ...) {
	va_list vl;
	char buffer[512];

	// Filter out unwanted debugging messages
	if (!(group & m_group)) {
		return 0;
	}

	va_start(vl, format);

	vprintf(format, vl);

	va_end(vl);

	return 0;
}
