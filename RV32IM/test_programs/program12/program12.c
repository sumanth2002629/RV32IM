#include "firmware.h"

int add(int x,int y)

void addition(void)
{
    int x=2;int y=3;
    int z = add(x,y);
}

int add(int x,int y)
{
    int z = x+y;
    return z;
}
