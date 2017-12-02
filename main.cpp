/*
 * Filename: main.cpp
 * Purpose: The reverse game entry point of the application.
 * Created on: Oct 20, 2017
 * Author: Gal Shav-Artza.
 */

#include <iostream>
#include <exception>
#include "BoardExceptions.hpp"
#include "Coordinator.hpp"

/*
 * Program entry point.
 */
int main(std::size_t argc, char * argv[])
{

	try
	{
		Coordinator coordinator;
		coordinator.Run();

		return 0;
	}

	catch (ExceptionIncorrentParameter i_Error)
	{
		std::cout << i_Error.what() << std::endl;
	}

	catch (std::exception i_Error)
	{
		std::cout << i_Error.what() << std::endl;
	}

	catch (...)
	{
		std::cout << "Unhandled exception." << std::endl;
	}
}
