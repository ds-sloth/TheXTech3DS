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

#include "globals.h"
#include "graphics.h"
#include "collision.h"
#include "game_main.h"
#include "sound.h"
#include "change_res.h"

#include "pseudo_vb.h"

#include <Utils/maths.h>


//  Get the screen position
void GetvScreen(int A)
{
    if(Player[A].Mount == 2)
        Player[A].Location.Height = 0;
    vScreenX[A] = -Player[A].Location.X + (vScreen[A].Width * 0.5) - Player[A].Location.Width / 2.0;
    vScreenY[A] = -Player[A].Location.Y + (vScreen[A].Height * 0.5) - vScreenYOffset - Player[A].Location.Height;
    vScreenX[A] = vScreenX[A] - vScreen[A].tempX;
    vScreenY[A] = vScreenY[A] - vScreen[A].TempY;
    if (vScreen[A].Width + level[Player[A].Section].X > level[Player[A].Section].Width)
        vScreenX[A] = -level[Player[A].Section].X/2 + -(level[Player[A].Section].Width - vScreen[A].Width)/2;
    else if(-vScreenX[A] < level[Player[A].Section].X)
        vScreenX[A] = -level[Player[A].Section].X;
    else if(-vScreenX[A] + vScreen[A].Width > level[Player[A].Section].Width)
        vScreenX[A] = -(level[Player[A].Section].Width - vScreen[A].Width);
    if (vScreen[A].Height + level[Player[A].Section].Y > level[Player[A].Section].Height)
        vScreenY[A] = -level[Player[A].Section].Y/2 + -(level[Player[A].Section].Height - vScreen[A].Height)/2;
    else if(-vScreenY[A] < level[Player[A].Section].Y)
        vScreenY[A] = -level[Player[A].Section].Y;
    else if(-vScreenY[A] + vScreen[A].Height > level[Player[A].Section].Height)
        vScreenY[A] = -(level[Player[A].Section].Height - vScreen[A].Height);
    if(vScreen[A].TempDelay > 0)
        vScreen[A].TempDelay = vScreen[A].TempDelay - 1;
    else
    {
        if(vScreen[A].tempX > 0)
            vScreen[A].tempX = vScreen[A].tempX - 1;
        if(vScreen[A].tempX < 0)
            vScreen[A].tempX = vScreen[A].tempX + 1;
        if(vScreen[A].TempY > 0)
            vScreen[A].TempY = vScreen[A].TempY - 1;
        if(vScreen[A].TempY < 0)
            vScreen[A].TempY = vScreen[A].TempY + 1;
    }
    if(vScreenX[A] & 1) vScreenX[A] -= 1;
    if(vScreenY[A] & 1) vScreenY[A] -= 1;
    if(Player[A].Mount == 2)
        Player[A].Location.Height = 128;
}

//  Get the screen position if it were 800x600
void GetvScreenCanonical(int A, int* left, int* top)
{
    if(Player[A].Mount == 2)
        Player[A].Location.Height = 0;
    *left = -Player[A].Location.X + (800 * 0.5) - Player[A].Location.Width / 2.0;
    *top = -Player[A].Location.Y + (600 * 0.5) - vScreenYOffset - Player[A].Location.Height;
    *left -= vScreen[A].tempX;
    *top -= vScreen[A].TempY;
    if(-(*left) < level[Player[A].Section].X)
        *left = -level[Player[A].Section].X;
    else if(-(*left) + 800 > level[Player[A].Section].Width)
        *left = -(level[Player[A].Section].Width - 800);
    if(-(*top) < level[Player[A].Section].Y)
        *top = -level[Player[A].Section].Y;
    else if(-(*top) + 600 > level[Player[A].Section].Height)
        *top = -(level[Player[A].Section].Height - 600);
    if(Player[A].Mount == 2)
        Player[A].Location.Height = 128;
}

// Get the average screen position for all players
void GetvScreenAverage()
{
    int A = 0;
    int B = 0;
    double OldX = 0;
    double OldY = 0;

    OldX = vScreenX[1];
    OldY = vScreenY[1];
    UNUSED(OldY);

    vScreenX[1] = 0;
    vScreenY[1] = 0;

    for(A = 1; A <= numPlayers; A++)
    {
        if(!Player[A].Dead && Player[A].Effect != 6)
        {
            vScreenX[1] = vScreenX[1] - Player[A].Location.X - Player[A].Location.Width / 2.0;
            if(Player[A].Mount == 2)
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y;
            else
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y - Player[A].Location.Height;
            B = B + 1;
        }
    }

    A = 1;
    if(B == 0)
    {
        if(GameMenu)
        {
            vScreenX[1] = -level[0].X;
            B = 1;
        }
        else
            return;
    }
    vScreenX[1] = (vScreenX[1] / B) + (ScreenW * 0.5);
    vScreenY[1] = (vScreenY[1] / B) + (ScreenH * 0.5) - vScreenYOffset;

    if (vScreen[A].Width + level[Player[1].Section].X > level[Player[1].Section].Width)
        vScreenX[A] = -level[Player[1].Section].X/2 + -(level[Player[1].Section].Width - vScreen[A].Width)/2;
    else if(-vScreenX[A] < level[Player[1].Section].X)
        vScreenX[A] = -level[Player[1].Section].X;
    else if(-vScreenX[A] + ScreenW > level[Player[1].Section].Width)
        vScreenX[A] = -(level[Player[1].Section].Width - ScreenW);
    if (vScreen[A].Height + level[Player[1].Section].Y > level[Player[1].Section].Height)
        vScreenY[A] = -level[Player[1].Section].Y/2 + -(level[Player[1].Section].Height - vScreen[A].Height)/2;
    else if(-vScreenY[A] < level[Player[1].Section].Y)
        vScreenY[A] = -level[Player[1].Section].Y;
    else if(-vScreenY[A] + ScreenH > level[Player[1].Section].Height)
        vScreenY[A] = -(level[Player[1].Section].Height - ScreenH);

    if(GameMenu)
    {
        if(vScreenX[1] > OldX)
        {
            if(fEqual(vScreenX[1], -level[0].X))
                vScreenX[1] = OldX + 20;
            else
                vScreenX[1] = OldX;
        }
        else if(vScreenX[1] < OldX - 10)
            vScreenX[1] = OldX - 10;
    }

    if(vScreenX[A] & 1) vScreenX[A] -= 1;
    if(vScreenY[A] & 1) vScreenY[A] -= 1;
}

// Get the average screen position for all players as if the screen were 800x600
void GetvScreenAverageCanonical(int* left, int* top)
{
    int A = 0;
    int B = 0;

    *left = 0;
    *top = 0;

    for(A = 1; A <= numPlayers; A++)
    {
        if(!Player[A].Dead && Player[A].Effect != 6)
        {
            *left -= Player[A].Location.X + Player[A].Location.Width / 2.0;
            if(Player[A].Mount == 2)
                *top -= Player[A].Location.Y;
            else
                *top -= Player[A].Location.Y + Player[A].Location.Height;
            B += 1;
        }
    }

    A = 1;
    if(B == 0)
    {
        if(GameMenu)
        {
            *left = -level[0].X;
            B = 1;
        }
        else
            return;
    }
    *left = (*left / B) + (800 / 2);
    *top = (*top / B) + (600 / 2) - vScreenYOffset;

    if(-(*left) < level[Player[1].Section].X)
        *left = -level[Player[1].Section].X;
    else if(-(*left) + 800 > level[Player[1].Section].Width)
        *left = -(level[Player[1].Section].Width - 800);
    if(-(*top) < level[Player[1].Section].Y)
        *top = -level[Player[1].Section].Y;
    else if(-(*top) + 600 > level[Player[1].Section].Height)
        *top = -(level[Player[1].Section].Height - 600);
}

// Get the average screen position for all players with no level edge detection
void GetvScreenAverage2()
{
    int A = 0;
    int B = 0;
    vScreenX[1] = 0;
    vScreenY[1] = 0;
    for(A = 1; A <= numPlayers; A++)
    {
        if(Player[A].Dead == false)
        {
            vScreenX[1] = vScreenX[1] - Player[A].Location.X - Player[A].Location.Width / 2.0;
            if(Player[A].Mount == 2)
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y;
            else
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y - Player[A].Location.Height;
            B = B + 1;
        }
    }
    A = 1;
    if(B == 0)
        return;
    vScreenX[1] = (vScreenX[1] / B) + (ScreenW * 0.5);
    vScreenY[1] = (vScreenY[1] / B) + (ScreenH * 0.5) - vScreenYOffset;

    if(vScreenX[A] & 1) vScreenX[A] -= 1;
    if(vScreenY[A] & 1) vScreenY[A] -= 1;
}

void SetupGraphics()
{
    //DUMMY AND USELESS

    // Creates the back buffer for the main game
    // myBackBuffer = CreateCompatibleDC(GetDC(0))
    // myBufferBMP = CreateCompatibleBitmap(GetDC(0), screenw, screenh)
//    myBackBuffer = CreateCompatibleDC(frmMain::hdc);
//    myBufferBMP = CreateCompatibleBitmap(frmMain::hdc, ScreenW, ScreenH);
//    SelectObject myBackBuffer, myBufferBMP;
//    GFX.Split(2).Width = ScreenW;
//    GFX.Split(2).Height = ScreenH;
    // GFX.BackgroundColor(1).Width = Screen.Width
    // GFX.BackgroundColor(1).Height = Screen.Height
    // GFX.BackgroundColor(2).Width = Screen.Width
    // GFX.BackgroundColor(2).Height = Screen.Height
}

void SetupEditorGraphics()
{
    //DUMMY AND USELESS

//    GFX.Split(1).Width = frmLevelWindow.vScreen(1).Width
//    GFX.Split(1).Height = frmLevelWindow.vScreen(1).Height
//    GFX.Split(2).Width = frmLevelWindow.vScreen(1).Width
//    GFX.Split(2).Height = frmLevelWindow.vScreen(1).Height
//    vScreen(1).Height = frmLevelWindow.vScreen(1).ScaleHeight
//    vScreen(1).Width = frmLevelWindow.vScreen(1).ScaleWidth
//    vScreen(1).Left = 0
//    vScreen(1).Top = 0
//    vScreen(2).Visible = False
//    'Creates the back buffer for the level editor
//    'myBackBuffer = CreateCompatibleDC(GetDC(0))
//    'myBufferBMP = CreateCompatibleBitmap(GetDC(0), screenw, screenh)
//    'SelectObject myBackBuffer, myBufferBMP
//    GFX.BackgroundColor(1).Width = frmLevelWindow.vScreen(1).Width
//    GFX.BackgroundColor(1).Height = frmLevelWindow.vScreen(1).Height
//    GFX.BackgroundColor(2).Width = frmLevelWindow.vScreen(1).Width
//    GFX.BackgroundColor(2).Height = frmLevelWindow.vScreen(1).Height
}

void PlayerWarpGFX(int A, Location_t &tempLocation, float &X2, float &Y2)
{
    // .Effect = 3      -- Warp Pipe
    // .Effect2 = 0     -- Entering
    // .Effect2 = 1     -- Move to next spot
    // .Effect2 => 100  -- Delay at next spot
    // .Effect2 = 2     -- Exiting
    // .Effect2 = 3     -- Done
    if(Player[A].Effect2 == 0.0)
    {
        if(Warp[Player[A].Warp].Direction == 3) // Moving down
        {
            if(tempLocation.Height > (Warp[Player[A].Warp].Entrance.Y + Warp[Player[A].Warp].Entrance.Height) - (tempLocation.Y))
                tempLocation.Height = (Warp[Player[A].Warp].Entrance.Y + Warp[Player[A].Warp].Entrance.Height) - (tempLocation.Y);
        }
        else if(Warp[Player[A].Warp].Direction == 1) // Moving up
        {
            if(Warp[Player[A].Warp].Entrance.Y > tempLocation.Y)
            {
                Y2 = float(Warp[Player[A].Warp].Entrance.Y - tempLocation.Y);
                tempLocation.Y = Warp[Player[A].Warp].Entrance.Y;
                tempLocation.Height = tempLocation.Height - Y2;
            }
        }
        else if(Warp[Player[A].Warp].Direction == 4) // Moving right
            tempLocation.Width = (Warp[Player[A].Warp].Entrance.X + Warp[Player[A].Warp].Entrance.Width) - (tempLocation.X);
        else if(Warp[Player[A].Warp].Direction == 2) // Moving left
        {
            X2 = float(Warp[Player[A].Warp].Entrance.X - tempLocation.X);
            if(X2 < 0)
                X2 = 0;
            else
                tempLocation.X = Warp[Player[A].Warp].Entrance.X;
        }
    }
    else if(Maths::iRound(Player[A].Effect2) == 2)
    {
        if(Warp[Player[A].Warp].Direction2 == 3) // Moving up
        {
            if(tempLocation.Height > (Warp[Player[A].Warp].Exit.Y + Warp[Player[A].Warp].Exit.Height) - (tempLocation.Y))
                tempLocation.Height = (Warp[Player[A].Warp].Exit.Y + Warp[Player[A].Warp].Exit.Height) - (tempLocation.Y);
        }
        else if(Warp[Player[A].Warp].Direction2 == 1) // Moving down
        {
            if(Warp[Player[A].Warp].Exit.Y > tempLocation.Y)
            {
                Y2 = float(Warp[Player[A].Warp].Exit.Y - tempLocation.Y);
                tempLocation.Y = Warp[Player[A].Warp].Exit.Y;
                tempLocation.Height = tempLocation.Height - double(Y2);
            }
        }
        else if(Warp[Player[A].Warp].Direction2 == 4) // Moving left
            tempLocation.Width = (Warp[Player[A].Warp].Exit.X + Warp[Player[A].Warp].Exit.Width) - (tempLocation.X);
        else if(Warp[Player[A].Warp].Direction2 == 2) // Moving right
        {
            X2 = float(Warp[Player[A].Warp].Exit.X - tempLocation.X);
            if(X2 < 0)
                X2 = 0;
            else
                tempLocation.X = Warp[Player[A].Warp].Exit.X;
        }
    }

    if(Maths::iRound(Player[A].Effect2) == 1 || Player[A].Effect2 >= 100)
        tempLocation.Height = 0;

    if(tempLocation.Height < 0)
    {
        tempLocation.Height = 0;
        tempLocation.Width = 0;
    }

    tempLocation.Width -= double(X2);
}

void NPCWarpGFX(int A, Location_t &tempLocation, float &X2, float &Y2)
{
    // player(a).effect = 3      -- Warp Pipe
    // player(a).effect2 = 0     -- Entering
    // player(a).effect2 = 1     -- Move to next spot
    // player(a).effect2 => 100  -- Delay at next spot
    // player(a).effect2 = 2     -- Exiting
    // player(a).effect2 = 3     -- Done
    if(Player[A].Effect2 == 0.0)
    {
        if(Warp[Player[A].Warp].Direction == 3) // Moving down
        {
            if(tempLocation.Height > (Warp[Player[A].Warp].Entrance.Y + Warp[Player[A].Warp].Entrance.Height) - (tempLocation.Y))
                tempLocation.Height = (Warp[Player[A].Warp].Entrance.Y + Warp[Player[A].Warp].Entrance.Height) - (tempLocation.Y);
        }
        else if(Warp[Player[A].Warp].Direction == 1) // Moving up
        {
            if(Warp[Player[A].Warp].Entrance.Y > tempLocation.Y)
            {
                Y2 = float(Warp[Player[A].Warp].Entrance.Y - tempLocation.Y);
                tempLocation.Y = Warp[Player[A].Warp].Entrance.Y;
                tempLocation.Height = tempLocation.Height - double(Y2);
            }
        }
        else if(Warp[Player[A].Warp].Direction == 4) // Moving right
            tempLocation.Width = (Warp[Player[A].Warp].Entrance.X + Warp[Player[A].Warp].Entrance.Width) - (tempLocation.X);
        else if(Warp[Player[A].Warp].Direction == 2) // Moving left
        {
            X2 = float(Warp[Player[A].Warp].Entrance.X - tempLocation.X);
            if(X2 < 0)
                X2 = 0;
            else
                tempLocation.X = Warp[Player[A].Warp].Entrance.X;
        }
    }
    else if(Maths::iRound(Player[A].Effect2) == 2)
    {
        if(Warp[Player[A].Warp].Direction2 == 3) // Moving up
        {
            if(tempLocation.Height > (Warp[Player[A].Warp].Exit.Y + Warp[Player[A].Warp].Exit.Height) - (tempLocation.Y))
                tempLocation.Height = (Warp[Player[A].Warp].Exit.Y + Warp[Player[A].Warp].Exit.Height) - (tempLocation.Y);
        }
        else if(Warp[Player[A].Warp].Direction2 == 1) // Moving down
        {
            if(Warp[Player[A].Warp].Exit.Y > tempLocation.Y)
            {
                Y2 = float(Warp[Player[A].Warp].Exit.Y - tempLocation.Y);
                tempLocation.Y = Warp[Player[A].Warp].Exit.Y;
                tempLocation.Height = tempLocation.Height - double(Y2);
            }
        }
        else if(Warp[Player[A].Warp].Direction2 == 4) // Moving left
            tempLocation.Width = (Warp[Player[A].Warp].Exit.X + Warp[Player[A].Warp].Exit.Width) - (tempLocation.X);
        else if(Warp[Player[A].Warp].Direction2 == 2) // Moving right
        {
            X2 = float(Warp[Player[A].Warp].Exit.X - tempLocation.X);
            if(X2 < 0)
                X2 = 0;
            else
                tempLocation.X = Warp[Player[A].Warp].Exit.X;
        }
    }

    if(Maths::iRound(Player[A].Effect2) == 1 || Player[A].Effect2 >= 100)
        tempLocation.Height = 0;

    if(tempLocation.Height < 0)
    {
        tempLocation.Height = 0;
        tempLocation.Width = 0;
    }
}

// change from fullscreen to windowed mode
void ChangeScreen()
{}

void GetvScreenCredits()
{
    int A = 0;
    int B = 0;
    vScreenX[1] = 0;
    vScreenY[1] = 0;
    for(A = 1; A <= numPlayers; A++)
    {
        if(Player[A].Dead == false && Player[A].Effect != 6)
        {
            vScreenX[1] = vScreenX[1] - Player[A].Location.X - Player[A].Location.Width / 2.0;
            if(Player[A].Mount == 2)
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y;
            else
                vScreenY[1] = vScreenY[1] - Player[A].Location.Y - Player[A].Location.Height;
            B = B + 1;
        }
    }
    A = 1;
    if(B == 0)
        return;
    vScreenX[1] = (vScreenX[1] / B) + (ScreenW * 0.5);
    vScreenY[1] = (vScreenY[1] / B) + (ScreenH * 0.5) - vScreenYOffset;
    if(-vScreenX[A] < level[Player[1].Section].X)
        vScreenX[A] = -level[Player[1].Section].X;
    if(-vScreenX[A] + ScreenW > level[Player[1].Section].Width)
        vScreenX[A] = -(level[Player[1].Section].Width - ScreenW);
    if(-vScreenY[A] < level[Player[1].Section].Y + 100)
        vScreenY[A] = -level[Player[1].Section].Y + 100;
    if(-vScreenY[A] + ScreenH > level[Player[1].Section].Height - 100)
        vScreenY[A] = -(level[Player[1].Section].Height - ScreenH) - 100;

    if(vScreenX[A] & 1) vScreenX[A] -= 1;
    if(vScreenY[A] & 1) vScreenY[A] -= 1;
}

int pfrX(int plrFrame)
{
    int A;
    A = plrFrame;
    A = A - 50;
    while(A > 100)
        A = A - 100;
    if(A > 90)
        A = 9;
    else if(A > 90)
        A = 9;
    else if(A > 80)
        A = 8;
    else if(A > 70)
        A = 7;
    else if(A > 60)
        A = 6;
    else if(A > 50)
        A = 5;
    else if(A > 40)
        A = 4;
    else if(A > 30)
        A = 3;
    else if(A > 20)
        A = 2;
    else if(A > 10)
        A = 1;
    else
        A = 0;
    return A * 100;
}

int pfrY(int plrFrame)
{
    int A;
    A = plrFrame;
    A = A - 50;
    while(A > 100)
        A = A - 100;
    A = A - 1;
    while(A > 9)
        A = A - 10;
    return A * 100;
}

void DrawFrozenNPC(int Z, int A)
{
    auto &n = NPC[A];
    if((vScreenCollision(Z, n.Location) ||
        vScreenCollision(Z, newLoc(n.Location.X - (NPCWidthGFX[n.Type] - n.Location.Width) / 2,
                            n.Location.Y, CDbl(NPCWidthGFX[n.Type]), CDbl(NPCHeight[n.Type])))) && !n.Hidden)
    {
// draw npc
        frmMain.renderTexture(int(vScreenX[Z] + n.Location.X + 2),
                              int(vScreenY[Z] + n.Location.Y + 2),
                              int(n.Location.Width - 4),
                              int(n.Location.Height - 4),
                              GFXNPCBMP[int(n.Special)],
                              2, 2 + int(n.Special2) * NPCHeight[int(n.Special)], n.Shadow);

        // draw ice
        frmMain.renderTexture(int(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type]),
                              int(vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type]),
                              int(n.Location.Width - 6), int(n.Location.Height - 6),
                              GFXNPCBMP[n.Type], 0, 0, n.Shadow);
        frmMain.renderTexture(int(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type] + n.Location.Width - 6),
                              int(vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type]),
                              6, int(n.Location.Height - 6),
                              GFXNPCBMP[n.Type], 128 - 6, 0, n.Shadow);
        frmMain.renderTexture(int(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type]),
                              int(vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type] + n.Location.Height - 6),
                              int(n.Location.Width - 6), 6,
                              GFXNPCBMP[n.Type], 0, 128 - 6, n.Shadow);
        frmMain.renderTexture(int(vScreenX[Z] + n.Location.X + NPCFrameOffsetX[n.Type] + n.Location.Width - 6),
                              int(vScreenY[Z] + n.Location.Y + NPCFrameOffsetY[n.Type] + n.Location.Height - 6),
                              6, 6, GFXNPCBMP[n.Type],
                              128 - 6, 128 - 6, n.Shadow);
    }
}
