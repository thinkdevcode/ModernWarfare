/////////////////////////////////////////////////
/// MapManager.h
/// Created: September 14, 2009
/////////////////////////////////////////////////

#ifndef _MapManager_
#define _MapManager_

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////
/// MapManager:
///		Handles the game map. Loads maps, handles
///		resources and positions, controls 
///		scrolling around map, etc.
/////////////////////////////////////////////////

namespace MapManager
{
	void Initialize();
	void Event(sf::Event& Event);
	void LoadMap(sf::Image &Tile, sf::Uint32 Size);
	void Render();
	void Scroll();

	void SetScrollSpeed(float Speed);
	void SetScrollBuffer(float Buffer);
	bool GetMapLoaded();

	namespace
	{
		sf::Int32					ScrollX;			///< Current X coord (window)
		sf::Int32					ScrollY;			///< Current Y coord (window)
		sf::Int32					WindowHeight;		///< RenderWindow Height
		sf::Int32					WindowWidth;		///< RenderWindow Width
		std::vector<sf::Sprite>		Layer0;				///< Layer 0 of map sprites
		sf::Uint32					MapSize;			///< Size of map (across or down)
		float						ScrollTime;			///< Variable to keep scrolling constant
		bool						MapLoaded;			///< Is map loaded?
		float						ScrollingSpeed;		///< How fast map scrolls (default: 850)
		float						ScrollingBuffer;	///< Buffer for edge of screen (default: 175)
	}
}



#endif