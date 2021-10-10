#include "genesis.h"

int game01()
{
    VDP_drawText("Soon, a game here.", 6, 2);
	
    while(TRUE)
    {
        // nothing to do here
        // ...

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}