////////////////////////////////////////////////////////
/// Vector2.cpp
/// Created: July 30, 2009
////////////////////////////////////////////////////////

#include "Vector2.h"

namespace gtp
{
	namespace math
	{
		Vector2::Vector2() : x(0), y(0) { }

		Vector2::Vector2(float x, float y) : x(x), y(y) { }

		Vector2& Vector2::operator=(const Vector2& param)
		{
			x = param.x;
			y = param.y;
			return *this;
		}

		void Vector2::DeltaVector(float TargetX, float TargetY, float CurrentX, float CurrentY)
		{
			x = TargetX - CurrentX;
			y = TargetY - CurrentY;
		}

		Vector2 Normalize(Vector2 Target, Vector2 Current)
		{
			Vector2 _Normal;
			float SlopeX = Target.x - Current.x;
			float SlopeY = Target.y - Current.y;
			float Magnitude = Distance(Target, Current);
			_Normal.y = SlopeY / Magnitude;
			_Normal.x = SlopeX / Magnitude;
			return _Normal;
		}

		float Distance(Vector2 Target, Vector2 Current)
		{
			return sqrt(((Target.y - Current.y) * (Target.y - Current.y)) + ((Target.x - Current.x) * (Target.x - Current.x)));
		}
	}
}