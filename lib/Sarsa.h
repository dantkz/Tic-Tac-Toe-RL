//
// Implementation of Sarsa algorithm.
//
#ifndef SARSA_H 
#define SARSA_H

#include "State.h"
#include "Action.h"
#include "Agent.h"
#include "Egreedy.h"

#include <memory>
#include <vector>
#include <map>

namespace rlearning
{
    // The starting policy is epsilon-greedy.
    class Sarsa : public Egreedy {
        public:
            Sarsa() {
                epsilon = 0.05;
                gamma = 0.9;
                alpha = 0.1;
            };

            std::shared_ptr<Action> GetAction(std::shared_ptr<State> state) {return Egreedy::GetAction(state);};

            // Not applicable
            virtual void SetReward(std::shared_ptr<State>, std::shared_ptr<Action>, double) {};


            void SetReward(std::shared_ptr<State>, std::shared_ptr<Action>, 
                           std::shared_ptr<State>, std::shared_ptr<Action>,
                           double);

            // Reward decay.
            double gamma;
            // Step-size parameter.
            double alpha;
    };
}

#endif
