
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

struct uptime formatted_uptime(long uptime) {
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

struct packages formatted_packages(unsigned long pacman_packages,
                                   unsigned long apt_packages,
                                   unsigned long apk_packages) {
  struct packages pkgs;
  if (pacman_packages > 0) {
    pkgs.pacman_packages = pacman_packages;
  } else {
    pkgs.pacman_packages = 0;
  }
  if (apt_packages > 0) {
    pkgs.apt_packages = apt_packages;
  } else {
    pkgs.apt_packages = 0;
  }
  if (apk_packages > 0) {
    pkgs.apk_packages = apk_packages;
  } else {
    pkgs.apk_packages = 0;
  }
  return pkgs;
}

int main() {
  configuration config;
  struct color col;
  struct packages pkgs;
  parse_config(&config);
  col.ansi_id_color = config.IDCOLOR;
  col.ansi_text_color = config.TXTCOLOR;
  col.logo_color = config.LOGOCOLOR;

  unsigned int core_count = 0;
  unsigned int thread_count = 0;
  long uptime = 0;
  float available_memory;
  float used_memory = 0;
  float total_memory = 0;
  char hostname[256];
  char cpu_model[100];
  char os_name[256];
  char kernel_version[256];
  char unit[3];
  char motherboard_info[256];
  struct date rootfsage;
  unsigned long pacman_packages = 0;
  unsigned long apt_packages = 0;
  unsigned long apk_packages = 0;

  char *username = get_username();
  core_count = get_core_count();
  thread_count = get_thread_count();
  available_memory = get_avalible_memory();
  total_memory = get_total_memory();
  uptime = get_uptime();
  get_board_model(&motherboard_info);

  used_memory = total_memory - available_memory;
  get_hostname(hostname);
  get_cpu_model(cpu_model);
  if (get_operating_system_name_bedrock(os_name) == 1) {
    get_operating_system_name(os_name);
  }
  if (strcmp(os_name, "Arch Linux") == 0) {
    pacman_packages = get_num_packages(PACMAN_PACKAGE_MANAGER);
  } else if (strcmp(os_name, "Debian") == 0) {
    apt_packages = get_num_packages(APT_PACKAGE_MANAGER);
  } else if (strstr(os_name, "Ubuntu") != NULL) {
    apk_packages = get_num_packages(APT_PACKAGE_MANAGER);
  } else if (strcmp(os_name, "Bedrock Linux")) {
    apk_packages = get_num_packages(APK_PACKAGE_MANAGER);
    pacman_packages = get_num_packages(PACMAN_PACKAGE_MANAGER);
    apt_packages = get_num_packages(APT_PACKAGE_MANAGER);
  } else if (strstr(os_name, "Alpine Linux" )) {
    apk_packages = get_num_packages(APK_PACKAGE_MANAGER);
  }

  if (uname(kernel_version)) {
    strcpy(kernel_version, "Unknown");
  }

  if (get_creation_date(&rootfsage)) {
    fprintf(stderr, "Error getting rootfs age\n");
    return 1;
  }

  struct uptime upt = formatted_uptime(uptime);
  if (config.DISPLAY_LOGO) {
    if (strcmp(os_name, "Arch Linux") == 0) {
      printf("%s%s%s\n", col.logo_color, logo_arch, COLOR_END);
    } else if (strstr(os_name, "Alpine Linux") != NULL) {
      printf("%s%s%s\n", col.logo_color, alpine_logo, COLOR_END);
    } else if (strstr(os_name, "Arco Linux") != NULL) {
      printf("%s%s%s\n", col.logo_color, arcolinux_logo, COLOR_END);
    } else if (strstr(os_name, "Aritx Linux") != NULL) {
      printf("%s%s%s\n", col.logo_color, artix_logo, COLOR_END);
    } else if (strstr(os_name, "Bedrock Linux") != NULL) {
      printf("%s%s%s\n", col.logo_color, bedrock_logo, COLOR_END);
    } else if (strstr(os_name, "Gentoo") != NULL) {
      printf("%s%s%s\n", col.logo_color, gentoo_logo, COLOR_END);
    } else if (strstr(os_name, "Ubuntu") != NULL) {
      printf("%s%s%s\n", col.logo_color, ubuntu_logo, COLOR_END);
    } else {
      printf("%s%s%s\n", col.logo_color, generic_logo, COLOR_END);
    }
  }

  /* Checking to display the memory in gigabytes or kilobytes. */

  if (config.USE_GIGABYTES) {
    used_memory = ((total_memory - available_memory) /
                   (float)KILOBYTE_GIGABYTE_CONVERSION);
    total_memory = get_total_memory() / (float)KILOBYTE_GIGABYTE_CONVERSION;
    strcpy(unit, "GB");
  } else {
    strcpy(unit, "kB");
  }

  /* Checking if the user wants to display the CPU information. If they do, it
  will print the CPU information. */
  if (config.DISPLAY_CPU_INFO) {
    printf("%sCPU:%s\t\t%s%s (%u cores, %u threads)%s\n", col.ansi_id_color,
           COLOR_END, col.ansi_text_color, cpu_model, core_count, thread_count,
           COLOR_END);
  }

  if (config.DISPLAY_ETC_CPU_INFO) {
    printf("%sEXTRA CPU INFO:%s%s Model number 0x%X, Family Value: 0x%X%s\n",
           col.ansi_id_color, COLOR_END, col.ansi_text_color,
           cpu_get_modelnum(), cpu_get_family_value(), COLOR_END);
  }

  /* Checking if the user wants to display the memory information. If they do,
  it will print the memory information. */
  if (config.DISPLAY_MEMORY_INFO) {
    printf("%sRAM:%s\t\t%s%.2f/%.2f %s%s\n", col.ansi_id_color, COLOR_END,
           col.ansi_text_color, used_memory, total_memory, unit, COLOR_END);
  }

  /* Checking if the user wants to display the operating system information. If
  they do, it will print the operating system information. */
  if (config.DISPLAY_OPERATING_SYSTEM) {
    printf("%sOS:%s\t\t%s%s (%s)%s\n", col.ansi_id_color, COLOR_END,
           col.ansi_text_color, os_name, OPERATING_SYSTEM, COLOR_END);
  }

  if (config.DISPLAY_PACKAGES) {

    pkgs = formatted_packages(pacman_packages, apt_packages, apk_packages);
    printf("%sPackages:%s\t%s", col.ansi_id_color, COLOR_END,
           col.ansi_text_color);
    if (pkgs.pacman_packages > 0) {
      printf("%lu (Pacman) ", pkgs.pacman_packages);
    }
    if (pkgs.apt_packages > 0) {
      printf("%lu (Apt) ", pkgs.apt_packages);
    }
    if (pkgs.apk_packages > 0) {
      printf("%lu (Apk)", pkgs.apk_packages);
    }
    printf("%s\n", COLOR_END);
  }
  if (config.DISPLAY_USERNAME) {
    printf("%sUser:%s%s\t\t%s%s\n", col.ansi_id_color, COLOR_END,
           col.ansi_text_color, username, COLOR_END);
  }

  /* Checking if the user wants to display the hostname. If they do, it will
   * print the hostname. */
  if (config.DISPLAY_HOSTNAME) {
    printf("%sHostname:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END,
           col.ansi_text_color, hostname, COLOR_END);
  }

  if (config.DISPLAY_MOTHERBOARD_INFO) {
    printf("%sMotherboard:%s%s\t%s%s\n", col.ansi_id_color, COLOR_END,
           col.ansi_text_color, motherboard_info, COLOR_END);
  }

  /* Parsing the rootfsage string and printing the first 3 words. */
  if (config.DISPLAY_ROOTFS_BIRTHDAY) {
    printf("%sROOTFS BIRTH:%s%s\t", col.ansi_id_color, COLOR_END,
           col.ansi_text_color);
    if (config.DISPLAY_DATES_YYYY_MM_DD) {
      printf("%d/%d/%d%s\n", rootfsage.year, rootfsage.month, rootfsage.day,
             COLOR_END);
    } else {
      printf("%d/%d/%d%s\n", rootfsage.month, rootfsage.day, rootfsage.year,
             COLOR_END);
    }

    /* This is checking if the user wants to display the uptime. If they do, it
     * will print the uptime. */
    if (config.DISPLAY_UPTIME) {
      printf("%sUptime:%s%s\t\t", col.ansi_id_color, COLOR_END,
             col.ansi_text_color);
      if (upt.days > 0) {
        printf("%u days ", upt.days);
      }
      if (upt.hours > 0) {
        printf("%u hours ", upt.hours);
      }
      if (upt.minutes > 0) {
        printf("%u minutes ", upt.minutes);
      }
      if (upt.seconds > 0) {
        printf("%u seconds", upt.seconds);
      }
      printf("%s\n", COLOR_END);
    }

    /* This is checking if the operating system is Linux and if the user wants
    to display the kernel version. If both of these are true, it will print the
    kernel version. */
    if (strcmp(OPERATING_SYSTEM, "Linux") && config.DISPLAY_KERNEL_VERSION) {
      printf("%sKernel:%s\t\t%s", col.ansi_id_color, COLOR_END, kernel_version);
    }

    return 0;
  }
}