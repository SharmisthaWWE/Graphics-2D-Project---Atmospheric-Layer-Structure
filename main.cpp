#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <SOIL.h>
#include<stdarg.h>
using namespace std;

int segments = 1000;float cx = 0, cy = -40, radius = 20;//For Earth
int segmentsb = 1000;float cxb = 0, cyb = 7, radiusb = 3;// For Ballon
int segmentsc1 = 1000;float cxc1 = 0, cyc1 = 25, radiusc1 = 0.75;// For Commet1
float cxc2 = 3, cyc2 = 25, radiusc2 = 0.75;// For Commet2
float cxc3 = 6, cyc3 = 25, radiusc3 = 0.75;// For Commet3
float cxc4 = -1.5, cyc4 = 20, radiusc4 = 0.75;// For Commet4
float cxc5 = 1.5, cyc5 = 20, radiusc5 = 0.75;// For Commet5
float cxc6 = 4.5, cyc6 = 20, radiusc6 = 0.75;// For Commet6
float cxc7 = 7.5, cyc7 = 20, radiusc7 = 0.75;// For Commet7
float Tropo_x = 0.0, Tropo_y = -2.0;
float Strato_x = 0.0, Strato_y = 0.0;
float Meso_x = 0.0, Meso_y = 10.0;
float Thermo_x = 0.0, Thermo_y = 0.0;
float Exo_x = 7.0, Exo_y = 0.0;
float sun_x = 0.0, sun_y = -50.0;
float Earth_x = 0.0, Earth_y = 0.0;
float Violate_x = 0.0, Violate_y = 0.0;

int refreshTime = 900, refresh = 100;
int state = 0, sunColor = 0, starBlink = 0, ultraViolet = 0, effect = 0, Thunder = 0, ThunderVary = 0, Blink = 0, Night = 0, Music = 1;
string  MusicPath;
char* PointBackgroundMusic = NULL;
char* PointThunderMusic = NULL;
char* PointStopMusic = NULL;

//For Font
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
GLvoid *font_style1 = GLUT_BITMAP_HELVETICA_18;

int Earth[150][100] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void init()
{
    glClearColor(175.0/255.0, 238.0/255.0, 238.0/255.0, 0.0);

    glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);

    glShadeModel(GL_SMOOTH);
}

void ainit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);
}

void printDetail(float x, float y, float z, char* format, ...)
{
    va_list arg_list;
    char str[1000];

    va_start(arg_list, format);
    vsprintf(str, format, arg_list);
    va_end(arg_list);

    glRasterPos3f(x, y, z);

    for(int i=0; str[i] != '\0'; i++)
    {
        glutBitmapCharacter(font_style, str[i]);
    }
}

void printName(float x, float y, float z, char* format, ...)
{
    va_list arg_list;
    char str[1000];

    va_start(arg_list, format);
    vsprintf(str, format, arg_list);
    va_end(arg_list);

    glRasterPos3f(x, y, z);

    for(int i=0; str[i] != '\0'; i++)
    {
        glutBitmapCharacter(font_style1, str[i]);
    }
}

void Star_Draw(float vertex, float vertexy)
{
    float x = vertex, y = vertexy;

    glBegin(GL_LINE_STRIP);
        glVertex3f(x, y, 0.0);
        glVertex3f(x+1, y-1, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f(x+1, y, 0.0);
        glVertex3f(x, y-1, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f((x+x+1)/2, y, 0.0);
        glVertex3f((x+x+1)/2, y-1, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f(x, (y+y-1)/2, 0.0);
        glVertex3f(x+1, (y+y-1)/2, 0.0);
    glEnd();
}

void DrawCircle(float cxg, float cyg, float radiusg)
{
    for(int i = 0; i < segments; i++)
    {
        float theta = 2.0 * 3.1416 * (float) i/ (float) segments;
        float x = radiusg * cos(theta);
        float y = radiusg * sin(theta);
        glVertex2f(x+cxg, y+cyg);
    }
}

void DrawEllipse(float cxg, float cyg, float radiusg)
{
    for(int i = segments - 1; i >= 0; i--)
    {
        float theta = 2.0 * (-1.5708) * (float) i/ (float) segments;
        float x = radiusg * cos(theta);
        float y = radiusg * sin(theta);
        glVertex2f(x+cxg, y+cyg);
    }
}

void Timer(int time)
{
    if(state == 0)
    {
        Tropo_x -= 2;
        if(Tropo_x <= -25.0) Tropo_x = 15.0;

        Strato_x -= 1;
        if(Strato_x <= -23.0) Strato_x = 13.0;

        Thermo_x -= 2;
        if(Thermo_x <= -90.0) Thermo_x = 20.0;

        Exo_x -= 2;
        if(Exo_x <= -60.0) Exo_x = 15.0;

        starBlink++;

        if(Blink >= 4) Blink = 0;
        else Blink++;
    }

    glutPostRedisplay();
    glutTimerFunc(refreshTime, Timer, 0);
}

void Timer1(int time)
{
    if(state == 0)
    {
        if(Earth_x <= -27.5) Earth_x = 3.0;
        else Earth_x -= 1;

        if(sun_x >= 105.8)
        {
            sun_x += 0.3;
            sun_y -= 0.6;
        }
        else if(sun_x >= 10.8 && sun_y >= 21.5)
        {
            sun_x += 0.3;
        }
        else{
            sun_x += 0.1;
            sun_y += 0.6;
        }

        if(sun_x >= 142.8)
        {
            sun_x = 0.0;
            sun_y = -50.0;
        }

        if(sunColor == 0) sunColor = 1;
        else sunColor = 0;

        if(Violate_y <= -35.0 && effect == 1) effect = 0;
        else if(Violate_y > -35.0 && effect == 1)
        {
            Violate_x -= 0.1;
            Violate_y -= 0.6;
        }

        if(Thunder == 1 && ThunderVary > 0) ThunderVary++;

        Meso_y -= 0.8;
        if(Meso_y <= -5.0) Meso_y = 30.0;
    }

    if(Music == 1) PlaySound(PointBackgroundMusic, NULL, SND_ASYNC| SND_FILENAME| SND_LOOP| SND_NOSTOP| SND_NOWAIT);

    glutPostRedisplay();
    glutTimerFunc(refresh, Timer1, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix

    //Earth er Code

    glColor3f(99.0/255.0, 184.0/255.0, 255.0/255.0);
    glPushMatrix();
        glBegin(GL_POLYGON);
            DrawCircle(cx, cy, radius);
        glEnd();

        glPushMatrix();
            glTranslatef(Earth_x, Earth_y, 0.0);
            glColor3f(70.0/255.0, 179.0/255.0, 113.0/255.0);
            float ex = -17.5, ey = -30.0;
            for(int i=0;i<=60;i++)
            {
                for(int j=0;j<70;j++)
                {
                    if(Earth[i][j] == 1)
                    {
                        glBegin(GL_LINE_LOOP);
                        glVertex3f(ex, ey, 0.0);
                        glVertex3f(ex+1, ey, 0.0);
                        glVertex3f(ex+1, ey, 0.0);
                        glVertex3f(ex, ey, 0.0);
                        glEnd();
                    }
                    ex++;
                }
                if(i<10) ex -= (70+0.3);
                else ex -= (70-0.3);
                ey -= 0.3;
            }
            glEnd();
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
            DrawEllipse(1.0, -58.0, 2);
            DrawEllipse(0.0, -58.0, 2);
            DrawEllipse(-1.0, -58.0, 2);
            DrawEllipse(-4.0, -58.0, 2);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex3f(-10.0, -58.0, 0.0);
            glVertex3f(-0.0, -60.0, 0.0);
            glVertex3f(3.0, -57.5, 0.0);
            glVertex3f(5.0, -59.5, 0.0);
            glVertex3f(11.0, -57.0, 0.0);
        glEnd();
    glPopMatrix();

    //Troposphere Code

    glColor3d(135.0/255.0, 206.0/255.0, 235.0/255.0);
    glBegin(GL_POLYGON);
        glVertex3f(-15, -5,0);
        glVertex3f(-10, -20,0);
        glVertex3f(10, -20,0);
        glVertex3f(15, -5,0);
    glEnd();

    glPushMatrix();      //Plane Code
        glTranslatef(Tropo_x, Tropo_y, 0.0);
        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(8.0, -10.0, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(-2.5, -10.0, 0.0);
            glColor3f(238.0/255.0, 174.0/255.0, 238.0/255.0);
            glVertex3f(-5.0, -11.5, 0.0);
            glColor3f(238.0/255.0, 174.0/255.0, 238.0/255.0);
            glVertex3f(6.5, -11.5, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(6.5, -10.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex3f(2.0, -10.0, 0.0);
            glVertex3f(-2.0, -10.0, 0.0);
            glColor3f(238.0/255.0, 174.0/255.0, 238.0/255.0);
            glVertex3f(5.5, -15.0, 0.0);
        glEnd();

         glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(2.0, -10.0, 0.0);
            glColor3f(238.0/255.0, 174.0/255.0, 238.0/255.0);
            glVertex3f(0.0, -10.0, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(6.0, -7.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(238.0/255.0, 174.0/255.0, 238.0/255.0);
            glVertex3f(6.5, -11.5, 0.0);
            glVertex3f(8.5, -14.0, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(7.5, -11.0, 0.0);
            glVertex3f(8.5, -8.5, 0.0);
            glVertex3f(6.5, -10.0, 0.0);
        glEnd();
    glPopMatrix();

    //Stratosphere Code

    glColor3f(99.0/255.0, 184.0/255.0, 255.0/255.0);
    glBegin(GL_POLYGON);
        glVertex3f(-20, 11,0);
        glVertex3f(-15, -5,0);
        glVertex3f(15, -5,0);
        glVertex3f(20, 11,0);
    glEnd();

    glPushMatrix();
    glTranslatef(Strato_x, Strato_y, 0.0);
        glBegin(GL_LINE_STRIP);       //Ballon Er Dati Code
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(-2.0, 5.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glColor3f(255.0/255.0, 192.0/255.0, 203.0/255.0);
            glVertex3f(0.0, 5.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(2.0, 5.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
        glEnd();

        glColor3f(1.0, 1.0, 0.0);        //Ballon Er Code
        glBegin(GL_POLYGON);
            DrawCircle(cxb, cyb, radiusb);
        glEnd();
    glPopMatrix();

    //Mesosphere

    glColor3f(30.0/255.0, 144.0/255.0, 255.0/255.0);
    glBegin(GL_POLYGON);
        glVertex3f(-25, 29,0);
        glVertex3f(-20, 11,0);
        glVertex3f(20, 11,0);
        glVertex3f(25, 29,0);
    glEnd();

    glPushMatrix();       //Commet Code
        glTranslatef(Meso_x, Meso_y, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
            DrawCircle(cxc1, cyc1, radiusc1);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc2, cyc2, radiusc2);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc3, cyc3, radiusc3);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc4, cyc4, radiusc4);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc5, cyc5, radiusc5);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc6, cyc6, radiusc6);
        glEnd();

        glBegin(GL_POLYGON);
            DrawCircle(cxc7, cyc7, radiusc7);
        glEnd();

    //Commet Dati Code      //Left to Right

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(-0.5, 25.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(0.5, 28.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(0.5, 25.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(2.5, 25.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(3.5, 28.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(3.5, 25.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(5.5, 25.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(6.5, 28.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(6.5, 25.0, 0.0);
        glEnd();

        //Commet Dati Code  //Right to Left

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(7.0, 20.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(8.0, 23.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(8.0, 20.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(4.0, 20.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(5.0, 23.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(5.0, 20.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(1.0, 20.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(2.0, 23.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(2.0, 20.0, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(-2.0, 20.0, 0.0);
            glColor3f(250.0/255.0, 128.0/255.0, 114/255);
            glVertex3f(-1.0, 23.0, 0.0);
            glColor3f(1.0, 1.0, 224/255);
            glVertex3f(-1.0, 20.0, 0.0);
        glEnd();
    glPopMatrix();

    //Thermosphere

    glColor3f(72.0/255.0, 118.0/255.0, 255.0/255.0);
    glBegin(GL_POLYGON);
        glVertex3f(-30, 46,0);
        glColor3f(67.0/255.0, 110.0/255.0, 238.0/255.0);
        glVertex3f(-25, 29,0);
        glColor3f(67.0/255.0, 110.0/255.0, 238.0/255.0);
        glVertex3f(25, 29,0);
        glColor3f(72.0/255.0, 118.0/255.0, 255.0/255.0);
        glVertex3f(30, 46,0);
    glEnd();

    glPushMatrix();        // Cloud Code
        glTranslatef(Thermo_x, Thermo_y, 0.0);
        glBegin(GL_POLYGON);
            glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);
            DrawCircle(20.0, 40.0, 5);
            glColor3f(1.0, 1.0, 1.0);
            DrawCircle(23.0, 41.0, 5);
            glColor3f(245.0/255.0, 245.0/255.0, 245.0/255.0);
            DrawCircle(27.0, 38.0, 6);
            glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);
            DrawCircle(12.0, 38.0, 7);
            glColor3f(245.0/255.0, 245.0/255.0, 245.0/255.0);
            DrawCircle(18.0, 36.0, 6.6);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);
            DrawCircle(45.0, 36.0, 5.0);
            glColor3f(245.0/255.0, 245.0/255.0, 245.0/255.0);
            DrawCircle(50.0, 37.0, 5.0);
            glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);
            DrawCircle(54.0, 35.0, 5.0);
        glEnd();

        //Thunder Effect

        if(Thunder == 1)
        {
            if(ThunderVary == 40)
            {
                ThunderVary = 0;
                Thunder = 0;
            }
            else if(ThunderVary >= 1)
            {
                if(ThunderVary % 2 == 1) glColor3f(190.0/255.0, 190.0/255.0, 190.0/255.0);
                else glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);

                glBegin(GL_POLYGON);
                    glVertex3f(35.0, 45.0, 0.0);
                    glVertex3f(15.0, 40.0, 0.0);
                    glVertex3f(15.0, 42.9, 0.0);
                glEnd();

                glBegin(GL_POLYGON);
                    glVertex3f(15.0, 40.0, 0.0);
                    glVertex3f(15.0, 42.9, 0.0);
                    glVertex3f(30.0, 37.0, 0.0);
                    glVertex3f(30.0, 34.5, 0.0);
                glEnd();

                glBegin(GL_POLYGON);
                    glVertex3f(30.0, 37.0, 0.0);
                    glVertex3f(13.0, 31.0, 0.0);
                    glVertex3f(30.0, 34.5, 0.0);
                glEnd();
            }
        }
    glPopMatrix();

    // Exosphere

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-35, 66,0);
        glVertex3f(-30, 46,0);
        glVertex3f(30, 46,0);
        glVertex3f(35, 66,0);
    glEnd();

        if(starBlink%5 == 1) glColor3f(1.0, 1.0, 1.0);
        else glColor3f(0.0, 0.0, 1.0);
        Star_Draw(-30.0, 60.0);
        if(starBlink%3 == 1) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(1.0, 1.0, 1.0);
        Star_Draw(-20.0, 60.0);
        if(starBlink%5 == 0) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(1.0, 1.0, 1.0);
        Star_Draw(-25.0, 60.0);
        Star_Draw(30.0, 60.0);
        if(starBlink%6 == 1) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(255.0/255.0, 250.0/255.0, 240.0/255.0);
        Star_Draw(0.0, 60.0);
        if(starBlink%3 == 0) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(1.0, 1.0, 1.0);
        Star_Draw(-23.0, 55.0);
        if(starBlink%6 == 0) glColor3f(1.0, 1.0, 1.0);
        else glColor3f(0.0, 0.0, 1.0);
        Star_Draw(-27.0, 55.0);
        Star_Draw(-10.0, 55.0);

    glPushMatrix();
        glTranslatef(Exo_x, Exo_y, 0.0);
        glColor3f(205.0/255.0, 181.0/255.0, 205.0/255.0);
        glBegin(GL_LINE);
            glRectf(27.0, 59.0, 20.0, 53.0);
            glColor3f(139.0/255.0, 139.0/255.0, 122.0/255.0);
            glRectf(23.0, 60.0, 22.0, 59.0);
            glRectf(23.0, 52.0, 22.0, 53.0);

            //Waves Right

            if(Blink == 1) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(28.0, 65.0, 26.5, 61.0);
            if(Blink == 2) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(26.0, 65.0, 24.5, 61.0);
            if(Blink == 3) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(24.0, 65.0, 22.5, 61.0);
            if(Blink == 4) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(22.0, 65.0, 20.5, 61.0);

            //Waves Left

            if(Blink == 1) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(28.0, 47.0, 26.5, 51.0);
            if(Blink == 2) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(26.0, 47.0, 24.5, 51.0);
            if(Blink == 3) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(24.0, 47.0, 22.5, 51.0);
            if(Blink == 4) glColor3d(255.0/255.0, 0.0/255.0, 255.0/255.0);
            else glColor3d(127.0/255.0, 255.0/255.0, 212.0/255.0);
            glRectf(22.0, 47.0, 20.5, 51.0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(122.0/255.0, 55.0/255.0, 139.0/255.0);
            glVertex3f(27.0, 57.0, 0.0);
            glColor3f(255.0/255.0, 187.0/255.0, 255.0/255.0);
            glVertex3f(20.0, 57.0, 0.0);
            glColor3f(255.0/255.0, 187.0/255.0, 255.0/255.0);
            glVertex3f(20.0, 55.0, 0.0);
            glColor3f(122.0/255.0, 55.0/255.0, 139.0/255.0);
            glVertex3f(27.0, 55.0, 0.0);
        glEnd();

        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
            glVertex3f(20.0, 59.0, 0.0);
            glVertex3f(18.5, 58.0, 0.0);
            glVertex3f(18.5, 54.0, 0.0);
            glVertex3f(20.0, 53.0, 0.0);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();

   glColor3f(175.0/255.0, 238.0/255.0, 238.0/255.0);
   glBegin(GL_POLYGON);
        glVertex3f(-90.0, 70.0, 0.0);
        glVertex3f(-90.0, -20.0, 0.0);
        glVertex3f(-10.5, -20.0, 0.0);
        glVertex3f(-37.5, 70.0, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
        glVertex3f(80.0, 70.0, 0.0);
        glVertex3f(80.0, -20.0, 0.0);
        glVertex3f(10.5, -20.0, 0.0);
        glVertex3f(37.5, 70.0, 0.0);
   glEnd();

   glColor3f(0.0, 0.0, 0.0);
   printDetail(-50.0, -15.0, 0.0, "%s", "Troposphere");
   printDetail(-50.0, 3.0, 0.0, "%s", "Stratosphere");
   printDetail(-50.0, 20.0, 0.0, "%s", "Mesosphere");
   printDetail(-50.0, 37.0, 0.0, "%s", "Thermosphere");
   printDetail(-50.0, 52.0, 0.0, "%s", "Exosphere");
   printName(16.0, -6.5, 0.0, "%s", "20km");
   printName(21.0, 9.0, 0.0, "%s", "50km");
   printName(26.0, 27.5, 0.0, "%s", "85km");
   printName(31.0, 44, 0.0, "%s", "690km");
   printName(36.0, 64, 0.0, "%s", "10,000km");

    //Sun er code

   glPushMatrix();

       glTranslatef(sun_x, sun_y, 0.0);
       if(sunColor == 0) glColor3f(255.0/255.0, 165.0/255.0, 0.0/255.0);
       else glColor3f(255.0/255.0, 99.0/255.0, 71.0/255.0);
       glBegin(GL_POLYGON);
           glVertex3f(-65.0, 69.0, 0.0);
           glVertex3f(-75.0, 59.0, 0.0);
           glVertex3f(-65.0, 51.0, 0.0);
       glEnd();

       if(sunColor == 0) glColor3f(255.0/255.0, 99.0/255.0, 71.0/255.0);
       else glColor3f(255.0/255.0, 165.0/255.0, 0.0/255.0);
       glBegin(GL_POLYGON);
           glVertex3f(-66.0, 52.0, 0.0);
           glVertex3f(-60.0, 44.0, 0.0);
           glVertex3f(-54.0, 52.0, 0.0);
       glEnd();

       if(sunColor == 0) glColor3f(255.0/255.0, 165.0/255.0, 0.0/255.0);
       else glColor3f(255.0/255.0, 99.0/255.0, 71.0/255.0);
       glBegin(GL_POLYGON);
           glVertex3f(-55.0, 69.0, 0.0);
           glVertex3f(-45.0, 59.0, 0.0);
           glVertex3f(-55.0, 51.0, 0.0);
       glEnd();

       if(sunColor == 0) glColor3f(255.0/255.0, 99.0/255.0, 71.0/255.0);
       else glColor3f(255.0/255.0, 165.0/255.0, 0.0/255.0);
       glBegin(GL_POLYGON);
           glVertex3f(-66.0, 67.0, 0.0);
           glVertex3f(-60.0, 75.0, 0.0);
           glVertex3f(-53.0, 67.0, 0.0);
       glEnd();

       glColor3f(1.0, 1.0, 0.0);
       glBegin(GL_POLYGON);
            DrawCircle(-60.0, 60.0, 10.0);
       glEnd();

       glColor3f(248.0/255.0, 248.0/255.0, 255.0/255.0);
       glBegin(GL_POLYGON);
            DrawEllipse(-60.0, 55.0, 3.5);
       glEnd();

       glColor3f(0.0, 0.0, 0.0);
       glBegin(GL_POLYGON);
            DrawCircle(-65.0, 61.5, 2.5);
       glEnd();

      glBegin(GL_POLYGON);
            DrawCircle(-55.0, 61.5, 2.5);
       glEnd();

      glBegin(GL_LINE_STRIP);
            glVertex3f(-68.9, 64.5, 0.0);
            glVertex3f(-65.0, 61.5, 0.0);
            glVertex3f(-55.0, 61.5, 0.0);
            glVertex3f(-50.5, 64.5, 0.0);
       glEnd();

    glPopMatrix();

    if(ultraViolet == 1 && sun_x >= 48.0 && sun_x <= 68.0)      //UltraViolet Ray
    {
        effect = 1;

        glColor3f(255.0/255.0, 250.0/255.0, 205.0/255.0);
        glBegin(GL_POLYGON);
            DrawEllipse(0.0, 67.0, 20);
        glEnd();

        glColor3f(255.0/255.0, 248.0/255.0, 220.0/255.0);
        glBegin(GL_POLYGON);
            DrawEllipse(0.0, 67.0, 15);
        glEnd();

        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
            DrawEllipse(0.0, 67.0, 10);
        glEnd();
    }

    if(effect == 1 && sun_x >= 48.0 && sun_x <= 68.0)
    {
        glPushMatrix();
        if(Violate_y > -35.0) glColor3f(199.0/255.0, 21.0/255.0, 133.0/255.0);
        else glColor3f(255.0/255.0, 106.0/255.0, 106.0/255.0);
        glTranslatef(Violate_x, Violate_y, 0.0);
            glBegin(GL_POLYGON);
                glVertex3f(1.0, 45.0, 0.0);
                glVertex3f(0.0, 45.0, 0.0);
                glVertex3f(0.0, 35.0, 0.0);
                glVertex3f(1.0, 35.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(-0.5, 35.0, 0.0);
                glVertex3f(1.5, 35.0, 0.0);
                glVertex3f(0.5, 30.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(-1.0, 45.0, 0.0);
                glVertex3f(-2.0, 45.0, 0.0);
                glVertex3f(-5.0, 35.0, 0.0);
                glVertex3f(-6.0, 35.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(-6.5, 35.0, 0.0);
                glVertex3f(-4.5, 35.0, 0.0);
                glVertex3f(-6.0, 30.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(2.0, 45.0, 0.0);
                glVertex3f(3.0, 45.0, 0.0);
                glVertex3f(5.0, 35.0, 0.0);
                glVertex3f(6.0, 35.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(6.5, 35.0, 0.0);
                glVertex3f(4.5, 35.0, 0.0);
                glVertex3f(6.0, 30.0, 0.0);
            glEnd();

            glBegin(GL_POLYGON);
                glVertex3f(1.0, 45.0, 0.0);
                glVertex3f(0.0, 45.0, 0.0);
                glVertex3f(0.0, 35.0, 0.0);
                glVertex3f(1.0, 35.0, 0.0);
            glEnd();
        glPopMatrix();
    }
    else if(effect == 0)
    {
        Violate_x = 0.0;
        Violate_y = 0.0;
    }

    glColor3f(175.0/255.0, 238.0/255.0, 238.0/255.0);
    glBegin(GL_POLYGON);
        glVertex3f(-70.0, -20.0, 0.0);
        glVertex3f(-70.0, -60.0, 0.0);
        glVertex3f(-15.0, -60.0, 0.0);
        glVertex3f(-20.9, -40.0, 0.0);
        glVertex3f(-15.0, -20.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(-20.0, -35.0, 0.0);
        glVertex3f(-20.0, -45.0, 0.0);
        glVertex3f(-20.9, -45.0, 0.0);
        glVertex3f(-20.9, -35.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(70.0, -20.0, 0.0);
        glVertex3f(70.0, -60.0, 0.0);
        glVertex3f(15.0, -60.0, 0.0);
        glVertex3f(20.9, -40.0, 0.0);
        glVertex3f(15.0, -20.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(20.0, -35.0, 0.0);
        glVertex3f(20.0, -45.0, 0.0);
        glVertex3f(20.9, -45.0, 0.0);
        glVertex3f(20.9, -35.0, 0.0);
    glEnd();

    glFlush();
}

void ShowStrato()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    printName(-74.0, 65.0, 0.0, "%s", "The Stratosphere is the second major layer of Earth's atmosphere, just above the Troposphere");
    printName(-74.0, 58.0, 0.0, "%s", "and below the Mesosphere. It is stratified in temperature with warmer layers higher up and");
    printName(-74.0, 51.0, 0.0, "%s", "cooler layers farther down. This is in contrast to the troposphere near the Earth's surface,");
    printName(-74.0, 44.0, 0.0, "%s", "which is cooler higher up and warmer farther down. The border of the troposphere and ");
    printName(-74.0, 37.0, 0.0, "%s", "stratosphere, the tropopause, is marked by where this inversion begins, which in terms");
    printName(-74.0, 30.0, 0.0, "%s", "of atmospheric thermodynamics is the equilibrium level. At moderate latitudes the ");
    printName(-74.0, 23.0, 0.0, "%s", "stratosphere is situated between about 10–13 km (33,000–43,000 ft.) and 50 km (160,000 ft.)");
    printName(-74.0, 16.0, 0.0, "%s", "altitude above the surface, while at the poles it starts at about 8 km (26,000 ft.) altitude,");
    printName(-74.0, 9.0, 0.0, "%s", " and near the equator it may start at altitudes as high as 18 km (59,000 ft.).");
    printName(-74.0, -5.0, 0.0, "%s", "Temperature: ");
    printName(-74.0, -12.0, 0.0, "%s", "Within this layer, temperature increases as altitude increases the top of the stratosphere has a");
    printName(-74.0, -19.0, 0.0, "%s", " temperature of about 270 K (−3°C or 26.6°F), just slightly below the freezing point of water.");
    printName(-74.0, -30.0, 0.0, "%s", "Life: ");
    printName(-74.0, -37.0, 0.0, "%s", "Bacteria, Birds");
    glFlush();
}

void ShowTropo()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    printName(-74.0, 65.0, 0.0, "%s", "The Troposphere is the lowest portion of Earth’s atmosphere. It contains approximately 80% of ");
    printName(-74.0, 58.0, 0.0, "%s", "the atmosphere’s mass and 99% of its water vapor. The average depth of the troposphere is ");
    printName(-74.0, 51.0, 0.0, "%s", "approximately 17 km in the middle latitudes. It is deeper up to 20 km in the tropics and ");
    printName(-74.0, 44.0, 0.0, "%s", "shallower near the Polar Regions approximately 7 km in winter. The lowest part of the ");
    printName(-74.0, 37.0, 0.0, "%s", "troposphere, where friction with the Earth's surface influences air flow, is the planetary ");
    printName(-74.0, 30.0, 0.0, "%s", "boundary layer. This layer is typically a few hundred meters to 2 km deep depending on the ");
    printName(-74.0, 23.0, 0.0, "%s", "landform and time of day. The border between the troposphere and stratosphere, called the ");
    printName(-74.0, 16.0, 0.0, "%s", "tropopause, is a temperature inversion.");
    printName(-74.0, 3.0, 0.0, "%s", "Composition: ");
    printName(-74.0, -4.0, 0.0, "%s", "The chemical composition of the troposphere is essentially uniform, with the notable exception ");
    printName(-74.0, -11.0, 0.0, "%s", "of water vapor. The source of water vapor is at the surface through the processes of evaporation");
    printName(-74.0, -18.0, 0.0, "%s", "and transpiration. Furthermore the temperature of the troposphere decreases with height, and ");
    printName(-74.0, -25.0, 0.0, "%s", "saturation vapor pressure decreases strongly as temperature drops, so the amount of water ");
    printName(-74.0, -32.0, 0.0, "%s", "vapor that can exist in the atmosphere decreases strongly with height.");
    printName(-74.0, -46.0, 0.0, "%s", "Pressure & Temperature: ");
    printName(-74.0, -53.0, 0.0, "%s", "The pressure of the atmosphere is maximum at sea level and decreases with higher altitude. This");
    printName(-74.0, -60.0, 0.0, "%s", "is because the atmosphere is very nearly in hydrostatic equilibrium, so that the pressure is ");
    printName(-74.0, -67.0, 0.0, "%s", "equal to the weight of air above a given point. The temperature of the troposphere generally ");
    printName(-74.0, -74.0, 0.0, "%s", "decreases as altitude increases.");
    glFlush();
}

void ShowMeso()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    printName(-74.0, 65.0, 0.0, "%s", "The Mesosphere is the layer of the Earth’s Atmosphere that is directly above the stratopause");
    printName(-74.0, 58.0, 0.0, "%s", "and directly below the mesopause. In the mesosphere temperature decreases with increasing ");
    printName(-74.0, 51.0, 0.0, "%s", "height. The upper boundary of the mesosphere is the mesopause, which can be the coldest ");
    printName(-74.0, 44.0, 0.0, "%s", "naturally occurring place on Earth with temperatures below 130 K (−226 °F; −143 °C). The ");
    printName(-74.0, 37.0, 0.0, "%s", "exact upper and lower boundaries of the mesosphere vary with latitude and with season, but ");
    printName(-74.0, 30.0, 0.0, "%s", "the lower boundary of the mesosphere is usually located at heights of about 50 km (160,000 ft.)");
    printName(-74.0, 23.0, 0.0, "%s", " above the Earth's surface and the mesopause is usually at heights near 100 km, except at middle");
    printName(-74.0, 16.0, 0.0, "%s", " and high latitudes in summer where it descends to heights of about 85 km.");
    printName(-74.0, 3.0, 0.0, "%s", "Temperature: ");
    printName(-74.0, -4.0, 0.0, "%s", "The top of the mesosphere, called the mesopause, is the coldest part of Earth's atmosphere.");
    printName(-74.0, -11.0, 0.0, "%s", "Temperatures in the upper mesosphere fall as low as −100 °C (173 K; −148 °F), varying ");
    printName(-74.0, -18.0, 0.0, "%s", "according to latitude and season.");
    glFlush();
}

void ShowThermo()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    printName(-74.0, 65.0, 0.0, "%s", "The Thermosphere is the layer of the Earth’s Atmosphere directly above the mesosphere and");
    printName(-74.0, 58.0, 0.0, "%s", "directly below the exosphere. Within this layer, UV causes ionization. The thermosphere ");
    printName(-74.0, 51.0, 0.0, "%s", "begins about 85 km above the Earth. At these high altitudes, the residual atmospheric gases");
    printName(-74.0, 44.0, 0.0, "%s", "sort into strata according to molecular mass. Thermosphere temperature increase with altitude");
    printName(-74.0, 37.0, 0.0, "%s", "due to absorption of highly energetic solar radiation. Temperatures are highly dependent on solar");
    printName(-74.0, 30.0, 0.0, "%s", "activity, and can rise to 2,000 °C (3,630 °F). Radiation causes the atmosphere particles in this layer");
    printName(-74.0, 23.0, 0.0, "%s", "to become electrically charged, enabling radio waves to bounce off and be received beyond the horizon.");
    printName(-74.0, 16.0, 0.0, "%s", " In the exosphere, beginning at 500 to 1,000 km above the Earth's surface, the atmosphere turns into space.");
    printName(-74.0, 3.0, 0.0, "%s", "Temperature: ");
    printName(-74.0, -4.0, 0.0, "%s", "The highly diluted gas in this layer can reach 2,500 °C (4,530 °F) during the day. Even ");
    printName(-74.0, -11.0, 0.0, "%s", "though the temperature is so high, one would not feel warm in the thermosphere, because ");
    printName(-74.0, -18.0, 0.0, "%s", "it is so near vacuum that there is not enough contact with the few atoms of gas to transfer");
    printName(-74.0, -25.0, 0.0, "%s", "much heat. ");
    glFlush();
}

void ShowExo()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    printName(-74.0, 65.0, 0.0, "%s", "The Exosphere is a thin, atmosphere-like volume surrounding a planetary body where molecules");
    printName(-74.0, 58.0, 0.0, "%s", "are gravitationally bound to that body, but where the density is too low for them to behave");
    printName(-74.0, 51.0, 0.0, "%s", "as a gas by colliding with each other. In the case of bodies with substantial atmospheres,");
    printName(-74.0, 44.0, 0.0, "%s", " such as the Earth’s atmosphere, the exosphere is the uppermost layer, where the atmosphere");
    printName(-74.0, 37.0, 0.0, "%s", " thins out and merges with interplanetary space. It is located directly above the thermosphere.");
    printName(-74.0, 20.0, 0.0, "%s", "Temperature: ");
    printName(-74.0, 13.0, 0.0, "%s", "The lower boundary of the exosphere is known as exopause it is also called the exobase, as in ");
    printName(-74.0, 6.0, 0.0, "%s", "Earth's atmosphere the atmospheric temperature becomes nearly a constant above this altitude.");
    glFlush();
}

void Control(unsigned char key, int x, int y)
{
	switch (key) {
		case 't':
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(150, 40);
            glutInitWindowSize(800, 600);
            glutCreateWindow("About Troposphere");
            ainit();state = 1;
            glutDisplayFunc(ShowTropo);
        break;

		case 's':
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(150, 40);
            glutInitWindowSize(800, 600);
            glutCreateWindow("About Stratosphere");
            ainit();state = 1;
            glutDisplayFunc(ShowStrato);
        break;

        case 'm':
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(150, 40);
            glutInitWindowSize(800, 500);
            glutCreateWindow("About Mesosphere");
            ainit();state = 1;
            glutDisplayFunc(ShowMeso);
        break;

        case 'h':
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(150, 40);
            glutInitWindowSize(800, 500);
            glutCreateWindow("About Thermosphere");
            ainit();state = 1;
            glutDisplayFunc(ShowThermo);
        break;

        case 'e':
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(150, 40);
            glutInitWindowSize(800, 500);
            glutCreateWindow("About Exosphere");
            ainit();state = 1;
            glutDisplayFunc(ShowExo);
        break;

        case 'z':
            if(state == 0) state = 1;
            else state = 0;
        break;

        case 'u':
            if(ultraViolet == 0) ultraViolet = 1;
            else ultraViolet = 0;
        break;

        case 'd':
            if(Thunder == 0)
            {
                Thunder = 1;
                ThunderVary = 1;
                PlaySound(PointThunderMusic, NULL, SND_ASYNC| SND_FILENAME);
            }
        break;

	  default:
			break;
	}
}

void noop(int value)
{
    if(value == 1){
        Music = 1;
        PlaySound(PointBackgroundMusic, NULL, SND_ASYNC| SND_FILENAME| SND_LOOP| SND_NOSTOP| SND_NOWAIT);
    }
    else if(value == 2){
        Music = 0;
        PlaySound(PointStopMusic, NULL, SND_ASYNC| SND_FILENAME);
    }
    else exit(0);
    glutPostRedisplay();
}

int main()
{
    cout<<"Welcome to Arithmatic Layer Structure Visual Effect!!!!\n\n\nFollow the Following Instructions to use,\nPress 't' to know about Troposphere.\nPress 's' to know about Stratosphere.\nPress 'm' to know about Mesosphere.\nPress 'h' to know about Thermosphere.\nPress 'e' to know about Exosphere.\nPress 'z' to stop Animation.\nPress 'u' to watch Ultra-Violate Ray Effect on Layer.\nPress 'd' to watch Thunder Effect in Layer.\n\n\n                                  ENJOY!!!\n\n\n";

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(150, 40);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Atmospheric Layer Structure");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutTimerFunc(0, Timer1, 0);
    glutKeyboardFunc(Control);

    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    string::size_type pos = string(path).find("Atmospheric_Layer_Structure");
    MusicPath = string(path).substr(0,pos);
    MusicPath += "Atmospheric_Layer_Structure";
    string BackgroundMusic = MusicPath + "\\chill.wav";
    string ThunderMusic = MusicPath + "\\thunder.wav";
    string StopMusic = MusicPath + "\\Silent.wav";
    PointBackgroundMusic  = const_cast<char*>(BackgroundMusic.c_str());
    PointThunderMusic  = const_cast<char*>(ThunderMusic.c_str());
    PointStopMusic  = const_cast<char*>(StopMusic.c_str());

    glutCreateMenu(noop);
    glutAddMenuEntry("Play Music", 1);
    glutAddMenuEntry("Stop Music", 2);
    glutAddMenuEntry("Quit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
