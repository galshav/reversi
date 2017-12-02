/*
 * Filename: Board.cpp
 * Purpose: Board class implementation.
 * Created on: Oct 20, 2017
 * Author: Gal Shav-Artza.
 */

#include <vector>				// For game internal data member.
#include <cinttypes>			// For using built-in integer types.
#include <utility>				// For std::move().
#include <iostream> 			// For printing.
#include "BoardExceptions.hpp"	// For exceptions.
#include "Board.hpp"

/*
 * Default constructor.
 * The default board size is 8.
 */
Board::Board() :
	m_BoardSize(8),
	m_Data(std::vector<CellState>(m_BoardSize * m_BoardSize))
{
	Board::setInitialState();
}

/*
 * Basic constructor.
 * Initiate the board managed resource size to a specific size.
 * If the given size is odd or less than 4 board size is (8 * 8).
 * Input:
 *     i_BoardSize - Required board size.
 */
Board::Board(const std::size_t & i_BoardSize) :
	m_BoardSize((1 == i_BoardSize % 2) || (i_BoardSize < 4) ?
				 8 :
				 i_BoardSize),
	m_Data(std::vector<CellState>(m_BoardSize * m_BoardSize))
{
	Board::setInitialState();
}

/*
 * Moving constructor.
 * Take ownership on other internal's resource.
 * Input:
 *     i_Other - Another board.
 */
Board::Board(Board && i_Other) :
	m_BoardSize(i_Other.m_BoardSize),
	m_Data(std::move(i_Other.m_Data))
{
	i_Other.m_BoardSize = 0;
	i_Other.m_Data = {Empty};
}

/*
 * Moving assignment operator.
 * Input:
 *     i_Other - Other board to move internal memory into.
 */
Board & Board::operator=(Board && i_Other) noexcept
{
	// Guard from assigning an object to itself.
	if (this == &i_Other)
	{
		return *this;
	}

	// Move operations.
	m_BoardSize = i_Other.m_BoardSize;
	m_Data = std::move(i_Other.m_Data);
	// Reset i_Other internal's memebers for more secure solution (makes forensics harder).
	i_Other.m_BoardSize = 0;
	i_Other.m_Data = {Empty};
	return *this;
}

/*
 * Destructor.
 */
Board::~Board()
{
	m_BoardSize = 0;
	//m_Data.~vector();
}

/*
 * Prints the board.
 */
void Board::Print() const
{
	// Print the column number.
	std::cout << ' ';
	for (std::size_t j = 0; j < m_BoardSize; ++j)
	{
		std::cout << j << " ";
	}
	std::cout << std::endl;

	for (std::size_t i = 0; i < m_BoardSize; ++i)
	{
		// Print the line number.
		std::cout << i;

		for (std::size_t j = 0; j < m_BoardSize; ++j)
		{
			CellState cellState = m_Data[i * m_BoardSize + j];
			if (Red == cellState)
			{
				std::cout << "X ";
			}

			else if (Black == cellState)
			{
				std::cout << "O ";
			}

			else
			{
				std::cout << "- ";
			}
		}

		std::cout << std::endl;
	}
}

/*
 * Set a a cell into a given state.
 * Input:
 *     i_Row - The row number.
 *     i_Column - The column number.
 *     i_CellState - the state set to.
 */
void Board::SetCell(const std::size_t & i_Row, const std::size_t & i_Column, const CellState & i_CellState)
{
	if (i_Row >= m_BoardSize || i_Column >= m_BoardSize || i_Row < 0 || i_Column < 0)
	{
		throw ExceptionIncorrentParameter();
	}

	std::size_t oneDimensionalIndex = i_Row * m_BoardSize + i_Column;
	m_Data[oneDimensionalIndex] = i_CellState;
}

/*
 * Set the initial state of the centered cells on the board.
 */
void Board::setInitialState() noexcept
{
	std::size_t centerTopLeftRow = (m_BoardSize / 2) - 1;
	std::size_t centerTopLeftColumn = (m_BoardSize / 2) - 1;
	Board::SetCell(centerTopLeftRow, centerTopLeftColumn, Red);
	Board::SetCell(centerTopLeftRow, centerTopLeftColumn + 1, Black);
	Board::SetCell(centerTopLeftRow + 1, centerTopLeftColumn, Black);
	Board::SetCell(centerTopLeftRow + 1, centerTopLeftColumn + 1, Red);
}

/*
 * Get the board size.
 * @return board size.
 */
const std::size_t Board::GetBoardSize() const
{
	return m_BoardSize;
}

/*
 * Operator[] overloading.
 * @param i_Index - The requested board element.
 * @return Cellstate of the requested cell.
 */
CellState Board::operator[](std::size_t i_Index) const
{
	return m_Data[i_Index];
}

/*
 * Calculate player's score.
 * @param i_Symbol - Player's symbol.
 * @return the players updated score.
 */
std::size_t Board::CalculatePlayerScore(const CellState & i_Symbol)
{
	std::size_t counter = 0;

	for (std::size_t i = 0; i < m_BoardSize; i++)
	{
		for (std::size_t j = 0; j < m_BoardSize; j++)
		{
			if (i_Symbol == m_Data[i * m_BoardSize + j])
			{
				counter++;
			}
		}
	}

	return counter;
}

/*
 * Gets the internal board vector data.
 */
std::vector<CellState> Board::GetData() const
{
	return m_Data;
}

void Board::SetData(const std::vector<CellState> & i_Data)
{
	m_Data = i_Data;
}
