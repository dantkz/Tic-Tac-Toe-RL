#define BOOST_TEST_MODULE MainTest
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <memory>

#include "Action.h"
#include "Agent.h"
#include "Environment.h"
#include "State.h"

#include "Game.h"
#include "Board.h"
#include "Human.h"
#include "Move.h"
#include "TicTacToe.h"

#include "Egreedy.h"
#include "Sarsa.h"
#include "Qlearner.h"

using namespace std;
using namespace rlearning;

//------------------

BOOST_AUTO_TEST_SUITE(TestBoard)

BOOST_AUTO_TEST_CASE(TestBoardCase_Constructors)
{
  shared_ptr<Board> board(new Board());
  shared_ptr<Board> board_other(new Board());
  shared_ptr<Board> board_copy(new Board(board));

  BOOST_CHECK_NE(board, board_other);
  BOOST_CHECK_NE(board, board_copy);
  BOOST_CHECK_EQUAL(board->GetString(), board_copy->GetString());
}

BOOST_AUTO_TEST_CASE(TestBoardCase_MakeMove_GetIndex)
{
  shared_ptr<Board> board(new Board());
  shared_ptr<Board> board_copy(new Board(board));

  BOOST_CHECK_EQUAL(board->GetIndex(), board_copy->GetIndex());
  board_copy->MakeMove(dynamic_pointer_cast<Move>(board_copy->ActionList()[0]));
  BOOST_CHECK_NE(board->GetIndex(), board_copy->GetIndex());
}

BOOST_AUTO_TEST_CASE(TestBoardCase_MakeMove_ActionList_Move)
{
  shared_ptr<Board> board(new Board());
  shared_ptr<Board> board_copy(new Board(board));


  board_copy->MakeMove(dynamic_pointer_cast<Move>(board_copy->ActionList()[0]));
  BOOST_CHECK_NE(board->GetString(), board_copy->GetString());
  BOOST_CHECK_EQUAL(board->ActionList().size()-1, board_copy->ActionList().size());

  shared_ptr<Move> move1 = dynamic_pointer_cast<Move>(board->ActionList()[1]);
  shared_ptr<Move> move2 = dynamic_pointer_cast<Move>(board_copy->ActionList()[0]);
  BOOST_CHECK_NE(move1->Mark, move2->Mark);
  BOOST_CHECK_EQUAL(move1->Mark, 1);
  BOOST_CHECK_EQUAL(move2->Mark, -1);
  BOOST_CHECK_EQUAL(move1->Location, move2->Location);

  board_copy->MakeMove(dynamic_pointer_cast<Move>(board_copy->ActionList()[0]));
  BOOST_CHECK_EQUAL(board_copy->ActionList()[0]->GetString(), board->ActionList()[2]->GetString());

  for (int i=0; i<9; i++)
  {
    BOOST_CHECK_EQUAL(board->ActionList().size(), 9-i);
    for (unsigned int j=0; j<board->ActionList().size(); j++)
    {
        if (i%2==0)
        {   
            BOOST_CHECK_EQUAL(dynamic_pointer_cast<Move>(board->ActionList()[j])->Mark, 1);
        } else {
            BOOST_CHECK_EQUAL(dynamic_pointer_cast<Move>(board->ActionList()[j])->Mark, -1);
        }
        int n = j+9-board->ActionList().size();
        BOOST_CHECK_EQUAL(dynamic_pointer_cast<Move>(board->ActionList()[j])->Location, n);
    }
    board->MakeMove(dynamic_pointer_cast<Move>(board->ActionList()[0]));
  }
}

BOOST_AUTO_TEST_CASE(TestBoardCase_GetRewardForIsTerminal)
{
  shared_ptr<Board> board(new Board());

  for (int i=0; i<7; i++)
  {
    BOOST_CHECK_EQUAL(board->IsTerminal, false);
    BOOST_CHECK_EQUAL(board->GetRewardFor(1), 0);
    BOOST_CHECK_EQUAL(board->GetRewardFor(-1), 0);
    board->MakeMove(dynamic_pointer_cast<Move>(board->ActionList()[0]));
  }

  // xox
  // oxo
  // x
  BOOST_CHECK_EQUAL(board->GetRewardFor(1), 1);
  BOOST_CHECK_EQUAL(board->GetRewardFor(-1), -1);

  BOOST_CHECK_EQUAL(board->IsTerminal, true);
}

BOOST_AUTO_TEST_CASE(TestBoardCase_GetRewardForIsTerminal2)
{
  shared_ptr<Board> board(new Board());

  for (int i=0; i<3; i++)
  {
    BOOST_CHECK_EQUAL(board->IsTerminal, false);
    BOOST_CHECK_EQUAL(board->GetRewardFor(1), 0);
    BOOST_CHECK_EQUAL(board->GetRewardFor(-1), 0);
    board->MakeMove(dynamic_pointer_cast<Move>(board->ActionList()[0]));
  }
  // xox
  //
  //
  for (int i=0; i<3; i++)
  {
    BOOST_CHECK_EQUAL(board->IsTerminal, false);
    BOOST_CHECK_EQUAL(board->GetRewardFor(1), 0);
    BOOST_CHECK_EQUAL(board->GetRewardFor(-1), 0);
    board->MakeMove(dynamic_pointer_cast<Move>(board->ActionList()[3]));
  }
  // xox
  //
  // oxo
  
  for (int i=0; i<3; i++)
  {
    BOOST_CHECK_EQUAL(board->IsTerminal, false);
    BOOST_CHECK_EQUAL(board->GetRewardFor(1), 0);
    BOOST_CHECK_EQUAL(board->GetRewardFor(-1), 0);
    board->MakeMove(dynamic_pointer_cast<Move>(board->ActionList()[0]));
  }
  // xox
  // xox
  // oxo
  
  BOOST_CHECK_EQUAL(board->GetRewardFor(1), 0);
  BOOST_CHECK_EQUAL(board->GetRewardFor(-1), 0);
  BOOST_CHECK_EQUAL(board->IsTerminal, true);
}

BOOST_AUTO_TEST_SUITE_END()
    
//------------------

BOOST_AUTO_TEST_SUITE(TestTicTacToe)

BOOST_AUTO_TEST_CASE(TestTicTacToe_Episode)
{
    TicTacToe game;
    shared_ptr<Agent> agent0(new Sarsa());
    shared_ptr<Agent> agent1(new Qlearner());
    game.AddAgent(0, agent0);
    game.AddAgent(1, agent1);

    Game episode = game.MakeEpisode();
    
    BOOST_CHECK_EQUAL(episode.AgentIds.size(), episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Moves.size()   , episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Marks.size()   , episode.Boards.size());

    for (unsigned int i=0; i<episode.Boards.size()-1; i++)
    {
        if (i%2==0)
            BOOST_CHECK_EQUAL(episode.Marks[i], 1);
        else
            BOOST_CHECK_EQUAL(episode.Marks[i], -1);
        
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(1), 0);
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(-1), 0);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//------------------

BOOST_AUTO_TEST_SUITE(TestSarsa)

BOOST_AUTO_TEST_CASE(TestSarsa_MakeEpisode)
{
    TicTacToe game;
    shared_ptr<Agent> agent0(new Sarsa());
    shared_ptr<Agent> agent1(new Sarsa());
    game.AddAgent(0, agent0);
    game.AddAgent(1, agent1);

    Game episode = game.MakeEpisode();
    
    BOOST_CHECK_EQUAL(episode.AgentIds.size(), episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Moves.size()   , episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Marks.size()   , episode.Boards.size());

    for (unsigned int i=0; i<episode.Boards.size()-1; i++)
    {
        if (i%2==0)
            BOOST_CHECK_EQUAL(episode.Marks[i], 1);
        else
            BOOST_CHECK_EQUAL(episode.Marks[i], -1);
        
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(1), 0);
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(-1), 0);
    }
}

BOOST_AUTO_TEST_CASE(TestSarsa_TrainEpisode)
{
    TicTacToe game;
    shared_ptr<Agent> agent0(new Sarsa());
    shared_ptr<Agent> agent1(new Sarsa());
    game.AddAgent(0, agent0);
    game.AddAgent(1, agent1);

    for (int i=0; i<10; i++)
    {
        Game episode = game.MakeEpisode();
        game.TrainFrom(episode);    
        BOOST_CHECK_EQUAL(episode.Marks[0], 1);
        BOOST_CHECK_EQUAL(episode.AgentIds[0], 0);
        BOOST_CHECK_EQUAL(episode.Marks[1], -1);
        BOOST_CHECK_EQUAL(episode.AgentIds[1], 1);
    }

    game.ClearAgents();
    game.AddAgent(1, agent0);
    game.AddAgent(0, agent1);
    for (int i=0; i<10; i++)
    {
        Game episode = game.MakeEpisode();
        game.TrainFrom(episode);    
        BOOST_CHECK_EQUAL(episode.Marks[0], 1);
        BOOST_CHECK_EQUAL(episode.AgentIds[0], 0);
        BOOST_CHECK_EQUAL(episode.Marks[1], -1);
        BOOST_CHECK_EQUAL(episode.AgentIds[1], 1);
    }

    
}


BOOST_AUTO_TEST_SUITE_END()
    
//------------------

BOOST_AUTO_TEST_SUITE(TestQlearner)

BOOST_AUTO_TEST_CASE(TestQlearner_MakeEpisode)
{
    TicTacToe game;
    shared_ptr<Agent> agent0(new Qlearner());
    shared_ptr<Agent> agent1(new Qlearner());
    game.AddAgent(0, agent0);
    game.AddAgent(1, agent1);

    Game episode = game.MakeEpisode();
    
    BOOST_CHECK_EQUAL(episode.AgentIds.size(), episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Moves.size()   , episode.Boards.size());
    BOOST_CHECK_EQUAL(episode.Marks.size()   , episode.Boards.size());

    for (unsigned int i=0; i<episode.Boards.size()-1; i++)
    {
        if (i%2==0)
            BOOST_CHECK_EQUAL(episode.Marks[i], 1);
        else
            BOOST_CHECK_EQUAL(episode.Marks[i], -1);
        
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(1), 0);
        BOOST_CHECK_EQUAL(episode.Boards[i]->GetRewardFor(-1), 0);
    }
}

BOOST_AUTO_TEST_CASE(TestQlearner_TrainEpisode)
{
    TicTacToe game;
    shared_ptr<Agent> agent0(new Qlearner());
    shared_ptr<Agent> agent1(new Qlearner());
    game.AddAgent(0, agent0);
    game.AddAgent(1, agent1);

    for (int i=0; i<10; i++)
    {
        Game episode = game.MakeEpisode();
        game.TrainFrom(episode);    
        BOOST_CHECK_EQUAL(episode.Marks[0], 1);
        BOOST_CHECK_EQUAL(episode.AgentIds[0], 0);
        BOOST_CHECK_EQUAL(episode.Marks[1], -1);
        BOOST_CHECK_EQUAL(episode.AgentIds[1], 1);
        
    }

    game.ClearAgents();
    game.AddAgent(1, agent0);
    game.AddAgent(0, agent1);
    for (int i=0; i<10; i++)
    {
        Game episode = game.MakeEpisode();
        game.TrainFrom(episode);    
        BOOST_CHECK_EQUAL(episode.Marks[0], 1);
        BOOST_CHECK_EQUAL(episode.AgentIds[0], 0);
        BOOST_CHECK_EQUAL(episode.Marks[1], -1);
        BOOST_CHECK_EQUAL(episode.AgentIds[1], 1);
    }

}


BOOST_AUTO_TEST_SUITE_END()

//------------------

BOOST_AUTO_TEST_SUITE(TestSerialization)

BOOST_AUTO_TEST_CASE(TestSerializationEgreedy)
{
    TicTacToe game;
    shared_ptr<Egreedy> sarsa(new Qlearner());
    shared_ptr<Egreedy> qlearner(new Sarsa());
    game.AddAgent(0, sarsa);
    game.AddAgent(1, qlearner);

    for (int i=0; i<10; i++)
    {
        Game episode = game.MakeEpisode(i%2);
        game.TrainFrom(episode);    
    }

    string sarsaFilename = "tmp.txt";
    sarsa->Save(sarsaFilename);
    shared_ptr<Egreedy> nsarsa(new Sarsa());
    nsarsa->epsilon = sarsa->epsilon+0.1;
    BOOST_CHECK_NE(sarsa->Q.size(), nsarsa->Q.size());
    BOOST_CHECK_NE(sarsa->epsilon, nsarsa->epsilon);
    BOOST_CHECK_NE(sarsa, nsarsa);
    nsarsa->Load(sarsaFilename);
    BOOST_CHECK_NE(sarsa, nsarsa);
    BOOST_CHECK_EQUAL(sarsa->epsilon, nsarsa->epsilon);
    BOOST_CHECK_EQUAL(sarsa->Q.size(), nsarsa->Q.size());

    for (std::map<unsigned int,std::vector<double>>::iterator map_it=sarsa->Q.begin();
        map_it!=sarsa->Q.end(); ++map_it)
        {
            BOOST_CHECK_EQUAL(map_it->second.size(), nsarsa->Q[map_it->first].size());
            for (unsigned int i=0; i<map_it->second.size(); i++)
            {
                BOOST_CHECK_EQUAL(map_it->second[i], nsarsa->Q[map_it->first][i]);
            }
        }


    string qlearnerFilename = "tmp.txt";
    qlearner->Save(qlearnerFilename);
    shared_ptr<Egreedy> nqlearner(new Qlearner());
    nqlearner->epsilon = qlearner->epsilon+0.1;
    BOOST_CHECK_NE(qlearner->Q.size(), nqlearner->Q.size());
    BOOST_CHECK_NE(qlearner->epsilon, nqlearner->epsilon);
    BOOST_CHECK_NE(qlearner, nqlearner);
    nqlearner->Load(qlearnerFilename);
    BOOST_CHECK_NE(qlearner, nqlearner);
    BOOST_CHECK_EQUAL(qlearner->epsilon, nqlearner->epsilon);
    BOOST_CHECK_EQUAL(qlearner->Q.size(), nqlearner->Q.size());

    for (std::map<unsigned int,std::vector<double>>::iterator map_it=qlearner->Q.begin();
        map_it!=qlearner->Q.end(); ++map_it)
        {
            BOOST_CHECK_EQUAL(map_it->second.size(), nqlearner->Q[map_it->first].size());
            for (unsigned int i=0; i<map_it->second.size(); i++)
            {
                BOOST_CHECK_EQUAL(map_it->second[i], nqlearner->Q[map_it->first][i]);
            }
        }
    

}
BOOST_AUTO_TEST_SUITE_END()
    
//------------------
