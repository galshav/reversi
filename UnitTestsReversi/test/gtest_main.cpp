/*
 * gtest_main.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: gal
 */

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
