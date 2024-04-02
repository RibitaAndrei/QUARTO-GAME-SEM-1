#include "stdafx.h"
#include "CppUnitTest.h"

#include "Piece.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace quarto;


namespace QuartoTests
{		
	TEST_CLASS(PieceTests)
	{
	public:
		using enum Piece::Body;
		using enum Piece::Color;
		using enum Piece::Height;
		using enum Piece::Shape;

		TEST_METHOD(Constructor)
		{
			// AAA cum stim ca e corect un test:
			// Arange
			// Act
			// Assert
			Piece piece{ Full, Dark, Short, Square };

			Assert::IsTrue(Full == piece.GetBody());
			Assert::IsTrue(Dark == piece.GetColor());
			Assert::IsTrue(Short == piece.GetHeight());
			Assert::IsTrue(Square == piece.GetShape());
		}

		TEST_METHOD(Print)
		{	//arange
			Piece piece{ Full, Dark, Short, Square };
			std::stringstream stream;
			std::string expectedOutput{ "0001" };

			//act
			stream << piece;

			//asert
			Assert::AreEqual(expectedOutput, stream.str(), L"If you see this message, piece is not printed correctly");
		}

		// TDD - test driven development
		TEST_METHOD(BoolConversionTrue)
		{
			Piece piece{ NoBody, Dark, NoHeight, Square };

			bool result{ static_cast<bool>(piece) };

			Assert::IsTrue(result);
		}

		TEST_METHOD(BoolConversionFalse)
		{
			Piece piece;

			bool result{ static_cast<bool>(piece) };

			Assert::IsFalse(result);
		}

		TEST_METHOD(IntersectionNonEmpty)
		{
			Piece piece1{ Hollow, Dark, Tall, Round };
			Piece piece2{ Full, Dark, Tall, Square };
			Piece expectedPiece{ NoBody, Dark, Tall, NoShape };

			Piece result{ piece1 & piece2 };

			Assert::IsTrue(expectedPiece.GetBody() == result.GetBody());
			Assert::IsTrue(expectedPiece.GetColor() == result.GetColor());
			Assert::IsTrue(expectedPiece.GetHeight() == result.GetHeight());
			Assert::IsTrue(expectedPiece.GetShape() == result.GetShape());
		}

		TEST_METHOD(IntersectionEmpty)
		{
			Piece piece1{ Hollow, Dark, Tall, Round };
			Piece piece2{ Full, Light, Short, Square };
			Piece expectedPiece; // default constructed invalid piece

			Piece result{ piece1 & piece2 };

			Assert::IsTrue(expectedPiece.GetBody() == result.GetBody());
			Assert::IsTrue(expectedPiece.GetColor() == result.GetColor());
			Assert::IsTrue(expectedPiece.GetHeight() == result.GetHeight());
			Assert::IsTrue(expectedPiece.GetShape() == result.GetShape());
		}
	};
}