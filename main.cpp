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
float evenReflectionPosition = 0.0f;
float oddReflectionPosition = 0.0f;
float cloudPosition = 0.0f;
float cloudPosition2 = 400.0f;
float cloudPosition3 = 800.0f;
float cloudPosition4 = 1200.0f;
bool dayNight = true;
float clockTime = 0.0f;  // Simulated time for clock (0-12 hours)

// Function to set color from palette
void getColor(const string& colorName) {
    if (colors.find(colorName) != colors.end()) {
        Color c = colors[colorName];
        glColor3ub(c.r, c.g, c.b);
    } else {
        glColor3ub(255, 255, 255); // Default white if color not found
    }
}

// Function to render text on buildings
void renderText(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to render larger bold text - thick and bold
void renderTextLarge(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    // Draw text multiple times for thickness effect
    glRasterPos2f(x + 1, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 2, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to render 2x bigger bold text
void renderTextExtraLarge(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 1, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 2, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 3, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x, y - 1);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 1, y - 1);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 2, y - 1);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(x + 3, y - 1);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to render 2x bigger text without bold
void renderTextBigger(float x, float y, const string& text) {
    float spacing = 22.0f; // Gap between characters
    for (size_t i = 0; i < text.length(); i++) {
        float charX = x + (i * spacing);
        // Move M character 8 pixels left
        if (i == 0) charX -= 8.0f;
        
        glRasterPos2f(charX, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        glRasterPos2f(charX + 1, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        glRasterPos2f(charX, y - 1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        glRasterPos2f(charX + 1, y - 1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// Function to draw an ornamental watch tower clock
void drawClock(float x, float y, float time) {
    // Outer decorative ring (gold-like)
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 32; i++) {
            float rad = i * 11.25f * 3.14159f / 180.0f;
            glVertex2f(x + 58.0f * cos(rad), y + 58.0f * sin(rad));
        }
    glEnd();
    
    // Outer frame border (dark metal)
    glColor3ub(40, 40, 40);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 32; i++) {
            float rad = i * 11.25f * 3.14159f / 180.0f;
            glVertex2f(x + 58.0f * cos(rad), y + 58.0f * sin(rad));
        }
    glEnd();
    
    // Inner silver ring
    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 32; i++) {
            float rad = i * 11.25f * 3.14159f / 180.0f;
            glVertex2f(x + 54.0f * cos(rad), y + 54.0f * sin(rad));
        }
    glEnd();
    
    // Clock face background - white (main dial)
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 32; i++) {
            float rad = i * 11.25f * 3.14159f / 180.0f;
            glVertex2f(x + 50.0f * cos(rad), y + 50.0f * sin(rad));
        }
    glEnd();
    
    // Clock face border - dark circle
    glColor3ub(50, 50, 50);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 32; i++) {
            float rad = i * 11.25f * 3.14159f / 180.0f;
            glVertex2f(x + 50.0f * cos(rad), y + 50.0f * sin(rad));
        }
    glEnd();
    
    // Hour markers - Roman numeral style thick lines
    glColor3ub(30, 30, 30);
    for(int h = 0; h < 12; h++) {
        float angle = (h * 30.0f - 90.0f) * 3.14159f / 180.0f;
        float markerX1 = x + 45.0f * cos(angle);
        float markerY1 = y + 45.0f * sin(angle);
        float markerX2 = x + 40.0f * cos(angle);
        float markerY2 = y + 40.0f * sin(angle);
        
        glBegin(GL_QUADS);
            glVertex2f(markerX1 - 1.5f, markerY1 - 1.5f);
            glVertex2f(markerX1 + 1.5f, markerY1 + 1.5f);
            glVertex2f(markerX2 + 1.5f, markerY2 + 1.5f);
            glVertex2f(markerX2 - 1.5f, markerY2 - 1.5f);
        glEnd();
    }
    
    // Decorative minute markers
    glColor3ub(150, 150, 150);
    for(int m = 0; m < 60; m++) {
        if(m % 5 != 0) {  // Skip hour positions
            float angle = (m * 6.0f - 90.0f) * 3.14159f / 180.0f;
            float markerX = x + 48.0f * cos(angle);
            float markerY = y + 48.0f * sin(angle);
            
            glBegin(GL_POLYGON);
                for(int i = 0; i < 6; i++) {
                    float rad = i * 60.0f * 3.14159f / 180.0f;
                    glVertex2f(markerX + 0.8f * cos(rad), markerY + 0.8f * sin(rad));
                }
            glEnd();
        }
    }
    
    // Heavy duty metallic hub - large and solid
    glColor3ub(120, 120, 120);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 16; i++) {
            float rad = i * 22.5f * 3.14159f / 180.0f;
            glVertex2f(x + 8.0f * cos(rad), y + 8.0f * sin(rad));
        }
    glEnd();
    
    // Hub center reinforcement
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 8; i++) {
            float rad = i * 45.0f * 3.14159f / 180.0f;
            glVertex2f(x + 4.0f * cos(rad), y + 4.0f * sin(rad));
        }
    glEnd();
    
    // Hour hand (shorter, thick, ornate)
    float hourAngle = (fmod(-time * 2.0f, 12.0f) / 12.0f * 360.0f - 90.0f) * 3.14159f / 180.0f;
    glColor3ub(20, 20, 20);
    glBegin(GL_QUADS);
        float hx1 = x + 20.0f * cos(hourAngle);
        float hy1 = y + 20.0f * sin(hourAngle);
        float hx2 = x + 6.0f * cos(hourAngle + 1.5708f);
        float hy2 = y + 6.0f * sin(hourAngle + 1.5708f);
        float hx3 = x + 6.0f * cos(hourAngle - 1.5708f);
        float hy3 = y + 6.0f * sin(hourAngle - 1.5708f);
        
        glVertex2f(x, y);
        glVertex2f(hx2, hy2);
        glVertex2f(hx1, hy1);
        glVertex2f(hx3, hy3);
    glEnd();
    
    // Hour hand decorative tip
    glColor3ub(200, 160, 0);  // Gold tip
    glBegin(GL_POLYGON);
        float hx = x + 20.0f * cos(hourAngle);
        float hy = y + 20.0f * sin(hourAngle);
        for(int i = 0; i < 6; i++) {
            float rad = i * 60.0f * 3.14159f / 180.0f;
            glVertex2f(hx + 1.5f * cos(rad), hy + 1.5f * sin(rad));
        }
    glEnd();
    
    // Minute hand (longer, elegant)
    float minuteAngle = (fmod(-time * 2.0f * 12.0f, 60.0f) / 60.0f * 360.0f - 90.0f) * 3.14159f / 180.0f;
    glColor3ub(100, 100, 100);
    glBegin(GL_QUADS);
        float mx1 = x + 33.0f * cos(minuteAngle);
        float my1 = y + 33.0f * sin(minuteAngle);
        float mx2 = x + 4.5f * cos(minuteAngle + 1.5708f);
        float my2 = y + 4.5f * sin(minuteAngle + 1.5708f);
        float mx3 = x + 4.5f * cos(minuteAngle - 1.5708f);
        float my3 = y + 4.5f * sin(minuteAngle - 1.5708f);
        
        glVertex2f(x, y);
        glVertex2f(mx2, my2);
        glVertex2f(mx1, my1);
        glVertex2f(mx3, my3);
    glEnd();
    
    // Minute hand decorative tip
    glColor3ub(180, 180, 180);
    glBegin(GL_POLYGON);
        float mx = x + 33.0f * cos(minuteAngle);
        float my = y + 33.0f * sin(minuteAngle);
        for(int i = 0; i < 6; i++) {
            float rad = i * 60.0f * 3.14159f / 180.0f;
            glVertex2f(mx + 1.2f * cos(rad), my + 1.2f * sin(rad));
        }
    glEnd();
    
    // Center ornamental jewel
    glColor3ub(255, 215, 0);  // Gold
    glBegin(GL_POLYGON);
        for(int i = 0; i < 8; i++) {
            float rad = i * 45.0f * 3.14159f / 180.0f;
            glVertex2f(x + 2.5f * cos(rad), y + 2.5f * sin(rad));
        }
    glEnd();
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
    
    // Hospital name - centered on top with black background
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(390, 765);
        glVertex2f(590, 765);
        glVertex2f(590, 830);
        glVertex2f(390, 830);
    glEnd();
    if (isDay) {
        glColor3ub(255, 255, 255);
    } else {
        glColor3ub(255, 255, 0);
    }
    renderTextLarge(420, 795, "HOSPITAL");
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
    
    // School name - centered on top with black background
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(1000, 780);
        glVertex2f(1175, 780);
        glVertex2f(1175, 845);
        glVertex2f(1000, 845);
    glEnd();
    if (isDay) {
        glColor3ub(255, 255, 255);
    } else {
        glColor3ub(255, 255, 0);
    }
    renderTextLarge(1032, 810, "SCHOOL");
    
    // Clock on school building
    drawClock(1355, 875, clockTime);
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
    
    // Mall name - centered on top with black background
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(1630, 900);
        glVertex2f(1750, 900);
        glVertex2f(1750, 965);
        glVertex2f(1630, 965);
    glEnd();
    
    if (isDay) {
        glColor3ub(255, 255, 255);
    } else {
        glColor3ub(255, 255, 0);
    }
    renderTextBigger(1657, 930, "MALL");
}


//Train Bridge
void trainBridge()
{
    // Simple metro rail elevated bridge
    
    // Main train track deck (thicker below)
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,430);
        glVertex2f(1920,430);
        glVertex2f(1920,410);
        glVertex2f(0,410);
    glEnd();
    
    // Deck underside
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(0,410);
        glVertex2f(1920,410);
        glVertex2f(1920,405);
        glVertex2f(0,405);
    glEnd();
    
    // Support pillars (hourglass/tapered shape - wider in middle)
    float pillarPositions[] = {200, 480, 760, 1040, 1320, 1600, 1880};
    
    for(int i = 0; i < 7; i++) {
        float x = pillarPositions[i];
        
        // Upper tapered section (narrows going down)
        getColor("bridgeShade");
        glBegin(GL_QUADS);
            // Wide at top
            glVertex2f(x - 35, 415);
            glVertex2f(x + 35, 415);
            // Narrower in middle
            glVertex2f(x + 25, 300);
            glVertex2f(x - 25, 300);
        glEnd();
        
        // Lower tapered section (narrows going down more)
        glBegin(GL_QUADS);
            // Wide in middle
            glVertex2f(x - 25, 300);
            glVertex2f(x + 25, 300);
            // Narrower at bottom
            glVertex2f(x + 15, 150);
            glVertex2f(x - 15, 150);
        glEnd();
        
        // Pillar side highlight
        getColor("bridge");
        glBegin(GL_QUADS);
            glVertex2f(x + 35, 415);
            glVertex2f(x + 38, 415);
            glVertex2f(x + 28, 300);
            glVertex2f(x + 25, 300);
        glEnd();
        
        glBegin(GL_QUADS);
            glVertex2f(x + 25, 300);
            glVertex2f(x + 28, 300);
            glVertex2f(x + 18, 150);
            glVertex2f(x + 15, 150);
        glEnd();
        
        // Base for stability
        getColor("bridgeShade");
        glBegin(GL_QUADS);
            glVertex2f(x - 20, 155);
            glVertex2f(x + 20, 155);
            glVertex2f(x + 20, 150);
            glVertex2f(x - 20, 150);
        glEnd();
    }
    
    // Road deck below
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,300);
        glVertex2f(1920,300);
        glVertex2f(1920,290);
        glVertex2f(0,290);
    glEnd();
    
    // Road deck edge
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(0,290);
        glVertex2f(1920,290);
        glVertex2f(1920,288);
        glVertex2f(0,288);
    glEnd();
    
    // Simple side barriers on road
    getColor("bridgeShade");
    for(int i = 0; i < 48; i++) {
        float x = i * 40;
        glBegin(GL_QUADS);
            glVertex2f(x, 300);
            glVertex2f(x + 3, 300);
            glVertex2f(x + 3, 275);
            glVertex2f(x, 275);
        glEnd();
    }
    
    // Road deck below
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(0,300);
        glVertex2f(1920,300);
        glVertex2f(1920,290);
        glVertex2f(0,290);
    glEnd();
    
    // Road deck edge
    getColor("bridgeShade");
    glBegin(GL_QUADS);
        glVertex2f(0,290);
        glVertex2f(1920,290);
        glVertex2f(1920,288);
        glVertex2f(0,288);
    glEnd();
    
    // Simple side barriers on road
    getColor("bridgeShade");
    for(int i = 0; i < 48; i++) {
        float x = i * 40;
        glBegin(GL_QUADS);
            glVertex2f(x, 300);
            glVertex2f(x + 3, 300);
            glVertex2f(x + 3, 275);
            glVertex2f(x, 275);
        glEnd();
    }
}

//Street Light
void streetLight()
{
//1st
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(335,125);
        glVertex2f(335,240);
        glVertex2f(343,240);
        glVertex2f(343,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(343,232);
        glVertex2f(343,240);
        glVertex2f(366,240);
        glVertex2f(366,232);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(366,225);
        glVertex2f(366,232);
        glVertex2f(374,232);
        glVertex2f(374,225);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(366,218);
        glVertex2f(366,225);
        glVertex2f(374,225);
        glVertex2f(374,218);
    glEnd();
//2nd
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(646,125);
        glVertex2f(646,240);
        glVertex2f(654,240);
        glVertex2f(654,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(654,232);
        glVertex2f(654,240);
        glVertex2f(677,240);
        glVertex2f(677,232);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(677,225);
        glVertex2f(677,232);
        glVertex2f(685,232);
        glVertex2f(685,225);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(677,218);
        glVertex2f(677,225);
        glVertex2f(685,225);
        glVertex2f(685,218);
    glEnd();
//3rd
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1120,125);
        glVertex2f(1120,240);
        glVertex2f(1128,240);
        glVertex2f(1128,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1128,232);
        glVertex2f(1128,240);
        glVertex2f(1151,240);
        glVertex2f(1151,232);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1151,225);
        glVertex2f(1151,232);
        glVertex2f(1159,232);
        glVertex2f(1159,225);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(1151,218);
        glVertex2f(1151,225);
        glVertex2f(1159,225);
        glVertex2f(1159,218);
    glEnd();
//4th
    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1514,125);
        glVertex2f(1514,240);
        glVertex2f(1522,240);
        glVertex2f(1522,125);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1522,232);
        glVertex2f(1522,240);
        glVertex2f(1545,240);
        glVertex2f(1545,232);
    glEnd();

    getColor("bridge");
    glBegin(GL_QUADS);
        glVertex2f(1545,225);
        glVertex2f(1545,232);
        glVertex2f(1553,232);
        glVertex2f(1553,225);
    glEnd();

    getColor("whiteLight");
    glBegin(GL_QUADS);
        glVertex2f(1545,218);
        glVertex2f(1545,225);
        glVertex2f(1553,225);
        glVertex2f(1553,218);
    glEnd();
}

//Car
void car_1()
{
    glPushMatrix();
    glTranslatef(carPosition_1, 25, 0);
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

    // Headlight beam (night only) - pointing left
    if (!isDay) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4ub(255, 255, 200, 60);
        glBegin(GL_TRIANGLES);
            glVertex2f(1180, 145);
            glVertex2f(1040, 125);
            glVertex2f(1040, 165);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(1196, 169);
            glVertex2f(1020, 150);
            glVertex2f(1020, 188);
        glEnd();
        glDisable(GL_BLEND);
    }
    glPopMatrix();
}

void car_2()
{
    glPushMatrix();
    glTranslatef(carPosition_2, 25, 0);
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

    // Headlight beam (night only) - pointing right
    if (!isDay) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4ub(255, 255, 200, 60);
        glBegin(GL_TRIANGLES);
            glVertex2f(1695, 139);
            glVertex2f(1835, 125);
            glVertex2f(1835, 153);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(1634, 153);
            glVertex2f(1774, 139);
            glVertex2f(1774, 167);
        glEnd();
        glDisable(GL_BLEND);
    }
    glPopMatrix();
}

void car_3()
{
    glPushMatrix();
    glTranslatef(carPosition_3, 25, 0);
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

    // Headlight beam (night only) - pointing left
    if (!isDay) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4ub(255, 255, 200, 60);
        glBegin(GL_TRIANGLES);
            glVertex2f(400, 145);
            glVertex2f(260, 130);
            glVertex2f(260, 160);
        glEnd();
        glDisable(GL_BLEND);
    }
    glPopMatrix();
}

void car_4()
{
    glPushMatrix();
    glTranslatef(carPosition_4, 25, 0);
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

    // Headlight beam (night only) - pointing right
    if (!isDay) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4ub(255, 255, 200, 60);
        glBegin(GL_TRIANGLES);
            glVertex2f(170, 145);
            glVertex2f(310, 130);
            glVertex2f(310, 160);
        glEnd();
        glDisable(GL_BLEND);
    }
    glPopMatrix();
}

// DDA Line Drawing Algorithm
void drawDDALine(int x0, int y0, int x1, int y1, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    // Case handling like the taught process
    int steps;
    float xIncrement, yIncrement;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
        xIncrement = (float) (dx > 0 ? 1 : -1);
        yIncrement = (float)dy / (float)steps;
    } else {
        steps = abs(dy);
        xIncrement = (float)dx / (float)steps;
        yIncrement = (float) (dy > 0 ? 1 : -1);
    }

    // Start from initial point
    float x = (float)x0;
    float y = (float)y0;
    
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor4ub(r, g, b, a);
    
    for(int i = 0; i <= steps; i++) {
        glVertex2i((int)(x + 0.5), (int)(y + 0.5));  // Round to nearest integer
        x += xIncrement;
        y += yIncrement;
    }
    
    glEnd();
    glPointSize(1.0);
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

    // Train headlight beams using DDA algorithm (night only)
    if (!isDay) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Draw headlight beam using DDA line algorithm
        // Upper beam line
        int x0 = 1679, y0 = 505;
        int x1 = 1850, y1 = 530;
        drawDDALine(x0, y0, x1, y1, 255, 255, 200, 80);
        
        // Lower beam line
        x0 = 1679; y0 = 460;
        x1 = 1850; y1 = 435;
        drawDDALine(x0, y0, x1, y1, 255, 255, 200, 80);
        
        // Fill the beam area with semi-transparent light
        glColor4ub(255, 255, 200, 50);
        glBegin(GL_QUADS);
            glVertex2f(1679, 505);
            glVertex2f(1850, 530);
            glVertex2f(1850, 435);
            glVertex2f(1679, 460);
        glEnd();
        
        glDisable(GL_BLEND);
    }

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
// Midpoint Circle Algorithm - draws circle using 8-way symmetry
void drawMidpointCircle(int cX, int cY, int radius, const string& colorName)
{
    int X = 0, Y = radius;
    int p = 1 - radius;
    
    getColor(colorName);
    glBegin(GL_POINTS);
    
    while(X <= Y){
        // Plot all 8 octants
        // Octant 1 (X, Y)
        glVertex2i(X + cX, Y + cY);
        glVertex2i(Y + cX, X + cY);
        
        // Octant 2 (-X, Y)
        glVertex2i(-X + cX, Y + cY);
        glVertex2i(-Y + cX, X + cY);
        
        // Octant 3 (-X, -Y)
        glVertex2i(-X + cX, -Y + cY);
        glVertex2i(-Y + cX, -X + cY);
        
        // Octant 4 (X, -Y)
        glVertex2i(X + cX, -Y + cY);
        glVertex2i(Y + cX, -X + cY);
        
        // Update decision parameter and coordinates
        if(p < 0){
            X++;
            p = p + 2*X + 1;
        }
        else{
            X++;
            Y--;
            p = p + 2*X - 2*Y + 1;
        }
    }
    
    glEnd();
}

// Fill circle by drawing concentric circles using midpoint algorithm
void fillMidpointCircle(int cX, int cY, int radius, const string& colorName)
{
    // Draw filled circle by drawing all circles from radius down to 0
    for(int r = radius; r >= 0; r--){
        drawMidpointCircle(cX, cY, r, colorName);
    }
}

void sun()
{
    const int cx = 965;
    const int cy = 990;
    const int rSun = 45;
    const int rMoon = 35;

    if (isDay) {
        // Draw sun using midpoint circle algorithm
        fillMidpointCircle(cx, cy, rSun, "sunDay");
    } else {
        // Draw moon using midpoint circle algorithm
        fillMidpointCircle(cx, cy, rMoon, "moon");
        
        // Cutout to form crescent using night sky color
        fillMidpointCircle(cx + 12, cy, rMoon - 6, "skyNight");
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

    // White reflected bars on left window
    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1455,165);
        glVertex2f(1462,165);
        glVertex2f(1462,157);
        glVertex2f(1455,157);
    glEnd();

    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1462,172);
        glVertex2f(1470,172);
        glVertex2f(1470,165);
        glVertex2f(1462,165);
    glEnd();

    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1470,179);
        glVertex2f(1478,179);
        glVertex2f(1478,172);
        glVertex2f(1470,172);
    glEnd();

    // White reflected bars on right window
    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1585,165);
        glVertex2f(1592,165);
        glVertex2f(1592,157);
        glVertex2f(1585,157);
    glEnd();

    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1592,172);
        glVertex2f(1600,172);
        glVertex2f(1600,165);
        glVertex2f(1592,165);
    glEnd();

    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1600,179);
        glVertex2f(1608,179);
        glVertex2f(1608,172);
        glVertex2f(1600,172);
    glEnd();

    // White reflected bars on bridge window
    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1550,240);
        glVertex2f(1556,240);
        glVertex2f(1556,234);
        glVertex2f(1550,234);
    glEnd();

    glColor3ub(230, 240, 255);
    glBegin(GL_QUADS);
        glVertex2f(1556,245);
        glVertex2f(1562,245);
        glVertex2f(1562,240);
        glVertex2f(1556,240);
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
        glVertex2f(1107,950);
        glVertex2f(1107,955);
        glVertex2f(1265,955);
        glVertex2f(1265,950);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1120,945);
        glVertex2f(1120,950);
        glVertex2f(1188,950);
        glVertex2f(1188,945);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1205,945);
        glVertex2f(1205,950);
        glVertex2f(1281,950);
        glVertex2f(1281,945);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1164,955);
        glVertex2f(1164,960);
        glVertex2f(1216,960);
        glVertex2f(1216,955);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1168,960);
        glVertex2f(1168,964);
        glVertex2f(1212,964);
        glVertex2f(1212,960);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1188,964);
        glVertex2f(1188,969);
        glVertex2f(1200,969);
        glVertex2f(1200,964);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1232,940);
        glVertex2f(1232,945);
        glVertex2f(1241,945);
        glVertex2f(1241,940);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(1253,940);
        glVertex2f(1253,945);
        glVertex2f(1273,945);
        glVertex2f(1273,940);
    glEnd();
    glPopMatrix();
}

void cloudMove2()
{
    glPushMatrix();
    glTranslatef(cloudPosition2,0, 0);
    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(200,1005);
        glVertex2f(200,1010);
        glVertex2f(340,1010);
        glVertex2f(340,1005);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(210,1000);
        glVertex2f(210,1005);
        glVertex2f(270,1005);
        glVertex2f(270,1000);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(285,1000);
        glVertex2f(285,1005);
        glVertex2f(350,1005);
        glVertex2f(350,1000);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(240,1010);
        glVertex2f(240,1015);
        glVertex2f(285,1015);
        glVertex2f(285,1010);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(245,1015);
        glVertex2f(245,1019);
        glVertex2f(280,1019);
        glVertex2f(280,1015);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(260,1019);
        glVertex2f(260,1023);
        glVertex2f(270,1023);
        glVertex2f(270,1019);
    glEnd();
    glPopMatrix();
}

void cloudMove3()
{
    glPushMatrix();
    glTranslatef(cloudPosition3,0, 0);
    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(500,975);
        glVertex2f(500,980);
        glVertex2f(620,980);
        glVertex2f(620,975);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(515,970);
        glVertex2f(515,975);
        glVertex2f(565,975);
        glVertex2f(565,970);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(580,970);
        glVertex2f(580,975);
        glVertex2f(630,975);
        glVertex2f(630,970);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(545,980);
        glVertex2f(545,985);
        glVertex2f(585,985);
        glVertex2f(585,980);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(550,985);
        glVertex2f(550,989);
        glVertex2f(580,989);
        glVertex2f(580,985);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(560,989);
        glVertex2f(560,993);
        glVertex2f(570,993);
        glVertex2f(570,989);
    glEnd();
    glPopMatrix();
}

void cloudMove4()
{
    glPushMatrix();
    glTranslatef(cloudPosition4,0, 0);
    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(300,960);
        glVertex2f(300,965);
        glVertex2f(430,965);
        glVertex2f(430,960);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(315,955);
        glVertex2f(315,960);
        glVertex2f(370,960);
        glVertex2f(370,955);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(385,955);
        glVertex2f(385,960);
        glVertex2f(440,960);
        glVertex2f(440,955);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(345,965);
        glVertex2f(345,970);
        glVertex2f(390,970);
        glVertex2f(390,965);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(350,970);
        glVertex2f(350,974);
        glVertex2f(385,974);
        glVertex2f(385,970);
    glEnd();

    getColor("cloud");
    glBegin(GL_QUADS);
        glVertex2f(360,974);
        glVertex2f(360,978);
        glVertex2f(375,978);
        glVertex2f(375,974);
    glEnd();
    glPopMatrix();
}

//Background
// Stars in night sky
void stars()
{
    if (!isDay) {
        glColor3ub(255, 255, 255);
        glPointSize(2.0);
        glBegin(GL_POINTS);
        // Draw scattered stars across the sky
        glVertex2f(150, 950);
        glVertex2f(280, 1020);
        glVertex2f(420, 980);
        glVertex2f(580, 1050);
        glVertex2f(650, 920);
        glVertex2f(780, 1000);
        glVertex2f(850, 940);
        glVertex2f(1050, 1030);
        glVertex2f(1150, 970);
        glVertex2f(1280, 1010);
        glVertex2f(1420, 950);
        glVertex2f(1520, 1040);
        glVertex2f(1650, 990);
        glVertex2f(1780, 1020);
        glVertex2f(1850, 960);
        glVertex2f(320, 880);
        glVertex2f(500, 920);
        glVertex2f(720, 860);
        glVertex2f(940, 900);
        glVertex2f(1100, 870);
        glVertex2f(1340, 890);
        glVertex2f(1560, 850);
        glVertex2f(1720, 880);
        glVertex2f(200, 780);
        glVertex2f(450, 820);
        glVertex2f(680, 760);
        glVertex2f(890, 800);
        glVertex2f(1020, 740);
        glVertex2f(1220, 790);
        glVertex2f(1480, 770);
        glVertex2f(1670, 810);
        glVertex2f(1820, 750);
        glEnd();
        glPointSize(1.0);
    }
}

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
    
    cloudPosition += 5.5f;
    if (cloudPosition > 1920) cloudPosition = -350;
    
    cloudPosition2 += 4.2f;
    if (cloudPosition2 > 1920) cloudPosition2 = -450;
    
    cloudPosition3 += 3.8f;
    if (cloudPosition3 > 1920) cloudPosition3 = -550;
    
    cloudPosition4 += 6.1f;
    if (cloudPosition4 > 1920) cloudPosition4 = -250;
    
    clockTime += 0.01f;  // Faster clock advancement
    if (clockTime >= 12.0f) clockTime = 0.0f;  // Reset at 12 hours
    
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
    //Stars (night only)
    stars();
    //Cloud Move
    cloudMove();
    cloudMove2();
    cloudMove3();
    cloudMove4();
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
    //Cars moving right (behind pillars)
    car_2();
    car_4();
    //Train Bridge
    trainBridge();
    //Cars moving left (in front of pillars)
    car_1();
    car_3();
    //Water
    water();
    //Reflection
    reflection();
    //Boat
    boat();
    //Sun
    sun();

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
