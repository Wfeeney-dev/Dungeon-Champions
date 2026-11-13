#pragma once
#include <raylib.h>

const int virScreenWidth = 640;
const int virScreenHeight = 360;
const int virScale = 3;

const int screenWidth = virScreenWidth * virScale;
const int screenHeight = virScreenHeight * virScale;

inline bool application_running = true;