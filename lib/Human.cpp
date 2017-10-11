#include "Human.h"
#include <iostream>
#include "assert.h"
using namespace std;


namespace rlearning
{

    shared_ptr<Action> Human::GetAction(shared_ptr<State> currentState)
    {
        assert(currentState->ActionList().size()>0);

        int decision = -1;
        while (!(decision<currentState->ActionList().size() && decision>=0))
        {
            cout << "Current state: " << endl;
            cout << currentState->GetString();
            
            for (unsigned int i=0; i<currentState->ActionList().size(); i++)
            {
                cout << "Action number: " << i << ". ";
                cout << currentState->ActionList()[i]->GetString();
            }
            
            cout << "Please choose action number ";
            cin >> decision;
        }

        return currentState->ActionList()[decision];
    }

    void Human::SetReward(shared_ptr<State> curState, shared_ptr<Action> curAction, double reward)
    {
        cout << "Reward: " << reward << endl;
    }

    void Human::SetReward(
            shared_ptr<State> curState, shared_ptr<Action> curAction,
            shared_ptr<State> nextState, shared_ptr<Action> nextAction, double reward)
    {
        cout << "Reward: " << reward << endl;
    }
}

