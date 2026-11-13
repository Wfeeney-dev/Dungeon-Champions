#include "menu.h"

// Main Menu
Image bgImage;
Texture2D bgTexture;

Image titleImage;
Texture2D titleTexture;

Image scrollImage;
Texture2D scrollTexture;

Image playUnselectedImage;
Texture2D playUnselectedTexture;

Image playSelectedImage;
Texture2D playSelectedTexture;

Image settingsUnselectedImage;
Texture2D settingsUnselectedTexture;

Image settingsSelectedImage;
Texture2D settingsSelectedTexture;

Image quitUnselectedImage;
Texture2D quitUnselectedTexture;

Image quitSelectedImage;
Texture2D quitSelectedTexture;

// Settings Menu Textures
Image tempSettingsImage;
Texture2D tempSettingsTexture;

void GameLoadMenuTextures() 
{
	// Main Menu Textures
	bgImage = LoadImage("assets\\title_screen\\menu_background.png");
	bgTexture = LoadTextureFromImage(bgImage);

	titleImage = LoadImage("assets\\title_screen\\menu_title.png");
	titleTexture = LoadTextureFromImage(titleImage);

	scrollImage = LoadImage("assets\\title_screen\\menu_scroll.png");
	scrollTexture = LoadTextureFromImage(scrollImage);

	playUnselectedImage = LoadImage("assets\\title_screen\\menu_play.png");
	playUnselectedTexture = LoadTextureFromImage(playUnselectedImage);

	playSelectedImage = LoadImage("assets\\title_screen\\menu_play_selected.png");
	playSelectedTexture = LoadTextureFromImage(playSelectedImage);

	settingsUnselectedImage = LoadImage("assets\\title_screen\\menu_settings.png");
	settingsUnselectedTexture = LoadTextureFromImage(settingsUnselectedImage);

	settingsSelectedImage = LoadImage("assets\\title_screen\\menu_settings_selected.png");
	settingsSelectedTexture = LoadTextureFromImage(settingsSelectedImage);

	quitUnselectedImage = LoadImage("assets\\title_screen\\menu_quit.png");
	quitUnselectedTexture = LoadTextureFromImage(quitUnselectedImage);

	quitSelectedImage = LoadImage("assets\\title_screen\\menu_quit_selected.png");
	quitSelectedTexture = LoadTextureFromImage(quitSelectedImage);

	// Settings Menu Textures
	tempSettingsImage = LoadImage("assets\\title_screen\\menu_settings.png");
	tempSettingsTexture = LoadTextureFromImage(tempSettingsImage);
}

void GameUpdateMenu(enum State* screenState, enum State* menuHovered, Vector2 mouseLocation)
{
	int playY = virScreenHeight / 2 + 25;
	int settingsY = virScreenHeight / 2 + 65;
	int quitY = virScreenHeight / 2 + 105;

	if (*screenState == State::MENU)
	{
		Rectangle playBounds = {
			(float)(virScreenWidth / 2 - playSelectedTexture.width / 2),
			(float)playY,
			(float)playSelectedTexture.width,
			(float)playSelectedTexture.height
		};

		Rectangle settingsBounds = {
			(float)(virScreenWidth / 2 - settingsSelectedTexture.width / 2),
			(float)settingsY,
			(float)settingsSelectedTexture.width,
			(float)settingsSelectedTexture.height
		};

		Rectangle quitBounds = {
			(float)(virScreenWidth / 2 - quitSelectedTexture.width / 2),
			(float)quitY,
			(float)quitSelectedTexture.width,
			(float)quitSelectedTexture.height
		};

		bool playHovered = CheckCollisionPointRec(mouseLocation, playBounds);
		bool settingsHovered = CheckCollisionPointRec(mouseLocation, settingsBounds);
		bool quitHovered = CheckCollisionPointRec(mouseLocation, quitBounds);

		if (playHovered)
		{
			*menuHovered = State::PLAY;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { SetMouseCursor(MOUSE_CURSOR_DEFAULT);  *screenState = State::PLAY; return; }
		}
		else if (settingsHovered)
		{
			*menuHovered = State::SETTINGS;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { SetMouseCursor(MOUSE_CURSOR_DEFAULT);  *screenState = State::SETTINGS; return; }
		}
		else if (quitHovered)
		{
			*menuHovered = State::QUIT;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) application_running = false; // Exit the game
		}
		else
		{
			*menuHovered = State::MENU;
		}

		SetMouseCursor(*menuHovered ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);
	}

	// Temporay Settings Menu Leading back to main menu
	if (*screenState == State::SETTINGS)
	{
		Rectangle tempSettingsBounds = {
			(float)(virScreenWidth / 2 - tempSettingsTexture.width / 2),
			(float)(virScreenHeight / 2),
			(float)tempSettingsTexture.width,
			(float)tempSettingsTexture.height,
		};

		if (CheckCollisionPointRec(mouseLocation, tempSettingsBounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			*screenState = State::MENU;
		}

	}

	if (*screenState == State::PLAY)
	{
		// Play State Updates
	}
}

void GameDrawMenu(enum State* screenState, enum State* menuHovered)
{

	int playY = virScreenHeight / 2 + 25;
	int settingsY = virScreenHeight / 2 + 65;
	int quitY = virScreenHeight / 2 + 105;

	// Main Menu
	//----------------------------------------------------------------------------------
	if (*screenState == State::MENU)
	{
		DrawTexture(
			bgTexture,
			virScreenWidth / 2 - bgTexture.width / 2,
			virScreenHeight / 2 - bgTexture.height / 2,
			WHITE);
		DrawTexture(
			scrollTexture,
			virScreenWidth / 2 - scrollTexture.width / 2,
			virScreenHeight / 2 + 5,
			WHITE);
		DrawTexture(
			titleTexture,
			virScreenWidth / 2 - titleTexture.width / 2,
			virScreenHeight / 2 - 180,
			WHITE);

		// Play button: swap to the selected version while hovered
		Texture2D playTexture = (*menuHovered == PLAY) ? playSelectedTexture : playUnselectedTexture;
		DrawTexture(
			playTexture,
			virScreenWidth / 2 - playTexture.width / 2,
			playY,
			WHITE);

		Texture2D settingsTexture = (*menuHovered == SETTINGS) ? settingsSelectedTexture : settingsUnselectedTexture;
		DrawTexture(
			settingsTexture,
			virScreenWidth / 2 - settingsTexture.width / 2,
			settingsY,
			WHITE);

		Texture2D quitTexture = (*menuHovered == QUIT) ? quitSelectedTexture : quitUnselectedTexture;
		DrawTexture(
			quitTexture,
			virScreenWidth / 2 - quitTexture.width / 2,
			quitY,
			WHITE);
	}
	//----------------------------------------------------------------------------------
	// Settings Menu
	if (*screenState == State::SETTINGS)
	{
		DrawTexture(
			bgTexture,
			virScreenWidth / 2 - bgTexture.width / 2,
			virScreenHeight / 2 - bgTexture.height / 2,
			WHITE);

		DrawTexture(
			tempSettingsTexture,
			virScreenWidth / 2 - tempSettingsTexture.width / 2,
			virScreenHeight / 2,
			WHITE);
	}
	//----------------------------------------------------------------------------------
	// Play State
	if (*screenState == State::PLAY)
	{
		// Game Drawing
	}
	//----------------------------------------------------------------------------------
}