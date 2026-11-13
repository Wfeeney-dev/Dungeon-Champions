#include <iostream>
#include "menu/menu.h"

int main(void)
{
	// Initialisation

	enum State menuHovered = State::MENU;
	enum State screenState = State::MENU;

	short int monitorID = GetCurrentMonitor();

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Dungeon Champions");
	SetWindowMinSize(virScreenWidth, virScreenHeight);

	// Everything is drawn into this small texture at the virtual resolution,
	// then stretched to fit the window.
	RenderTexture2D target = LoadRenderTexture(virScreenWidth, virScreenHeight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

	InitAudioDevice();

	GameLoadMenuTextures();
	// ToggleBorderlessWindowed();

	SetTargetFPS(60);

	while (!WindowShouldClose() && application_running)
	{
		// Work out how big the virtual screen is on the window, keeping its aspect ratio
		float winW = (float)GetScreenWidth();
		float winH = (float)GetScreenHeight();
		float scale = winW / virScreenWidth;
		float scaleY = winH / virScreenHeight;
		if (scaleY < scale) scale = scaleY;

		float offsetX = (winW - virScreenWidth * scale) * 0.5f;
		float offsetY = (winH - virScreenHeight * scale) * 0.5f;

		// Convert the real mouse position into virtual screen coordinates
		Vector2 mouseWindow = GetMousePosition();
		Vector2 mouseLocation = {
			(mouseWindow.x - offsetX) / scale,
			(mouseWindow.y - offsetY) / scale
		};

		// Update
		//----------------------------------------------------------------------------------
		GameUpdateMenu(&screenState, &menuHovered, mouseLocation);

		// Draw
		//----------------------------------------------------------------------------------
		BeginTextureMode(target);
			ClearBackground(BLACK);
			GameDrawMenu(&screenState, &menuHovered);
		EndTextureMode();

		BeginDrawing();
			ClearBackground(BLACK);

			// Flip vertically: render textures are stored upside down
			Rectangle src = { 0.0f, 0.0f, (float)virScreenWidth, -(float)virScreenHeight };
			Rectangle dst = { offsetX, offsetY, virScreenWidth * scale, virScreenHeight * scale };
			Vector2 origin = { 0.0f, 0.0f };
			DrawTexturePro(target.texture, src, dst, origin, 0.0f, WHITE);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadRenderTexture(target);
	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
