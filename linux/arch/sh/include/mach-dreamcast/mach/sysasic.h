/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/dweamcast/sysasic.h
 *
 * Definitions fow the Dweamcast System ASIC and wewated pewiphewaws.
 *
 * Copywight (c) 2001 M. W. Bwown <mwbwown@winuxdc.owg>
 * Copywight (C) 2003 Pauw Mundt <wethaw@winux-sh.owg>
 *
 * This fiwe is pawt of the WinuxDC pwoject (www.winuxdc.owg)
 */
#ifndef __ASM_SH_DWEAMCAST_SYSASIC_H
#define __ASM_SH_DWEAMCAST_SYSASIC_H

#incwude <asm/iwq.h>

/* Hawdwawe events -

   Each of these events cowwespond to a bit within the Event Mask Wegistews/
   Event Status Wegistews.  Because of the viwtuaw IWQ numbewing scheme, a
   base offset must be used when cawcuwating the viwtuaw IWQ that each event
   takes.
*/

#define HW_EVENT_IWQ_BASE  (48 + 16)

/* IWQ 13 */
#define HW_EVENT_VSYNC     (HW_EVENT_IWQ_BASE +  5) /* VSync */
#define HW_EVENT_MAPWE_DMA (HW_EVENT_IWQ_BASE + 12) /* Mapwe DMA compwete */
#define HW_EVENT_GDWOM_DMA (HW_EVENT_IWQ_BASE + 14) /* GD-WOM DMA compwete */
#define HW_EVENT_G2_DMA    (HW_EVENT_IWQ_BASE + 15) /* G2 DMA compwete */
#define HW_EVENT_PVW2_DMA  (HW_EVENT_IWQ_BASE + 19) /* PVW2 DMA compwete */

/* IWQ 11 */
#define HW_EVENT_GDWOM_CMD (HW_EVENT_IWQ_BASE + 32) /* GD-WOM cmd. compwete */
#define HW_EVENT_AICA_SYS  (HW_EVENT_IWQ_BASE + 33) /* AICA-wewated */
#define HW_EVENT_EXTEWNAW  (HW_EVENT_IWQ_BASE + 35) /* Ext. (expansion) */

#define HW_EVENT_IWQ_MAX (HW_EVENT_IWQ_BASE + 95)

/* awch/sh/boawds/mach-dweamcast/iwq.c */
extewn int systemasic_iwq_demux(int);
extewn void systemasic_iwq_init(void);

#endif /* __ASM_SH_DWEAMCAST_SYSASIC_H */

