//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class sounds_c
	{
	public:

		enum kill_sounds_e
		{
			kill_sound_one = 1,
			kill_sound_two = 2,
			kill_sound_four = 4,
			kill_sound_seven = 7,
			kill_sound_eight = 8,
			kill_sound_nine = 9,
			kill_sound_ten = 10,
			kill_sound_twelve = 12,
			kill_sound_fourteen = 14,
			kill_sound_sixteen = 16,
			kill_sound_eightteen = 18,
			kill_sound_twenty = 20,
			kill_sound_twentytwo = 22,
			kill_sound_twentyfour = 24,
			kill_sound_twentysix = 26,
			kill_sound_twentyeight = 28,
			kill_sound_thirty = 30
		};

		void play_kill_sound();
		void play_hit_marker_sound();
		void reset();

	private:

		std::int32_t kill_count = 0;
	};

	extern sounds_c sounds;
}

//=====================================================================================