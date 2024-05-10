#pragma once

#include "enums.hpp"
#include "eastl.hpp"
#include "offsets.hpp"
#include "math.hpp"
#include "vfunc.hpp"
#include "typeinfo.hpp"

#include <cstdint>

namespace fb
{
	class ServerPlayer;
	class ServerSoldierEntity;
	class ServerConnection;
	namespace network
	{
		class ChatMessage;
	}
	class ServerPeer;

	typedef void(HACK_THISCALL* t_fb__ServerSoldierEntity__setPosition)(fb::ServerSoldierEntity* thisptr, float* position);
	inline t_fb__ServerSoldierEntity__setPosition fb__ServerSoldierEntity__setPosition = (t_fb__ServerSoldierEntity__setPosition)OFFSET_SERVERSOLDIER_SETPOS;

	typedef fb::ServerConnection* (HACK_THISCALL* t_fb__ServerPeer__connectionForPlayer)(fb::ServerPeer* thisptr, fb::ServerPlayer* player);
	inline t_fb__ServerPeer__connectionForPlayer fb__ServerPeer__connectionForPlayer = (t_fb__ServerPeer__connectionForPlayer)OFFSET_CONNECTIONFORPLAYER;

	typedef void(HACK_THISCALL* t_fb__ServerConnection__sendChatMessage)(fb::ServerConnection* thisptr, fb::network::ChatMessage* chat);
	inline t_fb__ServerConnection__sendChatMessage fb__ServerConnection__sendChatMessage = (t_fb__ServerConnection__sendChatMessage)OFFSET_SENDCHATMESSAGE;

	typedef char* (HACK_THISCALL* t_fb__NetworkChatMessage__NetworkChatMessage)(fb::network::ChatMessage* a1, int channelId, unsigned __int64 recipientMask, wchar_t* string);
	inline t_fb__NetworkChatMessage__NetworkChatMessage fb__NetworkChatMessage__NetworkChatMessage = (t_fb__NetworkChatMessage__NetworkChatMessage)OFFSET_NETWORKMSG_CONSTRUCT;

	typedef fb::ServerPlayer* (HACK_CDECL* t_fb__bfServerAdministration__getPlayer)(char** name); // eastl::string
	inline t_fb__bfServerAdministration__getPlayer fb__bfServerAdministration__getPlayer = (t_fb__bfServerAdministration__getPlayer)OFFSET_SERVERADM_GETPLAYER;


	template <typename T> class SmartArray
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_lastElement2;
	public:

		T At(INT nIndex)
		{
			if (m_firstElement == 0)
				return 0;

			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}

		__int32 size()
		{
			__int32 p = ((intptr_t)m_lastElement - (intptr_t)m_firstElement);

			return p / sizeof(intptr_t);
		}
		bool exist(T a)
		{
			for (int i = 0; i < size(); i++)
				if (At(i) == a)
					return true;

			return false;
		}
		T operator [](INT index) { return At(index); }
	};

	namespace network
	{
		class ChatMessage
		{
		public:
			static ChatMessage* allocNew(wchar_t* w, ChatChannelType type = CctAdmin)
			{
				ChatMessage* ncm = new ChatMessage;

				fb__NetworkChatMessage__NetworkChatMessage(ncm, type, -1, w);

				return ncm;
			}

			char pad_0000[11]; //0x0000
			wchar_t m_string[128]; //0x000B
			unsigned int m_playerId; //0x010B
			unsigned __int64 m_recipientMask; //0x010F
			ChatChannelType m_channelId; //0x0117
			bool m_senderIsDead; //0x011B
		}; //Size: 0x0120
		static_assert(sizeof(ChatMessage) == 0x0120);
	}

	class ServerPlayerEntryComponent
	{
	public:
		char pad_0000[76]; //0x0000
		ServerPlayer* m_player; //0x004C
	};

	class ServerVehicleEntity
	{
	public:
		virtual TypeInfo* GetType();

		char pad_0000[248]; //0x0004
		SmartArray<ServerPlayerEntryComponent*> m_entries; //0x00F8
	};

	class ServerPlayer
	{
	public:
		virtual ~ServerPlayer();
		virtual void* getSoldier();
		virtual void* getEntry();
		virtual bool inVehicle();

		char pad_0004[4]; //0x0004
		class PlayerData* m_playerData; //0x0008
		char pad_000C[4]; //0x000C
		eastl::string m_Name; //0x0010
		uint64_t m_nativeData; //0x0020
		char m_id[17]; //0x0028
		char pad_0039[907]; //0x0039
		ServerSoldierEntity* m_customizationSoldier; // 0x03C4
		char pad_03C8[36]; // 0x3C8
		ServerVehicleEntity* m_attachedControllable; // 0x03E8
		// ...
	};

	class ServerPlayerManager
	{
	public:
		virtual ~ServerPlayerManager();
		virtual eastl::vector<ServerPlayer*>* getPlayers();
	};

	class ServerPeer
	{

	};

	//fb::ServerConnection : fb::network::EngineConnectionPeer, fb::network::IControlObjectServer, fb::network::IChatMessageHandler, fb::MessageListener
	class ServerConnection
	{
	
	};

	class ServerGameContext // inherit GameContext
	{
	public:
		char pad_0000[16]; //0x0000
		class ServerLevel* m_level; //0x0010
		/*
		fb::MaterialGridManager *m_materialGridManager;
		fb::ant::AnimationManager *m_animationManager;
		fb::ModelAnimationManager *m_modelAnimationManager;
		fb::MessageManager *m_messageManager;
		fb::BlueprintBundleManager *m_blueprintBundleManager;
		fb::DLCManager *m_dlcManager;
		fb::DemoControl *m_demoControl;
		fb::Realm m_realm;
		*/
		char pad_0014[28]; //0x0014
		ServerPlayerManager* m_serverPlayerManager; //0x0030
		class ServerPeer* m_serverPeer; //0x0034

		static ServerGameContext* GetInstance()
		{
			return *(ServerGameContext**)OFFSET_SERVERGAMECONTEXT;
		}
	};

	class ServerSoldierEntity
	{
	public:
		virtual TypeInfo* getType();
		VFUNC(void, getTransform, 22, (SM::Matrix* mat), (this, mat));

		char pad_0004[44]; //0x0004
		class CharacterPhysicsEntity* m_characterPhysicsEntity; //0x0030
		char pad_0034[244]; //0x0034
		float m_HealthRaw; //0x0128
		char pad_012C[24]; //0x012C
		class ServerPlayer* m_pPlayer; //0x0144
		char pad_0148[136]; //0x0148
		float m_MaxHealth; //0x01D0
		char pad_01D4[424]; //0x01D4
		class SoldierBlueprint* m_soldierBlueprint; //0x037C
		char pad_0380[440]; //0x0380
		class ServerSoldierHealthModuleImpl* m_healthModule; //0x0538
		class ServerSoldierWeaponsComponent* m_ServerSoldierWeaponsComponent; //0x053C
		class ServerSoldierBodyComponent* m_serverSoldierBodyComponent; //0x0540
		class ServerBoneCollisionComponent* m_serverBoneCollisionComponent; //0x0544
		class ServerRagdollComponent* m_serverRagdollComponent; //0x0548
		class ServerCharacterCustomizationComponent* m_serverCharacterCustomizationComponent; //0x054C

		void setPosition(const SM::Vector4& position);
		void setPosition(const SM::Vector3& position);
	};

	void messageChat(fb::ServerPlayer* player, std::wstring wstr);
	void messageChat(fb::ServerPlayer* player, const char* fmt, ...);
}