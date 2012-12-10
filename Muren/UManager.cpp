#include "UManager.h"

extern sf::RenderWindow GameWindow;
extern sf::View GameView;
extern sf::Uint32 PlayerTeamId;
extern sf::Vector2f MouseViewCoords();

namespace UManager
{
	/////////////////////////////////////////////////
	/// Initializes variables to be used in UManager
	/////////////////////////////////////////////////
	void Initialize()
	{
		CullTimer.Reset();
	}

	void Event(sf::Event& Event)
	{
		/////////////////////////////////////////////////
		/// RIGHT mouse click pressed
		if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Right))
		{
			std::map<sf::Uint32, Unit *>::iterator UnitIt;
			for (UnitIt = LiveUnits.begin(); UnitIt != LiveUnits.end(); ++UnitIt)
				UnitIt->second->MoveToPosition(MouseViewCoords());
		}
	}

	/////////////////////////////////////////////////
	/// Create a unit.
	/////////////////////////////////////////////////
	void Create(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position)
	{
		Unit* NewUnit = new Unit(GameWindow, Image, Team, PlayerTeamId, &UnitDied);
		NewUnit->SetPosition(Position);
		LiveUnits[NewUnit->GetId()] = NewUnit;
	}

	/////////////////////////////////////////////////
	/// Create a unit.
	/////////////////////////////////////////////////
	void Create(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position, UnitStats Stats)
	{
		Unit* NewUnit = new Unit(GameWindow, Image, Team, PlayerTeamId, Stats, &UnitDied);
		NewUnit->SetPosition(Position);
		LiveUnits[NewUnit->GetId()] = NewUnit;
	}

	/////////////////////////////////////////////////
	/// Iterate through all LIVE units to determine
	/// which should be visible to the player.
	/// Returns if any units were culled.
	/////////////////////////////////////////////////
	bool CullUnits()
	{
		CulledUnits.clear();
		sf::Uint32 Count = 0;
		sf::Vector2f Origin = GameWindow.ConvertCoords(0, 0, &GameView);
		sf::Vector2f Max = GameWindow.ConvertCoords(GameWindow.GetHeight(), GameWindow.GetWidth(), &GameView);
		//check if unit is within view
		std::map<sf::Uint32, Unit *>::iterator UnitIt;
		for (UnitIt = LiveUnits.begin(); UnitIt != LiveUnits.end(); ++UnitIt)
		{
			if ( UnitIt->second->GetPosition().x < Origin.x || UnitIt->second->GetPosition().x > Max.x ||
				 UnitIt->second->GetPosition().y < Origin.y || UnitIt->second->GetPosition().y > Max.y )
			{
				//unit is not within view
			}

			else
			{
				CulledUnits.push_back(UnitIt->second);
				++Count;
			}
		}
		return (Count > 0);
	}

	sf::Uint32 PollSelectedUnits()
	{
		SelectedUnits.clear();
		std::map<sf::Uint32, Unit *>::iterator UnitIt;
		for (UnitIt = LiveUnits.begin(); UnitIt != LiveUnits.end(); ++UnitIt)
			if (UnitIt->second->Selected())
				SelectedUnits[UnitIt->second->GetId()] = UnitIt->second;
		return (sf::Uint32) SelectedUnits.size();
	}

	std::map<sf::Uint32, Unit *>& GetSelectedUnits()
	{
		return SelectedUnits;
	}

	std::map<sf::Uint32, Unit *>& GetLiveUnits()
	{
		return LiveUnits;
	}

	/////////////////////////////////////////////////
	/// Render only visible units. (Culled)
	/////////////////////////////////////////////////
	void Render()
	{
		Update();
		CollectGarbage();
		CullUnits();
		CullTimer.Reset();
		std::list<Unit *>::iterator UnitIt;
		for (UnitIt = CulledUnits.begin(); UnitIt != CulledUnits.end(); ++UnitIt)
			(*UnitIt)->Render();
	}

	/////////////////////////////////////////////////
	/// Updates all LIVE units.
	/////////////////////////////////////////////////
	void Update()
	{
		std::map<sf::Uint32, Unit *>::iterator UnitIt;
		for (UnitIt = LiveUnits.begin(); UnitIt != LiveUnits.end(); ++UnitIt)
			UnitIt->second->Update(LiveUnits);
	}

	/////////////////////////////////////////////////
	/// Deletes all dead objects.
	/// Do not use every loop.
	/////////////////////////////////////////////////
	void CollectGarbage()
	{
		std::map<sf::Uint32, Unit *>::iterator UnitIt;
		for (UnitIt = DeadUnits.begin(); UnitIt != DeadUnits.end(); ++UnitIt)
		{
			Log::WriteObjectLog(Log::FILE, UnitIt->second->GetId(), "Deleted by CollectGarbage()");
			delete UnitIt->second;
		}
		DeadUnits.clear();
	}

	/////////////////////////////////////////////////
	/// Deletes ALL objects created.
	/// Must be called at game shutdown.
	/////////////////////////////////////////////////
	void CollectAllObjects()
	{
		CollectGarbage();
		std::map<sf::Uint32, Unit *>::iterator UnitIt;
		for (UnitIt = LiveUnits.begin(); UnitIt != LiveUnits.end(); ++UnitIt)
		{
			Log::WriteObjectLog(Log::FILE, UnitIt->second->GetId(), "Deleted by CollectAllGarbage()");
			delete UnitIt->second;
		}
		LiveUnits.clear();
	}

	/////////////////////////////////////////////////
	/// Callback function for unit death.
	/// Moves unit from Live container to Dead cont-
	/// -ainer.
	/////////////////////////////////////////////////
	void UnitDied(Unit* Unit)
	{
		DeadUnits[Unit->GetId()] = Unit;
		LiveUnits.erase(Unit->GetId());
	}

}