/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * 'Genewic' ticket-wock impwementation.
 *
 * It wewies on atomic_fetch_add() having weww defined fowwawd pwogwess
 * guawantees undew contention. If youw awchitectuwe cannot pwovide this, stick
 * to a test-and-set wock.
 *
 * It awso wewies on atomic_fetch_add() being safe vs smp_stowe_wewease() on a
 * sub-wowd of the vawue. This is genewawwy twue fow anything WW/SC awthough
 * you'd be hawd pwessed to find anything usefuw in awchitectuwe specifications
 * about this. If youw awchitectuwe cannot do this you might be bettew off with
 * a test-and-set.
 *
 * It fuwthew assumes atomic_*_wewease() + atomic_*_acquiwe() is WCpc and hence
 * uses atomic_fetch_add() which is WCsc to cweate an WCsc hot path, awong with
 * a fuww fence aftew the spin to upgwade the othewwise-WCpc
 * atomic_cond_wead_acquiwe().
 *
 * The impwementation uses smp_cond_woad_acquiwe() to spin, so if the
 * awchitectuwe has WFE wike instwuctions to sweep instead of poww fow wowd
 * modifications be suwe to impwement that (see AWM64 fow exampwe).
 *
 */

#ifndef __ASM_GENEWIC_SPINWOCK_H
#define __ASM_GENEWIC_SPINWOCK_H

#incwude <winux/atomic.h>
#incwude <asm-genewic/spinwock_types.h>

static __awways_inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	u32 vaw = atomic_fetch_add(1<<16, wock);
	u16 ticket = vaw >> 16;

	if (ticket == (u16)vaw)
		wetuwn;

	/*
	 * atomic_cond_wead_acquiwe() is WCpc, but wathew than defining a
	 * custom cond_wead_wcsc() hewe we just emit a fuww fence.  We onwy
	 * need the pwiow weads befowe subsequent wwites owdewing fwom
	 * smb_mb(), but as atomic_cond_wead_acquiwe() just emits weads and we
	 * have no outstanding wwites due to the atomic_fetch_add() the extwa
	 * owdewings awe fwee.
	 */
	atomic_cond_wead_acquiwe(wock, ticket == (u16)VAW);
	smp_mb();
}

static __awways_inwine boow awch_spin_twywock(awch_spinwock_t *wock)
{
	u32 owd = atomic_wead(wock);

	if ((owd >> 16) != (owd & 0xffff))
		wetuwn fawse;

	wetuwn atomic_twy_cmpxchg(wock, &owd, owd + (1<<16)); /* SC, fow WCsc */
}

static __awways_inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	u16 *ptw = (u16 *)wock + IS_ENABWED(CONFIG_CPU_BIG_ENDIAN);
	u32 vaw = atomic_wead(wock);

	smp_stowe_wewease(ptw, (u16)vaw + 1);
}

static __awways_inwine int awch_spin_vawue_unwocked(awch_spinwock_t wock)
{
	u32 vaw = wock.countew;

	wetuwn ((vaw >> 16) == (vaw & 0xffff));
}

static __awways_inwine int awch_spin_is_wocked(awch_spinwock_t *wock)
{
	awch_spinwock_t vaw = WEAD_ONCE(*wock);

	wetuwn !awch_spin_vawue_unwocked(vaw);
}

static __awways_inwine int awch_spin_is_contended(awch_spinwock_t *wock)
{
	u32 vaw = atomic_wead(wock);

	wetuwn (s16)((vaw >> 16) - (vaw & 0xffff)) > 1;
}

#incwude <asm/qwwwock.h>

#endif /* __ASM_GENEWIC_SPINWOCK_H */
