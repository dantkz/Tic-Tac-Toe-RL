//
// Abstract class for Action that can be taken from a State
//
#ifndef ACTION_H 
#define ACTION_H
#include <string>

namespace rlearning
{
    class Action{
        public:
            virtual ~Action(){};
            virtual std::string GetString() = 0;

            // Computes unique identifier for the Action
            //TODO: template instead of unsigned int?
            virtual unsigned int GetIndex() = 0;
            
    };
}

#endif
