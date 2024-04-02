#pragma once
#include <array>
#include <optional>
#include <ranges>

#include "Piece.h"


namespace quarto
{
	class Board
	{
	public:
		using Position = std::pair<size_t, size_t>;
		static const size_t kWidth{ 4 };
		static const size_t kHeight{ 4 };

	public:
		Board() = default;

		// Getter
		const std::optional<Piece>& operator[] (const Position& pos) const;
		// Getter and/or Setter
		std::optional<Piece>& operator[] (const Position& pos);

		// C++23 Explicit object (this) parameter
		// Oct 2023 - Commented because it is not supported inside modules
		//template<typename Self>
		//auto&& operator[] (this Self&& self, const Position& position)
		//{
		//	const auto& [line, column] = position;
		//	return self.m_pieces[line * kWidth + column];
		//}

		auto GetLine(size_t index) const
		{
			return m_pieces 
				| std::views::drop(index * kWidth) 
				| std::views::take(kWidth);
		}

		auto GetColumn(size_t index) const
		{
			return m_pieces
				| std::views::drop(index)
				| std::views::stride(kWidth)
				| std::views::take(kHeight); //sau nu
		}

		auto GetMainDiagonal() const
		{
			return m_pieces
				| std::views::stride(kWidth + 1)
				| std::views::take(kHeight);

		}

		auto GetSecondaryDiagonal() const
		{
			return m_pieces
				| std::views::drop(kWidth - 1)
				| std::views::stride(kWidth - 1)
				| std::views::take(kHeight);
				
		}

		bool IsFull() const;

	private:
		static const size_t kSize{ kWidth * kHeight };
		std::array<std::optional<Piece>, kSize> m_pieces;
	};
	
	std::ostream& operator<< (std::ostream& os, const Board& board);
}