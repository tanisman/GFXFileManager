#pragma once

#include "IFileManager.h"

class CJArchiveFm
{
public:
	char pad_0x0000[0x4]; //0x0000

	int *fm_instance; //0x0004 ptr to object

	int hFile; //0x0008 filehandle

	char pad_0x000C[0x8]; //0x000C

	unsigned char p14; //0x0014 
	unsigned char p15; //0x0015 

	char pad_0x0016[0xA]; //0x0016
	int p20; //0x0020 
	int p24; //0x0024 
	int p28; //0x0028 

};//Size=0x002C

