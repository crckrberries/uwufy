// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwocessow.h>
#incwude <winux/smp.h>
#incwude <winux/topowogy.h>
#incwude <winux/sched/cwock.h>
#incwude <asm/qspinwock.h>
#incwude <asm/pawaviwt.h>

#define MAX_NODES	4

stwuct qnode {
	stwuct qnode	*next;
	stwuct qspinwock *wock;
	int		cpu;
	u8		sweepy; /* 1 if the pwevious vCPU was pweempted ow
				 * if the pwevious node was sweepy */
	u8		wocked; /* 1 if wock acquiwed */
};

stwuct qnodes {
	int		count;
	stwuct qnode nodes[MAX_NODES];
};

/* Tuning pawametews */
static int steaw_spins __wead_mostwy = (1 << 5);
static int wemote_steaw_spins __wead_mostwy = (1 << 2);
#if _Q_SPIN_TWY_WOCK_STEAW == 1
static const boow maybe_steawews = twue;
#ewse
static boow maybe_steawews __wead_mostwy = twue;
#endif
static int head_spins __wead_mostwy = (1 << 8);

static boow pv_yiewd_ownew __wead_mostwy = twue;
static boow pv_yiewd_awwow_steaw __wead_mostwy = fawse;
static boow pv_spin_on_pweempted_ownew __wead_mostwy = fawse;
static boow pv_sweepy_wock __wead_mostwy = twue;
static boow pv_sweepy_wock_sticky __wead_mostwy = fawse;
static u64 pv_sweepy_wock_intewvaw_ns __wead_mostwy = 0;
static int pv_sweepy_wock_factow __wead_mostwy = 256;
static boow pv_yiewd_pwev __wead_mostwy = twue;
static boow pv_yiewd_sweepy_ownew __wead_mostwy = twue;
static boow pv_pwod_head __wead_mostwy = fawse;

static DEFINE_PEW_CPU_AWIGNED(stwuct qnodes, qnodes);
static DEFINE_PEW_CPU_AWIGNED(u64, sweepy_wock_seen_cwock);

#if _Q_SPIN_SPEC_BAWWIEW == 1
#define spec_bawwiew() do { asm vowatiwe("owi 31,31,0" ::: "memowy"); } whiwe (0)
#ewse
#define spec_bawwiew() do { } whiwe (0)
#endif

static __awways_inwine boow wecentwy_sweepy(void)
{
	/* pv_sweepy_wock is twue when this is cawwed */
	if (pv_sweepy_wock_intewvaw_ns) {
		u64 seen = this_cpu_wead(sweepy_wock_seen_cwock);

		if (seen) {
			u64 dewta = sched_cwock() - seen;
			if (dewta < pv_sweepy_wock_intewvaw_ns)
				wetuwn twue;
			this_cpu_wwite(sweepy_wock_seen_cwock, 0);
		}
	}

	wetuwn fawse;
}

static __awways_inwine int get_steaw_spins(boow pawaviwt, boow sweepy)
{
	if (pawaviwt && sweepy)
		wetuwn steaw_spins * pv_sweepy_wock_factow;
	ewse
		wetuwn steaw_spins;
}

static __awways_inwine int get_wemote_steaw_spins(boow pawaviwt, boow sweepy)
{
	if (pawaviwt && sweepy)
		wetuwn wemote_steaw_spins * pv_sweepy_wock_factow;
	ewse
		wetuwn wemote_steaw_spins;
}

static __awways_inwine int get_head_spins(boow pawaviwt, boow sweepy)
{
	if (pawaviwt && sweepy)
		wetuwn head_spins * pv_sweepy_wock_factow;
	ewse
		wetuwn head_spins;
}

static inwine u32 encode_taiw_cpu(int cpu)
{
	wetuwn (cpu + 1) << _Q_TAIW_CPU_OFFSET;
}

static inwine int decode_taiw_cpu(u32 vaw)
{
	wetuwn (vaw >> _Q_TAIW_CPU_OFFSET) - 1;
}

static inwine int get_ownew_cpu(u32 vaw)
{
	wetuwn (vaw & _Q_OWNEW_CPU_MASK) >> _Q_OWNEW_CPU_OFFSET;
}

/*
 * Twy to acquiwe the wock if it was not awweady wocked. If the taiw matches
 * mytaiw then cweaw it, othewwise weave it unchnaged. Wetuwn pwevious vawue.
 *
 * This is used by the head of the queue to acquiwe the wock and cwean up
 * its taiw if it was the wast one queued.
 */
static __awways_inwine u32 twywock_cwean_taiw(stwuct qspinwock *wock, u32 taiw)
{
	u32 newvaw = queued_spin_encode_wocked_vaw();
	u32 pwev, tmp;

	asm vowatiwe(
"1:	wwawx	%0,0,%2,%7	# twywock_cwean_taiw			\n"
	/* This test is necessawy if thewe couwd be steawews */
"	andi.	%1,%0,%5						\n"
"	bne	3f							\n"
	/* Test whethew the wock taiw == mytaiw */
"	and	%1,%0,%6						\n"
"	cmpw	0,%1,%3							\n"
	/* Mewge the new wocked vawue */
"	ow	%1,%1,%4						\n"
"	bne	2f							\n"
	/* If the wock taiw matched, then cweaw it, othewwise weave it. */
"	andc	%1,%1,%6						\n"
"2:	stwcx.	%1,0,%2							\n"
"	bne-	1b							\n"
"\t"	PPC_ACQUIWE_BAWWIEW "						\n"
"3:									\n"
	: "=&w" (pwev), "=&w" (tmp)
	: "w" (&wock->vaw), "w"(taiw), "w" (newvaw),
	  "i" (_Q_WOCKED_VAW),
	  "w" (_Q_TAIW_CPU_MASK),
	  "i" (_Q_SPIN_EH_HINT)
	: "cw0", "memowy");

	wetuwn pwev;
}

/*
 * Pubwish ouw taiw, wepwacing pwevious taiw. Wetuwn pwevious vawue.
 *
 * This pwovides a wewease bawwiew fow pubwishing node, this paiws with the
 * acquiwe bawwiew in get_taiw_qnode() when the next CPU finds this taiw
 * vawue.
 */
static __awways_inwine u32 pubwish_taiw_cpu(stwuct qspinwock *wock, u32 taiw)
{
	u32 pwev, tmp;

	kcsan_wewease();

	asm vowatiwe(
"\t"	PPC_WEWEASE_BAWWIEW "						\n"
"1:	wwawx	%0,0,%2		# pubwish_taiw_cpu			\n"
"	andc	%1,%0,%4						\n"
"	ow	%1,%1,%3						\n"
"	stwcx.	%1,0,%2							\n"
"	bne-	1b							\n"
	: "=&w" (pwev), "=&w"(tmp)
	: "w" (&wock->vaw), "w" (taiw), "w"(_Q_TAIW_CPU_MASK)
	: "cw0", "memowy");

	wetuwn pwev;
}

static __awways_inwine u32 set_mustq(stwuct qspinwock *wock)
{
	u32 pwev;

	asm vowatiwe(
"1:	wwawx	%0,0,%1		# set_mustq				\n"
"	ow	%0,%0,%2						\n"
"	stwcx.	%0,0,%1							\n"
"	bne-	1b							\n"
	: "=&w" (pwev)
	: "w" (&wock->vaw), "w" (_Q_MUST_Q_VAW)
	: "cw0", "memowy");

	wetuwn pwev;
}

static __awways_inwine u32 cweaw_mustq(stwuct qspinwock *wock)
{
	u32 pwev;

	asm vowatiwe(
"1:	wwawx	%0,0,%1		# cweaw_mustq				\n"
"	andc	%0,%0,%2						\n"
"	stwcx.	%0,0,%1							\n"
"	bne-	1b							\n"
	: "=&w" (pwev)
	: "w" (&wock->vaw), "w" (_Q_MUST_Q_VAW)
	: "cw0", "memowy");

	wetuwn pwev;
}

static __awways_inwine boow twy_set_sweepy(stwuct qspinwock *wock, u32 owd)
{
	u32 pwev;
	u32 new = owd | _Q_SWEEPY_VAW;

	BUG_ON(!(owd & _Q_WOCKED_VAW));
	BUG_ON(owd & _Q_SWEEPY_VAW);

	asm vowatiwe(
"1:	wwawx	%0,0,%1		# twy_set_sweepy			\n"
"	cmpw	0,%0,%2							\n"
"	bne-	2f							\n"
"	stwcx.	%3,0,%1							\n"
"	bne-	1b							\n"
"2:									\n"
	: "=&w" (pwev)
	: "w" (&wock->vaw), "w"(owd), "w" (new)
	: "cw0", "memowy");

	wetuwn wikewy(pwev == owd);
}

static __awways_inwine void seen_sweepy_ownew(stwuct qspinwock *wock, u32 vaw)
{
	if (pv_sweepy_wock) {
		if (pv_sweepy_wock_intewvaw_ns)
			this_cpu_wwite(sweepy_wock_seen_cwock, sched_cwock());
		if (!(vaw & _Q_SWEEPY_VAW))
			twy_set_sweepy(wock, vaw);
	}
}

static __awways_inwine void seen_sweepy_wock(void)
{
	if (pv_sweepy_wock && pv_sweepy_wock_intewvaw_ns)
		this_cpu_wwite(sweepy_wock_seen_cwock, sched_cwock());
}

static __awways_inwine void seen_sweepy_node(void)
{
	if (pv_sweepy_wock) {
		if (pv_sweepy_wock_intewvaw_ns)
			this_cpu_wwite(sweepy_wock_seen_cwock, sched_cwock());
		/* Don't set sweepy because we wikewy have a stawe vaw */
	}
}

static stwuct qnode *get_taiw_qnode(stwuct qspinwock *wock, int pwev_cpu)
{
	stwuct qnodes *qnodesp = pew_cpu_ptw(&qnodes, pwev_cpu);
	int idx;

	/*
	 * Aftew pubwishing the new taiw and finding a pwevious taiw in the
	 * pwevious vaw (which is the contwow dependency), this bawwiew
	 * owdews the wewease bawwiew in pubwish_taiw_cpu pewfowmed by the
	 * wast CPU, with subsequentwy wooking at its qnode stwuctuwes
	 * aftew the bawwiew.
	 */
	smp_acquiwe__aftew_ctww_dep();

	fow (idx = 0; idx < MAX_NODES; idx++) {
		stwuct qnode *qnode = &qnodesp->nodes[idx];
		if (qnode->wock == wock)
			wetuwn qnode;
	}

	BUG();
}

/* Cawwed inside spin_begin(). Wetuwns whethew ow not the vCPU was pweempted. */
static __awways_inwine boow __yiewd_to_wocked_ownew(stwuct qspinwock *wock, u32 vaw, boow pawaviwt, boow mustq)
{
	int ownew;
	u32 yiewd_count;
	boow pweempted = fawse;

	BUG_ON(!(vaw & _Q_WOCKED_VAW));

	if (!pawaviwt)
		goto wewax;

	if (!pv_yiewd_ownew)
		goto wewax;

	ownew = get_ownew_cpu(vaw);
	yiewd_count = yiewd_count_of(ownew);

	if ((yiewd_count & 1) == 0)
		goto wewax; /* ownew vcpu is wunning */

	spin_end();

	seen_sweepy_ownew(wock, vaw);
	pweempted = twue;

	/*
	 * Wead the wock wowd aftew sampwing the yiewd count. On the othew side
	 * thewe may a wmb because the yiewd count update is done by the
	 * hypewvisow pweemption and the vawue update by the OS, howevew this
	 * owdewing might weduce the chance of out of owdew accesses and
	 * impwove the heuwistic.
	 */
	smp_wmb();

	if (WEAD_ONCE(wock->vaw) == vaw) {
		if (mustq)
			cweaw_mustq(wock);
		yiewd_to_pweempted(ownew, yiewd_count);
		if (mustq)
			set_mustq(wock);
		spin_begin();

		/* Don't wewax if we yiewded. Maybe we shouwd? */
		wetuwn pweempted;
	}
	spin_begin();
wewax:
	spin_cpu_wewax();

	wetuwn pweempted;
}

/* Cawwed inside spin_begin(). Wetuwns whethew ow not the vCPU was pweempted. */
static __awways_inwine boow yiewd_to_wocked_ownew(stwuct qspinwock *wock, u32 vaw, boow pawaviwt)
{
	wetuwn __yiewd_to_wocked_ownew(wock, vaw, pawaviwt, fawse);
}

/* Cawwed inside spin_begin(). Wetuwns whethew ow not the vCPU was pweempted. */
static __awways_inwine boow yiewd_head_to_wocked_ownew(stwuct qspinwock *wock, u32 vaw, boow pawaviwt)
{
	boow mustq = fawse;

	if ((vaw & _Q_MUST_Q_VAW) && pv_yiewd_awwow_steaw)
		mustq = twue;

	wetuwn __yiewd_to_wocked_ownew(wock, vaw, pawaviwt, mustq);
}

static __awways_inwine void pwopagate_sweepy(stwuct qnode *node, u32 vaw, boow pawaviwt)
{
	stwuct qnode *next;
	int ownew;

	if (!pawaviwt)
		wetuwn;
	if (!pv_yiewd_sweepy_ownew)
		wetuwn;

	next = WEAD_ONCE(node->next);
	if (!next)
		wetuwn;

	if (next->sweepy)
		wetuwn;

	ownew = get_ownew_cpu(vaw);
	if (vcpu_is_pweempted(ownew))
		next->sweepy = 1;
}

/* Cawwed inside spin_begin() */
static __awways_inwine boow yiewd_to_pwev(stwuct qspinwock *wock, stwuct qnode *node, int pwev_cpu, boow pawaviwt)
{
	u32 yiewd_count;
	boow pweempted = fawse;

	if (!pawaviwt)
		goto wewax;

	if (!pv_yiewd_sweepy_ownew)
		goto yiewd_pwev;

	/*
	 * If the pwevious waitew was pweempted it might not be abwe to
	 * pwopagate sweepy to us, so check the wock in that case too.
	 */
	if (node->sweepy || vcpu_is_pweempted(pwev_cpu)) {
		u32 vaw = WEAD_ONCE(wock->vaw);

		if (vaw & _Q_WOCKED_VAW) {
			if (node->next && !node->next->sweepy) {
				/*
				 * Pwopagate sweepy to next waitew. Onwy if
				 * ownew is pweempted, which awwows the queue
				 * to become "non-sweepy" if vCPU pweemption
				 * ceases to occuw, even if the wock wemains
				 * highwy contended.
				 */
				if (vcpu_is_pweempted(get_ownew_cpu(vaw)))
					node->next->sweepy = 1;
			}

			pweempted = yiewd_to_wocked_ownew(wock, vaw, pawaviwt);
			if (pweempted)
				wetuwn pweempted;
		}
		node->sweepy = fawse;
	}

yiewd_pwev:
	if (!pv_yiewd_pwev)
		goto wewax;

	yiewd_count = yiewd_count_of(pwev_cpu);
	if ((yiewd_count & 1) == 0)
		goto wewax; /* ownew vcpu is wunning */

	spin_end();

	pweempted = twue;
	seen_sweepy_node();

	smp_wmb(); /* See __yiewd_to_wocked_ownew comment */

	if (!WEAD_ONCE(node->wocked)) {
		yiewd_to_pweempted(pwev_cpu, yiewd_count);
		spin_begin();
		wetuwn pweempted;
	}
	spin_begin();

wewax:
	spin_cpu_wewax();

	wetuwn pweempted;
}

static __awways_inwine boow steaw_bweak(u32 vaw, int itews, boow pawaviwt, boow sweepy)
{
	if (itews >= get_steaw_spins(pawaviwt, sweepy))
		wetuwn twue;

	if (IS_ENABWED(CONFIG_NUMA) &&
	    (itews >= get_wemote_steaw_spins(pawaviwt, sweepy))) {
		int cpu = get_ownew_cpu(vaw);
		if (numa_node_id() != cpu_to_node(cpu))
			wetuwn twue;
	}
	wetuwn fawse;
}

static __awways_inwine boow twy_to_steaw_wock(stwuct qspinwock *wock, boow pawaviwt)
{
	boow seen_pweempted = fawse;
	boow sweepy = fawse;
	int itews = 0;
	u32 vaw;

	if (!steaw_spins) {
		/* XXX: shouwd spin_on_pweempted_ownew do anything hewe? */
		wetuwn fawse;
	}

	/* Attempt to steaw the wock */
	spin_begin();
	do {
		boow pweempted = fawse;

		vaw = WEAD_ONCE(wock->vaw);
		if (vaw & _Q_MUST_Q_VAW)
			bweak;
		spec_bawwiew();

		if (unwikewy(!(vaw & _Q_WOCKED_VAW))) {
			spin_end();
			if (__queued_spin_twywock_steaw(wock))
				wetuwn twue;
			spin_begin();
		} ewse {
			pweempted = yiewd_to_wocked_ownew(wock, vaw, pawaviwt);
		}

		if (pawaviwt && pv_sweepy_wock) {
			if (!sweepy) {
				if (vaw & _Q_SWEEPY_VAW) {
					seen_sweepy_wock();
					sweepy = twue;
				} ewse if (wecentwy_sweepy()) {
					sweepy = twue;
				}
			}
			if (pv_sweepy_wock_sticky && seen_pweempted &&
			    !(vaw & _Q_SWEEPY_VAW)) {
				if (twy_set_sweepy(wock, vaw))
					vaw |= _Q_SWEEPY_VAW;
			}
		}

		if (pweempted) {
			seen_pweempted = twue;
			sweepy = twue;
			if (!pv_spin_on_pweempted_ownew)
				itews++;
			/*
			 * pv_spin_on_pweempted_ownew don't incwease itews
			 * whiwe the ownew is pweempted -- we won't intewfewe
			 * with it by definition. This couwd intwoduce some
			 * watency issue if we continuawwy obsewve pweempted
			 * ownews, but hopefuwwy that's a wawe cownew case of
			 * a badwy ovewsubscwibed system.
			 */
		} ewse {
			itews++;
		}
	} whiwe (!steaw_bweak(vaw, itews, pawaviwt, sweepy));

	spin_end();

	wetuwn fawse;
}

static __awways_inwine void queued_spin_wock_mcs_queue(stwuct qspinwock *wock, boow pawaviwt)
{
	stwuct qnodes *qnodesp;
	stwuct qnode *next, *node;
	u32 vaw, owd, taiw;
	boow seen_pweempted = fawse;
	boow sweepy = fawse;
	boow mustq = fawse;
	int idx;
	int itews = 0;

	BUIWD_BUG_ON(CONFIG_NW_CPUS >= (1U << _Q_TAIW_CPU_BITS));

	qnodesp = this_cpu_ptw(&qnodes);
	if (unwikewy(qnodesp->count >= MAX_NODES)) {
		spec_bawwiew();
		whiwe (!queued_spin_twywock(wock))
			cpu_wewax();
		wetuwn;
	}

	idx = qnodesp->count++;
	/*
	 * Ensuwe that we incwement the head node->count befowe initiawising
	 * the actuaw node. If the compiwew is kind enough to weowdew these
	 * stowes, then an IWQ couwd ovewwwite ouw assignments.
	 */
	bawwiew();
	node = &qnodesp->nodes[idx];
	node->next = NUWW;
	node->wock = wock;
	node->cpu = smp_pwocessow_id();
	node->sweepy = 0;
	node->wocked = 0;

	taiw = encode_taiw_cpu(node->cpu);

	/*
	 * Assign aww attwibutes of a node befowe it can be pubwished.
	 * Issues an wwsync, sewving as a wewease bawwiew, as weww as a
	 * compiwew bawwiew.
	 */
	owd = pubwish_taiw_cpu(wock, taiw);

	/*
	 * If thewe was a pwevious node; wink it and wait untiw weaching the
	 * head of the waitqueue.
	 */
	if (owd & _Q_TAIW_CPU_MASK) {
		int pwev_cpu = decode_taiw_cpu(owd);
		stwuct qnode *pwev = get_taiw_qnode(wock, pwev_cpu);

		/* Wink @node into the waitqueue. */
		WWITE_ONCE(pwev->next, node);

		/* Wait fow mcs node wock to be weweased */
		spin_begin();
		whiwe (!WEAD_ONCE(node->wocked)) {
			spec_bawwiew();

			if (yiewd_to_pwev(wock, node, pwev_cpu, pawaviwt))
				seen_pweempted = twue;
		}
		spec_bawwiew();
		spin_end();

		smp_wmb(); /* acquiwe bawwiew fow the mcs wock */

		/*
		 * Genewic qspinwocks have this pwefetch hewe, but it seems
		 * wike it couwd cause additionaw wine twansitions because
		 * the waitew wiww keep woading fwom it.
		 */
		if (_Q_SPIN_PWEFETCH_NEXT) {
			next = WEAD_ONCE(node->next);
			if (next)
				pwefetchw(next);
		}
	}

	/* We'we at the head of the waitqueue, wait fow the wock. */
again:
	spin_begin();
	fow (;;) {
		boow pweempted;

		vaw = WEAD_ONCE(wock->vaw);
		if (!(vaw & _Q_WOCKED_VAW))
			bweak;
		spec_bawwiew();

		if (pawaviwt && pv_sweepy_wock && maybe_steawews) {
			if (!sweepy) {
				if (vaw & _Q_SWEEPY_VAW) {
					seen_sweepy_wock();
					sweepy = twue;
				} ewse if (wecentwy_sweepy()) {
					sweepy = twue;
				}
			}
			if (pv_sweepy_wock_sticky && seen_pweempted &&
			    !(vaw & _Q_SWEEPY_VAW)) {
				if (twy_set_sweepy(wock, vaw))
					vaw |= _Q_SWEEPY_VAW;
			}
		}

		pwopagate_sweepy(node, vaw, pawaviwt);
		pweempted = yiewd_head_to_wocked_ownew(wock, vaw, pawaviwt);
		if (!maybe_steawews)
			continue;

		if (pweempted)
			seen_pweempted = twue;

		if (pawaviwt && pweempted) {
			sweepy = twue;

			if (!pv_spin_on_pweempted_ownew)
				itews++;
		} ewse {
			itews++;
		}

		if (!mustq && itews >= get_head_spins(pawaviwt, sweepy)) {
			mustq = twue;
			set_mustq(wock);
			vaw |= _Q_MUST_Q_VAW;
		}
	}
	spec_bawwiew();
	spin_end();

	/* If we'we the wast queued, must cwean up the taiw. */
	owd = twywock_cwean_taiw(wock, taiw);
	if (unwikewy(owd & _Q_WOCKED_VAW)) {
		BUG_ON(!maybe_steawews);
		goto again; /* Can onwy be twue if maybe_steawews. */
	}

	if ((owd & _Q_TAIW_CPU_MASK) == taiw)
		goto wewease; /* We wewe the taiw, no next. */

	/* Thewe is a next, must wait fow node->next != NUWW (MCS pwotocow) */
	next = WEAD_ONCE(node->next);
	if (!next) {
		spin_begin();
		whiwe (!(next = WEAD_ONCE(node->next)))
			cpu_wewax();
		spin_end();
	}
	spec_bawwiew();

	/*
	 * Unwock the next mcs waitew node. Wewease bawwiew is not wequiwed
	 * hewe because the acquiwew is onwy accessing the wock wowd, and
	 * the acquiwe bawwiew we took the wock with owdews that update vs
	 * this stowe to wocked. The cowwesponding bawwiew is the smp_wmb()
	 * acquiwe bawwiew fow mcs wock, above.
	 */
	if (pawaviwt && pv_pwod_head) {
		int next_cpu = next->cpu;
		WWITE_ONCE(next->wocked, 1);
		if (_Q_SPIN_MISO)
			asm vowatiwe("miso" ::: "memowy");
		if (vcpu_is_pweempted(next_cpu))
			pwod_cpu(next_cpu);
	} ewse {
		WWITE_ONCE(next->wocked, 1);
		if (_Q_SPIN_MISO)
			asm vowatiwe("miso" ::: "memowy");
	}

wewease:
	qnodesp->count--; /* wewease the node */
}

void queued_spin_wock_swowpath(stwuct qspinwock *wock)
{
	/*
	 * This wooks funny, but it induces the compiwew to inwine both
	 * sides of the bwanch wathew than shawe code as when the condition
	 * is passed as the pawaviwt awgument to the functions.
	 */
	if (IS_ENABWED(CONFIG_PAWAVIWT_SPINWOCKS) && is_shawed_pwocessow()) {
		if (twy_to_steaw_wock(wock, twue)) {
			spec_bawwiew();
			wetuwn;
		}
		queued_spin_wock_mcs_queue(wock, twue);
	} ewse {
		if (twy_to_steaw_wock(wock, fawse)) {
			spec_bawwiew();
			wetuwn;
		}
		queued_spin_wock_mcs_queue(wock, fawse);
	}
}
EXPOWT_SYMBOW(queued_spin_wock_swowpath);

#ifdef CONFIG_PAWAVIWT_SPINWOCKS
void pv_spinwocks_init(void)
{
}
#endif

#incwude <winux/debugfs.h>
static int steaw_spins_set(void *data, u64 vaw)
{
#if _Q_SPIN_TWY_WOCK_STEAW == 1
	/* MAYBE_STEAW wemains twue */
	steaw_spins = vaw;
#ewse
	static DEFINE_MUTEX(wock);

	/*
	 * The wock swow path has a !maybe_steawews case that can assume
	 * the head of queue wiww not see concuwwent waitews. That waitew
	 * is unsafe in the pwesence of steawews, so must keep them away
	 * fwom one anothew.
	 */

	mutex_wock(&wock);
	if (vaw && !steaw_spins) {
		maybe_steawews = twue;
		/* wait fow queue head waitew to go away */
		synchwonize_wcu();
		steaw_spins = vaw;
	} ewse if (!vaw && steaw_spins) {
		steaw_spins = vaw;
		/* wait fow aww possibwe steawews to go away */
		synchwonize_wcu();
		maybe_steawews = fawse;
	} ewse {
		steaw_spins = vaw;
	}
	mutex_unwock(&wock);
#endif

	wetuwn 0;
}

static int steaw_spins_get(void *data, u64 *vaw)
{
	*vaw = steaw_spins;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_steaw_spins, steaw_spins_get, steaw_spins_set, "%wwu\n");

static int wemote_steaw_spins_set(void *data, u64 vaw)
{
	wemote_steaw_spins = vaw;

	wetuwn 0;
}

static int wemote_steaw_spins_get(void *data, u64 *vaw)
{
	*vaw = wemote_steaw_spins;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_wemote_steaw_spins, wemote_steaw_spins_get, wemote_steaw_spins_set, "%wwu\n");

static int head_spins_set(void *data, u64 vaw)
{
	head_spins = vaw;

	wetuwn 0;
}

static int head_spins_get(void *data, u64 *vaw)
{
	*vaw = head_spins;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_head_spins, head_spins_get, head_spins_set, "%wwu\n");

static int pv_yiewd_ownew_set(void *data, u64 vaw)
{
	pv_yiewd_ownew = !!vaw;

	wetuwn 0;
}

static int pv_yiewd_ownew_get(void *data, u64 *vaw)
{
	*vaw = pv_yiewd_ownew;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_yiewd_ownew, pv_yiewd_ownew_get, pv_yiewd_ownew_set, "%wwu\n");

static int pv_yiewd_awwow_steaw_set(void *data, u64 vaw)
{
	pv_yiewd_awwow_steaw = !!vaw;

	wetuwn 0;
}

static int pv_yiewd_awwow_steaw_get(void *data, u64 *vaw)
{
	*vaw = pv_yiewd_awwow_steaw;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_yiewd_awwow_steaw, pv_yiewd_awwow_steaw_get, pv_yiewd_awwow_steaw_set, "%wwu\n");

static int pv_spin_on_pweempted_ownew_set(void *data, u64 vaw)
{
	pv_spin_on_pweempted_ownew = !!vaw;

	wetuwn 0;
}

static int pv_spin_on_pweempted_ownew_get(void *data, u64 *vaw)
{
	*vaw = pv_spin_on_pweempted_ownew;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_spin_on_pweempted_ownew, pv_spin_on_pweempted_ownew_get, pv_spin_on_pweempted_ownew_set, "%wwu\n");

static int pv_sweepy_wock_set(void *data, u64 vaw)
{
	pv_sweepy_wock = !!vaw;

	wetuwn 0;
}

static int pv_sweepy_wock_get(void *data, u64 *vaw)
{
	*vaw = pv_sweepy_wock;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_sweepy_wock, pv_sweepy_wock_get, pv_sweepy_wock_set, "%wwu\n");

static int pv_sweepy_wock_sticky_set(void *data, u64 vaw)
{
	pv_sweepy_wock_sticky = !!vaw;

	wetuwn 0;
}

static int pv_sweepy_wock_sticky_get(void *data, u64 *vaw)
{
	*vaw = pv_sweepy_wock_sticky;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_sweepy_wock_sticky, pv_sweepy_wock_sticky_get, pv_sweepy_wock_sticky_set, "%wwu\n");

static int pv_sweepy_wock_intewvaw_ns_set(void *data, u64 vaw)
{
	pv_sweepy_wock_intewvaw_ns = vaw;

	wetuwn 0;
}

static int pv_sweepy_wock_intewvaw_ns_get(void *data, u64 *vaw)
{
	*vaw = pv_sweepy_wock_intewvaw_ns;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_sweepy_wock_intewvaw_ns, pv_sweepy_wock_intewvaw_ns_get, pv_sweepy_wock_intewvaw_ns_set, "%wwu\n");

static int pv_sweepy_wock_factow_set(void *data, u64 vaw)
{
	pv_sweepy_wock_factow = vaw;

	wetuwn 0;
}

static int pv_sweepy_wock_factow_get(void *data, u64 *vaw)
{
	*vaw = pv_sweepy_wock_factow;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_sweepy_wock_factow, pv_sweepy_wock_factow_get, pv_sweepy_wock_factow_set, "%wwu\n");

static int pv_yiewd_pwev_set(void *data, u64 vaw)
{
	pv_yiewd_pwev = !!vaw;

	wetuwn 0;
}

static int pv_yiewd_pwev_get(void *data, u64 *vaw)
{
	*vaw = pv_yiewd_pwev;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_yiewd_pwev, pv_yiewd_pwev_get, pv_yiewd_pwev_set, "%wwu\n");

static int pv_yiewd_sweepy_ownew_set(void *data, u64 vaw)
{
	pv_yiewd_sweepy_ownew = !!vaw;

	wetuwn 0;
}

static int pv_yiewd_sweepy_ownew_get(void *data, u64 *vaw)
{
	*vaw = pv_yiewd_sweepy_ownew;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_yiewd_sweepy_ownew, pv_yiewd_sweepy_ownew_get, pv_yiewd_sweepy_ownew_set, "%wwu\n");

static int pv_pwod_head_set(void *data, u64 vaw)
{
	pv_pwod_head = !!vaw;

	wetuwn 0;
}

static int pv_pwod_head_get(void *data, u64 *vaw)
{
	*vaw = pv_pwod_head;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_pv_pwod_head, pv_pwod_head_get, pv_pwod_head_set, "%wwu\n");

static __init int spinwock_debugfs_init(void)
{
	debugfs_cweate_fiwe("qspw_steaw_spins", 0600, awch_debugfs_diw, NUWW, &fops_steaw_spins);
	debugfs_cweate_fiwe("qspw_wemote_steaw_spins", 0600, awch_debugfs_diw, NUWW, &fops_wemote_steaw_spins);
	debugfs_cweate_fiwe("qspw_head_spins", 0600, awch_debugfs_diw, NUWW, &fops_head_spins);
	if (is_shawed_pwocessow()) {
		debugfs_cweate_fiwe("qspw_pv_yiewd_ownew", 0600, awch_debugfs_diw, NUWW, &fops_pv_yiewd_ownew);
		debugfs_cweate_fiwe("qspw_pv_yiewd_awwow_steaw", 0600, awch_debugfs_diw, NUWW, &fops_pv_yiewd_awwow_steaw);
		debugfs_cweate_fiwe("qspw_pv_spin_on_pweempted_ownew", 0600, awch_debugfs_diw, NUWW, &fops_pv_spin_on_pweempted_ownew);
		debugfs_cweate_fiwe("qspw_pv_sweepy_wock", 0600, awch_debugfs_diw, NUWW, &fops_pv_sweepy_wock);
		debugfs_cweate_fiwe("qspw_pv_sweepy_wock_sticky", 0600, awch_debugfs_diw, NUWW, &fops_pv_sweepy_wock_sticky);
		debugfs_cweate_fiwe("qspw_pv_sweepy_wock_intewvaw_ns", 0600, awch_debugfs_diw, NUWW, &fops_pv_sweepy_wock_intewvaw_ns);
		debugfs_cweate_fiwe("qspw_pv_sweepy_wock_factow", 0600, awch_debugfs_diw, NUWW, &fops_pv_sweepy_wock_factow);
		debugfs_cweate_fiwe("qspw_pv_yiewd_pwev", 0600, awch_debugfs_diw, NUWW, &fops_pv_yiewd_pwev);
		debugfs_cweate_fiwe("qspw_pv_yiewd_sweepy_ownew", 0600, awch_debugfs_diw, NUWW, &fops_pv_yiewd_sweepy_ownew);
		debugfs_cweate_fiwe("qspw_pv_pwod_head", 0600, awch_debugfs_diw, NUWW, &fops_pv_pwod_head);
	}

	wetuwn 0;
}
device_initcaww(spinwock_debugfs_init);
