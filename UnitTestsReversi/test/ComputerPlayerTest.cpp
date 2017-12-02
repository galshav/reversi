/*
 * ComputerPlayerTest.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: gal
 */

#include "gtest/gtest.h"
#include "ComputerPlayer.hpp"
#include "Validator.hpp"
#include <utility>

/*
 * Test for getting the opponent symbols.
 */
TEST(ValidatorTest, GetOpponentSymbol)
{
	EXPECT_EQ(Validator::GetOpponentSymbol(Red), Black);
	EXPECT_EQ(Validator::GetOpponentSymbol(Black), Red);
}

/*
 * Find minimum rank for computer player move.
 */
TEST(ValidatorTest, FindMinInRanksVector)
{
	std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> ranksVector;

	std::pair<std::pair<std::size_t, std::size_t>, std::size_t> firstRank;
	std::pair<std::size_t, std::size_t> firstBoardIndex;
	firstBoardIndex.first = 1;
	firstBoardIndex.second = 1;
	std::size_t rank1 = 1;
	firstRank.first = firstBoardIndex;
	firstRank.second = rank1;
	ranksVector.push_back(firstRank);

	std::pair<std::pair<std::size_t, std::size_t>, std::size_t> secondRank;
	std::pair<std::size_t, std::size_t> secondBoardIndex;
	secondBoardIndex.first = 2;
	secondBoardIndex.second = 2;
	std::size_t rank2 = 2;
	secondRank.first = secondBoardIndex;
	secondRank.second = rank2;
	ranksVector.push_back(secondRank);

	std::pair<std::pair<std::size_t, std::size_t>, std::size_t> thirdRank;
	std::pair<std::size_t, std::size_t> thirdBoardIndex;
	thirdBoardIndex.first = 1;
	thirdBoardIndex.second = 1;
	std::size_t rank3 = 3;
	thirdRank.first = thirdBoardIndex;
	thirdRank.second = rank3;
	ranksVector.push_back(thirdRank);

	EXPECT_EQ(Validator::FindMinRank(ranksVector), firstBoardIndex);
}

/*
 * Test the computer move minimum-maximum algorithm.
 */
TEST(ComputerPlayerTest, PlayMoveTest)
{
	// Initiate a game board.
	Board board;

	// first board simulation.
	std::vector<CellState> boardSimulation = board.GetData();
	boardSimulation[2 * 8 + 4] = Red;
	boardSimulation[3 * 8 + 4] = Red;
	boardSimulation[4 * 8 + 4] = Black;
	boardSimulation[4 * 8 + 5] = Black;

	// Simulate first player move.
	board.SetCell(2, 4, Red);
	Validator::FlipOpponentCells(2, 4, board, Red);

	// Computer move.
	ComputerPlayer * computerPlayer = new ComputerPlayer();
	computerPlayer->SetSymbol(Black);
	bool playSuccess = computerPlayer->Play(board);

	EXPECT_TRUE(playSuccess);
	EXPECT_EQ(board.GetData(), boardSimulation);

	// Free allocated memory.
	delete(computerPlayer);
}

