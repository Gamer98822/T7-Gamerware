//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	aimbot_c aimbot;

	void aimbot_c::standard_aim()
	{
		if (!configs.silent_aim.current.enabled)
		{
			if (aim_state.is_auto_aiming)
			{
				aim_state.aim_angles *= configs.aim_power.current.value / 100.0f;

				if (configs.auto_aim_time.current.value)
				{
					aim_state.aim_angles *= std::stcast<std::float_t>(aim_state.current_aim_time.count()) / configs.auto_aim_time.current.value;
				}

				if (aim_state.current_aim_delay.count() == configs.auto_aim_delay.current.value)
				{
					functions::get_client_active()->viewAngles += aim_state.aim_angles;
				}
			}

			if (aim_state.is_auto_zooming)
				if (aim_state.current_zoom_delay.count() == configs.auto_zoom_delay.current.value)
					functions::CL_SetADS(structures::LOCAL_CLIENT_FIRST, true);
		}
	}
	/*
	//=====================================================================================
	*/
	void aimbot_c::silent_aim(structures::usercmd_s* usercmd)
	{
		if (configs.silent_aim.current.enabled)
		{
			if (aim_state.is_auto_aiming)
			{
				usercmd->viewAngles[0] += angle_to_short(aim_state.aim_angles.x);
				usercmd->viewAngles[1] += angle_to_short(aim_state.aim_angles.y);

				mathematics.movement_fix(usercmd, short_to_angle(usercmd->viewAngles[1] + angle_to_short(aim_state.aim_angles.y)), short_to_angle(usercmd->viewAngles[1]), usercmd->forwardMove, usercmd->rightMove);
			}

			if (aim_state.is_auto_zooming)
				if (aim_state.current_zoom_delay.count() == configs.auto_zoom_delay.current.value)
					functions::CL_SetADS(structures::LOCAL_CLIENT_FIRST, true);
		}
	}
	/*
	//=====================================================================================
	*/
	void aimbot_c::auto_fire(structures::usercmd_s* usercmd)
	{
		static auto last_fire_time = 0u;
		if (last_fire_time > usercmd->serverTime)
		{
			last_fire_time = 0u;
		}

		auto fire_time = std::stcast<std::float_t>(functions::BG_GetFireTime(usercmd->weapon));

		if (aim_state.is_auto_firing && aim_state.current_fire_delay.count() == configs.auto_fire_delay.current.value)
		{
			if (usercmd->serverTime - last_fire_time > std::max(fire_time, configs.fire_rate_limiter.current.value))
			{
				usercmd->buttons[0] |= 0x80000000;
				usercmd->buttons[1] |= 0x20000000;

				if (functions::BG_IsDualWield(functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)))
				{
					usercmd->buttons[0] |= 0x100080;
				}

				last_fire_time = usercmd->serverTime;
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void aimbot_c::full_auto_all_weapons(structures::usercmd_s* usercmd)
	{
		if ((!aim_state.is_auto_firing || aim_state.current_fire_delay.count() < configs.auto_fire_delay.current.value) && configs.full_auto_all_weapons.current.enabled)
		{
			if (usercmd->buttons[0] & 0x80000000)
			{
				usercmd->buttons[0] &= ~0x80000000;
			}

			if (usercmd->buttons[1] & 0x20000000)
			{
				usercmd->buttons[1] &= ~0x20000000;
			}

			if (functions::BG_IsDualWield(functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)))
			{
				if (usercmd->buttons[0] & 0x100080)
				{
					usercmd->buttons[0] &= ~0x100080;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void aimbot_c::set_aim_state()
	{
		aim_state.aim_target_acquired = (aim_state.aim_target_num > -1);
		aim_state.anti_aim_target_acquired = (aim_state.anti_aim_target_num > -1);
		aim_state.is_zooming = (functions::get_cg()->predictedPlayerEntity.nextState.lerp.eFlags[1] & entity_flag_zoom);
		aim_state.lockon_target = (configs.aimbot_mode.current.integer == configs_c::aimbot_mode_auto || (configs.aimbot_mode.current.integer == configs_c::aimbot_mode_manual && aim_state.is_zooming));
		aim_state.is_auto_aiming = (aim_state.aim_target_acquired && aim_state.lockon_target);
		aim_state.is_auto_zooming = (configs.auto_zoom.current.enabled && aim_state.aim_target_acquired && configs.aimbot_mode.current.integer == configs_c::aimbot_mode_auto);
		aim_state.is_auto_firing = (configs.auto_fire.current.enabled && aim_state.is_auto_aiming);

		if (aim_state.lockon_target)
		{
			if (aim_state.current_aim_delay.count() == configs.auto_aim_delay.current.value)
				aim_state.current_aim_time += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - aim_state.delta_timer);

			aim_state.current_aim_delay += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - aim_state.delta_timer);
			aim_state.current_zoom_delay += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - aim_state.delta_timer);
			aim_state.current_fire_delay += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - aim_state.delta_timer);
		}

		aim_state.delta_timer = std::chrono::high_resolution_clock::now();

		if (aim_state.last_aim_target_num != aim_state.aim_target_num)
		{
			aim_state.last_aim_target_num = aim_state.aim_target_num;
			aim_state.current_aim_time = 0ms;
		}

		if (!aim_state.aim_target_acquired || packets.is_air_stuck)
			aim_state.current_aim_delay = aim_state.current_zoom_delay = aim_state.current_fire_delay = 0ms;

		if (aim_state.current_aim_time.count() > configs.auto_aim_time.current.value)
			aim_state.current_aim_time = niggerware::utils::misc::milliseconds_cast(configs.auto_aim_time.current.value);

		if (aim_state.current_aim_delay.count() > configs.auto_aim_delay.current.value)
			aim_state.current_aim_delay = niggerware::utils::misc::milliseconds_cast(configs.auto_aim_delay.current.value);

		if (aim_state.current_zoom_delay.count() > configs.auto_zoom_delay.current.value)
			aim_state.current_zoom_delay = niggerware::utils::misc::milliseconds_cast(configs.auto_zoom_delay.current.value);

		if (aim_state.current_fire_delay.count() > configs.auto_fire_delay.current.value)
			aim_state.current_fire_delay = niggerware::utils::misc::milliseconds_cast(configs.auto_fire_delay.current.value);

		if (aim_state.aim_target_acquired)
		{
			aim_state.aim_pos_world = target_list.entities[aim_state.aim_target_num].hit_location;

			mathematics.calculate_aim_angles(aim_state.aim_pos_world, functions::get_view_origin(), &aim_state.aim_angles);
			mathematics.calculate_anti_aim_angles(functions::get_centity(aim_state.aim_target_num)->pose.origin, functions::get_cg()->predictedPlayerState.origin, &aim_state.anti_aim_angles);
		}

		if (aim_state.anti_aim_target_acquired)
		{
			mathematics.calculate_anti_aim_angles(functions::get_centity(aim_state.anti_aim_target_num)->pose.origin, functions::get_cg()->predictedPlayerState.origin, &aim_state.anti_aim_angles);
		}
	}
}

//=====================================================================================