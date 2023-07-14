// define SHADER_NAME before including this file

#define STRINGIFY_MACRO(x) STR(x)
#define STR(x) #x
#define EXPAND(x) x
#define CONCAT(n1, n2) STRINGIFY_MACRO(EXPAND(n1)EXPAND(n2))

#if BGFX_PLATFORM_SUPPORTS_DX9BC
#include CONCAT(SHADER_NAME,.sc.dx9.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_DX9BC

#if BGFX_PLATFORM_SUPPORTS_DXBC
#include CONCAT(SHADER_NAME,.sc.dx11.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_DXBC

#if BGFX_PLATFORM_SUPPORTS_PSSL
#include CONCAT(SHADER_NAME,.sc.pssl.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_PSSL

#if BGFX_PLATFORM_SUPPORTS_ESSL
#include CONCAT(SHADER_NAME,.sc.essl.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_ESSL

#if BGFX_PLATFORM_SUPPORTS_GLSL
#include CONCAT(SHADER_NAME,.sc.glsl.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_GLSL

#if BGFX_PLATFORM_SUPPORTS_SPIRV
#include CONCAT(SHADER_NAME,.sc.spv.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_SPIRV

#if BGFX_PLATFORM_SUPPORTS_METAL
#include CONCAT(SHADER_NAME,.sc.mtl.bin.h)
#endif // BGFX_PLATFORM_SUPPORTS_METAL

#undef SHADER_NAME