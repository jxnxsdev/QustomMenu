#include "main.hpp"

#include "scotland2/shared/modloader.h"
#include "ModConfig.hpp"
#include "bsml/shared/BSML.hpp"
#include "Quotes/quotes.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
#include "bsml/shared/BSML/SharedCoroutineStarter.hpp"


static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be
// removed if those are in use
Configuration &getConfig() {
  static Configuration config(modInfo);
  return config;
}

// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  getConfig().Load();
  getModConfig().Init(modInfo);

  // File logging
  Paper::Logger::RegisterFileContextId(PaperLogger.tag);

  PaperLogger.info("Completed setup!");
}

custom_types::Helpers::Coroutine textScaler(HMUI::CurvedTextMeshPro* text) {
    float currentSize = 40.0f;
    float direction = false; // wether the text is scaling up or down

    while (true) {

        if (currentSize >= 70.0f) {
            direction = false;
        } else if (currentSize <= 40.0f) {
            direction = true;
        }

        if (direction) {
            currentSize += 0.3f;
        } else {
            currentSize -= 0.3f;
        }

        text->set_fontSize(currentSize);

        co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(0.01f));
    }
}

MAKE_HOOK_MATCH(MainMenuViewController_DidActivate, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if (firstActivation) {
        if (!getModConfig().enable_quotes.GetValue()) return;

        bool customQuotes = getModConfig().custom_quotes.GetValue();

        if (customQuotes) {
            CustomMenu::Quotes::LoadCustomQuotes();
        } else {
            CustomMenu::Quotes::LoadQuotes();
        }

        std::string quote = CustomMenu::Quotes::GetRandomQuote();
        PaperLogger.info("Quote: {0}", quote.c_str());

        UnityEngine::Color color = getModConfig().quote_color.GetValue();

        auto* QuoteCanvas = BSML::Lite::CreateFloatingScreen(
                { 1840, 300 }, { 5.0f, 17.0f, 25.0 }, { 0, 0, 30}, 1000000.0f, false, false);

        auto* QuoteText = BSML::Lite::CreateText(QuoteCanvas->get_transform(), quote);
        QuoteText->set_fontSize(40.0f);
        QuoteText->set_color(color);
        QuoteText->set_alignment(TMPro::TextAlignmentOptions::Center);
        QuoteText->GetComponent<UnityEngine::RectTransform*>()->set_sizeDelta({ 1840, 300 });
        QuoteText->set_fontStyle(TMPro::FontStyles::Bold);

        BSML::SharedCoroutineStarter::StartCoroutine(textScaler(QuoteText));
    }
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
  il2cpp_functions::Init();
  BSML::Init();

  CustomMenu::Quotes::EnsureFile();
  PaperLogger.info("Installing hooks...");
  INSTALL_HOOK(PaperLogger, MainMenuViewController_DidActivate);
  PaperLogger.info("Installed all hooks!");
}