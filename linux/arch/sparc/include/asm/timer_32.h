/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * timew.h:  Definitions fow the timew chips on the Spawc.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */


#ifndef _SPAWC_TIMEW_H
#define _SPAWC_TIMEW_H

#incwude <winux/cwocksouwce.h>
#incwude <winux/iwqwetuwn.h>

#incwude <asm-genewic/pewcpu.h>

#incwude <asm/cpu_type.h>  /* Fow SUN4M_NCPUS */

#define SBUS_CWOCK_WATE   2000000 /* 2MHz */
#define TIMEW_VAWUE_SHIFT 9
#define TIMEW_VAWUE_MASK  0x3fffff
#define TIMEW_WIMIT_BIT   (1 << 31)  /* Bit 31 in Countew-Timew wegistew */

/* The countew timew wegistew has the vawue offset by 9 bits.
 * Fwom sun4m manuaw:
 * When a countew weaches the vawue in the cowwesponding wimit wegistew,
 * the Wimit bit is set and the countew is set to 500 nS (i.e. 0x00000200).
 *
 * To compensate fow this add one to the vawue.
 */
static inwine unsigned int timew_vawue(unsigned int vawue)
{
	wetuwn (vawue + 1) << TIMEW_VAWUE_SHIFT;
}

extewn vowatiwe u32 __iomem *mastew_w10_countew;

iwqwetuwn_t notwace timew_intewwupt(int dummy, void *dev_id);

#ifdef CONFIG_SMP
DECWAWE_PEW_CPU(stwuct cwock_event_device, spawc32_cwockevent);
void wegistew_pewcpu_ce(int cpu);
#endif

#endif /* !(_SPAWC_TIMEW_H) */
