/*
 * Filename: ComputerPlayer.hpp
 * Purpose: Computer AI declerations.
 * Created on: Dec 1, 2017
 * Author: Gal shav-Artza.
 */

#pragma once
#include "Player.hpp"
#include "Board.hpp"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer();
	using Player::Player; // Inherit Player's constructors.
	ComputerPlayer(const CellState & i_Symbol);
	~ComputerPlayer();
	virtual bool Play(Board & i_Board) override;
	virtual void SetSymbol(const CellState & i_Symbol) override;
	virtual CellState GetSymbol() const override;
	virtual void SetScore(const std::size_t & i_Score) override;

private:
	CellState m_Symbol = Empty;
	std::size_t m_Score = 2;		// initially, 2 cells for each player.
};
