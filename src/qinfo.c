
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

char *formatted_uptime(long uptime) {
  /* Calculating the number of days, hours, minutes and seconds. */
  unsigned int days = (unsigned int)uptime / SECOND_DAY_CONVERSION;
  unsigned int hours = (unsigned int)uptime / SECOND_HOUR_CONVERSION % HOUR_DAY_CONVERSION;
  unsigned int minutes = (unsigned int)uptime / SECOND_MINUTE_CONVERSION % MINUTE_HOUR_CONVERSION;
  unsigned int seconds = (unsigned int)uptime % SECOND_MINUTE_CONVERSION;
  /* Allocating memory for the string. */
  char *string = malloc(sizeof(char) * 100);
  /* Checking if the memory was allocated successfully. If it was not, it prints
    an error message and returns NULL. */
  if (string == NULL) {
    fprintf(stderr, "Error: Could not allocate memory for the string\n");
    return NULL;
  }
  /* Copying the string into the allocated memory. */
  sprintf(string, "%u days, %u hours, %u minutes, %u seconds", days, hours,
          minutes, seconds);
  return string;
}

int main() {
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
  if (USE_GIGABYTES) {
    used_memory = ((total_memory - available_memory) / (float)KILOBYTE_GIGABYTE_CONVERSION);
    total_memory = get_total_memory() / (float)KILOBYTE_GIGABYTE_CONVERSION;
    strcpy(unit, "GB");
  } else {
    strcpy(unit, "kB");
  }


  /* Checking if the user wants to display the CPU information. If they do, it
  will print the CPU information. */
  if (DISPLAY_CPU_INFO) {
    printf("%sCPU:%s\t\t%s (%u cores, %u threads)\n", BWHT, COLOR_END, cpu_model,
           core_count, thread_count);
  }

  /* Checking if the user wants to display the memory information. If they do,
  it will print the memory information. */
  if (DISPLAY_MEMORY_INFO) {
    printf("%sRAM:%s\t\t%.2f/%.2f %s \n", BWHT, COLOR_END, used_memory,
           total_memory, unit);
  }

  /* Checking if the user wants to display the operating system information. If
  they do, it will print the operating system information. */
  if (DISPLAY_OPERATING_SYSTEM) {
    printf("%sOS:%s\t\t%s (%s)\n", BWHT, COLOR_END, os_name, OPERATING_SYSTEM);
  }

  /* Checking if the user wants to display the hostname. If they do, it will
   * print the hostname. */
  if (DISPLAY_HOSTNAME) {
    printf("%sHostname:%s\t%s\n", BWHT, COLOR_END, hostname);
  }

  /* This is checking if the user wants to display the uptime. If they do, it
   * will print the uptime. */
  if (DISPLAY_UPTIME) {
    printf("%sUptime:%s\t\t%s\n", BWHT, COLOR_END, formatted_uptime(uptime));
  }

  /* This is checking if the operating system is Linux and if the user wants to
  display the kernel version. If both of these are true, it will print the
  kernel version. */
  if (strcmp(OPERATING_SYSTEM, "Linux") && DISPLAY_KERNEL_VERSION) {
    printf("%sKernel:%s\t\t%s", BWHT, COLOR_END, kernel_version);
  }

  return 0;
}