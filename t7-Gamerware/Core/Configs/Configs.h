//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class configs_c
	{
	public:

		configs_c();

		enum cvar_type_e
		{
			cvar_type_bool,
			cvar_type_int,
			cvar_type_float,
			cvar_type_string,
			cvar_type_color,
		};

		struct cvar_value_s
		{
			bool enabled;
			std::int32_t integer;
			std::float_t value;
			std::string string;
			ImVec4 color;

			cvar_value_s()
			{
				this->enabled = false;
				this->integer = 0;
				this->value = 0.0f;
				this->string = "";
				this->color = { 0.0f, 0.0f, 0.0f, 0.0f };
			}

			~cvar_value_s() {}
		};

		struct cvar_limits_s
		{
			struct
			{
				std::int32_t min;
				std::int32_t max;
			} integer;

			struct
			{
				std::float_t min;
				std::float_t max;
			} value;

			cvar_limits_s()
			{
				this->integer.min = 0;
				this->integer.max = 0;

				this->value.min = 0.0f;
				this->value.max = 0.0f;
			}

			~cvar_limits_s() {}
		};

		struct cvar_step_s
		{
			std::int32_t integer;
			std::float_t value;

			cvar_step_s()
			{
				this->integer = 1;
				this->value = 1.0f;
			}

			~cvar_step_s() {}
		};

		struct cvar_s
		{
			std::string name;
			std::string format;
			std::vector<std::string> items;

			cvar_type_e type;
			cvar_value_s current, reset;
			cvar_limits_s domain;
			cvar_step_s step;

			cvar_s() {}

			cvar_s(const std::string& name, const std::string& format, const std::vector<std::string>& items, const cvar_type_e type, const cvar_value_s& value, const cvar_limits_s& domain, const cvar_step_s& step)
			{
				this->name = name;
				this->format = format;
				this->items = items;
				this->type = type;
				this->current = value;
				this->reset = value;
				this->domain = domain;
				this->step = step;
			}

			~cvar_s() {}
		};

		struct config_list_s
		{
			char new_config_name[MAX_PATH] = { 0 };

			std::int32_t config_selection;
			std::vector<std::string> config_files;

			auto set_config_selection()
			{
				for (auto i{ 0u }; i < config_files.size(); i++)
				{
					auto is_selected = (config_selection == i);

					if (ImGui::Selectable(config_files[i].c_str(), is_selected))
					{
						config_selection = i;
					}
				}
			}

			auto get_config_selection()
			{
				return config_files[config_selection];
			}
		} config_list;

		enum aimbot_mode_e
		{
			aimbot_mode_off,
			aimbot_mode_manual,
			aimbot_mode_auto,
			aimbot_mode_max
		};

		enum sort_algorithm_e
		{
			sort_algorithm_distance,
			sort_algorithm_damage,
			sort_algorithm_fov,
			sort_algorithm_max
		};

		enum kill_sounds_e
		{
			kill_sounds_off,
			kill_sounds_male,
			kill_sounds_female,
			kill_sounds_max
		};

		enum anti_aim_pitch_e
		{
			anti_aim_pitch_off,
			anti_aim_pitch_zero,
			anti_aim_pitch_up,
			anti_aim_pitch_down,
			anti_aim_pitch_jitter,
			anti_aim_pitch_random,
			anti_aim_pitch_reverse,
			anti_aim_pitch_custom,
			anti_aim_pitch_max
		};

		enum anti_aim_yaw_e
		{
			anti_aim_yaw_off,
			anti_aim_yaw_spin,
			anti_aim_yaw_jitter,
			anti_aim_yaw_random,
			anti_aim_yaw_reverse,
			anti_aim_yaw_custom,
			anti_aim_yaw_max
		};

		enum bone_scan_e
		{
			bone_scan_off,
			bone_scan_priorities_only,
			bone_scan_everyone,
			bone_scan_max
		};

		enum esp_hack_mode_e

		{
			esp_mode_off,
			esp_mode_axis,
			esp_mode_allies,
			esp_mode_full,
			esp_mode_max
		};

		enum esp_boxes_e
		{
			esp_boxes_off,
			esp_boxes_border,
			esp_boxes_corner,
			esp_boxes_border_filled,
			esp_boxes_corner_filled,
			esp_boxes_border_3d,
			esp_boxes_corner_3d,
			esp_boxes_max
		};

		enum esp_bones_e
		{
			esp_bones_off,
			esp_bones_dots,
			esp_bones_lines,
			esp_bones_max
		};

		enum esp_snap_lines_e
		{
			esp_snap_lines_off,
			esp_snap_lines_top,
			esp_snap_lines_center,
			esp_snap_lines_bottom,
			esp_snap_lines_alternating_1,
			esp_snap_lines_alternating_2,
			esp_snap_lines_max
		};

		enum esp_entities_e
		{
			esp_entities_off,
			esp_entities_info,
			esp_entities_border_3d,
			esp_entities_corner_3d,
			esp_entities_max
		};

		enum give_currency_e
		{
			give_currency_off,
			give_currency_crypto_keys,
			give_currency_liquid_divinium,
			give_currency_max
		};

		enum spend_currency_e
		{
			spend_currency_off,
			spend_currency_crypto_keys,
			spend_currency_liquid_divinium,
			spend_currency_max
		};

		cvar_s aimbot_mode;

		cvar_s auto_zoom;
		cvar_s auto_fire;
		cvar_s auto_wall;
		cvar_s silent_aim;

		cvar_s sort_algorithm_targets;
		cvar_s sort_algorithm_bones;
		cvar_s kill_sounds;
		cvar_s hit_marker_sounds;
		cvar_s multi_threading;

		cvar_s no_recoil;
		cvar_s no_spread;
		cvar_s no_flinch;
		cvar_s quick_reload;

		cvar_s anti_aim_pitch_default;
		cvar_s anti_aim_yaw_default;
		cvar_s anti_aim_pitch_on_sprint;
		cvar_s anti_aim_yaw_on_sprint;
		cvar_s anti_aim_pitch_on_target;
		cvar_s anti_aim_yaw_on_target;
		cvar_s anti_aim_spin_speed;
		cvar_s anti_aim_shield_pitch_shift;
		cvar_s anti_aim_shield_yaw_shift;
		cvar_s anti_aim_custom_pitch;
		cvar_s anti_aim_custom_yaw;

		cvar_s target_actors;
		cvar_s target_vehicles;
		cvar_s target_helicopters;

		cvar_s bones_inclusion;
		cvar_s bones_selection;

		cvar_s esp_mode;

		cvar_s esp_boxes;
		cvar_s esp_bones;
		cvar_s esp_snap_lines;
		cvar_s esp_entities;
		cvar_s esp_distances;
		cvar_s esp_names;
		cvar_s esp_weapons;
		cvar_s esp_health_bars;
		cvar_s esp_aim_pos;
		cvar_s esp_cross_hair;
		cvar_s esp_bullet_tracers;
		cvar_s esp_threat_warning;

		cvar_s esp_compass;
		cvar_s esp_radar;

		cvar_s color_axis_visible;
		cvar_s color_axis_visible_text;
		cvar_s color_axis_visible_outline;
		cvar_s color_axis_occluded;
		cvar_s color_axis_occluded_text;
		cvar_s color_axis_occluded_outline;
		cvar_s color_allies_visible;
		cvar_s color_allies_visible_text;
		cvar_s color_allies_visible_outline;
		cvar_s color_allies_occluded;
		cvar_s color_allies_occluded_text;
		cvar_s color_allies_occluded_outline;
		cvar_s color_entities;
		cvar_s color_entities_text;
		cvar_s color_entities_outline;
		cvar_s color_aimbot_target;
		cvar_s color_aimbot_target_text;
		cvar_s color_aimbot_target_outline;
		cvar_s color_anti_aim_target;
		cvar_s color_anti_aim_target_text;
		cvar_s color_anti_aim_target_outline;
		cvar_s color_prioritized;
		cvar_s color_prioritized_text;
		cvar_s color_prioritized_outline;
		cvar_s color_aim_pos;
		cvar_s color_aim_pos_outline;
		cvar_s color_cross_hair;
		cvar_s color_tracer_line;
		cvar_s color_tracer_hit;
		cvar_s color_tracer_hit_outline;
		cvar_s color_threat_warning;

		cvar_s third_person;
		cvar_s full_auto_all_weapons;
		cvar_s perma_hatr;

		cvar_s aim_bone;
		cvar_s aim_angle;
		cvar_s aim_power;
		cvar_s min_damage;
		cvar_s fire_rate_limiter;
		cvar_s auto_aim_time;
		cvar_s auto_aim_delay;
		cvar_s auto_zoom_delay;
		cvar_s auto_fire_delay;
		cvar_s fake_lag;
		cvar_s third_person_hotkey;
		cvar_s air_stuck_hotkey;

		cvar_s change_name;
		cvar_s change_clan;

		cvar_s give_currency;
		cvar_s spend_currency;
		cvar_s burn_duplicates;
		cvar_s spoof_all_dlc_items;
		cvar_s spoof_xuid;
		cvar_s kill_spam;
		cvar_s chat_spam;
		cvar_s vote_spam;
		cvar_s join_by_steam_id;
		cvar_s crash_by_steam_id;
		cvar_s popup_by_steam_id;

		cvar_s cbuf_add_text;
		cvar_s cl_add_reliable_command;
		cvar_s sv_game_send_server_command;
		cvar_s dvar_set_from_string_by_name;

		cvar_s hide_p2p;
		cvar_s hide_dedi;
		cvar_s hide_empty;
		cvar_s hide_full;

		std::vector<std::pair<configs_c::cvar_s*, ImVec3>> rgb_colors;

		bool save(const std::string& name);
		bool load(const std::string& name);

		void draw_menu_tab();

		cvar_s add_bool(const std::string& name, const bool value);
		cvar_s add_int(const std::string& name, const std::vector<std::string>& items, const std::int32_t value, const std::int32_t min = std::numeric_limits<std::int32_t>::min(), const std::int32_t max = std::numeric_limits<std::int32_t>::max(), const std::int32_t step = 1, const std::string& format = "");
		cvar_s add_float(const std::string& name, const std::float_t value, const std::float_t min = std::numeric_limits<std::float_t>::min(), const std::float_t max = std::numeric_limits<std::float_t>::max(), const std::float_t step = 1.0f, const std::string& format = "");
		cvar_s add_string(const std::string& name, const std::string& value);
		cvar_s add_color(const std::string& name, const ImVec4& value, const std::float_t speed = 0.0f, const std::float_t minspeed = 0.0f, const std::float_t maxspeed = 1000.0f);
	};

	extern configs_c configs;
}

//=====================================================================================
