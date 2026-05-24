// CyprusPluginExample - draws a little panel when you hold L1+R1 and tap D-Up.
// Simple on purpose. Plugins will get closer to ScriptHook over time so porting
// scripts from PC is painless.

#include "CyprusScriptHook.h"
#include "natives.h"
#include <cstddef>

static const CyprusApi* api = nullptr;
static bool showPanel = false;

static void drawText(const char* str, float x, float y, float scale, int r, int g, int b, int a) {
    UI::SET_TEXT_FONT(0);
    UI::SET_TEXT_SCALE(0.0f, scale);
    UI::SET_TEXT_COLOUR(r, g, b, a);
    UI::SET_TEXT_CENTRE(0);
    UI::_SET_TEXT_ENTRY((char*)"STRING");
    UI::_ADD_TEXT_COMPONENT_STRING((char*)str);
    UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
}

static void drawPanel() {
    const float px = 0.180f, py = 0.300f, pw = 0.230f, ph = 0.230f;
    GRAPHICS::DRAW_RECT(px, py, pw, ph, 12, 12, 16, 220);
    GRAPHICS::DRAW_RECT(px, py - ph / 2.0f + 0.018f, pw, 0.036f, 255, 20, 60, 235);

    float left = px - pw / 2.0f + 0.012f;
    float row  = py - ph / 2.0f + 0.006f;

    drawText("CYPRUS PLUGIN", left, row, 0.40f, 255, 255, 255, 255);          row += 0.045f;
    drawText("Loaded from a .plugin file", left, row, 0.32f, 200, 200, 210, 255); row += 0.035f;
    drawText("Cyprus Menu now supports plugins!", left, row, 0.32f, 200, 200, 210, 255); row += 0.050f;
    drawText("Create your own just like ScriptHook", left, row, 0.32f, 160, 200, 255, 255); row += 0.035f;
    drawText("Only requirement: PS4 SDK 1.750", left, row, 0.32f, 160, 200, 255, 255); row += 0.055f;
    drawText("L1 + R1 + D-Up to toggle.", left, row, 0.32f, 255, 220, 120, 255);
}

static void scriptMain() {
    for (;;) {
        if (api->IsPadPressed(CYPRUS_PAD_L1) &&
            api->IsPadPressed(CYPRUS_PAD_R1) &&
            api->IsPadJustPressed(CYPRUS_PAD_DPAD_UP)) {
            showPanel = !showPanel;
            api->Notify("Cyprus Plugin", showPanel ? "Panel shown" : "Panel hidden");
        }

        if (showPanel)
            drawPanel();

        api->ScriptWait(0);
    }
}

static const char* kScriptName = "CyprusPluginExample";

extern "C" int module_start(std::size_t argc, const void* argv) {
    api = CyprusApiFromArgp(argc, argv);
    if (!api || api->abiVersion < CYPRUS_ABI_VERSION)
        return -1;

    api->ScriptRegister(kScriptName, scriptMain);
    api->Notify("Cyprus Plugin", "Loaded - L1+R1+D-Up for UI");
    return 0;
}

extern "C" int module_stop(std::size_t argc, const void* argv) {
    (void)argc; (void)argv;
    if (api)
        api->ScriptUnregister(kScriptName);
    return 0;
}
