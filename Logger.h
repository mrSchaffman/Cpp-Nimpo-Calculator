#pragma once
#include <cstddef>
#include<string>

#define DEBUG_MODE
namespace utility
{
#ifdef DEBUG_MODE
	class ILogger
	{
	public:
		enum class LogLevel { Error, Info, Debug };
	public:
		virtual~ILogger() = default;
		virtual void log(LogLevel level, const std::string& s) = 0;
	};

#endif // DEBUG_MODE
}

