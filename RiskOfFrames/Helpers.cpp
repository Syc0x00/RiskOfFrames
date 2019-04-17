#include "stdafx.h"
#include "Helpers.h"

std::mutex mtx;

void Console::Log(const char *str) {
	mtx.lock();
	std::cout << "[+] " << str << std::endl;
	mtx.unlock();
}

void Console::Warn(const char *str) {
	mtx.lock();
	std::cout << "[?] " << str << std::endl;
	mtx.unlock();
}

void Console::Err(const char *str) {
	std::cout << "[!] " << str << std::endl;
	Helpers::Exit(0);
}

void Console::Address(const char *name, int address) {
	mtx.lock();
	std::cout << "[+] " << name << ": 0x" << std::hex << address << std::dec << std::endl;
	mtx.unlock();
}

void Console::Bytes(const char *name, int bytes[]) {
	mtx.lock();
	std::cout << "[+] " << name << ": " << std::endl;
	// for size of bytes
	// print 2 bytes in hex or smt
	std::cout << std::endl;
	mtx.unlock();
}

// Bad code but it works
extern HMODULE g_DLLMOD;

void Helpers::Init() {
	// Console window
	AllocConsole();
	AttachConsole(GetProcessId(GetCurrentProcess()));
	freopen("CON", "w", stdout);

	SetConsoleTitleA("Zm By Syc0x00");
	Console::Log("Console initialized");
	return;
}

void Helpers::Exit(int timer) {
	Sleep(timer);
	Console::Log("Detaching...");
	FreeConsole(); // This way you can close the console without closing BO2
	FreeLibraryAndExitThread(g_DLLMOD, 0);
}

inline int Helpers::Ptr(int address) {
	int *ptr = reinterpret_cast<int *>(address);
	return *ptr; // Return the value of the pointer
}

const char *Helpers::VariableText(const char *format, ...) {
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr); // It should use vsnprintf but meh doesn't matter here

	va_end(argptr);

	return buffer;
}

void Helpers::KeyPress(unsigned char keyCode) {
	Console::Log("Helpers::KeyPress doesn't work yet :(");
	keybd_event(keyCode, 0, 0, 0); //Press down the Key
	keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0); //Release the Key

	return;
}
