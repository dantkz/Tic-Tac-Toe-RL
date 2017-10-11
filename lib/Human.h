//
// Implementation of the agent that makes decisions based on Human input.
//
#ifndef HUMAN_H 
#define HUMAN_H

#include "Agent.h"
#include "Action.h"
#include "State.h"
#include <memory>

namespace rlearning
{
    class Human : public Agent{
        public:
            Human(){};
            ~Human(){};

            std::shared_ptr<Action> GetAction(std::shared_ptr<State>);

            void SetReward(std::shared_ptr<State>, std::shared_ptr<Action>, double);
            void SetReward( std::shared_ptr<State>, std::shared_ptr<Action>,
                            std::shared_ptr<State>, std::shared_ptr<Action>, 
                            double);
    };
}

#endif
