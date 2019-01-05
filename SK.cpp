#define _WIN32_WINNT 0x0501

#include "SK.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
//#include <qtextedit.h>
//#include <qmessagebox.h>
#include <time.h>

#define BUFSIZE 1024            // ample space for our string buffer
#define FILESYSNAMEBUFSIZE 8192 // probably more than we need


softKey::softKey ()
{
}

softKey::~softKey()
{
}

int softKey::registraSK (const char fileName[])
{
	BOOL bFlag;           // generic results flag for return
	TCHAR PtBuf[BUFSIZE]; // string buffer for mount points
	DWORD dwSysFlags;     // flags that describe the file system
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];
	DWORD lpVolumeSerialNumber;  // volume serial number

	PtBuf[0] = WCHAR('C');
	PtBuf[1] = WCHAR(':');
	PtBuf[2] = WCHAR('\\');
	PtBuf[3] = 0;

	// _tcscpy (PtBuf, WCHAR("C:\\"));
	bFlag = GetVolumeInformation( PtBuf, NULL, 0, &lpVolumeSerialNumber, NULL,&dwSysFlags, FileSysNameBuf,
                         FILESYSNAMEBUFSIZE);
	if(!bFlag) {
		return -1;
	}

	lpVolumeSerialNumber ^= 0x9A8DE4C2;

	// Semente para o gerador pseudo-aleatorio
	srand( (unsigned)time( NULL ) );

	/* Sorteia 1024 numeros aleatorios */
	unsigned int FileKeyBuf[FILESYSNAMEBUFSIZE];
	for( int i=0; i < 1024;i++ ) {
		FileKeyBuf[i] = rand();
	}
	//textEditMsg->append(str);
	// localiza chave
	unsigned int index = lpVolumeSerialNumber % 1024;
	FileKeyBuf[index] = lpVolumeSerialNumber;

	// Grava arquivo
	FILE * stream;
	int numgrv;

	/* Open file in text mode: */
	if( (stream = fopen( fileName, "wb+" )) != NULL )
	{
		/* 1024 characteres para o stream */
		numgrv = fwrite( FileKeyBuf, sizeof( unsigned int ), 1024, stream );
		fclose( stream );
		return 1;
	} else
		return -2;
}


int softKey::verificaSK (const char fileName[])
{

	BOOL bFlag;           // generic results flag for return
	TCHAR PtBuf[BUFSIZE]; // string buffer for mount points
	DWORD dwSysFlags;     // flags that describe the file system
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];
	DWORD lpVolumeSerialNumber;  // volume serial number

	PtBuf[0] = WCHAR('C');
	PtBuf[1] = WCHAR(':');
	PtBuf[2] = WCHAR('\\');
	PtBuf[3] = 0;


	// _tcscpy (PtBuf, WCHAR("C:\\"));
	bFlag = GetVolumeInformation( PtBuf, NULL, 0, &lpVolumeSerialNumber, NULL,&dwSysFlags, FileSysNameBuf,
                         FILESYSNAMEBUFSIZE);
	if(!bFlag) {
		return -1;
	}

	lpVolumeSerialNumber ^= 0x9A8DE4C2;

	unsigned int FileKeyBuf[FILESYSNAMEBUFSIZE];

	// Le Arquivo
	FILE *stream;
	int numlido;

	/* Open file in text mode: */
	if( (stream = fopen( fileName, "rb+" )) == NULL )
		return -2;

	/* 1024 characteres lidos do stream */
	numlido = fread( FileKeyBuf, sizeof( unsigned int ), 1024, stream );
	fclose( stream );

	// localiza e testa a chave
	unsigned int index = lpVolumeSerialNumber % 1024;
	DWORD lpVolumeSerialNumberREAD;  // volume serial number lido do arq lic
	lpVolumeSerialNumberREAD = FileKeyBuf[index];
	if( lpVolumeSerialNumberREAD != lpVolumeSerialNumber ) {
		// SK incorreto
		return 0;
	}

	return 1;
}


