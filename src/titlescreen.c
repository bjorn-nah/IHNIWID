#include "genesis.h"

bool loop_screen;

void myJoyHandler( u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)
		{
			loop_screen = FALSE;
		}
	}
}

int titlescreen()
{
    VDP_drawText("I have no idea what I'm doing", 6, 12);

	JOY_init();
	JOY_setEventHandler( &myJoyHandler );
	loop_screen = TRUE;
	
    while(loop_screen)
    {
        // nothing to do here
        // ...

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }
	VDP_clearText( 6, 12,	29); 	

    return 0;
}