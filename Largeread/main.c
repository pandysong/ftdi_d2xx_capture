/*
	Simple example to read a large amount of data from a BM device.
	Device must have bitbang capabilities to enable this to work	

	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o largeread main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include <stdlib.h>
#include "../ftd2xx.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	char * pcBufRead;
	DWORD dwBytesRead;
	FILE * fh;
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;
	int iport;
    int baudrate;
    char *file_name;
    int cnt;
	
    if (argc < 4)
    {
        printf("Usage: %s port baudrate save_to\n", argv[0]);
        return -1;
    }
    sscanf(argv[1], "%d", &iport);
    sscanf(argv[2], "%d", &baudrate);
    file_name = argv[3];
	
	fh = fopen(file_name, "wb+");
	if(fh == NULL) {
		printf("Cant open source file\n");
		return 1;
	}
		
	ftStatus = FT_Open(iport, &ftHandle);
	if(ftStatus != FT_OK) {
		/* 
			This can fail if the ftdi_sio driver is loaded
		 	use lsmod to check this and rmmod ftdi_sio to remove
			also rmmod usbserial
		 */
		printf("FT_Open(%d) failed\n", iport);
		return 1;
	}

	pcBufRead = (char *)malloc(BUF_SIZE);
	FT_ResetDevice(ftHandle);
	FT_SetBaudRate(ftHandle, baudrate);
	FT_SetDtr(ftHandle);
	FT_SetRts(ftHandle);
	FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
	FT_SetTimeouts(ftHandle, 0, 0);				// infinite timeouts	
	FT_SetBitMode(ftHandle, 0xFF, 0);

    cnt = 0;
    while (1)
    {
        FT_Read(ftHandle, pcBufRead, BUF_SIZE, &dwBytesRead);
        cnt += dwBytesRead;
        fwrite(pcBufRead, 1, dwBytesRead, fh);
        printf("\rwritten: %d", cnt);
        fflush(stdout);
    }
	fclose(fh);
	free(pcBufRead);
	FT_Close(ftHandle);
	
	return 0;
}
