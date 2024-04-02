#include "Player.h"


using quarto::Board;
using quarto::Piece;
using quarto::Player;

Player::Player(std::string_view name) :
	m_name{ name }
{
	// Empty
}

Piece Player::PickPiece(std::istream& in, UnusedPieces& unusedPieces) const
{
	std::string pickedPieceName;
	in >> pickedPieceName;
	Piece pickedPiece{ unusedPieces.PickPiece(pickedPieceName) };
	return pickedPiece;
}

Board::Position Player::PlacePiece(std::istream& in, Piece&& piece, Board& board) const
{
	size_t line{ std::numeric_limits<size_t>::max() };
	size_t column{ std::numeric_limits<size_t>::max() };

	if (in.good() && in >> line >> column)
	{
		Board::Position position{ line, column };

		auto& optionalPiece{ board[position] };

		if (optionalPiece.has_value())
			throw std::exception{ "That position is occupied by another piece." };

		optionalPiece = std::move(piece);

		return position;
	}

	in.clear();
	in.seekg(std::ios::end);
	// in.ignore(std::numeric_limits<size_t>::max());

	throw std::out_of_range{ "Please enter only two numbers from 0 to 3." };
}

const std::string& Player::GetName() const
{
	return m_name;
}

std::ostream& quarto::operator<<(std::ostream& os, const Player& player)
{
	os << player.GetName();
	//os.flush();
	//if (!os)
	//	std::cerr << "Unable to flush ostream parameter os\n";
	return os;
}
