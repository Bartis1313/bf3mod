#include "hooks.hpp"

#include <MinHook.h>

bool hooks::install()
{
	if (MH_Initialize() != MH_OK)
		return false;

	return true;
}


/* todo: verify if ida failed with ret type, and get retaddr check from
*	.text:01338CDC                 cmp     eax, ebx
	.text:01338CDE                 jz      loc_1338FCD
	.text:01338CE4                 test    byte ptr [eax+41h], 1

	to control suppression data, rather than setting it off always
	supp class size 0x38

	a1 - fb::ServerDamageGiverInfo damageGiverInfo
	a2 - fb::EntityWorld entityWorld
	a3 - eastl::fixed_vector of excluded soldiers
	a4 - vec3 spawnpos
	a5 - vec3 projectile start
	a6 - vec3 projectile end
	a7 - float suppression modifier
*/
typedef char* (__cdecl* fb__suppressEnemies)(int a1, int a2, int a3, int a4, int a5, int a6, float a7);
fb__suppressEnemies o__fb__suppressEnemies = 0;
char* __cdecl hkfb__suppressEnemies(int a1, int a2, int a3, int a4, int a5, int a6, float a7)
{
	return nullptr;
}

#include <stdio.h>

#define CREATE_SAFE_HOOK(addr, func, original) \
auto hook__##func = MH_CreateHook((LPVOID)addr, func, (LPVOID*)&original); \
if(hook__##func != MH_OK) { printf("%s failed, %s", #func, MH_StatusToString(hook__##func)); return FALSE; }

bool hooks::init()
{
	CREATE_SAFE_HOOK(0x01338C70, hkfb__suppressEnemies, o__fb__suppressEnemies);

	return true;
}

bool hooks::shutdown()
{
	if (MH_RemoveHook(MH_ALL_HOOKS) != MH_OK)
		return false;
	if (MH_Uninitialize() != MH_OK)
		return false;

	return true;
}