////////////////////////////////////////////////////////
/// MainMenu.h
/// Created: September 26, 2009
////////////////////////////////////////////////////////

#ifndef _MainMenu_
#define _MainMenu_

#include <SFML/Graphics.hpp>
//#include <SFML/cpGUI/cpGUI.h>
#include "GameState.h"

class MainMenu : public GameState
{
public:
	enum MenuStatus
	{
		NO_EVENT = 0,
		EXIT_GAME,
		SINGLE_PLAYER,
		MULTI_PLAYER,
		OPTIONS
	};

	MainMenu(sf::RenderWindow& Game);
	virtual ~MainMenu();

	sf::Int32 Draw();
	sf::Int32 Event();
	void Update();

	/////////////////////////////////////////////////
	/// Overloaded '=' operator, needed for error
	MainMenu& operator=(const MainMenu& U);
	/////////////////////////////////////////////////

protected:

	sf::RenderWindow&	m_RenderWindow;
	sf::Image			m_TitleImage;
	sf::Sprite			m_TitleSprite;
	sf::String			m_EnterText;
	sf::String			m_ExitText;
	sf::Shape			m_EnterBox;
	sf::Shape			m_ExitBox;
};

#endif