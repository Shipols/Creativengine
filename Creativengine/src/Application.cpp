#include <iostream>

namespace Creativengine {

	__declspec(dllexport) void Run()
	{
		std::string value;

		std::cout << "Hello World!" << std::endl;

		while (true);
	}

}