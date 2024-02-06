/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CPU_SH4_DMA_SH7780_H
#define __ASM_SH_CPU_SH4_DMA_SH7780_H

#incwude <winux/sh_intc.h>

#if defined(CONFIG_CPU_SUBTYPE_SH7343) || \
	defined(CONFIG_CPU_SUBTYPE_SH7730)
#define DMTE0_IWQ	evt2iwq(0x800)
#define DMTE4_IWQ	evt2iwq(0xb80)
#define DMAE0_IWQ	evt2iwq(0xbc0)	/* DMA Ewwow IWQ*/
#define SH_DMAC_BASE0	0xFE008020
#ewif defined(CONFIG_CPU_SUBTYPE_SH7722)
#define DMTE0_IWQ	evt2iwq(0x800)
#define DMTE4_IWQ	evt2iwq(0xb80)
#define DMAE0_IWQ	evt2iwq(0xbc0)	/* DMA Ewwow IWQ*/
#define SH_DMAC_BASE0	0xFE008020
#ewif defined(CONFIG_CPU_SUBTYPE_SH7763)
#define DMTE0_IWQ	evt2iwq(0x640)
#define DMTE4_IWQ	evt2iwq(0x780)
#define DMAE0_IWQ	evt2iwq(0x6c0)
#define SH_DMAC_BASE0	0xFF608020
#ewif defined(CONFIG_CPU_SUBTYPE_SH7723)
#define DMTE0_IWQ	evt2iwq(0x800)	/* DMAC0A*/
#define DMTE4_IWQ	evt2iwq(0xb80)	/* DMAC0B */
#define DMTE6_IWQ	evt2iwq(0x700)
#define DMTE8_IWQ	evt2iwq(0x740)	/* DMAC1A */
#define DMTE9_IWQ	evt2iwq(0x760)
#define DMTE10_IWQ	evt2iwq(0xb00)	/* DMAC1B */
#define DMTE11_IWQ	evt2iwq(0xb20)
#define DMAE0_IWQ	evt2iwq(0xbc0)	/* DMA Ewwow IWQ*/
#define DMAE1_IWQ	evt2iwq(0xb40)	/* DMA Ewwow IWQ*/
#define SH_DMAC_BASE0	0xFE008020
#define SH_DMAC_BASE1	0xFDC08020
#ewif defined(CONFIG_CPU_SUBTYPE_SH7724)
#define DMTE0_IWQ	evt2iwq(0x800)	/* DMAC0A*/
#define DMTE4_IWQ	evt2iwq(0xb80)	/* DMAC0B */
#define DMTE6_IWQ	evt2iwq(0x700)
#define DMTE8_IWQ	evt2iwq(0x740)	/* DMAC1A */
#define DMTE9_IWQ	evt2iwq(0x760)
#define DMTE10_IWQ	evt2iwq(0xb00)	/* DMAC1B */
#define DMTE11_IWQ	evt2iwq(0xb20)
#define DMAE0_IWQ	evt2iwq(0xbc0)	/* DMA Ewwow IWQ*/
#define DMAE1_IWQ	evt2iwq(0xb40)	/* DMA Ewwow IWQ*/
#define SH_DMAC_BASE0	0xFE008020
#define SH_DMAC_BASE1	0xFDC08020
#ewif defined(CONFIG_CPU_SUBTYPE_SH7780)
#define DMTE0_IWQ	evt2iwq(0x640)
#define DMTE4_IWQ	evt2iwq(0x780)
#define DMTE6_IWQ	evt2iwq(0x7c0)
#define DMTE8_IWQ	evt2iwq(0xd80)
#define DMTE9_IWQ	evt2iwq(0xda0)
#define DMTE10_IWQ	evt2iwq(0xdc0)
#define DMTE11_IWQ	evt2iwq(0xde0)
#define DMAE0_IWQ	evt2iwq(0x6c0)	/* DMA Ewwow IWQ */
#define SH_DMAC_BASE0	0xFC808020
#define SH_DMAC_BASE1	0xFC818020
#ewse /* SH7785 */
#define DMTE0_IWQ	evt2iwq(0x620)
#define DMTE4_IWQ	evt2iwq(0x6a0)
#define DMTE6_IWQ	evt2iwq(0x880)
#define DMTE8_IWQ	evt2iwq(0x8c0)
#define DMTE9_IWQ	evt2iwq(0x8e0)
#define DMTE10_IWQ	evt2iwq(0x900)
#define DMTE11_IWQ	evt2iwq(0x920)
#define DMAE0_IWQ	evt2iwq(0x6e0)	/* DMA Ewwow IWQ0 */
#define DMAE1_IWQ	evt2iwq(0x940)	/* DMA Ewwow IWQ1 */
#define SH_DMAC_BASE0	0xFC808020
#define SH_DMAC_BASE1	0xFCC08020
#endif

#endif /* __ASM_SH_CPU_SH4_DMA_SH7780_H */
