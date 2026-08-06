#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <filesystem>
#include <windows.h>
#include <winnt.h>
#include <YRPP.h>
#include <YRPPCore.h>
#include <Syringe.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <Debug.h>
#include <Helpers/Macro.h>
#include <LocomotionClass.h>
#include <future>
#include <Drawing.h>
#include <d3d11.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <string>
#include <iostream>
#include <GScreenClass.h>
#include <WWMouseClass.h>
#include <TacticalClass.h>
#include <GadgetClass.h>
#include <MessageListClass.h>
#include <CCToolTip.h>
#include <MouseClass.h>
#include <SessionClass.h>
#include <Helpers/CompileTime.h>

#include <type_traits>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include <GScreenClass.h> 
#include <WWMouseClass.h> 
#include <TacticalClass.h> 
#include <GadgetClass.h> 
#include <MessageListClass.h> 
#include <CCToolTip.h> 
#include <MouseClass.h> 
#include <SessionClass.h> 
#include <avrt.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "avrt.lib")

class RSC
{
public:

	//function declarations
	static void DLLMAINEnter();
    static void RSCLeave();
	static void UnlockSingleCoreLimit(HANDLE hProcess);
	static void SetHighResTimer();
    static void RestoreHighResTimer();
	static void ApplyMMCSS();
    static void RestoreMMCSS();
	static void Render(MapClass* pthis);
	static void RenderSystemInit();

	//static variables
	static HANDLE hInstance;
	static HANDLE hProcess;
	static bool UnlockSingleCoreLimitEnable;
	static bool RenderSystemEnable;
	static bool Sovietstylesystem;
	static bool ThreadPoolEnable;
	static bool RenderThreadEnable;
	static const char* General;
	static const size_t readLength = 2048;
	static char readBuffer[readLength];
	static const char readDelims[4];
	static const char readDefval[4];




};




