/*
 * Copyright 2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <common/tbbr/tbbr_img_def.h>
#include <lib/utils_def.h>
#include <lib/xlat_tables/xlat_tables_v2.h>

#define PLATFORM_LINKER_FORMAT		"elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH		aarch64

#define PLATFORM_STACK_SIZE		0xB00
#define CACHE_WRITEBACK_GRANULE		64

#define PLAT_PRIMARY_CPU		U(0x0)
#define PLATFORM_MAX_CPU_PER_CLUSTER	U(4)
#define PLATFORM_CLUSTER_COUNT		U(1)
#define PLATFORM_CLUSTER0_CORE_COUNT	U(4)
#define PLATFORM_CLUSTER1_CORE_COUNT	U(0)
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT)

#define IMX_PWR_LVL0			MPIDR_AFFLVL0
#define IMX_PWR_LVL1			MPIDR_AFFLVL1
#define IMX_PWR_LVL2			MPIDR_AFFLVL2

#define PWR_DOMAIN_AT_MAX_LVL		U(1)
#define PLAT_MAX_PWR_LVL		U(2)
#define PLAT_MAX_OFF_STATE		U(4)
#define PLAT_MAX_RET_STATE		U(2)

#define PLAT_WAIT_RET_STATE		U(1)
#define PLAT_STOP_OFF_STATE		U(3)

#if defined(NEED_BL2)
#define BL2_BASE			U(0x970000)
#define BL2_LIMIT			U(0x990000)
#define BL31_BASE			U(0x950000)
#define BL31_LIMIT			U(0x970000)
#define IMX_FIP_BASE			U(0x40310000)
#define IMX_FIP_SIZE			U(0x000300000)
#define IMX_FIP_LIMIT			U(FIP_BASE + FIP_SIZE)

/* Define FIP image location on eMMC */
#define IMX_FIP_MMC_BASE		U(0x100000)

#define PLAT_IMX8MP_BOOT_MMC_BASE	U(0x30B50000) /* SD */
#else
#define BL31_BASE			U(0x970000)
#define BL31_LIMIT			U(0x990000)
#endif

#define PLAT_PRI_BITS			U(3)
#define PLAT_SDEI_CRITICAL_PRI		0x10
#define PLAT_SDEI_NORMAL_PRI		0x20
#define PLAT_SDEI_SGI_PRIVATE		U(9)

/* non-secure uboot base */
#define PLAT_NS_IMAGE_OFFSET		U(0x40200000)
#define PLAT_NS_IMAGE_SIZE		U(0x00200000)

/* GICv3 base address */
#define PLAT_GICD_BASE			U(0x38800000)
#define PLAT_GICR_BASE			U(0x38880000)

#define PLAT_VIRT_ADDR_SPACE_SIZE	(ULL(1) << 32)
#define PLAT_PHY_ADDR_SPACE_SIZE	(ULL(1) << 32)

#define MAX_XLAT_TABLES			8
#define MAX_MMAP_REGIONS		16

#define HAB_RVT_BASE			U(0x00000900) /* HAB_RVT for i.MX8MM */

#define IMX_BOOT_UART_CLK_IN_HZ		24000000 /* Select 24MHz oscillator */
#define PLAT_CRASH_UART_BASE		IMX_BOOT_UART_BASE
#define PLAT_CRASH_UART_CLK_IN_HZ	24000000
#define IMX_CONSOLE_BAUDRATE		115200

#define IMX_AIPSTZ1			U(0x301f0000)
#define IMX_AIPSTZ2			U(0x305f0000)
#define IMX_AIPSTZ3			U(0x309f0000)
#define IMX_AIPSTZ4			U(0x32df0000)
#define IMX_AIPSTZ5			U(0x30df0000)

#define IMX_AIPS_BASE			U(0x30000000)
#define IMX_AIPS_SIZE			U(0x3000000)
#define IMX_GPV_BASE			U(0x32000000)
#define IMX_GPV_SIZE			U(0x800000)
#define IMX_AIPS1_BASE			U(0x30200000)
#define IMX_AIPS4_BASE			U(0x32c00000)
#define IMX_ANAMIX_BASE			U(0x30360000)
#define IMX_CCM_BASE			U(0x30380000)
#define IMX_SRC_BASE			U(0x30390000)
#define IMX_GPC_BASE			U(0x303a0000)
#define IMX_RDC_BASE			U(0x303d0000)
#define IMX_CSU_BASE			U(0x303e0000)
#define IMX_WDOG_BASE			U(0x30280000)
#define IMX_SNVS_BASE			U(0x30370000)
#define IMX_NOC_BASE			U(0x32700000)
#define IMX_NOC_SIZE			U(0x100000)
#define IMX_TZASC_BASE			U(0x32F80000)
#define IMX_IOMUX_GPR_BASE		U(0x30340000)
#define IMX_CAAM_BASE			U(0x30900000)
#define IMX_DDRC_BASE			U(0x3d400000)
#define IMX_DDRPHY_BASE			U(0x3c000000)
#define IMX_DDR_IPS_BASE		U(0x3d000000)
#define IMX_DDR_IPS_SIZE		U(0x1800000)
#define IMX_ROM_BASE			U(0x0)

#define IMX_GIC_BASE			PLAT_GICD_BASE
#define IMX_GIC_SIZE			U(0x200000)

#define IMX_HSIOMIX_CTL_BASE		U(0x32f10000)
#define IMX_HDMI_CTL_BASE		U(0x32fc0000)
#define RTX_RESET_CTL0			U(0x20)
#define RTX_CLK_CTL0			U(0x40)
#define RTX_CLK_CTL1			U(0x50)
#define TX_CONTROL0			U(0x200)
#define TX_CONTROL1			U(0x220)

#define IMX_MEDIAMIX_CTL_BASE		U(0x32ec0000)
#define RSTn_CSR			U(0x0)
#define CLK_EN_CSR			U(0x4)
#define RST_DIV				U(0x8)
#define LCDIF_ARCACHE_CTRL		U(0x4c)
#define ISI_CACHE_CTRL			U(0x50)

#define WDOG_WSR			U(0x2)
#define WDOG_WCR_WDZST			BIT(0)
#define WDOG_WCR_WDBG			BIT(1)
#define WDOG_WCR_WDE			BIT(2)
#define WDOG_WCR_WDT			BIT(3)
#define WDOG_WCR_SRS			BIT(4)
#define WDOG_WCR_WDA			BIT(5)
#define WDOG_WCR_SRE			BIT(6)
#define WDOG_WCR_WDW			BIT(7)

#define SRC_A53RCR0			U(0x4)
#define SRC_A53RCR1			U(0x8)
#define SRC_OTG1PHY_SCR			U(0x20)
#define SRC_OTG2PHY_SCR			U(0x24)
#define SRC_GPR1_OFFSET			U(0x74)

#define SNVS_LPCR			U(0x38)
#define SNVS_LPCR_SRTC_ENV		BIT(0)
#define SNVS_LPCR_DP_EN			BIT(5)
#define SNVS_LPCR_TOP			BIT(6)

#define IOMUXC_GPR10			U(0x28)
#define GPR_TZASC_EN			BIT(0)
#define GPR_TZASC_EN_LOCK		BIT(16)

#define ANAMIX_MISC_CTL			U(0x124)
#define DRAM_PLL_CTRL			(IMX_ANAMIX_BASE + 0x50)

#define MAX_CSU_NUM			U(64)

#define OCRAM_S_BASE			U(0x00180000)
#define OCRAM_S_SIZE			U(0x8000)
#define OCRAM_S_LIMIT			(OCRAM_S_BASE + OCRAM_S_SIZE)
#define SAVED_DRAM_TIMING_BASE		OCRAM_S_BASE

#define COUNTER_FREQUENCY		8000000 /* 8MHz */

#define IMX_WDOG_B_RESET

#define MAX_IO_HANDLES			3U
#define MAX_IO_DEVICES			2U
#define MAX_IO_BLOCK_DEVICES		1U

#define GIC_MAP		MAP_REGION_FLAT(IMX_GIC_BASE, IMX_GIC_SIZE, MT_DEVICE | MT_RW)
#define AIPS_MAP	MAP_REGION_FLAT(IMX_AIPS_BASE, IMX_AIPS_SIZE, MT_DEVICE | MT_RW) /* AIPS map */
#define OCRAM_S_MAP	MAP_REGION_FLAT(OCRAM_S_BASE, OCRAM_S_SIZE, MT_MEMORY | MT_RW) /* OCRAM_S */
#define DDRC_MAP	MAP_REGION_FLAT(IMX_DDRPHY_BASE, IMX_DDR_IPS_SIZE, MT_DEVICE | MT_RW) /* DDRMIX */
#define NOC_MAP		MAP_REGION_FLAT(IMX_NOC_BASE, IMX_NOC_SIZE, MT_DEVICE | MT_RW) /* NOC QoS */

#endif /* platform_def.h */
