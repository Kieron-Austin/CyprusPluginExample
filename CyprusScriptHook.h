#pragma once
#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

#define CYPRUS_ABI_VERSION_MAJOR 1
#define CYPRUS_ABI_VERSION_MINOR 1   // 1.1 added LoadTexture / DrawSprite
#define CYPRUS_ABI_VERSION ((CYPRUS_ABI_VERSION_MAJOR << 16) | CYPRUS_ABI_VERSION_MINOR)

enum CyprusPadButton {
    CYPRUS_PAD_CROSS = 0,
    CYPRUS_PAD_CIRCLE,
    CYPRUS_PAD_SQUARE,
    CYPRUS_PAD_TRIANGLE,
    CYPRUS_PAD_L1,
    CYPRUS_PAD_R1,
    CYPRUS_PAD_L2,
    CYPRUS_PAD_R2,
    CYPRUS_PAD_L3,
    CYPRUS_PAD_R3,
    CYPRUS_PAD_DPAD_UP,
    CYPRUS_PAD_DPAD_DOWN,
    CYPRUS_PAD_DPAD_LEFT,
    CYPRUS_PAD_DPAD_RIGHT,
    CYPRUS_PAD_OPTIONS,
    CYPRUS_PAD_TOUCH,
    CYPRUS_PAD_COUNT
};

// Owned by the menu - don't reorder or remove anything!.
typedef struct CyprusApi {
    uint32_t abiVersion;   
    uint32_t structSize;   

    void (*ScriptRegister)(const char* name, void (*entry)(void));
    void (*ScriptUnregister)(const char* name);
    void (*ScriptWait)(uint32_t ms);

    bool (*IsPadPressed)(int button);      
    bool (*IsPadJustPressed)(int button);  

    void (*Notify)(const char* title, const char* message);  

    bool (*LoadTexture)(const char* filePath, const char* txdName);
    void (*DrawSprite)(const char* txdName, const char* textureName,
                       float x, float y, float w, float h,
                       float heading, int r, int g, int b, int a);
} CyprusApi;

#ifdef __cplusplus
static inline const CyprusApi* CyprusApiFromArgp(size_t argc, const void* argv) {
    if (!argv || argc < sizeof(const CyprusApi*)) return nullptr;
    return *reinterpret_cast<const CyprusApi* const*>(argv);
}
#endif

#ifdef __cplusplus
}
#endif
