#pragma once
#include <utility>
#include <stack>
#include <map>
#include <kernel.h>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <sstream>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define _TYPES_H_INCLUDED
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long int size_t;
typedef char CHAR;
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef int Scaleform;



typedef struct {
	float x, y;
} Vector2;

typedef struct {
	float x, _padX, y, _padY, z, _padZ;
} Vector3;

typedef struct {
	float x, y, z, w;
} Vector4;


    
template <typename T, size_t N>
    char (*RtlpNumberOf(T (&)[N]))[N];
    
    
