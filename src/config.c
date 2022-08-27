#include "config.h"
#include "../library/ini.h"
#include <stdlib.h>
#include <string.h>

const char *argp_program_version =
  VERSION;
const char *argp_program_bug_address =
  "<decator.c@proton.me>";

static char *get_color(const char *value) {
  if (strcmp(value, "red") == 0) {
    return RED;
  } else if (strcmp(value, "green") == 0) {
    return GRN;
  } else if (strcmp(value, "yellow") == 0) {
    return YEL;
  } else if (strcmp(value, "blue") == 0) {
    return BLU;
  } else if (strcmp(value, "magenta") == 0) {
    return MAG;
  } else if (strcmp(value, "cyan") == 0) {
    return CYN;
  } else if (strcmp(value, "white") == 0) {
    return WHT;
  } else if (strcmp(value, "black") == 0) {
    return BLK;
  } else if (strcmp(value, "bold red") == 0) {
    return BRED;
  } else if (strcmp(value, "bold green") == 0) {
    return BGRN;
  } else if (strcmp(value, "bold yellow") == 0) {
    return BYEL;
  } else if (strcmp(value, "bold blue") == 0) {
    return BBLU;
  } else if (strcmp(value, "bold magenta") == 0) {
    return BMAG;
  } else if (strcmp(value, "bold cyan") == 0) {
    return BCYN;
  } else if (strcmp(value, "bold white") == 0) {
    return BWHT;
  } else if (strcmp(value, "bold black") == 0) {
    return BBLK;
  } else
    return "";
}

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
  } else if (MATCH("Extra", "DISPLAY_DATES")) {
    if (strcmp(value, "YMD") == 0) {
      pconfig->DISPLAY_DATES_YYYY_MM_DD = true;
    }

    else if (strcmp(value, "MDY") == 0) {
      pconfig->DISPLAY_DATES_YYYY_MM_DD = false;
    }

  } else if (MATCH("Display", "DISPLAY_MOTHERBOARD_INFO")) {
    pconfig->DISPLAY_MOTHERBOARD_INFO =
        (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_LOGO")) {
    pconfig->DISPLAY_LOGO = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_PACKAGES")) {
    pconfig->DISPLAY_PACKAGES = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Color", "IDCOLOR")) {
    pconfig->IDCOLOR = get_color(value);
  } else if (MATCH("Color", "TXTCOLOR")) {
    pconfig->TXTCOLOR = get_color(value);
  } else if (MATCH("Color", "LOGOCOLOR")) {
    pconfig->LOGOCOLOR = get_color(value);
    return 0; /* unknown section/name, error */
  } else if (MATCH("Display", "DISPLAY_USERNAME")) {
    pconfig->DISPLAY_USERNAME = (strcmp(value, "true") == 0) ? true : false;
  } else if (MATCH("Display", "DISPLAY_SHELL")) {
    pconfig->DISPLAY_SHELL = (strcmp(value, "true") == 0) ? true : false;
  } 
  else {
  }
  return 1;
}

int parse_config(configuration *pconfig, char* CONFIG_FILE_NAME, bool silent) {

  configuration config;

  /* Setting the default values for the configuration. */
  config.DISPLAY_CPU_INFO = true;
  config.DISPLAY_ETC_CPU_INFO = true;
  config.DISPLAY_MEMORY_INFO = true;
  config.DISPLAY_MOTHERBOARD_INFO = true;
  config.DISPLAY_HOSTNAME = true;
  config.DISPLAY_UPTIME = true;
  config.DISPLAY_OPERATING_SYSTEM = true;
  config.USE_GIGABYTES = true;
  config.DISPLAY_KERNEL_VERSION = true;
  config.DISPLAY_LOGO = true;
  config.DISPLAY_ROOTFS_BIRTHDAY = true;
  config.DISPLAY_DATES_YYYY_MM_DD = true;
  config.DISPLAY_USERNAME = true;
  config.DISPLAY_PACKAGES = true;
  config.DISPLAY_SHELL = true;
  config.IDCOLOR = BWHT;
  config.TXTCOLOR = WHT;
  config.LOGOCOLOR = WHT;
  

  if (ini_parse(CONFIG_FILE_NAME, handler, &config) < 0 && !silent) {
    fprintf(stderr, "'%s' not found, not loading configuration\n",
            CONFIG_FILE_NAME);
  return 1;
  }

  *pconfig = config;
  return 0;
}