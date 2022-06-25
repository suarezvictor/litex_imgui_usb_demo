// This file is Copyright (c) 2021 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#ifndef STATIC_ASSERT
//TODO: move to a more general place
//https://stackoverflow.com/questions/3385515/static-assert-in-c
#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
#define LITEX_STATIC_ASSERT3(X,L) STATIC_ASSERT(X,static_assertion_at_line_##L)
#define LITEX_STATIC_ASSERT2(X,L) LITEX_STATIC_ASSERT3(X,L)
#define LITEX_STATIC_ASSERT(X)    LITEX_STATIC_ASSERT2(X,__LINE__)
#endif

#define LITEX_PACKED32 __attribute__((packed, aligned(4)))

//general defitions and helpers for CSR access

#include <stdint.h>
#include <generated/csr.h>
typedef int litepheripheral_id;

typedef volatile uint32_t csr1word_t; //one 32-bit word (NOTE: MEMORY MAPPED IO NEEDS VOLATILE QUALIFIER)
typedef volatile uint64_t csr2word_t; //two 32-bit words (NOTE: MEMORY MAPPED IO NEEDS VOLATILE QUALIFIER)
#define LITECSR_T(s) csr ## s ## word_t //macro for selecting 64-bit or 32-bit registers based on size defintions in csr.h
#define LITECSR(s) LITECSR_T(s) //indirect use does macro expansion prior to concatenation

static inline csr2word_t csr_swap_words(csr2word_t x) { return (x >> 32) | (x << 32); } 
static inline csr2word_t litecsr_adjust_csr2(csr2word_t x) { return csr_swap_words(x); } //64-bit values are inverted
static inline csr1word_t litecsr_adjust_csr1(csr1word_t x) { return x; }

#define LITECSR_ACCESS_(v, sz) litecsr_adjust_csr ## sz (v)
#define LITECSR_ACCESS(v, sz) LITECSR_ACCESS_(v, sz)
#define LITECSR_READ(ph, s, field) LITECSR_ACCESS((s)->field, ph ## _ ## field ## _SIZE)
#define LITECSR_WRITE(ph, s, field, v) (s)->field = LITECSR_ACCESS(v, ph ## _ ## field ## _SIZE)

#define LITEX_OFFSET_ASSERT(ph, t, f) LITEX_STATIC_ASSERT(offsetof(t, f) == ph ## _ ## f ## _ADDR - ph ## _BASE);

