////////////////////////////////////////////////////////
/// MWEditor.cpp
/// Created: September 10, 2009
////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "../Muren/WinMainData.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////////////////////////////
	/// Assign useless data (in case needed)
	WinMainData WindowsData;
	WindowsData.hInstance = hInstance;
	WindowsData.hPrevInstance = hPrevInstance;
	WindowsData.lpCmdLine = lpCmdLine;
	WindowsData.nCmdShow = nCmdShow;

	/////////////////////////////////////////////////
	/// Create render window and provide settings
    sf::RenderWindow Editor;
	Editor.Create(sf::VideoMode(1280, 800, 32), "Modern Warfare Editor");
	Editor.UseVerticalSync(true);

	/////////////////////////////////////////////////
	/// Game loop
    while (Editor.IsOpened())
    {
		sf::Event Event;
        while (Editor.GetEvent(Event))
        {
			/////////////////////////////////////////////////
			/// Close event, close the game
			if (Event.Type == sf::Event::Closed)
                Editor.Close();

			/////////////////////////////////////////////////
			/// Escape key hit (go to menu)
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				Editor.Close();
		}

		/////////////////////////////////////////////////
        Editor.Clear();

		/////////////////////////////////////////////////
        Editor.Display();
    }

	/////////////////////////////////////////////////
	/// Game terminating successfuly
    return EXIT_SUCCESS;
}