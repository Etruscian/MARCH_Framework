
#ifndef ESC_HW_H_INCLUDED
#define ESC_HW_H_INCLUDED


#include <string.h>

#include "../../Communication/Drivers/spi.h"
#include "utypes.h"
#include "esc.h"


uint16_t ESC_read (uint16_t address, void *buf, uint16_t len, void *tALevent);
uint16_t ESC_write (uint16_t address, void *buf, uint16_t len, void *tALevent);
void ESC_init(void);

#endif // ESC_HW_H_INCLUDED

