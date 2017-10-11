//
// Container for the sequences of boards and moves of TicTacToe game.
//
#ifndef GAME_H 
#define GAME_H

#include "Environment.h"
#include "Agent.h"
#include "Board.h"
#include "Move.h"
#include <vector>
#include <memory>

namespace rlearning
{
    class Game { 
        public:
            std::vector<std::shared_ptr<Board> > Boards;
            std::vector<std::shared_ptr<Move> > Moves;
            std::vector<unsigned int> AgentIds;
            std::vector<int> Marks;
    };
}

#endif
