/**
 * TODO: license
 */

/**
 * - Stream ids are 6-bit wide.
 * - The stream id 0 is reserved as an smmu bypassable id.
 * - When setting up the table for a given system configuration all of the bus 
 *  masters intended for the same translation context (e.g. virtual machine)
 *  should be configured with the same stream id as the number of stream match 
 *  registers in MMU-500 is limited.
 */

struct {
    sc_rsrc_t rsrc;
    sc_rm_sid_t sid;
} sid_rsrcs[] = {
    {SC_R_DMA_0_CH12, 0x1},
    {SC_R_DMA_0_CH13, 0x1},
    {SC_R_ENET_0, 0x2},
    {SC_R_SDHC_0, 0x3},
};