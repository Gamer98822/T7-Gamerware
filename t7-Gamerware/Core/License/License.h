//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class license_c
	{
	public:

		license_c() : auth_thread(&license_c::auth_hwid, this) {}

		void auth_hwid();

		std::thread auth_thread;
	};

	extern license_c license;
}

//=====================================================================================
