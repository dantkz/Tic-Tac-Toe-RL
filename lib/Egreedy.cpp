#include "Egreedy.h"
#include <iostream>
#include "assert.h"
#include <memory>
#include <stdlib.h>
#include <vector>
#include <string>

#include <time.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;


namespace rlearning
{
    void Egreedy::Load(string filename)
    {
        ifstream inpfs(filename.c_str());
        {
            boost::archive::text_iarchive inparch(inpfs);
            inparch >> epsilon;
            unsigned int qSize;
            inparch >> qSize;
            
            for (unsigned int i=0; i<qSize; i++)
            {
                unsigned int key;
                inparch >> key;
                inparch >> Q[key];
            }
        }
    } 

    void Egreedy::Save(string filename)
    {
        ofstream outfs(filename.c_str());
        {
            boost::archive::text_oarchive outarch(outfs);
            outarch << epsilon;
            unsigned int qSize = Q.size();
            outarch << qSize;

            for (std::map<unsigned int,std::vector<double> >::iterator map_it=Q.begin();
                    map_it!=Q.end(); ++map_it)
            {
                outarch << map_it->first;
                outarch & (map_it->second);
            }


        }
    } 

    shared_ptr<Action> Egreedy::GetAction(shared_ptr<State> currentState)
    {
        assert(currentState);
        assert(currentState->ActionList().size()>0);

        unsigned int decision = -1;

        unsigned int actionNumber = currentState->ActionList().size();
        unsigned int stateIndex = currentState->GetIndex();

        // First encounter of this state
        if (Q[stateIndex].size()==0)
        {
            if (actionNumber>0)
            {
                // Init
                for (unsigned int i=0; i<actionNumber; i++)
                {
                    Q[stateIndex].push_back(1.0/actionNumber);
                }
            }
        }
        assert(Q[stateIndex].size() == actionNumber);

        //Choose epsilon-greedy
        double r = ((double) rand() / (RAND_MAX)) + 1;
        if (r<epsilon)
        {
            decision = rand()%actionNumber;
        }
        else
        {
            // Choose max (the first encountered max)
            double maxValue = -1;
            for (unsigned int i=0; i<Q[stateIndex].size(); i++)
            {
                if (Q[stateIndex][i]>maxValue)
                {
                    decision = i;
                    maxValue = Q[stateIndex][i];
                }
            }
        }

        assert(decision>=0 && decision<actionNumber);

        return currentState->ActionList()[decision];
    }
}

