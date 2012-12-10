/////////////////////////////////////////////////
/// UnitManager.h
/// Created: September 7, 2009
/////////////////////////////////////////////////

#ifndef _UnitManager_
#define _UnitManager_

//#define _DEBUGLOG_ 1

#include <list>
#include <map>
#include "Unit.h"

/////////////////////////////////////////////////
/// UnitManager Class:
///		Handles and controls all the units in
///		the game.
/////////////////////////////////////////////////
class UnitManager
{
public:
	/////////////////////////////////////////////////
	/// UnitManager: Default constructor
	UnitManager(sf::RenderWindow& Window, sf::View& GameView);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// setPlayerTeamId: Sets the current players team
	///		color.
	void setPlayerTeamId(sf::Uint32 Team);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// CreateUnit: Creates a unit with parameters
	void CreateUnit(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position);
	void CreateUnit(sf::Image &Image, sf::Uint32 Team, sf::Vector2f Position, UnitStats Stats);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// Draw: Draw all units
	void Draw();
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// Update: Update all units (various tasks)
	void Update();
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// MoveToPosition: Send "MoveToPosition" units
	void MoveToPosition(sf::Vector2f Position);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/// SelectionBox: Send "SelectionBox" units
	void SelectionBox(sf::Vector2f Beginning, sf::Vector2f End);
	/////////////////////////////////////////////////

protected:

	sf::RenderWindow&	m_RenderWindow;		///< Reference to Game Window
	sf::View&			m_GameView;			///< Reference to the game view
	//std::list<Unit *>	m_UnitList;			///< List of all units
	//std::list<Unit *>	m_UnitRenderList;	///< List of units on screen
	sf::Uint32			m_PlayerId;			///< Current Player Color
	sf::Clock			m_Timer;

private:

	sf::Uint32 CullUnits();
};

#endif