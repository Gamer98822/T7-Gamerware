//=====================================================================================

#include "../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	hooks_c hooks;

	CG_Draw2DInternal_t CG_Draw2DInternal_o;
	CL_CreateCmd_t CL_CreateCmd_o;
	CL_CreateNewCommands_t CL_CreateNewCommands_o;
	CL_WritePacket_t CL_WritePacket_o;
	BG_WeaponFireRecoil_t BG_WeaponFireRecoil_o;
	CG_TransitionPlayerState_t CG_TransitionPlayerState_o;
	CG_BulletHitEvent_t CG_BulletHitEvent_o;
	CG_UpdateThirdPersonPlayerEntity_t CG_UpdateThirdPersonPlayerEntity_o;
	CG_OffsetThirdPersonView_GetViewOrgFromDObj_t CG_OffsetThirdPersonView_GetViewOrgFromDObj_o;
	CG_Obituary_t CG_Obituary_o;
	CG_DeployServerCommand_t CG_DeployServerCommand_o;

	LiveSteam_FilterPersonaName_t LiveSteam_FilterPersonaName_o = std::recast<LiveSteam_FilterPersonaName_t>(offsets::LiveSteam_FilterPersonaName);
	Utf8safe_strncpyz_t Utf8safe_strncpyz_o = std::recast<Utf8safe_strncpyz_t>(offsets::Utf8safe_strncpyz);

	ZwContinue_t ZwContinue_o;

	void hooks_c::init(HINSTANCE instance)
	{
		cheat_base = instance;

		manager.create(offsets::CG_Draw2DInternal, CG_Draw2DInternal_h, CG_Draw2DInternal_o);
		manager.create(offsets::CL_CreateCmd, CL_CreateCmd_h, CL_CreateCmd_o);
		manager.create(offsets::CL_CreateNewCommands, CL_CreateNewCommands_h, CL_CreateNewCommands_o);
		manager.create(offsets::CL_WritePacket, CL_WritePacket_h, CL_WritePacket_o);
		manager.create(offsets::BG_WeaponFireRecoil, BG_WeaponFireRecoil_h, BG_WeaponFireRecoil_o);
		manager.create(offsets::CG_TransitionPlayerState, CG_TransitionPlayerState_h, CG_TransitionPlayerState_o);
		manager.create(offsets::CG_BulletHitEvent, CG_BulletHitEvent_h, CG_BulletHitEvent_o);
		manager.create(offsets::CG_UpdateThirdPersonPlayerEntity, CG_UpdateThirdPersonPlayerEntity_h, CG_UpdateThirdPersonPlayerEntity_o);
		manager.create(offsets::CG_OffsetThirdPersonView_GetViewOrgFromDObj, CG_OffsetThirdPersonView_GetViewOrgFromDObj_h, CG_OffsetThirdPersonView_GetViewOrgFromDObj_o);
		manager.create(offsets::CG_Obituary, CG_Obituary_h, CG_Obituary_o);
		manager.create(offsets::CG_DeployServerCommand, CG_DeployServerCommand_h, CG_DeployServerCommand_o);

		create_exception_handler();
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::free()
	{
		manager.remove(offsets::CG_Draw2DInternal);
		manager.remove(offsets::CL_CreateCmd);
		manager.remove(offsets::CL_CreateNewCommands);
		manager.remove(offsets::CL_WritePacket);
		manager.remove(offsets::BG_WeaponFireRecoil);
		manager.remove(offsets::CG_TransitionPlayerState);
		manager.remove(offsets::CG_BulletHitEvent);
		manager.remove(offsets::CG_UpdateThirdPersonPlayerEntity);
		manager.remove(offsets::CG_OffsetThirdPersonView_GetViewOrgFromDObj);
		manager.remove(offsets::CG_Obituary);
		manager.remove(offsets::CG_DeployServerCommand);

		destroy_exception_handler();
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::enable_all()
	{
		if (!hooked_all)
		{
			manager.enable();

			hooked_all = true;
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::disable_all()
	{
		if (hooked_all)
		{
			manager.disable();

			hooked_all = false;
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::handle_hooks()
	{
		if (hook_timer.expired())
		{
			if (functions::is_match_loaded())
			{
				enable_all();
			}

			else
			{
				disable_all();
			}

			hook_timer.reset(10ms);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::set_name(std::string name)
	{
		niggerware::utils::string::copy(structures::get_user_data()->name, name, sizeof(main_gui.text_buffers.change_name));
		niggerware::utils::string::copy(std::recast<char*>(offsets::name_buffer), name, sizeof(main_gui.text_buffers.change_name));
	}
	
	/*
	//=====================================================================================
	*/
	void __fastcall CG_Draw2DInternal_h(structures::LocalClientNum_t localClientNum)
	{
		hooks.sys_value = functions::Sys_GetTLS();
		hooks.material_ptr = functions::Material_RegisterHandle("white", 7, true, INFINITE);

		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				drawing.get_information();
				drawing.calculate_tracers();
				drawing.calculate_colors();

				if (configs.perma_hatr.current.enabled && functions::get_cg()->predictedPlayerState.satalliteTypeEnabled != 1)
				{
					functions::get_cg()->predictedPlayerState.satalliteTypeEnabled = 1;
				}
			}

			else
			{
				sounds.reset();
				drawing.tracers.clear();
			}
		}

		functions::spoof_call(CG_Draw2DInternal_o, localClientNum);
	}
	/*
	//=====================================================================================
	*/
	structures::usercmd_s* __fastcall CL_CreateCmd_h(structures::usercmd_s* retstr, structures::LocalClientNum_t localClientNum)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				functions::G_ParseHitLocDmgTable();

				target_list.get_information();

				if (functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState) || !functions::is_player_out_of_ammo())
				{
					aimbot.standard_aim();
				}

				if (!functions::BG_UsingVehicleWeapon(&functions::get_cg()->predictedPlayerState))
				{
					removals.fast_reload();
				}

				removals.no_recoil();
			}
		}

		return functions::spoof_call(CL_CreateCmd_o, retstr, localClientNum);
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CL_CreateNewCommands_h(structures::LocalClientNum_t localClientNum)
	{
		functions::spoof_call(CL_CreateNewCommands_o, localClientNum);

		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				static std::int32_t backup_angles[3];

				auto old_cmd = functions::get_client_active()->get_user_cmd(functions::get_client_active()->currentCmd - 1);
				auto current_cmd = functions::get_client_active()->get_user_cmd(functions::get_client_active()->currentCmd);
				auto new_cmd = functions::get_client_active()->get_user_cmd(functions::get_client_active()->currentCmd + 1);

				if (packets.is_air_stuck)
					*current_cmd = *old_cmd;

				*new_cmd = *current_cmd;
				++functions::get_client_active()->currentCmd;

				old_cmd->viewAngles[0] = backup_angles[0];
				old_cmd->viewAngles[1] = backup_angles[1];
				old_cmd->viewAngles[2] = backup_angles[2];

				backup_angles[0] = current_cmd->viewAngles[0];
				backup_angles[1] = current_cmd->viewAngles[1];
				backup_angles[2] = current_cmd->viewAngles[2];

				++old_cmd->serverTime;
				--current_cmd->serverTime;

				packets.process_packets(old_cmd, current_cmd, new_cmd);
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CL_WritePacket_h(structures::LocalClientNum_t localClientNum)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				auto current_cmd = functions::get_client_active()->get_user_cmd(functions::get_client_active()->currentCmd);

				packets.process_packets(current_cmd);

				if (packets.is_packet_choked(current_cmd))
				{
					functions::spoof_call(CL_WritePacket_o, localClientNum);
				}
			}

			else
			{
				functions::spoof_call(CL_WritePacket_o, localClientNum);
			}
		}

		else
		{
			functions::spoof_call(CL_WritePacket_o, localClientNum);
		}
	}
	/*
	//=====================================================================================
	*/
	void __fastcall BG_WeaponFireRecoil_h(structures::player_state_s* ps, std::float_t fPitchMove, std::float_t fYawMove, ImVec2* recoilSpeed, ImVec3* kickAVel, std::int32_t* previousRecoilTime, bool previouslyFiring, std::float_t* previousRecoilRatio, std::uint32_t* holdrand)
	{
		if (!configs.no_recoil.current.enabled)
		{
			functions::spoof_call(BG_WeaponFireRecoil_o, ps, fPitchMove, fYawMove, recoilSpeed, kickAVel, previousRecoilTime, previouslyFiring, previousRecoilRatio, holdrand);
		}
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CG_TransitionPlayerState_h(structures::LocalClientNum_t localClientNum, structures::player_state_s* ps, structures::trans_player_state_s* ops)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				removals.no_flinch(ps);
			}
		}

		functions::spoof_call(CG_TransitionPlayerState_o, localClientNum, ps, ops);
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CG_BulletHitEvent_h(structures::LocalClientNum_t localClientNum, std::int64_t sourceEntityNum, std::int64_t targetEntityNum, std::int64_t weapon, ImVec3 startPos, ImVec3 position, ImVec3 normal, std::int32_t surfType, std::int32_t eventIndex, char eventParam, std::int32_t hitContents, std::int16_t boneIndex, std::int32_t modelIndex)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				if
				(
					sourceEntityNum == functions::get_cg()->predictedPlayerState.clientNum &&
					functions::get_centity(targetEntityNum)->nextState.eType == structures::et_player &&
					weapon == functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)
				)
				{
					if (configs.esp_bullet_tracers.current.enabled)
					{
						std::int32_t shots, ignore_num;
						std::float_t range, spread;
						ImVec3 origin, tracer_start;
						structures::orientation_s orientation;
						structures::BulletFireParams fire_params;

						if (functions::CG_PrepFireParams(structures::LOCAL_CLIENT_FIRST, &functions::get_cg()->predictedPlayerEntity, functions::GScr_AllocString("tag_flash"), &functions::get_cg()->predictedPlayerState, functions::BG_GetPlayerWeapon(&functions::get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false), eventIndex, true, &fire_params, &tracer_start, &shots, &range, &orientation, &origin, &spread, &ignore_num))
						{
							drawing_c::tracer_s tracer;

							tracer.start_time = std::chrono::high_resolution_clock::now();

							tracer.hit_outline_color = configs.color_tracer_hit_outline.current.color;
							tracer.hit_color = configs.color_tracer_hit.current.color;
							tracer.line_color = configs.color_tracer_line.current.color;

							tracer.hit_outline_alpha = configs.color_tracer_hit_outline.current.color.w;
							tracer.hit_alpha = configs.color_tracer_hit.current.color.w;
							tracer.line_alpha = configs.color_tracer_line.current.color.w;

							tracer.start_pos_world = tracer_start;
							tracer.hit_pos_world = position;

							drawing.tracers.push_back(tracer);
						}
					}

					if (configs.hit_marker_sounds.current.enabled)
					{
						sounds.play_hit_marker_sound();
					}
				}
			}
		}

		functions::spoof_call(CG_BulletHitEvent_o, localClientNum, sourceEntityNum, targetEntityNum, weapon, startPos, position, normal, surfType, eventIndex, eventParam, hitContents, boneIndex, modelIndex);
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CG_UpdateThirdPersonPlayerEntity_h(structures::LocalClientNum_t localClientNum)
	{
		functions::spoof_call(CG_UpdateThirdPersonPlayerEntity_o, localClientNum);

		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				anti_aim.apply_to_third_person_view();
			}
		}
	}
	/*
	//=====================================================================================
	*/
	bool __fastcall CG_OffsetThirdPersonView_GetViewOrgFromDObj_h(structures::LocalClientNum_t localClientNum, structures::cg_s* cgameGlob)
	{
		auto result = functions::spoof_call(CG_OffsetThirdPersonView_GetViewOrgFromDObj_o, localClientNum, cgameGlob);

		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				anti_aim.stabilize_third_person_view_origin();
			}
		}

		return result;
	}
	/*
	//=====================================================================================
	*/
	void __fastcall CG_Obituary_h(structures::LocalClientNum_t localClientNum, structures::entity_state_s* ent)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::is_in_game() && functions::get_cg()->predictedPlayerState.otherFlags & 0x4)
			{
				if (ent->attackerEntityNum == functions::get_cg()->predictedPlayerState.clientNum && ent->attackerEntityNum != ent->otherEntityNum)
				{
					auto kill_spam(configs.kill_spam.current.string);
					if (!kill_spam.empty())
					{
						auto mod = ""s;

						switch (ent->eventParm)
						{
						case structures::MOD_MELEE:
						case structures::MOD_MELEE_ASSASSINATE:
							mod = "Fists";
							break;
						case structures::MOD_MELEE_WEAPON_BUTT:
							mod = "Weapon Butt";
							break;
						case structures::MOD_HEAD_SHOT:
							mod = "Headshot";
							break;
						case structures::MOD_CRUSH:
							mod = "Crush";
							break;
						case structures::MOD_FALLING:
							mod = "Falling";
							break;
						case structures::MOD_SUICIDE:
						case structures::MOD_TRIGGER_HURT:
						case structures::MOD_DROWN:
							mod = "Suicide";
							break;
						case structures::MOD_IMPACT:
							mod = "Impact";
							break;
						case structures::MOD_HIT_BY_OBJECT:
							mod = "Crate";
							break;
						default:
							mod = functions::get_weapon_display_name(ent->weapon);
							break;
						}

						kill_spam = niggerware::utils::string::find_and_replace(kill_spam, place_holder_weapon_name, mod);
						kill_spam = functions::parse_place_holders(kill_spam, ent->attackerEntityNum, ent->otherEntityNum);

						functions::send_chat_message_all(kill_spam);
					}

					if (configs.kill_sounds.current.integer > configs_c::kill_sounds_off)
					{
						sounds.play_kill_sound();
					}
				}
			}
		}

		functions::spoof_call(CG_Obituary_o, localClientNum, ent);
	}
	/*
	//=====================================================================================
	*/
	bool __fastcall CG_DeployServerCommand_h(structures::LocalClientNum_t localClientNum)
	{
		exploits.log_server_command();

		return functions::spoof_call(CG_DeployServerCommand_o, localClientNum);
	}
	/*
	//=====================================================================================
	*/
	const char* __fastcall LiveSteam_FilterPersonaName_h(char* name, std::size_t size, bool ascii)
	{
		niggerware::utils::hook::detach(LiveSteam_FilterPersonaName_o, LiveSteam_FilterPersonaName_h);
		return nullptr;
	}
	/*
	//=====================================================================================
	*/
	void __fastcall Utf8safe_strncpyz_h(char* dst, const char* src, std::size_t size)
	{
		niggerware::utils::hook::detach(Utf8safe_strncpyz_o, Utf8safe_strncpyz_h);
		niggerware::utils::string::copy(dst, src, sizeof(main_gui.text_buffers.change_name));
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::CL_ConnectionlessCMD(LPCONTEXT Context)
	{
		Context->Rsp -= 0x8C8;
		Context->Rip += 0x7;

		auto from{ *std::recast<structures::netadr_t*>(Context->Rdx) };
		auto msg{ std::recast<structures::msg_t*>(Context->R8) };

		if (exploits.log_connectionless_packet(from, msg))
		{
			Context->Rip = offsets::CL_ConnectionlessCMD_add_rsp;
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::dwInstantDispatchMessage(LPCONTEXT Context)
	{
		Context->Rsp -= 0x60;
		Context->Rip += 0x4;

		auto sender_id{ Context->Rcx };
		auto message{ std::recast<const char*>(Context->R8) };
		auto message_size{ Context->R9 };

		if (exploits.log_instant_message(message, message_size, sender_id))
		{
			Context->Rip = offsets::dwInstantDispatchMessage_add_rsp;
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::LobbyMsgRW_PackageElement(LPCONTEXT Context)
	{
		auto lobby_msg{ std::recast<structures::LobbyMsg*>(Context->Rcx) };
		auto type{ std::stcast<structures::LobbyMsgElementType>(Context->Rax) };

		if (type == structures::MESSAGE_ELEMENT_ARRAY_BEGIN || type == structures::MESSAGE_ELEMENT_ARRAY_ELEMENT)
		{
			Context->Rax = FALSE;
		}

		else
		{
			Context->Rax = TRUE;
		}

		Context->Rip = offsets::LobbyMsgRW_PackageElement_add_rsp;
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::UI_DoModelStringReplacement(LPCONTEXT Context)
	{
		Context->Rsp -= Context->Rax;
		Context->Rip += 0x3;

		auto text{ std::recast<char*>(Context->R8) };

		if (auto pos{ functions::find_invalid_models(text) }; pos != std::string::npos)
		{
			niggerware::utils::string::copy(&text[pos], invalid_model);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::MainWndProc(LPCONTEXT Context)
	{
		auto hwnd{ std::recast<HWND>(Context->Rcx) };
		auto umsg{ std::stcast<UINT>(Context->Rdx) };

		auto wparam{ std::stcast<WPARAM>(Context->R8) };
		auto lparam{ std::stcast<LPARAM>(Context->R9) };

		if (main_gui.window_procedure(hwnd, umsg, wparam, lparam))
		{
			Context->Rsp += 0x30;

			Context->Rax = TRUE;
			Context->Rip = offsets::MainWndProc_add_rsp;
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::CG_Draw2DInternal(LPCONTEXT Context)
	{
		if (functions::get_cg() && functions::get_client_active())
		{
			if (functions::get_cg()->cgs.voteTime)
			{
				if (auto pos{ functions::find_invalid_materials(functions::get_cg()->cgs.voteString) }; pos != std::string::npos)
				{
					niggerware::utils::string::copy(&functions::get_cg()->cgs.voteString[pos], invalid_material);
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::UI_Interface_DrawText(LPCONTEXT Context)
	{
		auto text{ std::recast<char*>(Context->R12) };

		if (auto pos{ functions::find_invalid_materials(text) }; pos != std::string::npos)
		{
			niggerware::utils::string::copy(&text[pos], invalid_material);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::UI_Interface_GetNumTextLines(LPCONTEXT Context)
	{
		auto text{ std::recast<char*>(Context->Rdi) };

		if (auto pos{ functions::find_invalid_materials(text) }; pos != std::string::npos)
		{
			niggerware::utils::string::copy(&text[pos], invalid_material);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::UI_Interface_GetTextWidthHeight(LPCONTEXT Context)
	{
		auto text{ std::recast<char*>(Context->Rdi) };

		if (auto pos{ functions::find_invalid_materials(text) }; pos != std::string::npos)
		{
			niggerware::utils::string::copy(&text[pos], invalid_material);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::HandlePacketInternal(LPCONTEXT Context)
	{
		auto from_adr{ *std::recast<structures::netadr_t*>(Context->Rdx) };
		auto from_xuid{ Context->R8 };

		auto lobby_module{ std::stcast<structures::LobbyModule>(Context->R9) };
		auto lobby_type{ std::stcast<structures::LobbyType>(Context->Rsp + 0xE0) };

		auto msg{ *std::recast<structures::msg_t**>(Context->Rsp + 0xE8) };

		structures::LobbyMsg lobby_msg{};
		functions::LobbyMsgRW_PrepReadMsg(&lobby_msg, msg);

		if (exploits.log_packet_internal(from_adr, from_xuid, lobby_module, lobby_type, &lobby_msg))
		{
			functions::MSG_Discard(msg);
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::Com_Frame(LPCONTEXT Context)
	{
		if (auto config_string{ structures::get_config_strings()->get_value(3627) }; niggerware::utils::string::is_equal(config_string, strpair(mspreload_command), false))
		{
			functions::CL_StoreConfigString(3627, "");

			notify::protection("Loadside crash");
		}
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::create_exception_handler()
	{
		ZwContinue_o = niggerware::utils::memory::get_export<ZwContinue_t>("ZwContinue", "ntdll.dll");
		niggerware::utils::memory::write_protected(niggerware::utils::memory::relative_offset(niggerware::utils::memory::get_export<std::uintptr_t>
		(
			"KiUserExceptionDispatcher", 
			"ntdll.dll"
		), 4), handler_thunk.get_thunk());

		r_fullscreen = *std::recast<structures::dvar_t**>(offsets::r_fullscreen);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::r_fullscreen, 0xC0000001);

		cg_draw2D = *std::recast<structures::dvar_t**>(offsets::cg_draw2D);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::cg_draw2D, 0xC0000002);

		loc_warnings = *std::recast<structures::dvar_t**>(offsets::loc_warnings);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::loc_warnings, 0xC0000003);

		loc_language = *std::recast<structures::dvar_t**>(offsets::loc_language);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::loc_language, 0xC0000004);

		lobbymsg_prints = *std::recast<structures::dvar_t**>(offsets::lobbymsg_prints);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::lobbymsg_prints, 0xC0000005);

		com_sv_running = *std::recast<structures::dvar_t**>(offsets::com_sv_running);
		niggerware::utils::memory::write<std::uintptr_t>(offsets::com_sv_running, 0xC0000006);
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::destroy_exception_handler()
	{
		niggerware::utils::memory::write(offsets::r_fullscreen, r_fullscreen);
		niggerware::utils::memory::write(offsets::cg_draw2D, cg_draw2D);
		niggerware::utils::memory::write(offsets::loc_warnings, loc_warnings);
		niggerware::utils::memory::write(offsets::loc_language, loc_language);
		niggerware::utils::memory::write(offsets::lobbymsg_prints, lobbymsg_prints);
		niggerware::utils::memory::write(offsets::com_sv_running, com_sv_running);
	}
	/*
	//=====================================================================================
	*/
	bool hooks_c::is_dvar_retaddr(LPCONTEXT Context, std::uintptr_t retaddr)
	{
		return *std::recast<std::uintptr_t*>(Context->Rsp + 0x28) == retaddr;
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::catch_exception(LPEXCEPTION_RECORD ExceptionRecord, LPCONTEXT ContextRecord)
	{
		constexpr auto stack_size = 0x100;

		MEMORY_BASIC_INFORMATION exception_mbi;
		VirtualQuery(ExceptionRecord->ExceptionAddress, &exception_mbi, sizeof(MEMORY_BASIC_INFORMATION));

		auto exception_module = niggerware::utils::memory::get_module_name(std::recast<std::uintptr_t>(exception_mbi.AllocationBase));
		auto exception_offset = std::recast<std::uintptr_t>(ExceptionRecord->ExceptionAddress) - std::recast<std::uintptr_t>(exception_mbi.AllocationBase);

		functions::write_log("Image base: 0x%llX", niggerware::utils::memory::get_module_base());
		functions::write_log("Cheat base: 0x%llX", cheat_base);

		functions::write_log("Exception code: 0x%llX", ExceptionRecord->ExceptionCode);
		functions::write_log("Exception address: 0x%llX (%s+0x%llX)", ExceptionRecord->ExceptionAddress, exception_module.c_str(), exception_offset);

		functions::write_log("Rax: 0x%llX", ContextRecord->Rax);
		functions::write_log("Rcx: 0x%llX", ContextRecord->Rcx);
		functions::write_log("Rdx: 0x%llX", ContextRecord->Rdx);
		functions::write_log("Rbx: 0x%llX", ContextRecord->Rbx);

		functions::write_log("Rsp: 0x%llX", ContextRecord->Rsp);
		functions::write_log("Rbp: 0x%llX", ContextRecord->Rbp);

		functions::write_log("Rsi: 0x%llX", ContextRecord->Rsi);
		functions::write_log("Rdi: 0x%llX", ContextRecord->Rdi);

		functions::write_log("R8: 0x%llX", ContextRecord->R8);
		functions::write_log("R9: 0x%llX", ContextRecord->R9);
		functions::write_log("R10: 0x%llX", ContextRecord->R10);
		functions::write_log("R11: 0x%llX", ContextRecord->R11);
		functions::write_log("R12: 0x%llX", ContextRecord->R12);
		functions::write_log("R13: 0x%llX", ContextRecord->R13);
		functions::write_log("R14: 0x%llX", ContextRecord->R14);
		functions::write_log("R15: 0x%llX", ContextRecord->R15);

		functions::write_log("Rip: 0x%llX", ContextRecord->Rip);

		for (auto i{ 0 }; i < stack_size; i += 0x8)
		{
			functions::write_log("Rsp+0x%02X: 0x%llX", i, *std::recast<std::uintptr_t*>(ContextRecord->Rsp + i));
		}

		std::abort();
	}
	/*
	//=====================================================================================
	*/
	void hooks_c::handler(LPEXCEPTION_RECORD ExceptionRecord, LPCONTEXT ContextRecord)
	{
		ContextRecord->Dr0 = offsets::CL_ConnectionlessCMD_sub_rsp;
		ContextRecord->Dr1 = offsets::dwInstantDispatchMessage_sub_rsp;
		ContextRecord->Dr2 = offsets::LobbyMsgRW_PackageElement_movzx_r8d;
		ContextRecord->Dr3 = offsets::UI_DoModelStringReplacement_sub_rsp;

		ContextRecord->Dr7 = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6);

		if (ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
		{
			if (ContextRecord->Rip == offsets::CL_ConnectionlessCMD_sub_rsp)
			{
				CL_ConnectionlessCMD(ContextRecord);

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::dwInstantDispatchMessage_sub_rsp)
			{
				dwInstantDispatchMessage(ContextRecord);

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::LobbyMsgRW_PackageElement_movzx_r8d)
			{
				LobbyMsgRW_PackageElement(ContextRecord);

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::UI_DoModelStringReplacement_sub_rsp)
			{
				UI_DoModelStringReplacement(ContextRecord);

				ZwContinue(ContextRecord, FALSE);
			}
		}

		else if (ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
		{
			switch (ContextRecord->Rcx)
			{
			case 0xC0000001:

				if (is_dvar_retaddr(ContextRecord, offsets::r_fullscreen_ret))
				{
					MainWndProc(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(r_fullscreen);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000002:

				if (is_dvar_retaddr(ContextRecord, offsets::cg_draw2D_ret))
				{
					CG_Draw2DInternal(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(cg_draw2D);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000003:

				if (is_dvar_retaddr(ContextRecord, offsets::loc_warnings_ret))
				{
					UI_Interface_DrawText(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(loc_warnings);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000004:

				if (is_dvar_retaddr(ContextRecord, offsets::UI_Interface_GetNumTextLines_ret))
				{
					UI_Interface_GetNumTextLines(ContextRecord);
				}

				if (is_dvar_retaddr(ContextRecord, offsets::UI_Interface_GetTextWidthHeight_ret))
				{
					UI_Interface_GetTextWidthHeight(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(loc_language);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000005:

				if (is_dvar_retaddr(ContextRecord, offsets::lobbymsg_prints_ret))
				{
					HandlePacketInternal(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(lobbymsg_prints);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000006:

				if (is_dvar_retaddr(ContextRecord, offsets::com_sv_running_ret))
				{
					Com_Frame(ContextRecord);
				}

				ContextRecord->Rcx = std::recast<std::uintptr_t>(com_sv_running);

				ZwContinue(ContextRecord, FALSE);
			}

			switch (ContextRecord->Rbx)
			{
			case 0xC0000001:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(r_fullscreen);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000002:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(cg_draw2D);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000003:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(loc_warnings);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000004:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(loc_language);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000005:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(lobbymsg_prints);

				ZwContinue(ContextRecord, FALSE);

			case 0xC0000006:

				ContextRecord->Rbx = std::recast<std::uintptr_t>(com_sv_running);

				ZwContinue(ContextRecord, FALSE);
			}

			if (ContextRecord->Rip == offsets::Sys_GetTLS_exception_1)
			{
				ContextRecord->Rcx = sys_value->traceInfo;
				ContextRecord->Rip += 0x4;

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::Sys_GetTLS_exception_2)
			{
				ContextRecord->R9 = sys_value->traceInfo;
				ContextRecord->Rip += 0x4;

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::Sys_GetTLS_exception_3)
			{
				ContextRecord->Rcx = sys_value->traceInfo;
				ContextRecord->Rip += 0x4;

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::DObjGetBoneIndex_exception)
			{
				ContextRecord->Rax = FALSE;
				ContextRecord->Rip = offsets::DObjGetBoneIndex_ret;

				notify::protection("DObjGetBoneIndex crash");

				ZwContinue(ContextRecord, FALSE);
			}

			else if (ContextRecord->Rip == offsets::CG_GetEntityImpactType_exception)
			{
				ContextRecord->Rax = FALSE;
				ContextRecord->Rip = offsets::CG_GetEntityImpactType_ret;

				notify::protection("CG_GetEntityImpactType crash");

				ZwContinue(ContextRecord, FALSE);
			}

			else if (niggerware::utils::memory::is_address_within_range(ContextRecord->Rip, offsets::LiveInvites_SendJoinInfo_min, offsets::LiveInvites_SendJoinInfo_max))
			{
				ContextRecord->Rip = offsets::LiveInvites_SendJoinInfo_ret;

				ZwContinue(ContextRecord, FALSE);
			}

			else
			{
				catch_exception(ExceptionRecord, ContextRecord);
			}
		}

		else if (ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
		{
			catch_exception(ExceptionRecord, ContextRecord);
		}

		else if (ExceptionRecord->ExceptionCode == EXCEPTION_STACK_INVALID)
		{
			catch_exception(ExceptionRecord, ContextRecord);
		}
	}
}

//=====================================================================================