//=====================================================================================

#pragma once

#include "Notifications/imgui_notify.h"

//=====================================================================================

namespace t7
{
	class logger
	{
	public:

		static logger& instance()
		{
			static logger inst;
			return inst;
		}

		std::vector<std::string> log_entries;

		template<typename... parameters>
		void add_entry(std::string line, parameters... params)
		{
			log_entries.push_back(niggerware::utils::string::va(line, params...));
			functions::write_log(line, params...);
		}

		void draw_menu_tab()
		{
			if (ImGui::BeginTabItem("Log"))
			{
				if (ImGui::ListBoxHeader("##log", ImGui::GetContentRegionAvail()))
				{
					for (auto& log_entry : log_entries)
					{
						ImGui::Selectable(log_entry.c_str(), false, ImGuiSelectableFlags_Disabled);
					}

					if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
					{
						ImGui::SetScrollHereY(1.0f);
					}

					ImGui::ListBoxFooter();
				}

				ImGui::EndTabItem();
			}
		}

	private:

		logger() = default;
		logger(const logger&) = default;
	};

	namespace notify
	{
		template<typename... parameters>
		static void error(std::string message, parameters... params)
		{
			ImGuiToast toast(ImGuiToastType_Error);

			toast.set_title("[ERROR]");
			toast.set_content(message.c_str(), params...);

			ImGui::InsertNotification(toast);
			logger::instance().add_entry("%s %s", toast.get_title(), toast.get_content());
		}

		template<typename... parameters>
		static void warning(std::string message, parameters... params)
		{
			ImGuiToast toast(ImGuiToastType_Warning);

			toast.set_title("[WARNING]");
			toast.set_content(message.c_str(), params...);

			ImGui::InsertNotification(toast);
			logger::instance().add_entry("%s %s", toast.get_title(), toast.get_content());
		}

		template<typename... parameters>
		static void info(std::string message, parameters... params)
		{
			ImGuiToast toast(ImGuiToastType_Info);

			toast.set_title("[INFO]");
			toast.set_content(message.c_str(), params...);

			ImGui::InsertNotification(toast);
			logger::instance().add_entry("%s %s", toast.get_title(), toast.get_content());
		}

		template<typename... parameters>
		static void success(std::string message, parameters... params)
		{
			ImGuiToast toast(ImGuiToastType_Success);

			toast.set_title("[SUCCESS]");
			toast.set_content(message.c_str(), params...);

			ImGui::InsertNotification(toast);
			logger::instance().add_entry("%s %s", toast.get_title(), toast.get_content());
		}

		template<typename... parameters>
		static void protection(std::string message, parameters... params)
		{
			ImGuiToast toast(ImGuiToastType_Success);

			toast.set_title("[PROTECTION]");
			toast.set_content(message.c_str(), params...);

			ImGui::InsertNotification(toast);
			logger::instance().add_entry("%s %s", toast.get_title(), toast.get_content());
		}
	}
}

//=====================================================================================