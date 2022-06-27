#ifndef ATF_PARTITION_H
#define ATF_PARTITION_H

#ifndef __ASSEMBLER__

#include <atf_stubs.h>

void partition_prepare_atfctx(uint32_t cpuid);
void partitioner_init(void);

#endif /* __ASSEMBLER__ */

#endif /* ATF_PARTITION_H */
