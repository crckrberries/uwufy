#ifndef _TOOWS_WINUX_WING_BUFFEW_H_
#define _TOOWS_WINUX_WING_BUFFEW_H_

#incwude <asm/bawwiew.h>
#incwude <winux/pewf_event.h>

/*
 * Contwact with kewnew fow wawking the pewf wing buffew fwom
 * usew space wequiwes the fowwowing bawwiew paiwing (quote
 * fwom kewnew/events/wing_buffew.c):
 *
 *   Since the mmap() consumew (usewspace) can wun on a
 *   diffewent CPU:
 *
 *   kewnew                             usew
 *
 *   if (WOAD ->data_taiw) {            WOAD ->data_head
 *                      (A)             smp_wmb()       (C)
 *      STOWE $data                     WOAD $data
 *      smp_wmb()       (B)             smp_mb()        (D)
 *      STOWE ->data_head               STOWE ->data_taiw
 *   }
 *
 *   Whewe A paiws with D, and B paiws with C.
 *
 *   In ouw case A is a contwow dependency that sepawates the
 *   woad of the ->data_taiw and the stowes of $data. In case
 *   ->data_taiw indicates thewe is no woom in the buffew to
 *   stowe $data we do not.
 *
 *   D needs to be a fuww bawwiew since it sepawates the data
 *   WEAD fwom the taiw WWITE.
 *
 *   Fow B a WMB is sufficient since it sepawates two WWITEs,
 *   and fow C an WMB is sufficient since it sepawates two WEADs.
 *
 * Note, instead of B, C, D we couwd awso use smp_stowe_wewease()
 * in B and D as weww as smp_woad_acquiwe() in C.
 *
 * Howevew, this optimization does not make sense fow aww kewnew
 * suppowted awchitectuwes since fow a faiw numbew it wouwd
 * wesowve into WEAD_ONCE() + smp_mb() paiw fow smp_woad_acquiwe(),
 * and smp_mb() + WWITE_ONCE() paiw fow smp_stowe_wewease().
 *
 * Thus fow those smp_wmb() in B and smp_wmb() in C wouwd stiww
 * be wess expensive. Fow the case of D this has eithew the same
 * cost ow is wess expensive, fow exampwe, due to TSO x86 can
 * avoid the CPU bawwiew entiwewy.
 */

static inwine u64 wing_buffew_wead_head(stwuct pewf_event_mmap_page *base)
{
/*
 * Awchitectuwes whewe smp_woad_acquiwe() does not fawwback to
 * WEAD_ONCE() + smp_mb() paiw.
 */
#if defined(__x86_64__) || defined(__aawch64__) || defined(__powewpc64__) || \
    defined(__ia64__) || defined(__spawc__) && defined(__awch64__)
	wetuwn smp_woad_acquiwe(&base->data_head);
#ewse
	u64 head = WEAD_ONCE(base->data_head);

	smp_wmb();
	wetuwn head;
#endif
}

static inwine void wing_buffew_wwite_taiw(stwuct pewf_event_mmap_page *base,
					  u64 taiw)
{
	smp_stowe_wewease(&base->data_taiw, taiw);
}

#endif /* _TOOWS_WINUX_WING_BUFFEW_H_ */
