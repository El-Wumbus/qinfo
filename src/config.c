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
        pconfig->DISPLAY_DATES_YYYY_MM_DD = (strcmp(value, "YMD") == 0) ? true : false;
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
    return 1;
}

int parse_config(configuration *pconfig, char *config_file_name, bool silent)
{

    configuration config;

    /* Setting the default values for the configuration. */
    DISPLAY_CPU_INFO = true;
    DISPLAY_ETC_CPU_INFO = false;
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

    for (int i = 0; i < 12; i++)
    {

        switch (i)
        {
        case 0:
            config.configuration_array[i] = DISPLAY_LOGO;
            break;
        case 1:
            config.configuration_array[i] = DISPLAY_CPU_INFO;
            break;
        case 2:
            config.configuration_array[i] = DISPLAY_MEMORY_INFO;
            break;
        case 3:
            config.configuration_array[i] = DISPLAY_OPERATING_SYSTEM;
            break;
        case 4:
            config.configuration_array[i] = DISPLAY_USERNAME;
            break;
        case 5:
            config.configuration_array[i] = DISPLAY_SHELL;
            break;
        case 6:
            config.configuration_array[i] = DISPLAY_HOSTNAME;
            break;
        case 7:
            config.configuration_array[i] = DISPLAY_MOTHERBOARD_INFO;
            break;
        case 8:
            config.configuration_array[i] = DISPLAY_ROOTFS_BIRTHDAY;
            break;
        case 9:
            config.configuration_array[i] = DISPLAY_UPTIME;
            break;
        case 10:
            config.configuration_array[i] = DISPLAY_KERNEL_VERSION;
            break;
        case 11:
            config.configuration_array[i] = DISPLAY_DISK_USAGE;
            break;
        case 12:
            config.configuration_array[i] = DISPLAY_PACKAGES;
            break;
        case 13:
            config.configuration_array[i] = DISPLAY_ETC_CPU_INFO;
            break;
        case 14:
            config.configuration_array[i] = DISPLAY_PACKAGES;
            break;
        }
    }
    *pconfig = config;
    return 0;
}