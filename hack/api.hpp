#pragma once

#define HACK_FASTCALL	__fastcall
#define HACK_THISCALL	__thiscall
#define HACK_CDECL		__cdecl
#define HACK_INLINE		__forceinline

#define HACK_THISPTR			void* thisptr
#define HACK_FAST_ARGS			[[maybe_unused]] HACK_THISPTR, [[maybe_unused]] void* edx

// settings
#define HACK_WANT_CONSOLE
// use only if you rename this dll into pbsv.dll, and keep original pbsv to be renamed
#define HACK_AUTOINJECT_BY_PB