#pragma once

#include <filesystem>
#include "constants.hpp"
#include <string>
#include <vector>
#include <fstream>
#include "UnityEngine/Sprite.hpp"
#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "main.hpp"

namespace CustomMenu::Banners {
    static std::vector<std::string> bannerFiles;

    static void EnsureFolder() {
        std::string modPath = Constants::ModPath;
        if (!std::filesystem::exists(modPath)) {
            std::filesystem::create_directory(modPath);
        }

        std::string path = Constants::BannerFolder;
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directory(path);
        }
    }

    static void parseFiles() {
        std::string path = Constants::BannerFolder;
        bannerFiles.clear();

        PaperLogger.info("Parsing files in: {0}", path.c_str());

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            PaperLogger.info("Found file: {0}", entry.path().string().c_str());
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                if (extension == ".png" || extension == ".jpg") {
                    std::string fileName = entry.path().filename().string();
                    bannerFiles.push_back(fileName);
                    PaperLogger.info("Added file: {0}", fileName.c_str());
                }
            }
        }
    }

    static std::vector<std::string> getBannerFiles() {
        return bannerFiles;
    }

    static UnityEngine::Sprite* readFileAsSprite(std::string filename) {
        std::string path = Constants::BannerFolder + "/" + filename;
        if (!std::filesystem::exists(path)) {
            return nullptr;
        }
        auto* sprite = BSML::Lite::FileToSprite(path);
        return sprite;
    }
}