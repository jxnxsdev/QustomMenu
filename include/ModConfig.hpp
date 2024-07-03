#pragma once
#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector3.hpp"
#include <string>

DECLARE_CONFIG(ModConfig,
               CONFIG_VALUE(disable_logo, bool, "DisableBSLogo", false);

               CONFIG_VALUE(enable_quotes, bool, "EnableQuotes", true);
               CONFIG_VALUE(custom_quotes, bool, "CustomQuotes", false);
               CONFIG_VALUE(quote_color, UnityEngine::Color, "QuoteColor", UnityEngine::Color(1.0f, 1.0f, 0.33f, 1.0f));

               CONFIG_VALUE(enable_banners, bool, "EnableBanners", true);
               CONFIG_VALUE(left_banner, std::string, "LeftBanner", "default.png");
               CONFIG_VALUE(right_banner, std::string, "RightBanner", "default.png");

               CONFIG_VALUE(left_banner_position, UnityEngine::Vector3, "LeftBannerPosition", UnityEngine::Vector3(-15.0f, 17.0f, 25.0));
               CONFIG_VALUE(right_banner_position, UnityEngine::Vector3, "RightBannerPosition", UnityEngine::Vector3(15.0f, 17.0f, 25.0));

               CONFIG_VALUE(left_banner_scale_multiplier, float, "LeftBannerScale", 5.0f);
               CONFIG_VALUE(right_banner_scale_multiplier, float, "RightBannerScale", 5.0f);
)
