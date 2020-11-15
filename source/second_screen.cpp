#include "globals.h"
#include "frm_main.h"
#include "graphics.h"

#include "second_screen.h"
#include <cstring>

uint64_t perf_times[10];
uint64_t graphics_times[17];

char messageBufs[10][41];
int currentMessage = 0;
bool debugMode = true;

void writeMessage(std::string message)
{

}

void drawSecondScreen()
{
    char tempBuf[41];
    frmMain.initDraw(1);

    SuperPrint("Logic times (us)", 4, 16, 0);
    // this frame minus last frame
    snprintf(tempBuf, 41, "Total %llu (%llu%%)", (perf_times[5]-perf_times[6])/268,
        100-((graphics_times[2]-graphics_times[1])*100)/(perf_times[5]-perf_times[6]));
    SuperPrint(tempBuf, 4, 336, 0);
    SuperPrint("Layers   NPCs Blocks Effect", 4, 16, 16);
    snprintf(tempBuf, 41, "%6llu %6llu %6llu %6llu", (perf_times[1]-perf_times[0])/268,
        (perf_times[2]-perf_times[1])/268, (perf_times[3]-perf_times[2])/268,
        (perf_times[4]-perf_times[3])/268);
    SuperPrint(tempBuf, 4, 16, 32);
    SuperPrint("Player   Draw  Sound Events", 4, 16, 48);
    snprintf(tempBuf, 41, "%6llu %6llu %6llu %6llu", (perf_times[5]-perf_times[4])/268,
        (perf_times[7]-perf_times[6])/268, (perf_times[8]-perf_times[7])/268,
        (perf_times[9]-perf_times[8])/268);
    SuperPrint(tempBuf, 4, 16, 64);

    SuperPrint("Draw times (us)", 4, 16, 96);
    SuperPrint("  Prep WaitBG Scenes BGNPCs Blocks", 4, 16, 112);
    snprintf(tempBuf, 41, "%6llu %6llu %6llu %6llu %6llu", (graphics_times[1]-graphics_times[0])/268,
        (graphics_times[2]-graphics_times[1])/268, (graphics_times[3]-graphics_times[2])/268,
        (graphics_times[4]-graphics_times[3])/268, (graphics_times[5]-graphics_times[4])/268);
    SuperPrint(tempBuf, 4, 16, 128);
    SuperPrint("FGNPCs Player Frgrnd Effect Intfac", 4, 16, 144);
    snprintf(tempBuf, 41, "%6llu %6llu %6llu %6llu %6llu", (graphics_times[6]-graphics_times[5])/268,
        (graphics_times[7]-graphics_times[6])/268, (graphics_times[8]-graphics_times[7])/268,
        (graphics_times[9]-graphics_times[8])/268, (graphics_times[10]-graphics_times[9])/268);
    SuperPrint(tempBuf, 4, 16, 160);
    SuperPrint("  Menu 2ndeye 2ndscr GPUdrw", 4, 16, 176);
    snprintf(tempBuf, 41, "%6llu %6llu %6llu %6llu", (graphics_times[11]-graphics_times[10])/268,
        (graphics_times[12]-graphics_times[11])/268, (graphics_times[14]-graphics_times[13])/268,
        (graphics_times[15]-graphics_times[14])/268);
    SuperPrint(tempBuf, 4, 16, 194);
}

void drawSecondScreen2()
{

}
