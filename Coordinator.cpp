/*
 * Coordinator.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: gal
 */


#include "Coordinator.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"
#include <exception>
#include <iostream>

/*
 * Default constructor.
 */
Coordinator::Coordinator() :
	m_FirstPlayer(nullptr),
	m_SecondPlayer(nullptr),
	m_Board(8)
{
}

/*
 * Destructor.
 * Used to free allocated resources.
 */
Coordinator::~Coordinator()
{
	delete(m_FirstPlayer);
	delete(m_SecondPlayer);
}

/*
 * Run the main game loop.
 */
void Coordinator::Run()
{
	// Choose game mode.
	unsigned int gameMode;
	std::cout << "Game mode: 0 - Human vs Human | 1 - Human vs Computer" << std::endl;
	std::cin >> gameMode;

	// Set Players.
	if (0 == gameMode)
	{
		m_FirstPlayer = new HumanPlayer();
		m_FirstPlayer->SetSymbol(Red);
		m_SecondPlayer = new HumanPlayer();
		m_SecondPlayer->SetSymbol(Black);
	}

	else if (1 == gameMode)
	{
		m_FirstPlayer = new HumanPlayer();
		m_FirstPlayer->SetSymbol(Red);
		m_SecondPlayer = new ComputerPlayer();
		m_SecondPlayer->SetSymbol(Black);
	}

	// Quit if incorrect mode applied.
	else
	{
		throw std::exception();
	}

	m_Board.Print();
	while (true)
	{
		// First player iteration.
		bool firstPlayerPlayed = m_FirstPlayer->Play(m_Board);
		std::size_t firstScore = m_Board.CalculatePlayerScore(m_FirstPlayer->GetSymbol());
		m_FirstPlayer->SetScore(firstScore);
		std::size_t secondScore = m_Board.CalculatePlayerScore(m_SecondPlayer->GetSymbol());
		m_SecondPlayer->SetScore(secondScore);
		m_Board.Print();
		bool gameOver = IsGameOver(m_Board, m_FirstPlayer->GetSymbol());
		if (true == gameOver)
		{
			std::cout << "First player won!" << std::endl;
			return;
		}

		// Second player iteration.
		bool secondPlayerPlayed = m_SecondPlayer->Play(m_Board);
		firstScore = m_Board.CalculatePlayerScore(m_FirstPlayer->GetSymbol());
		m_FirstPlayer->SetScore(firstScore);
		secondScore = m_Board.CalculatePlayerScore(m_SecondPlayer->GetSymbol());
		m_SecondPlayer->SetScore(secondScore);
		m_Board.Print();
		gameOver = IsGameOver(m_Board, m_SecondPlayer->GetSymbol());
		if (true == gameOver)
		{
			std::cout << "Second player won!" << std::endl;
			return;
		}

		// Checks if no more moves are allowed for both players.
		if (false == firstPlayerPlayed && false == secondPlayerPlayed)
		{
			if (firstScore > secondScore)
			{
				std::cout << "First player won." << std::endl;
			}

			else if (secondScore > firstScore)
			{
				std::cout << "Second player won." << std::endl;
			}

			else
			{
				std::cout << "It's a tie." << std::endl;
			}

			return;
		}
	}
}

bool Coordinator::IsGameOver(const Board & i_Board, const CellState & i_Symbol) const
{
	std::size_t boardSize = i_Board.GetBoardSize();

	for (size_t i = 0; i < boardSize; ++i)
	{
		for (size_t j = 0 ; j < boardSize; ++j)
		{
			if (i_Symbol == i_Board[i * boardSize + j] ||
				Empty == i_Board[i * boardSize + j])
			{
				continue;
			}

			else
			{
				// Opponent cells on the board.
				return false;
			}
		}
	}

	// All cells are filled with same player's color.
	return true;
}
