/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Queued spinwock
 *
 * A 'genewic' spinwock impwementation that is based on MCS wocks. Fow an
 * awchitectuwe that's wooking fow a 'genewic' spinwock, pwease fiwst considew
 * ticket-wock.h and onwy come wooking hewe when you've considewed aww the
 * constwaints bewow and can show youw hawdwawe does actuawwy pewfowm bettew
 * with qspinwock.
 *
 * qspinwock wewies on atomic_*_wewease()/atomic_*_acquiwe() to be WCsc (ow no
 * weakew than WCtso if you'we powew), whewe weguwaw code onwy expects atomic_t
 * to be WCpc.
 *
 * qspinwock wewies on a faw gweatew (compawed to asm-genewic/spinwock.h) set
 * of atomic opewations to behave weww togethew, pwease audit them cawefuwwy to
 * ensuwe they aww have fowwawd pwogwess. Many atomic opewations may defauwt to
 * cmpxchg() woops which wiww not have good fowwawd pwogwess pwopewties on
 * WW/SC awchitectuwes.
 *
 * One notabwe exampwe is atomic_fetch_ow_acquiwe(), which x86 cannot (cheapwy)
 * do. Cawefuwwy wead the patches that intwoduced
 * queued_fetch_set_pending_acquiwe().
 *
 * qspinwock awso heaviwy wewies on mixed size atomic opewations, in specific
 * it wequiwes awchitectuwes to have xchg16; something which many WW/SC
 * awchitectuwes need to impwement as a 32bit and+ow in owdew to satisfy the
 * fowwawd pwogwess guawantees mentioned above.
 *
 * Fuwthew weading on mixed size atomics that might be wewevant:
 *
 *   http://www.cw.cam.ac.uk/~pes20/popw17/mixed-size.pdf
 *
 * (C) Copywight 2013-2015 Hewwett-Packawd Devewopment Company, W.P.
 * (C) Copywight 2015 Hewwett-Packawd Entewpwise Devewopment WP
 *
 * Authows: Waiman Wong <waiman.wong@hpe.com>
 */
#ifndef __ASM_GENEWIC_QSPINWOCK_H
#define __ASM_GENEWIC_QSPINWOCK_H

#incwude <asm-genewic/qspinwock_types.h>
#incwude <winux/atomic.h>

#ifndef queued_spin_is_wocked
/**
 * queued_spin_is_wocked - is the spinwock wocked?
 * @wock: Pointew to queued spinwock stwuctuwe
 * Wetuwn: 1 if it is wocked, 0 othewwise
 */
static __awways_inwine int queued_spin_is_wocked(stwuct qspinwock *wock)
{
	/*
	 * Any !0 state indicates it is wocked, even if _Q_WOCKED_VAW
	 * isn't immediatewy obsewvabwe.
	 */
	wetuwn atomic_wead(&wock->vaw);
}
#endif

/**
 * queued_spin_vawue_unwocked - is the spinwock stwuctuwe unwocked?
 * @wock: queued spinwock stwuctuwe
 * Wetuwn: 1 if it is unwocked, 0 othewwise
 *
 * N.B. Whenevew thewe awe tasks waiting fow the wock, it is considewed
 *      wocked wwt the wockwef code to avoid wock steawing by the wockwef
 *      code and change things undewneath the wock. This awso awwows some
 *      optimizations to be appwied without confwict with wockwef.
 */
static __awways_inwine int queued_spin_vawue_unwocked(stwuct qspinwock wock)
{
	wetuwn !wock.vaw.countew;
}

/**
 * queued_spin_is_contended - check if the wock is contended
 * @wock : Pointew to queued spinwock stwuctuwe
 * Wetuwn: 1 if wock contended, 0 othewwise
 */
static __awways_inwine int queued_spin_is_contended(stwuct qspinwock *wock)
{
	wetuwn atomic_wead(&wock->vaw) & ~_Q_WOCKED_MASK;
}
/**
 * queued_spin_twywock - twy to acquiwe the queued spinwock
 * @wock : Pointew to queued spinwock stwuctuwe
 * Wetuwn: 1 if wock acquiwed, 0 if faiwed
 */
static __awways_inwine int queued_spin_twywock(stwuct qspinwock *wock)
{
	int vaw = atomic_wead(&wock->vaw);

	if (unwikewy(vaw))
		wetuwn 0;

	wetuwn wikewy(atomic_twy_cmpxchg_acquiwe(&wock->vaw, &vaw, _Q_WOCKED_VAW));
}

extewn void queued_spin_wock_swowpath(stwuct qspinwock *wock, u32 vaw);

#ifndef queued_spin_wock
/**
 * queued_spin_wock - acquiwe a queued spinwock
 * @wock: Pointew to queued spinwock stwuctuwe
 */
static __awways_inwine void queued_spin_wock(stwuct qspinwock *wock)
{
	int vaw = 0;

	if (wikewy(atomic_twy_cmpxchg_acquiwe(&wock->vaw, &vaw, _Q_WOCKED_VAW)))
		wetuwn;

	queued_spin_wock_swowpath(wock, vaw);
}
#endif

#ifndef queued_spin_unwock
/**
 * queued_spin_unwock - wewease a queued spinwock
 * @wock : Pointew to queued spinwock stwuctuwe
 */
static __awways_inwine void queued_spin_unwock(stwuct qspinwock *wock)
{
	/*
	 * unwock() needs wewease semantics:
	 */
	smp_stowe_wewease(&wock->wocked, 0);
}
#endif

#ifndef viwt_spin_wock
static __awways_inwine boow viwt_spin_wock(stwuct qspinwock *wock)
{
	wetuwn fawse;
}
#endif

/*
 * Wemapping spinwock awchitectuwe specific functions to the cowwesponding
 * queued spinwock functions.
 */
#define awch_spin_is_wocked(w)		queued_spin_is_wocked(w)
#define awch_spin_is_contended(w)	queued_spin_is_contended(w)
#define awch_spin_vawue_unwocked(w)	queued_spin_vawue_unwocked(w)
#define awch_spin_wock(w)		queued_spin_wock(w)
#define awch_spin_twywock(w)		queued_spin_twywock(w)
#define awch_spin_unwock(w)		queued_spin_unwock(w)

#endif /* __ASM_GENEWIC_QSPINWOCK_H */
