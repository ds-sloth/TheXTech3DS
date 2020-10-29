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

// #include <Logger/logger.h>

#include "globals.h"
#include "joystick.h"

#include "pseudo_vb.h"

#include <3ds.h>

/*
static void updateJoyKey(uint32_t keys, bool &key, const KM_Key &mkey)
{
    key = mkey.id & keys;
}*/

static bool bindJoystickKey(uint32_t keys, KM_Key &k)
{
    for(int i = 0; i < 32; i++)
    {
        if ((1<<i) & keys) {
            k.val = 1;
            k.id = i;
            k.type = (int)ConJoystick_t::JoyButton;
            return true;
        }
    }
    k.val = 0;
    k.id = 0;
    k.type = (int)ConJoystick_t::NoControl;
    return false;
}

void UpdateControls()
{
    uint32_t keys = hidKeysHeld();

    int A = 0;

    For(B, 1, numPlayers)
    {
        if(B == 2 && numPlayers == 2) {
            A = 2;
        } else {
            A = 1;
        }

        {
            Controls_t &c = Player[A].Controls;
            c.Down = conJoystick[A].Down.id & keys;
            c.Drop = conJoystick[A].Drop.id & keys;
            c.Jump = conJoystick[A].Jump.id & keys;
            c.Left = conJoystick[A].Left.id & keys;
            c.Right = conJoystick[A].Right.id & keys;
            c.Run = conJoystick[A].Run.id & keys;
            c.Start = conJoystick[A].Start.id & keys;
            c.Up = conJoystick[A].Up.id & keys;
            c.AltJump = conJoystick[A].AltJump.id & keys;
            c.AltRun = conJoystick[A].AltRun.id & keys;

            if(!Player[A].Controls.Start && !Player[A].Controls.Jump) {
                Player[A].UnStart = true;
            }

            if(c.Up && c.Down)
            {
                c.Up = false;
                c.Down = false;
            }

            if(c.Left && c.Right)
            {
                c.Left = false;
                c.Right = false;
            }

            if(!(Player[A].State == 5 && Player[A].Mount == 0) && c.AltRun)
                c.Run = true;
            if(ForcedControls && !GamePaused )
            {
                Player[A].Controls = ForcedControl;
            }
        }
    }

    if(SingleCoop > 0)
    {
        if(numPlayers == 1 || numPlayers > 2)
            SingleCoop = 0;

        Controls_t tempControls;
        if(SingleCoop == 1) {
            Player[2].Controls = tempControls;
        } else {
            Player[2].Controls = Player[1].Controls;
            Player[1].Controls = tempControls;
        }
    }

    For(A, 1, numPlayers)
    {
        {
            Player_t &p = Player[A];
            if(p.SpinJump)
            {
                if(p.SpinFrame < 4 || p.SpinFrame > 9) {
                    p.Direction = -1;
                } else {
                    p.Direction = 1;
                }
            }
        }
    }
}

bool PollJoystick(KM_Key &key)
{
    uint32_t keys = hidKeysDown();
    return bindJoystickKey(keys, key);
}

bool JoyIsKeyDown(const KM_Key &key)
{
    uint32_t keys = hidKeysDown();
    return key.id & keys;
}

bool getKeyState(KEYCODE kc)
{
    return kc & hidKeysDown();
}
