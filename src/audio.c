#include <stdio.h>

#include <litex.h>
#include <i2s/litex_i2s.h>

uint16_t audio_volume = 0xFFFF/2;

#define CORDIC_HALF_PI 0x40000000u
#define CORDIC_SHIFT 30
static inline int64_t cordic_sin(x)
{
  return x;
}


int FAST_CODE synth(unsigned count)
{
	static int64_t wt = 0;
    const int f = 1000; //Hz
	const int bits = 24; //i2s_tx_get_bits();
	static int cycle_count = 0;
 	for(size_t i = 0; i < count; i+=2)
	{
	  wt += f*4ull*CORDIC_HALF_PI/44100;
	  if(wt > 2*CORDIC_HALF_PI)
	  {
	    wt -= 4ull*CORDIC_HALF_PI; //angle wrapping (-pi to pi)
	    ++cycle_count;
	  }
	  int32_t sample = ((uint64_t)audio_volume*cordic_sin(wt))>>(16+CORDIC_SHIFT-bits+1);
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

void i2s_demo(void)
{
    unsigned freq = i2s_tx_frequency();
    unsigned channels = i2s_tx_get_default_channels();
    unsigned bits = i2s_tx_get_bits();
    printf("Audio frequency: %d, channels %d, bits %d\n", freq, channels, bits);

    i2s_tx_start();
}

void audio_init(void)
{
	i2s_demo();
}

