//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class anti_aim_c
	{
	public:

		ImVec3 anti_aim_angles;

		void anti_aim_all(structures::usercmd_s* usercmd);
		void anti_aim_pitch(structures::usercmd_s* usercmd, std::int32_t pitch);
		void anti_aim_yaw(structures::usercmd_s* usercmd, std::int32_t yaw);

		void apply_to_third_person_view();
		void stabilize_third_person_view_origin();

		bool ready_for_anti_aim();
	};

	extern anti_aim_c anti_aim;
}

//=====================================================================================
