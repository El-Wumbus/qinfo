#include "config.h"
#include "../library/ini.h"
#include <stdlib.h>
#include <string.h>

static int handler(void *user, const char *section, const char *name,
                   const char *value) {
  configuration *pconfig = (configuration *)user;

  if (MATCH("Display", "DISPLAY_CPU_INFO")) {
    pconfig->DISPLAY_CPU_INFO = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_EXTRA_CPU_INFO")) {
    pconfig->DISPLAY_ETC_CPU_INFO = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_MEMORY_INFO")) {
    pconfig->DISPLAY_MEMORY_INFO = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_HOSTNAME")) {
    pconfig->DISPLAY_HOSTNAME = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_UPTIME")) {
    pconfig->DISPLAY_UPTIME = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_OPERATING_SYSTEM")) {
    pconfig->DISPLAY_OPERATING_SYSTEM =
        (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Extra", "USE_GIGABYTES")) {
    pconfig->USE_GIGABYTES = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_KERNEL_VERSION")) {
    pconfig->DISPLAY_KERNEL_VERSION =
        (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_ROOTFS_BIRTHDAY")) {
    pconfig->DISPLAY_ROOTFS_BIRTHDAY =
        (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Extra", "DISPLAY_DATES_YYYY_MM_DD")) {
    pconfig->DISPLAY_DATES_YYYY_MM_DD =
        (strcmp(value, "true") == 0) ? true : false;
  } else {
    return 0; /* unknown section/name, error */
  }
  return 1;
}

int parse_config(configuration *pconfig) {

char *homedir = getenv("HOME");
char CONFIG_FILE_NAME[MAX_PATH];
sprintf(CONFIG_FILE_NAME, "%s/.config/.qinfo.conf", homedir);

  configuration config;
  config.DISPLAY_CPU_INFO = true;
  config.DISPLAY_ETC_CPU_INFO = true;
  config.DISPLAY_MEMORY_INFO = true;
  config.DISPLAY_HOSTNAME = true;
  config.DISPLAY_UPTIME = true;
  config.DISPLAY_OPERATING_SYSTEM = true;
  config.USE_GIGABYTES = true;
  config.DISPLAY_KERNEL_VERSION = true;
  config.DISPLAY_ROOTFS_BIRTHDAY = true;
  config.DISPLAY_DATES_YYYY_MM_DD = true;
  if (ini_parse(CONFIG_FILE_NAME, handler, &config) < 0) {
    fprintf(stderr, "'%s' not found, not loading configuration\n", CONFIG_FILE_NAME);
  }
/*
  printf("DISPLAY_CPU_INFO=%d\n", config.DISPLAY_CPU_INFO);
  printf("DISPLAY_ETC_CPU_INFO=%d\n", config.DISPLAY_ETC_CPU_INFO);
  printf("DISPLAY_MEMORY_INFO=%d\n", config.DISPLAY_MEMORY_INFO);
  printf("DISPLAY_HOSTNAME=%d\n", config.DISPLAY_HOSTNAME);
  printf("DISPLAY_UPTIME=%d\n", config.DISPLAY_UPTIME);
  printf("DISPLAY_OPERATING_SYSTEM=%d\n", config.DISPLAY_OPERATING_SYSTEM);
  printf("USE_GIGABYTES=%d\n", config.USE_GIGABYTES);
  printf("DISPLAY_KERNEL_VERSION=%d\n", config.DISPLAY_KERNEL_VERSION);
  printf("DISPLAY_ROOTFS_BIRTHDAY=%d\n", config.DISPLAY_ROOTFS_BIRTHDAY);
  printf("DISPLAY_DATES_YYYY_MM_DD=%d\n", config.DISPLAY_DATES_YYYY_MM_DD); */

  *pconfig = config;
  return 0;
}