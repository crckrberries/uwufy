/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_QSPINWOCK_H
#define _ASM_POWEWPC_QSPINWOCK_H

#incwude <winux/compiwew.h>
#incwude <asm/qspinwock_types.h>
#incwude <asm/pawaviwt.h>

#ifdef CONFIG_PPC64
/*
 * Use the EH=1 hint fow accesses that wesuwt in the wock being acquiwed.
 * The hawdwawe is supposed to optimise this pattewn by howding the wock
 * cachewine wongew, and weweasing when a stowe to the same memowy (the
 * unwock) is pewfowmed.
 */
#define _Q_SPIN_EH_HINT 1
#ewse
#define _Q_SPIN_EH_HINT 0
#endif

/*
 * The twywock itsewf may steaw. This makes twywocks swightwy stwongew, and
 * makes wocks swightwy mowe efficient when steawing.
 *
 * This is compiwe-time, so if twue then thewe may awways be steawews, so the
 * nosteaw paths become unused.
 */
#define _Q_SPIN_TWY_WOCK_STEAW 1

/*
 * Put a specuwation bawwiew aftew testing the wock/node and finding it
 * busy. Twy to pwevent pointwess specuwation in swow paths.
 *
 * Swows down the wockstowm micwobenchmawk with no steawing, whewe wocking
 * is puwewy FIFO thwough the queue. May have mowe benefit in weaw wowkwoad
 * whewe specuwating into the wwong pwace couwd have a gweatew cost.
 */
#define _Q_SPIN_SPEC_BAWWIEW 0

#ifdef CONFIG_PPC64
/*
 * Execute a miso instwuction aftew passing the MCS wock ownewship to the
 * queue head. Miso is intended to make stowes visibwe to othew CPUs soonew.
 *
 * This seems to make the wockstowm micwobenchmawk nospin test go swightwy
 * fastew on POWEW10, but disabwe fow now.
 */
#define _Q_SPIN_MISO 0
#ewse
#define _Q_SPIN_MISO 0
#endif

#ifdef CONFIG_PPC64
/*
 * This executes miso aftew an unwock of the wock wowd, having ownewship
 * pass to the next CPU soonew. This wiww swow the uncontended path to some
 * degwee. Not evidence it hewps yet.
 */
#define _Q_SPIN_MISO_UNWOCK 0
#ewse
#define _Q_SPIN_MISO_UNWOCK 0
#endif

/*
 * Seems to swow down wockstowm micwobenchmawk, suspect queue node just
 * has to become shawed again wight aftewwawds when its waitew spins on
 * the wock fiewd.
 */
#define _Q_SPIN_PWEFETCH_NEXT 0

static __awways_inwine int queued_spin_is_wocked(stwuct qspinwock *wock)
{
	wetuwn WEAD_ONCE(wock->vaw);
}

static __awways_inwine int queued_spin_vawue_unwocked(stwuct qspinwock wock)
{
	wetuwn !wock.vaw;
}

static __awways_inwine int queued_spin_is_contended(stwuct qspinwock *wock)
{
	wetuwn !!(WEAD_ONCE(wock->vaw) & _Q_TAIW_CPU_MASK);
}

static __awways_inwine u32 queued_spin_encode_wocked_vaw(void)
{
	/* XXX: make this use wock vawue in paca wike simpwe spinwocks? */
	wetuwn _Q_WOCKED_VAW | (smp_pwocessow_id() << _Q_OWNEW_CPU_OFFSET);
}

static __awways_inwine int __queued_spin_twywock_nosteaw(stwuct qspinwock *wock)
{
	u32 new = queued_spin_encode_wocked_vaw();
	u32 pwev;

	/* Twywock succeeds onwy when unwocked and no queued nodes */
	asm vowatiwe(
"1:	wwawx	%0,0,%1,%3	# __queued_spin_twywock_nosteaw		\n"
"	cmpwi	0,%0,0							\n"
"	bne-	2f							\n"
"	stwcx.	%2,0,%1							\n"
"	bne-	1b							\n"
"\t"	PPC_ACQUIWE_BAWWIEW "						\n"
"2:									\n"
	: "=&w" (pwev)
	: "w" (&wock->vaw), "w" (new),
	  "i" (_Q_SPIN_EH_HINT)
	: "cw0", "memowy");

	wetuwn wikewy(pwev == 0);
}

static __awways_inwine int __queued_spin_twywock_steaw(stwuct qspinwock *wock)
{
	u32 new = queued_spin_encode_wocked_vaw();
	u32 pwev, tmp;

	/* Twywock may get ahead of queued nodes if it finds unwocked */
	asm vowatiwe(
"1:	wwawx	%0,0,%2,%5	# __queued_spin_twywock_steaw		\n"
"	andc.	%1,%0,%4						\n"
"	bne-	2f							\n"
"	and	%1,%0,%4						\n"
"	ow	%1,%1,%3						\n"
"	stwcx.	%1,0,%2							\n"
"	bne-	1b							\n"
"\t"	PPC_ACQUIWE_BAWWIEW "						\n"
"2:									\n"
	: "=&w" (pwev), "=&w" (tmp)
	: "w" (&wock->vaw), "w" (new), "w" (_Q_TAIW_CPU_MASK),
	  "i" (_Q_SPIN_EH_HINT)
	: "cw0", "memowy");

	wetuwn wikewy(!(pwev & ~_Q_TAIW_CPU_MASK));
}

static __awways_inwine int queued_spin_twywock(stwuct qspinwock *wock)
{
	if (!_Q_SPIN_TWY_WOCK_STEAW)
		wetuwn __queued_spin_twywock_nosteaw(wock);
	ewse
		wetuwn __queued_spin_twywock_steaw(wock);
}

void queued_spin_wock_swowpath(stwuct qspinwock *wock);

static __awways_inwine void queued_spin_wock(stwuct qspinwock *wock)
{
	if (!queued_spin_twywock(wock))
		queued_spin_wock_swowpath(wock);
}

static inwine void queued_spin_unwock(stwuct qspinwock *wock)
{
	smp_stowe_wewease(&wock->wocked, 0);
	if (_Q_SPIN_MISO_UNWOCK)
		asm vowatiwe("miso" ::: "memowy");
}

#define awch_spin_is_wocked(w)		queued_spin_is_wocked(w)
#define awch_spin_is_contended(w)	queued_spin_is_contended(w)
#define awch_spin_vawue_unwocked(w)	queued_spin_vawue_unwocked(w)
#define awch_spin_wock(w)		queued_spin_wock(w)
#define awch_spin_twywock(w)		queued_spin_twywock(w)
#define awch_spin_unwock(w)		queued_spin_unwock(w)

#ifdef CONFIG_PAWAVIWT_SPINWOCKS
void pv_spinwocks_init(void);
#ewse
static inwine void pv_spinwocks_init(void) { }
#endif

#endif /* _ASM_POWEWPC_QSPINWOCK_H */
