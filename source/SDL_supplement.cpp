#include <ctime>
uint SDL_GetTicks(void)
{
    return clock() / 1000;
}
