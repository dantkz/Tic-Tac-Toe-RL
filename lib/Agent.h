//
// Abstract class for Agent that can interact with Environment
//
#ifndef AGENT_H 
#define AGENT_H

#include "State.h"
#include "Action.h"

#include <memory>
#include <vector>

namespace rlearning
{
    class Agent{
        public:
            virtual ~Agent(){};

            // Chooses an Action given the State. Uses ActionList() of the State to choose valid Action.
            virtual std::shared_ptr<Action> GetAction(std::shared_ptr<State>) = 0;

            // Learns from observing reward from State and Action from that State.
            virtual void SetReward(std::shared_ptr<State>, std::shared_ptr<Action>, double) = 0;

            // Learns from observing  State s, Action a from s to State s' and next 
            // Action a' and Reward given when taking Action a.
            virtual void SetReward( std::shared_ptr<State>, std::shared_ptr<Action>,
                                    std::shared_ptr<State>, std::shared_ptr<Action>, 
                                    double) = 0;
    };
}

#endif
