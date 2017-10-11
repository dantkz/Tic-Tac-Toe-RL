//
// Implementation of TicTacToe game as Environment for two Agents.
//
#ifndef TICTACTOE_H 
#define TICTACTOE_H

#include "Environment.h"
#include "Agent.h"
#include "Board.h"
#include "Move.h"
#include "Game.h"

#include <vector>
#include <tuple>
#include <string>
#include <memory>

namespace rlearning
{
    class TicTacToe : public Environment {

        public:
            TicTacToe(){agents.resize(2);};
            ~TicTacToe(){};

            // Add agents. There must be 2 agents.
            void AddAgent(unsigned int i, std::shared_ptr<Agent>);
            void ClearAgents();

            // Ask agents for moves and generate an episode.
            // currentAgentId starts with 'x' move
            Game MakeEpisode(unsigned int currentAgentId = 0);

            // Give States, Actions and Rewards to Agents using Episode
            void TrainFrom(Game);

            // Logs for storing rewards of the agents for each Episode. 
            // See rewards vector below.
            void SaveLog(std::string);
            void AddToLog(Game);
        private:
            std::vector<std::shared_ptr<Agent> > agents;

            // The tuple stores:
            // 0
            // Mark of agents[0]: -1 for 'o' and 1 for 'x' 
            // Reward of agents[0]
            // 1
            // Mark of agents[1]: -1 for 'o' and 1 for 'x' 
            // Reward of agents[1]
            std::vector< std::tuple<unsigned int, int, double, unsigned int, int, double> > rewards;
    };
}

#endif
