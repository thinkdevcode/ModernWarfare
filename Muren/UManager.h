#ifndef _UManager_
#define _UManager_

#include <map>
#include <list>
#include "Unit.h"

namespace UManager
{
	void Initialize();

	void Event(sf::Event& Event);

	void Create(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position);
	void Create(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position, UnitStats Stats);

	bool CullUnits();

	sf::Uint32 PollSelectedUnits();

	std::map<sf::Uint32, Unit *>& GetSelectedUnits();
	std::map<sf::Uint32, Unit *>& GetLiveUnits();

	void Render();
	void Update();

	void CollectGarbage();
	void CollectAllObjects();

	void UnitDied(Unit* Unit);

	namespace
	{
		std::map<sf::Uint32, Unit *>	LiveUnits;
		std::map<sf::Uint32, Unit *>	DeadUnits;
		std::list<Unit *>				CulledUnits;
		std::map<sf::Uint32, Unit *>	SelectedUnits;
		sf::Clock						CullTimer;
	}
}

#endif