/////////////////////////////////////////////////
/// UnitManager.cpp
/// Created: September 7, 2009
/////////////////////////////////////////////////

#include "UnitManager.h"

UnitManager::UnitManager(sf::RenderWindow &Window, sf::View& GameView)
	: m_RenderWindow(Window), m_GameView(GameView)
{ }

void UnitManager::setPlayerTeamId(sf::Uint32 Team)
{
	m_PlayerId = Team;
}

void UnitManager::CreateUnit(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position)
{
	Unit* NewUnit = new Unit(m_RenderWindow, Image, Team);
	NewUnit->setUnitPosition(Position);
}

void UnitManager::CreateUnit(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position, UnitStats Stats)
{
	Unit* NewUnit = new Unit(m_RenderWindow, Image, Team, Stats);
	NewUnit->setUnitPosition(Position);
}

void UnitManager::Draw()
{
	Update();

	int Count;

	if (m_Timer.GetElapsedTime() > 0.1f)
	{
		Count = CullUnits();
		Object::CollectGarbage();
		m_Timer.Reset();
	}

	if (Count > 0)
	{
		std::list<Object *>::iterator UnitIt;
		for (UnitIt = Unit::m_CulledObjects.begin(); UnitIt != Unit::m_CulledObjects.end(); ++UnitIt)
			(Unit *)(*UnitIt)->Draw();
	}
}

void UnitManager::Update()
{
	//std::list<Unit *>::iterator UnitIt;
	std::map<sf::Uint32, Object *>::iterator ObjectIter;
	for (ObjectIter = Object::m_LiveObjects.begin(); ObjectIter != Object::m_LiveObjects.end(); ++ObjectIter)
		ObjectIter->second->Update();
}

/*
void UnitManager::MoveToPosition(sf::Vector2f Position)
{
	std::map<sf::Uint32, Unit *>::iterator ObjectIter;
	for (ObjectIter = Object::m_LiveObjects.begin(); ObjectIter != Object::m_LiveObjects.end(); ++ObjectIter)
		ObjectIter->second->MoveToPosition(Position);
}

void UnitManager::SelectionBox(sf::Vector2f Beginning, sf::Vector2f End)
{
	std::map<sf::Uint32, Unit *>::iterator ObjectIter;
	for (ObjectIter = Object::m_LiveObjects.begin(); ObjectIter != Object::m_LiveObjects.end(); ++ObjectIter)
		ObjectIter->second->SelectionBox(Beginning, End, m_PlayerId);
}
*/

sf::Uint32 UnitManager::CullUnits()
{
	#ifdef _DEBUGLOG_
		Log::Write(Log::FILE, "Entering UnitManager::CullUnits()");
	#endif

	Object::m_CulledObjects.clear();

	sf::Uint32 Count = 0;

	sf::Vector2f Origin = m_RenderWindow.ConvertCoords(0, 0, &m_GameView);
	sf::Vector2f Max = m_RenderWindow.ConvertCoords(m_RenderWindow.GetHeight(), m_RenderWindow.GetWidth(), &m_GameView);

	//check if unit is within view
	std::map<sf::Uint32, Unit *>::iterator ObjectIter;
	for (ObjectIter = Object::m_LiveObjects.begin(); ObjectIter != Object::m_LiveObjects.end(); ++ObjectIter)
	{
		if ( ObjectIter->second->getCurrentPosition().x < Origin.x || ObjectIter->second->getCurrentPosition().x > Max.x ||
			 ObjectIter->second->getCurrentPosition().y < Origin.y || ObjectIter->second->getCurrentPosition().y > Max.y )
		{
			//unit is not within view
		}
		else
		{
			#ifdef _DEBUGLOG_
				Log::Write(Log::FILE, "Added Unit to m_UnitRenderList");
			#endif
				Object::m_CulledObjects.push_back(ObjectIter->second);
			++Count;
		}
	}

	#ifdef _DEBUGLOG_
		Log::Write(Log::FILE, "Leaving UnitManager::CullUnits()");
	#endif

	return Count;
}