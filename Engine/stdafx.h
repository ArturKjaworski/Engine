// stdafx.h: do³¹cz plik do standardowych systemowych plików do³¹czanych,
// lub specyficzne dla projektu pliki do³¹czane, które s¹ czêsto wykorzystywane, ale
// s¹ rzadko zmieniane
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

// TODO: W tym miejscu odwo³aj siê do dodatkowych nag³ówków wymaganych przez program
