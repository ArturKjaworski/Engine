// stdafx.h: do��cz plik do standardowych systemowych plik�w do��czanych,
// lub specyficzne dla projektu pliki do��czane, kt�re s� cz�sto wykorzystywane, ale
// s� rzadko zmieniane
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include "iostream"
#include "string"
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include "PxPhysicsAPI.h"
#include "Vec3.h"
#include <time.h>
#include <windows.h>

#define PI 3.1415
#define FPS 60.f
#define SIM_TIME 1.f/FPS

using namespace std;
using namespace physx;

// TODO: W tym miejscu odwo�aj si� do dodatkowych nag��wk�w wymaganych przez program
