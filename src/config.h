#ifndef  CONFIG_H
#define CONFIG_H

#include <stdbool.h>



/* Display cpu name and core/thread info */
bool DISPLAY_CPU_INFO         = true;

/* Display memory capacity and usage ratio */
bool DISPLAY_MEMORY_INFO      = true;

/* Display the computer's hostname */
bool DISPLAY_HOSTNAME         = true;

/* Display the system uptime */
bool DISPLAY_UPTIME           = true;

/* Display the operating system name */
bool DISPLAY_OPERATING_SYSTEM = true;

/* measure memory in gigabytes instead of kilobytes */
bool USE_GIGABYTES            = true;

/* Only supported properly on unix-like operating systems */
bool DISPLAY_KERNEL_VERSION   = true;

#endif /* CONFIG_H */