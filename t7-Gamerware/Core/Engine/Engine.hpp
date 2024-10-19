//===================================JTAG==================================================

#pragma once

using namespace std::literals;

//=====================================================================================

namespace t7
{
	constexpr auto program_name = "T7 - Gamerware";

	const static auto default_cfg = niggerware::utils::file::append_to_current_dir(niggerware::utils::string::find_and_erase(program_name, " ") + ".cfg");
	const static auto default_dat = niggerware::utils::file::append_to_current_dir(niggerware::utils::string::find_and_erase(program_name, " ") + ".dat");
	const static auto default_ini = niggerware::utils::file::append_to_current_dir(niggerware::utils::string::find_and_erase(program_name, " ") + ".ini");
	const static auto default_log = niggerware::utils::file::append_to_current_dir(niggerware::utils::string::find_and_erase(program_name, " ") + ".log");
	const static auto default_txt = niggerware::utils::file::append_to_current_dir(niggerware::utils::string::find_and_erase(program_name, " ") + ".txt");

	constexpr auto max_clients = 18;
	constexpr auto max_entities = 1024;
	constexpr auto max_sessions = 50;
	constexpr auto entity_flag_crouch = 0x4;
	constexpr auto entity_flag_prone = 0x8;
	constexpr auto entity_flag_fire = 0x40;
	constexpr auto entity_flag_streak = 0x4000;
	constexpr auto entity_flag_sprint = 0x20000;
	constexpr auto entity_flag_dead = 0x40000;
	constexpr auto entity_flag_zoom = 0x80000;
	constexpr auto entity_flag_mantle = 0x400;
	constexpr auto entity_flag_move = 0x100000;
	constexpr auto pi_double = std::stcast<std::float_t>(M_PI) * 2.0f;
	constexpr auto pi_half = std::stcast<std::float_t>(M_PI) / 2.0f;

	constexpr auto loadingnewmap_packet = "loadingnewmap";
	constexpr auto relay_packet = "relay";
	constexpr auto vt_packet = "vt";
	constexpr auto mstart_packet = "mstart";
	constexpr auto requeststats_packet = "requeststats";
	constexpr auto connectresponsemigration_packet = "connectResponseMigration";
	constexpr auto steamauth_packet = "steamAuth";
	constexpr auto steamauthreq_packet = "steamAuthReq";

	constexpr auto mspreload_command = "mspreload";

	constexpr auto place_holder_attacker = "%a";
	constexpr auto place_holder_victim = "%v";
	constexpr auto place_holder_weapon_name = "%w";
	constexpr auto place_holder_ip = "%ip";

	constexpr auto place_holder_newline_char = "%n";
	constexpr auto place_holder_tab_char = "%t";
	constexpr auto place_holder_hex_value = "%x";
	constexpr auto place_holder_random_color = "%r";
	constexpr auto place_holder_crash = "%c";

	constexpr auto invalid_material = "^1<sig>";
	constexpr auto invalid_model = "^1<sig>";

	constexpr auto crash_invalid_material = "^H\x7F\x7F\xFF";
	constexpr auto crash_invalid_button = "^Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa^";
	constexpr auto crash_invalid_model = "$(aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa)";

	constexpr auto convert_to_meters(std::float_t a) { return a / 55.0f; }
	constexpr auto convert_to_feet(std::float_t a) { return convert_to_meters(a) * 3.281f; }
	constexpr auto byte_to_float(std::float_t a) { return a / 255.0f; }
	constexpr auto float_to_byte(std::float_t a) { return a * 255.0f; }
	constexpr auto dword_from_bytes(byte* a) { return (a[0]) | (a[1] << 8) | (a[2] << 16) | (a[3] << 24); }
	constexpr auto get_sign(std::float_t a) { return a ? ((*std::recast<std::int32_t*>(&a) >> 31) | 1) : 0; }
	constexpr auto degrees_to_radians(std::float_t a) { return a * (std::stcast<std::float_t>(M_PI) / 180.0f); }
	constexpr auto radians_to_degrees(std::float_t a) { return a * (180.0f / std::stcast<std::float_t>(M_PI)); }
	constexpr auto angle_to_short(std::float_t a) { return std::stcast<std::int32_t>(a * (65536 / 360.0f)) & 65535; }
	constexpr auto short_to_angle(std::int32_t a) { return std::stcast<std::float_t>(a * (360.0f / 65536)); }
	constexpr auto angle_normalize(std::float_t a) { return short_to_angle(angle_to_short(a)); }
	constexpr auto angle_compare_180(std::float_t a) { return (a < 90.0f && a > -90.0f) || (a > 270.0f || a < -270.0f); }

	namespace offsets
	{
		const static auto get_aslr_address(std::uintptr_t offset)
		{
			return niggerware::utils::memory::get_module_base() + offset;
		}
		const static auto host_bullshit = get_aslr_address(0x1ECB2B0);

		const static auto mouse_input = get_aslr_address(0x17E6F335);
		const static auto hWnd = get_aslr_address(0x17E763D0);
		const static auto MainWndProc = get_aslr_address(0x2334790);
		const static auto MainWndProc_add_rsp = get_aslr_address(0x233505E);
		const static auto CG_SimulateBulletFire_EndPos = get_aslr_address(0x123DB50);
		const static auto BG_random = get_aslr_address(0x2687A80);
		const static auto BG_seedRandWithGameTime = get_aslr_address(0x2687AB0);
		const static auto BG_GetWeaponDef = get_aslr_address(0x26E9FC0);
		const static auto BG_GetWeaponFullDef = get_aslr_address(0x26EA450);
		const static auto CG_GuessSpreadForWeapon = get_aslr_address(0x11F8620);
		const static auto CG_GetPlayerViewOrigin = get_aslr_address(0x11F04C0);
		const static auto BG_GetPlayerWeapon = get_aslr_address(0x26D05A0);
		const static auto BG_WeaponFireRecoil = get_aslr_address(0x26D2B20);
		const static auto CL_IsLocalClientInGame = get_aslr_address(0x13598E0);
		const static auto CL_WritePacket = get_aslr_address(0x13407E0);
		const static auto CG_LocationalTrace = get_aslr_address(0x12AEA10);
		const static auto Com_GetClientDObj = get_aslr_address(0x214E140);
		const static auto GScr_AllocString = get_aslr_address(0x1A83520);
		const static auto CG_DObjGetWorldTagPos = get_aslr_address(0x1ABD50);
		const static auto BulletTraceSimulated = get_aslr_address(0x1169BA0);
		const static auto CG_SimulateBulletFire_BulletProcess = get_aslr_address(0x123A950);
		const static auto Dvar_FindVar = get_aslr_address(0x22BCCD0);
		const static auto SCR_UpdateScreen = get_aslr_address(0x13E1550);
		const static auto CG_PredictPlayerState = get_aslr_address(0x9C3AF0);
		const static auto BG_GetSurfacePenetrationDepth = get_aslr_address(0x26D08C0);
		const static auto BG_Bullet_AdvanceTrace = get_aslr_address(0xA2020);
		const static auto BG_GetPenetrateType = get_aslr_address(0x26F1310);
		const static auto Trace_GetEntityHitId = get_aslr_address(0x20E5230);
		const static auto ScrPlace_GetView = get_aslr_address(0x13E55A0);
		const static auto Sys_Milliseconds = get_aslr_address(0x2332870);
		const static auto view_port = get_aslr_address(0x53E4728);
		const static auto dx_ptr = get_aslr_address(0xF4B6868);
		const static auto CG_Draw2DInternal = get_aslr_address(0x60F920);
		const static auto CL_CreateNewCommands = get_aslr_address(0x12F6F50);
		const static auto BG_Bullet_FirePenetrate = get_aslr_address(0xA2170);
		const static auto jmp_dwptr_rbx = get_aslr_address(0x2A9643B);
		const static auto CL_SetADS = get_aslr_address(0x1326F60);
		const static auto BG_IsDualWield = get_aslr_address(0x26F3C60);
		const static auto weapon_names = get_aslr_address(0x49D9410);
		const static auto BG_GetMinDamageRangeScaled = get_aslr_address(0x26F0990);
		const static auto BG_GetMultishotBaseMinDamageRangeScaled = get_aslr_address(0x26F0DA0);
		const static auto Dvar_GetFloat = get_aslr_address(0x22BD620);
		const static auto CG_TransitionPlayerState = get_aslr_address(0x99D520);
		const static auto BG_UsingVehicleWeapon = get_aslr_address(0x26D2A80);
		const static auto CG_BulletHitEvent = get_aslr_address(0x1187BF0);
		const static auto CG_PrepFireParams = get_aslr_address(0x1221280);
		const static auto cl_mouseAccel = get_aslr_address(0x53DC170);
		const static auto Live_IsUserInGame = get_aslr_address(0x1E0D750);
		const static auto BG_HasPerk = get_aslr_address(0x2682A20);
		const static auto MSG_Init = get_aslr_address(0x2154F80);
		const static auto MSG_WriteString = get_aslr_address(0x2158220);
		const static auto MSG_WriteByte = get_aslr_address(0x21577C0);
		const static auto NET_OutOfBandData = get_aslr_address(0x2173600);
		const static auto Com_ControllerIndex_GetNetworkID = get_aslr_address(0x20EF800);
		const static auto LobbyPeerToPeer_CanITalkToPeer = get_aslr_address(0x1EF95D0);
		const static auto Sys_GetTLS_exception_1 = get_aslr_address(0x20E23CF);
		const static auto Sys_GetTLS = get_aslr_address(0x21837B0);
		const static auto BG_GetWeaponHitLocationMultiplier = get_aslr_address(0x26F2FC0);
		const static auto PM_WeaponAmmoAvailable = get_aslr_address(0x26E7CD0);
		const static auto CL_AddReliableCommand = get_aslr_address(0x135D4C0);
		const static auto Cbuf_AddText = get_aslr_address(0x20EC010);
		const static auto BG_Bullet_GetDepth = get_aslr_address(0xA2CF0);
		const static auto BG_Bullet_FixupHitInfo = get_aslr_address(0xA2B30);
		const static auto BG_GetWeaponDamageForRange = get_aslr_address(0x26F2BE0);
		const static auto Dvar_GetInt = get_aslr_address(0x22BE860);
		const static auto SV_GameSendServerCommand = get_aslr_address(0x224F580);
		const static auto Loot_IncCurrency = get_aslr_address(0x1E82C50);
		const static auto GScr_AddRankXPToPlayerEnt = get_aslr_address(0x15E75C0);
		const static auto server_id = get_aslr_address(0x569B250);
		const static auto BG_GetSpreadForWeapon = get_aslr_address(0x26D0750);
		const static auto SendToClient = get_aslr_address(0x2256EE0);
		const static auto client = get_aslr_address(0x176F9318);
		const static auto LobbyClientSession_GetSession = get_aslr_address(0x1ECDA20);
		const static auto LobbyHostSession_GetSession = get_aslr_address(0x1EDCDD0);
		const static auto LobbySession_GetClientByClientNum = get_aslr_address(0x1F00070);
		const static auto LobbySession_GetClientNetAdrByIndex = get_aslr_address(0x1ECC090);
		const static auto session_mode_state = get_aslr_address(0x168ED7F4);
		const static auto LiveStats_MoveToPlayerStatPath = get_aslr_address(0x162A690);
		const static auto LobbyActiveList_GetSessionInfo = get_aslr_address(0x1EFE300);
		const static auto NetAdr_ToString = get_aslr_address(0x2172E70);
		const static auto CL_HandleRelayPacket = get_aslr_address(0x1359240);
		const static auto Dvar_GetBool = get_aslr_address(0x22BCED0);
		const static auto steam_user_interface = get_aslr_address(0x10BBCB98);
		const static auto steam_user_stats_interface = get_aslr_address(0x10BBCBB8);
		const static auto steam_friends_interface = get_aslr_address(0x10BBCBA0);
		const static auto steam_apps_interface = get_aslr_address(0x10BBCBC0);
		const static auto LiveSteam_GetUserSteamIDAsXUID = get_aslr_address(0x1EB07D0);
		const static auto LiveSteam_FilterPersonaName = get_aslr_address(0x1EB02C0);
		const static auto LiveSteam_FriendPersonaNameFromXuid = get_aslr_address(0x1EB04C0);
		const static auto LiveUser_GetXuid = get_aslr_address(0x1EC7310);
		const static auto LiveSteam_PopOverlayForSteamID = get_aslr_address(0x1EB0F80);
		const static auto user_data = get_aslr_address(0x14FB3420);
		const static auto name_buffer = get_aslr_address(0x15E84638);
		const static auto client_connection = get_aslr_address(0x53D8BC0);
		const static auto Dvar_SetFloat = get_aslr_address(0x22C6DC0);
		const static auto Dvar_SetInt = get_aslr_address(0x22C7EC0);
		const static auto Dvar_SetBool = get_aslr_address(0x22C6280);
		const static auto CG_DObjGetWorldTagMatrix = get_aslr_address(0x1ABCF0);
		const static auto LiveStorage_UploadStatsForController = get_aslr_address(0x1EC0D30);
		const static auto Com_SessionMode_GetMode = get_aslr_address(0x20F6D30);
		const static auto item_infos = get_aslr_address(0x19C2AE80);
		const static auto LiveStats_MoveToUnlockPath = get_aslr_address(0x1EA1490);
		const static auto BG_UnlockablesGetLocalCACRoot = get_aslr_address(0x16A390);
		const static auto BG_UnlockablesSetLoadoutItem = get_aslr_address(0x16C8A0);
		const static auto BG_UnlockablesIsItemLockedFromBuffer = get_aslr_address(0x26A90D0);
		const static auto BG_UnlockablesIsItemDLCAvailable = get_aslr_address(0x26A8B80);
		const static auto BG_UnlockablesIsItemLocked = get_aslr_address(0x26A8F60);
		const static auto BG_UnlockablesDLCWeaponDisabled = get_aslr_address(0x26A37B0);
		const static auto BG_UnlockablesIsItemPublicPurchasedFromBuffer = get_aslr_address(0x26A9490);
		const static auto BG_UnlockablesIsItemPurchasedFromBuffer = get_aslr_address(0x26A96E0);
		const static auto LiveStats_SetClanTagText = get_aslr_address(0x1EA5480);
		const static auto CL_ControllerIndex_GetUsername = get_aslr_address(0x283A8C0);
		const static auto LiveStats_GetClanName = get_aslr_address(0x1E9CE10);
		const static auto LiveUser_GetXuidString = get_aslr_address(0x1EC6E90);
		const static auto LiveInventory_GetItemQuantity = get_aslr_address(0x1E09030);
		const static auto LiveInventory_GetPlayerInventory = get_aslr_address(0x1E091A0);
		const static auto LiveInventory_GetPlayerInventoryItemId = get_aslr_address(0x1E08FD0);
		const static auto player_inventory_data = get_aslr_address(0x111CD818);
		const static auto CL_HandleVoiceTypePacket = get_aslr_address(0x1359310);
		const static auto LiveStats_GetRootDDLState = get_aslr_address(0x1EA96D0);
		const static auto DDL_MoveToPath = get_aslr_address(0x2522470);
		const static auto DDL_SetUInt = get_aslr_address(0x2522970);
		const static auto DDL_SetInt = get_aslr_address(0x2522900);
		const static auto LiveStats_Core_GetDDLContext = get_aslr_address(0x1EA9660);
		const static auto LiveStats_Core_GetStableDDLContext = get_aslr_address(0x1EA9730);
		const static auto LobbyVM_JoinEvent = get_aslr_address(0x1EEF890);
		const static auto LobbyClientSession_IsHost = get_aslr_address(0x1ECC240);
		const static auto LobbyHostSession_IsHost = get_aslr_address(0x1ED9110);
		const static auto Sys_GetTLS_exception_2 = get_aslr_address(0x20E188D);
		const static auto Sys_GetTLS_exception_3 = get_aslr_address(0x20E20D4);
		const static auto CG_IsEntityFriendly = get_aslr_address(0x1D6180);
		const static auto DDL_GetUInt = get_aslr_address(0x2521F30);
		const static auto SV_SetClientStat = get_aslr_address(0x2248240);
		const static auto dwInstantSendMessage = get_aslr_address(0x143A810);
		const static auto Live_GetPlayerStatusByXuid = get_aslr_address(0x1DF8E30);
		const static auto dwInstantDispatchMessage_sub_rsp = get_aslr_address(0x143A606);
		const static auto dwInstantDispatchMessage_add_rsp = get_aslr_address(0x143A696);
		const static auto CL_ConnectionlessCMD = get_aslr_address(0x134CD50);
		const static auto CL_ConnectionlessCMD_sub_rsp = get_aslr_address(0x134CD62);
		const static auto CL_ConnectionlessCMD_add_rsp = get_aslr_address(0x134D585);
		const static auto UI_SafeTranslateString = get_aslr_address(0x228ED50);
		const static auto LiveSteam_GetPersonaName_ret = get_aslr_address(0x1EB0DEC);
		const static auto NET_OutOfBandPrint = get_aslr_address(0x2173710);
		const static auto BG_FactionData_GetTeamColor = get_aslr_address(0x206BFE0);
		const static auto Com_SessionMode_IsMode = get_aslr_address(0x20F7370);
		const static auto CG_GetDObjOrientation = get_aslr_address(0x8CE8F0);
		const static auto DObjCalcBounds = get_aslr_address(0x2335B50);
		const static auto BG_GetAmmoInClip = get_aslr_address(0x26E6750);
		const static auto BG_GetClipSize = get_aslr_address(0x26E6A10);
		const static auto BG_GetDualWieldWeapon = get_aslr_address(0x26EF410);
		const static auto BG_GetAmmoNotInClip = get_aslr_address(0x26E6830);
		const static auto CG_CycleWeapon = get_aslr_address(0x11A7150);
		const static auto dwNetadrToCommonAddr = get_aslr_address(0x143DA60);
		const static auto CL_LocalClientIsInGame = get_aslr_address(0x13E32D0);
		const static auto LobbySession_IsClientNumHost = get_aslr_address(0x1ECC190);
		const static auto LobbySession_GetClientNumByXuid = get_aslr_address(0x1ECC030);
		const static auto LobbySession_GetClientXuidByClientNum = get_aslr_address(0x1ECC0F0);
		const static auto LobbyActiveList_GetGamertag = get_aslr_address(0x1EFD9D0);
		const static auto Dvar_SetFromStringByName = get_aslr_address(0x22C7500);
		const static auto StringTable_GetAsset = get_aslr_address(0x22AE3D0);
		const static auto StringTable_Lookup = get_aslr_address(0x22AE7F0);
		const static auto LiveStorage_GetStatsBufferWithCaller = get_aslr_address(0x1EBEE70);
		const static auto SV_SetClientInt64Stat = get_aslr_address(0x2248210);
		const static auto StringTable_LookupRowNumForValue = get_aslr_address(0x22AEA50);
		const static auto StringTable_GetColumnValueForRow = get_aslr_address(0x22AE660);
		const static auto dwCommonAddrToString = get_aslr_address(0x143C670);
		const static auto NetAdr_Compare = get_aslr_address(0x2172870);
		const static auto LiveFriends_IsFriendByXUID = get_aslr_address(0x1DF93A0);
		const static auto LiveUser_IsXUIDLocalPlayer = get_aslr_address(0x1EC7130);
		const static auto sv_bullet_range = get_aslr_address(0x176F86C0);
		const static auto sv_penetrationCount = get_aslr_address(0x176F86A8);
		const static auto bg_bulletPenetrationTreatVoidsAsSolid = get_aslr_address(0x19C2AA30);
		const static auto BG_GetWeaponName = get_aslr_address(0x26EA400);
		const static auto BG_GetWeaponDisplayName = get_aslr_address(0x26E9FE0);
		const static auto Live_IsUserSignedInToDemonware = get_aslr_address(0x1E0D7A0);
		const static auto Material_RegisterHandle = get_aslr_address(0x1CD4B90);
		const static auto AngleNormalize360 = get_aslr_address(0x22A4DF0);
		const static auto CG_ClientHasPerk = get_aslr_address(0x9435D0);
		const static auto sv_clientSideVehicles = get_aslr_address(0x176F8688);
		const static auto sv_clientSideVehicles_ret = get_aslr_address(0x71B1B3);
		const static auto CG_IsThirdPerson = get_aslr_address(0x863650);
		const static auto CG_GetPredictedPlayerState = get_aslr_address(0x8DF6A0);
		const static auto CL_GetLocalClientGlobals = get_aslr_address(0x71BD0);
		const static auto CG_GetPose = get_aslr_address(0x1C4D70);
		const static auto G_GetEntity = get_aslr_address(0x15F5A50);
		const static auto dwRegisterSecIDAndKey = get_aslr_address(0x143E120);
		const static auto dwCommonAddrToNetadr = get_aslr_address(0x143C360);
		const static auto MSG_InitReadOnly = get_aslr_address(0x2155010);
		const static auto MSG_BeginReading = get_aslr_address(0x2154D00);
		const static auto MSG_ReadByte = get_aslr_address(0x2155450);
		const static auto LobbyMsg_SendInfoRequest = get_aslr_address(0x1EE5470);
		const static auto LobbyMsgRW_PrepReadData = get_aslr_address(0x1EF69C0);
		const static auto MSG_ReadData = get_aslr_address(0x21554B0);
		const static auto Msg_InfoResponse = get_aslr_address(0x1EE1E60);
		const static auto Com_SessionMode_IsPublicOnlineGame = get_aslr_address(0x20F7480);
		const static auto LobbyMsgRW_PrepWriteMsg = get_aslr_address(0x1EF6A30);
		const static auto LobbyMsgRW_PackageUInt = get_aslr_address(0x1EF68A0);
		const static auto Live_IsDemonwareFetchingDone = get_aslr_address(0x1E0D710);
		const static auto Com_IsInGame = get_aslr_address(0x21482C0);
		const static auto MSG_Discard = get_aslr_address(0x2154D90);
		const static auto CG_Obituary = get_aslr_address(0x7F0540);
		const static auto CG_UpdateThirdPersonPlayerEntity = get_aslr_address(0x111BCA0);
		const static auto CG_OffsetThirdPersonView_GetViewOrgFromDObj = get_aslr_address(0x10E3470);
		const static auto LiveInvites_SendJoinInfo_min = get_aslr_address(0x1E7E870);
		const static auto LiveInvites_SendJoinInfo_max = get_aslr_address(0x1E7EB0F);
		const static auto LiveInvites_SendJoinInfo_ret = get_aslr_address(0x1E7EAF6);
		const static auto LobbyClientMsg_SendDisconnectClient = get_aslr_address(0x1ED4050);
		const static auto loc_warnings = get_aslr_address(0x1791ED70);
		const static auto loc_warnings_ret = get_aslr_address(0x1F34A57);
		const static auto Dvar_GetString = get_aslr_address(0x22BF590);
		const static auto Dvar_SetString = get_aslr_address(0x22C8720);
		const static auto ui_mapname = get_aslr_address(0x179DFAC0);
		const static auto CG_DeployServerCommand = get_aslr_address(0xF755E0);
		const static auto Cmd_TokenizeStringNoEval = get_aslr_address(0x20EEE10);
		const static auto Cmd_EndTokenizedString = get_aslr_address(0x20ECED0);
		const static auto CG_BoldGameMessage = get_aslr_address(0x8C4C30);
		const static auto CG_BoldGameMessageCenter = get_aslr_address(0x8C4C80);
		const static auto CG_GameMessage = get_aslr_address(0x8CB400);
		const static auto CL_GetConfigString = get_aslr_address(0x1321110);
		const static auto CL_StoreConfigString = get_aslr_address(0x13667C0);
		const static auto WallRun_IsWallRunning = get_aslr_address(0x1706D0);
		const static auto Slide_IsPlayerSliding = get_aslr_address(0x168CA0);
		const static auto PM_IsSprinting = get_aslr_address(0x268DA70);
		const static auto lobbymsg_prints = get_aslr_address(0x1574D840);
		const static auto lobbymsg_prints_ret = get_aslr_address(0x1EF800B);
		const static auto LobbyMsgRW_PrepReadMsg = get_aslr_address(0x1EF69F0);
		const static auto LobbySession_GetControllingLobbySession = get_aslr_address(0x1ECC170);
		const static auto Utf8safe_strncpyz = get_aslr_address(0x1EB1630);
		const static auto config_strings = get_aslr_address(0x5722828);
		const static auto LobbyMsgRW_PackageElement = get_aslr_address(0x1EF65C0);
		const static auto LobbyMsgRW_PackageElement_movzx_r8d = get_aslr_address(0x1EF64DE);
		const static auto LobbyMsgRW_PackageElement_add_rsp = get_aslr_address(0x1EF6509);
		const static auto LobbyMsgRW_PackageInt = get_aslr_address(0x1EF66D0);
		const static auto LobbyMsgRW_PackageUChar = get_aslr_address(0x1EF6800);
		const static auto LobbyMsgRW_PackageUShort = get_aslr_address(0x1EF6920);
		const static auto LobbyMsgRW_PackageGlob = get_aslr_address(0x1EF66B0);
		const static auto LobbyMsgTransport_SendOutOfBand = get_aslr_address(0x1EF8420);
		const static auto LobbyMsgTransport_SendToAdr = get_aslr_address(0x1EF8800);
		const static auto LobbyClientMsg_SendModifiedStats = get_aslr_address(0x1ED4210);
		const static auto com_sv_running = get_aslr_address(0x168ED848);
		const static auto com_sv_running_ret = get_aslr_address(0x20F8F4E);
		const static auto DDL_GetInt = get_aslr_address(0x2521C80);
		const static auto Storage_GetDDLRootState = get_aslr_address(0x2276B80);
		const static auto Storage_GetDDLContext = get_aslr_address(0x2276AB0);
		const static auto DObjGetBoneIndex_exception = get_aslr_address(0x233D3E5);
		const static auto DObjGetBoneIndex_ret = get_aslr_address(0x233D4AE);
		const static auto CG_GetEntityImpactType_exception = get_aslr_address(0x11D256B);
		const static auto CG_GetEntityImpactType_ret = get_aslr_address(0x11D2572);
		const static auto CL_CreateCmd = get_aslr_address(0x12F5390);
		const static auto LobbyTypes_GetMsgTypeName = get_aslr_address(0x1EEBD10);
		const static auto DrawText2D_sub_rsp = get_aslr_address(0x1C60989);
		const static auto BG_GetFireTime = get_aslr_address(0x26EF7A0);
		const static auto BG_GetFireType = get_aslr_address(0x26EF810);
		const static auto _report_rangecheckfailure = get_aslr_address(0x2C41374);
		const static auto _report_gsfailure = get_aslr_address(0x2C412A0);
		const static auto LobbyMsgRW_ReadArrayBegin = get_aslr_address(0x1EF6EE0);
		const static auto r_fullscreen = get_aslr_address(0xAE94DF8);
		const static auto r_fullscreen_ret = get_aslr_address(0x23347CD);
		const static auto Message_Key_Internal = get_aslr_address(0x1DEAAD0);
		const static auto G_ParseHitLocDmgTable = get_aslr_address(0x1987530);
		const static auto loc_language = get_aslr_address(0x1791ED48);
		const static auto UI_Interface_GetNumTextLines_ret = get_aslr_address(0x1F34FA3);
		const static auto UI_Interface_GetTextWidthHeight_ret = get_aslr_address(0x1F3518B);
		const static auto SendLobbyChatMsg = get_aslr_address(0x1EB36F0);
		const static auto LobbyMsgRW_PackageArrayStart = get_aslr_address(0x1EF6510);
		const static auto LobbyMsgRW_PackageBool = get_aslr_address(0x1EF6580);
		const static auto LobbyMsgRW_PackageChar = get_aslr_address(0x1EF65A0);
		const static auto LobbyMsgRW_PackageFloat = get_aslr_address(0x1EF6630);
		const static auto LobbyMsgRW_PackageShort = get_aslr_address(0x1EF6750);
		const static auto LobbyMsgRW_PackageString = get_aslr_address(0x1EF6770);
		const static auto LobbyMsgRW_PackageUInt64 = get_aslr_address(0x1EF6820);
		const static auto LobbyMsgRW_PackageXuid = get_aslr_address(0x1EF6940);
		const static auto Msg_LobbyState = get_aslr_address(0x1ED5290);
		const static auto cg_fov = get_aslr_address(0x4A31A78);
		const static auto cg_fov_default = get_aslr_address(0x17AC61F0);
		const static auto cg_fov_default_thirdperson = get_aslr_address(0x17AC61F8);
		const static auto Loot_BuyCrate = get_aslr_address(0x1E82480);
		const static auto Loot_BurnDuplicates = get_aslr_address(0x1E82360);
		const static auto Loot_SpendVials = get_aslr_address(0x1E83860);
		const static auto Loot_LiquefyGum = get_aslr_address(0x1E83080);
		const static auto Com_SessionMode_SetNetworkMode = get_aslr_address(0x20F75B0);
		const static auto UI_DoModelStringReplacement_sub_rsp = get_aslr_address(0x1F334D3);
		const static auto cg_draw2D = get_aslr_address(0x4A31988);
		const static auto cg_draw2D_ret = get_aslr_address(0x61115E);
		const static auto matchmaking_list = get_aslr_address(0x99AA4B0);
		const static auto LobbySearch_SearchSession = get_aslr_address(0x1EFC500);
	}

	namespace structures
	{
		
		
		enum bone_e
		{
			bone_helmet,
			bone_head,
			bone_neck,
			bone_spine_4,
			bone_upper_spine,
			bone_lower_spine,
			bone_main_root,
			bone_left_clavicle,
			bone_right_clavicle,
			bone_left_shoulder,
			bone_right_shoulder,
			bone_left_hip,
			bone_right_hip,
			bone_left_elbow,
			bone_right_elbow,
			bone_left_knee,
			bone_right_knee,
			bone_left_wrist_twist,
			bone_right_wrist_twist,
			bone_left_ankle,
			bone_right_ankle,
			bone_left_wrist,
			bone_right_wrist,
			bone_left_ball,
			bone_right_ball,
			bone_max
		};
		/*
		//=====================================================================================
		*/
		static std::map<std::int32_t, std::pair<std::string, std::string>> bone_names =
		{
			{ bone_helmet, { "Helmet", "j_helmet"} },
			{ bone_head, { "Head", "j_head"} },
			{ bone_neck, { "Neck", "j_neck"} },
			{ bone_spine_4, { "Spine 4", "j_spine4"} },
			{ bone_upper_spine, { "Upper Spine", "j_spineupper"} },
			{ bone_lower_spine, { "Lower Spine", "j_spinelower"} },
			{ bone_main_root, { "Main Root", "j_mainroot"} },
			{ bone_left_clavicle, { "Left Clavicle", "j_clavicle_le"} },
			{ bone_right_clavicle, { "Right Clavicle", "j_clavicle_ri"} },
			{ bone_left_shoulder, { "Left Shoulder", "j_shoulder_le"} },
			{ bone_right_shoulder, { "Right Shoulder", "j_shoulder_ri"} },
			{ bone_left_hip, { "Left Hip", "j_hip_le"} },
			{ bone_right_hip, { "Right Hip", "j_hip_ri"} },
			{ bone_left_elbow, { "Left Elbow", "j_elbow_le"} },
			{ bone_right_elbow, { "Right Elbow", "j_elbow_ri"} },
			{ bone_left_knee, { "Left Knee", "j_knee_le"} },
			{ bone_right_knee, { "Right Knee", "j_knee_ri"} },
			{ bone_left_wrist_twist, { "Left Wrist Twist", "j_wristtwist_le"} },
			{ bone_right_wrist_twist, { "Right Wrist Twist", "j_wristtwist_ri"} },
			{ bone_left_ankle, { "Left Ankle", "j_ankle_le"} },
			{ bone_right_ankle, { "Right Ankle", "j_ankle_ri"} },
			{ bone_left_wrist, { "Left Wrist", "j_wrist_le"} },
			{ bone_right_wrist, { "Right Wrist", "j_wrist_ri"} },
			{ bone_left_ball, { "Left Ball", "j_ball_le"} },
			{ bone_right_ball, { "Right Ball", "j_ball_ri"} }
		};
		/*
		//=====================================================================================
		*/
		enum entity_type_e
		{
			et_general,
			et_player,
			et_player_corpse,
			et_item,
			et_missile,
			et_player_invisible,
			et_scriptmover,
			et_sound_blend,
			et_fx,
			et_loop_fx,
			et_primary_light,
			et_lensflare,
			et_reflection_probe,
			et_helicopter,
			et_plane,
			et_vehicle,
			et_vehicle_spawner,
			et_vehicle_corpse,
			et_actor,
			et_actor_spawner,
			et_actor_corpse,
			et_streamer_hint,
			et_zbarrier,
			et_trigger,
			et_events,
		};
		/*
		//=====================================================================================
		*/
		struct trajectory_s
		{
		public:
			std::int32_t trType;
			std::int32_t trTime;
			std::int32_t trDuration;
			ImVec3 trBase;
			ImVec3 trDelta;
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct lerp_entity_state_s
		{
		public:
			std::int32_t eFlags[2];
			trajectory_s pos;
			trajectory_s apos;
		private:
			byte _0x50[0x78];
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 4)
		struct entity_state_s
		{
		public:
			std::int32_t number;
			lerp_entity_state_s lerp;
		private:
			byte _0xCC[0xCC];
		public:
			std::uint64_t eventParm;
			entity_type_e eType;
		private:
			byte _0x1A4[0xA];
		public:
			std::int16_t otherEntityNum;
			std::int16_t attackerEntityNum;
		private:
			byte _0x1B2[0x6];
		public:
			std::int64_t weapon;
		private:
			byte _0x1C0[0x33C];
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 4)
		struct cpose_s
		{
		private:
			byte _0x0[0x40];
		public:
			ImVec3 origin;
			ImVec3 angles;
			ImVec3 absmin;
			ImVec3 absmax;
		private:
			byte _0x70[0x2C0];
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct centity_s
		{
		public:
			cpose_s pose;
			lerp_entity_state_s prevState;
			entity_state_s nextState;
			std::int32_t alive;
		private:
			byte _0x8F8[0x8];
		};
		/*
		//=====================================================================================
		*/
		struct client_info_s
		{
		public:
			std::int32_t infoValid;
			std::int32_t nextValid;
			std::int32_t clientNum;
			char clientName[32];
			std::int32_t team;
		private:
			byte _0x30[0x64];
		public:
			std::int32_t score;
		private:
			byte _0x98[0x14];
		public:
			std::int32_t deaths;
		private:
			byte _0xB0[0x28];
		public:
			std::int32_t kills;
		private:
			byte _0xDC[0x18];
		public:
			std::int32_t health;
		private:
			byte _0xF8[0x48C];
		public:
			ImVec3 angles;
		private:
			byte _0x590[0x940];
		};
		/*
		//=====================================================================================
		*/
		struct refdef_s
		{
		public:
			std::int32_t x;
			std::int32_t y;
			std::int32_t width;
			std::int32_t height;
		private:
			byte _0x10[0x68];
		public:
			std::float_t fovX;
			std::float_t fovY;
		private:
			byte _0x80[0x8];
		public:
			ImVec3 viewOrigin;
		private:
			byte _0x94[0x10];
		public:
			ImVec3 viewAxis[3];
		private:
			byte _0xC8[0x1A6B28];
		};
		/*
		//=====================================================================================
		*/
		struct player_held_weapon_s
		{
		public:
			std::int64_t weapon;
		private:
			byte _0x8[0x28];
		};
		/*
		//=====================================================================================
		*/
		struct player_state_s
		{
		public:
			std::int32_t clientNum;
			std::int32_t commandTime;
		private:
			byte _0x8[0x18];
		public:
			std::int32_t otherFlags;
		private:
			byte _0x24[0x10];
		public:
			ImVec3 origin;
			ImVec3 velocity;
		private:
			byte _0x4C[0x10];
		public:
			std::uint32_t weaponState;
		private:
			byte _0x60[0x18];
		public:
			std::uint32_t weaponStateLeft;
		private:
			byte _0x7C[0x40];
		public:
			bool bThirdPerson;
		private:
			byte _0xBD[0x13];
		public:
			ImVec3 deltaAngles;
		private:
			byte _0xDC[0x220];
		public:
			std::float_t weaponPosFrac;
		private:
			byte _0x300[0x18];
		public:
			ImVec3 viewAngles;
		private:
			byte _0x324[0x30];
		public:
			std::int32_t damageEvent;
			std::int32_t damageYaw;
			std::int32_t damagePitch;
			std::int32_t damageProjYaw;
			std::int32_t damageCount;
			std::int32_t stats[4];
			player_held_weapon_s heldWeapons[15];
		private:
			byte _0x648[0xE4];
		public:
			std::int32_t satalliteTypeEnabled;
		private:
			byte _0x730[0xB4];
		public:
			std::int32_t mantleFlags;
		private:
			byte _0x7E8[0x390];
		public:
			std::float_t spreadMultiplier;
		private:
			byte _0xB7C[0x4];
		};
		/*
		//=====================================================================================
		*/
		struct cgs_s
		{
		private:
			byte _0x0[0x1BC];
		public:
			std::int32_t voteTime;
		private:
			byte _0x1C0[0x8];
		public:
			char voteString[256];
		};
		/*
		//=====================================================================================
		*/
		struct cg_s
		{
		public:
			std::int32_t clientNum;
		private:
			byte _0x4[0x7C];
		public:
			ImVec3 origin;
			ImVec3 velocity;
		private:
			byte _0x98[0x11A7EC];
		public:
			std::float_t frameInterpolation;
			std::int32_t frameTime;
			std::int32_t time;
			std::int32_t oldTime;
		private:
			byte _0x11A894[0x14];
		public:
			bool bThirdPerson;
			bool renderingThirdPerson;
			bool renderingThirdPersonDeath;
			bool renderingThirdPersonLastFrame;
		private:
			byte _0x11A8AC[0x4];
		public:
			player_state_s predictedPlayerState;
		private:
			byte _0x11B430[0xA9F8];
		public:
			centity_s predictedPlayerEntity;
		private:
			byte _0x126728[0xB5C8];
		public:
			refdef_s refDef;
			ImVec3 refDefViewAngles;
		private:
			byte _0x2D88EC[0xEBC8];
		public:
			std::int32_t v_dmg_time;
			std::float_t v_dmg_pitch;
			std::float_t v_dmg_roll;
			std::float_t v_dmg_flash;
			std::float_t bobCycle;
			std::float_t xySpeed;
			ImVec3 kickAngleVelocity;
			ImVec3 kickAngles;
			ImVec3 offsetAngles;
			std::float_t gunPitch;
			std::float_t gunYaw;
		private:
			byte _0x2E74F8[0x548];
		public:
			client_info_s clientInfo[max_clients];
		private:
			byte _0x2F84E0[0x38C960];
		public:
			cgs_s cgs;
		private:
			byte _0x685108[0x2259D8];
		public:
			centity_s centity[max_entities];
		};
		/*
		//=====================================================================================
		*/
		struct usercmd_s
		{
		public:
			std::uint32_t serverTime;
			std::uint32_t buttons[2];
		private:
			byte _0xC[0x4];
		public:
			std::int32_t viewAngles[3];
		private:
			byte _0x1C[0x4];
		public:
			std::int64_t weapon;
		private:
			byte _0x28[0x10];
		public:
			char forwardMove;
			char rightMove;
		private:
			byte _0x3A[0x16];
		};
		/*
		//=====================================================================================
		*/
		struct client_active_s
		{
		private:
			byte _0x0[0xA8];
		public:
			std::int32_t ping;
		private:
			byte _0xAC[0x34];
		public:
			ImVec3 origin;
		private:
			byte _0xEC[0x94];
		public:
			ImVec3 spawnAngles;
		private:
			byte _0x18C[0xB64C];
		public:
			ImVec3 recoilAngles;
		private:
			byte _0xB7E4[0xE4];
		public:
			ImVec3 viewAngles;
		private:
			byte _0xB8D4[0x10001C];
			usercmd_s userCmd[128];
		public:
			std::int32_t currentCmd;

			usercmd_s* get_user_cmd(std::int32_t cmdnum)
			{
				return &userCmd[cmdnum & 0x7F];
			}
		};
		/*
		//=====================================================================================
		*/
		enum weapon_type_e
		{
			weaptype_bullet,
			weaptype_grenade,
			weaptype_projectile,
			weaptype_binoculars,
			weaptype_gas,
			weaptype_bomb,
			weaptype_mine,
			weaptype_melee,
			weaptype_riotshield,
			weaptype_max
		};
		/*
		//=====================================================================================
		*/
		enum weapon_class_e
		{
			weapclass_rifle,
			weapclass_mg,
			weapclass_smg,
			weapclass_spread,
			weapclass_pistol,
			weapclass_grenade,
			weapclass_rocketlauncher,
			weapclass_turret,
			weapclass_non_player,
			weapclass_gas,
			weapclass_item,
			weapclass_melee,
			weapclass_killstreak_alt_stored_weapon,
			weapclass_pistol_spread,
			weapclass_ball,
			weapclass_max
		};
		/*
		//=====================================================================================
		*/
		enum weapon_fire_type_e
		{
			weapon_firetype_fullauto,
			weapon_firetype_singleshot,
			weapon_firetype_burstfire,
			weapon_firetype_autoburstfire,
			weapon_firetype_stacked,
			weapon_firetype_alllocked,
			weapon_firetype_minigun,
			weapon_firetype_chargeshot,
			weapon_firetype_chargeshotburst,
			weapon_firetype_chargeshotautoburst,
			weapon_firetype_jetgun,
			weapon_firetype_melee,
			weapon_firetype_aimonly,
			weapon_firetype_max,
		};
		/*
		//=====================================================================================
		*/
		enum penetrate_type_e
		{
			penetrate_type_none,
			penetrate_type_small,
			penetrate_type_medium,
			penetrate_type_large,
			penetrate_type_count,
			penetrate_type_max
		};
		/*
		//=====================================================================================
		*/
		struct weapon_def_s
		{
		private:
			byte _0x0[0x6C];
		public:
			weapon_type_e weaponType;
			weapon_class_e weaponClass;
			penetrate_type_e penetrateType;
		private:
			byte _0x78[0xDED];
		public:
			bool bRifleBullet;
		private:
			byte _0xE66[0x267];
		public:
			bool bulletImpactExplode;
		private:
			byte _0x10CE[0x18A];
		public:
			std::float_t adsSpread;
		};
		/*
		//=====================================================================================
		*/
		struct weapon_full_def_s
		{
		public:
			char* internalName;
		private:
			byte _0x8[0x10];
		public:
			weapon_def_s* weaponDef;
			char* displayName;
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		union __m128
		{
		public:
			std::float_t m128_f32[4];
			std::int8_t m128_i8[16];
			std::int16_t m128_i16[8];
			std::int32_t m128_i32[4];
			std::int64_t m128_i64[2];
			std::uint8_t m128_u8[16];
			std::uint16_t m128_u16[8];
			std::uint32_t m128_u32[4];
			std::uint64_t m128_u64[2];
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct float4_1
		{
		public:
			__m128 v;
		};
		/*
		//=====================================================================================
		*/
		struct hybrid_vector
		{
		public:
			float4_1 vec;
		};
		/*
		//=====================================================================================
		*/
		enum trace_brush_type_e
		{
			trace_brushtype_none,
			trace_brushtype_brush,
		};
		/*
		//=====================================================================================
		*/
		enum trace_hit_type_e
		{
			trace_hittype_none,
			trace_hittype_entity,
			trace_hittype_dynent_model,
			trace_hittype_dynent_brush,
			trace_hittype_glass,
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct trace_t
		{
		public:
			hybrid_vector normal;
			std::float_t fraction;
			std::int32_t sflags;
			std::uint32_t cflags;
			trace_brush_type_e brushType;
			std::uint32_t brushId;
			trace_hit_type_e hitType;
			std::uint16_t hitId;
			std::uint16_t modelIndex;
			std::int16_t subModelBoneIndex;
			std::int32_t partName;
			std::int16_t boneIndex;
			std::uint16_t partGroup;
			bool allsolid;
			bool startsolid;
			bool walkable;
			void* staticModel;
			std::int32_t hitPartition;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct BulletTraceResults
		{
		public:
			trace_t trace;
			std::int32_t hitEntNum;
			ImVec3 hitPos;
			bool ignoreHitEnt;
			std::int32_t depthSurfaceType;
			std::int32_t hitSubtargetNum;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct BulletFireParams
		{
		public:
			std::int32_t weaponEntIndex;
			std::int32_t ignoreEntIndex;
			std::float_t damageMultiplier;
			std::int32_t methodOfDeath;
			ImVec3 origStart;
			ImVec3 start;
			ImVec3 end;
			ImVec3 dir;
			ImVec3 origDir;
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct BulletHitInfo
		{
		public:
			BulletFireParams bp;
			BulletTraceResults br;
			BulletFireParams revBp;
			BulletTraceResults revBr;
			bool traceHit;
			bool revTraceHit;
			bool allSolid;
			bool voidFilled;
			std::int32_t sflags;
			std::int32_t sflagsRv;
			std::float_t depth;
			std::float_t range;
			std::float_t damage;
			std::float_t damageReduction;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 16)
		struct BulletPenetrationInfo
		{
		public:
			BulletHitInfo hits[5];
			std::int32_t count;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct screen_placement_s
		{
		public:
			ImVec2 scaleVirtualToReal;
			ImVec2 scaleVirtualToFull;
			ImVec2 scaleRealToVirtual;
			ImVec2 virtualViewableMin;
			ImVec2 virtualViewableMax;
			ImVec2 virtualTweakableMin;
			ImVec2 virtualTweakableMax;
			ImVec2 realViewportBase;
			ImVec2 realViewportSize;
			ImVec2 realViewportMid;
			ImVec2 realViewableMin;
			ImVec2 realViewableMax;
			ImVec2 realTweakableMin;
			ImVec2 realTweakableMax;
			ImVec2 subScreen;
			std::float_t hudSplitscreenScale;
		};
		/*
		//=====================================================================================
		*/
		struct view_port_s
		{
		public:
			std::int32_t width;
			std::int32_t height;
		};
		/*
		//=====================================================================================
		*/
		struct weapon_name_s
		{
		private:
			byte _0x0[0x20];
		public:
			char* displayName;
		private:
			byte _0x28[0x10];
		};
		/*
		//=====================================================================================
		*/
		struct weapon_names_s
		{
		private:
			weapon_name_s weaponName[512];
		public:

			weapon_name_s* get_weapon_name(std::int64_t weapon)
			{
				return &weaponName[weapon & 0x1FF];
			}
		};
		/*
		//=====================================================================================
		*/
		struct orientation_s
		{
		public:
			ImVec3 origin;
			ImVec3 axis[3];
		};
		/*
		//=====================================================================================
		*/
		struct bounds_s
		{
		public:
			ImVec3 midPoint;
			ImVec3 halfSize;
		};
		/*
		//=====================================================================================
		*/
		enum netsrc_t
		{
			NS_NULL = 0xFFFFFFFF,
			NS_CLIENT1 = 0x0,
			NS_CLIENT2 = 0x1,
			NS_CLIENT3 = 0x2,
			NS_CLIENT4 = 0x3,
			NS_SERVER = 0x4,
			NS_MAXCLIENTS = 0x4,
			NS_PACKET = 0x5,
		};
		/*
		//=====================================================================================
		*/
	
		
		
		
		enum PacketModeList
		{
			PACKETDATA_FIRST = 0x0,
			PACKETDATA_UNDEFINED = 0x0,
			PACKETDATA_HEADER = 0x1,
			PACKETDATA_OVERHEAD = 0x2,
			PACKETDATA_DATA = 0x3,
			PACKETDATA_RELIABLEDATA = 0x4,
			PACKETDATA_ZEROFLOAT = 0x5,
			PACKETDATA_SMALLFLOAT = 0x6,
			PACKETDATA_LARGEFLOAT = 0x7,
			PACKETDATA_ZEROINT = 0x8,
			PACKETDATA_SMALLANGLE = 0x9,
			PACKETDATA_ZEROANGLE = 0xA,
			PACKETDATA_TIMEDELTA = 0xB,
			PACKETDATA_TIME = 0xC,
			PACKETDATA_24BITFLAGINDEX = 0xD,
			PACKETDATA_GROUNDENTITY = 0xE,
			PACKETDATA_ENTITYNUM = 0xF,
			PACKETDATA_LASTFIELDCHANGED = 0x10,
			PACKETDATA_NOTNETWORKDATA = 0x11,
			PACKETDATA_ORIGINDELTA = 0x12,
			PACKETDATA_ORIGIN = 0x13,
			NUM_PACKETDATA_MODES = 0x14,
		};
		/*
		//=====================================================================================
		*/
		struct PacketMode
		{
			std::uint32_t start;
			PacketModeList mode;
		};
		/*
		//=====================================================================================
		*/
		struct msg_t
		{
			bool overflowed;
			bool readOnly;
			char* data;
			char* splitData;
			std::int32_t maxsize;
			std::int32_t cursize;
			std::int32_t splitSize;
			std::int32_t readcount;
			std::int32_t bit;
			std::int32_t lastEntityRef;
			bool flush;
			netsrc_t targetLocalNetID;
		};
		/*
		//=====================================================================================
		*/
		enum netadrtype_t
		{
			NA_BOT = 0x0,
			NA_BAD = 0x1,
			NA_LOOPBACK = 0x2,
			NA_RAWIP = 0x3,
			NA_IP = 0x4,
		};
		/*
		//=====================================================================================
		*/
		union netipv4_t
		{
			std::uint8_t octets[4];
			std::uint32_t inaddr;
		};
		/*
		//=====================================================================================
		*/
		struct netadr_t
		{
		public:
			netipv4_t ipv4;
			std::uint16_t port;
			netadrtype_t type;
			netsrc_t localNetID;
		};
		/*
		//=====================================================================================
		*/
		struct client_s
		{
		private:
			byte _0x0[0x2C];
		public:
			netadr_t netadr;
		private:
			byte _0x40[0xE5130];
		};
		/*
		//=====================================================================================
		*/
		struct gentity_s
		{
		private:
			byte _0x0[0x4F8];
		};
		/*
		//=====================================================================================
		*/
		struct user_data_s
		{
		public:
			std::uint64_t xuid;
			char name[32];
		};
		/*
		//=====================================================================================
		*/
		struct client_connection_s
		{
		public:
			std::uint32_t flags;
			std::uint32_t keyCatchers;
			netadr_t serverAddress;
		private:
			byte _0x18[0x4524];
		public:
			std::int32_t serverCommandSequence;
			std::int32_t lastExecutedServerCommand;
			char serverCommands[128][1024];
		private:
			byte _0x24544[0x10];
		public:
			netadr_t remoteAddress;
		private:
			byte _0x24564[0x1214];
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 1)
		struct item_info_s
		{
		private:
			byte _0x0[0x18];
		public:
			byte requiredLevel;
			byte requiredPrestige;
		private:
			byte _0x26[0x1];
		public:
			std::int32_t flags;
		private:
			byte _0x1F[0xB9];
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct item_infos_s
		{
		public:
			item_info_s itemInfo[256];
		private:
			byte _0xD800[0x5D70];
		};
		/*
		//=====================================================================================
		*/
		struct loot_item_s
		{
		public:
			std::uint32_t itemId;
			std::uint32_t quantity;
			std::uint32_t modTime;
			std::uint32_t expireTime;
			std::uint16_t collisionField;
		private:
			byte _0x12[0x2];
		};
		/*
		//=====================================================================================
		*/
		struct player_inventory_data_s
		{
		public:
			loot_item_s lootItem[4000];
			std::int32_t itemCount;
		private:
			byte _0x13884[0x4];
		public:
			std::uint32_t itemFlags;
		private:
			byte _0x1388C[0x41C];
		};
		/*
		//=====================================================================================
		*/
		struct player_status_s
		{
		private:
			byte _0x0[0x50];
		public:
			std::uint32_t flags;
		};
		/*
		//=====================================================================================
		*/
		enum JoinType
		{
			JOIN_TYPE_NORMAL = 0x0,
			JOIN_TYPE_PLAYLIST = 0x1,
			JOIN_TYPE_FRIEND = 0x2,
			JOIN_TYPE_INVITE = 0x3,
			JOIN_TYPE_PARTY = 0x4,
			JOIN_TYPE_GROUPS = 0x5,
			JOIN_TYPE_COUNT = 0x6,
		};
		/*
		//=====================================================================================
		*/
		enum svscmd_type
		{
			SV_CMD_CAN_IGNORE = 0x0,
			SV_CMD_RELIABLE = 0x1,
		};
		/*
		//=====================================================================================
		*/
		enum eModes
		{
			MODE_ZOMBIES = 0x0,
			MODE_MULTIPLAYER = 0x1,
			MODE_CAMPAIGN = 0x2,
			MODE_COUNT = 0x3,
			MODE_INVALID = 0x3,
			MODE_FIRST = 0x0,
		};
		/*
		//=====================================================================================
		*/
		struct bdSecurityID
		{
		public:
			std::uint8_t ab[8];
		}; typedef bdSecurityID XNKID;
		/*
		//=====================================================================================
		*/
#pragma pack(push, 1)
		struct XNADDR
		{
			union addrbuff_u
			{
				struct addrbuff_s
				{
				private:
					byte _0x0[0x1E];
				public:
					netipv4_t ipv4;
					std::uint16_t port;
				private:
					byte _0x24[0x1];
				} ab;

				std::uint8_t bytes[37];
			} addrBuff;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct bdSecurityKey
		{
		public:
			std::uint8_t ab[16];
		}; typedef bdSecurityKey XNKEY;
		/*
		//=====================================================================================
		*/
		struct XSESSION_INFO
		{
			XNKID sessionID;
			XNADDR hostAddress;
			XNKEY keyExchangeKey;
		};
		/*
		//=====================================================================================
		*/
		struct SerializedAdr
		{
		public:
			bool valid;
			XNADDR xnaddr;
		};
		/*
		//=====================================================================================
		*/
		enum LobbyModule
		{
			LOBBY_MODULE_INVALID = 0xFFFFFFFF,
			LOBBY_MODULE_HOST = 0x0,
			LOBBY_MODULE_CLIENT = 0x1,
			LOBBY_MODULE_COUNT = 0x2,
			LOBBY_MODULE_FIRST = 0x0,
			LOBBY_MODULE_LAST = 0x1,
			LOBBY_MODULE_PEER_TO_PEER = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyType
		{
			LOBBY_TYPE_INVALID = 0xFFFFFFFF,
			LOBBY_TYPE_PRIVATE = 0x0,
			LOBBY_TYPE_GAME = 0x1,
			LOBBY_TYPE_TRANSITION = 0x2,
			LOBBY_TYPE_COUNT = 0x3,
			LOBBY_TYPE_FIRST = 0x0,
			LOBBY_TYPE_LAST = 0x2,
			LOBBY_TYPE_AUTO = 0x3,
		};
		/*
		//=====================================================================================
		*/
		struct tls_data_s
		{
		public:
			std::uintptr_t vaInfo;
			std::uintptr_t errorJmpBuf;
			std::uintptr_t traceInfo;
			std::uintptr_t cmdArgs;
			std::uintptr_t errorData;
		};
		/*
		//=====================================================================================
		*/
		struct session_info_s
		{
		public:
			bool inSession;
		private:
			byte _0x1[0x3];
		public:
			netadr_t netAdr;
		private:
			byte _0x14[0x4];
		public:
			time_t lastMessageSentToPeer;
		};
		/*
		//=====================================================================================
		*/
		struct fixed_client_info_s
		{
		public:
			std::uint64_t xuid;
		private:
			byte _0x8[0xB0];
		public:
			char gamerTag[32];
		};
		/*
		//=====================================================================================
		*/
		struct active_client_s
		{
		private:
			byte _0x0[0x4E0];
		public:
			session_info_s sessionInfo[2];
		private:
			byte _0x520[0x28FF0];
		};
		/*
		//=====================================================================================
		*/
		struct host_info_s
		{
		public:
			std::uint64_t xuid;
			char name[32];
			netadr_t netAdr;
			SerializedAdr serializedAdr;
			bdSecurityID secId;
			bdSecurityKey secKey;
			std::uint32_t serverLocation;
		};
		/*
		//=====================================================================================
		*/
		struct session_host_s
		{
		public:
			host_info_s info;
			std::int32_t maxClients;
		};
		/*
		//=====================================================================================
		*/
		struct session_client_s
		{
		private:
			byte _0x0[0x8];
		public:
			active_client_s* activeClient;
		private:
			byte _0x10[0x20];
		};
		/*
		//=====================================================================================
		*/
		struct lobby_session_s
		{
		private:
			byte _0x0[0x60];
		public:
			session_host_s host;
		private:
			byte _0xC0[0x38];
		public:
			session_client_s client[18];
		private:
			byte _0x458[0x1F78];
		};
		/*
		//=====================================================================================
		*/
		enum LocalClientNum_t
		{
			INVALID_LOCAL_CLIENT = 0xFFFFFFFF,
			LOCAL_CLIENT_FIRST = 0x0,
			LOCAL_CLIENT_KEYBOARD_AND_MOUSE = 0x0,
			LOCAL_CLIENT_0 = 0x0,
			LOCAL_CLIENT_1 = 0x1,
			LOCAL_CLIENT_2 = 0x2,
			LOCAL_CLIENT_3 = 0x3,
			LOCAL_CLIENT_COUNT = 0x4,
		};
		/*
		//=====================================================================================
		*/
		enum ControllerIndex_t
		{
			INVALID_CONTROLLER_PORT = 0xFFFFFFFF,
			CONTROLLER_INDEX_FIRST = 0x0,
			CONTROLLER_INDEX_0 = 0x0,
			CONTROLLER_INDEX_1 = 0x1,
			CONTROLLER_INDEX_2 = 0x2,
			CONTROLLER_INDEX_3 = 0x3,
			CONTROLLER_INDEX_COUNT = 0x4,
		};
		/*
		//=====================================================================================
		*/
		struct cmd_args_s
		{
		private:
			std::int32_t nesting;
			LocalClientNum_t localClientNum[8];
			ControllerIndex_t controllerIndex[8];
			std::int32_t argshift[8];
			std::int32_t argc[8];
			const char** argv[8];
			char textPool[8192];
			const char* argvPool[512];
			std::int32_t usedTextPool[8];
			std::int32_t totalUsedArgvPool;
			std::int32_t totalUsedTextPool;
		public:

			char** get_args()
			{
				return std::cocast<char**>(argv[nesting]);
			}

			std::int32_t get_arg_count()
			{
				return argc[nesting];
			}
		};
		/*
		//=====================================================================================
		*/
		struct material_name_s
		{
		public:
			char prefix;
			char type;

			std::uint8_t width;
			std::uint8_t height;
			std::uint8_t length;

			std::string name;
		};
		/*
		//=====================================================================================
		*/
		typedef bool(__fastcall* bullet_trace)(std::int32_t, const BulletFireParams*, BulletTraceResults*, const std::int64_t, const int, int);
		typedef bool(__fastcall* bullet_process)(std::int32_t, BulletFireParams*, BulletTraceResults*, const std::int64_t, const int, const int, const int, int*, bool, std::uint32_t*, void*);
		typedef void(__fastcall* bullet_processReverse)(BulletFireParams*, BulletTraceResults*, BulletFireParams*, BulletTraceResults*, bool, const std::int64_t, const int, int*, bool, std::uint32_t*);
		/*
		//=====================================================================================
		*/
		struct BulletTraceHandler
		{
			bullet_trace bulletTrace;
			bullet_process bulletProcess;
			bullet_processReverse bulletProcessReverse;
		};
		/*
		//=====================================================================================
		*/
		struct InviteMessage
		{
		public:
			XSESSION_INFO sessionInfo;
			bool fromMPInvite;
			bool fromZMInvite;
			bool fromCPInvite;
		};
		/*
		//=====================================================================================
		*/
		enum JoinRejectionReason
		{
			REASON_NONE = 0x0,
			REASON_PARTY_PRIVACY_CLOSED = 0x1,
			REASON_PARTY_PRIVACY_INVITE_ONLY = 0x2,
			REASON_SYSTEMLINK_LOBBY = 0x3,
			REASON_SPLITSCREEN_LOBBY = 0x4,
		};
		/*
		//=====================================================================================
		*/
		enum IMType
		{
			JOIN_REQUEST = 0x0,
			JOIN_REPLY = 0x1,
			INVITE = 0x2,
			UPDATE_INVITE_INFO = 0x3,
			NUM_INSTANT_MESSAGE_TYPES = 0x4,
		};
		/*
		//=====================================================================================
		*/
		struct JoinSessionMessage
		{
		public:
			IMType mType;
			byte _0x4[0x60];
		};
		/*
		//=====================================================================================
		*/
		struct scr_entref_s
		{
		private:
			std::uint16_t entnum;
			std::uint16_t classnum;

		public:
			scr_entref_s(std::uint16_t entitynum, std::uint16_t classnum) : entnum(entitynum), classnum(classnum) {  }
			scr_entref_s() {  }
		};
		/*
		//=====================================================================================
		*/
		enum MsgType
		{
			MESSAGE_TYPE_NONE = 0xFFFFFFFF,
			MESSAGE_TYPE_INFO_REQUEST = 0x0,
			MESSAGE_TYPE_INFO_RESPONSE = 0x1,
			MESSAGE_TYPE_LOBBY_STATE_PRIVATE = 0x2,
			MESSAGE_TYPE_LOBBY_STATE_GAME = 0x3,
			MESSAGE_TYPE_LOBBY_STATE_GAMEPUBLIC = 0x4,
			MESSAGE_TYPE_LOBBY_STATE_GAMECUSTOM = 0x5,
			MESSAGE_TYPE_LOBBY_STATE_GAMETHEATER = 0x6,
			MESSAGE_TYPE_LOBBY_HOST_HEARTBEAT = 0x7,
			MESSAGE_TYPE_LOBBY_HOST_DISCONNECT = 0x8,
			MESSAGE_TYPE_LOBBY_HOST_DISCONNECT_CLIENT = 0x9,
			MESSAGE_TYPE_LOBBY_HOST_LEAVE_WITH_PARTY = 0xA,
			MESSAGE_TYPE_LOBBY_CLIENT_HEARTBEAT = 0xB,
			MESSAGE_TYPE_LOBBY_CLIENT_DISCONNECT = 0xC,
			MESSAGE_TYPE_LOBBY_CLIENT_RELIABLE_DATA = 0xD,
			MESSAGE_TYPE_LOBBY_CLIENT_CONTENT = 0xE,
			MESSAGE_TYPE_LOBBY_MODIFIED_STATS = 0xF,
			MESSAGE_TYPE_JOIN_LOBBY = 0x10,
			MESSAGE_TYPE_JOIN_RESPONSE = 0x11,
			MESSAGE_TYPE_JOIN_AGREEMENT_REQUEST = 0x12,
			MESSAGE_TYPE_JOIN_AGREEMENT_RESPONSE = 0x13,
			MESSAGE_TYPE_JOIN_COMPLETE = 0x14,
			MESSAGE_TYPE_JOIN_MEMBER_INFO = 0x15,
			MESSAGE_TYPE_SERVERLIST_INFO = 0x16,
			MESSAGE_TYPE_PEER_TO_PEER_CONNECTIVITY_TEST = 0x17,
			MESSAGE_TYPE_PEER_TO_PEER_INFO = 0x18,
			MESSAGE_TYPE_LOBBY_MIGRATE_TEST = 0x19,
			MESSAGE_TYPE_LOBBY_MIGRATE_ANNOUNCE_HOST = 0x1A,
			MESSAGE_TYPE_LOBBY_MIGRATE_START = 0x1B,
			MESSAGE_TYPE_INGAME_MIGRATE_TO = 0x1C,
			MESSAGE_TYPE_INGAME_MIGRATE_NEW_HOST = 0x1D,
			MESSAGE_TYPE_VOICE_PACKET = 0x1E,
			MESSAGE_TYPE_VOICE_RELAY_PACKET = 0x1F,
			MESSAGE_TYPE_DEMO_STATE = 0x20,
			MESSAGE_TYPE_COUNT = 0x21,
		};
		/*
		//=====================================================================================
		*/
		struct Msg_InfoRequest
		{
		public:
			std::uint32_t nonce;
		};
		/*
		//=====================================================================================
		*/
		enum LobbyNetworkMode
		{
			LOBBY_NETWORKMODE_INVALID = 0xFFFFFFFF,
			LOBBY_NETWORKMODE_UNKNOWN = 0x0,
			LOBBY_NETWORKMODE_LAN = 0x1,
			LOBBY_NETWORKMODE_LIVE = 0x2,
			LOBBY_NETWORKMODE_COUNT = 0x3,
			LOBBY_NETWORKMODE_LOCAL = 0x1,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyMainMode
		{
			LOBBY_MAINMODE_INVALID = 0xFFFFFFFF,
			LOBBY_MAINMODE_CP = 0x0,
			LOBBY_MAINMODE_MP = 0x1,
			LOBBY_MAINMODE_ZM = 0x2,
			LOBBY_MAINMODE_COUNT = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyMode
		{
			LOBBY_MODE_INVALID = 0xFFFFFFFF,
			LOBBY_MODE_PUBLIC = 0x0,
			LOBBY_MODE_CUSTOM = 0x1,
			LOBBY_MODE_THEATER = 0x2,
			LOBBY_MODE_ARENA = 0x3,
			LOBBY_MODE_FREERUN = 0x4,
			LOBBY_MODE_COUNT = 0x5,
		};
		/*
		//=====================================================================================
		*/
		struct LobbyParams
		{
		public:
			LobbyNetworkMode networkMode;
			LobbyMainMode mainMode;
		};
		/*
		//=====================================================================================
		*/
		struct InfoResponseLobby
		{
		public:
			bool isValid;
			std::uint64_t hostXuid;
			char hostName[32];
			bdSecurityID secId;
			bdSecurityKey secKey;
			SerializedAdr serializedAdr;
			LobbyParams lobbyParams;
		};
		/*
		//=====================================================================================
		*/
		struct Msg_InfoResponse
		{
		public:
			std::uint32_t nonce;
			std::int32_t uiScreen;
			char natType;
			InfoResponseLobby lobby[2];
		};
		/*
		//=====================================================================================
		*/
		struct Msg_ModifiedStats
		{
		public:
			std::int32_t statsSize;
			std::uint8_t statsBuffer[65536];
		};
		/*
		//=====================================================================================
		*/
		struct Msg_VoicePacket
		{
		public:
			LobbyType lobbyType;
			std::uint8_t talkerIndex;
			std::int32_t relayBits;
			std::uint16_t sizeofVoiceData;
			std::uint8_t numPacketsInData;
			std::uint8_t voiceData[1198];
		};
		/*
		//=====================================================================================
		*/
		enum PackageType
		{
			PACKAGE_TYPE_NONE = 0x0,
			PACKAGE_TYPE_WRITE = 0x1,
			PACKAGE_TYPE_READ = 0x2,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyMsgElementType
		{
			MESSAGE_ELEMENT_INT32 = 0x0,
			MESSAGE_ELEMENT_UINT32 = 0x1,
			MESSAGE_ELEMENT_INT16 = 0x2,
			MESSAGE_ELEMENT_UINT16 = 0x3,
			MESSAGE_ELEMENT_INT8 = 0x4,
			MESSAGE_ELEMENT_UINT8 = 0x5,
			MESSAGE_ELEMENT_INT64 = 0x6,
			MESSAGE_ELEMENT_UINT64 = 0x7,
			MESSAGE_ELEMENT_FLOAT = 0x8,
			MESSAGE_ELEMENT_XUID = 0x9,
			MESSAGE_ELEMENT_STRING = 0xA,
			MESSAGE_ELEMENT_GLOB = 0xB,
			MESSAGE_ELEMENT_ARRAY_BEGIN = 0xC,
			MESSAGE_ELEMENT_ARRAY_ELEMENT = 0xD,
			MESSAGE_ELEMENT_ARRAY_END = 0xE,
			MESSAGE_ELEMENT_DEBUG_START = 0xF,
			MESSAGE_ELEMENT_DEBUG_END = 0x10,
			MESSAGE_ELEMENT_COUNT = 0x11,
		};
		/*
		//=====================================================================================
		*/
		struct LobbyMsg
		{
		public:
			msg_t msg;
			MsgType msgType;
			PackageType packageType;
			char encodeFlags;
		};
		/*
		//=====================================================================================
		*/
		enum LobbyDisconnectClient
		{
			LOBBY_DISCONNECT_CLIENT_INVALID = 0xFFFFFFFF,
			LOBBY_DISCONNECT_CLIENT_DROP = 0x0,
			LOBBY_DISCONNECT_CLIENT_KICK = 0x1,
			LOBBY_DISCONNECT_CLIENT_BADDLC = 0x2,
			LOBBY_DISCONNECT_CLIENT_KICK_PARTY = 0x3,
			LOBBY_DISCONNECT_CLIENT_HOSTRELOAD = 0x4,
			LOBBY_DISCONNECT_CLIENT_NOPARTYCHAT = 0x5,
		};
		/*
		//=====================================================================================
		*/
		enum errorCode
		{
			ERROR_NONE = 0x0,
			ERROR_FATAL = 0x1,
			ERROR_DROP = 0x2,
			ERROR_FROM_STARTUP = 0x4,
			ERROR_SERVERDISCONNECT = 0x8,
			ERROR_DISCONNECT = 0x10,
			ERROR_SCRIPT = 0x20,
			ERROR_SCRIPT_DROP = 0x40,
			ERROR_LOCALIZATION = 0x80,
			ERROR_UI = 0x100,
			ERROR_LUA = 0x200,
			ERROR_SOFTRESTART = 0x400,
			ERROR_SOFTRESTART_KEEPDW = 0x800,
			ERROR_SOFTRESTART_SILENT = 0x1000,
		};
		/*
		//=====================================================================================
		*/
		struct trans_player_state_s
		{
		public:
			std::int32_t eFlags;
			std::int32_t otherFlags;
			std::int32_t damageEvent;
			std::int16_t predictableEventSequence;
			std::int32_t predictableEvents[4];
			std::int16_t unpredictableEventSequence;
			std::int32_t unpredictableEvents[4];
		};
		/*
		//=====================================================================================
		*/
		struct view_state_s
		{
		public:
			player_state_s* ps;
			std::int32_t damageTime;
			std::int32_t time;
			std::float_t v_dmg_pitch;
			std::float_t v_dmg_roll;
			std::float_t xySpeed;
			std::float_t frameTime;
			std::float_t lastIdleFactor;
		};
		/*
		//=====================================================================================
		*/
		struct config_strings_s
		{
		private:
			std::int32_t stringOffsets[3630];
			std::uint32_t stringChecksums[3630];
			char stringData[65536];
		public:

			const char* get_value(std::int32_t index)
			{
				return &stringData[stringOffsets[index]];
			}
		};
		/*
		//=====================================================================================
		*/
		enum NetChanMsgType_e
		{
			NETCHAN_INVALID_CHANNEL = 0xFFFFFFFF,
			NETCHAN_SNAPSHOT = 0x0,
			NETCHAN_CLIENTMSG = 0x1,
			NETCHAN_VOICE = 0x2,
			NETCHAN_LOBBY_VOICE = 0x3,
			NETCHAN_LOBBYPRIVATE_STATE = 0x4,
			NETCHAN_LOBBYPRIVATE_HEARTBEAT = 0x5,
			NETCHAN_LOBBYPRIVATE_RELIABLE = 0x6,
			NETCHAN_LOBBYPRIVATE_UNRELIABLE = 0x7,
			NETCHAN_LOBBYPRIVATE_MIGRATE = 0x8,
			NETCHAN_LOBBYGAME_STATE = 0x9,
			NETCHAN_LOBBYGAME_HEARTBEAT = 0xA,
			NETCHAN_LOBBYGAME_RELIABLE = 0xB,
			NETCHAN_LOBBYGAME_UNRELIABLE = 0xC,
			NETCHAN_LOBBYGAME_MIGRATE = 0xD,
			NETCHAN_LOBBYTRANSITION_STATE = 0xE,
			NETCHAN_LOBBYTRANSITION_HEARTBEAT = 0xF,
			NETCHAN_LOBBYTRANSITION_RELIABLE = 0x10,
			NETCHAN_LOBBYTRANSITION_UNRELIABLE = 0x11,
			NETCHAN_LOBBYTRANSITION_MIGRATE = 0x12,
			NETCHAN_LOBBY_JOIN = 0x13,
			NETCHAN_PTP = 0x14,
			NETCHAN_CLIENT_CONTENT = 0x15,
			NETCHAN_CLIENT_CMD = 0x16,
			NETCHAN_CONNECTIONLESS_CMD = 0x17,
			NETCHAN_TEST = 0x18,
			NETCHAN_MAX_CHANNELS = 0x19,
		};
		/*
		//=====================================================================================
		*/
		enum InventoryCurrency
		{
			INVENTORY_CURRENCY_INVALID = 0xFFFFFFFF,
			INVENTORY_CURRENCY_COD_POINTS = 0x0,
			INVENTORY_CURRENCY_MP_LOOT_XP = 0x1,
			INVENTORY_CURRENCY_MP_CRYPTO_KEYS = 0x2,
			INVENTORY_CURRENCY_ZM_VIALS = 0x3,
			INVENTORY_CURRENCY_MP_BUNDLE_ITEM = 0x4,
			INVENTORY_CURRENCY_RESERVE_2 = 0x5,
			INVENTORY_CURRENCY_RESERVE_3 = 0x6,
			INVENTORY_CURRENCY_RESERVE_4 = 0x7,
			INVENTORY_CURRENCY_RESERVE_5 = 0x8,
			INVENTORY_CURRENCY_RESERVE_6 = 0x9,
			INVENTORY_CURRENCY_RESERVE_7 = 0xA,
			INVENTORY_CURRENCY_RESERVE_8 = 0xB,
			INVENTORY_CURRENCY_RESERVE_9 = 0xC,
			INVENTORY_CURRENCY_RESERVE_10 = 0xD,
			INVENTORY_CURRENCY_RESERVE_11 = 0xE,
			INVENTORY_CURRENCY_RESERVE_12 = 0xF,
			INVENTORY_CURRENCY_RESERVE_13 = 0x10,
			INVENTORY_CURRENCY_RESERVE_14 = 0x11,
			INVENTORY_CURRENCY_RESERVE_15 = 0x12,
			INVENTORY_CURRENCY_RESERVE_16 = 0x13,
			INVENTORY_CURRENCY_COUNT = 0x14,
		};
		/*
		//=====================================================================================
		*/
		enum PlayerRoleButtonOverrideTypes
		{
			PRBO_NONE = 0x0,
			PRBO_FRAG = 0x1,
			PRBO_SMOKE = 0x2,
			PRBO_SPECIAL_OFFHAND = 0x3,
			PRBO_WEAPON_SWITCH_HERO = 0x4,
			PRBO_COUNT = 0x5,
		};
		/*
		//=====================================================================================
		*/
		enum statsLocation
		{
			STATS_LOCATION_NORMAL = 0x0,
			STATS_LOCATION_FORCE_NORMAL = 0x1,
			STATS_LOCATION_STABLE = 0x2,
			STATS_LOCATION_OTHERPLAYER = 0x3,
			STATS_LOCATION_COUNT = 0x4,
		};
		/*
		//=====================================================================================
		*/
		enum StorageFileType
		{
			STORAGE_COMMON_SETTINGS = 0x0,
			STORAGE_PROFILE_SHOUTCASTER = 0x1,
			STORAGE_CP_SAVEGAME_ONLINE = 0x2,
			STORAGE_CP_SAVEGAME_OFFLINE = 0x3,
			STORAGE_CPNIGHTMARE_SAVEGAME_ONLINE = 0x4,
			STORAGE_CPNIGHTMARE_SAVEGAME_OFFLINE = 0x5,
			STORAGE_CP_STATS_ONLINE = 0x6,
			STORAGE_CP_STATS_OFFLINE = 0x7,
			STORAGE_CP_STATS_NIGHTMARE_ONLINE = 0x8,
			STORAGE_CP_STATS_NIGHTMARE_OFFLINE = 0x9,
			STORAGE_CP_LOADOUTS = 0xA,
			STORAGE_CP_LOADOUTS_OFFLINE = 0xB,
			STORAGE_MP_STATS_ONLINE = 0xC,
			STORAGE_MP_STATS_OFFLINE = 0xD,
			STORAGE_MP_LOADOUTS = 0xE,
			STORAGE_MP_LOADOUTS_CUSTOM = 0xF,
			STORAGE_MP_LOADOUTS_ARENA = 0x10,
			STORAGE_MP_LOADOUTS_OFFLINE = 0x11,
			STORAGE_MP_CLASS_SETS = 0x12,
			STORAGE_ZM_STATS_ONLINE = 0x13,
			STORAGE_ZM_STATS_OFFLINE = 0x14,
			STORAGE_ZM_LOADOUTS = 0x15,
			STORAGE_ZM_LOADOUTS_OFFLINE = 0x16,
			STORAGE_FR_STATS_ONLINE = 0x17,
			STORAGE_FR_STATS_OFFLINE = 0x18,
			STORAGE_PAINTSHOP_DATA = 0x19,
			STORAGE_GUNSMITH = 0x1A,
			STORAGE_PAINTJOBS = 0x1B,
			STORAGE_EMBLEMS = 0x1C,
			STORAGE_DEFAULT_EMBLEMS = 0x1D,
			STORAGE_EMBLEMS_LOOT = 0x1E,
			STORAGE_CUSTOM_GAMES = 0x1F,
			STORAGE_OFFICIAL_CUSTOM_GAMES = 0x20,
			STORAGE_EXTERNAL_DATA = 0x21,
			STORAGE_FILE_COUNT = 0x22,
			STORAGE_FILE_FIRST = 0x0,
			STORAGE_FILE_INVALID = 0xFFFFFFFF,
		};
		/*
		//=====================================================================================
		*/
		struct DDLState
		{
		public:
			bool isValid;
			std::int32_t offset;
			std::int32_t arrayIndex;
			void* member;
			const void* ddlDef;
		};
		/*
		//=====================================================================================
		*/
		struct DDLContext
		{
		public:
			void* buff;
			std::int32_t len;
			const void* def;
			void(*writeCB)(DDLContext*, void*);
			void* userData;
		};
		/*
		//=====================================================================================
		*/
		enum chatChannel_e
		{
			CHAT_CHANNEL_ALL = 0x0,
			CHAT_CHANNEL_TEAM = 0x1,
			CHAT_CHANNEL_PARTY = 0x2,
			CHAT_CHANNEL_COUNT = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum meansOfDeath_t
		{
			MOD_UNKNOWN = 0x0,
			MOD_PISTOL_BULLET = 0x1,
			MOD_RIFLE_BULLET = 0x2,
			MOD_GRENADE = 0x3,
			MOD_GRENADE_SPLASH = 0x4,
			MOD_PROJECTILE = 0x5,
			MOD_PROJECTILE_SPLASH = 0x6,
			MOD_MELEE = 0x7,
			MOD_MELEE_WEAPON_BUTT = 0x8,
			MOD_MELEE_ASSASSINATE = 0x9,
			MOD_HEAD_SHOT = 0xA,
			MOD_CRUSH = 0xB,
			MOD_TELEFRAG = 0xC,
			MOD_FALLING = 0xD,
			MOD_SUICIDE = 0xE,
			MOD_TRIGGER_HURT = 0xF,
			MOD_EXPLOSIVE = 0x10,
			MOD_IMPACT = 0x11,
			MOD_BURNED = 0x12,
			MOD_ELECTROCUTED = 0x13,
			MOD_HIT_BY_OBJECT = 0x14,
			MOD_DROWN = 0x15,
			MOD_GAS = 0x16,
			MOD_POST_GAME = 0x17,
			MOD_NUM = 0x18,
		};
		/*
		//=====================================================================================
		*/
		using StorageSlot = std::int32_t;
		using max_lobby_msg_buf = char[0x20000];
		using XUID = std::uint64_t;
		using LobbyLeaderActivity = std::int32_t;
		using LobbyID = std::uint64_t;
		using BGEmblemBackgroundID = std::int16_t;
		using gametypesettings_t = std::uint8_t[0xC000];
		/*
		//=====================================================================================
		*/
		enum PartyPrivacy
		{
			PARTY_PRIVACY_OPEN = 0x0,
			PARTY_PRIVACY_FRIENDS_ONLY = 0x1,
			PARTY_PRIVACY_INVITE_ONLY = 0x2,
			PARTY_PRIVACY_CLOSED = 0x3,
			PARTY_PRIVACY_COUNT = 0x4,
		};
		/*
		//=====================================================================================
		*/
		enum SessionStatus
		{
			SESSION_STATUS_INVALID = 0xFFFFFFFF,
			SESSION_STATUS_IDLE = 0x0,
			SESSION_STATUS_JOIN = 0x1,
			SESSION_STATUS_MERGE = 0x2,
			SESSION_STATUS_MIGRATE = 0x3,
			SESSION_STATUS_PAUSED = 0x4,
			SESSION_STATUS_COUNT = 0x5,
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 2)
		struct ClientProgression
		{
			std::uint8_t rank;
			std::uint8_t prestige;
			std::uint16_t paragonRank;
			std::uint8_t paragonIconId;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct BubbleGumBuffsLobbyClientInfo
		{
			std::uint8_t bubbleGumBuffs[5];
			std::uint8_t bubbleGumBuffConsumableCount[5];
		};
		/*
		//=====================================================================================
		*/
		struct CharacterCustomizationLobbyClientInfo
		{
			std::uint8_t selectedCharacterType;
			std::uint8_t selectedCharacterMode;
			std::uint8_t selectedHeadType;
			std::uint8_t selectedLoadoutSlot;
			std::uint8_t selectedCharacterItem[2];
			std::uint8_t selectedCharacterItemColors[2][3];
		};
		/*
		//=====================================================================================
		*/
		struct Variant
		{
			char variantName[17];
			std::int32_t attachment[8];
			std::uint8_t attachmentVariant[8];
			std::uint8_t camoIndex;
			std::int32_t paintjobSlot;
			std::int32_t paintjobIndex;
			std::int32_t weaponIndex;
			std::int32_t variantIndex;
			std::int32_t sortIndex;
		};
		/*
		//=====================================================================================
		*/
		struct CollectibleInfo
		{
			bool isSet;
			char mapName[32];
			std::uint8_t collectibleIndex;
		};
		/*
		//=====================================================================================
		*/
		enum connstate_t
		{
			CA_DISCONNECTED = 0x0,
			CA_CINEMATIC = 0x1,
			CA_UICINEMATIC = 0x2,
			CA_LOGO = 0x3,
			CA_CONNECTING = 0x4,
			CA_UISERVER = 0x5,
			CA_CONFIRMLOADING = 0x6,
			CA_CONNECTED = 0x7,
			CA_SENDINGDATA = 0x8,
			CA_SENDINGDATA_WAIT = 0x9,
			CA_LOADING = 0xA,
			CA_PRIMED = 0xB,
			CA_ACTIVE = 0xC,
			CA_COUNT = 0xD,
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct MutableClientInfo
		{
			LobbyID lobbyID;
			char clantag[5];
			ClientProgression progression[3];
			BubbleGumBuffsLobbyClientInfo bubbleGumInfo;
			int arenaPoints;
			float arenaSkill;
			float arenaVariance;
			CharacterCustomizationLobbyClientInfo heroInfo;
			Variant showcaseWeapon;
			CollectibleInfo collectibles[9];
			uint32_t flags;
			BGEmblemBackgroundID backgroundId;
			uint32_t musicUnlocks[3];
			float skillRating;
			float skillVariance;
			int8_t defaultEmblemIndex;
			int8_t easterEggBits;
			uint16_t unlockedMedals;
			uint32_t profileNonce;
			std::uint8_t ddlBuff[512];
			std::uint16_t ddlBuffSize;
			uint32_t probationEndTime[2];
			uint32_t dlcBits;
			uint32_t doubleXPGroupMask;
			bool isSplitscreenClient;
			bool isInPlatformParty;
			bool isInFrontend;
			connstate_t connectionState;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct MsgMutableClientInfo
		{
			MutableClientInfo mutableClientInfo;
		};
		/*
		//=====================================================================================
		*/
		struct MsgClientLobbyInfo
		{
			XUID xuid;
			std::uint8_t clientNum;
			std::int8_t clientType;
			char gamertag[32];
			LobbyID lobbyID;
			std::int32_t qport;
			std::uint8_t latencyBand;
			MsgMutableClientInfo mutableClientInfoMsg;
			std::int32_t score;
			std::int32_t connectivityBits;
			SerializedAdr serializedAdr;
			netsrc_t localNetID;
			std::uint32_t joinOrder;
			std::uint32_t dlcBits;
		};
		/*
		//=====================================================================================
		*/
		struct MsgHostMigrateInfo
		{
			std::uint8_t indexBits;
			std::int32_t lasthostTimeMS;
			XUID migrateNominees[18];
		};
		/*
		//=====================================================================================
		*/
		struct PlatformSessionData
		{
			char sessionId[64];
			char sessionInfo[64];
		};
		/*
		//=====================================================================================
		*/
		struct MsgPlatformSessionData
		{
			PlatformSessionData platformSessionData;
		};
		/*
		//=====================================================================================
		*/
		struct Msg_LobbyState
		{
			std::int32_t stateNum;
			LobbyNetworkMode lobbyNetworkMode;
			LobbyMainMode lobbyMainMode;
			PartyPrivacy partyPrivacy;
			LobbyType lobbyType;
			LobbyMode lobbyMode;
			SessionStatus status;
			std::int32_t uiScreen;
			LobbyLeaderActivity uiLeaderActivity;
			char key[32];
			XUID clientLeader;
			XUID platformSessionID;
			std::int32_t maxClients;
			bool isAdvertised;
			std::int32_t clientCount;
			MsgClientLobbyInfo clientList[18];
			MsgHostMigrateInfo migrateInfo;
			MsgPlatformSessionData platformData;
			char ugcName[32];
			std::uint32_t ugcVersion;
		};
		/*
		//=====================================================================================
		*/
		enum GameServerStatus
		{
			GAME_SERVER_STATUS_IDLE = 0x0,
			GAME_SERVER_STATUS_PRELOADING = 0x1,
			GAME_SERVER_STATUS_STARTING_SERVER = 0x2,
			GAME_SERVER_STATUS_MIGRATING = 0x3,
			GAME_SERVER_STATUS_RUNNING = 0x4,
			GAME_SERVER_STATUS_RUNNING_DEMO = 0x5,
		};
		/*
		//=====================================================================================
		*/
		struct uint128_t
		{
			std::uint64_t lower;
			std::uint64_t upper;
		};
		/*
		//=====================================================================================
		*/
		enum eGameModes
		{
			MODE_GAME_MATCHMAKING_PLAYLIST = 0x0,
			MODE_GAME_MATCHMAKING_MANUAL = 0x1,
			MODE_GAME_DEFAULT = 0x2,
			MODE_GAME_LEAGUE = 0x3,
			MODE_GAME_FREERUN = 0x4,
			MODE_GAME_THEATER = 0x5,
			MODE_GAME_COUNT = 0x6,
			MODE_GAME_INVALID = 0x6,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyPregameState
		{
			LOBBY_PREGAME_STATE_IDLE = 0x0,
			LOBBY_PREGAME_STATE_ITEM_VOTE = 0x1,
			LOBBY_PREGAME_STATE_CHARACTER_DRAFT = 0x2,
			LOBBY_PREGAME_STATE_CAC_EDIT = 0x3,
			LOBBY_PREGAME_STATE_SCORESTREAK_EDIT = 0x4,
			LOBBY_PREGAME_STATE_LAUNCH_GAME = 0x5,
			LOBBY_PREGAME_STATE_COUNT = 0x6,
		};
		/*
		//=====================================================================================
		*/
		enum VoteItemType
		{
			VOTE_ITEM_TYPE_INVALID = 0x0,
			VOTE_ITEM_TYPE_ITEM = 0x1,
			VOTE_ITEM_TYPE_ATTACHMENT = 0x2,
			VOTE_ITEM_TYPE_ITEM_ATTACHMENT = 0x3,
			VOTE_ITEM_TYPE_ATTACHMENT_GROUP = 0x4,
			VOTE_ITEM_TYPE_COUNT = 0x5,
		};
		/*
		//=====================================================================================
		*/
		enum itemGroup_t
		{
			ITEMGROUP_SMG = 0x0,
			ITEMGROUP_FIRST = 0x0,
			ITEMGROUP_ASSAULT = 0x1,
			ITEMGROUP_CQB = 0x2,
			ITEMGROUP_LMG = 0x3,
			ITEMGROUP_SNIPER = 0x4,
			ITEMGROUP_PISTOL = 0x5,
			ITEMGROUP_LAUNCHER = 0x6,
			ITEMGROUP_KNIFE = 0x7,
			ITEMGROUP_SPECIAL = 0x8,
			ITEMGROUP_SHOTGUN = 0x9,
			ITEMGROUP_EXPLOSIVE = 0xA,
			ITEMGROUP_GRENADE = 0xB,
			ITEMGROUP_MASTERKEY = 0xC,
			ITEMGROUP_GRENADELAUNCHER = 0xD,
			ITEMGROUP_FLAMETHROWER = 0xE,
			ITEMGROUP_SPECIALTY = 0xF,
			ITEMGROUP_SPECIALGRENADE = 0x10,
			ITEMGROUP_MISCWEAPON = 0x11,
			ITEMGROUP_FEATURE = 0x12,
			ITEMGROUP_BONUSCARD = 0x13,
			ITEMGROUP_CYBERCOM_TACRIG = 0x14,
			ITEMGROUP_GLOBAL_ITEMS_START = 0x15,
			ITEMGROUP_KILLSTREAK = 0x15,
			ITEMGROUP_HERO = 0x16,
			ITEMGROUP_BUBBLEGUM = 0x17,
			ITEMGROUP_BUBBLEGUM_CONSUMABLE = 0x18,
			ITEMGROUP_CYBERCOM_CORE = 0x19,
			ITEMGROUP_CYBERCOM_ABILITIES = 0x1A,
			ITEMGROUP_COUNT = 0x1B,
			ITEMGROUP_INVALID = 0xFFFFFFFF,
		};
		/*
		//=====================================================================================
		*/
		enum eAttachment
		{
			ATTACHMENT_NOT_FOUND = 0xFFFFFFFF,
			ATTACHMENT_NONE = 0x0,
			ATTACHMENT_TYPE_FIRST = 0x1,
			ATTACHMENT_ACOG = 0x1,
			ATTACHMENT_CLANTAG = 0x2,
			ATTACHMENT_DAMAGE = 0x3,
			ATTACHMENT_DUALCLIP = 0x4,
			ATTACHMENT_DUALOPTIC = 0x5,
			ATTACHMENT_DW = 0x6,
			ATTACHMENT_DYNZOOM = 0x7,
			ATTACHMENT_EXTBARREL = 0x8,
			ATTACHMENT_EXTCLIP = 0x9,
			ATTACHMENT_FASTADS = 0xA,
			ATTACHMENT_FASTRELOAD = 0xB,
			ATTACHMENT_FMJ = 0xC,
			ATTACHMENT_GL = 0xD,
			ATTACHMENT_GADGET_MOD_0 = 0xE,
			ATTACHMENT_GADGET_MOD_TAKE_TWO = 0xE,
			ATTACHMENT_GADGET_MOD_1 = 0xF,
			ATTACHMENT_GADGET_MOD_2 = 0x10,
			ATTACHMENT_GADGET_MOD_3 = 0x11,
			ATTACHMENT_GADGET_MOD_4 = 0x12,
			ATTACHMENT_GADGET_MOD_5 = 0x13,
			ATTACHMENT_GRIP = 0x14,
			ATTACHMENT_HOLO = 0x15,
			ATTACHMENT_IR = 0x16,
			ATTACHMENT_IRONSIGHTS = 0x17,
			ATTACHMENT_KILLCOUNTER = 0x18,
			ATTACHMENT_MK = 0x19,
			ATTACHMENT_MMS = 0x1A,
			ATTACHMENT_NOTRACER = 0x1B,
			ATTACHMENT_PRECISION = 0x1C,
			ATTACHMENT_QUICKDRAW = 0x1D,
			ATTACHMENT_RANGEFINDER = 0x1E,
			ATTACHMENT_RECON = 0x1F,
			ATTACHMENT_REDDOT = 0x20,
			ATTACHMENT_REFLEX = 0x21,
			ATTACHMENT_RF = 0x22,
			ATTACHMENT_SELECTFIRE = 0x23,
			ATTACHMENT_STACKFIRE = 0x24,
			ATTACHMENT_STALKER = 0x25,
			ATTACHMENT_STEADYAIM = 0x26,
			ATTACHMENT_SUPPLY = 0x27,
			ATTACHMENT_SUPPRESSED = 0x28,
			ATTACHMENT_SWAYREDUC = 0x29,
			ATTACHMENT_TACKNIFE = 0x2A,
			ATTACHMENT_VZOOM = 0x2B,
			ATTACHMENT_TYPE_LAST = 0x2B,
			ATTACHMENT_TYPE_COUNT = 0x2C,
			ATTACHMENT_INVALID = 0x2C,
		};
		/*
		//=====================================================================================
		*/
		enum VoteType
		{
			VOTE_TYPE_INVALID = 0x0,
			VOTE_TYPE_BAN = 0x1,
			VOTE_TYPE_PROTECT = 0x2,
			VOTE_TYPE_COUNT = 0x3,
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct ItemVote
		{
			XUID clientXuid;
			VoteItemType itemType;
			std::uint32_t itemIndex;
			itemGroup_t itemGroup;
			eAttachment attachment;
			VoteType voteType;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		enum team_t
		{
			TEAM_FREE = 0x0,
			TEAM_BAD = 0x0,
			TEAM_DEAD = 0x0,
			TEAM_ALLIES = 0x1,
			TEAM_AXIS = 0x2,
			TEAM_THREE = 0x3,
			TEAM_FOUR = 0x4,
			TEAM_FIVE = 0x5,
			TEAM_SIX = 0x6,
			TEAM_SEVEN = 0x7,
			TEAM_EIGHT = 0x8,
			TEAM_NINE = 0x9,
			TEAM_TEN = 0xA,
			TEAM_ELEVEN = 0xB,
			TEAM_TWELVE = 0xC,
			TEAM_THIRTEEN = 0xD,
			TEAM_FOURTEEN = 0xE,
			TEAM_FIFTEEN = 0xF,
			TEAM_SIXTEEN = 0x10,
			TEAM_SEVENTEEN = 0x11,
			TEAM_EIGHTEEN = 0x12,
			TEAM_NEUTRAL = 0x13,
			TEAM_SPECTATOR = 0x14,
			TEAM_NUM_PLAYING_TEAMS = 0x14,
			TEAM_NUM_TEAMS = 0x15,
			TEAM_LOCALPLAYERS = 0x16,
			TEAM_FIRST_PLAYING_TEAM = 0x1,
			TEAM_LAST_PLAYING_TEAM = 0x13,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyMapVote
		{
			LOBBY_MAPVOTE_INVALID = 0xFFFFFFFF,
			LOBBY_MAPVOTE_NONE = 0x0,
			LOBBY_MAPVOTE_NEXT = 0x1,
			LOBBY_MAPVOTE_PREVIOUS = 0x2,
			LOBBY_MAPVOTE_RANDOM = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum LobbyClientPregameState
		{
			LOBBY_CLIENT_PREGAME_STATE_IDLE = 0x0,
			LOBBY_CLIENT_PREGAME_STATE_SELECTING = 0x1,
			LOBBY_CLIENT_PREGAME_STATE_SELECTED = 0x2,
			LOBBY_CLIENT_PREGAME_STATE_SELECTION_FORCED = 0x3,
			LOBBY_CLIENT_PREGAME_STATE_SELECTION_COMPLETE = 0x4,
			LOBBY_CLIENT_PREGAME_STATE_RESET = 0x5,
			LOBBY_CLIENT_PREGAME_STATE_END = 0x6,
			LOBBY_CLIENT_PREGAME_STATE_COUNT = 0x7,
		};
		/*
		//=====================================================================================
		*/
		enum heroLoadoutTypes_e
		{
			HERO_LOADOUT_TYPE_INVALID = 0xFFFFFFFF,
			HERO_LOADOUT_TYPE_FIRST = 0x0,
			HERO_LOADOUT_TYPE_WEAPON = 0x0,
			HERO_LOADOUT_TYPE_GADGET = 0x1,
			HERO_LOADOUT_TYPE_COUNT = 0x2,
		};
		/*
		//=====================================================================================
		*/
		struct CharacterSelection
		{
			std::uint32_t characterIndex;
			heroLoadoutTypes_e loadoutType;
		};
		/*
		//=====================================================================================
		*/
		struct GameClientData
		{
			team_t team;
			LobbyMapVote mapVote;
			bool readyUp;
			LobbyClientPregameState pregameState;
			std::int32_t pregamePosition;
			bool pregameEditComplete;
			std::uint32_t itemVoteCount;
			CharacterSelection characterSelection;
		};
		/*
		//=====================================================================================
		*/
		struct CustomGameDetails
		{
			char name[64];
			bool isOfficial;
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 4)
		struct GameData
		{
			GameServerStatus serverStatus;
			std::int32_t launchNonce;
			uint128_t matchHash;
			eGameModes gameMode;
			char gameType[32];
			char mapName[32];
			char ugcName[32];
			std::uint32_t ugcVersion;
			std::int32_t status;
			std::int32_t statusValue;
			LobbyPregameState pregameState;
			std::uint32_t pregameVoteCount;
			ItemVote pregameVotes[216];
			std::int32_t playlistId;
			std::int32_t playlistCurrentEntry;
			std::uint8_t playlistLastEntries[8];
			std::uint8_t playlistNext;
			std::uint8_t playlistPrev;
			std::uint8_t playlistPrevCount;
			GameClientData client[18];
			char cpQueuedLevel[32];
			bool loadingMovieSkipped;
			char demoName[32];
			std::uint64_t fileId;
			std::int32_t fileSize;
			bool isUserFile;
			bool isLiveStream;
			XUID authorXUID;
			eModes mainMode;
			char demoMode[32];
			char fileCategory[32];
			CustomGameDetails customGameDetails;
			bool dirty;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct Msg_LobbyStateGame
		{
			Msg_LobbyState core;
			GameData dataGame;
			std::int32_t compressedBufferSize;
			gametypesettings_t compressedBuffer;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
#pragma pack(push, 8)
		struct StringTableCell
		{
			const char* string;
			std::int32_t hash;
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct StringTable
		{
			const char* name;
			std::int32_t columnCount;
			std::int32_t rowCount;
			StringTableCell* values;
			std::int16_t* cellIndex;
		};
		/*
		//=====================================================================================
		*/
		struct dvar_t;
		typedef uint32_t dvarStrHash_t;
		/*
		//=====================================================================================
		*/
		enum dvarType_t
		{
			DVAR_TYPE_INVALID = 0x0,
			DVAR_TYPE_BOOL = 0x1,
			DVAR_TYPE_FLOAT = 0x2,
			DVAR_TYPE_FLOAT_2 = 0x3,
			DVAR_TYPE_FLOAT_3 = 0x4,
			DVAR_TYPE_FLOAT_4 = 0x5,
			DVAR_TYPE_INT = 0x6,
			DVAR_TYPE_ENUM = 0x7,
			DVAR_TYPE_STRING = 0x8,
			DVAR_TYPE_COLOR = 0x9,
			DVAR_TYPE_INT64 = 0xA,
			DVAR_TYPE_UINT64 = 0xB,
			DVAR_TYPE_LINEAR_COLOR_RGB = 0xC,
			DVAR_TYPE_COLOR_XYZ = 0xD,
			DVAR_TYPE_COLOR_LAB = 0xE,
			DVAR_TYPE_SESSIONMODE_BASE_DVAR = 0xF,
			DVAR_TYPE_COUNT = 0x10,
		};
		/*
		//=====================================================================================
		*/
		union DvarValue
		{
			bool enabled;
			std::int32_t integer;
			std::uint32_t unsignedInt;
			std::int64_t integer64;
			std::uint64_t unsignedInt64;
			std::float_t value;
			ImVec4 vector;
			const char* string;
			std::uint8_t color[4];
			const dvar_t* indirect[3];
		};
		/*
		//=====================================================================================
		*/
		union DvarLimits
		{
			struct
			{
				std::int32_t stringCount;
				const char** strings;
			} enumeration;
			struct
			{
				std::int32_t min;
				std::int32_t max;
			} integer;
			struct
			{
				std::int64_t min;
				std::int64_t max;
			} integer64;
			struct
			{
				std::uint64_t min;
				std::uint64_t max;
			} unsignedInt64;
			struct
			{
				std::float_t min;
				std::float_t max;
			} value;
			struct
			{
				std::float_t min;
				std::float_t max;
			} vector;
		};
		/*
		//=====================================================================================
		*/
		struct dvar_t
		{
			dvarStrHash_t name;
			const char* debugName;
			const char* description;
			std::uint32_t flags;
			dvarType_t type;
			bool modified;
			DvarValue current;
			DvarValue latched;
			DvarValue reset;
			DvarLimits domain;
			dvar_t* hashNext;
		};
		/*
		//=====================================================================================
		*/
		enum LootCrateType
		{
			LOOT_CRATE_TYPE_COMMON = 0x0,
			LOOT_CRATE_TYPE_RARE = 0x1,
			LOOT_CRATE_TYPE_BRIBE = 0x2,
			LOOT_CRATE_TYPE_COUNT = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum eNetworkModes
		{
			MODE_NETWORK_OFFLINE = 0x0,
			MODE_NETWORK_SYSTEMLINK = 0x1,
			MODE_NETWORK_ONLINE = 0x2,
			MODE_NETWORK_COUNT = 0x3,
			MODE_NETWORK_INVALID = 0x3,
		};
		/*
		//=====================================================================================
		*/
		struct GfxDrawSurfFields
		{
			std::uint64_t useSiegeTextures : 1;
			std::uint64_t objectId : 18;
			std::uint64_t lateDepthSort : 5;
			std::uint64_t materialSortedIndex : 16;
			std::uint64_t techniqueIndexPlusOne : 11;
			std::uint64_t decalSurfSort : 6;
			std::uint64_t earlyDepthSort : 7;
		};
		/*
		//=====================================================================================
		*/
		union GfxSortKey
		{
			GfxDrawSurfFields fields;
			std::uint64_t packed;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialInfo
		{
			const char* name;
			std::uint32_t namehash;
			std::uint32_t gameFlags;
			std::uint8_t layerSortDecal;
			std::uint8_t pad2;
			std::uint8_t textureAtlasRowCount;
			std::uint8_t textureAtlasColumnCount;
			GfxSortKey drawSurf;
			std::uint32_t bindlessMaterialSortIndex;
			std::int32_t surfaceFlags;
			std::uint32_t contents;
		};
		/*
		//=====================================================================================
		*/
		enum GfxCameraRegion : std::uint8_t
		{
			CAMERA_REGION_GBUFFER_DEPTH_HACK = 0x0,
			CAMERA_REGION_GBUFFER_DEPTH_HACK_DECAL = 0x1,
			CAMERA_REGION_GBUFFER = 0x2,
			CAMERA_REGION_GBUFFER_DECAL = 0x3,
			CAMERA_REGION_GBUFFER_NO_VOLUME_DECAL = 0x4,
			CAMERA_REGION_LIT_OPAQUE = 0x5,
			CAMERA_REGION_LIT_TRANS = 0x6,
			CAMERA_REGION_LIT_TRANS_POST_RESOLVE = 0x7,
			CAMERA_REGION_LIT_POST_RESOLVE = 0x8,
			CAMERA_REGION_WATER = 0x9,
			CAMERA_REGION_EMISSIVE_FX = 0xA,
			CAMERA_REGION_DEPTH_HACK_SSS = 0xB,
			CAMERA_REGION_FORWARD_SSS = 0xC,
			CAMERA_REGION_DEPTH_HACK = 0xD,
			CAMERA_REGION_DEPTH_HACK_TRANS = 0xE,
			CAMERA_REGION_DEPTH_HACK_POST_BLUR = 0xF,
			CAMERA_REGION_SONAR = 0x10,
			CAMERA_REGION_OIT = 0x11,
			CAMERA_REGION_DEPTH_PRIME = 0x12,
			CAMERA_REGION_UNDERWATER = 0x13,
			CAMERA_REGION_COUNT = 0x14,
			CAMERA_REGION_NONE = 0x14,
		};
		/*
		//=====================================================================================
		*/
		enum MaterialShaderPipeline : std::uint8_t
		{
			SHADER_PIPELINE_NONE = 0x0,
			SHADER_PIPELINE_VS_PS = 0x1,
			SHADER_PIPELINE_LS_HS_VS_PS = 0x2,
			SHADER_PIPELINE_LS_HS_ES_GS_VS_PS = 0x3,
			SHADER_PIPELINE_ES_GS_VS_PS = 0x4,
			SHADER_PIPELINE_CS = 0x5,
			SHADER_PIPELINE_TYPE_COUNT = 0x6,
		};
		/*
		//=====================================================================================
		*/
		enum MaterialDrawMethodType : std::uint8_t
		{
			MATERIAL_DRAW_METHOD_SHIP = 0x0,
			MATERIAL_DRAW_METHOD_DEBUG = 0x1,
			MATERIAL_DRAW_METHOD_SHIP_NEO = 0x2,
			MATERIAL_DRAW_METHOD_COUNT = 0x3,
			MATERIAL_DRAW_METHOD_VENDOR_COUNT = 0x3,
			MATERIAL_DRAW_METHOD_VENDOR_VALID_COUNT = 0x3,
			MATERIAL_DRAW_METHOD_INVALID = 0xFF,
		};
		/*
		//=====================================================================================
		*/
		enum GfxPrimitiveType
		{
			kPrimitiveTypeNone = 0x0,
			kPrimitiveTypePointList = 0x1,
			kPrimitiveTypeLineList = 0x2,
			kPrimitiveTypeLineStrip = 0x3,
			kPrimitiveTypeTriList = 0x4,
			kPrimitiveTypeTriFan = 0x5,
			kPrimitiveTypeTriStrip = 0x6,
			kPrimitiveTypePatch = 0x9,
			kPrimitiveTypeLineListAdjacency = 0xA,
			kPrimitiveTypeLineStripAdjacency = 0xB,
			kPrimitiveTypeTriListAdjacency = 0xC,
			kPrimitiveTypeTriStripAdjacency = 0xD,
			kPrimitiveTypeRectList = 0x11,
			kPrimitiveTypeLineLoop = 0x12,
			kPrimitiveTypeQuadList = 0x13,
			kPrimitiveTypeQuadStrip = 0x14,
			kPrimitiveTypePolygon = 0x15,
		};
		/*
		//=====================================================================================
		*/
		enum MaterialStreamDest : std::uint8_t
		{
			STREAM_DST_POSITION = 0x0,
			STREAM_DST_NORMAL = 0x1,
			STREAM_DST_TANGENT = 0x2,
			STREAM_DST_TANGENT_0 = 0x2,
			STREAM_DST_TANGENT_1 = 0x3,
			STREAM_DST_COLOR_0 = 0x4,
			STREAM_DST_COLOR_1 = 0x5,
			STREAM_DST_COLOR_2 = 0x6,
			STREAM_DST_COLOR_3 = 0x7,
			STREAM_DST_COLOR_4 = 0x8,
			STREAM_DST_COLOR_5 = 0x9,
			STREAM_DST_DEPTH = 0xA,
			STREAM_DST_TEXCOORD_0 = 0xB,
			STREAM_DST_TEXCOORD_1 = 0xC,
			STREAM_DST_TEXCOORD_2 = 0xD,
			STREAM_DST_TEXCOORD_3 = 0xE,
			STREAM_DST_TEXCOORD_4 = 0xF,
			STREAM_DST_TEXCOORD_5 = 0x10,
			STREAM_DST_TEXCOORD_6 = 0x11,
			STREAM_DST_TEXCOORD_7 = 0x12,
			STREAM_DST_TEXCOORD_8 = 0x13,
			STREAM_DST_TEXCOORD_9 = 0x14,
			STREAM_DST_TEXCOORD_10 = 0x15,
			STREAM_DST_TEXCOORD_11 = 0x16,
			STREAM_DST_TEXCOORD_12 = 0x17,
			STREAM_DST_TEXCOORD_13 = 0x18,
			STREAM_DST_OFFPOSITION = 0x19,
			STREAM_DST_TENSION = 0x1A,
			STREAM_DST_UVOFFSETS = 0x1B,
			STREAM_DST_GLASS_SHARD_INDEX = 0x1C,
			STREAM_DST_BLENDWEIGHT = 0x1D,
			STREAM_DST_BLENDINDICES = 0x1E,
			STREAM_DST_BENTNORMAL = 0x1F,
			STREAM_DST_CLIPDISTANCE_0 = 0x20,
			STREAM_DST_CLIPDISTANCE_1 = 0x21,
			STREAM_DST_CLIPDISTANCE_2 = 0x22,
			STREAM_DST_CLIPDISTANCE_3 = 0x23,
			STREAM_DST_CLIPDISTANCE_4 = 0x24,
			STREAM_DST_CLIPDISTANCE_5 = 0x25,
			STREAM_DST_COUNT = 0x26,
		};
		/*
		//=====================================================================================
		*/
		struct DataFormat
		{
			union
			{
				struct
				{
					std::uint32_t m_surfaceFormat : 8;
					std::uint32_t m_channelType : 4;
					std::uint32_t m_channelX : 3;
					std::uint32_t m_channelY : 3;
					std::uint32_t m_channelZ : 3;
					std::uint32_t m_channelW : 3;
					std::uint32_t m_unused : 8;
				} m_bits;
				std::uint32_t m_asInt;
			};
		};
		/*
		//=====================================================================================
		*/
		struct OrbisVertexDeclaration
		{
			bool valid;
			std::int32_t stream[16];
			std::int32_t offset[16];
			DataFormat type[16];
		};
		/*
		//=====================================================================================
		*/
		struct MaterialVertexDeclaration
		{
			std::uint8_t vertexInputCount;
			MaterialStreamDest vertexInputs[16];
			OrbisVertexDeclaration decl[14];
		};
		/*
		//=====================================================================================
		*/
		struct ShaderCommonData
		{
			std::uint32_t m_shaderSize : 23;
			std::uint32_t m_shaderIsUsingSrt : 1;
			std::uint32_t m_numInputUsageSlots : 8;
			std::uint16_t m_embeddedConstantBufferSizeInDQW;
			std::uint16_t m_scratchSizeInDWPerThread;
		};
		/*
		//=====================================================================================
		*/
		struct VsStageRegisters
		{
			std::uint32_t m_spiShaderPgmLoVs;
			std::uint32_t m_spiShaderPgmHiVs;
			std::uint32_t m_spiShaderPgmRsrc1Vs;
			std::uint32_t m_spiShaderPgmRsrc2Vs;
			std::uint32_t m_spiVsOutConfig;
			std::uint32_t m_spiShaderPosFormat;
			std::uint32_t m_paClVsOutCntl;
		};
		/*
		//=====================================================================================
		*/
		struct VsShader
		{
			ShaderCommonData m_common;
			VsStageRegisters m_vsStageRegisters;
			std::uint8_t m_numInputSemantics;
			std::uint8_t m_numExportSemantics;
			std::uint8_t m_gsModeOrNumInputSemanticsCs;
			std::uint8_t m_fetchControl;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialVertexShaderProgram
		{
			std::uint8_t* fetchShader;
			std::uint32_t fetchShaderSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* vsBytes;
				VsShader* vs;
			};
			std::uint32_t vsSize;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialVertexShader
		{
			const char* name;
			const char* extraDef;
			MaterialVertexShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct PsStageRegisters
		{
			std::uint32_t m_spiShaderPgmLoPs;
			std::uint32_t m_spiShaderPgmHiPs;
			std::uint32_t m_spiShaderPgmRsrc1Ps;
			std::uint32_t m_spiShaderPgmRsrc2Ps;
			std::uint32_t m_spiShaderZFormat;
			std::uint32_t m_spiShaderColFormat;
			std::uint32_t m_spiPsInputEna;
			std::uint32_t m_spiPsInputAddr;
			std::uint32_t m_spiPsInControl;
			std::uint32_t m_spiBarycCntl;
			std::uint32_t m_dbShaderControl;
			std::uint32_t m_cbShaderMask;
		};
		/*
		//=====================================================================================
		*/
		struct PsShader
		{
			ShaderCommonData m_common;
			PsStageRegisters m_psStageRegisters;
			std::uint8_t m_numInputSemantics;
			std::uint8_t m_reserved[3];
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialPixelShaderProgram
		{
			std::uint8_t* program;
			std::uint32_t programSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* psBytes;
				PsShader* ps;
			};
			std::uint32_t psSize;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialPixelShader
		{
			const char* name;
			const char* extraDef;
			MaterialPixelShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct GsStageRegisters
		{
			std::uint32_t m_spiShaderPgmLoGs;
			std::uint32_t m_spiShaderPgmHiGs;
			std::uint32_t m_spiShaderPgmRsrc1Gs;
			std::uint32_t m_spiShaderPgmRsrc2Gs;
			std::uint32_t m_vgtStrmoutConfig;
			std::uint32_t m_vgtGsOutPrimType;
			std::uint32_t m_vgtGsInstanceCnt;
		};
		/*
		//=====================================================================================
		*/
		struct GsShader
		{
			ShaderCommonData m_common;
			GsStageRegisters m_gsStageRegisters;
			std::uint32_t m_memExportVertexSizeInDWord[4];
			std::uint32_t m_maxOutputVertexCount : 11;
			std::uint32_t m_inputVertexCountMinus1 : 5;
			std::uint32_t m_inputVertexSizeInDWord : 8;
			std::uint32_t m_isPatchTopology : 1;
			std::uint32_t m_reserved : 7;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialGeometryShaderProgram
		{
			std::uint8_t* program;
			std::uint32_t programSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* gsBytes;
				GsShader* gs;
			};
			std::uint32_t gsSize;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialGeometryShader
		{
			const char* name;
			const char* extraDef;
			MaterialGeometryShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct LsStageRegisters
		{
			std::uint32_t m_spiShaderPgmLoLs;
			std::uint32_t m_spiShaderPgmHiLs;
			std::uint32_t m_spiShaderPgmRsrc1Ls;
			std::uint32_t m_spiShaderPgmRsrc2Ls;
		};
		/*
		//=====================================================================================
		*/
		struct LsShader
		{
			ShaderCommonData m_common;
			LsStageRegisters m_lsStageRegisters;
			std::uint8_t m_numInputSemantics;
			std::uint8_t m_fetchControl;
			std::uint8_t m_reserved[2];
			std::uint32_t m_lsStride;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialLocalShaderProgram
		{
			std::uint8_t* fetchShader;
			std::uint32_t fetchShaderSize;
			std::uint8_t* program;
			std::uint32_t programSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* lsBytes;
				LsShader* ls;
			};
			std::uint32_t lsSize;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialLocalShader
		{
			const char* name;
			const char* extraDef;
			MaterialLocalShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct HsStageRegisters
		{
			std::uint32_t m_spiShaderPgmLoHs;
			std::uint32_t m_spiShaderPgmHiHs;
			std::uint32_t m_spiShaderPgmRsrc1Hs;
			std::uint32_t m_spiShaderPgmRsrc2Hs;
			std::uint32_t m_vgtTfParam;
			std::uint32_t m_vgtHosMaxTessLevel;
			std::uint32_t m_vgtHosMinTessLevel;
		};
		/*
		//=====================================================================================
		*/
		struct HullStateConstants
		{
			std::uint32_t m_numInputCP;
			std::uint32_t m_numOutputCP;
			std::uint32_t m_numPatchConst;
			std::uint32_t m_cpStride;
			std::uint32_t m_numThreads;
			std::uint32_t m_tessFactorStride;
			std::uint32_t m_firstEdgeTessFactorIndex;
		};
		/*
		//=====================================================================================
		*/
		struct HsShader
		{
			ShaderCommonData m_common;
			HsStageRegisters m_hsStageRegisters;
			HullStateConstants m_hullStateConstants;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialHullShaderProgram
		{
			std::uint8_t* program;
			std::uint32_t programSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* hsBytes;
				HsShader* hs;
			};
			std::uint32_t hsSize;
			std::uint32_t lsStride;
			std::uint32_t numPatches;
			std::uint32_t vgtPrimitiveCount;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialHullShader
		{
			const char* name;
			const char* extraDef;
			MaterialHullShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(8)) MaterialDomainShaderProgram
		{
			std::uint8_t* program;
			std::uint32_t programSize;
			std::uint8_t* code;
			std::uint32_t codeSize;
			union
			{
				std::uint8_t* dsBytes;
				VsShader* ds;
			};
			std::uint32_t dsSize;
			std::uint8_t* binding;
			std::uint32_t bindingSize;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialDomainShader
		{
			const char* name;
			const char* extraDef;
			MaterialDomainShaderProgram prog;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialArgumentCodeConst
		{
			std::uint16_t index;
			std::uint8_t firstRow;
			std::uint8_t rowCount;
		};
		/*
		//=====================================================================================
		*/
		enum GfxRenderTargetId : std::uint8_t
		{
			R_RENDERTARGET_NULL = 0x0,
			R_RENDERTARGET_COMBO = 0x1,
			R_RENDERTARGET_SAVED_SCREEN = 0x2,
			R_RENDERTARGET_FRAME_BUFFER = 0x3,
			R_RENDERTARGET_DISPLAY_BUFFER_0 = 0x4,
			R_RENDERTARGET_DISPLAY_BUFFER_1 = 0x5,
			R_RENDERTARGET_SHADOWMAP_SUN_1P = 0x6,
			R_RENDERTARGET_SHADOWMAP_SUN_2P = 0x7,
			R_RENDERTARGET_SHADOWMAP_SUN_4P = 0x8,
			R_RENDERTARGET_SHADOWMAP_SPOT_ARRAY = 0x9,
			R_RENDERTARGET_SHADOWMAP_OMNI_ARRAY = 0xA,
			R_RENDERTARGET_SHADOWMAP_TRANS_1P = 0xB,
			R_RENDERTARGET_SHADOWMAP_TRANS_2P = 0xC,
			R_RENDERTARGET_SHADOWMAP_TRANS_4P = 0xD,
			R_RENDERTARGET_SCENE = 0xE,
			R_RENDERTARGET_SCENE_COLOR_ONLY = 0xF,
			R_RENDERTARGET_OIT_FALLBACK_COLOR = 0x10,
			R_RENDERTARGET_OIT_FALLBACK = 0x11,
			R_RENDERTARGET_SCENE_SAVED = 0x12,
			R_RENDERTARGET_SCENE_DEPTH = 0x13,
			R_RENDERTARGET_SCENE_DEPTH_UAV = 0x14,
			R_RENDERTARGET_SCENE_DEPTH_BEFORE_OIT = 0x15,
			R_RENDERTARGET_RESOLVED_SCENE = 0x16,
			R_RENDERTARGET_UI3D = 0x17,
			R_RENDERTARGET_GBUFFER = 0x18,
			R_RENDERTARGET_GBUFFER_WMV = 0x19,
			R_RENDERTARGET_FORWARD_SSS = 0x1A,
			R_RENDERTARGET_SSAO_STUB = 0x1B,
			R_RENDERTARGET_SSAO_DEPTH_STUB = 0x1C,
			R_RENDERTARGET_GTAO_HISTORY_HALFRES_0 = 0x1D,
			R_RENDERTARGET_GTAO_HISTORY_HALFRES_1 = 0x1E,
			R_RENDERTARGET_GTAO_HISTORY_HALFRES_2 = 0x1F,
			R_RENDERTARGET_GTAO_TMP_HALFRES = 0x20,
			R_RENDERTARGET_GTAO_TWEAKED_HALFRES = 0x21,
			R_RENDERTARGET_LIGHTING_PING = 0x22,
			R_RENDERTARGET_LIGHTING_PONG = 0x23,
			R_RENDERTARGET_RESOLVED_QUARTER = 0x24,
			R_RENDERTARGET_EXPOSURE = 0x25,
			R_RENDERTARGET_VOLUMETRIC_LIGHTS_HALF = 0x26,
			R_RENDERTARGET_DEPTH_BEFORE_OIT_QUARTER = 0x27,
			R_RENDERTARGET_DEPTH_AFTER_OIT_QUARTER = 0x28,
			R_RENDERTARGET_DEPTH_UV_OFFSET_QUARTER = 0x29,
			R_RENDERTARGET_VOLUMETRIC_LIGHTS_QUARTER = 0x2A,
			R_RENDERTARGET_VOLUMETRIC_LIGHTS_TEMP_QUARTER = 0x2B,
			R_RENDERTARGET_VOLUMETRIC_ADAPTIVE_TRANSPARENCY_DEPTH = 0x2C,
			R_RENDERTARGET_VOLUMETRIC_ADAPTIVE_TRANSPARENCY_TRANS = 0x2D,
			R_RENDERTARGET_VOLUMETRIC_ALPHA = 0x2E,
			R_RENDERTARGET_LENS_FLARE = 0x2F,
			R_RENDERTARGET_ADS_BLUR_PING = 0x30,
			R_RENDERTARGET_ADS_BLUR_PONG = 0x31,
			R_RENDERTARGET_ADS_BLUR_LARGE = 0x32,
			R_RENDERTARGET_BLOOM_MIP1_PING = 0x33,
			R_RENDERTARGET_BLOOM_MIP1_PONG = 0x34,
			R_RENDERTARGET_BLOOM_MIP2_PING = 0x35,
			R_RENDERTARGET_BLOOM_MIP2_PONG = 0x36,
			R_RENDERTARGET_BLOOM_MIP3_PING = 0x37,
			R_RENDERTARGET_BLOOM_MIP3_PONG = 0x38,
			R_RENDERTARGET_BLOOM_MIP4_PING = 0x39,
			R_RENDERTARGET_BLOOM_MIP4_PONG = 0x3A,
			R_RENDERTARGET_BLOOM_MIP5_PING = 0x3B,
			R_RENDERTARGET_BLOOM_MIP5_PONG = 0x3C,
			R_RENDERTARGET_BLOOM_MIP1_FP10_TMP = 0x3D,
			R_RENDERTARGET_RESOLVED_NORMAL = 0x3E,
			R_RENDERTARGET_RESOLVED_ALBEDO = 0x3F,
			R_RENDERTARGET_LINEAR_PING = 0x40,
			R_RENDERTARGET_LINEAR_PONG = 0x41,
			R_RENDERTARGET_UPSAMPLE_NEO_1 = 0x42,
			R_RENDERTARGET_UPSAMPLE_NEO_2 = 0x43,
			R_RENDERTARGET_1K_TL_NEO = 0x44,
			R_RENDERTARGET_1K_TR_NEO = 0x45,
			R_RENDERTARGET_1K_BL_NEO = 0x46,
			R_RENDERTARGET_1K_BR_NEO = 0x47,
			R_RENDERTARGET_1K_EDGE = 0x48,
			R_RENDERTARGET_1K_LUMA_1 = 0x49,
			R_RENDERTARGET_1K_LUMA_2 = 0x4A,
			R_RENDERTARGET_LAST_DEPTH_NEO = 0x4B,
			R_RENDERTARGET_SCENE_LUMA = 0x4C,
			R_RENDERTARGET_LINEAR_QUARTER_PING = 0x4D,
			R_RENDERTARGET_LINEAR_QUARTER_PONG = 0x4E,
			R_RENDERTARGET_DOWNSAMPLED_SCENE = 0x4F,
			R_RENDERTARGET_SMAA_EDGES = 0x50,
			R_RENDERTARGET_SMAA_TEMPORAL_0 = 0x51,
			R_RENDERTARGET_SMAA_TEMPORAL_1 = 0x52,
			R_RENDERTARGET_SMAA_TEMPORAL_LUMA_0 = 0x53,
			R_RENDERTARGET_SMAA_TEMPORAL_LUMA_1 = 0x54,
			R_RENDERTARGET_SMAA_TEMPORAL_LUMA_2 = 0x55,
			R_RENDERTARGET_SMAA_TEMPORAL_LUMA_3 = 0x56,
			R_RENDERTARGET_SMAA_FILMIC_0 = 0x57,
			R_RENDERTARGET_SMAA_FILMIC_1 = 0x58,
			R_RENDERTARGET_SMAA_DEPTH_STENCIL = 0x59,
			R_RENDERTARGET_SMAA_BLEND = 0x5A,
			R_RENDERTARGET_DOF_UNDERWATER_BLUR_X = 0x5B,
			R_RENDERTARGET_DOF_UNDERWATER_BLUR_Y = 0x5C,
			R_RENDERTARGET_DOF_UNDERWATER_BLUR_V = 0x5D,
			R_RENDERTARGET_DOF_NEAR_COC = 0x5E,
			R_RENDERTARGET_DOF_NEAR_COC_PING = 0x5F,
			R_RENDERTARGET_DOF_NEAR_COC_PONG = 0x60,
			R_RENDERTARGET_DOF_NEAR_COC_BLUR = 0x61,
			R_RENDERTARGET_DOF_COC = 0x62,
			R_RENDERTARGET_DOF_BLUR_RGB_COC_MRT_MIP0 = 0x63,
			R_RENDERTARGET_DOF_BLUR_RGB_COC_MRT_MIP1 = 0x64,
			R_RENDERTARGET_DOF_BLUR_RGB_MIP0 = 0x65,
			R_RENDERTARGET_DOF_BLUR_RGB_MIP1 = 0x66,
			R_RENDERTARGET_DOF_BLUR_RGB_SMOOTH = 0x67,
			R_RENDERTARGET_MOTION_VECTOR_0 = 0x68,
			R_RENDERTARGET_MOTION_VECTOR_1 = 0x69,
			R_RENDERTARGET_MOTION_VECTOR_MB = 0x6A,
			R_RENDERTARGET_VELOCITY_TILE0_PINGPONG = 0x6B,
			R_RENDERTARGET_VELOCITY_TILE0 = 0x6C,
			R_RENDERTARGET_VELOCITY_TILE1 = 0x6D,
			R_RENDERTARGET_SONAR = 0x6E,
			R_RENDERTARGET_DEPTH_FOR_SONAR = 0x6F,
			R_RENDERTARGET_OVERDRAW = 0x70,
			R_RENDERTARGET_LEONARDO_HDR_SCREENSHOT = 0x71,
			R_RENDERTARGET_HIGHRES_CAPTURE = 0x72,
			R_RENDERTARGET_COUNT = 0x73,
			R_RENDERTARGET_NONE = 0x0,
		};
		/*
		//=====================================================================================
		*/
		union MaterialArgumentDef
		{
			MaterialArgumentCodeConst codeConst;
			std::uint32_t codeTexture;
			std::uint32_t nameHash;
			GfxRenderTargetId renderTargetId;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialShaderArgument
		{
			std::uint16_t type;
			std::uint16_t location;
			std::uint16_t size;
			std::uint16_t buffer;
			MaterialArgumentDef u;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialShaderArgumentBindless
		{
			std::uint8_t type;
			std::uint8_t size;
			std::uint16_t location;
			std::uint32_t nameHash;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialDrawMethod
		{
			MaterialShaderPipeline pipeline;
			std::uint8_t stableArgCount;
			std::uint8_t materialType;
			MaterialDrawMethodType drawMethodType;
			GfxPrimitiveType primitiveType;
			std::uint32_t indexCount;
			std::uint16_t bindlessStride;
			std::uint8_t bindlessArgCount;
			std::uint8_t bindlessArgConstantSkipCount;
			MaterialVertexDeclaration* vertexDecl;
			MaterialVertexShader* vertexShader;
			MaterialPixelShader* pixelShader;
			MaterialGeometryShader* geometryShader;
			MaterialLocalShader* localShader;
			MaterialHullShader* hullShader;
			MaterialDomainShader* domainShader;
			MaterialShaderArgument* args;
			MaterialShaderArgumentBindless* bindlessArgs;
			std::uint32_t shaderUsageCount;
			std::uint32_t* shaderUsageTable;
		};
		/*
		//=====================================================================================
		*/
		struct Blend
		{
			std::uint32_t valid : 1;
			std::uint32_t enabled : 1;
			std::uint32_t rgbSrc : 4;
			std::uint32_t rgbOp : 3;
			std::uint32_t rgbDst : 4;
			std::uint32_t alphaSrc : 4;
			std::uint32_t alphaOp : 3;
			std::uint32_t alphaDst : 4;
			std::uint32_t writeMask : 4;
		};
		/*
		//=====================================================================================
		*/
		struct Depth
		{
			std::uint32_t write : 1;
			std::uint32_t test : 3;
		};
		/*
		//=====================================================================================
		*/
		struct Stencil
		{
			std::uint32_t enable : 1;
			std::uint32_t passOp : 3;
			std::uint32_t failOp : 3;
			std::uint32_t zFailOp : 3;
			std::uint32_t func : 3;
		};
		/*
		//=====================================================================================
		*/
		struct Primitive
		{
			std::uint32_t mrtBlending : 1;
			std::uint32_t cullMode : 2;
			std::uint32_t polygonOffset : 2;
			std::uint32_t wireframe : 1;
			std::uint32_t depthClipEnable : 1;
		};
		/*
		//=====================================================================================
		*/
		struct OverrideOptions
		{
			std::uint32_t reverseCullMode : 1;
			std::uint32_t disableDepthClip : 1;
			std::uint32_t reverseDepthTest : 1;
			std::uint32_t replaceStencil : 1;
		};
		/*
		//=====================================================================================
		*/
		struct BlendControl
		{
			std::uint32_t m_reg;
		};
		/*
		//=====================================================================================
		*/
		struct GfxBlendState
		{
			BlendControl blendControl[8];
			bool mrtBlending;
			std::uint32_t writeMask;
		};
		/*
		//=====================================================================================
		*/
		struct DepthStencilControl
		{
			std::uint32_t m_reg;
		};
		/*
		//=====================================================================================
		*/
		struct StencilOpControl
		{
			std::uint32_t m_reg;
		};
		/*
		//=====================================================================================
		*/
		struct StencilControl
		{
			std::uint8_t m_testVal;
			std::uint8_t m_mask;
			std::uint8_t m_writeMask;
			std::uint8_t m_opVal;
		};
		/*
		//=====================================================================================
		*/
		struct GfxDepthStencilState
		{
			DepthStencilControl depthStencilControl;
			StencilOpControl stencilOpControl;
			StencilControl frontStencilControl;
			StencilControl backStencilControl;
		};
		/*
		//=====================================================================================
		*/
		struct ClipControl
		{
			std::uint32_t m_reg;
		};
		/*
		//=====================================================================================
		*/
		enum PrimitiveSetupCullFaceMode
		{
			kPrimitiveSetupCullFaceNone = 0x0,
			kPrimitiveSetupCullFaceFront = 0x1,
			kPrimitiveSetupCullFaceBack = 0x2,
			kPrimitiveSetupCullFaceFrontAndBack = 0x3,
		};
		/*
		//=====================================================================================
		*/
		enum PrimitiveSetupPolygonMode
		{
			kPrimitiveSetupPolygonModePoint = 0x0,
			kPrimitiveSetupPolygonModeLine = 0x1,
			kPrimitiveSetupPolygonModeFill = 0x2,
		};
		/*
		//=====================================================================================
		*/
		enum PrimitiveSetupPolygonOffsetMode
		{
			kPrimitiveSetupPolygonOffsetEnable = 0x1,
			kPrimitiveSetupPolygonOffsetDisable = 0x0,
		};
		/*
		//=====================================================================================
		*/
		struct GfxRasterizerState
		{
			ClipControl clipControl;
			PrimitiveSetupCullFaceMode cullMode;
			PrimitiveSetupPolygonMode polyMode;
			PrimitiveSetupPolygonOffsetMode polygonOffsetMode;
			std::float_t polygonOffsetBias;
			std::float_t polygonOffsetScale;
			std::float_t polygonOffsetClamp;
		};
		/*
		//=====================================================================================
		*/
		struct GfxStateMap
		{
			Blend blend[8];
			Depth depth;
			Stencil stencilFront;
			Stencil stencilBack;
			Primitive primitive;
			std::uint8_t stencilRef;
			std::uint8_t stencilReadMask;
			std::uint8_t stencilWriteMask;
			OverrideOptions overrides;
			GfxBlendState* blendState;
			GfxDepthStencilState* depthStencilState;
			GfxDepthStencilState* depthStencilState_reverseDepthTest;
			GfxDepthStencilState* depthStencilState_replaceStencil;
			GfxRasterizerState* rasterizerState;
			GfxRasterizerState* rasterizerState_reverseCull;
			GfxRasterizerState* rasterizerState_depthClipDisable;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialTechnique
		{
			const char* name;
			MaterialDrawMethod drawMethods[3];
			GfxStateMap* stateMap;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialTechniqueSet
		{
			const char* name;
			std::uint32_t renderFlags;
			MaterialTechnique* techniques[16];
		};
		/*
		//=====================================================================================
		*/
		struct XPakEntryInfo
		{
			std::uint64_t key;
			std::int64_t offset;
			std::uint64_t size;
			std::uint64_t xpakIndex : 5;
			std::uint64_t compressed : 1;
			std::uint64_t valid : 1;
			std::uint64_t adjacentLeftType : 3;
			std::uint64_t adjacentRightType : 3;
			std::uint64_t adjacentLeft : 18;
			std::uint64_t adjacentRight : 18;
			std::uint64_t padding : 15;
		};
		/*
		//=====================================================================================
		*/
		struct GfxStreamedPartInfo
		{
			XPakEntryInfo xpakEntry;
			std::uint32_t levelCountAndSize;
			std::uint16_t width;
			std::uint16_t height;
		};
		/*
		//=====================================================================================
		*/
		struct Texture
		{
			std::uint32_t m_regs[8];
		};
		/*
		//=====================================================================================
		*/
		struct GfxTexture
		{
			Texture basemap;
		};
		/*
		//=====================================================================================
		*/
		enum GfxPixelFormat
		{
			GFX_PF_INVALID = 0x0,
			GFX_PF_UNKNOWN = 0x0,
			GFX_PF_D24S8 = 0x1,
			GFX_PF_D24FS8 = 0x2,
			GFX_PF_A8 = 0x3,
			GFX_PF_R8_UN = 0x4,
			GFX_PF_R8_UI = 0x5,
			GFX_PF_D16 = 0x6,
			GFX_PF_R16_UN = 0x7,
			GFX_PF_R16_UI = 0x8,
			GFX_PF_R16F = 0x9,
			GFX_PF_R8G8_UN = 0xA,
			GFX_PF_R8G8_SNORM = 0xB,
			GFX_PF_B5G6R5 = 0xC,
			GFX_PF_B4G4R4A4 = 0xD,
			GFX_PF_D32F = 0xE,
			GFX_PF_R32F = 0xF,
			GFX_PF_R16G16_UN = 0x10,
			GFX_PF_R16G16_SNORM = 0x11,
			GFX_PF_R16G16F = 0x12,
			GFX_PF_R9G9B9E5 = 0x13,
			GFX_PF_R8G8B8A8 = 0x14,
			GFX_PF_R8G8B8A8_SNORM = 0x15,
			GFX_PF_B8G8R8A8 = 0x16,
			GFX_PF_R8G8B8A8_SRGB = 0x17,
			GFX_PF_R10G10B10A2 = 0x18,
			GFX_PF_B10G10R10A2 = 0x19,
			GFX_PF_R11G11B10F = 0x1A,
			GFX_PF_R32G32F = 0x1B,
			GFX_PF_R16G16B16A16_UN = 0x1C,
			GFX_PF_R16G16B16A16F = 0x1D,
			GFX_PF_R32G32B32A32F = 0x1E,
			GFX_PF_BC1 = 0x1F,
			GFX_PF_BC1_SRGB = 0x20,
			GFX_PF_BC2 = 0x21,
			GFX_PF_BC2_SRGB = 0x22,
			GFX_PF_BC3 = 0x23,
			GFX_PF_BC3_SRGB = 0x24,
			GFX_PF_BC4 = 0x25,
			GFX_PF_BC5 = 0x26,
			GFX_PF_BC6_UH = 0x27,
			GFX_PF_BC6_SH = 0x28,
			GFX_PF_BC7 = 0x29,
			GFX_PF_BC7_SRGB = 0x2A,
			GFX_PF_R32G32B32A32_UN = 0x2B,
			GFX_PF_R32_UI = 0x2C,
			GFX_PF_R32G32_UI = 0x2D,
		};
		/*
		//=====================================================================================
		*/
		enum GfxImageSemantic : std::uint8_t
		{
			IMG_SEMANTIC_UNKNOWN = 0x0,
			IMG_SEMANTIC_2D = 0x1,
			IMG_SEMANTIC_DIFFUSE_MAP = 0x2,
			IMG_SEMANTIC_EFFECT_MAP = 0x3,
			IMG_SEMANTIC_NORMAL_MAP = 0x4,
			IMG_SEMANTIC_SPECULAR_MASK = 0x5,
			IMG_SEMANTIC_SPECULAR_MAP = 0x6,
			IMG_SEMANTIC_GLOSS_MAP = 0x7,
			IMG_SEMANTIC_OCCLUSION_MAP = 0x8,
			IMG_SEMANTIC_REVEAL_MAP = 0x9,
			IMG_SEMANTIC_MULTIPLE_MASK = 0xA,
			IMG_SEMANTIC_THICKNESS_MAP = 0xB,
			IMG_SEMANTIC_CAMO_MAP = 0xC,
			IMG_SEMANTIC_ONE_CHANNEL = 0xD,
			IMG_SEMANTIC_TWO_CHANNEL = 0xE,
			IMG_SEMANTIC_EMBLEM = 0xF,
			IMG_SEMANTIC_CUSTOM = 0x10,
			IMG_SEMANTIC_LUT_TPAGE = 0x11,
			IMG_SEMANTIC_LIGHT_COOKIE = 0x12,
			IMG_SEMANTIC_HDR = 0x13,
			IMG_SEMANTIC_EYE_CAUSTIC = 0x14,
			IMG_SEMANTIC_COUNT = 0x15,
		};
		/*
		//=====================================================================================
		*/
		enum MapType : std::uint8_t
		{
			MAPTYPE_NONE = 0x0,
			MAPTYPE_2D = 0x1,
			MAPTYPE_2D_ARRAY = 0x2,
			MAPTYPE_3D = 0x3,
			MAPTYPE_CUBE = 0x4,
			MAPTYPE_CUBE_ARRAY = 0x5,
			MAPTYPE_COUNT = 0x6,
		};
		/*
		//=====================================================================================
		*/
		struct GfxImage
		{
			std::uint8_t* pixels;
			std::uint8_t* fallbackPixels;
			const char* name;
			GfxStreamedPartInfo streamedParts[4];
			GfxTexture texture;
			GfxTexture fallbackTexture;
			std::uint32_t flags;
			std::int32_t alignment;
			std::uint32_t hash;
			std::uint32_t totalSize;
			std::uint32_t fallbackSize;
			GfxPixelFormat format;
			std::uint16_t width;
			std::uint16_t height;
			std::uint16_t depth;
			GfxImageSemantic semantic;
			MapType mapType;
			std::uint8_t category;
			std::uint8_t levelCount;
			std::uint8_t fallbackLevel;
			std::uint8_t useFallback;
			std::uint8_t streaming;
			std::uint8_t streamedPartCount;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialTextureDef
		{
			GfxImage* image;
			std::uint32_t nameHash;
			ImVec2 uvScale;
			std::uint8_t texSizeShift[2];
			std::uint16_t uvOffset[3];
			std::uint16_t usage;
			std::uint8_t isMatureContent;
		};
		/*
		//=====================================================================================
		*/
		enum GfxSamplerState : std::uint16_t
		{
			SAMPLER_FILTER_SHIFT = 0x0,
			SAMPLER_FILTER_DISABLED = 0x0,
			SAMPLER_FILTER_NEAREST = 0x1,
			SAMPLER_FILTER_LINEAR = 0x2,
			SAMPLER_FILTER_ANISO2X = 0x3,
			SAMPLER_FILTER_ANISO4X = 0x4,
			SAMPLER_FILTER_ANISO8X = 0x5,
			SAMPLER_FILTER_ANISO16X = 0x6,
			SAMPLER_FILTER_COMPARE = 0x7,
			SAMPLER_FILTER_COUNT = 0x8,
			SAMPLER_FILTER_MASK = 0x7,
			SAMPLER_MIPMAP_SHIFT = 0x3,
			SAMPLER_MIPMAP_DISABLED = 0x0,
			SAMPLER_MIPMAP_NEAREST = 0x8,
			SAMPLER_MIPMAP_LINEAR = 0x10,
			SAMPLER_MIPMAP_COUNT = 0x3,
			SAMPLER_MIPMAP_MASK = 0x18,
			SAMPLER_WRAPMODE_U_SHIFT = 0x5,
			SAMPLER_CLAMP_U = 0x20,
			SAMPLER_CLAMP_BORDER_U = 0x40,
			SAMPLER_MIRROR_U = 0x60,
			SAMPLER_WRAPMODE_V_SHIFT = 0x7,
			SAMPLER_CLAMP_V = 0x80,
			SAMPLER_CLAMP_BORDER_V = 0x100,
			SAMPLER_MIRROR_V = 0x180,
			SAMPLER_WRAPMODE_W_SHIFT = 0x9,
			SAMPLER_CLAMP_W = 0x200,
			SAMPLER_CLAMP_BORDER_W = 0x400,
			SAMPLER_MIRROR_W = 0x600,
			SAMPLER_WRAPMODE_U_MASK = 0x60,
			SAMPLER_WRAPMODE_V_MASK = 0x180,
			SAMPLER_WRAPMODE_W_MASK = 0x600,
			SAMPLER_BORDER_COLOR_SHIFT = 0xB,
			SAMPLER_BORDER_COLOR_BLACK = 0x0,
			SAMPLER_BORDER_COLOR_WHITE = 0x800,
			SAMPLER_BORDER_COLOR_MASK = 0x800,
			SAMPLER_FILTER_MODE_SHIFT = 0xC,
			SAMPLER_FILTER_MODE_LERP = 0x0,
			SAMPLER_FILTER_MODE_MIN = 0x1000,
			SAMPLER_FILTER_MODE_MAX = 0x2000,
			SAMPLER_FILTER_MODE_MASK = 0x3000,
			SAMPLER_FLAGS_SHIFT = 0xE,
			SAMPLER_DONT_BIAS_MIP = 0x4000,
			SAMPLER_FLAGS_MASK = 0x4000,
			SAMPLER_STATES_MASK = 0x7FFF,
			SAMPLER_STATES_COUNT = 0x8000,
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(4)) MaterialSamplerDef
		{
			std::uint32_t nameHash;
			GfxSamplerState samplerState;
		};
		/*
		//=====================================================================================
		*/
		struct MaterialConstantDef
		{
			std::uint32_t nameHash;
			const char* name;
			ImVec4 literal;
		};
		/*
		//=====================================================================================
		*/
		struct __declspec(align(16)) Material
		{
			MaterialInfo info;
			std::uint8_t textureCount;
			std::uint8_t samplerCount;
			std::uint8_t constantCount;
			GfxCameraRegion cameraRegion;
			MaterialTechniqueSet* techniqueSet;
			MaterialTextureDef* textureTable;
			MaterialSamplerDef* samplerTable;
			MaterialConstantDef* constantTable;
		};
		/*
		//=====================================================================================
		*/
#pragma pack(push, 1)
		struct matchmaking_info_s
		{
		public:
			XNKID sessionID;
			XNADDR hostAddress;
		private:
			byte _0x2D[0xDF];
		public:
			std::uint32_t gameType;
			std::uint32_t maxPlayers;
			std::uint32_t numPlayers;
			std::uint64_t gameSecurityId;
			std::uint8_t gameSecurityKey[17];
		private:
			byte _0x131[0x3];
		public:
			std::uint32_t serverType;
			std::uint64_t xuid;
			std::uint32_t serverLocation;
			std::uint32_t latencyBand;
			std::uint32_t showInMatchmaking;
			std::uint32_t netcodeVersion;
			std::uint32_t mapPacks;
			std::uint32_t playlistVersion;
			std::uint32_t playlistNumber;
			std::uint32_t isEmpty;
			std::uint32_t teamSizeMax;
			std::float_t skill;
			std::uint64_t geo_1;
			std::uint64_t geo_2;
			std::uint64_t geo_3;
			std::uint64_t geo_4;
		private:
			byte _0x188[0x38];

		public:

			bool is_invalid()
			{
				constexpr auto invalid_id = 0x0101010101010101;

				return niggerware::utils::memory::is_equal(&sessionID, &invalid_id, 8);
			}

			bool is_p2p()
			{
				return serverType == 1001 || serverType == 1002 || serverType == 1003 || serverType == 1004;
			}

			bool is_dedi() 
			{ 
				return serverType == 2000; 
			}

			bool is_empty()
			{
				return numPlayers == 0;
			}

			bool is_full()
			{
				return numPlayers == maxPlayers;
			}
		};
#pragma pack(pop)
		/*
		//=====================================================================================
		*/
		struct matchmaking_list_s
		{
		public:
			matchmaking_info_s session[max_sessions];
		};
		/*
		//=====================================================================================
		*/
		const static auto get_render_device() { return *std::recast<IDXGISwapChain**>(offsets::dx_ptr); }
		const static auto get_window_handle() { return *std::recast<HWND*>(offsets::hWnd); }
		const static auto get_steam_user() { return *std::recast<ISteamUser**>(offsets::steam_user_interface); }
		const static auto get_steam_user_stats() { return *std::recast<ISteamUserStats**>(offsets::steam_user_stats_interface); }
		const static auto get_steam_friends() { return *std::recast<ISteamFriends**>(offsets::steam_friends_interface); }
		const static auto get_steam_apps() { return *std::recast<ISteamApps**>(offsets::steam_apps_interface); }
		const static auto get_view_port() { return std::recast<view_port_s*>(offsets::view_port); }
		const static auto get_weapon_names() { return std::recast<weapon_names_s*>(std::recast<std::uintptr_t*>(offsets::weapon_names)); }
		const static auto get_client(std::int32_t clientnum) { return &std::recast<client_s*>(offsets::client)[clientnum]; }
		const static auto get_user_data() { return std::recast<user_data_s*>(offsets::user_data); }
		const static auto get_client_connection(LocalClientNum_t localClientNum) { return &std::recast<client_connection_s*>(std::recast<std::uintptr_t*>(offsets::client_connection))[localClientNum]; }
		const static auto get_item_infos(eModes mode) { return &std::recast<item_infos_s*>(offsets::item_infos)[mode]; }
		const static auto get_player_inventory_data(ControllerIndex_t controllerIndex) { return &std::recast<player_inventory_data_s*>(offsets::player_inventory_data)[controllerIndex]; }
		const static auto get_config_strings() { return std::recast<config_strings_s*>(offsets::config_strings); }
		const static auto get_matchmaking_list() { return std::recast<matchmaking_list_s*>(offsets::matchmaking_list); }
	}

	namespace functions
	{
		template<typename... parameters>
		static void write_log(std::string line, parameters... params)
		{
			niggerware::utils::file::write_log(default_log, line, params...);
		}
		/*
		//=====================================================================================
		*/
		
		
		
		template<typename ret, typename... parameters>
		static inline auto spoof_call(ret(*func)(parameters...), parameters... params) -> ret
		{
			return niggerware::utils::call::spoof_call(std::recast<void*>(offsets::jmp_dwptr_rbx), func, params...);
		}
		/*
		//=====================================================================================
		*/
		static void CG_SimulateBulletFire_EndPos(std::uint32_t* randSeed, std::float_t spreadMin, std::float_t spreadMax, ImVec3 start, ImVec3* end, ImVec3* dir, std::float_t angleMin, std::float_t angleMax, ImVec3 forwardDir, ImVec3 rightDir, ImVec3 upDir, std::float_t maxRange, std::int64_t weapon, std::int32_t shotIndex, std::int32_t maxShotIndex)
		{
			return spoof_call(std::recast<decltype(CG_SimulateBulletFire_EndPos)*>(offsets::CG_SimulateBulletFire_EndPos), randSeed, spreadMin, spreadMax, start, end, dir, angleMin, angleMax, forwardDir, rightDir, upDir, maxRange, weapon, shotIndex, maxShotIndex);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_random(std::uint32_t* pHoldrand)
		{
			return spoof_call(std::recast<decltype(BG_random)*>(offsets::BG_random), pHoldrand);
		}
		/*
		//=====================================================================================
		*/
		static void BG_seedRandWithGameTime(std::uint32_t* pHoldrand)
		{
			return spoof_call(std::recast<decltype(BG_seedRandWithGameTime)*>(offsets::BG_seedRandWithGameTime), pHoldrand);
		}
		/*
		//=====================================================================================
		*/
	
		
		static char* host_bullshit(unsigned int a1)
		{
			return spoof_call(std::recast<decltype(host_bullshit)*>(offsets::host_bullshit), a1);
		}
		
		static structures::weapon_def_s* BG_GetWeaponDef(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponDef)*>(offsets::BG_GetWeaponDef), weapon);
		}
		/*
		//=====================================================================================
		*/
		static structures::weapon_full_def_s* BG_GetWeaponFullDef(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponFullDef)*>(offsets::BG_GetWeaponFullDef), weapon);
		}
		/*
		//=====================================================================================
		*/
		static void CG_GuessSpreadForWeapon(structures::LocalClientNum_t localClientNum, structures::centity_s* entity, structures::weapon_def_s* weapondef, std::float_t* minspread, std::float_t* maxspread)
		{
			return spoof_call(std::recast<decltype(CG_GuessSpreadForWeapon)*>(offsets::CG_GuessSpreadForWeapon), localClientNum, entity, weapondef, minspread, maxspread);
		}
		/*
		//=====================================================================================
		*/
		static void CG_GetPlayerViewOrigin(structures::LocalClientNum_t localClientNum, structures::player_state_s* ps, ImVec3* origin)
		{
			return spoof_call(std::recast<decltype(CG_GetPlayerViewOrigin)*>(offsets::CG_GetPlayerViewOrigin), localClientNum, ps, origin);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_GetPlayerWeapon(structures::player_state_s* ps, structures::LocalClientNum_t localClientNum, bool preferspin)
		{
			return spoof_call(std::recast<decltype(BG_GetPlayerWeapon)*>(offsets::BG_GetPlayerWeapon), ps, localClientNum, preferspin);
		}
		/*
		//=====================================================================================
		*/
		static bool CL_IsLocalClientInGame(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(CL_IsLocalClientInGame)*>(offsets::CL_IsLocalClientInGame), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t CG_LocationalTrace(structures::trace_t* trace, ImVec3 from, ImVec3 to, std::int32_t skip)
		{
			return spoof_call(std::recast<decltype(CG_LocationalTrace)*>(offsets::CG_LocationalTrace), trace, from, to, skip);
		}
		/*
		//=====================================================================================
		*/
		static void* Com_GetClientDObj(std::int32_t entitynum, structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(Com_GetClientDObj)*>(offsets::Com_GetClientDObj), entitynum, localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static std::uint32_t GScr_AllocString(const char* name)
		{
			return spoof_call(std::recast<decltype(GScr_AllocString)*>(offsets::GScr_AllocString), name);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_DObjGetWorldTagPos(structures::cpose_s* pose, void* dobj, std::uint32_t tag, ImVec3* position)
		{
			return spoof_call(std::recast<decltype(CG_DObjGetWorldTagPos)*>(offsets::CG_DObjGetWorldTagPos), pose, dobj, tag, position);
		}
		/*
		//=====================================================================================
		*/
		static bool BulletTraceSimulated(structures::LocalClientNum_t localClientNum, structures::BulletFireParams* bp, structures::BulletTraceResults* br, std::int64_t weapon, std::int32_t attackerNum, std::int32_t lastSurfaceType)
		{
			return spoof_call(std::recast<decltype(BulletTraceSimulated)*>(offsets::BulletTraceSimulated), localClientNum, bp, br, weapon, attackerNum, lastSurfaceType);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_SimulateBulletFire_BulletProcess(structures::LocalClientNum_t localClientNum, structures::BulletFireParams* bp, structures::BulletTraceResults* br, std::int64_t weapon, std::int32_t attackerNum, std::int32_t gameTime, std::int32_t dFlags, std::int32_t* outImpactFlags, bool processFx, std::uint32_t* randSeed, void* data)
		{
			return spoof_call(std::recast<decltype(CG_SimulateBulletFire_BulletProcess)*>(offsets::CG_SimulateBulletFire_BulletProcess), localClientNum, bp, br, weapon, attackerNum, gameTime, dFlags, outImpactFlags, processFx, randSeed, data);
		}
		/*
		//=====================================================================================
		*/
		static structures::dvar_t* Dvar_FindVar(const char* name)
		{
			return spoof_call(std::recast<decltype(Dvar_FindVar)*>(offsets::Dvar_FindVar), name);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_Bullet_AdvanceTrace(structures::BulletFireParams* bp, structures::BulletTraceResults* br, std::float_t distance)
		{
			return spoof_call(std::recast<decltype(BG_Bullet_AdvanceTrace)*>(offsets::BG_Bullet_AdvanceTrace), bp, br, distance);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_GetSurfacePenetrationDepth(structures::penetrate_type_e penetration, std::uint32_t surface)
		{
			return spoof_call(std::recast<decltype(BG_GetSurfacePenetrationDepth)*>(offsets::BG_GetSurfacePenetrationDepth), penetration, surface);
		}
		/*
		//=====================================================================================
		*/
		static structures::penetrate_type_e BG_GetPenetrateType(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetPenetrateType)*>(offsets::BG_GetPenetrateType), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::uint16_t Trace_GetEntityHitId(structures::trace_t* trace)
		{
			return spoof_call(std::recast<decltype(Trace_GetEntityHitId)*>(offsets::Trace_GetEntityHitId), trace);
		}
		/*
		//=====================================================================================
		*/
		static structures::screen_placement_s* ScrPlace_GetView(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(ScrPlace_GetView)*>(offsets::ScrPlace_GetView), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t Sys_Milliseconds()
		{
			return spoof_call(std::recast<decltype(Sys_Milliseconds)*>(offsets::Sys_Milliseconds));
		}
		/*
		//=====================================================================================
		*/
		static bool BG_Bullet_FirePenetrate(structures::LocalClientNum_t localClientNum, structures::BulletTraceHandler* handler, structures::BulletFireParams* bp, structures::BulletPenetrationInfo* penetrationInfo, std::int64_t weapon, std::int32_t attackerNum, std::float_t bulletPenetrationMultiplier, std::int32_t gameTime, std::uint32_t* randSeed, void* data)
		{
			return spoof_call(std::recast<decltype(BG_Bullet_FirePenetrate)*>(offsets::BG_Bullet_FirePenetrate), localClientNum, handler, bp, penetrationInfo, weapon, attackerNum, bulletPenetrationMultiplier, gameTime, randSeed, data);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t CL_SetADS(structures::LocalClientNum_t localClientNum, bool ads)
		{
			return spoof_call(std::recast<decltype(CL_SetADS)*>(offsets::CL_SetADS), localClientNum, ads);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_IsDualWield(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_IsDualWield)*>(offsets::BG_IsDualWield), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_GetMinDamageRangeScaled(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetMinDamageRangeScaled)*>(offsets::BG_GetMinDamageRangeScaled), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_GetMultishotBaseMinDamageRangeScaled(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetMultishotBaseMinDamageRangeScaled)*>(offsets::BG_GetMultishotBaseMinDamageRangeScaled), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t Dvar_GetFloat(structures::dvar_t* dvar)
		{
			return spoof_call(std::recast<decltype(Dvar_GetFloat)*>(offsets::Dvar_GetFloat), dvar);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UsingVehicleWeapon(structures::player_state_s* ps)
		{
			return spoof_call(std::recast<decltype(BG_UsingVehicleWeapon)*>(offsets::BG_UsingVehicleWeapon), ps);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_PrepFireParams(structures::LocalClientNum_t localClientNum, structures::centity_s* ent, std::uint32_t boneName, structures::player_state_s* ps, std::int64_t weapon, std::int32_t eventIndex, bool isPlayer, structures::BulletFireParams* bp, ImVec3* tracerStart, std::int32_t* shotCount, std::float_t* range, structures::orientation_s* orient, ImVec3* origin, std::float_t* aimSpreadAmount, std::int32_t* ignoreEntity)
		{
			return spoof_call(std::recast<decltype(CG_PrepFireParams)*>(offsets::CG_PrepFireParams), localClientNum, ent, boneName, ps, weapon, eventIndex, isPlayer, bp, tracerStart, shotCount, range, orient, origin, aimSpreadAmount, ignoreEntity);
		}
		/*
		//=====================================================================================
		*/
		static bool Live_IsUserInGame(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(Live_IsUserInGame)*>(offsets::Live_IsUserInGame), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_HasPerk(structures::player_state_s* ps, std::int32_t perk)
		{
			return spoof_call(std::recast<decltype(BG_HasPerk)*>(offsets::BG_HasPerk), ps, perk);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_Init(structures::msg_t* buf, char* data, std::size_t length)
		{
			return spoof_call(std::recast<decltype(MSG_Init)*>(offsets::MSG_Init), buf, data, length);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_WriteString(structures::msg_t* sb, const char* s)
		{
			return spoof_call(std::recast<decltype(MSG_WriteString)*>(offsets::MSG_WriteString), sb, s);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_WriteByte(structures::msg_t* msg, std::int32_t c)
		{
			return spoof_call(std::recast<decltype(MSG_WriteByte)*>(offsets::MSG_WriteByte), msg, c);
		}
		/*
		//=====================================================================================
		*/
		static bool NET_OutOfBandData(structures::netsrc_t sock, structures::netadr_t adr, const char* format, std::size_t len)
		{
			return spoof_call(std::recast<decltype(NET_OutOfBandData)*>(offsets::NET_OutOfBandData), sock, adr, format, len);
		}
		/*
		//=====================================================================================
		*/
		static structures::netsrc_t Com_ControllerIndex_GetNetworkID(std::int32_t controller)
		{
			return spoof_call(std::recast<decltype(Com_ControllerIndex_GetNetworkID)*>(offsets::Com_ControllerIndex_GetNetworkID), controller);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyPeerToPeer_CanITalkToPeer(structures::lobby_session_s* lobbysession, std::int32_t clientnum)
		{
			return spoof_call(std::recast<decltype(LobbyPeerToPeer_CanITalkToPeer)*>(offsets::LobbyPeerToPeer_CanITalkToPeer), lobbysession, clientnum);
		}
		/*
		//=====================================================================================
		*/
		static structures::tls_data_s* Sys_GetTLS()
		{
			return spoof_call(std::recast<decltype(Sys_GetTLS)*>(offsets::Sys_GetTLS));
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_GetWeaponHitLocationMultiplier(std::int64_t weapon, std::int32_t hitloc)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponHitLocationMultiplier)*>(offsets::BG_GetWeaponHitLocationMultiplier), weapon, hitloc);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t PM_WeaponAmmoAvailable(structures::player_state_s* ps)
		{
			return spoof_call(std::recast<decltype(PM_WeaponAmmoAvailable)*>(offsets::PM_WeaponAmmoAvailable), ps);
		}
		/*
		//=====================================================================================
		*/
		static void CL_AddReliableCommand(structures::LocalClientNum_t localClientNum, const char* command)
		{
			return spoof_call(std::recast<decltype(CL_AddReliableCommand)*>(offsets::CL_AddReliableCommand), localClientNum, command);
		}
		/*
		//=====================================================================================
		*/
		static void Cbuf_AddText(structures::LocalClientNum_t localClientNum, const char* command)
		{
			return spoof_call(std::recast<decltype(Cbuf_AddText)*>(offsets::Cbuf_AddText), localClientNum, command);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_Bullet_GetDepth(structures::BulletHitInfo* hitInfo, structures::BulletTraceResults* br, structures::BulletFireParams* revBp, structures::BulletTraceResults* revBr)
		{
			return spoof_call(std::recast<decltype(BG_Bullet_GetDepth)*>(offsets::BG_Bullet_GetDepth), hitInfo, br, revBp, revBr);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_Bullet_FixupHitInfo(structures::BulletPenetrationInfo *penetrationInfo, std::int32_t fix_up_count, std::int32_t last_valid_surface_penetration, std::int32_t last_valid_surface_type, std::int32_t next_valid_surface_type, std::float_t* damageMultiplier, std::float_t bulletPenetrationMultiplier, structures::penetrate_type_e penetrateType)
		{
			return spoof_call(std::recast<decltype(BG_Bullet_FixupHitInfo)*>(offsets::BG_Bullet_FixupHitInfo), penetrationInfo, fix_up_count, last_valid_surface_penetration, last_valid_surface_type, next_valid_surface_type, damageMultiplier, bulletPenetrationMultiplier, penetrateType);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t BG_GetWeaponDamageForRange(std::int64_t weapon, ImVec3 origstart, ImVec3 hitpos)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponDamageForRange)*>(offsets::BG_GetWeaponDamageForRange), weapon, origstart, hitpos);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t Dvar_GetInt(structures::dvar_t* dvar)
		{
			return spoof_call(std::recast<decltype(Dvar_GetInt)*>(offsets::Dvar_GetInt), dvar);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t SV_GameSendServerCommand(std::int32_t clientnum, structures::svscmd_type type, const char* command)
		{
			return spoof_call(std::recast<decltype(SV_GameSendServerCommand)*>(offsets::SV_GameSendServerCommand), clientnum, type, command);
		}
		/*
		//=====================================================================================
		*/
		static bool Loot_IncCurrency(structures::ControllerIndex_t controllerIndex, structures::InventoryCurrency currencyType, std::uint32_t amount)
		{
			return spoof_call(std::recast<decltype(Loot_IncCurrency)*>(offsets::Loot_IncCurrency), controllerIndex, currencyType, amount);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t GScr_AddRankXPToPlayerEnt(structures::gentity_s* entity, std::int32_t clientnum, std::int32_t rankxp)
		{
			return spoof_call(std::recast<decltype(GScr_AddRankXPToPlayerEnt)*>(offsets::GScr_AddRankXPToPlayerEnt), entity, clientnum, rankxp);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_GetSpreadForWeapon(structures::player_state_s* ps, std::int64_t weapon, std::float_t* minimum, std::float_t* maximum)
		{
			return spoof_call(std::recast<decltype(BG_GetSpreadForWeapon)*>(offsets::BG_GetSpreadForWeapon), ps, weapon, minimum, maximum);
		}
		/*
		//=====================================================================================
		*/
		static bool SendToClient(std::int32_t clientnum, const char* data, std::size_t len)
		{
			return spoof_call(std::recast<decltype(SendToClient)*>(offsets::SendToClient), clientnum, data, len);
		}
		/*
		//=====================================================================================
		*/
		static structures::lobby_session_s* LobbyClientSession_GetSession(structures::LobbyType lobbytype)
		{
			return spoof_call(std::recast<decltype(LobbyClientSession_GetSession)*>(offsets::LobbyClientSession_GetSession), lobbytype);
		}
		/*
		//=====================================================================================
		*/
		static structures::lobby_session_s* LobbyHostSession_GetSession(structures::LobbyType lobbytype)
		{
			return spoof_call(std::recast<decltype(LobbyHostSession_GetSession)*>(offsets::LobbyHostSession_GetSession), lobbytype);
		}
		/*
		//=====================================================================================
		*/
		static structures::session_client_s* LobbySession_GetClientByClientNum(structures::lobby_session_s* lobbysession, std::int32_t clientnum)
		{
			return spoof_call(std::recast<decltype(LobbySession_GetClientByClientNum)*>(offsets::LobbySession_GetClientByClientNum), lobbysession, clientnum);
		}
		/*
		//=====================================================================================
		*/
		static structures::netadr_t* LobbySession_GetClientNetAdrByIndex(structures::netadr_t* netadr, structures::LobbyType lobbytype, std::int32_t clientnum)
		{
			return spoof_call(std::recast<decltype(LobbySession_GetClientNetAdrByIndex)*>(offsets::LobbySession_GetClientNetAdrByIndex), netadr, lobbytype, clientnum);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t LiveStats_MoveToPlayerStatPath(std::int32_t clientnum, const char* stat, std::float_t statvalue, bool arenavalue)
		{
			return spoof_call(std::recast<decltype(LiveStats_MoveToPlayerStatPath)*>(offsets::LiveStats_MoveToPlayerStatPath), clientnum, stat, statvalue, arenavalue);
		}
		/*
		//=====================================================================================
		*/
		static structures::session_info_s* LobbyActiveList_GetSessionInfo(structures::active_client_s* activeclient, structures::LobbyType lobbytype)
		{
			return spoof_call(std::recast<decltype(LobbyActiveList_GetSessionInfo)*>(offsets::LobbyActiveList_GetSessionInfo), activeclient, lobbytype);
		}
		/*
		//=====================================================================================
		*/
		static char* NetAdr_ToString(const structures::netadr_t* adr)
		{
			return spoof_call(std::recast<decltype(NetAdr_ToString)*>(offsets::NetAdr_ToString), adr);
		}
		/*
		//=====================================================================================
		*/
		static bool Dvar_GetBool(structures::dvar_t* dvar)
		{
			return spoof_call(std::recast<decltype(Dvar_GetBool)*>(offsets::Dvar_GetBool), dvar);
		}
		/*
		//=====================================================================================
		*/
		static std::uint64_t LiveUser_GetXuid(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(LiveUser_GetXuid)*>(offsets::LiveUser_GetXuid), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static void LiveSteam_PopOverlayForSteamID(std::uint64_t steamid)
		{
			return spoof_call(std::recast<decltype(LiveSteam_PopOverlayForSteamID)*>(offsets::LiveSteam_PopOverlayForSteamID), steamid);
		}
		/*
		//=====================================================================================
		*/
		static void Dvar_SetFloat(structures::dvar_t* dvar, std::float_t value)
		{
			return spoof_call(std::recast<decltype(Dvar_SetFloat)*>(offsets::Dvar_SetFloat), dvar, value);
		}
		/*
		//=====================================================================================
		*/
		static void Dvar_SetInt(structures::dvar_t* dvar, std::int32_t value)
		{
			return spoof_call(std::recast<decltype(Dvar_SetInt)*>(offsets::Dvar_SetInt), dvar, value);
		}
		/*
		//=====================================================================================
		*/
		static void Dvar_SetBool(structures::dvar_t* dvar, bool value)
		{
			return spoof_call(std::recast<decltype(Dvar_SetBool)*>(offsets::Dvar_SetBool), dvar, value);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_DObjGetWorldTagMatrix(structures::cpose_s* pose, void* dobj, std::uint32_t tag, ImVec3 axis[3], ImVec3* origin)
		{
			return spoof_call(std::recast<decltype(CG_DObjGetWorldTagMatrix)*>(offsets::CG_DObjGetWorldTagMatrix), pose, dobj, tag, axis, origin);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t LiveStorage_UploadStatsForController(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(LiveStorage_UploadStatsForController)*>(offsets::LiveStorage_UploadStatsForController), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static structures::eModes Com_SessionMode_GetMode()
		{
			return spoof_call(std::recast<decltype(Com_SessionMode_GetMode)*>(offsets::Com_SessionMode_GetMode));
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t LiveStats_MoveToUnlockPath(structures::eModes mode, std::int64_t chararray, std::uint32_t unlockindex)
		{
			return spoof_call(std::recast<decltype(LiveStats_MoveToUnlockPath)*>(offsets::LiveStats_MoveToUnlockPath), mode, chararray, unlockindex);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_UnlockablesGetLocalCACRoot(std::int64_t cacRoot, std::int32_t controllerindex, std::int32_t customClass, structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesGetLocalCACRoot)*>(offsets::BG_UnlockablesGetLocalCACRoot), cacRoot, controllerindex, customClass, mode);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_UnlockablesSetLoadoutItem(std::int64_t cacRoot, std::int64_t classnum, std::uint32_t slot, std::uint32_t item)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesSetLoadoutItem)*>(offsets::BG_UnlockablesSetLoadoutItem), cacRoot, classnum, slot, item);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesIsItemLockedFromBuffer(std::int32_t a1, std::int64_t a2, std::int32_t a3)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesIsItemLockedFromBuffer)*>(offsets::BG_UnlockablesIsItemLockedFromBuffer), a1, a2, a3);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesIsItemDLCAvailable(std::uint32_t a1, std::uint32_t a2, std::uint32_t a3)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesIsItemDLCAvailable)*>(offsets::BG_UnlockablesIsItemDLCAvailable), a1, a2, a3);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesIsItemLocked(std::uint32_t a1, std::uint32_t a2, std::int32_t a3)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesIsItemLocked)*>(offsets::BG_UnlockablesIsItemLocked), a1, a2, a3);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesDLCWeaponDisabled(std::uint32_t a1, std::uint32_t a2)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesDLCWeaponDisabled)*>(offsets::BG_UnlockablesDLCWeaponDisabled), a1, a2);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesIsItemPublicPurchasedFromBuffer(std::uint32_t a1, std::int64_t a2, std::int32_t a3)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesIsItemPublicPurchasedFromBuffer)*>(offsets::BG_UnlockablesIsItemPublicPurchasedFromBuffer), a1, a2, a3);
		}
		/*
		//=====================================================================================
		*/
		static bool BG_UnlockablesIsItemPurchasedFromBuffer(std::uint32_t a1, std::int64_t a2, std::int32_t a3)
		{
			return spoof_call(std::recast<decltype(BG_UnlockablesIsItemPurchasedFromBuffer)*>(offsets::BG_UnlockablesIsItemPurchasedFromBuffer), a1, a2, a3);
		}
		/*
		//=====================================================================================
		*/
		static bool LiveStats_SetClanTagText(structures::ControllerIndex_t controllerIndex, const char* clantag)
		{
			return spoof_call(std::recast<decltype(LiveStats_SetClanTagText)*>(offsets::LiveStats_SetClanTagText), controllerIndex, clantag);
		}
		/*
		//=====================================================================================
		*/
		static char* CL_ControllerIndex_GetUsername(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(CL_ControllerIndex_GetUsername)*>(offsets::CL_ControllerIndex_GetUsername), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static char* LiveStats_GetClanName(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(LiveStats_GetClanName)*>(offsets::LiveStats_GetClanName), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static char* LiveUser_GetXuidString(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(LiveUser_GetXuidString)*>(offsets::LiveUser_GetXuidString), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static structures::player_inventory_data_s* LiveInventory_GetPlayerInventory(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(LiveInventory_GetPlayerInventory)*>(offsets::LiveInventory_GetPlayerInventory), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static structures::loot_item_s* LiveInventory_GetPlayerInventoryItemId(structures::ControllerIndex_t controllerIndex, std::int32_t item)
		{
			return spoof_call(std::recast<decltype(LiveInventory_GetPlayerInventoryItemId)*>(offsets::LiveInventory_GetPlayerInventoryItemId), controllerIndex, item);
		}
		/*
		//=====================================================================================
		*/
		static structures::DDLState* LiveStats_GetRootDDLState(structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(LiveStats_GetRootDDLState)*>(offsets::LiveStats_GetRootDDLState), mode);
		}
		/*
		//=====================================================================================
		*/
		static bool DDL_MoveToPath(const structures::DDLState* fromState, structures::DDLState* toState, std::int32_t depth, const char** path)
		{
			return spoof_call(std::recast<decltype(DDL_MoveToPath)*>(offsets::DDL_MoveToPath), fromState, toState, depth, path);
		}
		/*
		//=====================================================================================
		*/
		static bool DDL_SetUInt(structures::DDLState* state, structures::DDLContext* context, std::uint32_t value)
		{
			return spoof_call(std::recast<decltype(DDL_SetUInt)*>(offsets::DDL_SetUInt), state, context, value);
		}
		/*
		//=====================================================================================
		*/
		static bool DDL_SetInt(structures::DDLState* state, structures::DDLContext* context, std::int32_t value)
		{
			return spoof_call(std::recast<decltype(DDL_SetInt)*>(offsets::DDL_SetInt), state, context, value);
		}
		/*
		//=====================================================================================
		*/
		static structures::DDLContext* LiveStats_Core_GetDDLContext(structures::ControllerIndex_t controllerIndex, structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(LiveStats_Core_GetDDLContext)*>(offsets::LiveStats_Core_GetDDLContext), controllerIndex, mode);
		}
		/*
		//=====================================================================================
		*/
		static structures::DDLContext* LiveStats_Core_GetStableDDLContext(structures::ControllerIndex_t controllerIndex, structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(LiveStats_Core_GetStableDDLContext)*>(offsets::LiveStats_Core_GetStableDDLContext), controllerIndex, mode);
		}
		/*
		//=====================================================================================
		*/
		static void LobbyVM_JoinEvent(structures::ControllerIndex_t controllerIndex, std::uint64_t xuid, structures::JoinType joinType)
		{
			return spoof_call(std::recast<decltype(LobbyVM_JoinEvent)*>(offsets::LobbyVM_JoinEvent), controllerIndex, xuid, joinType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyClientSession_IsHost(structures::LobbyType lobbyType)
		{
			return spoof_call(std::recast<decltype(LobbyClientSession_IsHost)*>(offsets::LobbyClientSession_IsHost), lobbyType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyHostSession_IsHost(structures::LobbyType lobbyType)
		{
			return spoof_call(std::recast<decltype(LobbyHostSession_IsHost)*>(offsets::LobbyHostSession_IsHost), lobbyType);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_IsEntityFriendly(structures::LocalClientNum_t localClientNum, structures::centity_s* entity)
		{
			return spoof_call(std::recast<decltype(CG_IsEntityFriendly)*>(offsets::CG_IsEntityFriendly), localClientNum, entity);
		}
		/*
		//=====================================================================================
		*/
		static std::uint32_t DDL_GetUInt(const structures::DDLState* state, const structures::DDLContext* context)
		{
			return spoof_call(std::recast<decltype(DDL_GetUInt)*>(offsets::DDL_GetUInt), state, context);
		}
		/*
		//=====================================================================================
		*/
		static void SV_SetClientStat(std::int32_t clientnum, std::int64_t ddlpath, std::int64_t value)
		{
			return spoof_call(std::recast<decltype(SV_SetClientStat)*>(offsets::SV_SetClientStat), clientnum, ddlpath, value);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t dwInstantSendMessage(structures::ControllerIndex_t controllerIndex, const std::uint64_t* recipientUIDs, std::size_t numRecipients, char msgType, void* message, std::uint32_t msgSize)
		{
			return spoof_call(std::recast<decltype(dwInstantSendMessage)*>(offsets::dwInstantSendMessage), controllerIndex, recipientUIDs, numRecipients, msgType, message, msgSize);
		}
		/*
		//=====================================================================================
		*/
		static structures::player_status_s* Live_GetPlayerStatusByXuid(structures::ControllerIndex_t controllerIndex, std::uint64_t xuid)
		{
			return spoof_call(std::recast<decltype(Live_GetPlayerStatusByXuid)*>(offsets::Live_GetPlayerStatusByXuid), controllerIndex, xuid);
		}
		/*
		//=====================================================================================
		*/
		static const char* UI_SafeTranslateString(const char* string)
		{
			return spoof_call(std::recast<decltype(UI_SafeTranslateString)*>(offsets::UI_SafeTranslateString), string);
		}
		/*
		//=====================================================================================
		*/
		static bool NET_OutOfBandPrint(structures::netsrc_t sock, structures::netadr_t adr, const char* data)
		{
			return spoof_call(std::recast<decltype(NET_OutOfBandPrint)*>(offsets::NET_OutOfBandPrint), sock, adr, data);
		}
		/*
		//=====================================================================================
		*/
		static void BG_FactionData_GetTeamColor(structures::LocalClientNum_t localClientNum, std::int32_t team, ImVec4* color, bool alpha)
		{
			return spoof_call(std::recast<decltype(BG_FactionData_GetTeamColor)*>(offsets::BG_FactionData_GetTeamColor), localClientNum, team, color, alpha);
		}
		/*
		//=====================================================================================
		*/
		static bool Com_SessionMode_IsMode(structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(Com_SessionMode_IsMode)*>(offsets::Com_SessionMode_IsMode), mode);
		}
		/*
		//=====================================================================================
		*/
		static void CG_GetDObjOrientation(structures::LocalClientNum_t localClientNum, std::int32_t entitynum, ImVec3* axis, ImVec3* origin)
		{
			return spoof_call(std::recast<decltype(CG_GetDObjOrientation)*>(offsets::CG_GetDObjOrientation), localClientNum, entitynum, axis, origin);
		}
		/*
		//=====================================================================================
		*/
		static void DObjCalcBounds(void* dobj, ImVec3* mins, ImVec3* maxs)
		{
			return spoof_call(std::recast<decltype(DObjCalcBounds)*>(offsets::DObjCalcBounds), dobj, mins, maxs);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_GetAmmoInClip(structures::player_state_s* ps, std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetAmmoInClip)*>(offsets::BG_GetAmmoInClip), ps, weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_GetClipSize(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetClipSize)*>(offsets::BG_GetClipSize), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_GetDualWieldWeapon(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetDualWieldWeapon)*>(offsets::BG_GetDualWieldWeapon), weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t BG_GetAmmoNotInClip(structures::player_state_s* ps, std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetAmmoNotInClip)*>(offsets::BG_GetAmmoNotInClip), ps, weapon);
		}
		/*
		//=====================================================================================
		*/
		static void CG_CycleWeapon(structures::LocalClientNum_t localClientNum, bool cycleForward, structures::PlayerRoleButtonOverrideTypes buttonOverride, bool bAllowBallSwitch)
		{
			return spoof_call(std::recast<decltype(CG_CycleWeapon)*>(offsets::CG_CycleWeapon), localClientNum, cycleForward, buttonOverride, bAllowBallSwitch);
		}
		/*
		//=====================================================================================
		*/
		static bool dwNetadrToCommonAddr(const structures::netadr_t* netadr, structures::XNADDR* commonAddrBuf, std::size_t commonAddrBufSize, structures::bdSecurityID* id)
		{
			return spoof_call(std::recast<decltype(dwNetadrToCommonAddr)*>(offsets::dwNetadrToCommonAddr), netadr, commonAddrBuf, commonAddrBufSize, id);
		}
		/*
		//=====================================================================================
		*/
		static bool CL_LocalClientIsInGame(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(CL_LocalClientIsInGame)*>(offsets::CL_LocalClientIsInGame), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbySession_IsClientNumHost(structures::LobbyType lobbytype, std::int32_t clientnum)
		{
			return spoof_call(std::recast<decltype(LobbySession_IsClientNumHost)*>(offsets::LobbySession_IsClientNumHost), lobbytype, clientnum);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t LobbySession_GetClientNumByXuid(structures::LobbyType lobbytype, std::uint64_t xuid)
		{
			return spoof_call(std::recast<decltype(LobbySession_GetClientNumByXuid)*>(offsets::LobbySession_GetClientNumByXuid), lobbytype, xuid);
		}
		/*
		//=====================================================================================
		*/
		static std::uint64_t LobbySession_GetClientXuidByClientNum(structures::LobbyType lobbytype, std::int32_t clientnum)
		{
			return spoof_call(std::recast<decltype(LobbySession_GetClientXuidByClientNum)*>(offsets::LobbySession_GetClientXuidByClientNum), lobbytype, clientnum);
		}
		/*
		//=====================================================================================
		*/
		static const char* LobbyActiveList_GetGamertag(structures::active_client_s* activeclient)
		{
			return spoof_call(std::recast<decltype(LobbyActiveList_GetGamertag)*>(offsets::LobbyActiveList_GetGamertag), activeclient);
		}
		/*
		//=====================================================================================
		*/
		static void Dvar_SetFromStringByName(const char* name, const char* value, bool create)
		{
			return spoof_call(std::recast<decltype(Dvar_SetFromStringByName)*>(offsets::Dvar_SetFromStringByName), name, value, create);
		}
		/*
		//=====================================================================================
		*/
		static void StringTable_GetAsset(const char* filename, structures::StringTable** tablePtr)
		{
			return spoof_call(std::recast<decltype(StringTable_GetAsset)*>(offsets::StringTable_GetAsset), filename, tablePtr);
		}
		/*
		//=====================================================================================
		*/
		static const char* StringTable_Lookup(structures::StringTable* table, std::int32_t comparisonColumn, const char* value, std::int32_t valueColumn)
		{
			return spoof_call(std::recast<decltype(StringTable_Lookup)*>(offsets::StringTable_Lookup), table, comparisonColumn, value, valueColumn);
		}
		/*
		//=====================================================================================
		*/
		static structures::DDLContext* LiveStorage_GetStatsBufferWithCaller(structures::ControllerIndex_t controllerIndex, const char* file, const char* func, std::int32_t line, structures::eModes mode, structures::statsLocation playerStatsLocation)
		{
			return spoof_call(std::recast<decltype(LiveStorage_GetStatsBufferWithCaller)*>(offsets::LiveStorage_GetStatsBufferWithCaller), controllerIndex, file, func, line, mode, playerStatsLocation);
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t SV_SetClientInt64Stat(std::int32_t clientNum, char* searchState, std::uint64_t value, structures::statsLocation location)
		{
			return spoof_call(std::recast<decltype(SV_SetClientInt64Stat)*>(offsets::SV_SetClientInt64Stat), clientNum, searchState, value, location);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t StringTable_LookupRowNumForValue(structures::StringTable* table, std::int32_t comparisonColumn, const char* value)
		{
			return spoof_call(std::recast<decltype(StringTable_LookupRowNumForValue)*>(offsets::StringTable_LookupRowNumForValue), table, comparisonColumn, value);
		}
		/*
		//=====================================================================================
		*/
		static const char* StringTable_GetColumnValueForRow(structures::StringTable* table, std::int32_t row, std::int32_t column)
		{
			return spoof_call(std::recast<decltype(StringTable_GetColumnValueForRow)*>(offsets::StringTable_GetColumnValueForRow), table, row, column);
		}
		/*
		//=====================================================================================
		*/
		static std::uint32_t dwCommonAddrToString(structures::XNADDR* commonAddrBuf, std::size_t commonAddrBufSize, char* buf, std::size_t length)
		{
			return spoof_call(std::recast<decltype(dwCommonAddrToString)*>(offsets::dwCommonAddrToString), commonAddrBuf, commonAddrBufSize, buf, length);
		}
		/*
		//=====================================================================================
		*/
		static bool NetAdr_Compare(const structures::netadr_t* a, const structures::netadr_t* b)
		{
			return spoof_call(std::recast<decltype(NetAdr_Compare)*>(offsets::NetAdr_Compare), a, b);
		}
		/*
		//=====================================================================================
		*/
		static bool LiveFriends_IsFriendByXUID(structures::ControllerIndex_t controllerIndex, std::uint64_t xuid)
		{
			return spoof_call(std::recast<decltype(LiveFriends_IsFriendByXUID)*>(offsets::LiveFriends_IsFriendByXUID), controllerIndex, xuid);
		}
		/*
		//=====================================================================================
		*/
		static bool LiveUser_IsXUIDLocalPlayer(std::uint64_t xuid)
		{
			return spoof_call(std::recast<decltype(LiveUser_IsXUIDLocalPlayer)*>(offsets::LiveUser_IsXUIDLocalPlayer), xuid);
		}
		/*
		//=====================================================================================
		*/
		static const char* BG_GetWeaponName(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponName)*>(offsets::BG_GetWeaponName), weapon);
		}
		/*
		//=====================================================================================
		*/
		static const char* BG_GetWeaponDisplayName(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetWeaponDisplayName)*>(offsets::BG_GetWeaponDisplayName), weapon);
		}
		/*
		//=====================================================================================
		*/
		static bool Live_IsUserSignedInToDemonware(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(Live_IsUserSignedInToDemonware)*>(offsets::Live_IsUserSignedInToDemonware), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static structures::Material* Material_RegisterHandle(const char* name, std::int64_t imageTrack, bool errorIfMissing, std::int32_t waitTime)
		{
			return spoof_call(std::recast<decltype(Material_RegisterHandle)*>(offsets::Material_RegisterHandle), name, imageTrack, errorIfMissing, waitTime);
		}
		/*
		//=====================================================================================
		*/
		static std::float_t AngleNormalize360(std::float_t angle)
		{
			return spoof_call(std::recast<decltype(AngleNormalize360)*>(offsets::AngleNormalize360), angle);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_ClientHasPerk(structures::LocalClientNum_t localClientNum, std::int32_t clientnum, std::int32_t perk)
		{
			return spoof_call(std::recast<decltype(CG_ClientHasPerk)*>(offsets::CG_ClientHasPerk), localClientNum, clientnum, perk);
		}
		/*
		//=====================================================================================
		*/
		static bool CG_IsThirdPerson(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(CG_IsThirdPerson)*>(offsets::CG_IsThirdPerson), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static structures::player_state_s* CG_GetPredictedPlayerState(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(CG_GetPredictedPlayerState)*>(offsets::CG_GetPredictedPlayerState), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static structures::client_active_s* CL_GetLocalClientGlobals(structures::LocalClientNum_t localClientNum)
		{
			return spoof_call(std::recast<decltype(CL_GetLocalClientGlobals)*>(offsets::CL_GetLocalClientGlobals), localClientNum);
		}
		/*
		//=====================================================================================
		*/
		static structures::cpose_s* CG_GetPose(structures::LocalClientNum_t localClientNum, std::int32_t entitynum)
		{
			return spoof_call(std::recast<decltype(CG_GetPose)*>(offsets::CG_GetPose), localClientNum, entitynum);
		}
		/*
		//=====================================================================================
		*/
		static structures::gentity_s* G_GetEntity(structures::scr_entref_s* entref, structures::LocalClientNum_t localClientNum, std::int32_t entitynum)
		{
			return spoof_call(std::recast<decltype(G_GetEntity)*>(offsets::G_GetEntity), entref, localClientNum, entitynum);
		}
		/*
		//=====================================================================================
		*/
		static bool dwRegisterSecIDAndKey(const structures::bdSecurityID* id, const structures::bdSecurityKey* key)
		{
			return spoof_call(std::recast<decltype(dwRegisterSecIDAndKey)*>(offsets::dwRegisterSecIDAndKey), id, key);
		}
		/*
		//=====================================================================================
		*/
		static bool dwCommonAddrToNetadr(structures::netadr_t* const netadr, const structures::XNADDR* const commonAddrBuf, const structures::bdSecurityID* id)
		{
			return spoof_call(std::recast<decltype(dwCommonAddrToNetadr)*>(offsets::dwCommonAddrToNetadr), netadr, commonAddrBuf, id);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_InitReadOnly(structures::msg_t* buf, const char* data, std::size_t length)
		{
			return spoof_call(std::recast<decltype(MSG_InitReadOnly)*>(offsets::MSG_InitReadOnly), buf, data, length);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_BeginReading(structures::msg_t* msg)
		{
			return spoof_call(std::recast<decltype(MSG_BeginReading)*>(offsets::MSG_BeginReading), msg);
		}
		/*
		//=====================================================================================
		*/
		static std::uint8_t MSG_ReadByte(structures::msg_t* msg)
		{
			return spoof_call(std::recast<decltype(MSG_ReadByte)*>(offsets::MSG_ReadByte), msg);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsg_SendInfoRequest(const structures::ControllerIndex_t controllerIndex, const std::uint64_t* xuid, std::int32_t xuidCount, const structures::Msg_InfoRequest* msgData)
		{
			return spoof_call(std::recast<decltype(LobbyMsg_SendInfoRequest)*>(offsets::LobbyMsg_SendInfoRequest), controllerIndex, xuid, xuidCount, msgData);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PrepReadData(structures::LobbyMsg* lobbyMsg, char* data, std::size_t length)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PrepReadData)*>(offsets::LobbyMsgRW_PrepReadData), lobbyMsg, data, length);
		}
		/*
		//=====================================================================================
		*/
		static void MSG_ReadData(structures::msg_t* msg, char* data, std::size_t len)
		{
			return spoof_call(std::recast<decltype(MSG_ReadData)*>(offsets::MSG_ReadData), msg, data, len);
		}
		/*
		//=====================================================================================
		*/
		static bool Msg_InfoResponse(structures::Msg_InfoResponse* msgData, structures::LobbyMsg* lobbyMsg)
		{
			return spoof_call(std::recast<decltype(Msg_InfoResponse)*>(offsets::Msg_InfoResponse), msgData, lobbyMsg);
		}
		/*
		//=====================================================================================
		*/
		static bool Com_SessionMode_IsPublicOnlineGame()
		{
			return spoof_call(std::recast<decltype(Com_SessionMode_IsPublicOnlineGame)*>(offsets::Com_SessionMode_IsPublicOnlineGame));
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PrepWriteMsg(structures::LobbyMsg* lobbyMsg, char* data, std::int32_t length, structures::MsgType msgType)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PrepWriteMsg)*>(offsets::LobbyMsgRW_PrepWriteMsg), lobbyMsg, data, length, msgType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageUInt(structures::LobbyMsg* lobbyMsg, const char* key, std::uint32_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageUInt)*>(offsets::LobbyMsgRW_PackageUInt), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool Live_IsDemonwareFetchingDone(structures::ControllerIndex_t controllerIndex)
		{
			return spoof_call(std::recast<decltype(Live_IsDemonwareFetchingDone)*>(offsets::Live_IsDemonwareFetchingDone), controllerIndex);
		}
		/*
		//=====================================================================================
		*/
		static bool Com_IsInGame()
		{
			return spoof_call(std::recast<decltype(Com_IsInGame)*>(offsets::Com_IsInGame));
		}
		/*
		//=====================================================================================
		*/
		static void MSG_Discard(structures::msg_t* msg)
		{
			return spoof_call(std::recast<decltype(MSG_Discard)*>(offsets::MSG_Discard), msg);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyClientMsg_SendDisconnectClient(const structures::ControllerIndex_t controllerIndex, structures::LobbyType lobbyType, std::uint64_t xuid, structures::LobbyDisconnectClient disconnectClient)
		{
			return spoof_call(std::recast<decltype(LobbyClientMsg_SendDisconnectClient)*>(offsets::LobbyClientMsg_SendDisconnectClient), controllerIndex, lobbyType, xuid, disconnectClient);
		}
		/*
		//=====================================================================================
		*/
		static const char* Dvar_GetString(structures::dvar_t* dvar)
		{
			return spoof_call(std::recast<decltype(Dvar_GetString)*>(offsets::Dvar_GetString), dvar);
		}
		/*
		//=====================================================================================
		*/
		static void Dvar_SetString(structures::dvar_t* dvar, const char* value)
		{
			return spoof_call(std::recast<decltype(Dvar_SetString)*>(offsets::Dvar_SetString), dvar, value);
		}
		/*
		//=====================================================================================
		*/
		static void Cmd_TokenizeStringNoEval(const char* text_in)
		{
			return spoof_call(std::recast<decltype(Cmd_TokenizeStringNoEval)*>(offsets::Cmd_TokenizeStringNoEval), text_in);
		}
		/*
		//=====================================================================================
		*/
		static void Cmd_EndTokenizedString()
		{
			return spoof_call(std::recast<decltype(Cmd_EndTokenizedString)*>(offsets::Cmd_EndTokenizedString));
		}
		/*
		//=====================================================================================
		*/
		static void CG_BoldGameMessage(structures::LocalClientNum_t localClientNum, const char* message, std::int32_t duration)
		{
			return spoof_call(std::recast<decltype(CG_BoldGameMessage)*>(offsets::CG_BoldGameMessage), localClientNum, message, duration);
		}
		/*
		//=====================================================================================
		*/
		static void CG_BoldGameMessageCenter(structures::LocalClientNum_t localClientNum, const char* message)
		{
			return spoof_call(std::recast<decltype(CG_BoldGameMessageCenter)*>(offsets::CG_BoldGameMessageCenter), localClientNum, message);
		}
		/*
		//=====================================================================================
		*/
		static void CG_GameMessage(structures::LocalClientNum_t localClientNum, const char* message)
		{
			return spoof_call(std::recast<decltype(CG_GameMessage)*>(offsets::CG_GameMessage), localClientNum, message);
		}
		/*
		//=====================================================================================
		*/
		static const char* CL_GetConfigString(std::int32_t configStringIndex)
		{
			return spoof_call(std::recast<decltype(CL_GetConfigString)*>(offsets::CL_GetConfigString), configStringIndex);
		}
		/*
		//=====================================================================================
		*/
		static void CL_StoreConfigString(std::int32_t index, const char* s)
		{
			return spoof_call(std::recast<decltype(CL_StoreConfigString)*>(offsets::CL_StoreConfigString), index, s);
		}
		/*
		//=====================================================================================
		*/
		static bool WallRun_IsWallRunning(structures::player_state_s* ps)
		{
			return spoof_call(std::recast<decltype(WallRun_IsWallRunning)*>(offsets::WallRun_IsWallRunning), ps);
		}
		/*
		//=====================================================================================
		*/
		static bool Slide_IsPlayerSliding(structures::player_state_s* ps)
		{
			return spoof_call(std::recast<decltype(Slide_IsPlayerSliding)*>(offsets::Slide_IsPlayerSliding), ps);
		}
		/*
		//=====================================================================================
		*/
		static bool PM_IsSprinting(structures::player_state_s* ps)
		{
			return spoof_call(std::recast<decltype(PM_IsSprinting)*>(offsets::PM_IsSprinting), ps);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PrepReadMsg(structures::LobbyMsg* lobbyMsg, structures::msg_t* msg)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PrepReadMsg)*>(offsets::LobbyMsgRW_PrepReadMsg), lobbyMsg, msg);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbySession_GetControllingLobbySession(structures::LobbyModule lobbymodule)
		{
			return spoof_call(std::recast<decltype(LobbySession_GetControllingLobbySession)*>(offsets::LobbySession_GetControllingLobbySession), lobbymodule);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageElement(structures::LobbyMsg* lobbyMsg, bool addElement)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageElement)*>(offsets::LobbyMsgRW_PackageElement), lobbyMsg, addElement);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageInt(structures::LobbyMsg* lobbyMsg, const char* key, std::int32_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageInt)*>(offsets::LobbyMsgRW_PackageInt), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageUChar(structures::LobbyMsg* lobbyMsg, const char* key, std::uint8_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageUChar)*>(offsets::LobbyMsgRW_PackageUChar), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageUShort(structures::LobbyMsg* lobbyMsg, const char* key, std::uint16_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageUShort)*>(offsets::LobbyMsgRW_PackageUShort), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageGlob(structures::LobbyMsg* lobbyMsg, const char* key, void* val, std::int32_t numbytes)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageGlob)*>(offsets::LobbyMsgRW_PackageGlob), lobbyMsg, key, val, numbytes);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgTransport_SendOutOfBand(structures::ControllerIndex_t controllerIndex, std::uint64_t targetXuid, structures::netadr_t adr, structures::msg_t* msg, structures::MsgType msgType)
		{
			return spoof_call(std::recast<decltype(LobbyMsgTransport_SendOutOfBand)*>(offsets::LobbyMsgTransport_SendOutOfBand), controllerIndex, targetXuid, adr, msg, msgType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgTransport_SendToAdr(structures::ControllerIndex_t controllerIndex, structures::NetChanMsgType_e channel, structures::LobbyModule destModule, structures::netadr_t adr, std::uint64_t toXuid, structures::msg_t* msg, structures::MsgType msgType)
		{
			return spoof_call(std::recast<decltype(LobbyMsgTransport_SendToAdr)*>(offsets::LobbyMsgTransport_SendToAdr), controllerIndex, channel, destModule, adr, toXuid, msg, msgType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyClientMsg_SendModifiedStats(structures::ControllerIndex_t controllerIndex, structures::LobbyType lobbyType)
		{
			return spoof_call(std::recast<decltype(LobbyClientMsg_SendModifiedStats)*>(offsets::LobbyClientMsg_SendModifiedStats), controllerIndex, lobbyType);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t DDL_GetInt(const structures::DDLState* state, const structures::DDLContext* context)
		{
			return spoof_call(std::recast<decltype(DDL_GetInt)*>(offsets::DDL_GetInt), state, context);
		}
		/*
		//=====================================================================================
		*/
		static const structures::DDLState* Storage_GetDDLRootState(const structures::StorageFileType fileType)
		{
			return spoof_call(std::recast<decltype(Storage_GetDDLRootState)*>(offsets::Storage_GetDDLRootState), fileType);
		}
		/*
		//=====================================================================================
		*/
		static structures::DDLContext* Storage_GetDDLContext(const structures::ControllerIndex_t controllerIndex, const structures::StorageFileType fileType, structures::StorageSlot slot)
		{
			return spoof_call(std::recast<decltype(Storage_GetDDLContext)*>(offsets::Storage_GetDDLContext), controllerIndex, fileType, slot);
		}
		/*
		//=====================================================================================
		*/
		static const char* LobbyTypes_GetMsgTypeName(structures::MsgType msgType)
		{
			return spoof_call(std::recast<decltype(LobbyTypes_GetMsgTypeName)*>(offsets::LobbyTypes_GetMsgTypeName), msgType);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t BG_GetFireTime(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetFireTime)*>(offsets::BG_GetFireTime), weapon);
		}
		/*
		//=====================================================================================
		*/
		static structures::weapon_fire_type_e BG_GetFireType(std::int64_t weapon)
		{
			return spoof_call(std::recast<decltype(BG_GetFireType)*>(offsets::BG_GetFireType), weapon);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_ReadArrayBegin(structures::LobbyMsg* lobbyMsg, const char* expectedKey)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_ReadArrayBegin)*>(offsets::LobbyMsgRW_ReadArrayBegin), lobbyMsg, expectedKey);
		}
		/*
		//=====================================================================================
		*/
		static void Message_Key_Internal(structures::LocalClientNum_t localClientNum, const char* chatText, structures::chatChannel_e chatChannel)
		{
			return spoof_call(std::recast<decltype(Message_Key_Internal)*>(offsets::Message_Key_Internal), localClientNum, chatText, chatChannel);
		}
		/*
		//=====================================================================================
		*/
		static void G_ParseHitLocDmgTable()
		{
			return spoof_call(std::recast<decltype(G_ParseHitLocDmgTable)*>(offsets::G_ParseHitLocDmgTable));
		}
		/*
		//=====================================================================================
		*/
		static void SendLobbyChatMsg(const char* pchMsgBody)
		{
			return spoof_call(std::recast<decltype(SendLobbyChatMsg)*>(offsets::SendLobbyChatMsg), pchMsgBody);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageArrayStart(structures::LobbyMsg* lobbyMsg, const char* key)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageArrayStart)*>(offsets::LobbyMsgRW_PackageArrayStart), lobbyMsg, key);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageBool(structures::LobbyMsg* lobbyMsg, const char* key, bool* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageBool)*>(offsets::LobbyMsgRW_PackageBool), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageChar(structures::LobbyMsg* lobbyMsg, const char* key, std::int8_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageChar)*>(offsets::LobbyMsgRW_PackageChar), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageFloat(structures::LobbyMsg* lobbyMsg, const char* key, std::float_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageFloat)*>(offsets::LobbyMsgRW_PackageFloat), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageShort(structures::LobbyMsg* lobbyMsg, const char* key, std::int16_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageShort)*>(offsets::LobbyMsgRW_PackageShort), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageString(structures::LobbyMsg* lobbyMsg, const char* key, char* val, const std::int32_t maxChar)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageString)*>(offsets::LobbyMsgRW_PackageString), lobbyMsg, key, val, maxChar);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageUInt64(structures::LobbyMsg* lobbyMsg, const char* key, std::uint64_t* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageUInt64)*>(offsets::LobbyMsgRW_PackageUInt64), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbyMsgRW_PackageXuid(structures::LobbyMsg* lobbyMsg, const char* key, structures::XUID* val)
		{
			return spoof_call(std::recast<decltype(LobbyMsgRW_PackageXuid)*>(offsets::LobbyMsgRW_PackageXuid), lobbyMsg, key, val);
		}
		/*
		//=====================================================================================
		*/
		static bool Msg_LobbyState(structures::Msg_LobbyState* msgData, structures::LobbyMsg* lobbyMsg)
		{
			return spoof_call(std::recast<decltype(Msg_LobbyState)*>(offsets::Msg_LobbyState), msgData, lobbyMsg);
		}
		/*
		//=====================================================================================
		*/
		static bool Loot_BuyCrate(structures::ControllerIndex_t controllerIndex, structures::LootCrateType crateType, structures::InventoryCurrency currencyType)
		{
			return spoof_call(std::recast<decltype(Loot_BuyCrate)*>(offsets::Loot_BuyCrate), controllerIndex, crateType, currencyType);
		}
		/*
		//=====================================================================================
		*/
		static bool Loot_BurnDuplicates(structures::ControllerIndex_t controllerIndex, structures::eModes mode)
		{
			return spoof_call(std::recast<decltype(Loot_BurnDuplicates)*>(offsets::Loot_BurnDuplicates), controllerIndex, mode);
		}
		/*
		//=====================================================================================
		*/
		static bool Loot_SpendVials(structures::ControllerIndex_t controllerIndex, std::uint32_t vialCount)
		{
			return spoof_call(std::recast<decltype(Loot_SpendVials)*>(offsets::Loot_SpendVials), controllerIndex, vialCount);
		}
		/*
		//=====================================================================================
		*/
		static bool Loot_LiquefyGum(structures::ControllerIndex_t controllerIndex, structures::eModes mode, const char* itemName, bool burnAll)
		{
			return spoof_call(std::recast<decltype(Loot_LiquefyGum)*>(offsets::Loot_LiquefyGum), controllerIndex, mode, itemName, burnAll);
		}
		/*
		//=====================================================================================
		*/
		static void Com_SessionMode_SetNetworkMode(structures::eNetworkModes mode)
		{
			return spoof_call(std::recast<decltype(Com_SessionMode_SetNetworkMode)*>(offsets::Com_SessionMode_SetNetworkMode), mode);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbySearch_SearchSession(structures::lobby_session_s* lobbysession)
		{
			return spoof_call(std::recast<decltype(LobbySearch_SearchSession)*>(offsets::LobbySearch_SearchSession), lobbysession);
		}
		/*
		//=====================================================================================
		*/
		static structures::lobby_session_s* LobbySession_GetSession(structures::LobbyModule lobbyModule, structures::LobbyType lobbyType)
		{
			if (lobbyModule)
				return LobbyClientSession_GetSession(lobbyType);

			else
				return LobbyHostSession_GetSession(lobbyType);
		}
		/*
		//=====================================================================================
		*/
		static bool LobbySession_IsHost(structures::LobbyModule lobbyModule, structures::LobbyType lobbyType)
		{
			if (lobbyModule)
				return LobbyClientSession_IsHost(lobbyType);

			else
				return LobbyHostSession_IsHost(lobbyType);
		}
		/*
		//=====================================================================================
		*/
		static std::string XNKIDToString(structures::XNKID* xnkid)
		{
			return niggerware::utils::string::va
			(
				"%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
				xnkid->ab[0],
				xnkid->ab[1],
				xnkid->ab[2],
				xnkid->ab[3],
				xnkid->ab[4],
				xnkid->ab[5],
				xnkid->ab[6],
				xnkid->ab[7]
			);
		}
		/*
		//=====================================================================================
		*/
		static std::string XNADDRToString(structures::XNADDR* xnaddr)
		{
			return niggerware::utils::string::va
			(
				"%u.%u.%u.%u:%u",
				xnaddr->addrBuff.ab.ipv4.octets[0],
				xnaddr->addrBuff.ab.ipv4.octets[1],
				xnaddr->addrBuff.ab.ipv4.octets[2],
				xnaddr->addrBuff.ab.ipv4.octets[3],
				xnaddr->addrBuff.ab.port
			);
		}
		/*
		//=====================================================================================
		*/
		static std::string XNKEYToString(structures::XNKEY* xnkey)
		{
			return niggerware::utils::string::va
			(
				"%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
				xnkey->ab[0],
				xnkey->ab[1],
				xnkey->ab[2],
				xnkey->ab[3],
				xnkey->ab[4],
				xnkey->ab[5],
				xnkey->ab[6],
				xnkey->ab[7],
				xnkey->ab[8],
				xnkey->ab[9],
				xnkey->ab[10],
				xnkey->ab[11],
				xnkey->ab[12],
				xnkey->ab[13],
				xnkey->ab[14],
				xnkey->ab[15]
			);
		}
		/*
		//=====================================================================================
		*/
		static structures::cg_s* get_cg()
		{
			auto player_state = CG_GetPredictedPlayerState(structures::LOCAL_CLIENT_FIRST);

			return std::recast<structures::cg_s*>(std::recast<std::uintptr_t>(player_state) - 0x11A8B0);
		}
		/*
		//=====================================================================================
		*/
		static structures::client_active_s* get_client_active()
		{
			return CL_GetLocalClientGlobals(structures::LOCAL_CLIENT_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static structures::centity_s* get_centity(std::int32_t entitynum)
		{
			auto cpose = CG_GetPose(structures::LOCAL_CLIENT_FIRST, entitynum);

			return std::recast<structures::centity_s*>(cpose);
		}
		/*
		//=====================================================================================
		*/
		static structures::gentity_s* get_gentity(std::int32_t entitynum) 
		{ 
			structures::scr_entref_s entref;

			return G_GetEntity(&entref, structures::LOCAL_CLIENT_FIRST, entitynum);
		}
		/*
		//=====================================================================================
		*/
		static const char* dvar_get_string(std::uintptr_t address)
		{
			return Dvar_GetString(*std::recast<structures::dvar_t**>(address));
		}
		/*
		//=====================================================================================
		*/
		static std::float_t dvar_get_float(std::uintptr_t address)
		{
			return Dvar_GetFloat(*std::recast<structures::dvar_t**>(address));
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t dvar_get_int(std::uintptr_t address)
		{
			return Dvar_GetInt(*std::recast<structures::dvar_t**>(address));
		}
		/*
		//=====================================================================================
		*/
		static bool dvar_get_bool(std::uintptr_t address)
		{
			return Dvar_GetBool(*std::recast<structures::dvar_t**>(address));
		}
		/*
		//=====================================================================================
		*/
		static void dvar_set_string(std::uintptr_t address, const char* value)
		{
			Dvar_SetString(*std::recast<structures::dvar_t**>(address), value);
		}
		/*
		//=====================================================================================
		*/
		static void dvar_set_float(std::uintptr_t address, std::float_t value)
		{
			Dvar_SetFloat(*std::recast<structures::dvar_t**>(address), value);
		}
		/*
		//=====================================================================================
		*/
		static void dvar_set_int(std::uintptr_t address, std::int32_t value)
		{
			Dvar_SetInt(*std::recast<structures::dvar_t**>(address), value);
		}
		/*
		//=====================================================================================
		*/
		static void dvar_set_bool(std::uintptr_t address, bool value)
		{
			Dvar_SetBool(*std::recast<structures::dvar_t**>(address), value);
		}
		/*
		//=====================================================================================
		*/
		static std::string insert_newline_chars(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, place_holder_newline_char, "\n");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string insert_tab_chars(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, place_holder_tab_char, "\t");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string insert_hex_chars(std::string text)
		{
			std::size_t pos;

			while ((pos = niggerware::utils::string::to_lower(text).find(niggerware::utils::string::to_lower(place_holder_hex_value))) != std::string::npos)
				text.replace(pos, std::strlen(place_holder_hex_value) + 2, 1, (niggerware::utils::string::stoul(text.substr(pos + std::strlen(place_holder_hex_value), 2), nullptr, 0x10) & 0xFF));

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string insert_random_color(std::string text)
		{
			static std::random_device random_device;
			static std::uniform_int_distribution random_color_code(0, 9);

			std::size_t pos;

			while ((pos = niggerware::utils::string::to_lower(text).find(niggerware::utils::string::to_lower(place_holder_random_color))) != std::string::npos)
				text.replace(pos, std::strlen(place_holder_random_color), "^" + std::to_string(random_color_code(random_device)));

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string insert_crash_shader(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, place_holder_crash, crash_invalid_material);

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string remove_color_codes(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "^0");
			text = niggerware::utils::string::find_and_erase(text, "^1");
			text = niggerware::utils::string::find_and_erase(text, "^2");
			text = niggerware::utils::string::find_and_erase(text, "^3");
			text = niggerware::utils::string::find_and_erase(text, "^4");
			text = niggerware::utils::string::find_and_erase(text, "^5");
			text = niggerware::utils::string::find_and_erase(text, "^6");
			text = niggerware::utils::string::find_and_erase(text, "^7");
			text = niggerware::utils::string::find_and_erase(text, "^8");
			text = niggerware::utils::string::find_and_erase(text, "^9");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string remove_material_handles(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "^H");
			text = niggerware::utils::string::find_and_erase(text, "^I");
			text = niggerware::utils::string::find_and_erase(text, "^B");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string remove_model_paths(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "$(");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string remove_escape_sequences(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "\a");
			text = niggerware::utils::string::find_and_erase(text, "\b");
			text = niggerware::utils::string::find_and_erase(text, "\f");
			text = niggerware::utils::string::find_and_erase(text, "\n");
			text = niggerware::utils::string::find_and_erase(text, "\r");
			text = niggerware::utils::string::find_and_erase(text, "\t");
			text = niggerware::utils::string::find_and_erase(text, "\v");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string remove_modifiers(std::string text)
		{
			text = remove_color_codes(text);
			text = remove_material_handles(text);
			text = remove_model_paths(text);
			text = remove_escape_sequences(text);

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string replace_material_handles(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, "^H", "&H");
			text = niggerware::utils::string::find_and_replace(text, "^I", "&I");
			text = niggerware::utils::string::find_and_replace(text, "^B", "&B");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string replace_model_paths(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, "$(", "&(");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string replace_escape_sequences(std::string text)
		{
			text = niggerware::utils::string::find_and_replace(text, "\a", "\\a");
			text = niggerware::utils::string::find_and_replace(text, "\b", "\\b");
			text = niggerware::utils::string::find_and_replace(text, "\f", "\\f");
			text = niggerware::utils::string::find_and_replace(text, "\n", "\\n");
			text = niggerware::utils::string::find_and_replace(text, "\r", "\\r");
			text = niggerware::utils::string::find_and_replace(text, "\t", "\\t");
			text = niggerware::utils::string::find_and_replace(text, "\v", "\\v");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string clean_name(std::string name)
		{
			name = remove_color_codes(name);
			name = remove_material_handles(name);
			name = remove_model_paths(name);
			name = replace_escape_sequences(name);

			return name;
		}
		/*
		//=====================================================================================
		*/
		static structures::LobbyModule get_current_lobby_module()
		{
			return structures::LOBBY_MODULE_CLIENT;
		}
		/*
		//=====================================================================================
		*/
		static structures::LobbyType get_current_lobby_type()
		{
			if (LobbySession_GetControllingLobbySession(structures::LOBBY_MODULE_CLIENT))
			{
				return structures::LOBBY_TYPE_GAME;
			}

			else
			{
				return structures::LOBBY_TYPE_PRIVATE;
			}
		}
		/*
		//=====================================================================================
		*/
		static structures::lobby_session_s* get_current_lobby_session()
		{
			return LobbySession_GetSession(get_current_lobby_module(), get_current_lobby_type());
		}
		/*
		//=====================================================================================
		*/
		static structures::session_client_s* get_session_client(std::int32_t clientnum)
		{
			return LobbySession_GetClientByClientNum(get_current_lobby_session(), clientnum);
		}
		/*
		//=====================================================================================
		*/
		static structures::netadr_t get_client_netadr(std::int32_t clientnum)
		{
			structures::netadr_t client_adr{};
			LobbySession_GetClientNetAdrByIndex(&client_adr, get_current_lobby_type(), clientnum);

			return client_adr;
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_name(std::int32_t clientnum)
		{
			if (auto session_client{ get_session_client(clientnum) }; session_client && session_client->activeClient && clientnum > -1)
			{
				return clean_name(LobbyActiveList_GetGamertag(session_client->activeClient));
			}

			return {};
		}
		/*
		//=====================================================================================
		*/
		static std::int64_t get_weapon_base_index(std::int64_t weapon)
		{
			return (weapon & 0x1FF);
		}
		/*
		//=====================================================================================
		*/
		static std::string get_weapon_display_name(std::int64_t weapon)
		{
			if (auto weapon_display_name{ BG_GetWeaponDisplayName(weapon) }; weapon_display_name)
			{
				return UI_SafeTranslateString(weapon_display_name);
			}

			return {};
		}
		/*
		//=====================================================================================
		*/
		static std::string get_weapon_name(std::int32_t clientnum)
		{
			return get_weapon_display_name(get_centity(clientnum)->nextState.weapon);
		}
		/*
		//=====================================================================================
		*/
		static std::uint64_t get_client_xuid(std::int32_t clientnum)
		{
			return LobbySession_GetClientXuidByClientNum(get_current_lobby_type(), clientnum);
		}
		/*
		//=====================================================================================
		*/
		static std::uint64_t get_client_xuid(const structures::netadr_t* clientadr)
		{
			for (auto i = 0; i < max_clients; i++)
			{
				auto netadr = get_client_netadr(i);

				if (NetAdr_Compare(&netadr, clientadr))
				{
					return LobbySession_GetClientXuidByClientNum(get_current_lobby_type(), i);
				}
			}

			return 0;
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t get_client_num(std::uint64_t clientxuid)
		{
			return LobbySession_GetClientNumByXuid(get_current_lobby_type(), clientxuid);
		}
		/*
		//=====================================================================================
		*/
		static std::int32_t get_client_num(const structures::netadr_t* clientadr)
		{
			for (auto i = 0; i < max_clients; i++)
			{
				auto netadr = get_client_netadr(i);

				if (NetAdr_Compare(&netadr, clientadr))
				{
					return i;
				}
			}

			return -1;
		}
		/*
		//=====================================================================================
		*/
		static bool can_i_talk_to_peer(std::int32_t clientnum)
		{
			return LobbyPeerToPeer_CanITalkToPeer(get_current_lobby_session(), clientnum);
		}
		/*
		//=====================================================================================
		*/
		static std::uint64_t get_our_xuid()
		{
			return LiveUser_GetXuid(structures::CONTROLLER_INDEX_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static std::string get_our_xuid_string()
		{
			return LiveUser_GetXuidString(structures::CONTROLLER_INDEX_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static bool are_we_host()
		{
			return LobbySession_IsHost(get_current_lobby_module(), get_current_lobby_type());
		}
		/*
		//=====================================================================================
		*/
		static bool is_client_num_host(std::int32_t clientnum)
		{
			return LobbySession_IsClientNumHost(get_current_lobby_type(), clientnum);
		}
		/*
		//=====================================================================================
		*/
		static bool weapon_is_buckshot()
		{
			if (auto weapon_def{ BG_GetWeaponDef(BG_GetPlayerWeapon(&get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false)) }; weapon_def && (weapon_def->weaponClass == structures::weapclass_spread || weapon_def->weaponClass == structures::weapclass_pistol_spread))
				return true;

			return false;
		}
		/*
		//=====================================================================================
		*/
		static std::float_t get_bullet_range()
		{
			if (weapon_is_buckshot())
			{
				auto min_damage = BG_GetMultishotBaseMinDamageRangeScaled(BG_GetPlayerWeapon(&get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false));
				auto damage_range_scale = BG_GetMinDamageRangeScaled(BG_GetPlayerWeapon(&get_cg()->predictedPlayerState, structures::LOCAL_CLIENT_FIRST, false));

				return std::min(min_damage, damage_range_scale);
			}

			return dvar_get_float(offsets::sv_bullet_range);
		}
		/*
		//=====================================================================================
		*/
		static niggerware::utils::misc::ipv4_c get_ip_address(const structures::netadr_t* netadr)
		{
			structures::XNADDR xnaddr{};
			dwNetadrToCommonAddr(netadr, &xnaddr, sizeof(structures::XNADDR), nullptr);

			return { xnaddr.addrBuff.ab.ipv4.octets };
		}
		/*
		//=====================================================================================
		*/
		static niggerware::utils::misc::ipv4_c get_ip_address(const std::int32_t clientnum)
		{
			auto netadr = get_client_netadr(clientnum);

			structures::XNADDR xnaddr{};
			dwNetadrToCommonAddr(&netadr, &xnaddr, sizeof(structures::XNADDR), nullptr);

			return { xnaddr.addrBuff.ab.ipv4.octets };
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(std::int32_t clientnum)
		{
			return niggerware::utils::string::va("{ name:%s, ip:%s, id:%llu }", get_client_name(clientnum).c_str(), get_ip_address(clientnum).to_string().c_str(), get_client_xuid(clientnum));
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(const structures::netadr_t* netadr)
		{
			return niggerware::utils::string::va("{ ip:%s }", get_ip_address(netadr).to_string().c_str());
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(const std::uint64_t xuid)
		{
			return niggerware::utils::string::va("{ id:%llu }", xuid);
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(std::string name, const structures::netadr_t* netadr)
		{
			return niggerware::utils::string::va("{ name:%s, ip:%s }", name.c_str(), get_ip_address(netadr).to_string().c_str());
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(std::string name, const std::uint64_t xuid)
		{
			return niggerware::utils::string::va("{ name:%s, id:%llu } ", name.c_str(), xuid);
		}
		/*
		//=====================================================================================
		*/
		static std::string get_client_identity(const structures::netadr_t* netadr, const std::uint64_t xuid)
		{
			return niggerware::utils::string::va("{ ip:%s, id:%llu }", get_ip_address(netadr).to_string().c_str(), xuid);
		}
		/*
		//=====================================================================================
		*/
		static void send_chat_message_all(std::string message)
		{
			SendLobbyChatMsg(niggerware::utils::string::va("%i %s", structures::CHAT_CHANNEL_ALL, message.c_str()).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void send_chat_message_team(std::string message)
		{
			SendLobbyChatMsg(niggerware::utils::string::va("%i %s", structures::CHAT_CHANNEL_TEAM, message.c_str()).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void send_chat_message_party(std::string message)
		{
			SendLobbyChatMsg(niggerware::utils::string::va("%i %s", structures::CHAT_CHANNEL_PARTY, message.c_str()).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void call_vote(std::string message)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("callvote %s\n", message.c_str()).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void vote(std::string message)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("vote %s\n", message.c_str()).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void auth_user(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("authUser %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void unauth_user(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("unauthUser %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void ban_user(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("banUser %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void unban_user(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("unbanUser %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void auth_user_master(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("authUserMaster %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void unauth_user_master(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("unauthUserMaster %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void ban_user_master(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("banUserMaster %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void unban_user_master(std::uint64_t xuid)
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("unbanUserMaster %llu\n", xuid).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void disconnect_server()
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, "sl");
		}
		/*
		//=====================================================================================
		*/
		static void crash_server()
		{
			LobbyClientMsg_SendModifiedStats(structures::CONTROLLER_INDEX_FIRST, structures::LOBBY_TYPE_GAME);
		}
		/*
		//=====================================================================================
		*/
		static void loadside_server()
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("loadside 0 %s dm 1", dvar_get_string(offsets::ui_mapname)).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void set_network_mode_online()
		{
			Com_SessionMode_SetNetworkMode(structures::MODE_NETWORK_ONLINE);
		}
		/*
		//=====================================================================================
		*/
		static void end_round()
		{
			CL_AddReliableCommand(structures::LOCAL_CLIENT_FIRST, niggerware::utils::string::va("mr %i -1 endround", *std::recast<std::uint32_t*>(offsets::server_id)).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void disconnect()
		{
			Cbuf_AddText(structures::LOCAL_CLIENT_FIRST, "disconnect");
		}
		/*
		//=====================================================================================
		*/
		static void give_crypto_keys(std::int32_t clientnum, std::int32_t amount)
		{
			SV_GameSendServerCommand(clientnum, structures::SV_CMD_RELIABLE, niggerware::utils::string::va("x %u %u", structures::INVENTORY_CURRENCY_MP_LOOT_XP, amount * 100).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void take_crypto_keys(std::int32_t clientnum, std::int32_t amount)
		{
			SV_GameSendServerCommand(clientnum, structures::SV_CMD_RELIABLE, niggerware::utils::string::va("y %u %u", structures::INVENTORY_CURRENCY_MP_LOOT_XP, amount * 100).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void give_liquid_divinium(std::int32_t clientnum, std::int32_t amount)
		{
			SV_GameSendServerCommand(clientnum, structures::SV_CMD_RELIABLE, niggerware::utils::string::va("x %u %u", structures::INVENTORY_CURRENCY_ZM_VIALS, amount).c_str());
		}
		/*
		//=====================================================================================
		*/
		static void take_liquid_divinium(std::int32_t clientnum, std::int32_t amount)
		{
			SV_GameSendServerCommand(clientnum, structures::SV_CMD_RELIABLE, niggerware::utils::string::va("y %u %u", structures::INVENTORY_CURRENCY_ZM_VIALS, amount).c_str());
		}
		/*
		//=====================================================================================
		*/
		static bool is_local_client_in_game()
		{
			return CL_IsLocalClientInGame(structures::LOCAL_CLIENT_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static bool local_client_is_in_game()
		{
			return CL_LocalClientIsInGame(structures::LOCAL_CLIENT_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static bool is_user_in_game()
		{
			return Live_IsUserInGame(structures::CONTROLLER_INDEX_FIRST);
		}
		/*
		//=====================================================================================
		*/
		static bool is_in_game()
		{
			return Com_IsInGame();
		}
		/*
		//=====================================================================================
		*/
		static bool is_match_loaded()
		{
			return (is_local_client_in_game() && local_client_is_in_game() && is_user_in_game() && is_in_game());
		}
		/*
		//=====================================================================================
		*/
		static bool local_player_is_valid()
		{
			return ((get_cg()->predictedPlayerEntity.alive & 0x2) && !(get_cg()->predictedPlayerEntity.nextState.lerp.eFlags[1] & entity_flag_dead));
		}
		/*
		//=====================================================================================
		*/
		static bool CG_IsPlayerReloading()
		{
			return ((get_cg()->predictedPlayerState.weaponState - 12) <= 8 || (get_cg()->predictedPlayerState.weaponStateLeft - 12) <= 8);
		}
		/*
		//=====================================================================================
		*/
		static bool is_player_out_of_ammo()
		{
			return (CG_IsPlayerReloading() || PM_WeaponAmmoAvailable(&get_cg()->predictedPlayerState) == 0);
		}
		/*
		//=====================================================================================
		*/
		static bool is_third_person()
		{
			return (get_cg()->bThirdPerson | get_cg()->predictedPlayerState.bThirdPerson);
		}
		/*
		//=====================================================================================
		*/
		static void set_third_person(bool enable)
		{
			get_cg()->bThirdPerson = get_cg()->predictedPlayerState.bThirdPerson = enable;
		}
		/*
		//=====================================================================================
		*/
		static std::string parse_place_holders(std::string text)
		{
			text = insert_newline_chars(text);
			text = insert_tab_chars(text);
			text = insert_hex_chars(text);
			text = insert_random_color(text);
			text = insert_crash_shader(text);

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string parse_place_holders(std::string text, std::uint32_t attacker, std::uint32_t victim)
		{
			text = niggerware::utils::string::find_and_replace(text, place_holder_attacker, get_client_name(attacker));
			text = niggerware::utils::string::find_and_replace(text, place_holder_victim, get_client_name(victim));
			text = niggerware::utils::string::find_and_replace(text, place_holder_ip, get_ip_address(victim).to_string());

			return text;
		}
		/*
		//=====================================================================================
		*/
		static void show_place_holder_info()
		{
			if (ImGui::GetMouseCursor() == ImGuiMouseCursor_TextInput)
			{
				ImGui::BeginTooltipEx(0, ImGuiTooltipFlags_OverridePreviousTooltip);
				ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCol_TextDisabled);

				ImGui::TextUnformatted(niggerware::utils::string::va
				(
					"%s = your name\n%s = their name\n%s = their ip",
					place_holder_attacker, place_holder_victim, place_holder_ip
				).c_str());

				ImGui::PopStyleColor();
				ImGui::EndTooltip();
			}
		}
		/*
		//=====================================================================================
		*/
		static std::string strip_color_codes(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "^0");
			text = niggerware::utils::string::find_and_erase(text, "^1");
			text = niggerware::utils::string::find_and_erase(text, "^2");
			text = niggerware::utils::string::find_and_erase(text, "^3");
			text = niggerware::utils::string::find_and_erase(text, "^4");
			text = niggerware::utils::string::find_and_erase(text, "^5");
			text = niggerware::utils::string::find_and_erase(text, "^6");
			text = niggerware::utils::string::find_and_erase(text, "^7");
			text = niggerware::utils::string::find_and_erase(text, "^8");
			text = niggerware::utils::string::find_and_erase(text, "^9");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string strip_material_handles(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "^H");
			text = niggerware::utils::string::find_and_erase(text, "^I");
			text = niggerware::utils::string::find_and_erase(text, "^B");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string strip_model_paths(std::string text)
		{
			text = niggerware::utils::string::find_and_erase(text, "$(");

			return text;
		}
		/*
		//=====================================================================================
		*/
		static std::string strip_modifiers(std::string text)
		{
			text = strip_color_codes(text);
			text = strip_material_handles(text);
			text = strip_model_paths(text);

			return text;
		}
		/*
		//=====================================================================================
		*/
		static bool has_invalid_material_chars(std::string text)
		{
			if (text.empty())
			{
				return true;
			}

			for (auto& c : text)
			{
				if (!::isalnum(c) && c != '$' && c != '/' && c != '_')
				{
					return true;
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_invalid_material(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '^')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == 'H' || material.type == 'I')
					{
						if (name.size() > 5)
						{
							material.length = name.at(4);
							material.name = name.substr(5, material.length);

							if (material.name.size() < material.length)
							{
								return true;
							}

							else if (has_invalid_material_chars(material.name))
							{
								return true;
							}
						}

						else
						{
							return true;
						}
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_invalid_button(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '^')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == 'B')
					{
						if (name.size() > 2)
						{
							material.name = name.substr(2);
							material.length = material.name.find('^');

							if (material.length >= 64)
							{
								return true;
							}

							else if (material.length == std::string::npos)
							{
								return true;
							}
						}

						else
						{
							return true;
						}
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_invalid_model(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '$')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == '(')
					{
						if (name.size() > 2)
						{
							material.name = name.substr(2);
							material.length = material.name.find(')');

							if (material.length >= 64)
							{
								return true;
							}

							else if (material.length == std::string::npos)
							{
								return true;
							}
						}

						else
						{
							return true;
						}
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_material(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '^')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == 'H' || material.type == 'I')
					{
						return true;
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_button(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '^')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == 'B')
					{
						return true;
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static bool is_model(std::string name)
		{
			structures::material_name_s material;

			material.prefix = name.at(0);

			if (material.prefix == '$')
			{
				if (name.size() > 1)
				{
					material.type = name.at(1);

					if (material.type == '(')
					{
						return true;
					}
				}
			}

			return false;
		}
		/*
		//=====================================================================================
		*/
		static std::size_t find_materials(std::string text)
		{
			if (auto pos{ text.find("^H") }; pos != std::string::npos)
				return pos;
			if (auto pos{ text.find("^I") }; pos != std::string::npos)
				return pos;

			return std::string::npos;
		}
		/*
		//=====================================================================================
		*/
		static std::size_t find_buttons(std::string text)
		{
			if (auto pos{ text.find("^B") }; pos != std::string::npos)
				return pos;

			return std::string::npos;
		}
		/*
		//=====================================================================================
		*/
		static std::size_t find_models(std::string text)
		{
			if (auto pos{ text.find("$(") }; pos != std::string::npos)
				return pos;

			return std::string::npos;
		}
		/*
		//=====================================================================================
		*/
		static std::size_t find_invalid_materials(std::string text)
		{
			std::size_t pos = 0u;

			while ((pos = text.find('^', pos)) != std::string::npos)
			{
				if (is_invalid_material(text.substr(pos)))
				{
					return pos;
				}

				if (is_invalid_button(text.substr(pos)))
				{
					return pos;
				}

				pos++;
			}

			return std::string::npos;
		}
		/*
		//=====================================================================================
		*/
		static std::size_t find_invalid_models(std::string text)
		{
			std::size_t pos = 0u;

			while ((pos = text.find('$', pos)) != std::string::npos)
			{
				if (is_invalid_model(text.substr(pos)))
				{
					return pos;
				}

				pos++;
			}

			return std::string::npos;
		}
		/*
		//=====================================================================================
		*/
		static ImVec3 get_view_origin()
		{
			ImVec3 view_origin;
			CG_GetPlayerViewOrigin(structures::LOCAL_CLIENT_FIRST, &get_cg()->predictedPlayerState, &view_origin);

			if (BG_UsingVehicleWeapon(&get_cg()->predictedPlayerState))
			{
				return get_cg()->refDef.viewOrigin;
			}

			else
			{
				return view_origin;
			}
		}
		/*
		//=====================================================================================
		*/
		static ImVec3 get_view_angles()
		{
			if (BG_UsingVehicleWeapon(&get_cg()->predictedPlayerState))
			{
				return get_cg()->predictedPlayerState.viewAngles;
			}

			else if (is_third_person())
			{
				return get_cg()->refDefViewAngles;
			}

			else
			{
				return { get_cg()->gunPitch, get_cg()->gunYaw, 0.0f };
			}
		}
		/*
		//=====================================================================================
		*/
		static structures::cmd_args_s* get_cmd_args()
		{
			if (auto cmd_args{ std::recast<structures::cmd_args_s*>(Sys_GetTLS()->cmdArgs) }; cmd_args)
			{
				return cmd_args;
			}

			return nullptr;
		}
	}
}

//=====================================================================================

#include "Notification.hpp"

//=====================================================================================