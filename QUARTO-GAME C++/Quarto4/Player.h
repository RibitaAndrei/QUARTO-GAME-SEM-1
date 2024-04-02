#pragma once

#include "Board.h"
#include "UnusedPieces.h"


namespace quarto
{
	class Player
	{
	public:
		Player(std::string_view name);

		// Used when a player must choose a piece from the pool of unused pieces; the piece is removed from the pool and returned.
		// An exception is raised if the input is wrong.
		Piece PickPiece(std::istream& in, UnusedPieces& unusedPieces) const;

		// Used when the player must place a piece on the board. The function takes ownership of the piece and moves it on the board.
		// The position on the board (line, column) where the piece has been placed is returned.
		// Can throw: ios_base::failure, out_of_range or logic_error.
		Board::Position PlacePiece(std::istream& in, Piece&& piece, Board& board) const;

		const std::string& GetName() const;

	private:
		std::string m_name;
	};

	std::ostream& operator<< (std::ostream& os, const Player& player);	
}