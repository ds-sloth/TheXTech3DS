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

#include <fmt_format_ne.h>
#include <Utils/maths.h>


// This draws the graphic to the screen when in a level/game menu/outro/level editor
void UpdateGraphics(bool skipRepaint)
{
//    On Error Resume Next
    int A = 0;
    std::string timeStr;
    int Z = 0;
    int numScreens = 0;

    if(!GameIsActive)
        return;

    // frame skip code
    cycleCount += 1;

    if(FrameSkip)
    {
        if(SDL_GetTicks() + floor(1000 * (1 - (cycleCount / 63.0))) > GoalTime) // Don't draw this frame
        {
            numScreens = 1;
            if(!LevelEditor)
            {
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
            }

            for(Z = 1; Z <= numScreens; Z++)
            {
                if(!LevelEditor)
                {
                    if(ScreenType == 2 || ScreenType == 3)
                        GetvScreenAverage();
                    else if(ScreenType == 5 && !vScreen[2].Visible)
                        GetvScreenAverage();
                    else if(ScreenType == 7)
                        GetvScreenCredits();
                    else
                    {
                        GetvScreen(Z);
                    }
                }

                for(A = 1; A <= numNPCs; A++)
                {
                    if(vScreenCollision(Z, NPC[A].Location) && !NPC[A].Hidden)
                    {
                        if(NPC[A].Reset[Z] || NPC[A].Active)
                        {
                            if(!NPC[A].Active)
                            {
                                NPC[A].JustActivated = Z;
//                                if(nPlay.Online == true)
//                                {
//                                    Netplay::sendData "2a" + std::to_string(A) + "|" + (nPlay.MySlot + 1) + LB;
//                                    NPC[A].JustActivated = nPlay.MySlot + 1;
//                                }
                            }
                            NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
//                            if(nPlay.Online == true && nPlay.NPCWaitCount >= 10 && nPlay.Mode == 0)
//                                timeStr = timeStr + "2b" + std::to_string(A) + LB;
                            NPC[A].Active = true;
                        }
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
            return;
        }
    }
    fpsCount++;

    std::string SuperText;
    std::string tempText;
    int BoxY = 0;
    bool tempBool = false;
    int B = 0;
//    int B2 = 0;
    int C = 0;
    int D = 0;
    int E = 0;
    double d2 = 0;
//    int e2 = 0;
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

//    If TakeScreen = True Then // Useless
//        If LevelEditor = True Or MagicHand = True Then
//            frmLevelWindow.vScreen(1).AutoRedraw = True
//        Else
//            frmMain.AutoRedraw = True
//        End If
//    End If

    // Background frames
    if(!FreezeNPCs)
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


//    If LevelEditor = False Then  'Sets up the screens if not in level editor
    { // NOT AN EDITOR
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
    }

    // printf("drawing... \n");
    frmMain.initDraw();

    if(SingleCoop == 2)
        numScreens = 2;

    For(Z, 1, numScreens)
    {
        if(SingleCoop == 2)
            Z = 2;

//        If LevelEditor = True Then
//            S = curSection
//        ElseIf nPlay.Online = True Then
//            S = Player(nPlay.MySlot + 1).Section
//        Else
        {
            S = Player[Z].Section;
//        End If
        }

//        If GameOutro = True Then ScreenType = 7
        if(GameOutro)
            ScreenType = 7;
//        If LevelEditor = False Then
        {
            if(ScreenType == 2 || ScreenType == 3)
                GetvScreenAverage();
            else if(ScreenType == 5 && !vScreen[2].Visible)
                GetvScreenAverage();
            else if(ScreenType == 7)
                GetvScreenCredits();
            else
                GetvScreen(Z);
            if(Background2[S] == 0)
            {
                if(numScreens > 1)
                    frmMain.renderRect(vScreen[Z].Left, vScreen[Z].Top,
                                       vScreen[Z].Width, vScreen[Z].Height, 0, 0, 0, 255, true);
                else
                    frmMain.clearBuffer();
            }
        }
//        Else
//            If Background2(S) = 0 Then BitBlt myBackBuffer, 0, 0, ScreenW, ScreenH, 0, 0, 0, vbWhiteness
//        End If

        if(qScreen)
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
        if(!LevelEditor)
        {
            if(NoTurnBack[Player[Z].Section])
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
        }

        if(numScreens > 1) // To separate drawing of screens
            frmMain.setViewport(vScreen[Z].Left, vScreen[Z].Top, vScreen[Z].Width, vScreen[Z].Height);

        // printf("background... \n");
        DrawBackground(S, Z);


//            If LevelEditor = True Then
//                If BlockFlash <= 30 Then
//                    With tempLocation 'Black out the level edges
//                        .X = level(curSection).X
//                        .Y = level(curSection).Y
//                        .Width = level(curSection).Width
//                        .Height = level(curSection).Height
//                        BitBlt myBackBuffer, 0, 0, vScreenX(Z) + level(curSection).X, vScreen(Z).Height, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        BitBlt myBackBuffer, 0, 0, vScreenX(Z) + level(curSection).Width, vScreenY(Z) + level(curSection).Y, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        If -vScreenX(Z) < level(curSection).Width Then
//                            BitBlt myBackBuffer, vScreenX(Z) + level(curSection).Width, 0, vScreen(Z).Width, vScreen(Z).Height, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        Else
//                            BitBlt myBackBuffer, 0, 0, vScreen(Z).Width, vScreen(Z).Height, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        End If
//                        If -vScreenY(Z) < level(curSection).Height Then
//                            BitBlt myBackBuffer, 0, vScreenY(Z) + level(curSection).Height, vScreen(Z).Width, vScreen(Z).Height, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        Else
//                            BitBlt myBackBuffer, 0, 0, vScreen(Z).Width, vScreen(Z).Height, GFX.Split(2).hdc, 0, 0, vbSrcCopy
//                        End If
//                    End With
//                End If
//            End If

        // This seems to be the player collision code, if so I have no idea why it is just in the graphics section TODO
        if(!GameMenu)
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
                        Player[A].Location.SpeedY = dRand() * 12 - 6;
                        Player[A].CanJump = true;
                    }
                }
            }
        }
        // printf("background tiles... \n");
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

        // printf("more backgrounds... \n");
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
                            {
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeight[NPC[A].Type], NPC[A].Shadow);
                            }
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
                        // more logic code... :( TODO
                        if(NPC[A].Reset[Z] || NPC[A].Active)
                        {
                            if(!NPC[A].Active)
                                NPC[A].JustActivated = Z;
                            NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
                            NPC[A].Active = true;
                        }
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
                            {
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeightGFX[NPC[Player[A].HoldingNPC].Type]);
                            }
                            else
                            {
                                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeight[NPC[Player[A].HoldingNPC].Type]);
                            }

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
                        {
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeightGFX[NPC[Player[A].HoldingNPC].Type]);
                        }
                        else
                        {
                            frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, tempLocation.Width, tempLocation.Height, GFXNPC[NPC[Player[A].HoldingNPC].Type], X2, Y2 + NPC[Player[A].HoldingNPC].Frame * NPCHeight[NPC[Player[A].HoldingNPC].Type]);
                        }

                    }
                }
            }
        }


        fBlock = FirstBlock[int(-vScreenX[Z] / 32) - 1];
        lBlock = LastBlock[int((-vScreenX[Z] + vScreen[Z].Width) / 32) + 1];


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
                    // If Not NPCIsACoin(.Type) Then
                    if((vScreenCollision(Z, NPC[A].Location) | vScreenCollision(Z, newLoc(NPC[A].Location.X - (NPCWidthGFX[NPC[A].Type] - NPC[A].Location.Width) / 2.0, NPC[A].Location.Y, static_cast<double>(NPCWidthGFX[NPC[A].Type]), static_cast<double>(NPCHeight[NPC[A].Type])))) != 0 && NPC[A].Hidden == false)
                    {
                        if(NPC[A].Active)
                        {
                            if(NPCWidthGFX[NPC[A].Type] == 0)
                            {
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                            }
                            else
                            {
                                frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                            }
                        }
                        if(NPC[A].Reset[Z] || NPC[A].Active)
                        {
                            if(!NPC[A].Active) // more logic, ahh TODO
                                NPC[A].JustActivated = Z;
                            NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
                            NPC[A].Active = true;
                         }
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


        // printf("ice... \n");
        for(A = 1; A <= numNPCs; A++)
        {
            if(NPC[A].Type == 263 && NPC[A].Effect == 0 && NPC[A].HoldingPlayer == 0)
            {
                if((vScreenCollision(Z, NPC[A].Location) | vScreenCollision(Z, newLoc(NPC[A].Location.X - (NPCWidthGFX[NPC[A].Type] - NPC[A].Location.Width) / 2.0, NPC[A].Location.Y, static_cast<double>(NPCWidthGFX[NPC[A].Type]), static_cast<double>(NPCHeight[NPC[A].Type])))) != 0 && NPC[A].Hidden == false)
                {
                    DrawFrozenNPC(Z, A);
                    if(NPC[A].Reset[Z] || NPC[A].Active)
                    {
                        if(!NPC[A].Active)
                        {
                            NPC[A].JustActivated = Z;
                        }
                        NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
                        NPC[A].Active = true;
                     }
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


//        For A = 1 To numNPCs 'Display NPCs that should be in front of blocks
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
                            if(NPC[A].Type == 0)
                            {
                                NPC[A].Killed = 9;
                                KillNPC(A, 9);
                            }
                            else if(NPC[A].Active)
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
                                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(NPC[A].Location.X))) + YoshiBX, vScreenY[Z] + NPC[A].Location.Y + YoshiBY, 32, 32, GFXYoshiB[B], 0, 32 * YoshiBFrame, NPC[A].Shadow);

                                    // Yoshi's Head
                                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(NPC[A].Location.X))) + YoshiTX, vScreenY[Z] + NPC[A].Location.Y + YoshiTY, 32, 32, GFXYoshiT[B], 0, 32 * YoshiTFrame, NPC[A].Shadow);
                                }
                            }
                            if((NPC[A].Reset[1] && NPC[A].Reset[2]) || NPC[A].Active || NPC[A].Type == 57)
                            {
                                if(!NPC[A].Active)
                                {
                                    NPC[A].JustActivated = Z;
//                                    if(nPlay.Online == true)
//                                    {
//                                        Netplay::sendData "2a" + std::to_string(A) + "|" + (nPlay.MySlot + 1) + LB;
//                                        NPC[A].JustActivated = nPlay.MySlot + 1;
//                                    }
                                }
                                NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
                                if(NPCIsYoshi[NPC[A].Type] || NPCIsBoot[NPC[A].Type] || NPC[A].Type == 9 || NPC[A].Type == 14 || NPC[A].Type == 22 || NPC[A].Type == 90 || NPC[A].Type == 153 || NPC[A].Type == 169 || NPC[A].Type == 170 || NPC[A].Type == 182 || NPC[A].Type == 183 || NPC[A].Type == 184 || NPC[A].Type == 185 || NPC[A].Type == 186 || NPC[A].Type == 187 || NPC[A].Type == 188 || NPC[A].Type == 195 || NPC[A].Type == 104)
                                    NPC[A].TimeLeft = Physics.NPCTimeOffScreen * 20;

//                                if(nPlay.Online == true && nPlay.NPCWaitCount >= 10 && nPlay.Mode == 0)
//                                    timeStr = timeStr + "2b" + std::to_string(A) + LB;
                                NPC[A].Active = true;
                            }
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
//        Next A
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
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + MarioFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + MarioFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99, Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXMario[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 2)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 38;
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + LuigiFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99, Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXLuigi[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 3)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99, Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXPeach[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame);
                }
                else if(Player[A].Character == 4)
                {
                    if(Player[A].State == 1)
                        Y = 24;
                    else
                        Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99, Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXToad[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
                }
                else if(Player[A].Character == 5)
                {
                    Y = 30;
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + LinkFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] - Physics.PlayerWidth[Player[A].Character][Player[A].State] / 2 + 64, vScreenY[Z] + Player[A].Location.Y + LinkFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY - Y, 99, Player[A].Location.Height - 20 - Player[A].MountOffsetY, GFXLink[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                    frmMain.renderTexture(vScreenX[Z] + static_cast<int>(floor(static_cast<double>(Player[A].Location.X))) + Player[A].Location.Width / 2.0 - 64, vScreenY[Z] + Player[A].Location.Y + Player[A].Location.Height - 128, 128, 128, GFX.Mount[Player[A].Mount], 0, 128 * Player[A].MountFrame, ShadowMode);
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
                    {
                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                    }
                    else
                    {
                        frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                    }
                }
            }
        }



//'normal player draw code
//        For A = numPlayers To 1 Step -1 'Players in front of blocks
        for(int A = numPlayers; A >= 1; A--)// Players in front of blocks
        {
//            DrawPlayer A, Z
            DrawPlayer(A, Z);
//        Next A
        }
//'normal player end




//        If LevelEditor = True Or MagicHand = True Then
//            For A = 1 To numBackground 'Foreground objects
//                With Background(A)
//                    If Foreground(.Type) = True Then
//                        If vScreenCollision(Z, .Location) And .Hidden = False Then
//                            If BackgroundHasNoMask(.Type) Then
//                                'BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, GFXBackgroundWidth(.Type), GFXBackgroundHeight(.Type), GFXBackground(.Type), 0, 0, vbSrcCopy
//                                BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, GFXBackgroundWidth(.Type), BackgroundHeight(.Type), GFXBackground(.Type), 0, BackgroundHeight(.Type) * BackgroundFrame(.Type), vbSrcCopy
//                            Else
//                                BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, BackgroundWidth(.Type), BackgroundHeight(.Type), GFXBackgroundMask(.Type), 0, BackgroundHeight(.Type) * BackgroundFrame(.Type), vbSrcAnd
//                                BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, BackgroundWidth(.Type), BackgroundHeight(.Type), GFXBackground(.Type), 0, BackgroundHeight(.Type) * BackgroundFrame(.Type), vbSrcPaint
//                            End If
//                        End If
//                    End If
//                End With
//            Next A
//        Else

        { // NOT AN EDITOR
            for(A = LastBackground + 1; A <= numBackground; A++) // Foreground objects
            {
                if(vScreenCollision(Z, Background[A].Location) && !Background[A].Hidden)
                {
                    frmMain.renderTexture(vScreenX[Z] + Background[A].Location.X, vScreenY[Z] + Background[A].Location.Y, GFXBackgroundWidth[Background[A].Type], BackgroundHeight[Background[A].Type], GFXBackground[Background[A].Type], 0, BackgroundHeight[Background[A].Type] * BackgroundFrame[Background[A].Type]);
                }
            }
//        End If
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
                                {
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + NPCFrameOffsetX[NPC[A].Type], vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type], NPC[A].Location.Width, NPC[A].Location.Height, GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPC[A].Location.Height, NPC[A].Shadow);
                                }
                                else
                                {
                                    frmMain.renderTexture(vScreenX[Z] + NPC[A].Location.X + (NPCFrameOffsetX[NPC[A].Type] * -NPC[A].Direction) - NPCWidthGFX[NPC[A].Type] / 2.0 + NPC[A].Location.Width / 2.0, vScreenY[Z] + NPC[A].Location.Y + NPCFrameOffsetY[NPC[A].Type] - NPCHeightGFX[NPC[A].Type] + NPC[A].Location.Height, NPCWidthGFX[NPC[A].Type], NPCHeightGFX[NPC[A].Type], GFXNPC[NPC[A].Type], 0, NPC[A].Frame * NPCHeightGFX[NPC[A].Type], NPC[A].Shadow);
                                }
                            }
                            if((NPC[A].Reset[1] && NPC[A].Reset[2]) || NPC[A].Active)
                            {
                                if(!NPC[A].Active)
                                {
                                    NPC[A].JustActivated = Z;
//                                    if(nPlay.Online == true)
//                                    {
//                                        Netplay::sendData "2a" + std::to_string(A) + "|" + (nPlay.MySlot + 1) + LB;
//                                        NPC[A].JustActivated = nPlay.MySlot + 1;
//                                    }
                                }
                                NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
//                                if(nPlay.Online == true && nPlay.NPCWaitCount >= 10 && nPlay.Mode == 0)
//                                    timeStr = timeStr + "2b" + std::to_string(A) + LB;
                                NPC[A].Active = true;
                            }
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

// effects on top
        For(A, 1, numEffects)
        {
//            With Effect(A)
            auto &e = Effect[A];
//                If .Type <> 112 And .Type <> 54 And .Type <> 55 And .Type <> 59 And .Type <> 77 And .Type <> 81 And .Type <> 82 And .Type <> 103 And .Type <> 104 And .Type <> 114 And .Type <> 123 And .Type <> 124 Then
            if(e.Type != 112 && e.Type != 54 && e.Type != 55 && e.Type != 59 &&
               e.Type != 77 && e.Type != 81 && e.Type != 82 && e.Type != 103 &&
               e.Type != 104 && e.Type != 114 && e.Type != 123 && e.Type != 124)
            {
//                    If vScreenCollision(Z, .Location) Then
                if(vScreenCollision(Z, e.Location))
                {
//                        BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, .Location.Width, .Location.Height, GFXEffectMask(.Type), 0, .Frame * EffectHeight(.Type), vbSrcAnd
//                        If .Shadow = False Then BitBlt myBackBuffer, vScreenX(Z) + .Location.X, vScreenY(Z) + .Location.Y, .Location.Width, .Location.Height, GFXEffect(.Type), 0, .Frame * EffectHeight(.Type), vbSrcPaint
                    frmMain.renderTexture(int(vScreenX[Z] + e.Location.X), int(vScreenY[Z] + e.Location.Y),
                                          int(e.Location.Width), int(e.Location.Height),
                                          GFXEffectBMP[e.Type], 0, e.Frame * EffectHeight[e.Type], e.Shadow);
//                    End If
                }
//                End If
            }
//            End With
//        Next A
        }

//        'water
//        If LevelEditor = True Then
//            For B = 1 To numWater
//                With Water(B)
//                    If .Hidden = False Then
//                        For A = 1 To .Location.Height / 32
//                            BitBlt myBackBuffer, .Location.X + vScreenX(Z), .Location.Y + vScreenY(Z) + 32 * A - 32, 2, 32, GFX.Water.hdc, 0, 0, vbSrcCopy
//                            BitBlt myBackBuffer, .Location.X + vScreenX(Z) + .Location.Width - 2, .Location.Y + vScreenY(Z) + 32 * A - 32, 2, 32, GFX.Water.hdc, 0, 0, vbSrcCopy
//                        Next A
//                        For A = 1 To .Location.Width / 32
//                            BitBlt myBackBuffer, .Location.X + vScreenX(Z) + 32 * A - 32, .Location.Y + vScreenY(Z), 32, 2, GFX.Water.hdc, 0, 0, vbSrcCopy
//                            BitBlt myBackBuffer, .Location.X + vScreenX(Z) + 32 * A - 32, .Location.Y + vScreenY(Z) + .Location.Height - 2, 32, 2, GFX.Water.hdc, 0, 0, vbSrcCopy
//                        Next A
//                    End If
//                End With
//            Next B
//        End If

        // clip any off-level draws
        if (vScreen[Z].Width + level[S].X > level[S].Width) {
            B = (vScreen[Z].Width + level[S].X - level[S].Width) / 2;
            frmMain.renderRect(vScreen[Z].Left, vScreen[Z].Top,
                               B, vScreen[Z].Height, 0, 0, 0, 255, true);
            frmMain.renderRect(vScreen[Z].Left+vScreen[Z].Width-B, vScreen[Z].Top,
                               B, vScreen[Z].Height, 0, 0, 0, 255, true);
        }
        if (vScreen[Z].Height + level[S].Y > level[S].Height) {
            B = (vScreen[Z].Height + level[S].Y - level[S].Height) / 2;
            frmMain.renderRect(vScreen[Z].Left, vScreen[Z].Top,
                               vScreen[Z].Width, B, 0, 0, 0, 255, true);
            frmMain.renderRect(vScreen[Z].Left, vScreen[Z].Top+vScreen[Z].Height-B,
                               vScreen[Z].Width, B, 0, 0, 0, 255, true);
        }

        if(!LevelEditor) // Graphics for the main game.
        {
        // NPC Generators
            for(A = 1; A <= numNPCs; A++)
            {
                if(NPC[A].Generator)
                {
                    if(vScreenCollision(Z, NPC[A].Location) && !NPC[A].Hidden)
                        NPC[A].GeneratorActive = true;
                }
            }
            if(vScreen[2].Visible)
            {
                if(int(vScreen[Z].Width) == ScreenW)
                {
                    if(vScreen[Z].Top != 0.0)
                    {
                        frmMain.renderRect(0, 0, vScreen[Z].Width, 1, 0, 0, 0);
                    }
                    else
                    {
                        frmMain.renderRect(0, vScreen[Z].Height - 1, vScreen[Z].Width, 1, 0, 0, 0);
                    }
                }
                else
                {
                    if(vScreen[Z].Left != 0.0)
                    {
                        frmMain.renderRect(0, 0, 1, vScreen[Z].Height, 0, 0, 0);
                    }
                    else
                    {
                        frmMain.renderRect(vScreen[Z].Width - 1, 0, 1, vScreen[Z].Height, 0, 0, 0);
                    }
                }
            }

        // player names
        /* Dropped */



    //    'Interface
    //            B = 0
            B = 0;
    //            C = 0
            C = 0;
    //            If GameMenu = False And GameOutro = False Then
            if(!GameMenu && !GameOutro)
            {
    //                For A = 1 To numPlayers
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

    //                DrawInterface Z, numScreens
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
                                if(NPC[A].Reset[Z] || NPC[A].Active)
                                {
                                    NPC[A].TimeLeft = Physics.NPCTimeOffScreen;
//                                    if(nPlay.Online == true && nPlay.NPCWaitCount >= 10 && nPlay.Mode == 0)
//                                        timeStr = timeStr + "2b" + std::to_string(A) + LB;
                                    NPC[A].Active = true;
                                }
                                NPC[A].Reset[1] = false;
                                NPC[A].Reset[2] = false;
                            }
                            else
                                NPC[A].Reset[Z] = true;
                        }
                    }
                }


    //                If GamePaused = True Then
                if(GamePaused)
                {
                    if(MessageText.empty())
                    {
                        X = 0;
                        Y = 0;
                        if((DScreenType == 1 && Z == 2) || (DScreenType == 2 && Z == 1))
                            X = -ScreenW/2;
                        else if((DScreenType == 6 && Z == 2) || (DScreenType == 4 && Z == 2) || (DScreenType == 3 && Z == 1))
                            Y = -ScreenH/2;
                        frmMain.renderRect(ScreenW/2 - 190 + X, ScreenH/2 - 100 + Y, 380, 200, 0, 0, 0);
                        if(TestLevel)
                        {
                            SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 37 + Y);
                            SuperPrint("RESTART LEVEL", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 72 + Y);
                            SuperPrint("RESET CHECKPOINTS", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 107 + Y);
                            SuperPrint("QUIT TESTING", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 142 + Y);
                            frmMain.renderTexture(ScreenW/2 - 190 + 42 + X, ScreenH/2 - 100 + 37 + (MenuCursor * 35) + Y, 16, 16, GFX.MCursor[0], 0, 0);
                        }
                        else if(!Cheater && (LevelSelect || (/*StartLevel == FileName*/IsEpisodeIntro && NoMap)))
                        {
                            SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 57 + Y);
                            SuperPrint("SAVE & CONTINUE", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 92 + Y);
                            SuperPrint("SAVE & QUIT", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 127 + Y);
                            frmMain.renderTexture(ScreenW/2 - 190 + 42 + X, ScreenH/2 - 100 + 57 + (MenuCursor * 35) + Y, 16, 16, GFX.MCursor[0], 0, 0);
                        }
                        else
                        {
                            SuperPrint("CONTINUE", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 75 + Y);
                            SuperPrint("QUIT", 3, ScreenW/2 - 190 + 62 + X, ScreenH/2 - 100 + 110 + Y);
                            frmMain.renderTexture(ScreenW/2 - 190 + 42 + X, ScreenH/2 - 100 + 75 + (MenuCursor * 35) + Y, 16, 16, GFX.MCursor[0], 0, 0);
                        }
                    }
                    else
                    {
                        X = 0;
                        Y = 0;
                        if((DScreenType == 1 && Z == 2) || (DScreenType == 2 && Z == 1))
                            X = -ScreenW/2;
                        else if((DScreenType == 6 && Z == 2) || (DScreenType == 4 && Z == 2) || (DScreenType == 3 && Z == 1))
                            Y = -ScreenH/2;

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
                        frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + X,
                                              BoxY_Start + Y + Y, // not certain about this...
                                              TextBoxW, D*16 + 20, 0, 0, 0, 255);
                        frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + X + 2,
                                              BoxY_Start + Y + Y + 2, // not certain about this...
                                              TextBoxW - 4, D*16 + 20 - 4, 255, 255, 255, 255);
                        frmMain.renderRect(ScreenW/2 - TextBoxW / 2 + X + 4,
                                              BoxY_Start + Y + Y + 4, // not certain about this...
                                              TextBoxW - 8, D*16 + 20 - 8, 8, 96, 168, 255);
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
                                           ScreenW/2 - TextBoxW / 2 + X + 12 + (27 * 9) - (tempText.length() * 9),
                                           Y + BoxY);
                            }
                            else
                            {
                                SuperPrint(tempText, 4, ScreenW/2 - TextBoxW / 2 + 12 + X, Y + BoxY);
                            }
                            BoxY += 16;
                            tempBool = true;
                        } while(!SuperText.empty());
                    }
                }
    //            ElseIf GameOutro = False Then
            }

            else if(!GameOutro)
            {
                if(MenuMode != 1 && MenuMode != 2 && MenuMode != 4)
                    worldCurs = 0;

                int menuFix = -44; // for Input Settings

                frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[1].w / 2, 0, GFX.MenuGFX[1].w, GFX.MenuGFX[1].h, GFX.MenuGFX[1], 0, 0);
                frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[2].w / 2, 50,
                        GFX.MenuGFX[2].w, GFX.MenuGFX[2].h, GFX.MenuGFX[2], 0, 0);

                // frmMain.renderTexture(ScreenW / 2 - GFX.MenuGFX[3].w / 2, ScreenH - 34,
                //         GFX.MenuGFX[3].w, GFX.MenuGFX[3].h, GFX.MenuGFX[3], 0, 0);

                int MenuX = ScreenW / 2 - 100;
                int MenuY = ScreenH - 175;
                if(MenuMode == 0)
                {
                    SuperPrint("START GAME", 3, MenuX, MenuY);
                    SuperPrint("OPTIONS", 3, MenuX, MenuY + 30);
                    SuperPrint("EXIT", 3, MenuX, MenuY + 60);
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
                else if(MenuMode == 1 || MenuMode == 2 || MenuMode == 4)
                {
                    std::string tempStr = "";
                    minShow = 1;
                    maxShow = NumSelectWorld;
                    if(NumSelectWorld > 5)
                    {
                        minShow = worldCurs;
                        maxShow = minShow + 4;

                        if(MenuCursor <= minShow - 1)
                            worldCurs = worldCurs - 1;
                        if(MenuCursor >= maxShow - 1)
                            worldCurs = worldCurs + 1;

                        if(worldCurs < 1)
                            worldCurs = 1;
                        if(worldCurs > NumSelectWorld - 4)
                            worldCurs = NumSelectWorld - 4;

                        if(maxShow >= NumSelectWorld)
                        {
                            maxShow = NumSelectWorld;
                            minShow = NumSelectWorld - 4;
                        }

                        minShow = worldCurs;
                        maxShow = minShow + 4;
                    }

                    for(auto A = minShow; A <= maxShow; A++)
                    {
                        B = A - minShow + 1;
                        tempStr = SelectWorld[A].WorldName;
                        SuperPrint(tempStr, 3, MenuX, MenuY - 30 + (B * 30));
                    }

                    if(minShow > 1)
                    {
                        frmMain.renderTexture(ScreenW/2 - 8, MenuY - 20, GFX.MCursor[1]);
                    }
                    if(maxShow < NumSelectWorld)
                    {
                        frmMain.renderTexture(ScreenW/2 - 8, MenuY + 140, GFX.MCursor[2]);
                    }

                    B = MenuCursor - minShow + 1;
                    if(B >= 0 && B < 5)
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
    //                    SuperPrint "PLAYER 1 CONTROLS", 3, MenuX, MenuY
                    SuperPrint("PLAYER 1 CONTROLS", 3, MenuX, MenuY);
    //                    SuperPrint "PLAYER 2 CONTROLS", 3, MenuX, MenuY+30
                    SuperPrint("PLAYER 2 CONTROLS", 3, MenuX, MenuY+30);
    //                    If resChanged = True Then
                    if(resChanged)
    //                        SuperPrint "WINDOWED MODE", 3, MenuX, MenuY+60
                        SuperPrint("WINDOWED MODE", 3, MenuX, MenuY+60);
    //                    Else
                    else
    //                        SuperPrint "FULLSCREEN MODE", 3, MenuX, MenuY+60
                        SuperPrint("FULLSCREEN MODE", 3, MenuX, MenuY+60);
    //                    End If
    //                    SuperPrint "VIEW CREDITS", 3, MenuX, MenuY+90
                    SuperPrint("VIEW CREDITS", 3, MenuX, MenuY+90);
    //                    BitBlt myBackBuffer, MenuX - 20, 350 + (MenuCursor * 30), 16, 16, GFX.MCursorMask(0).hdc, 0, 0, vbSrcAnd
    //                    BitBlt myBackBuffer, MenuX - 20, 350 + (MenuCursor * 30), 16, 16, GFX.MCursor(0).hdc, 0, 0, vbSrcPaint
                    frmMain.renderTexture(MenuX - 20, MenuY + (MenuCursor * 30),
                                          GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
    //                ElseIf MenuMode = 31 Or MenuMode = 32 Then
                }
                else if(MenuMode == 31 || MenuMode == 32)
                {
    //                    If useJoystick(MenuMode - 30) = 0 Then
                    // if(useJoystick[MenuMode - 30] == 0)
                    // {
    //                        SuperPrint "INPUT......KEYBOARD", 3, MenuX, MenuY - 90 + menuFix
                        // SuperPrint("INPUT......KEYBOARD", 3, MenuX, MenuY - 90 + menuFix);
                        // SuperPrint(fmt::format_ne("UP.........{0}", getKeyName(conKeyboard[MenuMode - 30].Up)), 3, MenuX, MenuY - 60 + menuFix);
                        // SuperPrint(fmt::format_ne("DOWN.......{0}", getKeyName(conKeyboard[MenuMode - 30].Down)), 3, MenuX, MenuY - 30 + menuFix);
                        // SuperPrint(fmt::format_ne("LEFT.......{0}", getKeyName(conKeyboard[MenuMode - 30].Left)), 3, MenuX, MenuY + menuFix);
                        // SuperPrint(fmt::format_ne("RIGHT......{0}", getKeyName(conKeyboard[MenuMode - 30].Right)), 3, MenuX, MenuY + 30 + menuFix);
                        // SuperPrint(fmt::format_ne("RUN........{0}", getKeyName(conKeyboard[MenuMode - 30].Run)), 3, MenuX, MenuY + 60 + menuFix);
                        // SuperPrint(fmt::format_ne("ALT RUN....{0}", getKeyName(conKeyboard[MenuMode - 30].AltRun)), 3, MenuX, MenuY + 90 + menuFix);
                        // SuperPrint(fmt::format_ne("JUMP.......{0}", getKeyName(conKeyboard[MenuMode - 30].Jump)), 3, MenuX, MenuY + 120 + menuFix);
                        // SuperPrint(fmt::format_ne("ALT JUMP...{0}", getKeyName(conKeyboard[MenuMode - 30].AltJump)), 3, MenuX, MenuY + 150 + menuFix);
                        // SuperPrint(fmt::format_ne("DROP ITEM..{0}", getKeyName(conKeyboard[MenuMode - 30].Drop)), 3, MenuX, MenuY + 180 + menuFix);
                        // SuperPrint(fmt::format_ne("PAUSE......{0}", getKeyName(conKeyboard[MenuMode - 30].Start)), 3, MenuX, MenuY + 210 + menuFix);
    //                    Else
                    // }
                    // else
                    // {
                        SuperPrint("INPUT......JOYSTICK " + std::to_string(useJoystick[MenuMode - 30]), 3, MenuX, 260 + menuFix);

                        SuperPrint(fmt::format_ne("UP.........{0}", getJoyKeyName(conJoystick[MenuMode - 30].Up)), 3, MenuX, MenuY - 60 + menuFix);
                        SuperPrint(fmt::format_ne("DOWN.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Down)), 3, MenuX, MenuY - 30 + menuFix);
                        SuperPrint(fmt::format_ne("LEFT.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Left)), 3, MenuX, MenuY + menuFix);
                        SuperPrint(fmt::format_ne("RIGHT......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Right)), 3, MenuX, MenuY + 30 + menuFix);
                        SuperPrint(fmt::format_ne("RUN........{0}", getJoyKeyName(conJoystick[MenuMode - 30].Run)), 3, MenuX, MenuY + 60 + menuFix);
                        SuperPrint(fmt::format_ne("ALT RUN....{0}", getJoyKeyName(conJoystick[MenuMode - 30].AltRun)), 3, MenuX, MenuY + 90 + menuFix);
                        SuperPrint(fmt::format_ne("JUMP.......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Jump)), 3, MenuX, MenuY + 120 + menuFix);
                        SuperPrint(fmt::format_ne("ALT JUMP...{0}", getJoyKeyName(conJoystick[MenuMode - 30].AltJump)), 3, MenuX, MenuY + 150 + menuFix);
                        SuperPrint(fmt::format_ne("DROP ITEM..{0}", getJoyKeyName(conJoystick[MenuMode - 30].Drop)), 3, MenuX, MenuY + 180 + menuFix);
                        SuperPrint(fmt::format_ne("PAUSE......{0}", getJoyKeyName(conJoystick[MenuMode - 30].Start)), 3, MenuX, MenuY + 210 + menuFix);

//                        if(conJoystick[MenuMode - 30].Run >= 0)
//                            SuperPrint(fmt::format_ne("RUN........{0}", conJoystick[MenuMode - 30].Run), 3, MenuX, 290 + menuFix);
//                        else
//                            SuperPrint("RUN........_", 3, MenuX, 290 + menuFix);

//                        if(conJoystick[MenuMode - 30].AltRun >= 0)
//                            SuperPrint(fmt::format_ne("ALT RUN....{0}", conJoystick[MenuMode - 30].AltRun), 3, MenuX, 320 + menuFix);
//                        else
//                            SuperPrint("ALT RUN...._", 3, MenuX, 320 + menuFix);

//                        if(conJoystick[MenuMode - 30].Jump >= 0)
//                            SuperPrint(fmt::format_ne("JUMP.......{0}", conJoystick[MenuMode - 30].Jump), 3, MenuX, 350 + menuFix);
//                        else
//                            SuperPrint("JUMP......._", 3, MenuX, 350 + menuFix);

//                        if(conJoystick[MenuMode - 30].AltJump >= 0)
//                            SuperPrint(fmt::format_ne("ALT JUMP...{0}", conJoystick[MenuMode - 30].AltJump), 3, MenuX, 380 + menuFix);
//                        else
//                            SuperPrint("ALT JUMP..._", 3, MenuX, 380 + menuFix);

//                        if(conJoystick[MenuMode - 30].Drop >= 0)
//                            SuperPrint(fmt::format_ne("DROP ITEM..{0}", conJoystick[MenuMode - 30].Drop), 3, MenuX, 410 + menuFix);
//                        else
//                            SuperPrint("DROP ITEM.._", 3, MenuX, 410 + menuFix);

//                        if(conJoystick[MenuMode - 30].Start >= 0)
//                            SuperPrint(fmt::format_ne("PAUSE......{0}", conJoystick[MenuMode - 30].Start), 3, MenuX, 440 + menuFix);
//                        else
//                            SuperPrint("PAUSE......_", 3, MenuX, 440 + menuFix);
                    // }

                    frmMain.renderTexture(MenuX - 20, MenuY - 90 + (MenuCursor * 30) + menuFix,
                                          GFX.MCursor[0].w, GFX.MCursor[0].h, GFX.MCursor[0], 0, 0);
                }

                // frmMain.renderTexture(int(MenuMouseX), int(MenuMouseY), GFX.ECursor[2]);
            }
            if(PrintFPS > 0) {
                SuperPrint(fmt::format_ne("{0}", int(PrintFPS)), 1, 8, 8);
            }
        }

        // There was code for magic hand mode here.

        if(numScreens > 1) // for multiple screens
            frmMain.resetViewport();

        if(GameOutro)
        {
            frmMain.renderRect(0, 0, ScreenW, Maths::iRound(CreditChop), 0, 0, 0);
            frmMain.renderRect(0, ScreenH - Maths::iRound(CreditChop), ScreenW, ScreenH, 0, 0, 0);
            DoCredits();
        }

//        If LevelEditor = True Then
//            StretchBlt frmLevelWindow.vScreen(Z).hdc, 0, 0, frmLevelWindow.vScreen(Z).ScaleWidth, frmLevelWindow.vScreen(Z).ScaleHeight, myBackBuffer, 0, 0, 800, 600, vbSrcCopy
//        Else
        { // NOT AN EDITOR!!!
            if(ScreenShake > 0)
            {
                ScreenShake--;
                if(ScreenShake == 0)
                {
                    frmMain.offsetViewport(0, 0);
                }
                else
                {
                    A = (iRand() % ScreenShake * 4) - ScreenShake * 2;
                    B = (iRand() % ScreenShake * 4) - ScreenShake * 2;
                    frmMain.offsetViewport(A, B);
                }
            }
        }
//    Next Z
    }

    // if(!skipRepaint)
    //     frmMain.repaint();
    if (!skipRepaint)
        frmMain.finalizeDraw();
    // printf("finalized!\n");

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
}
