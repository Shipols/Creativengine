#include "Logger.h"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::PrintLine(const char* message, MessageType type)
{
	if (type == MessageType::info)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x002);
		std::cout << "[INFO] " << message << std::endl;
		
	} else if (type == MessageType::warning)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x006);
		std::cout << "[WARNING] " << message << std::endl;
		
	} else if (type == MessageType::error)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00C);
		std::cout << "[ERROR] " << message << std::endl;

	} else if (type == MessageType::criticalError)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x004);
		std::cout << "[CRITICAL ERROR] " << message << std::endl;
	}
}
