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
            "Performance Test",
            "Freeek Pattern",
            "ff9 - Smooth Criminal",
            "Electric Callboy music pack when?",
            "Amogus",
            "Sponsored by Liveness™",
            "Beat Saber 2.0 confirmed?",
            "OST 8 Release 09.11.2024",
            "streamer play rap god",
            "Lstoast",
            "Can you play *insert random rush e meme map here*?",
            "Download the GaySabers mod!",
            "Reality Check Through The Skull",
            "Bandoot",
            "Tempex",
            "i am ob1cb",
            "$100 bills on easy"
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