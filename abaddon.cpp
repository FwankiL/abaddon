#include <gtkmm.h>
#include <memory>
#include <string>
#include <algorithm>
#include "discord/discord.hpp"
#include "dialogs/token.hpp"
#include "abaddon.hpp"

#ifdef _WIN32
    #pragma comment(lib, "crypt32.lib")
#endif

Abaddon::Abaddon()
    : m_settings("abaddon.ini") {
    m_discord.SetAbaddon(this);
    LoadFromSettings();
}

Abaddon::~Abaddon() {
    m_settings.Close();
    m_discord.Stop();
}

int Abaddon::StartGTK() {
    m_gtk_app = Gtk::Application::create("com.github.lorpus.abaddon");

    m_main_window = std::make_unique<MainWindow>();
    m_main_window->SetAbaddon(this);
    m_main_window->set_title("Abaddon");
    m_main_window->show();
    m_main_window->UpdateComponents();

    m_gtk_app->signal_shutdown().connect([&]() {
        StopDiscord();
    });

    if (!m_settings.IsValid()) {
        Gtk::MessageDialog dlg(*m_main_window, "The settings file could not be created!", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dlg.run();
    }

    return m_gtk_app->run(*m_main_window);
}

void Abaddon::LoadFromSettings() {
    std::string token = m_settings.GetSetting("discord", "token");
    if (token.size()) {
        m_discord_token = token;
        m_discord.UpdateToken(m_discord_token);
    }
}

void Abaddon::StartDiscord() {
    m_discord.Start();
}

void Abaddon::StopDiscord() {
    m_discord.Stop();
}

bool Abaddon::IsDiscordActive() const {
    return m_discord.IsStarted();
}

std::string Abaddon::GetDiscordToken() const {
    return m_discord_token;
}

const DiscordClient &Abaddon::GetDiscordClient() const {
    std::scoped_lock<std::mutex> guard(m_mutex);
    return m_discord;
}

void Abaddon::DiscordNotifyReady() {
    m_main_window->UpdateComponents();
}

void Abaddon::DiscordNotifyChannelListFullRefresh() {
    m_main_window->UpdateChannelListing();
}

void Abaddon::DiscordNotifyMessageCreate(Snowflake id) {
    m_main_window->UpdateChatNewMessage(id);
}

void Abaddon::ActionConnect() {
    if (!m_discord.IsStarted())
        StartDiscord();
    m_main_window->UpdateComponents();
}

void Abaddon::ActionDisconnect() {
    if (m_discord.IsStarted())
        StopDiscord();
    m_main_window->UpdateComponents();
}

void Abaddon::ActionSetToken() {
    TokenDialog dlg(*m_main_window);
    auto response = dlg.run();
    if (response == Gtk::RESPONSE_OK) {
        m_discord_token = dlg.GetToken();
        m_discord.UpdateToken(m_discord_token);
        m_main_window->UpdateComponents();
        m_settings.SetSetting("discord", "token", m_discord_token);
    }
}

void Abaddon::ActionMoveGuildUp(Snowflake id) {
    auto order = m_discord.GetUserSortedGuilds();
    // get iter to target
    decltype(order)::iterator target_iter;
    for (auto it = order.begin(); it != order.end(); it++) {
        if (it->first == id) {
            target_iter = it;
            break;
        }
    }

    decltype(order)::iterator left = target_iter - 1;
    std::swap(*left, *target_iter);

    std::vector<Snowflake> new_sort;
    for (const auto &x : order)
        new_sort.push_back(x.first);

    m_discord.UpdateSettingsGuildPositions(new_sort);
}

void Abaddon::ActionMoveGuildDown(Snowflake id) {
    auto order = m_discord.GetUserSortedGuilds();
    // get iter to target
    decltype(order)::iterator target_iter;
    for (auto it = order.begin(); it != order.end(); it++) {
        if (it->first == id) {
            target_iter = it;
            break;
        }
    }

    decltype(order)::iterator right = target_iter + 1;
    std::swap(*right, *target_iter);

    std::vector<Snowflake> new_sort;
    for (const auto &x : order)
        new_sort.push_back(x.first);

    m_discord.UpdateSettingsGuildPositions(new_sort);
}

void Abaddon::ActionCopyGuildID(Snowflake id) {
    Gtk::Clipboard::get()->set_text(std::to_string(id));
}

void Abaddon::ActionListChannelItemClick(Snowflake id) {
    m_main_window->UpdateChatActiveChannel(id);
    if (m_channels_requested.find(id) == m_channels_requested.end()) {
        m_discord.FetchMessagesInChannel(id, [this, id](const std::vector<MessageData> &msgs) {
            if (msgs.size() > 0) {
                m_oldest_listed_message[id] = msgs.back().ID;
                m_main_window->UpdateChatWindowContents();
            }

            m_channels_requested.insert(id);
        });
    } else {
        m_main_window->UpdateChatWindowContents();
    }
}

void Abaddon::ActionChatLoadHistory(Snowflake id) {
    if (m_channels_history_loaded.find(id) != m_channels_history_loaded.end())
        return;

    if (m_channels_history_loading.find(id) != m_channels_history_loading.end())
        return;

    m_channels_history_loading.insert(id);

    m_discord.FetchMessagesInChannelBefore(id, m_oldest_listed_message[id], [this, id](const std::vector<MessageData> &msgs) {
        m_channels_history_loading.erase(id);

        if (msgs.size() == 0) {
            m_channels_history_loaded.insert(id);
        } else {
            m_oldest_listed_message[id] = msgs.back().ID;
            m_main_window->UpdateChatPrependHistory(msgs);
        }
    });
}

void Abaddon::ActionChatInputSubmit(std::string msg, Snowflake channel) {
    m_discord.SendChatMessage(msg, channel);
}

int main(int argc, char **argv) {
    Gtk::Main::init_gtkmm_internals(); // why???
    Abaddon abaddon;
    return abaddon.StartGTK();
}