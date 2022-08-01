#include <stdio.h>

#include <litex.h>
#include <i2s/litex_i2s.h>

#define MOD_PLAYER //comment for simple sinusouid test

extern uint16_t audio_volume;
extern uint16_t audio_param[];


#ifdef MOD_PLAYER
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset

//#define HXCMOD_SLOW_TARGET //use in slow systems
#include "HxCModPlayer/hxcmod.h"
#include "HxCModPlayer/framegenerator.h"
#include "HxCModPlayer/packer/pack.h"
#include "HxCModPlayer/data_files/data_cartoon_dreams_n_fantasies_mod.h" //song as data

volatile static tracker_buffer_state trackbuf_state1;
static modcontext modloaded;

int i2s_audio_send_cb(unsigned count)
{
	static int16_t stream[I2S_FIFO_DEPTH];

	trackbuf_state1.nb_of_state = 0;
	hxcmod_fillbuffer(&modloaded, stream, count/2, &trackbuf_state1);

	for(int i = 0; i < count; ++i)
	  i2s_tx_enqueue_sample((stream[i]*audio_volume)>>8); //sample is 16 bits, volume is 16 bit, output is 24 bit

	return count;
}

void mod_load(int samplerate)
{
	static unsigned char *songname;

	hxcmod_init(&modloaded);
	hxcmod_setcfg(&modloaded, samplerate, 0, 0);

	songname = unpack(data_cartoon_dreams_n_fantasies_mod->data,
		data_cartoon_dreams_n_fantasies_mod->csize,
		data_cartoon_dreams_n_fantasies_mod->data,
		data_cartoon_dreams_n_fantasies_mod->size);

	hxcmod_load(&modloaded,(void*)songname,data_cartoon_dreams_n_fantasies_mod->size);
	printf("MOD song loaded: \"%s\"\n", songname);

    //init track buffer
	memset(&trackbuf_state1,0,sizeof(tracker_buffer_state));
	trackbuf_state1.nb_max_of_state = 1000;
	trackbuf_state1.track_state_buf = malloc(sizeof(tracker_state) * trackbuf_state1.nb_max_of_state);
	memset(trackbuf_state1.track_state_buf,0,sizeof(tracker_state) * trackbuf_state1.nb_max_of_state);
	trackbuf_state1.sample_step = I2S_FIFO_DEPTH;
}

//include implementation files
#include "HxCModPlayer/hxcmod.c"
#include "HxCModPlayer/framegenerator.c"
#include "HxCModPlayer/packer/lzw.c"
#include "HxCModPlayer/packer/pack.c"
#include "HxCModPlayer/packer/rle.c"

#else //not MOD_PLAYER

#include "cordic.h"

//#define AUDIO_FLOAT

int FAST_CODE synth(unsigned count)
{
	const int f = audio_param[0]; //Hz
	const int bits = 24; //i2s_tx_get_bits();
	static int cycle_count = 0;
#ifndef AUDIO_FLOAT
	static int64_t wt = 0;
#else
	static float wt = 0;
#endif
 	for(size_t i = 0; i < count; i+=2)
	{
#ifndef AUDIO_FLOAT
	  wt += f*4ull*CORDIC_HALF_PI/44100;
	  if(wt > 2*CORDIC_HALF_PI)
	  {
	    wt -= 4ull*CORDIC_HALF_PI; //angle wrapping (-pi to pi)
	    ++cycle_count;
	  }
	  int32_t sample = ((uint64_t)audio_volume*cordic_sin(wt))>>(16+CORDIC_SHIFT-bits+1);
#else
	  wt += 2.*M_PI*f/44100;
	  int32_t sample = (1<<(bits-16))*sin(wt)*audio_volume;
#endif

	  i2s_tx_enqueue_sample(sample); //left
	  i2s_tx_enqueue_sample(sample); //right
	}
#warning A pause here causes the demo to hang
	//if(cycle_count > 30*f)
	//  return -1; //request pause
	return count;
}

int i2s_audio_send_cb(unsigned count)
{
  return synth(count);
}
#endif // MOD_PLAYER


void audio_init(void)
{
    unsigned freq = i2s_tx_frequency();
    unsigned channels = i2s_tx_get_default_channels();
    unsigned bits = i2s_tx_get_bits();
    printf("Audio frequency: %d, channels %d, bits %d\n", freq, channels, bits);

#ifdef MOD_PLAYER
    mod_load(freq*2); //FIXME: doubling frequency correct issues with hardware samplerate
#endif

    i2s_tx_start();
}

