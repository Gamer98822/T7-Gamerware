//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class drawing_c
	{
	public:

		struct tracer_s
		{
			bool world_to_screen_success;
			ImVec2 hit_pos_screen, start_pos_screen;
			ImVec3 hit_pos_world, start_pos_world;
			ImVec4 hit_outline_color, hit_color, line_color;
			std::float_t hit_outline_alpha, hit_alpha, line_alpha;
			std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
		};

		std::vector<tracer_s> tracers;

		struct compass_s
		{
			std::float_t compass_size, arrow_size;
			ImVec2 compass_pos, arrow_pos[max_clients];
		} compass;

		struct radar_s
		{
			std::float_t radar_scale = 10.0f, radar_size, blip_size;
			ImVec2 radar_pos, blip_pos[max_clients];
		} radar;

		struct world_space_s
		{
			ImVec3 bones[structures::bone_max], box_corners[8], box_axis[3], box_origin, box_min, box_max, box_center;
		};

		struct screen_space_s
		{
			ImVec2 bones[structures::bone_max], box_corners[8], box_pos, box_size, lower_point, upper_point, box_center;
			std::float_t scale;
		};

		struct entities_s
		{
			bool is_visible, is_friendly, world_to_screen_success;
			ImVec4 esp_color, esp_text_color, esp_outline_color, shield_bounding_box_color, aim_pos_color, aim_pos_outline_color;
			std::string weapon_name;

			world_space_s world_space;
			screen_space_s screen_space;

			void reset()
			{
				is_visible = false;
				is_friendly = false;
				world_to_screen_success = false;
			}
		} entities[max_entities];

		void draw_border(ImVec2 position, ImVec2 dimentions, bool fill, ImVec4 col);
		void draw_border(ImVec2 corners2d[8], ImVec4 col);
		void draw_corners(ImVec2 position, ImVec2 dimentions, std::float_t length, bool fill, ImVec4 col);
		void draw_corners(ImVec2 corners2d[8], std::float_t length, ImVec4 col);
		void draw_bones(ImVec2 bones2d[structures::bone_max], ImVec4 col);
		void draw_bones(ImVec2 bones2d[structures::bone_max], ImVec4 col, ImVec4 outlinecol);
		void draw_line(ImVec2 a, ImVec2 b, ImVec4 col);
		void draw_string(std::string text, ImVec2 position, ImVec4 col, ImVec4 outlinecol);
		void draw_aim_pos(ImVec2 position, ImVec4 col, ImVec4 outlinecol);
		void draw_health_bar(structures::client_info_s* client, ImVec2 position, ImVec2 dimentions, ImVec4 col, ImVec4 outlinecol);
		void draw_client(structures::centity_s* entity, structures::client_info_s* client, ImVec2 bones2d[structures::bone_max], ImVec2 corners2d[8], ImVec2 center, std::float_t scale, std::float_t distance, ImVec4 col, ImVec4 textcol, ImVec4 outlinecol);
		void draw_entity(ImVec2 corners2d[8], std::string name, ImVec2 center, std::float_t distance, ImVec4 col, ImVec4 textcol, ImVec4 outlinecol);
		bool calculate_box(ImVec3 bones3d[structures::bone_max], ImVec2 bones2d[structures::bone_max], ImVec2* position, ImVec2* dimentions);
		bool calculate_box(structures::centity_s* entity, ImVec3 center, ImVec3 corners3d[8], ImVec2 corners2d[8]);
		void get_esp_color(std::int32_t index);
		void get_esp_text_color(std::int32_t index);
		void get_esp_outline_color(std::int32_t index);
		void get_aim_pos_color(std::int32_t index);
		void get_aim_pos_outline_color(std::int32_t index);
		void calculate_colors();
		void calculate_tracers();
		bool should_draw_index(std::int32_t index);
		bool should_skip_bone(std::int32_t index);
		void get_information();
		bool setup_world_space(std::int32_t index);
		void setup_screen_space(std::int32_t index);
		void draw_esp();
		void draw_compass();
		void draw_radar();
		void draw_cross_hair();
		void draw_tracers();
		void draw_threat_warning();
	};

	extern drawing_c drawing;
}

//=====================================================================================