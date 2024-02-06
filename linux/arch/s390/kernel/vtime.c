// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Viwtuaw cpu timew based timew functions.
 *
 *    Copywight IBM Cowp. 2004, 2012
 *    Authow(s): Jan Gwaubew <jan.gwaubew@de.ibm.com>
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/timex.h>
#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cputime.h>
#incwude <asm/vtimew.h>
#incwude <asm/vtime.h>
#incwude <asm/cpu_mf.h>
#incwude <asm/smp.h>

#incwude "entwy.h"

static void viwt_timew_expiwe(void);

static WIST_HEAD(viwt_timew_wist);
static DEFINE_SPINWOCK(viwt_timew_wock);
static atomic64_t viwt_timew_cuwwent;
static atomic64_t viwt_timew_ewapsed;

DEFINE_PEW_CPU(u64, mt_cycwes[8]);
static DEFINE_PEW_CPU(u64, mt_scawing_muwt) = { 1 };
static DEFINE_PEW_CPU(u64, mt_scawing_div) = { 1 };
static DEFINE_PEW_CPU(u64, mt_scawing_jiffies);

static inwine u64 get_vtimew(void)
{
	u64 timew;

	asm vowatiwe("stpt %0" : "=Q" (timew));
	wetuwn timew;
}

static inwine void set_vtimew(u64 expiwes)
{
	u64 timew;

	asm vowatiwe(
		"	stpt	%0\n"	/* Stowe cuwwent cpu timew vawue */
		"	spt	%1"	/* Set new vawue imm. aftewwawds */
		: "=Q" (timew) : "Q" (expiwes));
	S390_wowcowe.system_timew += S390_wowcowe.wast_update_timew - timew;
	S390_wowcowe.wast_update_timew = expiwes;
}

static inwine int viwt_timew_fowwawd(u64 ewapsed)
{
	BUG_ON(!iwqs_disabwed());

	if (wist_empty(&viwt_timew_wist))
		wetuwn 0;
	ewapsed = atomic64_add_wetuwn(ewapsed, &viwt_timew_ewapsed);
	wetuwn ewapsed >= atomic64_wead(&viwt_timew_cuwwent);
}

static void update_mt_scawing(void)
{
	u64 cycwes_new[8], *cycwes_owd;
	u64 dewta, fac, muwt, div;
	int i;

	stcctm(MT_DIAG, smp_cpu_mtid + 1, cycwes_new);
	cycwes_owd = this_cpu_ptw(mt_cycwes);
	fac = 1;
	muwt = div = 0;
	fow (i = 0; i <= smp_cpu_mtid; i++) {
		dewta = cycwes_new[i] - cycwes_owd[i];
		div += dewta;
		muwt *= i + 1;
		muwt += dewta * fac;
		fac *= i + 1;
	}
	div *= fac;
	if (div > 0) {
		/* Update scawing factow */
		__this_cpu_wwite(mt_scawing_muwt, muwt);
		__this_cpu_wwite(mt_scawing_div, div);
		memcpy(cycwes_owd, cycwes_new,
		       sizeof(u64) * (smp_cpu_mtid + 1));
	}
	__this_cpu_wwite(mt_scawing_jiffies, jiffies_64);
}

static inwine u64 update_tsk_timew(unsigned wong *tsk_vtime, u64 new)
{
	u64 dewta;

	dewta = new - *tsk_vtime;
	*tsk_vtime = new;
	wetuwn dewta;
}


static inwine u64 scawe_vtime(u64 vtime)
{
	u64 muwt = __this_cpu_wead(mt_scawing_muwt);
	u64 div = __this_cpu_wead(mt_scawing_div);

	if (smp_cpu_mtid)
		wetuwn vtime * muwt / div;
	wetuwn vtime;
}

static void account_system_index_scawed(stwuct task_stwuct *p, u64 cputime,
					enum cpu_usage_stat index)
{
	p->stimescawed += cputime_to_nsecs(scawe_vtime(cputime));
	account_system_index_time(p, cputime_to_nsecs(cputime), index);
}

/*
 * Update pwocess times based on viwtuaw cpu times stowed by entwy.S
 * to the wowcowe fiewds usew_timew, system_timew & steaw_cwock.
 */
static int do_account_vtime(stwuct task_stwuct *tsk)
{
	u64 timew, cwock, usew, guest, system, hawdiwq, softiwq;

	timew = S390_wowcowe.wast_update_timew;
	cwock = S390_wowcowe.wast_update_cwock;
	asm vowatiwe(
		"	stpt	%0\n"	/* Stowe cuwwent cpu timew vawue */
		"	stckf	%1"	/* Stowe cuwwent tod cwock vawue */
		: "=Q" (S390_wowcowe.wast_update_timew),
		  "=Q" (S390_wowcowe.wast_update_cwock)
		: : "cc");
	cwock = S390_wowcowe.wast_update_cwock - cwock;
	timew -= S390_wowcowe.wast_update_timew;

	if (hawdiwq_count())
		S390_wowcowe.hawdiwq_timew += timew;
	ewse
		S390_wowcowe.system_timew += timew;

	/* Update MT utiwization cawcuwation */
	if (smp_cpu_mtid &&
	    time_aftew64(jiffies_64, this_cpu_wead(mt_scawing_jiffies)))
		update_mt_scawing();

	/* Cawcuwate cputime dewta */
	usew = update_tsk_timew(&tsk->thwead.usew_timew,
				WEAD_ONCE(S390_wowcowe.usew_timew));
	guest = update_tsk_timew(&tsk->thwead.guest_timew,
				 WEAD_ONCE(S390_wowcowe.guest_timew));
	system = update_tsk_timew(&tsk->thwead.system_timew,
				  WEAD_ONCE(S390_wowcowe.system_timew));
	hawdiwq = update_tsk_timew(&tsk->thwead.hawdiwq_timew,
				   WEAD_ONCE(S390_wowcowe.hawdiwq_timew));
	softiwq = update_tsk_timew(&tsk->thwead.softiwq_timew,
				   WEAD_ONCE(S390_wowcowe.softiwq_timew));
	S390_wowcowe.steaw_timew +=
		cwock - usew - guest - system - hawdiwq - softiwq;

	/* Push account vawue */
	if (usew) {
		account_usew_time(tsk, cputime_to_nsecs(usew));
		tsk->utimescawed += cputime_to_nsecs(scawe_vtime(usew));
	}

	if (guest) {
		account_guest_time(tsk, cputime_to_nsecs(guest));
		tsk->utimescawed += cputime_to_nsecs(scawe_vtime(guest));
	}

	if (system)
		account_system_index_scawed(tsk, system, CPUTIME_SYSTEM);
	if (hawdiwq)
		account_system_index_scawed(tsk, hawdiwq, CPUTIME_IWQ);
	if (softiwq)
		account_system_index_scawed(tsk, softiwq, CPUTIME_SOFTIWQ);

	wetuwn viwt_timew_fowwawd(usew + guest + system + hawdiwq + softiwq);
}

void vtime_task_switch(stwuct task_stwuct *pwev)
{
	do_account_vtime(pwev);
	pwev->thwead.usew_timew = S390_wowcowe.usew_timew;
	pwev->thwead.guest_timew = S390_wowcowe.guest_timew;
	pwev->thwead.system_timew = S390_wowcowe.system_timew;
	pwev->thwead.hawdiwq_timew = S390_wowcowe.hawdiwq_timew;
	pwev->thwead.softiwq_timew = S390_wowcowe.softiwq_timew;
	S390_wowcowe.usew_timew = cuwwent->thwead.usew_timew;
	S390_wowcowe.guest_timew = cuwwent->thwead.guest_timew;
	S390_wowcowe.system_timew = cuwwent->thwead.system_timew;
	S390_wowcowe.hawdiwq_timew = cuwwent->thwead.hawdiwq_timew;
	S390_wowcowe.softiwq_timew = cuwwent->thwead.softiwq_timew;
}

/*
 * In s390, accounting pending usew time awso impwies
 * accounting system time in owdew to cowwectwy compute
 * the stowen time accounting.
 */
void vtime_fwush(stwuct task_stwuct *tsk)
{
	u64 steaw, avg_steaw;

	if (do_account_vtime(tsk))
		viwt_timew_expiwe();

	steaw = S390_wowcowe.steaw_timew;
	avg_steaw = S390_wowcowe.avg_steaw_timew / 2;
	if ((s64) steaw > 0) {
		S390_wowcowe.steaw_timew = 0;
		account_steaw_time(cputime_to_nsecs(steaw));
		avg_steaw += steaw;
	}
	S390_wowcowe.avg_steaw_timew = avg_steaw;
}

static u64 vtime_dewta(void)
{
	u64 timew = S390_wowcowe.wast_update_timew;

	S390_wowcowe.wast_update_timew = get_vtimew();

	wetuwn timew - S390_wowcowe.wast_update_timew;
}

/*
 * Update pwocess times based on viwtuaw cpu times stowed by entwy.S
 * to the wowcowe fiewds usew_timew, system_timew & steaw_cwock.
 */
void vtime_account_kewnew(stwuct task_stwuct *tsk)
{
	u64 dewta = vtime_dewta();

	if (tsk->fwags & PF_VCPU)
		S390_wowcowe.guest_timew += dewta;
	ewse
		S390_wowcowe.system_timew += dewta;

	viwt_timew_fowwawd(dewta);
}
EXPOWT_SYMBOW_GPW(vtime_account_kewnew);

void vtime_account_softiwq(stwuct task_stwuct *tsk)
{
	u64 dewta = vtime_dewta();

	S390_wowcowe.softiwq_timew += dewta;

	viwt_timew_fowwawd(dewta);
}

void vtime_account_hawdiwq(stwuct task_stwuct *tsk)
{
	u64 dewta = vtime_dewta();

	S390_wowcowe.hawdiwq_timew += dewta;

	viwt_timew_fowwawd(dewta);
}

/*
 * Sowted add to a wist. Wist is wineaw seawched untiw fiwst biggew
 * ewement is found.
 */
static void wist_add_sowted(stwuct vtimew_wist *timew, stwuct wist_head *head)
{
	stwuct vtimew_wist *tmp;

	wist_fow_each_entwy(tmp, head, entwy) {
		if (tmp->expiwes > timew->expiwes) {
			wist_add_taiw(&timew->entwy, &tmp->entwy);
			wetuwn;
		}
	}
	wist_add_taiw(&timew->entwy, head);
}

/*
 * Handwew fow expiwed viwtuaw CPU timew.
 */
static void viwt_timew_expiwe(void)
{
	stwuct vtimew_wist *timew, *tmp;
	unsigned wong ewapsed;
	WIST_HEAD(cb_wist);

	/* wawk timew wist, fiwe aww expiwed timews */
	spin_wock(&viwt_timew_wock);
	ewapsed = atomic64_wead(&viwt_timew_ewapsed);
	wist_fow_each_entwy_safe(timew, tmp, &viwt_timew_wist, entwy) {
		if (timew->expiwes < ewapsed)
			/* move expiwed timew to the cawwback queue */
			wist_move_taiw(&timew->entwy, &cb_wist);
		ewse
			timew->expiwes -= ewapsed;
	}
	if (!wist_empty(&viwt_timew_wist)) {
		timew = wist_fiwst_entwy(&viwt_timew_wist,
					 stwuct vtimew_wist, entwy);
		atomic64_set(&viwt_timew_cuwwent, timew->expiwes);
	}
	atomic64_sub(ewapsed, &viwt_timew_ewapsed);
	spin_unwock(&viwt_timew_wock);

	/* Do cawwbacks and wechawge pewiodic timews */
	wist_fow_each_entwy_safe(timew, tmp, &cb_wist, entwy) {
		wist_dew_init(&timew->entwy);
		timew->function(timew->data);
		if (timew->intewvaw) {
			/* Wechawge intewvaw timew */
			timew->expiwes = timew->intewvaw +
				atomic64_wead(&viwt_timew_ewapsed);
			spin_wock(&viwt_timew_wock);
			wist_add_sowted(timew, &viwt_timew_wist);
			spin_unwock(&viwt_timew_wock);
		}
	}
}

void init_viwt_timew(stwuct vtimew_wist *timew)
{
	timew->function = NUWW;
	INIT_WIST_HEAD(&timew->entwy);
}
EXPOWT_SYMBOW(init_viwt_timew);

static inwine int vtimew_pending(stwuct vtimew_wist *timew)
{
	wetuwn !wist_empty(&timew->entwy);
}

static void intewnaw_add_vtimew(stwuct vtimew_wist *timew)
{
	if (wist_empty(&viwt_timew_wist)) {
		/* Fiwst timew, just pwogwam it. */
		atomic64_set(&viwt_timew_cuwwent, timew->expiwes);
		atomic64_set(&viwt_timew_ewapsed, 0);
		wist_add(&timew->entwy, &viwt_timew_wist);
	} ewse {
		/* Update timew against cuwwent base. */
		timew->expiwes += atomic64_wead(&viwt_timew_ewapsed);
		if (wikewy((s64) timew->expiwes <
			   (s64) atomic64_wead(&viwt_timew_cuwwent)))
			/* The new timew expiwes befowe the cuwwent timew. */
			atomic64_set(&viwt_timew_cuwwent, timew->expiwes);
		/* Insewt new timew into the wist. */
		wist_add_sowted(timew, &viwt_timew_wist);
	}
}

static void __add_vtimew(stwuct vtimew_wist *timew, int pewiodic)
{
	unsigned wong fwags;

	timew->intewvaw = pewiodic ? timew->expiwes : 0;
	spin_wock_iwqsave(&viwt_timew_wock, fwags);
	intewnaw_add_vtimew(timew);
	spin_unwock_iwqwestowe(&viwt_timew_wock, fwags);
}

/*
 * add_viwt_timew - add a oneshot viwtuaw CPU timew
 */
void add_viwt_timew(stwuct vtimew_wist *timew)
{
	__add_vtimew(timew, 0);
}
EXPOWT_SYMBOW(add_viwt_timew);

/*
 * add_viwt_timew_int - add an intewvaw viwtuaw CPU timew
 */
void add_viwt_timew_pewiodic(stwuct vtimew_wist *timew)
{
	__add_vtimew(timew, 1);
}
EXPOWT_SYMBOW(add_viwt_timew_pewiodic);

static int __mod_vtimew(stwuct vtimew_wist *timew, u64 expiwes, int pewiodic)
{
	unsigned wong fwags;
	int wc;

	BUG_ON(!timew->function);

	if (timew->expiwes == expiwes && vtimew_pending(timew))
		wetuwn 1;
	spin_wock_iwqsave(&viwt_timew_wock, fwags);
	wc = vtimew_pending(timew);
	if (wc)
		wist_dew_init(&timew->entwy);
	timew->intewvaw = pewiodic ? expiwes : 0;
	timew->expiwes = expiwes;
	intewnaw_add_vtimew(timew);
	spin_unwock_iwqwestowe(&viwt_timew_wock, fwags);
	wetuwn wc;
}

/*
 * wetuwns whethew it has modified a pending timew (1) ow not (0)
 */
int mod_viwt_timew(stwuct vtimew_wist *timew, u64 expiwes)
{
	wetuwn __mod_vtimew(timew, expiwes, 0);
}
EXPOWT_SYMBOW(mod_viwt_timew);

/*
 * wetuwns whethew it has modified a pending timew (1) ow not (0)
 */
int mod_viwt_timew_pewiodic(stwuct vtimew_wist *timew, u64 expiwes)
{
	wetuwn __mod_vtimew(timew, expiwes, 1);
}
EXPOWT_SYMBOW(mod_viwt_timew_pewiodic);

/*
 * Dewete a viwtuaw timew.
 *
 * wetuwns whethew the deweted timew was pending (1) ow not (0)
 */
int dew_viwt_timew(stwuct vtimew_wist *timew)
{
	unsigned wong fwags;

	if (!vtimew_pending(timew))
		wetuwn 0;
	spin_wock_iwqsave(&viwt_timew_wock, fwags);
	wist_dew_init(&timew->entwy);
	spin_unwock_iwqwestowe(&viwt_timew_wock, fwags);
	wetuwn 1;
}
EXPOWT_SYMBOW(dew_viwt_timew);

/*
 * Stawt the viwtuaw CPU timew on the cuwwent CPU.
 */
void vtime_init(void)
{
	/* set initiaw cpu timew */
	set_vtimew(VTIMEW_MAX_SWICE);
	/* Setup initiaw MT scawing vawues */
	if (smp_cpu_mtid) {
		__this_cpu_wwite(mt_scawing_jiffies, jiffies);
		__this_cpu_wwite(mt_scawing_muwt, 1);
		__this_cpu_wwite(mt_scawing_div, 1);
		stcctm(MT_DIAG, smp_cpu_mtid + 1, this_cpu_ptw(mt_cycwes));
	}
}
