/*
 * Validator.hpp
 *
 *  Created on: Oct 28, 2017
 *      Author: gal
 */

#pragma once
#include "Board.hpp"			// For using board enum and reference.
#include <vector>				// For using vector.
#include <utility>				// For using pair.

enum Direction
{
	TopLeft   , Top   , TopRight,
	Left,               Right,
	BottomLeft, Bottom, BottomRight
};

/*
 * Validates the user inputs and legitimate operations on the board.
 */
class Validator
{
public:
	static std::vector<std::pair<std::size_t, std::size_t>> GetPossibleMoves(const Board & i_Board, const CellState & i_Symbol);
	static bool CheckNeighbors(const std::size_t & i_Row, const std::size_t & i_Column, const Board & i_Board, const CellState & i_Symbol);
	static bool CheckDirection(const std::size_t & i_Row, const std::size_t & i_Column, const Board & i_Board, const CellState & i_Symbol, const Direction & i_Direction);
	static void FlipOpponentCells(const std::size_t & i_Row, const std::size_t & i_Column, Board & i_Board, const CellState & i_Symbol);
	static void FlipInDirection(const std::size_t & i_Row, const std::size_t & i_Column, Board & i_Board, const CellState & i_Symbol, const Direction & i_Direction);
	static CellState GetOpponentSymbol(const CellState & i_Symbol);
	static std::pair<std::size_t, std::size_t> FindMinRank(const std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> & i_MoveRanks);

private:

};
