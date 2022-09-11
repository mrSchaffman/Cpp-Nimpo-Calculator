#pragma once
#include"Logger.h"

namespace utility
{
#ifdef DEBUG_MODE

	class FileLogger : public ILogger
	{
	public:
		template<typename...Args>
		static void log(const Args&...args)
		{
			std::ofstream logfile(msDebugFileName_, std::ios_base::app);
			if (logfile.fail())
			{
				std::cerr << "Unable to open debug file!" << std::endl;
				return;
			}
			((logfile << args), ...);
			logfile << std::endl;
		}

		void log(LogLevel level, const std::string& s) override {};
	private:
		static const std::string msDebugFileName_;
	};

	const std::string FileLogger::msDebugFileName_ = "logfile.txt";

#define logToFile(...) FileLogger::log(__func__,"():",__VA_ARGS__)

#else

#define logToFile(...)

#endif // DEBUG_MODE

}
