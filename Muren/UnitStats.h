////////////////////////////////////////////////////////
/// UnitStats.h
/// Created: July 27, 2009
////////////////////////////////////////////////////////

#ifndef _UnitStats_
#define _UnitStats_

/////////////////////////////////////////////////
/// UnitStats struct has all of the stats used by
/// the game for units.
/////////////////////////////////////////////////
struct UnitStats
{
	int HealthPoints;		///< Current Health Points
	int MaxHealthPoints;	///< Maximum Health Points
	int AmmunitionCount;	///< How much ammunition is left
	int FiringAccuracy;		///< How accurate shot is
	int AttackPower;		///< How powerful shot it
	int AttackSpeed;		///< How fast shot is
	float AttackRange;		///< How long shot is
	float RunSpeed;			///< Units run speed
	UnitStats()
		: HealthPoints(100), MaxHealthPoints(100), AmmunitionCount(500), FiringAccuracy(50),
		AttackPower(5), AttackSpeed(333), AttackRange(250), RunSpeed(150.f)
	{
		// Default stats
	};
};

#endif