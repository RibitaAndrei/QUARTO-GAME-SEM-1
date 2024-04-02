#pragma once

#include "Piece.h"
#include "Board.h"
#include "UnusedPieces.h"
#include "Player.h"
#include "BoardStateChecker.h"


int main()
{
	using namespace quarto;
	using enum Piece::Body;
	using enum Piece::Color;
	using enum Piece::Height;
	using enum Piece::Shape;

	Piece piece{ Full, Dark, Short, Square };
	std::cout << "Full, Dark, Short, Square piece: " << piece << std::endl;

	Board board;
	std::cout << "Empty board:\n" << board << std::endl;

	board[{0, 0}] = std::move(piece);
	std::cout << "Moved piece to board:\n" << board << std::endl;

	UnusedPieces unusedPieces;
	std::cout << "All available pieces:\n" << unusedPieces << std::endl;
	unusedPieces.PickPiece("0001");
	std::cout << "Extracted \"0001\" remaining pieces after extracted:\n" << unusedPieces << std::endl;

	Player player{ "player1" };
	std::cout << "Player 1 pick a piece: ";
	auto pickedPiece{ player.PickPiece(std::cin, unusedPieces) };
	std::cout << player << " picked piece: " << pickedPiece << std::endl;

	std::cout << "Player 1 write a position: ";
	auto position{ player.PlacePiece(std::cin, std::move(pickedPiece), board) };
	std::cout << player << " placed piece on: " << position.first << " " << position.second << std::endl;

	std::cout << "\nUpdated board:\n";
	std::cout << board;

	return 0;
}
