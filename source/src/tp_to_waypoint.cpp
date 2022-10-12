#include "../inc/tp_to_waypoint.h"
#include <stdio.h>

/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015 (Source base native)
			(C) Super Cool Ninja 2022 (Source code modification features.)
*/


void load_ground_and_tp_to(Vector3& location)
{
	auto player = PLAYER::PLAYER_PED_ID();

	if (!GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 100.f, &location.z, false))
	{
		static const float groundCheckH[] = {
			0.f, 50.f, 100.f, 150.f,  200.f, 250.f, 300.f, 350.f, 400.f,
				450.f, 500.f, 550.f, 600.f, 650.f, 700.f, 750.f, 800.f
		};


		//Loop trough all the step to check the ground distance
		//Then it load the collision and all the object near
		//Then set the position height so the player don't spawn under the map.
		for (auto const height : groundCheckH)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, location.x, location.y, height, false, false, false);

			WAIT(50);

			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, height, &location.z, false))
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, height);
				STREAMING::LOAD_ALL_OBJECTS_NOW();
				location.z += 3.f;
				break;
			}
		}
	}

	auto playerHeading = ENTITY::GET_ENTITY_HEADING(player);
	ENTITY::SET_ENTITY_COORDS(player, location.x, location.y, location.z, false, false, true, false);
	ENTITY::SET_ENTITY_HEADING(player, playerHeading);

	printf("Player teleported to : %f %f %f\n", location.x, location.y, location.z);
}


void tp_to_waypoint()
{
	auto blip = UI::GET_FIRST_BLIP_INFO_ID(eBlipSprite::BlipSpriteWaypoint);

	if (!UI::DOES_BLIP_EXIST(blip))
	{
		printf("Waypoint not foud !\n");
		return;
	}

	//Get the waypoint coords :
	auto waypoint = UI::GET_BLIP_COORDS(blip);
	load_ground_and_tp_to(waypoint);
}
