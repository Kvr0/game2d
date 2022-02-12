#pragma once
#ifndef _GAME2D_S4MATHMATRIX_H_
#define _GAME2D_S4MATHMATRIX_H_
#include "s4BaseObject.h"
#include "s4Matrix.h"
#include "DxLib.h"
namespace game2d
{
	template<typename T, size_t N, size_t M, std::enable_if_t<N == M, std::nullptr_t> = nullptr> class __MatrixDet;


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
		s4MathMatrix& add(const s4MathMatrix& _rhs)
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

		// �萔�{
		s4MathMatrix& coe(const T& _rhs)
		{
			for (auto& v : data)
			{
				v *= _rhs;
			}
			return *this;
		}

		// ���Z
		s4MathMatrix& sub(const s4MathMatrix& _rhs)
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

		// ��Z
		// A<W,H> * B<H,R>
		template<size_t R>
		s4MathMatrix<T, N, R> mul(const s4MathMatrix<T, M, R>& _rhs) const
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

		// ��Βl

		// �t�s��

		// �]���q
		constexpr s4MathMatrix<T, N - 1, M - 1> adj(size_t _i, size_t _j) const
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

		// �s��
		constexpr T det() const
		{
			static_assert(N == M, "game2d::s4MathMatrix::det: This matrix must be a square matrix.");
			return __MatrixDet<T,N,M>()(*this);
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

	};

	template<typename T, size_t N, size_t M, std::enable_if_t<N == M, std::nullptr_t>>
	class __MatrixDet
	{
	public:
		constexpr T operator()(const s4MathMatrix<T, N, M>& _mat) const
		{
			T ret = 0;
			for (size_t i = 0; i < N; i++)
			{
				ret += (i % 2 == 0 ? 1 : -1) * _mat.at({ i,0 }) * _mat.adj(i, 0).det();
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
}
#endif // !_GAME2D_S4MATHMATRIX_H_