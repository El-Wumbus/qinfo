#include "../library/ini.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = VERSION;
const char *argp_program_bug_address = "<decator.c@proton.me>";

static char *
get_color(const char *value)
{
    if (strcmp(value, "red") == 0)
    {
        return RED;
    }
    else if (strcmp(value, "green") == 0)
    {
        return GRN;
    }
    else if (strcmp(value, "yellow") == 0)
    {
        return YEL;
    }
    else if (strcmp(value, "blue") == 0)
    {
        return BLU;
    }
    else if (strcmp(value, "magenta") == 0)
    {
        return MAG;
    }
    else if (strcmp(value, "cyan") == 0)
    {
        return CYN;
    }
    else if (strcmp(value, "white") == 0)
    {
        return WHT;
    }
    else if (strcmp(value, "black") == 0)
    {
        return BLK;
    }
    else if (strcmp(value, "bold red") == 0)
    {
        return BRED;
    }
    else if (strcmp(value, "bold green") == 0)
    {
        return BGRN;
    }
    else if (strcmp(value, "bold yellow") == 0)
    {
        return BYEL;
    }
    else if (strcmp(value, "bold blue") == 0)
    {
        return BBLU;
    }
    else if (strcmp(value, "bold magenta") == 0)
    {
        return BMAG;
    }
    else if (strcmp(value, "bold cyan") == 0)
    {
        return BCYN;
    }
    else if (strcmp(value, "bold white") == 0)
    {
        return BWHT;
    }
    else if (strcmp(value, "bold black") == 0)
    {
        return BBLK;
    }
    else
        return "";
}

static bool DISPLAY_CPU_INFO, DISPLAY_ETC_CPU_INFO, DISPLAY_MEMORY_INFO,
    DISPLAY_HOSTNAME, DISPLAY_UPTIME, DISPLAY_OPERATING_SYSTEM, DISPLAY_USERNAME,
    DISPLAY_KERNEL_VERSION, DISPLAY_ROOTFS_BIRTHDAY, DISPLAY_MOTHERBOARD_INFO,
    DISPLAY_LOGO, DISPLAY_PACKAGES, DISPLAY_SHELL, DISPLAY_DISK_USAGE;

static int
handler(void *user, const char *section, const char *name, const char *value)
{
    configuration *pconfig = (configuration *)user;

    if (MATCH("Display", "DISPLAY_CPU_INFO"))
    {
        DISPLAY_CPU_INFO = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_EXTRA_CPU_INFO"))
    {
        DISPLAY_ETC_CPU_INFO = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_MEMORY_INFO"))
    {
        DISPLAY_MEMORY_INFO = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_HOSTNAME"))
    {
        DISPLAY_HOSTNAME = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_UPTIME"))
    {
        DISPLAY_UPTIME = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_OPERATING_SYSTEM"))
    {
        DISPLAY_OPERATING_SYSTEM = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Extra", "USE_GIGABYTES"))
    {
        pconfig->USE_GIGABYTES = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_KERNEL_VERSION"))
    {
        DISPLAY_KERNEL_VERSION = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_ROOTFS_BIRTHDAY"))
    {
        DISPLAY_ROOTFS_BIRTHDAY = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Extra", "DISPLAY_DATES"))
    {
        if (strcmp(value, "YMD") == 0)
        {
            pconfig->DISPLAY_DATES_YYYY_MM_DD = true;
        }

        else if (strcmp(value, "MDY") == 0)
        {
            pconfig->DISPLAY_DATES_YYYY_MM_DD = false;
        }
    }
    else if (MATCH("Display", "DISPLAY_MOTHERBOARD_INFO"))
    {
        DISPLAY_MOTHERBOARD_INFO = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_LOGO"))
    {
        DISPLAY_LOGO = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_PACKAGES"))
    {
        DISPLAY_PACKAGES = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Color", "IDCOLOR"))
    {
        pconfig->IDCOLOR = get_color(value);
    }
    else if (MATCH("Color", "TXTCOLOR"))
    {
        pconfig->TXTCOLOR = get_color(value);
    }
    else if (MATCH("Color", "LOGOCOLOR"))
    {
        pconfig->LOGOCOLOR = get_color(value);
        return 0; /* unknown section/name, error */
    }
    else if (MATCH("Display", "DISPLAY_USERNAME"))
    {
        DISPLAY_USERNAME = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_SHELL"))
    {
        DISPLAY_SHELL = (strcmp(value, "true") == 0) ? true : false;
    }
    else if (MATCH("Display", "DISPLAY_DISK_USAGE"))
    {
        DISPLAY_DISK_USAGE = (strcmp(value, "true") == 0) ? true : false;
    }
    else
    {
    }
    return 1;
}

int parse_config(configuration *pconfig, char *config_file_name, bool silent)
{

    configuration config;

    /* Setting the default values for the configuration. */
    DISPLAY_CPU_INFO = true;
    DISPLAY_ETC_CPU_INFO = true;
    DISPLAY_MEMORY_INFO = true;
    DISPLAY_MOTHERBOARD_INFO = true;
    DISPLAY_HOSTNAME = true;
    DISPLAY_UPTIME = true;
    DISPLAY_OPERATING_SYSTEM = true;
    config.USE_GIGABYTES = true;
    DISPLAY_KERNEL_VERSION = true;
    DISPLAY_LOGO = true;
    DISPLAY_ROOTFS_BIRTHDAY = true;
    config.DISPLAY_DATES_YYYY_MM_DD = true;
    DISPLAY_USERNAME = true;
    DISPLAY_PACKAGES = true;
    DISPLAY_SHELL = true;
    DISPLAY_DISK_USAGE = true;
    config.IDCOLOR = BWHT;
    config.TXTCOLOR = WHT;
    config.LOGOCOLOR = WHT;

    if (ini_parse(config_file_name, handler, &config) < 0 && !silent)
    {
        fprintf(stderr, "'%s' not found, not loading configuration\n", config_file_name);
        return 1;
    }


    int i = 0;
    while (i < 12)
    {

        switch (i)
        {
        case 0:
            if (DISPLAY_LOGO)
                config.configuration_array[i] = true;
            break;
        case 1:
            if (DISPLAY_CPU_INFO)
                config.configuration_array[i] = true;
            break;
        case 2:
            if (DISPLAY_MEMORY_INFO)
                config.configuration_array[i] = true;
            break;
        case 3:
            if (DISPLAY_OPERATING_SYSTEM)
                config.configuration_array[i] = true;
            break;
        case 4:
            if (DISPLAY_USERNAME)
                config.configuration_array[i] = true;
            break;
        case 5:
            if (DISPLAY_SHELL)
                config.configuration_array[i] = true;
            break;
        case 6:
            if (DISPLAY_HOSTNAME)
                config.configuration_array[i] = true;
            break;
        case 7:
            if (DISPLAY_MOTHERBOARD_INFO)
                config.configuration_array[i] = true;
            break;
        case 8:
            if (DISPLAY_ROOTFS_BIRTHDAY)
                config.configuration_array[i] = true;
            break;
        case 9:
            if (DISPLAY_UPTIME)
                config.configuration_array[i] = true;
            break;
        case 10:
            if (DISPLAY_KERNEL_VERSION)
                config.configuration_array[i] = true;
            break;
        case 11:
            if (DISPLAY_DISK_USAGE)
                config.configuration_array[i] = true;
            break;
        case 12:
            if (DISPLAY_PACKAGES)
                config.configuration_array[i] = true;
            break;
        case 13:
            if (DISPLAY_ETC_CPU_INFO)
                config.configuration_array[i] = true;
            break;
        }
        i++;
    }
    *pconfig = config;
    return 0;
}