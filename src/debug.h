
int debug(const char* format, ...);

// ###################################
// MessageBox creation

// Suppress all error MessageBoxes (not recommended)
#define DEBUG_SUPPRESS_ERROR 0

// Crazy macro for simpler assembly code
#if DEBUG_SUPPRESS_ERROR == 0
#define _ERROR_MSGBOX() MessageBox(0, "Cannot exec " __FUNCTION__, "[TODO] GFXFileManager", MB_OK | MB_ICONERROR)
#else
#define _ERROR_MSGBOX()
#endif

