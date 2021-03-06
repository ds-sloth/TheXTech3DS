/*
 * TheXTech - A platform game engine ported from old source code for VB6
 *
 * Copyright (c) 2009-2011 Andrew Spinks, original VB6 code
 * Copyright (c) 2020-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "../globals.h"
#include "../graphics.h"
#include "../collision.h"
#include "../editor.h"
#include "../npc.h"
#include "../location.h"
#include "../n3ds-clock.h"
#include "../second_screen.h"
#include "../editor_screen.h"

#include <fmt_format_ne.h>


// This draws the graphic to the screen when in a level/game menu/outro/level editor
void UpdateGraphics(bool skipRepaint)
{
//    On Error Resume Next
    int A = 0;
    std::string timeStr;
    int Z = 0;
    int numScreens = 0;
    // FILE* log = fopen("/gfx.txt", "wb");
    // fprintf(log, "stack: %p\n", &log); fflush(log);
    // fputs("time 0\n",log); fflush(log);
    graphics_times[0] = svcGetSystemTick();

    if(!GameIsActive)
        return;

    // frame skip code
    cycleCount += 1;

    bool Do_FrameSkip = (FrameSkip && (SDL_GetTicks() + floor(1000 * (1 - (cycleCount / 63.0))) > GoalTime));
    if (!Do_FrameSkip) fpsCount++;

    std::string SuperText;
    std::string tempText;
    int BoxY = 0;
    bool tempBool = false;
    int B = 0;
    int C = 0;
    int D = 0;
    int E = 0;
    double d2 = 0;
    int X = 0;
    int Y = 0;
    int fBlock = 0;
    int lBlock = 0;
    Location_t tempLocation;
    int S = 0; // Level section to display

    if(Score > 9999990)
        Score = 9999990;

    if(Lives > 99)
        Lives = 99;

    numScreens = 1;

    // Background frames
    if(!Do_FrameSkip && !FreezeNPCs)
    {
        BackgroundFrameCount[26]++;
        if(BackgroundFrameCount[26] >= 8)
        {
            BackgroundFrame[26]++;
            if(BackgroundFrame[26] >= 8)
                BackgroundFrame[26] = 0;
            BackgroundFrameCount[26] = 0;
        }
        BackgroundFrameCount[18]++;
        if(BackgroundFrameCount[18] >= 12)
        {
            BackgroundFrame[18]++;
            if(BackgroundFrame[18] >= 4)
                BackgroundFrame[18] = 0;
            BackgroundFrame[19] = BackgroundFrame[18];
            BackgroundFrame[20] = BackgroundFrame[18];
            BackgroundFrame[161] = BackgroundFrame[18];
            BackgroundFrameCount[18] = 0;
        }
        BackgroundFrameCount[36] = BackgroundFrameCount[36] + 1;
        if(BackgroundFrameCount[36] >= 2)
        {
            BackgroundFrame[36] = BackgroundFrame[36] + 1;
            if(BackgroundFrame[36] >= 4)
                BackgroundFrame[36] = 0;
            BackgroundFrameCount[36] = 0;
        }
        BackgroundFrame[68] = BackgroundFrame[36];
        BackgroundFrameCount[65] = BackgroundFrameCount[65] + 1;
        if(BackgroundFrameCount[65] >= 8)
        {
            BackgroundFrame[65] = BackgroundFrame[65] + 1;
            if(BackgroundFrame[65] >= 4)
                BackgroundFrame[65] = 0;
            BackgroundFrameCount[65] = 0;
        }

        BackgroundFrame[66] = BackgroundFrame[65];

        BackgroundFrame[70] = BackgroundFrame[65];
        BackgroundFrame[100] = BackgroundFrame[65];

        BackgroundFrame[134] = BackgroundFrame[65];
        BackgroundFrame[135] = BackgroundFrame[65];
        BackgroundFrame[136] = BackgroundFrame[65];
        BackgroundFrame[137] = BackgroundFrame[65];
        BackgroundFrame[138] = BackgroundFrame[65];


        BackgroundFrameCount[82] = BackgroundFrameCount[82] + 1;
        if(BackgroundFrameCount[82] >= 10)
        {
            BackgroundFrame[82] = BackgroundFrame[82] + 1;
            if(BackgroundFrame[82] >= 4)
                BackgroundFrame[82] = 0;
            BackgroundFrameCount[82] = 0;
        }

        BackgroundFrameCount[170] = BackgroundFrameCount[170] + 1;
        if(BackgroundFrameCount[170] >= 8)
        {
            BackgroundFrame[170] = BackgroundFrame[170] + 1;
            if(BackgroundFrame[170] >= 4)
                BackgroundFrame[170] = 0;
            BackgroundFrame[171] = BackgroundFrame[170];
            BackgroundFrameCount[170] = 0;
        }

        BackgroundFrameCount[125] = BackgroundFrameCount[125] + 1;
        if(BackgroundFrameCount[125] >= 4)
        {
            if(BackgroundFrame[125] == 0)
                BackgroundFrame[125] = 1;
            else
                BackgroundFrame[125] = 0;
            BackgroundFrameCount[125] = 0;
        }
        SpecialFrames();
    }

    BackgroundFrame[172] = BackgroundFrame[66];
    BackgroundFrameCount[158] += 1;

    if(BackgroundFrameCount[158] >= 6)
    {
        BackgroundFrameCount[158] = 0;
        BackgroundFrame[158] = BackgroundFrame[158] + 1;
        BackgroundFrame[159] = BackgroundFrame[159] + 1;
        if(BackgroundFrame[158] >= 4)
            BackgroundFrame[158] = 0;
        if(BackgroundFrame[159] >= 8)
            BackgroundFrame[159] = 0;
    }

    BackgroundFrameCount[168] = BackgroundFrameCount[168] + 1;
    if(BackgroundFrameCount[168] >= 8)
    {
        BackgroundFrame[168] = BackgroundFrame[168] + 1;
        if(BackgroundFrame[168] >= 8)
            BackgroundFrame[168] = 0;
        BackgroundFrameCount[168] = 0;
    }

    BackgroundFrameCount[173] = BackgroundFrameCount[173] + 1;
    if(BackgroundFrameCount[173] >= 8)
    {
        BackgroundFrameCount[173] = 0;
        if(BackgroundFrame[173] == 0)
            BackgroundFrame[173] = 1;
        else
            BackgroundFrame[173] = 0;
    }

    BackgroundFrameCount[187] = BackgroundFrameCount[187] + 1;
    if(BackgroundFrameCount[187] >= 6)
    {
        BackgroundFrame[187] = BackgroundFrame[187] + 1;
        if(BackgroundFrame[187] >= 4)
            BackgroundFrame[187] = 0;
        BackgroundFrame[188] = BackgroundFrame[187];
        BackgroundFrame[189] = BackgroundFrame[187];
        BackgroundFrame[190] = BackgroundFrame[187];
        BackgroundFrameCount[187] = 0;
    }

    // Any and all screen-based logic... Things we don't want to need to do twice.
    if(ScreenType == 1)
        numScreens = 2;
    if(ScreenType == 4)
        numScreens = 2;
    if(ScreenType == 5)
    {
        DynamicScreen();
        if(vScreen[2].Visible)
            numScreens = 2;
        else
            numScreens = 1;
    }
    if(ScreenType == 8)
        numScreens = 1;
    if(SingleCoop == 2)
        numScreens = 2;

    For(Z, 1, numScreens)
    {
        if(SingleCoop == 2)
            Z = 2;

        if(LevelEditor)
            S = curSection;
        else
            S = Player[Z].Section;

        if(GameOutro) ScreenType = 7;

        if(!LevelEditor)
        {
            if(ScreenType == 2 || ScreenType == 3)
                GetvScreenAverage();
            else if(ScreenType == 5 && !vScreen[2].Visible)
                GetvScreenAverage();
            else if(ScreenType == 7)
                GetvScreenCredits();
            else
                GetvScreen(Z);

            if(ForcedControls || qScreen)
            {
                if(ScreenType == 2 || ScreenType == 3)
                    GetvScreenAverageCanonical(&X, &Y);
                else if(ScreenType == 5 && !vScreen[2].Visible)
                    GetvScreenAverageCanonical(&X, &Y);
                else if(ScreenType == 7)
                    GetvScreenAverageCanonical(&X, &Y);
                else
                    GetvScreenCanonical(Z, &X, &Y);
            }
        }

        if(!Do_FrameSkip && qScreen)
        {
            if(vScreenX[1] < qScreenX[1] - 2)
                qScreenX[1] = qScreenX[1] - 2;
            else if(vScreenX[1] > qScreenX[1] + 2)
                qScreenX[1] = qScreenX[1] + 2;
            if(vScreenY[1] < qScreenY[1] - 2)
                qScreenY[1] = qScreenY[1] - 2;
            else if(vScreenY[1] > qScreenY[1] + 2)
                qScreenY[1] = qScreenY[1] + 2;
            if(qScreenX[1] < vScreenX[1] + 5 && qScreenX[1] > vScreenX[1] - 5 &&
               qScreenY[1] < vScreenY[1] + 5 && qScreenY[1] > vScreenY[1] - 5)
                qScreen = false;
            vScreenX[1] = qScreenX[1];
            vScreenY[1] = qScreenY[1];
        }

        // noturningback
        if(!LevelEditor && NoTurnBack[Player[Z].Section])
        {
            A = Z;
            if(numScreens > 1)
            {
                if(Player[1].Section == Player[2].Section)
                {
                    if(Z == 1)
                        GetvScreen(2);
                    if(-vScreenX[1] < -vScreenX[2])
                        A = 1;
                    else
                        A = 2;
                }
            }
            if(-vScreenX[A] > level[S].X)
            {
                LevelChop[S] += float(-vScreenX[A] - level[S].X);
                level[S].X = -vScreenX[A];
            }
        }

        // Position swap code?
        if(!GameMenu && !LevelEditor)
        {
            if(numPlayers > 2)
            {
                For(A, 1, numPlayers)
                {
                    Player_t &p = Player[A];
                    if(!vScreenCollision(Z, p.Location) && LevelMacro == 0 &&
                        p.Location.Y < level[p.Section].Height &&
                        p.Location.Y + p.Location.Height > level[p.Section].Y &&
                        p.TimeToLive == 0 && !p.Dead)
                    {
                        for(B = 1; B <= numPlayers; B++)
                        {
                            if(!Player[B].Dead && Player[B].TimeToLive == 0 && Player[B].Section == Player[A].Section && vScreenCollision(Z, Player[B].Location))
                            {
                                if(C == 0 || std::abs(Player[A].Location.X + Player[A].Location.Width / 2.0 - (Player[B].Location.X + Player[B].Location.Width / 2.0)) < C)
                                {
                                    C = std::abs(Player[A].Location.X + Player[A].Location.Width / 2.0 - (Player[B].Location.X + Player[B].Location.Width / 2.0));
                                    D = B;
                                }
                            }
                        }
                        if(C == 0)
                        {
                            for(B = 1; B <= numPlayers; B++)
                            {
                                if(!Player[B].Dead && Player[B].TimeToLive == 0 && Player[B].Section == Player[A].Section)
                                {
                                    if(C == 0 || std::abs(Player[A].Location.X + Player[A].Location.Width / 2.0 - (Player[B].Location.X + Player[B].Location.Width / 2.0)) < C)
                                    {
                                        C = std::abs(Player[A].Location.X + Player[A].Location.Width / 2.0 - (Player[B].Location.X + Player[B].Location.Width / 2.0));
                                        D = B;
                                    }
                                }
                            }
                        }
                        Player[A].Location.X = Player[D].Location.X + Player[D].Location.Width / 2.0 - Player[A].Location.Width / 2.0;
                        Player[A].Location.Y = Player[D].Location.Y + Player[D].Location.Height - Player[A].Location.Height;
                        Player[A].Section = Player[D].Section;
                        Player[A].Location.SpeedX = Player[D].Location.SpeedX;
                        Player[A].Location.SpeedY = Player[D].Location.SpeedY;
                        Player[A].Location.SpeedY = dRand() * 12 - 6; // ?????
                        Player[A].CanJump = true;
                    }
                }
            }
        }
        if(!LevelEditor)
        {
            for(A = 1; A <= numNPCs; A++)
            {
                bool onscreen;
                if(ForcedControls || qScreen)
                    onscreen = vScreenCollisionCanonical(X, Y, NPC[A].Location);
                else
                    onscreen = vScreenCollision(Z, NPC[A].Location);
                if(onscreen && !NPC[A].Hidden)
                {
                    if(NPC[A].Type == 0) // figure this out
                    {
                        NPC[A].Killed = 9;
                        KillNPC(A, 9);
                    }
                    else if((NPC[A].Reset[1] && NPC[A].Reset[2]) || NPC[A].Active || NPC[A].Type == 57)
                    {
                        if(!NPC[A].Active)
                            NPC[A].JustActivated = Z;
                        NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
                        if(NPCIsYoshi[NPC[A].Type] || NPCIsBoot[NPC[A].Type] || NPC[A].Type == 9 || NPC[A].Type == 14 || NPC[A].Type == 22 || NPC[A].Type == 90 || NPC[A].Type == 153 || NPC[A].Type == 169 || NPC[A].Type == 170 || NPC[A].Type == 182 || NPC[A].Type == 183 || NPC[A].Type == 184 || NPC[A].Type == 185 || NPC[A].Type == 186 || NPC[A].Type == 187 || NPC[A].Type == 188 || NPC[A].Type == 195 || NPC[A].Type == 104)
                            NPC[A].TimeLeft = Physics.NPCTimeOffScreen * 20;

                        NPC[A].Active = true;
                    }
                    if(NPC[A].Generator)
                        NPC[A].GeneratorActive = true;
                    NPC[A].Reset[1] = false;
                    NPC[A].Reset[2] = false;
                }
                else
                {
                    NPC[A].Reset[Z] = true;
                    if(numScreens == 1)
                        NPC[A].Reset[2] = true;
                    if(SingleCoop == 1)
                        NPC[A].Reset[2] = true;
                    else if(SingleCoop == 2)
                        NPC[A].Reset[1] = true;
                }
            }
        }
    }

    if (Do_FrameSkip) return;

    if(ScreenShake > 0) // need to test...
    {
        ScreenShake--;
        if(ScreenShake == 0)
        {
            frmMain.offsetViewport(0, 0);
        }
        else
        {
            A = (iRand() % ScreenShake * 2)*2 - ScreenShake * 2;
            B = (iRand() % ScreenShake * 2)*2 - ScreenShake * 2;
            frmMain.offsetViewport(A, B);
        }
    }

    // printf("drawing... \n");
    // fputs("time 1\n",log); fflush(log);
    graphics_times[1] = svcGetSystemTick();
    frmMain.initDraw(0);
    // fputs("time 1.5\n",log); fflush(log);
    For(Z, 1, numScreens)
    {
        if(SingleCoop == 2)
            Z = 2;

        if (LevelEditor)
            S = curSection;
        else
            S = Player[Z].Section;

        if(numScreens > 1) // To separate drawing of screens
            frmMain.setViewport(vScreen[Z].Left, vScreen[Z].Top, vScreen[Z].Width, vScreen[Z].Height);

        // printf("background... \n");
        // try instead doing this one twice with the camera in different places.......
        frmMain.setLayer(0);
        // fputs("time 1.8\n",log); fflush(log);
        DrawBackground(S, Z);
        if(LevelEditor)
        {
            if (vScreenX[Z] + level[S].X > 0) {
                frmMain.renderRect(0, 0,
                                   vScreenX[Z] + level[S].X, ScreenH, 0.2f, 0.2f, 0.2f, 1.f, true);
            }
            if (ScreenW > level[S].Width + vScreenX[Z]) {
                frmMain.renderRect(level[S].Width + vScreenX[Z], 0,
                                   ScreenW - (level[S].Width + vScreenX[Z]), ScreenH, 0.2f, 0.2f, 0.2f, 1.f, true);
            }
            if (vScreenY[Z] + level[S].Y > 0) {
                frmMain.renderRect(0, 0,
                                   ScreenW, vScreenY[Z] + level[S].Y, 0.2f, 0.2f, 0.2f, 1.f, true);
            }
            if (ScreenH > level[S].Height + vScreenY[Z]) {
                frmMain.renderRect(0, level[S].Height + vScreenY[Z],
                                   ScreenW, ScreenH - (level[S].Height + vScreenY[Z]), 0.2f, 0.2f, 0.2f, 1.f, true);
            }
        }

        // fputs("time 2\n",log); fflush(log);
        graphics_times[2] = svcGetSystemTick();

        // printf("background tiles... \n");
        frmMain.setLayer(1);
        if (LevelEditor)
        {
            For(A, 1, numBackground)
            {
                if(Background[A].Type == 11 || Background[A].Type == 12 || Background[A].Type == 60
                    || Background[A].Type == 61 || Background[A].Type == 75 || Background[A].Type == 76
                    || Background[A].Type == 77 || Background[A].Type == 78 || Background[A].Type == 79)
                {
                    if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                    {
                        frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                              vScreenY[Z] + Background[A].Location.Y,
                                              GFXBackgroundWidth[Background[A].Type],
                                              BackgroundHeight[Background[A].Type],
                                              GFXBackgroundBMP[Background[A].Type], 0,
                                              BackgroundHeight[Background[A].Type] *
                                              BackgroundFrame[Background[A].Type]);
                    }
                }
            }
        }
        else{// NOT AN EDITOR
            For(A, 1, MidBackground - 1)  // First backgrounds
            {
                if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                {
                    frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                          vScreenY[Z] + Background[A].Location.Y,
                                          GFXBackgroundWidth[Background[A].Type],
                                          BackgroundHeight[Background[A].Type],
                                          GFXBackgroundBMP[Background[A].Type], 0,
                                          BackgroundHeight[Background[A].Type] *
                                          BackgroundFrame[Background[A].Type]);
                }
            }
        }

        tempLocation.Width = 32;
        tempLocation.Height = 32;

        // printf("blocks... \n");
        For(A, 1, sBlockNum) // Display sizable blocks
        {
            if(BlockIsSizable[Block[sBlockArray[A]].Type] && (!Block[sBlockArray[A]].Invis || LevelEditor))
            {
                if(vScreenCollision(Z, Block[sBlockArray[A]].Location) && !Block[sBlockArray[A]].Hidden)
                {
                    int bHeight = Block[sBlockArray[A]].Location.Height / 32.0;
                    for(B = 0; B < bHeight; B++)
                    {
                        int bWidth = Block[sBlockArray[A]].Location.Width / 32.0;
                        for(C = 0; C < bWidth; C++)
                        {
                            tempLocation.X = Block[sBlockArray[A]].Location.X + C * 32;
                            tempLocation.Y = Block[sBlockArray[A]].Location.Y + B * 32;
                            if(vScreenCollision(Z, tempLocation))
                            {
                                D = C;
                                E = B;

                                if(D != 0)
                                {
                                    if(fEqual(D, (Block[sBlockArray[A]].Location.Width / 32.0) - 1))
                                        D = 2;
                                    else
                                    {
                                        D = 1;
                                        d2 = 0.5;
                                        UNUSED(d2);
                                    }
                                }

                                if(E != 0)
                                {
                                    if(fEqual(E, (Block[sBlockArray[A]].Location.Height / 32.0) - 1))
                                        E = 2;
                                    else
                                        E = 1;
                                }
                                frmMain.renderTexture(vScreenX[Z] + Block[sBlockArray[A]].Location.X + C * 32, vScreenY[Z] + Block[sBlockArray[A]].Location.Y + B * 32, 32, 32, GFXBlockBMP[Block[sBlockArray[A]].Type], D * 32, E * 32);
                            }
                        }
                    }
                }
            }
        }

        if (LevelEditor)
        {
            For(A, 1, numBackground)
            {
                if(!(Background[A].Type == 11 || Background[A].Type == 12 || Background[A].Type == 60
                    || Background[A].Type == 61 || Background[A].Type == 75 || Background[A].Type == 76
                    || Background[A].Type == 77 || Background[A].Type == 78 || Background[A].Type == 79) && !Foreground[Background[A].Type])
                {
                    if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                    {
                        frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                              vScreenY[Z] + Background[A].Location.Y,
                                              GFXBackgroundWidth[Background[A].Type],
                                              BackgroundHeight[Background[A].Type],
                                              GFXBackgroundBMP[Background[A].Type], 0,
                                              BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
                    }
                }
            }
        }
        else { // NOT AN EDITOR
            for(A = MidBackground; A <= LastBackground; A++) // Second backgrounds
            {
                if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                {
                    frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                          vScreenY[Z] + Background[A].Location.Y,
                                          BackgroundWidth[Background[A].Type],
                                          BackgroundHeight[Background[A].Type],
                                          GFXBackgroundBMP[Background[A].Type],
                                          0, BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
                }
            }
        }

        For(A, numBackground + 1, numBackground + numLocked) // Locked doors
        {
            if(vScreenCollision(Z, Background[A].Location) &&
                (Background[A].Type == 98 || Background[A].Type == 160) && !Background[A].Hidden)
            {
                frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                      vScreenY[Z] + Background[A].Location.Y,
                                      BackgroundWidth[Background[A].Type], BackgroundHeight[Background[A].Type],
                                      GFXBackgroundBMP[Background[A].Type],
                                      0, BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
            }
        }

        // fputs("time 3\n",log); fflush(log);
        graphics_times[3] = svcGetSystemTick();
        frmMain.setLayer(2);
        // printf("some NPCs... \n");
        For(A, 1, numNPCs) // Display NPCs that should be behind blocks
        {
            if(((NPC[A].Effect == 208 || NPCIsAVine[NPC[A].Type] ||
                 NPC[A].Type == 209 || NPC[A].Type == 159 || NPC[A].Type == 245 ||
                 NPC[A].Type == 8 || NPC[A].Type == 93 || NPC[A].Type == 74 ||
                 NPC[A].Type == 256 || NPC[A].Type == 257 || NPC[A].Type == 51 ||
                 NPC[A].Type == 52 || NPC[A].Effect == 1 || NPC[A].Effect == 3 ||
                 NPC[A].Effect == 4 || (NPC[A].Type == 45 && NPC[A].Special == 0.0)) &&
                 (NPC[A].standingOnPlayer == 0 && (!NPC[A].Generator || LevelEditor))) ||
                 NPC[A].Type == 179 || NPC[A].Type == 270)
            {
                if(NPC[A].Effect != 2 && (!NPC[A].Generator || LevelEditor))
                {
                    if(vScreenCollision(Z, NPC[A].Location) && !NPC[A].Hidden)
                    {
                        if(NPC[A].Active)
                        {
                            if(NPC[A].Type == 8 || NPC[A].Type == 74 || NPC[A].Type == 93 || NPC[A].Type == 245 || NPC[A].Type == 256 || NPC[A].Type == 270)
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeight[NPC[A].Type], NPC[A].Shadow);
                            else if(NPC[A].Type == 51 || NPC[A].Type == 257)
                            {
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type],
                                        vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type],
                                        NPC[A].Location.Width, NPC[A].Location.Height,
                                        GFXNPC[NPC[A].Type], 0,
                                        NPC[A].Frame * NPCHeight[NPC[A].Type] + NPCHeight[NPC[A].Type] - NPC[A].Location.Height,
                                        NPC[A].Shadow);
                            }
                            else if(NPC[A].Type == 52)
                            {
                                if(NPC[A].Direction == -1)
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeight[NPC[A].Type], NPC[A].Shadow);
                                else
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], NPCWidth[NPC[A].Type] - NPC[A].Location.Width, NPC[A].Frame * NPCHeight[NPC[A].Type], NPC[A].Shadow);
                            }
                            else if(NPCWidthGFX[NPC[A].Type] == 0 || NPC[A].Effect == 1)
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeight[NPC[A].Type], NPC[A].Shadow);
                            else
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type] - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                        }
                    }
                }
            }
        }


        // printf("drawing players... \n");
        For(A, 1, numPlayers)
        {
            if(!Player[A].Dead && !Player[A].Immune2 && Player[A].TimeToLive == 0 && Player[A].Effect == 3)
            {
                float Y2 = 0;
                float X2 = 0;

                if(vScreenCollision(Z, Player[A].Location))
                {
                    // warp NPCs
                    if(Player[A].HoldingNPC > 0 && Player[A].Frame != 15)
                    {
                        if((vScreenCollision(Z, NPC[Player[A].HoldingNPC].Location) | vScreenCollision(Z, newLoc(NPC[Player[A].HoldingNPC].Location.X - (NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] - NPC[Player[A].HoldingNPC].Location.Width) / 2.0, NPC[Player[A].HoldingNPC].Location.Y, static_cast<double>(NPCWidthGFX[NPC[Player[A].HoldingNPC].Type]), static_cast<double>(NPCHeight[NPC[Player[A].HoldingNPC].Type])))) != 0 && NPC[Player[A].HoldingNPC].Hidden == false)
                        {
                            tempLocation = NPC[Player[A].HoldingNPC].Location;
                            if(NPCHeightGFX[NPC[Player[A].HoldingNPC].Type] != 0 || NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] != 0)
                            {
                                tempLocation.Height = NPCHeightGFX[NPC[Player[A].HoldingNPC].Type];
                                tempLocation.Width = NPCWidthGFX[NPC[Player[A].HoldingNPC].Type];
                                tempLocation.Y = NPC[Player[A].HoldingNPC].Location.Y + NPC[Player[A].HoldingNPC].Location.Height - NPCHeightGFX[NPC[Player[A].HoldingNPC].Type];
                                tempLocation.X = NPC[Player[A].HoldingNPC].Location.X + NPC[Player[A].HoldingNPC].Location.Width / 2.0 - NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] / 2.0;
                            }
                            else
                            {
                                tempLocation.Height = NPCHeight[NPC[Player[A].HoldingNPC].Type];
                                tempLocation.Width = NPCWidth[NPC[Player[A].HoldingNPC].Type];
                            }
                            tempLocation.X = tempLocation.X + NPCFrameOffsetX[NPC[Player[A].HoldingNPC].Type];
                            tempLocation.Y = tempLocation.Y + NPCFrameOffsetY[NPC[Player[A].HoldingNPC].Type];
                            Y2 = 0;
                            X2 = 0;
                            NPCWarpGFX(A, tempLocation, X2, Y2);
                            if(NPCHeightGFX[NPC[Player[A].HoldingNPC].Type] != 0 || NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] != 0)
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeightGFX[NPC[Player[A].HoldingNPC].Type]);
                            else
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeight[NPC[Player[A].HoldingNPC].Type]);

                        }
                    }

                    if(Player[A].Mount == 3)
                    {
                        B = Player[A].MountType;
                        // Yoshi's Body
                        tempLocation = Player[A].Location;
                        tempLocation.Height = 32;
                        tempLocation.Width = 32;
                        tempLocation.X = tempLocation.X + Player[A].YoshiBX;
                        tempLocation.Y = tempLocation.Y + Player[A].YoshiBY;
                        Y2 = 0;
                        X2 = 0;
                        PlayerWarpGFX(A, tempLocation, X2, Y2);
                        frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXYoshiB[B], X2, Y2 + 32 * Player[A].YoshiBFrame, ShadowMode);
                        // Yoshi's Head
                        tempLocation = Player[A].Location;
                        tempLocation.Height = 32;
                        tempLocation.Width = 32;
                        tempLocation.X = tempLocation.X + Player[A].YoshiTX;
                        tempLocation.Y = tempLocation.Y + Player[A].YoshiTY;
                        Y2 = 0;
                        X2 = 0;
                        PlayerWarpGFX(A, tempLocation, X2, Y2);
                        frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXYoshiT[B], X2, Y2 + 32 * Player[A].YoshiTFrame);
                    }
                    if(Player[A].Character == 1)
                    {
                        if(Player[A].Mount == 1)
                        {
                            tempLocation = Player[A].Location;
                            if(Player[A].State == 1)
                                tempLocation.Height = Player[A].Location.Height - MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            else
                                tempLocation.Height = Player[A].Location.Height - MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - 30;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + MarioFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXMario[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2);
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 32;
                            tempLocation.Width = 32;
                            tempLocation.X = tempLocation.X + Player[A].Location.Width / 2.0 - 16;
                            tempLocation.Y = tempLocation.Y + Player[A].Location.Height - 30;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFX.Boot[Player[A].MountType], X2, Y2 + 32 * Player[A].MountFrame);
                        }
                        else
                        {
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 99;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + MarioFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXMario[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2, ShadowMode);
                        }
                    }
                    else if(Player[A].Character == 2)
                    {
                        if(Player[A].Mount == 1)
                        {
                            tempLocation = Player[A].Location;
                            if(Player[A].State == 1)
                                tempLocation.Height = Player[A].Location.Height - LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            else
                                tempLocation.Height = Player[A].Location.Height - LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - 30;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + LuigiFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXLuigi[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2);
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 32;
                            tempLocation.Width = 32;
                            tempLocation.X = tempLocation.X + Player[A].Location.Width / 2.0 - 16;
                            tempLocation.Y = tempLocation.Y + Player[A].Location.Height - 30;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFX.Boot[Player[A].MountType], X2, Y2 + 32 * Player[A].MountFrame, ShadowMode);
                        }
                        else
                        {
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 99;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + LuigiFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXLuigi[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2);
                        }
                    }
                    else if(Player[A].Character == 3)
                    {
                        if(Player[A].Mount == 1)
                        {
                            tempLocation = Player[A].Location;
                            if(Player[A].State == 1)
                                tempLocation.Height = Player[A].Location.Height - PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            else
                                tempLocation.Height = Player[A].Location.Height - PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - 30;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXPeach[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2);
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 32;
                            tempLocation.Width = 32;
                            tempLocation.X = tempLocation.X + Player[A].Location.Width / 2.0 - 16;
                            tempLocation.Y = tempLocation.Y + Player[A].Location.Height - 30;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFX.Boot[Player[A].MountType], X2, Y2 + 32 * Player[A].MountFrame, ShadowMode);
                        }
                        else
                        {
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 99;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXPeach[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2, ShadowMode);
                        }
                    }
                    else if(Player[A].Character == 4)
                    {
                        if(Player[A].Mount == 1)
                        {
                            tempLocation = Player[A].Location;
                            if(Player[A].State == 1)
                                tempLocation.Height = Player[A].Location.Height - ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            else
                                tempLocation.Height = Player[A].Location.Height - ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - 26;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            if(Player[A].State == 1)
                                tempLocation.Y = tempLocation.Y + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + 6;
                            else
                                tempLocation.Y = tempLocation.Y + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - 4;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXToad[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2);
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 32;
                            tempLocation.Width = 32;
                            tempLocation.X = tempLocation.X + Player[A].Location.Width / 2.0 - 16;
                            tempLocation.Y = tempLocation.Y + Player[A].Location.Height - 30;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFX.Boot[Player[A].MountType], X2, Y2 + 32 * Player[A].MountFrame, ShadowMode);
                        }
                        else
                        {
                            tempLocation = Player[A].Location;
                            tempLocation.Height = 99;
                            tempLocation.Width = 99;
                            tempLocation.X = tempLocation.X + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                            tempLocation.Y = tempLocation.Y + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY;
                            Y2 = 0;
                            X2 = 0;
                            PlayerWarpGFX(A, tempLocation, X2, Y2);
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXToad[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2, ShadowMode);
                        }
                    }
                    else if(Player[A].Character == 5)
                    {
                        if(Player[A].Frame > 5)
                            Player[A].Frame = 1;
                        tempLocation = Player[A].Location;
                        tempLocation.Height = 99;
                        tempLocation.Width = 99;
                        tempLocation.X = tempLocation.X + LinkFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)];
                        tempLocation.Y = tempLocation.Y + LinkFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY;
                        Y2 = 0;
                        X2 = 0;
                        PlayerWarpGFX(A, tempLocation, X2, Y2);
                        frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXLink[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction) + X2, pfrY(100 + Player[A].Frame * Player[A].Direction) + Y2, ShadowMode);
                    }
                }
                if(Player[A].HoldingNPC > 0 && Player[A].Frame == 15)
                {
                    if((vScreenCollision(Z, NPC[Player[A].HoldingNPC].Location) | vScreenCollision(Z, newLoc(NPC[Player[A].HoldingNPC].Location.X - (NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] - NPC[Player[A].HoldingNPC].Location.Width) / 2.0, NPC[Player[A].HoldingNPC].Location.Y, static_cast<double>(NPCWidthGFX[NPC[Player[A].HoldingNPC].Type]), static_cast<double>(NPCHeight[NPC[Player[A].HoldingNPC].Type])))) != 0 && NPC[Player[A].HoldingNPC].Hidden == false && NPC[Player[A].HoldingNPC].Type != 263)
                    {
                        tempLocation = NPC[Player[A].HoldingNPC].Location;
                        if(NPCHeightGFX[NPC[Player[A].HoldingNPC].Type] != 0 || NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] != 0)
                        {
                            tempLocation.Height = NPCHeightGFX[NPC[Player[A].HoldingNPC].Type];
                            tempLocation.Width = NPCWidthGFX[NPC[Player[A].HoldingNPC].Type];
                            tempLocation.Y = NPC[Player[A].HoldingNPC].Location.Y + NPC[Player[A].HoldingNPC].Location.Height - NPCHeightGFX[NPC[Player[A].HoldingNPC].Type];
                            tempLocation.X = NPC[Player[A].HoldingNPC].Location.X + NPC[Player[A].HoldingNPC].Location.Width / 2.0 - NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] / 2.0;
                        }
                        else
                        {
                            tempLocation.Height = NPCHeight[NPC[Player[A].HoldingNPC].Type];
                            tempLocation.Width = NPCWidth[NPC[Player[A].HoldingNPC].Type];
                        }
                        tempLocation.X = tempLocation.X + NPCFrameOffsetX[NPC[Player[A].HoldingNPC].Type];
                        tempLocation.Y = tempLocation.Y + NPCFrameOffsetY[NPC[Player[A].HoldingNPC].Type];
                        Y2 = 0;
                        X2 = 0;
                        NPCWarpGFX(A, tempLocation, X2, Y2);
                        if(NPCHeightGFX[NPC[Player[A].HoldingNPC].Type] != 0 || NPCWidthGFX[NPC[Player[A].HoldingNPC].Type] != 0)
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeightGFX[NPC[Player[A].HoldingNPC].Type]);
                        else
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeight[NPC[Player[A].HoldingNPC].Type]);
                    }
                }
            }
        }


        if (LevelEditor)
        {
            fBlock = 1;
            lBlock = numBlock;
        }
        else
        {
            fBlock = FirstBlock[int(-vScreenX[Z] / 32) - 1];
            lBlock = LastBlock[int((-vScreenX[Z] + vScreen[Z].Width) / 32) + 1];
        }

        // fputs("time 4\n",log); fflush(log);
        graphics_times[4] = svcGetSystemTick();
        // printf("more blocks... \n");
        For(A, fBlock, lBlock)
        {
            if(!BlockIsSizable[Block[A].Type] && (!Block[A].Invis || (LevelEditor && BlockFlash <= 30)) && Block[A].Type != 0 && !BlockKills[Block[A].Type])
            {
                if(vScreenCollision(Z, Block[A].Location) && !Block[A].Hidden)
                {
                    // Don't show a visual difference of hit-resized block in a comparison to original state
                    double offX = Block[A].wasShrinkResized ? 0.05 : 0.0;
                    double offW = Block[A].wasShrinkResized ? 0.1 : 0.0;
                    frmMain.renderTexture(vScreenX[Z] + Block[A].Location.X - offX,
                                          vScreenY[Z] + Block[A].Location.Y + Block[A].ShakeY3,
                                          Block[A].Location.Width + offW,
                                          Block[A].Location.Height,
                                          GFXBlock[Block[A].Type],
                                          0,
                                          BlockFrame[Block[A].Type] * 32);
                }
            }
        }

        // printf("some effects... \n");
        for(A = 1; A <= numEffects; A++)
            if(Effect[A].Type == 112 || Effect[A].Type == 54 || Effect[A].Type == 55 ||
               Effect[A].Type == 59 || Effect[A].Type == 77 || Effect[A].Type == 81 ||
               Effect[A].Type == 82 || Effect[A].Type == 103 || Effect[A].Type == 104 ||
               Effect[A].Type == 114 || Effect[A].Type == 123 || Effect[A].Type == 124)
                if(vScreenCollision(Z, Effect[A].Location))
                    frmMain.renderTexture(vScreenX[Z] + Effect[A].Location.X, vScreenY[Z] + Effect[A].Location.Y, Effect[A].Location.Width, Effect[A].Location.Height, GFXEffect[Effect[A].Type], 0, Effect[A].Frame * EffectHeight[Effect[A].Type], Effect[A].Shadow);


        // printf("some NPCs... \n");
        for(A = 1; A <= numNPCs; A++) // Display NPCs that should be behind other npcs
        {
            if(NPC[A].Effect == 0)
            {
                if(NPC[A].HoldingPlayer == 0 && (NPC[A].standingOnPlayer > 0 || NPC[A].Type == 56 || NPC[A].Type == 22 || NPC[A].Type == 49 || NPC[A].Type == 91 || NPC[A].Type == 160 || NPC[A].Type == 282 || NPCIsACoin[NPC[A].Type]) && (NPC[A].Generator == false || LevelEditor == true))
                {
                    if((vScreenCollision(Z, NPC[A].Location) | vScreenCollision(Z, newLoc(NPC[A].Location.X - (NPCWidthGFX[NPC[A].Type] - NPC[A].Location.Width) / 2.0, NPC[A].Location.Y, static_cast<double>(NPCWidthGFX[NPC[A].Type]), static_cast<double>(NPCHeight[NPC[A].Type])))) != 0 && NPC[A].Hidden == false)
                    {
                        if(NPC[A].Active)
                        {
                            if(NPCWidthGFX[NPC[A].Type] == 0)
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                            else
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                        }
                    }
                }
            }
        }


        // printf("ice... \n");
        for(A = 1; A <= numNPCs; A++)
        {
            if(NPC[A].Type == 263 && NPC[A].Effect == 0 && NPC[A].HoldingPlayer == 0)
            {
                if((vScreenCollision(Z, NPC[A].Location) | vScreenCollision(Z, newLoc(NPC[A].Location.X - (NPCWidthGFX[NPC[A].Type] - NPC[A].Location.Width) / 2.0, NPC[A].Location.Y, static_cast<double>(NPCWidthGFX[NPC[A].Type]), static_cast<double>(NPCHeight[NPC[A].Type])))) != 0 && NPC[A].Hidden == false)
                    DrawFrozenNPC(Z, A);
            }
        }

        // fputs("time 5\n",log); fflush(log);
        graphics_times[5] = svcGetSystemTick();

        For(A, 1, numNPCs) // Display NPCs that should be in front of blocks
        {
            if(NPC[A].Effect == 0)
            {
                if(!(NPC[A].HoldingPlayer > 0 || NPCIsAVine[NPC[A].Type] || NPC[A].Type == 209 || NPC[A].Type == 282 || NPC[A].Type == 270 || NPC[A].Type == 160 || NPC[A].Type == 159 || NPC[A].Type == 8 || NPC[A].Type == 245 || NPC[A].Type == 93 || NPC[A].Type == 51 || NPC[A].Type == 52 || NPC[A].Type == 74 || NPC[A].Type == 256 || NPC[A].Type == 257 || NPC[A].Type == 56 || NPC[A].Type == 22 || NPC[A].Type == 49 || NPC[A].Type == 91) && !(NPC[A].Type == 45 && NPC[A].Special == 0) && NPC[A].standingOnPlayer == 0 && NPCForeground[NPC[A].Type] == false && (NPC[A].Generator == false || LevelEditor == true) && NPC[A].Type != 179 && NPC[A].Type != 263)
                {
                    if(!NPCIsACoin[NPC[A].Type])
                    {
                        if(vScreenCollision(Z, NPC[A].Location) && !NPC[A].Hidden)
                        {
                            if((NPC[A].Type != 0) && NPC[A].Active)
                            {
                                if(!NPCIsYoshi[NPC[A].Type])
                                {
                                    if(NPCWidthGFX[NPC[A].Type] == 0)
                                    {
                                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                                    }
                                    else
                                    {
                                        if(NPC[A].Type == 283 && NPC[A].Special > 0)
                                        {
                                            if(NPCWidthGFX[NPC[A].Special] == 0)
                                            {
                                                tempLocation.Width = NPCWidth[NPC[A].Special];
                                                tempLocation.Height = NPCHeight[NPC[A].Special];
                                            }
                                            else
                                            {
                                                tempLocation.Width = NPCWidthGFX[NPC[A].Special];
                                                tempLocation.Height = NPCHeightGFX[NPC[A].Special];
                                            }
                                            tempLocation.X = NPC[A].Location.X + NPC[A].Location.Width / 2.0 - tempLocation.Width / 2.0;
                                            tempLocation.Y = NPC[A].Location.Y + NPC[A].Location.Height / 2.0 - tempLocation.Height / 2.0;
                                            B = EditorNPCFrame(static_cast<int>(floor(static_cast<double>(NPC[A].Special))), NPC[A].Direction);
                                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[A].Special], 0, B * tempLocation.Height);
                                        }

                                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                                    }
                                }
                                else
                                {
                                    if(NPC[A].Type == 95)
                                        B = 1;
                                    else if(NPC[A].Type == 98)
                                        B = 2;
                                    else if(NPC[A].Type == 99)
                                        B = 3;
                                    else if(NPC[A].Type == 100)
                                        B = 4;
                                    else if(NPC[A].Type == 148)
                                        B = 5;
                                    else if(NPC[A].Type == 149)
                                        B = 6;
                                    else if(NPC[A].Type == 150)
                                        B = 7;
                                    else if(NPC[A].Type == 228)
                                        B = 8;
                                    int YoshiBX = 0;
                                    int YoshiBY = 0;
                                    int YoshiTX = 0;
                                    int YoshiTY = 0;
                                    int YoshiTFrame = 0;
                                    int YoshiBFrame = 0;
                                    YoshiBX = 0;
                                    YoshiBY = 0;
                                    YoshiTX = 20;
                                    YoshiTY = -32;
                                    YoshiBFrame = 6;
                                    YoshiTFrame = 0;
                                    if(NPC[A].Special == 0.0)
                                    {
                                        if(!FreezeNPCs)
                                            NPC[A].FrameCount = NPC[A].FrameCount + 1;
                                        if(NPC[A].FrameCount >= 70)
                                        {
                                            if(!FreezeNPCs)
                                                NPC[A].FrameCount = 0;
                                        }
                                        else if(NPC[A].FrameCount >= 50)
                                            YoshiTFrame = 3;
                                    }
                                    else
                                    {
                                        if(!FreezeNPCs)
                                            NPC[A].FrameCount = NPC[A].FrameCount + 1;
                                        if(NPC[A].FrameCount > 8)
                                        {
                                            YoshiBFrame = 0;
                                            NPC[A].FrameCount = 0;
                                        }
                                        else if(NPC[A].FrameCount > 6)
                                        {
                                            YoshiBFrame = 1;
                                            YoshiTX = YoshiTX - 1;
                                            YoshiTY = YoshiTY + 2;
                                            YoshiBY = YoshiBY + 1;
                                        }
                                        else if(NPC[A].FrameCount > 4)
                                        {
                                            YoshiBFrame = 2;
                                            YoshiTX = YoshiTX - 2;
                                            YoshiTY = YoshiTY + 4;
                                            YoshiBY = YoshiBY + 2;
                                        }
                                        else if(NPC[A].FrameCount > 2)
                                        {
                                            YoshiBFrame = 1;
                                            YoshiTX = YoshiTX - 1;
                                            YoshiTY = YoshiTY + 2;
                                            YoshiBY = YoshiBY + 1;
                                        }
                                        else
                                            YoshiBFrame = 0;
                                        if(!FreezeNPCs)
                                            NPC[A].Special2 = NPC[A].Special2 + 1;
                                        if(NPC[A].Special2 > 30)
                                        {
                                            YoshiTFrame = 0;
                                            if(!FreezeNPCs)
                                                NPC[A].Special2 = 0;
                                        }
                                        else if(NPC[A].Special2 > 10)
                                            YoshiTFrame = 2;

                                    }
                                    if(YoshiBFrame == 6)
                                    {
                                        YoshiBY = YoshiBY + 10;
                                        YoshiTY = YoshiTY + 10;
                                    }
                                    if(NPC[A].Direction == 1)
                                    {
                                        YoshiTFrame = YoshiTFrame + 5;
                                        YoshiBFrame = YoshiBFrame + 7;
                                    }
                                    else
                                    {
                                        YoshiBX = -YoshiBX;
                                        YoshiTX = -YoshiTX;
                                    }
                                    // YoshiBX = YoshiBX + 4
                                    // YoshiTX = YoshiTX + 4
                                    // Yoshi's Body
                                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(NPC[A].Location.X))) + YoshiBX, vScreenY[Z] + NPC[A].Location.Y + YoshiBY, 32, 32, GFXYoshiB[B], 0, 32 * YoshiBFrame, NPC[A].Shadow);

                                    // Yoshi's Head
                                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(NPC[A].Location.X))) + YoshiTX, vScreenY[Z] + NPC[A].Location.Y + YoshiTY, 32, 32, GFXYoshiT[B], 0, 32 * YoshiTFrame, NPC[A].Shadow);
                                }
                            }
                        }
                    }
                }
            }
        }

        // npc chat bubble
        for(A = 1; A <= numNPCs; A++)
        {
            if(NPC[A].Active && NPC[A].Chat)
            {
                B = NPCHeightGFX[NPC[A].Type] - NPC[A].Location.Height;
                if(B < 0)
                    B = 0;
                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPC[A].Location.Width / 2.0 - GFX.Chat.w / 2, vScreenY[Z] + NPC[A].Location.Y - 30 - B, GFX.Chat.w, GFX.Chat.h, GFX.Chat, 0, 0);
            }
        }


        For(A, 1, numPlayers) // The clown car
        {
            if(!Player[A].Dead && !Player[A].Immune2 && Player[A].TimeToLive == 0 &&
               !(Player[A].Effect == 3 || Player[A].Effect == 5) && Player[A].Mount == 2)
            {
                if(Player[A].Character == 1)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 36;
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + MarioFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99., Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXMario[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 2)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 38;
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + LuigiFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99., Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXLuigi[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 3)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99., Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXPeach[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame);
                }
                else if(Player[A].Character == 4)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99., Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXToad[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 5)
                {
                    Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + LinkFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + LinkFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99., Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXLink[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + (floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
            }
        }


        for(A = 1; A <= numNPCs; A++) // Put held NPCs on top
        {
            if(
                (
                  (
                    (NPC[A].HoldingPlayer > 0 && Player[NPC[A].HoldingPlayer].Effect != 3) ||
                    (NPC[A].Type == 50 && NPC[A].standingOnPlayer == 0) ||
                    (NPC[A].Type == 17 && NPC[A].CantHurt > 0)
                  ) || NPC[A].Effect == 5
                ) && NPC[A].Type != 91 && !Player[NPC[A].HoldingPlayer].Dead
            )
            {
                if(NPC[A].Type == 263)
                {
                    DrawFrozenNPC(Z, A);
                }
                else if(!NPCIsYoshi[NPC[A].Type] && NPC[A].Type > 0)
                {
                    if(NPCWidthGFX[NPC[A].Type] == 0)
                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                    else
                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                }
            }
        }


        // fputs("player\n",log); fflush(log);
        graphics_times[6] = svcGetSystemTick();
        for(int A = numPlayers; A >= 1; A--)// Players in front of blocks
        {
            DrawPlayer(A, Z);
        }

        // fputs("time 7\n",log); fflush(log);
        graphics_times[7] = svcGetSystemTick();
        if (LevelEditor)
        {
            For(A, 1, numBackground)
            {
                if(Foreground[Background[A].Type])
                {
                    if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                    {
                        frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X,
                                              vScreenY[Z] + Background[A].Location.Y,
                                              GFXBackgroundWidth[Background[A].Type],
                                              BackgroundHeight[Background[A].Type],
                                              GFXBackgroundBMP[Background[A].Type], 0,
                                              BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
                    }
                }
            }
        }
        else
        {
            for(A = LastBackground + 1; A <= numBackground; A++) // Foreground objects
            {
                if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                    frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X, vScreenY[Z] + Background[A].Location.Y, GFXBackgroundWidth[Background[A].Type], BackgroundHeight[Background[A].Type], GFXBackground[Background[A].Type], 0, BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
            }
        }

        for(A = 1; A <= numNPCs; A++) // foreground NPCs
        {
            if(NPC[A].Effect == 0)
            {
                if(NPCForeground[NPC[A].Type] && NPC[A].HoldingPlayer == 0 && (!NPC[A].Generator || LevelEditor))
                {
                    if(!NPCIsACoin[NPC[A].Type])
                    {
                        if(vScreenCollision(Z, NPC[A].Location) && !NPC[A].Hidden)
                        {
                            if(NPC[A].Active)
                            {
                                if(NPCWidthGFX[NPC[A].Type] == 0)
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                                else
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                            }
                        }
                    }
                }
            }
        }

        for(A = fBlock; A <= lBlock; A++) // Blocks in Front
        {
            if(BlockKills[Block[A].Type])
            {
                if(vScreenCollision(Z, Block[A].Location) && !Block[A].Hidden)
                {
                    // Don't show a visual difference of hit-resized block in a comparison to original state
                    double offX = Block[A].wasShrinkResized ? 0.05 : 0.0;
                    double offW = Block[A].wasShrinkResized ? 0.1 : 0.0;
                    frmMain.renderTexture(vScreenX[Z] + Block[A].Location.X - offX,
                                          vScreenY[Z] + Block[A].Location.Y + Block[A].ShakeY3,
                                          Block[A].Location.Width + offW,
                                          Block[A].Location.Height,
                                          GFXBlock[Block[A].Type],
                                          0,
                                          BlockFrame[Block[A].Type] * 32);
                }
            }
        }

        // fputs("time 8\n",log); fflush(log);
        graphics_times[8] = svcGetSystemTick();
        // effects on top
        For(A, 1, numEffects)
        {
            auto &e = Effect[A];
            if(e.Type != 112 && e.Type != 54 && e.Type != 55 && e.Type != 59 &&
               e.Type != 77 && e.Type != 81 && e.Type != 82 && e.Type != 103 &&
               e.Type != 104 && e.Type != 114 && e.Type != 123 && e.Type != 124)
            {
                if(vScreenCollision(Z, e.Location))
                {
                    frmMain.renderTexture(int(vScreenX[Z] + e.Location.X), int(vScreenY[Z] + e.Location.Y),
                                          int(e.Location.Width), int(e.Location.Height),
                                          GFXEffectBMP[e.Type], 0, e.Frame * EffectHeight[e.Type], e.Shadow);
                }
            }
        }

        if(LevelEditor)
        {
            for(B = 1; B <= numWater; B++)
            {
                if(!Water[B].Hidden && vScreenCollision(Z, Water[B].Location))
                {
                    if (Water[B].Quicksand)
                        frmMain.renderRect(vScreenX[Z] + Water[B].Location.X, vScreenY[Z] + Water[B].Location.Y, Water[B].Location.Width, Water[B].Location.Height,
                            1.f, 1.f, 0.f, 1.f, false);
                    else
                        frmMain.renderRect(vScreenX[Z] + Water[B].Location.X, vScreenY[Z] + Water[B].Location.Y, Water[B].Location.Width, Water[B].Location.Height,
                            0.f, 1.f, 1.f, 1.f, false);
                }
            }
        }

        // fputs("time 9\n",log); fflush(log);
        graphics_times[9] = svcGetSystemTick();
        frmMain.setLayer(3);
        // per-screen interface
        B = 0;
        C = 0;
        if(!GameMenu && !GameOutro && !LevelEditor)
        {
            For(A, 1, numPlayers)
            {
                if(Player[A].ShowWarp > 0)
                {
                    std::string tempString;
                    auto &w = Warp[Player[A].ShowWarp];
                    if(!w.noPrintStars && w.maxStars > 0 && Player[A].Mount != 2)
                    {
                        tempString = fmt::format_ne("{0}/{1}", w.curStars, w.maxStars);
                        frmMain.renderTexture(Player[A].Location.X + Player[A].Location.Width / 2.0 + vScreenX[Z] - tempString.length() * 9, Player[A].Location.Y + Player[A].Location.Height - 96 + vScreenY[Z] + 1, GFX.Interface[1].w, GFX.Interface[1].h, GFX.Interface[1], 0, 0);
                        frmMain.renderTexture(Player[A].Location.X + Player[A].Location.Width / 2.0 + vScreenX[Z] - tempString.length() * 9 - 20, Player[A].Location.Y + Player[A].Location.Height - 96 + vScreenY[Z], GFX.Interface[5].w, GFX.Interface[5].h, GFX.Interface[5], 0, 0);
                        SuperPrint(tempString, 3,
                                   float(Player[A].Location.X + Player[A].Location.Width / 2.0 + vScreenX[Z] - tempString.length() * 9 + 18),
                                   float(Player[A].Location.Y + Player[A].Location.Height - 96 + vScreenY[Z]));
                    }
                }
            }

            DrawInterface(Z, numScreens);

            For(A, 1, numNPCs) // Display NPCs that got dropped from the container
            {
                if(NPC[A].Effect == 2)
                {
                    if(std::fmod(NPC[A].Effect2, 3) != 0.0)
                    {
                        if(vScreenCollision(Z, NPC[A].Location))
                        {
                            if(NPC[A].Active)
                            {
                                if(NPCWidthGFX[NPC[A].Type] == 0)
                                {
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height);
                                }
                                else
                                {
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type] - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type]);
                                }
                            }
                        }
                    }
                }
            }
        }

        if(LevelEditor || (MagicHand && !GamePaused))
        {
            frmMain.setLayer(2);
            if(LevelEditor)
            {
                BlockFlash += 1;

                if(BlockFlash > 45)
                    BlockFlash = 0;

                if(BlockFlash <= 30)
                {
                    for (A = 1; A <= numBlock; A++)
                    {
                        if(Block[A].Special > 0 && !Block[A].Hidden)
                        {
                            if(vScreenCollision(Z, Block[A].Location))
                            {
                                if (Block[A].Special > 1000)
                                    C = Block[A].Special - 1000;
                                else
                                    C = 10;
                                if(NPCWidthGFX[C] == 0)
                                {
                                    tempLocation.X = Block[A].Location.X + Block[A].Location.Width / 2 - NPCWidth[C] / 2;
                                    tempLocation.Y = Block[A].Location.Y + Block[A].Location.Height / 2 - NPCHeight[C] / 2;
                                    tempLocation.Height = NPCHeight[C];
                                    tempLocation.Width = NPCWidth[C];
                                }
                                else
                                {
                                    tempLocation.X = Block[A].Location.X + Block[A].Location.Width / 2 - NPCWidthGFX[C] / 2;
                                    tempLocation.Y = Block[A].Location.Y + Block[A].Location.Height / 2 - NPCHeightGFX[C] / 2;
                                    tempLocation.Height = NPCHeightGFX[C];
                                    tempLocation.Width = NPCWidthGFX[C];
                                }
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X + NPCFrameOffsetX[C],
                                    vScreenY[Z] + tempLocation.Y + NPCFrameOffsetY[C],
                                    tempLocation.Width, tempLocation.Height,
                                    GFXNPC[C], 0, EditorNPCFrame(C, -1) * tempLocation.Height);
                            }
                        }
                    }

                    for (A = 1; A <= numNPCs; A++)
                    {
                        if(!NPC[A].Hidden && (NPC[A].Type == 91 || NPC[A].Type == 96)
                            && (NPC[A].Special > 0))
                        {
                            if (vScreenCollision(Z, NPC[A].Location))
                            {
                                C = NPC[A].Special;
                                if (NPCWidthGFX[C] == 0)
                                {
                                    tempLocation.Height = NPCHeight[C];
                                    tempLocation.Width = NPCWidth[C];
                                }
                                else
                                {
                                    tempLocation.Height = NPCHeightGFX[C];
                                    tempLocation.Width = NPCWidthGFX[C];
                                }
                                if(NPC[A].Type == 96)
                                    tempLocation.Y = NPC[A].Location.Y + NPC[A].Location.Height - tempLocation.Height;
                                else
                                    tempLocation.Y = NPC[A].Location.Y;
                                tempLocation.X = NPC[A].Location.X + NPC[A].Location.Width / 2 - tempLocation.Width / 2;
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X + NPCFrameOffsetX[C],
                                    vScreenY[Z] + tempLocation.Y + NPCFrameOffsetY[C],
                                    tempLocation.Width, tempLocation.Height,
                                    GFXNPC[C], 0, EditorNPCFrame(C, -1) * tempLocation.Height);
                            }
                        }
                    }
                }


                for(A = 1; A <= 2; A++)
                {
                    if (!(PlayerStart[A].Width > 0)) continue;
                    if (vScreenCollision(Z, PlayerStart[A]))
                    {
                        C = Physics.PlayerHeight[testPlayer[A].Character][2] - Physics.PlayerHeight[A][2];
                        switch (testPlayer[A].Character)
                        {
                        case 1:
                            frmMain.renderTexture(vScreenX[Z] + PlayerStart[A].X + MarioFrameX[201],
                                    vScreenY[Z] + PlayerStart[A].Y + MarioFrameY[201] - C,
                                    99, 99, GFXMario[2], 500, 0);
                            break;
                        case 2:
                            frmMain.renderTexture(vScreenX[Z] + PlayerStart[A].X + LuigiFrameX[201],
                                    vScreenY[Z] + PlayerStart[A].Y + LuigiFrameY[201] - C,
                                    99, 99, GFXLuigi[2], 500, 0);
                            break;
                        case 3:
                            frmMain.renderTexture(vScreenX[Z] + PlayerStart[A].X + PeachFrameX[201],
                                    vScreenY[Z] + PlayerStart[A].Y + PeachFrameY[201] - C,
                                    99, 99, GFXPeach[2], 500, 0);
                            break;
                        case 4:
                            frmMain.renderTexture(vScreenX[Z] + PlayerStart[A].X + ToadFrameX[201],
                                    vScreenY[Z] + PlayerStart[A].Y + ToadFrameY[201] - C,
                                    99, 99, GFXToad[2], 500, 0);
                            break;
                        case 5:
                            frmMain.renderTexture(vScreenX[Z] + PlayerStart[A].X + LinkFrameX[201],
                                    vScreenY[Z] + PlayerStart[A].Y + LinkFrameY[201] - C,
                                    99, 99, GFXLink[2], 500, 0);
                            break;
                        }
                    }
                }

                for(A = 1; A <= numWarps; A++)
                {
                    if(Warp[A].Direction > 0 && !Warp[A].Hidden)
                    {
                        bool complete = Warp[A].PlacedEnt && Warp[A].PlacedExit;
                        if(Warp[A].PlacedEnt)
                        {
                            if (complete)
                                frmMain.renderRect(vScreenX[Z] + Warp[A].Entrance.X, vScreenY[Z] + Warp[A].Entrance.Y, 32, 32,
                                    1.f, 0.f, 1.f, 1.f, false);
                            else
                                frmMain.renderRect(vScreenX[Z] + Warp[A].Entrance.X, vScreenY[Z] + Warp[A].Entrance.Y, 32, 32,
                                    1.f, 0.f, 0.f, 1.f, false);
                            SuperPrint(std::to_string(A), 1, vScreenX[Z] + Warp[A].Entrance.X + 2, vScreenY[Z] + Warp[A].Entrance.Y + 2);
                        }
                        if(Warp[A].PlacedExit)
                        {
                            if (complete)
                                frmMain.renderRect(vScreenX[Z] + Warp[A].Exit.X, vScreenY[Z] + Warp[A].Exit.Y, 32, 32,
                                    1.f, 0.f, 1.f, 1.f, false);
                            else
                                frmMain.renderRect(vScreenX[Z] + Warp[A].Exit.X, vScreenY[Z] + Warp[A].Exit.Y, 32, 32,
                                    1.f, 0.f, 0.f, 1.f, false);
                            SuperPrint(std::to_string(A), 1, vScreenX[Z] + Warp[A].Exit.X + Warp[A].Exit.Width - 16 - 2,
                                vScreenY[Z] + Warp[A].Exit.Y + Warp[A].Exit.Height - 14 - 2);
                        }
                    }
                }
            }

            frmMain.setLayer(0);
            if(LevelEditor)
            {
                if (BlockFlash > 30 || BlockFlash == 0)
                {
                    if (vScreenX[Z] + level[S].X > 0) {
                        frmMain.renderRect(0, 0,
                                           vScreenX[Z] + level[S].X, ScreenH, 0.f, 0.f, 0.f, 1.f, true);
                    }
                    if (ScreenW > level[S].Width + vScreenX[Z]) {
                        frmMain.renderRect(level[S].Width + vScreenX[Z], 0,
                                           ScreenW - (level[S].Width + vScreenX[Z]), ScreenH, 0.f, 0.f, 0.f, 1.f, true);
                    }
                    if (vScreenY[Z] + level[S].Y > 0) {
                        frmMain.renderRect(0, 0,
                                           ScreenW, vScreenY[Z] + level[S].Y, 0.f, 0.f, 0.f, 1.f, true);
                    }
                    if (ScreenH > level[S].Height + vScreenY[Z]) {
                        frmMain.renderRect(0, level[S].Height + vScreenY[Z],
                                           ScreenW, ScreenH - (level[S].Height + vScreenY[Z]), 0.f, 0.f, 0.f, 1.f, true);
                    }
                }
            }


            frmMain.setLayer(3);
            if(editorScreen.active && !MessageText.empty()) // In-Editor message box preview
            {
                SuperText = MessageText;
                const int BoxY_Start = ScreenH/2 - 150;
                const int TextBoxW = 500;
                // Draw background all at once:
                // how many lines are there?
                // A is the proposed start of the next line
                B = 0; // start of current line
                C = 0; // planned start of next line
                D = 1; // n lines
                for(A = 1; A <= int(SuperText.size()); A++)
                {
                    if(SuperText[size_t(A) - 1] == ' ' || A == int(SuperText.size()))
                    {
                        if(A-B < 28)
                            C = A;
                        else {
                            B = C;
                            D ++;
                        }
                    }
                }
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 ,
                                      BoxY_Start,
                                      TextBoxW, D*16 + 20, 0.f, 0.f, 0.f, 1.f);
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + 2,
                                      BoxY_Start + 2,
                                      TextBoxW - 4, D*16 + 20 - 4, 1.f, 1.f, 1.f, 1.f);
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + 4,
                                      BoxY_Start + 4,
                                      TextBoxW - 8, D*16 + 20 - 8, 8.f/255.f, 96.f/255.f, 168.f/255.f, 1.f);
                tempBool = false; // multi-line
                BoxY = BoxY_Start + 10;
                do
                {
                    // find last word break
                    B = 0;
                    for(A = 1; A <= int(SuperText.size()); A++)
                    {
                        if(SuperText[size_t(A) - 1] == ' ' || A == int(SuperText.size()))
                        {
                            if(A < 28)
                                B = A;
                            else
                                break;
                        }
                    }

                    if(B == 0)
                        B = A;

                    tempText = SuperText.substr(0, size_t(B));
                    SuperText = SuperText.substr(size_t(B), SuperText.length());
                    if(SuperText.length() == 0 && !tempBool)
                    {
                        SuperPrint(tempText,
                                   4,
                                   ScreenW/2 - TextBoxW / 2 + 12 + (27 * 9) - (tempText.length() * 9),
                                   BoxY);
                    }
                    else
                    {
                        SuperPrint(tempText, 4, ScreenW/2 - TextBoxW / 2 + 12, BoxY);
                    }
                    BoxY += 16;
                    tempBool = true;
                } while(!SuperText.empty());
            }

            // Display the cursor
            {
                auto &e = EditorCursor;
                int curX = int(double(e.X) - vScreen[Z].Left);
                int curY = int(double(e.Y) - vScreen[Z].Top);

                if (BlockFlash < 15)
                {
                    // don't draw the currently held object
                }
                else if(e.Mode == OptCursor_t::LVL_BLOCKS) // Blocks
                {
                    auto &b = e.Block;
                    if(BlockIsSizable[b.Type])
                    {
                        if(vScreenCollision(Z, b.Location))
                        {
                            for(B = 0; B <= (b.Location.Height / 32) - 1; B++)
                            {
                                for(C = 0; C <= (b.Location.Width / 32) - 1; C++)
                                {
                                    D = C;
                                    E = B;

                                    if(D != 0)
                                    {
                                        if(fEqual(D, (b.Location.Width / 32) - 1))
                                            D = 2;
                                        else
                                        {
                                            D = 1;
                                            d2 = 0.5;
                                        }
                                    }

                                    if(E != 0)
                                    {
                                        if(fEqual(E, (b.Location.Height / 32) - 1))
                                            E = 2;
                                        else
                                            E = 1;
                                    }

                                    frmMain.renderTexture(vScreenX[Z] + b.Location.X + C * 32,
                                                          vScreenY[Z] + b.Location.Y + B * 32,
                                                          32, 32, GFXBlock[b.Type], D * 32, E * 32);
//                                    if((D == 0 || D == 2) || (E == 0 || E == 2))
//                                    {
//                                        frmMain.renderTexture(vScreenX(Z) + .Location.X + C * 32, vScreenY(Z) + .Location.Y + B * 32, 32, 32, GFXBlock(.Type), D * 32, E * 32)
//                                    }
//                                    else
//                                        frmMain.renderTexture(vScreenX(Z) + .Location.X + C * 32, vScreenY(Z) + .Location.Y + B * 32, 32, 32, GFXBlock(.Type), D * 32, E * 32)

                                }
                            }
                        }
                    }
                    else
                    {
                        if(vScreenCollision(Z, b.Location))
                        {
                            frmMain.renderTexture(vScreenX[Z] + b.Location.X,
                                                  vScreenY[Z] + b.Location.Y + b.ShakeY3,
                                                  b.Location.Width,
                                                  b.Location.Height,
                                                  GFXBlock[b.Type], 0, BlockFrame[b.Type] * 32);
                        }
                    }
                }

                else if(e.Mode == OptCursor_t::LVL_SETTINGS) // Player start points
                {
                    // TODO: determine what is going on here
                    if(e.SubMode == 4 || e.SubMode == 5)
                    {
                        A = e.SubMode - 3;
                        C = Physics.PlayerHeight[testPlayer[A].Character][2] - Physics.PlayerHeight[A][2];
                        switch (testPlayer[A].Character)
                        {
                        case 1:
                            frmMain.renderTexture(vScreenX[Z] + e.Location.X + MarioFrameX[201],
                                    vScreenY[Z] + e.Location.Y + MarioFrameY[201] - C,
                                    99, 99, GFXMario[2], 500, 0);
                            break;
                        case 2:
                            frmMain.renderTexture(vScreenX[Z] + e.Location.X + LuigiFrameX[201],
                                    vScreenY[Z] + e.Location.Y + LuigiFrameY[201] - C,
                                    99, 99, GFXLuigi[2], 500, 0);
                            break;
                        case 3:
                            frmMain.renderTexture(vScreenX[Z] + e.Location.X + PeachFrameX[201],
                                    vScreenY[Z] + e.Location.Y + PeachFrameY[201] - C,
                                    99, 99, GFXPeach[2], 500, 0);
                            break;
                        case 4:
                            frmMain.renderTexture(vScreenX[Z] + e.Location.X + ToadFrameX[201],
                                    vScreenY[Z] + e.Location.Y + ToadFrameY[201] - C,
                                    99, 99, GFXToad[2], 500, 0);
                            break;
                        case 5:
                            frmMain.renderTexture(vScreenX[Z] + e.Location.X + LinkFrameX[201],
                                    vScreenY[Z] + e.Location.Y + LinkFrameY[201] - C,
                                    99, 99, GFXLink[2], 500, 0);
                            break;
                        }
                    }
                }

                else if(e.Mode == OptCursor_t::LVL_BGOS) // BGOs
                {
                    auto &b = e.Background;
                    if(vScreenCollision(Z, b.Location))
                    {
                        frmMain.renderTexture(vScreenX[Z] + b.Location.X,
                                              vScreenY[Z] + b.Location.Y,
                                              BackgroundWidth[b.Type],
                                              BackgroundHeight[b.Type],
                                              GFXBackground[b.Type], 0,
                                              BackgroundHeight[b.Type] * BackgroundFrame[b.Type]);
                    }
                }

                else if(e.Mode == OptCursor_t::LVL_NPCS) // NPCs
                {
                    e.NPC.Frame = NPC[0].Frame;
                    e.NPC.FrameCount = NPC[0].FrameCount;
                    NPC[0] = e.NPC;
                    NPCFrames(0);
                    e.NPC = NPC[0];

                    auto &n = e.NPC;
                    if(NPCWidthGFX[n.Type] == 0)
                    {
                        frmMain.renderTexture(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type],
                                              vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type],
                                              n.Location.Width,
                                              n.Location.Height,
                                              GFXNPC[n.Type], 0, n.Frame * n.Location.Height);
                    }
                    else
                    {
                        if(n.Type == 283 && n.Special > 0)
                        {
                            if(NPCWidthGFX[n.Special] == 0)
                            {
                                tempLocation.Width = NPCWidth[n.Special];
                                tempLocation.Height = NPCHeight[n.Special];
                            }
                            else
                            {
                                tempLocation.Width = NPCWidthGFX[n.Special];
                                tempLocation.Height = NPCHeightGFX[n.Special];
                            }
                            tempLocation.X = n.Location.X + n.Location.Width / 2 - tempLocation.Width / 2;
                            tempLocation.Y = n.Location.Y + n.Location.Height / 2 - tempLocation.Height / 2;
                            B = EditorNPCFrame(int(n.Special), n.Direction);

                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X + NPCFrameOffsetX[n.Type],
                                                  vScreenY[Z] + tempLocation.Y,
                                                  tempLocation.Width, tempLocation.Height,
                                                  GFXNPC[n.Special], 0, B * tempLocation.Height);
                        }

                        frmMain.renderTexture(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type] - NPCWidthGFX[n.Type] / 2 + n.Location.Width / 2,
                                              vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type] - NPCHeightGFX[n.Type] + n.Location.Height,
                                              NPCWidthGFX[n.Type], NPCHeightGFX[n.Type], GFXNPC[n.Type],
                                              0, n.Frame * NPCHeightGFX[n.Type]);
                    }
                }
                else if(EditorCursor.Mode == OptCursor_t::LVL_WATER) // Water
                {
                    if (EditorCursor.Water.Quicksand)
                        frmMain.renderRect(vScreenX[Z] + EditorCursor.Location.X, vScreenY[Z] + EditorCursor.Location.Y, EditorCursor.Location.Width, EditorCursor.Location.Height,
                            1.f, 1.f, 0.f, 1.f, false);
                    else
                        frmMain.renderRect(vScreenX[Z] + EditorCursor.Location.X, vScreenY[Z] + EditorCursor.Location.Y, EditorCursor.Location.Width, EditorCursor.Location.Height,
                            0.f, 1.f, 1.f, 1.f, false);
                }
                else if(EditorCursor.Mode == OptCursor_t::LVL_WARPS)
                {
                    frmMain.renderRect(vScreenX[Z] + EditorCursor.Location.X, vScreenY[Z] + EditorCursor.Location.Y, EditorCursor.Location.Width, EditorCursor.Location.Height,
                        1.f, 0.f, 0.f, 1.f, false);
                }

                if(EditorCursor.Mode == 0 || EditorCursor.Mode == 6) // Eraser
                {
                    frmMain.renderTexture(curX - 2, curY, GFX.ECursor[3]);
                }

                else if(EditorCursor.Mode == 13 || EditorCursor.Mode == 14) // Selector
                {
                    frmMain.renderTexture(curX, curY, GFX.ECursor[2]);
                }

                // Section Resize
                else if(EditorCursor.Mode == 2 && EditorCursor.SubMode < 4)
                {
                    frmMain.renderTexture(curX, curY, GFX.ECursor[1]);
                }

//                Else
                else
                {
//                    If .Mode = 5 Then
                    frmMain.renderTexture(curX, curY, GFX.ECursor[2]);
                    if(!e.Layer.empty() && strcasecmp(e.Layer.c_str(), "Default") != 0)
                        SuperPrint(EditorCursor.Layer, 3, curX + 28 , curY + 34);
                }

//            End With
            }
        }
        if(numScreens > 1) // for multiple screens
            frmMain.resetViewport();
    }
    // other interface
    if(vScreen[2].Visible)
    {
        if(int(vScreen[2].Width) == ScreenW)
            frmMain.renderRect(0, ScreenH/2-2, vScreen[2].Width, 4, 0, 0, 0);
        else
            frmMain.renderRect(ScreenW/2-2, 0, 4, vScreen[2].Height, 0, 0, 0);
    }
    // fputs("time 10\n",log); fflush(log);
    graphics_times[10] = svcGetSystemTick();
    if(!GameMenu && !GameOutro && !LevelEditor)
    {
        if(GamePaused)
        {
            if(MessageText.empty())
            {
                frmMain.renderRect(ScreenW/2 - 190, ScreenH/2 - 100, 380, 200, 0, 0, 0);
                if(TestLevel)
                {
                    SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 37);
                    SuperPrint("RESTART LEVEL", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 72);
                    SuperPrint("RESET CHECKPOINTS", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 107);
                    SuperPrint("QUIT TESTING", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 142);
                    frmMain.renderTexture(ScreenW/2 - 190 + 42, ScreenH/2 - 100 + 37 + (MenuCursor * 35), 16, 16, GFX.MCursor[0], 0, 0);
                }
                else if(!Cheater && (LevelSelect || (/*StartLevel == FileName*/IsEpisodeIntro && NoMap)))
                {
                    SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 57);
                    SuperPrint("SAVE & CONTINUE", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 92);
                    SuperPrint("SAVE & QUIT", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 127);
                    frmMain.renderTexture(ScreenW/2 - 190 + 42, ScreenH/2 - 100 + 57 + (MenuCursor * 35), 16, 16, GFX.MCursor[0], 0, 0);
                }
                else
                {
                    SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 75);
                    SuperPrint("QUIT", 3, ScreenW/2 - 190 + 62, ScreenH/2 - 100 + 110);
                    frmMain.renderTexture(ScreenW/2 - 190 + 42, ScreenH/2 - 100 + 75 + (MenuCursor * 35), 16, 16, GFX.MCursor[0], 0, 0);
                }
            }
            else
            {
                SuperText = MessageText;
                const int BoxY_Start = ScreenH/2 - 150;
                const int TextBoxW = 500;
                // Draw background all at once:
                // how many lines are there?
                // A is the proposed start of the next line
                B = 0; // start of current line
                C = 0; // planned start of next line
                D = 1; // n lines
                for(A = 1; A <= int(SuperText.size()); A++)
                {
                    if(SuperText[size_t(A) - 1] == ' ' || A == int(SuperText.size()))
                    {
                        if(A-B < 28)
                            C = A;
                        else {
                            B = C;
                            D ++;
                        }
                    }
                }
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 ,
                                      BoxY_Start,
                                      TextBoxW, D*16 + 20, 0.f, 0.f, 0.f, 1.f);
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + 2,
                                      BoxY_Start + 2,
                                      TextBoxW - 4, D*16 + 20 - 4, 1.f, 1.f, 1.f, 1.f);
                frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + 4,
                                      BoxY_Start + 4,
                                      TextBoxW - 8, D*16 + 20 - 8, 8.f/255.f, 96.f/255.f, 168.f/255.f, 1.f);
                tempBool = false; // multi-line
                BoxY = BoxY_Start + 10;
                do
                {
                    // find last word break
                    B = 0;
                    for(A = 1; A <= int(SuperText.size()); A++)
                    {
                        if(SuperText[size_t(A) - 1] == ' ' || A == int(SuperText.size()))
                        {
                            if(A < 28)
                                B = A;
                            else
                                break;
                        }
                    }

                    if(B == 0)
                        B = A;

                    tempText = SuperText.substr(0, size_t(B));
                    SuperText = SuperText.substr(size_t(B), SuperText.length());
                    if(SuperText.length() == 0 && !tempBool)
                    {
                        SuperPrint(tempText,
                                   4,
                                   ScreenW/2 - TextBoxW / 2 + 12 + (27 * 9) - (tempText.length() * 9),
                                   BoxY);
                    }
                    else
                    {
                        SuperPrint(tempText, 4, ScreenW/2 - TextBoxW / 2 + 12, BoxY);
                    }
                    BoxY += 16;
                    tempBool = true;
                } while(!SuperText.empty());
            }
        }
    }

    else if(GameMenu && !GameOutro)
    {
        if(MenuMode != 1 && MenuMode != 2 && MenuMode != 4 && MenuMode != 9)
            worldCurs = 0;

        int menuFix = -30; // for Input Settings

        frmMain.setLayer(2);
        frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[1].w / 2, 0, GFX.MenuGFX[1].w, GFX.MenuGFX[1].h, GFX.MenuGFX[1], 0, 0);
        frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[3].w / 2, ScreenH - 20,
            GFX.MenuGFX[3].w, GFX.MenuGFX[3].h, GFX.MenuGFX[3], 0, 0);

        frmMain.setLayer(3);
        frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[2].w / 2, 30,
                GFX.MenuGFX[2].w, GFX.MenuGFX[2].h, GFX.MenuGFX[2], 0, 0);

        int MenuX = ScreenW / 2 - 100;
        int MenuY = ScreenH - 200;
        if(MenuMode == 0)
        {
            SuperPrint("START GAME", 3, MenuX, MenuY);
            SuperPrint("2 PLAYER GAME", 3, MenuX, MenuY + 30);
            SuperPrint("BATTLE GAME", 3, MenuX, MenuY + 60);
            SuperPrint("EDITOR", 3, MenuX, MenuY + 90);
            SuperPrint("OPTIONS", 3, MenuX, MenuY + 120);
            SuperPrint("EXIT", 3, MenuX, MenuY + 150);
            frmMain.renderTexture(MenuX - 20, MenuY + (MenuCursor * 30), 16, 16, GFX.MCursor[0], 0, 0);
        }
        // Character select
        else if(MenuMode == 100 || MenuMode == 200 || MenuMode == 300 || MenuMode == 400 || MenuMode == 500)
        {
            A = 0;
            B = 0;
            C = 0;

            // TODO: Make a custom playable character names print here
            if(!blockCharacter[1])
                SuperPrint("MARIO GAME", 3, MenuX, MenuY);
            else
            {
                A = A - 30;
                if(MenuCursor + 1 >= 1)
                    B = B - 30;
                if(PlayerCharacter >= 1)
                    C = C - 30;
            }

            if(!blockCharacter[2])
                SuperPrint("LUIGI GAME", 3, MenuX, MenuY + 30 + A);
            else
            {
                A = A - 30;
                if(MenuCursor + 1 >= 2)
                    B = B - 30;
                if(PlayerCharacter >= 2)
                    C = C - 30;
            }

            if(!blockCharacter[3])
                SuperPrint("PEACH GAME", 3, MenuX, MenuY + 60 + A);
            else
            {
                A = A - 30;
                if(MenuCursor + 1 >= 3)
                    B = B - 30;
                if(PlayerCharacter >= 3)
                    C = C - 30;
            }

            if(!blockCharacter[4])
                SuperPrint("TOAD GAME", 3, MenuX, MenuY + 90 + A);
            else
            {
                A = A - 30;
                if(MenuCursor + 1 >= 4)
                    B = B - 30;
                if(PlayerCharacter >= 4)
                    C = C - 30;
            }

            if(!blockCharacter[5])
                SuperPrint("LINK GAME", 3, MenuX, MenuY + 120 + A);
            else
            {
                A = A - 30;
                if(MenuCursor + 1 >= 5)
                    B = B - 30;
                if(PlayerCharacter >= 5)
                    C = C - 30;
            }

            if(MenuMode == 300 || MenuMode == 500)
            {
                frmMain.renderTexture(MenuX - 20, B + MenuY + (MenuCursor * 30), GFX.MCursor[3]);
                frmMain.renderTexture(MenuX - 20, C + MenuY + ((PlayerCharacter - 1) * 30), GFX.MCursor[0]);
            }
            else
            {
                frmMain.renderTexture(MenuX - 20, B + MenuY + (MenuCursor * 30), GFX.MCursor[0]);
            }

        }
        else if(MenuMode == 1 || MenuMode == 2 || MenuMode == 4 || MenuMode == 9)
        {
            std::string tempStr = "";
            minShow = 1;
            maxShow = (MenuMode == 4) ? NumSelectBattle : ((MenuMode == 9) ? NumSelectWorldEditable : NumSelectWorld);
            if(maxShow > 6)
            {
                minShow = worldCurs;
                maxShow = minShow + 5;

                if(MenuCursor <= minShow - 1)
                    worldCurs = worldCurs - 1;
                if(MenuCursor >= maxShow - 1)
                    worldCurs = worldCurs + 1;

                if(worldCurs < 1)
                    worldCurs = 1;
                if (MenuMode == 9)
                {
                    if(worldCurs > NumSelectWorldEditable - 5)
                        worldCurs = NumSelectWorldEditable - 5;

                    if(maxShow >= NumSelectWorldEditable)
                    {
                        maxShow = NumSelectWorldEditable;
                        minShow = NumSelectWorldEditable - 5;
                    }
                }
                else if (MenuMode == 4)
                {
                    if(worldCurs > NumSelectBattle - 5)
                        worldCurs = NumSelectBattle - 5;

                    if(maxShow >= NumSelectBattle)
                    {
                        maxShow = NumSelectBattle;
                        minShow = NumSelectBattle - 5;
                    }
                }
                else
                {
                    if(worldCurs > NumSelectWorld - 5)
                        worldCurs = NumSelectWorld - 5;

                    if(maxShow >= NumSelectWorld)
                    {
                        maxShow = NumSelectWorld;
                        minShow = NumSelectWorld - 5;
                    }
                }

                minShow = worldCurs;
                maxShow = minShow + 5;
            }

            for(auto A = minShow; A <= maxShow; A++)
            {
                B = A - minShow + 1;
                tempStr = (MenuMode != 4) ? SelectWorld[A].WorldName : SelectBattle[A].WorldName;
                SuperPrint(tempStr, 3, MenuX, MenuY - 30 + (B * 30));
            }

            if(minShow > 1)
            {
                frmMain.renderTexture(ScreenW/2 - 8, MenuY - 20, GFX.MCursor[1]);
            }
            if(maxShow < ((MenuMode == 4) ? NumSelectBattle : ((MenuMode == 9) ? NumSelectWorldEditable : NumSelectWorld)))
            {
                frmMain.renderTexture(ScreenW/2 - 8, MenuY + 170, GFX.MCursor[2]);
            }

            B = MenuCursor - minShow + 1;
            if(B >= 0 && B < 6)
            {
                frmMain.renderTexture(MenuX - 20, MenuY + (B * 30), GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
            }
        }

        else if(MenuMode == 10 || MenuMode == 20) // Save Select
        {
            for(auto A = 1; A <= maxSaveSlots; A++)
            {
                if(SaveSlot[A] >= 0)
                {
                    SuperPrint(fmt::format_ne("SLOT {0} ... {1}", A, SaveSlot[A]), 3, MenuX, MenuY - 30 + (A * 30));
                    if(SaveStars[A] > 0)
                    {
                        frmMain.renderTexture(MenuX + 260, MenuY - 30 + (A * 30) + 1,
                                              GFX.Interface[5].w, GFX.Interface[5].h,
                                              GFX.Interface[5], 0, 0);
                        frmMain.renderTexture(MenuX + 260 + 24, MenuY - 30 + (A * 30) + 2,
                                              GFX.Interface[1].w, GFX.Interface[1].h,
                                              GFX.Interface[1], 0, 0);
                        SuperPrint(fmt::format_ne(" {0}", SaveStars[A]), 3, MenuX + 288, MenuY - 30 + (A * 30));
                    }
                }
                else
                {
                    SuperPrint(fmt::format_ne("SLOT {0} ... EMPTY", A), 3, MenuX, MenuY - 30 + (A * 30));
                }
            }
            frmMain.renderTexture(MenuX - 20, MenuY + (MenuCursor * 30), GFX.MCursor[0]);
        }

        // Options Menu
        else if(MenuMode == 3)
        {
            SuperPrint("PLAYER 1 CONTROLS", 3, MenuX, MenuY);
            SuperPrint("PLAYER 2 CONTROLS", 3, MenuX, MenuY+30);
            SuperPrint("EDITOR CONTROLS", 3, MenuX, MenuY+60);
            if (n3ds_clocked == -1)
            {
                if (debugMode)
                    SuperPrint("HIDE DEBUG SCREEN", 3, MenuX, MenuY+90);
                else
                    SuperPrint("SHOW DEBUG SCREEN", 3, MenuX, MenuY+90);
                SuperPrint("VIEW CREDITS", 3, MenuX, MenuY+120);
            }
            else
            {
                if (n3ds_clocked)
                    SuperPrint("USE O3DS CLOCK SPEED", 3, MenuX, MenuY+90);
                else
                    SuperPrint("USE N3DS CLOCK SPEED", 3, MenuX, MenuY+90);
                if (debugMode)
                    SuperPrint("HIDE DEBUG SCREEN", 3, MenuX, MenuY+120);
                else
                    SuperPrint("SHOW DEBUG SCREEN", 3, MenuX, MenuY+120);
                SuperPrint("VIEW CREDITS", 3, MenuX, MenuY+150);
            }
            frmMain.renderTexture(MenuX - 20, MenuY + (MenuCursor * 30),
                                  GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
        }
        // player controls
        else if(MenuMode == 31 || MenuMode == 32)
        {
            SuperPrint("3DS INPUT..PLAYER " + std::to_string(MenuMode - 30), 3, MenuX, MenuY - 120 + menuFix);

            SuperPrint(fmt::format_ne("UP.........{0}", getJoyKeyName(conJoystick[MenuMode - 30].Up)), 3, MenuX, MenuY - 90 + menuFix);
            SuperPrint(fmt::format_ne("DOWN.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Down)), 3, MenuX, MenuY - 60 + menuFix);
            SuperPrint(fmt::format_ne("LEFT.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Left)), 3, MenuX, MenuY - 30 + menuFix);
            SuperPrint(fmt::format_ne("RIGHT......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Right)), 3, MenuX, MenuY + menuFix);
            SuperPrint(fmt::format_ne("RUN........{0}", getJoyKeyName(conJoystick[MenuMode - 30].Run)), 3, MenuX, MenuY + 30 + menuFix);
            SuperPrint(fmt::format_ne("ALT RUN....{0}", getJoyKeyName(conJoystick[MenuMode - 30].AltRun)), 3, MenuX, MenuY + 60 + menuFix);
            SuperPrint(fmt::format_ne("JUMP.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Jump)), 3, MenuX, MenuY + 90 + menuFix);
            SuperPrint(fmt::format_ne("ALT JUMP...{0}", getJoyKeyName(conJoystick[MenuMode - 30].AltJump)), 3, MenuX, MenuY + 120 + menuFix);
            SuperPrint(fmt::format_ne("DROP ITEM..{0}", getJoyKeyName(conJoystick[MenuMode - 30].Drop)), 3, MenuX, MenuY + 150 + menuFix);
            SuperPrint(fmt::format_ne("PAUSE......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Start)), 3, MenuX, MenuY + 180 + menuFix);

            frmMain.renderTexture(MenuX - 20, MenuY - 120 + (MenuCursor * 30) + menuFix,
                                  GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
        }
        // editor controls
        else if(MenuMode == 33)
        {
            SuperPrint("3DS INPUT..EDITOR", 3, MenuX, MenuY - 120 + menuFix);

            SuperPrint(fmt::format_ne("UP.........{0}", getJoyKeyName(editorConJoystick.Up)), 3, MenuX, MenuY - 90 + menuFix);
            SuperPrint(fmt::format_ne("DOWN.......{0}", getJoyKeyName(editorConJoystick.Down)), 3, MenuX, MenuY - 60 + menuFix);
            SuperPrint(fmt::format_ne("LEFT.......{0}", getJoyKeyName(editorConJoystick.Left)), 3, MenuX, MenuY - 30 + menuFix);
            SuperPrint(fmt::format_ne("RIGHT......{0}", getJoyKeyName(editorConJoystick.Right)), 3, MenuX, MenuY + menuFix);
            SuperPrint(fmt::format_ne("PREV SECT..{0}", getJoyKeyName(editorConJoystick.PrevSection)), 3, MenuX, MenuY + 30 + menuFix);
            SuperPrint(fmt::format_ne("NEXT SECT..{0}", getJoyKeyName(editorConJoystick.NextSection)), 3, MenuX, MenuY + 60 + menuFix);
            SuperPrint(fmt::format_ne("SWITCH SCR.{0}", getJoyKeyName(editorConJoystick.SwitchScreens)), 3, MenuX, MenuY + 90 + menuFix);
            SuperPrint(fmt::format_ne("TEST PLAY..{0}", getJoyKeyName(editorConJoystick.TestPlay)), 3, MenuX, MenuY + 120 + menuFix);
            SuperPrint(fmt::format_ne("SELECT.....{0}", getJoyKeyName(editorConJoystick.Select)), 3, MenuX, MenuY + 150 + menuFix);
            SuperPrint(fmt::format_ne("ERASER.....{0}", getJoyKeyName(editorConJoystick.Erase)), 3, MenuX, MenuY + 180 + menuFix);

            frmMain.renderTexture(MenuX - 20, MenuY - 120 + (MenuCursor * 30) + menuFix,
                                  GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
        }
    }

    if(PrintFPS > 0) {
        SuperPrint(fmt::format_ne("{0}", int(PrintFPS)), 1, 8 + Max3DOffset, 8);
    }

    if(GameOutro)
        DoCredits();
    // fputs("time 11\n",log); fflush(log);
    graphics_times[11] = svcGetSystemTick();

    // if(!skipRepaint)
    //     frmMain.repaint();
    // fputs("time 12\n",log); fflush(log);
    graphics_times[12] = svcGetSystemTick();
    if (!LevelEditor)
        drawSecondScreen();
    graphics_times[13] = graphics_times[12]; // so we can report this frame's time to draw second screen next frame
    graphics_times[14] = svcGetSystemTick();

    if (!skipRepaint)
        frmMain.finalizeDraw();
    // fputs("time 15\n",log); fflush(log);
    graphics_times[15] = svcGetSystemTick();

    // Update Coin Frames
    CoinFrame2[1] = CoinFrame2[1] + 1;
    if(CoinFrame2[1] >= 6)
    {
        CoinFrame2[1] = 0;
        CoinFrame[1] = CoinFrame[1] + 1;
        if(CoinFrame[1] >= 4)
            CoinFrame[1] = 0;
    }
    CoinFrame2[2] = CoinFrame2[2] + 1;
    if(CoinFrame2[2] >= 6)
    {
        CoinFrame2[2] = 0;
        CoinFrame[2] = CoinFrame[2] + 1;
        if(CoinFrame[2] >= 7)
            CoinFrame[2] = 0;
    }
    CoinFrame2[3] = CoinFrame2[3] + 1;
    if(CoinFrame2[3] >= 7)
    {
        CoinFrame2[3] = 0;
        CoinFrame[3] = CoinFrame[3] + 1;
        if(CoinFrame[3] >= 4)
            CoinFrame[3] = 0;
    }
    // // fputs("done!\n",log); fclose(log);
}
