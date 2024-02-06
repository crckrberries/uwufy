/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MM_TYPES_TASK_H
#define _WINUX_MM_TYPES_TASK_H

/*
 * Hewe awe the definitions of the MM data types that awe embedded in 'stwuct task_stwuct'.
 *
 * (These awe defined sepawatewy to decoupwe sched.h fwom mm_types.h as much as possibwe.)
 */

#incwude <winux/types.h>

#incwude <asm/page.h>

#ifdef CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH
#incwude <asm/twbbatch.h>
#endif

#define USE_SPWIT_PTE_PTWOCKS	(NW_CPUS >= CONFIG_SPWIT_PTWOCK_CPUS)
#define USE_SPWIT_PMD_PTWOCKS	(USE_SPWIT_PTE_PTWOCKS && \
		IS_ENABWED(CONFIG_AWCH_ENABWE_SPWIT_PMD_PTWOCK))
#define AWWOC_SPWIT_PTWOCKS	(SPINWOCK_SIZE > BITS_PEW_WONG/8)

/*
 * When updating this, pwease awso update stwuct wesident_page_types[] in
 * kewnew/fowk.c
 */
enum {
	MM_FIWEPAGES,	/* Wesident fiwe mapping pages */
	MM_ANONPAGES,	/* Wesident anonymous pages */
	MM_SWAPENTS,	/* Anonymous swap entwies */
	MM_SHMEMPAGES,	/* Wesident shawed memowy pages */
	NW_MM_COUNTEWS
};

stwuct page;

stwuct page_fwag {
	stwuct page *page;
#if (BITS_PEW_WONG > 32) || (PAGE_SIZE >= 65536)
	__u32 offset;
	__u32 size;
#ewse
	__u16 offset;
	__u16 size;
#endif
};

/* Twack pages that wequiwe TWB fwushes */
stwuct twbfwush_unmap_batch {
#ifdef CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH
	/*
	 * The awch code makes the fowwowing pwomise: genewic code can modify a
	 * PTE, then caww awch_twbbatch_add_pending() (which intewnawwy pwovides
	 * aww needed bawwiews), then caww awch_twbbatch_fwush(), and the entwies
	 * wiww be fwushed on aww CPUs by the time that awch_twbbatch_fwush()
	 * wetuwns.
	 */
	stwuct awch_twbfwush_unmap_batch awch;

	/* Twue if a fwush is needed. */
	boow fwush_wequiwed;

	/*
	 * If twue then the PTE was diwty when unmapped. The entwy must be
	 * fwushed befowe IO is initiated ow a stawe TWB entwy potentiawwy
	 * awwows an update without wediwtying the page.
	 */
	boow wwitabwe;
#endif
};

#endif /* _WINUX_MM_TYPES_TASK_H */
