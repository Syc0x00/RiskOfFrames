#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4326) // main should be int bullshit

// win
#include "targetver.h"
#include <windows.h>

// std
#include <iostream>
#include <mutex>

// d3d
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// self
#include "Helpers.h"
#include "Fullscreen.h"
