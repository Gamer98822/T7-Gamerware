//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	sessions_c sessions;

	void sessions_c::refresh()
	{
		functions::LobbySearch_SearchSession(functions::get_current_lobby_session());
	}
	/*
	//=====================================================================================
	*/
	void sessions_c::draw_menu_tab()
	{
		auto& style = ImGui::GetStyle();

		if (ImGui::BeginTabItem("Servers"))
		{
			ImGui::Checkbox(configs.hide_p2p.name.c_str(), &configs.hide_p2p.current.enabled);

			ImGui::SameLine(100.0f * main_gui.scaling_factor);

			ImGui::Checkbox(configs.hide_dedi.name.c_str(), &configs.hide_dedi.current.enabled);

			ImGui::SameLine(200.0f * main_gui.scaling_factor);

			ImGui::Checkbox(configs.hide_empty.name.c_str(), &configs.hide_empty.current.enabled);

			ImGui::SameLine(300.0f * main_gui.scaling_factor);

			ImGui::Checkbox(configs.hide_full.name.c_str(), &configs.hide_full.current.enabled);

			ImGui::SameLine((ImGui::GetWindowContentRegionWidth() + style.WindowPadding.x) - (85.0f * main_gui.scaling_factor));

			if (ImGui::Button("Refresh List", { 85.0f * main_gui.scaling_factor, 0.0f })) refresh();

			ImGui::Columns(3, "SessionList");
			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);

			ImGui::Text("IP Address:"); ImGui::NextColumn();
			ImGui::Text("Steam ID:"); ImGui::NextColumn();
			ImGui::Text("Clients:"); ImGui::NextColumn();

			ImGui::PopStyleColor();

			for (auto i{ 0 }; i < max_sessions; i++)
			{
				auto item_id = niggerware::utils::string::va("session##%i", i);
				auto session = &structures::get_matchmaking_list()->session[i];

				if (!should_hide_session(session))
				{
					auto server_adr = functions::XNADDRToString(&session->hostAddress);
					auto server_xuid = session->xuid;
					auto server_clients = niggerware::utils::string::va("%u/%u", session->numPlayers, session->maxPlayers);

					auto is_current_session = niggerware::utils::memory::is_equal(&functions::get_current_lobby_session()->host.info.secId, &session->sessionID, 8);

					ImGui::Separator();
					ImGui::PushID(item_id.c_str());

					if (is_current_session)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
						ImGui::Selectable(server_adr.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
						ImGui::PopStyleColor();
					}
					else
					{
						ImGui::Selectable(server_adr.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					}

					if (ImGui::BeginPopupContextItem(item_id.c_str()))
					{
						if (ImGui::MenuItem("Join Session"))
						{
							functions::LobbyVM_JoinEvent(structures::CONTROLLER_INDEX_FIRST, server_xuid, structures::JOIN_TYPE_PARTY);
						}


						if (ImGui::MenuItem("Crash Server"))
						{

							exploits.send_instant_crash(server_xuid);

						}

						ImGui::Separator();

						if (ImGui::MenuItem("Copy IP Address"))
						{
							ImGui::LogToClipboard();
							ImGui::LogText(server_adr.c_str());
							ImGui::LogFinish();
						}

						if (ImGui::MenuItem("Copy Steam ID"))
						{
							ImGui::LogToClipboard();
							ImGui::LogText("%llu", server_xuid);
							ImGui::LogFinish();
						}

						if (ImGui::MenuItem("Copy Clients"))
						{
							ImGui::LogToClipboard();
							ImGui::LogText(server_clients.c_str());
							ImGui::LogFinish();
						}

						ImGui::EndPopup();
					} ImGui::NextColumn();

					if (is_current_session)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
						ImGui::Selectable(std::to_string(server_xuid).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
						ImGui::PopStyleColor();
					}
					else
					{
						ImGui::Selectable(std::to_string(server_xuid).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					}

					ImGui::OpenPopupOnItemClick(item_id.c_str());
					ImGui::NextColumn();

					if (is_current_session)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 1.0f, 0.3f, 1.0f });
						ImGui::Selectable(server_clients.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
						ImGui::PopStyleColor();
					}
					else
					{
						ImGui::Selectable(server_clients.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
					}

					ImGui::OpenPopupOnItemClick(item_id.c_str());
					ImGui::NextColumn();

					ImGui::PopID();
				}
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndTabItem();
		}
	}
	/*
	//=====================================================================================
	*/
	bool sessions_c::should_hide_session(structures::matchmaking_info_s* session)
	{
		if (session->is_invalid())
			return true;

		if (configs.hide_p2p.current.enabled && session->is_p2p())
			return true;

		if (configs.hide_dedi.current.enabled && session->is_dedi())
			return true;

		if (configs.hide_empty.current.enabled && session->is_empty())
			return true;

		if (configs.hide_full.current.enabled && session->is_full())
			return true;

		return false;
	}
}

//=====================================================================================