#pragma once

#ifndef DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // !DEBUG

#define PI  3.141590
#define DEG 57.29582
#define RAD 0.017453

#define DEGTORAD 0.017453f
#define RADTODEG 57.29577f

#include "SettingsConfig.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <cmath>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <Windows.h>

class System;

using std::cout;
using std::endl;
using std::to_string;
using std::cos; 
using std::cosf;
using std::sin;
using std::sinf;
using std::atanf;
using std::make_shared;

using std::vector;
using std::string;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
typedef unsigned int uint;
typedef sf::SoundBuffer Buff;
typedef sf::Vector2i v2i;
typedef sf::Vector2f v2f;
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;
