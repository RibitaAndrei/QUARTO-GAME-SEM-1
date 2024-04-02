#pragma once
#include <unordered_map>

#include "Piece.h"


namespace quarto
{
	class UnusedPieces
	{
	public:
		// Creates a pool with the 16 possible pieces.
		UnusedPieces();

		// Removes the piece found with given name and returns it.
		// Raises exception if it is not found.
		Piece PickPiece(std::string_view name);

		friend std::ostream& operator<< (std::ostream& os, const UnusedPieces& unusedPieces);

	private:
		void GeneratePiecesCpp11();
		void GeneratePiecesBitset();
		void GeneratePiecesCpp2x();
		void GeneratePiecesManually();
		void EmplacePiece(Piece&& piece);

	private:
		std::unordered_map<std::string, Piece> m_pool;
	};
}