#pragma once 

#include <Windows.h>
#include <stdio.h>

#include "shit_t.h"
#include "CJArchiveFm.h"

#define FM_VERSION 0x1007


typedef BOOL (*error_handler_t)(void);

class IFileManager
{
public:
	virtual int get_mode(void) = 0; //returns the container-mode (1 for CP, 2 for CW)
	virtual int Function_1(int, int) = 0; //
	virtual int Function_2(int, int) = 0; //

	virtual int CreateContainer(const char *filename,  const char *password) = 0; //simliar to OpenContainer, but no mode
	virtual int OpenContainer(const char *filename, const char* password, int mode) = 0; //
	virtual int CloseContainer(void) = 0; //
	virtual int IsOpen(void) = 0; //

	virtual int Function_7(void) = 0; //Similar in both implementations
	virtual int getMainModule(void) = 0; //returns main module handle, called in F49 
	virtual int Function_9(int) = 0; //CWF returns -1


	virtual int Open2(CJArchiveFm* fm, const char *filename, int access, int unknown) = 0;
	virtual int Open(const char *filename, int access, int unknown) = 0; //

	virtual int Function_12(void) = 0; //return -1
	virtual int Function_13(void) = 0; //return 0
	virtual int Function_14(int, int, int) = 0; //
	virtual int Function_15(char* fullpath, int) = 0; //
	virtual int Function_16(int) = 0; //
	virtual int Close(int index) = 0; //
	virtual int Read(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten) = 0;
	virtual int Write(int hFile, char* lpBuffer, int nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten) = 0;


	virtual char* getCmdLine_Path(void) = 0; //
	virtual char* getCmdLine_Args(void) = 0; //
	virtual void getShit(shit_t* shit) = 0; //get shit
	virtual int setShit(int a, int b) = 0; //set shit

	virtual int CreateDirectory(const char* name) = 0; //Create directory
	virtual int RemoveDirectory(const char* name) = 0; //Remove directory
	virtual bool ResetDirectory(void) = 0; //
	virtual bool ChangeDirectory(char* dirname) = 0; //
	virtual int GetDirectoryName(size_t buffersize, char* Dst) = 0; //
	
	
	virtual int SetVirtualPath(char *path) = 0; //set root
	virtual int GetVirtualPath(char* dest) = 0; //similar on both impl
	
	virtual int Function_31(int, char* filename, int) = 0; //Find First File
	virtual int Function_32(int, int) = 0; //find next file
	virtual int Function_33(int) = 0; //find close
	virtual int FileNameFromHandle(int hFile, char* dst, size_t count) = 0; //GetFileName
	virtual int GetFileSize(int hFile, LPDWORD lpFileSizeHigh) = 0; //
	virtual BOOL GetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) = 0; //
	virtual BOOL SetFileTime(int hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastWriteTime) = 0; //
	virtual int Seek(int hFile, LONG lDistanceToMove, DWORD dwMoveMethod) = 0; //
	virtual int get_hwnd(void) = 0; //
	virtual void set_hwnd(int) = 0; //
	virtual void set_error_handler(error_handler_t callback) = 0; //sets a callback
	virtual int Function_42(int, int, int, int) = 0; //Search file on disk (historic code?)
	virtual int Function_43(int, int, int, int) = 0; //open file(s)
	virtual int Function_44(int, int, int, int) = 0; //create directories on disk
	virtual int Function_45(int, int, int, int) = 0; //Open File(s) and write

	// Returns: 0 on found, -1 on not found
	virtual int file_exists(char* name, int flags) = 0; //
	
	// Shows an open file dialog
	virtual int ShowDialog(int*);
	virtual int Function_48(int a, int b, int c); //
	virtual int Function_49(void) = 0; //
	virtual int Function_50(int) = 0; //returns zero in both impl.
	
	// get the version of this file manager
	virtual int getVersion(void);

	//prompt error if version mismatch 
	virtual int checkVersion(int version);

	virtual int Function53(int) = 0; //
	virtual int Function54() = 0; //
	virtual ~IFileManager(void) {

	};

};//Size=0x0004
