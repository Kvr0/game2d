#pragma once
#ifndef _GAME2D_S4MATHMATRIX_H_
#define _GAME2D_S4MATHMATRIX_H_
#include "s4BaseObject.h"
#include "s4Matrix.h"
#include <cmath>
namespace game2d
{
	template<typename T, size_t N, size_t M, std::enable_if_t<N == M, std::nullptr_t> = nullptr> class __MatrixDet;

	template<typename T, size_t S, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr> class s4ColumnMathVector;
	template<typename T, size_t S, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr> class s4RowMathVector;


	template<typename T, size_t N, size_t M, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	class s4MathMatrix : public s4Matrix<T, N, M>
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4MathMatrix<T, N, M>, s4Matrix<T, N, M>>();
	public:
		using s4Matrix<T, N, M>::s4Matrix;
		using s4Matrix<T, N, M>::at;
		using s4Matrix<T, N, M>::data;

		// ���Z
		constexpr s4MathMatrix& add(const s4MathMatrix& _rhs)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					at({i,j}) += _rhs.at({ i,j });
				}
			}
			return *this;
		}
		constexpr s4MathMatrix& operator+=(const s4MathMatrix& _rhs)
		{
			return add(_rhs);
		}
		constexpr s4MathMatrix operator+(const s4MathMatrix& _rhs) const
		{
			s4MathMatrix tmp = *this;
			tmp.add(_rhs);
			return tmp;
		}

		// ���Z
		constexpr s4MathMatrix& sub(const s4MathMatrix& _rhs)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					at({ i,j }) -= _rhs.at({ i,j });
				}
			}
			return *this;
		}
		constexpr s4MathMatrix& operator-=(const s4MathMatrix& _rhs)
		{
			return sub(_rhs);
		}
		constexpr s4MathMatrix operator-(const s4MathMatrix& _rhs) const
		{
			s4MathMatrix tmp = *this;
			tmp.sub(_rhs);
			return tmp;
		}

		// �萔��Z
		constexpr s4MathMatrix& coe_mul(const T& _rhs)
		{
			for (auto& v : data)
			{
				v *= _rhs;
			}
			return *this;
		}
		constexpr s4MathMatrix& operator*=(const T& _rhs)
		{
			return coe_mul(_rhs);
		}
		constexpr s4MathMatrix operator*(const T& _rhs) const
		{
			s4MathMatrix tmp = *this;
			tmp.coe_mul(_rhs);
			return tmp;
		}

		// �萔���Z
		constexpr s4MathMatrix& coe_div(const T& _rhs)
		{
			for (auto& v : data)
			{
				v /= _rhs;
			}
			return *this;
		}
		constexpr s4MathMatrix& operator/=(const T& _rhs)
		{
			return coe_mul(_rhs);
		}
		constexpr s4MathMatrix operator/(const T& _rhs) const
		{
			s4MathMatrix tmp = *this;
			tmp.coe_div(_rhs);
			return tmp;
		}

		// ��Z
		// A<N,M> * B<M,R>
		template<size_t R>
		constexpr s4MathMatrix<T, N, R> mul(const s4MathMatrix<T, M, R>& _rhs) const
		{
			s4MathMatrix<T, N, R> tmp;

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					for (size_t k = 0; k < R; k++)
					{
						tmp.at({ i, k }) += at({ i,j }) * _rhs.at({ j, k });
					}
				}
			}
			return tmp;
		}
		template<size_t R>
		constexpr s4MathMatrix<T, N, R> operator*(const s4MathMatrix<T, M, R>& _rhs) const
		{
			return mul(_rhs);
		}

		// ���s��
		constexpr s4MathMatrix<T, N - 1, M - 1> minor(size_t _i, size_t _j) const
		{
			s4MathMatrix<T, N - 1, M - 1> tmp;

			for (size_t i = 0; i < N; i++)
			{
				if (i != _i)
				{
					for (size_t j = 0; j < M; j++)
					{
						if (j != _j)
						{
							tmp.at({ (i < _i ? i:i - 1),(j < _j ? j:j - 1) }) = at({ i,j });
						}
					}
				}
			}

			return tmp;
		}

		// �]���q
		constexpr T adj(size_t _i, size_t _j) const
		{
			return ((_i+_j) % 2 == 0 ? 1 : -1) * minor(_i, _j).det();
		}

		// �]���q�s��
		constexpr s4MathMatrix adj_mat() const
		{
			s4MathMatrix tmp;

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					tmp.at({ j,i }) = adj(i, j);
				}
			}

			return tmp;
		}

		// �s��
		constexpr T det() const
		{
			static_assert(N == M, "game2d::s4MathMatrix::det: This matrix must be a square matrix.");
			return __MatrixDet<T,N,M>()(*this);
		}

		// �t�s��
		constexpr s4MathMatrix inverse() const
		{
			return adj_mat().coe_div(det());
		}

		// �]�u�s��
		constexpr s4MathMatrix<T, M, N> trans() const
		{
			s4MathMatrix<T,M,N> tmp;

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					tmp.at({ j,i }) = at({i,j});
				}
			}

			return tmp;
		}

		// �[��
		static constexpr s4MathMatrix zero()
		{
			return s4MathMatrix();
		}

		// �P�ʍs��
		static constexpr s4MathMatrix identity()
		{
			s4MathMatrix tmp;
			for (size_t i = 0; i < N; i++)
			{
				tmp.at({ i,i }) = 1;
			}
			return tmp;
		}

		// �s��̑傫��
		constexpr T magnitude() const
		{
			T tmp = 0;
			if (!std::is_floating_point<T>::value) return tmp;
			for (auto& v : data) tmp += v * v;
			return std::sqrt(tmp);
		}
	};

	// �萔��Z
	template<typename T, size_t N, size_t M, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	constexpr s4MathMatrix<T, N, M> operator*(const T& _lhs, const s4MathMatrix<T, N, M>& _rhs)
	{
		return _rhs * _lhs;
	}

	// �s�񎮌v�Z
	template<typename T, size_t N, size_t M, std::enable_if_t<N == M, std::nullptr_t>>
	class __MatrixDet
	{
	public:
		constexpr T operator()(const s4MathMatrix<T, N, M>& _mat) const
		{
			T ret = 0;
			for (size_t i = 0; i < N; i++)
			{
				ret += _mat.at({ i,0 }) * _mat.adj(i, 0);
			}
			return ret;
		}
	};
	template<typename T>
	class __MatrixDet<T,1,1>
	{
	public:
		constexpr T operator()(const s4MathMatrix<T, 1,1>& _mat) const
		{
			return _mat.at({ 0,0 });
		}
	};

	// �s�x�N�g��
	template<typename T, size_t S, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t>>
	class s4ColumnMathVector : public s4Matrix<T, 1, S>
	{
	public:
		using value_type = T;
	private:
		static inline bool ___ = s4BaseObject::apply<s4ColumnMathVector<T, S>, s4Matrix<value_type, 1, S>>();
	public:
		using s4ColumnMathVector<value_type, 1, S>::s4Matrix;
		using s4ColumnMathVector<value_type, 1, S>::at;

		// �擾
		constexpr value_type& at(size_t _idx)
		{
			return at({ 0, _idx });
		}
		constexpr const value_type& at(size_t _idx) const
		{
			return at({ 0, _idx });
		}

		constexpr value_type& operator[](size_t _idx)
		{
			return at(_idx);
		}
		constexpr const value_type& operator[](size_t _idx) const
		{
			return at(_idx);
		}
	};

	// ��x�N�g��
	template<typename T, size_t S, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t>>
	class s4RowMathVector : public s4Matrix<T, S, 1>
	{
	public:
		using value_type = T;
	private:
		static inline bool ___ = s4BaseObject::apply<s4RowMathVector<T, S>, s4Matrix<value_type, S, 1>>();
	public:
		using s4RowMathVector<value_type, S, 1>::s4Matrix;
		using s4RowMathVector<value_type, 1, S>::at;

		// �擾
		constexpr value_type& at(size_t _idx)
		{
			return at({ _idx, 0 });
		}
		constexpr const value_type& at(size_t _idx) const
		{
			return at({ _idx, 0 });
		}

		constexpr value_type& operator[](size_t _idx)
		{
			return at(_idx);
		}
		constexpr const value_type& operator[](size_t _idx) const
		{
			return at(_idx);
		}
	};

	template<typename T, size_t S, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	using s4MathVector = s4ColumnMathVector<T, S>;


	// �x�N�g���̍쐬
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	s4ColumnMathVector<T, S> make_s4ColumnMathVector(T _arg0, Args ...args)
	{
		return s4ColumnMathVector<T, S>({ _arg0, args... });
	}
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	s4RowMathVector<T, S> make_s4RowMathVector(T _arg0, Args ...args)
	{
		return s4RowMathVector<T, S>({ _arg0, args... });
	}
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
	s4MathVector<T, S> make_s4MathVector(T _arg0, Args ...args)
	{
		return s4MathVector<T, S>({ _arg0, args... });
	}
}
#endif // !_GAME2D_S4MATHMATRIX_H_