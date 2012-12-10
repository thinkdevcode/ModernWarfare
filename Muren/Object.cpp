#include "Object.h"

sf::Uint32 Object::m_StaticId = 0;

Object::Object()
{
	m_UniqueId = m_StaticId;
	m_StaticId++;
}

Object::~Object()
{ }

const sf::Uint32 Object::GetId() const
{
	return m_UniqueId;
}