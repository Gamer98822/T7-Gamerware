//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class sessions_c
	{
	public:

		void refresh();
		void draw_menu_tab();

	private:

		bool should_hide_session(structures::matchmaking_info_s* session);
	};

	extern sessions_c sessions;
}

//=====================================================================================
