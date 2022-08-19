#include "cpu.h"

// Register values for CPUID.

static uint32_t eax, ebx, ecx, edx;

static inline void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx,
                         uint32_t *ecx, uint32_t *edx) {
  __asm__ __volatile__("cpuid"
                       : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                       : "a"(leaf), "c"(0x0)
                       : "memory");
}

#define CPUID(leaf) cpuid(leaf, &eax, &ebx, &ecx, &edx);

int cpu_get_modelnum(void) {
  // System Info.
  CPUID(1);
  uint32_t extended_model = (eax >> 16) & 0x7FFFF;
  uint32_t m = (eax >> 4) & 0xF;
  return (extended_model << 4) + m;
}

int cpu_get_family_value(void) {
  CPUID(1);
  uint32_t extended_family = (eax >> 20) & 0xFF;
  uint32_t family_code = (eax >> 8) & 0x1F;
  return extended_family + family_code;
}
