#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#ifndef TU_ATTR_ALWAYS_INLINE
#define TU_ATTR_ALWAYS_INLINE __attribute__((always_inline))
#endif

//FIXME: move to a more global place
#define FAST_DATA __attribute__ ((section (".fast_data"))) //needed to avoid issues at USB setup
#define FAST_CODE __attribute__ ((section (".fast_text"))) //100% needed to make it work
#define IRAM_ATTR FAST_CODE //needed for reliability

