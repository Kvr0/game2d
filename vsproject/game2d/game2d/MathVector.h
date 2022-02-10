#pragma once
namespace game2d
{
	class MathVector : public BaseObject
	{
	public:
		float x;
		float y;

		MathVector(float _x, float _y);
		virtual ~MathVector();

		// •„†”½“]
		MathVector operator-() const;

		// ‰ÁZ
		MathVector& operator+=(const MathVector& _rhs);
		friend MathVector operator+(const MathVector& _lhs, const MathVector& _rhs);

		// Œ¸Z
		MathVector& operator-=(const MathVector& _rhs);
		friend MathVector operator-(const MathVector& _lhs, const MathVector& _rhs);

		// æZ
		MathVector& operator*=(float _rhs);
		friend MathVector operator*(const MathVector& _lhs, float _rhs);

		// œZ
		MathVector& operator/=(float _rhs);
		friend MathVector operator/(const MathVector& _lhs, float _rhs);

		// ƒxƒNƒgƒ‹‚Ì‘å‚«‚³
		float magnitude() const;

		// ³‹K‰»
		MathVector& normalize();
		MathVector normalized() const;

		// “àÏ
		float inner_product(const MathVector& _rhs) const;

		// Šp“x
		float angle(const MathVector& _rhs) const;
		float angle() const;
	};
}