#include "Qlearner.h"
#include <iostream>
#include "assert.h"
using namespace std;


namespace rlearning
{
    void Qlearner::SetReward(
            shared_ptr<State> curState, shared_ptr<Action> curAction,
            shared_ptr<State> nextState, shared_ptr<Action>, double reward)
    {
        unsigned int curStateIndex = curState->GetIndex();
        unsigned int curActionIndex = 0;

        while (curState->ActionList()[curActionIndex]->GetIndex()!=curAction->GetIndex())
            curActionIndex++;
        assert(curActionIndex<Q[curStateIndex].size());

        double nextQ = 0;
        if (nextState)
        {
            unsigned int nextStateIndex = nextState->GetIndex();
            if (Q[nextStateIndex].size()==0)
            {
                nextQ = 0;
            }
            else
            {
                nextQ = Q[nextStateIndex][0];
                for (unsigned int nextActionIndex = 1; nextActionIndex<Q[nextStateIndex].size(); nextActionIndex++)
                {
                    if (nextQ<Q[nextStateIndex][nextActionIndex])
                        nextQ = Q[nextStateIndex][nextActionIndex];
                }
            }
        }

        double curQ = Q[curStateIndex][curActionIndex];
        Q[curStateIndex][curActionIndex] += alpha*(reward + gamma*nextQ - curQ);
    }
}

