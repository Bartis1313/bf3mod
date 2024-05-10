#pragma once

#include "typeinfo.hpp"

namespace fb
{
	class Message : public fb::ITypedObject
	{
	public:
		const int category; //0x0004
		const int type; //0x0008
		char pad_000C[28]; //0x000C
	}; //Size: 0x0028
	static_assert(sizeof(Message) == 0x28);
}