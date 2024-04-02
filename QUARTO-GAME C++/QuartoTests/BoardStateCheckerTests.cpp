#include "stdafx.h"
#include "CppUnitTest.h"

#include "BoardStateChecker.h"

using namespace quarto;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
    template<>
    inline std::wstring ToString<BoardStateChecker::State>(const BoardStateChecker::State& state)
    {
        switch (state)
        {
        case BoardStateChecker::State::None:
            return L"None";
        case BoardStateChecker::State::Win:
            return L"Win";
        case BoardStateChecker::State::Draw:
            return L"Draw";
        default:
            return L"";
        }
    }
}

namespace QuartoTests
{
    TEST_CLASS(BoardStateCheckerTests)
    {
    public:
        using enum Piece::Body;
        using enum Piece::Color;
        using enum Piece::Height;
        using enum Piece::Shape;

        using State = BoardStateChecker::State;

        TEST_METHOD(Draw)
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
            Board::Position lastPosition{ 3, 3 };
            board[lastPosition] = Piece{ Full, Light, Short, Square };

            State expectedState{ State::Draw };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(NoneOnePiece)
        {
            Board board;
            Board::Position lastPosition{ 2, 1 };
            board[lastPosition] = Piece{ Full, Dark, Short, Round };

            State expectedState{ State::None };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(NoneLineOne)
        {
            Board board;
            board[{0, 0}] = Piece{ Full, Dark, Short, Round };
            board[{0, 1}] = Piece{ Hollow, Dark, Short, Round };
            Board::Position lastPosition{ 0, 2 };
            board[lastPosition] = Piece{ Hollow, Dark, Short, Square };

            State expectedState{ State::None };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(WinLineOne)
        {
            Board board;
            board[{0, 0}] = Piece{ Full, Dark, Short, Round };
            board[{0, 1}] = Piece{ Hollow, Dark, Short, Round };
            board[{0, 2}] = Piece{ Full, Dark, Tall, Square };
            Board::Position lastPosition{ 0, 3 };
            board[lastPosition] = Piece{ Hollow, Dark, Short, Square };

            State expectedState{ State::Win };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(WinColumnThree)
        {
            Board board;
            board[{0, 2}] = Piece{ Full, Dark, Short, Round };
            board[{1, 2}] = Piece{ Hollow, Dark, Short, Round };
            board[{2, 2}] = Piece{ Full, Dark, Tall, Square };
            Board::Position lastPosition{ 3, 2 };
            board[lastPosition] = Piece{ Hollow, Dark, Short, Square };

            State expectedState{ State::Win };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(WinMainDiagonal)
        {
            Board board;
            board[{0, 0}] = Piece{ Full, Dark, Short, Round };
            board[{1, 1}] = Piece{ Hollow, Dark, Short, Round };
            board[{2, 2}] = Piece{ Full, Dark, Tall, Square };
            Board::Position lastPosition{ 3, 3 };
            board[lastPosition] = Piece{ Hollow, Dark, Short, Square };

            State expectedState{ State::Win };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }

        TEST_METHOD(WinSecondaryDiagonal)
        {
            Board board;
            board[{0, 3}] = Piece{ Full, Dark, Short, Round };
            board[{1, 2}] = Piece{ Hollow, Dark, Short, Round };
            board[{2, 1}] = Piece{ Full, Dark, Tall, Square };
            Board::Position lastPosition{ 3, 0 };
            board[lastPosition] = Piece{ Hollow, Dark, Short, Square };

            State expectedState{ State::Win };

            State result{ BoardStateChecker::Check(board, lastPosition) };

            Assert::AreEqual(expectedState, result);
        }
    };
}