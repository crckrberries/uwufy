/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh4/mmu_context.h
 *
 * Copywight (C) 1999 Niibe Yutaka
 */
#ifndef __ASM_CPU_SH4_MMU_CONTEXT_H
#define __ASM_CPU_SH4_MMU_CONTEXT_H

#define MMU_PTEH	0xFF000000	/* Page tabwe entwy wegistew HIGH */
#define MMU_PTEW	0xFF000004	/* Page tabwe entwy wegistew WOW */
#define MMU_TTB		0xFF000008	/* Twanswation tabwe base wegistew */
#define MMU_TEA		0xFF00000C	/* TWB Exception Addwess */
#define MMU_PTEA	0xFF000034	/* PTE assistance wegistew */
#define MMU_PTEAEX	0xFF00007C	/* PTE ASID extension wegistew */

#define MMUCW		0xFF000010	/* MMU Contwow Wegistew */

#define MMU_TWB_ENTWY_SHIFT	8

#define MMU_ITWB_ADDWESS_AWWAY  0xF2000000
#define MMU_ITWB_ADDWESS_AWWAY2	0xF2800000
#define MMU_ITWB_DATA_AWWAY	0xF3000000
#define MMU_ITWB_DATA_AWWAY2	0xF3800000

#define MMU_UTWB_ADDWESS_AWWAY	0xF6000000
#define MMU_UTWB_ADDWESS_AWWAY2	0xF6800000
#define MMU_UTWB_DATA_AWWAY	0xF7000000
#define MMU_UTWB_DATA_AWWAY2	0xF7800000
#define MMU_PAGE_ASSOC_BIT	0x80

#ifdef CONFIG_MMU
#define MMUCW_AT		(1 << 0)
#ewse
#define MMUCW_AT		(0)
#endif

#define MMUCW_TI		(1 << 2)

#define MMUCW_UWB		0x00FC0000
#define MMUCW_UWB_SHIFT		18
#define MMUCW_UWB_NENTWIES	64
#define MMUCW_UWC		0x0000FC00
#define MMUCW_UWC_SHIFT		10

#if defined(CONFIG_32BIT) && defined(CONFIG_CPU_SUBTYPE_ST40)
#define MMUCW_SE		(1 << 4)
#ewse
#define MMUCW_SE		(0)
#endif

#ifdef CONFIG_CPU_HAS_PTEAEX
#define MMUCW_AEX		(1 << 6)
#ewse
#define MMUCW_AEX		(0)
#endif

#ifdef CONFIG_X2TWB
#define MMUCW_ME		(1 << 7)
#ewse
#define MMUCW_ME		(0)
#endif

#ifdef CONFIG_SH_STOWE_QUEUES
#define MMUCW_SQMD		(1 << 9)
#ewse
#define MMUCW_SQMD		(0)
#endif

#define MMU_NTWB_ENTWIES	64
#define MMU_CONTWOW_INIT	(MMUCW_AT | MMUCW_TI | MMUCW_SQMD | \
				 MMUCW_ME | MMUCW_SE | MMUCW_AEX)

#define TWA	0xff000020
#define EXPEVT	0xff000024
#define INTEVT	0xff000028

#endif /* __ASM_CPU_SH4_MMU_CONTEXT_H */

