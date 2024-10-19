//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class auto_wall_c
	{
	public:

		std::float_t get_bullet_damage(structures::centity_s* entity, ImVec3 start, ImVec3 end);
		std::float_t trace_bullet(structures::centity_s* entity, ImVec3 start, ImVec3 end);
		std::float_t get_remaining_damage(structures::BulletFireParams* bp, structures::BulletTraceResults* br, std::int64_t weapon);
	};

	extern auto_wall_c auto_wall;
}

//=====================================================================================
