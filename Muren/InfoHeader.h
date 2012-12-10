/////////////////////////////////////////////////
/// InfoHeader.h
/// Created: September 28, 2009
/////////////////////////////////////////////////

#ifndef _InfoHeader_
#define _InfoHeader_

#include <windows.h>

struct InfoHeader
{
	DWORD	Size;				//specifies the number of bytes required by the struct
	LONG	Width;				//specifies width in pixels
	LONG	Height;				//species height in pixels
	WORD	Planes;				//specifies the number of color planes, must be 1
	WORD	BitCount;			//specifies the number of bit per pixel
	DWORD	Compression;		//spcifies the type of compression
	DWORD	SizeImage;			//size of image in bytes
	LONG	XPixelsPerMeter;	//number of pixels per meter in x axis
	LONG	YPixelsPerMeter;	//number of pixels per meter in y axis
	DWORD	ColorsUsed;			//number of colors used by the bitmap
	DWORD	ColorsImportant;	//number of colors that are important
};

#endif