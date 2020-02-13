#pragma once

#include <json.hpp>
#include <utility>

namespace CppTelegramBots {
    class ChatPermissions {
    public:
        bool canSendMessages{false};
        bool canSendMediaMessages{false};
        bool canSendPolls{false};
        bool canSendOtherMessages{false};
        bool canAddWebPagePreviews{false};
        bool canChangeInfo{false};
        bool canInviteUsers{false};
        bool canPinMessages{false};

        explicit ChatPermissions(bool canSendMessages = false,
                                 bool canSendMediaMessages = false,
                                 bool canSendPolls = false,
                                 bool canSendOtherMessages = false,
                                 bool canAddWebPagePreviews = false,
                                 bool canChangeInfo = false,
                                 bool canInviteUsers = false,
                                 bool canPinMessages = false) {
            this->canSendMessages = canSendMessages;
            this->canSendMediaMessages = canSendMediaMessages;
            this->canSendPolls = canSendPolls;
            this->canSendOtherMessages = canSendOtherMessages;
            this->canAddWebPagePreviews = canAddWebPagePreviews;
            this->canChangeInfo = canChangeInfo;
            this->canInviteUsers = canInviteUsers;
            this->canPinMessages = canPinMessages;
        };

        std::string toString() {
            nlohmann::json json = {
                    {"can_send_messages", this->canSendMessages},
                    {"can_send_media_messages", this->canSendMediaMessages},
                    {"can_send_polls", this->canSendPolls},
                    {"can_send_other_messages", this->canSendOtherMessages},
                    {"can_add_web_page_previews", this->canAddWebPagePreviews},
                    {"can_change_info", this->canChangeInfo},
                    {"can_invite_users", this->canInviteUsers},
                    {"can_pin_messages", this->canPinMessages}
            };
            return json.dump();
        }
    };

    void from_json(nlohmann::json json, ChatPermissions &permissions) {
        if (json.count("can_send_messages") != 0) json.at("can_send_messages").get_to(permissions.canSendMessages);
        if (json.count("can_send_media_messages") != 0) json.at("can_send_media_messages").get_to(permissions.canSendMediaMessages);
        if (json.count("can_send_polls") != 0) json.at("can_send_polls").get_to(permissions.canSendPolls);
        if (json.count("can_send_other_messages") != 0) json.at("can_send_other_messages").get_to(permissions.canSendOtherMessages);
        if (json.count("can_add_web_page_previews") != 0) json.at("can_add_web_page_previews").get_to(permissions.canAddWebPagePreviews);
        if (json.count("can_change_info") != 0) json.at("can_change_info").get_to(permissions.canChangeInfo);
        if (json.count("can_invite_users") != 0) json.at("can_invite_users").get_to(permissions.canInviteUsers);
        if (json.count("can_pin_messages") != 0) json.at("can_pin_messages").get_to(permissions.canPinMessages);
    }
}
