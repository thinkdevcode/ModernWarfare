/////////////////////////////////////////////////
/// MapManager.cpp
/// Created: September 14, 2009
/////////////////////////////////////////////////

#include "MapManager.h"

extern sf::RenderWindow GameWindow;
extern sf::View GameView;
extern sf::Uint32 PlayerTeamId;

namespace MapManager
{
	void Initialize()
	{
		MapLoaded = false;
		ScrollingSpeed = 850.f;
		ScrollingBuffer = 175.f;
	}

	void LoadMap(sf::Image &Tile, sf::Uint32 Size)
	{
		float x = 0.f;
		float y = 0.f;
		sf::Uint32 column = 0;
		sf::Uint32 row = 0;

		for (sf::Uint32 b = 0; b < (Size * Size); ++b)
		{
			Layer0.push_back(sf::Sprite(Tile));
			Layer0[b].SetPosition( ( x + (column * Tile.GetWidth() ) ), ( y + (row * Tile.GetHeight() ) ) );
			if (column < Size)
				++column;
			if (column == Size)
			{
				column = 0;
				++row;
			}
		}

		MapSize = Size;
		MapLoaded = true;
	}

	void Render()
	{
		Scroll();

		for (sf::Uint32 b = 0; b < (MapSize * MapSize); ++b)
			GameWindow.Draw(Layer0[b]);
	}

	void Scroll()
	{
		/// Get the global mouse coords
		ScrollX = GameWindow.GetInput().GetMouseX();
		ScrollY = GameWindow.GetInput().GetMouseY();
		ScrollTime = GameWindow.GetFrameTime();
		WindowHeight = (int)GameWindow.GetHeight();
		WindowWidth = (int)GameWindow.GetWidth();

		/// Direction 1 (Quadrant 1 - North West)
		if ((ScrollX < ScrollingBuffer) && (ScrollY < ScrollingBuffer))
			GameView.Move(-ScrollingSpeed * ScrollTime, -ScrollingSpeed * ScrollTime);

		/// Direction 2 (Quadrant 2 - North)
		if ((ScrollX > ScrollingBuffer) && (ScrollX < (WindowWidth - ScrollingBuffer)) && (ScrollY < ScrollingBuffer))
			GameView.Move(0.f, -ScrollingSpeed * ScrollTime);

		/// Direction 3 (Quadrant 3 - North East)
		if ((ScrollX > (WindowWidth - ScrollingBuffer)) && (ScrollY < ScrollingBuffer))
			GameView.Move(ScrollingSpeed * ScrollTime, -ScrollingSpeed * ScrollTime);

		/// Direction 4 (Quadrant 4 - East)
		if ((ScrollX > (WindowWidth - ScrollingBuffer)) && (ScrollY < (WindowHeight - ScrollingBuffer)) && (ScrollY > ScrollingBuffer))
			GameView.Move(ScrollingSpeed * ScrollTime, 0.f);

		/// Direction 5 (Quadrant 5 - South East)
		if ((ScrollX > (WindowWidth - ScrollingBuffer)) && (ScrollY > (WindowHeight - ScrollingBuffer)))
			GameView.Move(ScrollingSpeed * ScrollTime, ScrollingSpeed * ScrollTime);

		/// Direction 6 (Quadrant 6 - South)
		if ((ScrollX > ScrollingBuffer) && (ScrollX < (WindowWidth - ScrollingBuffer)) && (ScrollY > (WindowHeight - ScrollingBuffer)))
			GameView.Move(0.f, ScrollingSpeed * ScrollTime);

		/// Direction 7 (Quadrant 7 - South West)
		if ((ScrollX < ScrollingBuffer) && (ScrollY > (WindowHeight - ScrollingBuffer)))
			GameView.Move(-ScrollingSpeed * ScrollTime, ScrollingSpeed * ScrollTime);

		/// Direction 8 (Quadrant 8 - West)
		if ((ScrollX < ScrollingBuffer) && (ScrollY > ScrollingBuffer) && (ScrollY < (WindowHeight - ScrollingBuffer)))
			GameView.Move(-ScrollingSpeed * ScrollTime, 0.f);
	}
	void SetScrollSpeed(float Speed) { ScrollingSpeed = Speed; }
	void SetScrollBuffer(float Buffer) { ScrollingBuffer = Buffer; }
	bool GetMapLoaded() { return MapLoaded; }
}