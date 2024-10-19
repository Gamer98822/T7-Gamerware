//=====================================================================================

#pragma once

#include "Engine/Engine.hpp"

//=====================================================================================

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//=====================================================================================

namespace t7
{
	constexpr auto max_virtual_keys = 0x100;

	HRESULT __fastcall Present_h(IDXGISwapChain* _this, void* rdx, void* r8, void* r9, UINT SyncInterval, UINT Flags);
	typedef decltype(Present_h)* Present_t;
	extern Present_t Present_o;

	HRESULT __fastcall ResizeBuffers_h(IDXGISwapChain* _this, void* rdx, void* r8, void* r9, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	typedef decltype(ResizeBuffers_h)* ResizeBuffers_t;
	extern ResizeBuffers_t ResizeBuffers_o;

	class main_gui_c
	{
	public:

		bool initialized, show_window;

		std::string ini_file_name, log_file_name;

		ImFont* tahoma, *bank_gothic_pro_light, *eurostile_extended;
		std::float_t scaling_factor = 1.0f, tahoma_size = 13.0f, bank_gothic_pro_light_size = 14.0f, eurostile_extended_size = 18.0f;

		niggerware::utils::misc::timer_c chat_spam_timer, vote_spam_timer;

		struct text_buffers_s
		{
			char change_name[32] = { 0 };
			char change_clan[8] = { 0 };
			char kill_spam[1024] = { 0 };
			char chat_spam[1024] = { 0 };
			char vote_spam[1024] = { 0 };
			char join_by_steam_id[20] = { 0 };
			char crash_by_steam_id[20] = { 0 };
			char popup_by_steam_id[20] = { 0 };
			char cbuf_add_text[1024] = { 0 };
			char cl_add_reliable_command[1024] = { 0 };
			char sv_game_send_server_command[1024] = { 0 };
			char dvar_set_from_string_by_name[1024] = { 0 };
		} text_buffers;

		struct virtual_keys_s
		{
			bool key, down, up;
		} virtual_keys[max_virtual_keys];

		ID3D11Device* renderer_device;
		ID3D11DeviceContext* renderer_device_context;
		ID3D11RenderTargetView* render_target_view;
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;

		std::vector<IUnknown*> device_objects;
		std::mutex lock;

		void init();
		void free();

		void setup_imgui();

		void device_from_swap(IDXGISwapChain* pSwapChain);
		void device_context_from_swap(IDXGISwapChain* pSwapChain);
		void create_render_target_view(IDXGISwapChain* pSwapChain);
		void get_swap_chain_desc(IDXGISwapChain* pSwapChain);

		ImVec2 get_view_port();

		void release_objects();
		void invalidate();
		void update_colors();

		void draw_main_gui();
		void draw_toast_popups();
		void draw_color_picker(configs_c::cvar_s* cvar, bool alpha);

		void process_lobby();

		bool get_key_press(std::int32_t vkey, bool immediate);
		bool should_ignore_msg(UINT uMsg);
		bool window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

	extern main_gui_c main_gui;
}

//=====================================================================================
