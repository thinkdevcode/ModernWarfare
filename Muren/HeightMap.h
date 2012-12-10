/////////////////////////////////////////////////
/// HeightMap.cpp
/// Created: September 28, 2009
/////////////////////////////////////////////////

#ifndef _HeightMap_
#define _HeightMap_

#include <SFML/Graphics.hpp>

#include "FileHeader.h"
#include "InfoHeader.h"

typedef unsigned char HeightData;

class HeightMap
{
public:
	HeightMap();
	~HeightMap();

	bool LoadHeightMap(std::string FileName);
protected:
	FILE*			m_File;
	FileHeader		m_FileHeader;
	InfoHeader		m_InfoHeader;
	HeightData*		m_HeightData;
	sf::Uint32		m_ImageIndex;
	unsigned char	m_TempRGB;
	bool			m_MapLoaded;

};

#endif