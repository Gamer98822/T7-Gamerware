//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class target_list_c
	{
	public:

		struct aim_target_info_s
		{
			bool is_priority;
			std::int32_t index;
			std::float_t distance, damage, fov;
		};

		struct anti_aim_target_info_s
		{
			std::int32_t index;
			std::float_t distance, damage, fov;
		};

		struct damage_info_s
		{
			ImVec3 pos;
			std::float_t distance, damage, fov;
		};

		struct bone_list_s
		{
			std::uint32_t get_bone_flag(std::int32_t index)
			{
				return (1 << index);
			}

			void set_selection(std::int32_t index)
			{
				configs.bones_selection.current.integer ^= get_bone_flag(index);
			}

			bool is_selected(std::int32_t index)
			{
				return (configs.bones_selection.current.integer & get_bone_flag(index));
			}

			void get_bone_selection()
			{
				for (auto i{ 0 }; i < structures::bone_max; i++)
				{
					if (ImGui::Selectable(structures::bone_names[i].first.c_str(), is_selected(i)))
					{
						set_selection(i);
					}
				}
			}
		} bone_list;

		struct entities_s
		{
			bool trace_success;
			std::vector<ImVec3> hit_points;
			std::float_t distance, damage, fov;
			ImVec3 bones[structures::bone_max], hit_location;
			ImVec3 box_corners[8], box_axis[3], box_origin, box_min, box_max, box_center;

			void reset()
			{
				trace_success = false;
				hit_points.clear();
			}
		} entities[max_entities];

		struct priorities_s
		{
			bool is_prioritized, is_ignored;
		} priorities[max_clients];

		std::vector<aim_target_info_s> aim_target_list;
		std::vector<anti_aim_target_info_s> anti_aim_target_list;

		void get_information();
		bool setup_hit_points(std::int32_t index);
		bool should_skip_target(std::int32_t index);
		void scan_target_info(std::int32_t index);
		void add_to_aim_target_list(std::int32_t index);
		void add_to_anti_aim_target_list(std::int32_t index);
		void sort_aim_target_list();
		void sort_anti_aim_target_list();
		bool entity_is_valid(std::int32_t index);
		bool entity_is_visible(std::int32_t index);
		bool entity_is_friendly(std::int32_t index);
		std::float_t trace_entity_internal(structures::centity_s* entity, bool autowall, ImVec3 position);
		bool trace_entity(structures::centity_s* entity, bool autowall, std::vector<ImVec3> hitpoints, ImVec3* position, std::float_t* damage);
		bool should_scan_index(std::int32_t index);
		void draw_tab_header();
	};

	extern target_list_c target_list;
}

//=====================================================================================
