#ifndef CONFIG_H
#define CONFIG_H
#include "color.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXPATH 2048
#define MATCH(s, n) strcmp (section, s) == 0 && strcmp (name, n) == 0
#define VERSION "qinfo 0.0.1"
#ifdef _WIN32
#define CONFIGFILE "%s%s\\Documents\\qinfo.ini"
#else
#define CONFIGFILE "%s/.config/.qinfo.conf"
#endif

/* A macro that compares the section and name to the strings passed in. */

typedef struct
{
    bool configuration_array[14];
    bool USE_GIGABYTES;
    bool DISPLAY_DATES_YYYY_MM_DD;
    char *IDCOLOR;
    char *TXTCOLOR;
    char *LOGOCOLOR;
} configuration;

int parse_config (configuration *pconfig, char *config_location, bool silent);

#endif /* CONFIG_H */
