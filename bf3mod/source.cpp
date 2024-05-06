#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

#include "utils.hpp"
#include "hooks.hpp"

#define HACK_RET_OK     TRUE
#define HACK_RET_FAIL   FALSE

DWORD WINAPI HackInitThread([[maybe_unused]] LPVOID)
{
#ifdef _DEBUG
    Sleep(5000);
#endif

#ifdef HACK_WANT_CONSOLE
    CreateConsole();
#endif

    MemPatch(0x01117A50, "\xC3", 1); // PBSdk_DropClient
    MemPatch(0x01106990, "\xC3", 1); // PB CL log spam

    if (!hooks::init())
        return HACK_RET_FAIL;

    if (hooks::create())
        return HACK_RET_FAIL;

    return HACK_RET_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        HANDLE hThread = CreateThread(0, 0, HackInitThread, 0, 0, 0);
        if (hThread == INVALID_HANDLE_VALUE)
        {
            // something... that... shouldnt... happen...
        }
        else
            CloseHandle(hThread);
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        // nothing fancy, do without thread
        hooks::shutdown();
    }
    
    return TRUE;
}

