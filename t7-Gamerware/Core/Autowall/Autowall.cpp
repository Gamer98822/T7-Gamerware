//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	auto_wall_c auto_wall;

	std::float_t auto_wall_c::get_bullet_damage(structures::centity_s* entity, ImVec3 start, ImVec3 end)
	{
		if (functions::get_bullet_range() < mathematics.calculate_distance(end, start))
			return 0.0f;

		auto client_num = functions::get_cg()->predictedPlayerState.clientNum;
		auto weapon_id = functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false);
		auto weapon_def = functions::BG_GetWeaponDef(weapon_id);
		auto penetrate_type = functions::BG_GetPenetrateType(weapon_id);
		auto penetration_multiplier = functions::CG_ClientHasPerk(structures::LOCAL_CLIENT_FIRST, client_num, 9) ? 2.0f : 1.0f;

		if (!weapon_id || !weapon_def)
			return 0.0f;

		structures::BulletFireParams bp;
		niggerware::utils::memory::zero(&bp, sizeof(structures::BulletFireParams));

		structures::BulletTraceResults br;
		niggerware::utils::memory::zero(&br, sizeof(structures::BulletTraceResults));

		structures::BulletFireParams bp_reverse;
		niggerware::utils::memory::zero(&bp_reverse, sizeof(structures::BulletFireParams));

		structures::BulletTraceResults br_reverse;
		niggerware::utils::memory::zero(&br_reverse, sizeof(structures::BulletTraceResults));

		structures::BulletPenetrationInfo penetration_info;
		niggerware::utils::memory::zero(&penetration_info, sizeof(structures::BulletPenetrationInfo));

		structures::BulletHitInfo* hit_info = nullptr;

		bp.weaponEntIndex = 1022;
		bp.ignoreEntIndex = client_num;
		bp.damageMultiplier = 1.0f;
		bp.methodOfDeath = weapon_def->bRifleBullet + 1;

		bp.origStart = start;
		bp.start = start;
		bp.end = end;

		bp.dir = end - start;
		mathematics.vector_normalize(&bp.dir);

		if (!functions::BulletTraceSimulated(structures::LOCAL_CLIENT_FIRST, &bp, &br, weapon_id, client_num, 0))
			return 0.0f;

		if (weapon_def->bulletImpactExplode || penetrate_type == structures::penetrate_type_none)
			return 0.0f;

		auto penetration_count = functions::dvar_get_int(offsets::sv_penetrationCount);
		auto trace_hit = true;
		auto next_valid_surface_type = br.depthSurfaceType, last_valid_surface_type = br.depthSurfaceType, last_valid_surface_penetration = 0, wall_count = 0, surface_count = 0, fix_up_count = 0;
		auto damage_multiplier = 1.0f, surface_depth = 0.0f, reverse_surface_depth = 0.0f;

		if (penetration_count > 0)
		{
			while (true)
			{
				fix_up_count = penetration_info.count;
				penetration_info.count = fix_up_count + 1;
				hit_info = &penetration_info.hits[fix_up_count];
				hit_info->sflags = next_valid_surface_type;
				hit_info->bp = bp;
				hit_info->br.trace = br.trace;
				hit_info->br.hitEntNum = br.hitEntNum;
				hit_info->br.hitPos = br.hitPos;
				hit_info->traceHit = trace_hit;

				if (!_bittest(std::recast<const long*>(&br.trace.sflags), 0xC) && (br.trace.sflags & 0x3F00000))
				{
					if (functions::BG_Bullet_FixupHitInfo(&penetration_info, fix_up_count, last_valid_surface_penetration, last_valid_surface_type, br.depthSurfaceType, &bp.damageMultiplier, penetration_multiplier, penetrate_type))
					{
						return 0.0f;
					}

					last_valid_surface_type = br.depthSurfaceType;
					last_valid_surface_penetration = fix_up_count;
					wall_count = fix_up_count;
				}

				surface_depth = functions::BG_GetSurfacePenetrationDepth(penetrate_type, last_valid_surface_type) * penetration_multiplier;
				surface_depth = std::min(surface_depth, 3.4028235e38f);

				if (br.trace.sflags & 0x4)
					surface_depth = 100.0f;

				if (surface_depth <= 0.0f || _bittest(std::recast<const long*>(&br.trace.sflags), 0x8) || !functions::BG_Bullet_AdvanceTrace(&bp, &br, 0.25999999f))
					return 0.0f;

				trace_hit = functions::BulletTraceSimulated(structures::LOCAL_CLIENT_FIRST, &bp, &br, weapon_id, client_num, 0);

				bp_reverse = bp;
				br_reverse = br;

				bp_reverse.dir = bp.dir * -1.0f;
				bp_reverse.start = bp.end;
				bp_reverse.end = (bp_reverse.dir * 0.0099999998f) + hit_info->br.hitPos;
				br_reverse.trace.normal.vec.v.m128_i32[0] ^= 0x80000000;
				br_reverse.trace.normal.vec.v.m128_f32[1] = -br_reverse.trace.normal.vec.v.m128_f32[1];
				br_reverse.trace.normal.vec.v.m128_f32[2] = -br_reverse.trace.normal.vec.v.m128_f32[2];

				if (trace_hit)
					functions::BG_Bullet_AdvanceTrace(&bp_reverse, &br_reverse, 0.0099999998f);

				hit_info->revTraceHit = functions::BulletTraceSimulated(structures::LOCAL_CLIENT_FIRST, &bp_reverse, &br_reverse, weapon_id, client_num, 0);
				hit_info->allSolid = hit_info->revTraceHit && br_reverse.trace.allsolid || br.trace.startsolid && br_reverse.trace.startsolid;

				if (br_reverse.trace.sflags & 0x4)
					br_reverse.hitEntNum = br_reverse.trace.hitId;

				hit_info->revBp = bp_reverse;
				hit_info->revBr = br_reverse;

				hit_info->damage = functions::BG_GetWeaponDamageForRange(weapon_id, bp.origStart, br.hitPos);

				if (hit_info->revTraceHit || hit_info->allSolid)
				{
					hit_info->depth = functions::BG_Bullet_GetDepth(hit_info, &br, &bp_reverse, &br_reverse);

					if (hit_info->revTraceHit)
					{
						hit_info->sflagsRv = br_reverse.depthSurfaceType;

						if (!_bittest(std::recast<const long*>(&br_reverse.trace.sflags), 0xC) && br_reverse.trace.sflags & 0x3F00000)
						{
							if (functions::BG_Bullet_FixupHitInfo(&penetration_info, penetration_info.count, wall_count, last_valid_surface_type, br_reverse.depthSurfaceType, &bp.damageMultiplier, penetration_multiplier, penetrate_type))
							{
								return 0.0f;
							}

							last_valid_surface_penetration = penetration_info.count;
							last_valid_surface_type = br_reverse.depthSurfaceType;
							wall_count = last_valid_surface_penetration;
						}

						reverse_surface_depth = functions::BG_GetSurfacePenetrationDepth(penetrate_type, last_valid_surface_type) * penetration_multiplier;
						surface_depth = std::min(surface_depth, reverse_surface_depth);

						if (br_reverse.trace.sflags & 0x4)
							surface_depth = 100.0f;

						if (surface_depth <= 0.0f || _bittest(std::recast<const long*>(&br_reverse.trace.sflags), 0x8))
							return 0.0f;
					}

					damage_multiplier -= hit_info->depth / surface_depth;

					if (damage_multiplier <= 0.0f)
						return 0.0f;
				}

				else
				{
					if (!trace_hit)
						break;

					if (functions::dvar_get_int(offsets::bg_bulletPenetrationTreatVoidsAsSolid) & 0x8)
					{
						hit_info->voidFilled = true;
						hit_info->depth = functions::BG_Bullet_GetDepth(hit_info, &hit_info->br, &bp, &br);
					}
				}

				if (!trace_hit)
					break;

				last_valid_surface_penetration = wall_count;

				if (++surface_count >= penetration_count)
					return 0.0f;

				next_valid_surface_type = br.depthSurfaceType;
			}

			last_valid_surface_penetration = wall_count;
		}

		if (functions::BG_Bullet_FixupHitInfo(&penetration_info, penetration_info.count, last_valid_surface_penetration, last_valid_surface_type, last_valid_surface_type, &bp.damageMultiplier, penetration_multiplier, penetrate_type))
		{
			return 0.0f;
		}

		else
		{
			return get_remaining_damage(&hit_info->bp, &hit_info->br, weapon_id);
		}
	}
	/*
	//=====================================================================================
	*/
	std::float_t auto_wall_c::trace_bullet(structures::centity_s* entity, ImVec3 start, ImVec3 end)
	{
		if (functions::get_bullet_range() < mathematics.calculate_distance(end, start))
			return 0.0f;

		auto client_num = functions::get_cg()->predictedPlayerState.clientNum;
		auto weapon_id = functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false);
		auto weapon_def = functions::BG_GetWeaponDef(weapon_id);

		if (!weapon_id || !weapon_def)
			return 0.0f;

		structures::BulletFireParams bp;
		niggerware::utils::memory::zero(&bp, sizeof(structures::BulletFireParams));

		structures::BulletTraceResults br;
		niggerware::utils::memory::zero(&br, sizeof(structures::BulletTraceResults));

		bp.weaponEntIndex = 1022;
		bp.ignoreEntIndex = client_num;
		bp.damageMultiplier = 1.0f;
		bp.methodOfDeath = weapon_def->bRifleBullet + 1;

		bp.origStart = start;
		bp.start = start;
		bp.end = end;

		bp.dir = end - start;
		mathematics.vector_normalize(&bp.dir);

		if (functions::BulletTraceSimulated(structures::LOCAL_CLIENT_FIRST, &bp, &br, weapon_id, client_num, 0))
		{
			if (functions::Trace_GetEntityHitId(&br.trace) == entity->nextState.number || br.trace.fraction == 1.0f)
			{
				return get_remaining_damage(&bp, &br, weapon_id);
			}
		}

		return 0.0f;
	}
	/*
	//=====================================================================================
	*/
	std::float_t auto_wall_c::get_remaining_damage(structures::BulletFireParams* bp, structures::BulletTraceResults* br, std::int64_t weapon)
	{
		auto result = 0.0f;

		if (bp->damageMultiplier > 0.0f)
		{
			result = std::stcast<std::float_t>(functions::BG_GetWeaponDamageForRange(weapon, bp->origStart, br->hitPos)) * bp->damageMultiplier;
			result *= functions::BG_GetWeaponHitLocationMultiplier(weapon, br->trace.partGroup);
		}

		return result;
	}
}

//=====================================================================================