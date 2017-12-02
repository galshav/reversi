/*
 * HumanPlayer.hpp
 *
 *  Created on: Oct 27, 2017
 *      Author: gal
 */

#pragma once
#include "Player.hpp"
#include "Board.hpp"			// For using the board enum.

/*
 * Human Player class.
 */
class HumanPlayer : public Player
{
public:
	HumanPlayer();
	using Player::Player; // Inherit the Player's constructors.
	HumanPlayer(const CellState & i_Symbol);
	virtual ~HumanPlayer();
	virtual bool Play(Board & i_Board) override;
	virtual void SetSymbol(const CellState & i_Symbol) override;
	virtual CellState GetSymbol() const override;
	virtual void SetScore(const std::size_t & i_Score) override;

private:
	CellState m_Symbol = Empty;
	std::size_t m_Score = 2;		// initially, 2 cells for each player.
};
