#include "Dbg.hh"

void DBG::Print(const LogType& LogType, const std::string_view szDesc)
{
	switch (LogType)
	{
	case LogType::None:
		break;

	case LogType::Info:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_BLUE) | FOREGROUND_INTENSITY);
		std::cout << "[INFO]  ";
		break;
	}

	case LogType::Warn:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN) | FOREGROUND_INTENSITY);
		std::cout << "[WARN]  ";
		break;
	}

	case LogType::Err:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "[ERROR] ";
		break;
	}

	default:
		break;
	}

	std::tm TimeInfo;
	std::stringstream Stream;
	std::time_t Time = system_clock::to_time_t(system_clock::now());
	localtime_s(&TimeInfo, &Time);
	Stream << "[" << std::put_time(&TimeInfo, "%H:%M:%S") << "] ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	std::cout << Stream.str();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));

	std::cout << szDesc << '\n';
}

void DBG::PrintLastErr(const std::string_view szErrLoc)
{
	LPCSTR szErr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), REINTER<LPSTR>(&szErr), NULL, NULL);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "[ERROR] ";

	std::tm TimeInfo;
	std::stringstream Stream;
	std::time_t Time = system_clock::to_time_t(system_clock::now());
	localtime_s(&TimeInfo, &Time);
	Stream << "[" << std::put_time(&TimeInfo, "%H:%M:%S") << "] ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	std::cout << Stream.str();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));

	std::cout << szErrLoc << ": " << szErr;
}