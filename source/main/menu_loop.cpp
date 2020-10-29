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

#include <DirManager/dirman.h>
#include <AppPath/app_path.h>
#include <Utils/files.h>
#include <PGE_File_Formats/file_formats.h>
#include <pge_delay.h>
#include <fmt_format_ne.h>

#include "../globals.h"
#include "../game_main.h"
#include "../sound.h"
#include "../joystick.h"
#include "../effect.h"
#include "../graphics.h"
#include "../blocks.h"
#include "../npc.h"
#include "../layers.h"
#include "../player.h"
#include "../collision.h"
#include "level_file.h"

#include "../pseudo_vb.h"

//Dim ScrollDelay As Integer
static int ScrollDelay = 0;

void MenuLoop()
{
//    On Error Resume Next
//    Dim A As Integer
//    int A;
//    Dim B As Integer
    int B;
//    Dim tempLocation As Location
    Location_t tempLocation;
//    Dim newJoystick As Boolean
//    bool newJoystick; // UNUSED
//    Dim tempBool As Boolean
    bool tempBool;
//    Dim menuLen As Integer
    int menuLen;
//    Dim blankPlayer As Player
    Player_t blankPlayer;
//    UpdateControls
    UpdateControls();
//    SingleCoop = 0
    SingleCoop = 0;

//    With Player(1).Controls
    {
        Controls_t &c = Player[1].Controls;

        bool menuDoPress = (c.Start || c.Jump);
        bool menuBackPress = c.Run;

//    If frmMain.MousePointer <> 99 Then
        if(frmMain.MousePointer != 99)
        {
//        frmMain.MousePointer = 99
            frmMain.MousePointer = 99;
            showCursor(0);
//    End If
        }
//    If .Up = False And .Down = False And .Jump = False And .Run = False And .Start = False Then
        if(!c.Up && !c.Down && !c.Jump && !c.Run && !c.Start)
        {
            bool k = false;
            k |= menuDoPress;
            k |= menuBackPress;

            if(!k)
                MenuCursorCanMove = true;
        }
        if(!getNewKeyboard && !getNewJoystick)
        {
            if(c.Up)
            {
                if(MenuCursorCanMove)
                {
                    MenuCursor -= 1;
                    if(MenuMode >= 100)
                    {
                        while((MenuCursor == (PlayerCharacter - 1) &&
                              (MenuMode == 300 || MenuMode == 500)) ||
                               blockCharacter[MenuCursor + 1])
                        {
                            MenuCursor -= 1;
                            if(MenuCursor < 0)
                                MenuCursor = numCharacters - 1;
                        }
                    }
                    PlaySound(26);
                }
                MenuCursorCanMove = false;
            }
            else if(c.Down)
            {
                if(MenuCursorCanMove)
                {
                    MenuCursor += 1;
                    if(MenuMode >= 100)
                    {
                        while((MenuCursor == (PlayerCharacter - 1) &&
                              (MenuMode == 300 || MenuMode == 500)) ||
                               blockCharacter[MenuCursor + 1])
                        {
                            MenuCursor += 1;
                            if(MenuCursor >= numCharacters)
                                MenuCursor = 0;
                        }
                    }
                    PlaySound(26);
                }
                MenuCursorCanMove = false;
            }
        }

//        If MenuMode = 0 Then ' Main Menu
        // Main Menu
        if(MenuMode == 0)
        {
            if(menuBackPress && MenuCursorCanMove)
            {
                if(MenuCursor != 2)
                {
                    MenuCursor = 2;
                    PlaySound(26);
                }
            }
            else if(menuDoPress && MenuCursorCanMove)
            {
                MenuCursorCanMove = false;
                PlayerCharacter = 0;
                PlayerCharacter2 = 0;
                if(MenuCursor == 0)
                {
                    PlaySound(29);
                    MenuMode = 1;
                    FindWorlds();
                    MenuCursor = 0;
                }
                else if(MenuCursor == 1)
                {
                    PlaySound(29);
                    MenuMode = 3;
                    MenuCursor = 0;
                }
                else if(MenuCursor == 2)
                {
                    PlaySound(29);
                    frmMain.clearBuffer();
                    StopMusic();
                    frmMain.repaint();
                    DoEvents();
                    PGE_Delay(500);
                    KillIt();
                }
            }
            if(MenuCursor > 2) MenuCursor = 0;
            if(MenuCursor < 0) MenuCursor = 2;
        }

        // Character Select
        else if(MenuMode == 100 || MenuMode == 200 || MenuMode == 300 || MenuMode == 400 || MenuMode == 500)
        {
            if(MenuCursorCanMove)
            {
                if(menuBackPress)
                {
                    if(MenuMode == 300)
                    {
                        MenuMode = 200;
                        MenuCursor = PlayerCharacter - 1;
                    } else if(MenuMode == 500) {
                        MenuMode = 400;
                        MenuCursor = PlayerCharacter - 1;
                    } else {
                        MenuCursor = selWorld - 1;
                        MenuMode = MenuMode / 100;
                    }
                    MenuCursorCanMove = false;
                    PlaySound(26);
                }
                else if(menuDoPress)
                {
                    PlaySound(29);
                    if(MenuMode == 100)
                    {
                        PlayerCharacter = MenuCursor + 1;
                        MenuMode = 10;
                        MenuCursor = 0;
                    } else if(MenuMode == 200) {
                        PlayerCharacter = MenuCursor + 1;
                        MenuMode = 300;
                        MenuCursor = PlayerCharacter2;
                    } else if(MenuMode == 300) {
                        PlayerCharacter2 = MenuCursor + 1;
                        MenuMode = 20;
                        MenuCursor = 0;
                    } else if(MenuMode == 400) {
                        PlayerCharacter = MenuCursor + 1;
                        MenuMode = 500;
                        MenuCursor = PlayerCharacter2 - 1;
                        if(MenuCursor < 0) MenuCursor = 0;
                    } else if(MenuMode == 500) {
                        PlayerCharacter2 = MenuCursor + 1;
                        MenuCursor = 0;
                        StartBattleMode();
                        return;
                    }
                    MenuCursorCanMove = false;
                }
            }

            if(MenuMode > 0)
            {
                if(MenuCursor > numCharacters - 1)
                {
                    MenuCursor = 0;
                    while((MenuCursor == PlayerCharacter - 1 && (MenuMode == 300 || MenuMode == 500)) ||
                          blockCharacter[MenuCursor + 1])
                    {
                        MenuCursor = MenuCursor + 1;
                    }
                }
                if(MenuCursor < 0)
                {
                    MenuCursor = numCharacters - 1;
                    while((MenuCursor == PlayerCharacter - 1 && (MenuMode == 300 || MenuMode == 500)) ||
                          blockCharacter[MenuCursor + 1])
                    {
                        MenuCursor = MenuCursor - 1;
                    }
                }
            }

            while(((MenuMode == 300 || MenuMode == 500) && MenuCursor == PlayerCharacter - 1) ||
                   blockCharacter[MenuCursor + 1])
            {
                MenuCursor = MenuCursor + 1;
            }

            if(MenuMode >= 100)
            {
                if(MenuCursor >= numCharacters)
                {
                    MenuCursor = 0;
                } else {
                    For(A, 1, numPlayers)
                    {
                        Player[A].Character = MenuCursor + 1;
                        SizeCheck(A);
                    }
                    For(A, 1, numNPCs)
                    {
                        if(NPC[A].Type == 13)
                            NPC[A].Special = MenuCursor + 1;
                    }
                }
            }
        }

        // World Select
        else if(MenuMode == 1 || MenuMode == 2 || MenuMode == 4)
        {
            if(MenuCursorCanMove)
            {
                if(menuBackPress)
                {
                    MenuCursor = MenuMode - 1;
                    if(MenuMode == 4)
                        MenuCursor = 2;
                    MenuMode = 0;
                    PlaySound(26);
                    MenuCursorCanMove = false;
                }
                else if(menuDoPress)
                {
                    PlaySound(29);
                    selWorld = MenuCursor + 1;
                    FindSaves();
                    For(A, 1, numCharacters)
                    {
                        if(MenuMode == 4) {
                            blockCharacter[A] = false;
                        } else {
                            blockCharacter[A] = SelectWorld[selWorld].blockChar[A];
                        }
                    }
                    MenuMode = MenuMode * 100;
                    MenuCursor = 0;
                    if(MenuMode == 400 && PlayerCharacter != 0) MenuCursor = PlayerCharacter - 1;
                    MenuCursorCanMove = false;
                }
            }

            // if we didn't just pick a world
            if(MenuMode < 100)
            {
                if(MenuCursor >= NumSelectWorld)
                    MenuCursor = 0;
                if(MenuCursor < 0)
                    MenuCursor = NumSelectWorld - 1;
            }
        }

        // Save Select
        else if(MenuMode == 10 || MenuMode == 20)
        {
            if(MenuCursorCanMove)
            {
                if(menuBackPress)
                {
                    if(AllCharBlock > 0) {
                        MenuMode = MenuMode / 10;
                        MenuCursor = selWorld - 1;
                    } else {
                        if(MenuMode == 10) {
                            MenuCursor = PlayerCharacter - 1;
                            MenuMode = 100;
                        } else {
                            MenuMode = 300;
                            MenuCursor = PlayerCharacter2 - 1;
                        }
                    }
                    MenuCursorCanMove = false;
                    PlaySound(29);
                }
                else if(menuDoPress)
                {
                    PlaySound(29);
                    numPlayers = MenuMode / 10;
                    For(A, 1, numCharacters)
                    {
                        SavedChar[A] = blankPlayer;
                        SavedChar[A].Character = A;
                        SavedChar[A].State = 1;
                    }
                    Player[1].State = 1;
                    Player[1].Mount = 0;
                    Player[1].Character = 1;
                    Player[1].HeldBonus = 0;
                    Player[1].CanFly = false;
                    Player[1].CanFly2 = false;
                    Player[1].TailCount = 0;
                    Player[1].YoshiBlue = false;
                    Player[1].YoshiRed = false;
                    Player[1].YoshiYellow = false;
                    Player[1].Hearts = 0;
                    Player[2].State = 1;
                    Player[2].Mount = 0;
                    Player[2].Character = 2;
                    Player[2].HeldBonus = 0;
                    Player[2].CanFly = false;
                    Player[2].CanFly2 = false;
                    Player[2].TailCount = 0;
                    Player[2].YoshiBlue = false;
                    Player[2].YoshiRed = false;
                    Player[2].YoshiYellow = false;
                    Player[2].Hearts = 0;
                    if(numPlayers <= 2 && PlayerCharacter > 0) {
                        Player[1].Character = PlayerCharacter;
                        PlayerCharacter = 0;
                    }
                    if(numPlayers == 2 && PlayerCharacter2 > 0)
                    {
                        Player[2].Character = PlayerCharacter2;
                        PlayerCharacter2 = 0;
                    }
                    selSave = MenuCursor + 1;
                    numStars = 0;
                    Coins = 0;
                    Score = 0;
                    Lives = 3;
                    LevelSelect = true;
                    GameMenu = false;
                    frmMain.clearBuffer();
                    frmMain.repaint();
                    StopMusic();
                    DoEvents();
                    PGE_Delay(500);

                    ClearGame();
                    OpenWorld(SelectWorld[selWorld].WorldPath + SelectWorld[selWorld].WorldFile);
                    if(SaveSlot[selSave] >= 0)
                    {
                        if(!NoMap)
                            StartLevel.clear();
                        LoadGame();
                    }

                    if(WorldUnlock)
                    {
                        For(A, 1, numWorldPaths)
                        {
                            tempLocation = WorldPath[A].Location;
                            {
                                Location_t &l =tempLocation;
                                l.X = l.X + 4;
                                l.Y = l.Y + 4;
                                l.Width = l.Width - 8;
                                l.Height = l.Height - 8;
                            }

                            WorldPath[A].Active = true;

                            For(B, 1, numScenes)
                            {
                                if(CheckCollision(tempLocation, Scene[B].Location))
                                    Scene[B].Active = false;
                            }
                        }

                        For(A, 1, numWorldLevels)
                            WorldLevel[A].Active = true;
                    }

                    SetupPlayers();

                    if(!StartLevel.empty())
                    {
                        PlaySound(28);
                        SoundPause[26] = 200;
                        LevelSelect = false;

                        GameThing();
                        ClearLevel();

                        PGE_Delay(1000);
                        std::string levelPath = SelectWorld[selWorld].WorldPath + StartLevel;
                        if(!OpenLevel(levelPath))
                        {
                            MessageText = fmt::format_ne("ERROR: Can't open \"{0}\": file doesn't exist or corrupted.", StartLevel);
                            PauseGame(1);
                            ErrorQuit = true;
                        }
                    }
                    return;
                }
            }

            if(MenuMode < 100)
            {
                if(MenuCursor > 2) MenuCursor = 0;
                if(MenuCursor < 0) MenuCursor = 2;
            }
        }

        // Options
        else if(MenuMode == 3)
        {
            if(MenuCursorCanMove) {
                if(menuBackPress)
                {
                    MenuMode = 0;
                    MenuCursor = 3;
                    MenuCursorCanMove = false;
                    PlaySound(26);
                }
                else if(menuDoPress)
                {
//                    MenuCursorCanMove = False
                    MenuCursorCanMove = false;
//                    If MenuCursor = 0 Then
                    if(MenuCursor == 0) {
//                        MenuCursor = 0
                        MenuCursor = 0;
//                        MenuMode = 31
                        MenuMode = 31;
//                        PlaySound 26
                        PlaySound(26);
//                    ElseIf MenuCursor = 1 Then
                    } else if(MenuCursor == 1) {
//                        MenuCursor = 0
                        MenuCursor = 0;
//                        MenuMode = 32
                        MenuMode = 32;
//                        PlaySound 26
                        PlaySound(26);
//                    ElseIf MenuCursor = 2 Then
                    } else if(MenuCursor == 2) {
//                        PlaySound 29
                        PlaySound(29);
//                        ChangeScreen
                        ChangeScreen();
//                    ElseIf MenuCursor = 3 Then
                    } else if(MenuCursor == 3) {
//                        PlaySound 29
                        PlaySound(29);
//                        GameMenu = False
                        GameMenu = false;
//                        GameOutro = True
                        GameOutro = true;
//                        CreditChop = 300
                        CreditChop = 300;
//                        EndCredits = 0
                        EndCredits = 0;
//                        SetupCredits
                        SetupCredits();
//                    End If
                    }
//                End If
                }
//            End If
            }
//            If MenuMode = 3 Then
            if(MenuMode == 3) {
//                If MenuCursor > 3 Then MenuCursor = 0
                if(MenuCursor > 3)
                    MenuCursor = 0;
//                If MenuCursor < 0 Then MenuCursor = 3
                if(MenuCursor < 0)
                    MenuCursor = 3;
//            End If
            }

//        ElseIf MenuMode = 31 Or MenuMode = 32 Then 'Input Settings
        }

        // Input Settings
        else if(MenuMode == 31 || MenuMode == 32)
        {
            if(MenuCursorCanMove || !getNewJoystick)
            {
                if(getNewJoystick)
                {
                    KM_Key joyKey;
                    bool gotNewKey = PollJoystick(joyKey);

                    if(!JoyIsKeyDown(oldJumpJoy))
                    {
                        oldJumpJoy.type = -1;
                        if(gotNewKey)
                        {
                            PlaySound(29);
                            if(MenuCursor == 1)
                                conJoystick[MenuMode - 30].Up = joyKey;
                            else if(MenuCursor == 2)
                                conJoystick[MenuMode - 30].Down = joyKey;
                            else if(MenuCursor == 3)
                                conJoystick[MenuMode - 30].Left = joyKey;
                            else if(MenuCursor == 4)
                                conJoystick[MenuMode - 30].Right = joyKey;
                            else if(MenuCursor == 5)
                                conJoystick[MenuMode - 30].Run = joyKey;
                            else if(MenuCursor == 6)
                                conJoystick[MenuMode - 30].AltRun = joyKey;
                            else if(MenuCursor == 7)
                                conJoystick[MenuMode - 30].Jump = joyKey;
                            else if(MenuCursor == 8)
                                conJoystick[MenuMode - 30].AltJump = joyKey;
                            else if(MenuCursor == 9)
                                conJoystick[MenuMode - 30].Drop = joyKey;
                            else if(MenuCursor == 10)
                                conJoystick[MenuMode - 30].Start = joyKey;
                            getNewJoystick = false;
                            MenuCursorCanMove = false;
                        }
                        /*
                        else if(getKeyState(vbKeyEscape) == KEY_PRESSED) // would like to make timeout......
                        {
                            if(MenuCursor == 1)
                                conJoystick[MenuMode - 30].Up = lastJoyButton;
                            else if(MenuCursor == 2)
                                conJoystick[MenuMode - 30].Down = lastJoyButton;
                            else if(MenuCursor == 3)
                                conJoystick[MenuMode - 30].Left = lastJoyButton;
                            else if(MenuCursor == 4)
                                conJoystick[MenuMode - 30].Right = lastJoyButton;
                            else if(MenuCursor == 5)
                                conJoystick[MenuMode - 30].Run = lastJoyButton;
                            else if(MenuCursor == 6)
                                conJoystick[MenuMode - 30].AltRun = lastJoyButton;
                            else if(MenuCursor == 7)
                                conJoystick[MenuMode - 30].AltJump = lastJoyButton;
                            else if(MenuCursor == 8)
                                conJoystick[MenuMode - 30].Jump = lastJoyButton;
                            else if(MenuCursor == 9)
                                conJoystick[MenuMode - 30].Drop = lastJoyButton;
                            else if(MenuCursor == 10)
                                conJoystick[MenuMode - 30].Start = lastJoyButton;
                            getNewJoystick = false;
                            MenuCursorCanMove = false;
                        } */
                    }
                }
                else
                {
                    if(menuBackPress)
                    {
                        SaveConfig();
                        MenuCursor = MenuMode - 31;
                        MenuMode = 3;
                        MenuCursorCanMove = false;
                        PlaySound(26);
                    }
                    else if(menuDoPress)
                    {
                        if(MenuCursor == 1)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Up;
                            conJoystick[MenuMode - 30].Up.type = -1;
                        }
                        else if(MenuCursor == 2)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Down;
                            conJoystick[MenuMode - 30].Down.type = -1;
                        }
                        else if(MenuCursor == 3)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Left;
                            conJoystick[MenuMode - 30].Left.type = -1;
                        }
                        else if(MenuCursor == 4)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Right;
                            conJoystick[MenuMode - 30].Right.type = -1;
                        }
                        else if(MenuCursor == 5)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Run;
                            conJoystick[MenuMode - 30].Run.type = -1;
                        }
                        else if(MenuCursor == 6)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].AltRun;
                            conJoystick[MenuMode - 30].AltRun.type = -1;
                        }
                        else if(MenuCursor == 7)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Jump;
                            oldJumpJoy = conJoystick[MenuMode - 30].Jump;
                            conJoystick[MenuMode - 30].Jump.type = -1;
                        }
                        else if(MenuCursor == 8)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].AltJump;
                            conJoystick[MenuMode - 30].AltJump.type = -1;
                        }
                        else if(MenuCursor == 9)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Drop;
                            conJoystick[MenuMode - 30].Drop.type = -1;
                        }
                        else if(MenuCursor == 10)
                        {
                            lastJoyButton = conJoystick[MenuMode - 30].Start;
                            conJoystick[MenuMode - 30].Start.type = -1;
                        }
                        getNewJoystick = true;
                        MenuCursorCanMove = false;
                    }
                }
            }

//            If you haven't returned....
            if(MenuMode != 3)
            {
                if(MenuCursor > 10)
                    MenuCursor = 0;
                if(MenuCursor < 0)
                    MenuCursor = 10;
            }
//    End With ' Player.Controls
        }
    }


//'check for all characters blocked
//        If MenuMode = 100 Or MenuMode = 200 Or MenuMode = 300 Then
    if(MenuMode == 100 || MenuMode == 200 || MenuMode == 300)
    {
//            AllCharBlock = 0
        AllCharBlock = 0;
//            For A = 1 To numCharacters
        For(A, 1, numCharacters)
        {
//                If blockCharacter(A) = False Then
            if(!blockCharacter[A])
            {
//                    If AllCharBlock = 0 Then
                if(AllCharBlock == 0)
                {
//                        AllCharBlock = A
                    AllCharBlock = A;
//                    Else
                }
                else
                {
//                        AllCharBlock = 0
                    AllCharBlock = 0;
//                        Exit For
                    break;
//                    End If
                }
//                End If
            }
//            Next A
        }
//            If AllCharBlock > 0 Then
        if(AllCharBlock > 0)
        {
//                PlayerCharacter = AllCharBlock
            PlayerCharacter = AllCharBlock;
//                PlayerCharacter2 = AllCharBlock
            PlayerCharacter2 = AllCharBlock;
//                If MenuMode = 100 Then
            if(MenuMode == 100)
            {
//                    MenuMode = 10
                MenuMode = 10;
//                    MenuCursor = 0
                MenuCursor = 0;
//                ElseIf MenuMode = 200 Then
            } else if(MenuMode == 200) {
//                    MenuMode = 300
                MenuMode = 300;
//                    MenuCursor = PlayerCharacter2
                MenuCursor = PlayerCharacter2;
            } else {
//                Else
//                    MenuMode = 20
                MenuMode = 20;
//                    MenuCursor = 0
                MenuCursor = 0;
//                End If
            }
//            End If
//        End If
        }
    }



//    If CheckLiving = 0 Then
    if(CheckLiving() == 0)
    {
//        ShowLayer "Destroyed Blocks"
        ShowLayer("Destroyed Blocks");
//        For A = 1 To numNPCs
        For(A, 1, numNPCs)
        {
//            If NPC(A).DefaultType = 0 Then
            if(NPC[A].DefaultType == 0)
            {
//                If NPC(A).TimeLeft > 10 Then NPC(A).TimeLeft = 10
                if(NPC[A].TimeLeft > 10) NPC[A].TimeLeft = 10;
//            End If
            }
//        Next A
        }
//    End If
    }

//    For A = 1 To numPlayers
    For(A, 1, numPlayers)
    {
//        With Player(A) ' Player
        Player_t &p = Player[A];
//            If .TimeToLive > 0 Then
        if(p.TimeToLive > 0)
        {
//                .TimeToLive = 0
            p.TimeToLive = 0;
//                .Dead = True
            p.Dead = true;
//            End If
        }
//            .Controls.Down = False
        p.Controls.Down = false;
//            .Controls.Drop = False
        p.Controls.Drop = false;
//            .Controls.Right = True
        p.Controls.Right = true;
//            .Controls.Left = False
        p.Controls.Left = false;
//            .Controls.Run = True
        p.Controls.Run = true;
//            .Controls.Up = False
        p.Controls.Up = false;
//            .Controls.AltRun = False
        p.Controls.AltRun = false;
//            .Controls.AltJump = False
        p.Controls.AltJump = false;
//            If .Jump = 0 Or .Location.Y < level(0).Y + 200 Then .Controls.Jump = False
        if(p.Jump == 0 || p.Location.Y < level[0].Y + 200)
            p.Controls.Jump = false;
//            If .Location.SpeedX < 0.5 Then
        if(p.Location.SpeedX < 0.5)
        {
//                .Controls.Jump = True
            p.Controls.Jump = true;
//                If .Slope > 0 Or .StandingOnNPC > 0 Or .Location.SpeedY = 0 Then .CanJump = True
            if(p.Slope > 0 || p.StandingOnNPC > 0 || p.Location.SpeedY == 0.0)
                p.CanJump = true;
//            End If
        }
//            If .HoldingNPC = 0 Then
        if(p.HoldingNPC ==0)
        {
//                If (.State = 3 Or .State = 6 Or .State = 7) And Rnd * 100 > 90 Then
            if((p.State ==3 || p.State == 6 || p.State == 7) && (dRand() * 100.0) > 90.0)
            {
//                    If .FireBallCD = 0 And .RunRelease = False Then
                if(p.FireBallCD == 0 && !p.RunRelease) {
//                        .Controls.Run = False
                    p.Controls.Run = false;
//                    End If
                }
//                End If
            }
//                If (.State = 4 Or .State = 5) And .TailCount = 0 And .RunRelease = False Then
            if((p.State == 4 || p.State == 5) && p.TailCount == 0 && !p.RunRelease)
            {
//                    tempLocation.Width = 24
                tempLocation.Width = 24;
//                    tempLocation.Height = 20
                tempLocation.Height = 20;
//                    tempLocation.Y = .Location.Y + .Location.Height - 22
                tempLocation.Y = p.Location.Y + p.Location.Height - 22;
//                    tempLocation.X = .Location.X + .Location.Width
                tempLocation.X = p.Location.X + p.Location.Width;
//                    For B = 1 To numNPCs
                For(B, 1, numNPCs)
                {
//                        If NPC(B).Active = True And Not NPCIsABonus(NPC(B).Type) And _
//                           Not NPCWontHurt(NPC(B).Type) And NPC(B).HoldingPlayer = 0 Then
                    if(NPC[B].Active && !NPCIsABonus[NPC[B].Type] &&
                       !NPCWontHurt[NPC[B].Type] && NPC[B].HoldingPlayer == 0)
                    {
//                            If CheckCollision(tempLocation, NPC(B).Location) Then
                        if(CheckCollision(tempLocation, NPC[B].Location)) {
//                                .Controls.Run = False
                            p.Controls.Run = false;
//                            End If
                        }
//                        End If
                    }
//                    Next B
                }
//                End If
            }
//                If .StandingOnNPC > 0 Then
            if(p.StandingOnNPC > 0)
            {
//                    If NPCGrabFromTop(NPC(.StandingOnNPC).Type) = True Then
                if(NPCGrabFromTop[NPC[p.StandingOnNPC].Type])
                {
//                        .Controls.Down = True
                    p.Controls.Down = true;
//                        .Controls.Run = True
                    p.Controls.Run = true;
//                        .RunRelease = True
                    p.RunRelease = true;
//                    End If
                }
//                End If
            }
//            End If
        }
//            If .Character = 5 Then
        if(p.Character == 5)
        {
//                If .FireBallCD = 0 And .RunRelease = False Then
            if(p.FireBallCD == 0 && !p.RunRelease)
            {
//                    tempLocation.Width = 38 + .Location.SpeedX * 0.5
                tempLocation.Width = 38 + p.Location.SpeedX * 0.5;
//                    tempLocation.Height = .Location.Height - 8
                tempLocation.Height = p.Location.Height - 8;
//                    tempLocation.Y = .Location.Y + 4
                tempLocation.Y = p.Location.Y + 4;
//                    tempLocation.X = .Location.X + .Location.Width
                tempLocation.X = p.Location.X + p.Location.Width;
//                    For B = 1 To numNPCs
                For(B, 1, numNPCs)
                {
//                        If NPC(B).Active = True And Not NPCIsABonus(NPC(B).Type) And Not NPCWontHurt(NPC(B).Type) And NPC(B).HoldingPlayer = 0 Then
                    if(NPC[B].Active && !NPCIsABonus[NPC[B].Type] &&
                      !NPCWontHurt[NPC[B].Type] && NPC[B].HoldingPlayer == 0)
                    {
//                            If CheckCollision(tempLocation, NPC(B).Location) Then
                        if(CheckCollision(tempLocation, NPC[B].Location))
                        {
//                                .RunRelease = True
                            p.RunRelease = true;
//                                If NPC(B).Location.Y > .Location.Y + .Location.Height / 2 Then .Controls.Down = True
                            if(NPC[B].Location.Y > p.Location.Y + p.Location.Height / 2)
                                p.Controls.Down = true;
//                                Exit For
                            break;
//                            End If
                        }
//                        End If
                    }
//                    Next B
                }
//                End If
            }

//                If .Slope = 0 And .StandingOnNPC = 0 Then
            if(p.Slope == 0 && p.StandingOnNPC == 0)
            {
//                    If .Location.SpeedY < 0 Then
                if(p.Location.SpeedY < 0)
                {
//                        tempLocation.Width = 200
                    tempLocation.Width = 200;
//                        tempLocation.Height = .Location.Y - level(0).Y + .Location.Height
                    tempLocation.Height = p.Location.Y - level[0].Y + p.Location.Height;
//                        tempLocation.Y = level(0).Y
                    tempLocation.Y = level[0].Y;
//                        tempLocation.X = .Location.X
                    tempLocation.X = p.Location.X;
//                        For B = 1 To numNPCs
                    For(B, 1, numNPCs)
                    {
//                            If NPC(B).Active = True And Not NPCIsABonus(NPC(B).Type) And Not NPCWontHurt(NPC(B).Type) And NPC(B).HoldingPlayer = 0 Then
                        if(NPC[B].Active && !NPCIsABonus[NPC[B].Type] &&
                           !NPCWontHurt[NPC[B].Type] && NPC[B].HoldingPlayer == 0)
                        {
//                                If CheckCollision(tempLocation, NPC(B).Location) Then
                            if(CheckCollision(tempLocation, NPC[B].Location))
                            {
//                                    .Controls.Up = True
                                p.Controls.Up = true;
//                                    Exit For
                                break;
//                                End If
                            }
//                            End If
                        }
//                        Next B
                    }
//                    ElseIf .Location.SpeedY > 0 Then
                } else if(p.Location.SpeedY > 0) {
//                        tempLocation.Width = 200
                    tempLocation.Width = 200;
//                        tempLocation.Height = level(0).Height - .Location.Y
                    tempLocation.Height = level[0].Height - p.Location.Y;
//                        tempLocation.Y = .Location.Y
                    tempLocation.Y = p.Location.Y;
//                        tempLocation.X = .Location.X
                    tempLocation.X = p.Location.X;
//                        For B = 1 To numNPCs
                    For(B, 1, numNPCs)
                    {
//                            If NPC(B).Active = True And Not NPCIsABonus(NPC(B).Type) And Not NPCWontHurt(NPC(B).Type) And NPC(B).HoldingPlayer = 0 Then
                        if(NPC[B].Active && !NPCIsABonus[NPC[B].Type] &&
                           !NPCWontHurt[NPC[B].Type] && NPC[B].HoldingPlayer == 0)
                        {
//                                If CheckCollision(tempLocation, NPC(B).Location) Then
                            if(CheckCollision(tempLocation, NPC[B].Location))
                            {
//                                    .Controls.Down = True
                                p.Controls.Down = true;
//                                    Exit For
                                break;
//                                End If
                            }
//                            End If
                        }
//                        Next B
                    }
//                    End If
                }
//                End If
            }
//            End If
        }


//            If .Location.X < -vScreenX(1) - .Location.Width And Not -vScreenX(1) <= level(0).X Then .Dead = True
        if(p.Location.X < -vScreenX[1] - p.Location.Width && !(-vScreenX[1] <= level[0].X))
            p.Dead = true;
//            If .Location.X > -vScreenX(1) + 1000 Then .Dead = True
        if(p.Location.X > -vScreenX[1] + 1000)
            p.Dead = true;
//            If .Location.X > -vScreenX(1) + 600 And -vScreenX(1) + 850 < level(0).Width Then .Controls.Run = False
        if(p.Location.X > -vScreenX[1] + 600 && -vScreenX[1] + 850 < level[0].Width)
            p.Controls.Run = false;
//            If -vScreenX(1) <= level(0).X And (.Dead = True Or .TimeToLive > 0) Then
        if(-vScreenX[1] <= level[0].X && (p.Dead || p.TimeToLive > 0))
        {
//                .ForceHold = 65
            p.ForceHold = 65;
//                .State = Int(Rnd * 6) + 2
            p.State = (iRand() % 6) + 2;
//                .CanFly = False
            p.CanFly = false;
//                .CanFly2 = False
            p.CanFly2 = false;
//                .TailCount = 0
            p.TailCount = 0;
//                .Dead = False
            p.Dead = false;
//                .TimeToLive = 0
            p.TimeToLive = 0;
//                .Character = Int(Rnd * 5) + 1
            p.Character = (iRand() % 5) + 1;
//                If A >= 1 And A <= 5 Then .Character = A
            if(A >= 1 && A <= 5) p.Character = A;
//                .HeldBonus = 0
            p.HeldBonus = 0;
//                .Section = 0
            p.Section = 0;
//                .Mount = 0
            p.Mount = 0;
//                .MountType = 0
            p.MountType = 0;
//                .YoshiBlue = False
            p.YoshiBlue = false;
//                .YoshiRed = False
            p.YoshiRed = false;
//                .YoshiYellow = False
            p.YoshiYellow = false;
//                .YoshiNPC = 0
            p.YoshiNPC = 0;
//                .Wet = 0
            p.Wet = 0;
//                .WetFrame = False
            p.WetFrame = false;
//                .YoshiPlayer = 0
            p.YoshiPlayer = 0;
//                .Bumped = False
            p.Bumped = false;
//                .Bumped2 = 0
            p.Bumped2 = 0;
//                .Direction = 1
            p.Direction = 1;
//                .Dismount = 0
            p.Dismount = 0;
//                .Effect = 0
            p.Effect = 0;
//                .Effect2 = 0
            p.Effect2 = 0;
//                .FireBallCD = 0
            p.FireBallCD = 0;
//                .ForceHold = 0
            p.ForceHold = 0;
//                .Warp = 0
            p.Warp = 0;
//                .WarpCD = 0
            p.WarpCD = 0;
//                .GroundPound = False
            p.GroundPound = false;
//                .Immune = 0
            p.Immune = 0;
//                .Frame = 0
            p.Frame = 0;
//                .Slope = 0
            p.Slope = 0;
//                .Slide = False
            p.Slide = false;
//                .SpinJump = False
            p.SpinJump = false;
//                .FrameCount = 0
            p.FrameCount = 0;
//                .TailCount = 0
            p.TailCount = 0;
//                .Duck = False
            p.Duck = false;
//                .GroundPound = False
            p.GroundPound = false;
//                .Hearts = 3
            p.Hearts = 3;
//                PlayerFrame A
            PlayerFrame(A);
//                .Location.Height = Physics.PlayerHeight(.Character, .State)
            p.Location.Height = Physics.PlayerHeight[p.Character][p.State];
//                .Location.Width = Physics.PlayerWidth(.Character, .State)
            p.Location.Width = Physics.PlayerWidth[p.Character][p.State];
//                .Location.X = level(.Section).X - A * 48
            p.Location.X = level[p.Section].X - A * 48;
//                .Location.SpeedX = Physics.PlayerRunSpeed
            p.Location.SpeedX = double(Physics.PlayerRunSpeed);
//                .Location.Y = level(.Section).Height - .Location.Height - 33
            p.Location.Y = level[p.Section].Height - p.Location.Height - 33;
//                Do

            do
            {
//                    tempBool = True
                tempBool = true;
//                    For B = 1 To numBlock
                For(B, 1, numBlock)
                {
//                        If CheckCollision(.Location, Block(B).Location) = True Then
                    if(CheckCollision(p.Location, Block[B].Location))
                    {
//                            .Location.Y = Block(B).Location.Y - .Location.Height - 0.1
                        p.Location.Y = Block[B].Location.Y - p.Location.Height - 0.1;
//                            tempBool = False
                        tempBool = false;
//                        End If
                    }
//                    Next B
                }
//                Loop While tempBool = False
            } while(!tempBool);

//                If UnderWater(.Section) = False Then
            if(!UnderWater[p.Section])
            {
//                    If Int(Rnd * 25) + 1 = 25 Then
                if((iRand() % 25) + 1 == 25)
                {
//                        .Mount = 1
                    p.Mount = 1;
//                        .MountType = Int(Rnd * 3) + 1
                    p.MountType = (iRand() % 3) + 1;
//                        If .State = 1 Then
                    if(p.State == 1)
                    {
//                            .Location.Height = Physics.PlayerHeight(1, 2)
                        p.Location.Height = Physics.PlayerHeight[1][2];
//                            .Location.Y = .Location.Y - Physics.PlayerHeight(1, 2) + Physics.PlayerHeight(.Character, 1)
                        p.Location.Y = p.Location.Y - Physics.PlayerHeight[1][2] + Physics.PlayerHeight[p.Character][1];
//                        End If
                    }
//                    End If
                }
//                End If
            }

//                If .Mount = 0 And .Character <= 2 Then
            if(p.Mount == 0 && p.Character <= 2)
            {
//                    If Int(Rnd * 15) + 1 = 15 Then
                if((iRand() % 15) + 1 == 15)
                {
//                        .Mount = 3
                    p.Mount = 3;
//                        .MountType = Int(Rnd * 7) + 1
                    p.MountType = (iRand() % 7) + 1;
//                        .Location.Y = .Location.Y + .Location.Height
                    p.Location.Y = p.Location.Y + p.Location.Height;
//                        .Location.Height = Physics.PlayerHeight(2, 2)
                    p.Location.Height = Physics.PlayerHeight[2][2];
//                        .Location.Y = .Location.Y - .Location.Height - 0.01
                    p.Location.Y = p.Location.Y - p.Location.Height - 0.01;
//                    End If
                }
//                End If
            }

//                .CanFly = False
            p.CanFly = false;
//                .CanFly2 = False
            p.CanFly2 = false;
//                .RunCount = 0
            p.RunCount = 0;
//                If .Mount = 0 And .Character <> 5 Then
            if(p.Mount == 0 && p.Character != 5)
            {
//                    numNPCs = numNPCs + 1
                numNPCs += 1;
//                    .HoldingNPC = numNPCs
                p.HoldingNPC = numNPCs;
//                    .ForceHold = 120
                p.ForceHold = 120;
//                    With NPC(numNPCs)
                {
                    NPC_t &n = NPC[numNPCs];
//                        Do
                    do
                    {
//                            Do
                        do
                        {
//                                .Type = Int(Rnd * 286) + 1
                            n.Type = (iRand() % 286) + 1;
//                            Loop While .Type = 11 Or .Type = 16 Or .Type = 18 Or .Type = 15 Or .Type = 21 Or .Type = 12 Or .Type = 13 Or .Type = 30 Or .Type = 17 Or .Type = 31 Or .Type = 32 Or (.Type >= 37 And .Type <= 44) Or .Type = 46 Or .Type = 47 Or .Type = 50 Or (.Type >= 56 And .Type <= 70) Or .Type = 8 Or .Type = 74 Or .Type = 51 Or .Type = 52 Or .Type = 75 Or .Type = 34 Or NPCIsToad(.Type) Or NPCIsAnExit(.Type) Or NPCIsYoshi(.Type) Or (.Type >= 78 And .Type <= 87) Or .Type = 91 Or .Type = 93 Or (.Type >= 104 And .Type <= 108) Or .Type = 125 Or .Type = 133 Or (.Type >= 148 And .Type <= 151) Or .Type = 159 Or .Type = 160 Or .Type = 164 Or .Type = 168 Or (.Type >= 154 And .Type <= 157) Or .Type = 159 Or .Type = 160 Or .Type = 164 Or .Type = 165 Or .Type = 171 Or .Type = 178 Or .Type = 197 Or .Type = 180 Or .Type = 181 Or .Type = 190 Or .Type = 192 Or .Type = 196 Or .Type = 197 Or (UnderWater(0) = True And NPCIsBoot(.Type) = True) Or (.Type >= 198 And .Type <= 228) Or .Type = 234
                        } while(n.Type == 11 || n.Type == 16 || n.Type == 18 || n.Type == 15 ||
                                n.Type == 21 || n.Type == 12 || n.Type == 13 || n.Type == 30 ||
                                n.Type == 17 || n.Type == 31 || n.Type == 32 ||
                                (n.Type >= 37 && n.Type <= 44) || n.Type == 46 || n.Type == 47 ||
                                n.Type == 50 || (n.Type >= 56 && n.Type <= 70) || n.Type == 8 ||
                                n.Type == 74 || n.Type == 51 || n.Type == 52 || n.Type == 75 ||
                                n.Type == 34 || NPCIsToad[n.Type] || NPCIsAnExit[n.Type] ||
                                NPCIsYoshi[n.Type] || (n.Type >= 78 && n.Type <= 87) ||
                                n.Type == 91 || n.Type == 93 || (n.Type >= 104 && n.Type <= 108) ||
                                n.Type == 125 || n.Type == 133 || (n.Type >= 148 && n.Type <= 151) ||
                                n.Type == 159 || n.Type == 160 || n.Type == 164 || n.Type == 168 ||
                                (n.Type >= 154 && n.Type <= 157) || n.Type == 159 || n.Type == 160 ||
                                n.Type == 164 || n.Type == 165 || n.Type == 171 || n.Type == 178 ||
                                n.Type == 197 || n.Type == 180 || n.Type == 181 || n.Type == 190 ||
                                n.Type == 192 || n.Type == 196 || n.Type == 197 ||
                                (UnderWater[0] == true && NPCIsBoot[n.Type] == true) ||
                                (n.Type >= 198 && n.Type <= 228) || n.Type == 234);
//                        Loop While .Type = 235 Or .Type = 231 Or .Type = 179 Or .Type = 49 Or .Type = 237 Or .Type = 238 Or .Type = 239 Or .Type = 240 Or .Type = 245 Or .Type = 246 Or .Type = 248 Or .Type = 254 Or .Type = 255 Or .Type = 256 Or .Type = 257 Or .Type = 259 Or .Type = 260 Or .Type = 262 Or .Type = 263 Or .Type = 265 Or .Type = 266 Or (.Type >= 267 And .Type <= 272) Or .Type = 275 Or .Type = 276 Or (.Type >= 280 And .Type <= 284) Or .Type = 241
                    } while(n.Type == 235 || n.Type == 231 || n.Type == 179 || n.Type == 49 ||
                            n.Type == 237 || n.Type == 238 || n.Type == 239 || n.Type == 240 ||
                            n.Type == 245 || n.Type == 246 || n.Type == 248 || n.Type == 254 ||
                            n.Type == 255 || n.Type == 256 || n.Type == 257 || n.Type == 259 ||
                            n.Type == 260 || n.Type == 262 || n.Type == 263 || n.Type == 265 ||
                            n.Type == 266 || (n.Type >= 267 && n.Type <= 272) ||
                            n.Type == 275 || n.Type == 276 ||
                            (n.Type >= 280 && n.Type <= 284) || n.Type == 241);
//                        .Active = True
                    n.Active = true;
//                        .HoldingPlayer = A
                    n.HoldingPlayer = A;
//                        .Location.Height = NPCHeight(.Type)
                    n.Location.Height = NPCHeight[n.Type];
//                        .Location.Width = NPCWidth(.Type)
                    n.Location.Width = NPCWidth[n.Type];
//                        .Location.Y = Player(A).Location.Y  'level(.Section).Height + 1000
                    n.Location.Y = Player[A].Location.Y;  // level[n.Section].Height + 1000
//                        .Location.X = Player(A).Location.X 'level(.Section).X + 1000
                    n.Location.X = Player[A].Location.X; // level[n.Section].X + 1000
//                        .TimeLeft = 100
                    n.TimeLeft = 100;
//                        .Section = Player(A).Section
                    n.Section = Player[A].Section;
//                    End With
                }
//                End If
            }
//            ElseIf .Location.X > level(.Section).Width + 64 Then
        } else if(p.Location.X > level[p.Section].Width + 64) {
//                .Dead = True
            p.Dead = true;
//            End If
        }
//            If .WetFrame = True Then
        if(p.WetFrame)
        {
//                If .Location.SpeedY = 0 Or .Slope > 0 Then .CanJump = True
            if(p.Location.SpeedY == 0.0 || p.Slope > 0)
                p.CanJump = true;
//                If Rnd * 100 > 98 Or .Location.SpeedY = 0 Or .Slope > 0 Then .Controls.Jump = True
            if((dRand() * 100) > 98.0 || p.Location.SpeedY == 0.0 || p.Slope > 0)
                p.Controls.Jump = true;
//            End If
        }

        if((dRand() * 100) > 95.0 && Player[A].HoldingNPC == 0 && Player[A].Slide == false && Player[A].CanAltJump == true && Player[A].Mount == 0)
            Player[A].Controls.AltJump = true;
        if(dRand() * 1000 >= 999 && Player[A].CanFly2 == false)
            Player[A].Controls.Run = false;
        if(Player[A].Mount == 3 && dRand() * 100 >= 98 && Player[A].RunRelease == false)
            Player[A].Controls.Run = false;
        if(NPC[Player[A].HoldingNPC].Type == 22 || NPC[Player[A].HoldingNPC].Type == 49)
            Player[A].Controls.Run = true;
        if(Player[A].Slide == true && Player[A].CanJump == true)
        {
            if(Player[A].Location.SpeedX > -2 && Player[A].Location.SpeedX < 2)
                Player[A].Controls.Jump = true;
        }
        if(Player[A].CanFly == false && Player[A].CanFly2 == false && (Player[A].State == 4 || Player[A].State == 5) && Player[A].Slide == false)
            Player[A].Controls.Jump = true;
        if(Player[A].Quicksand > 0)
        {
            Player[A].CanJump = true;
            Player[A].Controls.Jump = true;
        }
        if(Player[A].FloatTime > 0 || (Player[A].CanFloat == true && Player[A].FloatRelease == true && Player[A].Jump == 0 && Player[A].Location.SpeedY > 0 && (dRand() * 100) > 95.0))
            Player[A].Controls.Jump = true;
        if(NPC[Player[A].HoldingNPC].Type == 13 && (dRand() * 100) > 95.0)
        {
            Player[A].Controls.Run = false;
            if(iRand() % 2 == 1)
                Player[A].Controls.Up = true;
            if(iRand() % 2 == 1)
                Player[A].Controls.Right = false;
        }

        if(Player[A].Slide == false && (Player[A].Slope > 0 || Player[A].StandingOnNPC > 0 || Player[A].Location.SpeedY == 0.0))
        {
            tempLocation = Player[A].Location;
            tempLocation.Width = 95;
            tempLocation.Height = tempLocation.Height - 1;
            for(auto B = 1; B <= numBlock; B++)
            {
                if(BlockSlope[Block[B].Type] == 0 && BlockIsSizable[Block[B].Type] == false && BlockOnlyHitspot1[Block[B].Type] == false && Block[B].Hidden == false)
                {
                    if(CheckCollision(Block[B].Location, tempLocation) == true)
                    {
                        Player[A].CanJump = true;
                        Player[A].SpinJump = false;
                        Player[A].Controls.Jump = true;
                        break;
                    }
                }
            }
        }
        if(Player[A].Slope == 0 && Player[A].Slide == false && Player[A].StandingOnNPC == 0 && (Player[A].Slope > 0 || Player[A].Location.SpeedY == 0.0))
        {
            tempBool = false;
            tempLocation = Player[A].Location;
            tempLocation.Width = 16;
            tempLocation.Height = 16;
            tempLocation.X = Player[A].Location.X + Player[A].Location.Width;
            tempLocation.Y = Player[A].Location.Y + Player[A].Location.Height;
            for(auto B = 1; B <= numBlock; B++)
            {
                if((BlockIsSizable[Block[B].Type] == false || Block[B].Location.Y > Player[A].Location.Y + Player[A].Location.Height - 1) && BlockOnlyHitspot1[Block[B].Type] == false && Block[B].Hidden == false)
                {
                    if(CheckCollision(Block[B].Location, tempLocation) == true)
                    {
                        tempBool = true;
                        break;
                    }
                }
            }
            if(tempBool == false)
            {
                Player[A].CanJump = true;
                Player[A].SpinJump = false;
                Player[A].Controls.Jump = true;
            }
        }
        if(Player[A].Character == 5 && Player[A].Controls.Jump == true)
        {
            Player[A].Controls.AltJump = true;
            // .Controls.Jump = False
        }
    }

//    If LevelMacro > 0 Then UpdateMacro
    if(LevelMacro > 0) UpdateMacro();
//    UpdateLayers
    UpdateLayers();
//    UpdateNPCs
    UpdateNPCs();
//    UpdateBlocks
    UpdateBlocks();
//    UpdateEffects
    UpdateEffects();
//    UpdatePlayer
    UpdatePlayer();
//    UpdateGraphics
    UpdateGraphics();
//    UpdateSound
    UpdateSound();
//    UpdateEvents
    UpdateEvents();


//    If MenuMouseDown = True Then
    if(MenuMouseDown)
    {
//        If Rnd * 100 > 40 Then
        if(dRand() * 100 > 40.0)
        {
//            NewEffect 80, newLoc(MenuMouseX - vScreenX(1), MenuMouseY - vScreenY(1))
            NewEffect(80, newLoc(MenuMouseX - vScreenX[1], MenuMouseY - vScreenY[1]));
//            Effect(numEffects).Location.SpeedX = Rnd * 4 - 2
            Effect[numEffects].Location.SpeedX = dRand() * 4 - 2;
//            Effect(numEffects).Location.SpeedY = Rnd * 4 - 2
            Effect[numEffects].Location.SpeedY = dRand() * 4 - 2;
//        End If
        }
//        For A = 1 To numNPCs
        For(A, 1, numNPCs)
        {
//            If NPC(A).Active = True Then
            if(NPC[A].Active)
            {
//                If CheckCollision(newLoc(MenuMouseX - vScreenX(1), MenuMouseY - vScreenY(1)), NPC(A).Location) = True Then
                if(CheckCollision(newLoc(MenuMouseX - vScreenX[1], MenuMouseY - vScreenY[1]), NPC[A].Location))
                {
//                    If NPCIsACoin(NPC(A).Type) = False Then
                    if(!NPCIsACoin[NPC[A].Type])
                    {
//                        NPC(0) = NPC(A)
                        NPC[0] = NPC[A];
//                        NPC(0).Location.X = MenuMouseX - vScreenX(1)
                        NPC[0].Location.X = MenuMouseX - vScreenX[1];
//                        NPC(0).Location.Y = MenuMouseY - vScreenY(1)
                        NPC[0].Location.Y = MenuMouseY - vScreenY[1];
//                        NPCHit A, 3, 0
                        NPCHit(A, 3, 0);
//                    Else
                    } else {
//                        NewEffect 78, NPC(A).Location
                        NewEffect(78, NPC[A].Location);
//                        NPC(A).Killed = 9
                        NPC[A].Killed = 9;
//                    End If
                    }
//                End If
                }
//            End If
            }
//        Next A
        }
//        For A = 1 To numBlock
        For(A, 1, numBlock)
        {
//            If Block(A).Hidden = False Then
            if(!Block[A].Hidden)
            {
//                If CheckCollision(newLoc(MenuMouseX - vScreenX(1), MenuMouseY - vScreenY(1)), Block(A).Location) = True Then
                if(CheckCollision(newLoc(MenuMouseX - vScreenX[1], MenuMouseY - vScreenY[1]), Block[A].Location))
                {
//                    BlockHit A
                    BlockHit(A);
//                    BlockHitHard A
                    BlockHitHard(A);
//                End If
                }
//            End If
            }
//        Next A
        }
//    End If
    }

//    MenuMouseMove = False
    MenuMouseMove = false;
//    MenuMouseClick = False
    MenuMouseClick = false;
//    If MenuMouseDown = True Then
    if(MenuMouseDown)
    {
//        MenuMouseRelease = False
        MenuMouseRelease = false;
//    Else
    }
    else
    {
//        MenuMouseRelease = True
        MenuMouseRelease = true;
//    End If
    }
//    MenuMouseBack = False
    MenuMouseBack = false;
}

void FindWorlds()
{
    NumSelectWorld = 0;

    std::vector<std::string> worldRoots;
    worldRoots.push_back(AppPath + "worlds/");
#if defined(__APPLE__) && defined(USE_BUNDLED_ASSETS)
    worldRoots.push_back(AppPathManager::userWorldsRootDir() + "/");
#endif

    SelectWorld.clear();
    SelectWorld.push_back(SelectWorld_t()); // Dummy entry

    for(auto worldsRoot : worldRoots)
    {
        DirMan episodes(worldsRoot);

        std::vector<std::string> dirs;
        std::vector<std::string> files;
        episodes.getListOfFolders(dirs);
        WorldData head;

        for(auto &dir : dirs)
        {
            std::string epDir = worldsRoot + dir + "/";
            DirMan episode(epDir);
            episode.getListOfFiles(files, {".wld", ".wldx"});

            for(std::string &fName : files)
            {
                std::string wPath = epDir + fName;
                if(FileFormats::OpenWorldFileHeader(wPath, head))
                {
                    SelectWorld_t w;
                    w.WorldName = head.EpisodeTitle;
                    head.charactersToS64();
                    w.WorldPath = epDir;
                    w.WorldFile = fName;
                    w.blockChar[1] = head.nocharacter1;
                    w.blockChar[2] = head.nocharacter2;
                    w.blockChar[3] = head.nocharacter3;
                    w.blockChar[4] = head.nocharacter4;
                    w.blockChar[5] = head.nocharacter5;

                    SelectWorld.push_back(w);
                }
            }
        }
    }

    NumSelectWorld = (SelectWorld.size() - 1);
}

void FindLevels()
{
    std::vector<std::string> battleRoots;
    battleRoots.push_back(AppPath + "battle/");
#if defined(__APPLE__) && defined(USE_BUNDLED_ASSETS)
    battleRoots.push_back(AppPathManager::userBattleRootDir() + "/");
#endif

    SelectWorld.clear();
    SelectWorld.push_back(SelectWorld_t()); // Dummy entry

    NumSelectWorld = 1;
    SelectWorld.push_back(SelectWorld_t()); // "random level" entry
    SelectWorld[1].WorldName = "Random Level";
    LevelData head;

    for(auto battleRoot : battleRoots)
    {
        std::vector<std::string> files;
        DirMan battleLvls(battleRoot);
        battleLvls.getListOfFiles(files, {".lvl", ".lvlx"});
        for(std::string &fName : files)
        {
            std::string wPath = battleRoot + fName;
            if(FileFormats::OpenLevelFileHeader(wPath, head))
            {
                SelectWorld_t w;
                w.WorldPath = battleRoot;
                w.WorldFile = fName;
                w.WorldName = head.LevelName;
                SelectWorld.push_back(w);
            }
        }
    }

    NumSelectWorld = (SelectWorld.size() - 1);
}

void FindSaves()
{
    std::string newInput = "";

    std::string episode = SelectWorld[selWorld].WorldPath;
    GamesaveData f;
    for(auto A = 1; A <= maxSaveSlots; A++)
    {
        SaveSlot[A] = -1;
        SaveStars[A] = 0;

        std::string saveFile = makeGameSavePath(episode,
                                                SelectWorld[selWorld].WorldFile,
                                                fmt::format_ne("save{0}.savx", A));
        std::string saveFileOld = episode + fmt::format_ne("save{0}.savx", A);
        std::string saveFileAncient = episode + fmt::format_ne("save{0}.sav", A);

        if((Files::fileExists(saveFile) && FileFormats::ReadExtendedSaveFileF(saveFile, f)) ||
           (Files::fileExists(saveFileOld) && FileFormats::ReadExtendedSaveFileF(saveFileOld, f)) ||
           (Files::fileExists(saveFileAncient) && FileFormats::ReadSMBX64SavFileF(saveFileAncient, f)))
        {
            int curActive = 0;
            int maxActive = 0;

            // "game beat flag"
            maxActive++;
            if(f.gameCompleted)
                curActive++;

            // How much paths open
            maxActive += f.visiblePaths.size();
            for(auto &p : f.visiblePaths)
            {
                if(p.second)
                    curActive++;
            }

            // How much levels opened
            maxActive += f.visibleLevels.size();
            for(auto &p : f.visibleLevels)
            {
                if(p.second)
                    curActive++;
            }

            // How many stars collected
            maxActive += (int(f.totalStars) * 4);
            SaveStars[A] = int(f.gottenStars.size());

            curActive += (SaveStars[A] * 4);

            if(maxActive > 0)
                SaveSlot[A] = int((float(curActive) / float(maxActive)) * 100);
            else
                SaveSlot[A] = 100;
        }
    }
}
