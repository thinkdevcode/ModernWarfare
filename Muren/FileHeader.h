/////////////////////////////////////////////////
/// FileHeader.h
/// Created: September 28, 2009
/////////////////////////////////////////////////

#ifndef _FileHeader_
#define _FileHeader_

#include <windows.h>

struct FileHeader
{
	WORD	FileType;	//specifies the file type
	DWORD	Size;		//specifies the size in bytes of the bitmap file
	WORD	Reserved1;  //reserved; must be 0
	WORD	Reserved2;  //reserved; must be 0
	DWORD	Offset;		//species the offset in bytes from the bitmapfileheader to the bitmap bits
};

#endif