
// Available Debug-Groups
enum debug_group {
	DEBUG_OFF			= 0,
	DEBUG_OBJECT		= 1,
	DEBUG_CONTAINER		= 2,
	DEBUG_FILE_GEN		= 4,
	DEBUG_FILE			= 8,
	DEBUG_FILE_NOTFOUND	= 16,
	DEBUG_IO			= 32,
	DEBUG_DIRECTORY		= 64,
	DEBUG_DIRECTORY_GEN	= 128,
	DEBUG_SEARCH		= 256,
	DEBUG_UNKNOWN		= 512,
	DEBUG_OTHER			= 1024,
	DEBUG_FULL			= 0xFFFFFFFF
};


// Methods provded
int debug_set_groups(debug_group groups);
int debug(debug_group group, const char* format, ...);


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

