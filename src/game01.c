#include "genesis.h"

// include ressources
#include "sprite.h"

#define MAX_POSY            FIX32(192)
#define MIN_POSY            FIX32(0)
#define GRAVITY     		FIX32(0.16)
#define FLY_SPEED			FIX32(4.2L)
#define PHONE_MUMBER		2

static void updatePhysic();
static void updateAnim();
static void joyEvent(u16 joy, u16 changed, u16 state);

// position and movement variables
fix32 posX;
fix32 posY;
fix32 movX;
fix32 movY;

Sprite* chicken;

// enemies sprites
Sprite* phones[PHONE_MUMBER];
// enemies positions and move direction
fix32 phonesPosX[PHONE_MUMBER];
fix32 phonesPosY[PHONE_MUMBER];
fix32 phonesMovX[PHONE_MUMBER];
fix32 phonesMovY[PHONE_MUMBER];

int game01()
{
	u16 palette[64];
	u16 i;
	
	SPR_init();
	
	// init values
	posX = FIX32(48L);
    posY = MAX_POSY;
	movY = FIX32(0);
	
	phonesPosX[0] = FIX32(64);
	phonesPosY[0] = FIX32(64);
	phonesPosX[1] = FIX32(96);
	phonesPosY[1] = FIX32(64);
	
	// init chicken sprite
    chicken = SPR_addSprite(&chicken_sprite, fix32ToInt(posX), fix32ToInt(posY), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	memcpy(&palette[0], chicken_sprite.palette->data, 16 * 2);
	VDP_setPaletteColors(0, palette, 16);
	
	// init phone sprites
	for(i=0; i < PHONE_MUMBER; i++){
		phones[i] = SPR_addSprite(&phone_sprite, fix32ToInt(phonesPosX[i]), fix32ToInt(phonesPosY[i]), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	}
	
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

static void chickenAnimSpeed(){
	if (movY < 0){
		chicken->timer = 3;
	}
	else chicken->timer = 8;
}

static void updateAnim()
{
	SPR_setFrameChangeCallback(chicken, chickenAnimSpeed);
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