//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	constexpr auto shitters_file = "Shitters.XB3";

	class shitters_c
	{
	public:

		shitters_c();
		
		enum action_flags_e
		{
			action_flag_none,
			action_flag_crash = 1 << 0,
			action_flag_migrate = 1 << 1,
			action_flag_immobilize = 1 << 2,
			action_flag_kick = 1 << 3,
			action_flag_prioritize = 1 << 4,
			action_flag_ignore = 1 << 5,
			action_flag_block_incoming = 1 << 6,
			action_flag_block_outgoing = 1 << 7,
			actions_flag_serverdisconnect = 1 << 8,
			actions_flag_autobluescreen = 1 << 9,
			action_flag_privatecrash = 1 << 10,
			action_flag_instant_popup = 1 << 11,
			action_flag_overflow = 1 <<12,
		};

		struct shitter_s
		{
			std::uint64_t xuid;
			std::string name;
			std::string last_encountered;
			std::uint32_t flags;

			structures::netadr_t netadr;

			shitter_s(std::uint64_t xuid, std::string name = "", std::string last_encountered = "Never", std::uint32_t flags = action_flag_none, structures::netadr_t netadr = {})
			{
				this->xuid = xuid;
				this->name = name;
				this->last_encountered = last_encountered;
				this->flags = flags;
				this->netadr = netadr;
			}

			shitter_s() {}
		};

		niggerware::utils::misc::timer_c shitters_timer;
		std::vector<shitter_s> shit_list;

		void refresh();
		void update();

		std::vector<shitter_s>::iterator get_if_present(const shitter_s& entry);

		bool is_present(const shitter_s& entry);
		bool is_in_session(const shitter_s& entry);

		void add(const shitter_s& entry);
		void remove(const shitter_s& entry);

		void process();

		void draw_modal_popup();
		void draw_menu_tab();

		void send_info_request(const std::uint64_t to);
		void get_info_response(const structures::InfoResponseLobby& lobby);

		structures::XSESSION_INFO get_session_info(const structures::InfoResponseLobby& lobby);
	};

	extern shitters_c shitters;
}

//=====================================================================================