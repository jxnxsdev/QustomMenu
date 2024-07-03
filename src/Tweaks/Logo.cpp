#include "Tweaks/Logo.hpp"

namespace CustomMenu::Tweaks::Logo {

    void onLoad() {
        logo = UnityEngine::GameObject::Find("Logo");
    }

    void setState() {
        bool disableLogo = getModConfig().disable_logo.GetValue();
        if (disableLogo) {
            logo->SetActive(false);
        } else {
            logo->SetActive(true);
        }
    }
}