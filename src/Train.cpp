#include <iostream>
#include "assert.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "TicTacToe.h"
#include "Egreedy.h"
#include "Sarsa.h"
#include "Qlearner.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
using namespace rlearning;

void PrintHelp()
{
        cout << "Usage: Train.exe [usesarsa] [useqlearner] *[number of episodes=10]" << endl;
        cout << "[usesarsa] can be 0 or 1" << endl;
        cout << "[useqlearner] can be 0 or 1" << endl;
        cout << "*[] optional" << endl;
}

int main(int argc,  char* argv[])
{
    if (argc!=4)
    {
        PrintHelp();
        return 0;
    }
    bool useSarsa = atoi(argv[1])==1;
    bool useQlearner = atoi(argv[2])==1;
    unsigned int episodeNumber = 10;
    string sarsaFilename = "sarsa.txt";
    string qlearnerFilename = "qlearner.txt";
    
    if (!useSarsa && !useQlearner)
    {
        PrintHelp();
        return 0;
    }

    if (argc>=4)
        episodeNumber = atoi(argv[3]);
    
    cout << "Episode number: " << episodeNumber << endl;

    TicTacToe game;
    shared_ptr<Egreedy> sarsa(new Sarsa());
    shared_ptr<Egreedy> qlearner(new Qlearner());

    if (useSarsa && useQlearner)
    {
        game.AddAgent(0, sarsa);
        game.AddAgent(1, qlearner);
    } 
    else if (useSarsa)
    {
        game.AddAgent(0, sarsa);
        game.AddAgent(1, sarsa);
    }
    else
    {
        game.AddAgent(0, qlearner);
        game.AddAgent(1, qlearner);
    }

    for (unsigned int i = 0; i<episodeNumber; i++)
    {
        cout << "Episode number: " << i+1 << " out of " << episodeNumber << endl;
        Game episode = game.MakeEpisode(i%2);
        game.TrainFrom(episode);
        game.AddToLog(episode);
    }
    game.SaveLog("rewards.txt");
    
    if (useSarsa)
        sarsa->Save(sarsaFilename);
    if (useQlearner)
        qlearner->Save(qlearnerFilename);

	return 0;
}
