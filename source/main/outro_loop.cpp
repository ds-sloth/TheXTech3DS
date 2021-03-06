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
#include "../game_main.h"
#include "../joystick.h"
#include "../npc.h"
#include "../blocks.h"
#include "../effect.h"
#include "../player.h"
#include "../graphics.h"
#include "../sound.h"

void OutroLoop()
{
    Controls_t blankControls;
    int A = 0;
    int B = 0;
    Location_t tempLocation;
    bool jumpBool = false;
    long long fBlock = 0;
    long long lBlock = 0;
    UpdateControls();

    for(A = 1; A <= numPlayers; A++)
    {
        Player[A].Controls = blankControls;
        Player[A].Controls.Left = true;
        jumpBool = true;
        tempLocation = Player[A].Location;
        tempLocation = Player[A].Location;
        tempLocation.SpeedX = 0;
        tempLocation.SpeedY = 0;
        tempLocation.Y = Player[A].Location.Y + Player[A].Location.Height - 8;
        tempLocation.Height = 16;
        tempLocation.Width = 16;
        if(Player[A].Location.SpeedX > 0)
            tempLocation.X = Player[A].Location.X + Player[A].Location.Width + 20;
        else
            tempLocation.X = Player[A].Location.X - tempLocation.Width - 20;
        fBlock = FirstBlock[(tempLocation.X / 32) - 1];
        lBlock = LastBlock[((tempLocation.X + tempLocation.Width) / 32.0) + 1];
        for(B = (int)fBlock; B <= lBlock; B++)
        {
            if(tempLocation.X + tempLocation.Width >= Block[B].Location.X)
            {
                if(tempLocation.X <= Block[B].Location.X + Block[B].Location.Width)
                {
                    if(tempLocation.Y + tempLocation.Height >= Block[B].Location.Y)
                    {
                        if(tempLocation.Y <= Block[B].Location.Y + Block[B].Location.Height)
                        {
                            if(BlockNoClipping[Block[B].Type] == false && Block[B].Invis == false && Block[B].Hidden == false && !(BlockIsSizable[Block[B].Type] && Block[B].Location.Y < Player[A].Location.Y + Player[A].Location.Height - 3))
                                jumpBool = false;
                        }
                    }
                }
            }
            else
            {
                if(BlocksSorted == true)
                    break;
            }
        }
        if(jumpBool == true || Player[A].Jump > 0)
            Player[A].Controls.Jump = true;
    }
    // most of the credits code, which was misplaced in the draw script
    for(A = 1; A <= numCredits; A++)
    {
        Credit[A].Location.Y -= 0.8;
    }
    // Closing screen
    if(Credit[numCredits].Location.Y + Credit[numCredits].Location.Height < -100)
    {
        if(musicPlaying)
        {
            FadeOutMusic(11000);
            musicPlaying = false;
        }

        CreditChop += 0.4f;
        if(CreditChop >= ScreenH/2)
        {
            CreditChop = ScreenH/2;
            EndCredits = EndCredits + 1;
            if(EndCredits == 300)
            {
                SetupCredits();
                GameOutro = false;
                GameMenu = true;
            }
        }
        else
            EndCredits = 0;
    }
    // Opening screen
    else if(CreditChop > 100 && Credit[numCredits].Location.Y + Credit[numCredits].Location.Height > 0)
    {
        CreditChop -= 0.4f;
        if(CreditChop > ScreenH/2) CreditChop = ScreenH/2;
        if(CreditChop < 100)
            CreditChop = 100;

        if(CreditChop+50 < ScreenH/2 && !musicPlaying)
        {
            if(bgMusic[0] <= 0) // Play default music if no music set in outro level
            {
                musicName = "tmusic";
                PlayMusic("tmusic", 2000);
                musicPlaying = true;
            }
            else // Otherwise, play the music that set by level
                StartMusic(0, 2000);
        }
    }
    UpdateNPCs();
    UpdateBlocks();
    UpdateEffects();
    UpdatePlayer();
    UpdateGraphics();
    UpdateSound();

}

void SetupCredits()
{
    int A = 0;
    numCredits = 0;
    AddCredit("Super Mario Bros. X");
    AddCredit("TheXTech");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("The Greatest Fan-Game of All Time");
    AddCredit("");
    AddCredit("");
    AddCredit("Created By:");
    AddCredit("");
    AddCredit("Andrew Spinks");
    AddCredit("'Redigit'");
    AddCredit("");
    AddCredit("");
    AddCredit("C++ port By:");
    AddCredit("");
    AddCredit("Vitaly Novichkov");
    AddCredit("'Wohlstand'");
    AddCredit("");
    AddCredit("");
    AddCredit("Ported to 3DS By:");
    AddCredit("");
    AddCredit("Abe Leite");
    AddCredit("'ds-sloth'");
    AddCredit("");
    AddCredit("");

    if(!WorldCredits[1].empty())
    {
        AddCredit("Level Design:");
        AddCredit("");
        for(A = 1; A <= maxWorldCredits; A++)
        {
            if(WorldCredits[A].empty())
                break;
            AddCredit(WorldCredits[A]);
        }
        AddCredit("");
        AddCredit("");
        AddCredit("");
    }

    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("Custom Sprites:");
    AddCredit("");
    AddCredit("Blue");
    AddCredit("Iceman404");
    AddCredit("LuigiFan");
    AddCredit("NameUser");
    AddCredit("Redigit");
    AddCredit("Valtteri");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("Special Thanks:");
    AddCredit("");
    AddCredit("3DS Port");
    AddCredit("");
    // ANYONE I got sound from, resources from, devkitPro in general, etc
    // citro2d, you know...
    AddCredit("...");
    AddCredit("");
    AddCredit("C++ Port");
    AddCredit("");
    AddCredit("Kevsoft");
    AddCredit("Rednaxela");
    AddCredit("Aero");
    AddCredit("Kley");
    AddCredit("ShadowYoshi (Joey)");
    AddCredit("");
    AddCredit("Original Game");
    AddCredit("");
    AddCredit("4matsy");
    AddCredit("AndyDark");
    AddCredit("Bikcmp");
    AddCredit("Blue");
    AddCredit("Captain Obvious");
    AddCredit("CaptainTrek");
    AddCredit("Chase");
    AddCredit("Coldwin");
    AddCredit("CrystalMike");
    AddCredit("DarkMatt");
    AddCredit("FallingSnow");
    AddCredit("Garro");
    AddCredit("Knuckles96");
    AddCredit("Kuribo");
    AddCredit("Kyasarin");
    AddCredit("Luminous");
    AddCredit("m4sterbr0s");
    AddCredit("NameUser");
    AddCredit("Namyrr");
    AddCredit("Qig");
    AddCredit("Quill");
    AddCredit("Red_Yoshi");
    AddCredit("Spitfire");
    AddCredit("Valtteri");
    AddCredit("Vandarx");
    AddCredit("Zephyr");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("'He has delivered us from the power");
    AddCredit("of darkness and conveyed us into");
    AddCredit("the kingdom of the Son of His love.'");
    AddCredit("");
    AddCredit("Colossians 1:13");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("");
    AddCredit("www.SuperMarioBrothers.org");
    AddCredit("wohlsoft.ru");
    AddCredit("github.com/ds-sloth/TheXTech3DS");

    for(A = 1; A <= numCredits; A++)
    {
        Credit[A].Location.Width = Credit[A].Text.size() * 18;
        Credit[A].Location.Height = 16;
        Credit[A].Location.X = 400 - (Credit[A].Location.Width / 2.0);
        Credit[A].Location.Y = 640 + 32 * A;
    }
}
