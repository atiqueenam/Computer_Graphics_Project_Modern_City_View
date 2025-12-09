#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cstdlib>
using namespace std;

//Color palette
struct Color {
    GLubyte r, g, b;
};

map<string, Color> colors = {
    {"background", {173, 216, 230}},
    {"sky", {200, 230, 255}},
    {"skyNight", {25, 25, 50}},
    {"seaDay", {100, 150, 200}},
    {"seaNight", {15, 25, 40}},
    {"backBackBuilding", {120, 120, 130}},
    {"backBuilding", {140, 140, 150}},
    {"backBuildingShadeLight", {110, 110, 120}},
    {"backBuildingShadeDark", {90, 90, 100}},
    {"frontBuilding", {160, 160, 170}},
    {"frontBuildingShade", {120, 120, 130}},
    {"frontBuildingWindowClose", {50, 50, 60}},
    {"frontBuildingWindowCurtain", {180, 80, 80}},
    {"frontBuildingWindowOpen", {255, 200, 100}},
    {"frontBuildingWindowShade", {200, 150, 100}},
    {"trainGrey", {80, 80, 90}},
    {"trainWheel", {40, 40, 40}},
    {"carGrey", {120, 120, 120}},
    {"carWindow", {100, 150, 200}},
    {"cloudDay", {255, 255, 255}},
    {"cloudNight", {50, 50, 60}},
    {"whiteLight", {255, 255, 200}},
    {"bridge", {60, 60, 70}},
    {"bridgeShade", {40, 40, 50}},
    {"trainTop", {30, 60, 120}},
    {"trainBody", {40, 80, 150}},
    {"trainStripeDark", {20, 40, 90}},
    {"trainStripeLight", {255, 140, 0}},
    {"trainGlass", {170, 210, 240}},
    {"trainGlassWhite", {230, 240, 255}},
    {"trainAccent", {255, 100, 0}},
    {"carBody_1", {220, 20, 20}},
    {"carBody_2", {20, 20, 220}},
    {"carWheel", {20, 20, 20}},
    {"carYellowLight", {255, 255, 0}},
    {"carRedLight", {255, 0, 0}},
    {"water", {80, 150, 200}},
    {"reflectionDark", {60, 120, 160}},
    {"reflectionLight", {120, 180, 220}},
    {"boatHull", {139, 69, 19}},
    {"boatShadow", {101, 50, 15}},
    {"boatDeck", {160, 82, 45}},
    {"boatCabin", {185, 130, 100}},
    {"boatCabinShade", {150, 100, 70}},
    {"boatWindow", {135, 206, 235}},
    {"boatPorthole", {100, 150, 200}},
    {"sunDay", {255, 200, 70}},
    {"moon", {210, 210, 235}},
    {"trainAccent", {255, 100, 0}},
};

bool isDay = true;
float boatPosition = -250.0f;
const float boatSpeed = 2.0f;
int boatAnimState = 0;

// Global variables for animation
float trainPosition = -1600.0f;
// Car 1 headlights face left, so move it left-to-right accordingly
float carPosition_1 = 1200.0f; // start off-screen right, move left - truck
float carPosition_2 = 300.0f;
float carPosition_3 = 1400.0f; // moves left
float carPosition_4 = -500.0f; // moves right
float cloudPosition_1 = 0.0f;
float cloudPosition_2 = 600.0f;
float evenReflectionPosition = 0.0f;
float oddReflectionPosition = 0.0f;
float cloudPosition = 0.0f;
bool dayNight = true;

// Function to set color from palette
void getColor(const string& colorName) {
    if (colors.find(colorName) != colors.end()) {
        Color c = colors[colorName];
        glColor3ub(c.r, c.g, c.b);
    } else {
        glColor3ub(255, 255, 255); // Default white if color not found
    }
}

//Back Back Building 1
void backBackBuilding_1()
{
    //Wide/tall tower shape
    getColor("backBackBuilding");
    glBegin(GL_QUADS);
        glVertex2f(130,550);
        glVertex2f(130,1000);
        glVertex2f(310,1000);
        glVertex2f(310,550);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_TRIANGLES);
        glVertex2f(130,1000);
        glVertex2f(220,1040);
        glVertex2f(310,1000);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(160,880);
        glVertex2f(160,920);
        glVertex2f(200,920);
        glVertex2f(200,880);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(240,880);
        glVertex2f(240,920);
        glVertex2f(280,920);
        glVertex2f(280,880);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(160,740);
        glVertex2f(160,780);
        glVertex2f(200,780);
        glVertex2f(200,740);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(240,740);
        glVertex2f(240,780);
        glVertex2f(280,780);
        glVertex2f(280,740);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(200,600);
        glVertex2f(200,640);
        glVertex2f(240,640);
        glVertex2f(240,600);
    glEnd();
}

//Back Back Building 2
void backBackBuilding_2()
{
    glPushMatrix();
    glTranslatef(0.0f, -600.0f, 0.0f);
    //Stepped block
    getColor("backBackBuilding");
    glBegin(GL_QUADS);
        glVertex2f(420,700);
        glVertex2f(420,990);
        glVertex2f(560,990);
        glVertex2f(560,700);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(440,990);
        glVertex2f(440,1040);
        glVertex2f(520,1040);
        glVertex2f(520,990);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(445,890);
        glVertex2f(445,930);
        glVertex2f(485,930);
        glVertex2f(485,890);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(495,890);
        glVertex2f(495,930);
        glVertex2f(535,930);
        glVertex2f(535,890);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(445,800);
        glVertex2f(445,840);
        glVertex2f(485,840);
        glVertex2f(485,800);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(495,800);
        glVertex2f(495,840);
        glVertex2f(535,840);
        glVertex2f(535,800);
    glEnd();
    glPopMatrix();
}

//Back Back Building 3
void backBackBuilding_3()
{
    glPushMatrix();
    glTranslatef(0.0f, -750.0f, 0.0f);
    //Wide plate tower with angled roof
    getColor("backBackBuilding");
    glBegin(GL_QUADS);
        glVertex2f(1180,860);
        glVertex2f(1180,1080);
        glVertex2f(1520,1080);
        glVertex2f(1520,860);
    glEnd();

    getColor("backBuildingShadeLight");
    glBegin(GL_TRIANGLES);
        glVertex2f(1180,1080);
        glVertex2f(1350,1115);
        glVertex2f(1520,1080);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(1210,1000);
        glVertex2f(1210,1040);
        glVertex2f(1270,1040);
        glVertex2f(1270,1000);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1340,1000);
        glVertex2f(1340,1040);
        glVertex2f(1400,1040);
        glVertex2f(1400,1000);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1430,1000);
        glVertex2f(1430,1040);
        glVertex2f(1490,1040);
        glVertex2f(1490,1000);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1260,940);
        glVertex2f(1260,980);
        glVertex2f(1320,980);
        glVertex2f(1320,940);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1380,940);
        glVertex2f(1380,980);
        glVertex2f(1440,980);
        glVertex2f(1440,940);
    glEnd();
    glPopMatrix();
}

//Back Building 1
void backBuilding_1()
{
    glPushMatrix();
    glTranslatef(0.0f, -150.0f, 0.0f);
    //Stepped blocky building with stripes
    getColor("backBuilding");
    glBegin(GL_QUADS);
        glVertex2f(30,260);
        glVertex2f(30,970);
        glVertex2f(260,970);
        glVertex2f(260,260);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(60,970);
        glVertex2f(60,1040);
        glVertex2f(200,1040);
        glVertex2f(200,970);
    glEnd();

    //Horizontal accent bands
    getColor("background");
    glBegin(GL_QUADS);
        glVertex2f(40,880);
        glVertex2f(40,900);
        glVertex2f(250,900);
        glVertex2f(250,880);
    glEnd();

    getColor("background");
    glBegin(GL_QUADS);
        glVertex2f(40,720);
        glVertex2f(40,740);
        glVertex2f(250,740);
        glVertex2f(250,720);
    glEnd();

    getColor("background");
    glBegin(GL_QUADS);
        glVertex2f(40,560);
        glVertex2f(40,580);
        glVertex2f(250,580);
        glVertex2f(250,560);
    glEnd();
    glPopMatrix();
}

//Back Building 2
void backBuilding_2()
{
    glPushMatrix();
    glTranslatef(0.0f, -210.0f, 0.0f);
    //Offset tower with side inset
    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(320,320);
        glVertex2f(320,980);
        glVertex2f(520,980);
        glVertex2f(520,320);
    glEnd();

    getColor("backBuilding");
    glBegin(GL_QUADS);
        glVertex2f(360,380);
        glVertex2f(360,1040);
        glVertex2f(590,1040);
        glVertex2f(590,380);
    glEnd();

    //Light band
    getColor("background");
    glBegin(GL_QUADS);
        glVertex2f(360,720);
        glVertex2f(360,760);
        glVertex2f(590,760);
        glVertex2f(590,720);
    glEnd();
    glPopMatrix();
}

//Back Building 3
void backBuilding_3()
{
    glPushMatrix();
    glTranslatef(0.0f, -90.0f, 0.0f);
    //Tall mixed-use slab with alternating strips
    getColor("backBuilding");
    glBegin(GL_QUADS);
        glVertex2f(640,200);
        glVertex2f(640,1000);
        glVertex2f(900,1000);
        glVertex2f(900,200);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(640,920);
        glVertex2f(640,940);
        glVertex2f(900,940);
        glVertex2f(900,920);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(640,760);
        glVertex2f(640,780);
        glVertex2f(900,780);
        glVertex2f(900,760);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(640,600);
        glVertex2f(640,620);
        glVertex2f(900,620);
        glVertex2f(900,600);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(640,440);
        glVertex2f(640,460);
        glVertex2f(900,460);
        glVertex2f(900,440);
    glEnd();
    glPopMatrix();
}

//Back Building 4
void backBuilding_4()
{
    glPushMatrix();
    glTranslatef(0.0f, -150.0f, 0.0f);
    //Narrow glassy tower with banded facade
    getColor("backBuildingShadeLight");
    glBegin(GL_QUADS);
        glVertex2f(980,260);
        glVertex2f(980,1020);
        glVertex2f(1200,1020);
        glVertex2f(1200,260);
    glEnd();

    getColor("backBuilding");
    glBegin(GL_QUADS);
        glVertex2f(1200,340);
        glVertex2f(1320,340);
        glVertex2f(1320,960);
        glVertex2f(1200,960);
    glEnd();

    //Bands on the left tower
    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(980,900);
        glVertex2f(980,920);
        glVertex2f(1200,920);
        glVertex2f(1200,900);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(980,760);
        glVertex2f(980,780);
        glVertex2f(1200,780);
        glVertex2f(1200,760);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(980,620);
        glVertex2f(980,640);
        glVertex2f(1200,640);
        glVertex2f(1200,620);
    glEnd();

    getColor("backBuildingShadeDark");
    glBegin(GL_QUADS);
        glVertex2f(980,480);
        glVertex2f(980,500);
        glVertex2f(1200,500);
        glVertex2f(1200,480);
    glEnd();

    //Bands on the right shaft
    getColor("frontBuildingWindowOpen");
    glBegin(GL_QUADS);
        glVertex2f(1200,880);
        glVertex2f(1320,880);
        glVertex2f(1320,860);
        glVertex2f(1200,860);
    glEnd();

    getColor("frontBuildingWindowOpen");
    glBegin(GL_QUADS);
        glVertex2f(1200,740);
        glVertex2f(1320,740);
        glVertex2f(1320,720);
        glVertex2f(1200,720);
    glEnd();

    getColor("frontBuildingWindowOpen");
    glBegin(GL_QUADS);
        glVertex2f(1200,600);
        glVertex2f(1320,600);
        glVertex2f(1320,580);
        glVertex2f(1200,580);
    glEnd();
    glPopMatrix();
}


//Back Building 5
void backBuilding_5()
{
    getColor("backBuilding");
    glBegin(GL_QUADS);
        glVertex2f(1480,1026);
        glVertex2f(1541,1026);
        glVertex2f(1541,126);
        glVertex2f(1480,126);
    glEnd();
}

//Front Building 1
void frontBuilding_1()
{
//Modernized tall slab tower with banding
    getColor("frontBuilding");
    glBegin(GL_QUADS);
        glVertex2f(0,125);
        glVertex2f(0,1000);
        glVertex2f(180,1000);
        glVertex2f(180,125);
    glEnd();

    getColor("frontBuildingShade");
    glBegin(GL_QUADS);
        glVertex2f(180,125);
        glVertex2f(180,1000);
        glVertex2f(200,1000);
        glVertex2f(200,125);
    glEnd();

//Horizontal accent stripes
    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(0,900);
        glVertex2f(180,900);
        glVertex2f(180,890);
        glVertex2f(0,890);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(0,750);
        glVertex2f(180,750);
        glVertex2f(180,740);
        glVertex2f(0,740);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(0,600);
        glVertex2f(180,600);
        glVertex2f(180,590);
        glVertex2f(0,590);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(0,450);
        glVertex2f(180,450);
        glVertex2f(180,440);
        glVertex2f(0,440);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(0,300);
        glVertex2f(180,300);
        glVertex2f(180,290);
        glVertex2f(0,290);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(30,820);
        glVertex2f(30,870);
        glVertex2f(80,870);
        glVertex2f(80,820);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(100,820);
        glVertex2f(100,870);
        glVertex2f(150,870);
        glVertex2f(150,820);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(30,670);
        glVertex2f(30,720);
        glVertex2f(80,720);
        glVertex2f(80,670);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(100,670);
        glVertex2f(100,720);
        glVertex2f(150,720);
        glVertex2f(150,670);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(65,520);
        glVertex2f(65,570);
        glVertex2f(115,570);
        glVertex2f(115,520);
    glEnd();
}

//Front Building 2
void frontBuilding_2()
{
//Broad stepped mid-rise with setback tower
    getColor("frontBuilding");
    glBegin(GL_QUADS);
        glVertex2f(200,125);
        glVertex2f(200,850);
        glVertex2f(520,850);
        glVertex2f(520,125);
    glEnd();

    getColor("frontBuilding");
    glBegin(GL_QUADS);
        glVertex2f(520,300);
        glVertex2f(520,850);
        glVertex2f(760,850);
        glVertex2f(760,300);
    glEnd();

    getColor("frontBuildingShade");
    glBegin(GL_QUADS);
        glVertex2f(760,400);
        glVertex2f(760,850);
        glVertex2f(800,850);
        glVertex2f(800,400);
    glEnd();

//Horizontal divisions
    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(200,750);
        glVertex2f(520,750);
        glVertex2f(520,740);
        glVertex2f(200,740);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(200,550);
        glVertex2f(520,550);
        glVertex2f(520,540);
        glVertex2f(200,540);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(520,750);
        glVertex2f(760,750);
        glVertex2f(760,740);
        glVertex2f(520,740);
    glEnd();

    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(520,550);
        glVertex2f(760,550);
        glVertex2f(760,540);
        glVertex2f(520,540);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(300,680);
        glVertex2f(300,730);
        glVertex2f(360,730);
        glVertex2f(360,680);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(380,680);
        glVertex2f(380,730);
        glVertex2f(440,730);
        glVertex2f(440,680);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(600,680);
        glVertex2f(600,730);
        glVertex2f(660,730);
        glVertex2f(660,680);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(680,680);
        glVertex2f(680,730);
        glVertex2f(740,730);
        glVertex2f(740,680);
    glEnd();
}


//Front Building 3
void frontBuilding_3()
{
    // Sculptural tower with angled crown
    getColor("frontBuilding");
    glBegin(GL_QUADS);
        glVertex2f(1280,125);
        glVertex2f(1280,950);
        glVertex2f(1430,950);
        glVertex2f(1430,125);
    glEnd();
    
    // Angled upper crown (left side higher)
    getColor("frontBuildingShade");
    glBegin(GL_TRIANGLES);
        glVertex2f(1280,950);
        glVertex2f(1355,1050);
        glVertex2f(1430,950);
    glEnd();
    
    // Three horizontal accent bands
    getColor("frontBuildingWindowClose");
    glBegin(GL_QUADS);
        glVertex2f(1280,800);
        glVertex2f(1430,800);
        glVertex2f(1430,810);
        glVertex2f(1280,810);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(1280,550);
        glVertex2f(1430,550);
        glVertex2f(1430,560);
        glVertex2f(1280,560);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(1280,300);
        glVertex2f(1430,300);
        glVertex2f(1430,310);
        glVertex2f(1280,310);
    glEnd();

    // Bigger windows
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(1300,850);
        glVertex2f(1300,900);
        glVertex2f(1350,900);
        glVertex2f(1350,850);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1360,850);
        glVertex2f(1360,900);
        glVertex2f(1410,900);
        glVertex2f(1410,850);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1300,700);
        glVertex2f(1300,750);
        glVertex2f(1350,750);
        glVertex2f(1350,700);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1360,700);
        glVertex2f(1360,750);
        glVertex2f(1410,750);
        glVertex2f(1410,700);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1330,600);
        glVertex2f(1330,650);
        glVertex2f(1380,650);
        glVertex2f(1380,600);
    glEnd();
}

//Front Building 4
void frontBuilding_4()
{
    // Modern cylindrical tower with curved profile simulation
    getColor("frontBuilding");
    glBegin(GL_QUADS);
        glVertex2f(1550,125);
        glVertex2f(1550,1000);
        glVertex2f(1850,1000);
        glVertex2f(1850,125);
    glEnd();
    
    // Left curved inset (simulated with shade)
    getColor("frontBuildingShade");
    glBegin(GL_QUADS);
        glVertex2f(1550,125);
        glVertex2f(1550,1000);
        glVertex2f(1580,1000);
        glVertex2f(1580,125);
    glEnd();
    
    // Vertical dark stripe (column)
    glBegin(GL_QUADS);
        glVertex2f(1700,125);
        glVertex2f(1700,1000);
        glVertex2f(1710,1000);
        glVertex2f(1710,125);
    glEnd();
    
    // Top cap - tapered roof
    getColor("frontBuildingWindowClose");
    glBegin(GL_TRIANGLES);
        glVertex2f(1550,1000);
        glVertex2f(1700,1100);
        glVertex2f(1850,1000);
    glEnd();
    
    // Four horizontal light bands
    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(1580,850);
        glVertex2f(1850,850);
        glVertex2f(1850,865);
        glVertex2f(1580,865);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(1580,650);
        glVertex2f(1850,650);
        glVertex2f(1850,665);
        glVertex2f(1580,665);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(1580,450);
        glVertex2f(1850,450);
        glVertex2f(1850,465);
        glVertex2f(1580,465);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(1580,250);
        glVertex2f(1850,250);
        glVertex2f(1850,265);
        glVertex2f(1580,265);
    glEnd();
}


//Train Bridge
void trainBridge()
{
//black_line
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,430);
        glVertex2f(1919,430);
        glVertex2f(1919,422);
        glVertex2f(0,422);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,414);
        glVertex2f(1919,414);
        glVertex2f(1919,360);
        glVertex2f(0,360);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(467,422);
        glVertex2f(489,422);
        glVertex2f(489,414);
        glVertex2f(467,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(603,422);
        glVertex2f(620,422);
        glVertex2f(620,414);
        glVertex2f(603,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(812,422);
        glVertex2f(831,422);
        glVertex2f(831,414);
        glVertex2f(812,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(980,422);
        glVertex2f(993,422);
        glVertex2f(993,414);
        glVertex2f(980,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_POLYGON);
        glVertex2f(1178,422);
        glVertex2f(1193,422);
        glVertex2f(1193,414);
        glVertex2f(1178,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1394,422);
        glVertex2f(1410,422);
        glVertex2f(1410,414);
        glVertex2f(1394,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1555,422);
        glVertex2f(1570,422);
        glVertex2f(1570,414);
        glVertex2f(1555,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1710,422);
        glVertex2f(1726,422);
        glVertex2f(1726,414);
        glVertex2f(1710,414);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1862,422);
        glVertex2f(1879,422);
        glVertex2f(1879,414);
        glVertex2f(1862,414);
    glEnd();
//red_stand
    getColor("bench");
    glBegin(GL_QUADS);
        glVertex2f(105,445);
        glVertex2f(157,445);
        glVertex2f(157,430);
        glVertex2f(105,430);
    glEnd();

    getColor("bench");
    glBegin(GL_QUADS);
        glVertex2f(112,430);
        glVertex2f(119,430);
        glVertex2f(119,414);
        glVertex2f(112,414);
    glEnd();

    getColor("bench");
    glBegin(GL_QUADS);
        glVertex2f(142,430);
        glVertex2f(150,430);
        glVertex2f(150,414);
        glVertex2f(142,414);
    glEnd();

    getColor("bench");
    glBegin(GL_QUADS);
        glVertex2f(211,445);
        glVertex2f(265,445);
        glVertex2f(265,430);
        glVertex2f(211,430);
    glEnd();

    getColor("bench");
    glBegin(GL_QUADS);
        glVertex2f(220,430);
        glVertex2f(227,430);
        glVertex2f(227,414);
        glVertex2f(220,414);
    glEnd();

     getColor("bench");
     glBegin(GL_QUADS);
        glVertex2f(251,430);
        glVertex2f(258,430);
        glVertex2f(258,414);
        glVertex2f(251,414);
    glEnd();
//gray_stand
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(58,505);
        glVertex2f(319,505);
        glVertex2f(319,490);
        glVertex2f(58,490);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(81,490);
        glVertex2f(96,490);
        glVertex2f(96,414);
        glVertex2f(81,414);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(281,490);
        glVertex2f(296,490);
        glVertex2f(296,414);
        glVertex2f(281,414);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(343,467);
        glVertex2f(350,467);
        glVertex2f(350,414);
        glVertex2f(343,414);
    glEnd();
//red_light
    getColor("redLight");
    glBegin(GL_QUADS);
        glVertex2f(343,452);
        glVertex2f(350,452);
        glVertex2f(350,445);
        glVertex2f(343,445);
    glEnd();
//left_1st_stair(black)
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,351);
        glVertex2f(12,351);
        glVertex2f(12,345);
        glVertex2f(0,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(12,345);
        glVertex2f(34,345);
        glVertex2f(34,337);
        glVertex2f(12,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,329);
        glVertex2f(50,329);
        glVertex2f(50,323);
        glVertex2f(34,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,323);
        glVertex2f(57,323);
        glVertex2f(57,308);
        glVertex2f(50,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,315);
        glVertex2f(73,315);
        glVertex2f(73,308);
        glVertex2f(50,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(81,329);
        glVertex2f(88,329);
        glVertex2f(88,323);
        glVertex2f(81,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(58,315);
        glVertex2f(65,315);
        glVertex2f(65,299);
        glVertex2f(58,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,307);
        glVertex2f(50,307);
        glVertex2f(50,292);
        glVertex2f(34,292);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,299);
        glVertex2f(181,299);
        glVertex2f(181,292);
        glVertex2f(50,292);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(58,292);
        glVertex2f(104,292);
        glVertex2f(104,284);
        glVertex2f(58,284);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,284);
        glVertex2f(88,284);
        glVertex2f(88,277);
        glVertex2f(50,277);
    glEnd();
//Grey_pillar(left_1st)
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(12,360);
        glVertex2f(19,360);
        glVertex2f(19,345);
        glVertex2f(12,345);
    glEnd();
//black_line
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,299);
        glVertex2f(1920,299);
        glVertex2f(1920,292);
        glVertex2f(0,292);
    glEnd();
//grey
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(12,337);
        glVertex2f(19,337);
        glVertex2f(19,299);
        glVertex2f(12,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(12,292);
        glVertex2f(19,292);
        glVertex2f(19,126);
        glVertex2f(12,126);
    glEnd();
//black_pillar
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(19,360);
        glVertex2f(34,360);
        glVertex2f(34,126);
        glVertex2f(19,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(19,360);
        glVertex2f(34,360);
        glVertex2f(34,126);
        glVertex2f(19,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,277);
        glVertex2f(73,277);
        glVertex2f(73,268);
        glVertex2f(34,268);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,268);
        glVertex2f(65,268);
        glVertex2f(65,254);
        glVertex2f(34,254);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,254);
        glVertex2f(81,254);
        glVertex2f(81,246);
        glVertex2f(50,246);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(65,246);
        glVertex2f(96,246);
        glVertex2f(96,238);
        glVertex2f(65,238);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(65,323);
        glVertex2f(81,323);
        glVertex2f(81,315);
        glVertex2f(65,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(65,315);
        glVertex2f(73,315);
        glVertex2f(73,308);
        glVertex2f(65,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(88,238);
        glVertex2f(119,238);
        glVertex2f(119,230);
        glVertex2f(88,230);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(104,230);
        glVertex2f(142,230);
        glVertex2f(142,223);
        glVertex2f(104,223);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,223);
        glVertex2f(157,223);
        glVertex2f(157,215);
        glVertex2f(135,215);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(150,193);
        glVertex2f(166,193);
        glVertex2f(166,177);
        glVertex2f(150,177);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(96,277);
        glVertex2f(113,277);
        glVertex2f(113,269);
        glVertex2f(96,269);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(96,269);
        glVertex2f(104,269);
        glVertex2f(104,238);
        glVertex2f(96,238);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(112,269);
        glVertex2f(135,269);
        glVertex2f(135,261);
        glVertex2f(112,261);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(127,261);
        glVertex2f(135,261);
        glVertex2f(135,230);
        glVertex2f(127,230);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,261);
        glVertex2f(150,261);
        glVertex2f(150,254);
        glVertex2f(135,254);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(150,254);
        glVertex2f(166,254);
        glVertex2f(166,246);
        glVertex2f(150,246);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(157,215);
        glVertex2f(166,215);
        glVertex2f(166,200);
        glVertex2f(157,200);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(142,223);
        glVertex2f(157,223);
        glVertex2f(157,207);
        glVertex2f(142,207);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,230);
        glVertex2f(142,230);
        glVertex2f(142,215);
        glVertex2f(135,215);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(142,223);
        glVertex2f(150,223);
        glVertex2f(150,170);
        glVertex2f(142,170);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(152,192);
        glVertex2f(166,192);
        glVertex2f(166,177);
        glVertex2f(152,177);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(119,215);
        glVertex2f(135,215);
        glVertex2f(135,207);
        glVertex2f(119,207);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(104,207);
        glVertex2f(119,207);
        glVertex2f(119,200);
        glVertex2f(104,200);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(112,207);
        glVertex2f(119,207);
        glVertex2f(119,169);
        glVertex2f(112,169);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(88,200);
        glVertex2f(104,200);
        glVertex2f(104,192);
        glVertex2f(88,192);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(73,192);
        glVertex2f(88,192);
        glVertex2f(88,185);
        glVertex2f(73,185);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(73,185);
        glVertex2f(81,185);
        glVertex2f(81,146);
        glVertex2f(73,146);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(58,185);
        glVertex2f(81,185);
        glVertex2f(81,177);
        glVertex2f(58,177);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(43,177);
        glVertex2f(57,177);
        glVertex2f(57,170);
        glVertex2f(43,170);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,170);
        glVertex2f(50,170);
        glVertex2f(50,162);
        glVertex2f(34,162);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(43,170);
        glVertex2f(50,170);
        glVertex2f(50,126);
        glVertex2f(43,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(34,131);
        glVertex2f(43,131);
        glVertex2f(43,126);
        glVertex2f(34,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(50,138);
        glVertex2f(81,138);
        glVertex2f(81,131);
        glVertex2f(50,131);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(58,146);
        glVertex2f(88,146);
        glVertex2f(88,139);
        glVertex2f(58,139);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(73,154);
        glVertex2f(104,154);
        glVertex2f(104,146);
        glVertex2f(73,146);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(88,161);
        glVertex2f(119,161);
        glVertex2f(119,155);
        glVertex2f(88,155);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(104,170);
        glVertex2f(135,170);
        glVertex2f(135,162);
        glVertex2f(104,162);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(119,177);
        glVertex2f(150,177);
        glVertex2f(150,170);
        glVertex2f(119,170);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,184);
        glVertex2f(166,184);
        glVertex2f(166,177);
        glVertex2f(135,177);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(150,192);
        glVertex2f(166,192);
        glVertex2f(166,177);
        glVertex2f(150,177);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(73,307);
        glVertex2f(126,307);
        glVertex2f(126,299);
        glVertex2f(73,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(88,360);
        glVertex2f(96,360);
        glVertex2f(96,307);
        glVertex2f(88,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(96,337);
        glVertex2f(112,337);
        glVertex2f(112,329);
        glVertex2f(96,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(104,329);
        glVertex2f(112,329);
        glVertex2f(112,307);
        glVertex2f(104,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(112,315);
        glVertex2f(150,315);
        glVertex2f(150,307);
        glVertex2f(112,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(112,315);
        glVertex2f(150,315);
        glVertex2f(150,307);
        glVertex2f(112,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(119,322);
        glVertex2f(166,322);
        glVertex2f(166,315);
        glVertex2f(119,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,329);
        glVertex2f(157,329);
        glVertex2f(157,322);
        glVertex2f(135,322);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(142,337);
        glVertex2f(173,337);
        glVertex2f(173,329);
        glVertex2f(142,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(135,345);
        glVertex2f(150,345);
        glVertex2f(150,337);
        glVertex2f(135,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(127,352);
        glVertex2f(143,352);
        glVertex2f(143,345);
        glVertex2f(127,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(112,345);
        glVertex2f(127,345);
        glVertex2f(127,337);
        glVertex2f(112,337);
    glEnd();
//gray_pillar
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(142,360);
        glVertex2f(158,360);
        glVertex2f(158,345);
        glVertex2f(142,345);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(150,345);
        glVertex2f(166,345);
        glVertex2f(166,337);
        glVertex2f(150,337);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(142,360);
        glVertex2f(157,360);
        glVertex2f(157,345);
        glVertex2f(142,345);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(150,345);
        glVertex2f(166,345);
        glVertex2f(166,337);
        glVertex2f(150,337);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(157,329);
        glVertex2f(173,329);
        glVertex2f(173,322);
        glVertex2f(157,322);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(166,323);
        glVertex2f(181,323);
        glVertex2f(181,299);
        glVertex2f(166,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(150,315);
        glVertex2f(181,315);
        glVertex2f(181,308);
        glVertex2f(150,308);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(126,308);
        glVertex2f(150,308);
        glVertex2f(150,299);
        glVertex2f(126,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(104,292);
        glVertex2f(119,292);
        glVertex2f(119,284);
        glVertex2f(104,284);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(88,284);
        glVertex2f(104,284);
        glVertex2f(104,277);
        glVertex2f(88,277);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(73,277);
        glVertex2f(96,277);
        glVertex2f(96,269);
        glVertex2f(73,269);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(34,254);
        glVertex2f(50,254);
        glVertex2f(50,246);
        glVertex2f(34,246);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(50,246);
        glVertex2f(65,246);
        glVertex2f(65,238);
        glVertex2f(50,238);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(73,238);
        glVertex2f(88,238);
        glVertex2f(88,230);
        glVertex2f(73,230);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(88,230);
        glVertex2f(104,230);
        glVertex2f(104,223);
        glVertex2f(88,223);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(104,223);
        glVertex2f(135,223);
        glVertex2f(135,215);
        glVertex2f(104,215);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(135,215);
        glVertex2f(142,215);
        glVertex2f(142,207);
        glVertex2f(135,207);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(150,207);
        glVertex2f(157,207);
        glVertex2f(157,200);
        glVertex2f(150,200);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(50,131);
        glVertex2f(81,131);
        glVertex2f(81,126);
        glVertex2f(50,126);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(81,138);
        glVertex2f(88,138);
        glVertex2f(88,131);
        glVertex2f(81,131);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(88,145);
        glVertex2f(104,145);
        glVertex2f(104,139);
        glVertex2f(88,139);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(104,154);
        glVertex2f(119,154);
        glVertex2f(119,146);
        glVertex2f(104,146);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(119,162);
        glVertex2f(135,162);
        glVertex2f(135,155);
        glVertex2f(119,155);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(135,170);
        glVertex2f(150,170);
        glVertex2f(150,162);
        glVertex2f(135,162);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(150,177);
        glVertex2f(166,177);
        glVertex2f(166,170);
        glVertex2f(150,170);
    glEnd();
//2nd_left_pillar
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(157,360);
        glVertex2f(265,360);
        glVertex2f(265,345);
        glVertex2f(157,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(166,345);
        glVertex2f(258,345);
        glVertex2f(258,329);
        glVertex2f(166,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(173,329);
        glVertex2f(251,329);
        glVertex2f(251,323);
        glVertex2f(173,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(181,323);
        glVertex2f(242,323);
        glVertex2f(242,126);
        glVertex2f(181,126);
    glEnd();
//gray_pillar
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(166,323);
        glVertex2f(181,323);
        glVertex2f(181,126);
        glVertex2f(166,126);
    glEnd();
//black
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(242,308);
        glVertex2f(251,308);
        glVertex2f(251,299);
        glVertex2f(242,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(265,352);
        glVertex2f(273,352);
        glVertex2f(273,345);
        glVertex2f(265,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(273,345);
        glVertex2f(281,345);
        glVertex2f(281,337);
        glVertex2f(273,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(281,337);
        glVertex2f(296,337);
        glVertex2f(296,329);
        glVertex2f(281,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(296,329);
        glVertex2f(312,329);
        glVertex2f(312,323);
        glVertex2f(296,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(312,323);
        glVertex2f(320,323);
        glVertex2f(320,315);
        glVertex2f(312,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(320,315);
        glVertex2f(335,315);
        glVertex2f(335,308);
        glVertex2f(320,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(335,308);
        glVertex2f(374,308);
        glVertex2f(374,299);
        glVertex2f(335,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(350,360);
        glVertex2f(358,360);
        glVertex2f(358,308);
        glVertex2f(350,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(374,315);
        glVertex2f(388,315);
        glVertex2f(388,308);
        glVertex2f(374,308);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(388,323);
        glVertex2f(396,323);
        glVertex2f(396,315);
        glVertex2f(388,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(396,329);
        glVertex2f(411,329);
        glVertex2f(411,323);
        glVertex2f(396,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(411,337);
        glVertex2f(426,337);
        glVertex2f(426,329);
        glVertex2f(411,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(426,345);
        glVertex2f(434,345);
        glVertex2f(434,337);
        glVertex2f(426,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(434,352);
        glVertex2f(449,352);
        glVertex2f(449,345);
        glVertex2f(434,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(449,360);
        glVertex2f(496,360);
        glVertex2f(496,352);
        glVertex2f(449,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(465,352);
        glVertex2f(480,352);
        glVertex2f(480,299);
        glVertex2f(465,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(496,352);
        glVertex2f(511,352);
        glVertex2f(511,345);
        glVertex2f(496,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(511,345);
        glVertex2f(519,345);
        glVertex2f(519,337);
        glVertex2f(511,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(519,337);
        glVertex2f(534,337);
        glVertex2f(534,329);
        glVertex2f(519,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(534,329);
        glVertex2f(550,329);
        glVertex2f(550,323);
        glVertex2f(534,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(550,323);
        glVertex2f(558,323);
        glVertex2f(558,315);
        glVertex2f(550,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(558,315);
        glVertex2f(572,315);
        glVertex2f(572,307);
        glVertex2f(558,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(572,307);
        glVertex2f(642,307);
        glVertex2f(642,299);
        glVertex2f(572,299);
    glEnd();
//gray
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(542,360);
        glVertex2f(558,360);
        glVertex2f(558,345);
        glVertex2f(542,345);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(550,345);
        glVertex2f(565,345);
        glVertex2f(565,329);
        glVertex2f(550,329);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(558,329);
        glVertex2f(572,329);
        glVertex2f(572,323);
        glVertex2f(558,323);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(565,323);
        glVertex2f(581,323);
        glVertex2f(581,315);
        glVertex2f(565,315);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(572,323);
        glVertex2f(581,323);
        glVertex2f(581,307);
        glVertex2f(572,307);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(565,307);
        glVertex2f(572,307);
        glVertex2f(572,299);
        glVertex2f(565,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(565,299);
        glVertex2f(581,299);
        glVertex2f(581,126);
        glVertex2f(565,126);
    glEnd();
//black_pillar
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(558,360);
        glVertex2f(665,360);
        glVertex2f(665,345);
        glVertex2f(558,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(565,345);
        glVertex2f(657,345);
        glVertex2f(657,329);
        glVertex2f(565,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(572,329);
        glVertex2f(650,329);
        glVertex2f(650,323);
        glVertex2f(572,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(581,323);
        glVertex2f(642,323);
        glVertex2f(642,126);
        glVertex2f(581,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(657,337);
        glVertex2f(665,337);
        glVertex2f(665,329);
        glVertex2f(657,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(665,345);
        glVertex2f(673,345);
        glVertex2f(673,337);
        glVertex2f(665,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(673,352);
        glVertex2f(688,352);
        glVertex2f(688,345);
        glVertex2f(673,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(688,360);
        glVertex2f(735,360);
        glVertex2f(735,352);
        glVertex2f(688,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(704,352);
        glVertex2f(719,352);
        glVertex2f(719,299);
        glVertex2f(704,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(735,352);
        glVertex2f(750,352);
        glVertex2f(750,345);
        glVertex2f(735,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(750,345);
        glVertex2f(758,345);
        glVertex2f(758,337);
        glVertex2f(750,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(758,337);
        glVertex2f(773,337);
        glVertex2f(773,329);
        glVertex2f(758,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(773,329);
        glVertex2f(789,329);
        glVertex2f(789,323);
        glVertex2f(773,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(789,323);
        glVertex2f(795,323);
        glVertex2f(795,315);
        glVertex2f(789,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(795,315);
        glVertex2f(810,315);
        glVertex2f(810,307);
        glVertex2f(795,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(810,307);
        glVertex2f(850,307);
        glVertex2f(850,299);
        glVertex2f(810,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(826,360);
        glVertex2f(834,360);
        glVertex2f(834,307);
        glVertex2f(826,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(850,315);
        glVertex2f(864,315);
        glVertex2f(864,307);
        glVertex2f(850,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(864,323);
        glVertex2f(872,323);
        glVertex2f(872,315);
        glVertex2f(864,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(872,329);
        glVertex2f(888,329);
        glVertex2f(888,323);
        glVertex2f(872,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(888,337);
        glVertex2f(903,337);
        glVertex2f(903,329);
        glVertex2f(888,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(903,345);
        glVertex2f(911,345);
        glVertex2f(911,337);
        glVertex2f(903,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(911,352);
        glVertex2f(926,352);
        glVertex2f(926,345);
        glVertex2f(911,345);
    glEnd();
//gray
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(919,360);
        glVertex2f(926,360);
        glVertex2f(926,352);
        glVertex2f(919,352);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(926,352);
        glVertex2f(934,352);
        glVertex2f(934,329);
        glVertex2f(926,329);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(934,345);
        glVertex2f(942,345);
        glVertex2f(942,323);
        glVertex2f(934,323);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(949,323);
        glVertex2f(957,323);
        glVertex2f(957,299);
        glVertex2f(949,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(942,299);
        glVertex2f(957,299);
        glVertex2f(957,126);
        glVertex2f(942,126);
    glEnd();
//black_pillar
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(926,360);
        glVertex2f(1042,360);
        glVertex2f(1042,352);
        glVertex2f(926,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(934,352);
        glVertex2f(1042,352);
        glVertex2f(1042,345);
        glVertex2f(934,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(942,345);
        glVertex2f(1034,345);
        glVertex2f(1034,323);
        glVertex2f(942,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(942,323);
        glVertex2f(949,323);
        glVertex2f(949,299);
        glVertex2f(942,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(957,329);
        glVertex2f(1019,329);
        glVertex2f(1019,126);
        glVertex2f(957,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1034, 323);
        glVertex2f(1042,323);
        glVertex2f(1042,315);
        glVertex2f(1034,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1042,315);
        glVertex2f(1057,315);
        glVertex2f(1057,307);
        glVertex2f(1042,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1058,307);
        glVertex2f(1096,307);
        glVertex2f(1096,299);
        glVertex2f(1058,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1073,360);
        glVertex2f(1080,360);
        glVertex2f(1080,307);
        glVertex2f(1073,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1096,315);
        glVertex2f(1111,315);
        glVertex2f(1111,307);
        glVertex2f(1096,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1111,323);
        glVertex2f(1119,323);
        glVertex2f(1119,315);
        glVertex2f(1111,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1119,329);
        glVertex2f(1134,329);
        glVertex2f(1134,323);
        glVertex2f(1119,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1134,337);
        glVertex2f(1150,337);
        glVertex2f(1150,329);
        glVertex2f(1134,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1150,345);
        glVertex2f(1157,345);
        glVertex2f(1157,337);
        glVertex2f(1150,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1158,352);
        glVertex2f(1172,352);
        glVertex2f(1172,345);
        glVertex2f(1158,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1172,360);
        glVertex2f(1218,360);
        glVertex2f(1218,352);
        glVertex2f(1172,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1188,352);
        glVertex2f(1203,352);
        glVertex2f(1203,299);
        glVertex2f(1188,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1218,352);
        glVertex2f(1233,352);
        glVertex2f(1233,345);
        glVertex2f(1218,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1233,345);
        glVertex2f(1241,345);
        glVertex2f(1241,337);
        glVertex2f(1233,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1241,337);
        glVertex2f(1256,337);
        glVertex2f(1256,329);
        glVertex2f(1241,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1256,329);
        glVertex2f(1272,329);
        glVertex2f(1272,323);
        glVertex2f(1256,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1272,323);
        glVertex2f(1280,323);
        glVertex2f(1280,315);
        glVertex2f(1272,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1280,315);
        glVertex2f(1295,315);
        glVertex2f(1295,307);
        glVertex2f(1280,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1295,307);
        glVertex2f(1334,307);
        glVertex2f(1334,299);
        glVertex2f(1295,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1311,360);
        glVertex2f(1318,360);
        glVertex2f(1318,307);
        glVertex2f(1311,307);
    glEnd();
//gray
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1325,360);
        glVertex2f(1341,360);
        glVertex2f(1341,345);
        glVertex2f(1325,345);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1334,345);
        glVertex2f(1341,345);
        glVertex2f(1341,337);
        glVertex2f(1334,337);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1341,345);
        glVertex2f(1349,345);
        glVertex2f(1349,323);
        glVertex2f(1341,323);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1349,330);
        glVertex2f(1357,330);
        glVertex2f(1357,323);
        glVertex2f(1349,323);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1357,323);
        glVertex2f(1365,323);
        glVertex2f(1365,299);
        glVertex2f(1357,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1349,315);
        glVertex2f(1357,315);
        glVertex2f(1357,299);
        glVertex2f(1349,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1349,299);
        glVertex2f(1365,299);
        glVertex2f(1365,126);
        glVertex2f(1349,126);
    glEnd();
//black
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1349,323);
        glVertex2f(1357,323);
        glVertex2f(1357,315);
        glVertex2f(1349,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1334,315);
        glVertex2f(1349,315);
        glVertex2f(1349,307);
        glVertex2f(1334,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1341,360);
        glVertex2f(1457,360);
        glVertex2f(1457,352);
        glVertex2f(1341,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1341,352);
        glVertex2f(1449,352);
        glVertex2f(1449,345);
        glVertex2f(1341,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1349,345);
        glVertex2f(1441,345);
        glVertex2f(1441,330);
        glVertex2f(1349,330);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1357,330);
        glVertex2f(1433,330);
        glVertex2f(1433,323);
        glVertex2f(1357,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1365,323);
        glVertex2f(1425,323);
        glVertex2f(1425,126);
        glVertex2f(1365,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1457,352);
        glVertex2f(1472,352);
        glVertex2f(1472,345);
        glVertex2f(1457,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1472,345);
        glVertex2f(1480,345);
        glVertex2f(1480,337);
        glVertex2f(1472,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1480,337);
        glVertex2f(1495,337);
        glVertex2f(1495,329);
        glVertex2f(1480,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1495,329);
        glVertex2f(1511,329);
        glVertex2f(1511,323);
        glVertex2f(1495,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1511,323);
        glVertex2f(1518,323);
        glVertex2f(1518,315);
        glVertex2f(1511,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1519,315);
        glVertex2f(1534,315);
        glVertex2f(1534,307);
        glVertex2f(1519,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1534,307);
        glVertex2f(1572,307);
        glVertex2f(1572,299);
        glVertex2f(1534,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1549,360);
        glVertex2f(1557,360);
        glVertex2f(1557,307);
        glVertex2f(1549,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1572,315);
        glVertex2f(1588,315);
        glVertex2f(1588,307);
        glVertex2f(1572,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1588,323);
        glVertex2f(1595,323);
        glVertex2f(1595,315);
        glVertex2f(1588,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1595,329);
        glVertex2f(1611,329);
        glVertex2f(1611,323);
        glVertex2f(1595,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1611,337);
        glVertex2f(1626,337);
        glVertex2f(1626,330);
        glVertex2f(1611,330);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1626,345);
        glVertex2f(1633,345);
        glVertex2f(1633,337);
        glVertex2f(1626,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1633,352);
        glVertex2f(1648,352);
        glVertex2f(1648,345);
        glVertex2f(1633,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1648,360);
        glVertex2f(1695,360);
        glVertex2f(1695,352);
        glVertex2f(1648,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1664,352);
        glVertex2f(1679,352);
        glVertex2f(1679,299);
        glVertex2f(1664,299);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1695,352);
        glVertex2f(1710,352);
        glVertex2f(1710,345);
        glVertex2f(1695,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1710,345);
        glVertex2f(1718,345);
        glVertex2f(1718,337);
        glVertex2f(1710,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1718,337);
        glVertex2f(1733,337);
        glVertex2f(1733,329);
        glVertex2f(1718,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1733,329);
        glVertex2f(1825,329);
        glVertex2f(1825,323);
        glVertex2f(1733,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1733,360);
        glVertex2f(1841,360);
        glVertex2f(1841,345);
        glVertex2f(1733,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1741,345);
        glVertex2f(1833,345);
        glVertex2f(1833,329);
        glVertex2f(1741,329);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1749,323);
        glVertex2f(1817,323);
        glVertex2f(1817,315);
        glVertex2f(1749,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1756,315);
        glVertex2f(1817,315);
        glVertex2f(1817,126);
        glVertex2f(1756,126);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1817,315);
        glVertex2f(1825,315);
        glVertex2f(1825,307);
        glVertex2f(1817,307);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1825,323);
        glVertex2f(1833,323);
        glVertex2f(1833,315);
        glVertex2f(1825,315);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1833,329);
        glVertex2f(1848,329);
        glVertex2f(1848,323);
        glVertex2f(1833,323);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1849,337);
        glVertex2f(1863,337);
        glVertex2f(1863,330);
        glVertex2f(1849,330);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1863,345);
        glVertex2f(1871,345);
        glVertex2f(1871,337);
        glVertex2f(1863,337);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1871,352);
        glVertex2f(1886,352);
        glVertex2f(1886,345);
        glVertex2f(1871,345);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1887,360);
        glVertex2f(1902,360);
        glVertex2f(1902,352);
        glVertex2f(1887,352);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1902,352);
        glVertex2f(1917,352);
        glVertex2f(1917,299);
        glVertex2f(1902,299);
    glEnd();
 //gray
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1718,360);
        glVertex2f(1733,360);
        glVertex2f(1733,345);
        glVertex2f(1718,345);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1726,345);
        glVertex2f(1741,345);
        glVertex2f(1741,337);
        glVertex2f(1726,337);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1733,337);
        glVertex2f(1741,337);
        glVertex2f(1741,329);
        glVertex2f(1733,329);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1733,323);
        glVertex2f(1749,323);
        glVertex2f(1749,315);
        glVertex2f(1733,315);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1741,315);
        glVertex2f(1756,315);
        glVertex2f(1756,299);
        glVertex2f(1741,299);
    glEnd();

    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(1741,299);
        glVertex2f(1757,299);
        glVertex2f(1757,126);
        glVertex2f(1741,126);
    glEnd();
}

//Street Light
void streetLight()
{
//1st
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(335,125);
        glVertex2f(335,207);
        glVertex2f(343,207);
        glVertex2f(343,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(343,199);
        glVertex2f(343,207);
        glVertex2f(366,207);
        glVertex2f(366,199);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(366,192);
        glVertex2f(366,199);
        glVertex2f(374,199);
        glVertex2f(374,192);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(366,185);
        glVertex2f(366,192);
        glVertex2f(374,192);
        glVertex2f(374,185);
    glEnd();
//2nd
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(726,125);
        glVertex2f(726,207);
        glVertex2f(734,207);
        glVertex2f(734,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(734,199);
        glVertex2f(734,207);
        glVertex2f(757,207);
        glVertex2f(757,199);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(757,192);
        glVertex2f(757,199);
        glVertex2f(765,199);
        glVertex2f(765,192);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(757,185);
        glVertex2f(757,192);
        glVertex2f(765,192);
        glVertex2f(765,185);
    glEnd();
//3rd
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1120,125);
        glVertex2f(1120,207);
        glVertex2f(1128,207);
        glVertex2f(1128,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1128,199);
        glVertex2f(1128,207);
        glVertex2f(1151,207);
        glVertex2f(1151,199);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1151,192);
        glVertex2f(1151,199);
        glVertex2f(1159,199);
        glVertex2f(1159,192);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(1151,185);
        glVertex2f(1151,192);
        glVertex2f(1159,192);
        glVertex2f(1159,185);
    glEnd();
//4th
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1514,125);
        glVertex2f(1514,207);
        glVertex2f(1522,207);
        glVertex2f(1522,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1522,199);
        glVertex2f(1522,207);
        glVertex2f(1545,207);
        glVertex2f(1545,199);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1545,192);
        glVertex2f(1545,199);
        glVertex2f(1553,199);
        glVertex2f(1553,192);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(1545,185);
        glVertex2f(1545,192);
        glVertex2f(1553,192);
        glVertex2f(1553,185);
    glEnd();
}

//Car
void car_1()
{
    glPushMatrix();
    glTranslatef(carPosition_1,0, 0);
    //body
    getColor("carBody_1");
    glBegin(GL_QUADS);
        glVertex2f(1180,131);
        glVertex2f(1180,145);
        glVertex2f(1318,145);
        glVertex2f(1318,131);
    glEnd();

    getColor("carBody_1");
    glBegin(GL_QUADS);
        glVertex2f(1188,145);
        glVertex2f(1188,169);
        glVertex2f(1212,169);
        glVertex2f(1212,145);
    glEnd();

    getColor("carBody_1");
    glBegin(GL_QUADS);
        glVertex2f(1226,145);
        glVertex2f(1226,185);
        glVertex2f(1318,185);
        glVertex2f(1318,145);
    glEnd();

    //wheel
    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(1188,125);
        glVertex2f(1188,131);
        glVertex2f(1203,131);
        glVertex2f(1203,125);
    glEnd();

    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(1218,125);
        glVertex2f(1218,131);
        glVertex2f(1233,131);
        glVertex2f(1233,125);
    glEnd();

    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(1295,125);
        glVertex2f(1295,131);
        glVertex2f(1310,131);
        glVertex2f(1310,125);
    glEnd();
    //hubcaps
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(1193,126);
        glVertex2f(1193,130);
        glVertex2f(1198,130);
        glVertex2f(1198,126);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1223,126);
        glVertex2f(1223,130);
        glVertex2f(1228,130);
        glVertex2f(1228,126);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1300,126);
        glVertex2f(1300,130);
        glVertex2f(1305,130);
        glVertex2f(1305,126);
    glEnd();
    //yellow light
    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1180,145);
        glVertex2f(1180,154);
        glVertex2f(1188,154);
        glVertex2f(1188,145);
    glEnd();
    //red light
    getColor("carRedLight");
    glBegin(GL_QUADS);
        glVertex2f(1310,145);
        glVertex2f(1310,154);
        glVertex2f(1318,154);
        glVertex2f(1318,145);
    glEnd();

    //yellow light
    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1196,169);
        glVertex2f(1196,177);
        glVertex2f(1212,177);
        glVertex2f(1212,169);
    glEnd();

    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1226,177);
        glVertex2f(1226,185);
        glVertex2f(1233,185);
        glVertex2f(1233,177);
    glEnd();

    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1311,177);
        glVertex2f(1311,185);
        glVertex2f(1318,185);
        glVertex2f(1318,177);
    glEnd();
    glPopMatrix();
}

void car_2()
{
    glPushMatrix();
    glTranslatef(carPosition_2,0, 0);
    //body
    getColor("carBody_2");
    glBegin(GL_QUADS);
        glVertex2f(1595,131);
        glVertex2f(1595,145);
        glVertex2f(1695,145);
        glVertex2f(1695,131);
    glEnd();

    getColor("carBody_2");
    glBegin(GL_QUADS);
        glVertex2f(1618,145);
        glVertex2f(1618,153);
        glVertex2f(1657,153);
        glVertex2f(1657,145);
    glEnd();
    //window strip
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(1625,146);
        glVertex2f(1625,152);
        glVertex2f(1685,152);
        glVertex2f(1685,146);
    glEnd();
    //wheel
    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(1611,125);
        glVertex2f(1611,131);
        glVertex2f(1626,131);
        glVertex2f(1626,125);
    glEnd();

    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(1665,125);
        glVertex2f(1665,131);
        glVertex2f(1680,131);
        glVertex2f(1680,125);
    glEnd();
    //hubcaps
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(1616,126);
        glVertex2f(1616,130);
        glVertex2f(1621,130);
        glVertex2f(1621,126);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(1670,126);
        glVertex2f(1670,130);
        glVertex2f(1675,130);
        glVertex2f(1675,126);
    glEnd();
    //red light
    getColor("carRedLight");
    glBegin(GL_QUADS);
        glVertex2f(1595,139);
        glVertex2f(1595,145);
        glVertex2f(1604,145);
        glVertex2f(1604,139);
    glEnd();
    //yellow light
    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1687,139);
        glVertex2f(1687,145);
        glVertex2f(1695,145);
        glVertex2f(1695,139);
    glEnd();

    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(1634,153);
        glVertex2f(1634,161);
        glVertex2f(1649,161);
        glVertex2f(1649,153);
    glEnd();
    //door handle
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(1638,147);
        glVertex2f(1638,151);
        glVertex2f(1648,151);
        glVertex2f(1648,147);
    glEnd();
    glPopMatrix();
}

void car_3()
{
    glPushMatrix();
    glTranslatef(carPosition_3, 0, 0);
    // body (reuse carBody_1)
    getColor("carBody_1");
    glBegin(GL_QUADS);
        glVertex2f(400,135);
        glVertex2f(400,155);
        glVertex2f(520,155);
        glVertex2f(520,135);
    glEnd();

    getColor("carBody_1");
    glBegin(GL_QUADS);
        glVertex2f(430,155);
        glVertex2f(430,175);
        glVertex2f(500,175);
        glVertex2f(500,155);
    glEnd();

    // window strip
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(440,158);
        glVertex2f(440,172);
        glVertex2f(490,172);
        glVertex2f(490,158);
    glEnd();

    // wheels
    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(420,125);
        glVertex2f(420,135);
        glVertex2f(440,135);
        glVertex2f(440,125);
    glEnd();

    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(480,125);
        glVertex2f(480,135);
        glVertex2f(500,135);
        glVertex2f(500,125);
    glEnd();
    // hubcaps
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(425,126);
        glVertex2f(425,130);
        glVertex2f(430,130);
        glVertex2f(430,126);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(485,126);
        glVertex2f(485,130);
        glVertex2f(490,130);
        glVertex2f(490,126);
    glEnd();

    // lights
    getColor("carRedLight");
    glBegin(GL_QUADS);
        glVertex2f(400,145);
        glVertex2f(400,155);
        glVertex2f(410,155);
        glVertex2f(410,145);
    glEnd();

    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(510,145);
        glVertex2f(510,155);
        glVertex2f(520,155);
        glVertex2f(520,145);
    glEnd();
    // door handle
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(455,148);
        glVertex2f(455,152);
        glVertex2f(465,152);
        glVertex2f(465,148);
    glEnd();
    glPopMatrix();
}

void car_4()
{
    glPushMatrix();
    glTranslatef(carPosition_4, 0, 0);
    // body (reuse carBody_2)
    getColor("carBody_2");
    glBegin(GL_QUADS);
        glVertex2f(50,135);
        glVertex2f(50,155);
        glVertex2f(170,155);
        glVertex2f(170,135);
    glEnd();

    getColor("carBody_2");
    glBegin(GL_QUADS);
        glVertex2f(80,155);
        glVertex2f(80,175);
        glVertex2f(150,175);
        glVertex2f(150,155);
    glEnd();

    // window strip
    getColor("carWindow");
    glBegin(GL_QUADS);
        glVertex2f(90,158);
        glVertex2f(90,172);
        glVertex2f(140,172);
        glVertex2f(140,158);
    glEnd();

    // wheels
    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(70,125);
        glVertex2f(70,135);
        glVertex2f(90,135);
        glVertex2f(90,125);
    glEnd();

    getColor("carWheel");
    glBegin(GL_QUADS);
        glVertex2f(130,125);
        glVertex2f(130,135);
        glVertex2f(150,135);
        glVertex2f(150,125);
    glEnd();

    // hubcaps
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(75,126);
        glVertex2f(75,130);
        glVertex2f(80,130);
        glVertex2f(80,126);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(135,126);
        glVertex2f(135,130);
        glVertex2f(140,130);
        glVertex2f(140,126);
    glEnd();

    // lights
    getColor("carRedLight");
    glBegin(GL_QUADS);
        glVertex2f(50,145);
        glVertex2f(50,155);
        glVertex2f(60,155);
        glVertex2f(60,145);
    glEnd();

    getColor("carYellowLight");
    glBegin(GL_QUADS);
        glVertex2f(160,145);
        glVertex2f(160,155);
        glVertex2f(170,155);
        glVertex2f(170,145);
    glEnd();
    // door handle
    getColor("carGrey");
    glBegin(GL_QUADS);
        glVertex2f(110,148);
        glVertex2f(110,152);
        glVertex2f(120,152);
        glVertex2f(120,148);
    glEnd();
    glPopMatrix();
}
//Train
void train()
{
    glPushMatrix();
    glTranslatef(trainPosition,0, 0);
//1s_compartment
    getColor("trainTop");
    glBegin(GL_QUADS);
        glVertex2f(420,521);
        glVertex2f(704,521);
        glVertex2f(704,514);
        glVertex2f(420,514);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(411,514);
        glVertex2f(711,514);
        glVertex2f(711,505);
        glVertex2f(411,505);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(411,505);
        glVertex2f(403,505);
        glVertex2f(403,490);
        glVertex2f(411,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(711,505);
        glVertex2f(719,505);
        glVertex2f(719,490);
        glVertex2f(711,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(411,505);
        glVertex2f(419,505);
        glVertex2f(419,460);
        glVertex2f(411,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(411,460);
        glVertex2f(711,460);
        glVertex2f(711,421);
        glVertex2f(411,421);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(405,445);
        glVertex2f(411,445);
        glVertex2f(411,437);
        glVertex2f(405,437);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(434,505);
        glVertex2f(442,505);
        glVertex2f(442,460);
        glVertex2f(434,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(503,505);
        glVertex2f(511,505);
        glVertex2f(511,460);
        glVertex2f(503,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(581,505);
        glVertex2f(589,505);
        glVertex2f(589,460);
        glVertex2f(581,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(659,505);
        glVertex2f(666,505);
        glVertex2f(666,460);
        glVertex2f(659,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(689,505);
        glVertex2f(711,505);
        glVertex2f(711,460);
        glVertex2f(689,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(711,445);
        glVertex2f(718,445);
        glVertex2f(718,437);
        glVertex2f(711,437);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(427,421);
        glVertex2f(695,421);
        glVertex2f(695,414);
        glVertex2f(427,414);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(419,467);
        glVertex2f(434,467);
        glVertex2f(434,460);
        glVertex2f(419,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(442,467);
        glVertex2f(503,467);
        glVertex2f(503,460);
        glVertex2f(442,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(511,467);
        glVertex2f(581,467);
        glVertex2f(581,460);
        glVertex2f(511,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(589,467);
        glVertex2f(659,467);
        glVertex2f(659,460);
        glVertex2f(589,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glColor3ub(34, 43, 59);
        glVertex2f(666,467);
        glVertex2f(689,467);
        glVertex2f(689,460);
        glVertex2f(666,460);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(427,505);
        glVertex2f(434,505);
        glVertex2f(434,467);
        glVertex2f(427,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(495,505);
        glVertex2f(503,505);
        glVertex2f(503,467);
        glVertex2f(495,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(573,505);
        glVertex2f(581,505);
        glVertex2f(581,467);
        glVertex2f(573,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(650,505);
        glVertex2f(658,505);
        glVertex2f(658,467);
        glVertex2f(650,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(682,505);
        glVertex2f(690,505);
        glVertex2f(690,467);
        glVertex2f(682,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(419,505);
        glVertex2f(427,505);
        glVertex2f(427,467);
        glVertex2f(419,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(442,505);
        glVertex2f(495,505);
        glVertex2f(495,467);
        glVertex2f(442,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(511,505);
        glVertex2f(573,505);
        glVertex2f(573,467);
        glVertex2f(511,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(589,505);
        glVertex2f(650,505);
        glVertex2f(650,467);
        glVertex2f(589,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(666,505);
        glVertex2f(682,505);
        glVertex2f(682,467);
        glVertex2f(666,467);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(457,483);
        glVertex2f(464,483);
        glVertex2f(464,475);
        glVertex2f(457,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(464,490);
        glVertex2f(472,490);
        glVertex2f(472,483);
        glVertex2f(464,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(472,498);
        glVertex2f(480,498);
        glVertex2f(480,490);
        glVertex2f(472,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(528,483);
        glVertex2f(535,483);
        glVertex2f(535,475);
        glVertex2f(528,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(535,490);
        glVertex2f(543,490);
        glVertex2f(543,483);
        glVertex2f(535,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(543,498);
        glVertex2f(550,498);
        glVertex2f(550,490);
        glVertex2f(543,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(604,483);
        glVertex2f(612,483);
        glVertex2f(612,475);
        glVertex2f(604,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(612,490);
        glVertex2f(620,490);
        glVertex2f(620,483);
        glVertex2f(612,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(620,498);
        glVertex2f(628,498);
        glVertex2f(628,490);
        glVertex2f(620,490);
    glEnd();
//2nd_compartment
    getColor("trainTop");
    glBegin(GL_QUADS);
        glVertex2f(750,521);
        glVertex2f(1034,521);
        glVertex2f(1034,514);
        glVertex2f(750,514);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(742,514);
        glVertex2f(1042,514);
        glVertex2f(1042,505);
        glVertex2f(742,505);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(736,505);
        glVertex2f(742,505);
        glVertex2f(742,490);
        glVertex2f(736,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1042,505);
        glVertex2f(1049,505);
        glVertex2f(1049,490);
        glVertex2f(1042,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(742,505);
        glVertex2f(750,505);
        glVertex2f(750,460);
        glVertex2f(742,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(742,460);
        glVertex2f(1042,460);
        glVertex2f(1042,421);
        glVertex2f(742,421);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(735,445);
        glVertex2f(742,445);
        glVertex2f(742,437);
        glVertex2f(735,437);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1042,445);
        glVertex2f(1049,445);
        glVertex2f(1049,437);
        glVertex2f(1042,437);
    glEnd();

     getColor("trainBody");
     glBegin(GL_QUADS);
        glVertex2f(765,505);
        glVertex2f(773,505);
        glVertex2f(773,460);
        glVertex2f(765,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(834,505);
        glVertex2f(841,505);
        glVertex2f(841,460);
        glVertex2f(834,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(911,505);
        glVertex2f(919,505);
        glVertex2f(919,460);
        glVertex2f(911,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(988,505);
        glVertex2f(995,505);
        glVertex2f(995,460);
        glVertex2f(988,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1018,505);
        glVertex2f(1042,505);
        glVertex2f(1042,460);
        glVertex2f(1018,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(750,467);
        glVertex2f(765,467);
        glVertex2f(765,460);
        glVertex2f(750,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(773,467);
        glVertex2f(834,467);
        glVertex2f(834,460);
        glVertex2f(773,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(841,467);
        glVertex2f(911,467);
        glVertex2f(911,460);
        glVertex2f(841,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(919,467);
        glVertex2f(988,467);
        glVertex2f(988,460);
        glVertex2f(919,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(995,467);
        glVertex2f(1018,467);
        glVertex2f(1018,460);
        glVertex2f(995,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(758,421);
        glVertex2f(1026,421);
        glVertex2f(1026,414);
        glVertex2f(758,414);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(750,505);
        glVertex2f(758,505);
        glVertex2f(758,467);
        glVertex2f(750,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(841,505);
        glVertex2f(857,505);
        glVertex2f(857,467);
        glVertex2f(841,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(857,498);
        glVertex2f(864,498);
        glVertex2f(864,467);
        glVertex2f(857,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(826,505);
        glVertex2f(834,505);
        glVertex2f(834,467);
        glVertex2f(826,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(857,505);
        glVertex2f(864,505);
        glVertex2f(864,498);
        glVertex2f(857,498);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(864,505);
        glVertex2f(903,505);
        glVertex2f(903,467);
        glVertex2f(864,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(919,505);
        glVertex2f(988,505);
        glVertex2f(988,467);
        glVertex2f(919,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(995,505);
        glVertex2f(1011,505);
        glVertex2f(1011,467);
        glVertex2f(995,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(773,505);
        glVertex2f(826,505);
        glVertex2f(826,467);
        glVertex2f(773,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(758,505);
        glVertex2f(765,505);
        glVertex2f(765,467);
        glVertex2f(758,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(826,505);
        glVertex2f(834,505);
        glVertex2f(834,467);
        glVertex2f(826,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(903,505);
        glVertex2f(911,505);
        glVertex2f(911,467);
        glVertex2f(903,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1011,505);
        glVertex2f(1018,505);
        glVertex2f(1018,467);
        glVertex2f(1011,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(980,505);
        glVertex2f(988,505);
        glVertex2f(988,467);
        glVertex2f(980,467);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(788,483);
        glVertex2f(795,483);
        glVertex2f(795,475);
        glVertex2f(788,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(795,490);
        glVertex2f(803,490);
        glVertex2f(803,483);
        glVertex2f(795,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(803,498);
        glVertex2f(810,498);
        glVertex2f(810,490);
        glVertex2f(803,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(864,483);
        glVertex2f(872,483);
        glVertex2f(872,475);
        glVertex2f(864,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(872,490);
        glVertex2f(880,490);
        glVertex2f(880,483);
        glVertex2f(872,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(880,498);
        glVertex2f(888,498);
        glVertex2f(888,490);
        glVertex2f(880,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(934,483);
        glVertex2f(942,483);
        glVertex2f(942,475);
        glVertex2f(934,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(942,490);
        glVertex2f(949,490);
        glVertex2f(949,483);
        glVertex2f(942,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(949,498);
        glVertex2f(957,498);
        glVertex2f(957,490);
        glVertex2f(949,490);
    glEnd();
//3rd_compartment
    getColor("trainTop");
    glBegin(GL_QUADS);
        glVertex2f(1080,521);
        glVertex2f(1365,521);
        glVertex2f(1365,514);
        glVertex2f(1080,514);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1073,514);
        glVertex2f(1371,514);
        glVertex2f(1371,505);
        glVertex2f(1073,505);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1065,505);
        glVertex2f(1073,505);
        glVertex2f(1073,490);
        glVertex2f(1065,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1065,505);
        glVertex2f(1073,505);
        glVertex2f(1073,490);
        glVertex2f(1065,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1073,505);
        glVertex2f(1080,505);
        glVertex2f(1080,460);
        glVertex2f(1073,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1073,460);
        glVertex2f(1371,460);
        glVertex2f(1371,421);
        glVertex2f(1073,421);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1065,445);
        glVertex2f(1073,445);
        glVertex2f(1073,437);
        glVertex2f(1065,437);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1096,505);
        glVertex2f(1103,505);
        glVertex2f(1103,460);
        glVertex2f(1096,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1165,505);
        glVertex2f(1172,505);
        glVertex2f(1172,460);
        glVertex2f(1165,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1241,505);
        glVertex2f(1249,505);
        glVertex2f(1249,460);
        glVertex2f(1241,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1318,505);
        glVertex2f(1325,505);
        glVertex2f(1325,460);
        glVertex2f(1318,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1349,505);
        glVertex2f(1371,505);
        glVertex2f(1371,460);
        glVertex2f(1349,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1371,505);
        glVertex2f(1380,505);
        glVertex2f(1380,490);
        glVertex2f(1371,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1371,445);
        glVertex2f(1380,445);
        glVertex2f(1380,437);
        glVertex2f(1371,437);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1088,421);
        glVertex2f(1356,421);
        glVertex2f(1356,414);
        glVertex2f(1088,414);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1080,467);
        glVertex2f(1096,467);
        glVertex2f(1096,460);
        glVertex2f(1080,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1103,467);
        glVertex2f(1164,467);
        glVertex2f(1164,460);
        glVertex2f(1103,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1172,467);
        glVertex2f(1241,467);
        glVertex2f(1241,460);
        glVertex2f(1172,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1249,467);
        glVertex2f(1318,467);
        glVertex2f(1318,460);
        glVertex2f(1249,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glColor3ub(34, 43, 59);
        glVertex2f(1325,467);
        glVertex2f(1349,467);
        glVertex2f(1349,460);
        glVertex2f(1325,460);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1311,505);
        glVertex2f(1318,505);
        glVertex2f(1318,467);
        glVertex2f(1311,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1233,505);
        glVertex2f(1241,505);
        glVertex2f(1241,467);
        glVertex2f(1233,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1157,505);
        glVertex2f(1165,505);
        glVertex2f(1165,460);
        glVertex2f(1157,460);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1080,505);
        glVertex2f(1088,505);
        glVertex2f(1088,467);
        glVertex2f(1080,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1341,505);
        glVertex2f(1349,505);
        glVertex2f(1349,467);
        glVertex2f(1341,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1088,505);
        glVertex2f(1096,505);
        glVertex2f(1096,467);
        glVertex2f(1088,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1080,505);
        glVertex2f(1088,505);
        glVertex2f(1088,467);
        glVertex2f(1080,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1103,505);
        glVertex2f(1157,505);
        glVertex2f(1157,467);
        glVertex2f(1103,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1172,505);
        glVertex2f(1233,505);
        glVertex2f(1233,467);
        glVertex2f(1172,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1249,505);
        glVertex2f(1311,505);
        glVertex2f(1311,467);
        glVertex2f(1249,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1325,505);
        glVertex2f(1341,505);
        glVertex2f(1341,467);
        glVertex2f(1325,467);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1119,483);
        glVertex2f(1127,483);
        glVertex2f(1127,475);
        glVertex2f(1119,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1127,490);
        glVertex2f(1134,490);
        glVertex2f(1134,483);
        glVertex2f(1127,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1134,498);
        glVertex2f(1142,498);
        glVertex2f(1142,490);
        glVertex2f(1134,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1188,483);
        glVertex2f(1196,483);
        glVertex2f(1196,475);
        glVertex2f(1188,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1196,490);
        glVertex2f(1203,490);
        glVertex2f(1203,483);
        glVertex2f(1196,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1203,498);
        glVertex2f(1211,498);
        glVertex2f(1211,490);
        glVertex2f(1203,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1264,483);
        glVertex2f(1272,483);
        glVertex2f(1272,475);
        glVertex2f(1264,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1272,490);
        glVertex2f(1280,490);
        glVertex2f(1280,483);
        glVertex2f(1272,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1280,498);
        glVertex2f(1287,498);
        glVertex2f(1287,490);
        glVertex2f(1280,490);
    glEnd();
//4th_compartment
    getColor("trainTop");
    glBegin(GL_QUADS);
        glVertex2f(1410,521);
        glVertex2f(1695,521);
        glVertex2f(1695,514);
        glVertex2f(1410,514);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1402,514);
        glVertex2f(1702,514);
        glVertex2f(1702,505);
        glVertex2f(1402,505);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1395,505);
        glVertex2f(1402,505);
        glVertex2f(1402,490);
        glVertex2f(1395,490);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1402,505);
        glVertex2f(1410,505);
        glVertex2f(1410,460);
        glVertex2f(1402,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1402,460);
        glVertex2f(1702,460);
        glVertex2f(1702,421);
        glVertex2f(1402,421);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1702,445);
        glVertex2f(1710,445);
        glVertex2f(1710,437);
        glVertex2f(1702,437);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1395,445);
        glVertex2f(1402,445);
        glVertex2f(1402,437);
        glVertex2f(1395,437);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1426,505);
        glVertex2f(1434,505);
        glVertex2f(1434,460);
        glVertex2f(1426,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1495,505);
        glVertex2f(1503,505);
        glVertex2f(1503,460);
        glVertex2f(1495,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1572,505);
        glVertex2f(1580,505);
        glVertex2f(1580,460);
        glVertex2f(1572,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1648,505);
        glVertex2f(1657,505);
        glVertex2f(1657,460);
        glVertex2f(1648,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1679,505);
        glVertex2f(1702,505);
        glVertex2f(1702,460);
        glVertex2f(1679,460);
    glEnd();

    getColor("trainBody");
    glBegin(GL_QUADS);
        glVertex2f(1702,505);
        glVertex2f(1710,505);
        glVertex2f(1710,490);
        glVertex2f(1702,490);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1410,467);
        glVertex2f(1426,467);
        glVertex2f(1426,460);
        glVertex2f(1410,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1434,467);
        glVertex2f(1495,467);
        glVertex2f(1495,460);
        glVertex2f(1434,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1503,467);
        glVertex2f(1572,467);
        glVertex2f(1572,460);
        glVertex2f(1503,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1580,467);
        glVertex2f(1648,467);
        glVertex2f(1648,460);
        glVertex2f(1580,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1657,467);
        glVertex2f(1679,467);
        glVertex2f(1679,460);
        glVertex2f(1657,460);
    glEnd();

    getColor("trainStripeDark");
    glBegin(GL_QUADS);
        glVertex2f(1419,421);
        glVertex2f(1687,421);
        glVertex2f(1687,414);
        glVertex2f(1419,414);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1410,505);
        glVertex2f(1419,505);
        glVertex2f(1419,467);
        glVertex2f(1410,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1434,505);
        glVertex2f(1488,505);
        glVertex2f(1488,467);
        glVertex2f(1434,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1503,505);
        glVertex2f(1564,505);
        glVertex2f(1564,467);
        glVertex2f(1503,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1580,505);
        glVertex2f(1641,505);
        glVertex2f(1641,467);
        glVertex2f(1580,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1657,505);
        glVertex2f(1672,505);
        glVertex2f(1672,467);
        glVertex2f(1657,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1419,505);
        glVertex2f(1426,505);
        glVertex2f(1426,467);
        glVertex2f(1419,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1488,505);
        glVertex2f(1495,505);
        glVertex2f(1495,467);
        glVertex2f(1488,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1564,505);
        glVertex2f(1572,505);
        glVertex2f(1572,467);
        glVertex2f(1564,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1641,505);
        glVertex2f(1648,505);
        glVertex2f(1648,467);
        glVertex2f(1641,467);
    glEnd();

    getColor("trainStripeLight");
    glBegin(GL_QUADS);
        glVertex2f(1672,505);
        glVertex2f(1679,505);
        glVertex2f(1679,467);
        glVertex2f(1672,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1657,475);
        glVertex2f(1664,475);
        glVertex2f(1664,467);
        glVertex2f(1657,467);
    glEnd();

    getColor("trainGlass");
    glBegin(GL_QUADS);
        glVertex2f(1603,475);
        glVertex2f(1633,475);
        glVertex2f(1633,467);
        glVertex2f(1603,467);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1449,483);
        glVertex2f(1457,483);
        glVertex2f(1457,475);
        glVertex2f(1449,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1457,490);
        glVertex2f(1464,490);
        glVertex2f(1464,483);
        glVertex2f(1457,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1464,498);
        glVertex2f(1472,498);
        glVertex2f(1472,490);
        glVertex2f(1464,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1526,483);
        glVertex2f(1534,483);
        glVertex2f(1534,475);
        glVertex2f(1526,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1534,490);
        glVertex2f(1541,490);
        glVertex2f(1541,483);
        glVertex2f(1534,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1541,498);
        glVertex2f(1549,498);
        glVertex2f(1549,490);
        glVertex2f(1541,490);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1595,483);
        glVertex2f(1603,483);
        glVertex2f(1603,475);
        glVertex2f(1595,475);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1603,490);
        glVertex2f(1610,490);
        glVertex2f(1610,483);
        glVertex2f(1603,483);
    glEnd();

    getColor("trainGlassWhite");
    glBegin(GL_QUADS);
        glVertex2f(1610,498);
        glVertex2f(1618,498);
        glVertex2f(1618,490);
        glVertex2f(1610,490);
    glEnd();

    glPopMatrix();
}

//Water Railing
void waterRailing()
{
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,110);
        glVertex2f(0,125);
        glVertex2f(1920,125);
        glVertex2f(1920,110);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(0,140);
        glVertex2f(0,150);
        glVertex2f(1920,150);
        glVertex2f(1920,140);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(0,125);
        glVertex2f(0,140);
        glVertex2f(13,140);
        glVertex2f(13,125);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(400,125);
        glVertex2f(400,140);
        glVertex2f(413,140);
        glVertex2f(413,125);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(787,125);
        glVertex2f(787,140);
        glVertex2f(800,140);
        glVertex2f(800,125);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(1174,125);
        glVertex2f(1174,140);
        glVertex2f(1187,140);
        glVertex2f(1187,125);
    glEnd();

    getColor("railingShade");
    glBegin(GL_QUADS);
        glVertex2f(1571,125);
        glVertex2f(1571,140);
        glVertex2f(1584,140);
        glVertex2f(1584,125);
    glEnd();
}

//Road surface under cars and bridge pillars
void roadSurface()
{
    // Main road bed
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,110);
        glVertex2f(0,150);
        glVertex2f(1920,150);
        glVertex2f(1920,110);
    glEnd();

    // Subtle top shade to separate road from cars visually
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(0,145);
        glVertex2f(0,150);
        glVertex2f(1920,150);
        glVertex2f(1920,145);
    glEnd();
}

//Water
void water()
{
    getColor("water");
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(0,110);
        glVertex2f(1920,110);
        glVertex2f(1920,0);
    glEnd();
}

//Reflection
void reflection()
{
    // Base dark band under the shoreline
    getColor("reflectionDark");
    glBegin(GL_QUADS);
        glVertex2f(0,95);
        glVertex2f(0,110);
        glVertex2f(1920,110);
        glVertex2f(1920,95);
    glEnd();

    // Front Building 1 reflection (x 0-180)
    getColor("reflectionLight");
    glBegin(GL_QUADS);
        glVertex2f(0,70);
        glVertex2f(0,95);
        glVertex2f(180,95);
        glVertex2f(180,70);
    glEnd();

    // Front Building 2 reflection (x 200-800)
    getColor("reflectionDark");
    glBegin(GL_QUADS);
        glVertex2f(200,65);
        glVertex2f(200,95);
        glVertex2f(800,95);
        glVertex2f(800,65);
    glEnd();

    // Front Building 3 reflection (x 1280-1430)
    getColor("reflectionLight");
    glBegin(GL_QUADS);
        glVertex2f(1280,70);
        glVertex2f(1280,95);
        glVertex2f(1430,95);
        glVertex2f(1430,70);
    glEnd();

    // Front Building 4 reflection (x 1550-1850)
    getColor("reflectionDark");
    glBegin(GL_QUADS);
        glVertex2f(1550,60);
        glVertex2f(1550,95);
        glVertex2f(1850,95);
        glVertex2f(1850,60);
    glEnd();

    glPopMatrix();
}


//sun
void sun()
{
    const float cx = 965.0f;
    const float cy = 990.0f;
    const float rSun = 45.0f;
    const float rMoon = 35.0f;
    const int segments = 48;

    if (isDay) {
        // Warm sun disk
        getColor("sunDay");
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segments; ++i) {
                float ang = (2.0f * M_PI * i) / segments;
                glVertex2f(cx + cosf(ang) * rSun, cy + sinf(ang) * rSun);
            }
        glEnd();
    } else {
        // Moon: bright disk minus a cutout for crescent
        getColor("moon");
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segments; ++i) {
                float ang = (2.0f * M_PI * i) / segments;
                glVertex2f(cx + cosf(ang) * rMoon, cy + sinf(ang) * rMoon);
            }
        glEnd();

        // Cutout to form crescent using night sky color
        getColor("skyNight");
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx + 12.0f, cy);
            for (int i = 0; i <= segments; ++i) {
                float ang = (2.0f * M_PI * i) / segments;
                glVertex2f(cx + 12.0f + cosf(ang) * (rMoon - 6.0f), cy + sinf(ang) * (rMoon - 6.0f));
            }
        glEnd();
    }
}

//Boat on water (bottom-right)
void boat()
{
    glPushMatrix();
    glTranslatef(-(float)boatPosition, -25.0f, 0.0f);
    
    // Main hull - proper boat shape with curved bow
    getColor("boatHull");
    glBegin(GL_POLYGON);
        glVertex2f(1200,50);  // Stern bottom
        glVertex2f(1850,50);  // Mid bottom
        glVertex2f(1900,58);  // Bow bottom curve
        glVertex2f(1930,72);  // Bow tip lower
        glVertex2f(1935,85);  // Bow tip upper
        glVertex2f(1915,100); // Bow upper curve
        glVertex2f(1850,110); // Bow deck level
        glVertex2f(1350,115); // Mid deck level
        glVertex2f(1230,110); // Stern curve upper
        glVertex2f(1210,90);  // Stern curve
        glVertex2f(1205,70);  // Stern lower
    glEnd();

    // Hull shadow/shading
    getColor("boatShadow");
    glBegin(GL_QUADS);
        glVertex2f(1220,58);
        glVertex2f(1840,58);
        glVertex2f(1870,70);
        glVertex2f(1240,70);
    glEnd();

    // Lower deck
    getColor("boatDeck");
    glBegin(GL_QUADS);
        glVertex2f(1230,110);
        glVertex2f(1850,110);
        glVertex2f(1850,118);
        glVertex2f(1230,118);
    glEnd();

    // Upper deck sections
    getColor("boatDeck");
    glBegin(GL_QUADS);
        glVertex2f(1350,115);
        glVertex2f(1750,115);
        glVertex2f(1750,125);
        glVertex2f(1350,125);
    glEnd();

    // Front deck area
    getColor("boatDeck");
    glBegin(GL_QUADS);
        glVertex2f(1750,115);
        glVertex2f(1880,115);
        glVertex2f(1880,125);
        glVertex2f(1750,125);
    glEnd();

    // Bow deck triangle
    getColor("boatDeck");
    glBegin(GL_TRIANGLES);
        glVertex2f(1880,115);
        glVertex2f(1915,120);
        glVertex2f(1880,125);
    glEnd();

    // Main cabin structure
    getColor("boatCabin");
    glBegin(GL_QUADS);
        glVertex2f(1420,125);
        glVertex2f(1720,125);
        glVertex2f(1720,200);
        glVertex2f(1420,200);
    glEnd();

    // Cabin side shading
    getColor("boatCabinShade");
    glBegin(GL_QUADS);
        glVertex2f(1720,125);
        glVertex2f(1740,125);
        glVertex2f(1740,200);
        glVertex2f(1720,200);
    glEnd();

    // Cabin roof structure
    getColor("boatCabinShade");
    glBegin(GL_POLYGON);
        glVertex2f(1410,200);
        glVertex2f(1730,200);
        glVertex2f(1740,205);
        glVertex2f(1740,218);
        glVertex2f(1420,218);
    glEnd();

    // Bridge/Upper cabin
    getColor("boatCabin");
    glBegin(GL_QUADS);
        glVertex2f(1520,218);
        glVertex2f(1640,218);
        glVertex2f(1640,260);
        glVertex2f(1520,260);
    glEnd();

    // Bridge roof
    getColor("boatCabinShade");
    glBegin(GL_QUADS);
        glVertex2f(1510,260);
        glVertex2f(1650,260);
        glVertex2f(1645,272);
        glVertex2f(1515,272);
    glEnd();

    // Large front windows on main cabin
    getColor("boatWindow");
    glBegin(GL_QUADS);
        glVertex2f(1440,145);
        glVertex2f(1550,145);
        glVertex2f(1550,185);
        glVertex2f(1440,185);
    glEnd();

    getColor("boatWindow");
    glBegin(GL_QUADS);
        glVertex2f(1570,145);
        glVertex2f(1680,145);
        glVertex2f(1680,185);
        glVertex2f(1570,185);
    glEnd();

    // Bridge windows
    getColor("boatWindow");
    glBegin(GL_QUADS);
        glVertex2f(1535,230);
        glVertex2f(1600,230);
        glVertex2f(1600,250);
        glVertex2f(1535,250);
    glEnd();

    // Window dividers for realism
    getColor("boatCabin");
    glBegin(GL_QUADS);
        glVertex2f(1493,145);
        glVertex2f(1497,145);
        glVertex2f(1497,185);
        glVertex2f(1493,185);
    glEnd();

    getColor("boatCabin");
    glBegin(GL_QUADS);
        glVertex2f(1623,145);
        glVertex2f(1627,145);
        glVertex2f(1627,185);
        glVertex2f(1623,185);
    glEnd();

    // Portholes on hull - circular look
    getColor("boatPorthole");
    for(int i = 0; i < 5; i++) {
        glBegin(GL_POLYGON);
            float cx = 1280 + i*100;
            float cy = 85;
            float radius = 12;
            for(int j = 0; j < 20; j++) {
                float angle = 2.0f * 3.14159f * j / 20;
                glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
            }
        glEnd();
    }

    // Railing on front deck
    getColor("boatShadow");
    glBegin(GL_QUADS);
        glVertex2f(1750,125);
        glVertex2f(1880,125);
        glVertex2f(1880,127);
        glVertex2f(1750,127);
    glEnd();

    // Small railings posts
    for(int i = 0; i < 6; i++) {
        getColor("boatShadow");
        glBegin(GL_QUADS);
            glVertex2f(1760 + i*20, 115);
            glVertex2f(1763 + i*20, 115);
            glVertex2f(1763 + i*20, 125);
            glVertex2f(1760 + i*20, 125);
        glEnd();
    }

    // Smokestack/funnel
    getColor("boatCabinShade");
    glBegin(GL_QUADS);
        glVertex2f(1450,200);
        glVertex2f(1480,200);
        glVertex2f(1480,250);
        glVertex2f(1450,250);
    glEnd();

    // Funnel top
    getColor("boatShadow");
    glBegin(GL_QUADS);
        glVertex2f(1445,250);
        glVertex2f(1485,250);
        glVertex2f(1485,258);
        glVertex2f(1445,258);
    glEnd();

    glPopMatrix();
}

//cloud
void cloud()
{
    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(739,964);
        glVertex2f(739,969);
        glVertex2f(891,969);
        glVertex2f(891,964);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(771,969);
        glVertex2f(771,978);
        glVertex2f(842,978);
        glVertex2f(842,969);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(855,969);
        glVertex2f(855,978);
        glVertex2f(916,978);
        glVertex2f(916,969);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(795,978);
        glVertex2f(795,984);
        glVertex2f(826,984);
        glVertex2f(826,978);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(814,957);
        glVertex2f(814,964);
        glVertex2f(872,964);
        glVertex2f(872,957);
    glEnd();
}

void cloudMove()
{
    glPushMatrix();
    glTranslatef(cloudPosition,0, 0);
    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1107,1034);
        glVertex2f(1107,1039);
        glVertex2f(1265,1039);
        glVertex2f(1265,1034);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1120,1029);
        glVertex2f(1120,1034);
        glVertex2f(1188,1034);
        glVertex2f(1188,1029);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1205,1029);
        glVertex2f(1205,1034);
        glVertex2f(1281,1034);
        glVertex2f(1281,1029);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1164,1039);
        glVertex2f(1164,1044);
        glVertex2f(1216,1044);
        glVertex2f(1216,1039);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1168,1044);
        glVertex2f(1168,1048);
        glVertex2f(1212,1048);
        glVertex2f(1212,1044);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1188,1048);
        glVertex2f(1188,1053);
        glVertex2f(1200,1053);
        glVertex2f(1200,1048);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1232,1024);
        glVertex2f(1232,1029);
        glVertex2f(1241,1029);
        glVertex2f(1241,1024);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1253,1024);
        glVertex2f(1253,1029);
        glVertex2f(1273,1029);
        glVertex2f(1273,1024);
    glEnd();
    glPopMatrix();
}

//Background
void backGround()
{
    // Day/night sky and water
    if (isDay) {
        getColor("sky");
    } else {
        getColor("skyNight");
    }
    glBegin(GL_QUADS);
        glVertex2f(0, 600);
        glVertex2f(1920, 600);
        glVertex2f(1920, 1080);
        glVertex2f(0, 1080);
    glEnd();

    // Water
    if (isDay) {
        getColor("seaDay");
    } else {
        getColor("seaNight");
    }
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1920, 0);
        glVertex2f(1920, 600);
        glVertex2f(0, 600);
    glEnd();
}

//Timer callback for animation
void update(int value)
{
    trainPosition += 13.0f;
    if (trainPosition > 1820) trainPosition = -1600;
    
    // Car 1 moves left (headlights on the left side)
    carPosition_1 -= 8.0f;
    if (carPosition_1 < -1600) carPosition_1 = 1800.0f;
    
    carPosition_2 += 7.4f;
    if (carPosition_2 > 2100) carPosition_2 = -350;

    carPosition_3 -= 8.2f; // left-moving
    if (carPosition_3 < -1600) carPosition_3 = 1800;

    carPosition_4 += 6.0f; // right-moving
    if (carPosition_4 > 2100) carPosition_4 = -700;
    
    boatPosition += boatSpeed;
    if (boatPosition > 1920) boatPosition = -950.0f;
    
    cloudPosition_1 += 1.5f;
    if (cloudPosition_1 > 1920) cloudPosition_1 = -200;
    
    cloudPosition_2 += 1.4f;
    if (cloudPosition_2 > 1920) cloudPosition_2 = -200;
    
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

//Idle callback
void idle()
{
    glutPostRedisplay();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Background
    backGround();
    //Cloud Move
    cloudMove();
    //Back Back Building
    backBackBuilding_1();
    backBackBuilding_2();
    backBackBuilding_3();
    //Back Building
    backBuilding_1();
    backBuilding_2();
    backBuilding_3();
    backBuilding_4();
    backBuilding_5();
    //Front Building
    frontBuilding_1();
    frontBuilding_2();
    frontBuilding_3();
    frontBuilding_4();
    //Train
    train();
    //Road under cars and bridge pillars
    roadSurface();
    //Street Light
    streetLight();
    //Car
    car_1();
    car_2();
    car_3();
    car_4();
    //Train Bridge
    trainBridge();
    //Water
    water();
    //Reflection
    reflection();
    //Boat
    boat();
    //Sun
    sun();
    //Cloud
    cloud();

    glutSwapBuffers();
}

void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1920.0, 0.0, 1080.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1920.0, 0.0, 1080.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
            case 'n':
                isDay = !isDay;
                break;
            default:
                break;
        }
        glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize (1280, 720);
    glutCreateWindow ("Pixel City");
    myInit ();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutIdleFunc(idle);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
