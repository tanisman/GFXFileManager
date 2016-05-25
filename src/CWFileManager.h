#pragma once

#include "IFileManager.h"


class CWFileManager : public IFileManager {
public:
	char root_dir[260]; //0x0004 
	char current_dir[260]; //0x0108 guessed ???
	__int32 bIsOpen; //0x020C 
	char pad_0x0210[0xC]; //0x0210
	DWORD mainModuleHandle; //0x021C Get by function_8 
	
	char pad_0x0220[0x1C]; //0x0220
	unsigned char bSomething; //0x023C bool
	
	char pad_0x023D[0x2B]; //0x023D
	
	error_handler_t error_handler; //0x0268 set by fun_A4 
	DWORD hwnd; //0x026C 
	
	char pad_0x0270[0x1D0]; //0x0270


	int bListMoreFiles;


public:
	virtual int get_mode(void);
	virtual int Function_1(int, int);
	virtual int Function_2(int, int);

	virtual int CreateContainer(const char *filename,  const char *password);
	virtual int OpenContainer(const char *filename, const char* password, int mode);
	virtual int CloseContainer(void);
	virtual int IsOpen(void);

	virtual int Function_7(void);
	virtual int getMainModule(void);
	virtual int Function_9(int);


	virtual int Open2(CJArchiveFm *fm, const char *filename, int access, int unknown);
	virtual int Open(const char *filename, int access, int unknown);

	virtual int Function_12(void);
	virtual int Function_13(void);
	virtual int Function_14(int, int, int);
	virtual int Function_15(char* fullpath, int);
	virtual int Delete(char *filename);
	virtual int Close(int index);

	virtual int Read(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten);
	virtual int Write(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten);


	virtual char* getCmdLine_Path(void);
	virtual char* getCmdLine_Args(void); 


	virtual void getShit(shit_t* shit); //get shit
	virtual int setShit(int a, int b); //set shit

	
	virtual int CreateDirectory(const char* name);
	virtual int RemoveDirectory(const char* name);

	virtual bool ResetDirectory(void);
	virtual bool ChangeDirectory(char* dirname);
	virtual int GetDirectoryName(size_t buffersize, char* Dst);

	virtual int SetVirtualPath(char *path);
	virtual int GetVirtualPath(char* dest);
	
	// Listing files 
	virtual searchresult_t* FindFirstFile(searchresult_t* search, char* pattern, result_entry_t* entry);
	virtual int FindNextFile(searchresult_t* search, result_entry_t* entry);
	virtual int FindClose(int);

	// File information
	virtual int FileNameFromHandle(int hFile, char* dst, size_t count); //GetFileName
	virtual int GetFileSize(int hFile, LPDWORD lpFileSizeHigh); //

	virtual BOOL GetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime); //
	virtual BOOL SetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime); //

	virtual int Seek(int hFile, LONG lDistanceToMove, DWORD dwMoveMethod);


	// error control
	virtual int get_hwnd(void);
	virtual void set_hwnd(int);
	virtual void set_error_handler(error_handler_t callback);


	// historic
	virtual int Function_42(int, int, int, int);
	virtual int ImportFile(char *srcdir, char *dstdir, char *filename, int d);
	virtual int Function_44(int, int, int, int);
	virtual int Function_45(int, int, int, int);



	virtual int file_exists(char* name, int flags);


	virtual int Function_49(void);
	virtual int Function_50(int);

	virtual int Function53(int); //
	virtual int Function54(); //

	virtual ~CWFileManager() { };

	CWFileManager() {
		this->bIsOpen = 0;
		this->bListMoreFiles = 1;
	}
};
