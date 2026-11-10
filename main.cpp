#include <iostream>
#include <raylib.h>

int main(void)
{	

	// Initialisation
	bool application_running = true;
	
	enum State {
		MENU = 0,
		PLAY = 1,
		SETTINGS = 2,
		QUIT = 3
	};
	enum State menuHovered = State::MENU;
	enum State screenState = State::MENU;

	short int monitorID = GetCurrentMonitor();

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Dungeon Champions");
	InitAudioDevice();
	// ToggleBorderlessWindowed();
	

	// Main Menu Textures
	Image bgImage = LoadImage("assets\\title_screen\\menu_background.png");
	Texture2D bgTexture = LoadTextureFromImage(bgImage);
	
	Image titleImage = LoadImage("assets\\title_screen\\menu_title.png");
	Texture2D titleTexture = LoadTextureFromImage(titleImage);

	Image scrollImage = LoadImage("assets\\title_screen\\menu_scroll.png");
	Texture2D scrollTexture = LoadTextureFromImage(scrollImage);

	Image playUnselectedImage = LoadImage("assets\\title_screen\\menu_play.png");
	Texture2D playUnselectedTexture = LoadTextureFromImage(playUnselectedImage);

	Image playSelectedImage = LoadImage("assets\\title_screen\\menu_play_selected.png");
	Texture2D playSelectedTexture = LoadTextureFromImage(playSelectedImage);

	Image settingsUnselectedImage = LoadImage("assets\\title_screen\\menu_settings.png");
	Texture2D settingsUnselectedTexture = LoadTextureFromImage(settingsUnselectedImage);

	Image settingsSelectedImage = LoadImage("assets\\title_screen\\menu_settings_selected.png");
	Texture2D settingsSelectedTexture = LoadTextureFromImage(settingsSelectedImage);

	Image quitUnselectedImage = LoadImage("assets\\title_screen\\menu_quit.png");
	Texture2D quitUnselectedTexture = LoadTextureFromImage(quitUnselectedImage);

	Image quitSelectedImage = LoadImage("assets\\title_screen\\menu_quit_selected.png");
	Texture2D quitSelectedTexture = LoadTextureFromImage(quitSelectedImage);

	// Settings Menu Textures
	Image tempSettingsImage = LoadImage("assets\\title_screen\\menu_settings.png");
	Texture2D tempSettingsTexture = LoadTextureFromImage(tempSettingsImage);

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
		int playY = screenHeight / 2 + 25;
		int settingsY = screenHeight / 2 + 65;
		int quitY = screenHeight / 2 + 105;

		if (screenState == State::MENU)
		{
			Rectangle playBounds = {
				(float)(screenWidth / 2 - playSelectedTexture.width / 2),
				(float)playY,
				(float)playSelectedTexture.width,
				(float)playSelectedTexture.height
			};

			Rectangle settingsBounds = {
				(float)(screenWidth / 2 - settingsSelectedTexture.width / 2),
				(float)settingsY,
				(float)settingsSelectedTexture.width,
				(float)settingsSelectedTexture.height
			};

			Rectangle quitBounds = {
				(float)(screenWidth / 2 - quitSelectedTexture.width / 2),
				(float)quitY,
				(float)quitSelectedTexture.width,
				(float)quitSelectedTexture.height
			};

			bool playHovered = CheckCollisionPointRec(mouseLocation, playBounds);
			bool settingsHovered = CheckCollisionPointRec(mouseLocation, settingsBounds);
			bool quitHovered = CheckCollisionPointRec(mouseLocation, quitBounds);

			if (playHovered)
			{
				menuHovered = State::PLAY;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { SetMouseCursor(MOUSE_CURSOR_DEFAULT);  screenState = State::PLAY; continue; }
			}
			else if (settingsHovered)
			{
				menuHovered = State::SETTINGS;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { SetMouseCursor(MOUSE_CURSOR_DEFAULT);  screenState = State::SETTINGS; continue; }
			}
			else if (quitHovered)
			{
				menuHovered = State::QUIT;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) application_running = false; // Exit the game
			}
			else
			{
				menuHovered = State::MENU;
			}

			SetMouseCursor(menuHovered ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);
		}

		// Temporay Settings Menu Leading back to main menu
		if (screenState == State::SETTINGS) 
		{
			Rectangle tempSettingsBounds = {
				(float)(screenWidth / 2 - tempSettingsTexture.width / 2),
				(float)(screenHeight / 2),
				(float)tempSettingsTexture.width,
				(float)tempSettingsTexture.height,
			};

			if (CheckCollisionPointRec(mouseLocation, tempSettingsBounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
			{
				screenState = State::MENU;
			}
			
		}


		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(RAYWHITE);
			// Main Menu
			//----------------------------------------------------------------------------------
			if (screenState == State::MENU)
			{
				DrawTexture(
					bgTexture,
					screenWidth / 2 - bgTexture.width / 2,
					screenHeight / 2 - bgTexture.height / 2,
					WHITE);
				DrawTexture(
					scrollTexture,
					screenWidth / 2 - scrollTexture.width / 2,
					screenHeight / 2 + 5,
					WHITE);
				DrawTexture(
					titleTexture,
					screenWidth / 2 - titleTexture.width / 2,
					screenHeight / 2 - 180,
					WHITE);

				// Play button: swap to the selected version while hovered
				Texture2D playTexture = (menuHovered == PLAY) ? playSelectedTexture : playUnselectedTexture;
				DrawTexture(
					playTexture,
					screenWidth / 2 - playTexture.width / 2,
					playY,
					WHITE);

				Texture2D settingsTexture = (menuHovered == SETTINGS) ? settingsSelectedTexture : settingsUnselectedTexture;
				DrawTexture(
					settingsTexture,
					screenWidth / 2 - settingsTexture.width / 2,
					settingsY,
					WHITE);

				Texture2D quitTexture = (menuHovered == QUIT) ? quitSelectedTexture : quitUnselectedTexture;
				DrawTexture(
					quitTexture,
					screenWidth / 2 - quitTexture.width / 2,
					quitY,
					WHITE);
			}
			if (screenState == State::SETTINGS)
			{
				DrawTexture(
					bgTexture,
					screenWidth / 2 - bgTexture.width / 2,
					screenHeight / 2 - bgTexture.height / 2,
					WHITE);

				DrawTexture(
					tempSettingsTexture,
					screenWidth / 2 - tempSettingsTexture.width / 2,
					screenHeight / 2,
					WHITE);
			}
			//----------------------------------------------------------------------------------
		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}