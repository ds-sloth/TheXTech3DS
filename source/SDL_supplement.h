typedef struct _SDL_Point {
    int x;
    int y;
} SDL_Point;

extern uint SDL_GetTicks(void);

const uint SDL_FLIP_NONE = 0;
const uint SDL_FLIP_HORIZONTAL = 1;
const uint SDL_FLIP_VERTICAL = 2; // bitwise combos

const char KEYNAMES[32][32] = {
 "A", "B", "SELECT", "START",
 "DRIGHT", "DLEFT", "DUP", "DDOWN",
 "R", "L", "X", "Y",
 "", "", "ZL", "ZR",
 "", "", "", "",
 "TOUCH", "", "", "",
 "CSTICK_RIGHT", "CSTICK_LEFT", "CSTICK_UP", "CSTICK_DOWN",
 "PAD_RIGHT", "PAD_LEFT", "PAD_UP", "PAD_DOWN"
};

enum KEYCODE {
 KEYCODE_A=1<<0,
 KEYCODE_B=1<<1,
 KEYCODE_SELECT=1<<2,
 KEYCODE_START=1<<3,
 KEYCODE_DRIGHT=1<<4,
 KEYCODE_DLEFT=1<<5,
 KEYCODE_DUP=1<<6,
 KEYCODE_DDOWN=1<<7,
 KEYCODE_R=1<<8,
 KEYCODE_L=1<<9,
 KEYCODE_X=1<<10,
 KEYCODE_Y=1<<11,
 KEYCODE_ZL=1<<14,
 KEYCODE_ZR=1<<15,

 KEYCODE_TOUCH=1<<20,
 KEYCODE_CSTICK_RIGHT=1<<24,
 KEYCODE_CSTICK_LEFT=1<<25,
 KEYCODE_CSTICK_UP=1<<26,
 KEYCODE_CSTICK_DOWN=1<<27,
 KEYCODE_PAD_RIGHT=1<<28,
 KEYCODE_PAD_LEFT=1<<29,
 KEYCODE_PAD_UP=1<<30,
 KEYCODE_PAD_DOWN=1<<31
};