#ifndef  CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#define MAX_PATH 2048
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
#define VERSION "qinfo 0.0.1"
/* A macro that compares the section and name to the strings passed in. */

typedef struct {
  bool DISPLAY_CPU_INFO;
  bool DISPLAY_ETC_CPU_INFO;
  bool DISPLAY_MEMORY_INFO;
  bool DISPLAY_HOSTNAME;
  bool DISPLAY_UPTIME;
  bool DISPLAY_OPERATING_SYSTEM;
  bool USE_GIGABYTES;
  bool DISPLAY_KERNEL_VERSION;
  bool DISPLAY_ROOTFS_BIRTHDAY;
  bool DISPLAY_DATES_YYYY_MM_DD;
  bool DISPLAY_MOTHERBOARD_INFO;
  bool DISPLAY_LOGO;
  bool DISPLAY_USERNAME;
  bool DISPLAY_PACKAGES;
  bool DISPLAY_SHELL;
  bool DISPLAY_DISK_USAGE;
  char* IDCOLOR;
  char* TXTCOLOR;
  char *LOGOCOLOR;
} configuration;

int parse_config(configuration *pconfig, char *config_location, bool silent);

#endif /* CONFIG_H */
