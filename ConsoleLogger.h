#pragma once
#include"Logger.h"
#include<sstream>
#include<Windows.h>

namespace utility
{
#ifdef DEBUG_MODE
	class ConsoleLogger : public ILogger
	{
	public:
		ConsoleLogger(std::ostream& os) : os_{ os } {};
		~ConsoleLogger() = default;

		void log(LogLevel level, const std::string& s) override {};

		template<typename...Args>
		static void log(const Args&...args)
		{
			std::ostringstream oss;
			((oss << args <<" "), ...);
			oss << "\n";
			OutputDebugStringA(oss.str().c_str());
		}
	private:
		std::ostream& os_;
	};

//#define logToConsole(...) ConsoleLogger::log(__func__,__VA_ARGS__)
#define logToConsole(...) ConsoleLogger::log(__VA_ARGS__)

#else

#define logToConsole(...)

#endif // DEBUG_MODE
}


