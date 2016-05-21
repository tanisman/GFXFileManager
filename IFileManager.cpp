#define _CRT_SECURE_NO_WARNINGS
#include "IFileManager.h"
#include <iostream>

int IFileManager::getVersion(void) {
	std::cout << "FM::getVersion()";
	return FM_VERSION;
};


int IFileManager::checkVersion(int version) {
	

	if (version != FM_VERSION) {
		std::cout << "FM::checkVersion(0x" << std::hex << version << ") = 0";
		
		char buffer[256];

		sprintf(buffer, "Dll Version(%x)\nNecessary Version(%x)", version, FM_VERSION);

		MessageBox(0, buffer, "Invalid Version(GFXFileManager.dll(Check Version))", MB_OK);

		return 0;
	}

	std::cout << "FM::checkVersion(0x" << std::hex << version << ") = 1";
	return 1;
};

int IFileManager::ShowDialog(int* initstruct) {
	std::cout << "FM::checkVersion(0x" << std::hex << initstruct << ") = 0";

	return 0;
};

int IFileManager::Function_48(int funptr, int b, int c) {
	std::cout << "FM::Function_48(0x" << std::hex << funptr << ", " << b << ", " << c << ") = 1";
	return 1;
}

