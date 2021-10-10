#include "genesis.h"


int titlescreen()
{
    VDP_drawText("I have no idea what I'm doing", 6, 12);

    while(TRUE)
    {
        // nothing to do here
        // ...

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}
