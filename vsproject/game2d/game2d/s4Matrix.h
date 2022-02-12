#pragma once
#ifndef _GAME2D_S4MATRIX_H_
#define _GAME2D_S4MATRIX_H_
#include "s4BaseObject.h"
#include <initializer_list>
#include <array>
namespace game2d
{
	template<typename T, size_t S> class s4ColumnVector;
	template<typename T, size_t S> class s4RowVector;

	template<typename T, size_t N, size_t M>
	class s4Matrix : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Matrix<T, N, M>, s4BaseObject>();
	public:
		using value_type = T;
		static inline const size_t width = M;
		static inline const size_t height = N;
	public:
		std::array<value_type, width * height> data;
	public:

		template<typename ...T>
		s4Matrix(const T& ...ts)
			:data{static_cast<const value_type&>(ts)...} {}
		s4Matrix() :data{} {}

		// 取得
		constexpr value_type& at(const s4Matrix<size_t, 2, 1>& _pos)
		{
			return data.at(width * _pos.data.at(0) + _pos.data.at(1));
		}
		constexpr const value_type& at(const s4Matrix<size_t, 2, 1>& _pos) const
		{
			return data.at(width * _pos.data.at(0) + _pos.data.at(1));
		}

		constexpr value_type& operator[](const s4Matrix<size_t, 2, 1>& _pos)
		{
			return at(_pos);
		}
		constexpr const value_type& operator[](const s4Matrix<size_t, 2, 1>& _pos) const
		{
			return at(_pos);
		}

		// 行列の大きさ
		constexpr s4Matrix<size_t, 2, 1> size() const noexcept
		{
			return { width, height };
		}

		// 特定の値で埋める
		constexpr void fill(const value_type& _u)
		{
			data.fill(_u);
		}

		// 行ベクトルの取得
		constexpr s4ColumnVector<value_type, width> getColumn(size_t _j) const
		{
			s4ColumnVector<value_type, width> tmp;
			for (size_t i = 0; i < width; i++) tmp.at(i) = at(i, _j);
			return tmp;
		}

		// 列ベクトルの取得
		constexpr s4RowVector<value_type, height> getRow(size_t _i) const
		{
			s4RowVector<value_type, height> tmp;
			for (size_t j = 0; j < height; j++) tmp.at(j) = at(_i, j);
			return tmp;
		}
	};

	// 行ベクトル
	template<typename T, size_t S>
	class s4ColumnVector : public s4Matrix<T, 1, S>
	{
	public:
		using value_type = T;
	private:
		static inline bool ___ = s4BaseObject::apply<s4ColumnVector<T, S>,s4Matrix<value_type, 1, S>>();
	public:
		using s4Matrix<value_type, 1, S>::s4Matrix;
		using s4Matrix<value_type, 1, S>::at;

		// 取得
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

	// 列ベクトル
	template<typename T, size_t S>
	class s4RowVector : public s4Matrix<T, S ,1>
	{
	public:
		using value_type = T;
	private:
		static inline bool ___ = s4BaseObject::apply<s4RowVector<T, S>, s4Matrix<value_type, S, 1>>();
	public:
		using s4Matrix<value_type, S, 1>::s4Matrix;
		using s4Matrix<value_type, 1, S>::at;

		// 取得
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

	template<typename T, size_t S>
	using s4Vector = s4ColumnVector<T,S>;


	// ベクトルの作成
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1>
	s4ColumnVector<T, S> make_s4ColumnVector(T _arg0, Args ...args)
	{
		return s4ColumnVector<T, S>({ _arg0, args... });
	}
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1>
	s4RowVector<T, S> make_s4RowVector(T _arg0, Args ...args)
	{
		return s4RowVector<T, S>({ _arg0, args... });
	}
	template<typename T, typename ...Args, size_t S = sizeof...(Args) + 1>
	s4Vector<T, S> make_s4Vector(T _arg0, Args ...args)
	{
		return s4Vector<T, S>({ _arg0, args... });
	}
}
#endif // !_GAME2D_S4MATRIX_H_