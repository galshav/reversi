/*
 * Filename: ComputerPlayer.cpp
 * Purpose: Implement the computer AI.
 * Author: Gal Shav-Artza.
 * Date: 01/12/2017.
 */

#pragma once
#include <iostream>
#include "ComputerPlayer.hpp"
#include "Board.hpp"
#include "Validator.hpp"

/*
 * Basic constructor.
 */
ComputerPlayer::ComputerPlayer() :
	m_Symbol(Empty),
	m_Score(2)
{
}

/*
 * Constructor.
 * @param i_Symbol - Computer symbol.
 */
ComputerPlayer::ComputerPlayer(const CellState & i_Symbol) :
		m_Symbol(i_Symbol),
		m_Score(2)
{
}

/*
 * Destructor.
 */
ComputerPlayer::~ComputerPlayer()
{
}

/*
 * Set computer score.
 * @param i_Score - Score to set.
 */
void ComputerPlayer::SetScore(const std::size_t & i_Score)
{
	m_Score = i_Score;
}

/*
 * Set computer symbol.
 * @param i_Symbol - Symbol to set.
 */
void ComputerPlayer::SetSymbol(const CellState & i_Symbol)
{
	m_Symbol = i_Symbol;
}

/*
 * Get computer symbol.
 * @return computer symbol.
 */
CellState ComputerPlayer::GetSymbol() const
{
	return m_Symbol;
}

/*
 * Play computer move using minmax algorithm
 * @param i_Board - Board to play on.
 * @return true if there is any possible moves, false otherwise.
 */
bool ComputerPlayer::Play(Board & i_Board)
{
	std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> rankedMoves;
	CellState opponentSymbol = Validator::GetOpponentSymbol(m_Symbol);

	// Save a snapshot of the original board.
	std::vector<CellState> originalBoard = i_Board.GetData();

	// Get all possible moves.
	std::vector<std::pair<std::size_t, std::size_t>> possibleMoves = Validator::GetPossibleMoves(i_Board, m_Symbol);
	if (0 != possibleMoves.size())
	{
		// Play each move.
		for (std::pair<std::size_t, std::size_t> move : possibleMoves)
		{
			std::vector<CellState> firstSave = i_Board.GetData();
			i_Board.SetCell(move.first, move.second, m_Symbol);
			Validator::FlipOpponentCells(move.first, move.second, i_Board, m_Symbol);

			// Get all possible moves of the opponent.
			std::vector<std::pair<std::size_t, std::size_t>> opponentPossibleMoves = Validator::GetPossibleMoves(i_Board, opponentSymbol);
			if (0 == opponentPossibleMoves.size())
			{
				// TO DO...
			}

			std::size_t stepRank = 0;

			// Play opponent move.
			for (std::pair<std::size_t, std::size_t> opponentMove : opponentPossibleMoves)
			{
				// Save board state.
				std::vector<CellState> secondSave = i_Board.GetData();

				// Make a move.
				i_Board.SetCell(opponentMove.first, opponentMove.second, opponentSymbol);
				Validator::FlipOpponentCells(opponentMove.first, opponentMove.second, i_Board, opponentSymbol);

				// Calculate the rank of the computer move.
				std::size_t opponentScore = i_Board.CalculatePlayerScore(opponentSymbol);
				std::size_t computerScore = i_Board.CalculatePlayerScore(m_Symbol);
				std::size_t scoreDifference = opponentScore - computerScore;

				if (scoreDifference > stepRank)
				{
					stepRank = scoreDifference;
				}

				// Restore temporary state.
				i_Board.SetData(secondSave);
			}

			// Update ranks vector.
			std::pair<std::pair<std::size_t, std::size_t>, std::size_t> moveRank;
			moveRank.first = move;
			moveRank.second = stepRank;
			rankedMoves.push_back(moveRank);

			// Restore temporary state.
			i_Board.SetData(firstSave);
			stepRank = 0;
		}

		// Restore original state.
		i_Board.SetData(originalBoard);

		// Find minimum value in the rank moves vector.
		std::pair<std::size_t, std::size_t> choosenMove = Validator::FindMinRank(rankedMoves);
		i_Board.SetCell(choosenMove.first, choosenMove.second, m_Symbol);
		Validator::FlipOpponentCells(choosenMove.first, choosenMove.second, i_Board, m_Symbol);
		std::cout << "Computer move: " << choosenMove.first << "," << choosenMove.second << std::endl << std::endl;

		return true;
	}

	else
	{
		std::cout << "No possible moves." << std::endl;
		return false;
	}

	return true;
}
