//=====================================================================================

#include "../StdAfx.hpp"

//=====================================================================================
bool aimbot_enabled = false;

namespace RCE
{

	std::map< int, std::string> log_s = {};

	static char logInput[255] = "";

	void AddToLog(std::string output)
	{
		log_s[(int)log_s.size() + 1] = output.c_str();

	}

}
#define OFFSET(x) ((INT64)GetModuleHandle(NULL) + (INT64)x)
#define s_UserDataForControllerMap OFFSET(0x340F180)



namespace t7
{
	

	main_gui_c main_gui;

	Present_t Present_o;
	ResizeBuffers_t ResizeBuffers_o;

	void main_gui_c::init()
	{
		auto present_hk_sig = niggerware::utils::memory::scan_pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 41 8B E8", "GameOverlayRenderer64.dll");
		auto create_hk_sig = niggerware::utils::memory::scan_pattern("48 89 5C 24 ? 57 48 83 EC ? 33 C0 48 89 44 24", "GameOverlayRenderer64.dll");

		__int64(__fastcall * CreateHook)(
			unsigned __int64 pFuncAddress,
			__int64 pDetourFuncAddress,
			unsigned __int64* pOriginalFuncAddressOut,
			int a4);

		CreateHook = (decltype(CreateHook))create_hk_sig;
		CreateHook(present_hk_sig, (__int64)&Present_h, (unsigned __int64*)&Present_o, 1);
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::free()
	{
		niggerware::utils::hook::detach(Present_o, Present_h);
		niggerware::utils::hook::detach(ResizeBuffers_o, ResizeBuffers_h);

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::setup_imgui()
	{
		if (get_view_port().x && get_view_port().y)
		{
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(swap_chain_desc.OutputWindow);
			ImGui_ImplDX11_Init(renderer_device, renderer_device_context);

			auto& io = ImGui::GetIO();
			auto& style = ImGui::GetStyle();

			io.IniFilename = default_ini.c_str();
			io.LogFilename = default_log.c_str();

			scaling_factor = get_view_port().y / 1080.0f;

			tahoma_size = scaling_factor * 13.0f;
			bank_gothic_pro_light_size = scaling_factor * 13.0f;
			eurostile_extended_size = scaling_factor * 18.0f;

			tahoma = io.Fonts->AddFontDefault(bank_gothic_pro_light_size);
			style.ScaleAllSizes(scaling_factor);

			ImGui::MergeIconsWithLatestFont(tahoma_size);

			bank_gothic_pro_light = io.Fonts->AddFontFromMemoryCompressedBase85TTF(bank_gothic_pro_light_otf_compressed_data_base85, bank_gothic_pro_light_size);
			eurostile_extended = io.Fonts->AddFontFromMemoryCompressedBase85TTF(eurostile_extended_compressed_data_base85, eurostile_extended_size);

			drawing.compass.compass_size = 720.0f * scaling_factor;
			drawing.compass.arrow_size = 27.0f * scaling_factor;

			drawing.radar.radar_size = 200.0f * scaling_factor;
			drawing.radar.blip_size = 8.0f * scaling_factor;

			initialized = true;
		}
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::device_from_swap(IDXGISwapChain* pSwapChain)
	{
		std::lock_guard<std::mutex> lg(lock);

		pSwapChain->GetDevice(IID_PPV_ARGS(&renderer_device));
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::device_context_from_swap(IDXGISwapChain* pSwapChain)
	{
		std::lock_guard<std::mutex> lg(lock);

		if (SUCCEEDED(pSwapChain->GetDevice(IID_PPV_ARGS(&renderer_device))))
		{
			renderer_device->GetImmediateContext(&renderer_device_context);
		}
	}
	/*
	//=====================================================================================
	*/
	char custom_class[32] = { 0 };

	std::string gamertag(custom_class);


	void main_gui_c::create_render_target_view(IDXGISwapChain* pSwapChain)
	{
		std::lock_guard<std::mutex> lg(lock);

		ID3D11Texture2D* back_buffer = nullptr;

		if (SUCCEEDED(pSwapChain->GetBuffer(0, IID_PPV_ARGS(&back_buffer))))
		{
			if (SUCCEEDED(renderer_device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view)))
			{
				device_objects.push_back(render_target_view);
			}

			back_buffer->Release();
		}
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::get_swap_chain_desc(IDXGISwapChain* pSwapChain)
	{
		std::lock_guard<std::mutex> lg(lock);

		pSwapChain->GetDesc(&swap_chain_desc);
	}
	/*
	//=====================================================================================
	*/
	ImVec2 main_gui_c::get_view_port()
	{
		RECT rect;

		GetWindowRect(swap_chain_desc.OutputWindow, &rect);

		return { std::stcast<std::float_t>(rect.right - rect.left), std::stcast<std::float_t>(rect.bottom - rect.top) };
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::release_objects()
	{
		std::lock_guard<std::mutex> lg(lock);

		for (auto& device_object : device_objects)
		{
			device_object->Release();
		}

		device_objects.clear();
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::invalidate()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_InvalidateDeviceObjects();

		initialized = false;
	}
	/*
	//=====================================================================================
	*/
	INT64 spoofedXUID;
	INT64 cacheXUID;



	inline void Spoof_Xuid(bool isSpoofed)
	{

		if (isSpoofed)
		{
			if (!spoofedXUID)
			{
				return;
			}
			**(__int64**)s_UserDataForControllerMap = spoofedXUID;
			return;
		}
		**(__int64**)s_UserDataForControllerMap = cacheXUID;



	}


	void main_gui_c::update_colors()
	{
		auto& io = ImGui::GetIO();

		for (auto& color_var : configs.rgb_colors)
		{
			if (color_var.first->current.value > 0.0f && io.Framerate > 0.0f)
			{
				ImGui::ColorConvertRGBtoHSV(color_var.first->current.color.x, color_var.first->current.color.y, color_var.first->current.color.z, color_var.second.x, color_var.second.y, color_var.second.z);

				color_var.second.x += 0.001f * (color_var.first->current.value / io.Framerate);

				ImGui::ColorConvertHSVtoRGB(color_var.second.x, color_var.second.y, color_var.second.z, color_var.first->current.color.x, color_var.first->current.color.y, color_var.first->current.color.z);
			}

			else
			{
				color_var.second.x = 0.0f;
			}
		}
	}
	/*
	//=====================================================================================
	*/





	


	void main_gui_c::draw_main_gui()
	{
		auto& io = ImGui::GetIO();
		auto& style = ImGui::GetStyle();

		io.MouseDrawCursor = show_window;

		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
		ImGui::NewFrame();
		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double>elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);






		


		ImGui::SetNextWindowPos({ 15, 15 });
		ImGui::SetNextWindowSize({ 320, 60 });
		ImGui::Begin("XB3", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		{

			ImGui::Text("T7 - Gamerware | %s", std::ctime(&end_time));
			ImGui::Text("FPS:");

			ImGui::SameLine();			
			ImGui::Text( "%.0f", io.Framerate);
		
			//io.Framerate


			ImGui::End();
		}
		ImGui::SetNextWindowPos({ 1750, 15 });
		ImGui::SetNextWindowSize({ 150, 30 });
		ImGui::Begin("F1", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		{


			ImGui::Text("Press F1 To Open");


			ImGui::End();
		}



		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(io.DisplaySize);

		ImGui::Begin("##Invisible", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
		ImGui::GetWindowDrawList()->PushClipRectFullScreen();

		ImGui::PopStyleColor(2);

		if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
		{
			drawing.draw_esp();
			drawing.draw_compass();
			drawing.draw_radar();
			drawing.draw_cross_hair();
			drawing.draw_tracers();
			drawing.draw_threat_warning();
		}

		auto shadow_color = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

		

		

		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game())
			{
			
			
			}
		}

	//	auto frames_per_second_text(niggerware::utils::string::va("%.0f", io.Framerate));
	//	auto frames_per_second_size(eurostile_extended->CalcTextSizeA(eurostile_extended_size, std::numeric_limits<std::float_t>::max(), 0.0f, frames_per_second_text.c_str()));
	//	auto frames_per_second_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 0.3f, 1.0f));

	//	ImGui::GetWindowDrawList()->AddText(eurostile_extended, eurostile_extended_size,
	//		ImVec2(io.DisplaySize.x - frames_per_second_size.x - frames_per_second_size.y + 1.0f, eurostile_extended_size - frames_per_second_size.y + 1.0f),
	//		shadow_color, frames_per_second_text.c_str());

	//	ImGui::GetWindowDrawList()->AddText(eurostile_extended, eurostile_extended_size,
	//		ImVec2(io.DisplaySize.x - frames_per_second_size.x - frames_per_second_size.y, eurostile_extended_size - frames_per_second_size.y),
	//		frames_per_second_color, frames_per_second_text.c_str());

		ImGui::End();

		



		


		if (show_window)
		{
			ImGui::SetNextWindowSize({ 400, 400 });

			if (ImGui::Begin(" Exception Logger"))
			{


				ImGui::BeginChild("ContentRegion", ImVec2(0.0f, 302.0f), true);
				{
					ImGui::Indent(3);
					for (const auto& text : RCE::log_s)
					{
					ImGui::TextDisabled(text.second.c_str());
					if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
					{
						ImGui::SetScrollHereY(1.0f);
					}
				}
					ImGui::EndChild();
				}

				ImGui::End();
			}
			
			ImGui::SetNextWindowPos({ 15, 415 });
			ImGui::SetNextWindowSize({ 500, 400 });

			if (ImGui::Begin("Gamer9882's Exploit Menu"))
			{

				ImGui::BeginTabBar("##exploit");

				
				if (ImGui::BeginTabItem("Players"))
				{
					ImGui::Columns(3, "PlayerList"); //used to be 2 colums
					ImGui::Separator();

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);

					ImGui::Text("Name:"); ImGui::NextColumn();
					ImGui::Text("Network IP:"); ImGui::NextColumn();


					ImGui::Text("Steam ID:"); ImGui::NextColumn();

					ImGui::PopStyleColor();

					auto local_client_num = functions::get_client_num(functions::get_our_xuid());
					auto hostBs = t7::functions::host_bullshit(1);
					long long hostxuid = *(__int64*)(hostBs);
					t7::structures::netadr_t hostNetAddr = *(t7::structures::netadr_t*)(hostBs + 0x28);
					for (auto i = 0; i < max_clients; i++)
					{
						if (auto session_client{ functions::get_session_client(i) }; session_client && session_client->activeClient)
						{
							auto client_name = functions::get_client_name(i);
							auto client_ip = functions::get_ip_address(i);
							auto client_xuid = functions::get_client_xuid(i);

							ImGui::Separator();
							ImGui::PushID(i);

							if (functions::is_in_game())
							{
								ImVec4 team_color;
								functions::BG_FactionData_GetTeamColor(structures::LOCAL_CLIENT_FIRST, functions::get_cg()->clientInfo[i].team, &team_color, false);

								ImGui::PushStyleColor(ImGuiCol_Text, team_color);
								ImGui::Selectable(client_name.c_str(), &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
								ImGui::PopStyleColor();
							}

							else
							{
								ImGui::Selectable(client_name.c_str(), &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
							}

							if (steam.friends)
							{
								auto steam_name = steam.friends->GetFriendPersonaName(client_xuid);

								if (steam_name && steam_name[0] && niggerware::utils::string::is_not_equal(steam_name, client_name) && niggerware::utils::string::is_not_equal(steam_name, "[unknown]"))
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
									ImGui::Selectable(niggerware::utils::string::va("(%s)", steam_name).c_str(), &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}
							}

							if (local_client_num == i)
							{
								ImGui::SameLine();
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 1.0f, 0.3f, 1.0f));
								ImGui::Selectable("[YOU]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
								ImGui::PopStyleColor();
							}

							if (functions::is_client_num_host(i))
							{
								ImGui::SameLine();
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
								ImGui::Selectable("[Host]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
								ImGui::PopStyleColor();
							}

							if (steam.friends)
							{
								if (steam.friends->GetFriendRelationship(client_xuid) == EFriendRelationship::k_EFriendRelationshipFriend)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 1.0f, 1.0f));
									ImGui::Selectable("[Friend]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}
							}

							if (auto shitter{ shitters.get_if_present({ client_xuid }) }; shitter != shitters.shit_list.end())
							{
								ImGui::SameLine();
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
								ImGui::Selectable("[In Database]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
								ImGui::PopStyleColor();

								if (shitter->flags & shitters_c::action_flag_crash)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Crash]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}

								if (shitter->flags & shitters_c::action_flag_migrate)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Migrate]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}

								if (shitter->flags & shitters_c::action_flag_immobilize)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Immobilize]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}

								if (shitter->flags & shitters_c::action_flag_kick)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Kick]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}

								if (shitter->flags & shitters_c::action_flag_prioritize)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Prioritize]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}

								if (shitter->flags & shitters_c::action_flag_ignore)
								{
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
									ImGui::Selectable("[Ignore]", &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
									ImGui::PopStyleColor();
								}
							}

							if (ImGui::BeginPopupContextItem(std::to_string(i).c_str()))
							{
								if (ImGui::MenuItem("Add To Database"))
								{
									shitters.add({ client_xuid, client_name, niggerware::utils::misc::get_current_time() });
								}

								if (ImGui::MenuItem("View Profile"))
								{
									functions::LiveSteam_PopOverlayForSteamID(client_xuid);

									show_window = false;
								}

								ImGui::Separator();

								
								
								
								if (ImGui::BeginMenu("Client Exploits", functions::can_i_talk_to_peer(i)))
								{
								
									
									
									
									if (ImGui::BeginMenu("Crashes"))
									{
										if (ImGui::MenuItem("InstantMSG"))
										{
											exploits.send_instant_crash(i);

										}
										if (ImGui::MenuItem("Relay Crash"))
										{
											exploits.send_relay_crash(i);

										}
										if (ImGui::MenuItem("Voice Relay Crash"))
										{
											exploits.send_voice_relay_packet_crash(i);

										}

										if (ImGui::MenuItem("Voice Packet Crash"))
										{
											exploits.send_voice_packet_crash(i);

										}

										if (ImGui::MenuItem("Voice Test Crash"))
										{
											exploits.send_vt_crash(i);

										}
										if (ImGui::MenuItem("Modified Stats Crash"))
										{
											exploits.send_modified_stats_crash(i);



										}
										

										if (ImGui::MenuItem("LSG Crash (Test)"))
										{
											exploits.send_lsgame_crash(hostNetAddr, client_xuid);


										}

										if (ImGui::MenuItem("Send All Crashes"))
										{

											exploits.send_all_crashes(i);


										}



										

										ImGui::EndMenu();

      								}

									if (ImGui::BeginMenu("Errors"))
									{
										if (ImGui::MenuItem("InstantMSG"))
										{
											exploits.send_instant_popup(i);

										}
										if (ImGui::MenuItem("ZM Ui Error"))
										{
											exploits.SendZM_UI_ERROR(client_xuid, hostNetAddr);

										}


										ImGui::EndMenu();

									}
									if (ImGui::BeginMenu("Kicks"))
									{
										if (ImGui::MenuItem("Host Disconnect Kick"))
										{
											exploits.send_disconnect_kick(i);

											
										}

										if (ImGui::MenuItem("NoPartyChat3 Kick"))
										{
											exploits.SendNOPARTYCHAT3(client_xuid, hostNetAddr);


										}

										if (ImGui::MenuItem("Migration Kick"))
										{
											exploits.send_migration_kick(i);

										}






										ImGui::EndMenu();

									}


									if (ImGui::BeginMenu("Misc"))
									{
										
										
										
										if (ImGui::MenuItem("Server Disconnect"))
										{
											exploits.Send_Client_Disconnect(hostNetAddr, hostxuid, client_xuid);



										}

										if (ImGui::MenuItem("Immobilize"))
										{
											exploits.send_immobilization_screen(i);

										}


										if (ImGui::MenuItem("ZM Blue Screen"))
										{
											exploits.SendBADDLC(client_xuid, hostNetAddr);


										}

									ImGui::EndMenu();

									}

									
								



									ImGui::EndMenu();
								}

								
								



								ImGui::Separator();

								ImGui::MenuItem("Ignore Player", nullptr, &target_list.priorities[i].is_ignored);

								ImGui::Separator();

								if (ImGui::MenuItem("Copy Name"))
								{
									ImGui::LogToClipboard();
									ImGui::LogText(client_name.c_str());
									ImGui::LogFinish();
								}

								if (ImGui::MenuItem("Copy IP Address"))
								{
									ImGui::LogToClipboard();
									ImGui::LogText(client_ip.to_string().c_str());
									ImGui::LogFinish();
								}

								if (ImGui::MenuItem("Copy Steam ID"))
								{
									ImGui::LogToClipboard();
									ImGui::LogText("%llu", client_xuid);
									ImGui::LogFinish();
								}

								ImGui::EndPopup();
							} ImGui::NextColumn();

							ImGui::Selectable(client_ip.to_string().c_str(), &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
							ImGui::OpenPopupOnItemClick(std::to_string(i).c_str());
							ImGui::NextColumn();

							ImGui::Selectable(std::to_string(client_xuid).c_str(), &target_list.priorities[i].is_prioritized, ImGuiSelectableFlags_SpanAllColumns);
							ImGui::OpenPopupOnItemClick(std::to_string(i).c_str());
							ImGui::NextColumn();

							ImGui::PopID();
						}
					}

					ImGui::Columns(1);
					ImGui::Separator();



					ImGui::EndTabItem();
				}


				
				if (ImGui::BeginTabItem("Exploits"))
				{

				
					
					
					
					
					
					
					
					
					ImGui::Text("Server Exploits");
					if (ImGui::Button("End Round", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						functions::end_round();
					}
					ImGui::SameLine();

					if (ImGui::Button("Loadside", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						functions::loadside_server();
					}
					ImGui::SameLine();

					if (ImGui::Button("SL Server", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						functions::disconnect_server();
					}
					ImGui::SameLine();

					if (ImGui::Button("Crash Server", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						functions::crash_server();
					}


					ImGui::Text("Client Crashes");

					if (ImGui::Button("Crash All", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						for (auto i = 0; i < max_clients; i++)
						{
							exploits.send_all_crashes(i);
						}


					}
					ImGui::SameLine();

					if (ImGui::Button("Popup All", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						for (auto i = 0; i < max_clients; i++)
						{
							exploits.send_instant_popup(i);
						}
					}					ImGui::SameLine();


					if (ImGui::Button("Migrate All", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						for (auto i = 0; i < max_clients; i++)
						{
							exploits.send_migration_screen(i);
						}
					}				
					ImGui::SameLine();


					if (ImGui::Button("Immobilize All", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						for (auto i = 0; i < max_clients; i++)
						{
							exploits.send_immobilization_screen(i);
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("Kick All", ImVec2(80.0f, 0.0f) * scaling_factor))
					{
						for (auto i = 0; i < max_clients; i++)
						{
							exploits.send_all_kicks(i);
						}
					}





					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.join_by_steam_id.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##join", text_buffers.join_by_steam_id, sizeof(text_buffers.join_by_steam_id), ImGuiInputTextFlags_CharsUnsigned | ImGuiInputTextFlags_CharsNoBlank))
					{
						configs.join_by_steam_id.current.string = text_buffers.join_by_steam_id;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##4"))
					{
						functions::LobbyVM_JoinEvent(structures::CONTROLLER_INDEX_FIRST, niggerware::utils::string::stoll(configs.join_by_steam_id.current.string), structures::JOIN_TYPE_PARTY);
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.crash_by_steam_id.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##crash", text_buffers.crash_by_steam_id, sizeof(text_buffers.crash_by_steam_id), ImGuiInputTextFlags_CharsUnsigned | ImGuiInputTextFlags_CharsNoBlank))
					{
						configs.crash_by_steam_id.current.string = text_buffers.crash_by_steam_id;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##5"))
					{
						exploits.send_instant_crash(std::vector<std::uint64_t>{ niggerware::utils::string::stoull(configs.crash_by_steam_id.current.string) });
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.popup_by_steam_id.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##popup", text_buffers.popup_by_steam_id, sizeof(text_buffers.popup_by_steam_id), ImGuiInputTextFlags_CharsUnsigned | ImGuiInputTextFlags_CharsNoBlank))
					{
						configs.popup_by_steam_id.current.string = text_buffers.popup_by_steam_id;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##6"))
					{
						exploits.send_instant_popup(std::vector<std::uint64_t>{ niggerware::utils::string::stoull(configs.popup_by_steam_id.current.string) });
					}








					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Stats"))
				{
					if (ImGui::Button("Make Public Match"))
					{
						functions::set_network_mode_online();
					}
					ImGui::SameLine();
					if (ImGui::Button("Fix Crypto"))
					{
						stats.fix_pending_loot();
					}



					if (ImGui::Button("Disconnect"))
					{
						functions::disconnect();
					}
					ImGui::SameLine();
					if (ImGui::Button("Quit"))
					{
						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "quit");

					}



					if (ImGui::Button("Reset Stats"))
					{
						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "PrestigeStatsResetAll; ClearCustomLeaderboards; PrestigeStatsReset; StarterPackPrestigeReset; statsetbyname PrestigeStatsResetAll PLEVEL; statsetbyname PrestigeStatsResetAll PLEVEL RANKXP");



					}


					if (ImGui::Button("Prestige Master"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, " statsetbyname PLEVEL 11; statsetbyname RANKXP 14570200; statsetbyname PARAGON_RANKXP 52542000; uploadstats; updategamerprofile;");

					}
					ImGui::SameLine();
					if (ImGui::Button("Modded Prestige"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "statsetbyname PLEVEL 12; uploadstats; updategamerprofile;");

					}
					ImGui::SameLine();
					if (ImGui::Button("Prestige 15"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "statsetbyname PLEVEL 15; uploadstats; updategamerprofile;");

					}
					
					ImGui::SameLine();
					if (ImGui::Button("Prestige 1337"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "statsetbyname PLEVEL 1337; uploadstats; updategamerprofile;");

					}
					ImGui::SameLine();
					if (ImGui::Button("Prestige 9882"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "statsetbyname PLEVEL 9882; uploadstats; updategamerprofile;");

					}
					if (ImGui::Button("Level 55"))
					{

						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "statsetbyname statsetbyname RANKXP 14570200; statsetbyname PARAGON_RANKXP 52542000; uploadstats; updategamerprofile;");

					}
					// statsetbyname PLEVEL 12; uploadstats; updategamerprofile;



					
					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.change_name.name.c_str());
					ImGui::PopStyleColor();

					ImGui::InputText("##name", text_buffers.change_name, sizeof(text_buffers.change_name));
					ImGui::SameLine();
					if (ImGui::Button("Execute##1"))
					{
						configs.change_name.current.string = text_buffers.change_name;
						hooks.set_name(functions::parse_place_holders(configs.change_name.current.string));


					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.change_clan.name.c_str());
					ImGui::PopStyleColor();

					ImGui::InputText("##clan", text_buffers.change_clan, sizeof(text_buffers.change_clan), ImGuiInputTextFlags_CharsNoBlank);
					ImGui::SameLine();
					if (ImGui::Button("Execute##2"))
					{
						configs.change_clan.current.string = text_buffers.change_clan;
						functions::LiveStats_SetClanTagText(structures::CONTROLLER_INDEX_FIRST, configs.change_clan.current.string.c_str());
					}

				

					

					if (ImGui::Button("Spoof To Shiny's XUID"))
					{
						spoofedXUID = _atoi64("76561199174887921");
						Spoof_Xuid(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Spoof To Gamer's XUID"))
					{
						spoofedXUID = _atoi64("76561198988449136");
						Spoof_Xuid(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Spoof To lergy's XUID"))
					{
						spoofedXUID = _atoi64("76561198120173385");
						Spoof_Xuid(true);
					}
					
					if (ImGui::Button("Spoof To XBOX360LSBEST's XUID"))
					{
						spoofedXUID = _atoi64("76561198331947611");
						Spoof_Xuid(true);
					}
					
					if (ImGui::Button("Spoof XUID"))
					{
						spoofedXUID = _atoi64("76561198331947611");
						Spoof_Xuid(true);
					}


					ImGui::EndTabItem();
				}


				sessions.draw_menu_tab();


				
				
				ImGui::EndTabBar();
				ImGui::End();
			}
			
			
			
			
			
			
			ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f) * scaling_factor);
			ImGui::Begin(program_name, &show_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

			if (ImGui::BeginTabBar("TabRegion"))
			{
				if (ImGui::BeginTabItem("Aimbot"))
				{
					ImGui::Combo(configs.aimbot_mode.name.c_str(), &configs.aimbot_mode.current.integer, niggerware::utils::string::concatenate(configs.aimbot_mode.items).c_str());

					ImGui::Checkbox("Aimbot", &aimbot_enabled);
				

					if (aimbot_enabled)
					{
						
						//no recoil
						configs.no_recoil.name.c_str(), & configs.no_recoil.current.enabled;
						configs.no_spread.name.c_str(), & configs.no_spread.current.enabled;



					}
					
					// &configs.auto_fire.current.enabled, &configs.silent_aim.current.enabled, &configs.auto_wall.current.enabled, &configs.no_recoil.current.enabled, &configs.no_spread.current.enabled, &configs.no_flinch.current.enabled, &configs.aimbot_mode.current.integer
					ImGui::Checkbox(configs.auto_zoom.name.c_str(), &configs.auto_zoom.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.auto_fire.name.c_str(), &configs.auto_fire.current.enabled);

					ImGui::Checkbox(configs.auto_wall.name.c_str(), &configs.auto_wall.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.silent_aim.name.c_str(), &configs.silent_aim.current.enabled);

					

					ImGui::Checkbox(configs.no_recoil.name.c_str(), &configs.no_recoil.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.no_spread.name.c_str(), &configs.no_spread.current.enabled);

					ImGui::Checkbox(configs.no_flinch.name.c_str(), &configs.no_flinch.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.quick_reload.name.c_str(), &configs.quick_reload.current.enabled);

					ImGui::Combo(configs.sort_algorithm_bones.name.c_str(), &configs.sort_algorithm_bones.current.integer, niggerware::utils::string::concatenate(configs.sort_algorithm_bones.items).c_str());

					ImGui::Checkbox(configs.multi_threading.name.c_str(), &configs.multi_threading.current.enabled);

					ImGui::Checkbox(configs.full_auto_all_weapons.name.c_str(), &configs.full_auto_all_weapons.current.enabled);



					if (ImGui::InputFloat(configs.fake_lag.name.c_str(), &configs.fake_lag.current.value, 1.0f, 100.0f, "%.0f ms"))
					{
						configs.fake_lag.current.value = std::max(configs.fake_lag.current.value, configs.fake_lag.domain.value.min);
						configs.fake_lag.current.value = std::min(configs.fake_lag.current.value, configs.fake_lag.domain.value.max);
					}

					ImGui::Hotkey(configs.third_person_hotkey.name.c_str(), &configs.third_person_hotkey.current.integer);

					ImGui::Hotkey(configs.air_stuck_hotkey.name.c_str(), &configs.air_stuck_hotkey.current.integer);



					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("ESP"))
				{
					ImGui::Combo(configs.esp_mode.name.c_str(), &configs.esp_mode.current.integer, niggerware::utils::string::concatenate(configs.esp_mode.items).c_str());


					ImGui::Combo(configs.esp_boxes.name.c_str(), &configs.esp_boxes.current.integer, niggerware::utils::string::concatenate(configs.esp_boxes.items).c_str());

					ImGui::Combo(configs.esp_bones.name.c_str(), &configs.esp_bones.current.integer, niggerware::utils::string::concatenate(configs.esp_bones.items).c_str());

					ImGui::Combo(configs.esp_snap_lines.name.c_str(), &configs.esp_snap_lines.current.integer, niggerware::utils::string::concatenate(configs.esp_snap_lines.items).c_str());

					ImGui::Combo(configs.esp_entities.name.c_str(), &configs.esp_entities.current.integer, niggerware::utils::string::concatenate(configs.esp_entities.items).c_str());

					ImGui::Checkbox(configs.esp_distances.name.c_str(), &configs.esp_distances.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.esp_names.name.c_str(), &configs.esp_names.current.enabled);

					ImGui::Checkbox(configs.esp_weapons.name.c_str(), &configs.esp_weapons.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.esp_health_bars.name.c_str(), &configs.esp_health_bars.current.enabled);

					ImGui::Checkbox(configs.esp_aim_pos.name.c_str(), &configs.esp_aim_pos.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.esp_cross_hair.name.c_str(), &configs.esp_cross_hair.current.enabled);

					ImGui::Checkbox(configs.esp_bullet_tracers.name.c_str(), &configs.esp_bullet_tracers.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.esp_threat_warning.name.c_str(), &configs.esp_threat_warning.current.enabled);



				



					if (ImGui::CollapsingHeader("Colors"))
					{
						draw_color_picker(&configs.color_axis_visible, true);

						draw_color_picker(&configs.color_axis_visible_text, true);

						draw_color_picker(&configs.color_axis_visible_outline, true);

						draw_color_picker(&configs.color_axis_occluded, true);

						draw_color_picker(&configs.color_axis_occluded_text, true);

						draw_color_picker(&configs.color_axis_occluded_outline, true);

						draw_color_picker(&configs.color_allies_visible, true);

						draw_color_picker(&configs.color_allies_visible_text, true);

						draw_color_picker(&configs.color_allies_visible_outline, true);

						draw_color_picker(&configs.color_allies_occluded, true);

						draw_color_picker(&configs.color_allies_occluded_text, true);

						draw_color_picker(&configs.color_allies_occluded_outline, true);

						draw_color_picker(&configs.color_entities, true);

						draw_color_picker(&configs.color_entities_text, true);

						draw_color_picker(&configs.color_entities_outline, true);

						draw_color_picker(&configs.color_aimbot_target, true);

						draw_color_picker(&configs.color_aimbot_target_text, true);

						draw_color_picker(&configs.color_aimbot_target_outline, true);

						draw_color_picker(&configs.color_anti_aim_target, true);

						draw_color_picker(&configs.color_anti_aim_target_text, true);

						draw_color_picker(&configs.color_anti_aim_target_outline, true);

						draw_color_picker(&configs.color_prioritized, true);

						draw_color_picker(&configs.color_prioritized_text, true);

						draw_color_picker(&configs.color_prioritized_outline, true);

						draw_color_picker(&configs.color_aim_pos, true);

						draw_color_picker(&configs.color_aim_pos_outline, true);

						draw_color_picker(&configs.color_cross_hair, true);

						draw_color_picker(&configs.color_tracer_line, true);

						draw_color_picker(&configs.color_tracer_hit, true);

						draw_color_picker(&configs.color_tracer_hit_outline, true);

						draw_color_picker(&configs.color_threat_warning, true);
					}

					ImGui::EndTabItem();
				}


				if (ImGui::BeginTabItem("Anti-Aim"))
				{
					auto combo_width = 160.0f * scaling_factor;

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text("Pitch:"); ImGui::SameLine(style.WindowPadding.x + combo_width + style.ItemSpacing.x); ImGui::Text("Yaw:");
					ImGui::PopStyleColor();

					ImGui::PushItemWidth(combo_width);

					ImGui::Combo("##pitchdefault", &configs.anti_aim_pitch_default.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_pitch_default.items).c_str());

					ImGui::SameLine();

					ImGui::Combo("##yawdefault", &configs.anti_aim_yaw_default.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_yaw_default.items).c_str());

					ImGui::SameLine();

					ImGui::PopItemWidth();

					ImGui::Text("Default");

					ImGui::PushItemWidth(combo_width);

					ImGui::Combo("##pitchsprint", &configs.anti_aim_pitch_on_sprint.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_pitch_on_sprint.items).c_str());

					ImGui::SameLine();

					ImGui::Combo("##yawsprint", &configs.anti_aim_yaw_on_sprint.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_yaw_on_sprint.items).c_str());

					ImGui::SameLine();

					ImGui::PopItemWidth();

					ImGui::Text("On Sprint");

					ImGui::PushItemWidth(combo_width);

					ImGui::Combo("##pitchtarget", &configs.anti_aim_pitch_on_target.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_pitch_on_target.items).c_str());

					ImGui::SameLine();

					ImGui::Combo("##yawtarget", &configs.anti_aim_yaw_on_target.current.integer, niggerware::utils::string::concatenate(configs.anti_aim_yaw_on_target.items).c_str());

					ImGui::SameLine();

					ImGui::PopItemWidth();

					ImGui::Text("On Target");

					if (ImGui::InputFloat(configs.anti_aim_spin_speed.name.c_str(), &configs.anti_aim_spin_speed.current.value, 1.0f, 100.0f, "%.0f degrees"))
					{
						configs.anti_aim_spin_speed.current.value = std::max(configs.anti_aim_spin_speed.current.value, configs.anti_aim_spin_speed.domain.value.min);
						configs.anti_aim_spin_speed.current.value = std::min(configs.anti_aim_spin_speed.current.value, configs.anti_aim_spin_speed.domain.value.max);
					}

					if (ImGui::InputFloat(configs.anti_aim_shield_pitch_shift.name.c_str(), &configs.anti_aim_shield_pitch_shift.current.value, 1.0f, 100.0f, "%.0f degrees"))
					{
						configs.anti_aim_shield_pitch_shift.current.value = std::max(configs.anti_aim_shield_pitch_shift.current.value, configs.anti_aim_shield_pitch_shift.domain.value.min);
						configs.anti_aim_shield_pitch_shift.current.value = std::min(configs.anti_aim_shield_pitch_shift.current.value, configs.anti_aim_shield_pitch_shift.domain.value.max);
					}

					if (ImGui::InputFloat(configs.anti_aim_shield_yaw_shift.name.c_str(), &configs.anti_aim_shield_yaw_shift.current.value, 1.0f, 100.0f, "%.0f degrees"))
					{
						configs.anti_aim_shield_yaw_shift.current.value = std::max(configs.anti_aim_shield_yaw_shift.current.value, configs.anti_aim_shield_yaw_shift.domain.value.min);
						configs.anti_aim_shield_yaw_shift.current.value = std::min(configs.anti_aim_shield_yaw_shift.current.value, configs.anti_aim_shield_yaw_shift.domain.value.max);
					}

					if (ImGui::InputFloat(configs.anti_aim_custom_pitch.name.c_str(), &configs.anti_aim_custom_pitch.current.value, 1.0f, 100.0f, "%.0f degrees"))
					{
						configs.anti_aim_custom_pitch.current.value = std::max(configs.anti_aim_custom_pitch.current.value, configs.anti_aim_custom_pitch.domain.value.min);
						configs.anti_aim_custom_pitch.current.value = std::min(configs.anti_aim_custom_pitch.current.value, configs.anti_aim_custom_pitch.domain.value.max);
					}

					if (ImGui::InputFloat(configs.anti_aim_custom_yaw.name.c_str(), &configs.anti_aim_custom_yaw.current.value, 1.0f, 100.0f, "%.0f degrees"))
					{
						configs.anti_aim_custom_yaw.current.value = std::max(configs.anti_aim_custom_yaw.current.value, configs.anti_aim_custom_yaw.domain.value.min);
						configs.anti_aim_custom_yaw.current.value = std::min(configs.anti_aim_custom_yaw.current.value, configs.anti_aim_custom_yaw.domain.value.max);
					}



					ImGui::EndTabItem();
				}


				if (ImGui::BeginTabItem("Misc."))
				{


					


					


					

					
				
					
					
					
					
					if (ImGui::Button("Godmode ") * scaling_factor)
					{
						stats.enable_invalid_specialist();
				

					}


					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.sv_game_send_server_command.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##servercmd", text_buffers.sv_game_send_server_command, sizeof(text_buffers.sv_game_send_server_command)))
					{
						configs.sv_game_send_server_command.current.string = text_buffers.sv_game_send_server_command;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##9"))
					{
						functions::SV_GameSendServerCommand(-1, structures::SV_CMD_RELIABLE, functions::parse_place_holders(configs.sv_game_send_server_command.current.string).c_str());
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.cbuf_add_text.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##cbufcmd", text_buffers.cbuf_add_text, sizeof(text_buffers.cbuf_add_text)))
					{
						configs.cbuf_add_text.current.string = text_buffers.cbuf_add_text;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##7"))
					{
						functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, functions::parse_place_holders(configs.cbuf_add_text.current.string).c_str());
					}



					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.dvar_set_from_string_by_name.name.c_str());
					ImGui::PopStyleColor();

					if (ImGui::InputText("##setdvar", text_buffers.dvar_set_from_string_by_name, sizeof(text_buffers.dvar_set_from_string_by_name)))
					{
						configs.dvar_set_from_string_by_name.current.string = text_buffers.dvar_set_from_string_by_name;
					} ImGui::SameLine();
					if (ImGui::Button("Execute##10"))
					{
						auto set_dvar = niggerware::utils::string::tokenize(configs.dvar_set_from_string_by_name.current.string, ' ');

						if (set_dvar.size() == 2)
						{
							functions::Dvar_SetFromStringByName(set_dvar[0].c_str(), set_dvar[1].c_str(), true);
						}
					}

					

					

					ImGui::EndTabItem();
				}
				

				if (ImGui::BeginTabItem("Tools"))
				{
					ImGui::Combo(configs.give_currency.name.c_str(), &configs.give_currency.current.integer, niggerware::utils::string::concatenate(configs.give_currency.items).c_str());

					ImGui::Combo(configs.spend_currency.name.c_str(), &configs.spend_currency.current.integer, niggerware::utils::string::concatenate(configs.spend_currency.items).c_str());

					ImGui::Checkbox(configs.burn_duplicates.name.c_str(), &configs.burn_duplicates.current.enabled);

					ImGui::SameLine(250.0f * scaling_factor);

					ImGui::Checkbox(configs.spoof_all_dlc_items.name.c_str(), &configs.spoof_all_dlc_items.current.enabled);

					if (ImGui::Button("Spoof All Black Market Items", ImVec2(165.0f, 0.0f) * scaling_factor))
					{
						stats.spoof_all_black_market_items();
					} ImGui::SameLine();

					if (ImGui::Button("Give All Achievements", ImVec2(165.0f, 0.0f) * scaling_factor))
					{
						steam.give_all_achievements();
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.kill_spam.name.c_str());
					ImGui::PopStyleColor();

					ImGui::InputText("##killspam", text_buffers.kill_spam, sizeof(text_buffers.kill_spam));
					ImGui::SameLine();
					if (ImGui::Button("Execute##1"))
					{
						configs.kill_spam.current.string = text_buffers.kill_spam;
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.chat_spam.name.c_str());
					ImGui::PopStyleColor();

					ImGui::InputText("##chatspam", text_buffers.chat_spam, sizeof(text_buffers.chat_spam));
					ImGui::SameLine();
					if (ImGui::Button("Execute##2"))
					{
						configs.chat_spam.current.string = text_buffers.chat_spam;
					}

					ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
					ImGui::Text(configs.vote_spam.name.c_str());
					ImGui::PopStyleColor();

					ImGui::InputText("##votespam", text_buffers.vote_spam, sizeof(text_buffers.vote_spam));
					ImGui::SameLine();
					if (ImGui::Button("Execute##3"))
					{
						configs.vote_spam.current.string = text_buffers.vote_spam;
					}

				

					

					ImGui::EndTabItem();
				}

				


				




				shitters.draw_menu_tab();

				configs.draw_menu_tab();



				ImGui::EndTabBar();
			}

			ImGui::End();
		}

		draw_toast_popups();

		ImGui::Render();
		renderer_device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (functions::is_in_game())
		{
			if (chat_spam_timer.expired())
			{
				if (!configs.chat_spam.current.string.empty())
				{
					functions::send_chat_message_all(functions::parse_place_holders(configs.chat_spam.current.string));
					chat_spam_timer.reset(1s);
				}
			}

			if (vote_spam_timer.expired())
			{
				if (!configs.vote_spam.current.string.empty())
				{
					functions::call_vote(niggerware::utils::string::va("map \"%s\"", functions::parse_place_holders(configs.vote_spam.current.string).c_str()));
					vote_spam_timer.reset(30s + std::chrono::milliseconds(std::max(functions::get_cg()->frameTime, functions::get_client_active()->ping)));
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::draw_toast_popups()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGuiCol_TitleBg);
		ImGui::RenderNotifications();
		ImGui::PopStyleColor();
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::draw_color_picker(configs_c::cvar_s* cvar, bool alpha)
	{
		constexpr auto num_columns = 8;
		constexpr auto num_rows = 4;
		constexpr auto total_palette = num_columns * num_rows;

		if (!cvar)
			return;

		if (cvar->type != configs_c::cvar_type_color)
			return;

		auto no_alpha = alpha ? ImGuiColorEditFlags_None : ImGuiColorEditFlags_NoAlpha;
		auto alpha_preview = alpha ? ImGuiColorEditFlags_AlphaPreview : ImGuiColorEditFlags_None;
		auto alpha_preview_half = alpha ? ImGuiColorEditFlags_AlphaPreviewHalf : ImGuiColorEditFlags_None;

		static ImVec4 saved_palette[total_palette], backup_color;

		auto init_palette = true;
		if (init_palette)
		{
			for (auto i{ 0 }; i < IM_ARRAYSIZE(saved_palette); i++)
			{
				ImGui::ColorConvertHSVtoRGB(i / std::stcast<std::float_t>(total_palette - 1), 1.0f, 1.0f, saved_palette[i].x, saved_palette[i].y, saved_palette[i].z);
				saved_palette[i].w = 1.0f;
			} init_palette = false;
		}

		ImGui::PushID(cvar);

		ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
		ImGui::Text(cvar->name.c_str());
		ImGui::PopStyleColor();

		if (ImGui::ColorButton("##button", cvar->current.color, alpha_preview))
		{
			ImGui::OpenPopup("##popup");
			backup_color = cvar->current.color;
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
				niggerware::utils::memory::copy(&cvar->current.color, payload->Data, sizeof(ImVec3));

			if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
				niggerware::utils::memory::copy(&cvar->current.color, payload->Data, sizeof(ImVec4));

			ImGui::EndDragDropTarget();
		}

		if (ImGui::BeginPopup("##popup"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text(("BOB ROSS COLOR PICKER FOR " + niggerware::utils::string::to_upper(cvar->name)).c_str());
			ImGui::PopStyleColor();

			ImGui::Separator();

			if (alpha)
				ImGui::ColorPicker4("##picker", cvar->current.color, no_alpha | alpha_preview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
			else
				ImGui::ColorPicker3("##picker", cvar->current.color, no_alpha | alpha_preview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);

			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text("Current:");
			ImGui::PopStyleColor();

			ImGui::ColorButton("##current", cvar->current.color, ImGuiColorEditFlags_NoPicker | alpha_preview_half, ImVec2(60, 40) * scaling_factor);

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text("Previous:");
			ImGui::PopStyleColor();

			if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | alpha_preview_half, ImVec2(60, 40) * scaling_factor))
				cvar->current.color = backup_color;

			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);
			ImGui::Text("Palette:");
			ImGui::PopStyleColor();

			for (auto i{ 0 }; i < IM_ARRAYSIZE(saved_palette); i++)
			{
				ImGui::PushID(i);

				if ((i % num_columns) != 0)
					ImGui::SameLine();

				if (ImGui::ColorButton("##palette", saved_palette[i], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20, 20) * scaling_factor))
					cvar->current.color = ImVec4(saved_palette[i].x, saved_palette[i].y, saved_palette[i].z, cvar->current.color.w);

				if (ImGui::BeginDragDropTarget())
				{
					if (auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
						niggerware::utils::memory::copy(&saved_palette[i], payload->Data, sizeof(ImVec3));

					if (auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
						niggerware::utils::memory::copy(&saved_palette[i], payload->Data, sizeof(ImVec4));

					ImGui::EndDragDropTarget();
				}

				ImGui::PopID();
			}

			ImGui::EndGroup();
			ImGui::EndPopup();
		}

		ImGui::SameLine();

		auto& style = ImGui::GetStyle();

		ImGui::PushItemWidth(ImGui::CalcItemWidth() - (ImGui::GetFrameHeight() + style.ItemSpacing.x));
		if (ImGui::InputFloat("RGB Speed", &cvar->current.value, 1.0f, 100.0f, "%.0f"))
		{
			cvar->current.value = std::max(cvar->current.value, cvar->domain.value.min);
			cvar->current.value = std::min(cvar->current.value, cvar->domain.value.max);
		}
		ImGui::PopItemWidth();

		ImGui::PopID();
	}
	/*
	//=====================================================================================
	*/
	void main_gui_c::process_lobby()
	{
		for (auto i = 0; i < max_clients; i++)
		{
			if (auto session_client{ functions::get_session_client(i) }; !session_client || !session_client->activeClient)
			{
				target_list.priorities[i].is_prioritized = false;
				target_list.priorities[i].is_ignored = false;
			}
		}
	}
	/*
	//=====================================================================================
	*/
	bool main_gui_c::get_key_press(std::int32_t index, bool immediate)
	{
		if (virtual_keys[index].key)
		{
			virtual_keys[index].up = false;
			virtual_keys[index].down = true;
		}

		else if (!virtual_keys[index].key && virtual_keys[index].down)
		{
			virtual_keys[index].up = true;
			virtual_keys[index].down = false;
		}

		else
		{
			virtual_keys[index].up = false;
			virtual_keys[index].down = false;
		}

		if (immediate)
		{
			return virtual_keys[index].down;
		}

		else
		{
			return virtual_keys[index].up;
		}
	}
	/*
	//=====================================================================================
	*/
	bool main_gui_c::should_ignore_msg(UINT uMsg)
	{
		switch (uMsg)
		{
		case WM_MOUSEACTIVATE:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_MOUSEMOVE:
		case WM_NCHITTEST:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHOVER:
		case WM_ACTIVATEAPP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_SETCURSOR:
			return true;
		default:
			return false;
		}
	}
	/*
	//=====================================================================================
	*/
	bool main_gui_c::window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			main_gui.virtual_keys[VK_LBUTTON].key = true;
			break;

		case WM_LBUTTONUP:
			main_gui.virtual_keys[VK_LBUTTON].key = false;
			break;

		case WM_RBUTTONDOWN:
			main_gui.virtual_keys[VK_RBUTTON].key = true;
			break;

		case WM_RBUTTONUP:
			main_gui.virtual_keys[VK_RBUTTON].key = false;
			break;

		case WM_KEYDOWN:
			main_gui.virtual_keys[wParam].key = true;
			break;

		case WM_KEYUP:
			main_gui.virtual_keys[wParam].key = false;
			break;
		}

		if (main_gui.get_key_press(VK_F1, false))
			main_gui.show_window = !main_gui.show_window;

		if (GetAsyncKeyState(VK_F2))
		{
			functions::disconnect();


		}
		if (GetAsyncKeyState(VK_F3))
		{
			functions::Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "quit");


		}

		if (!main_gui.show_window && !(structures::get_client_connection(structures::LOCAL_CLIENT_FIRST)->keyCatchers & 0x20))
		{
			if (main_gui.get_key_press(configs.third_person_hotkey.current.integer, false))
			{
				configs.third_person.current.enabled = !configs.third_person.current.enabled;
			}

			packets.is_air_stuck = main_gui.get_key_press(configs.air_stuck_hotkey.current.integer, true);
		}

		niggerware::utils::memory::write(offsets::mouse_input, !main_gui.show_window);

		if (auto should_ignore{ ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) || main_gui.should_ignore_msg(uMsg) }; should_ignore && main_gui.show_window)
		{
			return true;
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	HRESULT __fastcall Present_h(IDXGISwapChain* _this, void* rdx, void* r8, void* r9, UINT SyncInterval, UINT Flags)
	{
		if (!main_gui.initialized)
		{
			if (!main_gui.renderer_device || !main_gui.renderer_device_context)
			{
				main_gui.device_context_from_swap(_this);
				main_gui.get_swap_chain_desc(_this);
			}

			else if (!main_gui.render_target_view)
			{
				main_gui.create_render_target_view(_this);
			}

			else
			{
				main_gui.setup_imgui();
			}
		}

		else
		{
			main_gui.update_colors();
			main_gui.draw_main_gui();
			main_gui.process_lobby();

			shitters.process();

			hooks.handle_hooks();
			stats.handle_loot();
			stats.handle_niggsploit();
		}

		return Present_o(_this, rdx, r8, r9, SyncInterval, Flags);
	}
	/*
	//=====================================================================================
	*/
	HRESULT __fastcall ResizeBuffers_h(IDXGISwapChain* _this, void* rdx, void* r8, void* r9, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		main_gui.release_objects();
		main_gui.create_render_target_view(_this);

		return ResizeBuffers_o(_this, rdx, r8, r9, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}
}

//=====================================================================================