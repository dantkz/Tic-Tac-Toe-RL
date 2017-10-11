//
// Abstract class for Environment.
//
#ifndef ENVIRONMENT_H 
#define ENVIRONMENT_H

#include "State.h"
#include "Action.h"
#include "Agent.h"
#include <memory>


namespace rlearning
{
    class Environment{
        public:
            virtual ~Environment(){};
            virtual void AddAgent(unsigned int i, std::shared_ptr<Agent>) = 0;
            virtual void ClearAgents() = 0;
    };
}

#endif
