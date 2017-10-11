//
// Absract class for storing States of the Environment
//
#ifndef STATE_H 
#define STATE_H
#include <string>
#include "Action.h" 
#include <vector>
#include <memory>

namespace rlearning
{
    class State{
        public:
            virtual ~State(){};
            virtual std::string GetString() = 0;
            // Gives vector with valid actions from the current state.
            virtual std::vector<std::shared_ptr<Action> > ActionList() = 0;

            // Computes the reward of the state. 
            // State may have different reward for different agents, hence the argument
            virtual double GetRewardFor(int) = 0;

            // Computes unique identifier for the State
            //TODO: template instead of unsigned int?
            virtual unsigned int GetIndex() = 0;

            bool IsTerminal;
    };
}

#endif
