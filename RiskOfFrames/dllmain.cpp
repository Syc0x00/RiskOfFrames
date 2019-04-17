#include "stdafx.h"

HMODULE g_DLLMOD;

void waitForKey() {
	SHORT keystate;
	while (!(keystate = GetKeyState(VK_F10) & 0x8000))
		Sleep(100);
	return;
}

void toggler() {
	SHORT keystate;

	while (1) {
		if ((keystate = GetKeyState(VK_F9) & 0x8000)) {
			// On
			if (!Fullscreen::Toggle(false)) {
				Console::Warn("Fullscreen::Toggle() failed");
			} else {
				Console::Log("Fullscreen off");
			}
		}
		if ((keystate = GetKeyState(VK_F8) & 0x8000)) {
			// Off
			if (!Fullscreen::Toggle(true)) {
				Console::Warn("Fullscreen::Toggle() failed");
			} else {
				Console::Log("Fullscreen on");
			}
		}
		Sleep(50);
	}
}

void main(void) {
	Helpers::Init();

	Console::Log("F8 for fullscreen. F9 for windowed. F10 to detach.");

	HANDLE keyThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)waitForKey, NULL, NULL, NULL);
	HANDLE togglerThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)toggler, NULL, NULL, NULL);

	WaitForSingleObject(keyThread, INFINITE);
	TerminateThread(togglerThread, 0);

	CloseHandle(keyThread);
	CloseHandle(togglerThread);

	Console::Log("Goodbye!");
	Helpers::Exit(0);
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			g_DLLMOD = hModule;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
