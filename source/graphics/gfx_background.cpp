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
#include <pge_delay.h>


void DrawBackground(int S, int Z)
{
    int tempVar;
    int A = 0;
    int B = 0;
    Location_t tempLocation;
    Location_t tempLevel;
    tempLevel = level[S];
    if(LevelEditor == true)
        LevelREAL[S] = level[S];
    level[S] = LevelREAL[S];

    A = 1; // Blocks
    if(Background2[S] == 1)
    {
        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 2; // Clouds
    if(Background2[S] == 1 || Background2[S] == 2 || Background2[S] == 22)
    {
        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A] - ScreenH + 100;
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    if(Background2[S] == 13)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 3; // Hills
    if(Background2[S] == 2)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 4; // Castle
    if(Background2[S] == 3)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 5; // Pipes
    if(Background2[S] == 4)
    {

        tempVar = (int)(floor(((level[S].Height - level[S].Y) / GFXBackground2Height[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.Y = level[S].Y + ((B * GFXBackground2Height[A] - B) - (vScreenY[Z] + vScreen[Z].Top + level[S].Y) * 0.5) - 32;
            if(level[S].Width - level[S].X > GFXBackground2Width[A])
            {
                tempLocation.X = (-vScreenX[Z] - level[S].X) / (level[S].Width - level[S].X - (ScreenW - vScreen[Z].Left)) * (GFXBackground2Width[A] - (ScreenW - vScreen[Z].Left));
                tempLocation.X = -vScreenX[Z] - tempLocation.X;
            }
            else
                tempLocation.X = level[S].Width - GFXBackground2Width[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 6; // Trees
    if(Background2[S] == 5)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 7; // Bonus
    if(Background2[S] == 6)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 8; // SMB Underground
    if(Background2[S] == 7)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Y - 32;
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 9; // Night
    if(Background2[S] == 8 || Background2[S] == 9)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 10; // Night 2
    if(Background2[S] == 9)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 11; // Overworld
    if(Background2[S] == 10)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 12; // SMW Hills
    if(Background2[S] == 11)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 13; // SMW Trees
    if(Background2[S] == 12)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 14; // SMB3 Desert
    if(Background2[S] == 14)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 15; // SMB3 Dungeon
    if(Background2[S] == 15)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 16; // Crateria
    if(Background2[S] == 16)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 17; // smb3 ship
    if(Background2[S] == 17)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Y - 32;
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 18; // SMW ghost house
    if(Background2[S] == 18)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (600 - vScreen(Z).Top)) * (GFXBackground2Height(A) / 4 - (600 - vScreen(Z).Top))
                // .Y = -vScreenY(Z) - .Y
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[3]);
            }
        }
    }

    A = 19; // smw forest
    if(Background2[S] == 19)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 20; // smb3 forest
    if(Background2[S] == 20)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 21; // smb3 battle game
    if(Background2[S] == 21)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 22; // SMB3 Waterfall
    if(Background2[S] == 22)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[3]);
            }
        }
    }

    A = 23; // SMB3 Tank
    if(Background2[S] == 23)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 24; // smb3 bowsers castle
    if(Background2[S] == 24)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Y - 32; // Height - GFXBackground2height(a)
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 25; // SMB2 Underground
    if(Background2[S] == 25)
    {

        tempVar = (int)(floor(((level[S].Height - level[S].Y) / GFXBackground2Height[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.Y = level[S].Y + ((B * GFXBackground2Height[A] - B) - (vScreenY[Z] + vScreen[Z].Top + level[S].Y) * 0.5) - 32;
            // .X = Level(S).X
            if(level[S].Width - level[S].X > GFXBackground2Width[A])
            {
                // .X = (-vScreenX(Z) - level(S).X) / (level(S).Width - level(S).X - 800) * (GFXBackground2Width(A) - 800)
                tempLocation.X = (-vScreenX[Z] - level[S].X) / (level[S].Width - level[S].X - (ScreenW - vScreen[Z].Left)) * (GFXBackground2Width[A] - (ScreenW - vScreen[Z].Left));
                tempLocation.X = -vScreenX[Z] - tempLocation.X;
            }
            else
                tempLocation.X = level[S].Width - GFXBackground2Width[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 26; // Toad's House
    if(Background2[S] == 26)
    {
        tempVar = int(std::ceil((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5)) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Y - 32; // Height - GFXBackground2height(a)
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X,
                                      vScreenY[Z] + tempLocation.Y,
                                      GFXBackground2Width[A],
                                      GFXBackground2Height[A],
                                      GFXBackground2[A],
                                      0, 0);
            }
        }
    }

    A = 27; // SMB3 Castle
    if(Background2[S] == 27)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 28; // SMW Bonus
    if(Background2[S] == 28)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 3;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 29; // SMW Night
    if(Background2[S] == 29)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (600 - vScreen(Z).Top)) * (GFXBackground2Height(A) / 4 - (600 - vScreen(Z).Top))
                // .Y = -vScreenY(Z) - .Y
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[6]);
            }
        }
    }

    A = 30; // SMW Cave
    if(Background2[S] == 30)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (600 - vScreen(Z).Top)) * (GFXBackground2Height(A) / 4 - (600 - vScreen(Z).Top))
                // .Y = -vScreenY(Z) - .Y
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];

            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[3]);
            }


        }
    }

    A = 31; // SMW Hills 2
    if(Background2[S] == 31)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 32; // SMW Clouds
    if(Background2[S] == 32)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 33; // SMW Snow
    if(Background2[S] == 33)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 34; // SMW Hills 3
    if(Background2[S] == 34)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 35; // SMB 3 Snow Trees
    if(Background2[S] == 35)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 36; // Snow Clouds
    if(Background2[S] == 35 || Background2[S] == 37)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A] - ScreenH + 100;
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    if(Background2[S] == 36)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 37; // SMB 3 Snow Hills
    if(Background2[S] == 37)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 38; // SMB3 Cave with Sky
    if(Background2[S] == 38)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            tempLocation.Y = level[S].Y - 20; // Height - GFXBackground2height(a)
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 39; // SMB3 Cave no Sky
    if(Background2[S] == 39)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 40; // Mystic Cave Zone
    if(Background2[S] == 40)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {



            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (ScreenH - vScreen(Z).Top)) * (GFXBackground2Height(A) - (ScreenH - vScreen(Z).Top))
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)



            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 953, GFXBackground2Width[A], 47, GFXBackground2[A], 0, 953);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.6))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.6);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 916, GFXBackground2Width[A], 37, GFXBackground2[A], 0, 916);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.7))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.7);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 849, GFXBackground2Width[A], 67, GFXBackground2[A], 0, 849);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.8))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.8);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 815, GFXBackground2Width[A], 34, GFXBackground2[A], 0, 815);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.9))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.9);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 709, GFXBackground2Width[A], 106, GFXBackground2[A], 0, 709);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.85))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.85);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 664, GFXBackground2Width[A], 45, GFXBackground2[A], 0, 664);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.8))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.8);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 614, GFXBackground2Width[A], 50, GFXBackground2[A], 0, 614);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 540, GFXBackground2Width[A], 74, GFXBackground2[A], 0, 540);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.7))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.7);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 408, GFXBackground2Width[A], 132, GFXBackground2[A], 0, 408);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 333, GFXBackground2Width[A], 75, GFXBackground2[A], 0, 333);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.8))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.8);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 278, GFXBackground2Width[A], 55, GFXBackground2[A], 0, 278);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.85))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.85);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 235, GFXBackground2Width[A], 43, GFXBackground2[A], 0, 235);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.9))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.9);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 123, GFXBackground2Width[A], 112, GFXBackground2[A], 0, 123);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.8))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.8);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 85, GFXBackground2Width[A], 38, GFXBackground2[A], 0, 85);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.7))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.7);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 48, GFXBackground2Width[A], 37, GFXBackground2[A], 0, 48);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.6))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.6);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 48, GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 41; // SMB 1 Castle
    if(Background2[S] == 41)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 42; // SMW Castle
    if(Background2[S] == 42)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {

                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (600 - vScreen(Z).Top)) * (GFXBackground2Height(A) / 4 - (600 - vScreen(Z).Top))
                // .Y = -vScreenY(Z) - .Y

                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[3]);
            }
        }
    }
    A = 43; // SMW Castle 2
    if(Background2[S] == 43)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 44; // SMB2 Castle
    if(Background2[S] == 44)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                tempLocation.Y = (-vScreenY[Z] - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH);
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 45; // Brinstar
    if(Background2[S] == 45)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 46; // Transport
    if(Background2[S] == 46)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 47; // Transport
    if(Background2[S] == 47)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 48; // SMB2 Blouds
    if(Background2[S] == 48)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 49; // Desert Night
    if(Background2[S] == 49)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 280, GFXBackground2Width[A], 450, GFXBackground2[A], 0, 280);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.9))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.9);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 268, GFXBackground2Width[A], 12, GFXBackground2[A], 0, 268);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.89))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.89);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 244, GFXBackground2Width[A], 24, GFXBackground2[A], 0, 244);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.88))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.88);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 228, GFXBackground2Width[A], 16, GFXBackground2[A], 0, 228);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.87))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.87);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 196, GFXBackground2Width[A], 32, GFXBackground2[A], 0, 196);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.86))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.86);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 164, GFXBackground2Width[A], 32, GFXBackground2[A], 0, 164);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.85))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.85);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 116, GFXBackground2Width[A], 48, GFXBackground2[A], 0, 116);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.84))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.84);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 58, GFXBackground2Width[A], 58, GFXBackground2[A], 0, 58);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.83))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.83);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 58, GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 50; // Shrooms
    if(Background2[S] == 50)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 378, GFXBackground2Width[A], 378, GFXBackground2[A], 0, 378);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.65))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.65);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 220, GFXBackground2[A], 0, 0);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.6))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.6);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 220, GFXBackground2Width[A], 159, GFXBackground2[A], 0, 220);
            }
        }
    }

    A = 51; // SMB1 Desert
    if(Background2[S] == 51)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.75))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.75);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 350, GFXBackground2[A], 0, 0);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 350, GFXBackground2Width[A], GFXBackground2Height[A] - 350, GFXBackground2[A], 0, 350);
            }
        }
    }
    A = 52; // SMB2 Desert Night
    if(Background2[S] == 52)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 280, GFXBackground2Width[A], GFXBackground2Height[A] - 280, GFXBackground2[A], 0, 280);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.9))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.9);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 268, GFXBackground2Width[A], 12, GFXBackground2[A], 0, 268);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.89))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.89);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 244, GFXBackground2Width[A], 24, GFXBackground2[A], 0, 244);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.88))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.88);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 228, GFXBackground2Width[A], 16, GFXBackground2[A], 0, 228);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.87))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.87);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 196, GFXBackground2Width[A], 32, GFXBackground2[A], 0, 196);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.86))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.86);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 164, GFXBackground2Width[A], 32, GFXBackground2[A], 0, 164);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.85))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.85);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 116, GFXBackground2Width[A], 48, GFXBackground2[A], 0, 116);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.84))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.84);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 58, GFXBackground2Width[A], 58, GFXBackground2[A], 0, 58);
            }
        }

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.83))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.83);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 58, GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 53; // Cliffs
    if(Background2[S] == 53)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }
    A = 54; // Warehouse
    if(Background2[S] == 54)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A], GFXBackground2[A], 0, 0);
            }
        }
    }

    A = 55; // SMW Water
    if(Background2[S] == 55)
    {

        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) / 4 - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], GFXBackground2Height[A] / 4.0, GFXBackground2[A], 0, (GFXBackground2Height[A] / 4.0) * SpecialFrame[3]);
            }
        }
    }

    A = 56; // SMB3 Water
    if(Background2[S] == 56)
    {
        if(level[S].Height - level[S].Y > GFXBackground2Height[A])
        {
            // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
            tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
            tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
        }
        else
            tempLocation.Y = level[S].Height - GFXBackground2Height[A];
        tempLocation.Height = GFXBackground2Height[A];
        tempLocation.Width = GFXBackground2Width[A];



        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.65))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.65);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y, GFXBackground2Width[A], 100, GFXBackground2[A], 0, 0);
            }
        }


        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.6))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.6);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 100, GFXBackground2Width[A], 245, GFXBackground2[A], 0, 100);
            }
        }


        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.55))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.55);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 345, GFXBackground2Width[A], 110, GFXBackground2[A], 0, 345);
            }
        }


        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X, vScreenY[Z] + tempLocation.Y + 455, GFXBackground2Width[A], GFXBackground2Height[A] - 455, GFXBackground2[A], 0, 455);
            }
        }
    }

    A = 57; // Warehouse
    if(Background2[S] == 57)
    {
        tempVar = (int)(floor(((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5))) + 2;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A])
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - 600) * (GFXBackground2Height(A) - 600)
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A];
            tempLocation.Height = GFXBackground2Height[A];
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X,
                                      vScreenY[Z] + tempLocation.Y,
                                      GFXBackground2Width[A],
                                      GFXBackground2Height[A],
                                      GFXBackground2[A],
                                      0, 0);
            }
        }
    }

    A = 58; // SMW Night
    if(Background2[S] == 58)
    {
        if (!GFXBackground2Width[A]) return;
        tempVar = (int)(floor((level[S].Width - level[S].X) / GFXBackground2Width[A] * 0.5)) + 1;
        for(B = 0; B <= tempVar; B++)
        {
            tempLocation.X = level[S].X + ((B * GFXBackground2Width[A]) - (vScreenX[Z] + vScreen[Z].Left + level[S].X) * 0.5);
            if(level[S].Height - level[S].Y > GFXBackground2Height[A] / 4.0)
            {
                // .Y = (-vScreenY(Z) - level(S).Y) / (level(S).Height - level(S).Y - (600 - vScreen(Z).Top)) * (GFXBackground2Height(A) / 4 - (600 - vScreen(Z).Top))
                // .Y = -vScreenY(Z) - .Y
                tempLocation.Y = (-vScreenY[Z] - vScreen[Z].Top - level[S].Y) / (level[S].Height - level[S].Y - ScreenH) * (GFXBackground2Height[A] / 4.0 - ScreenH) + vScreen[Z].Top;
                tempLocation.Y = -vScreenY[Z] - tempLocation.Y;
            }
            else
                tempLocation.Y = level[S].Height - GFXBackground2Height[A] / 4.0;
            tempLocation.Height = GFXBackground2Height[A] / 4;
            tempLocation.Width = GFXBackground2Width[A];
            if(vScreenCollision(Z, tempLocation))
            {
                frmMain.renderTexture(vScreenX[Z] + tempLocation.X,
                                      vScreenY[Z] + tempLocation.Y,
                                      GFXBackground2Width[A],
                                      GFXBackground2Height[A] / 4.0,
                                      GFXBackground2[A],
                                      0,
                                      (GFXBackground2Height[A] / 4.0) * SpecialFrame[6]
                );
            }
        }
    }
    level[S] = tempLevel;

}
