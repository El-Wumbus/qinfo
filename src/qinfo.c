#include <stdio.h>
#include "config.h"
#include "qinfo.h"
#include "system.h"
#include "color.h"

int main()
{
  unsigned int core_count;
  unsigned int thread_count;
  unsigned int total_memory;
  char hostname[256];
  char cpu_model[100];
  char os_name[256];
  
  if (OPERATING_SYSTEM == "Linux")
  {
    core_count = get_core_count();
    thread_count = get_thread_count();
    total_memory = get_total_memory();
    get_hostname(hostname);
    get_cpu_model(cpu_model);
    get_operating_system_name(os_name);
  }

  fprintf(stdout, "%sHostname:%s %s\n",BWHT,COLOR_END, hostname);
  fprintf(stdout, "%sCPU:%s %s (%u cores, %u threads)\n",BWHT,COLOR_END, cpu_model, core_count, thread_count);
  fprintf(stdout, "%sMemory:%s reset %u kB \n",BWHT,COLOR_END, total_memory);
  fprintf(stdout, "%sOperating System:%s %s (%s)\n",BWHT,COLOR_END, OPERATING_SYSTEM, os_name);
  return 0;
}