// https://github.com/0branch/boron/blob/master/support/well512.h

#ifndef WELL512_H
#define WELL512_H

#ifdef __sun__
#include <inttypes.h>
#else
#include <stdint.h>
#endif

#define WELL512_STATE_SIZE  16

typedef struct
{
    uint32_t wi;
    uint32_t wstate[ WELL512_STATE_SIZE ];
}
Well512;


#ifdef __cplusplus
extern "C" {
#endif
    
    void well512_init( Well512* ws, uint32_t seed );
    uint32_t well512_genU32( Well512* ws );
    
#ifdef __cplusplus
}
#endif


/*
 Generate a random number on [0,1)-real-interval.
 (uint32_t divided by 2^32)
 */
#define well512_genReal(ws)    (well512_genU32(ws) * (1.0 / 4294967296.0))


void well512_init( Well512* ws, uint32_t seed )
{
    int i;
    uint32_t prev;
    uint32_t* wstate = ws->wstate;
    
    ws->wi = 0;
    wstate[0] = seed;
    for( i = 1; i < WELL512_STATE_SIZE; ++i )
    {
        prev = wstate[i-1];
        wstate[i] = (1812433253 * (prev ^ (prev >> 30)) + i);
    }
}


/*
 Generates a random number on [0,0xffffffff]-interval
 */
uint32_t well512_genU32( Well512* ws )
{
    uint32_t a, b, c, z0;
    uint32_t* wstate = ws->wstate;
    uint32_t wi = ws->wi;
    
#define MAT0(v,t)   (v^(v<<t))
    
    a = wstate[wi];
    c = wstate[(wi + 13) & 15];
    b = MAT0(a,16) ^ MAT0(c,15);
    
    c = wstate[(wi + 9) & 15];
    c ^= (c>>11);
    
    wstate[wi] = a = b ^ c;
    ws->wi = wi = (wi + 15) & 15;
    z0 = wstate[wi];
    wstate[wi] = MAT0(z0,2) ^ MAT0(b,18) ^ (c<<28) ^
    (a ^ ((a << 5) & 0xDA442D24));
    
    return wstate[wi];
}

#endif /* WELL512_H */
