//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	stats_c stats;

	void stats_c::unlock_secret_items()
	{
		for (auto i{ 0 }; i < 256; i++)
		{
			auto item_info = &structures::get_item_infos(functions::Com_SessionMode_GetMode())->itemInfo[i];

			item_info->flags = 4;
			item_info->requiredLevel = 1;
			item_info->requiredPrestige = 1;
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::unlock_loot_items()
	{
		functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->itemFlags = 4;

		for (auto i{ 0 }; i < functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->itemCount; i++)
		{
			if (auto loot_item{ functions::LiveInventory_GetPlayerInventoryItemId(structures::CONTROLLER_INDEX_FIRST, i) }; loot_item)
			{
				loot_item->quantity = 1;
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::spoof_all_black_market_items()
	{
		functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->itemCount = 2914;

		for (auto i{ 0 }; i < 2890; i++)
		{
			if (i > 2865)
			{
				auto item_id = 0;
				if (get_column_value_for_row_from_path("gamedata/tables/common/inventory_items.csv", i - 2865, 2, &item_id))
				{
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].itemId = item_id;
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].quantity = 1;
				}
			}

			else if (i > 2818)
			{
				auto item_id = 0;
				if (get_column_value_for_row_from_path("gamedata/loot/zmlootitems.csv", i - 2818, 1, &item_id))
				{
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].itemId = item_id;
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].quantity = 999;
				}
			}

			else
			{
				auto item_id = 0;
				if (get_column_value_for_row_from_path("gamedata/loot/mplootitems.csv", i, 1, &item_id))
				{
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].itemId = item_id;
					functions::LiveInventory_GetPlayerInventory(structures::CONTROLLER_INDEX_FIRST)->lootItem[i].quantity = 1;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::give_crypto_keys(std::int32_t amount)
	{
		functions::Loot_IncCurrency(structures::CONTROLLER_INDEX_FIRST, structures::INVENTORY_CURRENCY_MP_LOOT_XP, amount * 100);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::give_liquid_divinium(std::int32_t amount)
	{
		functions::Loot_IncCurrency(structures::CONTROLLER_INDEX_FIRST, structures::INVENTORY_CURRENCY_ZM_VIALS, amount);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::spend_crypto_keys(structures::LootCrateType crate)
	{
		functions::Loot_BuyCrate(structures::CONTROLLER_INDEX_FIRST, crate, structures::INVENTORY_CURRENCY_MP_CRYPTO_KEYS);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::spend_liquid_divinium(std::int32_t count)
	{
		functions::Loot_SpendVials(structures::CONTROLLER_INDEX_FIRST, count);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::burn_duplicates(structures::eModes mode)
	{
		functions::Loot_BurnDuplicates(structures::CONTROLLER_INDEX_FIRST, mode);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::fix_pending_loot()
	{
		set_stat_from_path(functions::Com_SessionMode_GetMode(), "mp_loot_xp_due", 0);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::give_currency()
	{
		if (give_currency_timer.expired())
		{
			if (configs.give_currency.current.integer == configs_c::give_currency_crypto_keys)
			{
				give_crypto_keys(40);
			}

			else if (configs.give_currency.current.integer == configs_c::give_currency_liquid_divinium)
			{
				give_liquid_divinium(250);
			}

			give_currency_timer.reset(100ms);
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::spend_currency()
	{
		if (spend_currency_timer.expired())
		{
			if (configs.spend_currency.current.integer == configs_c::spend_currency_crypto_keys)
			{
				spend_crypto_keys(structures::LOOT_CRATE_TYPE_RARE);
			}

			else if (configs.spend_currency.current.integer == configs_c::spend_currency_liquid_divinium)
			{
				spend_liquid_divinium(3);
			}

			if (configs.burn_duplicates.current.enabled)
			{
				burn_duplicates(functions::Com_SessionMode_GetMode());
			}

			spend_currency_timer.reset(100ms);
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::handle_loot()
	{
		give_currency();
		spend_currency();

		functions::Dvar_SetFromStringByName("loot_noDupeRare_active", "1", true);
		functions::Dvar_SetFromStringByName("loot_trifectaActive", "1", true);
		functions::Dvar_SetFromStringByName("loot_trifecta_cryptoCost", "500", true);
		functions::Dvar_SetFromStringByName("trifecta_cryptokeys_drop_id", "0", true);
		functions::Dvar_SetFromStringByName("fileshareAllowDownload", "1", true);
		functions::Dvar_SetFromStringByName("fileshareAllowDownloadingOthersFiles", "1", true);
		functions::Dvar_SetFromStringByName("fileshareAllowVariantDownload", "1", true);
		functions::Dvar_SetFromStringByName("fileshareAllowEmblemDownload", "1", true);
		functions::Dvar_SetFromStringByName("enable_camo_materials_tab", "1", true);
		functions::Dvar_SetFromStringByName("tu10_validationFatal", "1", true);
	}
	/*
	//=====================================================================================
	*/
	std::uint32_t stats_c::get_specialist()
	{
		return get_stat_from_path(get_storage_type("loadouts_mp"), "cacLoadouts.characterContext.characterIndex");
	}
	/*
	//=====================================================================================
	*/
	void stats_c::set_specialist(std::uint32_t index)
	{
		set_stat_from_path(get_storage_type("loadouts_mp"), "cacLoadouts.characterContext.characterIndex", index);
	}
	/*
	//=====================================================================================
	*/


	void stats_c::enable_invalid_specialist()
	{
		if (auto specialist{ get_specialist() }; specialist != invalid_specialist)
		{
			character_index = specialist;
			set_specialist(invalid_specialist);

			invalid_specialist_set = true;
		}
	}


	void stats_c::enable_niggsploit()
	{
		if (auto specialist{ get_specialist() }; specialist != invalid_specialist)
		{
			character_index = specialist;
			set_specialist(invalid_specialist);

			niggsploit_set = true;
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::handle_niggsploit()
	{
		if (niggsploit_timer.expired())
		{
			if (niggsploit_set && get_specialist() != invalid_specialist)
			{
				set_specialist(character_index);
			}

			niggsploit_timer.reset(1s);
		}
	}
	/*
	//=====================================================================================
	*/
	void stats_c::draw_menu_tab()
	{
		if (ImGui::BeginTabItem("Stats"))
		{
			stats_list.stats_files.clear();

			for (auto& file : std::filesystem::directory_iterator{ "." })
			{
				if (niggerware::utils::string::to_lower(file.path().extension().string()) == ".stats")
				{
					stats_list.stats_files.push_back(file.path().filename().string());
				}
			}

			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
			if (ImGui::ListBoxHeader("##configs", stats_list.stats_files.size(), 20))
			{
				stats_list.set_stats_selection();

				ImGui::ListBoxFooter();
			} ImGui::PopItemWidth();

			if (ImGui::Button("Load", { ImGui::GetContentRegionAvailWidth(), 0.0f }))
			{
				if (!stats_list.stats_files.empty())
				{
					set_stats_from_file(stats_list.get_stats_selection());
				}
			}

			ImGui::EndTabItem();
		}
	}
	/*
	//=====================================================================================
	*/
	bool stats_c::get_column_value_for_row_from_path(std::string path, std::int32_t row, std::int32_t column, std::int32_t* value_ptr)
	{
		structures::StringTable* string_table = nullptr;
		functions::StringTable_GetAsset(path.c_str(), &string_table);

		if (value_ptr && string_table)
		{
			auto search_result = functions::StringTable_GetColumnValueForRow(string_table, row, column);
			auto column_value = niggerware::utils::string::stoi(search_result);

			*value_ptr = column_value;
			return true;
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	std::uint32_t stats_c::ddl_get_for_path(structures::DDLState* state, structures::DDLContext* context, std::string path)
	{
		auto ddl_path = niggerware::utils::string::tokenize(path, '.');

		functions::DDL_MoveToPath(state, state, ddl_path.size(), niggerware::utils::string::vector_to_pointer_array(ddl_path));
		return functions::DDL_GetUInt(state, context);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::ddl_set_for_path(structures::DDLState* state, structures::DDLContext* context, std::string path, std::uint32_t value)
	{
		auto ddl_path = niggerware::utils::string::tokenize(path, '.');

		functions::DDL_MoveToPath(state, state, ddl_path.size(), niggerware::utils::string::vector_to_pointer_array(ddl_path));
		functions::DDL_SetUInt(state, context, value);
	}
	/*
	//=====================================================================================
	*/
	std::uint32_t stats_c::get_stat_from_path(structures::eModes mode, std::string path)
	{
		auto ddl_state = *functions::LiveStats_GetRootDDLState(mode);
		auto ddl_context = functions::LiveStorage_GetStatsBufferWithCaller(structures::CONTROLLER_INDEX_FIRST, nullptr, nullptr, 0, mode, structures::STATS_LOCATION_NORMAL);

		return ddl_get_for_path(&ddl_state, ddl_context, path);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::set_stat_from_path(structures::eModes mode, std::string path, std::uint32_t value)
	{
		auto ddl_state = *functions::LiveStats_GetRootDDLState(mode);
		auto ddl_context = functions::LiveStorage_GetStatsBufferWithCaller(structures::CONTROLLER_INDEX_FIRST, nullptr, nullptr, 0, mode, structures::STATS_LOCATION_NORMAL);

		ddl_set_for_path(&ddl_state, ddl_context, path, value);
	}
	/*
	//=====================================================================================
	*/
	std::uint32_t stats_c::get_stat_from_path(structures::StorageFileType file, std::string path)
	{
		auto ddl_state = *functions::Storage_GetDDLRootState(file);
		auto ddl_context = functions::Storage_GetDDLContext(structures::CONTROLLER_INDEX_FIRST, file, 0);

		return ddl_get_for_path(&ddl_state, ddl_context, path);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::set_stat_from_path(structures::StorageFileType file, std::string path, std::uint32_t value)
	{
		auto ddl_state = *functions::Storage_GetDDLRootState(file);
		auto ddl_context = functions::Storage_GetDDLContext(structures::CONTROLLER_INDEX_FIRST, file, 0);

		ddl_set_for_path(&ddl_state, ddl_context, path, value);
	}
	/*
	//=====================================================================================
	*/
	void stats_c::set_stats_from_file(std::string path)
	{
		if (auto j{ niggerware::utils::file::json_read(path) }; j.is_array())
		{
			for (auto& [key, value] : j.items())
			{
				if (value.is_object())
				{
					for (auto& [key, value] : value.items())
					{
						if (value.is_number())
						{
							auto stat_path = key;
							auto stat_value = 0u;

							if (niggerware::utils::file::json_get(value, {}, stat_value))
							{
								set_stat_from_path(functions::Com_SessionMode_GetMode(), stat_path, stat_value);
							}
						}
					}
				}
			}
		}
	}
}

//=====================================================================================