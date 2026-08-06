#include "Debug.h"
#include <YRPPCore.h>
#include <MessageListClass.h>
#include <CRT.h>

char Debug::StringBuffer[0x1000];
char Debug::FinalStringBuffer[0x1000];
char Debug::DeferredStringBuffer[0x1000];
int Debug::CurrentBufferSize = 0;

void Debug::Log(const char* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	vsprintf_s(FinalStringBuffer, pFormat, args);
	LogGame("%s %s", "[RT-Soviet Combustion]", FinalStringBuffer);
	va_end(args);
}

void Debug::LogGame(const char* pFormat, ...)
{
	JMP_STD(0x4068E0);
}

