////////////////////////////////////////////////////////
/// GameState.h
/// Created: September 26, 2009
////////////////////////////////////////////////////////

#ifndef _GameState_
#define _GameState_

#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual sf::Int32	Draw()		=0;
	virtual sf::Int32	Event()		=0;
	virtual void		Update()	=0;
};

#endif