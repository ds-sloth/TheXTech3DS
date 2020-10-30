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

#include "game_main.h"
#include <AppPath/app_path.h>
#include <Utils/strings.h>
#include <Utils/files.h>
// #include <CrashHandler/crash_handler.h>
#include <cstring>
#include <pge_delay.h>

static void strToPlayerSetup(int player, const std::string &setupString)
{
    if(setupString.empty())
        return; // Do nothing

    std::vector<std::string> keys;

    auto &p = testPlayer[player];

    Strings::split(keys, setupString, ";");
    for(auto &k : keys)
    {
        if(k.empty())
            continue;
        if(k[0] == 'c') // Character
            p.Character = int(strtol(k.substr(1).c_str(), nullptr, 10));
        else if(k[0] == 's') // State
            p.State = int(strtol(k.substr(1).c_str(), nullptr, 10));
        else if(k[0] == 'm') // Mounts
            p.Mount = int(strtol(k.substr(1).c_str(), nullptr, 10));
        else if(k[0] == 't') // Mount types
            p.MountType = int(strtol(k.substr(1).c_str(), nullptr, 10));
    }

    if(p.Character < 1)
        p.Character = 1;
    if(p.Character > 5)
        p.Character = 5;

    if(p.State < 1)
        p.State = 1;
    if(p.State > 7)
        p.State = 7;


    switch(p.Mount)
    {
    default:
    case 0:
        p.Mount = 0;
        p.MountType = 0;
        break; // Rejected aliens
    case 1: case 2: case 3:
        break; // Allowed
    }

    switch(p.Mount)
    {
    case 1:
        if(p.MountType < 1 || p.MountType > 3) // Socks
            p.MountType = 1;
        break;
    default:
        break;
    case 3:
        if(p.MountType < 1 || p.MountType > 8) // Cat Llamas
            p.MountType = 1;
        break;
    }
}

extern "C"
int main(int argc, char**argv)
{
    CmdLineSetup_t setup;

    // CrashHandler::initSigs();

    AppPathManager::initAppPath();
    AppPath = AppPathManager::assetsRoot();

    OpenConfig_preSetup();

    setup.renderType = CmdLineSetup_t::RenderType(RenderMode);

    testPlayer.fill(Player_t());

    // set this flag before SDL initialization to allow game be quit when closing a window before a loading process will be completed
    GameIsActive = true;

    if(frmMain.initSDL(setup))
    {
        frmMain.freeSDL();
        return 1;
    }

    int ret = GameMain(setup);
    PGE_Delay(10000);
    frmMain.freeSDL();

    return ret;
}
