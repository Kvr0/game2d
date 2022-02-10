#include "MathVector.h"
#include <cmath>
namespace game2d
{
	MathVector::MathVector(float _x, float _y)
		:x(_x), y(_y)
	{
	}
	MathVector::~MathVector()
	{
	}

	// •„†”½“]
	MathVector MathVector::operator-() const
	{
		return MathVector(-x,-y);
	}

	// Zp‰‰Z
	MathVector& MathVector::operator+=(const MathVector& _rhs)
	{
		this->x += _rhs.x;
		this->y += _rhs.y;
		return *this;
	}
	MathVector& MathVector::operator-=(const MathVector& _rhs)
	{
		this->x -= _rhs.x;
		this->y -= _rhs.y;
		return *this;
	}
	MathVector& MathVector::operator*=(float _rhs)
	{
		this->x *= _rhs;
		this->y *= _rhs;
		return *this;
	}
	MathVector& MathVector::operator/=(float _rhs)
	{
		this->x /= _rhs;
		this->y /= _rhs;
		return *this;
	}

	// ƒxƒNƒgƒ‹‚Ì‘å‚«‚³
	float MathVector::magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	// ³‹K‰»
	MathVector& MathVector::normalize()
	{
		return *this /= magnitude();
	}
	MathVector MathVector::normalized() const
	{
		return MathVector(*this).normalize();
	}

	// “àÏ
	float MathVector::inner_product(const MathVector& _rhs) const
	{
		return x * _rhs.x + y * _rhs.y;
	}

	// Šp“x
	float MathVector::angle(const MathVector& _rhs) const
	{
		auto a = magnitude() * _rhs.magnitude();
		return a == 0.0f ? 0.0f : std::acos(inner_product(_rhs)/a);
	}
	float MathVector::angle() const
	{
		return angle(MathVector(1.0f, 0.0f));
	}

	// “ñ€‰‰Z
	MathVector operator+(const MathVector& _lhs, const MathVector& _rhs)
	{
		auto tmp = _lhs;
		tmp += _rhs;
		return tmp;
	}
	MathVector operator-(const MathVector& _lhs, const MathVector& _rhs)
	{
		auto tmp = _lhs;
		tmp -= _rhs;
		return tmp;
	}
	MathVector operator*(const MathVector& _lhs, float _rhs)
	{
		auto tmp = _lhs;
		tmp *= _rhs;
		return tmp;
	}
	MathVector operator/(const MathVector& _lhs, float _rhs)
	{
		auto tmp = _lhs;
		tmp /= _rhs;
		return tmp;
	}
}
