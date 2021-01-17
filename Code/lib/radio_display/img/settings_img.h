// We need this header file to use FLASH as storage with PROGMEM directive:
#include <pgmspace.h>

// Icon width and height
const uint16_t settWidth = 49;
const uint16_t settHeight = 48;

const unsigned short  settings[] PROGMEM={0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc618, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x6b4d, 0x2946, 0x0841, 0x39c9, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x0841, 0x18c5, 0x39c9, 0x9cd3, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb596, 0x39c9, 0x2946, 0x6b4d, 0xad55, 0x8430, 0x0841, 0xb596, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c5, 0x9cd3, 0xad55, 0x52ac, 0x18c5, 0x2946, 0x73af, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x52ac, 0x2946, 0x8430, 0xc618, 0xce79, 0xc618, 0xce79, 0x4a6a, 0x0841, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 0xce79, 0x2946, 0x6b4d, 0xce79, 0xc618, 0xce79, 0xc618, 0x8430, 0x2946, 0x2946, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0841, 0x8430, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0x4a6a, 0x0841, 0x4a6a, 0x8430, 0x9cd3, 0x52ac, 0x18c5, 0x6b4d, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x0841, 0xc618, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x6b4d, 0x4a6a, 0xce79, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xc618, 0xc618, 0x9cd3, 0x52ac, 0x4a6a, 0x4a6a, 0x52ac, 0xad55, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xce79, 0x39c9, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8430, 0x2946, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xce79, 0xce79, 0xce79, 0xce79, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0x18c5, 0x4a6a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x73af, 0x4a6a, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xce79, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x39c9, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x39c9, 0x73af, 0xce79, 0xbdf7, 0xbdf7, 0xce79, 0xce79, 0x9cd3, 0x9cd3, 0x9cd3, 0x39c9, 0x52ac, 0x73af, 0xad55, 0xad55, 0xbdf7, 0xbdf7, 0xce79, 0xce79, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x0841, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x73af, 0x2946, 0xc618, 0xbdf7, 0xc618, 0xce79, 0x8430, 0x39c9, 0x39c9, 0x6b4d, 0x73af, 0x6b4d, 0x73af, 0x73af, 0x73af, 0x73af, 0x8430, 0x6b4d, 0x4a6a, 0x9cd3, 0xc618, 0xc618, 0xbdf7, 0xc618, 0x2946, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0x73af, 0x18c5, 0xb596, 0xc618, 0xce79, 0xb596, 0x52ac, 0x39c9, 0x39c9, 0x73af, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x73af, 0x73af, 0x6b4d, 0x39c9, 0x52ac, 0xbdf7, 0xc618, 0xc618, 0xad55, 0x0841, 0x2946, 0xce79, 0xffff, 0xffff, 0xffff, 0xce79, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0x73af, 0x0841, 0x2946, 0x52ac, 0x6b4d, 0x2946, 0x39c9, 0xb596, 0xc618, 0xce79, 0x9cd3, 0x18c5, 0x52ac, 0x9cd3, 0x52ac, 0x73af, 0x73af, 0x6b4d, 0x4a6a, 0x52ac, 0x52ac, 0x4a6a, 0x6b4d, 0x6b4d, 0x8430, 0x8430, 0x73af, 0x39c9, 0x18c5, 0x9cd3, 0xce79, 0xc618, 0xb596, 0x39c9, 0x0841, 0x39c9, 0x52ac, 0x39c9, 0x18c5, 0x18c5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xce79, 0x2946, 0x9cd3, 0x8430, 0x6b4d, 0x6b4d, 0x9cd3, 0xce79, 0xc618, 0xce79, 0x73af, 0x2946, 0x6b4d, 0x39c9, 0x9cd3, 0x52ac, 0x39c9, 0x52ac, 0x73af, 0x73af, 0x8430, 0x8430, 0x73af, 0x6b4d, 0x4a6a, 0x39c9, 0x2946, 0x39c9, 0x52ac, 0x52ac, 0x39c9, 0x9cd3, 0xce79, 0xc618, 0xce79, 0x9cd3, 0x6b4d, 0x6b4d, 0x9cd3, 0xad55, 0x0841, 0x73af, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0x6b4d, 0x52ac, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xbdf7, 0xc618, 0x9cd3, 0x2946, 0x8430, 0x8430, 0x39c9, 0x39c9, 0x4a6a, 0x9cd3, 0xc618, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xc618, 0x9cd3, 0x39c9, 0x52ac, 0x9cd3, 0x9cd3, 0x73af, 0x39c9, 0x9cd3, 0xc618, 0xbdf7, 0xc618, 0xce79, 0xce79, 0xc618, 0xce79, 0x4a6a, 0x0841, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0x2946, 0x9cd3, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0x39c9, 0x39c9, 0x8430, 0x8430, 0x2946, 0x6b4d, 0xc618, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0xc618, 0x6b4d, 0x39c9, 0x52ac, 0x39c9, 0x39c9, 0x39c9, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0x9cd3, 0x0841, 0x9cd3, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xad55, 0x2946, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x6b4d, 0x52ac, 0x6b4d, 0x39c9, 0x4a6a, 0x8430, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x39c9, 0x73af, 0x8430, 0x4a6a, 0x6b4d, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x2946, 0x39c9, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0x6b4d, 0x73af, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0x9cd3, 0x39c9, 0x8430, 0x8430, 0x2946, 0x6b4d, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x6b4d, 0x52ac, 0x8430, 0x8430, 0x39c9, 0xb596, 0xc618, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xce79, 0x73af, 0x0841, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0x18c5, 0x39c9, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x6b4d, 0x52ac, 0x8430, 0x73af, 0x39c9, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xc618, 0xce79, 0xc618, 0xc618, 0xce79, 0xc618, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0x39c9, 0x52ac, 0x52ac, 0x18c5, 0x73af, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x9cd3, 0x2946, 0x0841, 0xc618, 0xffff, 0xffff, 
0xffff, 0xffff, 0x9cd3, 0x2946, 0x0841, 0x9cd3, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0x9cd3, 0x73af, 0x8430, 0x4a6a, 0x8430, 0xce79, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xc618, 0xb596, 0x52ac, 0x2946, 0x2946, 0x52ac, 0xb596, 0xc618, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xce79, 0x73af, 0x39c9, 0x8430, 0x6b4d, 0x4a6a, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x0841, 0x0841, 0x8430, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0x4a6a, 0x0841, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0x9cd3, 0x73af, 0x73af, 0x39c9, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x0841, 0x0841, 0x2946, 0x39c9, 0x0841, 0x0841, 0xad55, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xb596, 0x52ac, 0x8430, 0x73af, 0x6b4d, 0xbdf7, 0xbdf7, 0xc618, 0xad55, 0x0841, 0x2946, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x2946, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0x8430, 0x8430, 0x6b4d, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0x0841, 0x18c5, 0xce79, 0xffff, 0xffff, 0xffff, 0x2946, 0x18c5, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x52ac, 0x6b4d, 0x8430, 0x9cd3, 0xc618, 0xbdf7, 0xce79, 0x52ac, 0x0841, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x2946, 0xc618, 0xbdf7, 0xbdf7, 0x8430, 0x8430, 0x52ac, 0x73af, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x8430, 0x0841, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0841, 0x9cd3, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x73af, 0x6b4d, 0x8430, 0x73af, 0xbdf7, 0xc618, 0xc618, 0x0841, 0x4a6a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc618, 0x0841, 0xb596, 0xc618, 0xbdf7, 0x8430, 0x8430, 0x4a6a, 0x6b4d, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x6b4d, 0x0841, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x4a6a, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x52ac, 0x8430, 0x8430, 0xbdf7, 0xc618, 0xc618, 0x0841, 0x73af, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc618, 0x18c5, 0xbdf7, 0xc618, 0xbdf7, 0x8430, 0x8430, 0x4a6a, 0x6b4d, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x0841, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x39c9, 0x73af, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x52ac, 0x8430, 0x73af, 0xbdf7, 0xc618, 0xc618, 0x0841, 0x6b4d, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x39c9, 0xce79, 0xbdf7, 0xbdf7, 0x8430, 0x8430, 0x52ac, 0x73af, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xb596, 0x0841, 0x6b4d, 0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0841, 0xb596, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x73af, 0x6b4d, 0x8430, 0x8430, 0xbdf7, 0xbdf7, 0xce79, 0x39c9, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x2946, 0x8430, 0xce79, 0xbdf7, 0xbdf7, 0x8430, 0x8430, 0x6b4d, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x0841, 0x6b4d, 0xce79, 0xffff, 0x9cd3, 0x2946, 0x9cd3, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x52ac, 0x6b4d, 0x8430, 0x6b4d, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x0841, 0x9cd3, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0x4a6a, 0x39c9, 0xce79, 0xbdf7, 0xc618, 0xb596, 0x39c9, 0x8430, 0x8430, 0x52ac, 0xb596, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x8430, 0x2946, 0x18c5, 0x2946, 0x2946, 0x9cd3, 0xce79, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xc618, 0xad55, 0x39c9, 0x8430, 0x73af, 0x39c9, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x52ac, 0x0841, 0x9cd3, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0x9cd3, 0x2946, 0x52ac, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x52ac, 0x39c9, 0x4a6a, 0x2946, 0x8430, 0xce79, 0xbdf7, 0xc618, 0xc618, 0xc618, 0xbdf7, 0xce79, 0xc618, 0xad55, 0xad55, 0xc618, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x6b4d, 0x4a6a, 0x9cd3, 0x4a6a, 0x6b4d, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0x6b4d, 0x0841, 0x4a6a, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0x2946, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0x9cd3, 0x18c5, 0x6b4d, 0x52ac, 0x39c9, 0xb596, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xad55, 0x39c9, 0x73af, 0x8430, 0x6b4d, 0xad55, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x0841, 0xce79, 0xffff, 0xffff, 
0xffff, 0xffff, 0x6b4d, 0x39c9, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0x52ac, 0x73af, 0x9cd3, 0x52ac, 0x4a6a, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xce79, 0x52ac, 0x52ac, 0x9cd3, 0x6b4d, 0x73af, 0xce79, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x39c9, 0x2946, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xc618, 0x0841, 0xb596, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0x9cd3, 0x39c9, 0x52ac, 0x39c9, 0x2946, 0x6b4d, 0xce79, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0x52ac, 0x4a6a, 0x8430, 0x73af, 0x39c9, 0x9cd3, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xb596, 0x0841, 0x6b4d, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0x2946, 0x6b4d, 0xce79, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x2946, 0x73af, 0x8430, 0x4a6a, 0x52ac, 0xb596, 0xce79, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xce79, 0xb596, 0x4a6a, 0x39c9, 0x8430, 0x8430, 0x8430, 0x9cd3, 0xc618, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xbdf7, 0xce79, 0x6b4d, 0x0841, 0xce79, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0x9cd3, 0x0841, 0xc618, 0xce79, 0xc618, 0xc618, 0xce79, 0xce79, 0xbdf7, 0xce79, 0x73af, 0x39c9, 0x8430, 0x73af, 0x18c5, 0x2946, 0x6b4d, 0xb596, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xc618, 0xad55, 0x6b4d, 0x39c9, 0x6b4d, 0x8430, 0x8430, 0x6b4d, 0xbdf7, 0xc618, 0xbdf7, 0xce79, 0xce79, 0xc618, 0xc618, 0xce79, 0xbdf7, 0x0841, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0x2946, 0x39c9, 0x39c9, 0x0841, 0x0841, 0x39c9, 0x9cd3, 0xce79, 0xbdf7, 0xce79, 0x73af, 0x2946, 0x39c9, 0x73af, 0x8430, 0x52ac, 0x39c9, 0x39c9, 0x52ac, 0x8430, 0x8430, 0x52ac, 0x52ac, 0x39c9, 0x18c5, 0x73af, 0x9cd3, 0x73af, 0x39c9, 0x6b4d, 0xc618, 0xbdf7, 0xc618, 0x8430, 0x39c9, 0x0841, 0x0841, 0x18c5, 0x2946, 0x0841, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x0841, 0x2946, 0x52ac, 0x52ac, 0x2946, 0x0841, 0x6b4d, 0xc618, 0xbdf7, 0xce79, 0x9cd3, 0x52ac, 0x52ac, 0x6b4d, 0x8430, 0x4a6a, 0x52ac, 0x6b4d, 0x6b4d, 0x39c9, 0x39c9, 0x73af, 0x73af, 0x52ac, 0x8430, 0x52ac, 0x39c9, 0x8430, 0xce79, 0xbdf7, 0xc618, 0x52ac, 0x0841, 0x18c5, 0x6b4d, 0x73af, 0x4a6a, 0x0841, 0x52ac, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x0841, 0x52ac, 0xce79, 0xbdf7, 0xce79, 0xc618, 0x73af, 0x4a6a, 0x2946, 0x2946, 0x6b4d, 0x8430, 0x6b4d, 0x39c9, 0x8430, 0x6b4d, 0x52ac, 0x18c5, 0x4a6a, 0x6b4d, 0xb596, 0xce79, 0xbdf7, 0xce79, 0x6b4d, 0x0841, 0x6b4d, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xad55, 0x0841, 0xad55, 0xc618, 0xbdf7, 0xc618, 0xce79, 0xc618, 0x9cd3, 0x73af, 0x52ac, 0x4a6a, 0x2946, 0x39c9, 0x39c9, 0x52ac, 0x52ac, 0x8430, 0xb596, 0xce79, 0xc618, 0xbdf7, 0xc618, 0xad55, 0x0841, 0x4a6a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x39c9, 0x4a6a, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xce79, 0xce79, 0xbdf7, 0xb596, 0xb596, 0xb596, 0xc618, 0xce79, 0xce79, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x52ac, 0x0841, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9cd3, 0x2946, 0xce79, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xc618, 0xc618, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xbdf7, 0xce79, 0x39c9, 0x0841, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xad55, 0x2946, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xbdf7, 0xc618, 0xce79, 0xb596, 0xad55, 0x9cd3, 0xb596, 0xce79, 0xc618, 0xbdf7, 0xc618, 0xc618, 0xc618, 0xbdf7, 0xce79, 0x39c9, 0x2946, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x6b4d, 0x52ac, 0xce79, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xc618, 0xad55, 0x52ac, 0x0841, 0x0841, 0x0841, 0x0841, 0x4a6a, 0xb596, 0xc618, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xce79, 0x73af, 0x0841, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x2946, 0x2946, 0xbdf7, 0xce79, 0xc618, 0xbdf7, 0xc618, 0xad55, 0x0841, 0x0841, 0x52ac, 0xb596, 0xbdf7, 0x73af, 0x18c5, 0x0841, 0x9cd3, 0xc618, 0xbdf7, 0xce79, 0xce79, 0xad55, 0x39c9, 0x0841, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xad55, 0x0841, 0x0841, 0x39c9, 0x9cd3, 0xc618, 0xc618, 0x18c5, 0x0841, 0xbdf7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x4a6a, 0x0841, 0xbdf7, 0xce79, 0x9cd3, 0x39c9, 0x0841, 0x0841, 0x73af, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8430, 0x0841, 0x0841, 0x18c5, 0x39c9, 0x0841, 0xad55, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x2946, 0x2946, 0x2946, 0x0841, 0x0841, 0x6b4d, 0xce79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xad55, 0x52ac, 0x0841, 0x52ac, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0841, 0x4a6a, 0x9cd3, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};