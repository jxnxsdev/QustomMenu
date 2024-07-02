#pragma once
#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Color.hpp"

DECLARE_CONFIG(ModConfig,
               CONFIG_VALUE(enable_quotes, bool, "EnableQuotes", true);
               CONFIG_VALUE(custom_quotes, bool, "CustomQuotes", false);
               CONFIG_VALUE(quote_color, UnityEngine::Color, "QuoteColor", UnityEngine::Color(1.0f, 1.0f, 0.33f, 1.0f));
)
