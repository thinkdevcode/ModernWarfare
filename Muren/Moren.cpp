////////////////////////////////////////////////////////
/// Moren.cpp
/// Created: July 15, 2009
////////////////////////////////////////////////////////

#ifndef WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <SFML/Graphics.hpp>

#include "Developer.h"
#include "MapManager.h"
#include "Interface.h"
#include "Log.h"
#include "WinMainData.h"

#pragma warning (disable:4098)

sf::RenderWindow GameWindow;
sf::View GameView;
sf::Uint32 PlayerTeamId;

int MenuScreen();					///< Show the menu screen, at beginning and when Esc button is hit
sf::Vector2f MouseViewCoords();

/// Begin Modern Warfare
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////////////////////////////
	/// Assign windows data
	WinMainData WindowsData;
	WindowsData.hInstance		= hInstance;
	WindowsData.hPrevInstance	= hPrevInstance;
	WindowsData.lpCmdLine		= lpCmdLine;
	WindowsData.nCmdShow		= nCmdShow;

	/////////////////////////////////////////////////
	/// Create render window and provide settings
	sf::WindowSettings WindowSettings;
	WindowSettings.AntialiasingLevel = 4;
	GameWindow.Create(sf::VideoMode::GetMode(0), "Modern Warfare", sf::Style::None, WindowSettings);
	GameWindow.UseVerticalSync(true);

	/////////////////////////////////////////////////
	/// Create View (Currently: 1 + default)
	sf::Vector2f Center(((float)GameWindow.GetWidth() / 2), ((float)GameWindow.GetHeight() / 2));
	sf::Vector2f FullSize((float)GameWindow.GetWidth(), (float)GameWindow.GetHeight());
	GameView.SetCenter(Center);
	GameView.SetHalfSize(FullSize);

	Developer::Initialize();
	Interface::Initialize();
	MapManager::Initialize();
	UManager::Initialize();

	/////////////////////////////////////////////////
	/// Opening Menu and Ingame Menu (hit Esc)
	MenuScreen();

	/////////////////////////////////////////////////
	/// Load Images
	sf::Image Grass;
    if (!Grass.LoadFromFile("grass.png"))
        return EXIT_FAILURE;
	sf::Image BlackUnit;
    if (!BlackUnit.LoadFromFile("blackunit.png"))
        return EXIT_FAILURE;
	sf::Image WhiteUnit;
    if (!WhiteUnit.LoadFromFile("whiteunit.png"))
        return EXIT_FAILURE;

	PlayerTeamId = 1;

	UManager::Create(BlackUnit, 1, sf::Vector2f(100, 100));
	UManager::Create(BlackUnit, 1, sf::Vector2f(200, 200));
	UManager::Create(WhiteUnit, 2, sf::Vector2f(500, 500));
	UManager::Create(WhiteUnit, 2, sf::Vector2f(600, 600));


	/////////////////////////////////////////////////
	/// Create Developer class
	Developer::SetShowFPS(true);
	Developer::SetShowCoords(true);

	MapManager::LoadMap(Grass, 12);
	
	/////////////////////////////////////////////////
	/// Create selection rectangle outside of game loop
	static sf::Shape Selection = sf::Shape::Rectangle(0.f, 0.f, 0.f, 0.f, sf::Color(0, 0, 0, 0), 2.f, sf::Color::White);

	/////////////////////////////////////////////////
	/// Game loop
	while (GameWindow.IsOpened())
    {
		sf::Event Event;
        while (GameWindow.GetEvent(Event))
        {
			/////////////////////////////////////////////////
			/// Close event, close the game
			if (Event.Type == sf::Event::Closed)
				GameWindow.Close();

			/////////////////////////////////////////////////
			/// Escape key hit (go to menu)
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				MenuScreen();

			Interface::Event(Event);
			UManager::Event(Event);

			/////////////////////////////////////////////////
			/// Take a screenshot (F11)
			if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::F11))
			{
				char buffer[14];
				int random = sf::Randomizer::Random(0, 999999999);
				sprintf_s(buffer, "MW%d.jpg", random);
				sf::Image ScreenShot = GameWindow.Capture();
				ScreenShot.SaveToFile(buffer);
			}
		}
		
		/////////////////////////////////////////////////
        GameWindow.Clear();

		/////////////////////////////////////////////////
		/// Switch to Game View (Units/buildings/etc)
		GameWindow.SetView(GameView);

		/////////////////////////////////////////////////
		MapManager::Render();

		/////////////////////////////////////////////////
		/// Do unit actions
		UManager::Render();

		/////////////////////////////////////////////////
		/// Switch to Main view (and draw interface/admin)
		GameWindow.SetView(GameWindow.GetDefaultView());

		/////////////////////////////////////////////////
		Interface::Render();
		
		/////////////////////////////////////////////////
		Developer::Render();

		/////////////////////////////////////////////////
        GameWindow.Display();
    }

	UManager::CollectAllObjects();

	/////////////////////////////////////////////////
	/// Game terminating successfuly
    return EXIT_SUCCESS;
}

int MenuScreen()
{
	/// Ingame Loop
	while (GameWindow.IsOpened())
	{
		sf::Event Event;

		while (GameWindow.GetEvent(Event))
		{
			/// Close event, close the game
			if (Event.Type == sf::Event::Closed)
			{
				GameWindow.Close();
				return EXIT_SUCCESS;
			}

			if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left))
			{
				/// Get the global mouse coords
				int TesterX = GameWindow.GetInput().GetMouseX();
				int TesterY = GameWindow.GetInput().GetMouseY();

				/// Enter Game Button
				if ((TesterX > (((float)GameWindow.GetWidth() / 2.f) - 100.f)) && (TesterX < (((float)GameWindow.GetWidth() / 2.f) + 100.f)) && (TesterY > 300) && (TesterY < 350))
				{
					/// Enter Game Button :: return 1
					return 1;
				}

				/// Exit Game Button
				else if ((TesterX > (((float)GameWindow.GetWidth() / 2.f) - 100.f)) && (TesterX < (((float)GameWindow.GetWidth() / 2.f) + 100.f)) && (TesterY > 375) && (TesterY < 425))
				{
					/// Exit Game Button :: return 0
					GameWindow.Close();
					return EXIT_SUCCESS;
				}
			}
			
			/////////////////////////////////////////////////
			/// Take a screenshot (F11)
			if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::F11))
			{
				char buffer[14];
				int random = sf::Randomizer::Random(0, 999999999);
				sprintf_s(buffer, "MWM%d.jpg", random);
				sf::Image ScreenShot = GameWindow.Capture();
				ScreenShot.SaveToFile(buffer);
			}
			/////////////////////////////////////////////////
		}

		/// Load Images
		static sf::Image Title;
		if (!Title.LoadFromFile("title.png"))
			return EXIT_FAILURE;

		/// Create Sprites
		sf::Sprite TitleSprite(Title);

		/// Create Text
		sf::String EnterText("Enter Game", sf::Font::GetDefaultFont(), 20.f);
		sf::String ExitText("Exit Game", sf::Font::GetDefaultFont(), 20.f);

		/// Set Text
		EnterText.SetColor(sf::Color(255, 255, 255));
		ExitText.SetColor(sf::Color(255, 255, 255));

		/// Set positions of objects
		TitleSprite.SetPosition((((float)GameWindow.GetWidth() / 2.f) - 300.f), 20.f);
		EnterText.SetPosition((((float)GameWindow.GetWidth() / 2.f) - 53.f), 311.f);
		ExitText.SetPosition((((float)GameWindow.GetWidth() / 2.f) - 46.f), 386.f);

		/// Temporary boxes
		static sf::Shape Enter = sf::Shape::Rectangle((((float)GameWindow.GetWidth() / 2.f) - 100.f), 300.f, (((float)GameWindow.GetWidth() / 2.f) + 100.f), 350.f, sf::Color(0, 0, 0, 0), 1.f, sf::Color::White);
		static sf::Shape Exit = sf::Shape::Rectangle((((float)GameWindow.GetWidth() / 2.f) - 100.f), 375.f, (((float)GameWindow.GetWidth() / 2.f) + 100.f), 425.f, sf::Color(0, 0, 0, 0), 1.f, sf::Color::White);

		/// Clear our screen
		GameWindow.Clear();

		/// Draw our objects to screen
		GameWindow.Draw(Enter);
		GameWindow.Draw(Exit);
		GameWindow.Draw(TitleSprite);
		GameWindow.Draw(EnterText);
		GameWindow.Draw(ExitText);

		/// Display our screen
		GameWindow.Display();
	}

	/// Game terminating
	return EXIT_SUCCESS;
}

sf::Vector2f MouseViewCoords()
{
	return GameWindow.ConvertCoords(GameWindow.GetInput().GetMouseX(), GameWindow.GetInput().GetMouseY(), &GameView);
}