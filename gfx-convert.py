#!/usr/bin/python3

# this is a simple script

import os
import sys
import shutil

PREVIEW = False
REDO = False
datadir = sys.argv[1]
graphicsdir = os.path.join(datadir, 'graphics')
outdir = sys.argv[2]

for dirpath, _, files in os.walk(datadir, topdown=True):
    outpath = outdir+dirpath[len(datadir):]
    os.makedirs(outpath, exist_ok=True)
    for fn in files:
        rfn = os.path.join(dirpath, fn)
        if not os.path.isfile(rfn): continue
        destfn = os.path.join(outpath, fn)
        bmpfn = os.path.join(outpath, fn[:-3]+'bmp')
        t3xfn = os.path.join(outpath, fn[:-3]+'png')
        if not REDO and (os.path.isfile(destfn) or ((fn.endswith('.gif') or fn.endswith('.png')) and os.path.isfile(t3xfn))): continue
        print(rfn)
        if fn.endswith('.png'):
            os.system(f'convert -sample 50% "{rfn}" "{bmpfn}"')
        elif fn.endswith('m.gif') and os.path.isfile(rfn[:-5]+'.gif'):
            continue
        elif fn.endswith('.gif'):
            maskfn = rfn[:-4]+'m.gif'
            ftype = fn[:fn.rfind('-')]
            altmaskfn_gif = os.path.join(graphicsdir, ftype, fn[:-4]+'m.gif')
            altmaskfn_png = os.path.join(graphicsdir, ftype, fn[:-4]+'.png')
            if os.path.isfile(maskfn):
                os.system(f'convert "{rfn}" "{maskfn}" -alpha Off -compose CopyOpacity -composite -channel a -negate +channel -sample 50% "{bmpfn}"')
            elif os.path.isfile(altmaskfn_gif):
                if os.popen(f'identify -format "%[fx:w*2],%[fx:h*2]" "{rfn}"').read() == os.popen(f'identify -format "%[fx:w*2],%[fx:h*2]" "{altmaskfn_gif}"').read():
                    os.system(f'convert "{rfn}" "{altmaskfn_gif}" -alpha Off -compose CopyOpacity -composite -channel a -negate +channel -sample 50% "{bmpfn}"')
                else:
                    os.system(f'convert -sample 50% "{rfn}" "{bmpfn}"')
            elif os.path.isfile(altmaskfn_png):
                if os.popen(f'identify -format "%[fx:w*2],%[fx:h*2]" "{rfn}"').read() == os.popen(f'identify -format "%[fx:w*2],%[fx:h*2]" "{altmaskfn_png}"').read():
                    os.system(f'convert "{rfn}" "{altmaskfn_png}" -alpha On -compose CopyOpacity -composite -sample 50% "{bmpfn}"')
                else:
                    os.system(f'convert -sample 50% "{rfn}" "{bmpfn}"')
            else:
                os.system(f'convert -sample 50% "{rfn}" "{bmpfn}"')
        elif fn.endswith('.db'):
            continue
        elif fn.endswith('.ogg'): continue
        elif fn.endswith('.mp3'):
            os.system(f'ffmpeg -i "{rfn}" -aq 1 "{destfn}.ogg"')
            shutil.move(destfn+'.ogg', destfn)
            continue
        else:
            if rfn.endswith('npc-26.txt'): print('!!')
            shutil.copy(rfn, destfn)
            continue
        w, h = os.popen(f'identify -format "%[fx:w*2],%[fx:h*2]" "{bmpfn}"').read().split(',')
        open(t3xfn+'.size','w').write(f'{w:>4}\n{h:>4}\n')
        t3xfns = [t3xfn]
        bmpfns = [bmpfn]
        if int(h) > 2048:
            os.system(f'convert "{bmpfn}" -crop {w}x1024 "{bmpfn}%d.bmp"')
            os.remove(bmpfn)
            shutil.move(bmpfn+'0.bmp', bmpfn) #???
            t3xfns.append(t3xfn+'1')
            bmpfns.append(bmpfn+'1.bmp')
            if int(h) > 4096:
                t3xfns.append(t3xfn+'2')
                bmpfns.append(bmpfn+'2.bmp')
        for t3xfn_i, bmpfn_i in zip(t3xfns, bmpfns):
            if PREVIEW:
                pvwfn_i = t3xfn_i+'.bmp'
                os.system(f'tex3ds "{bmpfn_i}" -f rgba8888 -o "{t3xfn_i}" -p "{pvwfn_i}"')
            else:
                if os.system(f'tex3ds "{bmpfn_i}" -f rgba8888 -o "{t3xfn_i}"'):
                    print(f"It didn't work and {t3xfn_i} is missing. (Size: {w}x{h})")
                os.remove(bmpfn_i)
