// 
// Implementation of Moves for the game of TicTacToe.
//
#ifndef MOVE_H 
#define MOVE_H
#include <string>
#include "Action.h"


namespace rlearning
{
    class Move : public Action {
        public:
            Move(){};
            ~Move(){};
            std::string GetString();
            unsigned int GetIndex();

            // What is the mark for the current move?
            int Mark;

            // Where does this mark go?
            // This is left intentionally as int, and not unsigned int.
            // I have discovered a truly marvellous reason of this, 
            // which this comment is too narrow to contain.
            int Location;

    };
}

#endif
