/*
    Single file synth + demo song
    Copyright (C) 2005 - 2021 Alexander Zolotov <nightradio@gmail.com>
    WarmPlace.ru
	https://github.com/pixicoder/PS
    MIT license

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to 
deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.    
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include "SDL2/SDL.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define sleep(sec) Sleep(1000*(sec))
#else
    #include <unistd.h> //sleep()
#endif

#define SAMPLE_RATE 24000
#define one_tick_size (int)((SAMPLE_RATE)/7)
#define chan_num (int)8 //Number of channels (synth tracks)

int srate = SAMPLE_RATE;
int bufsize = 128; //amount of RL channels (actual buffer is double than that)
int exit_request = 0;
int fadeout = 0;
float fadeout_vol = 1;
float volume = 1.2;
int timer = 0; //0...one_tick_size
int tick = 0; //0...pattern size (number of lines)
int cur_pattern = 0; //0...number of patterns
float dc_sl = 0, dc_sr = 0;
float dc_psl = 0, dc_psr = 0;
float max_vol = 1;
int out_mode = 0; //0 - SDL; 1 - WAV EXPORT;
const char* export_file_name = NULL;

int myrand()
{
    static int seed = 0;

    seed *= 13;
    seed ^= 0x55555555;

    return seed;
}

uint8_t notes[] =
//line0: ch0 note, ch1 note, ch2 note ...
//line1: ...
//...
{
    100, 0, 130, 0, 0, 0, 0, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    255, 0, 0,   0, 0, 0, 0, 0
};

uint8_t notes2[] = 
{
    100, 0, 130, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0,
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 134, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 140, 0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    20, 0, 122, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    255, 0, 0, 0, 0, 0, 0, 0
};

uint8_t notes2_prehat[] = 
{
    100, 0, 130, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0,
    10, 0, 130, 0, 0, 0, 0, 0,
    200, 0, 134, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 0, 0,
    10, 0, 137, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    200, 100, 130, 0, 0, 0, 0, 0,
    100, 0, 140, 0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 0, 0,
    200, 100, 142, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    20, 0, 122, 0, 0, 0, 0, 0,
    10, 100, 0, 0, 0, 0, 0, 0,
    255, 0, 0, 0, 0, 0, 0, 0
};

uint8_t notes3[] = 
{
    100, 0, 131, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 130, 0, 0, 0, 0, 0,
    10, 0, 131, 0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 0, 0,
    10, 0, 137, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    100, 0, 140, 0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    20, 0, 128, 0, 0, 0, 0, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    255, 0, 0, 0, 0, 0, 0, 0
};

uint8_t notes_hat_first[] = 
{
    100, 0, 130, 99,   1, 0, 254, 254,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 138, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first2[] = 
{
    100, 0, 130, 99,   0, 140, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     2, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first3[] = 
{
    100, 0, 130, 99,   0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 142, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat[] = 
{
    100, 0, 130, 99,   0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes2_hat[] = 
{
    100, 0, 130, 94,   0, 142, 0, 0,
    10, 1, 0, 94,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 94,    0, 0, 0, 0,
    200, 100, 134, 94, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       2, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 94, 0, 0, 0, 0, 
    100, 1, 140, 94,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 94, 0, 0, 0, 0, 
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 122, 94,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes3_hat[] = 
{
    100, 0, 131, 92,   0, 145, 0, 0,
    10, 1, 0, 92,      0, 0, 0, 0,
    100, 2, 130, 128,  0, 0, 0, 0,
    10, 1, 131, 92,    0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0, 
    10, 4, 0, 128,     0, 0, 0, 0,
    20, 2, 0, 0,       1, 116, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0,
    100, 1, 140, 92,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 92, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 92,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes3_hat2[] = 
{
    100, 0, 131, 92,   0, 0, 0, 0,
    10, 1, 0, 92,      0, 0, 0, 0,
    100, 2, 130, 128,  0, 0, 0, 0,
    10, 1, 131, 92,    0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0, 
    10, 4, 0, 128,     0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0,
    100, 1, 140, 92,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 92, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 92,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes3_hat3[] = 
{
    100, 0, 131, 92,   0, 143, 0, 0,
    10, 1, 0, 92,      0, 0, 0, 0,
    100, 2, 130, 128,  0, 0, 0, 0,
    10, 1, 131, 92,    0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0, 
    10, 4, 0, 128,     0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0,
    100, 1, 140, 92,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 92, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 92,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes3_hat4[] = 
{
    100, 0, 131, 92,   0, 142, 0, 0,
    10, 1, 0, 92,      0, 0, 0, 0,
    100, 2, 130, 128,  0, 0, 0, 0,
    10, 1, 131, 92,    0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0, 
    10, 4, 0, 128,     0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 92, 0, 0, 0, 0,
    100, 1, 140, 92,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 92, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 92,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first_dual[] = 
{
    100, 0, 131, 95,   0, 0, 135, 0,
    10, 1, 0, 95,      0, 0, 0, 0,
    100, 2, 130, 0,    0, 0, 0, 0,
    10, 1, 131, 95,    0, 0, 0, 0,
    200, 100, 135, 95, 0, 135, 0, 0, 
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0,
    100, 1, 140, 95,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 95, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 95,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,

    100, 0, 131, 95,   0, 0, 135, 137,
    10, 1, 0, 95,      0, 0, 0, 0,
    100, 2, 130, 0,    0, 0, 0, 0,
    10, 1, 131, 95,    0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0, 
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0,
    100, 1, 140, 95,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 95, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 95,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,

    100, 0, 131, 95,   0, 0, 135, 140,
    10, 1, 0, 95,      0, 0, 0, 0,
    100, 2, 130, 0,    0, 0, 0, 0,
    10, 1, 131, 95,    0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0, 
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0,
    100, 1, 140, 95,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 95, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 95,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,

    100, 0, 131, 95,   2, 159, 135, 142,
    10, 1, 0, 95,      0, 0, 0, 0,
    100, 2, 130, 0,    0, 0, 0, 0,
    10, 1, 131, 95,    0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0, 
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0,
    100, 1, 140, 95,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 95, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 128, 95,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,

    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first2_dual[] = 
{
    100, 0, 130, 99,   0, 140, 135, 142,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 0, 0, 0,
    10, 4, 137, 0,     2, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first3_dual[] = 
{
    100, 0, 130, 99,   0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    100, 2, 128, 0,    0, 0, 0, 0,
    10, 1, 130, 99,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 0,       0, 142, 0, 0,
    10, 4, 137, 0,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 99, 0, 0, 0, 0,
    100, 1, 138, 99,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 99, 0, 0, 0, 0,
    10, 1, 0, 0,       0, 0, 0, 0,
    20, 2, 123, 99,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_hat_first_dual2[] = 
{
    100, 0, 130, 95,   0, 0, 131, 138,
    10, 1, 0, 95,      0, 0, 0, 0,
    100, 2, 128, 119,    0, 0, 0, 0,
    10, 1, 130, 95,    0, 0, 0, 0,
    200, 100, 135, 95, 0, 0, 0, 0,
    10, 4, 0, 0,       0, 0, 0, 0,
    20, 2, 0, 131,       0, 138, 0, 0,
    10, 4, 137, 119,     0, 0, 0, 0,
    100, 0, 0, 0,      0, 0, 0, 0,
    200, 100, 130, 95, 0, 0, 0, 0,
    100, 1, 138, 95,   0, 0, 0, 0,
    20, 3, 0, 0,       0, 0, 0, 0,
    200, 100, 142, 95, 0, 0, 0, 0,
    10, 1, 0, 119,       0, 0, 0, 0,
    20, 2, 123, 95,    0, 0, 0, 0,
    10, 60, 0, 0,      0, 0, 0, 0,
    255, 1, 0, 0,      0, 0, 0, 0
};

uint8_t notes_end[] = 
{
    100, 0, 130, 0, 0, 0, 130, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 0, 0, 128, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 125, 0, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 118, 0, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 0,   0, 0, 0, 0, 0,
    5, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0,   0, 0, 0, 0, 0,
    0, 0, 0,    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0,    0, 0, 0, 0, 0,
    2, 0, 0,    0, 0, 0, 0, 0,
    4, 0, 0,  0, 0, 0, 0, 0,

    255, 0, 0,   0, 0, 0, 0, 0
};

uint8_t notes_preend[] = 
{
    100, 0, 130, 0, 0, 0, 130, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 0, 0, 128, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 125, 0, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    100, 0, 130, 0, 0, 118, 0, 0, 
    10, 0, 0,    0, 0, 0, 0, 0,
    100, 0, 128, 0, 0, 0, 0, 0, 
    10, 0, 130,  0, 0, 0, 0, 0,
    200, 0, 135, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    10, 0, 137,  0, 0, 0, 0, 0,
    100, 0, 0,   0, 0, 0, 0, 0,
    200, 0, 130, 0, 0, 0, 0, 0,
    100, 0, 138, 0, 0, 0, 0, 0,
    20, 0, 0,    0, 0, 0, 0, 0,
    200, 0, 142, 0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,
    20, 0, 123,  0, 0, 0, 0, 0,
    10, 0, 0,    0, 0, 0, 0, 0,

    255, 0, 0,   0, 0, 0, 0, 0
};

//=-=-=-=

uint8_t part2[] = 
{
    100, 253, 0, 97,    4, 0, 135, 253,
//    100, 253, 0, 97,    4, 0, 0, 0,
    10, 1, 0, 99,     0, 0, 0, 0,
    100, 2, 0, 99,    0, 0, 0, 0,
    10, 1, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 97,     0, 0, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    100, 0, 0, 99,    0, 0, 0, 0,
    200, 100, 0, 97,  0, 0, 0, 0,
    100, 1, 0, 99,    0, 0, 0, 0,
    20, 3, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 1, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 99,     0, 0, 0, 0,
    10, 60, 0, 99,    0, 0, 0, 0,

    100, 0, 000, 97,   1, 0, 135, 0,
//    100, 0, 000, 97,   1, 0, 0, 0,
    10, 1, 000, 99,    0, 0, 0, 0,
    100, 2, 00, 99,    0, 0, 0, 0,
    10, 1, 000, 97,    0, 0, 0, 0,
    200, 100, 135, 99, 0, 0, 0, 0,
    10, 4, 0, 99,       0, 0, 0, 0,
    20, 2, 00, 97,     0, 0, 0, 0,
    10, 4, 00, 99,     0, 0, 0, 0,
    100, 0, 0, 99,      0, 0, 0, 0,
    200, 100, 000, 97, 0, 140, 0, 0,
    100, 1, 000, 99,   0, 0, 0, 0,
    20, 3, 00, 97,     0, 0, 0, 0,
    200, 100, 000, 99, 0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    20, 2, 000, 99,    0, 0, 0, 0,
    10, 60, 000, 99,   0, 0, 0, 0,

    100, 0, 0, 93,   0, 138, 135, 142,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 95,    0, 0, 0, 0,
    10, 1, 0, 93,    0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,     0, 0, 0, 0,
    10, 4, 0, 95,     0, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    100, 0, 0, 93,   0, 0, 135, 140,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 0,    0, 0, 0, 0,
    10, 1, 00, 95,    0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 95,     0, 0, 0, 0,
    10, 4, 0, 93,     2, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    255, 1, 99, 0,     0, 0, 0, 0
};

uint8_t part3[] = 
{
    100, 0, 0, 97,    3, 0, 135, 139,
    10, 1, 0, 99,     0, 0, 0, 0,
    100, 2, 0, 99,    0, 0, 0, 0,
    10, 1, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 97,     0, 139, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    100, 0, 0, 99,    0, 0, 0, 0,
    200, 100, 0, 97,  0, 0, 0, 0,
    100, 1, 0, 99,    0, 0, 0, 0,
    20, 3, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 1, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 99,     0, 0, 0, 0,
    10, 60, 0, 99,    0, 0, 0, 0,

    100, 0, 000, 97,   1, 0, 135, 0,
    10, 1, 000, 99,    0, 0, 0, 0,
    100, 2, 00, 99,    0, 0, 0, 0,
    10, 1, 000, 97,    0, 0, 0, 0,
    200, 100, 0, 99,   0, 0, 0, 0,
    10, 4, 0, 99,       0, 0, 0, 0,
    20, 2, 00, 97,     0, 0, 0, 0,
    10, 4, 00, 99,     0, 0, 0, 0,
    100, 0, 0, 99,      0, 0, 0, 0,
    200, 100, 000, 97, 0, 140, 0, 0,
    100, 1, 000, 99,   0, 0, 0, 0,
    20, 3, 00, 97,     0, 0, 0, 0,
    200, 100, 000, 99, 0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    20, 2, 000, 99,    0, 0, 0, 0,
    10, 60, 000, 99,   0, 0, 0, 0,

    100, 0, 0, 93,   0, 138, 135, 142,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 95,    0, 0, 0, 0,
    10, 1, 0, 93,    0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,     0, 0, 0, 0,
    10, 4, 0, 95,     0, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    100, 0, 0, 93,   0, 0, 135, 140,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 0,    0, 0, 0, 0,
    10, 1, 00, 95,    0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 95,     0, 0, 0, 0,
    10, 4, 0, 93,     2, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    255, 1, 99, 0,     0, 0, 0, 0

};

uint8_t part4[] = 
{
    100, 254, 0, 97,    3, 0, 135, 139,
    10, 1, 0, 99,     0, 0, 0, 0,
    100, 2, 0, 99,    0, 0, 0, 0,
    10, 1, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 97,     0, 139, 0, 0,
    10, 4, 0, 99,     0, 0, 0, 0,
    100, 0, 0, 99,    0, 0, 0, 0,
    200, 100, 0, 97,  0, 0, 0, 0,
    100, 1, 0, 99,    0, 0, 0, 0,
    20, 3, 0, 97,     0, 0, 0, 0,
    200, 100, 0, 99,  0, 0, 0, 0,
    10, 1, 0, 99,     0, 0, 0, 0,
    20, 2, 0, 99,     0, 0, 0, 0,
    10, 60, 0, 99,    0, 0, 0, 0,

    100, 0, 000, 97,   1, 0, 135, 0,
    10, 1, 000, 99,    0, 0, 0, 0,
    100, 2, 00, 99,    0, 0, 0, 0,
    10, 1, 000, 97,    0, 0, 0, 0,
    200, 100, 0, 99,   0, 0, 0, 0,
    10, 4, 0, 99,       0, 0, 0, 0,
    20, 2, 00, 97,     0, 0, 0, 0,
    10, 4, 00, 99,     0, 0, 0, 0,
    100, 0, 0, 99,      0, 0, 0, 0,
    200, 100, 000, 97, 0, 140, 0, 0,
    100, 1, 000, 99,   0, 0, 0, 0,
    20, 3, 00, 97,     0, 0, 0, 0,
    200, 100, 000, 99, 0, 0, 0, 0,
    10, 1, 0, 99,      0, 0, 0, 0,
    20, 2, 000, 99,    0, 0, 0, 0,
    10, 60, 000, 99,   0, 0, 0, 0,

    100, 0, 0, 93,   0, 138, 135, 142,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 95,    0, 0, 0, 0,
    10, 1, 0, 93,    0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,     0, 0, 0, 0,
    10, 4, 0, 95,     0, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 95, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    100, 0, 0, 93,   0, 0, 135, 140,
    10, 1, 0, 95,    0, 0, 0, 0,
    100, 2, 0, 0,    0, 0, 0, 0,
    10, 1, 00, 95,    0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 4, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 95,     0, 0, 0, 0,
    10, 4, 0, 93,     2, 0, 0, 0,
    100, 0, 0, 95,      0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    100, 1, 0, 95,   0, 0, 0, 0,
    20, 3, 0, 95,     0, 0, 0, 0,
    200, 100, 0, 93, 0, 0, 0, 0,
    10, 1, 0, 95,       0, 0, 0, 0,
    20, 2, 0, 93,    0, 0, 0, 0,
    10, 60, 0, 95,    0, 0, 0, 0,

    255, 1, 99, 0,     0, 0, 0, 0

};

uint8_t part5[] = 
{
    0, 0, 0, 0,   5, 0, 254, 254,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,

    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,
    0, 0, 0, 0,   0, 0, 253, 253,

    255, 1, 99, 0,     0, 0, 0, 0
};

uint8_t* patterns[] = 
{
    notes, notes, notes, notes,
    notes2, notes2, notes2, notes2,
    notes3, notes3, notes3, notes3,
    notes2, notes2, notes2, notes2_prehat,
    notes_hat_first, notes_hat, notes_hat_first2, notes_hat_first3,
    notes3_hat, notes3_hat2, notes3_hat3, notes3_hat4,
    notes_hat_first_dual,
    notes_preend,
    notes_hat_first, notes_hat, notes_hat_first2, notes_hat_first3,
    notes3_hat, notes3_hat2, notes3_hat3, notes3_hat4,
    notes_hat_first_dual,
    notes_end,

    part2,
    part3,
    part4,
    part3,
    part4,
    part3,
    part4,
    part3,
    part4,
    part3,
    part4,
    part3,
    part4,
    part3,
    0
};

enum {
    SYNTH_DRUM = 1,
    SYNTH_HAT,
    SYNTH_BASS,
    SYNTH_BASS_TINY,
    SYNTH_ACID_BASS,
    SYNTH_EFFECT,
    SYNTH_POLY,
    SYNTH_PAD
};

float drum_timer[ chan_num ];
float drum_timer2[ chan_num ];
float drum_timer3[ chan_num ];

float hat_timer[ chan_num ];
float hat_old1[ chan_num ];
float hat_old2[ chan_num ];

float bass_freq[ chan_num ];
float bass_tdelta[ chan_num ];
float bass_delta[ chan_num ];
float bass_timer[ chan_num ];

float effect_timer[ chan_num ];
float effect_timer2[ chan_num ];
int effect_lowfilter[ chan_num ];

int syn[ chan_num ] = { SYNTH_DRUM, SYNTH_HAT, SYNTH_BASS, SYNTH_BASS_TINY, SYNTH_EFFECT, SYNTH_POLY, SYNTH_PAD, SYNTH_PAD };

#define echo_size ( one_tick_size * 3 )
float echo_buf1[ echo_size * 2 ];
float echo_buf2[ echo_size * 2 ];
int echo_ptr = 0;
#define reverb 16
int slow_reverb[ reverb ];

#define max_flanger_size 100
float flanger_buf1[ max_flanger_size * 3 * 6 ];
float flanger_buf2[ max_flanger_size * 3 * 6 ];
float flanger_ptr = 0;
float flanger_size = 0;
float flanger_timer = 0;

int time_effect = 1;

int start_recorder = 0;
int rec_ptr = 0;
int rec_play = 0;
#define rec_size ( one_tick_size * 16 )
float rec1[ rec_size ];
float rec2[ rec_size ];

static inline void flanger_put( float v1, float v2 )
{
    float ptr2 = flanger_ptr - flanger_size;
    if( ptr2 < 0 ) ptr2 += ( flanger_size * 2 );
    flanger_buf1[ (int)ptr2 ] += v1 / 2;
    flanger_buf2[ (int)ptr2 ] += v2 / 2;
}

static inline void flanger_get( float* v1, float* v2 )
{
    int ptr2;
    flanger_buf1[ (int)flanger_ptr ] /= 1.1;
    flanger_buf2[ (int)flanger_ptr ] /= 1.1;
    *v1 += flanger_buf1[ (int)flanger_ptr ] / 1.5;
    *v2 += flanger_buf2[ (int)flanger_ptr ] / 1.5;
    flanger_ptr++;
    if( flanger_ptr >= flanger_size * 2 ) 
    {
	flanger_ptr -= flanger_size * 2;
    }
    flanger_timer += 0.0001;
    if( rec_play ) 
	flanger_size = 580;
    else
	flanger_size = ( ( sin( flanger_timer / 10 ) + 1 ) / 2 ) * ( max_flanger_size - 30 ) + 30;
}

static inline void echo_put( float v1, float v2 )
{
    int ptr2 = echo_ptr - echo_size;
    if( ptr2 < 0 ) ptr2 += ( echo_size * 2 );
    if( ptr2 < echo_size )
	echo_buf1[ ptr2 ] += v1 / 2;
    else
	echo_buf2[ ptr2 ] += v2 / 2;
    //Slow reverb:
    int a;
    for( a = 0; a < reverb; a ++ )
    {
	ptr2 = echo_ptr + slow_reverb[ a ];
	if( ptr2 < 0 ) ptr2 += ( echo_size * 2 ) * ( 1 - ( ptr2 / (echo_size*2) ) );
	if( ptr2 >= ( echo_size * 2 ) ) ptr2 -= ( echo_size * 2 ) * ( ptr2 / (echo_size*2) );
	if( a & 1 )
	    echo_buf1[ ptr2 ] += v1 / 6;
	else
	    echo_buf2[ ptr2 ] += v2 / 6;
    }
}

static inline void reverb_put( float v1, float v2 )
{
    int ptr2;
    //Slow reverb:
    int a;
    for( a = 0; a < reverb; a ++ )
    {
	ptr2 = echo_ptr + slow_reverb[ a ];
	if( ptr2 < 0 ) ptr2 += ( echo_size * 2 ) * ( 1 - ( ptr2 / (echo_size*2) ) );
	if( ptr2 >= ( echo_size * 2 ) ) ptr2 -= ( echo_size * 2 ) * ( ptr2 / (echo_size*2) );
	if( a & 1 )
	    echo_buf1[ ptr2 ] += v1 / 6;
	else
	    echo_buf2[ ptr2 ] += v2 / 6;
    }
}

static inline void echo_get( float* v1, float* v2 )
{
    int ptr2;
    //echo_buf1[ echo_ptr ] /= 2;
    //echo_buf2[ echo_ptr ] /= 2;
    *v1 += echo_buf1[ echo_ptr ];
    *v2 += echo_buf2[ echo_ptr ];
    echo_ptr++;
    if( echo_ptr >= echo_size * 2 ) 
    {
	echo_ptr = 0;
	int a;
	int r = ( ( rand() & 255 ) * (echo_size/2) ) >> 8;
	r += echo_size;
	for( a = 0; a < ( echo_size * 2 ); a++ )
	{
	    ptr2 = a - r;
	    if( ptr2 < 0 ) ptr2 += ( echo_size * 2 );
	    echo_buf1[ a ] = ( echo_buf1[ a ] + echo_buf1[ ptr2 ] ) / 2;
	    echo_buf2[ a ] = ( echo_buf2[ a ] + echo_buf2[ ptr2 ] ) / 2;
	}
    }
}

int offset = 0;
float bound = 0.05;

void main_callback( float* buf, int len )
{
    int a;
    int s;
    int c;
    uint8_t* cur_line;
    float res1;
#ifdef FULL_DETAIL
    float res2;
#endif
    float freq;
    for( a = 0; a < len; a++ ) { buf[ a << 1 ] = 0; buf[ ( a << 1 ) + 1 ] = 0; } //Clear buffer
    //Render:
    int tick_changed = 0;
    for( a = 0; a < len; a++ ) 
    {
	tick_changed = 0;
	if( timer >= one_tick_size )
	{ //Increment tick number:
	    timer = 0; tick++;
	}
	if( timer == 0 ) tick_changed = 1;
	//Synths (channels):
#ifdef FULL_DETAIL
	for( s = 0; s < chan_num; s++ )
#else
	s = 2;
#endif
	{
	    cur_line = patterns[ cur_pattern ] + ( tick * chan_num );
	    if( cur_line[ s ] == 255 ) 
	    { //End of pattern:
		tick = 0;
		cur_pattern++;
		if( patterns[ cur_pattern ] == 0 ) { exit_request = 1; return; }
		cur_line = patterns[ cur_pattern ] + ( tick * chan_num );
	    }
	    if( syn[ s ] == 0 ) continue;
	    switch( syn[ s ] )
	    {
#ifdef FULL_DETAIL
		case SYNTH_PAD: 
		    if( tick_changed )
		    {
			if( cur_line[ s ] )
			{
			    effect_timer[ s ] = 1;
			    bass_freq[ s ] = pow( 2, (float)( cur_line[ s ] + offset ) / 12.0F );
			    bass_tdelta[ s ] = bass_freq[ s ] / srate;
			    bass_timer[ s ] = 0;
			}
			if( cur_line[ s ] == 254 )
			    effect_timer[ s ] = 0;
			if( cur_line[ s ] == 253 )
			{
			    effect_timer[ s ] = 0;
			    bound = 0.1;
			}
		    }
		    if( effect_timer[ s ] )
		    {
			effect_timer[ s ] *= 0.99998;
			bass_delta[ s ] += ( bass_tdelta[ s ] - bass_delta[ s ] ) / 2000;
			bass_timer[ s ] += bass_delta[ s ];
			res1 = sin( bass_timer[ s ] ) * sin( bass_timer[ s ] * (sin( effect_timer[ s ] ) * 0.02) ) + cos( bass_timer[ s ] * 0.99 );
			res2 = cos( bass_timer[ s ] * 1.01 ) + cos( bass_timer[ s ] * 0.99 );
			if( res1 > 1 ) res1 = 1;
			if( res1 < -1 ) res1 = -1;
			if( res2 > 1 ) res2 = 1;
			if( res2 < -1 ) res2 = -1;
		    }
		    else
		    {
			res1 = 0;
			res2 = 0;
		    }
		    echo_put( res1 / 8, res2 / 8 );
		    res1 = 0;
		    res2 = 0;
		    break;

		case SYNTH_POLY:
		    if( tick_changed )
		    {
			if( cur_line[ s ] )
			{
			    effect_timer[ s ] = 1;
			    bass_freq[ s ] = pow( 2, (float)( cur_line[ s ] + offset ) / 12.0F );
			    bass_tdelta[ s ] = bass_freq[ s ] / srate;
			    bass_timer[ s ] = 0;
			}
		    }
		    if( effect_timer[ s ] )
		    {
			effect_timer[ s ] *= 0.99998;
			bass_delta[ s ] += ( bass_tdelta[ s ] - bass_delta[ s ] ) / 1800;
			bass_timer[ s ] += bass_delta[ s ];
			res1 = sin( bass_timer[ s ] ) * effect_timer[ s ];
			res2 = sin( bass_timer[ s ] * 1.01 ) * effect_timer[ s ];
		    }
		    else
		    {
			res1 = 0;
			res2 = 0;
		    }
		    buf[ ( a << 1 ) ] += res1 / 8;
		    buf[ ( a << 1 ) + 1 ] += res2 / 8;
		    echo_put( res1 / 4, res2 / 4 );
		    res1 = 0;
		    res2 = 0;
		    break;

		case SYNTH_EFFECT:
		    if( tick_changed )
		    {
			if( cur_line[ s ] )
			{
			    effect_timer[ s ] = 1;
			    effect_timer2[ s ] = 0;
			}
			if( cur_line[ s ] == 5 ) { effect_lowfilter[ s ] = 4; rec_play = 1; }
			if( cur_line[ s ] == 4 ) effect_lowfilter[ s ] = 3;
			if( cur_line[ s ] == 3 ) effect_lowfilter[ s ] = 2;
			if( cur_line[ s ] == 2 ) effect_lowfilter[ s ] = 1;
			if( cur_line[ s ] == 1 ) effect_lowfilter[ s ] = 0;
		    }
		    if( effect_timer[ s ] )
		    {
			effect_timer[ s ] *= 0.99996;
			effect_timer2[ s ] += 0.2;
			if( effect_lowfilter[ s ] == 4 )
			{
			    effect_timer[ s ] = 1;
			    /*res1 = rec1[ rec_ptr ] * 1.8;
			    res2 = rec2[ rec_ptr ] * 1.8;
			    rec_ptr--;
			    if( rec_ptr < 0 ) rec_ptr = rec_size - 1;*/
			}
			else
			if( effect_lowfilter[ s ] == 3 )
			{
			    res2 = sin( ( effect_timer2[ s ] * 1 ) * effect_timer[ s ] ) * effect_timer[ s ]; 
			    res1 = sin( ( effect_timer2[ s ] * 1.5 ) / effect_timer[ s ] ) * effect_timer[ s ];
			}
			else
			if( effect_lowfilter[ s ] == 2 )
			{
			    res2 = sin( ( effect_timer2[ s ] / 4 ) / effect_timer[ s ] ) * effect_timer[ s ]; 
			    res1 = sin( ( effect_timer2[ s ] / 3.5 ) / effect_timer[ s ] ) * effect_timer[ s ];
			}
			else
			if( effect_lowfilter[ s ] == 1 )
			{
			    res2 = sin( ( effect_timer2[ s ] / 2 ) / effect_timer[ s ] ) * effect_timer[ s ]; 
			    res1 = sin( ( effect_timer2[ s ] / 2.5 ) / effect_timer[ s ] ) * effect_timer[ s ];
			}
			else
			    res2 = res1 = sin( effect_timer2[ s ] / effect_timer[ s ] ) * effect_timer[ s ];
		    }
		    else
		    {
			res1 = 0;
			res2 = 0;
		    }
		    buf[ ( a << 1 ) ] += ( res1 / 9.0F );
		    buf[ ( a << 1 ) + 1 ] += ( res2 / 9.0F );
		    if( effect_lowfilter[ s ] != 4 )
			echo_put( res1 / 5, res2 / 5 );
		    res1 = 0;
		    res2 = 0;
		    break;

		case SYNTH_ACID_BASS: 
		    if( tick_changed )
		    {
			bass_freq[ s ] = pow( 2, (float)( cur_line[ s ] + offset ) / 12.0F );
			bass_tdelta[ s ] = bass_freq[ s ] / srate;
			bass_timer[ s ] = 0;
			effect_timer[ s ] = 1;
			effect_timer2[ s ] = 0;
		    }
		    bass_delta[ s ] += ( bass_tdelta[ s ] - bass_delta[ s ] ) / 300;
		    bass_timer[ s ] += bass_delta[ s ];
		    effect_timer2[ s ] += 0.02 * (32 - (float)tick);
		    effect_timer[ s ] *= 0.9997;
		    if( cur_line[ s ] )
		    {
			res2 = res1 = sin( bass_timer[ s ] ) + ( sin( bass_timer[ s ] * 4.01 ) * 0.9 );
			if( res1 > 0.2 ) res1 = 0.1;
			if( res1 < -0.2 ) res1 = -0.1;
			if( res2 > 0.2 ) res2 = 0.1;
			if( res2 < -0.2 ) res2 = -0.1;
			//res1 += ( sin( bass_timer[ s ] ) * cos( effect_timer2[ s ] * effect_timer[ s ] ) * 0.07 );
			//res2 += ( sin( bass_timer[ s ] ) * cos( effect_timer2[ s ] * effect_timer[ s ] ) * 0.07 );
			res1 *= effect_timer[ s ];
			res2 *= effect_timer[ s ];
		    }
		    else { res1 = 0; res2 = 0; }
		    echo_put( res1, res2 );
		    buf[ ( a << 1 ) ] += res1;
		    buf[ ( a << 1 ) + 1 ] += res2;
		    break;

#endif
		case SYNTH_BASS_TINY:
		case SYNTH_BASS:
		    if( tick_changed )
		    {
#ifdef FULL_DETAIL			
		    float note = (float)( cur_line[ s ] + offset );
			bass_freq[ s ] = powf( 2, note / 12.0F );
#else
			//TODO: make table
		    int note = (float)( cur_line[ s ] + offset );
			bass_freq[ s ] = powf( 2, note / 12.0F );
#endif
			bass_tdelta[ s ] = bass_freq[ s ] / srate;
			bass_timer[ s ] = 0;
			effect_timer[ s ] = 1;
		    }
		    bass_delta[ s ] += ( bass_tdelta[ s ] - bass_delta[ s ] ) / 300;
		    bass_timer[ s ] += bass_delta[ s ];
		    effect_timer[ s ] *= 0.9999;
		    if( cur_line[ s ] )
		    {
#ifdef FULL_DETAIL		
			res1 = sinf( bass_timer[ s ] ) + sinf( bass_timer[ s ] * 2.01 );
#else
			res1 = sinf( bass_timer[ s ] ) + sinf( bass_timer[ s ] * 2.01 ); //second term is optional
#endif
			if( res1 > bound ) res1 = 0.05;
			if( res1 < -bound ) res1 = -0.05;
#ifdef FULL_DETAIL		
			res2 = cosf( bass_timer[ s ] ) + cosf( bass_timer[ s ] * 2.006 );
			if( res2 > bound ) res2 = 0.05;
			if( res2 < -bound ) res2 = -0.05;
#endif
		    }
		    else
		    {
			res1 = 0;
#ifdef FULL_DETAIL			
			res2 = 0;
#endif
		    }
		    if( bound > 0.1 ) {
		    res1 *=  effect_timer[ s ];
#ifdef FULL_DETAIL
		    res2 *= effect_timer[ s ];
#endif
		    }
		    if( syn[ s ] == SYNTH_BASS_TINY ) 
		    {
			res1 *= 0.9;
#ifdef FULL_DETAIL
			res2 *= 0.9;
#endif
		    }
		    else
		    {
			if( !rec_play )
			{
#ifdef FULL_DETAIL
			    flanger_put( res1, res2 );
			    res1 *= 1./1.5;
			    flanger_get( &res1, &res2 );
			    res2 *= 1./1.5;
#else			    
			    flanger_put( res1, res1 );
			    res1 *= 1./1.5;
#endif
			}
		    }
#ifdef FULL_DETAIL
		    echo_put( res1, res2 );
		    buf[ ( a << 1 ) ] += res1;
		    buf[ ( a << 1 ) + 1 ] += res2;
#else
		    buf[ ( a << 1 ) ] += res1;
		    buf[ ( a << 1 ) + 1 ] += res1;
#endif
		    break;
#ifdef FULL_DETAIL
		case SYNTH_HAT:
		    if( tick_changed ) 
		    {
			if( cur_line[ s ] )
			    hat_timer[ s ] = 2;
			if( cur_line[ s ] == 254 )
			{
			    offset ++;
			    fadeout = 1;
			    break;
			}
			if( cur_line[ s ] == 253 )
			{
			    syn[ 3 ] = SYNTH_ACID_BASS;
			    start_recorder = 1;
			}
			if( cur_line[ s ] == 252 )
			    offset --;
		    }
		    if( cur_line[ s ] == 254 ) break;
		    if( cur_line[ s ] == 253 ) break;
		    if( cur_line[ s ] == 252 ) break;
		    hat_timer[ s ] -= 0.0004;
		    if( hat_timer[ s ] < 0 ) { hat_timer[ s ] = 0; break; }
		    res1 = ( ( (float)(myrand()&0x7FFF) / 32000.0F ) - 0.5 ) * ( (float)cur_line[ s ] / 10.0F );
		    res2 = ( ( (float)(myrand()&0x7FFF) / 32000.0F ) - 0.5 ) * ( (float)cur_line[ s ] / 10.0F );
		    if( res1 > hat_old1[ s ] ) hat_old1[ s ] += 0.03;
		    if( res1 < hat_old1[ s ] ) hat_old1[ s ] -= 0.03;
		    if( res2 > hat_old2[ s ] ) hat_old2[ s ] += 0.03;
		    if( res2 < hat_old2[ s ] ) hat_old2[ s ] -= 0.03;
		    res1 = hat_old1[ s ];
		    res2 = hat_old2[ s ];
		    hat_old1[ s ] = res1;
		    hat_old2[ s ] = res2;
		    res1 *= hat_timer[ s ] * ( (float)cur_line[ s ] / 100.0F );
		    res2 *= hat_timer[ s ] * ( (float)cur_line[ s ] / 100.0F );
		    //reverb_put( res1 / 5, res2 / 5 );
		    buf[ ( a << 1 ) ] += res1 / 1.8;
		    buf[ ( a << 1 ) + 1 ] += res2 / 1.8;
		    break;

		case SYNTH_DRUM: 
		    if( tick_changed ) 
		    {
			if( cur_line[ s ] )
			{
			    drum_timer[ s ] = 1;
			    drum_timer2[ s ] = 0;
			    drum_timer3[ s ] = 1;
			}
		    }
		    drum_timer[ s ] -= 0.001;
		    drum_timer2[ s ] += 0.03;
		    drum_timer3[ s ] += 0.003;
		    if( drum_timer[ s ] < 0 ) { drum_timer[ s ] = 0; break; }
		    if( 0 )
		    {
			res1 = drum_timer[ s ] * ( (float)cur_line[ s ] / 12.0F ) * sinf( ((float)cur_line[ s ] / 70) * drum_timer2[ s ] / drum_timer3[ s ] );
			res2 = drum_timer[ s ] * ( (float)cur_line[ s ] / 12.0F ) * sinf( drum_timer2[ s ] / drum_timer3[ s ] + 2 );
		    }
		    else
		    {
			res1 = drum_timer[ s ] * ( (float)cur_line[ s ] / 20.0F ) * sinf( ((float)cur_line[ s ] / 70) * drum_timer2[ s ] / drum_timer3[ s ] );
			res2 = res1;
			float d2 = drum_timer[ s ] * ( (float)cur_line[ s ] / 120.0F ) * sinf( drum_timer2[ s ] / drum_timer3[ s ] + 2 );
			if( tick & 1 )
			{
			    res1 *= 0.3f;
			    res1 += d2;
			}
			else
			{
			    res2 *= 0.3f;
			    res2 += d2;
			}
		    }
		    float clip = 0.3;
		    if( res1 > clip ) res1 = clip;
		    if( res1 < -clip ) res1 = -clip;
		    if( res2 > clip ) res2 = clip;
		    if( res2 < -clip ) res2 = -clip;
		    buf[ ( a << 1 ) ] += res1;
		    buf[ ( a << 1 ) + 1 ] += res2;
		    res1 = 0;
		    res2 = 0;
		    break;
#endif
	    }
	}
	//buf[ ( a << 1 ) ] = 0;
	//buf[ ( a << 1 ) + 1 ] = 0;
#ifdef FULL_DETAIL
	echo_get( &res1, &res2 );
	buf[ ( a << 1 ) ] += res1;
	buf[ ( a << 1 ) + 1 ] += res2;
#else
	buf[ ( a << 1 ) ] += res1;
	buf[ ( a << 1 ) + 1 ] += res1;
#endif
	if( start_recorder )
	{
	    rec1[ rec_ptr ] = buf[ ( a << 1 ) ];
	    rec2[ rec_ptr ] = buf[ ( a << 1 ) + 1 ];
	    //if( myrand() & 15 ) rec1[ rec_ptr ] += 0.2 * ( (float)( myrand() & 255 ) / 255 );
	    //if( myrand() & 15 ) rec2[ rec_ptr ] += 0.2 * ( (float)( myrand() & 255 ) / 255 );
	    rec_ptr++;
	    if( rec_ptr >= rec_size )
	    {
		start_recorder = 0;
		rec_ptr --;
	    }
	}
	if( rec_play )
	{
#ifdef FULL_DETAIL
	    flanger_put( rec1[ rec_ptr ] / 2, rec2[ rec_ptr ] / 2 );
	    res1 = 0; res2 = 0;
	    flanger_get( &res1, &res2 );
	    buf[ ( a << 1 ) ] += res1;
	    buf[ ( a << 1 ) + 1 ] += res2;
#else
	    buf[ ( a << 1 ) ] += res1;
	    buf[ ( a << 1 ) + 1 ] += res1;
#endif
	    rec_ptr--;
	    if( rec_ptr < 0 ) rec_ptr = rec_size - 1;
	}
	timer++;
#ifdef FULL_DETAIL
	if( fadeout )
	{
	    fadeout_vol -= 0.000001;
	    if( fadeout_vol <= 0 ) { fadeout_vol = 0; exit_request = 1; }
	    buf[ ( a << 1 ) ] *= fadeout_vol;
	    buf[ ( a << 1 ) + 1 ] *= fadeout_vol;
	}
#endif
    }
}

//Utrom ekzamen... Ja ne gotov :) ... na na na
//11 june 2005

void render_buf( float* buf, int len ) //buf: LRLRLR..; len - number of frames (one frame = LR (Left+Right channel));
{
    main_callback( buf, len );
    //Simple DC blocker:
    if( volume != 1 ) for( int a = 0; a < len * 2; a++ ) buf[ a ] *= volume;
    for( int a = 0; a < len; a++ )
    {
        dc_sl += buf[ a * 2 ]; dc_sl /= 2;
        dc_sr += buf[ a * 2 + 1 ]; dc_sr /= 2;
    }
    for( int a = 0; a < len; a++ )
    {
        //Simple DC blocker:
        float a2 = (float)(len-a) / len;
        float a3 = (float)a / len;
        buf[ a * 2 ] -= ( dc_psl * a2 ) + ( dc_sl * a3 );
        buf[ a * 2 + 1 ] -= ( dc_psr * a2 ) + ( dc_sr * a3 );
    	//Simple volume compression:
        buf[ a * 2 ] /= max_vol;
        buf[ a * 2 + 1 ] /= max_vol;
        max_vol -= 0.0005;
        if( max_vol < 1 ) max_vol = 1;
        float t1 = buf[ a * 2 ]; if( t1 < 0 ) t1 = -t1;
        float t2 = buf[ a * 2 + 1 ]; if( t2 < 0 ) t2 = -t2;
        if( t1 > max_vol ) max_vol = t1;
        if( t2 > max_vol ) max_vol = t2;
    }
    dc_psl = dc_sl; dc_psr = dc_sr;
}

#ifdef AUDIO_DEMO_STANDALONE
void sdl_audio_callback( void* udata, Uint8* stream, int len )
{
    render_buf( (float*)stream, len / 8 );
}

int sound_init()
{
    for( int a = 0; a < reverb; a++ ) slow_reverb[ a ] = ( ( rand() & 2047 ) - 1024 ) << 6;
    if( out_mode == 0 )
    {
	SDL_Init( 0 );
	SDL_AudioSpec a;
	a.freq = srate;
	a.format = AUDIO_F32;
	a.channels = 2;
	a.samples = bufsize;
	a.callback = sdl_audio_callback;
	a.userdata = NULL;
	if( SDL_OpenAudio( &a, NULL ) < 0 )
	{
    	    printf( "Couldn't open audio: %s\n", SDL_GetError() );
    	    return -1;
	}
	SDL_PauseAudio( 0 );
	return 0;
    }
    if( out_mode == 1 )
    {
	FILE* f = fopen( export_file_name, "wb" );
        if( f )
        {
    	    printf( "Exporting to WAV...\n" );
    	    int fixup1 = 0, fixup2 = 0;
    	    int out_bytes = 0;
    	    int val;
    	    //WAV header:
            fwrite( (void*)"RIFF", 1, 4, f );
            val = 4 + 24 + 8 + out_bytes;
            fixup1 = ftell( f );
            fwrite( &val, 4, 1, f );
            fwrite( (void*)"WAVE", 1, 4, f );
            //WAV FORMAT:
            fwrite( (void*)"fmt ", 1, 4, f );
            val = 16; fwrite( &val, 4, 1, f );
            val = 3; fwrite( &val, 2, 1, f ); //format
            val = 2; fwrite( &val, 2, 1, f ); //channels
            val = srate; fwrite( &val, 4, 1, f ); //frames per second
            val = srate * 2 * 4; fwrite( &val, 4, 1, f ); //bytes per second
            val = 2 * 4; fwrite( &val, 2, 1, f ); //block align
            val = 4 * 8; fwrite( &val, 2, 1, f ); //bits per sample
            //WAV DATA:
            fwrite( (void*)"data", 1, 4, f );
            fixup2 = ftell( f );
            fwrite( &out_bytes, 4, 1, f );
            while( !exit_request )
            {
        	float buf[ bufsize * 2 ];
		render_buf( buf, bufsize );
        	out_bytes += fwrite( buf, 1, bufsize * 2 * 4, f );
            }
            fseek( f, fixup1, SEEK_SET ); val = 4 + 24 + 8 + out_bytes; fwrite( &val, 4, 1, f );
            fseek( f, fixup2, SEEK_SET ); val = out_bytes; fwrite( &val, 4, 1, f );
            int frames = out_bytes / ( 4 * 2 );
            printf( "%d bytes; %d frames; %d seconds\n", out_bytes, frames, frames / srate );
    	    fclose( f );
        }
	return 0;
    }
    return -1;
}

void sound_close()
{
    if( out_mode == 0 )
    {
	SDL_CloseAudio();
	SDL_Quit();
    }
}

void int_handler( int param )
{
    exit_request = 1;
}

int main( int argc, char* argv[] )
{
    signal( SIGINT, int_handler );
    if( argc == 3 )
    {
	if( strcmp( argv[ 1 ], "-o" ) == 0 )
	{
	    export_file_name = argv[ 2 ];
	    out_mode = 1;
	}
    }
    printf( "\nNightRadio - P.S.\nnightradio@gmail.com\nWarmPlace.ru\n\n" );
    printf( "Usage:\n  just play: ./ps\n  export to WAV: ./ps -o filename.wav\n" );
    printf( "Press CTRL+C to exit\n\n" );
    if( sound_init() ) return 1;
    while( !exit_request )
    {
	sleep( 1 );
    }
    sound_close();
    return 0;
}
#endif //AUDIO_DEMO_STANDALONE
