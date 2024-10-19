//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	target_list_c target_list;

	void target_list_c::get_information()
	{
		if (functions::local_player_is_valid())
		{
			aimbot.aim_state.reset();

			for (auto i{ 0 }; i < max_entities; i++)
			{
				entities[i].reset();

				if (!entity_is_valid(i))
					continue;

				if (!setup_hit_points(i))
					continue;

				if (should_skip_target(i))
					continue;

				scan_target_info(i);

				add_to_aim_target_list(i);
				add_to_anti_aim_target_list(i);
			}

			sort_aim_target_list();
			sort_anti_aim_target_list();

			aimbot.set_aim_state();
		}
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::setup_hit_points(std::int32_t index)
	{
		if (auto dobj_ptr{ functions::Com_GetClientDObj(index, structures::LOCAL_CLIENT_FIRST) }; dobj_ptr)
		{
			if (functions::get_centity(index)->nextState.eType == structures::et_player)
			{
				ImVec3 min_temp =
				{
					std::numeric_limits<std::float_t>::max(),
					std::numeric_limits<std::float_t>::max(),
					std::numeric_limits<std::float_t>::max()
				}, max_temp =
				{
					-std::numeric_limits<std::float_t>::max(),
					-std::numeric_limits<std::float_t>::max(),
					-std::numeric_limits<std::float_t>::max()
				};

				for (auto i{ 0 }; i < structures::bone_max; i++)
				{
					if (!functions::CG_DObjGetWorldTagPos(&functions::get_centity(index)->pose, dobj_ptr, functions::GScr_AllocString(structures::bone_names[i].second.c_str()), &entities[index].bones[i]))
					{
						return false;
					}
				}

				if (should_scan_index(index))
				{
					for (auto i{ 0 }; i < structures::bone_max; i++)
					{
						if (bone_list.is_selected(i))
						{
							entities[index].hit_points.push_back(entities[index].bones[i]);
						}
					}
				}

				else
				{
					entities[index].hit_points.push_back(entities[index].bones[configs.aim_bone.current.integer]);
				}
			}

			else if (functions::get_centity(index)->nextState.eType == structures::et_actor)
			{
				if (!functions::CG_DObjGetWorldTagPos(&functions::get_centity(index)->pose, dobj_ptr, functions::GScr_AllocString(structures::bone_names[structures::bone_head].second.c_str()), &entities[index].bones[structures::bone_head]))
				{
					return false;
				}

				entities[index].hit_points.push_back(entities[index].bones[structures::bone_head]);
			}

			else if (functions::get_centity(index)->nextState.eType == structures::et_vehicle)
			{
				functions::DObjCalcBounds(dobj_ptr, &entities[index].box_min, &entities[index].box_max);
				functions::CG_GetDObjOrientation(structures::LOCAL_CLIENT_FIRST, index, entities[index].box_axis, &entities[index].box_origin);

				mathematics.rotate_box(entities[index].box_corners, entities[index].box_axis, entities[index].box_origin, entities[index].box_min, entities[index].box_max);
				mathematics.get_box_center(entities[index].box_corners, &entities[index].box_center);

				entities[index].hit_points.push_back(entities[index].box_center);
			}

			else if (functions::get_centity(index)->nextState.eType == structures::et_helicopter)
			{
				functions::DObjCalcBounds(dobj_ptr, &entities[index].box_min, &entities[index].box_max);
				functions::CG_GetDObjOrientation(structures::LOCAL_CLIENT_FIRST, index, entities[index].box_axis, &entities[index].box_origin);

				mathematics.rotate_box(entities[index].box_corners, entities[index].box_axis, entities[index].box_origin, entities[index].box_min, entities[index].box_max);
				mathematics.get_box_center(entities[index].box_corners, &entities[index].box_center);

				entities[index].hit_points.push_back(entities[index].box_center);
			} else return false;
		} else return false;

		return true;
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::should_skip_target(std::int32_t index)
	{
		if (entity_is_friendly(index))
		{
			return true;
		}

		if (index < max_clients)
		{
			if (priorities[index].is_ignored)
			{
				return true;
			}
		}

		if (functions::get_centity(index)->nextState.eType == structures::et_actor)
		{
			if (!configs.target_actors.current.enabled)
			{
				return true;
			}
		}

		else if (functions::get_centity(index)->nextState.eType == structures::et_vehicle)
		{
			if (!configs.target_vehicles.current.enabled)
			{
				return true;
			}
		}

		else if (functions::get_centity(index)->nextState.eType == structures::et_helicopter)
		{
			if (!configs.target_helicopters.current.enabled)
			{
				return true;
			}
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::scan_target_info(std::int32_t index)
	{
		entities[index].trace_success = trace_entity(functions::get_centity(index), configs.auto_wall.current.enabled, entities[index].hit_points, &entities[index].hit_location, &entities[index].damage);
		entities[index].distance = mathematics.calculate_distance(entities[index].hit_location, functions::get_view_origin());
		entities[index].fov = mathematics.calculate_fov(entities[index].hit_location, functions::get_view_origin(), functions::get_view_angles());
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::add_to_aim_target_list(std::int32_t index)
	{
		aim_target_info_s aim_target_info;

		if (entities[index].trace_success && entities[index].fov <= configs.aim_angle.current.value)
		{
			if (index < max_clients)
			{
				aim_target_info.is_priority = priorities[index].is_prioritized;
			}

			aim_target_info.index = index;

			aim_target_info.distance = entities[index].distance;
			aim_target_info.damage = entities[index].damage;
			aim_target_info.fov = entities[index].fov;

			aim_target_list.push_back(aim_target_info);
		}
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::add_to_anti_aim_target_list(std::int32_t index)
	{
		anti_aim_target_info_s anti_aim_target_info;

		if (index < max_clients)
		{
			if (priorities[index].is_prioritized && !priorities[index].is_ignored)
			{
				anti_aim_target_info.index = index;

				anti_aim_target_info.distance = entities[index].distance;
				anti_aim_target_info.damage = entities[index].damage;
				anti_aim_target_info.fov = entities[index].fov;

				anti_aim_target_list.push_back(anti_aim_target_info);
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::sort_aim_target_list()
	{
		if (!aim_target_list.empty())
		{
			if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_distance)
			{
				std::stable_sort(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& a, const aim_target_info_s& b) { return a.distance < b.distance; });

				if (auto aim_target{ std::find_if(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& targetinfo)
				{
					return targetinfo.is_priority;
				}) }; aim_target != aim_target_list.end())
				{
					aimbot.aim_state.aim_target_num = aim_target->index;
				}
				else
				{
					aimbot.aim_state.aim_target_num = aim_target_list.front().index;
				}
			}

			else if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_damage)
			{
				std::stable_sort(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& a, const aim_target_info_s& b) { return a.damage > b.damage; });

				if (auto aim_target{ std::find_if(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& targetinfo)
				{
					return targetinfo.is_priority;
				}) }; aim_target != aim_target_list.end())
				{
					aimbot.aim_state.aim_target_num = aim_target->index;
				}
				else
				{
					aimbot.aim_state.aim_target_num = aim_target_list.front().index;
				}
			}

			else if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_fov)
			{
				std::stable_sort(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& a, const aim_target_info_s& b) { return a.fov < b.fov; });

				if (auto aim_target{ std::find_if(aim_target_list.begin(), aim_target_list.end(), [&](const aim_target_info_s& targetinfo)
				{
					return targetinfo.is_priority;
				}) }; aim_target != aim_target_list.end())
				{
					aimbot.aim_state.aim_target_num = aim_target->index;
				}
				else
				{
					aimbot.aim_state.aim_target_num = aim_target_list.front().index;
				}
			}

			aim_target_list.clear();
		}
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::sort_anti_aim_target_list()
	{
		if (!anti_aim_target_list.empty())
		{
			if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_distance)
			{
				std::stable_sort(anti_aim_target_list.begin(), anti_aim_target_list.end(), [&](const anti_aim_target_info_s& a, const anti_aim_target_info_s& b) { return a.distance < b.distance; });

				aimbot.aim_state.anti_aim_target_num = anti_aim_target_list.front().index;
			}

			else if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_damage)
			{
				std::stable_sort(anti_aim_target_list.begin(), anti_aim_target_list.end(), [&](const anti_aim_target_info_s& a, const anti_aim_target_info_s& b) { return a.damage > b.damage; });

				aimbot.aim_state.anti_aim_target_num = anti_aim_target_list.front().index;
			}

			else if (configs.sort_algorithm_targets.current.integer == configs_c::sort_algorithm_fov)
			{
				std::stable_sort(anti_aim_target_list.begin(), anti_aim_target_list.end(), [&](const anti_aim_target_info_s& a, const anti_aim_target_info_s& b) { return a.fov < b.fov; });

				aimbot.aim_state.anti_aim_target_num = anti_aim_target_list.front().index;
			}

			anti_aim_target_list.clear();
		}
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::entity_is_valid(std::int32_t index)
	{
		return ((index != functions::get_cg()->predictedPlayerState.clientNum) && (functions::get_centity(index)->alive & 0x2) && !(functions::get_centity(index)->nextState.lerp.eFlags[1] & entity_flag_dead) && (functions::get_centity(index)->nextState.weapon != 0xA2));
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::entity_is_visible(std::int32_t index)
	{
		return trace_entity_internal(functions::get_centity(index), false, entities[index].bones[structures::bone_helmet]);
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::entity_is_friendly(std::int32_t index)
	{
		return functions::CG_IsEntityFriendly(structures::LOCAL_CLIENT_FIRST, functions::get_centity(index));
	}
	/*
	//=====================================================================================
	*/
	std::float_t target_list_c::trace_entity_internal(structures::centity_s* entity, bool autowall, ImVec3 position)
	{
		if (autowall && !functions::weapon_is_buckshot() && !functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState) && (entity->nextState.eType == structures::et_player || entity->nextState.eType == structures::et_actor))
		{
			return auto_wall.get_bullet_damage(entity, functions::get_view_origin(), position);
		}

		else
		{
			return auto_wall.trace_bullet(entity, functions::get_view_origin(), position);
		}
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::trace_entity(structures::centity_s* entity, bool autowall, std::vector<ImVec3> hitpoints, ImVec3* position, std::float_t* damage)
	{
		damage_info_s damage_info;
		std::vector<damage_info_s> targets;
		std::vector<std::future<std::float_t>> futures;

		if (configs.multi_threading.current.enabled)
		{
			for (auto i{ 0u }; i < hitpoints.size(); i++)
			{
				futures.push_back(std::async(&target_list_c::trace_entity_internal, this, entity, autowall, hitpoints[i]));
			}

			for (auto i{ 0u }; i < hitpoints.size(); i++)
			{
				if ((damage_info.damage = futures[i].get()) > configs.min_damage.current.value)
				{
					damage_info.pos = hitpoints[i];
					damage_info.distance = mathematics.calculate_distance(hitpoints[i], functions::get_view_origin());
					damage_info.fov = mathematics.calculate_fov(hitpoints[i], functions::get_view_origin(), functions::get_view_angles());

					targets.push_back(damage_info);
				}
			}

			futures.clear();
		}

		else
		{
			for (auto i{ 0u }; i < hitpoints.size(); i++)
			{
				if ((damage_info.damage = trace_entity_internal(entity, autowall, hitpoints[i])) > configs.min_damage.current.value)
				{
					damage_info.pos = hitpoints[i];
					damage_info.distance = mathematics.calculate_distance(hitpoints[i], functions::get_view_origin());
					damage_info.fov = mathematics.calculate_fov(hitpoints[i], functions::get_view_origin(), functions::get_view_angles());

					targets.push_back(damage_info);
				}
			}
		}

		if (!targets.empty())
		{
			if (configs.sort_algorithm_bones.current.integer == configs_c::sort_algorithm_distance)
			{
				std::stable_sort(targets.begin(), targets.end(), [&](const damage_info_s& a, const damage_info_s& b) { return a.distance < b.distance; });

				if (damage) *damage = targets.front().damage;
				if (position) *position = targets.front().pos;
			}

			if (configs.sort_algorithm_bones.current.integer == configs_c::sort_algorithm_damage)
			{
				std::stable_sort(targets.begin(), targets.end(), [&](const damage_info_s& a, const damage_info_s& b) { return a.damage > b.damage; });

				if (damage) *damage = targets.front().damage;
				if (position) *position = targets.front().pos;
			}

			if (configs.sort_algorithm_bones.current.integer == configs_c::sort_algorithm_fov)
			{
				std::stable_sort(targets.begin(), targets.end(), [&](const damage_info_s& a, const damage_info_s& b) { return a.fov < b.fov; });

				if (damage) *damage = targets.front().damage;
				if (position) *position = targets.front().pos;
			}

			targets.clear();

			return true;
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	bool target_list_c::should_scan_index(std::int32_t index)
	{
		switch (configs.bones_inclusion.current.integer)
		{
		case configs_c::bone_scan_priorities_only:
			return priorities[index].is_prioritized;

		case configs_c::bone_scan_everyone:
			return true;

		default:
			return false;
		}
	}
	/*
	//=====================================================================================
	*/
	void target_list_c::draw_tab_header()
	{
		if (ImGui::CollapsingHeader("Bone Selection"))
		{
			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());

			ImGui::Combo("##inclusion", &configs.bones_inclusion.current.integer, niggerware::utils::string::concatenate(configs.bones_inclusion.items).c_str());
			if (ImGui::ListBoxHeader("##selection", structures::bone_max, 10))
			{
				bone_list.get_bone_selection();

				ImGui::ListBoxFooter();
			}

			ImGui::PopItemWidth();
		}
	}
}

//=====================================================================================