#pragma once

#include <Windows.h>

HACK_INLINE void MemPatch(uintptr_t address, const char* pByte, size_t numberofbytestowrite)
{
	constexpr auto POINTER_SIZE = sizeof(void*);
	const auto addrCasted = reinterpret_cast<void*>(address);

	DWORD dwOld{ };
	VirtualProtect(addrCasted, POINTER_SIZE, PAGE_EXECUTE_READWRITE, &dwOld);

	if (pByte)
	{
		memcpy(addrCasted, pByte, numberofbytestowrite);
	}
	else
	{
		memset(addrCasted, 0x90, 5);
	}

	VirtualProtect(addrCasted, POINTER_SIZE, dwOld, &dwOld);
}

#include <stdio.h>

HACK_INLINE void CreateConsole()
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
}
