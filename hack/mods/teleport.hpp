#pragma once

#include <vector>
#include <string>

namespace fb
{
	class ServerPlayer;
}

namespace teleport
{
	void execute(fb::ServerPlayer* sender, const std::vector<std::string>& args);
}