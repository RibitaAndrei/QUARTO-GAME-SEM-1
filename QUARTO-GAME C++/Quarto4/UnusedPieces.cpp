#include "UnusedPieces.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <ranges>
#include <sstream>


using std::uint8_t;
using quarto::Piece;
using quarto::UnusedPieces;
// you can also use the namespace quarto{} and implement the methods inside it

UnusedPieces::UnusedPieces()
{
	// GeneratePiecesCpp11();
	GeneratePiecesBitset();
	// GeneratePiecesCpp2x();
	// GeneratePiecesManually();
}

Piece UnusedPieces::PickPiece(std::string_view name)
{
	/*
	if (auto itMap{ m_pool.find(std::string{ name }) }; itMap != m_pool.end())
	{
		Piece piece{ std::move(itMap->second) };
		m_pool.erase(itMap);
		return piece;
	}
	else
		throw std::invalid_argument{ "Piece not found" };
	*/

	
	if (auto node{ m_pool.extract(std::string{ name }) }; node)
		return std::move(node.mapped());
	else
		throw std::invalid_argument{ "Piece not found" };
}

std::ostream& quarto::operator<<(std::ostream& os, const UnusedPieces& unusedPieces)
{
	/*
	for (const auto &it : unusedPieces.m_pool)
		os << it.first << " ";
	*/

	for (const auto& [pieceName, piece] : unusedPieces.m_pool)
		os << pieceName << "  ";
	return os;

	// C++20 Ranges
	// for (const std::string& pieceName : unusedPieces.m_pool | std::ranges::views::keys)
	//	os << pieceName << "  ";
	// return os;
}

void UnusedPieces::GeneratePiecesCpp11()
{
	//const size_t kPermutationPoolSize{ 8 };
	std::array/*<uint8_t, kPermutationPoolSize>*/ permutationPool{ 0, 0, 0, 0, 1, 1, 1, 1 }; // CTAD
	const size_t kPermutationSize{ 4 };
	const size_t kMaxPermutations{ 5 };

	for (size_t currentPermutation{ /*0*/ }; currentPermutation < kMaxPermutations; ++currentPermutation)
	{
		auto itPoolBegin{ permutationPool.begin() + currentPermutation };
		auto itPoolEnd{ permutationPool.begin() + currentPermutation + kPermutationSize }; // itPoolBegin + kPermutationSize

		do
		{
			EmplacePiece(Piece{
				static_cast<Piece::Body>(*itPoolBegin),
				static_cast<Piece::Color>(*(itPoolBegin + 1)),
				static_cast<Piece::Height>(*(itPoolBegin + 2)),
				static_cast<Piece::Shape>(*(itPoolBegin + 3))
			});
		} while (std::next_permutation(itPoolBegin, itPoolEnd));
	}
}

void UnusedPieces::GeneratePiecesBitset()
{
	for (unsigned i{ 0 }; i < 16u; ++i)
	{
		std::bitset<4> pieceBits{ i };
		EmplacePiece(Piece{
			static_cast<Piece::Body>(pieceBits.test(3)),
			static_cast<Piece::Color>(pieceBits.test(2)),
			static_cast<Piece::Height>(pieceBits.test(1)),
			static_cast<Piece::Shape>(pieceBits.test(0)),
		});
	}
}

void UnusedPieces::GeneratePiecesCpp2x()
{
	std::array permutationPool{ 0, 0, 0, 0, 1, 1, 1, 1 };
	const size_t kPermutationSize{ 4 }; 
	//const size_t kMaxPermutations{ 5 }; // permutationPool.size() - permutationSize + 1

	namespace rv = std::ranges::views;

	// C++ 20
	//for (size_t dropCount : rv::iota(0u, kMaxPermutations)) // iota(0, maxPermutations) doesn't work
	//{
	//	auto view{ permutationPool | rv::drop(dropCount) | rv::take(kPermutationSize) };
	//	do
	//	{
	//		EmplacePiece(Piece{
	//			static_cast<Piece::Body>(view[0]),
	//			static_cast<Piece::Color>(view[1]),
	//			static_cast<Piece::Height>(view[2]),
	//			static_cast<Piece::Shape>(view[3])
	//		});
	//	} while (std::ranges::next_permutation(view).found);
	//}

	// C++ 23
	for (auto view : permutationPool | rv::slide(kPermutationSize)) // or rv::slide(permutationPool, permutationSize)
	{ 
		do
		{
			EmplacePiece(Piece{
				static_cast<Piece::Body>(view[0]),
				static_cast<Piece::Color>(view[1]),
				static_cast<Piece::Height>(view[2]),
				static_cast<Piece::Shape>(view[3])
			});
		} while (std::ranges::next_permutation(view).found);
	}
}

void UnusedPieces::GeneratePiecesManually()
{
	using enum Piece::Body;
	using enum Piece::Color;
	using enum Piece::Height;
	using enum Piece::Shape;
	EmplacePiece(Piece{ Full,   Dark,  Short, Round });
	EmplacePiece(Piece{ Hollow, Dark,  Short, Round });
	EmplacePiece(Piece{ Full,   Dark,  Short, Square });
	EmplacePiece(Piece{ Hollow, Dark,  Short, Square });
	EmplacePiece(Piece{ Full,   Dark,  Tall,  Round });
	EmplacePiece(Piece{ Hollow, Dark,  Tall,  Round });
	EmplacePiece(Piece{ Full,   Dark,  Tall,  Square });
	EmplacePiece(Piece{ Hollow, Dark,  Tall,  Square });
	EmplacePiece(Piece{ Full,   Light, Short, Round });
	EmplacePiece(Piece{ Hollow, Light, Short, Round });
	EmplacePiece(Piece{ Full,   Light, Short, Square });
	EmplacePiece(Piece{ Hollow, Light, Short, Square });
	EmplacePiece(Piece{ Full,   Light, Tall,  Round });
	EmplacePiece(Piece{ Hollow, Light, Tall,  Round });
	EmplacePiece(Piece{ Full,   Light, Tall,  Square });
	EmplacePiece(Piece{ Hollow, Light, Tall,  Square });
}

void UnusedPieces::EmplacePiece(Piece&& piece)
{
	std::stringstream stringStream;
	stringStream << piece;
	m_pool.emplace(stringStream.str(), std::forward<Piece>(piece));
	//m_pool.insert(std::make_pair(stringStream.str(), std::forward<Piece>(piece)));
	//m_pool.insert({ stringStream.str(), std::forward<Piece>(piece) });
}
