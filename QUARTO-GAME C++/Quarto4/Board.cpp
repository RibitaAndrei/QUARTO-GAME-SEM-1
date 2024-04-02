#include "Board.h"
#include <algorithm>


using quarto::Board;
using quarto::Piece;

std::string_view kEmptyBoardCell{ "____" };

const std::optional<Piece>& Board::operator[](const Position& position) const
{
	const auto& [line, column] = position;
	if (line >= kHeight || column >= kWidth)
		throw std::out_of_range{ "Line and columns indices should be less than 4" };
	return m_pieces[line * kWidth + column];
}

std::optional<Piece>& Board::operator[](const Position& position)
{
	return const_cast<std::optional<Piece>&>(std::as_const(*this)[position]);
}

bool Board::IsFull() const
{
	return std::ranges::all_of(m_pieces, [](const auto& piece) {return piece.has_value(); });
}

std::ostream& quarto::operator<<(std::ostream& os, const Board& board)
{
	Board::Position position/*{ 0, 0 }*/;
	auto& [line, column] = position;

	for (/*line = 0*/; line < Board::kHeight; ++line)
	{
		for (column = 0; column < Board::kWidth; ++column)
		{
			if (const auto& pieceOpt{ board[position] }; pieceOpt.has_value())
				os << pieceOpt.value();  // value_or(kEmptyBoardCell) doesn't work
			else
				os << kEmptyBoardCell;
			os << ' ';
		}
		os << std::endl;
	}

	return os;
}
