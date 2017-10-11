#include "TicTacToe.h"
#include "assert.h"
#include "Board.h"

#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

namespace rlearning
{
    void TicTacToe::SaveLog(string filename)
    {
        ofstream outfs(filename.c_str());
        {
            for (unsigned int i=0; i<this->rewards.size(); i++)
            {
                outfs << i << ", ";
                outfs <<  get<0>(this->rewards[i]) << ", ";
                outfs <<  get<1>(this->rewards[i]) << ", ";
                outfs <<  get<2>(this->rewards[i]) << ", ";
                outfs <<  get<3>(this->rewards[i]) << ", ";
                outfs <<  get<4>(this->rewards[i]) << ", ";
                outfs <<  get<5>(this->rewards[i]) << endl;
            }
        }
    }

    void TicTacToe::AddToLog(Game episode)
    {
        //agents[0] starts with
        int agent0Mark = 1;
        int agent1Mark = -1;
        if (episode.AgentIds[0]==1)
        {
            agent0Mark = -1;
            agent1Mark = 1;
        }
        double agent0reward = episode.Boards[episode.Boards.size()-1]->GetRewardFor(agent0Mark);
        double agent1reward = episode.Boards[episode.Boards.size()-1]->GetRewardFor(agent1Mark);
        
        this->rewards.push_back(make_tuple(0, agent0Mark, agent0reward, 1, agent1Mark, agent1reward));
    }

    void TicTacToe::AddAgent(unsigned int i, shared_ptr<Agent> agent)
    {
        agents[i%2]=agent;
    }

    void TicTacToe::ClearAgents()
    {
        agents.clear();
        agents.resize(2);
    }

    void TicTacToe::TrainFrom(Game episode)
    {
        assert(episode.AgentIds.size()==episode.Boards.size());
        assert(episode.Moves.size()==episode.Boards.size());
        assert(episode.Marks.size()==episode.Boards.size());
        
        for (unsigned int i=0; i<episode.Boards.size()-1; i++)
        {
            shared_ptr<Agent> agent = agents[episode.AgentIds[i]];
            shared_ptr<State> curState = episode.Boards[i];
            shared_ptr<Action> curAction = episode.Moves[i];

            unsigned int nexti = i+2;
            shared_ptr<State> nextState;
            shared_ptr<Action> nextAction;
            double reward = 0;
            if (nexti<episode.Boards.size())
            {
                nextState = episode.Boards[nexti];
                nextAction = episode.Moves[nexti];
                reward = episode.Boards[nexti]->GetRewardFor(episode.Marks[i]);
            }
            else
            {
                nextState = nullptr;
                nextAction = nullptr;
                reward = episode.Boards[episode.Boards.size()-1]->GetRewardFor(episode.Marks[i]);
            }
    
            //Not applicable: //agent->SetReward(curState, curAction, reward);
            agent->SetReward(curState, curAction, nextState, nextAction, reward);
        }
    }

    // One could combine MakeEpisode and TrainFrom into one method.
    // The feature is to generate episode and give rewards as the episode progresses 
    // through the agent's actions. This enables agent's adaptation to the environment 
    // without the necessity to wait for the episode to finish.
    // However, the game of TicTacToe is guaranteed to finish after at most 9 moves.
    // So, for readability and better code please use the MakeEpisode() method that 
    // generates the episode, and then use TrainFrom() method to provide states to the 
    // agents for training.
    Game TicTacToe::MakeEpisode(unsigned int currentAgentId)
    {
        Game episode;
        int currentMark = 1; //start with 'x'

        shared_ptr<Board> currentBoard(new Board());
        while(!currentBoard->IsTerminal)
        {
            episode.Boards.push_back(currentBoard);
            episode.AgentIds.push_back(currentAgentId);
            episode.Marks.push_back(currentMark);

            shared_ptr<Move> currentAction = dynamic_pointer_cast<Move>(agents[currentAgentId]->GetAction(dynamic_pointer_cast<State>(currentBoard)));

            episode.Moves.push_back(currentAction);
           
            //Do the action
            currentBoard = shared_ptr<Board>(new Board(currentBoard));
            currentBoard->MakeMove(currentAction);
            
            //Next Move
            currentAgentId= (currentAgentId+1)%2;
            currentMark = (-1)*currentMark;
        }
        episode.Boards.push_back(currentBoard);
        episode.AgentIds.push_back(currentAgentId);
        episode.Marks.push_back(currentMark);
        episode.Moves.push_back(nullptr);

        assert(episode.AgentIds.size()==episode.Boards.size());
        assert(episode.Moves.size()==episode.Boards.size());
        assert(episode.Marks.size()==episode.Boards.size());
        return episode;
    }
}
