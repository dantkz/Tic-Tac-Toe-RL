#include <iostream>
#include "TicTacToe.h"
#include "Human.h"
#include "Sarsa.h"
#include "Qlearner.h"
#include "Game.h"

#include <boost/filesystem.hpp>

using namespace rlearning;
using namespace std;

int main(int argc,  char* argv[])
{
    if (argc!=2)
    {
        cout << "Usage: Play.exe [model]" << endl;
        cout << "[model] = path to file with the saved model. You can use: 'output/sarsa.txt' or 'output/qlearning.txt'" << endl;
        return 0;
    }

    string agentFilename = argv[1];
    if (!boost::filesystem::exists(agentFilename))
    {
        cout << "File not found." << endl;
        return 0;
    }

    TicTacToe game;
    shared_ptr<Egreedy> agent(new Sarsa()); 
    agent->Load(agentFilename);
    agent->epsilon = 0;

    shared_ptr<Agent> human(new Human());

    game.AddAgent(0, agent);
    game.AddAgent(1, human);

    char input;
    bool isPlaying = true;
    while (isPlaying)
    {
        int humanStarts = 0;
        cout << "Do you want to go first? (y/N)" << endl;
        cin >> input;
        if (input=='y' || input=='Y')
            humanStarts = 1;

        //Play the game
        Game episode = game.MakeEpisode(humanStarts);

        cout << episode.Boards[episode.Boards.size()-1]->GetString();

        cout << "x player got: " << to_string((long long)episode.Boards[episode.Boards.size()-1]->GetRewardFor(1)) << endl;
        cout << "o player got: " << to_string((long long)episode.Boards[episode.Boards.size()-1]->GetRewardFor(-1)) << endl;

        //Ask to exit the game
        cout << "Finish playing? (y/N)" << endl;
        cin >> input;
        if (input=='y' || input=='Y')
            isPlaying = false;
    }

	return 0;
}
