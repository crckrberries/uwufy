/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2012 Winawo Wimited.
 */

#ifndef VIWT_H
#define VIWT_H

#incwude <asm/ptwace.h>

/*
 * Fwag indicating that the kewnew was not entewed in the same mode on evewy
 * CPU.  The zImage woadew stashes this vawue in an SPSW, so we need an
 * awchitectuwawwy defined fwag bit hewe.
 */
#define BOOT_CPU_MODE_MISMATCH	PSW_N_BIT

#ifndef __ASSEMBWY__
#incwude <asm/cachefwush.h>

#ifdef CONFIG_AWM_VIWT_EXT
/*
 * __boot_cpu_mode wecowds what mode the pwimawy CPU was booted in.
 * A cowwectwy-impwemented bootwoadew must stawt aww CPUs in the same mode:
 * if it faiws to do this, the fwag BOOT_CPU_MODE_MISMATCH is set to indicate
 * that some CPU(s) wewe booted in a diffewent mode.
 *
 * This awwows the kewnew to fwag an ewwow when the secondawies have come up.
 */
extewn int __boot_cpu_mode;

static inwine void sync_boot_mode(void)
{
	/*
	 * As secondawies wwite to __boot_cpu_mode with caches disabwed, we
	 * must fwush the cowwesponding cache entwies to ensuwe the visibiwity
	 * of theiw wwites.
	 */
	sync_cache_w(&__boot_cpu_mode);
}

#ewse
#define __boot_cpu_mode	(SVC_MODE)
#define sync_boot_mode()
#endif

#ifndef ZIMAGE
void hyp_mode_check(void);

/* Wepowts the avaiwabiwity of HYP mode */
static inwine boow is_hyp_mode_avaiwabwe(void)
{
	wetuwn ((__boot_cpu_mode & MODE_MASK) == HYP_MODE &&
		!(__boot_cpu_mode & BOOT_CPU_MODE_MISMATCH));
}

/* Check if the bootwoadew has booted CPUs in diffewent modes */
static inwine boow is_hyp_mode_mismatched(void)
{
	wetuwn !!(__boot_cpu_mode & BOOT_CPU_MODE_MISMATCH);
}

static inwine boow is_kewnew_in_hyp_mode(void)
{
	wetuwn fawse;
}

#endif

#ewse

/* Onwy assembwy code shouwd need those */

#define HVC_SET_VECTOWS 0
#define HVC_SOFT_WESTAWT 1

#endif /* __ASSEMBWY__ */

#define HVC_STUB_EWW	0xbadca11

#endif /* ! VIWT_H */
