#include "stdafx.h"
#include "CppUnitTest.h"

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace quarto;


namespace QuartoTests
{
	bool operator== (const Piece& lhs, const Piece& rhs) noexcept
	{
		return lhs.GetBody() == rhs.GetBody()
			&& lhs.GetColor() == rhs.GetColor()
			&& lhs.GetHeight() == rhs.GetHeight()
			&& lhs.GetShape() == rhs.GetShape();
	}

	TEST_CLASS(BoardTests)
	{
	public:
		using enum Piece::Body;
		using enum Piece::Color;
		using enum Piece::Height;
		using enum Piece::Shape;

		TEST_METHOD(DefaultConstructorEmptyBoard)
		{
			Board board;
			Board::Position position;
			auto& [line, column] = position;

			for (line = 0u; line < Board::kHeight; ++line)
				for (column = 0u; column < Board::kWidth; ++column)
					if (board[position].has_value())
						Assert::Fail();
		}

		TEST_METHOD(SetGetAtOneOne)
		{
			Board board;
			Piece piece{ Hollow, Light, Short, Round };
			Board::Position position{ 1, 1 };
			board[position] = piece;

			// Get test
			Assert::IsTrue(board[position].has_value());
			
			// Set test

			// Solution 1
			int epectedMemDiff{ 0 };
			int memDiff{ memcmp(&board[position], &piece, sizeof piece) };
			Assert::AreEqual(epectedMemDiff, memDiff);

			// Solution 2
			Assert::IsTrue(
				board[position]->GetBody() == piece.GetBody()
				&& board[position]->GetColor() == piece.GetColor()
				&& board[position]->GetHeight() == piece.GetHeight()
				&& board[position]->GetShape() == piece.GetShape()
			);

			// Solution 3
			// overload operator == for Piece
			Assert::IsTrue(board[position].value() == piece);
		}

		TEST_METHOD(GetAtOneOneConst)
		{
			const Board board;
			Board::Position position{ 1, 1 };

			Assert::IsFalse(board[position].has_value());
		}

		TEST_METHOD(GetAtMinusOneOne)
		{
			Board board;
			Board::Position position{ -1, 1 };

			Assert::ExpectException<std::out_of_range>(
				[&]() { board[position]; }
			);
		}

		TEST_METHOD(GetAtMinusOneOneConst)
		{
			const Board board;
			Board::Position position{ -1, 1 };

			Assert::ExpectException<std::out_of_range>(
				[&]() { board[position]; }
			);
		}

		TEST_METHOD(GetAtOneMinusOne)
		{
			Board board;
			Board::Position position{ 1, -1 };

			Assert::ExpectException<std::out_of_range>(
				[&]() { board[position]; }
			);
		}

		TEST_METHOD(GetAtOneMinusOneConst)
		{
			const Board board;
			Board::Position position{ 1, -1 };

			Assert::ExpectException<std::out_of_range>(
				[&]() { board[position]; }
			);
		}

		TEST_METHOD(GetLineTwo)
		{
			Board board;
			Piece piece1{ Full, Dark, Short, Round };
			board[{2, 0}] = piece1;
			Piece piece2{ Hollow, Light, Short, Square };
			board[{2, 2}] = piece2;
			auto line{ board.GetLine(2) };
			size_t expectedIterations{ 4 };
			size_t iterations{ 0 };

			// Test expected number of iterations
			for (const auto& _ : line)
			{
				++iterations;
			}

			Assert::AreEqual(expectedIterations, iterations);

			// Test access and values (Random Access Iterable needed)
			Assert::IsTrue(piece1 == line[0].value());
			Assert::IsFalse(line[1].has_value());
			Assert::IsTrue(piece2 == line[2].value());
			Assert::IsFalse(line[3].has_value());
		}

		TEST_METHOD(GetColumnOne)
		{
			Board board;
			Piece piece1{ Full, Light, Short, Round };
			board[{1, 1}] = piece1;
			Piece piece2{ Hollow, Dark, Short, Square };
			board[{2, 1}] = piece2;
			auto column{ board.GetColumn(1) };
			size_t expectedIterations{ 4 };
			size_t iterations{ 0 };

			// Test expected number of iterations
			for (const auto& _ : column)
			{
				++iterations;
			}

			Assert::AreEqual(expectedIterations, iterations);

			// Test access and values (Random Access Iterable needed)
			Assert::IsFalse(column[0].has_value());
			Assert::IsTrue(piece1 == column[1].value());
			Assert::IsTrue(piece2 == column[2].value());
			Assert::IsFalse(column[3].has_value());
		}

		TEST_METHOD(GetMainDiagonal)
		{
			Board board;
			Piece piece1{ Full, Light, Short, Round };
			board[{1, 1}] = piece1;
			Piece piece2{ Hollow, Dark, Short, Square };
			board[{2, 2}] = piece2;
			auto diagonal{ board.GetMainDiagonal() };
			size_t expectedIterations{ 4 };
			size_t iterations{ 0 };

			// Test expected number of iterations
			for (const auto& _ : diagonal)
			{
				++iterations;
			}

			Assert::AreEqual(expectedIterations, iterations);

			// Test access and values (Random Access Iterable needed)
			Assert::IsFalse(diagonal[0].has_value());
			Assert::IsTrue(piece1 == diagonal[1].value());
			Assert::IsTrue(piece2 == diagonal[2].value());
			Assert::IsFalse(diagonal[3].has_value());
		}

		TEST_METHOD(GetSecondaryDiagonal)
		{
			Board board;
			Piece piece1{ Full, Light, Short, Round };
			board[{0, 3}] = piece1;
			Piece piece2{ Hollow, Dark, Short, Square };
			board[{2, 1}] = piece2;
			auto diagonal{ board.GetSecondaryDiagonal() };
			size_t expectedIterations{ 4 };
			size_t iterations{ 0 };

			// Test expected number of iterations
			for (const auto& _ : diagonal)
			{
				++iterations;
			}

			Assert::AreEqual(expectedIterations, iterations);

			// Test access and values (Random Access Iterable needed)
			Assert::IsTrue(piece1 == diagonal[0].value());
			Assert::IsFalse(diagonal[1].has_value());
			Assert::IsTrue(piece2 == diagonal[2].value());
			Assert::IsFalse(diagonal[3].has_value());
		}

		TEST_METHOD(IsFullThreePieces)
		{
			Board board;
			board[{0, 0}] = Piece{ Hollow, Dark, Tall, Square };
			board[{2, 1}] = Piece{ Full, Light, Short, Round };
			board[{3, 2}] = Piece{ Full, Dark, Tall, Square };
			
			Assert::IsFalse(board.IsFull());
		}

		TEST_METHOD(IsFullAllPieces)
		{
			Board board;
			board[{0, 0}] = Piece{ Hollow, Dark, Tall, Square };
			board[{0, 1}] = Piece{ Full, Light, Short, Round };
			board[{0, 2}] = Piece{ Full, Dark, Tall, Square };
			board[{0, 3}] = Piece{ Hollow, Light, Short, Round };

			board[{1, 0}] = Piece{ Full, Light, Tall, Round };
			board[{1, 1}] = Piece{ Hollow, Dark, Short, Square };
			board[{1, 2}] = Piece{ Hollow, Light, Tall, Round };
			board[{1, 3}] = Piece{ Full, Dark, Short, Square };

			board[{2, 0}] = Piece{ Hollow, Dark, Tall, Round };
			board[{2, 1}] = Piece{ Full, Dark, Tall, Round };
			board[{2, 2}] = Piece{ Full, Dark, Short, Round };
			board[{2, 3}] = Piece{ Hollow, Light, Tall, Square };

			board[{3, 0}] = Piece{ Hollow, Light, Short, Square };
			board[{3, 1}] = Piece{ Hollow, Dark, Short, Round };
			board[{3, 2}] = Piece{ Full, Light, Tall, Square };
			board[{3, 3}] = Piece{ Full, Light, Short, Square };

			Assert::IsTrue(board.IsFull());
		}
	};
}