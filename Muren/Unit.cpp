////////////////////////////////////////////////////////
/// UnitStats.h
/// Created: July 27, 2009
////////////////////////////////////////////////////////

#include "Unit.h"

Unit::Unit(sf::RenderWindow& Game, sf::Image &Image, sf::Uint32 TeamId, sf::Uint32 PlayerId, void (*DeathFunc)(Unit*))
: m_RenderWindow(Game), m_Image(Image), m_Stats(), m_Selected(false), m_TeamId(TeamId), m_Moving(false), m_TargetUnit(NULL), m_PlayerId(PlayerId)
{
	m_Sprite.SetImage(Image);
	m_Sprite.SetCenter((float)(Image.GetHeight() / 2), (float)(Image.GetWidth() / 2));
	m_Height = (float)Image.GetHeight();
	m_Width = (float)Image.GetWidth();
	m_TargetTimer.Reset();
	m_ShootTimer.Reset();
	Death = DeathFunc;
}

Unit::Unit(sf::RenderWindow& Game, sf::Image &Image, sf::Uint32 TeamId, sf::Uint32 PlayerId, UnitStats Stats, void (*DeathFunc)(Unit*))
: m_RenderWindow(Game), m_Image(Image), m_Stats(Stats), m_Selected(false), m_TeamId(TeamId), m_Moving(false), m_TargetUnit(NULL), m_PlayerId(PlayerId)
{
	m_Sprite.SetImage(Image);
	m_Sprite.SetCenter((float)(Image.GetHeight() / 2), (float)(Image.GetWidth() / 2));
	m_Height = (float)Image.GetHeight();
	m_Width = (float)Image.GetWidth();
	m_TargetTimer.Reset();
	m_ShootTimer.Reset();
	Death = DeathFunc;
}

Unit::~Unit()
{

}

void Unit::Render()
{
	if (m_Selected)
	{
		m_HealthBarOutline = sf::Shape::Rectangle((m_Sprite.GetPosition().x - 12), (m_Sprite.GetPosition().y - 19), (m_Sprite.GetPosition().x + 12), (m_Sprite.GetPosition().y - 10), sf::Color::Black);
		m_HealthBar = sf::Shape::Rectangle((m_Sprite.GetPosition().x - 10), (m_Sprite.GetPosition().y - 17), (m_Sprite.GetPosition().x + 10), (m_Sprite.GetPosition().y - 12), sf::Color::Green);
		m_RenderWindow.Draw(m_HealthBarOutline);
		m_RenderWindow.Draw(m_HealthBar);
	}

	if (m_Moving)
	{
		float TravelDistance = m_Stats.RunSpeed * m_RenderWindow.GetFrameTime();

		float MovingOne = gtp::math::Distance(gtp::math::Vector2(m_Sprite.GetPosition().x, m_Sprite.GetPosition().y), gtp::math::Vector2(m_LastPosition.x, m_LastPosition.y));
		float MovingTwo = gtp::math::Distance(gtp::math::Vector2(m_GoToPosition.x, m_GoToPosition.y), gtp::math::Vector2(m_LastPosition.x, m_LastPosition.y));

		if (MovingOne + TravelDistance > MovingTwo)
		{
			m_Sprite.SetPosition(m_GoToPosition);
			m_Moving = false;
		}

		else
		{
			m_Sprite.SetX(m_Sprite.GetPosition().x + (m_NormalVector.x * m_Stats.RunSpeed * m_RenderWindow.GetFrameTime()));
			m_Sprite.SetY(m_Sprite.GetPosition().y + (m_NormalVector.y * m_Stats.RunSpeed * m_RenderWindow.GetFrameTime()));
		}
	}

	if (Alive())
		m_RenderWindow.Draw(m_Sprite);
}

void Unit::Update(std::map<sf::Uint32, Unit *>& Units)
{
	std::map<sf::Uint32, Unit *>::iterator UnitIt;

	//see if units overlapping
	for (UnitIt = Units.begin(); UnitIt != Units.end(); ++UnitIt)
	{
		//check if target unit is the same team
		if (UnitIt->second->GetTeam() == m_TeamId)
		{
			//check if target is itself
			if (UnitIt->second->GetId() != this->GetId())
			{
				//see if collision occured with target unit
				if (CircleTestA(UnitIt->second->GetSprite()))
				{
					//move unit away from target unit
					int Random1 = sf::Randomizer::Random(-3, 3);
					int Random2 = sf::Randomizer::Random(-3, 3);
					this->MoveToPosition(sf::Vector2f(m_Sprite.GetPosition().x + ((m_Sprite.GetSize().x / 2) + Random1), m_Sprite.GetPosition().y + ((m_Sprite.GetSize().y / 2) + Random2)));
				}
			}
		}
		//since target is not the same team, select target, and shoot
		else
		{
			//target new unit
			if (m_TargetTimer.GetElapsedTime() > 0.75f)
			{
				if (m_TargetUnit == NULL || !m_TargetUnit->Alive())
				{
					//check if target unit is within range
					if (CircleTestB(UnitIt->second->GetSprite(), m_Stats.AttackRange))
					{
						m_TargetUnit = UnitIt->second;
					}
				}
				m_TargetTimer.Reset();
			}

			//shoot target unit
			if (m_TargetUnit != NULL && m_TargetUnit->Alive())
			{
				if (m_ShootTimer.GetElapsedTime() > 1.f)
				{
					ShootPrimaryWeapon();
					m_ShootTimer.Reset();
				}
			}
		}
	}
}

bool Unit::CircleTestA(const sf::Sprite& Target)
{
    float Radius1 = (m_Sprite.GetSize().x + m_Sprite.GetSize().y) / 4;
    float Radius2 = (Target.GetSize().x + Target.GetSize().y) / 4;

	float square_distance = (m_Sprite.GetPosition().x - Target.GetPosition().x) * (m_Sprite.GetPosition().x - Target.GetPosition().x) +
							(m_Sprite.GetPosition().y - Target.GetPosition().y) * (m_Sprite.GetPosition().y - Target.GetPosition().y);
 
    return square_distance <= ((Radius1 + Radius2) * (Radius1 + Radius2));
}

bool Unit::CircleTestB(const sf::Sprite& Target, float Radius)
{
	float square_distance = (m_Sprite.GetPosition().x - Target.GetPosition().x) * (m_Sprite.GetPosition().x - Target.GetPosition().x) +
							(m_Sprite.GetPosition().y - Target.GetPosition().y) * (m_Sprite.GetPosition().y - Target.GetPosition().y);
 
    return square_distance <= (Radius * Radius);
}

const sf::Vector2f& Unit::GetPosition() const
{
	return m_Sprite.GetPosition();
}

const UnitStats& Unit::GetStats() const
{
	return m_Stats;
}

const sf::Sprite& Unit::GetSprite() const
{
	return m_Sprite;
}

const bool Unit::Selected() const
{
	return m_Selected;
}

const sf::Uint32 Unit::GetTeam() const
{
	return m_TeamId;
}

void Unit::SetStats(UnitStats Stats)
{
	m_Stats = Stats;
}

void Unit::SetPosition(sf::Vector2f NewPosition)
{
	m_LastPosition = m_Sprite.GetPosition();
	m_Sprite.SetPosition(NewPosition);
}

void Unit::SetSelected(bool Selected)
{
	m_Selected = Selected;
}

const bool Unit::Alive() const
{
	return (m_Stats.HealthPoints > 0);
}

void Unit::MoveToPosition(sf::Vector2f Position)
{
	if (m_Selected)
	{
		if(Position != this->GetPosition())
		{
			if(Position != m_GoToPosition)
			{
				m_GoToPosition = Position;
				m_NormalVector = gtp::math::Normalize(gtp::math::Vector2(m_GoToPosition.x, m_GoToPosition.y), gtp::math::Vector2(m_Sprite.GetPosition().x, m_Sprite.GetPosition().y));
				m_LastPosition = this->GetPosition();
				m_Moving = true;
			}
		}
	}
}

void Unit::SelectionBox(sf::Vector2f Begin, sf::Vector2f End)
{
	if (m_PlayerId == m_TeamId)
	{
		float SelectionTest = (End.x - m_Sprite.GetPosition().x) + (End.y - m_Sprite.GetPosition().y);
		float MinX = std::min(Begin.x, End.x);
		float MaxX = std::max(Begin.x, End.x);
		float MinY = std::min(Begin.y, End.y);
		float MaxY = std::max(Begin.y, End.y);
		if (SelectionTest >= -(m_Height / 3) && SelectionTest <= (m_Height / 3))
		{
			m_Selected = true;
		}
		else if (m_Sprite.GetPosition().x < MinX ||
			m_Sprite.GetPosition().x > MaxX ||
			m_Sprite.GetPosition().y < MinY ||
			m_Sprite.GetPosition().y > MaxY)
		{
			m_Selected = false;
		}
		else
		{
			m_Selected = true;
		}
	}
}


void Unit::TakeDamage(int Damage)
{
	m_Stats.HealthPoints -= Damage;
	if (m_Stats.HealthPoints <= 0)
		Death(this);
}

void Unit::ShootPrimaryWeapon()
{
	if (m_TargetUnit != NULL && m_TargetUnit->Alive() && m_Stats.AmmunitionCount > 0)
	{
		m_TargetUnit->TakeDamage(m_Stats.AttackPower);
		--m_Stats.AmmunitionCount;
	}
}