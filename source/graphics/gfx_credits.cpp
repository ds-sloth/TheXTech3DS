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
#include "../sound.h"
#include "../game_main.h"
#include "../pseudo_vb.h"


void DoCredits()
{
    int A = 0;
    if(GameMenu == true)
        return;

    int CC = (int)CreditChop;
    if (CC & 1) CC -= 1;

    frmMain.renderRect(0, 0, ScreenW, CC, 0, 0, 0);
    frmMain.renderRect(0, ScreenH - CC, ScreenW, CC, 0, 0, 0);

    for(A = 1; A <= numCredits; A++)
    {
        // Printing lines of credits
        if(Credit[A].Location.Y <= 600 && Credit[A].Location.Y + Credit[A].Location.Height >= 0)
        {
            int loc = (int)(Credit[A].Location.Y);
            if (loc & 1) loc -= 1;
            SuperPrint(Credit[A].Text, 4, (float)(Credit[A].Location.X), loc);
        }
    }
}
