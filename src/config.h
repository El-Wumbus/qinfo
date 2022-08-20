#ifndef  CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
#define MAX_PATH 2048
#include <stdbool.h>

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
} configuration;

int parse_config();

#endif /* CONFIG_H */
