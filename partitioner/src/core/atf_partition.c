#include <atf_partition.h>
#include <partition.h>
#include <atf_cpu.h>

static spinlock_t console_lock;

void partition_prepare_atfctx(uint32_t cpuid)
{
    cpu_context_t* ctx = NULL;
    el3_state_t* state = NULL;
    partition_cfg_t* prttn = NULL;

    /* Get partition struct corresponding to the running CPU */
    prttn = partition_get_prttn_by_coreid(cpuid);

    if (prttn != NULL) {
        /* Get ATF context to be modified before jumping to EL2-NS */
        ctx = cm_get_context(NON_SECURE);
        state = get_el3state_ctx(ctx);

        /* Modify ATF context before jumping to EL2-NS */
        write_ctx_reg(state, CTX_SCR_EL3,
            prttn->prttn_cfg_header.prttn_arch.scr_el3);
        write_ctx_reg(state, CTX_SPSR_EL3,
            prttn->prttn_cfg_header.prttn_arch.spsr_el3);
        write_ctx_reg(state, CTX_ELR_EL3, prttn->prttn_cfg_header.entrypoint);

        spin_lock(&console_lock);
        console_printf("BAO_PARTITIONER: Jump to partition %d entrypoint \n",
            prttn->prttn_id);
        spin_unlock(&console_lock);
    } else {
        ERROR("BAO_PARTITIONER: No partition defined for cpuid %d", cpuid);
        while (1) { };
    }
}

void partitions_init(void)
{
    unsigned int prttn_index = 0;

    for (; prttn_index < partitions.partitions_size; prttn_index++) {
        partition_cfg_t* partition = &partitions.partitions_list[prttn_index];
        uint32_t cpuid = partition->prttn_cfg_header.cpuids[0];
        uint64_t entrypoint = partition->prttn_cfg_header.entrypoint;

        spin_lock(&console_lock);
        console_printf("BAO_PARTITIONER: Initializing partition %d\n",
            prttn_index);
        spin_unlock(&console_lock);

        /* Awake master CPU from current iterated partition, except if it
        the primary CPU that is already running*/
        if (cpuid != plat_my_core_pos()) {
            spin_lock(&console_lock);
            console_printf("BAO_PARTITIONER: Wake-up partition %d master "
                           "CPU-%d\n",
                prttn_index, cpuid);
            spin_unlock(&console_lock);
            /* Wake-up the partition master CPU */
            cpu_init(cpuid, entrypoint);
        }
    }
}

void partitioner_init(void)
{
    console_printf("BAO_PARTITIONER: Initializing partitioner\n");

    /* Init each partition */
    partitions_init();
}
