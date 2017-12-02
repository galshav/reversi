/*
 * Filename: Board.hpp
 * Purpose: Board class declerations.
 * Created on: Oct 20, 2017
 * Author: Gal Shav-Artza.
 */

#pragma once
#include <vector>			// Board managed resource is vector<CellState>.
#include <cinttypes>		// For using built-in integer types.

// Create a new variable that represent the current cell state.
enum CellState {Empty, Red, Black};

/*
 * The board class is responsible to allocate and holds the required game values in memory.
 * It's contain a vector which is a managed resource.
 * By this the internal managed resource cannot leak.
 */
class Board
{
public:
	Board();
	Board(const std::size_t & i_BoardSize);
	Board(const Board & i_Other) = delete;				// Disable copy internal memory.
	Board & operator=(const Board & i_Other) = delete;  // Disable copy internal memory.
	Board & operator=(Board && i_Other) noexcept;
	Board(Board && i_Other);
	~Board();
	void Print() const;
	void SetCell(const std::size_t & i_Row, const std::size_t & i_Column, const CellState & i_CellState);
	const std::size_t GetBoardSize() const;
	CellState operator[](std::size_t i_Index) const;
	std::size_t CalculatePlayerScore(const CellState & i_Symbol);
	std::vector<CellState> GetData() const;
	void SetData(const std::vector<CellState> & i_Data);

private:
	void setInitialState() noexcept;
	std::size_t m_BoardSize = 0;
	std::vector<CellState> m_Data = {Empty};		// Managed resource - Contain game board data.
};
