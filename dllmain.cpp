#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <time.h>

const int playerBase = 0x017E0A8;
const int entityList = 0x018AC04;
const int baseGame = 0x00400000;
const int ammoOff = 0x0140;
const int hpOff = 0x0EC;
const int nadeOff = 0x0144;
const int armourOff = 0x0F0;
const int yawOff = 0x039;
const int pitchOff = 0x03A;
const int rollOff = 0x03B;
const int nameOff = 0x0205;
const int xPosOff = 0x028;
const int yPosOff = 0x02C;
const int zPosOff = 0x030;
const int xHeadOff = 0x04;
const int yHeadOff = 0x08;
const int zHeadOff = 0x0C;


void ChangeMemory(DWORD baseadress, int value, DWORD offset1, DWORD offset2)
{

	DWORD* adress = (DWORD*)((*(DWORD*)(baseadress + offset1)) + offset2);
	*(int*)adress = value;
}

/*
int ReadMemory(DWORD baseaddress, DWORD offset1, DWORD offset2)
{
	DWORD* address = (DWORD*)((*(DWORD*)(baseaddress + offset1)) + offset2);
	return *(int*)address;
}
*/

void ReadMemory(DWORD baseaddress, DWORD offset1, DWORD offset2, void* value, size_t size)
{
	BYTE* address = (BYTE*)((*(DWORD*)(baseaddress + offset1)) + offset2);
	memcpy(value, address, size);
}

DWORD WINAPI LoopFunction(LPVOID lpParam)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	// Print message to console
	std::cout << "Injection: OK Assault Cube" << "\n";

	bool run = true;
	float xPos, yPos, zPos, Yaw, Pitch, Roll = 0;

	while (run) {
		ChangeMemory(baseGame, 20, playerBase, ammoOff); //ammo
		ChangeMemory(baseGame, 100, playerBase, hpOff); //hp
		ChangeMemory(baseGame, 5, playerBase, nadeOff); //nades
		ChangeMemory(baseGame, 90, playerBase, armourOff); //armour
		ReadMemory(baseGame, playerBase, xPosOff, &xPos, sizeof(xPos));
		std::cout << "xPos: " << xPos << " ";
		Sleep(100);
	}

	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  dwAttached,
	LPVOID lpReserved
)



{
	switch (dwAttached)
	{
	case DLL_PROCESS_ATTACH:

		//MessageBoxA(0, "Injection: OK ", "Assault Cube ", 0);
		CreateThread(NULL, 0, &LoopFunction, NULL, 0, NULL);

		break;
	case DLL_PROCESS_DETACH:
		//MessageBoxA(0, "DLL Unloaded", "Assault Cube ", 0);
		std::cout << "Injection: Bye Bye Assault Cube" << "\n";

		break;
	}
	return TRUE;
}