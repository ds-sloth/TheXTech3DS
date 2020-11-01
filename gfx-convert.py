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
        if os.path.isfile(t3xfn) or os.path.isfile(destfn) and not REDO: continue
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
                os.system(f'convert "{rfn}" "{altmaskfn_gif}" -alpha Off -compose CopyOpacity -composite -channel a -negate +channel -sample 50% "{bmpfn}"')
            elif os.path.isfile(altmaskfn_png):
                os.system(f'convert "{rfn}" "{altmaskfn_png}" -alpha On -compose CopyOpacity -composite -sample 50% "{bmpfn}"')
            else:
                os.system(f'convert -sample 50% "{rfn}" "{bmpfn}"')
        elif fn.endswith('.db'):
            continue
        else:
            # shutil.copy(rfn, destfn)
            continue
        if PREVIEW:
            pvwfn = t3xfn+'.bmp'
            os.system(f'tex3ds "{bmpfn}" -f rgba8888 -o "{t3xfn}" -p "{pvwfn}"')
        else:
            if os.system(f'tex3ds "{bmpfn}" -f rgba8888 -o "{t3xfn}"'):
                print(f"It didn't work and {t3xfn} is missing.")
            os.remove(bmpfn)
