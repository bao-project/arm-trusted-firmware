#ifndef ATF_STUBS_H
#define ATF_STUBS_H

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <common/debug.h>
#include <arch_helpers.h>
#include <plat/common/platform.h>
#include <lib/psci/psci.h>
#include <context.h>
#include <lib/el3_runtime/context_mgmt.h>
#include <lib/spinlock.h>

#define console_printf(...)            tf_log(LOG_MARKER_INFO __VA_ARGS__)

#define spinlock_lock(lock)            spin_lock((spinlock_t*)(lock))
#define spinlock_unlock(lock)          spin_unlock((spinlock_t*)(lock))

/* Partition cookie registers accessors */
#define sysreg_elr_el3_write(_value)   write_elr_el3(_value)
#define sysreg_sctlr_el2_write(_value) write_sctlr_el2(_value)
#define sysreg_mair_el2_write(_value)  write_mair_el2(_value)
#define sysreg_tcr_el2_write(_value)   write_tcr_el2(_value)
#define sysreg_ttbr0_el2_write(_value) write_ttbr0_el2(_value)
#define sysreg_hcr_el2_write(_value)   write_hcr_el2(_value)
#define sysreg_vtcr_el2_write(_value)  write_vtcr_el2(_value)
#define sysreg_vttbr_el2_write(_value) write_vttbr_el2(_value)
#define sysreg_scr_el3_write(_value)   write_scr_el3(_value)
#define sysreg_scr_el3_read()          read_scr_el3()

DEFINE_SYSREG_RW_FUNCS(hacr_el2)
#define sysreg_hacr_el2_write(_value) write_hacr_el2(_value)

#endif /* __ASSEMBLER__ */

#endif /* ATF_STUBS_H */
