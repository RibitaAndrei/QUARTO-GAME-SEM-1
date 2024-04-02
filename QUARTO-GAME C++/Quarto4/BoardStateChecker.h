#pragma once

#include "Board.h"


namespace quarto
{
	class BoardStateChecker
    {
    public:
        enum class State : std::uint8_t
        {
            None,
            Win,
            Draw
        };

        static State Check(const Board& board, const Board::Position& position);
    };
}