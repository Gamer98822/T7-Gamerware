//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	packets_c packets;

	void packets_c::process_packets(structures::usercmd_s* oldcmd, structures::usercmd_s* currentcmd, structures::usercmd_s* newcmd)
	{
		if (!functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState) && !functions::is_player_out_of_ammo())
		{
			aimbot.silent_aim(oldcmd);
			aimbot.silent_aim(currentcmd);

			removals.no_spread(oldcmd, currentcmd->serverTime);
			removals.no_spread(currentcmd, newcmd->serverTime);

			aimbot.auto_fire(currentcmd);
			aimbot.auto_fire(newcmd);

			aimbot.full_auto_all_weapons(oldcmd);
			aimbot.full_auto_all_weapons(currentcmd);
		}
	}
	/*
	//=====================================================================================
	*/
	void packets_c::process_packets(structures::usercmd_s* currentcmd)
	{
		if (functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState))
		{
			aimbot.auto_fire(currentcmd);
			aimbot.silent_aim(currentcmd);
		}

		anti_aim.anti_aim_all(currentcmd);
	}
	/*
	//=====================================================================================
	*/
	bool packets_c::is_packet_choked(structures::usercmd_s* usercmd)
	{
		if (!configs.fake_lag.current.value || (configs.fake_lag.current.value && aimbot.aim_state.aim_target_acquired) || !functions::is_in_game())
		{
			return true;
		}

		static auto last_packet_time = 0u;
		if (!last_packet_time || last_packet_time > usercmd->serverTime || usercmd->serverTime > last_packet_time + configs.fake_lag.current.value)
		{
			last_packet_time = usercmd->serverTime;

			return true;
		}

		return false;
	}
}

//=====================================================================================