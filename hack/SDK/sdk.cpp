#include "sdk.hpp"

void fb::ServerSoldierEntity::setPosition(const SM::Vector4& position)
{
	float vec[4]{ };
	vec[0] = position.x;
	vec[1] = position.y;
	vec[2] = position.z;
	vec[3] = position.w;

	fb__ServerSoldierEntity__setPosition(this, vec);
}

void fb::ServerSoldierEntity::setPosition(const SM::Vector3& position)
{
	float vec[4]{ };
	vec[0] = position.x;
	vec[1] = position.y;
	vec[2] = position.z;
	vec[3] = 0.0f;

	fb__ServerSoldierEntity__setPosition(this, vec);
}

void fb::messageChat(fb::ServerPlayer* player, std::wstring wstr)
{
	if (!player)
		return;

	auto connection = fb__ServerPeer__connectionForPlayer(fb::ServerGameContext::GetInstance()->m_serverPeer, player);
	if (connection)
	{
		auto ncm = fb::network::ChatMessage::allocNew((wchar_t*)wstr.c_str());

		fb__ServerConnection__sendChatMessage(connection, ncm);
		delete ncm;
	}
}

void fb::messageChat(fb::ServerPlayer* player, const char* fmt, ...)
{
	if (!player)
		return;

	auto connection = fb__ServerPeer__connectionForPlayer(fb::ServerGameContext::GetInstance()->m_serverPeer, player);
	if (connection)
	{
		constexpr size_t MAX_MESSAGE_SIZE = 128;
		char buf[MAX_MESSAGE_SIZE];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf) - 1, fmt, args);
		va_end(args);

		const std::string message{ buf };
		const std::wstring messageW{ message.begin(), message.end() };

		auto ncm = fb::network::ChatMessage::allocNew((wchar_t*)messageW.c_str());

		fb__ServerConnection__sendChatMessage(connection, ncm);
		delete ncm;
	}
}