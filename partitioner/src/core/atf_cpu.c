#include <atf_cpu.h>

extern unsigned int plat_is_my_cpu_primary(void);

bool cpu_is_primary(void)
{
    return plat_is_my_cpu_primary();
}

void cpu_idle(void) { }

void cpu_init(unsigned int cpuid, unsigned int entrypoint)
{
    /* Call PSCI to wake-up the partition master CPU */
    psci_cpu_on(cpuid, entrypoint, 0x0);
}