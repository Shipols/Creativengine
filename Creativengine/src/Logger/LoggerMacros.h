#pragma once

#include "Logger.h"

#define LOGGER_INFO(...) Logger::PrintLine(__VA_ARGS__, MessageType::info);
#define LOGGER_WARNING(...) Logger::PrintLine(__VA_ARGS__, MessageType::warning);
#define LOGGER_ERROR(...) Logger::PrintLine(__VA_ARGS__, MessageType::error);
#define LOGGER_CRITICALERROR(...) Logger::PrintLine(__VA_ARGS__, MessageType::criticalError);