
/* qinfo -- Query (Quick) info fetches system info and displays it.
  Copyright (C) 2020 Aidan Neal
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "config.h"
#include "system.h"
#include "color.h"

int main()
{
  unsigned int core_count;
  unsigned int thread_count;
  float uptime, uptime_old;
  float available_memory;
  float used_memory;
  float total_memory;
  char hostname[256];
  char cpu_model[100];
  char os_name[256];
  char kernel_version[256];
  char unit[3];
  char uptime_identifier[10];

  /* This is checking if the operating system is Linux. If it is, it will get the core count, thread
  count, available memory, total memory, used memory, hostname, CPU model, operating system name,
  and kernel version. It will also check if the user wants to display the memory in gigabytes or
  kilobytes. */
  if (OPERATING_SYSTEM == "Linux")
  {
    core_count = get_core_count();
    thread_count = get_thread_count();
    available_memory = get_avalible_memory();
    total_memory = get_total_memory();
    uptime = get_uptime();

    used_memory = total_memory - available_memory;
    get_hostname(hostname);
    get_cpu_model(cpu_model);
    get_operating_system_name(os_name);
    uname(kernel_version);

    /* Checking to display the memory in gigabytes or kilobytes. */
    if (USE_GIGABYTES)
    {
      used_memory = ((total_memory - available_memory) / (float)1048576);
      total_memory = get_total_memory() / (float)1048576;
      strcpy(unit, "GB");
    }
    else
    {
      strcpy(unit, "kB");
    }
  }

  strcpy(uptime_identifier, "seconds");
  /* This is checking if the uptime is greater than 59 seconds. If it is, it will change the
  uptime identifier to minutes and divide the uptime by 60. */
  if (uptime > 59)
  {
    strcpy(uptime_identifier, "minute(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)60);
  }
  /* This is checking if the uptime is greater than 59 minutes. If it is, it will change the
  uptime identifier to hours and divide the uptime by 60. */
  if (uptime > 59)
  {
    strcpy(uptime_identifier, "hour(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)60);
  }
  /* Checking if the uptime is greater than 24 hours. If it is, it will change the uptime identifier to
  days and divide the uptime by 24. */
  if (uptime > 24)
  {
    strcpy(uptime_identifier, "day(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)24);
  }
  /* This is checking if the uptime is greater than 7 days. If it is, it will change the uptime
  identifier to weeks and divide the uptime by 7. */
  if (uptime > 7)
  {
    strcpy(uptime_identifier, "week(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)7);
  }
  /* This is checking if the uptime is greater than 4 weeks. If it is, it will change the uptime
  identifier to months and divide the uptime by 4. */
  if (uptime > 4)
  {
    strcpy(uptime_identifier, "months(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)4);
  }
  /* This is checking if the uptime is greater than 12 months. If it is, it will change the uptime
  identifier to years and divide the uptime by 12. */
  if (uptime > 12)
  {
    strcpy(uptime_identifier, "years(s)");
    uptime_old = uptime;
    uptime = (uptime_old / (float)12);
  }

  /* Checking if the user wants to display the CPU information. If they do, it will print the CPU
  information. */
  if (DISPLAY_CPU_INFO)
  {
    printf("%sCPU:%s %39s (%u cores, %u threads)\n", BWHT, COLOR_END, cpu_model, core_count, thread_count);
  }

  /* Checking if the user wants to display the memory information. If they do, it will print the memory
  information. */
  if (DISPLAY_MEMORY_INFO)
  {
    printf("%sRAM:%s %10.2f/%.2f %s \n", BWHT, COLOR_END, used_memory, total_memory, unit);
  }

  /* Checking if the user wants to display the operating system information. If they do, it will print
  the operating system information. */
  if (DISPLAY_OPERATING_SYSTEM)
  {
    printf("%sOS:%s %16s (%s)\n", BWHT, COLOR_END, os_name, OPERATING_SYSTEM);
  }

  /* Checking if the user wants to display the hostname. If they do, it will print the hostname. */
  if (DISPLAY_HOSTNAME)
  {
    printf("%sHostname:%s %s\n", BWHT, COLOR_END, hostname);
  }

  /* This is checking if the user wants to display the uptime. If they do, it will print the uptime. */
  if (DISPLAY_UPTIME)
  {
    printf("%sUptime:%s   %.2f %s\n", BWHT, COLOR_END, uptime, uptime_identifier);
  }

  /* This is checking if the operating system is Linux and if the user wants to display the kernel
  version. If both of these are true, it will print the kernel version. */
  if (OPERATING_SYSTEM == "Linux" && DISPLAY_KERNEL_VERSION)
  {
    printf("%sKernel:%s   %s", BWHT, COLOR_END, kernel_version);
  }

  return 0;
}