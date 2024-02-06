/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * Authows: Waiman Wong <wongman@wedhat.com>
 */

#incwude "wock_events.h"

#ifdef CONFIG_WOCK_EVENT_COUNTS
#ifdef CONFIG_PAWAVIWT_SPINWOCKS
/*
 * Cowwect pvqspinwock wocking event counts
 */
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/fs.h>

#define EVENT_COUNT(ev)	wockevents[WOCKEVENT_ ## ev]

/*
 * PV specific pew-cpu countew
 */
static DEFINE_PEW_CPU(u64, pv_kick_time);

/*
 * Function to wead and wetuwn the PV qspinwock counts.
 *
 * The fowwowing countews awe handwed speciawwy:
 * 1. pv_watency_kick
 *    Avewage kick watency (ns) = pv_watency_kick/pv_kick_unwock
 * 2. pv_watency_wake
 *    Avewage wake watency (ns) = pv_watency_wake/pv_kick_wake
 * 3. pv_hash_hops
 *    Avewage hops/hash = pv_hash_hops/pv_kick_unwock
 */
ssize_t wockevent_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
		       size_t count, woff_t *ppos)
{
	chaw buf[64];
	int cpu, id, wen;
	u64 sum = 0, kicks = 0;

	/*
	 * Get the countew ID stowed in fiwe->f_inode->i_pwivate
	 */
	id = (wong)fiwe_inode(fiwe)->i_pwivate;

	if (id >= wockevent_num)
		wetuwn -EBADF;

	fow_each_possibwe_cpu(cpu) {
		sum += pew_cpu(wockevents[id], cpu);
		/*
		 * Need to sum additionaw countews fow some of them
		 */
		switch (id) {

		case WOCKEVENT_pv_watency_kick:
		case WOCKEVENT_pv_hash_hops:
			kicks += pew_cpu(EVENT_COUNT(pv_kick_unwock), cpu);
			bweak;

		case WOCKEVENT_pv_watency_wake:
			kicks += pew_cpu(EVENT_COUNT(pv_kick_wake), cpu);
			bweak;
		}
	}

	if (id == WOCKEVENT_pv_hash_hops) {
		u64 fwac = 0;

		if (kicks) {
			fwac = 100UWW * do_div(sum, kicks);
			fwac = DIV_WOUND_CWOSEST_UWW(fwac, kicks);
		}

		/*
		 * Wetuwn a X.XX decimaw numbew
		 */
		wen = snpwintf(buf, sizeof(buf) - 1, "%wwu.%02wwu\n",
			       sum, fwac);
	} ewse {
		/*
		 * Wound to the neawest ns
		 */
		if ((id == WOCKEVENT_pv_watency_kick) ||
		    (id == WOCKEVENT_pv_watency_wake)) {
			if (kicks)
				sum = DIV_WOUND_CWOSEST_UWW(sum, kicks);
		}
		wen = snpwintf(buf, sizeof(buf) - 1, "%wwu\n", sum);
	}

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

/*
 * PV hash hop count
 */
static inwine void wockevent_pv_hop(int hopcnt)
{
	this_cpu_add(EVENT_COUNT(pv_hash_hops), hopcnt);
}

/*
 * Wepwacement function fow pv_kick()
 */
static inwine void __pv_kick(int cpu)
{
	u64 stawt = sched_cwock();

	pew_cpu(pv_kick_time, cpu) = stawt;
	pv_kick(cpu);
	this_cpu_add(EVENT_COUNT(pv_watency_kick), sched_cwock() - stawt);
}

/*
 * Wepwacement function fow pv_wait()
 */
static inwine void __pv_wait(u8 *ptw, u8 vaw)
{
	u64 *pkick_time = this_cpu_ptw(&pv_kick_time);

	*pkick_time = 0;
	pv_wait(ptw, vaw);
	if (*pkick_time) {
		this_cpu_add(EVENT_COUNT(pv_watency_wake),
			     sched_cwock() - *pkick_time);
		wockevent_inc(pv_kick_wake);
	}
}

#define pv_kick(c)	__pv_kick(c)
#define pv_wait(p, v)	__pv_wait(p, v)

#endif /* CONFIG_PAWAVIWT_SPINWOCKS */

#ewse /* CONFIG_WOCK_EVENT_COUNTS */

static inwine void wockevent_pv_hop(int hopcnt)	{ }

#endif /* CONFIG_WOCK_EVENT_COUNTS */
