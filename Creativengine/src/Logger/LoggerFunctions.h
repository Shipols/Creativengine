#pragma once

#include "Logger.h"

#define LOGGER_INFO(message) Logger::PrintLine(message, MessageType::info);
#define LOGGER_WARNING(message) Logger::PrintLine(message, MessageType::warning);
#define LOGGER_ERROR(message) Logger::PrintLine(message, MessageType::error);
#define LOGGER_CRITICALERROR(message) Logger::PrintLine(message, MessageType::criticalError);

namespace Creativengine {

	static void PrintInfo(const char* message)
	{
		Logger::PrintLine(message, MessageType::info);
	}

	static void PrintWarning(const char* message)
	{
		Logger::PrintLine(message, MessageType::warning);
	}

	static void PrintError(const char* message)
	{
		Logger::PrintLine(message, MessageType::error);
	}

	static void PrintCriticalError(const char* message)
	{
		Logger::PrintLine(message, MessageType::criticalError);
	}

}