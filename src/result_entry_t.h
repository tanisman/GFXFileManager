#pragma once

#include <Windows.h>

enum entry_type : char {
	ENTRY_FOLDER = 1,
	ENTRY_FILE = 2
};

class result_entry_t
{
public:
	__int32 N0000001B; //0x0000 
	FILETIME timestamp;
	__int32 N0000001E; //0x000C 
	__int32 N0000001F; //0x0010 
	__int32 N00000020; //0x0014 
	__int32 N00000021; //0x0018 
	__int32 N00000022; //0x001C 
	__int32 size; //0x0020 
	entry_type type; //0x0024 1 = folder, 2 = file
	char name[90]; //0x0025 

};//Size=0x007F


