#ifndef _MAIN_H_
#define _MAIN_H_

#include "config.h"
#include "hardware.h"
#include "typedefs.h"
#include "data.h"
#include "cc2420.h"
#include "stdio.h"
#include "string.h"
#include "circ_buffer.h"
#include "ce-random.h"
#include "ce-packets.h"

extern unsigned char appState;

//#define DEBUG

//#int debug_printf( const char *fmt, ... );
#if defined( DEBUG )
  #define DEBUG_PRINTF(x) printf x
#else
   #define DEBUG_PRINTF(x)
#endif

#endif