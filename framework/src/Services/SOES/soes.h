#ifndef __SOES_H__
#define __SOES_H__

#include "utypes.h"

/**

 * This function reads physical input values and assigns the corresponding members
 * of Rb.Inputs
 */
void cb_get_Inputs();

/**
 * This function writes physical output values from the corresponding members of
 * Wb.Outputs
 */
void cb_set_Outputs(void);

/**
 * This function sets an application loop callback function.
 */
void set_application_loop_hook(void (*callback)(void));

/**
 * Main function for SOES application
 */
void soes(void);

/**
 * Initialize the SOES stack
 */

void soes_init(void);


#endif /* SOES_H */
