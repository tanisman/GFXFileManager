// Show debug messages on file-open and file-close (slow!)
#define DEBUG_PRINT_FILES 0
// Show debug-messages on file-read and file-write (very slow!)
#define DEBUG_PRINT_IO 0
// Show debug-messages on unknown methods
#define DEBUG_PRINT_UNKNOWN 0
// Show a message when opening failed
#define DEBUG_PRINT_NOTFOUND 0


#include "CWFileManager.h"
#include <iostream>
#include <string>

#include "debug.h"


int CWFileManager::get_mode() {
	debug("WFM::get_mode() = 1\n");

	return 1;
}

int CWFileManager::Function_1(int a, int b) {

	if (a == 2) {
		bSomething = (b == 0) ? 0 : 1;
	}

	
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_1(%d , %d) = 0\n", a, b);
#endif
	return 0;
}

int CWFileManager::Function_2(int a, int b) {
	
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_2(%d , %d) = 0\n", a, b);
#endif

	MessageBox(0, "Cannot exec Function_2", "Error", MB_OK);

	return 0;
}

int CWFileManager::CreateContainer(const char *filename, const char *password) {
	
	debug("WFM::CreateContainer(\"%s\", \"%s\") = 0\n", filename, password);

	return 0;
}

int CWFileManager::OpenContainer(const char *filename, const char* password, int mode) {

	debug("WFM::OpenContainer(\"%s\", \"%s\", 0x%08x) = 1\n", filename, password, mode);
	//MessageBox(0, "Open called!", "", MB_OK);
	
	char buffer[512] = {0};
	strcpy_s(buffer, sizeof(buffer), filename);

	char *pchr = strrchr(buffer, '.');

	*pchr = 0;

	// Set the root directory
	strcpy_s(this->root_dir, sizeof(this->root_dir), buffer);
	this->ResetDirectory();

	this->bIsOpen = 1;

	return 1;
}

int CWFileManager::CloseContainer() {

	this->bIsOpen = 0;

	debug("WFM::CloseContainer() = 1\n");

	return 1;
}

int CWFileManager::IsOpen() {
	debug("WFM::IsOpen() = 0\n", this->bIsOpen);

	return bIsOpen;
}

int CWFileManager::Function_7() {
	// This parses something like a list ...
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_7() = 1\n");
#endif
	MessageBox(0, "Cannot exec Function_7", "Error", MB_OK);

	return 1;
}

int CWFileManager::getMainModule(void) {

	debug("WFM::getMainModule() = %08x\n", this->mainModuleHandle);

	return this->mainModuleHandle;
}

int CWFileManager::Function_9(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_9(%d) = -1\n", a);
#endif

	return -1;
}

// This is a shortcut for open ...
int CWFileManager::Open2(CJArchiveFm *fm, const char *filename, int access, int unknown) {
#if DEBUG_PRINT_FILES == 1
	debug("WFM::Open2(0x%08x, \"%s\", 0x%08x, 0x%08x) = 0\n", fm, filename, access, unknown);
#endif

	fm->p15 = 1;
	fm->fm_instance = (int*)this;


	int handle = this->Open(filename, access, unknown);

	fm->hFile = handle;

	// Magic flag stuff that is hopefully not used -.-
	fm->p14 = (access >> 30) & 1;

	if (fm->p14 != 0) {
		fm->p20 = fm->p28;
	} else {
		fm->p20 = fm->p24;
	}

	if (fm->hFile == -1) {
		return 0;
	}

	return 1;
}

int CWFileManager::Open(const char *filename, int access, int unknown) {
	int dwShareMode = 0;
	int dwCreationDistribution = 0;

	if (access == 0x40000000) 
	{
		dwCreationDistribution = CREATE_ALWAYS; // 0x2
	} 
	else
	{
		dwCreationDistribution = OPEN_EXISTING; // 0x3

		if (access == 0x80000000) 
		{
			dwShareMode = FILE_SHARE_READ;
		}
	}

	// Bugfix #1
	if (filename[0] == '\\') {
		filename++;
	}

	SetCurrentDirectory(this->current_dir);

	HANDLE hFile = CreateFile(filename, access, dwShareMode, 0, dwCreationDistribution, FILE_ATTRIBUTE_ARCHIVE, 0);

	
	debug("WFM::Open(\"%s\", 0x%x, 0x%x) = 0x%x\n", filename, access, unknown, (int)hFile);

	// Example filtering
	if (strstr(filename, "nvm")) {
		debug("Opening File in %s\n", filename);
	}

#if DEBUG_PRINT_NOTFOUND == 1
	if (hFile == INVALID_HANDLE_VALUE) {
		debug("Error opening file: %s%s\n", this->current_dir, filename);
	}
#endif
	
	return (int)hFile;
}

int CWFileManager::Function_12(void)  {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_12() = -1\n");
#endif
	return -1;
}


int CWFileManager::Function_13(void)  {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_13() = 0\n");
#endif
	return 0;
}

int CWFileManager::Function_14(int a, int b, int c)  {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_14(%d, %d, %d) = 0\n", a, b, c);
#endif

	MessageBox(0, "Cannot exec Function_14", "Error", MB_OK);

	return 0;
}

int CWFileManager::Function_15(char* fullpath, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_15(\"%s\", %08x) = 0\n", fullpath, b);
#endif
	MessageBox(0, "Cannot exec Function_15", "Error", MB_OK);

	return -1;
}

int CWFileManager::Delete(int hFile) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Delete(%08x) = 0\n", hFile);
#endif

	return 0;
}

int CWFileManager::Close(int hFile) {
#if DEBUG_PRINT_FILES == 1
	debug("WFM::Close(%08x) = 0\n", hFile);
#endif
	return CloseHandle((HANDLE)hFile);
}


int CWFileManager::Read(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten) {

	int ret = ReadFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	debug("WFM::Read(%08x, %08x, %d, %d) = %d\n", hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, ret);

	return ret;
}

int CWFileManager::Write(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten) {

	int ret = WriteFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	debug("WFM::Write(%08x, %08x, %d, %d) = %d\n", hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, ret);

	return ret;
}

char* CWFileManager::getCmdLine_Path(void){
	debug("WFM::getCmdLine_Path() = \"Silkroad.exe\"\n");
	return "Silkroad.exe";
}

char* CWFileManager::getCmdLine_Args(void) {
	debug("WFM::getCmdLine_Args() = \"/22 0 0\"\n");
	return "/22 0 0";
}


void CWFileManager::getShit(shit_t* shit) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::getShit(0x%x)\n", shit);

#endif
	shit->a = 0;
	shit->b = 0;
}

int CWFileManager::setShit(int a, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::setShit(0x%08x, 0x%08x) = 0\n", a, b);
#endif

	return 0;
}


int CWFileManager::CreateDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = CreateDirectory(name);

	debug("WFM::CreateDirectory(\"%s\") = 0x%x\n", name, ret);

	return ret;
}

int CWFileManager::RemoveDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = RemoveDirectory(name);

	debug("WFM::RemoveDirectory(\"%s\") = 0x%08x\n", name, ret);

	return ret;
}

bool CWFileManager::ResetDirectory(void) {

	bool ret = SetCurrentDirectory(this->root_dir);
	GetCurrentDirectory(sizeof(this->current_dir), this->current_dir);

	int len = strlen(this->current_dir);

	if (this->current_dir[len] != '\\') {
		strcat_s(this->current_dir, sizeof(this->current_dir), "\\");
	}

	debug("WFM::ResetDirectory() = %d\n" , ret);

	debug("Reseting to: %s\n", this->root_dir);
	debug("Current Directory is now: %s\n", this->current_dir);

	return ret;
}

bool CWFileManager::ChangeDirectory(char* dirname) {

	if (dirname[0] == 0) {
		return 1;
	}

	SetCurrentDirectory(this->current_dir);

	bool ret = SetCurrentDirectory(dirname);

	GetCurrentDirectory(sizeof(this->current_dir), this->current_dir);

	int len = strlen(this->current_dir);

	if (this->current_dir[len] != '\\') {
		strcat_s(this->current_dir, sizeof(this->current_dir), "\\");
	}

	debug("WFM::ChangeDirectory(\"%s\") = %d\n", dirname, ret);

	return ret;
}

int CWFileManager::GetDirectoryName(size_t buffersize, char* Dst) {

	strcpy_s(Dst, buffersize, this->current_dir);

	int len = strlen(Dst);

	debug("WFM::GetDirectoryName(%d, %08x) = %d\n", buffersize, Dst, len);

	return len;
}

int CWFileManager::SetVirtualPath(char *path) {
	strcpy_s(this->root_dir, sizeof(this->root_dir), path);
	strcpy_s(this->current_dir, sizeof(this->current_dir), path);

	debug("WFM::SetVirtualPath(%08x) = 1\n", path);

	return 1;
}

int CWFileManager::GetVirtualPath(char* dest) {
	strcpy_s(dest, sizeof(this->current_dir), this->current_dir);

	debug("WFM::SetVirtualPath(%08x) = 1\n", dest);

	return 1;
}

searchresult_t* CWFileManager::FindFirstFile(searchresult_t* search, char* filename, result_entry_t* entry) {

	debug("WFM::FindFirstFile(%08x, %08x, %08x) = 0\n", search, filename, entry);

	search->success = 0;

	if (this->bListMoreFiles >= 0) {
		
		search->success = 1;

		entry->type = ENTRY_FILE;

		
		entry->timestamp.dwLowDateTime = 0x80000;

		entry->size = 1337;



		strcpy_s(entry->name, sizeof(entry->name), "Benis.txt");
		
		this->bListMoreFiles--;
	}


	return search;
}

int CWFileManager::FindNextFile(searchresult_t* search, result_entry_t* entry) {

	debug("WFM::FindNextFile(%08x, %08x) = 0", search, entry);

	search->success = 0;

	if (this->bListMoreFiles >= 0) {
		
		search->success = 1;

		entry->type = ENTRY_FILE;

		strcpy_s(entry->name, sizeof(entry->name), "Benis.txt");
		
		this->bListMoreFiles--;
	}


	return 0;
}

int CWFileManager::FindClose(int a) {
	debug("WFM::FindClose(%08x) = 0\n", a);

	// Should always return 1 ...
	this->bListMoreFiles = 1;
	return 0;
}

int CWFileManager::FileNameFromHandle(int hFile, char* dst, size_t count) {

	char buffer[512] = {0};

	DWORD ret = GetFinalPathNameByHandle((HANDLE)hFile, buffer, sizeof(buffer), 0);

	if (ret == ERROR_PATH_NOT_FOUND) {
		debug("WFM::FileNameFromHandle(%08x, %08x, %08x) = 0\n", hFile, dst, count);
		return 0;
	}

	// \\?\D:\Chronyc ..
	strcpy_s(dst, count, &(buffer[4 + strlen(this->root_dir)]));

	for (int i = 0; dst[i] != 0; i++) {
		dst[i] = tolower(dst[i]);
	}

	debug("WFM::FileNameFromHandle(%08x, %08x, %08x) = 1\n", hFile, dst, count);
	return 1;
}


int CWFileManager::GetFileSize(int hFile, LPDWORD lpFileSizeHigh) {
	int ret = ::GetFileSize((HANDLE)hFile, lpFileSizeHigh);
	
	debug("WFM::GetFileSize(%d, %08x) = %d\n", hFile, lpFileSizeHigh, ret);

	return ret;
}

BOOL CWFileManager::GetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {
	int ret = ::GetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	debug("WFM::GetFileTime(%08x, %08x, %08x) = %d\n", hFile, lpCreationTime, lpLastWriteTime, ret);

	return ret;
}

BOOL CWFileManager::SetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {

	int ret = ::SetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	debug("WFM::SetFileTime(%08x, %08x, %08x) = %d\n", hFile, lpCreationTime, lpLastWriteTime, ret);

	return ret;
}

int CWFileManager::Seek(int hFile, LONG lDistanceToMove, DWORD dwMoveMethod) {

	int ret = SetFilePointer((HANDLE)hFile, lDistanceToMove, 0, dwMoveMethod);
	
	debug("WFM::Seek(%08x, %d, %d) = %d\n", hFile, lDistanceToMove, dwMoveMethod);

	return ret;
}


int CWFileManager::get_hwnd(void) {
	debug("WFM::get_hwnd() = %08x\n", this->hwnd);

	return this->hwnd;
}

void CWFileManager::set_hwnd(int nhwnd) {
	debug("WFM::set_hwnd(%08x)\n", nhwnd);

	this->hwnd = nhwnd;
}

void CWFileManager::set_error_handler(error_handler_t callback) {
	debug("WFM::set_error_handler(0x%08x)\n", callback);

	this->error_handler = callback;
}

int CWFileManager::Function_42(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_42(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);

#endif
	return 0;
}

int CWFileManager::ImportFile(char *srcdir, char *dstdir, char *filename, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::ImportFile(\"%s\", \"%s\", \"%s\", %08x) = 0\n", srcdir, dstdir, filename, d);
#endif

	return 0;
}

int CWFileManager::Function_44(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_44(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);

#endif
	return 0;
}

int CWFileManager::Function_45(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_45(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);
#endif

	return 0;
}


int CWFileManager::file_exists(char* name, int flags) {

	char buffer[512];

	strcpy_s(buffer, sizeof(buffer), current_dir);
	strcat_s(buffer, sizeof(buffer), name);

	int attrib = GetFileAttributes(buffer);

	int ret = 0; // File found

	if (attrib == INVALID_FILE_ATTRIBUTES) {
		ret = -1; // File not found
	}

	debug("WFM::file_exists(\"%s\", %08x) = %d", name, flags, ret);

	return ret;
}

int CWFileManager::Function_49(void) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_49() = 0");
#endif

	return 0;
}

int CWFileManager::Function_50(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function_50(0x%08x) = 0", a);
#endif

	return 0;
}

int CWFileManager::Function53(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function53(0x%08x) = 0", a);

#endif
	return 0;
}

int CWFileManager::Function54() {
#if DEBUG_PRINT_UNKNOWN == 1
	debug("WFM::Function54() = 0");
#endif
	return 0;
}
