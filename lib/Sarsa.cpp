#include "Sarsa.h"
#include <iostream>
#include "assert.h"
using namespace std;


namespace rlearning
{
    void Sarsa::SetReward(
            shared_ptr<State> curState, shared_ptr<Action> curAction,
            shared_ptr<State> nextState, shared_ptr<Action> nextAction, double reward)
    {
        unsigned int curStateIndex = curState->GetIndex();
        unsigned int curActionIndex = 0;

        while (curState->ActionList()[curActionIndex]->GetIndex()!=curAction->GetIndex())
            curActionIndex++;
        assert(curActionIndex<Q[curStateIndex].size());

        double nextQ = 0;
        if (nextState && nextAction)
        {
            unsigned int nextStateIndex = nextState->GetIndex();
            unsigned int nextActionIndex = 0;
            while (nextState->ActionList()[nextActionIndex]->GetIndex()!=nextAction->GetIndex())
                nextActionIndex++;
            assert(nextActionIndex<Q[nextStateIndex].size());
            nextQ = Q[nextStateIndex][nextActionIndex];
        }

        double curQ = Q[curStateIndex][curActionIndex];
        Q[curStateIndex][curActionIndex] += alpha*(reward + gamma*nextQ - curQ);
    }
}

