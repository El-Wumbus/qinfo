/*qinfo -- Query (Quick) info fetches system info and displays it.
  Author: Aidan Neal<decator.c@proton.me>
  qinfo is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/
#include "cpu.h"
#include "logo.h"
#include "qinfo.h"
#include <math.h> // Rounding

static struct color col;
static configuration config;

char CONFIG_FILE_NAME[MAXPATH];
static void
initconfig(char *config_file, bool silent)
{
    if (parse_config (&config, config_file, silent) < 0)
        {
            fprintf (stderr, "Critical Error: unexpected error while parsing configuration");
            exit (1);
        }

    col.ansi_id_color = config.IDCOLOR;
    col.ansi_text_color = config.TXTCOLOR;
    col.logo_color = config.LOGOCOLOR;
}

#ifdef __linux__
#include <argp.h>

static struct argp_option options[] = {{"hide_warnings", 's', 0, 0, "Hide any non-critical warnings."},
                                       {"config", 'c', "CONFIG_FILE", 0,
                                        "Use this config file instead of the defualt location."},
                                       {0}};

/*Program documentation. */
static char doc[] = "qinfo -- A system info program. Gets system info and displays it.";

/*A description of the arguments we accept. */
static char args_doc[] = "";

/*Parse a single option. */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
    /*Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 's':
        arguments->silent = true;
        break;
    case 'c':
        arguments->config_file = arg;
        break;
    }

    return 0;
}

/*Our argp parser. */
static struct argp argp = {options, parse_opt, args_doc, doc};

#endif

int main(int argc, char **argv)
{
    struct arguments arguments;

    /*Default values. */
    arguments.silent = false;
    arguments.config_file = CONFIG_FILE_NAME;

#ifdef _WIN32
    char *homedir = getenv("HOMEPATH");
    char *homedrive = getenv("HOMEDRIVE");
    sprintf(CONFIG_FILE_NAME, CONFIGFILE, homedrive, homedir);
    init(); // Do dumb windows API things

    // TODO: support silencing stderr
#else
    /*Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    char *homedir = getenv("HOME");
    sprintf(CONFIG_FILE_NAME, CONFIGFILE, homedir);

    if (arguments.silent)
    {
        freopen("/dev/null", "w", stderr);
    }
#endif

    initconfig(arguments.config_file, arguments.silent);

        int i = 0;
    while (i < 12)
    {

        bool x = config.configuration_array[i];
        switch (i)
        {
        case 0:
            if (x)
            {
                printlogo();
            }
            break;
        case 1:
            if (x)
            {
                printcpuinfo(false);
            }
            break;
        case 2:
            if (x)
            {
                printmem(config.USE_GIGABYTES);
            }
            break;
        case 3:
            if (x)
            {
                printos();
            }
            break;

        case 4:
            if (x)
            {
                printuser();
            }
            break;
        case 5:
            if (x)
            {
                printshell();
            }
            break;
        case 6:
            if (x)
            {
                printhostname();
            }
            break;
        case 7:
            if (x)
            {
                printboard();
            }
            break;
        case 8:
            if (x)
            {
                printrootfsbirth(config.DISPLAY_DATES_YYYY_MM_DD);
            }
            break;
        case 9:
            if (x)
            {
                printuptime();
            }
            break;
        case 10:
            if (x)
            {
                printkernel();
            }
            break;
        case 11:
            if (x)
            {
                printdiskinfo(config.USE_GIGABYTES);
            }
            break;
        case 12:
            if (x)
            {
                printpackages();
            }
            break;
        case 13:
            if (x)
            {
                printcpuinfo(true);
            }
            break;
        i++;
    }
    return 0;
}

static struct uptime
formatted_uptime(long uptime)
{
    struct uptime upt;
    /*Calculating the number of days, hours, minutes and seconds. */
    upt.days = (unsigned int)uptime / SECOND_DAY_CONVERSION;
    upt.hours = (unsigned int)uptime / SECOND_HOUR_CONVERSION % HOUR_DAY_CONVERSION;
    upt.minutes = (unsigned int)uptime / SECOND_MINUTE_CONVERSION % MINUTE_HOUR_CONVERSION;
    upt.seconds = (unsigned int)uptime % SECOND_MINUTE_CONVERSION;
    return upt;
}

static struct packages
formatted_packages(packagecount pacman_packages, packagecount apt_packages,
                   packagecount apk_packages, packagecount flatpak_packages,
                   packagecount snap_packages)
{
    struct packages pkgs;
    pkgs.pacman_packages = (pacman_packages > 0 ? pacman_packages : 0);
    pkgs.apt_packages = (apt_packages > 0 ? apt_packages : 0);
    pkgs.apk_packages = (apk_packages > 0 ? apk_packages : 0);
    pkgs.flatpak_packages = (flatpak_packages > 0 ? flatpak_packages : 0);
    pkgs.snap_packages = (snap_packages > 0 ? snap_packages : 0);
    return pkgs;
}

static char *
new_string()
{
    return malloc(BUFFERSIZE * sizeof(char));
}

static void
printos()
{
    char *os_name = new_string();
    os_name = realloc(os_name, get_operating_system_name(os_name));

    printf("%sOS:%s\t\t%s%s (%s)%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color, os_name,
           OPERATING_SYSTEM, COLOR_END);
    free(os_name);
}

static void
printlogo()
{
    char *os_name = new_string();
    os_name = realloc(os_name, get_operating_system_name(os_name));

    if (strcmp(os_name, "Arch Linux") == 0)
    {
        printf("%s%s%s\n", col.logo_color, logo_arch, COLOR_END);
    }
    else if (strstr(os_name, "Alpine Linux") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, alpine_logo, COLOR_END);
    }
    else if (strstr(os_name, "Arco Linux") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, arcolinux_logo, COLOR_END);
    }
    else if (strcmp(os_name, "Aritx Linux") == 0)
    {
        printf("%s%s%s\n", col.logo_color, artix_logo, COLOR_END);
    }
    else if (strstr(os_name, "Bedrock Linux") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, bedrock_logo, COLOR_END);
    }
    else if (strstr(os_name, "Gentoo") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, gentoo_logo, COLOR_END);
    }
    else if (strstr(os_name, "Ubuntu") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, ubuntu_logo, COLOR_END);
    }
    else if (strstr(os_name, "Windows 10") != NULL)
    {
        printf("%s%s%s\n", col.logo_color, windows10_logo, COLOR_END);
    }
    else
    {
        printf("%s%s%s\n", col.logo_color, generic_logo, COLOR_END);
    }

    free(os_name);
}

static void
printcpuinfo(bool extra)
{
    if (extra)
    {
        printf("%sEXTRA CPU INFO:%s%s Model number 0x%X, Family Value: 0x%X%s\n",
               col.ansi_id_color, COLOR_END, col.ansi_text_color, cpu_get_modelnum(),
               cpu_get_family_value(), COLOR_END);
    }
    else
    {
        char *cpu_model = new_string();
        cpu_model = realloc(cpu_model, get_cpu_model(cpu_model));

        unsigned int core_count = 0;
        unsigned int thread_count = 0;
        core_count = get_core_count();
        thread_count = get_thread_count();
        printf("%sCPU:%s\t\t%s%s (%u cores, %u threads)%s\n", col.ansi_id_color, COLOR_END,
               col.ansi_text_color, cpu_model, core_count, thread_count, COLOR_END);
        free(cpu_model);
    }
}

static void
printmem(bool gigs)
{
    char unit[3];
    float available_memory, used_memory = 0, total_memory = 0;

    available_memory = (float)get_avalible_memory();
    total_memory = (float)get_total_memory();
    used_memory = total_memory - available_memory;

    if (gigs)
    {
        used_memory = ((total_memory - available_memory) / (float)KILOBYTE_GIGABYTE_CONVERSION);
        total_memory = get_total_memory() / (float)KILOBYTE_GIGABYTE_CONVERSION;
        strcpy(unit, "GB");
    }
    else
    {
        strcpy(unit, "kB");
    }

    printf("%sRAM:%s\t\t%s%.2f/%.2f %s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color,
           used_memory, total_memory, unit, COLOR_END);
}

static void
printuser()
{
    char *username = get_username();
    printf("%sUser:%s%s\t\t%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color, username,
           COLOR_END);
}

static void
printshell()
{
    char *shell = new_string();
    shell = realloc(shell, get_shell_name(shell));
    printf("%sShell:%s%s\t\t%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color, shell,
           COLOR_END);
    free(shell);
}

static void
printhostname()
{
    char *hostname = malloc(sizeof(char) * BUFFERSIZE);
    hostname = realloc(hostname, get_hostname(hostname));
    printf("%sHostname:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color, hostname,
           COLOR_END);
    free(hostname);
}

static void
printboard()
{
    char *motherboard_info = new_string();
    motherboard_info = realloc(motherboard_info, get_board_model(motherboard_info));

    printf("%sMotherboard:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color,
           motherboard_info, COLOR_END);
    free(motherboard_info);
}

static void
printrootfsbirth(bool format)
{
    struct date rootfsage = get_creation_date();

    printf("%sROOTFS BIRTH:%s%s\t", col.ansi_id_color, COLOR_END, col.ansi_text_color);
    if (format)
    {
        printf("%d/%d/%d%s\n", rootfsage.year, rootfsage.month, rootfsage.day, COLOR_END);
    }
    else
    {
        printf("%d/%d/%d%s\n", rootfsage.month, rootfsage.day, rootfsage.year, COLOR_END);
    }
}

static void
printuptime()
{
    long uptime = get_uptime();
    struct uptime upt = formatted_uptime(uptime);

    printf("%sUptime:%s%s\t\t", col.ansi_id_color, COLOR_END, col.ansi_text_color);
    if (upt.days > 0)
    {
        printf("%u days ", upt.days);
    }

    if (upt.hours > 0)
    {
        printf("%u hours ", upt.hours);
    }

    if (upt.minutes > 0)
    {
        printf("%u minutes ", upt.minutes);
    }

    if (upt.seconds > 0)
    {
        printf("%u seconds", upt.seconds);
    }

    printf("%s\n", COLOR_END);
}

static void
printkernel()
{
    char *kernel_version = new_string();
    kernel_version = realloc(kernel_version, get_kernel_release(kernel_version));

    if (strcmp(kernel_version, "") == 0)
    {
        strcpy(kernel_version, "Unknown");
    }

    printf("%sKernel:%s\t\t%s%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color,
           kernel_version, COLOR_END);
    free(kernel_version);
}

static void
printpackages()
{
    struct packages pkgs;
    pkgs = formatted_packages(
        get_num_packages(PACMAN_PACKAGE_MANAGER), get_num_packages(APT_PACKAGE_MANAGER),
        get_num_packages(APK_PACKAGE_MANAGER), get_num_packages(FLATPAK_PACKAGE_MANAGER),
        get_num_packages(SNAP_PACKAGE_MANAGER));

    printf("%sPackages:%s\t%s", col.ansi_id_color, COLOR_END, col.ansi_text_color);
    if (pkgs.pacman_packages > 0)
    {
        printf("%lu (Pacman) ", pkgs.pacman_packages);
    }

    if (pkgs.apt_packages > 0)
    {
        printf("%lu (Apt) ", pkgs.apt_packages);
    }

    if (pkgs.apk_packages > 0)
    {
        printf("%lu (Apk)", pkgs.apk_packages);
    }

    if (pkgs.flatpak_packages > 0)
    {
        printf("%lu (Flatpak)", pkgs.flatpak_packages);
    }

    if (pkgs.snap_packages > 0)
    {
        printf("%lu (Snap)", pkgs.snap_packages);
    }

    printf("%s\n", COLOR_END);
}

static void
printdiskinfo(bool gigs)
{
    char **data = calloc(2, sizeof(char *));
    // if there's data in the second array, 'home' will be '1'.
    // Otherwise 'home' will be '0'.
    short int home = get_disk_usage(data, gigs);
    if (home == -2)
    {
        free(data);
        return;
    }
    if (home < 0)
    {
        fprintf(stderr, "ERROR: couldn't get disk usage.");
        return;
    }

    printf("%sRoot Usage:%s\t%s%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color, data[0],
           COLOR_END);

    if (home)
    {
        printf("%sHome Usage:%s\t%s%s%s\n", col.ansi_id_color, COLOR_END, col.ansi_text_color,
               data[1], COLOR_END);
    }

    for (iter i = 0; i < 2; i++)
    {
        free(data[i]);
    }

    free(data);
}