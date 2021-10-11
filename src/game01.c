#include "genesis.h"

// include ressources
#include "sprite.h"

#define MAX_POSY            FIX32(192)
#define MIN_POSY            FIX32(0)
#define GRAVITY     		FIX32(0.16)
#define FLY_SPEED			FIX32(4.2L)

static void updatePhysic();
static void updateAnim();
static void joyEvent(u16 joy, u16 changed, u16 state);

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
	
	// init values
	posX = FIX32(48L);
    posY = MAX_POSY;
	movY = FIX32(0);
	
	// init chicken sprite
    chicken = SPR_addSprite(&chicken_sprite, fix32ToInt(posX), fix32ToInt(posY), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	memcpy(&palette[0], chicken_sprite.palette->data, 16 * 2);
	VDP_setPaletteColors(0, palette, 16);
	
	JOY_setEventHandler(joyEvent);
	
    while(TRUE)
    {
		
		updatePhysic();
		updateAnim();
		
		SPR_update();

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}

static void updatePhysic()
{
	posY += movY;
	if (movY)
    {
        if (posY > MAX_POSY)
        {
            posY = MAX_POSY;
            movY = 0;
        }
        else if (posY < MIN_POSY)
        {
            movY = -movY;
        }
        else movY += GRAVITY;
    }
	SPR_setPosition(chicken, fix32ToInt(posX), fix32ToInt(posY));
}

static void updateAnim()
{
	/*
	if (movY < 0){
		chicken->timer = 5;
	}
	else chicken->timer = 10;
	*/
}

static void joyEvent(u16 joy, u16 changed, u16 state)
{

    if (state & (BUTTON_A | BUTTON_B | BUTTON_C))
    {
        if (posY > MIN_POSY)
        {
            movY = -FLY_SPEED;
        }
    }
}