//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	drawing_c drawing;

	void drawing_c::draw_border(ImVec2 position, ImVec2 dimentions, bool fill, ImVec4 col)
	{
		if (fill)
		{
			ImGui::GetWindowDrawList()->AddRectFilled(position, position + dimentions, ImGui::GetColorU32({ col.x, col.y, col.z, col.w * 0.25f }));
		}

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y }, { position.x + dimentions.x, position.y + 1.0f }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y }, { position.x + 1.0f, position.y + dimentions.y }, ImGui::GetColorU32(col));

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x + dimentions.x - 1.0f, position.y }, { position.x + dimentions.x, position.y + dimentions.y }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y + dimentions.y - 1.0f }, { position.x + dimentions.x, position.y + dimentions.y }, ImGui::GetColorU32(col));
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_border(ImVec2 corners2d[8], ImVec4 col)
	{
		draw_line(corners2d[0], corners2d[1], col);
		draw_line(corners2d[0], corners2d[2], col);
		draw_line(corners2d[0], corners2d[4], col);
		draw_line(corners2d[1], corners2d[3], col);
		draw_line(corners2d[1], corners2d[5], col);
		draw_line(corners2d[2], corners2d[3], col);
		draw_line(corners2d[2], corners2d[6], col);
		draw_line(corners2d[3], corners2d[7], col);
		draw_line(corners2d[4], corners2d[5], col);
		draw_line(corners2d[4], corners2d[6], col);
		draw_line(corners2d[6], corners2d[7], col);
		draw_line(corners2d[5], corners2d[7], col);
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_corners(ImVec2 position, ImVec2 dimentions, std::float_t length, bool fill, ImVec4 col)
	{
		if (fill)
		{
			ImGui::GetWindowDrawList()->AddRectFilled(position, position + dimentions, ImGui::GetColorU32({ col.x, col.y, col.z, col.w * 0.25f }));
		}

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y }, { position.x + dimentions.x / length + 1.0f, position.y + 1.0f }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y }, { position.x + 1.0f, position.y + dimentions.y / length + 1.0f }, ImGui::GetColorU32(col));

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x + dimentions.x - dimentions.x / length, position.y }, { position.x + dimentions.x, position.y + 1.0f }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x + dimentions.x - 1.0f, position.y }, { position.x + dimentions.x, position.y + dimentions.y / length + 1.0f }, ImGui::GetColorU32(col));

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y + dimentions.y - 1.0f }, { position.x + dimentions.x / length + 1.0f, position.y + dimentions.y }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y + dimentions.y - dimentions.y / length }, { position.x + 1.0f, position.y + dimentions.y }, ImGui::GetColorU32(col));

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x + dimentions.x - dimentions.x / length, position.y + dimentions.y - 1.0f }, { position.x + dimentions.x, position.y + dimentions.y }, ImGui::GetColorU32(col));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x + dimentions.x - 1.0f, position.y + dimentions.y - dimentions.y / length }, { position.x + dimentions.x, position.y + dimentions.y }, ImGui::GetColorU32(col));
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_corners(ImVec2 corners2d[8], std::float_t length, ImVec4 col)
	{
		ImVec2 mid_points[12][2];

		auto calculate_mid_points = [&](const ImVec2 a, const ImVec2 b, ImVec2* c, ImVec2* d, const std::float_t e)
		{
			c->x = b.x + (a.x - b.x) / e * (e - 1.0f);
			c->y = b.y + (a.y - b.y) / e * (e - 1.0f);

			d->x = b.x + (a.x - b.x) / e;
			d->y = b.y + (a.y - b.y) / e;
		};

		calculate_mid_points(corners2d[0], corners2d[1], &mid_points[0][0], &mid_points[0][1], length);
		calculate_mid_points(corners2d[0], corners2d[2], &mid_points[1][0], &mid_points[1][1], length);
		calculate_mid_points(corners2d[0], corners2d[4], &mid_points[2][0], &mid_points[2][1], length);
		calculate_mid_points(corners2d[1], corners2d[3], &mid_points[3][0], &mid_points[3][1], length);
		calculate_mid_points(corners2d[1], corners2d[5], &mid_points[4][0], &mid_points[4][1], length);
		calculate_mid_points(corners2d[2], corners2d[3], &mid_points[5][0], &mid_points[5][1], length);
		calculate_mid_points(corners2d[2], corners2d[6], &mid_points[6][0], &mid_points[6][1], length);
		calculate_mid_points(corners2d[3], corners2d[7], &mid_points[7][0], &mid_points[7][1], length);
		calculate_mid_points(corners2d[4], corners2d[5], &mid_points[8][0], &mid_points[8][1], length);
		calculate_mid_points(corners2d[4], corners2d[6], &mid_points[9][0], &mid_points[9][1], length);
		calculate_mid_points(corners2d[6], corners2d[7], &mid_points[10][0], &mid_points[10][1], length);
		calculate_mid_points(corners2d[5], corners2d[7], &mid_points[11][0], &mid_points[11][1], length);

		draw_line(corners2d[0], mid_points[0][0], col);
		draw_line(corners2d[0], mid_points[1][0], col);
		draw_line(corners2d[0], mid_points[2][0], col);
		draw_line(corners2d[1], mid_points[3][0], col);
		draw_line(corners2d[1], mid_points[4][0], col);
		draw_line(corners2d[2], mid_points[5][0], col);
		draw_line(corners2d[2], mid_points[6][0], col);
		draw_line(corners2d[3], mid_points[7][0], col);
		draw_line(corners2d[4], mid_points[8][0], col);
		draw_line(corners2d[4], mid_points[9][0], col);
		draw_line(corners2d[6], mid_points[10][0], col);
		draw_line(corners2d[5], mid_points[11][0], col);

		draw_line(corners2d[1], mid_points[0][1], col);
		draw_line(corners2d[2], mid_points[1][1], col);
		draw_line(corners2d[4], mid_points[2][1], col);
		draw_line(corners2d[3], mid_points[3][1], col);
		draw_line(corners2d[5], mid_points[4][1], col);
		draw_line(corners2d[3], mid_points[5][1], col);
		draw_line(corners2d[6], mid_points[6][1], col);
		draw_line(corners2d[7], mid_points[7][1], col);
		draw_line(corners2d[5], mid_points[8][1], col);
		draw_line(corners2d[6], mid_points[9][1], col);
		draw_line(corners2d[7], mid_points[10][1], col);
		draw_line(corners2d[7], mid_points[11][1], col);
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_bones(ImVec2 bones2d[structures::bone_max], ImVec4 col)
	{
		if (functions::Com_SessionMode_IsMode(structures::MODE_MULTIPLAYER))
		{
			auto center = (bones2d[structures::bone_helmet] + bones2d[structures::bone_head]) / 2.0f;
			auto diameter = mathematics.calculate_distance(bones2d[structures::bone_helmet], bones2d[structures::bone_head]);

			ImGui::GetWindowDrawList()->AddCircle(center, diameter / 2.0f, ImGui::GetColorU32(col), std::stcast<std::int32_t>(diameter));

			draw_line
			(
				bones2d[structures::bone_head],
				bones2d[structures::bone_neck],
				col
			);
		}

		draw_line
		(
			bones2d[structures::bone_neck],
			bones2d[structures::bone_left_shoulder],
			col
		);

		draw_line
		(
			bones2d[structures::bone_left_shoulder],
			bones2d[structures::bone_left_elbow],
			col
		);

		draw_line
		(
			bones2d[structures::bone_left_elbow],
			bones2d[structures::bone_left_wrist],
			col
		);

		draw_line
		(
			bones2d[structures::bone_neck],
			bones2d[structures::bone_right_shoulder],
			col
		);

		draw_line
		(
			bones2d[structures::bone_right_shoulder],
			bones2d[structures::bone_right_elbow],
			col
		);

		draw_line
		(
			bones2d[structures::bone_right_elbow],
			bones2d[structures::bone_right_wrist],
			col
		);

		draw_line
		(
			bones2d[structures::bone_neck],
			bones2d[structures::bone_upper_spine],
			col
		);

		draw_line
		(
			bones2d[structures::bone_upper_spine],
			bones2d[structures::bone_lower_spine],
			col
		);

		draw_line
		(
			bones2d[structures::bone_lower_spine],
			bones2d[structures::bone_left_hip],
			col
		);

		draw_line
		(
			bones2d[structures::bone_left_hip],
			bones2d[structures::bone_left_knee],
			col
		);

		draw_line
		(
			bones2d[structures::bone_left_knee],
			bones2d[structures::bone_left_ankle],
			col
		);

		draw_line
		(
			bones2d[structures::bone_lower_spine],
			bones2d[structures::bone_right_hip],
			col
		);

		draw_line
		(
			bones2d[structures::bone_right_hip],
			bones2d[structures::bone_right_knee],
			col
		);

		draw_line
		(
			bones2d[structures::bone_right_knee],
			bones2d[structures::bone_right_ankle],
			col
		);
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_bones(ImVec2 bones2d[structures::bone_max], ImVec4 col, ImVec4 outlinecol)
	{
		if (functions::Com_SessionMode_IsMode(structures::MODE_MULTIPLAYER))
		{
			ImGui::GetWindowDrawList()->AddRectFilled
			(
				{ bones2d[structures::bone_helmet].x - 1.0f, bones2d[structures::bone_helmet].y - 1.0f },
				{ bones2d[structures::bone_helmet].x + 2.0f, bones2d[structures::bone_helmet].y + 2.0f },
				ImGui::GetColorU32(outlinecol)
			);

			ImGui::GetWindowDrawList()->AddRectFilled
			(
				{ bones2d[structures::bone_helmet].x, bones2d[structures::bone_helmet].y },
				{ bones2d[structures::bone_helmet].x + 1.0f, bones2d[structures::bone_helmet].y + 1.0f },
				ImGui::GetColorU32(col)
			);

			ImGui::GetWindowDrawList()->AddRectFilled
			(
				{ bones2d[structures::bone_head].x - 1.0f, bones2d[structures::bone_head].y - 1.0f },
				{ bones2d[structures::bone_head].x + 2.0f, bones2d[structures::bone_head].y + 2.0f },
				ImGui::GetColorU32(outlinecol)
			);

			ImGui::GetWindowDrawList()->AddRectFilled
			(
				{ bones2d[structures::bone_head].x, bones2d[structures::bone_head].y },
				{ bones2d[structures::bone_head].x + 1.0f, bones2d[structures::bone_head].y + 1.0f },
				ImGui::GetColorU32(col)
			);
		}

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_neck].x - 1.0f, bones2d[structures::bone_neck].y - 1.0f },
			{ bones2d[structures::bone_neck].x + 2.0f, bones2d[structures::bone_neck].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_neck].x, bones2d[structures::bone_neck].y },
			{ bones2d[structures::bone_neck].x + 1.0f, bones2d[structures::bone_neck].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_upper_spine].x - 1.0f, bones2d[structures::bone_upper_spine].y - 1.0f },
			{ bones2d[structures::bone_upper_spine].x + 2.0f, bones2d[structures::bone_upper_spine].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_upper_spine].x, bones2d[structures::bone_upper_spine].y },
			{ bones2d[structures::bone_upper_spine].x + 1.0f, bones2d[structures::bone_upper_spine].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_lower_spine].x - 1.0f, bones2d[structures::bone_lower_spine].y - 1.0f },
			{ bones2d[structures::bone_lower_spine].x + 2.0f, bones2d[structures::bone_lower_spine].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_lower_spine].x, bones2d[structures::bone_lower_spine].y },
			{ bones2d[structures::bone_lower_spine].x + 1.0f, bones2d[structures::bone_lower_spine].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_shoulder].x - 1.0f, bones2d[structures::bone_left_shoulder].y - 1.0f },
			{ bones2d[structures::bone_left_shoulder].x + 2.0f, bones2d[structures::bone_left_shoulder].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_shoulder].x, bones2d[structures::bone_left_shoulder].y },
			{ bones2d[structures::bone_left_shoulder].x + 1.0f, bones2d[structures::bone_left_shoulder].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_shoulder].x - 1.0f, bones2d[structures::bone_right_shoulder].y - 1.0f },
			{ bones2d[structures::bone_right_shoulder].x + 2.0f, bones2d[structures::bone_right_shoulder].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_shoulder].x, bones2d[structures::bone_right_shoulder].y },
			{ bones2d[structures::bone_right_shoulder].x + 1.0f, bones2d[structures::bone_right_shoulder].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_hip].x - 1.0f, bones2d[structures::bone_left_hip].y - 1.0f },
			{ bones2d[structures::bone_left_hip].x + 2.0f, bones2d[structures::bone_left_hip].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_hip].x, bones2d[structures::bone_left_hip].y },
			{ bones2d[structures::bone_left_hip].x + 1.0f, bones2d[structures::bone_left_hip].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_hip].x - 1.0f, bones2d[structures::bone_right_hip].y - 1.0f },
			{ bones2d[structures::bone_right_hip].x + 2.0f, bones2d[structures::bone_right_hip].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_hip].x, bones2d[structures::bone_right_hip].y },
			{ bones2d[structures::bone_right_hip].x + 1.0f, bones2d[structures::bone_right_hip].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_elbow].x - 1.0f, bones2d[structures::bone_left_elbow].y - 1.0f },
			{ bones2d[structures::bone_left_elbow].x + 2.0f, bones2d[structures::bone_left_elbow].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_elbow].x, bones2d[structures::bone_left_elbow].y },
			{ bones2d[structures::bone_left_elbow].x + 1.0f, bones2d[structures::bone_left_elbow].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_elbow].x - 1.0f, bones2d[structures::bone_right_elbow].y - 1.0f },
			{ bones2d[structures::bone_right_elbow].x + 2.0f, bones2d[structures::bone_right_elbow].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_elbow].x, bones2d[structures::bone_right_elbow].y },
			{ bones2d[structures::bone_right_elbow].x + 1.0f, bones2d[structures::bone_right_elbow].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_knee].x - 1.0f, bones2d[structures::bone_left_knee].y - 1.0f },
			{ bones2d[structures::bone_left_knee].x + 2.0f, bones2d[structures::bone_left_knee].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_knee].x, bones2d[structures::bone_left_knee].y },
			{ bones2d[structures::bone_left_knee].x + 1.0f, bones2d[structures::bone_left_knee].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_knee].x - 1.0f, bones2d[structures::bone_right_knee].y - 1.0f },
			{ bones2d[structures::bone_right_knee].x + 2.0f, bones2d[structures::bone_right_knee].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_knee].x, bones2d[structures::bone_right_knee].y },
			{ bones2d[structures::bone_right_knee].x + 1.0f, bones2d[structures::bone_right_knee].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_wrist].x - 1.0f, bones2d[structures::bone_left_wrist].y - 1.0f },
			{ bones2d[structures::bone_left_wrist].x + 2.0f, bones2d[structures::bone_left_wrist].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_wrist].x, bones2d[structures::bone_left_wrist].y },
			{ bones2d[structures::bone_left_wrist].x + 1.0f, bones2d[structures::bone_left_wrist].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_wrist].x - 1.0f, bones2d[structures::bone_right_wrist].y - 1.0f },
			{ bones2d[structures::bone_right_wrist].x + 2.0f, bones2d[structures::bone_right_wrist].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_wrist].x, bones2d[structures::bone_right_wrist].y },
			{ bones2d[structures::bone_right_wrist].x + 1.0f, bones2d[structures::bone_right_wrist].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_ankle].x - 1.0f, bones2d[structures::bone_left_ankle].y - 1.0f },
			{ bones2d[structures::bone_left_ankle].x + 2.0f, bones2d[structures::bone_left_ankle].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_left_ankle].x, bones2d[structures::bone_left_ankle].y },
			{ bones2d[structures::bone_left_ankle].x + 1.0f, bones2d[structures::bone_left_ankle].y + 1.0f },
			ImGui::GetColorU32(col)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_ankle].x - 1.0f, bones2d[structures::bone_right_ankle].y - 1.0f },
			{ bones2d[structures::bone_right_ankle].x + 2.0f, bones2d[structures::bone_right_ankle].y + 2.0f },
			ImGui::GetColorU32(outlinecol)
		);

		ImGui::GetWindowDrawList()->AddRectFilled
		(
			{ bones2d[structures::bone_right_ankle].x, bones2d[structures::bone_right_ankle].y },
			{ bones2d[structures::bone_right_ankle].x + 1.0f, bones2d[structures::bone_right_ankle].y + 1.0f },
			ImGui::GetColorU32(col)
		);
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_line(ImVec2 a, ImVec2 b, ImVec4 col)
	{
		ImGui::GetWindowDrawList()->AddLine(a, b, ImGui::GetColorU32(col));
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_string(std::string text, ImVec2 position, ImVec4 col, ImVec4 outlinecol)
	{
		ImGui::GetWindowDrawList()->AddText(main_gui.bank_gothic_pro_light, main_gui.bank_gothic_pro_light_size, { position.x + 1.0f, position.y + 1.0f }, ImGui::GetColorU32(outlinecol), text.c_str());
		ImGui::GetWindowDrawList()->AddText(main_gui.bank_gothic_pro_light, main_gui.bank_gothic_pro_light_size, { position.x, position.y }, ImGui::GetColorU32(col), text.c_str());
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_aim_pos(ImVec2 position, ImVec4 col, ImVec4 outlinecol)
	{
		ImGui::GetWindowDrawList()->AddCircleFilled(position, 2.0f, ImGui::GetColorU32(outlinecol));
		ImGui::GetWindowDrawList()->AddCircleFilled(position, 1.0f, ImGui::GetColorU32(col));
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_health_bar(structures::client_info_s* client, ImVec2 position, ImVec2 dimentions, ImVec4 col, ImVec4 outlinecol)
	{
		auto current_health = client->health;
		auto max_health = functions::get_cg()->predictedPlayerState.stats[2];

		auto health_fraction = std::stcast<std::float_t>(current_health) / std::stcast<std::float_t>(max_health);

		health_fraction = std::max(health_fraction, 0.0f);
		health_fraction = std::min(health_fraction, 1.0f);

		ImGui::GetWindowDrawList()->AddRectFilled({ position.x - 1.0f, position.y - 1.0f }, { position.x + dimentions.x + 1.0f, position.y + dimentions.y + 1.0f }, ImGui::GetColorU32(outlinecol));
		ImGui::GetWindowDrawList()->AddRectFilled({ position.x, position.y + dimentions.y * (1.0f - health_fraction) }, position + dimentions, ImGui::GetColorU32(col));
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_client(structures::centity_s* entity, structures::client_info_s* client, ImVec2 bones2d[structures::bone_max], ImVec2 corners2d[8], ImVec2 center, std::float_t scale, std::float_t distance, ImVec4 col, ImVec4 textcol, ImVec4 outlinecol)
	{
		auto width = 0.0f, height = 0.0f, padding = 3.0f * main_gui.scaling_factor;

		auto entity_num = entity->nextState.number;
		auto entity_flags = entity->nextState.lerp.eFlags;
		auto is_friendly = target_list.entity_is_friendly(entity_num);

		if (entity_flags[1] & entity_flag_prone)
		{
			width = scale / 1.5f;
			height = scale / 2.0f;
		}

		else if (entity_flags[1] & entity_flag_crouch)
		{
			width = scale / 2.0f;
			height = scale / 2.0f;
		}

		else
		{
			width = scale / 2.0f;
			height = scale / 1.5f;
		}

		width *= 2.0f;
		height *= 2.0f;

		auto& io = ImGui::GetIO();

		if (configs.esp_boxes.current.integer == configs_c::esp_boxes_border)
			draw_border({ center.x - width / 2.0f, center.y - height / 2.0f }, { width, height }, false, col);

		else if (configs.esp_boxes.current.integer == configs_c::esp_boxes_corner)
			draw_corners({ center.x - width / 2.0f, center.y - height / 2.0f }, { width, height }, 3.0f, false, col);

		else if (configs.esp_boxes.current.integer == configs_c::esp_boxes_border_filled)
			draw_border({ center.x - width / 2.0f, center.y - height / 2.0f }, { width, height }, true, col);

		else if (configs.esp_boxes.current.integer == configs_c::esp_boxes_corner_filled)
			draw_corners({ center.x - width / 2.0f, center.y - height / 2.0f }, { width, height }, 3.0f, true, col);

		else if (configs.esp_boxes.current.integer == configs_c::esp_boxes_border_3d)
			draw_border(corners2d, col);

		else if (configs.esp_boxes.current.integer == configs_c::esp_boxes_corner_3d)
			draw_corners(corners2d, 3.0f, col);

		if (configs.esp_bones.current.integer == configs_c::esp_bones_dots)
			draw_bones(bones2d, col, outlinecol);

		else if (configs.esp_bones.current.integer == configs_c::esp_bones_lines)
			draw_bones(bones2d, col);
		
		if (configs.esp_snap_lines.current.integer == configs_c::esp_snap_lines_top)
			draw_line({ center.x, center.y - height / 2.0f }, { io.DisplaySize.x / 2.0f, 0.0f }, col);

		else if (configs.esp_snap_lines.current.integer == configs_c::esp_snap_lines_center)
			draw_line({ center.x, center.y }, { io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f }, col);

		else if (configs.esp_snap_lines.current.integer == configs_c::esp_snap_lines_bottom)
			draw_line({ center.x, center.y + height / 2.0f }, { io.DisplaySize.x / 2.0f, io.DisplaySize.y }, col);

		else if (configs.esp_snap_lines.current.integer == configs_c::esp_snap_lines_alternating_1)
			is_friendly ?
			draw_line({ center.x, center.y + height / 2.0f }, { io.DisplaySize.x / 2.0f, io.DisplaySize.y }, col) :
			draw_line({ center.x, center.y - height / 2.0f }, { io.DisplaySize.x / 2.0f, 0.0f }, col);

		else if (configs.esp_snap_lines.current.integer == configs_c::esp_snap_lines_alternating_2)
			is_friendly ?
			draw_line({ center.x, center.y - height / 2.0f }, { io.DisplaySize.x / 2.0f, 0.0f }, col) :
			draw_line({ center.x, center.y + height / 2.0f }, { io.DisplaySize.x / 2.0f, io.DisplaySize.y }, col);

		if (configs.esp_health_bars.current.enabled)
			draw_health_bar(client, { center.x - width / 2.0f - (padding + 1.0f), center.y - height / 2.0f + 1.0f }, { 1.0f, height - 2.0f }, col, outlinecol);

		if (configs.esp_distances.current.enabled && configs.esp_names.current.enabled)
		{
			auto text(functions::remove_modifiers(niggerware::utils::string::va("[%.0fft] %s", convert_to_feet(distance), client->clientName)));
			auto text_size = main_gui.bank_gothic_pro_light->CalcTextSizeA(main_gui.bank_gothic_pro_light_size, std::numeric_limits<std::float_t>::max(), 0.0f, text.c_str());

			draw_string(text, { center.x - text_size.x / 2.0f, center.y - height / 2.0f - padding - text_size.y }, textcol, outlinecol);
		}

		else if (configs.esp_distances.current.enabled)
		{
			auto text(functions::remove_modifiers(niggerware::utils::string::va("[%.0fft]", convert_to_feet(distance))));
			auto text_size = main_gui.bank_gothic_pro_light->CalcTextSizeA(main_gui.bank_gothic_pro_light_size, std::numeric_limits<std::float_t>::max(), 0.0f, text.c_str());

			draw_string(text, { center.x - text_size.x / 2.0f, center.y - height / 2.0f - padding - text_size.y }, textcol, outlinecol);
		}

		else if (configs.esp_names.current.enabled)
		{
			auto text(functions::remove_modifiers(client->clientName));
			auto text_size = main_gui.bank_gothic_pro_light->CalcTextSizeA(main_gui.bank_gothic_pro_light_size, std::numeric_limits<std::float_t>::max(), 0.0f, text.c_str());

			draw_string(text, { center.x - text_size.x / 2.0f, center.y - height / 2.0f - padding - text_size.y }, textcol, outlinecol);
		}

		if (configs.esp_weapons.current.enabled)
		{
			auto text(functions::remove_modifiers(entities[entity_num].weapon_name));
			auto text_size = main_gui.bank_gothic_pro_light->CalcTextSizeA(main_gui.bank_gothic_pro_light_size, std::numeric_limits<std::float_t>::max(), 0.0f, text.c_str());

			draw_string(text, { center.x - text_size.x / 2.0f, center.y + height / 2.0f + padding }, textcol, outlinecol);
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_entity(ImVec2 corners2d[8], std::string name, ImVec2 center, std::float_t distance, ImVec4 col, ImVec4 textcol, ImVec4 outlinecol)
	{
		if (configs.esp_entities.current.integer == configs_c::esp_entities_info)
		{
			auto text(functions::remove_modifiers(niggerware::utils::string::va("[%.0fft] %s", convert_to_feet(distance), name.c_str())));
			auto text_size = main_gui.bank_gothic_pro_light->CalcTextSizeA(main_gui.bank_gothic_pro_light_size, std::numeric_limits<std::float_t>::max(), 0.0f, text.c_str());

			draw_string(text, { center.x - text_size.x / 2.0f, center.y - text_size.y / 2.0f }, textcol, outlinecol);
		}

		else if (configs.esp_entities.current.integer == configs_c::esp_entities_border_3d)
			draw_border(corners2d, col);

		else if (configs.esp_entities.current.integer == configs_c::esp_entities_corner_3d)
			draw_corners(corners2d, 3.0f, col);
	}
	/*
	//=====================================================================================
	*/
	bool drawing_c::calculate_box(ImVec3 bones3d[structures::bone_max], ImVec2 bones2d[structures::bone_max], ImVec2* position, ImVec2* dimentions)
	{
		ImVec2 temp, min_temp =
		{
			std::numeric_limits<std::float_t>::max(),
			std::numeric_limits<std::float_t>::max()
		}, max_temp =
		{
			-std::numeric_limits<std::float_t>::max(),
			-std::numeric_limits<std::float_t>::max()
		};

		for (auto i{ 0 }; i < structures::bone_max; i++)
		{
			if (should_skip_bone(i))
				continue;

			if (!mathematics.world_to_screen(bones3d[i], &temp))
				return false;

			if (temp.x < min_temp.x)
				min_temp.x = temp.x;

			if (temp.x > max_temp.x)
				max_temp.x = temp.x;

			if (temp.y < min_temp.y)
				min_temp.y = temp.y;

			if (temp.y > max_temp.y)
				max_temp.y = temp.y;

			bones2d[i] = temp;
		}

		*dimentions = max_temp - min_temp;
		*position = min_temp;

		return true;
	}
	/*
	//=====================================================================================
	*/
	bool drawing_c::calculate_box(structures::centity_s* entity, ImVec3 center, ImVec3 corners3d[8], ImVec2 corners2d[8])
	{
		if (entity->nextState.eType == structures::et_player)
		{
			ImVec3 minimum, maximum;

			if (entity->nextState.lerp.eFlags[1] & entity_flag_prone)
			{
				minimum.x = center.x - 32.5f;
				minimum.y = center.y - 20.0f;
				minimum.z = center.z - 10.0f;

				maximum.x = center.x + 32.5f;
				maximum.y = center.y + 20.0f;
				maximum.z = center.z + 10.0f;
			}

			else if (entity->nextState.lerp.eFlags[1] & entity_flag_crouch)
			{
				minimum.x = center.x - 20.0f;
				minimum.y = center.y - 20.0f;
				minimum.z = center.z - 21.0f;

				maximum.x = center.x + 20.0f;
				maximum.y = center.y + 20.0f;
				maximum.z = center.z + 21.0f;
			}

			else
			{
				minimum.x = center.x - 20.0f;
				minimum.y = center.y - 20.0f;
				minimum.z = center.z - 32.5f;

				maximum.x = center.x + 20.0f;
				maximum.y = center.y + 20.0f;
				maximum.z = center.z + 32.5f;
			}

			mathematics.setup_box(corners3d, minimum, maximum);

			for (auto i = 0; i < 8; i++)
			{
				mathematics.rotate_point_yaw(corners3d[i], center, entity->pose.angles.y, &corners3d[i]);

				if (!mathematics.world_to_screen(corners3d[i], &corners2d[i]))
				{
					return false;
				}
			}
		}

		else
		{
			for (auto i = 0; i < 8; i++)
			{
				if (!mathematics.world_to_screen(corners3d[i], &corners2d[i]))
				{
					return false;
				}
			}
		}

		return true;
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_esp_color(std::int32_t index)
	{
		if (aimbot.aim_state.aim_target_num == index && configs.color_aimbot_target.current.color.w > 0.0f)
		{
			entities[index].esp_color = configs.color_aimbot_target.current.color;
		}

		else if (aimbot.aim_state.anti_aim_target_num == index && configs.color_anti_aim_target.current.color.w > 0.0f)
		{
			entities[index].esp_color = configs.color_anti_aim_target.current.color;
		}

		else if (target_list.priorities[index].is_prioritized && !target_list.priorities[index].is_ignored && !entities[index].is_friendly && configs.color_prioritized.current.color.w > 0.0f)
		{
			entities[index].esp_color = configs.color_prioritized.current.color;
		}

		else
		{
			if (entities[index].is_friendly)
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_color = configs.color_allies_visible.current.color;
				}

				else
				{
					entities[index].esp_color = configs.color_allies_occluded.current.color;
				}
			}

			else
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_color = configs.color_axis_visible.current.color;
				}

				else
				{
					entities[index].esp_color = configs.color_axis_occluded.current.color;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_esp_text_color(std::int32_t index)
	{
		if (aimbot.aim_state.aim_target_num == index && configs.color_aimbot_target_text.current.color.w > 0.0f)
		{
			entities[index].esp_text_color = configs.color_aimbot_target_text.current.color;
		}

		else if (aimbot.aim_state.anti_aim_target_num == index && configs.color_anti_aim_target_text.current.color.w > 0.0f)
		{
			entities[index].esp_text_color = configs.color_anti_aim_target_text.current.color;
		}

		else if (target_list.priorities[index].is_prioritized && !target_list.priorities[index].is_ignored && !entities[index].is_friendly && configs.color_prioritized_text.current.color.w > 0.0f)
		{
			entities[index].esp_text_color = configs.color_prioritized_text.current.color;
		}

		else
		{
			if (entities[index].is_friendly)
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_text_color = configs.color_allies_visible_text.current.color;
				}

				else
				{
					entities[index].esp_text_color = configs.color_allies_occluded_text.current.color;
				}
			}

			else
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_text_color = configs.color_axis_visible_text.current.color;
				}

				else
				{
					entities[index].esp_text_color = configs.color_axis_occluded_text.current.color;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_esp_outline_color(std::int32_t index)
	{
		if (aimbot.aim_state.aim_target_num == index && configs.color_aimbot_target_outline.current.color.w > 0.0f)
		{
			entities[index].esp_outline_color = configs.color_aimbot_target_outline.current.color;
		}

		else if (aimbot.aim_state.anti_aim_target_num == index && configs.color_anti_aim_target_outline.current.color.w > 0.0f)
		{
			entities[index].esp_outline_color = configs.color_anti_aim_target_outline.current.color;
		}

		else if (target_list.priorities[index].is_prioritized && !target_list.priorities[index].is_ignored && !entities[index].is_friendly && configs.color_prioritized_outline.current.color.w > 0.0f)
		{
			entities[index].esp_outline_color = configs.color_prioritized_outline.current.color;
		}

		else
		{
			if (entities[index].is_friendly)
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_outline_color = configs.color_allies_visible_outline.current.color;
				}

				else
				{
					entities[index].esp_outline_color = configs.color_allies_occluded_outline.current.color;
				}
			}

			else
			{
				if (entities[index].is_visible)
				{
					entities[index].esp_outline_color = configs.color_axis_visible_outline.current.color;
				}

				else
				{
					entities[index].esp_outline_color = configs.color_axis_occluded_outline.current.color;
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_aim_pos_color(std::int32_t index)
	{
		if (configs.color_aim_pos.current.color.w > 0.0f)
		{
			entities[index].aim_pos_color = configs.color_aim_pos.current.color;
		}

		else
		{
			entities[index].aim_pos_color = entities[index].esp_color;
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_aim_pos_outline_color(std::int32_t index)
	{
		if (configs.color_aim_pos_outline.current.color.w > 0.0f)
		{
			entities[index].aim_pos_outline_color = configs.color_aim_pos_outline.current.color;
		}

		else
		{
			entities[index].aim_pos_outline_color = entities[index].esp_outline_color;
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::calculate_colors()
	{
		for (auto i = 0; i < max_clients; i++)
		{
			get_esp_color(i);
			get_esp_text_color(i);
			get_esp_outline_color(i);
			get_aim_pos_color(i);
			get_aim_pos_outline_color(i);
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::calculate_tracers()
	{
		tracers.erase(std::remove_if(tracers.begin(), tracers.end(), [&](tracer_s& a)
		{
			auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - a.start_time);

			if (a.world_to_screen_success = mathematics.world_to_screen(a.hit_pos_world, &a.hit_pos_screen))
			{
				mathematics.world_to_screen(a.start_pos_world, &a.start_pos_screen);

				a.hit_outline_color.w = (1.0f - (std::stcast<std::float_t>(delta_time.count()) / 1000)) * a.hit_outline_alpha;
				a.hit_color.w = (1.0f - (std::stcast<std::float_t>(delta_time.count()) / 1000)) * a.hit_alpha;
				a.line_color.w = (1.0f - (std::stcast<std::float_t>(delta_time.count()) / 1000)) * a.line_alpha;
			}

			return (a.hit_outline_color.w <= 0.0f && a.hit_color.w <= 0.0f && a.line_color.w <= 0.0f);
		}), tracers.end());
	}
	/*
	//=====================================================================================
	*/
	bool drawing_c::should_draw_index(std::int32_t index)
	{
		return
		(
			(configs.esp_mode.current.integer == configs_c::esp_mode_axis && !target_list.entity_is_friendly(index)) ||
			(configs.esp_mode.current.integer == configs_c::esp_mode_allies && target_list.entity_is_friendly(index)) ||
			configs.esp_mode.current.integer == configs_c::esp_mode_full
		);
	}
	/*
	//=====================================================================================
	*/
	bool drawing_c::should_skip_bone(std::int32_t index)
	{
		return 
		(
			functions::Com_SessionMode_IsMode(structures::MODE_ZOMBIES) &&
			(
				index == structures::bone_helmet || 
				index == structures::bone_left_clavicle || 
				index == structures::bone_right_clavicle ||
				index == structures::bone_left_wrist_twist || 
				index == structures::bone_right_wrist_twist
			)
		);
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::get_information()
	{
		for (auto i{ 0 }; i < max_entities; i++)
		{
			entities[i].reset();

			if (!target_list.entity_is_valid(i))
				continue;

			if (!setup_world_space(i))
				continue;

			setup_screen_space(i);
		}
	}
	/*
	//=====================================================================================
	*/
	bool drawing_c::setup_world_space(std::int32_t index)
	{
		if (auto dobj_ptr{ functions::Com_GetClientDObj(index, structures::LOCAL_CLIENT_FIRST) }; dobj_ptr)
		{
			if (functions::get_centity(index)->nextState.eType == structures::et_player)
			{
				ImVec3 temp_min =
				{
					std::numeric_limits<std::float_t>::max(),
					std::numeric_limits<std::float_t>::max(),
					std::numeric_limits<std::float_t>::max()
				}, temp_max =
				{
					-std::numeric_limits<std::float_t>::max(),
					-std::numeric_limits<std::float_t>::max(),
					-std::numeric_limits<std::float_t>::max()
				};

				for (auto i{ 0 }; i < structures::bone_max; i++)
				{
					if (should_skip_bone(i))
						continue;

					if (!functions::CG_DObjGetWorldTagPos(&functions::get_centity(index)->pose, dobj_ptr, functions::GScr_AllocString(structures::bone_names[i].second.c_str()), &entities[index].world_space.bones[i]))
						return false;

					if (entities[index].world_space.bones[i].x < temp_min.x)
						temp_min.x = entities[index].world_space.bones[i].x;

					if (entities[index].world_space.bones[i].x > temp_max.x)
						temp_max.x = entities[index].world_space.bones[i].x;

					if (entities[index].world_space.bones[i].y < temp_min.y)
						temp_min.y = entities[index].world_space.bones[i].y;

					if (entities[index].world_space.bones[i].y > temp_max.y)
						temp_max.y = entities[index].world_space.bones[i].y;

					if (entities[index].world_space.bones[i].z < temp_min.z)
						temp_min.z = entities[index].world_space.bones[i].z;

					if (entities[index].world_space.bones[i].z > temp_max.z)
						temp_max.z = entities[index].world_space.bones[i].z;
				}

				entities[index].world_space.box_center = (temp_min + temp_max) / 2.0f;
			}

			else
			{
				functions::DObjCalcBounds(dobj_ptr, &entities[index].world_space.box_min, &entities[index].world_space.box_max);
				functions::CG_GetDObjOrientation(structures::LOCAL_CLIENT_FIRST, index, entities[index].world_space.box_axis, &entities[index].world_space.box_origin);

				mathematics.rotate_box(entities[index].world_space.box_corners, entities[index].world_space.box_axis, entities[index].world_space.box_origin, entities[index].world_space.box_min, entities[index].world_space.box_max);
				mathematics.get_box_center(entities[index].world_space.box_corners, &entities[index].world_space.box_center);
			}
		} else return false;

		return true;
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::setup_screen_space(std::int32_t index)
	{
		entities[index].weapon_name = functions::get_weapon_name(index);

		if (functions::get_centity(index)->nextState.eType == structures::et_player)
		{
			auto view_origin = functions::get_centity(index)->pose.origin;
			view_origin.z += 55.0f;

			entities[index].world_to_screen_success =
			(
				calculate_box(entities[index].world_space.bones, entities[index].screen_space.bones, &entities[index].screen_space.box_pos, &entities[index].screen_space.box_size) &&
				calculate_box(functions::get_centity(index), entities[index].world_space.box_center, entities[index].world_space.box_corners, entities[index].screen_space.box_corners) &&
				mathematics.world_to_screen(entities[index].world_space.box_center, &entities[index].screen_space.box_center) &&
				mathematics.world_to_screen(functions::get_centity(index)->pose.origin, &entities[index].screen_space.lower_point) &&
				mathematics.world_to_screen(view_origin, &entities[index].screen_space.upper_point)
			);

			mathematics.world_to_compass(functions::get_centity(index)->pose.origin, compass.compass_pos, compass.compass_size, &compass.arrow_pos[index]);
			mathematics.world_to_radar(functions::get_centity(index)->pose.origin, radar.radar_pos, radar.radar_scale, radar.radar_size, radar.blip_size, &radar.blip_pos[index]);

			entities[index].screen_space.scale = entities[index].screen_space.lower_point.y - entities[index].screen_space.upper_point.y;

			entities[index].is_visible = target_list.entity_is_visible(index);
			entities[index].is_friendly = target_list.entity_is_friendly(index);
		}

		else
		{
			entities[index].world_to_screen_success =
			(
				calculate_box(functions::get_centity(index), entities[index].world_space.box_center, entities[index].world_space.box_corners, entities[index].screen_space.box_corners) &&
				mathematics.world_to_screen(entities[index].world_space.box_center, &entities[index].screen_space.box_center)
			);
		}

		if (aimbot.aim_state.aim_target_acquired)
		{
			mathematics.world_to_screen(aimbot.aim_state.aim_pos_world, &aimbot.aim_state.aim_pos_screen);
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_esp()
	{
		for (auto i = 0; i < max_entities; i++)
		{
			if (should_draw_index(i))
			{
				if (target_list.entity_is_valid(i) && entities[i].world_to_screen_success)
				{
					switch (functions::get_centity(i)->nextState.eType)
					{
					case structures::et_player:
					{
						draw_client
						(
							functions::get_centity(i), 
							&functions::get_cg()->clientInfo[i],
							entities[i].screen_space.bones,
							entities[i].screen_space.box_corners,
							entities[i].screen_space.box_center,
							entities[i].screen_space.scale,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							entities[i].esp_color,
							entities[i].esp_text_color,
							entities[i].esp_outline_color
						);
					} break;

					case structures::et_item:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Item" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;

					case structures::et_missile:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Missile" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;

					case structures::et_helicopter:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Helicopter" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;

					case structures::et_plane:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Plane" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;

					case structures::et_vehicle:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Vehicle" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;

					case structures::et_actor:
					{
						draw_entity
						(
							entities[i].screen_space.box_corners,
							entities[i].weapon_name.empty() ? "Actor" : entities[i].weapon_name,
							entities[i].screen_space.box_center,
							mathematics.calculate_distance(functions::get_centity(i)->pose.origin, functions::get_cg()->predictedPlayerState.origin),
							configs.color_entities.current.color,
							configs.color_entities_text.current.color,
							configs.color_entities_outline.current.color
						);
					} break;
					}
				}
			}
		}

		if (configs.esp_aim_pos.current.enabled && aimbot.aim_state.aim_target_acquired)
		{
			draw_aim_pos(aimbot.aim_state.aim_pos_screen, configs.color_aim_pos.current.color, configs.color_aim_pos_outline.current.color);
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_compass()
	{
		auto draw_compass_arrow = [&](std::int32_t index, ImVec4 col)
		{
			auto angle = (((functions::get_view_angles().y - functions::get_centity(index)->pose.angles.y) + 180.0f) / 360.0f - 0.25f) * pi_double;

			ImVec2 base_x(compass.arrow_size / -2.0f, 0.0f);
			ImVec2 base_y(compass.arrow_size / 2.0f, compass.arrow_size / 2.0f * -0.75f);
			ImVec2 base_z(compass.arrow_size / 2.0f, compass.arrow_size / 2.0f * +0.75f);

			auto final_x = compass.arrow_pos[index] + ImRotate(base_x, ImCos(angle), ImSin(angle));
			auto final_y = compass.arrow_pos[index] + ImRotate(base_y, ImCos(angle), ImSin(angle));
			auto final_z = compass.arrow_pos[index] + ImRotate(base_z, ImCos(angle), ImSin(angle));

			ImGui::GetWindowDrawList()->AddTriangleFilled(final_x, final_y, final_z, ImGui::GetColorU32({ col.x, col.y, col.z, col.w * 0.25f }));

			ImGui::GetWindowDrawList()->AddLine(final_x, final_y, ImGui::GetColorU32(col));
			ImGui::GetWindowDrawList()->AddLine(final_y, final_z, ImGui::GetColorU32(col));
			ImGui::GetWindowDrawList()->AddLine(final_z, final_x, ImGui::GetColorU32(col));
		};

		auto& io = ImGui::GetIO();

		if (configs.esp_compass.current.enabled && configs.esp_mode.current.integer > configs_c::esp_mode_off)
		{
			compass.compass_pos = io.DisplaySize / 2.0f;

			for (auto i = 0; i < max_clients; i++)
			{
				if (should_draw_index(i))
				{
					if (target_list.entity_is_valid(i))
					{
						draw_compass_arrow(i, entities[i].esp_color);
					}
				}
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_radar()
	{
		auto draw_radar_blip = [&](std::int32_t index, ImVec4 col)
		{
			ImGui::GetWindowDrawList()->AddCircleFilled(radar.blip_pos[index], radar.blip_size / 2.0f,
				ImGui::GetColorU32({ col.x, col.y, col.z, col.w * 0.25f }));

			ImGui::GetWindowDrawList()->AddCircle(radar.blip_pos[index], radar.blip_size / 2.0f,
				ImGui::GetColorU32(col));
		};

		if (configs.esp_radar.current.enabled && configs.esp_mode.current.integer > configs_c::esp_mode_off)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGuiCol_TitleBg);

			ImGui::SetNextWindowSize({ radar.radar_size, radar.radar_size });
			ImGui::Begin("##Radar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
			ImGui::GetWindowDrawList()->PushClipRectFullScreen();

			ImGui::PopStyleColor(1);

			radar.radar_pos =
			{
				ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2.0f,
				ImGui::GetWindowPos().y + ImGui::GetWindowSize().y / 2.0f
			};

			ImGui::GetWindowDrawList()->AddLine
			(
				{ radar.radar_pos.x - radar.radar_size / 2.0f + 1.0f, radar.radar_pos.y },
				{ radar.radar_pos.x + radar.radar_size / 2.0f - 1.0f, radar.radar_pos.y },
				ImGui::GetColorU32({ 0.50f, 0.50f, 0.50f, 0.50f })
			);

			ImGui::GetWindowDrawList()->AddLine
			(
				{ radar.radar_pos.x, radar.radar_pos.y - radar.radar_size / 2.0f },
				{ radar.radar_pos.x, radar.radar_pos.y + radar.radar_size / 2.0f - 1.0f },
				ImGui::GetColorU32({ 0.50f, 0.50f, 0.50f, 0.50f })
			);

			ImGui::GetWindowDrawList()->AddRectFilled
			(
				{ radar.radar_pos.x - 2.0f * main_gui.scaling_factor, radar.radar_pos.y - 2.0f * main_gui.scaling_factor },
				{ radar.radar_pos.x + 3.0f * main_gui.scaling_factor, radar.radar_pos.y + 3.0f * main_gui.scaling_factor },
				ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f })
			);
			
			for (auto i = 0; i < max_clients; i++)
			{
				if (should_draw_index(i))
				{
					if (target_list.entity_is_valid(i))
					{
						draw_radar_blip(i, entities[i].esp_color);
					}
				}
			}

			ImGui::End();
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_cross_hair()
	{
		auto& io = ImGui::GetIO();

		if (configs.esp_cross_hair.current.enabled)
		{
			if (!aimbot.aim_state.is_zooming)
			{
				ImGui::GetWindowDrawList()->AddLine
				(
					{ (io.DisplaySize.x / 2.0f) - (12.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (1.0f * main_gui.scaling_factor) },
					{ (io.DisplaySize.x / 2.0f) - (4.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (1.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(configs.color_cross_hair.current.color)
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ (io.DisplaySize.x / 2.0f) + (3.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (1.0f * main_gui.scaling_factor) },
					{ (io.DisplaySize.x / 2.0f) + (11.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (1.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(configs.color_cross_hair.current.color)
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ (io.DisplaySize.x / 2.0f) - (1.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (12.0f * main_gui.scaling_factor) },
					{ (io.DisplaySize.x / 2.0f) - (1.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) - (4.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(configs.color_cross_hair.current.color)
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ (io.DisplaySize.x / 2.0f) - (1.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) + (3.0f * main_gui.scaling_factor) },
					{ (io.DisplaySize.x / 2.0f) - (1.0f * main_gui.scaling_factor), (io.DisplaySize.y / 2.0f) + (11.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(configs.color_cross_hair.current.color)
				);
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_tracers()
	{
		for (auto& tracer : tracers)
		{
			if (tracer.world_to_screen_success)
			{
				ImGui::GetWindowDrawList()->AddLine
				(
					{ tracer.hit_pos_screen.x + (5.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (5.0f * main_gui.scaling_factor) },
					{ tracer.hit_pos_screen.x + (-5.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (-5.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(tracer.hit_outline_color),
					3.0f
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ tracer.hit_pos_screen.x + (5.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (-5.0f * main_gui.scaling_factor) },
					{ tracer.hit_pos_screen.x + (-5.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (5.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(tracer.hit_outline_color),
					3.0f
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ tracer.hit_pos_screen.x + (4.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (4.0f * main_gui.scaling_factor) },
					{ tracer.hit_pos_screen.x + (-4.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (-4.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(tracer.hit_color),
					1.0f
				);

				ImGui::GetWindowDrawList()->AddLine
				(
					{ tracer.hit_pos_screen.x + (4.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (-4.0f * main_gui.scaling_factor) },
					{ tracer.hit_pos_screen.x + (-4.0f * main_gui.scaling_factor), tracer.hit_pos_screen.y + (4.0f * main_gui.scaling_factor) },
					ImGui::GetColorU32(tracer.hit_color),
					1.0f
				);

				ImGui::GetWindowDrawList()->AddLine(tracer.start_pos_screen, tracer.hit_pos_screen, ImGui::GetColorU32(tracer.line_color), 1.0f);
			}
		}
	}
	/*
	//=====================================================================================
	*/
	void drawing_c::draw_threat_warning()
	{
		if (configs.esp_threat_warning.current.enabled)
		{
			if (aimbot.aim_state.aim_target_acquired)
			{
				ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetCurrentWindow()->Rect().Min, ImGui::GetCurrentWindow()->Rect().Max, ImGui::GetColorU32(configs.color_threat_warning.current.color));
			}
		}
	}
}

//=====================================================================================