//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	CSteamID* __fastcall GetSteamID_h(ISteamUser* _this);
	typedef decltype(GetSteamID_h)* GetSteamID_t;
	extern GetSteamID_t GetSteamID_o;

	const char* __fastcall GetPersonaName_h(ISteamFriends* _this);
	typedef decltype(GetPersonaName_h)* GetPersonaName_t;
	extern GetPersonaName_t GetPersonaName_o;

	bool __fastcall BIsDlcInstalled_h(ISteamApps* _this, void* rdx, void* r8, void* r9, AppId_t appID);
	typedef decltype(BIsDlcInstalled_h)* BIsDlcInstalled_t;
	extern BIsDlcInstalled_t BIsDlcInstalled_o;

	class steam_c
	{
	public:

		bool is_xuid_over_ridden;
		std::uint64_t xuid_over_ride;
		std::string name_over_ride;

		ISteamUser* user;
		ISteamUserStats* user_stats;
		ISteamFriends* friends;
		ISteamApps* apps;

		void init();
		void free();

		void give_all_achievements();
	};

	extern steam_c steam;
}

//=====================================================================================
