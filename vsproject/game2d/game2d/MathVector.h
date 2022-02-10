#pragma once
#include "BaseObject.h"
namespace game2d
{
	class MathVector : public BaseObject
	{
	private:
		// ObjectTypeo^p¼Ï
		static bool ___;
	public:
		float x;
		float y;

		MathVector(float _x, float _y);
		virtual ~MathVector();

		// ½]
		MathVector operator-() const;

		// ÁZ
		MathVector& operator+=(const MathVector& _rhs);
		friend MathVector operator+(const MathVector& _lhs, const MathVector& _rhs);

		// ¸Z
		MathVector& operator-=(const MathVector& _rhs);
		friend MathVector operator-(const MathVector& _lhs, const MathVector& _rhs);

		// æZ
		MathVector& operator*=(float _rhs);
		friend MathVector operator*(const MathVector& _lhs, float _rhs);

		// Z
		MathVector& operator/=(float _rhs);
		friend MathVector operator/(const MathVector& _lhs, float _rhs);

		// xNgÌå«³
		float magnitude() const;

		// ³K»
		MathVector& normalize();
		MathVector normalized() const;

		// àÏ
		float inner_product(const MathVector& _rhs) const;

		// px
		float angle(const MathVector& _rhs) const;
		float angle() const;
	};
}