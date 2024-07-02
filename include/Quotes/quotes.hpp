#pragma once

#include "ModConfig.hpp"
#include "constants.hpp"
#include "main.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include <filesystem>


namespace CustomMenu::Quotes {
    static std::vector<std::string> quotes = {
            "!bsr 25f",
            "Demo Version",
            };

    static std::vector<std::string> customQuotes = {
            "No Quotes Found!"
    };

    static std::vector<std::string> selectedQuotes;

    void LoadQuotes();
    void LoadCustomQuotes();
    std::string GetRandomQuote();
    void EnsureFile();
}