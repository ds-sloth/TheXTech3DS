#!/usr/bin/python3
# this is a simple script
import os
import sys

PREVIEW = False

dir = sys.argv[1]
outdir = os.path.join('out', dir)
if not os.path.isdir(outdir):
    os.makedirs(outdir)
for fn in os.listdir(dir):
    rfn = os.path.join(dir, fn)
    if not os.path.isfile(rfn): continue
    bmpfn = os.path.join(outdir, fn[:-3]+'bmp')
    t3xfn = os.path.join(outdir, fn[:-3]+'png')
    if rfn.endswith('.png'):
        os.system(f'convert -sample 50% {rfn} {bmpfn}')
    # figure out the gif and mask situation next
    elif rfn.endswith('.gif'):
        continue
    else:
        continue
    if PREVIEW:
        pvwfn = t3xfn+'.bmp'
        os.system(f'tex3ds {bmpfn} -f rgba5551 -o {t3xfn} -p {pvwfn}')
    else:
        os.system(f'tex3ds {bmpfn} -f rgba5551 -o {t3xfn}')
        os.remove(bmpfn)
