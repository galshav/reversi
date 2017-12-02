/*
 * Player.hpp
 *
 *  Created on: Oct 27, 2017
 *      Author: gal
 */

#pragma once
#include "Board.hpp"

/*
 * An abstract class represent a player.
 */
class Player
{
public:
	virtual bool Play(Board & i_Board) = 0;
	virtual ~Player() = default;
	//Player(const CellState & i_Symbol);
	virtual void SetSymbol(const CellState & i_Symbol) = 0;
	virtual CellState GetSymbol() const = 0;
	virtual void SetScore(const std::size_t & i_Score) = 0;

private:

};
