#include <string>
#include "Board.h" 
#include "Move.h" 
#include "assert.h" 
#include <iostream> 

using namespace std;

namespace rlearning
{

    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
    
    Board::Board(void) {
        IsTerminal = false;
        Mark = 1;
        board.resize(Size*Size, 0);
        rewards.resize(2, 0);
    }

    Board::Board(const shared_ptr<Board> source)
    {
        IsTerminal = (source->IsTerminal); 
        Mark = (source->Mark); 
        board = (source->board); 
        rewards = (source->rewards);
    }
    
    unsigned int Board::GetIndex()
    {
        unsigned int index = 0;
        unsigned int power = 1;
        //TODO: 
        // Can potentially overflow, if Size is big
        // Otherwise, 3^9 = 19683 < 4294967296
        for (int i=0; i<Size*Size; i++)
        {
            index += power*(board[i]+1);
            power *= 3;
        }
        return index;
    }

    double Board::GetRewardFor(int who)
    {
        assert(who==1 || who==-1);

        if (who==1) // get reward for 'x' player
            return rewards[0];
        //else get reward for 'o' player
        return rewards[1];
    }
        
    string Board::GetString()
    {
        string result = "";
        for (int i=0; i<Size; i++)
        {
            for (int j=0; j<Size; j++)
            {
                int entry = board[i*Size+j];
                if (entry==0)
                    result += "[ ]";
                else if (entry==-1)
                    result += "[o]";
                else
                    result += "[x]";
            }
            result += "\n";
        }
        //result += "Next Move by: " + to_string((long long)Mark) + "\n";
        return result;
    }

    void Board::MakeMove(shared_ptr<Move> move)
    {
        // Make the move
        int index = move->Location;
        int mark = move->Mark;

        assert(0<=index && index<Size*Size);
        assert(mark==-1 || mark==1);
        assert(board[index]==0);
        board[index] = mark; 

        Mark = (-1)*Mark;

        // Evaluate the move
        int winner = WhoWon();
        if (winner==0)
        {
            return;
        }
        else 
        {
            IsTerminal = true;
            if (winner==1) // 'x' won 
            {
                rewards[0] = 1;
                rewards[1] = -1;
            }
            else if (winner==-1) // 'o' won
            {
                rewards[0] = -1;
                rewards[1] = 1;
            } 
            else  // draw
            {
                //rewards = 0;
            }

        }
    }

    int Board::WhoWon()
    {
        int sum;
        //Check rows
        for (int i=0; i<Size; i++)
        {
            sum = 0;
            for (int j=0; j<Size; j++)
                sum += board[i*Size+j];
            if (sum==-Size || sum==Size)
                return sgn(sum);
        }
        //Check columns
        for (int j=0; j<Size; j++)
        {
            sum = 0;
            for (int i=0; i<Size; i++)
                sum += board[i*Size+j];
            if (sum==-Size || sum==Size)
                return sgn(sum);
        }
        //Check topleft-bottomright diagonal
        sum = 0;
        for (int i=0; i<Size; i++)
        {
            int j=i;
            sum += board[i*Size+j];
        }
        if (sum==-Size || sum==Size)
            return sgn(sum);
        //Check topleft-bottomright diagonal
        sum = 0;
        for (int i=0; i<Size; i++)
        {
            int j=Size-1-i;
            sum += board[i*Size+j];
        }
        if (sum==-Size || sum==Size)
            return sgn(sum);

        //Check if there are empty fields
        for (int i=0; i<Size*Size; i++)
            if (board[i]==0)
                return 0;
        
        return -2;
    }

    vector<shared_ptr<Action> > Board::ActionList()
    {
        vector<shared_ptr<Action> > result;
        for (int i=0; i<Size*Size; i++)
        {
            if (board[i]==0)
            {
                shared_ptr<Move> move(new Move());
                move->Mark = Mark;
                move->Location = i;

                result.push_back(dynamic_pointer_cast<Action>(move));
            }
        }
        return result;
    }
    
}

