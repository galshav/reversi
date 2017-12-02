/*
 * Validator.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: gal
 */

#include "Validator.hpp"
#include "Board.hpp"

/*
 * Get a vector of all possible moves according to the rules.
 * @param i_Board - The gaming board.
 * @param i_Symbol - player's symbol.
 * @return vector of possible moves for current player.
 */
std::vector<std::pair<std::size_t, std::size_t>> Validator::GetPossibleMoves(const Board & i_Board, const CellState & i_Symbol)
{
	std::vector<std::pair<std::size_t, std::size_t>> possibleMoves;
	const std::size_t boardSize = i_Board.GetBoardSize();

	for (std::size_t i = 0; i < boardSize; ++i)
	{
		for (std::size_t j = 0 ; j < boardSize; ++j)
		{
			// Checks if the given cell is empty.
			std::size_t oneDimensionalIndex = i * boardSize + j;
			if (Empty == i_Board[oneDimensionalIndex])
			{
				bool possible = CheckNeighbors(i, j, i_Board, i_Symbol);
				if (true == possible)
				{
					// Add cell to possibleMoves vector.
					std::pair<std::size_t, std::size_t> pair(i, j);
					possibleMoves.push_back(pair);
				}
			}
		}
	}

	return possibleMoves;
}

/*
 * Check each neighbors of a given cell and return if flip process is available.
 * @param i_Row - Row number.
 * @param i_Colum - Column number.
 * @param i_Board - The gaming board.
 * @param i_Symbol - Player's symbol.
 * @return true if one of the flip is available, false otherwise.
 */
bool Validator::CheckNeighbors(const std::size_t & i_Row, const std::size_t & i_Column, const Board & i_Board, const CellState & i_Symbol)
{
	std::size_t boardSize = i_Board.GetBoardSize();

	// Current cell is top left.
	if (0 == i_Row && 0 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight));
	}

	// Current cell is top right.
	else if (0 == i_Row && boardSize - 1 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft));
	}

	// Current cell is bottom left.
	else if (boardSize - 1 == i_Row && 0 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right));
	}

	// Current cell is bottom right.
	else if (boardSize - 1 == i_Row && boardSize - 1 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft));
	}

	// Scan upper line.
	else if (0 == i_Row)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight));
	}

	// Scan bottom line.
	else if (boardSize - 1 == i_Row)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight));
	}

	// Scan left line
	else if (0 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight));
	}

	// Scan right line.
	else if (boardSize - 1 == i_Column)
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft));
	}

	// Scan all.
	else
	{
		return (CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Top) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Left) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Right) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom) ||
				CheckDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight));
	}

}

/*
 * Check if flip is required in specific direction.
 * @param i_Row - Row number.
 * @param i_Column - Column number.
 * @param i_Board - The gaming board.
 * @param i_Symbol - Player's symbol.
 * @param i_Direction - The scanning direction.
 * @return true if flip is available, false otherwise.
 */
bool Validator::CheckDirection(const std::size_t & i_Row, const std::size_t & i_Column, const Board & i_Board, const CellState & i_Symbol, const Direction & i_Direction)
{
	std::size_t boardSize = i_Board.GetBoardSize();
	std::size_t i = i_Row;
	std::size_t j = i_Column;
	bool flag = false;

	// Loop until out of board dimensions.
	while (i < boardSize && j < boardSize)
	{
	    // Update index in order to point to the next cell in the scanning process.
		if (Right == i_Direction)
		{
			j++;
		}

		else if (Left == i_Direction)
		{
			j--;
		}

		else if (Top == i_Direction)
		{
			i--;
		}

		else if (Bottom == i_Direction)
		{
			i++;
		}

		else if (TopLeft == i_Direction)
		{
			i--;
			j--;
		}

		else if (TopRight == i_Direction)
		{
			i--;
			j++;
		}

		else if (BottomLeft == i_Direction)
		{
			i++;
			j--;
		}

		else if (BottomRight == i_Direction)
		{
			i++;
			j++;
		}

		// Exit condition.
		if (i == boardSize || j == boardSize)
		{
			return false;
		}

		// Empty cell reached.
		if (Empty == i_Board[i * boardSize + j])
		{
			return false;
		}

		// Enemy cell reached.
		if (i_Symbol != i_Board[i * boardSize + j])
		{
			flag = true;
			continue;
		}

		if (false == flag)
		{
			return false;
		}

		else
		{
			return true;
		}
	}

	return false;
}

/*
 * Flip opponent cells is required.
 * @param i_Row - Row number.
 * @param i_column - Column number.
 * @param i_Board - The gaming board.
 * @param i_Symbol - Player's symbol.
 */
void Validator::FlipOpponentCells(const std::size_t & i_Row, const std::size_t & i_Column, Board & i_Board, const CellState & i_Symbol)
{
	std::size_t boardSize = i_Board.GetBoardSize();

		// Current cell is top left.
		if (0 == i_Row && 0 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight);
		}

		// Current cell is top right.
		else if (0 == i_Row && boardSize - 1 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft);
		}

		// Current cell is bottom left.
		else if (boardSize - 1 == i_Row && 0 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
		}

		// Current cell is bottom right.
		else if (boardSize - 1 == i_Row && boardSize - 1 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft);
		}

		// Scan upper line.
		else if (0 == i_Row)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight);
		}

		// Scan bottom line.
		else if (0 == i_Row)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight);
		}

		// Scan left line
		else if (0 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight);
		}

		// Scan right line.
		else if (boardSize - 1 == i_Column)
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft);
		}

		// Scan all.
		else
		{
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopLeft);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Top);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, TopRight);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Left);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Right);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomLeft);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, Bottom);
			FlipInDirection(i_Row, i_Column, i_Board, i_Symbol, BottomRight);
		}

	return;
}

/*
 * Flip opponent cells in specific direction.
 * @param i_Row - Row number.
 * @param i_column - Column number.
 * @param i_Board - The gaming board.
 * @param i_Symbol - Player's symbol.
 * @param i_direction - The scanning direction.
 */
void Validator::FlipInDirection(const std::size_t & i_Row, const std::size_t & i_Column, Board & i_Board, const CellState & i_Symbol, const Direction & i_Direction)
{
	std::size_t i = i_Row;
	std::size_t j = i_Column;
	std::size_t boardSize = i_Board.GetBoardSize();

	bool shouldFlip = CheckDirection(i_Row, i_Column, i_Board, i_Symbol, i_Direction);
	if (true == shouldFlip)
	{
		if (Right == i_Direction)
		{
			j++;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				j++;
			}
		}

		else if (Left == i_Direction)
		{
			j--;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				j--;
			}
		}

		else if (Top == i_Direction)
		{
			i--;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i--;
			}
		}

		else if (Bottom == i_Direction)
		{
			i++;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i++;
			}
		}

		else if (TopLeft == i_Direction)
		{
			i--;
			j--;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i--;
				j--;
			}
		}

		else if (TopRight == i_Direction)
		{
			i--;
			j++;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i--;
				j++;
			}
		}

		else if (BottomLeft == i_Direction)
		{
			i++;
			j--;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i++;
				j--;
			}
		}

		else if (BottomRight == i_Direction)
		{
			i++;
			j++;
			while(i_Symbol != i_Board[i * boardSize + j])
			{
				i_Board.SetCell(i, j, i_Symbol);
				i++;
				j++;
			}
		}
	}

	return;
}

/*
 * Return the opponent symbol.
 * @param i_Symbol - The CellState symbol.
 * @return opponent symbol.
 */
CellState Validator::GetOpponentSymbol(const CellState & i_Symbol)
{
	if (Red == i_Symbol)
	{
		return Black;
	}

	return Red;
}

/*
 * Find the minimum rank in a given ranks vector.
 * @param i_MoveRanks - Computer move ranks.
 * @return minimum rank in vector.
 */
std::pair<std::size_t, std::size_t> Validator::FindMinRank(const std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> & i_MoveRanks)
{
	std::pair<std::size_t, std::size_t> minMov;
	std::size_t min = i_MoveRanks[0].second;

	for (std::pair<std::pair<std::size_t, std::size_t>, std::size_t> move : i_MoveRanks)
	{
		if (move.second <= min)
		{
			min = move.second;
			minMov.first = move.first.first;
			minMov.second = move.first.second;
		}
	}

	return minMov;
}
