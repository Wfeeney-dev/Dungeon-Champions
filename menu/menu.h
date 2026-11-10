#pragma once
#include <raylib.h>
#include "../helpers/globals.h"

enum State {
	MENU = 0,
	PLAY = 1,
	SETTINGS = 2,
	QUIT = 3
};

void GameLoadMenuTextures();

void GameUpdateMenu(enum State* screenState, enum State* menuHovered, Vector2 mouseLocation);

void GameDrawMenu(enum State* screenState, enum State* menuHovered);

