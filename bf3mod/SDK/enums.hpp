#pragma once

namespace fb
{
	enum OrderType
	{
		OrderType_None = 0x0,
		OrderType_RequestHeal = 0x1,
		OrderType_LetMeHeal = 0x2,
		OrderType_RequestAmmo = 0x3,
		OrderType_LetMeGiveAmmo = 0x4,
		OrderType_LetMeRepair = 0x5,
		OrderType_RequestRide = 0x6,
		OrderType_GoGoGo = 0x7,
		OrderType_FollowMe = 0x8,
		OrderType_Negative = 0x9,
		OrderType_Sorry = 0xA,
		OrderType_ThankYou = 0xB,
		OrderType_RogerThat = 0xC,
		OrderType_NeedBackup = 0xD,
		OrderType_Count = 0xE,
	};

	enum CharacterStateType
	{
		CharacterStateType_OnGround = 0x0,
		CharacterStateType_Jumping = 0x1,
		CharacterStateType_InAir = 0x2,
		CharacterStateType_Climbing = 0x3,
		CharacterStateType_Falling = 0x4,
		CharacterStateType_User_0 = 0x5,
		CharacterStateType_User_1 = 0x6,
		CharacterStateType_User_2 = 0x7,
		CharacterStateType_User_3 = 0x8,
		CharacterStateType_User_4 = 0x9,
		CharacterStateType_User_5 = 0xA,
		CharacterStateType_StateCount = 0xB,
		CharacterStateType_Parachute = 0x5,
		CharacterStateType_Swimming = 0x6,
		CharacterStateType_AnimationControlled = 0x7,
		CharacterStateType_Sliding = 0x8,
	};

	enum hkpCharacterStateType
	{
		HK_CHARACTER_ON_GROUND = 0x0,
		HK_CHARACTER_JUMPING = 0x1,
		HK_CHARACTER_IN_AIR = 0x2,
		HK_CHARACTER_CLIMBING = 0x3,
		HK_CHARACTER_FLYING = 0x4,
		HK_CHARACTER_USER_STATE_0 = 0x5,
		HK_CHARACTER_USER_STATE_1 = 0x6,
		HK_CHARACTER_USER_STATE_2 = 0x7,
		HK_CHARACTER_USER_STATE_3 = 0x8,
		HK_CHARACTER_USER_STATE_4 = 0x9,
		HK_CHARACTER_USER_STATE_5 = 0xA,
		HK_CHARACTER_MAX_STATE_ID = 0xB,
	};

	// don't use it, it's messed
	enum WeaponSlot
	{
		WeaponSlot_0 = 0x0,
		WeaponSlot_1 = 0x1,
		WeaponSlot_2 = 0x2,
		WeaponSlot_3 = 0x3,
		WeaponSlot_4 = 0x4,
		WeaponSlot_5 = 0x5,
		WeaponSlot_6 = 0x6,
		WeaponSlot_7 = 0x7,
		WeaponSlot_8 = 0x8,
		WeaponSlot_9 = 0x9,
		WeaponSlot_NumSlots = 0xA,
		WeaponSlot_NotDefined = 0xB,
	};
	
	enum FIXED_WeaponSlot
	{
		Weapon_Primary = 0x0,
		Weapon_Secondary = 0x1, // pistol
		Weapon_GadgetSlot1 = 0x2,
		Weapon_GadgetSlot1_2 = 0x4, // verify this later why it happens
		Weapon_GadgetSlot2 = 0x5,
		Weapon_Grenade = 0x6,
		Weapon_Knife = 0x7,
	};
}