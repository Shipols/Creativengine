#pragma once

#include <iostream>
#include <ctime>
#include <Windows.h>

enum MessageType
{
	info,
	warning,
	error,
	criticalError
};

class Logger
{
public:
	Logger();
	~Logger();

	static void PrintLine(const char* message, MessageType type);
};