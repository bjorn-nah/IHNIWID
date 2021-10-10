#include "genesis.h"

// extern
int titlescreen();
int game01();

int main(bool hardReset)
{

    while(TRUE)
    {
        titlescreen();
		game01();
    }

    return 0;
}
