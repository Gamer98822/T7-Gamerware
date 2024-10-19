//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	mathematics_c mathematics;

	std::float_t mathematics_c::calculate_fov(ImVec3 start, ImVec3 end, ImVec3 angles)
	{
		auto dir = start - end;
		ImVec3 aim_angles;

		vector_normalize(&dir);
		vec_to_angles(dir, &aim_angles);

		make_vector(angles, &angles);
		make_vector(aim_angles, &aim_angles);

		auto length = vector_length(angles);
		auto product = dot_product(angles, aim_angles);

		std::float_t result = radians_to_degrees(std::acosf(product / std::powf(length, 2.0f)));

		if (std::isnan(result))
			result = 0.0f;

		return result;
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::dot_product(ImVec2 vec)
	{
		return (vec.x * vec.x + vec.y * vec.y);
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::dot_product(ImVec2 lhs, ImVec2 rhs)
	{
		return (lhs.x * rhs.x + lhs.y * rhs.y);
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::dot_product(ImVec3 vec)
	{
		return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::dot_product(ImVec3 lhs, ImVec3 rhs)
	{
		return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::vector_length(ImVec2 vec)
	{
		return std::sqrtf(dot_product(vec));
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::vector_length(ImVec2 lhs, ImVec2 rhs)
	{
		return std::sqrtf(dot_product(lhs, rhs));
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::vector_length(ImVec3 vec)
	{
		return std::sqrtf(dot_product(vec));
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::vector_length(ImVec3 lhs, ImVec3 rhs)
	{
		return std::sqrtf(dot_product(lhs, rhs));
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::calculate_distance(ImVec3 end, ImVec3 start)
	{
		auto dir = end - start;

		return vector_length(dir);
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::calculate_distance(ImVec2 end, ImVec2 start)
	{
		auto dir = end - start;

		return vector_length(dir);
	}
	/*
	//=====================================================================================
	*/
	ImVec3 mathematics_c::angle_to_forward(ImVec3 position, ImVec3 angles, std::float_t distance)
	{
		ImVec3 forward;

		angle_vectors(angles, &forward, nullptr, nullptr);

		return (position + (forward * distance));
	}
	/*
	//=====================================================================================
	*/
	ImVec3 mathematics_c::angle_to_right(ImVec3 position, ImVec3 angles, std::float_t distance)
	{
		ImVec3 right;

		angle_vectors(angles, nullptr, &right, nullptr);

		return (position + (right * distance));
	}
	/*
	//=====================================================================================
	*/
	ImVec3 mathematics_c::angle_to_up(ImVec3 position, ImVec3 angles, std::float_t distance)
	{
		ImVec3 up;

		angle_vectors(angles, nullptr, nullptr, &up);

		return (position + (up * distance));
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::vec_to_angles(ImVec3 direction, ImVec3* angles)
	{
		std::float_t temp, yaw, pitch;

		if (direction.x == 0.0f && direction.y == 0.0f)
		{
			yaw = 0.0f;

			if (direction.z > 0.0f)
				pitch = 90.0f;

			else
				pitch = 270.0f;
		}

		else
		{
			yaw = radians_to_degrees(std::atan2f(direction.y, direction.x));

			if (yaw < 0.0f)
				yaw += 360.0f;

			temp = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
			pitch = radians_to_degrees(std::atan2f(direction.z, temp));

			if (pitch < 0.0f)
				pitch += 360.0f;
		}

		angles->x = -pitch;
		angles->y = yaw;
		angles->z = 0.0f;
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::angles_to_axis(ImVec3 angles, ImVec3 axis[3])
	{
		std::float_t angle, sin_pitch, sin_yaw, sin_roll, cos_pitch, cos_yaw, cos_roll;

		angle = degrees_to_radians(angles.x);
		sin_pitch = std::sinf(angle);
		cos_pitch = std::cosf(angle);

		angle = degrees_to_radians(angles.y);
		sin_yaw = std::sinf(angle);
		cos_yaw = std::cosf(angle);

		angle = degrees_to_radians(angles.z);
		sin_roll = std::sinf(angle);
		cos_roll = std::cosf(angle);

		axis[0].x = cos_pitch * cos_yaw;
		axis[0].y = cos_pitch * sin_yaw;
		axis[0].z = -sin_pitch;

		axis[1].x = (-1.0f * sin_roll * sin_pitch * cos_yaw + -1.0f * cos_roll * -sin_yaw);
		axis[1].y = (-1.0f * sin_roll * sin_pitch * sin_yaw + -1.0f * cos_roll * cos_yaw);
		axis[1].z = -1.0f * sin_roll * cos_pitch;

		axis[2].x = (cos_roll * sin_pitch * cos_yaw + -sin_roll * -sin_yaw);
		axis[2].y = (cos_roll * sin_pitch * sin_yaw + -sin_roll * cos_yaw);
		axis[2].z = cos_roll * cos_pitch;
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::angle_vectors(ImVec3 angles, ImVec3* forward, ImVec3* right, ImVec3* up)
	{
		std::float_t angle, sin_pitch, sin_yaw, sin_roll, cos_pitch, cos_yaw, cos_roll;

		angle = degrees_to_radians(angles.x);
		sin_pitch = std::sinf(angle);
		cos_pitch = std::cosf(angle);

		angle = degrees_to_radians(angles.y);
		sin_yaw = std::sinf(angle);
		cos_yaw = std::cosf(angle);

		angle = degrees_to_radians(angles.z);
		sin_roll = std::sinf(angle);
		cos_roll = std::cosf(angle);

		if (forward)
		{
			forward->x = cos_pitch * cos_yaw;
			forward->y = cos_pitch * sin_yaw;
			forward->z = -sin_pitch;
		}

		if (right)
		{
			right->x = (-1.0f * sin_roll * sin_pitch * cos_yaw + -1.0f * cos_roll * -sin_yaw);
			right->y = (-1.0f * sin_roll * sin_pitch * sin_yaw + -1.0f * cos_roll * cos_yaw);
			right->z = -1.0f * sin_roll * cos_pitch;
		}

		if (up)
		{
			up->x = (cos_roll * sin_pitch * cos_yaw + -sin_roll * -sin_yaw);
			up->y = (cos_roll * sin_pitch * sin_yaw + -sin_roll * cos_yaw);
			up->z = cos_roll * cos_pitch;
		}
	}
	/*
	//=====================================================================================
	*/
	std::float_t mathematics_c::vector_normalize(ImVec3* direction)
	{
		auto length = vector_length(*direction);
		auto result = length;

		if (-length >= 0.0f)
			length = 1.0f;

		direction->x *= 1.0f / length;
		direction->y *= 1.0f / length;
		direction->z *= 1.0f / length;

		return result;
	}
	/*
	//=====================================================================================
	*/
	ImVec3 mathematics_c::clamp_angles(ImVec3 angles)
	{
		if (angles.x > 180.0f)
			angles.x -= 360.0f;

		if (angles.x < -180.0f)
			angles.x += 360.0f;

		if (angles.y > 180.0f)
			angles.y -= 360.0f;

		if (angles.y < -180.0f)
			angles.y += 360.0f;

		if (angles.z != 0.0f)
			angles.z = 0.0f;

		return angles;
	}
	/*
	//=====================================================================================
	*/
	char mathematics_c::clamp_move(std::int32_t move)
	{
		if (move < -128)
			move = -128;

		if (move > 127)
			move = 127;

		return move;
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::calculate_aim_angles(ImVec3 start, ImVec3 end, ImVec3* angles)
	{
		auto dir = start - end;

		vector_normalize(&dir);
		vec_to_angles(dir, angles);

		*angles = clamp_angles(*angles);
		*angles -= functions::get_view_angles();
		*angles = clamp_angles(*angles);
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::calculate_anti_aim_angles(ImVec3 start, ImVec3 end, ImVec3* angles)
	{
		auto direction = start - end;

		vector_normalize(&direction);
		vec_to_angles(direction, angles);

		*angles = clamp_angles(*angles);

		angles->x = configs.anti_aim_shield_pitch_shift.current.value - angles->x;
		angles->y = configs.anti_aim_shield_yaw_shift.current.value + angles->y - 180.0f;

		*angles -= functions::get_cg()->predictedPlayerState.deltaAngles;
		*angles = clamp_angles(*angles);
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::make_vector(ImVec3 angles, ImVec3* out)
	{
		auto up = degrees_to_radians(angles.x);
		auto right = degrees_to_radians(angles.y);

		out->x = -std::cosf(up) * -std::cosf(right);
		out->y = std::sinf(right) * std::cosf(up);
		out->z = -std::sinf(up);
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::movement_fix(structures::usercmd_s* usercmd, std::float_t oldyaw, std::float_t newyaw, std::float_t forward, std::float_t right)
	{
		auto delta = degrees_to_radians(oldyaw - newyaw);

		usercmd->forwardMove = clamp_move(std::stcast<std::int32_t>(std::cosf(delta) * forward - std::sinf(delta) * right));
		usercmd->rightMove = clamp_move(std::stcast<std::int32_t>(std::sinf(delta) * forward + std::cosf(delta) * right));
	}
	/*
	//=====================================================================================
	*/
	bool mathematics_c::world_to_screen(ImVec3 world, ImVec2* screen)
	{
		auto screen_placement = functions::ScrPlace_GetView(structures::LOCAL_CLIENT_FIRST);

		ImVec3 dir(world - functions::get_cg()->refDef.viewOrigin);
		ImVec3 proj
		(
			dot_product(dir, functions::get_cg()->refDef.viewAxis[0]),
			dot_product(dir, functions::get_cg()->refDef.viewAxis[1]),
			dot_product(dir, functions::get_cg()->refDef.viewAxis[2])
		);

		if (proj.x >= 0.0f)
		{
			*screen = ImVec2
			(
				((1.0f - ((proj.y / functions::get_cg()->refDef.fovX) * (1.0f / proj.x))) * (screen_placement->realViewportSize.x / 2.0f)) + screen_placement->realViewportBase.x,
				((1.0f - ((proj.z / functions::get_cg()->refDef.fovY) * (1.0f / proj.x))) * (screen_placement->realViewportSize.y / 2.0f)) + screen_placement->realViewportBase.y
			);

			return true;
		}

		else
		{
			*screen = ImVec2(-proj.y, -proj.z);

			if (std::abs(screen->x) < 0.001f)
			{
				if (std::abs(screen->y) < 0.001f)
				{
					screen->y = screen_placement->realViewportSize.y * 2.0f;

					return false;
				}

				screen->x = 0.001f;
			}

			if (std::abs(screen->y) < 0.001f)
				screen->y = 0.001f;

			while (screen_placement->realViewportSize.x > std::abs(screen->x))
			{
				screen->x *= screen_placement->realViewportSize.x;
				screen->y *= screen_placement->realViewportSize.x;
			}

			while (screen_placement->realViewportSize.y > std::abs(screen->y))
			{
				screen->x *= screen_placement->realViewportSize.y;
				screen->y *= screen_placement->realViewportSize.y;
			}

			return false;
		}
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::world_to_compass(ImVec3 world, ImVec2 compasspos, std::float_t compasssize, ImVec2* screen)
	{
		auto dir = functions::get_view_origin() - world;

		ImVec3 angles;

		vector_normalize(&dir);
		vec_to_angles(dir, &angles);

		angles = functions::get_view_angles() - angles;
		angles = clamp_angles(angles);

		auto angle = ((angles.y + 180.0f) / 360.0f - 0.25f) * pi_double;

		screen->x = compasspos.x + (std::cosf(angle) * (compasssize / 2.0f));
		screen->y = compasspos.y + (std::sinf(angle) * (compasssize / 2.0f));
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::world_to_radar(ImVec3 world, ImVec2 radarpos, std::float_t scale, std::float_t radarsize, std::float_t blipsize, ImVec2* screen)
	{
		ImVec2 delta, location;

		auto angle_cos = std::cosf(degrees_to_radians(functions::get_view_angles().y));
		auto angle_sin = std::sinf(degrees_to_radians(functions::get_view_angles().y));

		delta.x = world.x - functions::get_view_origin().x;
		delta.y = world.y - functions::get_view_origin().y;

		location.x = (delta.y * angle_cos - delta.x * angle_sin) / scale;
		location.y = (delta.x * angle_cos + delta.y * angle_sin) / scale;

		if (location.x < -(radarsize / 2.0f - blipsize / 2.0f - 1.0f))
			location.x = -(radarsize / 2.0f - blipsize / 2.0f - 1.0f);

		else if (location.x > (radarsize / 2.0f - blipsize / 2.0f - 1.0f))
			location.x = (radarsize / 2.0f - blipsize / 2.0f - 1.0f);

		if (location.y < -(radarsize / 2.0f - blipsize / 2.0f - 1.0f))
			location.y = -(radarsize / 2.0f - blipsize / 2.0f - 1.0f);

		else if (location.y > (radarsize / 2.0f - blipsize / 2.0f))
			location.y = (radarsize / 2.0f - blipsize / 2.0f);

		*screen = (location * -1.0f) + radarpos;
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::setup_box(ImVec3 corners[8], ImVec3 mins, ImVec3 maxs)
	{
		corners[0] = { mins.x, mins.y, mins.z };
		corners[1] = { maxs.x, mins.y, mins.z };
		corners[2] = { mins.x, maxs.y, mins.z };
		corners[3] = { maxs.x, maxs.y, mins.z };
		corners[4] = { mins.x, mins.y, maxs.z };
		corners[5] = { maxs.x, mins.y, maxs.z };
		corners[6] = { mins.x, maxs.y, maxs.z };
		corners[7] = { maxs.x, maxs.y, maxs.z };
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::get_box_center(ImVec3 corners[8], ImVec3* center)
	{
		ImVec3 min_temp =
		{
			std::numeric_limits<std::float_t>::max(),
			std::numeric_limits<std::float_t>::max(),
			std::numeric_limits<std::float_t>::max()
		}, max_temp =
		{
			-std::numeric_limits<std::float_t>::max(),
			-std::numeric_limits<std::float_t>::max(),
			-std::numeric_limits<std::float_t>::max()
		};


		for (auto i = 0; i < 8; i++)
		{
			if (corners[i].x < min_temp.x)
				min_temp.x = corners[i].x;

			if (corners[i].x > max_temp.x)
				max_temp.x = corners[i].x;

			if (corners[i].y < min_temp.y)
				min_temp.y = corners[i].y;

			if (corners[i].y > max_temp.y)
				max_temp.y = corners[i].y;

			if (corners[i].z < min_temp.z)
				min_temp.z = corners[i].z;

			if (corners[i].z > max_temp.z)
				max_temp.z = corners[i].z;
		}

		*center = (min_temp + max_temp) / 2.0f;
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::rotate_box(ImVec3 corners[8], ImVec3 axis[3], ImVec3 origin, ImVec3 mins, ImVec3 maxs)
	{
		corners[0] = origin + (axis[0] * mins.x + axis[1] * mins.y + axis[2] * mins.z);
		corners[1] = origin + (axis[0] * maxs.x + axis[1] * mins.y + axis[2] * mins.z);
		corners[2] = origin + (axis[0] * mins.x + axis[1] * maxs.y + axis[2] * mins.z);
		corners[3] = origin + (axis[0] * maxs.x + axis[1] * maxs.y + axis[2] * mins.z);
		corners[4] = origin + (axis[0] * mins.x + axis[1] * mins.y + axis[2] * maxs.z);
		corners[5] = origin + (axis[0] * maxs.x + axis[1] * mins.y + axis[2] * maxs.z);
		corners[6] = origin + (axis[0] * mins.x + axis[1] * maxs.y + axis[2] * maxs.z);
		corners[7] = origin + (axis[0] * maxs.x + axis[1] * maxs.y + axis[2] * maxs.z);
	}
	/*
	//=====================================================================================
	*/
	void mathematics_c::rotate_point_yaw(ImVec3 point, ImVec3 center, std::float_t yaw, ImVec3* out)
	{
		ImVec2 delta;

		auto angle_cos = std::cosf(((-yaw + 180.0f) / 360.0f - 0.25f) * pi_double);
		auto angle_sin = std::sinf(((-yaw + 180.0f) / 360.0f - 0.25f) * pi_double);

		delta.x = point.x - center.x;
		delta.y = point.y - center.y;

		out->x = center.x + angle_sin * delta.x - angle_cos * delta.y;
		out->y = center.y + angle_cos * delta.x + angle_sin * delta.y;
		out->z = point.z;
	}
}

//=====================================================================================