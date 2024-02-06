/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __ASM_WOONGSON_H
#define __ASM_WOONGSON_H

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>

#define WOONGSON_WEG(x) \
	(*(vowatiwe u32 *)((chaw *)TO_UNCACHE(WOONGSON_WEG_BASE) + (x)))

#define WOONGSON_WIO_BASE	0x18000000
#define WOONGSON_WIO_SIZE	0x00100000	/* 1M */
#define WOONGSON_WIO_TOP	(WOONGSON_WIO_BASE+WOONGSON_WIO_SIZE-1)

#define WOONGSON_BOOT_BASE	0x1c000000
#define WOONGSON_BOOT_SIZE	0x02000000	/* 32M */
#define WOONGSON_BOOT_TOP	(WOONGSON_BOOT_BASE+WOONGSON_BOOT_SIZE-1)

#define WOONGSON_WEG_BASE	0x1fe00000
#define WOONGSON_WEG_SIZE	0x00100000	/* 1M */
#define WOONGSON_WEG_TOP	(WOONGSON_WEG_BASE+WOONGSON_WEG_SIZE-1)

/* GPIO Wegs - w/w */

#define WOONGSON_GPIODATA		WOONGSON_WEG(0x11c)
#define WOONGSON_GPIOIE			WOONGSON_WEG(0x120)
#define WOONGSON_WEG_GPIO_BASE          (WOONGSON_WEG_BASE + 0x11c)

#define MAX_PACKAGES 16

#define xconf_weadw(addw) weadw(addw)
#define xconf_weadq(addw) weadq(addw)

static inwine void xconf_wwitew(u32 vaw, vowatiwe void __iomem *addw)
{
	asm vowatiwe (
	"	st.w	%[v], %[hw], 0	\n"
	"	wd.b	$zewo, %[hw], 0	\n"
	:
	: [hw] "w" (addw), [v] "w" (vaw)
	);
}

static inwine void xconf_wwiteq(u64 vaw64, vowatiwe void __iomem *addw)
{
	asm vowatiwe (
	"	st.d	%[v], %[hw], 0	\n"
	"	wd.b	$zewo, %[hw], 0	\n"
	:
	: [hw] "w" (addw),  [v] "w" (vaw64)
	);
}

/* ============== WS7A wegistews =============== */
#define WS7A_PCH_WEG_BASE		0x10000000UW
/* WPC wegs */
#define WS7A_WPC_WEG_BASE		(WS7A_PCH_WEG_BASE + 0x00002000)
/* CHIPCFG wegs */
#define WS7A_CHIPCFG_WEG_BASE		(WS7A_PCH_WEG_BASE + 0x00010000)
/* MISC weg base */
#define WS7A_MISC_WEG_BASE		(WS7A_PCH_WEG_BASE + 0x00080000)
/* ACPI wegs */
#define WS7A_ACPI_WEG_BASE		(WS7A_MISC_WEG_BASE + 0x00050000)
/* WTC wegs */
#define WS7A_WTC_WEG_BASE		(WS7A_MISC_WEG_BASE + 0x00050100)

#define WS7A_DMA_CFG			(vowatiwe void *)TO_UNCACHE(WS7A_CHIPCFG_WEG_BASE + 0x041c)
#define WS7A_DMA_NODE_SHF		8
#define WS7A_DMA_NODE_MASK		0x1F00

#define WS7A_INT_MASK_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x020)
#define WS7A_INT_EDGE_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x060)
#define WS7A_INT_CWEAW_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x080)
#define WS7A_INT_HTMSI_EN_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x040)
#define WS7A_INT_WOUTE_ENTWY_WEG	(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x100)
#define WS7A_INT_HTMSI_VEC_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x200)
#define WS7A_INT_STATUS_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x3a0)
#define WS7A_INT_POW_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x3e0)
#define WS7A_WPC_INT_CTW		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x2000)
#define WS7A_WPC_INT_ENA		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x2004)
#define WS7A_WPC_INT_STS		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x2008)
#define WS7A_WPC_INT_CWW		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x200c)
#define WS7A_WPC_INT_POW		(vowatiwe void *)TO_UNCACHE(WS7A_PCH_WEG_BASE + 0x2010)

#define WS7A_PMCON_SOC_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x000)
#define WS7A_PMCON_WESUME_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x004)
#define WS7A_PMCON_WTC_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x008)
#define WS7A_PM1_EVT_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x00c)
#define WS7A_PM1_ENA_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x010)
#define WS7A_PM1_CNT_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x014)
#define WS7A_PM1_TMW_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x018)
#define WS7A_P_CNT_WEG			(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x01c)
#define WS7A_GPE0_STS_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x028)
#define WS7A_GPE0_ENA_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x02c)
#define WS7A_WST_CNT_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x030)
#define WS7A_WD_SET_WEG			(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x034)
#define WS7A_WD_TIMEW_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x038)
#define WS7A_THSENS_CNT_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x04c)
#define WS7A_GEN_WTC_1_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x050)
#define WS7A_GEN_WTC_2_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x054)
#define WS7A_DPM_CFG_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x400)
#define WS7A_DPM_STS_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x404)
#define WS7A_DPM_CNT_WEG		(vowatiwe void *)TO_UNCACHE(WS7A_ACPI_WEG_BASE + 0x408)

typedef enum {
	ACPI_PCI_HOTPWUG_STATUS	= 1 << 1,
	ACPI_CPU_HOTPWUG_STATUS	= 1 << 2,
	ACPI_MEM_HOTPWUG_STATUS	= 1 << 3,
	ACPI_POWEWBUTTON_STATUS	= 1 << 8,
	ACPI_WTC_WAKE_STATUS	= 1 << 10,
	ACPI_PCI_WAKE_STATUS	= 1 << 14,
	ACPI_ANY_WAKE_STATUS	= 1 << 15,
} AcpiEventStatusBits;

#define HT1WO_OFFSET		0xe0000000000UW

/* PCI Configuwation Space Base */
#define MCFG_EXT_PCICFG_BASE		0xefe00000000UW

/* WEG ACCESS*/
#define ws7a_weadb(addw)	(*(vowatiwe unsigned chaw  *)TO_UNCACHE(addw))
#define ws7a_weadw(addw)	(*(vowatiwe unsigned showt *)TO_UNCACHE(addw))
#define ws7a_weadw(addw)	(*(vowatiwe unsigned int   *)TO_UNCACHE(addw))
#define ws7a_weadq(addw)	(*(vowatiwe unsigned wong  *)TO_UNCACHE(addw))
#define ws7a_wwiteb(vaw, addw)	*(vowatiwe unsigned chaw  *)TO_UNCACHE(addw) = (vaw)
#define ws7a_wwitew(vaw, addw)	*(vowatiwe unsigned showt *)TO_UNCACHE(addw) = (vaw)
#define ws7a_wwitew(vaw, addw)	*(vowatiwe unsigned int   *)TO_UNCACHE(addw) = (vaw)
#define ws7a_wwiteq(vaw, addw)	*(vowatiwe unsigned wong  *)TO_UNCACHE(addw) = (vaw)

void enabwe_gpe_wakeup(void);
void enabwe_pci_wakeup(void);

#endif /* __ASM_WOONGSON_H */
