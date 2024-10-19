//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace t7
{
	license_c license;

	void license_c::auth_hwid()
	{
		VMProtectBegin("auth_hwid");

		while (true)
		{
			std::string line;
			std::stringstream stream;
			std::vector<std::string> lines;

			stream = niggerware::auth::network::https_request(vmpstr("https://auth.niggerb0t.com/clients/logins"));

			while (std::getline(stream, line))
			{
				lines.push_back(line);
			}

			auto is_authed = false;

			for (auto i{ 0u }; i + 1 < lines.size(); i++)
			{
				if (niggerware::auth::crypto::decrypt(lines[i + 1]) == niggerware::auth::hwid::get())
				{
					if (auto pos{ lines[i].find(':') }; pos != std::string::npos)
					{
						auto cheats_str = lines[i].substr(pos + 1);
						auto cheats_vec = niggerware::utils::string::tokenize(niggerware::utils::string::find_and_erase(cheats_str, " "), ',');

						if (std::find(cheats_vec.begin(), cheats_vec.end(), vmpstr("t7")) != cheats_vec.end())
						{
							is_authed = true;
						}

						else if (std::find(cheats_vec.begin(), cheats_vec.end(), vmpstr("all")) != cheats_vec.end())
						{
							is_authed = true;
						}
					}
				}
			}

			lines.clear();

			if (!is_authed)
			{
				std::abort();
			}

			std::this_thread::sleep_for(60s);
		}

		VMProtectEnd();
	}
}

//=====================================================================================