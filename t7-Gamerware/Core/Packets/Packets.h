//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	class packets_c
	{
	public:

		bool is_air_stuck;

		void process_packets(structures::usercmd_s* oldcmd, structures::usercmd_s* currentcmd, structures::usercmd_s* newcmd);
		void process_packets(structures::usercmd_s* currentcmd);

		bool is_packet_choked(structures::usercmd_s* usercmd);
	};

	extern packets_c packets;
}

//=====================================================================================