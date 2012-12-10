/////////////////////////////////////////////////
/// HeightMap.h
/// Created: September 28, 2009
/////////////////////////////////////////////////

#include "HeightMap.h"

HeightMap::HeightMap()
: m_MapLoaded(false)
{ }

HeightMap::~HeightMap()
{
	free(m_HeightData);
}

bool HeightMap::LoadHeightMap(std::string FileName)
{
	m_MapLoaded = false;

	fopen_s(&m_File, FileName.c_str(), "rb");
	if (!m_File == NULL)
		return false;
	fread(&m_FileHeader, sizeof(FileHeader), 1, m_File);
	if (m_FileHeader.FileType != 0x4D42)
	{
		fclose(m_File);
		return false;
	}

	fread(&m_InfoHeader, sizeof(InfoHeader), 1, m_File);

	fseek(m_File, m_FileHeader.Offset, SEEK_SET);

	m_HeightData = (HeightData*)malloc(m_InfoHeader.SizeImage);

	if (!m_HeightData)
	{
		free(m_HeightData);
		fclose(m_File);
		return false;
	}

	fread(m_HeightData, m_InfoHeader.SizeImage, 1, m_File);

	if (m_HeightData == NULL)
	{
		fclose(m_File);
		return false;
	}

	for (m_ImageIndex = 0; m_ImageIndex < m_InfoHeader.SizeImage; m_ImageIndex += 3)
	{
		m_TempRGB = m_HeightData[m_ImageIndex];
		m_HeightData[m_ImageIndex] = m_HeightData[m_ImageIndex + 2];
		m_HeightData[m_ImageIndex + 2] = m_TempRGB;
	}

	fclose(m_File);

	return m_MapLoaded = true;
}