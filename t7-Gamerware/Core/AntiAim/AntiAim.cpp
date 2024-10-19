//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	anti_aim_c anti_aim;

	void anti_aim_c::anti_aim_all(structures::usercmd_s* usercmd)
	{
		if (aimbot.aim_state.aim_target_acquired)
		{
			anti_aim_pitch(usercmd, configs.anti_aim_pitch_on_target.current.integer);
			anti_aim_yaw(usercmd, configs.anti_aim_yaw_on_target.current.integer);
		}

		else if (functions::PM_IsSprinting(&functions::get_cg()->predictedPlayerState))
		{
			anti_aim_pitch(usercmd, configs.anti_aim_pitch_on_sprint.current.integer);
			anti_aim_yaw(usercmd, configs.anti_aim_yaw_on_sprint.current.integer);
		}

		else
		{
			anti_aim_pitch(usercmd, configs.anti_aim_pitch_default.current.integer);
			anti_aim_yaw(usercmd, configs.anti_aim_yaw_default.current.integer);
		}
	}
	/*
	//=====================================================================================
	*/
	void anti_aim_c::anti_aim_pitch(structures::usercmd_s* usercmd, std::int32_t pitch)
	{
		anti_aim_angles.x = short_to_angle(usercmd->viewAngles[0]);

		if (pitch == configs_c::anti_aim_pitch_zero)
		{
			anti_aim_angles.x = 0.0f - functions::get_cg()->predictedPlayerState.deltaAngles.x;
		}

		else if (pitch == configs_c::anti_aim_pitch_up)
		{
			anti_aim_angles.x = -70.0f - functions::get_cg()->predictedPlayerState.deltaAngles.x;
		}

		else if (pitch == configs_c::anti_aim_pitch_down)
		{
			anti_aim_angles.x = 70.0f - functions::get_cg()->predictedPlayerState.deltaAngles.x;
		}

		else if (pitch == configs_c::anti_aim_pitch_jitter)
		{
			switch (usercmd->serverTime % 2)
			{
			case 0:
				anti_aim_angles.x = -70.0f - functions::get_cg()->predictedPlayerState.deltaAngles.x;
				break;

			case 1:
				anti_aim_angles.x = 70.0f - functions::get_cg()->predictedPlayerState.deltaAngles.x;
				break;
			}
		}

		else if (pitch == configs_c::anti_aim_pitch_random)
		{
			std::random_device random_device;
			std::uniform_real_distribution random_pitch(-70.0f, 70.0f);

			anti_aim_angles.x = random_pitch(random_device) - functions::get_cg()->predictedPlayerState.deltaAngles.x;
		}

		else if (pitch == configs_c::anti_aim_pitch_reverse)
		{
			if (aimbot.aim_state.aim_target_acquired || aimbot.aim_state.anti_aim_target_acquired)
			{
				anti_aim_angles.x = aimbot.aim_state.anti_aim_angles.x;
			}

			else
			{
				anti_aim_angles.x = configs.anti_aim_shield_pitch_shift.current.value - functions::get_view_angles().x;

				if (anti_aim_angles.x > 70.0f) anti_aim_angles.x = 70.0f;
				if (anti_aim_angles.x < -70.0f) anti_aim_angles.x = -70.0f;

				anti_aim_angles.x -= functions::get_cg()->predictedPlayerState.deltaAngles.x;
			}
		}

		else if (pitch == configs_c::anti_aim_pitch_custom)
		{
			anti_aim_angles.x = configs.anti_aim_custom_pitch.current.value - functions::get_cg()->predictedPlayerState.deltaAngles.x;
		}

		if (ready_for_anti_aim() && pitch > configs_c::anti_aim_pitch_off)
		{
			usercmd->viewAngles[0] = angle_to_short(anti_aim_angles.x);
		}
	}
	/*
	//=====================================================================================
	*/
	void anti_aim_c::anti_aim_yaw(structures::usercmd_s* usercmd, std::int32_t yaw)
	{
		anti_aim_angles.y = short_to_angle(usercmd->viewAngles[1]);

		if (yaw == configs_c::anti_aim_yaw_spin)
		{
			static auto spin_angle = 0.0f;

			if (spin_angle >= 360.0f)
				spin_angle -= 360.0f;

			anti_aim_angles.y = spin_angle - functions::get_cg()->predictedPlayerState.deltaAngles.y;

			spin_angle += configs.anti_aim_spin_speed.current.value;
		}

		else if (yaw == configs_c::anti_aim_yaw_jitter)
		{
			switch (usercmd->serverTime % 4)
			{
			case 0:
				anti_aim_angles.y = 0.0f - functions::get_cg()->predictedPlayerState.deltaAngles.y;
				break;

			case 1:
				anti_aim_angles.y = 90.0f - functions::get_cg()->predictedPlayerState.deltaAngles.y;
				break;

			case 2:
				anti_aim_angles.y = 180.0f - functions::get_cg()->predictedPlayerState.deltaAngles.y;
				break;

			case 3:
				anti_aim_angles.y = 270.0f - functions::get_cg()->predictedPlayerState.deltaAngles.y;
				break;
			}
		}

		else if (yaw == configs_c::anti_aim_yaw_random)
		{
			std::random_device random_device;
			std::uniform_real_distribution random_yaw(0.0f, 360.0f);

			anti_aim_angles.y = random_yaw(random_device) - functions::get_cg()->predictedPlayerState.deltaAngles.y;
		}

		else if (yaw == configs_c::anti_aim_yaw_reverse)
		{
			if (aimbot.aim_state.aim_target_acquired || aimbot.aim_state.anti_aim_target_acquired)
			{
				anti_aim_angles.y = aimbot.aim_state.anti_aim_angles.y;
			}

			else
			{
				anti_aim_angles.y = configs.anti_aim_shield_yaw_shift.current.value + functions::get_view_angles().y - 180.0f;

				anti_aim_angles.y -= functions::get_cg()->predictedPlayerState.deltaAngles.y;
			}
		}

		else if (yaw == configs_c::anti_aim_yaw_custom)
		{
			anti_aim_angles.y = configs.anti_aim_custom_yaw.current.value - functions::get_cg()->predictedPlayerState.deltaAngles.y;
		}

		if (ready_for_anti_aim() && yaw > configs_c::anti_aim_yaw_off)
		{
			usercmd->viewAngles[1] = angle_to_short(anti_aim_angles.y);
		}
	}
	/*
	//=====================================================================================
	*/
	void anti_aim_c::apply_to_third_person_view()
	{
		functions::set_third_person(configs.third_person.current.enabled);

		functions::Dvar_SetFromStringByName("cg_thirdPersonRange", "90.0", true);
		functions::Dvar_SetFromStringByName("cg_thirdPersonAngle", "0.0", true);
		functions::Dvar_SetFromStringByName("cg_thirdPersonUpOffset", "30.0", true);

		if (functions::is_third_person() && ready_for_anti_aim() && !packets.is_air_stuck)
		{
			functions::get_cg()->clientInfo[functions::get_cg()->predictedPlayerEntity.nextState.number].angles.x = anti_aim_angles.x + functions::get_cg()->predictedPlayerState.deltaAngles.x;
			functions::get_cg()->predictedPlayerEntity.pose.angles.y = anti_aim_angles.y + functions::get_cg()->predictedPlayerState.deltaAngles.y;
		}
	}
	/*
	//=====================================================================================
	*/
	void anti_aim_c::stabilize_third_person_view_origin()
	{
		if (functions::is_third_person() && ready_for_anti_aim() && !packets.is_air_stuck)
		{
			functions::CG_GetPlayerViewOrigin(structures::LOCAL_CLIENT_FIRST, &functions::get_cg()->predictedPlayerState, &functions::get_cg()->refDef.viewOrigin);
		}
	}
	/*
	//=====================================================================================
	*/
	bool anti_aim_c::ready_for_anti_aim()
	{
		return 
		(
			functions::BG_GetWeaponDef(functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)) &&
			!functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState) &&
			!(functions::get_cg()->predictedPlayerEntity.nextState.lerp.eFlags[1] & entity_flag_prone) &&
			!functions::WallRun_IsWallRunning(&functions::get_cg()->predictedPlayerState) &&
			!functions::Slide_IsPlayerSliding(&functions::get_cg()->predictedPlayerState)
		);
	}
}

//=====================================================================================