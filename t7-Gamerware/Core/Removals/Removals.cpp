//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	removals_c removals;

	void removals_c::no_recoil()
	{
		if (configs.no_recoil.current.enabled)
		{
			functions::get_client_active()->recoilAngles = ImVec3();
		}
	}
	/*
	//=====================================================================================
	*/
	void removals_c::no_spread(structures::usercmd_s* usercmd, std::uint32_t servertime)
	{
		if (configs.no_spread.current.enabled)
		{
			if (aimbot.aim_state.is_auto_firing)
			{
				ImVec3 spread_angles;

				if (configs.silent_aim.current.enabled)
				{
					auto seed = transform_seed(servertime);
					auto weapon_spread = get_weapon_spread();

					bullet_random_dir(&seed, &spread_angles.y, &spread_angles.x);

					spread_angles *= weapon_spread;
				}

				else
				{
					get_spread_angles(servertime, get_weapon_spread(), &spread_angles);

					spread_angles = (functions::get_view_angles() - spread_angles);
				}

				usercmd->viewAngles[0] += angle_to_short(spread_angles.x);
				usercmd->viewAngles[1] += angle_to_short(spread_angles.y);
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void removals_c::no_flinch(structures::player_state_s* ps)
	{
		if (configs.no_flinch.current.enabled)
		{
			ps->damageYaw = 255;
			ps->damagePitch = 255;
			ps->damageCount = 0;
		}
	}
	/*
	//=====================================================================================
	*/
	void removals_c::fast_reload()
	{
		if (configs.quick_reload.current.enabled)
		{
			static auto reloaded_weapon{ 0i64 };

			auto is_reloading = [&]()
			{
				return functions::CG_IsPlayerReloading();
			};

			auto ammo_added = [&](std::int64_t weapon)
			{
				auto ammo_added = false;

				if (functions::BG_IsDualWield(functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)))
				{
					ammo_added =
					(
						(functions::BG_GetAmmoInClip(&functions::get_cg()->predictedPlayerState, weapon) == functions::BG_GetClipSize(weapon) &&
						(functions::BG_GetAmmoInClip(&functions::get_cg()->predictedPlayerState, functions::BG_GetDualWieldWeapon(weapon)) == functions::BG_GetClipSize(functions::BG_GetDualWieldWeapon(weapon)))) ||
						!functions::BG_GetAmmoNotInClip(&functions::get_cg()->predictedPlayerState, weapon) || !functions::BG_GetAmmoNotInClip(&functions::get_cg()->predictedPlayerState, functions::BG_GetDualWieldWeapon(weapon))
					);
				}

				else
				{
					ammo_added =
					(
						(functions::BG_GetAmmoInClip(&functions::get_cg()->predictedPlayerState, weapon) == functions::BG_GetClipSize(weapon)) ||
						!functions::BG_GetAmmoNotInClip(&functions::get_cg()->predictedPlayerState, weapon)
					);
				}

				return ammo_added;
			};

			if (reloaded_weapon)
			{
				for (auto i = 0; i < 15; i++)
				{
					if (auto held_weapon{ functions::get_cg()->predictedPlayerState.heldWeapons[i] }; held_weapon.weapon == functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false))
					{
						functions::CG_CycleWeapon(structures::LOCAL_CLIENT_FIRST, false, structures::PRBO_NONE, false);
						break;
					}
				}

				reloaded_weapon = 0;
			}

			if (auto current_weapon{ functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false) }; current_weapon && is_reloading() && ammo_added(current_weapon))
			{
				reloaded_weapon = current_weapon;

				for (auto i = 0; i < 15; i++)
				{
					if (auto held_weapon{ functions::get_cg()->predictedPlayerState.heldWeapons[i] }; held_weapon.weapon && held_weapon.weapon != reloaded_weapon)
					{
						functions::CG_CycleWeapon(structures::LOCAL_CLIENT_FIRST, true, structures::PRBO_NONE, false);
						break;
					}
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void removals_c::get_spread_angles(std::uint32_t servertime, std::float_t spread, ImVec3* angles)
	{
		ImVec3 axis[3], end, dir;
		auto seed = transform_seed(servertime);

		mathematics.angles_to_axis(functions::get_view_angles(), axis);
		functions::CG_SimulateBulletFire_EndPos(&seed, 0.0f, spread, functions::get_view_origin(), &end, &dir, 0.0f, 360.0f, axis[0], axis[1], axis[2], functions::get_bullet_range(), functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false), 0, 1);
		
		mathematics.vec_to_angles(dir, angles);
		*angles = mathematics.clamp_angles(*angles);
	}
	/*
	//=====================================================================================
	*/
	void removals_c::bullet_end_pos(std::uint32_t* seed, std::float_t spread, ImVec3 start, ImVec3* end, ImVec3* direction, ImVec3 axis[3], std::float_t range)
	{
		std::float_t random_right, random_up;
		bullet_random_dir(seed, &random_right, &random_up);

		random_right *= std::tanf(degrees_to_radians(spread)) * range;
		random_up *= std::tanf(degrees_to_radians(spread)) * range;

		*end = start + (axis[0] * range) + (axis[1] * random_right) + (axis[2] * random_up);
		*direction = *end - start;

		mathematics.vector_normalize(direction);
	}
	/*
	//=====================================================================================
	*/
	void removals_c::bullet_random_dir(std::uint32_t* seed, std::float_t* right, std::float_t* up)
	{
		auto random_a = functions::BG_random(seed) * 360.0f;
		random_a = functions::AngleNormalize360(random_a);
		random_a = degrees_to_radians(random_a);

		auto random_b = functions::BG_random(seed);

		*right = std::cosf(random_a) * random_b;
		*up = std::sinf(random_a) * random_b;
	}
	/*
	//=====================================================================================
	*/
	std::uint32_t removals_c::transform_seed(std::uint32_t servertime)
	{
		auto server_time = servertime;

		functions::BG_seedRandWithGameTime(&server_time);

		return server_time;
	}
	/*
	//=====================================================================================
	*/
	std::float_t removals_c::get_weapon_spread()
	{
		auto weapon_id = functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false);
		auto weapon_def = functions::BG_GetWeaponDef(weapon_id);

		if (!weapon_def)
			return 0.0f;

		std::float_t weapon_spread, min_spread, max_spread;
		functions::BG_GetSpreadForWeapon(&functions::get_cg()->predictedPlayerState, weapon_id, &min_spread, &max_spread);
		auto spread_multiplier = byte_to_float(functions::get_cg()->predictedPlayerState.spreadMultiplier);
		auto ads_spread = weapon_def->adsSpread;

		if (functions::get_cg()->predictedPlayerState.weaponPosFrac == 1.0f)
			weapon_spread = (ads_spread + (max_spread - ads_spread) * spread_multiplier);
		else
			weapon_spread = (min_spread + (max_spread - min_spread) * spread_multiplier);

		return weapon_spread;
	}
}

//=====================================================================================