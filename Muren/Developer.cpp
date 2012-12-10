/////////////////////////////////////////////////
/// Developer.cpp
/// Created: September 13, 2009
/////////////////////////////////////////////////

#include "Developer.h"

extern sf::RenderWindow GameWindow;
extern sf::View GameView;
extern sf::Uint32 PlayerTeamId;

namespace Developer
{
	void Initialize()
	{
		FPS.SetFont(sf::Font::GetDefaultFont());
		FPS.SetSize(15.f);
		FPS.SetColor(sf::Color::White);
		FPS.SetPosition(((float)GameWindow.GetWidth() - 210.f), 60.f);

		Coords.SetFont(sf::Font::GetDefaultFont());
		Coords.SetSize(15.f);
		Coords.SetColor(sf::Color::White);
		Coords.SetPosition(((float)GameWindow.GetWidth() - 210.f), 30.f);

		ShowFPS = false;
		ShowCoords = false;
	}

	void Render()
	{
		if (ShowFPS)
		{
			UpdateFPS();
			GameWindow.Draw(FPS);
		}
		if (ShowCoords)
		{
			UpdateCoords();
			GameWindow.Draw(Coords);
		}
	}

	void UpdateFPS()
	{
		if (FPSTimer.GetElapsedTime() > 0.5f)
		{
			FrameRate = 1.f / GameWindow.GetFrameTime();
			FPSTimer.Reset();
		}
		sprintf_s(FPSBuffer, "FPS: %i", (int)FrameRate);
		FPS.SetText(FPSBuffer);
	}

	void UpdateCoords()
	{
		MouseGUICoords = GameWindow.ConvertCoords(GameWindow.GetInput().GetMouseX(), GameWindow.GetInput().GetMouseY(), &GameView);
		MouseWCoords.x = GameWindow.GetInput().GetMouseX();
		MouseWCoords.y = GameWindow.GetInput().GetMouseY();
		sprintf_s(CoordBuffer, "Game Coords: (%i,%i)\nWindow Coords: (%i,%i)", (int)MouseGUICoords.x, (int)MouseGUICoords.y, MouseWCoords.x, MouseWCoords.y);
		Coords.SetText(CoordBuffer);
	}
	bool GetShowFPS() { return ShowFPS; }
	void SetShowFPS(bool Show) { ShowFPS = Show; }
	bool GetShowCoords() { return ShowCoords; }
	void SetShowCoords(bool Show) { ShowCoords = Show; }
}