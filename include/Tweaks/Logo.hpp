#pragma once

#include "ModConfig.hpp"
#include "UnityEngine/GameObject.hpp"

namespace CustomMenu::Tweaks::Logo {
    static SafePtrUnity<UnityEngine::GameObject> logo;

    void onLoad();
    void setState();
}