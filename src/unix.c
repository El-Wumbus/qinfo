#include "unix.h"
#include <math.h>
#include <stdlib.h>
/*
Author: Aidan Neal <decator.c@proton.me>
  qinfo is free software; you can redistribute it and/or
    modify it under the processs of the GNU Lesser General Public
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

/**
 * @brief Get the number of cores
 *
 * @return unsigned int
 */
unsigned int
get_core_count (void)
{
    /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info.
     */
    FILE *cpu_info = fopen ("/proc/cpuinfo", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 0. */
    if (cpu_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/cpuinfo\n");
            return 0;
        }
    unsigned int core_count;
    while (!fscanf (cpu_info, "cpu cores\t: %u", &core_count))
        fscanf (cpu_info, "%*[^c]");
    fclose (cpu_info);

    return core_count;
}

/**
 * @brief Get the thread count
 *
 * @return unsigned int
 */
unsigned int
get_thread_count (void)
{
    /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info.
     */
    FILE *cpu_info = fopen ("/proc/cpuinfo", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 0. */
    if (cpu_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/cpuinfo\n");
            return 0;
        }

    /* Reading the file until it finds the line that starts with "siblings:". */
    unsigned int thread_count;
    while (!fscanf (cpu_info, "siblings\t: %u", &thread_count))
        fscanf (cpu_info, "%*[^s]");
    fclose (cpu_info);

    return thread_count;
}

/**
 * @brief Get the total memory
 *
 * @return unsigned int
 */
int
get_total_memory (void)
{
    /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
     */
    FILE *mem_info = fopen ("/proc/meminfo", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 0. */
    if (mem_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/meminfo\n");
            return 0;
        }

    int total_memory;

    /* Reading the file until it finds the line that starts with "MemTotal:". */
    while (!fscanf (mem_info, "MemTotal:\t%u kB", &total_memory))
        fscanf (mem_info, "%*[^m]");
    fclose (mem_info);

    return total_memory;
}

/**
 * @brief Get the avalible memory
 *
 * @return int
 */
int
get_avalible_memory (void)
{
    /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
     */
    FILE *mem_info = fopen ("/proc/meminfo", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 0. */
    if (mem_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/meminfo\n");
            return 0;
        }

    int avalible_memory;
    while (!fscanf (mem_info, "MemAvailable:\t%u kB", &avalible_memory))
        fscanf (mem_info, "%*[^M]");
    fclose (mem_info);

    return avalible_memory;
}

long
get_uptime (void)
{
    FILE *uptime_file = fopen ("/proc/uptime", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 0. */
    if (uptime_file == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/uptime\n");
            return 0;
        }

    float uptime;
    while (!fscanf (uptime_file, "%f", &uptime))
        fscanf (uptime_file, "%*[^ ]");
    fclose (uptime_file);

    return (uptime);
}

/**
 * @brief Get the cpu model object
 *
 * @param storage_variable
 * @return int
 */
size_t
get_cpu_model (char *dest)
{
    /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
     */
    FILE *cpu_info = fopen ("/proc/cpuinfo", "r");

    /* Checking if the file was opened successfully. If it was not, it prints an
     * error message and returns 1. */
    if (cpu_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/cpuinfo\n");
            strcpy (dest, "(ERR)");
            return 6 * sizeof (char);
        }

    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));

    /* Reading the file until it finds the line that starts with "model name:". */
    while (!fscanf (cpu_info, "model name\t: %99[^\n]", buffer))
        fscanf (cpu_info, "%*[^m]");
    fclose (cpu_info);
    size_t len = (strlen (buffer) + 1) * sizeof (char);
    strcpy (dest, buffer);
    free (buffer);
    return len;
}

/**
 * @brief Get the operating system name
 *
 * @return char*
 */
size_t
get_operating_system_name (char *dest)
{
    FILE *os_info = fopen ("/bedrock/etc/os-release", "r");

    // For bedrock users
    if (os_info != NULL)
        {
            char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
            while (!fscanf (os_info, "NAME=\"%[^\"]\"", buffer))
                {
                    fscanf (os_info, "%*[^P]");
                }
            fclose (os_info);

            strcpy (dest, buffer);
            return (strlen (buffer) + 1) * sizeof (char);
        }

    os_info = fopen ("/etc/os-release", "r");

    if (os_info == NULL)
        {
            fprintf (stderr, "Error: Could not open /etc/os-release\n");
            strcpy (dest, "(ERR)");
            return 6 * sizeof (char);
        }

    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
    while (!fscanf (os_info, "PRETTY_NAME=\"%[^\"]\"", buffer))
        {
            fscanf (os_info, "%*[^P]");
        }
    fclose (os_info);

    strcpy (dest, buffer);
    size_t len = (strlen (buffer) + 1) * sizeof (char);
    free (buffer);
    return len;
}

/**
 * @brief Get the system hostname
 *
 * @param storage_variable
 * @return int
 */
size_t
get_hostname (char *dest)
{
    FILE *hostname_file = fopen ("/proc/sys/kernel/hostname", "r");

    if (hostname_file == NULL)
        {
            fprintf (stderr, "Error: Could not open /proc/sys/kernel/hostname\n");
            strcpy (dest, "(ERR)");
            return 6 * sizeof (char);
        }

    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
    while (!fscanf (hostname_file, "%99[^\n]", buffer))
        fscanf (hostname_file, "%*[^\n]");
    fclose (hostname_file);

    strcpy (dest, buffer);
    size_t len = (strlen (buffer) + 1) * sizeof (char);

    free (buffer);
    return len;
}

/**
 * @brief Return a string containing the sysname and release data from uname
 * system call
 *
 * @param dest
 * @return size_t
 */
size_t
get_kernel_release (char *dest)
{
    struct utsname unameData;

    if (uname (&unameData) != 0)
        {
            perror ("uname");
            strcpy (dest, "(ERR)");
            return 6 * sizeof (char);
        }
    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
    sprintf (buffer, "%s %s", unameData.sysname, unameData.release);

    strcpy (dest, buffer);
    size_t len = (strlen (buffer) + 1) * sizeof (char);
    free (buffer);

    return len;
}

/**
 * It reads the contents of the file `/sys/devices/virtual/dmi/id/board_name`
 * and returns the contents as a string
 *
 * @return The board name of the system.
 */
static char *
get_board_name (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen ("/sys/devices/virtual/dmi/id/board_name", "r");
    if (fp == NULL)
        {
            fprintf (stderr, "Error: couldn't open '/sys/devices/virtual/dmi/id/board_name'\n");
            return ("(ERR)");
        }

    if ((read = getline (&line, &len, fp)) != -1)
        {
            fclose (fp);
            for (register iter i = 0; i < len; i++)
                {
                    if (line[i] == '\n')
                        {
                            line[i] = '\0';
                            break;
                        }
                }
            return line;
        }

    fclose (fp);
    return NULL;
}

/**
 * It opens a file, reads a line, and returns the line
 *
 * @return The board vendor name.
 */
static char *
get_board_vendor (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen ("/sys/devices/virtual/dmi/id/board_vendor", "r");
    if (fp == NULL)
        {
            fprintf (stderr, "Failed to get '/sys/devices/virtual/dmi/id/board_vendor'\n");
            return "(ERR)";
        }

    if ((read = getline (&line, &len, fp)) != -1)
        {
            fclose (fp);
            for (register iter i = 0; i < len; i++)
                {
                    if (line[i] == '\n')
                        {
                            line[i] = '\0';
                            break;
                        }
                }
            return line;
        }

    fclose (fp);
    return NULL;
}

/**
 * It takes a string, and copies the board name and vendor into it
 *
 * @param storage_variable The variable to store the board model in.
 */
size_t
get_board_model (char *dest)
{
    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
    sprintf (buffer, "%s (%s)", get_board_name (), get_board_vendor ());
    buffer = (char *)realloc (buffer, (strlen (buffer) + 1) * sizeof (char));
    strcpy (dest, buffer);
    size_t len = (strlen (buffer) + 1) * sizeof (char);
    free (buffer);

    return len;
}

/**
 * It gets the creation date of the file system and stores it in a struct date
 *
 * @param storage_variable A pointer to a struct date variable that will be used
 * to
 *
 * @return The date of the file system's creation.
 */
struct date
get_creation_date (void)
{
    struct statx stx;
    mstatx (AT_FDCWD, "/", AT_STATX_SYNC_AS_STAT, STATX_BTIME, &stx);
    time_t epochtime = stx.stx_btime.tv_sec;
    struct tm t;
    char buf[11];
    struct date fs_birthdate;

    t = *localtime (&epochtime);
    strftime (buf, sizeof (buf), "%Y %m %d", &t);

    sscanf (buf, "%u %u %u", &fs_birthdate.year, &fs_birthdate.month, &fs_birthdate.day);
    return fs_birthdate;
}

char *
get_username (void)
{
    char *buf = getenv ("USER");
    if (buf == NULL)
        {
            register uid_t uid = getuid ();
            register struct passwd *pw = getpwuid (uid);
            if (pw)
                {
                    return pw->pw_name;
                }
        }
    return buf;
}

static packagecount
get_num_packages_dpkg (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long num_packages = 0;
    fp = popen ("apt list --installed 2>/dev/null", "r");
    if (fp == NULL)
        {
            return 0;
        }
    while ((read = getline (&line, &len, fp)) != -1)
        {
            num_packages++;
        }
    pclose (fp);
    if (num_packages > 0)
        {
            return num_packages - 1;
        }
    return num_packages;
}

static packagecount
get_num_packages_apk (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long num_packages = 0;
    fp = popen ("apk info 2> /dev/null", "r");
    if (fp == NULL)
        {
            return (0);
        }
    while ((read = getline (&line, &len, fp)) != -1)
        {
            num_packages++;
        }
    pclose (fp);
    if (line)
        {
            free (line);
        }
    return num_packages;
}

static packagecount
get_num_packages_pacman (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long num_packages = 0;
    fp = popen ("pacman -Q 2> /dev/null", "r");
    if (fp == NULL)
        {
            return (0);
        }
    while ((read = getline (&line, &len, fp)) != -1)
        {
            num_packages++;
        }
    pclose (fp);
    if (line)
        {
            free (line);
        }
    return num_packages;
}

static packagecount
get_num_packages_flatpak (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long num_packages = 0;
    fp = popen ("flatpak list 2> /dev/null", "r");
    if (fp == NULL)
        {
            return (0);
        }
    while ((read = getline (&line, &len, fp)) != -1)
        {
            num_packages++;
        }
    pclose (fp);
    if (line)
        {
            free (line);
        }
    return num_packages;
}

static packagecount
get_num_packages_snap (void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    packagecount num_packages = 0;
    fp = popen ("snap list 2> /dev/null", "r");
    if (fp == NULL)
        {
            return (0);
        }
    while ((read = getline (&line, &len, fp)) != -1)
        {
            num_packages++;
        }
    pclose (fp);
    if (line)
        {
            free (line);
        }
    if (num_packages > 0)
        {
            return num_packages - 1;
        }
    return num_packages;
}

static void
return_base (char *chararr, char *storage_variable)
{
    char *token;
    char *buffer = (char *)calloc (BUFFERSIZE, sizeof (char));
    char *rest = chararr;
    while ((token = strtok_r (rest, "/", &rest)))
        {
            strcpy (buffer, token);
        }
    strcpy (storage_variable, buffer);
    free (buffer);
    return;
}

size_t
get_shell_name (char *dest)
{
    char *shell = getenv ("0");
    if (shell != NULL)
        {
            if (strstr (shell, "/"))
                {
                    return_base (shell, shell);
                }
            char *shellname = (char *)calloc ((strlen (shell) + 1), sizeof (char));
            strcpy (shellname, shell);
            return ((strlen (shell) + 1) * sizeof (char));
        }

    int ppid = getppid ();
    char *token;
    char *process = calloc (BUFFERSIZE, sizeof (char));
    char *buffer = calloc (BUFFERSIZE, sizeof (char));

    if (!buffer || !process)
        {
            perror ("calloc");
            exit (EXIT_FAILURE);
        }
    sprintf (buffer, "/proc/%d/exe", ppid);
    while (strcmp (process, "") == 0)
        if (readlink (buffer, process, BUFFERSIZE - 1) < 0)
            {
                perror ("readlink");
                exit (1);
            }
    free (buffer);

    char *tokbuffer = calloc (BUFFERSIZE, sizeof (char));
    char *rest = process;
    while ((token = strtok_r (rest, "/", &rest)))
        {
            strcpy (tokbuffer, token);
        }

    strcpy (dest, tokbuffer);
    return (strlen (tokbuffer) + 1) * sizeof (char);
}

packagecount
get_num_packages (unsigned short package_manager_id)
{
    switch (package_manager_id)
        {
        case PACMAN_PACKAGE_MANAGER:
            return get_num_packages_pacman ();
            break;
        case APT_PACKAGE_MANAGER:
            return get_num_packages_dpkg ();
            break;
        case APK_PACKAGE_MANAGER:
            return get_num_packages_apk ();
            break;
        case FLATPAK_PACKAGE_MANAGER:
            return get_num_packages_flatpak ();
            break;
        case SNAP_PACKAGE_MANAGER:
            return get_num_packages_snap ();
            break;
        }
    return 0;
}

static short int
df (const char *path, struct statvfs *dest)
{
    struct statvfs stat;

    if (statvfs (path, &stat) != 0)
        {
            perror ("statvfs");
            return -1;
        }

    *dest = stat;
    return 0;
}

short
get_disk_usage (char **dest, bool gigs)
{
    char unit[3] = "GB";
    // Make and the matrix for storing output
    char **output = calloc (2, sizeof (char *));

    if (!output)
        {
            perror ("calloc");
            exit (EXIT_FAILURE);
        }

    for (register iter i = 0; i < 2; i++)
        {
            output[i] = calloc (BUFFERSIZE, sizeof (char));
            if (!output[i])
                {
                    perror ("calloc");
                    exit (EXIT_FAILURE);
                }
        }

    // Get root info
    struct statvfs info;

    if (df ("/", &info) < 0)
        {
            return -1;
        }

    // Get /home info, if /home is the same device as root,
    // ensure no home info is reported
    struct statvfs homeinfo;
    if (df ("/home", &homeinfo) < 0)
        {
            return -1;
        }
    bool home = true;
    if (info.f_fsid == homeinfo.f_fsid)
        {
            home = false;
        }

    float totalbytes = info.f_bsize * info.f_blocks,
          availablebytes = (info.f_bsize * info.f_bavail), usedbytes = totalbytes - availablebytes;
    signed int usageprecentage = roundf (
        100
        * (((float)totalbytes - availablebytes) / (((float)totalbytes + availablebytes) / 2.0)));
    float total, used;

    if (gigs)
        {
            total = roundf (totalbytes / BYTE_GIGABYTE_CONVERSION);
            used = (usedbytes / BYTE_GIGABYTE_CONVERSION);
        }
    else
        {
            total = roundf (totalbytes / BYTE_KILOBYTE_CONVERSION);
            used = (usedbytes / BYTE_KILOBYTE_CONVERSION);
            strcpy (unit, "kB");
        }

    sprintf (output[0], "%.2f/%.0f %s (%d%%)", used, total, unit, usageprecentage);

    if (!home)
        {
            strcpy (output[1], "");
            for (iter i = 0; i < 2; i++)
                {
                    dest[i] = output[i];
                }
            return 0;
        }

    totalbytes = homeinfo.f_bsize * homeinfo.f_blocks;
    availablebytes = (homeinfo.f_bsize * homeinfo.f_bavail),
    usedbytes = totalbytes - availablebytes;
    usageprecentage = round (
        100
        * (((float)totalbytes - availablebytes) / (((float)totalbytes + availablebytes) / 2.0)));

    if (gigs)
        {
            total = roundf (totalbytes / BYTE_GIGABYTE_CONVERSION);
            used = (usedbytes / BYTE_GIGABYTE_CONVERSION);
        }
    else
        {
            total = roundf (totalbytes / BYTE_KILOBYTE_CONVERSION);
            used = (usedbytes / BYTE_KILOBYTE_CONVERSION);
        }

    sprintf (output[1], "%.2f/%.0f %s (%d%%)", used, total, unit, usageprecentage);

    for (iter i = 0; i < 2; i++)
        {
            dest[i] = output[i];
        }
    return 1;
}