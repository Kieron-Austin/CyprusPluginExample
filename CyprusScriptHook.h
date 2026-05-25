#pragma once
#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

#define CYPRUS_ABI_VERSION_MAJOR 1
#define CYPRUS_ABI_VERSION_MINOR 3   // 1.1 textures, 1.2 scan+memory, 1.3 script globals
#define CYPRUS_ABI_VERSION ((CYPRUS_ABI_VERSION_MAJOR << 16) | CYPRUS_ABI_VERSION_MINOR)

enum CyprusScanMode {
    CYPRUS_SCAN_ADDRESS = 0, 
    CYPRUS_SCAN_RIP,         
    CYPRUS_SCAN_CALL,        
    CYPRUS_SCAN_DEREF        
};

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

// Owned by the menu - don't reorder or remove anything, only append.
typedef struct CyprusApi {
    uint32_t abiVersion;   
    uint32_t structSize;  

    void (*ScriptRegister)(const char* name, void (*entry)(void));
    void (*ScriptUnregister)(const char* name);
    void (*ScriptWait)(uint32_t ms);

    bool (*IsPadPressed)(int button);      
    bool (*IsPadJustPressed)(int button);  

    void (*Notify)(const char* title, const char* message);  // PS4/PS5 toast, title can be null

    bool (*LoadTexture)(const char* filePath, const char* txdName);
    void (*DrawSprite)(const char* txdName, const char* textureName,
                       float x, float y, float w, float h,
                       float heading, int r, int g, int b, int a);

    uintptr_t (*FindPattern)(const char* pattern, int offset, int scanMode);
    bool (*ReadMemory)(uintptr_t address, void* out, size_t size);
    bool (*WriteMemory)(uintptr_t address, const void* in, size_t size);
    void* (*GetGlobalPtr)(int index);
} CyprusApi;

#ifdef __cplusplus
} 
#endif

#ifdef __cplusplus
static inline const CyprusApi* CyprusApiFromArgp(size_t argc, const void* argv) {
    if (!argv || argc < sizeof(const CyprusApi*)) return nullptr;
    return *reinterpret_cast<const CyprusApi* const*>(argv);
}

class CyprusGlobal {
    void* m_handle;
public:
    CyprusGlobal(const CyprusApi* api, int index)
        : m_handle(api ? api->GetGlobalPtr(index) : nullptr) {}
    CyprusGlobal(void* p) : m_handle(p) {}
    CyprusGlobal(const CyprusGlobal& o) : m_handle(o.m_handle) {}

    CyprusGlobal At(int index) const {
        return CyprusGlobal(reinterpret_cast<void**>(m_handle) + index);
    }
    CyprusGlobal At(int index, int size) const { return At(1 + index * size); }
    CyprusGlobal at(int index) const { return At(index); }
    CyprusGlobal at(int index, int size) const { return At(index, size); }

    bool valid() const { return m_handle != nullptr; }

    template <typename T> T* Get() { return reinterpret_cast<T*>(m_handle); }
    template <typename T> T& As() { return *Get<T>(); }
    template <typename T> T& as() { return *Get<T>(); }
};

#ifndef CYPRUS_HOST_BUILD
using Global = CyprusGlobal;
#endif
#endif 
