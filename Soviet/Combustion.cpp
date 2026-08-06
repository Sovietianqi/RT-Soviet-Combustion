#include <RSC.h>

HANDLE RSC::hInstance = NULL;
HANDLE RSC::hProcess = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        RSC::hInstance = (HANDLE)hModule;
        DisableThreadLibraryCalls(hModule);

        break;
    }

    case DLL_PROCESS_DETACH:
    {

        break;
    }
        break;
    }
    return TRUE;
}

DEFINE_HOOK(0x7CD810, GameRun, 0x9)
{
    RSC::hProcess = GetCurrentProcess();
    return 0;
}

DEFINE_HOOK(0x52CAE9, GameInt, 0x5)
{
    RSC::UnlockSingleCoreLimit(RSC::hProcess);
    RSC::ApplyMMCSS();
    RSC::SetHighResTimer();
    return 0;
}

DEFINE_HOOK(0x52F639, Game_Cmdline, 0x5)
{
    Debug::Log("RT-Soviet Combustion Initialization Complete.\n");
    Debug::Log("RSC Version: 1.0.1.B by Sovietianqi.\n");
    Debug::Log("此版本为最后版本，如有问题请联系作者\n");
    Debug::Log("RT-Soviet Combustion Engine is free to use, please do not use it for commercial purposes.\n");
    return 0;
}

DEFINE_HOOK(0x7CD8F1, GameExit, 0x5)
{
    RSC::RSCLeave();
    RSC::RestoreMMCSS();
    RSC::RestoreHighResTimer();
    return 0;
}


