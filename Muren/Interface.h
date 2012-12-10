/////////////////////////////////////////////////
/// Interface.h
/// Created: September 5, 2009
/////////////////////////////////////////////////

#ifndef _Interface_
#define _Interface_

#include "UManager.h"

/////////////////////////////////////////////////
/// Interface:
///		Handles and controls all aspects of the
///		ingame HUD.
/////////////////////////////////////////////////

namespace Interface
{
	void Initialize();
	void Event(sf::Event& Event);
	void Render();
	void DisplaySystemMessage(std::string Message);

	void SetShowInterface(bool Show);
	void SwitchShowInterface();

	namespace
	{
		bool	ShowInterface;			///< Show Interface?
	}
}

#endif