//=====================================================================================

#include "StdAfx.hpp"

using namespace t7;

//=====================================================================================

void init(HINSTANCE instance)
{
	hooks.init(instance);
	main_gui.init();
	steam.init();
}

//=====================================================================================

void free()
{
	hooks.free();
	main_gui.free();
	steam.free();
}

//=====================================================================================

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, void* lpvReserved)
{
	//VMProtectBegin("DllMain");

	DisableThreadLibraryCalls(hinstDLL);

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		init(hinstDLL);
		return TRUE;

	case DLL_PROCESS_DETACH:
		free();
		return TRUE;

	default:
		return FALSE;
	}

	//VMProtectEnd();
}

//=====================================================================================