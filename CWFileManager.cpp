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

int CWFileManager::get_mode() {
	std::cout << "WFM::get_mode() = 1";

	return 1;
}

int CWFileManager::Function_1(int a, int b) {

	if (a == 2) {
		bSomething = (b == 0) ? 0 : 1;
	}

#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_1(" << a << ", " << b << ") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_2(int a, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_2(" << a << ", " << b << ") = 0" << std::endl;
#endif

	MessageBox(0, "Cannot exec Function_2", "Error", MB_OK);

	return 0;
}

int CWFileManager::CreateContainer(const char *filename, const char *password) {

	std::cout << "WFM::CreateContainer(\"" << filename << "\", \"" << password << "\") = 0" << std::endl;

	return 0;
}

int CWFileManager::OpenContainer(const char *filename, const char* password, int mode) {

	std::cout << "WFM::OpenContainer(\"" << filename << "\", \"" << password << "\", 0x" << std::hex << mode << ") = 1" << std::endl;

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

	std::cout << "WFM::CloseContainer() = 1" << std::endl;

	return 1;
}

int CWFileManager::IsOpen() {

	std::cout << "WFM::IsOpen() = " << this->bIsOpen << std::endl;

	return bIsOpen;
}

int CWFileManager::Function_7() {
	// This parses something like a list ...
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_7() = 1" << std::endl;
#endif
	MessageBox(0, "Cannot exec Function_7", "Error", MB_OK);

	return 1;
}

int CWFileManager::getMainModule(void) {

	std::cout << "WFM::getMainModule() = " << std::hex << this->mainModuleHandle << std::endl;

	return this->mainModuleHandle;
}

int CWFileManager::Function_9(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_9(" << a << ") = -1";
#endif

	return -1;
}

// This is a shortcut for open ...
int CWFileManager::Open2(CJArchiveFm *fm, const char *filename, int access, int unknown) {
#if DEBUG_PRINT_FILES == 1
	std::cout << "WFM::Open2(" 
		<< std::hex << fm
		<< ", \"" << filename << "\""
		<< ", " << std::hex << access
		<< ", " << std::hex << unknown
		<< ") = 0" << std::endl;
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

#if DEBUG_PRINT_FILES == 1
	std::cout << "WFM::Open("
		<< "\"" << filename << "\""
		<< ", 0x" << std::hex << access
		<< ", 0x" << std::hex << unknown
		<< ") = 0x" << std::hex << (int)hFile << std::endl;
#endif

	// Example filtering
	if (strstr(filename, "nvm")) {
		std::cout << "Opening File in " << this->current_dir << filename << std::endl;
	}

#if DEBUG_PRINT_NOTFOUND == 1
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Error opening file: " << this->current_dir << filename << std::endl;
	}
#endif
	
	return (int)hFile;
}

int CWFileManager::Function_12(void)  {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_12() = -1" << std::endl;
#endif
	return -1;
}


int CWFileManager::Function_13(void)  {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_13() = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_14(int a, int b, int c)  {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_14("
		<< std::hex << a
		<< ", " << std::hex << b
		<< ", " << std::hex << c
		<< ") = 0" << std::endl;
#endif
	MessageBox(0, "Cannot exec Function_14", "Error", MB_OK);

	return 0;
}

int CWFileManager::Function_15(char* fullpath, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_15("
		<< "\"" << fullpath << "\""
		<< ", " << std::hex << b
		<< ") = 0" << std::endl;
#endif
	MessageBox(0, "Cannot exec Function_15", "Error", MB_OK);

	return -1;
}

int CWFileManager::Function_16(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_16("
		<< std::hex << a
		<< ") = 0" << std::endl;
#endif
	MessageBox(0, "Cannot exec Function_16", "Error", MB_OK);

	return 0;
}

int CWFileManager::Close(int index) {
#if DEBUG_PRINT_FILES == 1
	std::cout << "WFM::Close(0x"
		<< std::hex << index
		<< ") = 0" << std::endl;
#endif
	return CloseHandle((HANDLE)index);
}


int CWFileManager::Read(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten) {

	/*std::cout << "WFM::Read("
	<< std::hex << hFile
	<< ", 0x" << std::hex << (int)lpBuffer
	<< ", " << nNumberOfBytesToWrite
	<< ", 0x" << std::hex << lpNumberOfBytesWritten
	<< ") = ";
	*/
	int ret = ReadFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	// std::cout << ret << std::endl;

	return ret;
}

int CWFileManager::Write(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten) {

	int ret = WriteFile((HANDLE)hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, 0);

	std::cout << "WFM::Read("
		<< std::hex << hFile
		<< ", 0x" << std::hex << (int)lpBuffer
		<< ", " << nNumberOfBytesToWrite
		<< ", 0x" << std::hex << lpNumberOfBytesWritten
		<< ") = " << ret << std::endl;

	return ret;
}

char* CWFileManager::getCmdLine_Path(void){
	std::cout << "WFM::getCmdLine_Path() = \"Silkroad.exe\"" << std::endl;
	return "Silkroad.exe";
}

char* CWFileManager::getCmdLine_Args(void) {
	std::cout << "WFM::getCmdLine_Args() = \"/22 0 0\"" << std::endl;
	return "/22 0 0";
}


void CWFileManager::getShit(shit_t* shit) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::getShit("
		<< "0x" << std::hex << shit
		<< ")" << std::endl;
#endif
	shit->a = 0;
	shit->b = 0;
}

int CWFileManager::setShit(int a, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::setShit("
		<< "0x" << std::hex << a
		<< "0x" << std::hex << b
		<< ") = 0" << std::endl;
#endif

	return 0;
}


int CWFileManager::CreateDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = CreateDirectory(name);

	std::cout << "WFM::CreateDirectory("
		<< "\"" << name << "\""
		<< ")  =0x" << std::hex  << ret << std::endl;

	return ret;
}

int CWFileManager::RemoveDirectory(const char* name) {

	SetCurrentDirectory(this->current_dir);
	int ret = RemoveDirectory(name);


	std::cout << "WFM::RemoveDirectory("
		<< "\"" << name << "\""
		<< ") = 0x" << std::hex << ret << std::endl;

	return ret;
}

bool CWFileManager::ResetDirectory(void) {

	bool ret = SetCurrentDirectory(this->root_dir);
	GetCurrentDirectory(sizeof(this->current_dir), this->current_dir);

	int len = strlen(this->current_dir);

	if (this->current_dir[len] != '\\') {
		strcat_s(this->current_dir, sizeof(this->current_dir), "\\");
	}

	std::cout << "WFM::ResetDirectory() = " << ret << std::endl;

	std::cout << "Reseting to: " << this->root_dir << std::endl;
	std::cout << "Current Directory is now: " << this->current_dir << std::endl;

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

	std::cout << "WFM::ChangeDirectory("
		<< "\"" << dirname << "\""
		<< ") = " << ret << std::endl;

	return ret;
}

int CWFileManager::GetDirectoryName(size_t buffersize, char* Dst) {

	strcpy_s(Dst, buffersize, this->current_dir);

	int len = strlen(Dst);

	std::cout << "WFM::GetDirectoryName("
		<< buffersize
		<< ", \"" << Dst << "\""
		<< ") = " << len << std::endl;

	return len;
}

int CWFileManager::SetVirtualPath(char *path) {
	strcpy_s(this->root_dir, sizeof(this->root_dir), path);
	strcpy_s(this->current_dir, sizeof(this->current_dir), path);

	std::cout << "WFM::SetVirtualPath("
		<< "\"" << path << "\")" << std::endl;
	return 1;
}

int CWFileManager::GetVirtualPath(char* dest) {
	strcpy_s(dest, sizeof(this->current_dir), this->current_dir);

	std::cout << "WFM::SetVirtualPath("
		<< std::hex << dest << ")" << std::endl;

	return 1;
}

int CWFileManager::Function_31(int a, char* filename, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_31("
		<< std::hex << a << ", " 
		<< std::hex << filename << ", "
		<< std::hex << b
		<< ") = 0" << std::endl;
#endif

	return 0;
}


int CWFileManager::Function_32(int a, int b) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_32("
		<< std::hex << a << ", " 
		<< std::hex << b
		<< ") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_33(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_33("
		<< std::hex << a 
		<< ") = 0" << std::endl;
#endif
	// Should always return 1 ...
	return 0;
}

int CWFileManager::FileNameFromHandle(int hFile, char* dst, size_t count) {
	/*std::cout << "WFM::FileNameFromHandle("
	<< std::hex << hFile << ", "
	<< std::hex << (int)dst << ", "
	<< std::hex << count
	<< ") = 0" << std::endl;
	*/
	char buffer[512] = {0};

	DWORD ret = GetFinalPathNameByHandle((HANDLE)hFile, buffer, sizeof(buffer), 0);

	if (ret == ERROR_PATH_NOT_FOUND) {
		return 0;
	}

	// \\?\D:\Chronyc ..
	strcpy_s(dst, count, &(buffer[4 + strlen(this->root_dir)]));

	for (int i = 0; dst[i] != 0; i++) {
		dst[i] = tolower(dst[i]);
	}

	return 1;
}


int CWFileManager::GetFileSize(int hFile, LPDWORD lpFileSizeHigh) {
	int ret = ::GetFileSize((HANDLE)hFile, lpFileSizeHigh);
	/*
	std::cout << "WFM::GetFileSize("
	<< std::hex << hFile << ", "
	<< std::hex << lpFileSizeHigh
	<< ") = " << ret << std::endl;
	*/
	return ret;
}

BOOL CWFileManager::GetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {
	int ret = ::GetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	std::cout << "WFM::GetFileTime("
		<< std::hex << hFile << ", "
		<< std::hex << lpCreationTime << ", "
		<< std::hex << lpLastWriteTime
		<< ") = " << ret << std::endl;

	return ret;
}



BOOL CWFileManager::SetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) {

	std::cout << "WFM::SetFileTime("
		<< std::hex << hFile << ", "
		<< std::hex << lpCreationTime << ", "
		<< std::hex << lpLastWriteTime
		<< ") = ";

	int ret = ::SetFileTime((HANDLE)hFile, lpCreationTime, 0, lpLastWriteTime);

	std::cout << ret << std::endl;

	return ret;
}

int CWFileManager::Seek(int hFile, LONG lDistanceToMove, DWORD dwMoveMethod) {

	int ret = SetFilePointer((HANDLE)hFile, lDistanceToMove, 0, dwMoveMethod);
	/*
	std::cout << "WFM::Seek("
	<< std::hex << hFile << ", "
	<< lDistanceToMove << ", "
	<< std::hex << dwMoveMethod
	<< ") = " << ret << std::endl;
	*/
	return ret;
}


int CWFileManager::get_hwnd(void) {
	std::cout << "WFM::get_hwnd() = " << this->hwnd << std::endl;

	return this->hwnd;
}

void CWFileManager::set_hwnd(int nhwnd) {
	std::cout << "WFM::set_hwnd("
		<< std::hex << nhwnd <<
		")" << std::endl;

	this->hwnd = nhwnd;
}

void CWFileManager::set_error_handler(error_handler_t callback) {

	std::cout << "WFM::set_error_handler(0x"
		<< std::hex << callback <<
		")" << std::endl;

	this->error_handler = callback;
}

int CWFileManager::Function_42(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_42("
		<< std::hex << a << ", "
		<< std::hex << b << ", "
		<< std::hex << c << ", "
		<< std::hex << d <<
		") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_43(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_43("
		<< std::hex << a << ", "
		<< std::hex << b << ", "
		<< std::hex << c << ", "
		<< std::hex << d <<
		") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_44(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_44("
		<< std::hex << a << ", "
		<< std::hex << b << ", "
		<< std::hex << c << ", "
		<< std::hex << d <<
		") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_45(int a, int b, int c, int d) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_45("
		<< std::hex << a << ", "
		<< std::hex << b << ", "
		<< std::hex << c << ", "
		<< std::hex << d <<
		") = 0" << std::endl;
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

	/*std::cout << "WFM::file_exists("
	<< "\"" << name << "\", "
	<< std::hex << flags
	<< ") = " << ret << std::endl;
	*/
	return ret;
}

int CWFileManager::Function_49(void) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_49() = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function_50(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function_50("
		<< std::hex << a
		<< ") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function53(int a) {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function53("
		<< std::hex << a
		<< ") = 0" << std::endl;
#endif
	return 0;
}

int CWFileManager::Function54() {
#if DEBUG_PRINT_UNKNOWN == 1
	std::cout << "WFM::Function54() = 0" << std::endl;
#endif
	return 0;
}
