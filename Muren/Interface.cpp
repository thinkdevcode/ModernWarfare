/////////////////////////////////////////////////
/// Interface.cpp
/// Created: September 5, 2009
/////////////////////////////////////////////////

#include "Interface.h"

extern sf::RenderWindow GameWindow;
extern sf::View GameView;
extern sf::Uint32 PlayerTeamId;
extern sf::Vector2f MouseViewCoords();

namespace Interface
{
	namespace 
	{
		sf::Shape		BottomBar;				///< Game bar at bottom of screen
		sf::Clock		SystemMessageTimer;		///< A timer for system messages (default time = 3 seconds)
		sf::String		SystemMessage;			///< The system message string
		bool			SystemMessageFlag;		///< Is there a system message being displayed?
		char			SingleBuffer[256];		///< For testing purposes
		sf::String		SingleString;			///< For testing purposes
		sf::Int32		ZoomLevel;				///< What level zoom is
		sf::Shape		SelectionRect;
		bool			LeftMouseButton;		///< true = pressed, false = released;
		float			SelectionOriginX;					///< Global X coord (for selection rectangle)
		float			SelectionOriginY;					///< Global Y coord (for selection rectangle)
	}

	void Initialize()
	{
		BottomBar = sf::Shape::Rectangle(0, (float)(GameWindow.GetHeight() - 100), (float)GameWindow.GetWidth(), (float)GameWindow.GetHeight(), sf::Color(15, 15, 15));
		SelectionRect = sf::Shape::Rectangle(0.f, 0.f, 0.f, 0.f, sf::Color(0, 0, 0, 0), 2.f, sf::Color::White);
		ShowInterface = true;
		ZoomLevel = 0;
		LeftMouseButton = false;
		SelectionOriginX = 0;
		SelectionOriginY = 0;
	}

	void Event(sf::Event& Event)
	{
		/////////////////////////////////////////////////
		/// LEFT mouse click pressed
		if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Left))
		{
			sf::Vector2f ViewCoords = MouseViewCoords();
			SelectionRect.SetPointPosition(0, ViewCoords.x, ViewCoords.y);
			SelectionRect.SetPointPosition(1, ViewCoords.x, ViewCoords.y);
			SelectionRect.SetPointPosition(2, ViewCoords.x, ViewCoords.y);
			SelectionRect.SetPointPosition(3, ViewCoords.x, ViewCoords.y);
			SelectionOriginX = ViewCoords.x;
			SelectionOriginY = ViewCoords.y;
			LeftMouseButton = true;
		}

		/////////////////////////////////////////////////
		/// LEFT mouse click release
		if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left))
		{
			LeftMouseButton = false;
			sf::Vector2f MouseEndCoords = MouseViewCoords();

			std::map<sf::Uint32, Unit *>::iterator UnitIt;
			for (UnitIt = UManager::GetLiveUnits().begin(); UnitIt != UManager::GetLiveUnits().end(); ++UnitIt)
				UnitIt->second->SelectionBox(sf::Vector2f(SelectionOriginX, SelectionOriginY), MouseEndCoords);
		}

		if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F12))
			SwitchShowInterface();

		/////////////////////////////////////////////////
		/// Zoom Out (Page Up)
		if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::PageUp))
		{
			if (ZoomLevel < -4)
				DisplaySystemMessage("Cannot Zoom Out Anymore!");
			else
			{
				GameView.Zoom(0.9f);
				--ZoomLevel;
			}
		}

		/////////////////////////////////////////////////
		/// Zoom In (Page Down)
		if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::PageDown))
		{
			if (ZoomLevel > 4)
				DisplaySystemMessage("Cannot Zoom In Anymore!");
			else
			{
				GameView.Zoom(1.1f);
				++ZoomLevel;
			}
		}
	}

	void Render()
	{
		/////////////////////////////////////////////////
		/// Unit Selection Rectangle
		if (LeftMouseButton)
		{
			GameWindow.SetView(GameView);
			sf::Vector2f ViewCoords = MouseViewCoords();
			SelectionRect.SetPointPosition(1, ViewCoords.x, SelectionOriginY);
			SelectionRect.SetPointPosition(2, ViewCoords.x, ViewCoords.y);
			SelectionRect.SetPointPosition(3, SelectionOriginX, ViewCoords.y);
			GameWindow.Draw(SelectionRect);
			GameWindow.SetView(GameWindow.GetDefaultView());
		}

		if (ShowInterface)
		{
			GameWindow.Draw(BottomBar);

			//If has units
			sf::Uint32 SelectedCount = UManager::PollSelectedUnits();
			if ( SelectedCount == 1)
			{
				sprintf_s(SingleBuffer, "Health Points: %i/%i\nAmmo Count: %i\nAccuracy: %i\nPower: %i dps\nAttack Speed: %i\nRun Speed: %i", 
						UManager::GetSelectedUnits().begin()->second->GetStats().HealthPoints, 
						UManager::GetSelectedUnits().begin()->second->GetStats().MaxHealthPoints, 
						UManager::GetSelectedUnits().begin()->second->GetStats().AmmunitionCount,
						UManager::GetSelectedUnits().begin()->second->GetStats().FiringAccuracy, 
						UManager::GetSelectedUnits().begin()->second->GetStats().AttackPower, 
						UManager::GetSelectedUnits().begin()->second->GetStats().AttackSpeed,
				   (int)UManager::GetSelectedUnits().begin()->second->GetStats().RunSpeed);
				SingleString.SetText(SingleBuffer);
				SingleString.SetFont(sf::Font::GetDefaultFont());
				SingleString.SetSize(15.f);
				SingleString.SetColor(sf::Color(255, 255, 255));
				SingleString.SetPosition(5.f, (float)(GameWindow.GetHeight() - 98));
				GameWindow.Draw(SingleString);
			}
			if ( SelectedCount >= 2)
			{
				//todo
			}
		}
		if (SystemMessageFlag)
		{
			if (SystemMessageTimer.GetElapsedTime() < 1.5f)
				GameWindow.Draw(SystemMessage);
			else
				SystemMessageFlag = false;
		}
	}

	void DisplaySystemMessage(std::string Message)
	{
		SystemMessage.SetColor(sf::Color::White);
		SystemMessage.SetFont(sf::Font::GetDefaultFont());
		SystemMessage.SetSize(30.f);
		SystemMessage.SetText(Message);
		SystemMessage.SetPosition(((float)GameWindow.GetWidth() / 2), ((float)GameWindow.GetHeight() / 2));
		SystemMessageFlag = true;
		SystemMessageTimer.Reset();
	}

	void SetShowInterface(bool Show) { ShowInterface = Show; }
	void SwitchShowInterface() { ShowInterface = !ShowInterface; }
}