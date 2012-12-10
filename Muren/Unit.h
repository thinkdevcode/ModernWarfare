////////////////////////////////////////////////////////
/// UnitStats.h
/// Created: July 27, 2009
////////////////////////////////////////////////////////

#define _DEBUGLOG_ 2

#ifndef _Unit_
#define _Unit_

#include "Object.h"
#include "UnitStats.h"
#include "Vector2.h"
#include "Log.h"

#pragma warning (disable:4098)
#pragma warning (disable:4512)   ///< reference in class throws warning

/////////////////////////////////////////////////
/// Unit Class:
///		This is the base unit class. It contains
///		all basic functions and methods used on
///		units ingame.
/////////////////////////////////////////////////
class Unit : public Object
{
public:
	/////////////////////////////////////////////////
	/// Unit: Default constructor
	Unit(sf::RenderWindow& Game, sf::Image &Image, sf::Uint32 TeamId, sf::Uint32 PlayerId, void (*DeathFunc)(Unit*));

	/////////////////////////////////////////////////
	/// Unit: Secondary constructor
	Unit(sf::RenderWindow& Game, sf::Image &Image, sf::Uint32 TeamId, sf::Uint32 PlayerId, UnitStats Stats, void (*DeathFunc)(Unit*));

	virtual ~Unit();

	void Event(sf::Event& Event);

	/////////////////////////////////////////////////
	/// Controls the units action states
	void Render();

	/////////////////////////////////////////////////
	/// Updates unit (finds targets, etc.)
	void Update(std::map<sf::Uint32, Unit *>& Units);

	/////////////////////////////////////////////////
	/// Returns current unit position
	const sf::Vector2f& GetPosition() const;

	/////////////////////////////////////////////////
	/// Returns current units stats (HP/Ammo/etc)
	const UnitStats& GetStats() const;

	/////////////////////////////////////////////////
	/// Returns unit Sprite
	const sf::Sprite& GetSprite() const;

	/////////////////////////////////////////////////
	/// Returns if unit is selected or not
	const bool Selected() const;

	const bool Alive() const;

	/////////////////////////////////////////////////
	/// Returns current team
	const sf::Uint32 GetTeam() const;

	/////////////////////////////////////////////////
	/// Set units Stats (if not used Constructor)
	/// If using ammo or lowering HP do not use this
	/// function
	void SetStats(UnitStats Stats);

	/////////////////////////////////////////////////
	/// Set units new position (Also saves last position)
	void SetPosition(sf::Vector2f NewPosition);

	/////////////////////////////////////////////////
	/// Set if unit is selected
	void SetSelected(bool Selected);

	/////////////////////////////////////////////////
	/// Moves unit to location
	void MoveToPosition(sf::Vector2f Position);

	void TakeDamage(int Damage);

	/////////////////////////////////////////////////
	/// See if unit got selected
	void SelectionBox(sf::Vector2f Beginning, sf::Vector2f End);

	/////////////////////////////////////////////////
	/// Overloaded '=' operator, needed for error
	Unit& operator=(const Unit& U);

protected:

	/////////////////////////////////////////////////
	/// Tests if unit collided with another unit
	bool CircleTestA(const sf::Sprite& Target);
	bool CircleTestB(const sf::Sprite& Target, float Radius);

	void ShootPrimaryWeapon();

	sf::RenderWindow&	m_RenderWindow;
	sf::Image&			m_Image;				///< Reference to sf::Image
	UnitStats			m_Stats;				///< Units stats (updated)
	sf::Clock			m_TargetTimer;			///< Internal Timer used for targetting
	sf::Clock			m_ShootTimer;			///< Internal Timer used for shooting

	sf::Sprite			m_Sprite;				///< Units sprite
	sf::Uint32			m_TeamId;				///< Units team color
	sf::Uint32			m_PlayerId;				///< Players Id
	float				m_Height;				///< Height of Unit
	float				m_Width;				///< Width of Unit

	bool				m_Moving;				///< Is Unit currently moving?
	gtp::math::Vector2	m_NormalVector;			///< Normalized vector of Target and Current position
	sf::Vector2f		m_LastPosition;			///< Last Position
	sf::Vector2f		m_GoToPosition;			///< Position moving towards

	bool				m_Selected;			///< Is Unit selected?

	sf::Shape			m_HealthBarOutline;		///< The outline of the HP Bar above the unit (Black)
	sf::Shape			m_HealthBar;			///< The actual HP Bar above the unit (Green)

	Unit*				m_TargetUnit;			///< A pointer to the target unit

	void (*Death)(Unit*);
};

#endif