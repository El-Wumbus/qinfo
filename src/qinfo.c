
/* qinfo -- Query (Quick) info fetches system info and displays it.
Author: Aidan Neal <decator.c@proton.me>
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

#include "qinfo.h"
#include "cpu.h"
#include "logo.h"

static char os_name[256];
static struct color col;
static configuration config;

static void initconfig()
{
  parse_config(&config);
  col.ansi_id_color = config.IDCOLOR;
  col.ansi_text_color = config.TXTCOLOR;
  col.logo_color = config.LOGOCOLOR;
}

struct uptime formatted_uptime(long uptime)
{
  struct uptime upt;
  /* Calculating the number of days, hours, minutes and seconds. */
  upt.days = (unsigned int)uptime / SECOND_DAY_CONVERSION;
  upt.hours =
      (unsigned int)uptime / SECOND_HOUR_CONVERSION % HOUR_DAY_CONVERSION;
  upt.minutes =
      (unsigned int)uptime / SECOND_MINUTE_CONVERSION % MINUTE_HOUR_CONVERSION;
  upt.seconds = (unsigned int)uptime % SECOND_MINUTE_CONVERSION;
  return upt;
}

struct packages formatted_packages(packagecount pacman_packages,
                                   packagecount apt_packages,
                                   packagecount apk_packages,
                                   packagecount flatpak_packages,
                                   packagecount snap_packages)
{
  struct packages pkgs;
  if (pacman_packages > 0)
  {
    pkgs.pacman_packages = pacman_packages;
  }
  else
  {
    pkgs.pacman_packages = 0;
  }
  if (apt_packages > 0)
  {
    pkgs.apt_packages = apt_packages;
  }
  else
  {
    pkgs.apt_packages = 0;
  }
  if (apk_packages > 0)
  {
    pkgs.apk_packages = apk_packages;
  }
  else
  {
    pkgs.apk_packages = 0;
  }
  if (flatpak_packages > 0)
  {
    pkgs.flatpak_packages = flatpak_packages;
  }
  else
  {
    pkgs.flatpak_packages = 0;
  }
  if (snap_packages > 0)
  {
    pkgs.snap_packages = snap_packages;
  }
  else
  {
    pkgs.snap_packages = 0;
  }
  return pkgs;
}

static void printos()
{
  if (get_operating_system_name_bedrock(os_name) == 1)
  {
    get_operating_system_name(os_name);
  }

  printf("%sOS:%s\t\t%s%s (%s)%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, os_name, OPERATING_SYSTEM, COLOR_END);
}

static void printlogo()
{

  if (get_operating_system_name_bedrock(os_name) == 1)
  {
    get_operating_system_name(os_name);
  }
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
  else if (strstr(os_name, "Aritx Linux") != NULL)
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
  else
  {
    printf("%s%s%s\n", col.logo_color, generic_logo, COLOR_END);
  }
}

static void printcpuinfo(bool extra)
{
  if (extra)
  {
    printf("%sEXTRA CPU INFO:%s%s Model number 0x%X, Family Value: 0x%X%s\n",
           col.ansi_id_color, COLOR_END, col.ansi_text_color,
           cpu_get_modelnum(), cpu_get_family_value(), COLOR_END);
  }
  else
  {
    char cpu_model[100];
    unsigned int core_count = 0;
    unsigned int thread_count = 0;
    core_count = get_core_count();
    thread_count = get_thread_count();
    get_cpu_model(cpu_model);
    printf("%sCPU:%s\t\t%s%s (%u cores, %u threads)%s\n", col.ansi_id_color,
           COLOR_END, col.ansi_text_color, cpu_model, core_count, thread_count,
           COLOR_END);
  }
}

static void printmem(bool gigs)
{
  char unit[3];
  float available_memory,
      used_memory = 0,
      total_memory = 0;

  available_memory = get_avalible_memory();
  total_memory = get_total_memory();
  used_memory = total_memory - available_memory;

  if (gigs)
  {
    used_memory = ((total_memory - available_memory) /
                   (float)KILOBYTE_GIGABYTE_CONVERSION);
    total_memory = get_total_memory() / (float)KILOBYTE_GIGABYTE_CONVERSION;
    strcpy(unit, "GB");
  }
  else
  {
    strcpy(unit, "kB");
  }
  printf("%sRAM:%s\t\t%s%.2f/%.2f %s%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, used_memory, total_memory, unit, COLOR_END);
}

static void printuser()
{
  char *username = get_username();
  printf("%sUser:%s%s\t\t%s%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, username, COLOR_END);
}

static void printshell()
{
  char shell[MAXLINE];

  get_shell_name(shell);

  printf("%sShell:%s%s\t\t%s%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, shell, COLOR_END);
}

static void printhostname()
{
  char hostname[256];
  get_hostname(hostname);
  printf("%sHostname:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, hostname, COLOR_END);
}

static void printboard()
{
  char motherboard_info[256];
  get_board_model(&motherboard_info);
  printf("%sMotherboard:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END,
         col.ansi_text_color, motherboard_info, COLOR_END);
}

static void printrootfsbirth(bool format)
{
  struct date rootfsage;

  if (get_creation_date(&rootfsage))
  {
    fprintf(stderr, "Error getting rootfs age\n");
    exit(1);
  }
  printf("%sROOTFS BIRTH:%s%s\t", col.ansi_id_color, COLOR_END,
         col.ansi_text_color);
  if (format)
  {
    printf("%d/%d/%d%s\n", rootfsage.year, rootfsage.month, rootfsage.day,
           COLOR_END);
  }
  else
  {
    printf("%d/%d/%d%s\n", rootfsage.month, rootfsage.day, rootfsage.year,
           COLOR_END);
  }
}

static void printuptime()
{
  long uptime = get_uptime();
  struct uptime upt = formatted_uptime(uptime);

  printf("%sUptime:%s%s\t\t", col.ansi_id_color, COLOR_END,
         col.ansi_text_color);
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

static void printkernel()
{
  char kernel_version[256];

  if (uname(kernel_version))
  {
    strcpy(kernel_version, "Unknown");
  }
  printf("%sKernel:%s\t\t%s%s%s", col.ansi_id_color, COLOR_END, col.ansi_text_color, kernel_version, COLOR_END);
}

static void printpackages()
{
  struct packages pkgs;
  packagecount pacman_packages = 0;
  packagecount apt_packages = 0;
  packagecount apk_packages = 0;
  packagecount flatpak_packages = 0;
  packagecount snap_packages = 0;
  flatpak_packages = get_num_packages(FLATPAK_PACKAGE_MANAGER);
  snap_packages = get_num_packages(SNAP_PACKAGE_MANAGER);
  pacman_packages = get_num_packages(PACMAN_PACKAGE_MANAGER);
  apt_packages = get_num_packages(APT_PACKAGE_MANAGER);
  apk_packages = get_num_packages(APK_PACKAGE_MANAGER);
  pkgs = formatted_packages(pacman_packages, apt_packages, apk_packages,
                            flatpak_packages, snap_packages);
  printf("%sPackages:%s\t%s", col.ansi_id_color, COLOR_END,
         col.ansi_text_color);
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

int main()
{
  initconfig();

  if (config.DISPLAY_LOGO)
  {
    printlogo();
  }

  if (config.DISPLAY_CPU_INFO)
  {
    printcpuinfo(false);
  }

  if (config.DISPLAY_ETC_CPU_INFO)
  {
    printcpuinfo(true);
  }

  if (config.DISPLAY_MEMORY_INFO)
  {
    printmem(config.USE_GIGABYTES);
  }

  if (config.DISPLAY_OPERATING_SYSTEM)
  {
    printos();
  }

  if (config.DISPLAY_USERNAME)
  {
    printuser();
  }

  if (config.DISPLAY_SHELL)
  {
    printshell();
  }

  if (config.DISPLAY_HOSTNAME)
  {
    printhostname();
  }

  if (config.DISPLAY_MOTHERBOARD_INFO)
  {
    printboard();
  }

  if (config.DISPLAY_ROOTFS_BIRTHDAY)
  {
    printrootfsbirth(config.DISPLAY_DATES_YYYY_MM_DD);
  }

  if (config.DISPLAY_UPTIME)
  {
    printuptime();
  }

  if (config.DISPLAY_KERNEL_VERSION)
  {
    printkernel();
  }

  if (config.DISPLAY_PACKAGES)
  {
    printpackages();
  }
  
  return 0;
}
