//=====================================================================================

#pragma once

#include "Engine/Engine.hpp"

//=====================================================================================

#define ZwContinue(ThreadContext, RaiseAlert) { ZwContinue_o(ThreadContext, RaiseAlert); return; }

//=====================================================================================

namespace t7
{
	void __fastcall CG_Draw2DInternal_h(structures::LocalClientNum_t localClientNum);
	typedef decltype(CG_Draw2DInternal_h)* CG_Draw2DInternal_t;
	extern CG_Draw2DInternal_t CG_Draw2DInternal_o;

	structures::usercmd_s* __fastcall CL_CreateCmd_h(structures::usercmd_s* retstr, structures::LocalClientNum_t localClientNum);
	typedef decltype(CL_CreateCmd_h)* CL_CreateCmd_t;
	extern CL_CreateCmd_t CL_CreateCmd_o;

	void __fastcall CL_CreateNewCommands_h(structures::LocalClientNum_t localClientNum);
	typedef decltype(CL_CreateNewCommands_h)* CL_CreateNewCommands_t;
	extern CL_CreateNewCommands_t CL_CreateNewCommands_o;

	void __fastcall CL_WritePacket_h(structures::LocalClientNum_t localClientNum);
	typedef decltype(CL_WritePacket_h)* CL_WritePacket_t;
	extern CL_WritePacket_t CL_WritePacket_o;

	void __fastcall BG_WeaponFireRecoil_h(structures::player_state_s* ps, std::float_t fPitchMove, std::float_t fYawMove, ImVec2* recoilSpeed, ImVec3* kickAVel, std::int32_t* previousRecoilTime, bool previouslyFiring, std::float_t* previousRecoilRatio, std::uint32_t* holdrand);
	typedef decltype(BG_WeaponFireRecoil_h)* BG_WeaponFireRecoil_t;
	extern BG_WeaponFireRecoil_t BG_WeaponFireRecoil_o;

	void __fastcall CG_TransitionPlayerState_h(structures::LocalClientNum_t localClientNum, structures::player_state_s* ps, structures::trans_player_state_s* ops);
	typedef decltype(CG_TransitionPlayerState_h)* CG_TransitionPlayerState_t;
	extern CG_TransitionPlayerState_t CG_TransitionPlayerState_o;

	void __fastcall CG_BulletHitEvent_h(structures::LocalClientNum_t localClientNum, std::int64_t sourceEntityNum, std::int64_t targetEntityNum, std::int64_t weapon, ImVec3 startPos, ImVec3 position, ImVec3 normal, std::int32_t surfType, std::int32_t eventIndex, char eventParam, std::int32_t hitContents, std::int16_t boneIndex, std::int32_t modelIndex);
	typedef decltype(CG_BulletHitEvent_h)* CG_BulletHitEvent_t;
	extern CG_BulletHitEvent_t CG_BulletHitEvent_o;

	void __fastcall CG_UpdateThirdPersonPlayerEntity_h(structures::LocalClientNum_t localClientNum);
	typedef decltype(CG_UpdateThirdPersonPlayerEntity_h)* CG_UpdateThirdPersonPlayerEntity_t;
	extern CG_UpdateThirdPersonPlayerEntity_t CG_UpdateThirdPersonPlayerEntity_o;

	bool __fastcall CG_OffsetThirdPersonView_GetViewOrgFromDObj_h(structures::LocalClientNum_t localClientNum, structures::cg_s* cgameGlob);
	typedef decltype(CG_OffsetThirdPersonView_GetViewOrgFromDObj_h)* CG_OffsetThirdPersonView_GetViewOrgFromDObj_t;
	extern CG_OffsetThirdPersonView_GetViewOrgFromDObj_t CG_OffsetThirdPersonView_GetViewOrgFromDObj_o;

	void __fastcall CG_Obituary_h(structures::LocalClientNum_t localClientNum, structures::entity_state_s* ent);
	typedef decltype(CG_Obituary_h)* CG_Obituary_t;
	extern CG_Obituary_t CG_Obituary_o;

	bool __fastcall CG_DeployServerCommand_h(structures::LocalClientNum_t localClientNum);
	typedef decltype(CG_DeployServerCommand_h)* CG_DeployServerCommand_t;
	extern CG_DeployServerCommand_t CG_DeployServerCommand_o;

	const char* __fastcall LiveSteam_FilterPersonaName_h(char* name, std::size_t size, bool ascii);
	typedef decltype(LiveSteam_FilterPersonaName_h)* LiveSteam_FilterPersonaName_t;
	extern LiveSteam_FilterPersonaName_t LiveSteam_FilterPersonaName_o;

	void __fastcall Utf8safe_strncpyz_h(char* dst, const char* src, std::size_t size);
	typedef decltype(Utf8safe_strncpyz_h)* Utf8safe_strncpyz_t;
	extern Utf8safe_strncpyz_t Utf8safe_strncpyz_o;

	typedef NTSTATUS(__fastcall* ZwContinue_t)(LPCONTEXT ThreadContext, BOOLEAN RaiseAlert);
	extern ZwContinue_t ZwContinue_o;

	class hooks_c
	{
	public:

		hooks_c() : handler_thunk(&hooks_c::handler, this) { }

		HINSTANCE cheat_base;

		structures::tls_data_s* sys_value;
		structures::Material* material_ptr;
		structures::dvar_t* r_fullscreen, *cg_draw2D, *loc_warnings, *loc_language, *lobbymsg_prints, *com_sv_running;

		bool hooked_all;
		niggerware::utils::misc::timer_c hook_timer;
		niggerware::utils::hook::min_hook_c manager;

		void init(HINSTANCE instance);
		void free();

		void enable_all();
		void disable_all();
		void handle_hooks();

		void set_name(std::string name);

		void CL_ConnectionlessCMD(LPCONTEXT Context);
		void dwInstantDispatchMessage(LPCONTEXT Context);
		void LobbyMsgRW_PackageElement(LPCONTEXT Context);
		void UI_DoModelStringReplacement(LPCONTEXT Context);

		void MainWndProc(LPCONTEXT Context);
		void CG_Draw2DInternal(LPCONTEXT Context);
		void UI_Interface_DrawText(LPCONTEXT Context);
		void UI_Interface_GetNumTextLines(LPCONTEXT Context);
		void UI_Interface_GetTextWidthHeight(LPCONTEXT Context);
		void HandlePacketInternal(LPCONTEXT Context);
		void Com_Frame(LPCONTEXT Context);

		void create_exception_handler();
		void destroy_exception_handler();

		bool is_dvar_retaddr(LPCONTEXT Context, std::uintptr_t retaddr);
		void catch_exception(LPEXCEPTION_RECORD ExceptionRecord, LPCONTEXT ContextRecord);

		void handler(LPEXCEPTION_RECORD ExceptionRecord, LPCONTEXT ContextRecord);
		niggerware::utils::thunk::cdecl_c<void(*)(LPEXCEPTION_RECORD, LPCONTEXT), hooks_c> handler_thunk;
	};

	extern hooks_c hooks;
}

//=====================================================================================