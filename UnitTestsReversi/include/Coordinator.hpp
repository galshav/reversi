/*
 * Coordinator.hpp
 *
 *  Created on: Oct 27, 2017
 *      Author: gal
 */

#pragma once
#include "Board.hpp"
#include "HumanPlayer.hpp"
#include "Player.hpp"

/*
 * Coordinate the entire game's moves.
 * Checks if the game isn't over and determine the current player's turn.
 */
class Coordinator
{
public:
	Coordinator();
	Coordinator(const Coordinator & i_Other) = delete;
	Coordinator(Coordinator && i_Other) = delete;
	~Coordinator() = default;
	bool IsGameOver(const Board & i_Board, const CellState & i_Symbol) const;
	void Run();

private:
	Player * m_FirstPlayer = nullptr;
	Player * m_SecondPlayer = nullptr;
	Board m_Board = 8;
	//HumanPlayer m_FirstPlayer = Empty;
	//HumanPlayer m_SecondPlayer = Empty;
};
