#include "ModSettingsViewController.hpp"

#include "HMUI/Touchable.hpp"
#include "bsml/shared/BSML-Lite.hpp"
#include "ModConfig.hpp"
#include "Banners/FileParser.hpp"
#include "Banners/Banners.hpp"

using namespace BSML::Lite;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;

void DidActivate(ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if(firstActivation) {
        CustomMenu::Banners::parseFiles();
        self->get_gameObject()->AddComponent<Touchable*>();
        GameObject* container = BSML::Lite::CreateScrollableSettingsContainer(
                static_cast<Component *>(self->get_transform()));
        Transform* parent = container->get_transform();

        // Tweaks
        auto* disable_logo = AddConfigValueToggle(parent, getModConfig().disable_logo);

        auto* reloadButton = CreateUIButton(parent, "Apply Changes", []() {
            CustomMenu::Banners::ReloadBanners();
        });

        // Quotes
        auto* enable_quotes = AddConfigValueToggle(parent, getModConfig().enable_quotes);
        auto* custom_quotes = AddConfigValueToggle(parent, getModConfig().custom_quotes);
        auto* quote_color = AddConfigValueColorPicker(parent, getModConfig().quote_color);

        // Banners
        auto* enable_banners = AddConfigValueToggle(parent, getModConfig().enable_banners);

        std::vector<std::string> bannerFiles = CustomMenu::Banners::getBannerFiles();

        if (bannerFiles.empty()) {
            bannerFiles.push_back("No Banners Found!");
        }

        std::vector<std::basic_string_view<char>> bannerFilesViews;
        bannerFilesViews.reserve(bannerFiles.size());
        for (const auto& str : bannerFiles) {
            bannerFilesViews.emplace_back(str);
        }
        std::span<std::basic_string_view<char>> bannerFilesSpan(bannerFilesViews);

        auto* selectLeftBanner = AddConfigValueDropdownString(parent, getModConfig().left_banner, bannerFilesSpan);
        auto *selectRightBanner = AddConfigValueDropdownString(parent, getModConfig().right_banner, bannerFilesSpan);

        auto leftBannerPosition = AddConfigValueIncrementVector3(parent, getModConfig().left_banner_position, 1, 0.5f);
        auto rightBannerPosition = AddConfigValueIncrementVector3(parent, getModConfig().right_banner_position, 1, 0.5f);

        auto leftBannerScale = AddConfigValueIncrementFloat(parent, getModConfig().left_banner_scale_multiplier, 1, 0.1f, 0.1f, 100.0f);
        auto rightBannerScale = AddConfigValueIncrementFloat(parent, getModConfig().right_banner_scale_multiplier, 1, 0.1f, 0.1f, 100.0f);

        auto* reloadButtonBanners = CreateUIButton(parent, "Reload Banners", []() {
            CustomMenu::Banners::ReloadBanners();
        });
    }
}