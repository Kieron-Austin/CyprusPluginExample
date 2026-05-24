#pragma once

#include "types.h"
#include <utility>

struct NativeArg_s {
	u64* returnValue;
	u32 argCount;
	u8 padding1[4];
	u64* argValues;
	u32 vectorCount;
	u8 padding2[4];
	Vector3* argVectors[4];
	Vector4 tempVectors[4];
	
	template<typename T>
	T& get_arg(std::size_t index) {
		static_assert(sizeof(T) <= sizeof(u64), "Argument type too large");
		return *reinterpret_cast<T*>(reinterpret_cast<u64*>(argValues) + index);
	}
};

extern NativeArg_s nativeArg;

extern void resetArgs();
extern void setVectors();

template<typename T>
inline void pushArg(T value) {
	*(T*)&nativeArg.argValues[nativeArg.argCount] = value;
	nativeArg.argCount++;
}

template<typename R>
inline R getReturn() {
	return *(R*)&nativeArg.returnValue[0];
}

template<typename T>
inline T& get_arg(std::size_t index) {
	return nativeArg.get_arg<T>(index);
}

inline u32 get_arg_count() {
	return nativeArg.argCount;
}

template<typename N, typename... A>
N invoke(u64 nativeAddress, A &&... args)
{
	resetArgs();
	int dummy[] = { 0, ((void)pushArg(std::forward<A>(args)), 0) ... };
	((void(*)(NativeArg_s*))(void*)nativeAddress)(&nativeArg);
	setVectors();
	return getReturn<N>();
}