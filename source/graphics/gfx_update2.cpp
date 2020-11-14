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
#include "../player.h"
#include "../second_screen.h"

// draws GFX to screen when on the world map/world map editor
void UpdateGraphics2(bool skipRedraw)
{
    if(!GameIsActive)
        return;

    cycleCount = cycleCount + 1;
    if(FrameSkip == true)
    {
        if(SDL_GetTicks() + floor(1000 * (1 - (cycleCount / 63.0))) > GoalTime)
            return;
    }
    fpsCount = fpsCount + 1;
    graphics_times[0] = svcGetSystemTick();
    int A = 0;
    int B = 0;
    int Z = 0;
    int WPHeight = 0;
//    Location_t tempLocation;
    Z = 1;

    vScreen[Z].Left = 0;
    vScreen[Z].Top = 0;
    vScreen[Z].Width = ScreenW;
    vScreen[Z].Height = ScreenH;
    SpecialFrames();
    SceneFrame2[1] = SceneFrame2[1] + 1;
    if(SceneFrame2[1] >= 12)
    {
        SceneFrame2[1] = 0;
        SceneFrame[1] = SceneFrame[1] + 1;
        if(SceneFrame[1] >= 4)
            SceneFrame[1] = 0;
        SceneFrame[4] = SceneFrame[1];
        SceneFrame[5] = SceneFrame[1];
        SceneFrame[6] = SceneFrame[1];
        SceneFrame[9] = SceneFrame[1];
        SceneFrame[10] = SceneFrame[1];
        SceneFrame[12] = SceneFrame[1];
        SceneFrame[51] = SceneFrame[1];
        SceneFrame[52] = SceneFrame[1];
        SceneFrame[53] = SceneFrame[1];
        SceneFrame[54] = SceneFrame[1];
        SceneFrame[55] = SceneFrame[1];
    }
    SceneFrame2[27] = SceneFrame2[27] + 1;
    if(SceneFrame2[27] >= 8)
    {
        SceneFrame2[27] = 0;
        SceneFrame[27] = SceneFrame[27] + 1;
        if(SceneFrame[27] >= 12)
            SceneFrame[27] = 0;
        SceneFrame[28] = SceneFrame[27];
        SceneFrame[29] = SceneFrame[27];
        SceneFrame[30] = SceneFrame[27];
    }
    SceneFrame2[33] = SceneFrame2[33] + 1;
    if(SceneFrame2[33] >= 4)
    {
        SceneFrame2[33] = 0;
        SceneFrame[33] = SceneFrame[27] + 1;
        if(SceneFrame[33] >= 14)
            SceneFrame[33] = 0;
        SceneFrame[34] = SceneFrame[33];
    }
    SceneFrame2[62] = SceneFrame2[62] + 1;
    if(SceneFrame2[62] >= 8)
    {
        SceneFrame2[62] = 0;
        SceneFrame[62] = SceneFrame[62] + 1;
        if(SceneFrame[62] >= 8)
            SceneFrame[62] = 0;
        SceneFrame[63] = SceneFrame[62];
    }
    LevelFrame2[2] = LevelFrame2[2] + 1;
    if(LevelFrame2[2] >= 6)
    {
        LevelFrame2[2] = 0;
        LevelFrame[2] = LevelFrame[2] + 1;
        if(LevelFrame[2] >= 6)
            LevelFrame[2] = 0;
        LevelFrame[9] = LevelFrame[2];
        LevelFrame[13] = LevelFrame[2];
        LevelFrame[14] = LevelFrame[2];
        LevelFrame[15] = LevelFrame[2];
        LevelFrame[31] = LevelFrame[2];
        LevelFrame[32] = LevelFrame[2];
    }
    LevelFrame2[8] = LevelFrame2[8] + 1;
    if(LevelFrame2[8] >= 12)
    {
        LevelFrame2[8] = 0;
        LevelFrame[8] = LevelFrame[8] + 1;
        if(LevelFrame[8] >= 4)
            LevelFrame[8] = 0;
    }
    LevelFrame2[12] = LevelFrame2[12] + 1;
    if(LevelFrame2[12] >= 8)
    {
        LevelFrame2[12] = 0;
        LevelFrame[12] = LevelFrame[12] + 1;
        if(LevelFrame[12] >= 2)
            LevelFrame[12] = 0;
    }
    LevelFrame2[25] = LevelFrame2[25] + 1;
    if(LevelFrame2[25] >= 8)
    {
        LevelFrame2[25] = 0;
        LevelFrame[25] = LevelFrame[25] + 1;
        if(LevelFrame[25] >= 4)
            LevelFrame[25] = 0;
        LevelFrame[26] = LevelFrame[25];
    }
    TileFrame2[14] = TileFrame2[14] + 1;
    if(TileFrame2[14] >= 14)
    {
        TileFrame2[14] = 0;
        TileFrame[14] = TileFrame[14] + 1;
        if(TileFrame[14] >= 4)
            TileFrame[14] = 0;
        TileFrame[27] = TileFrame[14];
        TileFrame[241] = TileFrame[14];
    }

    graphics_times[1] = svcGetSystemTick();
    frmMain.initDraw(0);

    // Draw the map!!
    frmMain.setLayer(0);
    for(A = 1; A <= numTiles; A++)
    {
        if(vScreenCollision2(1, Tile[A].Location) == true)
        {
            frmMain.renderTexture(vScreenX[Z] + Tile[A].Location.X,
                                  vScreenY[Z] + Tile[A].Location.Y,
                                  Tile[A].Location.Width,
                                  Tile[A].Location.Height,
                                  GFXTileBMP[Tile[A].Type], 0, TileHeight[Tile[A].Type] * TileFrame[Tile[A].Type]);
        }
    }
    graphics_times[2] = svcGetSystemTick();
    frmMain.setLayer(1);
    for(A = 1; A <= numScenes; A++)
    {
        if(vScreenCollision2(1, Scene[A].Location) == true && Scene[A].Active == true)
        {
            frmMain.renderTexture(vScreenX[Z] + Scene[A].Location.X,
                                  vScreenY[Z] + Scene[A].Location.Y,
                                  Scene[A].Location.Width, Scene[A].Location.Height,
                                  GFXSceneBMP[Scene[A].Type], 0, SceneHeight[Scene[A].Type] * SceneFrame[Scene[A].Type]);
        }
    }
    graphics_times[3] = svcGetSystemTick();
    for(A = 1; A <= numWorldPaths; A++)
    {
        if(vScreenCollision2(1, WorldPath[A].Location) == true && WorldPath[A].Active == true)
        {
            frmMain.renderTexture(vScreenX[Z] + WorldPath[A].Location.X,
                                  vScreenY[Z] + WorldPath[A].Location.Y,
                                  WorldPath[A].Location.Width, WorldPath[A].Location.Height,
                                  GFXPathBMP[WorldPath[A].Type], 0, 0);
        }
    }
    for(A = 1; A <= numWorldLevels; A++)
    {
        if(vScreenCollision2(1, WorldLevel[A].Location) == true && WorldLevel[A].Active == true)
        {
            if(WorldLevel[A].Path == true)
            {
                frmMain.renderTexture(vScreenX[Z] + WorldLevel[A].Location.X,
                                      vScreenY[Z] + WorldLevel[A].Location.Y,
                                      WorldLevel[A].Location.Width,
                                      WorldLevel[A].Location.Height,
                                      GFXLevelBMP[0], 0, 0);
            }
            if(WorldLevel[A].Path2 == true)
            {
                frmMain.renderTexture(vScreenX[Z] + WorldLevel[A].Location.X - 16,
                                      vScreenY[Z] + 8 + WorldLevel[A].Location.Y,
                                      64, 32,
                                      GFXLevelBMP[29], 0, 0);
            }
            if(GFXLevelBig[WorldLevel[A].Type] == true)
            {
                frmMain.renderTexture(vScreenX[Z] + WorldLevel[A].Location.X - (GFXLevelWidth[WorldLevel[A].Type] - 32) / 2.0,
                                      vScreenY[Z] + WorldLevel[A].Location.Y - GFXLevelHeight[WorldLevel[A].Type] + 32,
                                      GFXLevelWidth[WorldLevel[A].Type], GFXLevelHeight[WorldLevel[A].Type],
                                      GFXLevelBMP[WorldLevel[A].Type], 0, 32 * LevelFrame[WorldLevel[A].Type]);
            }
            else
            {
                frmMain.renderTexture(vScreenX[Z] + WorldLevel[A].Location.X,
                                      vScreenY[Z] + WorldLevel[A].Location.Y,
                                      WorldLevel[A].Location.Width, WorldLevel[A].Location.Height,
                                      GFXLevelBMP[WorldLevel[A].Type], 0, 32 * LevelFrame[WorldLevel[A].Type]);
            }
        }
    }

    graphics_times[4] = svcGetSystemTick();
    frmMain.setLayer(2);
    if(WorldPlayer[1].Type == 0)
        WorldPlayer[1].Type = 1;
    if(Player[1].Character == 1)
        WorldPlayer[1].Type = 1;
    if(Player[1].Character == 2)
        WorldPlayer[1].Type = 2;
    if(Player[1].Character == 3)
        WorldPlayer[1].Type = 3;
    if(Player[1].Character == 4)
        WorldPlayer[1].Type = 4;
    if(Player[1].Character == 5)
        WorldPlayer[1].Type = 5;
    if(WorldPlayer[1].Type == 3)
        WPHeight = 44;
    else if(WorldPlayer[1].Type == 4)
        WPHeight = 40;
    else
        WPHeight = 32;
    frmMain.renderTexture(vScreenX[Z] + WorldPlayer[1].Location.X,
                      vScreenY[Z] + WorldPlayer[1].Location.Y - 10 + WorldPlayer[1].Location.Height - WPHeight,
                      WorldPlayer[1].Location.Width, WPHeight,
                      GFXPlayerBMP[WorldPlayer[1].Type], 0, WPHeight * WorldPlayer[1].Frame);

    graphics_times[5] = svcGetSystemTick();
    // still on layer 2.
    // render background...
    // top...
    frmMain.renderTexture(0, 0, ScreenW-66, 130, GFX.Interface[4], 0, 0);
    // left
    frmMain.renderTexture(0, 130, 66, ScreenH-130-66, GFX.Interface[4], 0, 130);
    // right
    frmMain.renderTexture(ScreenW-66, 0, 66, ScreenH-66, GFX.Interface[4], GFX.Interface[4].w-66, 0);
    // bottom
    frmMain.renderTexture(0, ScreenH-66, ScreenW-66, 66, GFX.Interface[4], 0, GFX.Interface[4].h-66);
    // bottom-right
    frmMain.renderTexture(ScreenW-66, ScreenH-66, 66, 66, GFX.Interface[4], GFX.Interface[4].w-66, GFX.Interface[4].h-66);
    frmMain.setLayer(3);
    for(A = 1; A <= numPlayers; A++)
    {
        Player[A].Direction = -1;
        Player[A].Location.SpeedY = 0;
        Player[A].Location.SpeedX = -1;
        Player[A].Controls.Left = false;
        Player[A].Controls.Right = false;
        if(Player[A].Duck == true)
            UnDuck(A);
        PlayerFrame(A);
        if(Player[A].Mount == 3)
        {
            if(Player[A].MountType == 0)
                Player[A].MountType = 1;
            B = Player[A].MountType;
            // Yoshi's Body
            frmMain.renderTexture(32 + (48 * A) + Player[A].YoshiBX, 124 - Player[A].Location.Height + Player[A].YoshiBY,
                                  32, 32, GFXYoshiBBMP[B], 0, 32 * Player[A].YoshiBFrame, ShadowMode);

            // Yoshi's Head
            frmMain.renderTexture(32 + (48 * A) + Player[A].YoshiTX,
                                  124 - Player[A].Location.Height + Player[A].YoshiTY,
                                  32, 32, GFXYoshiTBMP[B], 0, 32 * Player[A].YoshiTFrame, ShadowMode);
        }
        if(Player[A].Character == 1)
        {
            if(Player[A].Mount == 0 || Player[A].Mount == 3)
            {
                frmMain.renderTexture(32 + (48 * A) + MarioFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)],
                                      124 - Player[A].Location.Height + MarioFrameY[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY,
                                      99, 99, GFXMarioBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction),
                                      pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
            }
            else if(Player[A].Mount == 1)
            {
                frmMain.renderTexture(32 + (48 * A) + MarioFrameX[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)],
                                      124 - Player[A].Location.Height + MarioFrameY[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)],
                                      99, Player[A].Location.Height - 26,
                                      GFXMarioBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction),
                                      pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);

                frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16, 124 - 30, 32, 32,
                                      GFX.Boot[Player[A].MountType], 0, 32 * Player[A].MountFrame, ShadowMode);

                if(Player[A].MountType == 3)
                {
                    Player[A].YoshiWingsFrameCount = Player[A].YoshiWingsFrameCount + 1;
                    Player[A].YoshiWingsFrame = 0;
                    if(Player[A].YoshiWingsFrameCount <= 12)
                        Player[A].YoshiWingsFrame = 1;
                    else if(Player[A].YoshiWingsFrameCount >= 24)
                        Player[A].YoshiWingsFrameCount = 0;

                    frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16 + 20, 124 - 30 - 10, 32, 32,
                                          GFX.YoshiWings, 0, 0 + 32 * Player[A].YoshiWingsFrame);
                }
            }
        }
        else if(Player[A].Character == 2)
        {
            if(Player[A].Mount == 0 || Player[A].Mount == 3)
            {
                frmMain.renderTexture(32 + (48 * A) + LuigiFrameX[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)],
                                      124 - Player[A].Location.Height + LuigiFrameY[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY, 99, 99,
                                      GFXLuigiBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction),
                                      pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
            }
            else if(Player[A].Mount == 1)
            {
                frmMain.renderTexture(32 + (48 * A) + LuigiFrameX[(Player[A].State * 100) +
                                        (Player[A].Frame * Player[A].Direction)],
                                      124 - Player[A].Location.Height +
                                        LuigiFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)],
                                      99, Player[A].Location.Height - 24,
                                      GFXLuigiBMP[Player[A].State],
                                      pfrX(100 + Player[A].Frame * Player[A].Direction),
                                      pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);

                frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16, 124 - 30, 32, 32, GFX.Boot[Player[A].MountType], 0, 32 * Player[A].MountFrame, ShadowMode);

                if(Player[A].MountType == 3)
                {
                    Player[A].YoshiWingsFrameCount = Player[A].YoshiWingsFrameCount + 1;
                    Player[A].YoshiWingsFrame = 0;
                    if(Player[A].YoshiWingsFrameCount <= 12)
                        Player[A].YoshiWingsFrame = 1;
                    else if(Player[A].YoshiWingsFrameCount >= 24)
                        Player[A].YoshiWingsFrameCount = 0;

                    frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16 + 20, 124 - 30 - 10, 32, 32, GFX.YoshiWings, 0, 0 + 32 * Player[A].YoshiWingsFrame, ShadowMode);
                }
            }
        }
        else if(Player[A].Character == 3)
        {
            if(Player[A].Mount == 0 || Player[A].Mount == 3)
            {
                frmMain.renderTexture(32 + (48 * A) + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 124 - Player[A].Location.Height + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY, 99, 99, GFXPeachBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
            }
            else if(Player[A].Mount == 1)
            {
                frmMain.renderTexture(32 + (48 * A) + PeachFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 124 - Player[A].Location.Height + PeachFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 99, Player[A].Location.Height - 24, GFXPeachBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);

                frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16, 124 - 30, 32, 32, GFX.Boot[Player[A].MountType], 0, 32 * Player[A].MountFrame, ShadowMode);

                if(Player[A].MountType == 3)
                {
                    Player[A].YoshiWingsFrameCount = Player[A].YoshiWingsFrameCount + 1;
                    Player[A].YoshiWingsFrame = 0;
                    if(Player[A].YoshiWingsFrameCount <= 12)
                        Player[A].YoshiWingsFrame = 1;
                    else if(Player[A].YoshiWingsFrameCount >= 24)
                        Player[A].YoshiWingsFrameCount = 0;

                    frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16 + 20, 124 - 30 - 10, 32, 32, GFX.YoshiWings, 0, 0 + 32 * Player[A].YoshiWingsFrame, ShadowMode);
                }
            }
        }
        else if(Player[A].Character == 4)
        {
            if(Player[A].Mount == 0 || Player[A].Mount == 3)
            {
                frmMain.renderTexture(32 + (48 * A) + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 124 - Player[A].Location.Height + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)] + Player[A].MountOffsetY, 99, 99, GFXToadBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
            }
            else if(Player[A].Mount == 1)
            {
                if(Player[A].State == 1)
                {
                    frmMain.renderTexture(32 + (48 * A) + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 6 + 124 - Player[A].Location.Height + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 99, Player[A].Location.Height - 24, GFXToadBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                }
                else
                {
                    frmMain.renderTexture(32 + (48 * A) + ToadFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 124 - Player[A].Location.Height + ToadFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 99, Player[A].Location.Height - 24, GFXToadBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
                }
                frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16, 124 - 30, 32, 32, GFX.Boot[Player[A].MountType], 0, 32 * Player[A].MountFrame, ShadowMode);

                if(Player[A].MountType == 3)
                {
                    Player[A].YoshiWingsFrameCount = Player[A].YoshiWingsFrameCount + 1;
                    Player[A].YoshiWingsFrame = 0;
                    if(Player[A].YoshiWingsFrameCount <= 12)
                        Player[A].YoshiWingsFrame = 1;
                    else if(Player[A].YoshiWingsFrameCount >= 24)
                        Player[A].YoshiWingsFrameCount = 0;
                    frmMain.renderTexture(32 + (48 * A) + Player[A].Location.Width / 2.0 - 16 + 20, 124 - 30 - 10, 32, 32, GFX.YoshiWings, 0, 0 + 32 * Player[A].YoshiWingsFrame, ShadowMode);
                }
            }
        }
        else if(Player[A].Character == 5)
        {
            frmMain.renderTexture(32 + (48 * A) + LinkFrameX[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 124 - Player[A].Location.Height + LinkFrameY[(Player[A].State * 100) + (Player[A].Frame * Player[A].Direction)], 99, 99, GFXLinkBMP[Player[A].State], pfrX(100 + Player[A].Frame * Player[A].Direction), pfrY(100 + Player[A].Frame * Player[A].Direction), ShadowMode);
        }
    }
    A = numPlayers + 1;
    // Print lives on the screen
    frmMain.renderTexture(32 + (48 * A), 126 - GFX.Interface[3].h, GFX.Interface[3].w, GFX.Interface[3].h, GFX.Interface[3], 0, 0);
    frmMain.renderTexture(32 + (48 * A) + 40, 128 - GFX.Interface[3].h, GFX.Interface[1].w, GFX.Interface[1].h, GFX.Interface[1], 0, 0);

    SuperPrint(std::to_string(int(Lives)), 1, 32 + (48 * A) + 62, 112);
    // Print coins on the screen
    if(Player[1].Character == 5)
    {
        frmMain.renderTexture(32 + (48 * A) + 16, 88, GFX.Interface[2].w, GFX.Interface[2].h, GFX.Interface[6], 0, 0);
    }
    else
    {
        frmMain.renderTexture(32 + (48 * A) + 16, 88, GFX.Interface[2].w, GFX.Interface[2].h, GFX.Interface[2], 0, 0);
    }
    frmMain.renderTexture(32 + (48 * A) + 40, 90, GFX.Interface[1].w, GFX.Interface[1].h, GFX.Interface[1], 0, 0);

    SuperPrint(std::to_string(Coins), 1, 32 + (48 * A) + 62, 90);
    // Print stars on the screen
    if(numStars > 0)
    {
        frmMain.renderTexture(32 + (48 * A) + 16, 66, GFX.Interface[5].w, GFX.Interface[5].h, GFX.Interface[5], 0, 0);
        frmMain.renderTexture(32 + (48 * A) + 40, 68, GFX.Interface[1].w, GFX.Interface[1].h, GFX.Interface[1], 0, 0);
        SuperPrint(std::to_string(numStars), 1, 32 + (48 * A) + 62, 68);
    }
    // Print the level's name
    if(WorldPlayer[1].LevelName != "")
    {
        SuperPrint(WorldPlayer[1].LevelName, 2, 32 + (48 * A) + 116, 109);
    }

    // still on layer 3
    if(GamePaused == true)
    {
        frmMain.renderRect(ScreenW/2 - 190, ScreenH/2 - 100, 380, 200, 0, 0, 0);
        if(Cheater == false)
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
    if(PrintFPS > 0)
    {
        SuperPrint(std::to_string(int(PrintFPS)), 1, 8, 8);
    }
    graphics_times[11] = svcGetSystemTick();

    graphics_times[12] = svcGetSystemTick();
    drawSecondScreen2();
    graphics_times[13] = graphics_times[12]; // so we can report this frame's time to draw second screen next frame
    graphics_times[14] = svcGetSystemTick();

    if (!skipRedraw)
        frmMain.finalizeDraw();
    graphics_times[15] = svcGetSystemTick();
}
