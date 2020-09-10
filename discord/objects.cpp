#include "objects.hpp"

#define JS_D(k, t)         \
    do {                   \
        j.at(k).get_to(t); \
    } while (0)

#define JS_O(k, t)                            \
    do {                                      \
        if (j.contains(k)) j.at(k).get_to(t); \
    } while (0)

#define JS_N(k, t)                                 \
    do {                                           \
        if (!j.at(k).is_null()) j.at(k).get_to(t); \
    } while (0)

#define JS_ON(k, t)                              \
    do {                                         \
        if (j.contains(k) && !j.at(k).is_null()) \
            j.at(k).get_to(t);                   \
    } while (0)

void from_json(const nlohmann::json &j, GatewayMessage &m) {
    JS_D("op", m.Opcode);
    m.Data = j.at("d");

    JS_ON("t", m.Type);
}

void from_json(const nlohmann::json &j, HelloMessageData &m) {
    JS_D("heartbeat_interval", m.HeartbeatInterval);
}

void from_json(const nlohmann::json &j, RoleData &m) {
    JS_D("id", m.ID);
    JS_D("name", m.Name);
    JS_D("color", m.Color);
    JS_D("hoist", m.IsHoisted);
    JS_D("position", m.Position);
    JS_D("permissions", m.PermissionsLegacy);
    std::string tmp;
    JS_D("permissions_new", tmp);
    m.Permissions = std::stoull(tmp);
    JS_D("managed", m.IsManaged);
    JS_D("mentionable", m.IsMentionable);
}

void from_json(const nlohmann::json &j, UserData &m) {
    JS_D("id", m.ID);
    JS_D("username", m.Username);
    JS_D("discriminator", m.Discriminator);
    JS_N("avatar", m.Avatar);
    JS_O("bot", m.IsBot);
    JS_O("system", m.IsSystem);
    JS_O("mfa_enabled", m.IsMFAEnabled);
    JS_O("locale", m.Locale);
    JS_O("verified", m.IsVerified);
    JS_O("email", m.Email);
    JS_O("flags", m.Flags);
    JS_ON("premium_type", m.PremiumType);
    JS_O("public_flags", m.PublicFlags);
    JS_O("desktop", m.IsDesktop);
    JS_O("mobile", m.IsMobile);
    JS_ON("nsfw_allowed", m.IsNSFWAllowed);
    JS_ON("phone", m.Phone);
}

void from_json(const nlohmann::json &j, GuildMemberData &m) {
    JS_O("user", m.User);
    JS_ON("nick", m.Nickname);
    JS_D("roles", m.Roles);
    JS_D("joined_at", m.JoinedAt);
    JS_ON("premium_since", m.PremiumSince);
    JS_D("deaf", m.IsDeafened);
    JS_D("mute", m.IsMuted);
}

void from_json(const nlohmann::json &j, GuildData &m) {
    JS_D("id", m.ID);
    if (j.contains("unavailable")) {
        m.IsUnavailable = true;
        return;
    }

    JS_D("name", m.Name);
    JS_N("icon", m.Icon);
    JS_N("splash", m.Splash);
    JS_ON("discovery_splash", m.DiscoverySplash);
    JS_O("owner", m.IsOwner);
    JS_D("owner_id", m.OwnerID);
    JS_O("permissions", m.Permissions);
    JS_O("permissions_new", m.PermissionsNew);
    JS_D("region", m.VoiceRegion);
    JS_N("afk_channel_id", m.AFKChannelID);
    JS_D("afk_timeout", m.AFKTimeout);
    JS_O("embed_enabled", m.IsEmbedEnabled);
    JS_ON("embed_channel_id", m.EmbedChannelID);
    JS_D("verification_level", m.VerificationLevel);
    JS_D("default_message_notifications", m.DefaultMessageNotifications);
    JS_D("explicit_content_filter", m.ExplicitContentFilter);
    JS_D("roles", m.Roles);
    // JS_D("emojis", m.Emojis);
    JS_D("features", m.Features);
    JS_D("mfa_level", m.MFALevel);
    JS_N("application_id", m.ApplicationID);
    JS_O("widget_enabled", m.IsWidgetEnabled);
    JS_ON("widget_channel_id", m.WidgetChannelID);
    JS_N("system_channel_id", m.SystemChannelID);
    JS_D("system_channel_flags", m.SystemChannelFlags);
    JS_N("rules_channel_id", m.RulesChannelID);
    JS_O("joined_at", m.JoinedAt);
    JS_O("large", m.IsLarge);
    JS_O("unavailable", m.IsUnavailable);
    JS_O("member_count", m.MemberCount);
    // JS_O("voice_states", m.VoiceStates);
    // JS_O("members", m.Members);
    JS_O("channels", m.Channels);
    // JS_O("presences", m.Presences);
    JS_ON("max_presences", m.MaxPresences);
    JS_O("max_members", m.MaxMembers);
    JS_N("vanity_url_code", m.VanityURL);
    JS_N("description", m.Description);
    JS_N("banner", m.BannerHash);
    JS_D("premium_tier", m.PremiumTier);
    JS_O("premium_subscription_count", m.PremiumSubscriptionCount);
    JS_D("preferred_locale", m.PreferredLocale);
    JS_N("public_updates_channel_id", m.PublicUpdatesChannelID);
    JS_O("max_video_channel_users", m.MaxVideoChannelUsers);
    JS_O("approximate_member_count", m.ApproximateMemberCount);
    JS_O("approximate_presence_count", m.ApproximatePresenceCount);
}

void from_json(const nlohmann::json &j, ChannelData &m) {
    JS_D("id", m.ID);
    JS_D("type", m.Type);
    JS_O("guild_id", m.GuildID);
    JS_O("position", m.Position);
    // JS_O("permission_overwrites", m.PermissionOverwrites);
    JS_ON("name", m.Name);
    JS_ON("topic", m.Topic);
    JS_O("nsfw", m.IsNSFW);
    JS_ON("last_message_id", m.LastMessageID);
    JS_O("bitrate", m.Bitrate);
    JS_O("user_limit", m.UserLimit);
    JS_O("rate_limit_per_user", m.RateLimitPerUser);
    JS_O("recipients", m.Recipients);
    JS_ON("icon", m.Icon);
    JS_O("owner_id", m.OwnerID);
    JS_O("application_id", m.ApplicationID);
    JS_ON("parent_id", m.ParentID);
    JS_ON("last_pin_timestamp", m.LastPinTimestamp);
}

void from_json(const nlohmann::json &j, MessageData &m) {
    JS_D("id", m.ID);
    JS_D("channel_id", m.ChannelID);
    JS_O("guild_id", m.GuildID);
    JS_D("author", m.Author);
    // JS_O("member", m.Member);
    JS_D("content", m.Content);
    JS_D("timestamp", m.Timestamp);
    JS_N("edited_timestamp", m.EditedTimestamp);
    JS_D("tts", m.IsTTS);
    JS_D("mention_everyone", m.DoesMentionEveryone);
    JS_D("mentions", m.Mentions);
    // JS_D("mention_roles", m.MentionRoles);
    // JS_O("mention_channels", m.MentionChannels);
    // JS_D("attachments", m.Attachments);
    JS_D("embeds", m.Embeds);
    // JS_O("reactions", m.Reactions);
    JS_O("nonce", m.Nonce);
    JS_D("pinned", m.IsPinned);
    JS_O("webhook_id", m.WebhookID);
    JS_D("type", m.Type);
    // JS_O("activity", m.Activity);
    // JS_O("application", m.Application);
    // JS_O("message_reference", m.MessageReference);
    JS_O("flags", m.Flags);
}

// probably gonna need to return present keys
void MessageData::from_json_edited(const nlohmann::json &j) {
    JS_D("id", ID);
    JS_D("channel_id", ChannelID);
    JS_O("guild_id", GuildID);
    JS_O("author", Author);
    JS_O("content", Content);
    JS_O("timestamp", Timestamp);
    JS_ON("edited_timestamp", EditedTimestamp);
    JS_O("tts", IsTTS);
    JS_O("mention_everyone", DoesMentionEveryone);
    JS_O("mentions", Mentions);
    JS_O("nonce", Nonce);
    JS_O("pinned", IsPinned);
    JS_O("webhook_id", WebhookID);
    JS_O("type", Type);
    JS_O("flags", Flags);
}

void from_json(const nlohmann::json &j, MessageDeleteData &m) {
    JS_D("id", m.ID);
    JS_D("channel_id", m.ChannelID);
    JS_O("guild_id", m.GuildID);
}

void from_json(const nlohmann::json &j, GuildMemberListUpdateMessage::GroupItem &m) {
    m.Type = "group";
    JS_D("id", m.ID);
    JS_D("count", m.Count);
}

GuildMemberData GuildMemberListUpdateMessage::MemberItem::GetAsMemberData() const {
    return m_member_data;
}

void from_json(const nlohmann::json &j, GuildMemberListUpdateMessage::MemberItem &m) {
    m.Type = "member";
    JS_D("user", m.User);
    JS_D("roles", m.Roles);
    JS_D("mute", m.IsMuted);
    JS_D("joined_at", m.JoinedAt);
    JS_D("deaf", m.IsDefeaned);
    JS_N("hoisted_role", m.HoistedRole);
    JS_ON("premium_since", m.PremiumSince);
    JS_ON("nick", m.Nickname);
    m.m_member_data = j;
}

void from_json(const nlohmann::json &j, GuildMemberListUpdateMessage::OpObject &m) {
    JS_D("op", m.Op);
    if (m.Op == "SYNC") {
        JS_D("range", m.Range);
        for (const auto &ij : j.at("items")) {
            if (ij.contains("group"))
                m.Items.push_back(std::make_unique<GuildMemberListUpdateMessage::GroupItem>(ij.at("group")));
            else if (ij.contains("member"))
                m.Items.push_back(std::make_unique<GuildMemberListUpdateMessage::MemberItem>(ij.at("member")));
        }
    }
}

void from_json(const nlohmann::json &j, GuildMemberListUpdateMessage &m) {
    JS_D("online_count", m.OnlineCount);
    JS_D("member_count", m.MemberCount);
    JS_D("id", m.ListIDHash);
    JS_D("guild_id", m.GuildID);
    JS_D("groups", m.Groups);
    JS_D("ops", m.Ops);
}

void to_json(nlohmann::json &j, const LazyLoadRequestMessage &m) {
    j["op"] = GatewayOp::LazyLoadRequest;
    j["d"] = nlohmann::json::object();
    j["d"]["guild_id"] = m.GuildID;
    j["d"]["channels"] = nlohmann::json::object();
    for (const auto &[key, chans] : m.Channels) { // apparently a map gets written as a list
        j["d"]["channels"][std::to_string(key)] = chans;
    }
    j["d"]["typing"] = m.ShouldGetTyping;
    j["d"]["activities"] = m.ShouldGetActivities;
    if (m.Members.size() > 0)
        j["d"]["members"] = m.Members;
}

void from_json(const nlohmann::json &j, ReadyEventData &m) {
    JS_D("v", m.GatewayVersion);
    JS_D("user", m.User);
    JS_D("guilds", m.Guilds);
    JS_D("session_id", m.SessionID);
    JS_D("analytics_token", m.AnalyticsToken);
    JS_D("friend_suggestion_count", m.FriendSuggestionCount);
    JS_D("user_settings", m.UserSettings);
    JS_D("private_channels", m.PrivateChannels);
}

void from_json(const nlohmann::json &j, UserSettingsData &m) {
    JS_D("timezone_offset", m.TimezoneOffset);
    JS_D("theme", m.Theme);
    JS_D("stream_notifications_enabled", m.AreStreamNotificationsEnabled);
    JS_D("status", m.Status);
    JS_D("show_current_game", m.ShouldShowCurrentGame);
    // JS_D("restricted_guilds", m.RestrictedGuilds);
    JS_D("render_reactions", m.ShouldRenderReactions);
    JS_D("render_embeds", m.ShouldRenderEmbeds);
    JS_D("native_phone_integration_enabled", m.IsNativePhoneIntegrationEnabled);
    JS_D("message_display_compact", m.ShouldMessageDisplayCompact);
    JS_D("locale", m.Locale);
    JS_D("inline_embed_media", m.ShouldInlineEmbedMedia);
    JS_D("inline_attachment_media", m.ShouldInlineAttachmentMedia);
    JS_D("guild_positions", m.GuildPositions);
    // JS_D("guild_folders", m.GuildFolders);
    JS_D("gif_auto_play", m.ShouldGIFAutoplay);
    // JS_D("friend_source_flags", m.FriendSourceFlags);
    JS_D("explicit_content_filter", m.ExplicitContentFilter);
    JS_D("enable_tts_command", m.IsTTSCommandEnabled);
    JS_D("disable_games_tab", m.ShouldDisableGamesTab);
    JS_D("developer_mode", m.DeveloperMode);
    JS_D("detect_platform_accounts", m.ShouldDetectPlatformAccounts);
    JS_D("default_guilds_restricted", m.AreDefaultGuildsRestricted);
    // JS_N("custom_status", m.CustomStatus);
    JS_D("convert_emoticons", m.ShouldConvertEmoticons);
    JS_D("contact_sync_enabled", m.IsContactSyncEnabled);
    JS_D("animate_emoji", m.ShouldAnimateEmojis);
    JS_D("allow_accessibility_detection", m.IsAccessibilityDetectionAllowed);
    JS_D("afk_timeout", m.AFKTimeout);
}

void from_json(const nlohmann::json &j, EmbedFooterData &m) {
    JS_D("text", m.Text);
    JS_O("icon_url", m.IconURL);
    JS_O("proxy_icon_url", m.ProxyIconURL);
}

void from_json(const nlohmann::json &j, EmbedImageData &m) {
    JS_O("url", m.URL);
    JS_O("proxy_url", m.ProxyURL);
    JS_O("height", m.Height);
    JS_O("width", m.Width);
}

void from_json(const nlohmann::json &j, EmbedThumbnailData &m) {
    JS_O("url", m.URL);
    JS_O("proxy_url", m.ProxyURL);
    JS_O("height", m.Height);
    JS_O("width", m.Width);
}

void from_json(const nlohmann::json &j, EmbedVideoData &m) {
    JS_O("url", m.URL);
    JS_O("height", m.Height);
    JS_O("width", m.Width);
}

void from_json(const nlohmann::json &j, EmbedProviderData &m) {
    JS_O("name", m.Name);
    JS_ON("url", m.URL);
}

void from_json(const nlohmann::json &j, EmbedAuthorData &m) {
    JS_O("name", m.Name);
    JS_O("url", m.URL);
    JS_O("icon_url", m.IconURL);
    JS_O("proxy_icon_url", m.ProxyIconURL);
}

void from_json(const nlohmann::json &j, EmbedFieldData &m) {
    JS_D("name", m.Name);
    JS_D("value", m.Value);
    JS_O("inline", m.Inline);
}

void from_json(const nlohmann::json &j, EmbedData &m) {
    JS_O("title", m.Title);
    JS_O("type", m.Type);
    JS_O("description", m.Description);
    JS_O("url", m.URL);
    JS_O("timestamp", m.Timestamp);
    JS_O("color", m.Color);
    JS_O("footer", m.Footer);
    JS_O("image", m.Image);
    JS_O("thumbnail", m.Thumbnail);
    JS_O("video", m.Video);
    JS_O("provider", m.Provider);
    JS_O("author", m.Author);
    JS_O("fields", m.Fields);
}

void to_json(nlohmann::json &j, const IdentifyProperties &m) {
    j["$os"] = m.OS;
    j["$browser"] = m.Browser;
    j["$device"] = m.Device;
}

void to_json(nlohmann::json &j, const IdentifyMessage &m) {
    j["op"] = GatewayOp::Identify;
    j["d"] = nlohmann::json::object();
    j["d"]["token"] = m.Token;
    j["d"]["properties"] = m.Properties;

    if (m.LargeThreshold)
        j["d"]["large_threshold"] = m.LargeThreshold;
}

void to_json(nlohmann::json &j, const HeartbeatMessage &m) {
    j["op"] = GatewayOp::Heartbeat;
    if (m.Sequence == -1)
        j["d"] = nullptr;
    else
        j["d"] = m.Sequence;
}

void to_json(nlohmann::json &j, const CreateMessageObject &m) {
    j["content"] = m.Content;
}

void to_json(nlohmann::json &j, const MessageEditObject &m) {
    if (m.Content.size() > 0)
        j["content"] = m.Content;

    // todo EmbedData to_json
    // if (m.Embeds.size() > 0)
    //    j["embeds"] = m.Embeds;

    if (m.Flags != -1)
        j["flags"] = m.Flags;
}

Snowflake::Snowflake()
    : m_num(Invalid) {}

Snowflake::Snowflake(const Snowflake &s)
    : m_num(s.m_num) {}

Snowflake::Snowflake(uint64_t n)
    : m_num(n) {}

Snowflake::Snowflake(const std::string &str) {
    if (str.size())
        m_num = std::stoull(str);
    else
        m_num = Invalid;
};

bool Snowflake::IsValid() const {
    return m_num != Invalid;
}

void from_json(const nlohmann::json &j, Snowflake &s) {
    std::string tmp;
    j.get_to(tmp);
    s.m_num = std::stoull(tmp);
}

void to_json(nlohmann::json &j, const Snowflake &s) {
    j = std::to_string(s);
}

#undef JS_O
#undef JS_D
#undef JS_N
#undef JS_ON