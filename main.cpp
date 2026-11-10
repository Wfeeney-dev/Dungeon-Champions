#include <iostream>
#include "menu/menu.h"

//Seperating Drawing and Updating Main Menu from the Main Loop

int main(void)
{	

	// Initialisation
	
	enum State menuHovered = State::MENU;
	enum State screenState = State::MENU;

	short int monitorID = GetCurrentMonitor();

	InitWindow(screenWidth, screenHeight, "Dungeon Champions");
	InitAudioDevice();

	GameLoadMenuTextures();
	// ToggleBorderlessWindowed();
	
	SetTargetFPS(60);

	while (application_running)
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here

		application_running = !WindowShouldClose();

		Vector2 mouseLocation = GetMousePosition();
		// std::cout << "Mouse Location X and Y: " << mouseLocation.x << " "<< mouseLocation.y;

		// Hit area uses the wider selected texture (it includes the swords), centred like the button

		GameUpdateMenu(&screenState, &menuHovered, mouseLocation);

		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(RAYWHITE);
			// Main Menu
			//----------------------------------------------------------------------------------
			GameDrawMenu(&screenState, &menuHovered);
			//----------------------------------------------------------------------------------
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}