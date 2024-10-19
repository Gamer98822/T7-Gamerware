//=====================================================================================

#pragma once

#include "../Engine/Engine.hpp"

//=====================================================================================

namespace t7
{
	constexpr auto invalid_specialist = 10;

	class stats_c
	{
	public:

		void unlock_secret_items();
		void unlock_loot_items();
		void spoof_all_black_market_items();
		void enable_invalid_specialist();

		void give_crypto_keys(std::int32_t amount);
		void give_liquid_divinium(std::int32_t amount);

		void spend_crypto_keys(structures::LootCrateType crate);
		void spend_liquid_divinium(std::int32_t count);

		void burn_duplicates(structures::eModes mode);
		void fix_pending_loot();

		void give_currency();
		void spend_currency();

		void handle_loot();

		std::uint32_t get_specialist();
		void set_specialist(std::uint32_t index);

		void enable_niggsploit();
		void handle_niggsploit();

		void draw_menu_tab();

	private:

		bool get_column_value_for_row_from_path(std::string path, std::int32_t row, std::int32_t column, std::int32_t* value);

		std::uint32_t ddl_get_for_path(structures::DDLState* state, structures::DDLContext* context, std::string path);
		void ddl_set_for_path(structures::DDLState* state, structures::DDLContext* context, std::string path, std::uint32_t value);

		std::uint32_t get_stat_from_path(structures::eModes mode, std::string path);
		void set_stat_from_path(structures::eModes mode, std::string path, std::uint32_t value);

		std::uint32_t get_stat_from_path(structures::StorageFileType file, std::string path);
		void set_stat_from_path(structures::StorageFileType file, std::string path, std::uint32_t value);
		bool invalid_specialist_set;

		void set_stats_from_file(std::string path);

		bool niggsploit_set;
		niggerware::utils::misc::timer_c give_currency_timer, spend_currency_timer, niggsploit_timer;
		std::uint32_t character_index;

		struct stats_list_s
		{
			std::int32_t stats_selection;
			std::vector<std::string> stats_files;

			auto set_stats_selection()
			{
				for (auto i{ 0u }; i < stats_files.size(); i++)
				{
					auto is_selected = (stats_selection == i);

					if (ImGui::Selectable(stats_files[i].c_str(), is_selected))
					{
						stats_selection = i;
					}
				}
			}

			auto get_stats_selection()
			{
				return stats_files[stats_selection];
			}
		} stats_list;

		std::map<std::string, structures::StorageFileType> stg_types =
		{
			{ "common_settings", structures::STORAGE_COMMON_SETTINGS },
			{ "profile_shoutcaster", structures::STORAGE_PROFILE_SHOUTCASTER },
			{ "savegame_online_cp", structures::STORAGE_CP_SAVEGAME_ONLINE },
			{ "savegame_offline_cp", structures::STORAGE_CP_SAVEGAME_OFFLINE },
			{ "savegame_online_nightmare", structures::STORAGE_CPNIGHTMARE_SAVEGAME_ONLINE },
			{ "savegame_offline_nightmare", structures::STORAGE_CPNIGHTMARE_SAVEGAME_OFFLINE },
			{ "stats_online_cp", structures::STORAGE_CP_STATS_ONLINE },
			{ "stats_offline_cp", structures::STORAGE_CP_STATS_OFFLINE },
			{ "stats_online_nightmare", structures::STORAGE_CP_STATS_NIGHTMARE_ONLINE },
			{ "stats_offline_nightmare", structures::STORAGE_CP_STATS_NIGHTMARE_OFFLINE },
			{ "loadouts_cp", structures::STORAGE_CP_LOADOUTS },
			{ "loadouts_offline_cp", structures::STORAGE_CP_LOADOUTS_OFFLINE },
			{ "stats_online_mp", structures::STORAGE_MP_STATS_ONLINE },
			{ "stats_offline_mp", structures::STORAGE_MP_STATS_OFFLINE },
			{ "loadouts_mp", structures::STORAGE_MP_LOADOUTS },
			{ "loadouts_custom_mp", structures::STORAGE_MP_LOADOUTS_CUSTOM },
			{ "loadouts_arena_mp", structures::STORAGE_MP_LOADOUTS_ARENA },
			{ "loadouts_offline_mp", structures::STORAGE_MP_LOADOUTS_OFFLINE },
			{ "class_sets_mp", structures::STORAGE_MP_CLASS_SETS },
			{ "stats_online_zm", structures::STORAGE_ZM_STATS_ONLINE },
			{ "stats_offline_zm", structures::STORAGE_ZM_STATS_OFFLINE },
			{ "loadouts_zm", structures::STORAGE_ZM_LOADOUTS },
			{ "loadouts_offline_zm", structures::STORAGE_ZM_LOADOUTS_OFFLINE },
			{ "stats_online_fr", structures::STORAGE_FR_STATS_ONLINE },
			{ "stats_offline_fr", structures::STORAGE_FR_STATS_OFFLINE },
			{ "paintshop_data", structures::STORAGE_PAINTSHOP_DATA },
			{ "gunsmith", structures::STORAGE_GUNSMITH },
			{ "paintjobs", structures::STORAGE_PAINTJOBS },
			{ "emblems", structures::STORAGE_EMBLEMS },
			{ "default_emblems", structures::STORAGE_DEFAULT_EMBLEMS },
			{ "emblems_loot", structures::STORAGE_EMBLEMS_LOOT },
			{ "custom_games", structures::STORAGE_CUSTOM_GAMES },
			{ "official_custom_games", structures::STORAGE_OFFICIAL_CUSTOM_GAMES },
			{ "external_data", structures::STORAGE_EXTERNAL_DATA }
		};

		auto get_storage_type(std::string file_type) { return stg_types[file_type]; }
	};

	extern stats_c stats;
}

//=====================================================================================
