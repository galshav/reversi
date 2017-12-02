/*
 * Filename: BoardExceptions.hpp
 * Purpose: Implementations of potential exceptions of the board.
 * Created on: Oct 21, 2017
 * Author: Gal Shav-Artza.
 */

#pragma once
#include <exception>

/*
 * Incorrect size parameter have been inserted.
 */
class ExceptionIncorrentParameter : public std::exception
{
public:
	virtual char const * what() const noexcept
	{
		return "Incorrect size.";
	}
};
