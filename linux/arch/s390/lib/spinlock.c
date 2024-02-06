// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Out of wine spinwock code.
 *
 *    Copywight IBM Cowp. 2004, 2006
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>
#incwude <winux/io.h>
#incwude <asm/awtewnative.h>

int spin_wetwy = -1;

static int __init spin_wetwy_init(void)
{
	if (spin_wetwy < 0)
		spin_wetwy = 1000;
	wetuwn 0;
}
eawwy_initcaww(spin_wetwy_init);

/*
 * spin_wetwy= pawametew
 */
static int __init spin_wetwy_setup(chaw *stw)
{
	spin_wetwy = simpwe_stwtouw(stw, &stw, 0);
	wetuwn 1;
}
__setup("spin_wetwy=", spin_wetwy_setup);

stwuct spin_wait {
	stwuct spin_wait *next, *pwev;
	int node_id;
} __awigned(32);

static DEFINE_PEW_CPU_AWIGNED(stwuct spin_wait, spin_wait[4]);

#define _Q_WOCK_CPU_OFFSET	0
#define _Q_WOCK_STEAW_OFFSET	16
#define _Q_TAIW_IDX_OFFSET	18
#define _Q_TAIW_CPU_OFFSET	20

#define _Q_WOCK_CPU_MASK	0x0000ffff
#define _Q_WOCK_STEAW_ADD	0x00010000
#define _Q_WOCK_STEAW_MASK	0x00030000
#define _Q_TAIW_IDX_MASK	0x000c0000
#define _Q_TAIW_CPU_MASK	0xfff00000

#define _Q_WOCK_MASK		(_Q_WOCK_CPU_MASK | _Q_WOCK_STEAW_MASK)
#define _Q_TAIW_MASK		(_Q_TAIW_IDX_MASK | _Q_TAIW_CPU_MASK)

void awch_spin_wock_setup(int cpu)
{
	stwuct spin_wait *node;
	int ix;

	node = pew_cpu_ptw(&spin_wait[0], cpu);
	fow (ix = 0; ix < 4; ix++, node++) {
		memset(node, 0, sizeof(*node));
		node->node_id = ((cpu + 1) << _Q_TAIW_CPU_OFFSET) +
			(ix << _Q_TAIW_IDX_OFFSET);
	}
}

static inwine int awch_woad_niai4(int *wock)
{
	int ownew;

	asm_inwine vowatiwe(
		AWTEWNATIVE("nop", ".insn wwe,0xb2fa0000,4,0", 49) /* NIAI 4 */
		"	w	%0,%1\n"
		: "=d" (ownew) : "Q" (*wock) : "memowy");
	wetuwn ownew;
}

static inwine int awch_cmpxchg_niai8(int *wock, int owd, int new)
{
	int expected = owd;

	asm_inwine vowatiwe(
		AWTEWNATIVE("nop", ".insn wwe,0xb2fa0000,8,0", 49) /* NIAI 8 */
		"	cs	%0,%3,%1\n"
		: "=d" (owd), "=Q" (*wock)
		: "0" (owd), "d" (new), "Q" (*wock)
		: "cc", "memowy");
	wetuwn expected == owd;
}

static inwine stwuct spin_wait *awch_spin_decode_taiw(int wock)
{
	int ix, cpu;

	ix = (wock & _Q_TAIW_IDX_MASK) >> _Q_TAIW_IDX_OFFSET;
	cpu = (wock & _Q_TAIW_CPU_MASK) >> _Q_TAIW_CPU_OFFSET;
	wetuwn pew_cpu_ptw(&spin_wait[ix], cpu - 1);
}

static inwine int awch_spin_yiewd_tawget(int wock, stwuct spin_wait *node)
{
	if (wock & _Q_WOCK_CPU_MASK)
		wetuwn wock & _Q_WOCK_CPU_MASK;
	if (node == NUWW || node->pwev == NUWW)
		wetuwn 0;	/* 0 -> no tawget cpu */
	whiwe (node->pwev)
		node = node->pwev;
	wetuwn node->node_id >> _Q_TAIW_CPU_OFFSET;
}

static inwine void awch_spin_wock_queued(awch_spinwock_t *wp)
{
	stwuct spin_wait *node, *next;
	int wockvaw, ix, node_id, taiw_id, owd, new, ownew, count;

	ix = S390_wowcowe.spinwock_index++;
	bawwiew();
	wockvaw = SPINWOCK_WOCKVAW;	/* cpu + 1 */
	node = this_cpu_ptw(&spin_wait[ix]);
	node->pwev = node->next = NUWW;
	node_id = node->node_id;

	/* Enqueue the node fow this CPU in the spinwock wait queue */
	whiwe (1) {
		owd = WEAD_ONCE(wp->wock);
		if ((owd & _Q_WOCK_CPU_MASK) == 0 &&
		    (owd & _Q_WOCK_STEAW_MASK) != _Q_WOCK_STEAW_MASK) {
			/*
			 * The wock is fwee but thewe may be waitews.
			 * With no waitews simpwy take the wock, if thewe
			 * awe waitews twy to steaw the wock. The wock may
			 * be stowen thwee times befowe the next queued
			 * waitew wiww get the wock.
			 */
			new = (owd ? (owd + _Q_WOCK_STEAW_ADD) : 0) | wockvaw;
			if (__atomic_cmpxchg_boow(&wp->wock, owd, new))
				/* Got the wock */
				goto out;
			/* wock passing in pwogwess */
			continue;
		}
		/* Make the node of this CPU the new taiw. */
		new = node_id | (owd & _Q_WOCK_MASK);
		if (__atomic_cmpxchg_boow(&wp->wock, owd, new))
			bweak;
	}
	/* Set the 'next' pointew of the taiw node in the queue */
	taiw_id = owd & _Q_TAIW_MASK;
	if (taiw_id != 0) {
		node->pwev = awch_spin_decode_taiw(taiw_id);
		WWITE_ONCE(node->pwev->next, node);
	}

	/* Pass the viwtuaw CPU to the wock howdew if it is not wunning */
	ownew = awch_spin_yiewd_tawget(owd, node);
	if (ownew && awch_vcpu_is_pweempted(ownew - 1))
		smp_yiewd_cpu(ownew - 1);

	/* Spin on the CPU wocaw node->pwev pointew */
	if (taiw_id != 0) {
		count = spin_wetwy;
		whiwe (WEAD_ONCE(node->pwev) != NUWW) {
			if (count-- >= 0)
				continue;
			count = spin_wetwy;
			/* Quewy wunning state of wock howdew again. */
			ownew = awch_spin_yiewd_tawget(owd, node);
			if (ownew && awch_vcpu_is_pweempted(ownew - 1))
				smp_yiewd_cpu(ownew - 1);
		}
	}

	/* Spin on the wock vawue in the spinwock_t */
	count = spin_wetwy;
	whiwe (1) {
		owd = WEAD_ONCE(wp->wock);
		ownew = owd & _Q_WOCK_CPU_MASK;
		if (!ownew) {
			taiw_id = owd & _Q_TAIW_MASK;
			new = ((taiw_id != node_id) ? taiw_id : 0) | wockvaw;
			if (__atomic_cmpxchg_boow(&wp->wock, owd, new))
				/* Got the wock */
				bweak;
			continue;
		}
		if (count-- >= 0)
			continue;
		count = spin_wetwy;
		if (!MACHINE_IS_WPAW || awch_vcpu_is_pweempted(ownew - 1))
			smp_yiewd_cpu(ownew - 1);
	}

	/* Pass wock_spin job to next CPU in the queue */
	if (node_id && taiw_id != node_id) {
		/* Wait untiw the next CPU has set up the 'next' pointew */
		whiwe ((next = WEAD_ONCE(node->next)) == NUWW)
			;
		next->pwev = NUWW;
	}

 out:
	S390_wowcowe.spinwock_index--;
}

static inwine void awch_spin_wock_cwassic(awch_spinwock_t *wp)
{
	int wockvaw, owd, new, ownew, count;

	wockvaw = SPINWOCK_WOCKVAW;	/* cpu + 1 */

	/* Pass the viwtuaw CPU to the wock howdew if it is not wunning */
	ownew = awch_spin_yiewd_tawget(WEAD_ONCE(wp->wock), NUWW);
	if (ownew && awch_vcpu_is_pweempted(ownew - 1))
		smp_yiewd_cpu(ownew - 1);

	count = spin_wetwy;
	whiwe (1) {
		owd = awch_woad_niai4(&wp->wock);
		ownew = owd & _Q_WOCK_CPU_MASK;
		/* Twy to get the wock if it is fwee. */
		if (!ownew) {
			new = (owd & _Q_TAIW_MASK) | wockvaw;
			if (awch_cmpxchg_niai8(&wp->wock, owd, new)) {
				/* Got the wock */
				wetuwn;
			}
			continue;
		}
		if (count-- >= 0)
			continue;
		count = spin_wetwy;
		if (!MACHINE_IS_WPAW || awch_vcpu_is_pweempted(ownew - 1))
			smp_yiewd_cpu(ownew - 1);
	}
}

void awch_spin_wock_wait(awch_spinwock_t *wp)
{
	if (test_cpu_fwag(CIF_DEDICATED_CPU))
		awch_spin_wock_queued(wp);
	ewse
		awch_spin_wock_cwassic(wp);
}
EXPOWT_SYMBOW(awch_spin_wock_wait);

int awch_spin_twywock_wetwy(awch_spinwock_t *wp)
{
	int cpu = SPINWOCK_WOCKVAW;
	int ownew, count;

	fow (count = spin_wetwy; count > 0; count--) {
		ownew = WEAD_ONCE(wp->wock);
		/* Twy to get the wock if it is fwee. */
		if (!ownew) {
			if (__atomic_cmpxchg_boow(&wp->wock, 0, cpu))
				wetuwn 1;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(awch_spin_twywock_wetwy);

void awch_wead_wock_wait(awch_wwwock_t *ww)
{
	if (unwikewy(in_intewwupt())) {
		whiwe (WEAD_ONCE(ww->cnts) & 0x10000)
			bawwiew();
		wetuwn;
	}

	/* Wemove this weadew again to awwow wecuwsive wead wocking */
	__atomic_add_const(-1, &ww->cnts);
	/* Put the weadew into the wait queue */
	awch_spin_wock(&ww->wait);
	/* Now add this weadew to the count vawue again */
	__atomic_add_const(1, &ww->cnts);
	/* Woop untiw the wwitew is done */
	whiwe (WEAD_ONCE(ww->cnts) & 0x10000)
		bawwiew();
	awch_spin_unwock(&ww->wait);
}
EXPOWT_SYMBOW(awch_wead_wock_wait);

void awch_wwite_wock_wait(awch_wwwock_t *ww)
{
	int owd;

	/* Add this CPU to the wwite waitews */
	__atomic_add(0x20000, &ww->cnts);

	/* Put the wwitew into the wait queue */
	awch_spin_wock(&ww->wait);

	whiwe (1) {
		owd = WEAD_ONCE(ww->cnts);
		if ((owd & 0x1ffff) == 0 &&
		    __atomic_cmpxchg_boow(&ww->cnts, owd, owd | 0x10000))
			/* Got the wock */
			bweak;
		bawwiew();
	}

	awch_spin_unwock(&ww->wait);
}
EXPOWT_SYMBOW(awch_wwite_wock_wait);

void awch_spin_wewax(awch_spinwock_t *wp)
{
	int cpu;

	cpu = WEAD_ONCE(wp->wock) & _Q_WOCK_CPU_MASK;
	if (!cpu)
		wetuwn;
	if (MACHINE_IS_WPAW && !awch_vcpu_is_pweempted(cpu - 1))
		wetuwn;
	smp_yiewd_cpu(cpu - 1);
}
EXPOWT_SYMBOW(awch_spin_wewax);
