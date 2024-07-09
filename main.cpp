#include <windows.h>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

uintptr_t LoadMenuMapASM_envi = 0x8DA758;
uintptr_t LoadMenuMapASM_call = 0x5793E0;
uintptr_t LoadMenuMapASM_jmp = 0x4ABC2F;
void __attribute__((naked)) LoadMenuMapASM() {
	__asm__ (
		"push edi\n\t"
		"mov edi, %2\n\t"
		"mov edi, [edi]\n\t"
		"push 2\n\t"
		"push 0x3F000000\n\t"
		"push 0\n\t" // a7, some ptr
		"push 0x672738\n\t"
		"push 0x672AB0\n\t"
		"call %1\n\t"
		"pop edi\n\t"
		"mov dword ptr [esi+0x1A0], 1\n\t"
		"jmp %0\n\t"
			:
			:  "m" (LoadMenuMapASM_jmp), "m" (LoadMenuMapASM_call), "m" (LoadMenuMapASM_envi)
	);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x202638) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using v1.2 (.exe size of 2990080 bytes)", "nya?!~", MB_ICONERROR);
				return TRUE;
			}

			auto config = toml::parse_file("FlatOut2MenuMap_gcp.toml");
			float fDrawDistance = config["main"]["draw_distance"].value_or(1000.0f);

			static char path1[] = "Menu";
			static char path2[] = "Menu1";
			static char path3[] = "A";
			NyaHookLib::Patch(0x4ABC0D + 1, path1);
			NyaHookLib::Patch(0x4ABC08 + 1, path2);
			NyaHookLib::Patch(0x4ABC03 + 1, path3);

			static char _path1[] = "data/Tracks/Menu/Menu1/A/";
			static char _path2[] = "data/Tracks/Menu/Menu1/";
			static char _path3[] = "data/Tracks/Menu/";
			NyaHookLib::Patch(0x4ABBD0 + 1, _path1);
			NyaHookLib::Patch(0x4ABBD5 + 1, _path2);
			NyaHookLib::Patch(0x4ABBDA + 1, _path3);

			NyaHookLib::Patch<float>(0x4ABBBC + 6, fDrawDistance);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4ABC25, &LoadMenuMapASM);

			//NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x4AD5BE, 0x4A8E25); // remove backgrounds
		} break;
		default:
			break;
	}
	return TRUE;
}