#ifndef CPU_H
#define CPU_H

/*  
 *  Fetches CPU model number.
 *
 */

#include <stdint.h>
int cpu_get_modelnum(void);
int cpu_get_family_value(void);

#endif
