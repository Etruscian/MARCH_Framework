#ifndef __UTYPES_H__
#define __UTYPES_H__

#include "cc.h"

typedef struct
{
   struct
   {
      uint32_t Position;
   } __attribute__((packed)) Inputs;
} __attribute__((packed)) _Rbuffer;

typedef struct
{
   struct
   {
      uint32_t PositionSetPoint;
   } __attribute__((packed)) Outputs;
} __attribute__((packed)) _Wbuffer;

typedef struct
{
} __attribute__((packed)) _Cbuffer;

extern _Rbuffer Rb;
extern _Wbuffer Wb;
extern _Cbuffer Cb;

#endif /* __UTYPES_H__ */
