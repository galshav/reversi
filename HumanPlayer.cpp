/*
 * HumanPlayer.cpp
 *
 *  Created on: Oct 27, 2017
 *      Author: gal
 */

#pragma once
#include <iostream>
#include <vector>
#include "HumanPlayer.hpp"
#include "Board.hpp"
#include "Validator.hpp"

/*
 * Default Constructor.
 */
HumanPlayer::HumanPlayer() :
	m_Symbol(Empty),
	m_Score(2)
{
}

/*
 * Basic constructor.
 */
HumanPlayer::HumanPlayer(const CellState & i_Symbol) :
		m_Symbol(i_Symbol),
		m_Score(2)
{
}

/*
 * Destructor.
 */
HumanPlayer::~HumanPlayer()
{
}

/*
 * Play one turn on a given board.
 * @param i_Board - Board to play on.
 * @return false if no moves allowed, true otherwise.
 */
bool HumanPlayer::Play(Board & i_Board)
{
	// Checks what are the possible moves.
	std::vector<std::pair<std::size_t, std::size_t>> possibleMoves = Validator::GetPossibleMoves(i_Board, m_Symbol);

	// Print possible moves to the screen.
	if (Red == m_Symbol)
	{
		std::cout << "Current user: X" << std::endl;
	}

	else
	{
		std::cout << "Current user: O" << std::endl;
	}

	std::cout << "Possible moves:" << std::endl;
	if (0 != possibleMoves.size())
	{
		for (std::pair<std::size_t, std::size_t> & move : possibleMoves)
		{
			std::cout << move.first << "," << move.second << std::endl;
		}
	}

	else
	{
		std::cout << "No possible moves." << std::endl;
		return false;
	}

	// Choose one of the possible moves.
	std::size_t row;
	std::size_t column;
	std::cin >> row >> column;

	// Set the game board according to the last selection.
	i_Board.SetCell(row, column, m_Symbol);

	// Flip opponent cells.
	Validator::FlipOpponentCells(row, column, i_Board, m_Symbol);

	return true;
}

/*
 * Set the human player symbol.
 * @param i_Symbol - Symbol to set.
 */
void HumanPlayer::SetSymbol(const CellState & i_Symbol)
{
	m_Symbol = i_Symbol;
}

/*
 * Get player symbol.
 * @return player symbol.
 */
CellState HumanPlayer::GetSymbol() const
{
	return m_Symbol;
}

/*
 * Set player score.
 * @param i_Score - Score to set.
 */
void HumanPlayer::SetScore(const std::size_t & i_Score)
{
	m_Score = i_Score;
}
