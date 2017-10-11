//
// Implementation of the board for game of TicTacToe.
//
#ifndef BOARD_H 
#define BOARD_H

#include <string>
#include "State.h"
#include "Move.h"
#include "Action.h"

namespace rlearning
{
    class Board : public State {
        public:
            Board(void);
            // Copy constructor
            Board(std::shared_ptr<Board>);
            ~Board(){};

            std::string GetString();

            // Makes the move and updates rewards accordingly.
            void MakeMove(std::shared_ptr<Move>);

            // Generates a vector of Actions that are valid (i.e. list of empty spaces)
            std::vector<std::shared_ptr<Action> > ActionList();

            double GetRewardFor(int);

            // Computes unique identifier using the combination of marks on the board
            //TODO: template instead of unsigned int?
            unsigned int GetIndex(); 

            bool IsTerminal;

        private:

            // Stores marks in vector board.
            // The empty spaces on the board are stored as 0.
            // Spaces with 'x' are stored as 1.
            // Spaces with 'o' are stored as -1.
            std::vector<int> board;

            // Constant size of 3.
            static const int Size = 3;

            // Computes winners. 
            // Returns 0 if game hasn't finished.
            // Returns -2 if draw.
            // Returns 1 or -1 if 'x' won or 'o' won, respectively
            int WhoWon(); 

            // Stores rewards for the game
            std::vector<int> rewards;

            // Stores the mark of the next move.
            int Mark;
    };
}

#endif
