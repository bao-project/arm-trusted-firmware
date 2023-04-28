#ifndef ATF_CPU_H
#define ATF_CPU_H

#ifndef __ASSEMBLER__

#include <atf_stubs.h>

/* CPU-related stubs declaration */
bool cpu_is_primary(void);
void cpu_idle(void);
void cpu_init(unsigned int cpuid, unsigned int entrypoint);

#endif /* __ASSEMBLER__ */

#endif /* ATF_CPU_H */
