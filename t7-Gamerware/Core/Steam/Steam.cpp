//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	steam_c steam;

	GetSteamID_t GetSteamID_o;
	GetPersonaName_t GetPersonaName_o;
	BIsDlcInstalled_t BIsDlcInstalled_o;

	void steam_c::init()
	{
		user = structures::get_steam_user();
		user_stats = structures::get_steam_user_stats();
		friends = structures::get_steam_friends();
		apps = structures::get_steam_apps();

		GetPersonaName_o = std::stcast<GetPersonaName_t>(niggerware::utils::hook::vmt(friends, GetPersonaName_h, 0));
		BIsDlcInstalled_o = std::stcast<BIsDlcInstalled_t>(niggerware::utils::hook::vmt(apps, BIsDlcInstalled_h, 7));
	}
	/*
	//=====================================================================================
	*/
	void steam_c::free()
	{
		niggerware::utils::hook::vmt(friends, GetPersonaName_o, 0);
		niggerware::utils::hook::vmt(apps, BIsDlcInstalled_o, 7);
	}
	/*
	//=====================================================================================
	*/
	void steam_c::give_all_achievements()
	{
		if (user_stats)
		{
			for (auto i{ 0 }; i < user_stats->GetNumAchievements(); i++)
			{
				user_stats->SetAchievement(user_stats->GetAchievementName(i));
			}

			user_stats->StoreStats();
		}
	}
	/*
	//=====================================================================================
	*/
	CSteamID* __fastcall GetSteamID_h(ISteamUser* _this)
	{
		auto steam_id = GetSteamID_o(_this);

		if (steam.is_xuid_over_ridden)
		{
			steam_id->SetFromUint64(steam.xuid_over_ride);
		}

		return steam_id;
	}
	/*
	//=====================================================================================
	*/
	const char* __fastcall GetPersonaName_h(ISteamFriends* _this)
	{
		if (!configs.change_name.current.string.empty())
		{
			if (niggerware::utils::memory::is_return_address(offsets::LiveSteam_GetPersonaName_ret))
			{
				niggerware::utils::hook::attach(LiveSteam_FilterPersonaName_o, LiveSteam_FilterPersonaName_h);
				niggerware::utils::hook::attach(Utf8safe_strncpyz_o, Utf8safe_strncpyz_h);
			}

			steam.name_over_ride = functions::parse_place_holders(configs.change_name.current.string);
			return steam.name_over_ride.c_str();
		}

		return GetPersonaName_o(_this);
	}
	/*
	//=====================================================================================
	*/
	bool __fastcall BIsDlcInstalled_h(ISteamApps* _this, void* rdx, void* r8, void* r9, AppId_t appID)
	{
		if (configs.spoof_all_dlc_items.current.enabled)
		{
			return true;
		}

		return BIsDlcInstalled_o(_this, rdx, r8, r9, appID);
	}
}

//=====================================================================================