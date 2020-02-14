#pragma once

#include <json.hpp>
#include "User.hpp"

namespace CppTelegramBots {
    class ChatMember {
    public:
        User user{};

        std::string status{};
        std::string customTitle{};

        int untilDate{};

        bool canBeEdited{false};
        bool canPostMessages{false};
        bool canEditMessages{false};
        bool canDeleteMessages{false};
        bool canRestrictMembers{false};
        bool canPromoteMembers{false};
        bool canChangeInfo{false};
        bool canInviteUsers{false};
        bool canPinMessages{false};
        bool isMember{false};
        bool canSendMessages{false};
        bool canSendMediaMessages{false};
        bool canSendPolls{false};
        bool canSendOtherMessages{false};
        bool canAddWebPagePreviews{false};

        ChatMember() = default;
    };

    void from_json(const nlohmann::json& json, ChatMember& chatMember) {
        json.at("user").get_to(chatMember.user);
        json.at("status").get_to(chatMember.status);
        if (json.count("custom_title") != 0) json.at("custom_title").get_to(chatMember.customTitle);
        if (json.count("until_date") != 0) json.at("until_date").get_to(chatMember.untilDate);
        if (json.count("can_be_edited") != 0) json.at("can_be_edited").get_to(chatMember.canBeEdited);
        if (json.count("can_post_messages") != 0) json.at("can_post_messages").get_to(chatMember.canPostMessages);
        if (json.count("can_edit_messages") != 0) json.at("can_edit_messages").get_to(chatMember.canEditMessages);
        if (json.count("can_delete_messages") != 0) json.at("can_delete_messages").get_to(chatMember.canDeleteMessages);
        if (json.count("can_restrict_members") != 0) json.at("can_restrict_members").get_to(chatMember.canRestrictMembers);
        if (json.count("can_promote_members") != 0) json.at("can_promote_members").get_to(chatMember.canPromoteMembers);
        if (json.count("can_change_info") != 0) json.at("can_change_info").get_to(chatMember.canChangeInfo);
        if (json.count("can_invite_users") != 0) json.at("can_invite_users").get_to(chatMember.canInviteUsers);
        if (json.count("can_pin_messages") != 0) json.at("can_pin_messages").get_to(chatMember.canPinMessages);
        if (json.count("is_member") != 0) json.at("is_member").get_to(chatMember.isMember);
        if (json.count("can_send_messages") != 0) json.at("can_send_messages").get_to(chatMember.canSendMessages);
        if (json.count("can_send_media_messages") != 0) json.at("can_send_media_messages").get_to(chatMember.canSendMediaMessages);
        if (json.count("can_send_polls") != 0) json.at("can_send_polls").get_to(chatMember.canSendPolls);
        if (json.count("can_send_other_messages") != 0) json.at("can_send_other_messages").get_to(chatMember.canSendOtherMessages);
        if (json.count("can_add_web_page_previews") != 0) json.at("can_add_web_page_previews").get_to(chatMember.canAddWebPagePreviews);
    }

}