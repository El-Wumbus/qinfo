#include <stdio.h>
#include "config.h"
#include "system.h"
#include "color.h"

int main()
{
  unsigned int core_count;
  unsigned int thread_count;
  float available_memory;
  float used_memory;
  float total_memory;
  char hostname[256];
  char cpu_model[100];
  char os_name[256];
  char kernel_version[256];
  char unit[3];

  if (OPERATING_SYSTEM == "Linux")
  {
    core_count = get_core_count();
    thread_count = get_thread_count();
    available_memory = get_avalible_memory();
    total_memory = get_total_memory();
    used_memory = total_memory - available_memory;

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

    get_hostname(hostname);
    get_cpu_model(cpu_model);
    get_operating_system_name(os_name);
    uname(kernel_version);
  }

  if (DISPLAY_CPU_INFO)
  {
    fprintf(stdout, "%sCPU:%s %s (%u cores, %u threads)\n", BWHT, COLOR_END, cpu_model, core_count, thread_count);
  }

  if (DISPLAY_MEMORY_INFO)
  {
    fprintf(stdout, "%sMemory:%s %.2f/%.2f %s \n", BWHT, COLOR_END, used_memory, total_memory, unit);
  }

  if (DISPLAY_HOSTNAME)
  {
    fprintf(stdout, "%sHostname:%s %s\n", BWHT, COLOR_END, hostname);
  }

  if (DISPLAY_OPERATING_SYSTEM)
  {
    fprintf(stdout, "%sOperating System:%s %s (%s)\n", BWHT, COLOR_END, os_name, OPERATING_SYSTEM);
  }

  if (OPERATING_SYSTEM == "Linux" && DISPLAY_KERNEL_VERSION)
  {
    fprintf(stdout, "%sKernel:%s %s", BWHT, COLOR_END, kernel_version);
  }

  return 0;
}