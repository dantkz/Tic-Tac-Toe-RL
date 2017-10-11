//
// Implementation of epsilon-greedy policy agent.
//

#ifndef EGREEDY_H 
#define EGREEDY_H

#include "State.h"
#include "Action.h"
#include "Agent.h"

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <fstream>

namespace rlearning
{
    class Egreedy : public Agent {
        public:
            Egreedy(){
                epsilon = 0.1;
            };

            // Returns epsilon-greedy choice
            std::shared_ptr<Action> GetAction(std::shared_ptr<State>);

            // Probability of random move for exploration.
            double epsilon;

            // Serialization
            void Save(std::string);
            void Load(std::string);

            // Stores action-values. The key is State->GetIndex().
            // The each entry in the vector stores the value of the Action
            // at corresponding index in State->ActionList().
            std::map<unsigned int, std::vector<double> > Q;

            // This agent doesn't learn
            void SetReward(std::shared_ptr<State>, std::shared_ptr<Action>, double) {};
            void SetReward( std::shared_ptr<State>, std::shared_ptr<Action>,
                                    std::shared_ptr<State>, std::shared_ptr<Action>, 
                                    double) {};
    };
}

#endif
