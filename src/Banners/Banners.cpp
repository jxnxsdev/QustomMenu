#include "Banners/Banners.hpp"
#include "Banners/FileParser.hpp"
#include "constants.hpp"
#include "bsml/shared/BSML-Lite/Creation/Image.hpp"


namespace CustomMenu::Banners {

    void LoadBanners() {
        UnityEngine::Vector3 leftBannerPositon = getModConfig().left_banner_position.GetValue();
        UnityEngine::Vector3 rightBannerPositon = getModConfig().right_banner_position.GetValue();

        float leftBannerScaleMP = getModConfig().left_banner_scale_multiplier.GetValue();
        float rightBannerScaleMP = getModConfig().right_banner_scale_multiplier.GetValue();

        UnityEngine::Vector2 leftBannerScale = { defaultScale.x * leftBannerScaleMP, defaultScale.y * leftBannerScaleMP };
        UnityEngine::Vector2 rightBannerScale = { defaultScale.x * rightBannerScaleMP, defaultScale.y * rightBannerScaleMP };


        UnityEngine::Vector2 leftBannerImageScale = { defaultImageScale.x * leftBannerScaleMP * 0.6f, defaultImageScale.y * leftBannerScaleMP * 0.6f};
        UnityEngine::Vector2 rightBannerImageScale = { defaultImageScale.x * rightBannerScaleMP * 0.6f, defaultImageScale.y * rightBannerScaleMP * 0.6f};

        leftBanner = BSML::Lite::CreateFloatingScreen(leftBannerScale, leftBannerPositon, { 0, 0, 0 }, 0.0f, false, false);
        rightBanner = BSML::Lite::CreateFloatingScreen(rightBannerScale, rightBannerPositon, { 0, 0, 0 }, 0.0f, false, false);
        leftBanner->GetComponent<UnityEngine::Canvas*>()->set_sortingOrder(0);
        rightBanner->GetComponent<UnityEngine::Canvas*>()->set_sortingOrder(0);

        std::string leftBannerFile = getModConfig().left_banner.GetValue();
        std::string rightBannerFile = getModConfig().right_banner.GetValue();

        if (leftBannerFile.empty()) {
            leftBannerFile = "default.png";
        }

        if (rightBannerFile.empty()) {
            rightBannerFile = "default.png";
        }

        UnityEngine::Sprite* leftBannerSprite = CustomMenu::Banners::readFileAsSprite(leftBannerFile);
        UnityEngine::Sprite* rightBannerSprite = CustomMenu::Banners::readFileAsSprite(rightBannerFile);

        if (leftBannerSprite == nullptr) {
            leftBannerSprite = BSML::Lite::Base64ToSprite(Constants::base64ErrorSprite);
        }

        if (rightBannerSprite == nullptr) {
            rightBannerSprite = BSML::Lite::Base64ToSprite(Constants::base64ErrorSprite);
        }

        HMUI::ImageView* leftBannerImage = BSML::Lite::CreateImage(leftBanner->get_transform(), leftBannerSprite, { 0, 0 }, leftBannerImageScale);
        HMUI::ImageView* rightBannerImage = BSML::Lite::CreateImage(rightBanner->get_transform(), rightBannerSprite, { 0, 0 }, rightBannerImageScale);
    }

    void ReloadBanners() {
        // delete old banners
        if (leftBanner != nullptr) {
            UnityEngine::Object::Destroy(leftBanner->get_gameObject());
        }

        if (rightBanner != nullptr) {
            UnityEngine::Object::Destroy(rightBanner->get_gameObject());
        }

        LoadBanners();
    }
}