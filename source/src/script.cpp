#include "../inc/script.h"
#include "../inc/keyboard.h"
#include "../inc/tp_to_waypoint.h"
#include <stdio.h>


/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015 (Source base native)
			(C) Super Cool Ninja 2022 (Source code modification features.)
*/


const short KEY_E = { 38 };


void update_features()
{
	while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE))
		WAIT(0);


	//If E is pressed 
	if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, KEY_E))
		tp_to_waypoint();
}




void mainThread()
{
	printf("Main thread loaded ! \n");

	while (true)
	{
		update_features();
		WAIT(0);
	}
}



void ScriptMain()
{
	AllocConsole();
	SetConsoleTitle("GTA_CONSOLE DEBUG MODE.");
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	srand(GetTickCount());
	mainThread();
}
