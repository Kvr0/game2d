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

		// �������]
		MathVector operator-() const;

		// ���Z
		MathVector& operator+=(const MathVector& _rhs);
		friend MathVector operator+(const MathVector& _lhs, const MathVector& _rhs);

		// ���Z
		MathVector& operator-=(const MathVector& _rhs);
		friend MathVector operator-(const MathVector& _lhs, const MathVector& _rhs);

		// ��Z
		MathVector& operator*=(float _rhs);
		friend MathVector operator*(const MathVector& _lhs, float _rhs);

		// ���Z
		MathVector& operator/=(float _rhs);
		friend MathVector operator/(const MathVector& _lhs, float _rhs);

		// �x�N�g���̑傫��
		float magnitude() const;

		// ���K��
		MathVector& normalize();
		MathVector normalized() const;

		// ����
		float inner_product(const MathVector& _rhs) const;

		// �p�x
		float angle(const MathVector& _rhs) const;
		float angle() const;
	};
}