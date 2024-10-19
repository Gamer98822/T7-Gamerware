//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class removals_c
	{
	public:

		void no_recoil();
		void no_spread(structures::usercmd_s* usercmd, std::uint32_t servertime);
		void no_flinch(structures::player_state_s* ps);
		void fast_reload();
		void get_spread_angles(std::uint32_t servertime, std::float_t spread, ImVec3* angles);
		void bullet_end_pos(std::uint32_t* seed, std::float_t spread, ImVec3 start, ImVec3* end, ImVec3* direction, ImVec3 axis[3], std::float_t range);
		void bullet_random_dir(std::uint32_t* seed, std::float_t* right, std::float_t* up);
		std::uint32_t transform_seed(std::uint32_t servertime);
		std::float_t get_weapon_spread();
	};

	extern removals_c removals;
}

//=====================================================================================