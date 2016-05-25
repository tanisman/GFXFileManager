#include "CWFileManager.h"
#include <iostream>
#include <string>

#include "debug.h"


int CWFileManager::get_mode() {
	debug(DEBUG_OTHER, "WFM::get_mode() = 1\n");

	return 1;
}

int CWFileManager::Function_1(int a, int b) {

	if (a == 2) {
		bSomething = (b == 0) ? 0 : 1;
	}

	debug(DEBUG_UNKNOWN, "WFM::Function_1(%d , %d) = 0\n", a, b);

	return 0;
}

int CWFileManager::Function_2(int a, int b) {
	
	debug(DEBUG_UNKNOWN, "WFM::Function_2(%d , %d) = 0\n", a, b);

	_ERROR_MSGBOX();

	return 0;
}

int CWFileManager::CreateContainer(const char *filename, const char *password) {
	
	debug(DEBUG_CONTAINER, "WFM::CreateContainer(\"%s\", \"%s\") = 0\n", filename, password);

	return 0;
}

int CWFileManager::OpenContainer(const char *filename, const char* password, int mode) {

	debug(DEBUG_CONTAINER, "WFM::OpenContainer(\"%s\", \"%s\", 0x%08x) = 1\n", filename, password, mode);
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

	debug(DEBUG_CONTAINER, "WFM::CloseContainer() = 1\n");

	return 1;
}

int CWFileManager::IsOpen() {
	debug(DEBUG_CONTAINER, "WFM::IsOpen() = 0\n", this->bIsOpen);

	return bIsOpen;
}

int CWFileManager::Function_7() {
	// This parses something like a list ...

	debug(DEBUG_UNKNOWN, "WFM::Function_7() = 1\n");

	_ERROR_MSGBOX();

	return 1;
}

int CWFileManager::getMainModule(void) {

	debug(DEBUG_OTHER, "WFM::getMainModule() = %08x\n", this->mainModuleHandle);

	return this->mainModuleHandle;
}

int CWFileManager::Function_9(int a) {

	debug(DEBUG_UNKNOWN, "WFM::Function_9(%d) = -1\n", a);


	return -1;
}

// This is a shortcut for open ...
int CWFileManager::Open2(CJArchiveFm *fm, const char *filename, int access, int unknown) {

	debug(DEBUG_FILE, "WFM::Open2(0x%08x, \"%s\", 0x%08x, 0x%08x) = 0\n", fm, filename, access, unknown);


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

	
	debug(DEBUG_FILE, "WFM::Open(\"%s\", 0x%x, 0x%x) = 0x%x\n", filename, access, unknown, (int)hFile);

	// Example filtering
	if (strstr(filename, "nvm")) {
		debug(DEBUG_FILE_GEN, "Opening File in %s\n", filename);
	}

	if (hFile == INVALID_HANDLE_VALUE) {
		debug(DEBUG_FILE_NOTFOUND, "Error opening file: %s%s\n", this->current_dir, filename);
	}
	
	return (int)hFile;
}

int CWFileManager::Function_12(void)  {

	debug(DEBUG_UNKNOWN, "WFM::Function_12() = -1\n");

	return -1;
}


int CWFileManager::Function_13(void)  {

	debug(DEBUG_UNKNOWN, "WFM::Function_13() = 0\n");

	return 0;
}

int CWFileManager::Function_14(int a, int b, int c)  {

	debug(DEBUG_UNKNOWN, "WFM::Function_14(%d, %d, %d) = 0\n", a, b, c);


	_ERROR_MSGBOX();

	return 0;
}

int CWFileManager::Function_15(char* fullpath, int b) {

	debug(DEBUG_UNKNOWN, "WFM::Function_15(\"%s\", %08x) = 0\n", fullpath, b);

	_ERROR_MSGBOX();

	return -1;
}

int CWFileManager::Delete(char *filename) {

	debug(DEBUG_FILE, "WFM::Delete(\"%s\") = 0\n", filename);


	return 0;
}

int CWFileManager::Close(int hFile) {

	debug(DEBUG_FILE, "WFM::Close(%08x) = 0\n", hFile);

	return CloseHandle((HANDLE)hFile);
}


int CWFileManager::Read(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten) {

	int ret = ReadFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	debug(DEBUG_IO, "WFM::Read(%08x, %08x, %d, %d) = %d\n", hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, ret);

	return ret;
}

int CWFileManager::Write(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten) {

	int ret = WriteFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	debug(DEBUG_IO, "WFM::Write(%08x, %08x, %d, %d) = %d\n", hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, ret);

	return ret;
}

char* CWFileManager::getCmdLine_Path(void){
	debug(DEBUG_OTHER, "WFM::getCmdLine_Path() = \"Silkroad.exe\"\n");
	return "Silkroad.exe";
}

char* CWFileManager::getCmdLine_Args(void) {
	debug(DEBUG_OTHER, "WFM::getCmdLine_Args() = \"/22 0 0\"\n");
	return "/22 0 0";
}


void CWFileManager::getShit(shit_t* shit) {

	debug(DEBUG_OTHER, "WFM::getShit(0x%x)\n", shit);


	shit->a = 0;
	shit->b = 0;
}

int CWFileManager::setShit(int a, int b) {

	debug(DEBUG_OTHER, "WFM::setShit(0x%08x, 0x%08x) = 0\n", a, b);


	return 0;
}


int CWFileManager::CreateDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = CreateDirectory(name);

	debug(DEBUG_DIRECTORY, "WFM::CreateDirectory(\"%s\") = 0x%x\n", name, ret);

	return ret;
}

int CWFileManager::RemoveDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = RemoveDirectory(name);

	debug(DEBUG_DIRECTORY, "WFM::RemoveDirectory(\"%s\") = 0x%08x\n", name, ret);

	return ret;
}

bool CWFileManager::ResetDirectory(void) {

	bool ret = SetCurrentDirectory(this->root_dir);
	GetCurrentDirectory(sizeof(this->current_dir), this->current_dir);

	int len = strlen(this->current_dir);

	if (this->current_dir[len] != '\\') {
		strcat_s(this->current_dir, sizeof(this->current_dir), "\\");
	}

	debug(DEBUG_DIRECTORY, "WFM::ResetDirectory() = %d\n" , ret);

	debug(DEBUG_DIRECTORY_GEN, "Reseting to: %s\n", this->root_dir);
	debug(DEBUG_DIRECTORY_GEN, "Current Directory is now: %s\n", this->current_dir);

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

	debug(DEBUG_DIRECTORY, "WFM::ChangeDirectory(\"%s\") = %d\n", dirname, ret);

	return ret;
}

int CWFileManager::GetDirectoryName(size_t buffersize, char* Dst) {

	strcpy_s(Dst, buffersize, this->current_dir);

	int len = strlen(Dst);

	debug(DEBUG_DIRECTORY, "WFM::GetDirectoryName(%d, %08x) = %d\n", buffersize, Dst, len);

	return len;
}

int CWFileManager::SetVirtualPath(char *path) {
	strcpy_s(this->root_dir, sizeof(this->root_dir), path);
	strcpy_s(this->current_dir, sizeof(this->current_dir), path);

	debug(DEBUG_DIRECTORY, "WFM::SetVirtualPath(%08x) = 1\n", path);

	return 1;
}

int CWFileManager::GetVirtualPath(char* dest) {
	strcpy_s(dest, sizeof(this->current_dir), this->current_dir);

	debug(DEBUG_DIRECTORY, "WFM::GetVirtualPath(%08x) = 1\n", dest);

	return 1;
}

searchresult_t* CWFileManager::FindFirstFile(searchresult_t* search, char* pattern, result_entry_t* entry) {

	debug(DEBUG_SEARCH, "WFM::FindFirstFile(%08x, \"%s\", %08x) = 0\n", search, pattern, entry);

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

	debug(DEBUG_SEARCH, "WFM::FindNextFile(%08x, %08x) = 0\n", search, entry);

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
	debug(DEBUG_SEARCH, "WFM::FindClose(%08x) = 0\n", a);

	// Should always return 1 ...
	this->bListMoreFiles = 1;
	return 0;
}

int CWFileManager::FileNameFromHandle(int hFile, char* dst, size_t count) {

	char buffer[512] = {0};

	DWORD ret = GetFinalPathNameByHandle((HANDLE)hFile, buffer, sizeof(buffer), 0);

	if (ret == ERROR_PATH_NOT_FOUND) {
		debug(DEBUG_FILE, "WFM::FileNameFromHandle(%08x, %08x, %08x) = 0\n", hFile, dst, count);
		return 0;
	}

	// \\?\D:\Chronyc ..
	strcpy_s(dst, count, &(buffer[4 + strlen(this->root_dir)]));

	for (int i = 0; dst[i] != 0; i++) {
		dst[i] = tolower(dst[i]);
	}

	debug(DEBUG_FILE, "WFM::FileNameFromHandle(%08x, %08x, %08x) = 1\n", hFile, dst, count);
	return 1;
}


int CWFileManager::GetFileSize(int hFile, LPDWORD lpFileSizeHigh) {
	int ret = ::GetFileSize((HANDLE)hFile, lpFileSizeHigh);
	
	debug(DEBUG_FILE, "WFM::GetFileSize(%d, %08x) = %d\n", hFile, lpFileSizeHigh, ret);

	return ret;
}

BOOL CWFileManager::GetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {
	int ret = ::GetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	debug(DEBUG_FILE, "WFM::GetFileTime(%08x, %08x, %08x) = %d\n", hFile, lpCreationTime, lpLastWriteTime, ret);

	return ret;
}

BOOL CWFileManager::SetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {

	int ret = ::SetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	debug(DEBUG_FILE, "WFM::SetFileTime(%08x, %08x, %08x) = %d\n", hFile, lpCreationTime, lpLastWriteTime, ret);

	return ret;
}

int CWFileManager::Seek(int hFile, LONG lDistanceToMove, DWORD dwMoveMethod) {

	int ret = SetFilePointer((HANDLE)hFile, lDistanceToMove, 0, dwMoveMethod);
	
	debug(DEBUG_FILE, "WFM::Seek(%08x, %d, %d) = %d\n", hFile, lDistanceToMove, dwMoveMethod);

	return ret;
}


int CWFileManager::get_hwnd(void) {
	debug(DEBUG_OTHER, "WFM::get_hwnd() = %08x\n", this->hwnd);

	return this->hwnd;
}

void CWFileManager::set_hwnd(int nhwnd) {
	debug(DEBUG_OTHER, "WFM::set_hwnd(%08x)\n", nhwnd);

	this->hwnd = nhwnd;
}

void CWFileManager::set_error_handler(error_handler_t callback) {
	debug(DEBUG_OTHER, "WFM::set_error_handler(0x%08x)\n", callback);

	this->error_handler = callback;
}

int CWFileManager::Function_42(int a, int b, int c, int d) {

	debug(DEBUG_UNKNOWN, "WFM::Function_42(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);


	return 0;
}

int CWFileManager::ImportFile(char *srcdir, char *dstdir, char *filename, int d) {

	debug(DEBUG_FILE, "WFM::ImportFile(\"%s\", \"%s\", \"%s\", %08x) = 0\n", srcdir, dstdir, filename, d);


	return 0;
}

int CWFileManager::Function_44(int a, int b, int c, int d) {

	debug(DEBUG_UNKNOWN, "WFM::Function_44(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);


	return 0;
}

int CWFileManager::Function_45(int a, int b, int c, int d) {

	debug(DEBUG_UNKNOWN, "WFM::Function_45(%08x, %08x, %08x, %08x) = 0\n", a, b, c, d);


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

	debug(DEBUG_FILE, "WFM::file_exists(\"%s\", %08x) = %d", name, flags, ret);

	return ret;
}

int CWFileManager::Function_49(void) {

	debug(DEBUG_UNKNOWN, "WFM::Function_49() = 0");


	return 0;
}

int CWFileManager::Function_50(int a) {

	debug(DEBUG_UNKNOWN, "WFM::Function_50(0x%08x) = 0", a);


	return 0;
}

int CWFileManager::Function53(int a) {

	debug(DEBUG_UNKNOWN, "WFM::Function53(0x%08x) = 0", a);


	return 0;
}

int CWFileManager::Function54() {

	debug(DEBUG_UNKNOWN, "WFM::Function54() = 0");

	return 0;
}
