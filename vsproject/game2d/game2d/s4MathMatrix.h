#pragma once
#ifndef _GAME2D_S4MATHMATRIX_H_
#define _GAME2D_S4MATHMATRIX_H_
#include "s4BaseObject.h"
#include "s4Matrix.h"
#include "DxLib.h"
namespace game2d
{
	template<typename T, size_t N, size_t M> class MatrixDet;


	template<typename T, size_t N, size_t M>
	class s4MathMatrix : public s4Matrix<T, N, M>
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4MathMatrix<T, N, M>, s4Matrix<T, N, M>>();
	public:
		using s4Matrix<T, N, M>::s4Matrix;
		using s4Matrix<T, N, M>::at;
		using s4Matrix<T, N, M>::data;

		// 加算
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

		// 定数倍
		s4MathMatrix& coe(const T& _rhs)
		{
			for (auto& v : data)
			{
				v *= _rhs;
			}
			return *this;
		}

		// 減算
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

		// 乗算
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

		// 絶対値

		// 逆行列

		// 固有値

		// 固有ベクトル

		// 余因子
		s4MathMatrix<T, N - 1, M - 1> adj(size_t _i, size_t _j) const
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

		// 行列式
		T det() const
		{
			return __MatrixDet<T,N,M>()(*this);
		}

		// 転置行列

		// ゼロ
		static constexpr s4MathMatrix zero()
		{
			return s4MathMatrix();
		}

		// 単位行列
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

	template<typename T, size_t N, size_t M>
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