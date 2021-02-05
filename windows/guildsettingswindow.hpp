#pragma once
#include <gtkmm.h>
#include "../discord/snowflake.hpp"
#include "guildsettings/infopane.hpp"
#include "guildsettings/banspane.hpp"
#include "guildsettings/invitespane.hpp"
#include "guildsettings/auditlogpane.hpp"

class GuildSettingsWindow : public Gtk::Window {
public:
    GuildSettingsWindow(Snowflake id);

protected:
    void on_hide() override;

private:
    Gtk::Box m_main;
    Gtk::Stack m_stack;
    Gtk::StackSwitcher m_switcher;

    GuildSettingsInfoPane m_pane_info;
    GuildSettingsBansPane m_pane_bans;
    GuildSettingsInvitesPane m_pane_invites;
    GuildSettingsAuditLogPane m_pane_audit_log;

    Snowflake GuildID;
};