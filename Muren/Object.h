#ifndef _Object_
#define _Object_

#include <SFML/Graphics.hpp>

class Object
{
public:
	const sf::Uint32 GetId() const;
	Object();
	virtual ~Object();

private:
	sf::Uint32 m_UniqueId;
	sf::Int32 m_RefCount;
	static sf::Uint32 m_StaticId;
};

#endif