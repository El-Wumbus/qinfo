#include <stdio.h>
#include "config.h"

int main()
{
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");
  if (cpu_info == NULL) {
    fprintf(stderr,"Error: Could not open /proc/cpuinfo\n");
    return 1;
  }

  unsigned int thread_count, core_count;
  while (!fscanf(cpu_info, "siblings\t: %u", &thread_count))
    fscanf(cpu_info, "%*[^s]");
  while (!fscanf(cpu_info, "cpu cores\t: %u", &core_count))
    fscanf(cpu_info, "%*[^c]");
  fclose(cpu_info);

  fprintf(stdout, "CPU: %u cores, %u threads\n", core_count, thread_count);
  return 0;
}