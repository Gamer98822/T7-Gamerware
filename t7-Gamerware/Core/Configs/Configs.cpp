//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	configs_c configs;

	configs_c::configs_c()
	{
		aimbot_mode = add_int("Mode", { "Off", "Manual", "Auto" }, aimbot_mode_off, aimbot_mode_off, aimbot_mode_max);

		auto_zoom = add_bool("Autozoom", false);
		auto_fire = add_bool("Autofire", false);
		auto_wall = add_bool("Autowall", false);
		silent_aim = add_bool("Silent-Aim", false);

		sort_algorithm_targets = add_int("Sort Algorithm Targets", { "Distance", "Damage", "Field of View" }, sort_algorithm_distance, sort_algorithm_distance, sort_algorithm_max);
		sort_algorithm_bones = add_int("Sort Algorithm Bones", { "Distance", "Damage", "Field of View" }, sort_algorithm_distance, sort_algorithm_distance, sort_algorithm_max);
		kill_sounds = add_int("Kill Sounds", { "Off", "Male", "Female" }, kill_sounds_off, kill_sounds_off, kill_sounds_max);
		hit_marker_sounds = add_bool("Hitmarker Sounds", false);
		multi_threading = add_bool("Multithreading", false);

		no_recoil = add_bool("No-Recoil", false);
		no_spread = add_bool("No-Spread", false);
		no_flinch = add_bool("No-Flinch", false);
		quick_reload = add_bool("Quick-Reload", false);

		anti_aim_pitch_default = add_int("Pitch Default", { "Off", "Zero", "Up", "Down", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_pitch_off, anti_aim_pitch_off, anti_aim_pitch_max);
		anti_aim_yaw_default = add_int("Yaw Default", { "Off", "Spin", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_yaw_off, anti_aim_yaw_off, anti_aim_yaw_max);
		anti_aim_pitch_on_sprint = add_int("Pitch On Sprint", { "Off", "Zero", "Up", "Down", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_pitch_off, anti_aim_pitch_off, anti_aim_pitch_max);
		anti_aim_yaw_on_sprint = add_int("Yaw On Sprint", { "Off", "Spin", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_yaw_off, anti_aim_yaw_off, anti_aim_yaw_max);
		anti_aim_pitch_on_target = add_int("Pitch On Target", { "Off", "Zero", "Up", "Down", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_pitch_off, anti_aim_pitch_off, anti_aim_pitch_max);
		anti_aim_yaw_on_target = add_int("Yaw On Target", { "Off", "Spin", "Jitter", "Random", "Reverse", "Custom" }, anti_aim_yaw_off, anti_aim_yaw_off, anti_aim_yaw_max);
		anti_aim_spin_speed = add_float("Spin Speed", 0.0f, -90.0f, 90.0f);
		anti_aim_shield_pitch_shift = add_float("Shield Pitch Shift", 0.0f, -70.0f, 70.0f);
		anti_aim_shield_yaw_shift = add_float("Shield Yaw Shift", 0.0f, -180.0f, 180.0f);
		anti_aim_custom_pitch = add_float("Custom Pitch", 0.0f, -70.0f, 70.0f);
		anti_aim_custom_yaw = add_float("Custom Yaw", 0.0f, -180.0f, 180.0f);

		target_actors = add_bool("Target Actors", false);
		target_vehicles = add_bool("Target Vehicles", false);
		target_helicopters = add_bool("Target Helicopters", false);

		bones_inclusion = add_int("Inclusion", { "Off", "Priorities Only", "Everyone" }, bone_scan_off, bone_scan_off, bone_scan_max);
		bones_selection = add_int("Selection", {}, 0);

		esp_mode = add_int("Mode", { "Off", "Axis", "Allies", "Full" }, esp_mode_off, esp_mode_off, esp_mode_max);

		esp_boxes = add_int("Boxes", { "Off", "Border", "Corner", "Border Filled", "Corner Filled", "Border 3D", "Corner 3D" }, esp_boxes_off, esp_boxes_off, esp_boxes_max);
		esp_bones = add_int("Bones", { "Off", "Dots", "Lines" }, esp_bones_off, esp_bones_off, esp_bones_max);
		esp_snap_lines = add_int("Snaplines", { "Off", "Top", "Center", "Bottom", "Alternating 1", "Alternating 2" }, esp_snap_lines_off, esp_snap_lines_off, esp_snap_lines_max);
		esp_entities = add_int("Entities", { "Off", "Info", "Border 3D", "Corner 3D" }, esp_entities_off, esp_entities_off, esp_entities_max);
		esp_distances = add_bool("Distances", false);
		esp_names = add_bool("Names", false);
		esp_weapons = add_bool("Weapons", false);
		esp_health_bars = add_bool("Health Bars", false);
		esp_aim_pos = add_bool("Aim Pos", false);
		esp_cross_hair = add_bool("Crosshair", false);
		esp_bullet_tracers = add_bool("Bullet Tracers", false);
		esp_threat_warning = add_bool("Threat Warning", false);
		esp_compass = add_bool("Compass", false);
		esp_radar = add_bool("Radar", false);

		color_axis_visible = add_color("Axis Visible:", { 0.0f, 1.0f, 0.5f, 1.0f });
		rgb_colors.push_back({ &color_axis_visible, {} });
		color_axis_visible_text = add_color("Axis Visible Text:", { 0.0f, 1.0f, 0.5f, 1.0f });
		rgb_colors.push_back({ &color_axis_visible_text, {} });
		color_axis_visible_outline = add_color("Axis Visible Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_axis_visible_outline, {} });
		color_axis_occluded = add_color("Axis Occluded:", { 0.0f, 1.0f, 0.5f, 1.0f });
		rgb_colors.push_back({ &color_axis_occluded, {} });
		color_axis_occluded_text = add_color("Axis Occluded Text:", { 0.0f, 1.0f, 0.5f, 1.0f });
		rgb_colors.push_back({ &color_axis_occluded_text, {} });
		color_axis_occluded_outline = add_color("Axis Occluded Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_axis_occluded_outline, {} });
		color_allies_visible = add_color("Allies Visible:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_visible, {} });
		color_allies_visible_text = add_color("Allies Visible Text:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_visible_text, {} });
		color_allies_visible_outline = add_color("Allies Visible Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_visible_outline, {} });
		color_allies_occluded = add_color("Allies Occluded:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_occluded, {} });
		color_allies_occluded_text = add_color("Allies Occluded Text:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_occluded_text, {} });
		color_allies_occluded_outline = add_color("Allies Occluded Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_allies_occluded_outline, {} });
		color_entities = add_color("Entities:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_entities, {} });
		color_entities_text = add_color("Entities Text:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_entities_text, {} });
		color_entities_outline = add_color("Entities Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_entities_outline, {} });
		color_aimbot_target = add_color("Aimbot Target:", { 1.0f, 0.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_aimbot_target, {} });
		color_aimbot_target_text = add_color("Aimbot Target Text:", { 1.0f, 0.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_aimbot_target_text, {} });
		color_aimbot_target_outline = add_color("Aimbot Target Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_aimbot_target_outline, {} });
		color_anti_aim_target = add_color("Anti-Aim Target:", { 1.0f, 1.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_anti_aim_target, {} });
		color_anti_aim_target_text = add_color("Anti-Aim Target Text:", { 1.0f, 1.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_anti_aim_target_text, {} });
		color_anti_aim_target_outline = add_color("Anti-Aim Target Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_anti_aim_target_outline, {} });
		color_prioritized = add_color("Prioritized:", { 1.0f, 1.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_prioritized, {} });
		color_prioritized_text = add_color("Prioritized Text:", { 1.0f, 1.0f, 0.25f, 1.0f });
		rgb_colors.push_back({ &color_prioritized_text, {} });
		color_prioritized_outline = add_color("Prioritized Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_prioritized_outline, {} });
		color_aim_pos = add_color("Aim Pos:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_aim_pos, {} });
		color_aim_pos_outline = add_color("Aim Pos Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_aim_pos_outline, {} });
		color_cross_hair = add_color("Crosshair:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_cross_hair, {} });
		color_tracer_line = add_color("Tracer Line:", { 1.0f, 0.0f, 0.0f, 1.0f }, 1000.0f);
		rgb_colors.push_back({ &color_tracer_line, {} });
		color_tracer_hit = add_color("Tracer Hit:", { 1.0f, 1.0f, 1.0f, 1.0f });
		rgb_colors.push_back({ &color_tracer_hit, {} });
		color_tracer_hit_outline = add_color("Tracer Hit Outline:", { 0.0f, 0.0f, 0.0f, 1.0f });
		rgb_colors.push_back({ &color_tracer_hit_outline, {} });
		color_threat_warning = add_color("Threat Warning:", { 1.0f, 1.0f, 1.0f, 0.125f });
		rgb_colors.push_back({ &color_threat_warning, {} });

		third_person = add_bool("Third Person", false);
		full_auto_all_weapons = add_bool("Full-Auto All Weapons", false);
		perma_hatr = add_bool("Perma H.A.T.R.", false);

		aim_bone = add_int("Aimbone", [&]() { std::vector<std::string> v; for (auto& [key, value] : structures::bone_names) v.push_back(value.first); return v; } (), structures::bone_helmet, structures::bone_helmet, structures::bone_max);
		aim_angle = add_float("Aimangle", 180.0f, 1.0f, 180.0f);
		aim_power = add_float("Aimpower", 100.0f, 1.0f, 100.0f);
		min_damage = add_float("Min Damage", 0.0f, 0.0f, 100.0f);
		fire_rate_limiter = add_float("Firerate Limiter", 0.0f, 0.0f, 1000.0f);
		auto_aim_time = add_float("Autoaim Time", 0.0f, 0.0f, 1000.0f);
		auto_aim_delay = add_float("Autoaim Delay", 0.0f, 0.0f, 1000.0f);
		auto_zoom_delay = add_float("Autozoom Delay", 0.0f, 0.0f, 1000.0f);
		auto_fire_delay = add_float("Autofire Delay", 0.0f, 0.0f, 1000.0f);
		fake_lag = add_float("Fake Lag", 0.0f, 0.0f, 1000.0f);
		third_person_hotkey = add_int("Third Person Hotkey", {}, 0);
		air_stuck_hotkey = add_int("Airstuck Hotkey", {}, 0);

		change_name = add_string("Change Name:", "");
		change_clan = add_string("Change Clan:", "");

		give_currency = add_int("Give Currency", { "Off", "Crypto Keys", "Liquid Divinium" }, give_currency_off, give_currency_off, give_currency_max);
		spend_currency = add_int("Spend Currency", { "Off", "Crypto Keys", "Liquid Divinium" }, spend_currency_off, spend_currency_off, spend_currency_max);
		burn_duplicates = add_bool("Burn Duplicates", false);
		spoof_all_dlc_items = add_bool("Spoof All DLC Items", false);
		spoof_xuid = add_bool("Spoof Xuid", false);
		kill_spam = add_string("Killspam:", "");
		chat_spam = add_string("Chatspam:", "");
		vote_spam = add_string("Votespam:", "");
		join_by_steam_id = add_string("Join By Steam ID:", "");
		crash_by_steam_id = add_string("Crash By Steam ID:", "");
		popup_by_steam_id = add_string("Popup By Steam ID:", "");

		cbuf_add_text = add_string("Cbuf_AddText:", "");
		cl_add_reliable_command = add_string("CL_AddReliableCommand:", "");
		sv_game_send_server_command = add_string("SV_GameSendServerCommand:", "");
		dvar_set_from_string_by_name = add_string("Dvar_SetFromStringByName:", "");

		hide_p2p = add_bool("Hide P2P", false);
		hide_dedi = add_bool("Hide Dedi", false);
		hide_empty = add_bool("Hide Empty", false);
		hide_full = add_bool("Hide Full", false);
	}
	/*
	//=====================================================================================
	*/
	bool configs_c::save(const std::string& name)
	{
		if (name.empty())
		{
			return false;
		}

		niggerware::utils::file::json j;

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "GlobalSettings", "Mode" }, aimbot_mode.current.integer);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BasicSettings", "Autozoom" }, auto_zoom.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BasicSettings", "Autofire" }, auto_fire.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BasicSettings", "Autowall" }, auto_wall.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BasicSettings", "SilentAim" }, silent_aim.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AdvancedSettings", "SortAlgorithmTargets" }, sort_algorithm_targets.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AdvancedSettings", "SortAlgorithmBones" }, sort_algorithm_bones.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AdvancedSettings", "KillSounds" }, kill_sounds.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AdvancedSettings", "HitmarkerSounds" }, hit_marker_sounds.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AdvancedSettings", "Multithreading" }, multi_threading.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "Removals", "NoRecoil" }, no_recoil.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "Removals", "NoSpread" }, no_spread.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "Removals", "NoFlinch" }, no_flinch.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "Removals", "QuickReload" }, quick_reload.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "PitchDefault" }, anti_aim_pitch_default.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "YawDefault" }, anti_aim_yaw_default.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "PitchOnSprint" }, anti_aim_pitch_on_sprint.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "YawOnSprint" }, anti_aim_yaw_on_sprint.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "PitchOnTarget" }, anti_aim_pitch_on_target.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "YawOnTarget" }, anti_aim_yaw_on_target.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "SpinSpeed" }, anti_aim_spin_speed.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "ShieldPitchShift" }, anti_aim_shield_pitch_shift.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "ShieldYawShift" }, anti_aim_shield_yaw_shift.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "CustomPitch" }, anti_aim_custom_pitch.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "AntiAim", "CustomYaw" }, anti_aim_custom_yaw.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "TargetSelection", "TargetActors" }, target_actors.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "TargetSelection", "TargetVehicles" }, target_vehicles.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "TargetSelection", "TargetHelicopters" }, target_helicopters.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BoneSelection", "Inclusion" }, bones_inclusion.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Aimbot", "BoneSelection", "Selection" }, bones_selection.current.integer);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "GlobalSettings", "Mode" }, esp_mode.current.integer);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Boxes" }, esp_boxes.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Bones" }, esp_bones.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Snaplines" }, esp_snap_lines.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Entities" }, esp_entities.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Distances" }, esp_distances.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Names" }, esp_names.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Weapons" }, esp_weapons.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "HealthBars" }, esp_health_bars.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "AimPos" }, esp_aim_pos.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "Crosshair" }, esp_cross_hair.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "BulletTracers" }, esp_bullet_tracers.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "WorldSpace", "ThreatWarning" }, esp_threat_warning.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "ScreenSpace", "Compass" }, esp_compass.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "ScreenSpace", "Radar" }, esp_radar.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisible", "Red" }, color_axis_visible.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisible", "Green" }, color_axis_visible.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisible", "Blue" }, color_axis_visible.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisible", "Alpha" }, color_axis_visible.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisible", "Speed" }, color_axis_visible.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Red" }, color_axis_visible_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Green" }, color_axis_visible_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Blue" }, color_axis_visible_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Alpha" }, color_axis_visible_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Speed" }, color_axis_visible_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Red" }, color_axis_visible_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Green" }, color_axis_visible_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Blue" }, color_axis_visible_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Alpha" }, color_axis_visible_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Speed" }, color_axis_visible_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccluded", "Red" }, color_axis_occluded.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccluded", "Green" }, color_axis_occluded.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccluded", "Blue" }, color_axis_occluded.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccluded", "Alpha" }, color_axis_occluded.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccluded", "Speed" }, color_axis_occluded.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Red" }, color_axis_occluded_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Green" }, color_axis_occluded_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Blue" }, color_axis_occluded_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Alpha" }, color_axis_occluded_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Speed" }, color_axis_occluded_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Red" }, color_axis_occluded_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Green" }, color_axis_occluded_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Blue" }, color_axis_occluded_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Alpha" }, color_axis_occluded_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Speed" }, color_axis_occluded_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisible", "Red" }, color_allies_visible.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisible", "Green" }, color_allies_visible.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisible", "Blue" }, color_allies_visible.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisible", "Alpha" }, color_allies_visible.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisible", "Speed" }, color_allies_visible.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Red" }, color_allies_visible_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Green" }, color_allies_visible_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Blue" }, color_allies_visible_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Alpha" }, color_allies_visible_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Speed" }, color_allies_visible_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Red" }, color_allies_visible_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Green" }, color_allies_visible_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Blue" }, color_allies_visible_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Alpha" }, color_allies_visible_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Speed" }, color_allies_visible_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Red" }, color_allies_occluded.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Green" }, color_allies_occluded.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Blue" }, color_allies_occluded.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Alpha" }, color_allies_occluded.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Speed" }, color_allies_occluded.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Red" }, color_allies_occluded_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Green" }, color_allies_occluded_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Blue" }, color_allies_occluded_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Alpha" }, color_allies_occluded_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Speed" }, color_allies_occluded_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Red" }, color_allies_occluded_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Green" }, color_allies_occluded_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Blue" }, color_allies_occluded_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Alpha" }, color_allies_occluded_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Speed" }, color_allies_occluded_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Entities", "Red" }, color_entities.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Entities", "Green" }, color_entities.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Entities", "Blue" }, color_entities.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Entities", "Alpha" }, color_entities.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Entities", "Speed" }, color_entities.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesText", "Red" }, color_entities_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesText", "Green" }, color_entities_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesText", "Blue" }, color_entities_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesText", "Alpha" }, color_entities_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesText", "Speed" }, color_entities_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Red" }, color_entities_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Green" }, color_entities_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Blue" }, color_entities_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Alpha" }, color_entities_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Speed" }, color_entities_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTarget", "Red" }, color_aimbot_target.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTarget", "Green" }, color_aimbot_target.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTarget", "Blue" }, color_aimbot_target.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTarget", "Alpha" }, color_aimbot_target.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTarget", "Speed" }, color_aimbot_target.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Red" }, color_aimbot_target_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Green" }, color_aimbot_target_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Blue" }, color_aimbot_target_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Alpha" }, color_aimbot_target_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Speed" }, color_aimbot_target_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Red" }, color_aimbot_target_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Green" }, color_aimbot_target_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Blue" }, color_aimbot_target_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Alpha" }, color_aimbot_target_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Speed" }, color_aimbot_target_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Red" }, color_anti_aim_target.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Green" }, color_anti_aim_target.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Blue" }, color_anti_aim_target.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Alpha" }, color_anti_aim_target.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Speed" }, color_anti_aim_target.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Red" }, color_anti_aim_target_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Green" }, color_anti_aim_target_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Blue" }, color_anti_aim_target_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Alpha" }, color_anti_aim_target_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Speed" }, color_anti_aim_target_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Red" }, color_anti_aim_target_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Green" }, color_anti_aim_target_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Blue" }, color_anti_aim_target_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Alpha" }, color_anti_aim_target_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Speed" }, color_anti_aim_target_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Prioritized", "Red" }, color_prioritized.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Prioritized", "Green" }, color_prioritized.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Prioritized", "Blue" }, color_prioritized.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Prioritized", "Alpha" }, color_prioritized.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Prioritized", "Speed" }, color_prioritized.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedText", "Red" }, color_prioritized_text.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedText", "Green" }, color_prioritized_text.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedText", "Blue" }, color_prioritized_text.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedText", "Alpha" }, color_prioritized_text.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedText", "Speed" }, color_prioritized_text.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Red" }, color_prioritized_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Green" }, color_prioritized_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Blue" }, color_prioritized_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Alpha" }, color_prioritized_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Speed" }, color_prioritized_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPos", "Red" }, color_aim_pos.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPos", "Green" }, color_aim_pos.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPos", "Blue" }, color_aim_pos.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPos", "Alpha" }, color_aim_pos.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPos", "Speed" }, color_aim_pos.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPosOutline", "Red" }, color_aim_pos_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPosOutline", "Green" }, color_aim_pos_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPosOutline", "Blue" }, color_aim_pos_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPosOutline", "Alpha" }, color_aim_pos_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "AimPosOutline", "Speed" }, color_aim_pos_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Crosshair", "Red" }, color_cross_hair.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Crosshair", "Green" }, color_cross_hair.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Crosshair", "Blue" }, color_cross_hair.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Crosshair", "Alpha" }, color_cross_hair.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "Crosshair", "Speed" }, color_cross_hair.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerLine", "Red" }, color_tracer_line.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerLine", "Green" }, color_tracer_line.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerLine", "Blue" }, color_tracer_line.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerLine", "Alpha" }, color_tracer_line.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerLine", "Speed" }, color_tracer_line.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHit", "Red" }, color_tracer_hit.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHit", "Green" }, color_tracer_hit.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHit", "Blue" }, color_tracer_hit.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHit", "Alpha" }, color_tracer_hit.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHit", "Speed" }, color_tracer_hit.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Red" }, color_tracer_hit_outline.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Green" }, color_tracer_hit_outline.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Blue" }, color_tracer_hit_outline.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Alpha" }, color_tracer_hit_outline.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Speed" }, color_tracer_hit_outline.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "ThreatWarning", "Red" }, color_threat_warning.current.color.x);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "ThreatWarning", "Green" }, color_threat_warning.current.color.y);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "ThreatWarning", "Blue" }, color_threat_warning.current.color.z);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "ThreatWarning", "Alpha" }, color_threat_warning.current.color.w);
		niggerware::utils::file::json_set(j, { "T7", "Esp", "Colors", "ThreatWarning", "Speed" }, color_threat_warning.current.value);

		niggerware::utils::file::json_set(j, { "T7", "Misc", "Enhancements", "ThirdPerson" }, third_person.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "Enhancements", "FullAutoAllWeapons" }, full_auto_all_weapons.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "Enhancements", "PermaHatr" }, perma_hatr.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "Aimbone" }, aim_bone.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "Aimangle" }, aim_angle.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "Aimpower" }, aim_power.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "MinDamage" }, min_damage.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "FirerateLimiter" }, fire_rate_limiter.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "AutoaimTime" }, auto_aim_time.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "AutoaimDelay" }, auto_aim_delay.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "AutozoomDelay" }, auto_zoom_delay.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "AutofireDelay" }, auto_fire_delay.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "FakeLag" }, fake_lag.current.value);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "ThirdPersonHotkey" }, third_person_hotkey.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "AimbotTweaks", "AirstuckHotkey" }, air_stuck_hotkey.current.integer);

		niggerware::utils::file::json_set(j, { "T7", "Misc", "Functions", "ChangeName" }, change_name.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Misc", "FUnctions", "ChangeClan" }, change_clan.current.string);

		niggerware::utils::file::json_set(j, { "T7", "Tools", "Loot", "GiveCurrency" }, give_currency.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "Loot", "SpendCurrency" }, spend_currency.current.integer);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "Loot", "BurnDuplicates" }, burn_duplicates.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "Loot", "SpoofAllDlcItems" }, spoof_all_dlc_items.current.enabled);

		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "Killspam" }, kill_spam.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "Chatspam" }, chat_spam.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "Votespam" }, vote_spam.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "JoinBySteamId" }, join_by_steam_id.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "CrashBySteamId" }, crash_by_steam_id.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "TrollToolkit", "PopupBySteamId" }, popup_by_steam_id.current.string);

		niggerware::utils::file::json_set(j, { "T7", "Tools", "CommandInput", "Cbuf_AddText" }, cbuf_add_text.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "CommandInput", "CL_AddReliableCommand" }, cl_add_reliable_command.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "CommandInput", "SV_GameSendServerCommand" }, sv_game_send_server_command.current.string);
		niggerware::utils::file::json_set(j, { "T7", "Tools", "CommandInput", "Dvar_SetFromStringByName" }, dvar_set_from_string_by_name.current.string);

		niggerware::utils::file::json_set(j, { "T7", "Sessions", "HideP2P" }, hide_p2p.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Sessions", "HideDedi" }, hide_dedi.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Sessions", "HideEmpty" }, hide_empty.current.enabled);
		niggerware::utils::file::json_set(j, { "T7", "Sessions", "HideFull" }, hide_full.current.enabled);

		niggerware::utils::file::json_write(name, j);

		return true;
	}
	/*
	//=====================================================================================
	*/
	bool configs_c::load(const std::string& name)
	{
		if (name.empty())
		{
			return false;
		}

		auto j = niggerware::utils::file::json_read(name);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "GlobalSettings", "Mode" }, aimbot_mode.current.integer);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BasicSettings", "Autozoom" }, auto_zoom.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BasicSettings", "Autofire" }, auto_fire.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BasicSettings", "Autowall" }, auto_wall.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BasicSettings", "SilentAim" }, silent_aim.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AdvancedSettings", "SortAlgorithmTargets" }, sort_algorithm_targets.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AdvancedSettings", "SortAlgorithmBones" }, sort_algorithm_bones.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AdvancedSettings", "KillSounds" }, kill_sounds.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AdvancedSettings", "HitmarkerSounds" }, hit_marker_sounds.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AdvancedSettings", "Multithreading" }, multi_threading.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "Removals", "NoRecoil" }, no_recoil.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "Removals", "NoSpread" }, no_spread.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "Removals", "NoFlinch" }, no_flinch.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "Removals", "QuickReload" }, quick_reload.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "PitchDefault" }, anti_aim_pitch_default.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "YawDefault" }, anti_aim_yaw_default.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "PitchOnSprint" }, anti_aim_pitch_on_sprint.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "YawOnSprint" }, anti_aim_yaw_on_sprint.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "PitchOnTarget" }, anti_aim_pitch_on_target.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "YawOnTarget" }, anti_aim_yaw_on_target.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "SpinSpeed" }, anti_aim_spin_speed.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "ShieldPitchShift" }, anti_aim_shield_pitch_shift.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "ShieldYawShift" }, anti_aim_shield_yaw_shift.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "CustomPitch" }, anti_aim_custom_pitch.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "AntiAim", "CustomYaw" }, anti_aim_custom_yaw.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "TargetSelection", "TargetActors" }, target_actors.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "TargetSelection", "TargetVehicles" }, target_vehicles.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "TargetSelection", "TargetHelicopters" }, target_helicopters.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BoneSelection", "Inclusion" }, bones_inclusion.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Aimbot", "BoneSelection", "Selection" }, bones_selection.current.integer);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "GlobalSettings", "Mode" }, esp_mode.current.integer);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Boxes" }, esp_boxes.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Bones" }, esp_bones.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Snaplines" }, esp_snap_lines.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Entities" }, esp_entities.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Distances" }, esp_distances.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Names" }, esp_names.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Weapons" }, esp_weapons.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "HealthBars" }, esp_health_bars.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "AimPos" }, esp_aim_pos.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "Crosshair" }, esp_cross_hair.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "BulletTracers" }, esp_bullet_tracers.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "WorldSpace", "ThreatWarning" }, esp_threat_warning.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "ScreenSpace", "Compass" }, esp_compass.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "ScreenSpace", "Radar" }, esp_radar.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisible", "Red" }, color_axis_visible.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisible", "Green" }, color_axis_visible.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisible", "Blue" }, color_axis_visible.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisible", "Alpha" }, color_axis_visible.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisible", "Speed" }, color_axis_visible.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Red" }, color_axis_visible_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Green" }, color_axis_visible_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Blue" }, color_axis_visible_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Alpha" }, color_axis_visible_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleText", "Speed" }, color_axis_visible_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Red" }, color_axis_visible_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Green" }, color_axis_visible_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Blue" }, color_axis_visible_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Alpha" }, color_axis_visible_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisVisibleOutline", "Speed" }, color_axis_visible_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccluded", "Red" }, color_axis_occluded.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccluded", "Green" }, color_axis_occluded.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccluded", "Blue" }, color_axis_occluded.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccluded", "Alpha" }, color_axis_occluded.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccluded", "Speed" }, color_axis_occluded.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Red" }, color_axis_occluded_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Green" }, color_axis_occluded_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Blue" }, color_axis_occluded_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Alpha" }, color_axis_occluded_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedText", "Speed" }, color_axis_occluded_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Red" }, color_axis_occluded_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Green" }, color_axis_occluded_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Blue" }, color_axis_occluded_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Alpha" }, color_axis_occluded_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AxisOccludedOutline", "Speed" }, color_axis_occluded_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisible", "Red" }, color_allies_visible.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisible", "Green" }, color_allies_visible.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisible", "Blue" }, color_allies_visible.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisible", "Alpha" }, color_allies_visible.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisible", "Speed" }, color_allies_visible.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Red" }, color_allies_visible_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Green" }, color_allies_visible_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Blue" }, color_allies_visible_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Alpha" }, color_allies_visible_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleText", "Speed" }, color_allies_visible_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Red" }, color_allies_visible_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Green" }, color_allies_visible_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Blue" }, color_allies_visible_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Alpha" }, color_allies_visible_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesVisibleOutline", "Speed" }, color_allies_visible_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Red" }, color_allies_occluded.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Green" }, color_allies_occluded.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Blue" }, color_allies_occluded.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Alpha" }, color_allies_occluded.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccluded", "Speed" }, color_allies_occluded.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Red" }, color_allies_occluded_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Green" }, color_allies_occluded_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Blue" }, color_allies_occluded_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Alpha" }, color_allies_occluded_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedText", "Speed" }, color_allies_occluded_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Red" }, color_allies_occluded_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Green" }, color_allies_occluded_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Blue" }, color_allies_occluded_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Alpha" }, color_allies_occluded_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AlliesOccludedOutline", "Speed" }, color_allies_occluded_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Entities", "Red" }, color_entities.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Entities", "Green" }, color_entities.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Entities", "Blue" }, color_entities.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Entities", "Alpha" }, color_entities.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Entities", "Speed" }, color_entities.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesText", "Red" }, color_entities_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesText", "Green" }, color_entities_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesText", "Blue" }, color_entities_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesText", "Alpha" }, color_entities_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesText", "Speed" }, color_entities_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Red" }, color_entities_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Green" }, color_entities_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Blue" }, color_entities_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Alpha" }, color_entities_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "EntitiesOutline", "Speed" }, color_entities_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTarget", "Red" }, color_aimbot_target.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTarget", "Green" }, color_aimbot_target.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTarget", "Blue" }, color_aimbot_target.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTarget", "Alpha" }, color_aimbot_target.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTarget", "Speed" }, color_aimbot_target.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Red" }, color_aimbot_target_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Green" }, color_aimbot_target_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Blue" }, color_aimbot_target_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Alpha" }, color_aimbot_target_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetText", "Speed" }, color_aimbot_target_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Red" }, color_aimbot_target_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Green" }, color_aimbot_target_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Blue" }, color_aimbot_target_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Alpha" }, color_aimbot_target_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimbotTargetOutline", "Speed" }, color_aimbot_target_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Red" }, color_anti_aim_target.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Green" }, color_anti_aim_target.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Blue" }, color_anti_aim_target.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Alpha" }, color_anti_aim_target.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTarget", "Speed" }, color_anti_aim_target.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Red" }, color_anti_aim_target_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Green" }, color_anti_aim_target_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Blue" }, color_anti_aim_target_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Alpha" }, color_anti_aim_target_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetText", "Speed" }, color_anti_aim_target_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Red" }, color_anti_aim_target_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Green" }, color_anti_aim_target_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Blue" }, color_anti_aim_target_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Alpha" }, color_anti_aim_target_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AntiAimTargetOutline", "Speed" }, color_anti_aim_target_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Prioritized", "Red" }, color_prioritized.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Prioritized", "Green" }, color_prioritized.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Prioritized", "Blue" }, color_prioritized.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Prioritized", "Alpha" }, color_prioritized.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Prioritized", "Speed" }, color_prioritized.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedText", "Red" }, color_prioritized_text.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedText", "Green" }, color_prioritized_text.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedText", "Blue" }, color_prioritized_text.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedText", "Alpha" }, color_prioritized_text.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedText", "Speed" }, color_prioritized_text.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Red" }, color_prioritized_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Green" }, color_prioritized_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Blue" }, color_prioritized_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Alpha" }, color_prioritized_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "PrioritizedOutline", "Speed" }, color_prioritized_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPos", "Red" }, color_aim_pos.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPos", "Green" }, color_aim_pos.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPos", "Blue" }, color_aim_pos.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPos", "Alpha" }, color_aim_pos.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPos", "Speed" }, color_aim_pos.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPosOutline", "Red" }, color_aim_pos_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPosOutline", "Green" }, color_aim_pos_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPosOutline", "Blue" }, color_aim_pos_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPosOutline", "Alpha" }, color_aim_pos_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "AimPosOutline", "Speed" }, color_aim_pos_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Crosshair", "Red" }, color_cross_hair.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Crosshair", "Green" }, color_cross_hair.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Crosshair", "Blue" }, color_cross_hair.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Crosshair", "Alpha" }, color_cross_hair.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "Crosshair", "Speed" }, color_cross_hair.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerLine", "Red" }, color_tracer_line.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerLine", "Green" }, color_tracer_line.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerLine", "Blue" }, color_tracer_line.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerLine", "Alpha" }, color_tracer_line.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerLine", "Speed" }, color_tracer_line.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHit", "Red" }, color_tracer_hit.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHit", "Green" }, color_tracer_hit.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHit", "Blue" }, color_tracer_hit.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHit", "Alpha" }, color_tracer_hit.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHit", "Speed" }, color_tracer_hit.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Red" }, color_tracer_hit_outline.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Green" }, color_tracer_hit_outline.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Blue" }, color_tracer_hit_outline.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Alpha" }, color_tracer_hit_outline.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "TracerHitOutline", "Speed" }, color_tracer_hit_outline.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "ThreatWarning", "Red" }, color_threat_warning.current.color.x);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "ThreatWarning", "Green" }, color_threat_warning.current.color.y);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "ThreatWarning", "Blue" }, color_threat_warning.current.color.z);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "ThreatWarning", "Alpha" }, color_threat_warning.current.color.w);
		niggerware::utils::file::json_get(j, { "T7", "Esp", "Colors", "ThreatWarning", "Speed" }, color_threat_warning.current.value);

		niggerware::utils::file::json_get(j, { "T7", "Misc", "Enhancements", "ThirdPerson" }, third_person.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "Enhancements", "FullAutoAllWeapons" }, full_auto_all_weapons.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "Enhancements", "PermaHatr" }, perma_hatr.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "Aimbone" }, aim_bone.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "Aimangle" }, aim_angle.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "Aimpower" }, aim_power.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "MinDamage" }, min_damage.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "FirerateLimiter" }, fire_rate_limiter.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "AutoaimTime" }, auto_aim_time.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "AutoaimDelay" }, auto_aim_delay.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "AutozoomDelay" }, auto_zoom_delay.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "AutofireDelay" }, auto_fire_delay.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "FakeLag" }, fake_lag.current.value);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "ThirdPersonHotkey" }, third_person_hotkey.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "AimbotTweaks", "AirstuckHotkey" }, air_stuck_hotkey.current.integer);

		niggerware::utils::file::json_get(j, { "T7", "Misc", "Functions", "ChangeName" }, change_name.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Misc", "FUnctions", "ChangeClan" }, change_clan.current.string);

		niggerware::utils::file::json_get(j, { "T7", "Tools", "Loot", "GiveCurrency" }, give_currency.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "Loot", "SpendCurrency" }, spend_currency.current.integer);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "Loot", "BurnDuplicates" }, burn_duplicates.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "Loot", "SpoofAllDlcItems" }, spoof_all_dlc_items.current.enabled);

		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "Killspam" }, kill_spam.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "Chatspam" }, chat_spam.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "Votespam" }, vote_spam.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "JoinBySteamId" }, join_by_steam_id.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "CrashBySteamId" }, crash_by_steam_id.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "TrollToolkit", "PopupBySteamId" }, popup_by_steam_id.current.string);

		niggerware::utils::file::json_get(j, { "T7", "Tools", "CommandInput", "Cbuf_AddText" }, cbuf_add_text.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "CommandInput", "CL_AddReliableCommand" }, cl_add_reliable_command.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "CommandInput", "SV_GameSendServerCommand" }, sv_game_send_server_command.current.string);
		niggerware::utils::file::json_get(j, { "T7", "Tools", "CommandInput", "Dvar_SetFromStringByName" }, dvar_set_from_string_by_name.current.string);

		niggerware::utils::file::json_get(j, { "T7", "Sessions", "HideP2P" }, hide_p2p.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Sessions", "HideDedi" }, hide_dedi.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Sessions", "HideEmpty" }, hide_empty.current.enabled);
		niggerware::utils::file::json_get(j, { "T7", "Sessions", "HideFull" }, hide_full.current.enabled);

		niggerware::utils::string::copy(main_gui.text_buffers.change_name, change_name.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.change_clan, change_clan.current.string);

		niggerware::utils::string::copy(main_gui.text_buffers.kill_spam, kill_spam.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.chat_spam, chat_spam.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.vote_spam, vote_spam.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.join_by_steam_id, join_by_steam_id.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.crash_by_steam_id, crash_by_steam_id.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.popup_by_steam_id, popup_by_steam_id.current.string);

		niggerware::utils::string::copy(main_gui.text_buffers.cbuf_add_text, cbuf_add_text.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.cl_add_reliable_command, cl_add_reliable_command.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.sv_game_send_server_command, sv_game_send_server_command.current.string);
		niggerware::utils::string::copy(main_gui.text_buffers.dvar_set_from_string_by_name, dvar_set_from_string_by_name.current.string);

		return true;
	}
	/*
	//=====================================================================================
	*/
	void configs_c::draw_menu_tab()
	{
		if (ImGui::BeginTabItem("Configs"))
		{
			config_list.config_files.clear();

			for (auto& file : std::filesystem::directory_iterator{ "." })
			{
				if (niggerware::utils::string::to_lower(file.path().extension().string()) == ".json")
				{
					config_list.config_files.push_back(file.path().filename().string());
				}
			}

			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
			if (ImGui::ListBoxHeader("##configs", config_list.config_files.size(), 20))
			{
				config_list.set_config_selection();

				ImGui::ListBoxFooter();
			} ImGui::PopItemWidth();

			ImGui::PushItemWidth(304.0f * main_gui.scaling_factor);
			ImGui::InputTextEx("##new", "New config name...", config_list.new_config_name, sizeof(config_list.new_config_name), {}, ImGuiInputTextFlags_CharsNoBlank); ImGui::SameLine();
			ImGui::PopItemWidth();
			if (ImGui::Button("Create", { 40.0f * main_gui.scaling_factor, 0.0f }))
			{
				std::filesystem::directory_entry file(config_list.new_config_name);

				if (!file.path().string().empty())
				{
					save(file.path().string() + ".json");
					niggerware::utils::memory::zero(config_list.new_config_name, sizeof(config_list.new_config_name));
				}
			} ImGui::SameLine();

			if (ImGui::Button("Delete", { 40.0f * main_gui.scaling_factor, 0.0f }))
			{
				if (!config_list.config_files.empty())
				{
					std::filesystem::remove(config_list.get_config_selection());
				}
			} ImGui::SameLine();

			if (ImGui::Button("Save", { 40.0f * main_gui.scaling_factor, 0.0f }))
			{
				if (!config_list.config_files.empty())
				{
					save(config_list.get_config_selection());
				}
			} ImGui::SameLine();

			if (ImGui::Button("Load", { 40.0f * main_gui.scaling_factor, 0.0f }))
			{
				if (!config_list.config_files.empty())
				{
					load(config_list.get_config_selection());
				}
			}

			ImGui::EndTabItem();
		}
	}
	/*
	//=====================================================================================
	*/
	configs_c::cvar_s configs_c::add_bool(const std::string& name, const bool value)
	{
		cvar_value_s cvar_value;

		cvar_value.enabled = value;

		return { name, {}, {}, cvar_type_bool, cvar_value, {}, {} };
	}
	/*
	//=====================================================================================
	*/
	configs_c::cvar_s configs_c::add_int(const std::string& name, const std::vector<std::string>& items, const std::int32_t value, const std::int32_t min, const std::int32_t max, const std::int32_t step, const std::string& format)
	{
		cvar_value_s cvar_value;
		cvar_limits_s cvar_limits;
		cvar_step_s cvar_step;

		cvar_value.integer = value;
		cvar_limits.integer.min = min;
		cvar_limits.integer.max = max;
		cvar_step.integer = step;

		return { name, format, items, cvar_type_int, cvar_value, cvar_limits, cvar_step };
	}
	/*
	//=====================================================================================
	*/
	configs_c::cvar_s configs_c::add_float(const std::string& name, const std::float_t value, const std::float_t min, const std::float_t max, const std::float_t step, const std::string& format)
	{
		cvar_value_s cvar_value;
		cvar_limits_s cvar_limits;
		cvar_step_s cvar_step;

		cvar_value.value = value;
		cvar_limits.value.min = min;
		cvar_limits.value.max = max;
		cvar_step.value = step;

		return { name, format, {}, cvar_type_float, cvar_value, cvar_limits, cvar_step };
	}
	/*
	//=====================================================================================
	*/
	configs_c::cvar_s configs_c::add_string(const std::string& name, const std::string& value)
	{
		cvar_value_s cvar_value;

		cvar_value.string = value;

		return { name, {}, {}, cvar_type_string, cvar_value, {}, {} };
	}
	/*
	//=====================================================================================
	*/
	configs_c::cvar_s configs_c::add_color(const std::string& name, const ImVec4& value, const std::float_t speed, const std::float_t minspeed, const std::float_t maxspeed)
	{
		cvar_value_s cvar_value;
		cvar_limits_s cvar_limits;

		cvar_value.color = value;
		cvar_value.value = speed;
		cvar_limits.value.min = minspeed;
		cvar_limits.value.max = maxspeed;

		return { name, {}, {}, cvar_type_color, cvar_value, cvar_limits, {} };
	}
}

//=====================================================================================