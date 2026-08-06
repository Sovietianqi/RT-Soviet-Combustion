#pragma once

#include <Windows.h>

class Debug
{
public:
	enum class ExitCode : int
	{
		Undefined = -1,
		SLFail = 114514,
		BadINIUsage = 1919810,
	};

	static char StringBuffer[0x1000];
	static char FinalStringBuffer[0x1000];
	static char DeferredStringBuffer[0x1000];
	static int CurrentBufferSize;

	static void Log(const char* pFormat, ...);
	static void LogGame(const char* pFormat, ...);
};

