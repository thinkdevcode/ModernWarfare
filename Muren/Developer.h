/////////////////////////////////////////////////
/// Developer.h
/// Created: September 13, 2009
/////////////////////////////////////////////////

#ifndef _Developer_
#define _Developer_

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////
/// Developer:
///		Handles all developer tasks within the
///		game such as handling developer commands 
///		and displaying information to console and
///		game window.
/////////////////////////////////////////////////

namespace Developer
{
	void Initialize();

	void Event(sf::Event& Event);
	void Render();
	void UpdateFPS();
	void UpdateCoords();

	bool GetShowFPS();
	void SetShowFPS(bool Show);

	bool GetShowCoords();
	void SetShowCoords(bool Show);

	namespace
	{
		bool				ShowFPS;			///< Display FPS?
		bool				ShowCoords;			///< Display Coords?
		sf::String			Coords;				///< String for displaying the mouse coords
		sf::String			FPS;				///< String for displaying the current FPS
		sf::Clock			FPSTimer;			///< Timer used for calculating FPS
		sf::Vector2f		MouseGUICoords;		///< 2D Vector for game coords
		sf::Vector2i		MouseWCoords;		///< 2D Vector for window coords
		float				FrameRate;			///< Keeps the framerate
		char				FPSBuffer[64];		///< Buffer for writing FPS to String
		char				CoordBuffer[128];	///< Buffer for writing coords to String
	}
}

#endif