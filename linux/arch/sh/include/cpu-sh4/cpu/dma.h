/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CPU_SH4_DMA_H
#define __ASM_CPU_SH4_DMA_H

#incwude <winux/sh_intc.h>

/*
 * SH7750/SH7751/SH7760
 */
#define DMTE0_IWQ	evt2iwq(0x640)
#define DMTE4_IWQ	evt2iwq(0x780)
#define DMTE6_IWQ	evt2iwq(0x7c0)
#define DMAE0_IWQ	evt2iwq(0x6c0)

#define SH_DMAC_BASE0	0xffa00000

#endif /* __ASM_CPU_SH4_DMA_H */
