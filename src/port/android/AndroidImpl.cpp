#ifdef __ANDROID__
#include "AndroidImpl.h"
#include <SDL2/SDL.h>
#include "public/bridge/consolevariablebridge.h"

#include <ImGui/imgui_internal.h>

static bool isShowingVirtualKeyboard = true;

void LUS::Android::ImGuiProcessEvent(bool wantsTextInput) {
    ImGuiInputTextState* state = ImGui::GetInputTextState(ImGui::GetActiveID());

    if (wantsTextInput) {
        if (!isShowingVirtualKeyboard) {
            state->ClearText();

            isShowingVirtualKeyboard = true;
            SDL_StartTextInput();
        }
    } else {
        if (isShowingVirtualKeyboard) {
            isShowingVirtualKeyboard = false;
            SDL_StopTextInput();
        }
    }
}

void LUS::Android::adjustGyro(float gyroData[3]){
    float gyroX = gyroData[0];
    float gyroY = gyroData[1];
    switch(SDL_GetDisplayOrientation(0)){
        case(SDL_ORIENTATION_PORTRAIT):
            // nothing to do
            break;
        case(SDL_ORIENTATION_PORTRAIT_FLIPPED):
            gyroData[0] = -gyroX;
            gyroData[1] = -gyroY;
            break;
        case(SDL_ORIENTATION_LANDSCAPE):
            gyroData[0] = -gyroY;
            gyroData[1] = gyroX;
            break;
        case(SDL_ORIENTATION_LANDSCAPE_FLIPPED):
            gyroData[0] = gyroY;
            gyroData[1] = -gyroX;
            break;
        case(SDL_ORIENTATION_UNKNOWN):
            // nothing to do
            break;
    }
}
#endif
