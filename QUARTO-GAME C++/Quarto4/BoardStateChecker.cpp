#include "BoardStateChecker.h"
#include <functional>
#include <numeric>


using quarto::BoardStateChecker;

BoardStateChecker::State BoardStateChecker::Check(const Board& board, const Board::Position& position)
{
	throw std::exception{ "BoardStateChecker::Check() is not implemented!" };
}