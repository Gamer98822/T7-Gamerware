//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class mathematics_c
	{
	public:

		std::float_t calculate_fov(ImVec3 start, ImVec3 end, ImVec3 angles);
		std::float_t dot_product(ImVec2 vec);
		std::float_t dot_product(ImVec2 lhs, ImVec2 rhs);
		std::float_t dot_product(ImVec3 vec);
		std::float_t dot_product(ImVec3 lhs, ImVec3 rhs);
		std::float_t vector_length(ImVec2 vec);
		std::float_t vector_length(ImVec2 lhs, ImVec2 rhs);
		std::float_t vector_length(ImVec3 vec);
		std::float_t vector_length(ImVec3 lhs, ImVec3 rhs);
		std::float_t calculate_distance(ImVec3 end, ImVec3 start);
		std::float_t calculate_distance(ImVec2 end, ImVec2 start);
		ImVec3 angle_to_forward(ImVec3 position, ImVec3 angles, std::float_t distance);
		ImVec3 angle_to_right(ImVec3 position, ImVec3 angles, std::float_t distance);
		ImVec3 angle_to_up(ImVec3 position, ImVec3 angles, std::float_t distance);
		void vec_to_angles(ImVec3 direction, ImVec3* angles);
		void angles_to_axis(ImVec3 angles, ImVec3 axis[3]);
		void angle_vectors(ImVec3 angles, ImVec3* forward, ImVec3* right, ImVec3* up);
		std::float_t vector_normalize(ImVec3* direction);
		ImVec3 clamp_angles(ImVec3 angles);
		char clamp_move(std::int32_t move);
		void calculate_aim_angles(ImVec3 start, ImVec3 end, ImVec3* angles);
		void calculate_anti_aim_angles(ImVec3 start, ImVec3 end, ImVec3* angles);
		void make_vector(ImVec3 angles, ImVec3* out);
		void movement_fix(structures::usercmd_s* usercmd, std::float_t oldyaw, std::float_t newyaw, std::float_t forward, std::float_t right);
		bool world_to_screen(ImVec3 world, ImVec2* screen);
		void world_to_compass(ImVec3 world, ImVec2 compasspos, std::float_t compasssize, ImVec2* screen);
		void world_to_radar(ImVec3 world, ImVec2 radarpos, std::float_t scale, std::float_t radarsize, std::float_t blipsize, ImVec2* screen);
		void setup_box(ImVec3 corners[8], ImVec3 mins, ImVec3 maxs);
		void get_box_center(ImVec3 corners[8], ImVec3* center);
		void rotate_box(ImVec3 corners[8], ImVec3 axis[3], ImVec3 origin, ImVec3 mins, ImVec3 maxs);
		void rotate_point_yaw(ImVec3 point, ImVec3 center, std::float_t yaw, ImVec3* out);
	};

	extern mathematics_c mathematics;
}

//=====================================================================================
