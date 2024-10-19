//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class aimbot_c
	{
	public:

		struct aim_state_s
		{
			bool aim_target_acquired, anti_aim_target_acquired, is_zooming, lockon_target, is_auto_aiming, is_auto_zooming, is_auto_firing;
			std::chrono::milliseconds current_aim_time, current_aim_delay, current_zoom_delay, current_fire_delay;
			std::chrono::time_point<std::chrono::high_resolution_clock> delta_timer;
			std::int32_t aim_target_num, last_aim_target_num, anti_aim_target_num;
			ImVec3 aim_pos_world, aim_angles, anti_aim_angles;
			ImVec2 aim_pos_screen;

			void reset()
			{
				aim_target_num = -1;
				anti_aim_target_num = -1;
			}
		} aim_state;

		void standard_aim();
		void silent_aim(structures::usercmd_s* usercmd);
		void auto_fire(structures::usercmd_s* usercmd);
		void full_auto_all_weapons(structures::usercmd_s* usercmd);
		void set_aim_state();
	};

	extern aimbot_c aimbot;
}

//=====================================================================================
