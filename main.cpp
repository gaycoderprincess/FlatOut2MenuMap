#include <windows.h>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

uintptr_t LoadMenuMapASM_envi = 0x8DA758;
uintptr_t LoadMenuMapASM_call = 0x5793E0;
uintptr_t LoadMenuMapASM_call2 = 0x579710;
uintptr_t LoadMenuMapASM_jmp = 0x4ABC2F;
void __attribute__((naked)) LoadMenuMapASM() {
	__asm__ (
		"push edi\n\t"
		"push eax\n\t"
		"mov edi, %2\n\t"
		"mov edi, [edi]\n\t"
		"push 2\n\t"
		"push 0x3F000000\n\t"
		"mov eax, 0x8E8448\n\t"
		"mov eax, [eax]\n\t"
		"push eax\n\t" // a7, some ptr
		"push 0x672738\n\t"
		"push 0x672AB0\n\t"
		"call %1\n\t"
		"mov edi, %2\n\t"
		"mov edi, [edi]\n\t"
		"push edi\n\t"
		"call %3\n\t"
		"pop eax\n\t"
		"pop edi\n\t"
		"mov dword ptr [esi+0x1A0], 1\n\t"
		"jmp %0\n\t"
			:
			:  "m" (LoadMenuMapASM_jmp), "m" (LoadMenuMapASM_call), "m" (LoadMenuMapASM_envi), "m" (LoadMenuMapASM_call2)
	);
}

auto luaL_checktype = (void(*)(void*, int, int))0x5B5DC0;
auto luaL_checkudata = (void*(*)(void*, int, const char*))0x5B5D00;
auto luaL_typerror = (void(*)(void*, int, const char*))0x5B5A50;
auto luaL_checknumber = (double(*)(void*, int))0x5B5F20;
auto lua_tonumber = (double(*)(void*, int))0x5B4300;

struct tGUIStruct {
	uint8_t _0[0x4E8];
	float fCameraTargetX;
	float fCameraTargetY;
	float fCameraTargetZ;
	float fCameraPosX;
	float fCameraPosY;
	float fCameraPosZ;
	float fCameraPosOffsetX;
	float fCameraPosOffsetY;
	float fCameraPosOffsetZ;
	uint8_t _50C[0x4];
	float fMenuCarMatrix[16];
};

int SetCameraPosition(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if ( !data )
		luaL_typerror(a1, 1, "GUI");
	auto gui = *(tGUIStruct**)data;
	gui->fCameraPosX = luaL_checknumber(a1, 2);
	gui->fCameraPosY = luaL_checknumber(a1, 3);
	gui->fCameraPosZ = luaL_checknumber(a1, 4);
	return 0;
}

int SetCameraTarget(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if ( !data )
		luaL_typerror(a1, 1, "GUI");
	auto gui = *(tGUIStruct**)data;
	gui->fCameraTargetX = luaL_checknumber(a1, 2);
	gui->fCameraTargetY = luaL_checknumber(a1, 3);
	gui->fCameraTargetZ = luaL_checknumber(a1, 4);
	return 0;
}

int SetMenuCarTransform(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if ( !data )
		luaL_typerror(a1, 1, "GUI");
	auto gui = *(tGUIStruct**)data;
	for (int i = 0; i < 16; i++) {
		gui->fMenuCarMatrix[i] = luaL_checknumber(a1, 2);
	}
	return 0;
}

struct tLUAFunction {
	const char* name;
	uintptr_t function;
	uint32_t padding;
};
tLUAFunction aGUIFunctions[] = {
		{ "EnterMenu", 0x4ACE60, 0 },
		{ "IsMenuAnimating", 0x4ACEC0, 0 },
		{ "SetActiveItem", 0x4ACF30, 0 },
		{ "GetActiveItem", 0x4ACFC0, 0 },
		{ "SetBackground", 0x4AD560, 0 },
		{ "SetBackgroundVideo", 0x4AD5D0, 0 },
		{ "ShowBottomBalk", 0x518A00, 0 },
		{ "HideBottomBalk", 0x518A00, 0 },
		{ "SetHelpButtons", 0x4AD640, 0 },
		{ "SetStatusText", 0x4AD7A0, 0 },
		{ "SwitchButtonText", 0x4AD840, 0 },
		{ "SetMenuButtonResources", 0x4AD910, 0 },
		{ "HideMenuButtons", 0x4AD080, 0 },
		{ "ShowMenuButtons", 0x4AD030, 0 },
		{ "InitMenuButtons", 0x4AD0D0, 0 },
		{ "PlayVideo", 0x4ADC50, 0 },
		{ "StartAttract", 0x4ADED0, 0 },
		{ "EndAttract", 0x4ADF20, 0 },
		{ "PlayCredits", 0x4ADF70, 0 },
		{ "CheckCheatCode", 0x4AEA10, 0 },
		{ "InitConfirmationDialog", 0x4AD120, 0 },
		{ "CloseConfirmationDialog", 0x4AD1E0, 0 },
		{ "InitMessageBox", 0x4AD420, 0 },
		{ "CloseMessageBox", 0x4AD4E0, 0 },
		{ "IsConfirmationDialogActive", 0x4AD250, 0 },
		{ "IsMessageBoxActive", 0x4AD2B0, 0 },
		{ "AllowOnlineOptionsMenu", 0x4AD310, 0 },
		{ "EnableOnlineOptionsMenu", 0x4AD370, 0 },
		{ "CanEnterOnlineOptions", 0x4AD3D0, 0 },
		{ "DefaultSettings", 0x4ADFC0, 0 },
		{ "ShowCar", 0x4ADFD0, 0 },
		{ "HideCar", 0x4AE010, 0 },
		{ "LoadCar", 0x4AE060, 0 },
		{ "LoadCarSkin", 0x4AE0E0, 0 },
		{ "SetCarRotate", 0x4AE170, 0 },
		{ "AllowCarRotate", 0x4AE1E0, 0 },
		{ "SetCarPose", 0x4AE250, 0 },
		{ "MenuSwitchIgnoreCarState", 0x4AE2B0, 0 },
		{ "SetMenuController", 0x518A00, 0 },
		{ "GetMenuController", 0x4ADA40, 0 },
		{ "GetActiveControllers", 0x4ADAA0, 0 },
		{ "GetLastActiveController", 0x4ADBF0, 0 },
		{ "ResetAllowedControllers", 0x4ADB10, 0 },
		{ "SetControllerAllowed", 0x4ADB70, 0 },
		{ "SetVibration", 0x4AE8A0, 0 },
		{ "SetControllerLayout", 0x4AE900, 0 },
		{ "CheckControllerDisconnect", 0x4AE9A0, 0 },
		{ "SetCameraPosition", (uintptr_t)&SetCameraPosition, 0 },
		{ "SetCameraTarget", (uintptr_t)&SetCameraTarget, 0 },
		{ "SetMenuCarTransform", (uintptr_t)&SetMenuCarTransform, 0 },
		{nullptr, 0, 0}
};

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x202638) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using v1.2 (.exe size of 2990080 bytes)", "nya?!~", MB_ICONERROR);
				return TRUE;
			}

			auto config = toml::parse_file("FlatOut2MenuMap_gcp.toml");
			float fDrawDistance = config["main"]["draw_distance"].value_or(1000.0f);
			bool bAddLUAFunctions = config["main"]["add_lua_functions"].value_or(true);

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

			if (bAddLUAFunctions) {
				NyaHookLib::Patch(0x4A616E, aGUIFunctions);
				NyaHookLib::Patch<uint16_t>(0x4AC4B5, 0x9090);
				NyaHookLib::Fill(0x4AC4BF, 0x90, 0x6C);
			}

			//NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x4AD5BE, 0x4A8E25); // remove backgrounds
		} break;
		default:
			break;
	}
	return TRUE;
}