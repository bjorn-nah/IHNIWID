#include "genesis.h"

// include ressources
#include "sprite.h"

// physic variables
fix32 flySpeed;
fix32 gravity;

// position and movement variables
fix32 posX;
fix32 posY;
fix32 movX;
fix32 movY;

Sprite* chicken;

int game01()
{
	u16 palette[64];
	
	SPR_init();
	
	posX = FIX32(48L);
    posY = FIX32(48L);
	
	// init chicken sprite
    chicken = SPR_addSprite(&chicken_sprite, fix32ToInt(posX), fix32ToInt(posY), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	memcpy(&palette[0], chicken_sprite.palette->data, 16 * 2);
	VDP_setPaletteColors(0, palette, 16);
	
    while(TRUE)
    {
		SPR_update();

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}