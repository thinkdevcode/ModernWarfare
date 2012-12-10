////////////////////////////////////////////////////////
/// MainMenu.cpp
/// Created: September 26, 2009
////////////////////////////////////////////////////////

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &Game)
: m_RenderWindow(Game)
{
	/// Load Images
	m_TitleImage.LoadFromFile("title.png");

	/// Create Sprites
	m_TitleSprite.SetImage(m_TitleImage);

	/// Set Text
	m_EnterText.SetText("Enter Game");
	m_EnterText.SetFont(sf::Font::GetDefaultFont());
	m_EnterText.SetSize(20.f);
	m_EnterText.SetColor(sf::Color(255, 255, 255));
	m_ExitText.SetText("Exit Game");
	m_ExitText.SetFont(sf::Font::GetDefaultFont());
	m_ExitText.SetSize(20.f);
	m_ExitText.SetColor(sf::Color(255, 255, 255));

	/// Set positions of objects
	m_TitleSprite.SetPosition((((float)m_RenderWindow.GetWidth() / 2.f) - 300.f), 20.f);
	m_EnterText.SetPosition((((float)m_RenderWindow.GetWidth() / 2.f) - 53.f), 311.f);
	m_ExitText.SetPosition((((float)m_RenderWindow.GetWidth() / 2.f) - 46.f), 386.f);

	/// Temporary boxes
	m_EnterBox = sf::Shape::Rectangle((((float)m_RenderWindow.GetWidth() / 2.f) - 100.f), 300.f, (((float)m_RenderWindow.GetWidth() / 2.f) + 100.f), 350.f, sf::Color(0, 0, 0, 0), 1.f, sf::Color::White);
	m_ExitBox = sf::Shape::Rectangle((((float)m_RenderWindow.GetWidth() / 2.f) - 100.f), 375.f, (((float)m_RenderWindow.GetWidth() / 2.f) + 100.f), 425.f, sf::Color(0, 0, 0, 0), 1.f, sf::Color::White);

}

MainMenu::~MainMenu()
{ }

sf::Int32 MainMenu::Draw()
{
	while (m_RenderWindow.IsOpened())
	{
		Update();
		if ( Event() == MainMenu::NO_EVENT)
		{
			m_RenderWindow.Clear();

			m_RenderWindow.Draw(m_TitleSprite);
			m_RenderWindow.Draw(m_EnterText);
			m_RenderWindow.Draw(m_ExitText);
			m_RenderWindow.Draw(m_EnterBox);
			m_RenderWindow.Draw(m_ExitBox);

			m_RenderWindow.Display();

			return MainMenu::NO_EVENT;
		}
	}
	return 1;
}

sf::Int32 MainMenu::Event()
{ 
	sf::Event Event;

	while (m_RenderWindow.GetEvent(Event))
	{
		/// Close event, close the game
		if (Event.Type == sf::Event::Closed)
		{
			m_RenderWindow.Close();
			return MainMenu::EXIT_GAME;
		}

		if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left))
		{
			/// Get the global mouse coords
			int TesterX = m_RenderWindow.GetInput().GetMouseX();
			int TesterY = m_RenderWindow.GetInput().GetMouseY();

			/// Enter Game Button
			if ((TesterX > (((float)m_RenderWindow.GetWidth() / 2.f) - 100.f)) && (TesterX < (((float)m_RenderWindow.GetWidth() / 2.f) + 100.f)) && (TesterY > 300) && (TesterY < 350))
			{
				/// Enter Game Button :: return 1
				return MainMenu::SINGLE_PLAYER;
			}

			/// Exit Game Button
			else if ((TesterX > (((float)m_RenderWindow.GetWidth() / 2.f) - 100.f)) && (TesterX < (((float)m_RenderWindow.GetWidth() / 2.f) + 100.f)) && (TesterY > 375) && (TesterY < 425))
			{
				/// Exit Game Button :: return 0
				m_RenderWindow.Close();
				return MainMenu::EXIT_GAME;
			}
		}
		
		/////////////////////////////////////////////////
		/// Take a screenshot (F11)
		if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::F11))
		{
			char buffer[14];
			int random = sf::Randomizer::Random(0, 999999999);
			sprintf_s(buffer, "MWM%d.jpg", random);
			sf::Image ScreenShot = m_RenderWindow.Capture();
			ScreenShot.SaveToFile(buffer);
		}
		/////////////////////////////////////////////////
	}

	return MainMenu::NO_EVENT;
}

void MainMenu::Update()
{ }