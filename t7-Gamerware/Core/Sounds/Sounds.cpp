//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	sounds_c sounds;

	void sounds_c::play_kill_sound()
	{
		kill_count++;

		if (kill_count == kill_sound_one)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill1.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill1.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_two)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill2.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill2.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_four)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill4.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill4.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_seven)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill7.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill7.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_eight)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill8.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill8.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_nine)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill9.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill9.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_ten)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill10.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill10.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twelve)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill12.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill12.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_fourteen)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill14.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill14.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_sixteen)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill16.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill16.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_eightteen)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill18.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill18.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twenty)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill20.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill20.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twentytwo)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill22.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill22.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twentyfour)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill24.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill24.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twentysix)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill26.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill26.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_twentyeight)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill28.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill28.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count == kill_sound_thirty)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill30.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill30.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}

		else if (kill_count > kill_sound_thirty)
		{
			if (configs.kill_sounds.current.integer == configs_c::kill_sounds_male)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Male\\Kill30+.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);

			else if (configs.kill_sounds.current.integer == configs_c::kill_sounds_female)
				PlaySound("C:\\Niggerware\\Sounds\\Kill\\Female\\Kill30+.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
		}
	}
	/*
	//=====================================================================================
	*/
	void sounds_c::play_hit_marker_sound()
	{
		PlaySound("C:\\Niggerware\\Sounds\\Hitmarker\\Hitmarker.wav", nullptr, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
	}
	/*
	//=====================================================================================
	*/
	void sounds_c::reset()
	{
		kill_count = 0;
	}
}

//=====================================================================================