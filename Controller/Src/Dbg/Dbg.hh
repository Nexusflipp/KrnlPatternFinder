#pragma once
#include <iostream>
#include "../Include/Inc_Base.hh"

enum LogType : short
{
	None = 0,
	Info,
	Warn,
	Err
};

namespace DBG
{
	void Print(const LogType& LogType, const std::string_view szDesc);

	template<typename T>
	void PrintObj(const LogType& LogType, const std::string_view szDesc, const T Obj)
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
			std::cout <<  "[WARN]  ";
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

		std::cout << szDesc << ": " << std::uppercase << Obj << '\n';
	}

	template<typename T>
	void PrintObjHex(const LogType& LogType, const std::string_view szDesc, const T Obj)
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

		std::cout << szDesc << ": 0x" << std::hex << std::uppercase << Obj << '\n';
	}

	template<typename T>
	void PrintObjHex(const LogType& LogType, const std::wstring_view szDesc, const T Obj)
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

		std::wcout << szDesc << ": 0x" << std::hex << std::uppercase << Obj << '\n';
	}

	template<typename T>
	void PrintObjHex(const LogType& LogType, const std::wstring_view szDesc, const std::wstring_view szDesc2, const T Obj)
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

		std::wcout << szDesc << " " <<szDesc2 << ": 0x" << std::hex << std::uppercase << Obj << '\n';
	}

	void PrintLastErr(const std::string_view szLoc);
}