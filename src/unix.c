#include "unix.h"
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
unsigned int get_core_count()
{
  /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info.
   */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 0. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    return 0;
  }
  unsigned int core_count;
  while (!fscanf(cpu_info, "cpu cores\t: %u", &core_count))
    fscanf(cpu_info, "%*[^c]");
  fclose(cpu_info);

  return core_count;
}

/**
 * @brief Get the thread count
 *
 * @return unsigned int
 */
unsigned int get_thread_count()
{
  /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info.
   */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 0. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    return 0;
  }

  /* Reading the file until it finds the line that starts with "siblings:". */
  unsigned int thread_count;
  while (!fscanf(cpu_info, "siblings\t: %u", &thread_count))
    fscanf(cpu_info, "%*[^s]");
  fclose(cpu_info);

  return thread_count;
}

/**
 * @brief Get the total memory
 *
 * @return unsigned int
 */
int get_total_memory()
{
  /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
   */
  FILE *mem_info = fopen("/proc/meminfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 0. */
  if (mem_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/meminfo\n");
    return 0;
  }

  int total_memory;

  /* Reading the file until it finds the line that starts with "MemTotal:". */
  while (!fscanf(mem_info, "MemTotal:\t%u kB", &total_memory))
    fscanf(mem_info, "%*[^m]");
  fclose(mem_info);

  return total_memory;
}

/**
 * @brief Get the avalible memory
 *
 * @return int
 */
int get_avalible_memory()
{
  /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
   */
  FILE *mem_info = fopen("/proc/meminfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 0. */
  if (mem_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/meminfo\n");
    return 0;
  }

  int avalible_memory;
  while (!fscanf(mem_info, "MemAvailable:\t%u kB", &avalible_memory))
    fscanf(mem_info, "%*[^M]");
  fclose(mem_info);

  return avalible_memory;
}

long get_uptime()
{
  FILE *uptime_file = fopen("/proc/uptime", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 0. */
  if (uptime_file == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/uptime\n");
    return 0;
  }

  float uptime;
  while (!fscanf(uptime_file, "%f", &uptime))
    fscanf(uptime_file, "%*[^ ]");
  fclose(uptime_file);

  return (uptime);
}

/**
 * @brief Get the cpu model object
 *
 * @param storage_variable
 * @return int
 */
char *get_cpu_model()
{
  /* Opening the file /proc/meminfo and assigning the file pointer to mem_info.
   */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an
   * error message and returns 1. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    exit(1);
  }

  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  /* Reading the file until it finds the line that starts with "model name:". */
  while (!fscanf(cpu_info, "model name\t: %99[^\n]", buffer))
    fscanf(cpu_info, "%*[^m]");
  fclose(cpu_info);

  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

/**
 * @brief Get the operating system name
 *
 * @return char*
 */
char *get_operating_system_name()
{
  FILE *os_info = fopen("/etc/os-release", "r");

  if (os_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /etc/os-release\n");
    return NULL;
  }

  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  while (!fscanf(os_info, "PRETTY_NAME=\"%[^\"]\"", buffer))
    fscanf(os_info, "%*[^P]");
  fclose(os_info);

  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

char *get_operating_system_name_bedrock()
{
  FILE *os_info = fopen("/bedrock/etc/os-release", "r");

  if (os_info == NULL)
  {
    return NULL;
  }

  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  while (!fscanf(os_info, "NAME=\"%[^\"]\"", buffer))
    fscanf(os_info, "%*[^P]");
  fclose(os_info);

  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

/**
 * @brief Get the system hostname
 *
 * @param storage_variable
 * @return int
 */
char *get_hostname()
{
  FILE *hostname_file = fopen("/proc/sys/kernel/hostname", "r");

  if (hostname_file == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/sys/kernel/hostname\n");
    exit(1);
  }

  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  while (!fscanf(hostname_file, "%99[^\n]", buffer))
    fscanf(hostname_file, "%*[^\n]");
  fclose(hostname_file);

  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

/**
 * @brief return the output of the uname --kernel-name --kernel-release command
 *
 * @param storage_variable
 * @return int
 */
char *kuname()
{
  struct utsname unameData;

  if (uname(&unameData) != 0)
  {
    perror("Uname");
    return NULL;
  }
  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  sprintf(buffer, "%s %s",unameData.sysname, unameData.release);

  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

/**
 * It reads the contents of the file `/sys/devices/virtual/dmi/id/board_name`
 * and returns the contents as a string
 *
 * @return The board name of the system.
 */
static char *get_board_name()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("/sys/devices/virtual/dmi/id/board_name", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Failed to get '/sys/devices/virtual/dmi/id/board_name'\n");
    exit(1);
  }

  if ((read = getline(&line, &len, fp)) != -1)
  {
    fclose(fp);
    for (register iterator i = 0; i < len; i++)
    {
      if (line[i] == '\n')
      {
        line[i] = '\0';
        break;
      }
    }
    return line;
  }

  fclose(fp);
  return NULL;
}

/**
 * It opens a file, reads a line, and returns the line
 *
 * @return The board vendor name.
 */
static char *get_board_vendor()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("/sys/devices/virtual/dmi/id/board_vendor", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Failed to get '/sys/devices/virtual/dmi/id/board_name'\n");
    exit(1);
  }

  if ((read = getline(&line, &len, fp)) != -1)
  {
    fclose(fp);
    for (register iterator i = 0; i < len; i++)
    {
      if (line[i] == '\n')
      {
        line[i] = '\0';
        break;
      }
    }
    return line;
  }

  fclose(fp);
  return NULL;
}

/**
 * It takes a string, and copies the board name and vendor into it
 *
 * @param storage_variable The variable to store the board model in.
 */
char *get_board_model()
{
  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  sprintf(buffer, "%s (%s)", get_board_name(), get_board_vendor());
  buffer = (char *)realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
  return buffer;
}

/**
 * It gets the creation date of the file system and stores it in a struct date
 *
 * @param storage_variable A pointer to a struct date variable that will be used
 * to
 *
 * @return The date of the file system's creation.
 */
struct date get_creation_date()
{

  struct statx stx;
  mstatx(AT_FDCWD, "/", AT_STATX_SYNC_AS_STAT, STATX_BTIME, &stx);
  time_t epochtime = stx.stx_btime.tv_sec;
  struct tm t;
  char buf[11];
  struct date fs_birthdate;

  t = *localtime(&epochtime);
  strftime(buf, sizeof(buf), "%Y %m %d", &t);

  sscanf(buf, "%u %u %u", &fs_birthdate.year, &fs_birthdate.month,
         &fs_birthdate.day);
  return fs_birthdate;
}

char *get_username()
{
  char *buf = getenv("USER");
  if (buf == NULL)
  {
    register uid_t uid = getuid();
    register struct passwd *pw = getpwuid(uid);
    if (pw)
    {
      return pw->pw_name;
    }
  }
  return buf;
}

static packagecount get_num_packages_dpkg()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned long num_packages = 0;
  fp = popen("apt list --installed 2>/dev/null", "r");
  if (fp == NULL)
  {
    return 0;
  }
  while ((read = getline(&line, &len, fp)) != -1)
  {
    num_packages++;
  }
  pclose(fp);
  if (num_packages > 0)
  {
    return num_packages - 1;
  }
  return num_packages;
}

static packagecount get_num_packages_apk()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned long num_packages = 0;
  fp = popen("apk info 2> /dev/null", "r");
  if (fp == NULL)
  {
    return (0);
  }
  while ((read = getline(&line, &len, fp)) != -1)
  {
    num_packages++;
  }
  pclose(fp);
  if (line)
  {
    free(line);
  }
  return num_packages;
}

static packagecount get_num_packages_pacman()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned long num_packages = 0;
  fp = popen("pacman -Q 2> /dev/null", "r");
  if (fp == NULL)
  {
    return (0);
  }
  while ((read = getline(&line, &len, fp)) != -1)
  {
    num_packages++;
  }
  pclose(fp);
  if (line)
  {
    free(line);
  }
  return num_packages;
}

static packagecount get_num_packages_flatpak()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned long num_packages = 0;
  fp = popen("flatpak list 2> /dev/null", "r");
  if (fp == NULL)
  {
    return (0);
  }
  while ((read = getline(&line, &len, fp)) != -1)
  {
    num_packages++;
  }
  pclose(fp);
  if (line)
  {
    free(line);
  }
  return num_packages;
}

static packagecount get_num_packages_snap()
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  packagecount num_packages = 0;
  fp = popen("snap list 2> /dev/null", "r");
  if (fp == NULL)
  {
    return (0);
  }
  while ((read = getline(&line, &len, fp)) != -1)
  {
    num_packages++;
  }
  pclose(fp);
  if (line)
  {
    free(line);
  }
  if (num_packages > 0)
  {
    return num_packages - 1;
  }
  return num_packages;
}

static void return_base(char *chararr, char *storage_variable)
{
  char *token;
  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  char *rest = chararr;
  while ((token = strtok_r(rest, "/", &rest)))
  {
    strcpy(buffer, token);
  }
  strcpy(storage_variable, buffer);
  free(buffer);
  return;
}

char *get_shell_name()
{
  char *shell = getenv("0");
  if (shell != NULL)
  {
    if (strstr(shell, "/"))
    {
      return_base(shell, shell);
    }
    char *shellname = (char *)calloc((strlen(shell) + 1), sizeof(char));
    strcpy(shellname, shell);
    return shellname;
  }

  int ppid = getppid();
  char *token;
  char *process = (char *)calloc(BUFFERSIZE, sizeof(char));
  char *buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  if (!buffer)
  {
    perror("calloc");
    exit(EXIT_FAILURE);
  }
  sprintf(buffer, "/proc/%d/exe", ppid);
  while (strcmp(process, "") == 0)
    if (readlink(buffer, process, BUFFERSIZE - 1) < 0)
    {
      perror("readlink");
      exit(1);
    }
  free(buffer);

  char *tokbuffer = (char *)calloc(BUFFERSIZE, sizeof(char));
  char *rest = process;
  while ((token = strtok_r(rest, "/", &rest)))
  {
    strcpy(tokbuffer, token);
  }

  tokbuffer = (char *)realloc(tokbuffer, (strlen(tokbuffer) + 1) * sizeof(char));
  return tokbuffer;
}

packagecount get_num_packages(unsigned short package_manager_id)
{
  switch (package_manager_id)
  {
  case PACMAN_PACKAGE_MANAGER:
    return get_num_packages_pacman();
    break;
  case APT_PACKAGE_MANAGER:
    return get_num_packages_dpkg();
    break;
  case APK_PACKAGE_MANAGER:
    return get_num_packages_apk();
    break;
  case FLATPAK_PACKAGE_MANAGER:
    return get_num_packages_flatpak();
    break;
  case SNAP_PACKAGE_MANAGER:
    return get_num_packages_snap();
    break;
  }
  return 0;
}
