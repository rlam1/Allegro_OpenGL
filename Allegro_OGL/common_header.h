// Header files of frequent usage

#include <ctime>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>

#include <allegro5\allegro.h>
#include <allegro5\allegro_opengl.h>
#define GLM_FORCE_RADIANS
#define degreesToRadians(x) x*(3.141592f/180.0f)
#include <glm\glm.hpp>

// Some useful defines

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()