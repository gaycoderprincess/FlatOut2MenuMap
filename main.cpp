#include <windows.h>
#include <algorithm>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"
#include "nya_commontimer.h"
#include "nya_commonmath.h"

#include "spline_library/spline_library/splines/uniform_cr_spline.h"

bool bAlwaysShowMenu = true;

const char* sCollisionName = "data/tracks/menu/menu1/a/geometry/track_cdb.gen";
const char* sStageName = "stage1";
uintptr_t LoadMenuMapASM_envi = 0x8DA758;
uintptr_t LoadMenuMapASM_call = 0x5793E0;
uintptr_t LoadMenuMapASM_call2 = 0x579710;
uintptr_t LoadMenuMapASM_call3 = 0x56D500;
uintptr_t LoadMenuMapASM_malloc = 0x6035CE;
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
		"push %4\n\t"
		"call %1\n\t" // load track

		"push 0x40\n\t"
		"call %5\n\t" // malloc
		"add esp, 4\n\t"
		"mov dword ptr [eax+0x30], 0\n\t"
		"mov edi, %2\n\t"
		"mov edi, [edi]\n\t"
		"mov [edi+0x24], eax\n\t" // mov ptr to track + 0x24
		"push eax\n\t"
		"mov eax, %7\n\t"
		"call %6\n\t" // load collision

		"mov edi, %2\n\t"
		"mov edi, [edi]\n\t"
		"push edi\n\t"
		"call %3\n\t" // load plants
		"pop eax\n\t"
		"pop edi\n\t"
		"mov dword ptr [esi+0x1A0], 1\n\t"
		"jmp %0\n\t"
			:
			:  "m" (LoadMenuMapASM_jmp), "m" (LoadMenuMapASM_call), "m" (LoadMenuMapASM_envi), "m" (LoadMenuMapASM_call2), "m" (sStageName), "m" (LoadMenuMapASM_malloc), "m" (LoadMenuMapASM_call3), "m" (sCollisionName)
	);
}

uintptr_t RenderMenuMapASM_call = 0x555B60;
uintptr_t RenderMenuMapASM_call2 = 0x555A60;
uintptr_t RenderMenuMapASM_call3 = 0x5548A0;
uintptr_t RenderMenuMapASM_call4 = 0x595000;
uintptr_t RenderMenuMapASM_jmp = 0x4CC0FA;
void __attribute__((naked)) RenderMenuMapASM() {
	__asm__ (
		// tree trunks
		"push eax\n\t"
		"push ecx\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"mov eax, [eax+0x1804]\n\t"
		"mov eax, [eax+0x14C]\n\t"
		"push eax\n\t"
		"mov eax, esi\n\t" // +1B4
		"mov ecx, 10\n\t"
		"call %3\n\t"
		"pop ecx\n\t"
		"pop eax\n\t"

		// trees
		"push eax\n\t"
		"push ecx\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"mov eax, [eax+0x1804]\n\t"
		"mov eax, [eax+0x154]\n\t"
		"push eax\n\t"
		"mov eax, esi\n\t" // +1B4
		"mov ecx, 11\n\t"
		"call %1\n\t"
		"pop ecx\n\t"
		"pop eax\n\t"

		// grass
		"push eax\n\t"
		"push ecx\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"mov eax, [eax+0x1804]\n\t"
		"mov eax, [eax+0x158]\n\t"
		"push eax\n\t"
		"mov eax, esi\n\t" // +1B4
		"mov ecx, 12\n\t"
		"call %1\n\t"
		"pop ecx\n\t"
		"pop eax\n\t"

		"push eax\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"mov eax, [eax+0x1804]\n\t"
		"mov eax, [eax+0x160]\n\t"
		"push eax\n\t"
		"push esi\n\t" // +1B4
		"mov eax, 14\n\t"
		"call %4\n\t"
		"pop eax\n\t"

		"push eax\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"mov eax, [eax+0x1804]\n\t"
		"mov eax, [eax+0x15C]\n\t"
		"push eax\n\t"
		"push esi\n\t" // +1B4
		"mov eax, 13\n\t"
		"call %4\n\t"
		"pop eax\n\t"

		// vegetation
		//"push ecx\n\t"
		//"push edx\n\t"
		//"push eax\n\t"
		//// scene ptr
		//"mov ecx, [esp+0x48]\n\t" // was +3C before
		//// scene + 0x1A4
		//"mov edx, [ecx+0x1A4]\n\t"
		//// camera + 0x10C
		//"mov eax, ebp\n\t"
		//"mov eax, [eax+0x10C]\n\t"
		//"push eax\n\t"
		//// d3d stuff
		//"mov eax, 0x8DA718\n\t"
		//"mov eax, [eax]\n\t"
		//"push eax\n\t"
		//// scene + 0x1A8
		//"mov eax, [ecx+0x1A8]\n\t"
		//"push eax\n\t"
		//// scene ptr
		//"push ecx\n\t"
		//// camera ptr
		//"mov ecx, ebp\n\t"
		//"call %5\n\t"
		//"pop eax\n\t"
		//"pop edx\n\t"
		//"pop ecx\n\t"

		"mov edx, [edi]\n\t"
		"mov ecx, edi\n\t"
		"call dword ptr [edx+0x60]\n\t"
		"jmp %0\n\t"
			:
			:  "m" (RenderMenuMapASM_jmp), "m" (RenderMenuMapASM_call), "m" (LoadMenuMapASM_envi), "m" (RenderMenuMapASM_call2), "m" (RenderMenuMapASM_call3), "m" (RenderMenuMapASM_call4)
	);
}

uintptr_t RenderMenuSkyASM_call = 0x592470;
uintptr_t RenderMenuSkyASM_jmp = 0x4CBED1;
void __attribute__((naked)) RenderMenuSkyASM() {
	__asm__ (
		// eax is camera ptr, then env ptr pushed, then some unused value
		"pushad\n\t"
		"push 10\n\t"
		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"push eax\n\t"
		"mov eax, ebp\n\t" // camera
		"call %1\n\t"
		"popad\n\t"

		"mov eax, %2\n\t"
		"mov eax, [eax]\n\t"
		"jmp %0\n\t"
			:
			:  "m" (RenderMenuSkyASM_jmp), "m" (RenderMenuSkyASM_call), "m" (LoadMenuMapASM_envi)
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
	float fMenuCarPosX;
	float fMenuCarPosY;
	float fMenuCarPosZ;
	uint8_t _50C[0x4];
	float fMenuCarMatrix[16];
};

std::vector<NyaVec3> camSplinePaths;
LoopingUniformCRSpline<NyaVec3>* camSpline;
float camSplineSpeed = 0.01;
double camSplineState = 0;
void __fastcall MenuCameraLoop(tGUIStruct* pGUI) {
	if (!camSpline) return;

	static CNyaTimer timer;
	camSplineState += timer.Process() * camSplineSpeed;

	NyaVec3 pos = camSpline->getPosition(camSplineState);
	pGUI->fCameraPosX = pos.x;
	pGUI->fCameraPosY = pos.y;
	pGUI->fCameraPosZ = pos.z;
}

uintptr_t MenuCameraLoopASM_jmp = 0x4A8A68;
void __attribute__((naked)) MenuCameraLoopASM() {
	__asm__ (
		"pushad\n\t"
		"mov ecx, ebx\n\t"
		"call %1\n\t"
		"popad\n\t"

		"mov eax, 0x8E8464\n\t"
		"mov eax, [eax]\n\t"
		"jmp %0\n\t"
			:
			:  "m" (MenuCameraLoopASM_jmp), "i" (MenuCameraLoop)
	);
}

int SetCameraPosition(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	if (camSpline) delete camSpline;
	camSpline = nullptr;
	camSplineState = 0;

	auto gui = *(tGUIStruct**)data;
	gui->fMenuCarPosX = 0;
	gui->fMenuCarPosY = 0;
	gui->fMenuCarPosZ = 0;
	gui->fCameraPosX = luaL_checknumber(a1, 2);
	gui->fCameraPosY = luaL_checknumber(a1, 3);
	gui->fCameraPosZ = luaL_checknumber(a1, 4);
	return 0;
}

int SetCameraTarget(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	auto gui = *(tGUIStruct**)data;
	gui->fMenuCarPosX = 0;
	gui->fMenuCarPosY = 0;
	gui->fMenuCarPosZ = 0;
	gui->fCameraTargetX = luaL_checknumber(a1, 2);
	gui->fCameraTargetY = luaL_checknumber(a1, 3);
	gui->fCameraTargetZ = luaL_checknumber(a1, 4);
	return 0;
}

int SetCameraSplinePoint(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	int id = luaL_checknumber(a1, 2);
	if (id >= 0 && id < camSplinePaths.size()) {
		camSplinePaths[id].x = luaL_checknumber(a1, 3);
		camSplinePaths[id].y = luaL_checknumber(a1, 4);
		camSplinePaths[id].z = luaL_checknumber(a1, 5);
	}

	if (camSpline) delete camSpline;
	camSpline = new LoopingUniformCRSpline<NyaVec3>(camSplinePaths);
	return 0;
}

int SetCameraSplineSpeed(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	camSplineSpeed = luaL_checknumber(a1, 2);
	return 0;
}

int SetCameraSplineCount(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	int count = luaL_checknumber(a1, 2);
	if (count > 0) {
		while (camSplinePaths.size() < count) camSplinePaths.push_back({0,0,0});
		while (camSplinePaths.size() > count) camSplinePaths.pop_back();
	}
	if (camSpline) delete camSpline;
	camSpline = nullptr;
	return 0;
}

int ResetCameraSpline(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	if (camSpline) delete camSpline;
	camSpline = nullptr;
	camSplinePaths.clear();
	camSplineState = 0;
	return 0;
}

int SetMenuCarTransform(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	auto gui = *(tGUIStruct**)data;
	gui->fMenuCarPosX = 0;
	gui->fMenuCarPosY = 0;
	gui->fMenuCarPosZ = 0;
	for (int i = 0; i < 16; i++) {
		gui->fMenuCarMatrix[i] = luaL_checknumber(a1, i + 2);
	}
	return 0;
}

int Hide3DMenu(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4ACA17, 0x4ACAD5);
	return 0;
}

int Show3DMenu(void* a1) {
	luaL_checktype(a1, 1, 7);
	auto data = luaL_checkudata(a1, 1, "GUI");
	if (!data) luaL_typerror(a1, 1, "GUI");

	if (bAlwaysShowMenu) NyaHookLib::Patch<uint16_t>(0x4ACA17, 0x28EB);
	else NyaHookLib::Patch<uint64_t>(0x4ACA17, 0xF883000000B8840F);
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
		{ "SetCameraSplinePoint", (uintptr_t)&SetCameraSplinePoint, 0 },
		{ "SetCameraSplineSpeed", (uintptr_t)&SetCameraSplineSpeed, 0 },
		{ "SetCameraSplineCount", (uintptr_t)&SetCameraSplineCount, 0 },
		{ "ResetCameraSpline", (uintptr_t)&ResetCameraSpline, 0 },
		{ "SetMenuCarTransform", (uintptr_t)&SetMenuCarTransform, 0 },
		{ "Hide3DMenu", (uintptr_t)&Hide3DMenu, 0 },
		{ "Show3DMenu", (uintptr_t)&Show3DMenu, 0 },
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
			bAlwaysShowMenu = config["main"]["always_show_menu"].value_or(true);
			bool bAlwaysUpdateCamera = config["main"]["always_update_camera"].value_or(true);

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

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4CC0F3, &RenderMenuMapASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4CBECC, &RenderMenuSkyASM);

			if (bAddLUAFunctions) {
				NyaHookLib::Patch(0x4A616E, aGUIFunctions);

				// disable vanilla menucar placement code
				NyaHookLib::Patch<uint16_t>(0x4AC4B5, 0x9090);
				NyaHookLib::Fill(0x4AC4BF, 0x90, 0x6C);
				NyaHookLib::Fill(0x4AC555, 0x90, 3);
				NyaHookLib::Fill(0x4AC55F, 0x90, 6);
				NyaHookLib::Patch<uint16_t>(0x4AC9D4, 0x9090);
				NyaHookLib::Fill(0x4AC9DC, 0x90, 3);
				NyaHookLib::Fill(0x4AC9E5, 0x90, 3);
				NyaHookLib::Fill(0x4AC9EF, 0x90, 3);

				NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4A8A63, &MenuCameraLoopASM);
			}

			if (bAlwaysShowMenu) {
				NyaHookLib::Patch<uint16_t>(0x4ACA17, 0x28EB);
				static float fadeSpeed = 100;
				NyaHookLib::Patch(0x4AC69D + 2, &fadeSpeed);
				NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4A8BBB, 0x4A8BD3);
			}

			if (bAlwaysUpdateCamera) {
				NyaHookLib::Fill(0x4AC70A, 0x90, 6);
			}
		} break;
		default:
			break;
	}
	return TRUE;
}