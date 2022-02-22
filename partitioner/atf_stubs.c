#include <atf_stubs.h>

extern unsigned plat_is_my_cpu_primary(void);

bool cpu_is_primary()
{
    return plat_is_my_cpu_primary();
}

void cpu_idle() {}
void cpu_init(unsigned cpuid) {}