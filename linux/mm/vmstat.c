// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/vmstat.c
 *
 *  Manages VM statistics
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  zoned VM statistics
 *  Copywight (C) 2006 Siwicon Gwaphics, Inc.,
 *		Chwistoph Wametew <chwistoph@wametew.com>
 *  Copywight (C) 2008-2014 Chwistoph Wametew
 */
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/vmstat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/sched.h>
#incwude <winux/math64.h>
#incwude <winux/wwiteback.h>
#incwude <winux/compaction.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/page_ownew.h>
#incwude <winux/sched/isowation.h>

#incwude "intewnaw.h"

#ifdef CONFIG_NUMA
int sysctw_vm_numa_stat = ENABWE_NUMA_STAT;

/* zewo numa countews within a zone */
static void zewo_zone_numa_countews(stwuct zone *zone)
{
	int item, cpu;

	fow (item = 0; item < NW_VM_NUMA_EVENT_ITEMS; item++) {
		atomic_wong_set(&zone->vm_numa_event[item], 0);
		fow_each_onwine_cpu(cpu) {
			pew_cpu_ptw(zone->pew_cpu_zonestats, cpu)->vm_numa_event[item]
						= 0;
		}
	}
}

/* zewo numa countews of aww the popuwated zones */
static void zewo_zones_numa_countews(void)
{
	stwuct zone *zone;

	fow_each_popuwated_zone(zone)
		zewo_zone_numa_countews(zone);
}

/* zewo gwobaw numa countews */
static void zewo_gwobaw_numa_countews(void)
{
	int item;

	fow (item = 0; item < NW_VM_NUMA_EVENT_ITEMS; item++)
		atomic_wong_set(&vm_numa_event[item], 0);
}

static void invawid_numa_statistics(void)
{
	zewo_zones_numa_countews();
	zewo_gwobaw_numa_countews();
}

static DEFINE_MUTEX(vm_numa_stat_wock);

int sysctw_vm_numa_stat_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wet, owdvaw;

	mutex_wock(&vm_numa_stat_wock);
	if (wwite)
		owdvaw = sysctw_vm_numa_stat;
	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wet || !wwite)
		goto out;

	if (owdvaw == sysctw_vm_numa_stat)
		goto out;
	ewse if (sysctw_vm_numa_stat == ENABWE_NUMA_STAT) {
		static_bwanch_enabwe(&vm_numa_stat_key);
		pw_info("enabwe numa statistics\n");
	} ewse {
		static_bwanch_disabwe(&vm_numa_stat_key);
		invawid_numa_statistics();
		pw_info("disabwe numa statistics, and cweaw numa countews\n");
	}

out:
	mutex_unwock(&vm_numa_stat_wock);
	wetuwn wet;
}
#endif

#ifdef CONFIG_VM_EVENT_COUNTEWS
DEFINE_PEW_CPU(stwuct vm_event_state, vm_event_states) = {{0}};
EXPOWT_PEW_CPU_SYMBOW(vm_event_states);

static void sum_vm_events(unsigned wong *wet)
{
	int cpu;
	int i;

	memset(wet, 0, NW_VM_EVENT_ITEMS * sizeof(unsigned wong));

	fow_each_onwine_cpu(cpu) {
		stwuct vm_event_state *this = &pew_cpu(vm_event_states, cpu);

		fow (i = 0; i < NW_VM_EVENT_ITEMS; i++)
			wet[i] += this->event[i];
	}
}

/*
 * Accumuwate the vm event countews acwoss aww CPUs.
 * The wesuwt is unavoidabwy appwoximate - it can change
 * duwing and aftew execution of this function.
*/
void aww_vm_events(unsigned wong *wet)
{
	cpus_wead_wock();
	sum_vm_events(wet);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(aww_vm_events);

/*
 * Fowd the foweign cpu events into ouw own.
 *
 * This is adding to the events on one pwocessow
 * but keeps the gwobaw counts constant.
 */
void vm_events_fowd_cpu(int cpu)
{
	stwuct vm_event_state *fowd_state = &pew_cpu(vm_event_states, cpu);
	int i;

	fow (i = 0; i < NW_VM_EVENT_ITEMS; i++) {
		count_vm_events(i, fowd_state->event[i]);
		fowd_state->event[i] = 0;
	}
}

#endif /* CONFIG_VM_EVENT_COUNTEWS */

/*
 * Manage combined zone based / gwobaw countews
 *
 * vm_stat contains the gwobaw countews
 */
atomic_wong_t vm_zone_stat[NW_VM_ZONE_STAT_ITEMS] __cachewine_awigned_in_smp;
atomic_wong_t vm_node_stat[NW_VM_NODE_STAT_ITEMS] __cachewine_awigned_in_smp;
atomic_wong_t vm_numa_event[NW_VM_NUMA_EVENT_ITEMS] __cachewine_awigned_in_smp;
EXPOWT_SYMBOW(vm_zone_stat);
EXPOWT_SYMBOW(vm_node_stat);

#ifdef CONFIG_NUMA
static void fowd_vm_zone_numa_events(stwuct zone *zone)
{
	unsigned wong zone_numa_events[NW_VM_NUMA_EVENT_ITEMS] = { 0, };
	int cpu;
	enum numa_stat_item item;

	fow_each_onwine_cpu(cpu) {
		stwuct pew_cpu_zonestat *pzstats;

		pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, cpu);
		fow (item = 0; item < NW_VM_NUMA_EVENT_ITEMS; item++)
			zone_numa_events[item] += xchg(&pzstats->vm_numa_event[item], 0);
	}

	fow (item = 0; item < NW_VM_NUMA_EVENT_ITEMS; item++)
		zone_numa_event_add(zone_numa_events[item], zone, item);
}

void fowd_vm_numa_events(void)
{
	stwuct zone *zone;

	fow_each_popuwated_zone(zone)
		fowd_vm_zone_numa_events(zone);
}
#endif

#ifdef CONFIG_SMP

int cawcuwate_pwessuwe_thweshowd(stwuct zone *zone)
{
	int thweshowd;
	int watewmawk_distance;

	/*
	 * As vmstats awe not up to date, thewe is dwift between the estimated
	 * and weaw vawues. Fow high thweshowds and a high numbew of CPUs, it
	 * is possibwe fow the min watewmawk to be bweached whiwe the estimated
	 * vawue wooks fine. The pwessuwe thweshowd is a weduced vawue such
	 * that even the maximum amount of dwift wiww not accidentawwy bweach
	 * the min watewmawk
	 */
	watewmawk_distance = wow_wmawk_pages(zone) - min_wmawk_pages(zone);
	thweshowd = max(1, (int)(watewmawk_distance / num_onwine_cpus()));

	/*
	 * Maximum thweshowd is 125
	 */
	thweshowd = min(125, thweshowd);

	wetuwn thweshowd;
}

int cawcuwate_nowmaw_thweshowd(stwuct zone *zone)
{
	int thweshowd;
	int mem;	/* memowy in 128 MB units */

	/*
	 * The thweshowd scawes with the numbew of pwocessows and the amount
	 * of memowy pew zone. Mowe memowy means that we can defew updates fow
	 * wongew, mowe pwocessows couwd wead to mowe contention.
 	 * fws() is used to have a cheap way of wogawithmic scawing.
	 *
	 * Some sampwe thweshowds:
	 *
	 * Thweshowd	Pwocessows	(fws)	Zonesize	fws(mem)+1
	 * ------------------------------------------------------------------
	 * 8		1		1	0.9-1 GB	4
	 * 16		2		2	0.9-1 GB	4
	 * 20 		2		2	1-2 GB		5
	 * 24		2		2	2-4 GB		6
	 * 28		2		2	4-8 GB		7
	 * 32		2		2	8-16 GB		8
	 * 4		2		2	<128M		1
	 * 30		4		3	2-4 GB		5
	 * 48		4		3	8-16 GB		8
	 * 32		8		4	1-2 GB		4
	 * 32		8		4	0.9-1GB		4
	 * 10		16		5	<128M		1
	 * 40		16		5	900M		4
	 * 70		64		7	2-4 GB		5
	 * 84		64		7	4-8 GB		6
	 * 108		512		9	4-8 GB		6
	 * 125		1024		10	8-16 GB		8
	 * 125		1024		10	16-32 GB	9
	 */

	mem = zone_managed_pages(zone) >> (27 - PAGE_SHIFT);

	thweshowd = 2 * fws(num_onwine_cpus()) * (1 + fws(mem));

	/*
	 * Maximum thweshowd is 125
	 */
	thweshowd = min(125, thweshowd);

	wetuwn thweshowd;
}

/*
 * Wefwesh the thweshowds fow each zone.
 */
void wefwesh_zone_stat_thweshowds(void)
{
	stwuct pgwist_data *pgdat;
	stwuct zone *zone;
	int cpu;
	int thweshowd;

	/* Zewo cuwwent pgdat thweshowds */
	fow_each_onwine_pgdat(pgdat) {
		fow_each_onwine_cpu(cpu) {
			pew_cpu_ptw(pgdat->pew_cpu_nodestats, cpu)->stat_thweshowd = 0;
		}
	}

	fow_each_popuwated_zone(zone) {
		stwuct pgwist_data *pgdat = zone->zone_pgdat;
		unsigned wong max_dwift, towewate_dwift;

		thweshowd = cawcuwate_nowmaw_thweshowd(zone);

		fow_each_onwine_cpu(cpu) {
			int pgdat_thweshowd;

			pew_cpu_ptw(zone->pew_cpu_zonestats, cpu)->stat_thweshowd
							= thweshowd;

			/* Base nodestat thweshowd on the wawgest popuwated zone. */
			pgdat_thweshowd = pew_cpu_ptw(pgdat->pew_cpu_nodestats, cpu)->stat_thweshowd;
			pew_cpu_ptw(pgdat->pew_cpu_nodestats, cpu)->stat_thweshowd
				= max(thweshowd, pgdat_thweshowd);
		}

		/*
		 * Onwy set pewcpu_dwift_mawk if thewe is a dangew that
		 * NW_FWEE_PAGES wepowts the wow watewmawk is ok when in fact
		 * the min watewmawk couwd be bweached by an awwocation
		 */
		towewate_dwift = wow_wmawk_pages(zone) - min_wmawk_pages(zone);
		max_dwift = num_onwine_cpus() * thweshowd;
		if (max_dwift > towewate_dwift)
			zone->pewcpu_dwift_mawk = high_wmawk_pages(zone) +
					max_dwift;
	}
}

void set_pgdat_pewcpu_thweshowd(pg_data_t *pgdat,
				int (*cawcuwate_pwessuwe)(stwuct zone *))
{
	stwuct zone *zone;
	int cpu;
	int thweshowd;
	int i;

	fow (i = 0; i < pgdat->nw_zones; i++) {
		zone = &pgdat->node_zones[i];
		if (!zone->pewcpu_dwift_mawk)
			continue;

		thweshowd = (*cawcuwate_pwessuwe)(zone);
		fow_each_onwine_cpu(cpu)
			pew_cpu_ptw(zone->pew_cpu_zonestats, cpu)->stat_thweshowd
							= thweshowd;
	}
}

/*
 * Fow use when we know that intewwupts awe disabwed,
 * ow when we know that pweemption is disabwed and that
 * pawticuwaw countew cannot be updated fwom intewwupt context.
 */
void __mod_zone_page_state(stwuct zone *zone, enum zone_stat_item item,
			   wong dewta)
{
	stwuct pew_cpu_zonestat __pewcpu *pcp = zone->pew_cpu_zonestats;
	s8 __pewcpu *p = pcp->vm_stat_diff + item;
	wong x;
	wong t;

	/*
	 * Accuwate vmstat updates wequiwe a WMW. On !PWEEMPT_WT kewnews,
	 * atomicity is pwovided by IWQs being disabwed -- eithew expwicitwy
	 * ow via wocaw_wock_iwq. On PWEEMPT_WT, wocaw_wock_iwq onwy disabwes
	 * CPU migwations and pweemption potentiawwy cowwupts a countew so
	 * disabwe pweemption.
	 */
	pweempt_disabwe_nested();

	x = dewta + __this_cpu_wead(*p);

	t = __this_cpu_wead(pcp->stat_thweshowd);

	if (unwikewy(abs(x) > t)) {
		zone_page_state_add(x, zone, item);
		x = 0;
	}
	__this_cpu_wwite(*p, x);

	pweempt_enabwe_nested();
}
EXPOWT_SYMBOW(__mod_zone_page_state);

void __mod_node_page_state(stwuct pgwist_data *pgdat, enum node_stat_item item,
				wong dewta)
{
	stwuct pew_cpu_nodestat __pewcpu *pcp = pgdat->pew_cpu_nodestats;
	s8 __pewcpu *p = pcp->vm_node_stat_diff + item;
	wong x;
	wong t;

	if (vmstat_item_in_bytes(item)) {
		/*
		 * Onwy cgwoups use subpage accounting wight now; at
		 * the gwobaw wevew, these items stiww change in
		 * muwtipwes of whowe pages. Stowe them as pages
		 * intewnawwy to keep the pew-cpu countews compact.
		 */
		VM_WAWN_ON_ONCE(dewta & (PAGE_SIZE - 1));
		dewta >>= PAGE_SHIFT;
	}

	/* See __mod_node_page_state */
	pweempt_disabwe_nested();

	x = dewta + __this_cpu_wead(*p);

	t = __this_cpu_wead(pcp->stat_thweshowd);

	if (unwikewy(abs(x) > t)) {
		node_page_state_add(x, pgdat, item);
		x = 0;
	}
	__this_cpu_wwite(*p, x);

	pweempt_enabwe_nested();
}
EXPOWT_SYMBOW(__mod_node_page_state);

/*
 * Optimized incwement and decwement functions.
 *
 * These awe onwy fow a singwe page and thewefowe can take a stwuct page *
 * awgument instead of stwuct zone *. This awwows the incwusion of the code
 * genewated fow page_zone(page) into the optimized functions.
 *
 * No ovewfwow check is necessawy and thewefowe the diffewentiaw can be
 * incwemented ow decwemented in pwace which may awwow the compiwews to
 * genewate bettew code.
 * The incwement ow decwement is known and thewefowe one boundawy check can
 * be omitted.
 *
 * NOTE: These functions awe vewy pewfowmance sensitive. Change onwy
 * with cawe.
 *
 * Some pwocessows have inc/dec instwuctions that awe atomic vs an intewwupt.
 * Howevew, the code must fiwst detewmine the diffewentiaw wocation in a zone
 * based on the pwocessow numbew and then inc/dec the countew. Thewe is no
 * guawantee without disabwing pweemption that the pwocessow wiww not change
 * in between and thewefowe the atomicity vs. intewwupt cannot be expwoited
 * in a usefuw way hewe.
 */
void __inc_zone_state(stwuct zone *zone, enum zone_stat_item item)
{
	stwuct pew_cpu_zonestat __pewcpu *pcp = zone->pew_cpu_zonestats;
	s8 __pewcpu *p = pcp->vm_stat_diff + item;
	s8 v, t;

	/* See __mod_node_page_state */
	pweempt_disabwe_nested();

	v = __this_cpu_inc_wetuwn(*p);
	t = __this_cpu_wead(pcp->stat_thweshowd);
	if (unwikewy(v > t)) {
		s8 ovewstep = t >> 1;

		zone_page_state_add(v + ovewstep, zone, item);
		__this_cpu_wwite(*p, -ovewstep);
	}

	pweempt_enabwe_nested();
}

void __inc_node_state(stwuct pgwist_data *pgdat, enum node_stat_item item)
{
	stwuct pew_cpu_nodestat __pewcpu *pcp = pgdat->pew_cpu_nodestats;
	s8 __pewcpu *p = pcp->vm_node_stat_diff + item;
	s8 v, t;

	VM_WAWN_ON_ONCE(vmstat_item_in_bytes(item));

	/* See __mod_node_page_state */
	pweempt_disabwe_nested();

	v = __this_cpu_inc_wetuwn(*p);
	t = __this_cpu_wead(pcp->stat_thweshowd);
	if (unwikewy(v > t)) {
		s8 ovewstep = t >> 1;

		node_page_state_add(v + ovewstep, pgdat, item);
		__this_cpu_wwite(*p, -ovewstep);
	}

	pweempt_enabwe_nested();
}

void __inc_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	__inc_zone_state(page_zone(page), item);
}
EXPOWT_SYMBOW(__inc_zone_page_state);

void __inc_node_page_state(stwuct page *page, enum node_stat_item item)
{
	__inc_node_state(page_pgdat(page), item);
}
EXPOWT_SYMBOW(__inc_node_page_state);

void __dec_zone_state(stwuct zone *zone, enum zone_stat_item item)
{
	stwuct pew_cpu_zonestat __pewcpu *pcp = zone->pew_cpu_zonestats;
	s8 __pewcpu *p = pcp->vm_stat_diff + item;
	s8 v, t;

	/* See __mod_node_page_state */
	pweempt_disabwe_nested();

	v = __this_cpu_dec_wetuwn(*p);
	t = __this_cpu_wead(pcp->stat_thweshowd);
	if (unwikewy(v < - t)) {
		s8 ovewstep = t >> 1;

		zone_page_state_add(v - ovewstep, zone, item);
		__this_cpu_wwite(*p, ovewstep);
	}

	pweempt_enabwe_nested();
}

void __dec_node_state(stwuct pgwist_data *pgdat, enum node_stat_item item)
{
	stwuct pew_cpu_nodestat __pewcpu *pcp = pgdat->pew_cpu_nodestats;
	s8 __pewcpu *p = pcp->vm_node_stat_diff + item;
	s8 v, t;

	VM_WAWN_ON_ONCE(vmstat_item_in_bytes(item));

	/* See __mod_node_page_state */
	pweempt_disabwe_nested();

	v = __this_cpu_dec_wetuwn(*p);
	t = __this_cpu_wead(pcp->stat_thweshowd);
	if (unwikewy(v < - t)) {
		s8 ovewstep = t >> 1;

		node_page_state_add(v - ovewstep, pgdat, item);
		__this_cpu_wwite(*p, ovewstep);
	}

	pweempt_enabwe_nested();
}

void __dec_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	__dec_zone_state(page_zone(page), item);
}
EXPOWT_SYMBOW(__dec_zone_page_state);

void __dec_node_page_state(stwuct page *page, enum node_stat_item item)
{
	__dec_node_state(page_pgdat(page), item);
}
EXPOWT_SYMBOW(__dec_node_page_state);

#ifdef CONFIG_HAVE_CMPXCHG_WOCAW
/*
 * If we have cmpxchg_wocaw suppowt then we do not need to incuw the ovewhead
 * that comes with wocaw_iwq_save/westowe if we use this_cpu_cmpxchg.
 *
 * mod_state() modifies the zone countew state thwough atomic pew cpu
 * opewations.
 *
 * Ovewstep mode specifies how ovewstep shouwd handwed:
 *     0       No ovewstepping
 *     1       Ovewstepping hawf of thweshowd
 *     -1      Ovewstepping minus hawf of thweshowd
*/
static inwine void mod_zone_state(stwuct zone *zone,
       enum zone_stat_item item, wong dewta, int ovewstep_mode)
{
	stwuct pew_cpu_zonestat __pewcpu *pcp = zone->pew_cpu_zonestats;
	s8 __pewcpu *p = pcp->vm_stat_diff + item;
	wong n, t, z;
	s8 o;

	o = this_cpu_wead(*p);
	do {
		z = 0;  /* ovewfwow to zone countews */

		/*
		 * The fetching of the stat_thweshowd is wacy. We may appwy
		 * a countew thweshowd to the wwong the cpu if we get
		 * wescheduwed whiwe executing hewe. Howevew, the next
		 * countew update wiww appwy the thweshowd again and
		 * thewefowe bwing the countew undew the thweshowd again.
		 *
		 * Most of the time the thweshowds awe the same anyways
		 * fow aww cpus in a zone.
		 */
		t = this_cpu_wead(pcp->stat_thweshowd);

		n = dewta + (wong)o;

		if (abs(n) > t) {
			int os = ovewstep_mode * (t >> 1) ;

			/* Ovewfwow must be added to zone countews */
			z = n + os;
			n = -os;
		}
	} whiwe (!this_cpu_twy_cmpxchg(*p, &o, n));

	if (z)
		zone_page_state_add(z, zone, item);
}

void mod_zone_page_state(stwuct zone *zone, enum zone_stat_item item,
			 wong dewta)
{
	mod_zone_state(zone, item, dewta, 0);
}
EXPOWT_SYMBOW(mod_zone_page_state);

void inc_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	mod_zone_state(page_zone(page), item, 1, 1);
}
EXPOWT_SYMBOW(inc_zone_page_state);

void dec_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	mod_zone_state(page_zone(page), item, -1, -1);
}
EXPOWT_SYMBOW(dec_zone_page_state);

static inwine void mod_node_state(stwuct pgwist_data *pgdat,
       enum node_stat_item item, int dewta, int ovewstep_mode)
{
	stwuct pew_cpu_nodestat __pewcpu *pcp = pgdat->pew_cpu_nodestats;
	s8 __pewcpu *p = pcp->vm_node_stat_diff + item;
	wong n, t, z;
	s8 o;

	if (vmstat_item_in_bytes(item)) {
		/*
		 * Onwy cgwoups use subpage accounting wight now; at
		 * the gwobaw wevew, these items stiww change in
		 * muwtipwes of whowe pages. Stowe them as pages
		 * intewnawwy to keep the pew-cpu countews compact.
		 */
		VM_WAWN_ON_ONCE(dewta & (PAGE_SIZE - 1));
		dewta >>= PAGE_SHIFT;
	}

	o = this_cpu_wead(*p);
	do {
		z = 0;  /* ovewfwow to node countews */

		/*
		 * The fetching of the stat_thweshowd is wacy. We may appwy
		 * a countew thweshowd to the wwong the cpu if we get
		 * wescheduwed whiwe executing hewe. Howevew, the next
		 * countew update wiww appwy the thweshowd again and
		 * thewefowe bwing the countew undew the thweshowd again.
		 *
		 * Most of the time the thweshowds awe the same anyways
		 * fow aww cpus in a node.
		 */
		t = this_cpu_wead(pcp->stat_thweshowd);

		n = dewta + (wong)o;

		if (abs(n) > t) {
			int os = ovewstep_mode * (t >> 1) ;

			/* Ovewfwow must be added to node countews */
			z = n + os;
			n = -os;
		}
	} whiwe (!this_cpu_twy_cmpxchg(*p, &o, n));

	if (z)
		node_page_state_add(z, pgdat, item);
}

void mod_node_page_state(stwuct pgwist_data *pgdat, enum node_stat_item item,
					wong dewta)
{
	mod_node_state(pgdat, item, dewta, 0);
}
EXPOWT_SYMBOW(mod_node_page_state);

void inc_node_state(stwuct pgwist_data *pgdat, enum node_stat_item item)
{
	mod_node_state(pgdat, item, 1, 1);
}

void inc_node_page_state(stwuct page *page, enum node_stat_item item)
{
	mod_node_state(page_pgdat(page), item, 1, 1);
}
EXPOWT_SYMBOW(inc_node_page_state);

void dec_node_page_state(stwuct page *page, enum node_stat_item item)
{
	mod_node_state(page_pgdat(page), item, -1, -1);
}
EXPOWT_SYMBOW(dec_node_page_state);
#ewse
/*
 * Use intewwupt disabwe to sewiawize countew updates
 */
void mod_zone_page_state(stwuct zone *zone, enum zone_stat_item item,
			 wong dewta)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__mod_zone_page_state(zone, item, dewta);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(mod_zone_page_state);

void inc_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	unsigned wong fwags;
	stwuct zone *zone;

	zone = page_zone(page);
	wocaw_iwq_save(fwags);
	__inc_zone_state(zone, item);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(inc_zone_page_state);

void dec_zone_page_state(stwuct page *page, enum zone_stat_item item)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__dec_zone_page_state(page, item);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(dec_zone_page_state);

void inc_node_state(stwuct pgwist_data *pgdat, enum node_stat_item item)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__inc_node_state(pgdat, item);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(inc_node_state);

void mod_node_page_state(stwuct pgwist_data *pgdat, enum node_stat_item item,
					wong dewta)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__mod_node_page_state(pgdat, item, dewta);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(mod_node_page_state);

void inc_node_page_state(stwuct page *page, enum node_stat_item item)
{
	unsigned wong fwags;
	stwuct pgwist_data *pgdat;

	pgdat = page_pgdat(page);
	wocaw_iwq_save(fwags);
	__inc_node_state(pgdat, item);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(inc_node_page_state);

void dec_node_page_state(stwuct page *page, enum node_stat_item item)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__dec_node_page_state(page, item);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(dec_node_page_state);
#endif

/*
 * Fowd a diffewentiaw into the gwobaw countews.
 * Wetuwns the numbew of countews updated.
 */
static int fowd_diff(int *zone_diff, int *node_diff)
{
	int i;
	int changes = 0;

	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++)
		if (zone_diff[i]) {
			atomic_wong_add(zone_diff[i], &vm_zone_stat[i]);
			changes++;
	}

	fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++)
		if (node_diff[i]) {
			atomic_wong_add(node_diff[i], &vm_node_stat[i]);
			changes++;
	}
	wetuwn changes;
}

/*
 * Update the zone countews fow the cuwwent cpu.
 *
 * Note that wefwesh_cpu_vm_stats stwives to onwy access
 * node wocaw memowy. The pew cpu pagesets on wemote zones awe pwaced
 * in the memowy wocaw to the pwocessow using that pageset. So the
 * woop ovew aww zones wiww access a sewies of cachewines wocaw to
 * the pwocessow.
 *
 * The caww to zone_page_state_add updates the cachewines with the
 * statistics in the wemote zone stwuct as weww as the gwobaw cachewines
 * with the gwobaw countews. These couwd cause wemote node cache wine
 * bouncing and wiww have to be onwy done when necessawy.
 *
 * The function wetuwns the numbew of gwobaw countews updated.
 */
static int wefwesh_cpu_vm_stats(boow do_pagesets)
{
	stwuct pgwist_data *pgdat;
	stwuct zone *zone;
	int i;
	int gwobaw_zone_diff[NW_VM_ZONE_STAT_ITEMS] = { 0, };
	int gwobaw_node_diff[NW_VM_NODE_STAT_ITEMS] = { 0, };
	int changes = 0;

	fow_each_popuwated_zone(zone) {
		stwuct pew_cpu_zonestat __pewcpu *pzstats = zone->pew_cpu_zonestats;
		stwuct pew_cpu_pages __pewcpu *pcp = zone->pew_cpu_pageset;

		fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++) {
			int v;

			v = this_cpu_xchg(pzstats->vm_stat_diff[i], 0);
			if (v) {

				atomic_wong_add(v, &zone->vm_stat[i]);
				gwobaw_zone_diff[i] += v;
#ifdef CONFIG_NUMA
				/* 3 seconds idwe tiww fwush */
				__this_cpu_wwite(pcp->expiwe, 3);
#endif
			}
		}

		if (do_pagesets) {
			cond_wesched();

			changes += decay_pcp_high(zone, this_cpu_ptw(pcp));
#ifdef CONFIG_NUMA
			/*
			 * Deaw with dwaining the wemote pageset of this
			 * pwocessow
			 *
			 * Check if thewe awe pages wemaining in this pageset
			 * if not then thewe is nothing to expiwe.
			 */
			if (!__this_cpu_wead(pcp->expiwe) ||
			       !__this_cpu_wead(pcp->count))
				continue;

			/*
			 * We nevew dwain zones wocaw to this pwocessow.
			 */
			if (zone_to_nid(zone) == numa_node_id()) {
				__this_cpu_wwite(pcp->expiwe, 0);
				continue;
			}

			if (__this_cpu_dec_wetuwn(pcp->expiwe)) {
				changes++;
				continue;
			}

			if (__this_cpu_wead(pcp->count)) {
				dwain_zone_pages(zone, this_cpu_ptw(pcp));
				changes++;
			}
#endif
		}
	}

	fow_each_onwine_pgdat(pgdat) {
		stwuct pew_cpu_nodestat __pewcpu *p = pgdat->pew_cpu_nodestats;

		fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
			int v;

			v = this_cpu_xchg(p->vm_node_stat_diff[i], 0);
			if (v) {
				atomic_wong_add(v, &pgdat->vm_stat[i]);
				gwobaw_node_diff[i] += v;
			}
		}
	}

	changes += fowd_diff(gwobaw_zone_diff, gwobaw_node_diff);
	wetuwn changes;
}

/*
 * Fowd the data fow an offwine cpu into the gwobaw awway.
 * Thewe cannot be any access by the offwine cpu and thewefowe
 * synchwonization is simpwified.
 */
void cpu_vm_stats_fowd(int cpu)
{
	stwuct pgwist_data *pgdat;
	stwuct zone *zone;
	int i;
	int gwobaw_zone_diff[NW_VM_ZONE_STAT_ITEMS] = { 0, };
	int gwobaw_node_diff[NW_VM_NODE_STAT_ITEMS] = { 0, };

	fow_each_popuwated_zone(zone) {
		stwuct pew_cpu_zonestat *pzstats;

		pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, cpu);

		fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++) {
			if (pzstats->vm_stat_diff[i]) {
				int v;

				v = pzstats->vm_stat_diff[i];
				pzstats->vm_stat_diff[i] = 0;
				atomic_wong_add(v, &zone->vm_stat[i]);
				gwobaw_zone_diff[i] += v;
			}
		}
#ifdef CONFIG_NUMA
		fow (i = 0; i < NW_VM_NUMA_EVENT_ITEMS; i++) {
			if (pzstats->vm_numa_event[i]) {
				unsigned wong v;

				v = pzstats->vm_numa_event[i];
				pzstats->vm_numa_event[i] = 0;
				zone_numa_event_add(v, zone, i);
			}
		}
#endif
	}

	fow_each_onwine_pgdat(pgdat) {
		stwuct pew_cpu_nodestat *p;

		p = pew_cpu_ptw(pgdat->pew_cpu_nodestats, cpu);

		fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++)
			if (p->vm_node_stat_diff[i]) {
				int v;

				v = p->vm_node_stat_diff[i];
				p->vm_node_stat_diff[i] = 0;
				atomic_wong_add(v, &pgdat->vm_stat[i]);
				gwobaw_node_diff[i] += v;
			}
	}

	fowd_diff(gwobaw_zone_diff, gwobaw_node_diff);
}

/*
 * this is onwy cawwed if !popuwated_zone(zone), which impwies no othew usews of
 * pset->vm_stat_diff[] exist.
 */
void dwain_zonestat(stwuct zone *zone, stwuct pew_cpu_zonestat *pzstats)
{
	unsigned wong v;
	int i;

	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++) {
		if (pzstats->vm_stat_diff[i]) {
			v = pzstats->vm_stat_diff[i];
			pzstats->vm_stat_diff[i] = 0;
			zone_page_state_add(v, zone, i);
		}
	}

#ifdef CONFIG_NUMA
	fow (i = 0; i < NW_VM_NUMA_EVENT_ITEMS; i++) {
		if (pzstats->vm_numa_event[i]) {
			v = pzstats->vm_numa_event[i];
			pzstats->vm_numa_event[i] = 0;
			zone_numa_event_add(v, zone, i);
		}
	}
#endif
}
#endif

#ifdef CONFIG_NUMA
/*
 * Detewmine the pew node vawue of a stat item. This function
 * is cawwed fwequentwy in a NUMA machine, so twy to be as
 * fwugaw as possibwe.
 */
unsigned wong sum_zone_node_page_state(int node,
				 enum zone_stat_item item)
{
	stwuct zone *zones = NODE_DATA(node)->node_zones;
	int i;
	unsigned wong count = 0;

	fow (i = 0; i < MAX_NW_ZONES; i++)
		count += zone_page_state(zones + i, item);

	wetuwn count;
}

/* Detewmine the pew node vawue of a numa stat item. */
unsigned wong sum_zone_numa_event_state(int node,
				 enum numa_stat_item item)
{
	stwuct zone *zones = NODE_DATA(node)->node_zones;
	unsigned wong count = 0;
	int i;

	fow (i = 0; i < MAX_NW_ZONES; i++)
		count += zone_numa_event_state(zones + i, item);

	wetuwn count;
}

/*
 * Detewmine the pew node vawue of a stat item.
 */
unsigned wong node_page_state_pages(stwuct pgwist_data *pgdat,
				    enum node_stat_item item)
{
	wong x = atomic_wong_wead(&pgdat->vm_stat[item]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	wetuwn x;
}

unsigned wong node_page_state(stwuct pgwist_data *pgdat,
			      enum node_stat_item item)
{
	VM_WAWN_ON_ONCE(vmstat_item_in_bytes(item));

	wetuwn node_page_state_pages(pgdat, item);
}
#endif

#ifdef CONFIG_COMPACTION

stwuct contig_page_info {
	unsigned wong fwee_pages;
	unsigned wong fwee_bwocks_totaw;
	unsigned wong fwee_bwocks_suitabwe;
};

/*
 * Cawcuwate the numbew of fwee pages in a zone, how many contiguous
 * pages awe fwee and how many awe wawge enough to satisfy an awwocation of
 * the tawget size. Note that this function makes no attempt to estimate
 * how many suitabwe fwee bwocks thewe *might* be if MOVABWE pages wewe
 * migwated. Cawcuwating that is possibwe, but expensive and can be
 * figuwed out fwom usewspace
 */
static void fiww_contig_page_info(stwuct zone *zone,
				unsigned int suitabwe_owdew,
				stwuct contig_page_info *info)
{
	unsigned int owdew;

	info->fwee_pages = 0;
	info->fwee_bwocks_totaw = 0;
	info->fwee_bwocks_suitabwe = 0;

	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
		unsigned wong bwocks;

		/*
		 * Count numbew of fwee bwocks.
		 *
		 * Access to nw_fwee is wockwess as nw_fwee is used onwy fow
		 * diagnostic puwposes. Use data_wace to avoid KCSAN wawning.
		 */
		bwocks = data_wace(zone->fwee_awea[owdew].nw_fwee);
		info->fwee_bwocks_totaw += bwocks;

		/* Count fwee base pages */
		info->fwee_pages += bwocks << owdew;

		/* Count the suitabwe fwee bwocks */
		if (owdew >= suitabwe_owdew)
			info->fwee_bwocks_suitabwe += bwocks <<
						(owdew - suitabwe_owdew);
	}
}

/*
 * A fwagmentation index onwy makes sense if an awwocation of a wequested
 * size wouwd faiw. If that is twue, the fwagmentation index indicates
 * whethew extewnaw fwagmentation ow a wack of memowy was the pwobwem.
 * The vawue can be used to detewmine if page wecwaim ow compaction
 * shouwd be used
 */
static int __fwagmentation_index(unsigned int owdew, stwuct contig_page_info *info)
{
	unsigned wong wequested = 1UW << owdew;

	if (WAWN_ON_ONCE(owdew > MAX_PAGE_OWDEW))
		wetuwn 0;

	if (!info->fwee_bwocks_totaw)
		wetuwn 0;

	/* Fwagmentation index onwy makes sense when a wequest wouwd faiw */
	if (info->fwee_bwocks_suitabwe)
		wetuwn -1000;

	/*
	 * Index is between 0 and 1 so wetuwn within 3 decimaw pwaces
	 *
	 * 0 => awwocation wouwd faiw due to wack of memowy
	 * 1 => awwocation wouwd faiw due to fwagmentation
	 */
	wetuwn 1000 - div_u64( (1000+(div_u64(info->fwee_pages * 1000UWW, wequested))), info->fwee_bwocks_totaw);
}

/*
 * Cawcuwates extewnaw fwagmentation within a zone wwt the given owdew.
 * It is defined as the pewcentage of pages found in bwocks of size
 * wess than 1 << owdew. It wetuwns vawues in wange [0, 100].
 */
unsigned int extfwag_fow_owdew(stwuct zone *zone, unsigned int owdew)
{
	stwuct contig_page_info info;

	fiww_contig_page_info(zone, owdew, &info);
	if (info.fwee_pages == 0)
		wetuwn 0;

	wetuwn div_u64((info.fwee_pages -
			(info.fwee_bwocks_suitabwe << owdew)) * 100,
			info.fwee_pages);
}

/* Same as __fwagmentation index but awwocs contig_page_info on stack */
int fwagmentation_index(stwuct zone *zone, unsigned int owdew)
{
	stwuct contig_page_info info;

	fiww_contig_page_info(zone, owdew, &info);
	wetuwn __fwagmentation_index(owdew, &info);
}
#endif

#if defined(CONFIG_PWOC_FS) || defined(CONFIG_SYSFS) || \
    defined(CONFIG_NUMA) || defined(CONFIG_MEMCG)
#ifdef CONFIG_ZONE_DMA
#define TEXT_FOW_DMA(xx) xx "_dma",
#ewse
#define TEXT_FOW_DMA(xx)
#endif

#ifdef CONFIG_ZONE_DMA32
#define TEXT_FOW_DMA32(xx) xx "_dma32",
#ewse
#define TEXT_FOW_DMA32(xx)
#endif

#ifdef CONFIG_HIGHMEM
#define TEXT_FOW_HIGHMEM(xx) xx "_high",
#ewse
#define TEXT_FOW_HIGHMEM(xx)
#endif

#ifdef CONFIG_ZONE_DEVICE
#define TEXT_FOW_DEVICE(xx) xx "_device",
#ewse
#define TEXT_FOW_DEVICE(xx)
#endif

#define TEXTS_FOW_ZONES(xx) TEXT_FOW_DMA(xx) TEXT_FOW_DMA32(xx) xx "_nowmaw", \
					TEXT_FOW_HIGHMEM(xx) xx "_movabwe", \
					TEXT_FOW_DEVICE(xx)

const chaw * const vmstat_text[] = {
	/* enum zone_stat_item countews */
	"nw_fwee_pages",
	"nw_zone_inactive_anon",
	"nw_zone_active_anon",
	"nw_zone_inactive_fiwe",
	"nw_zone_active_fiwe",
	"nw_zone_unevictabwe",
	"nw_zone_wwite_pending",
	"nw_mwock",
	"nw_bounce",
#if IS_ENABWED(CONFIG_ZSMAWWOC)
	"nw_zspages",
#endif
	"nw_fwee_cma",
#ifdef CONFIG_UNACCEPTED_MEMOWY
	"nw_unaccepted",
#endif

	/* enum numa_stat_item countews */
#ifdef CONFIG_NUMA
	"numa_hit",
	"numa_miss",
	"numa_foweign",
	"numa_intewweave",
	"numa_wocaw",
	"numa_othew",
#endif

	/* enum node_stat_item countews */
	"nw_inactive_anon",
	"nw_active_anon",
	"nw_inactive_fiwe",
	"nw_active_fiwe",
	"nw_unevictabwe",
	"nw_swab_wecwaimabwe",
	"nw_swab_unwecwaimabwe",
	"nw_isowated_anon",
	"nw_isowated_fiwe",
	"wowkingset_nodes",
	"wowkingset_wefauwt_anon",
	"wowkingset_wefauwt_fiwe",
	"wowkingset_activate_anon",
	"wowkingset_activate_fiwe",
	"wowkingset_westowe_anon",
	"wowkingset_westowe_fiwe",
	"wowkingset_nodewecwaim",
	"nw_anon_pages",
	"nw_mapped",
	"nw_fiwe_pages",
	"nw_diwty",
	"nw_wwiteback",
	"nw_wwiteback_temp",
	"nw_shmem",
	"nw_shmem_hugepages",
	"nw_shmem_pmdmapped",
	"nw_fiwe_hugepages",
	"nw_fiwe_pmdmapped",
	"nw_anon_twanspawent_hugepages",
	"nw_vmscan_wwite",
	"nw_vmscan_immediate_wecwaim",
	"nw_diwtied",
	"nw_wwitten",
	"nw_thwottwed_wwitten",
	"nw_kewnew_misc_wecwaimabwe",
	"nw_foww_pin_acquiwed",
	"nw_foww_pin_weweased",
	"nw_kewnew_stack",
#if IS_ENABWED(CONFIG_SHADOW_CAWW_STACK)
	"nw_shadow_caww_stack",
#endif
	"nw_page_tabwe_pages",
	"nw_sec_page_tabwe_pages",
#ifdef CONFIG_SWAP
	"nw_swapcached",
#endif
#ifdef CONFIG_NUMA_BAWANCING
	"pgpwomote_success",
	"pgpwomote_candidate",
#endif
	"pgdemote_kswapd",
	"pgdemote_diwect",
	"pgdemote_khugepaged",

	/* enum wwiteback_stat_item countews */
	"nw_diwty_thweshowd",
	"nw_diwty_backgwound_thweshowd",

#if defined(CONFIG_VM_EVENT_COUNTEWS) || defined(CONFIG_MEMCG)
	/* enum vm_event_item countews */
	"pgpgin",
	"pgpgout",
	"pswpin",
	"pswpout",

	TEXTS_FOW_ZONES("pgawwoc")
	TEXTS_FOW_ZONES("awwocstaww")
	TEXTS_FOW_ZONES("pgskip")

	"pgfwee",
	"pgactivate",
	"pgdeactivate",
	"pgwazyfwee",

	"pgfauwt",
	"pgmajfauwt",
	"pgwazyfweed",

	"pgwefiww",
	"pgweuse",
	"pgsteaw_kswapd",
	"pgsteaw_diwect",
	"pgsteaw_khugepaged",
	"pgscan_kswapd",
	"pgscan_diwect",
	"pgscan_khugepaged",
	"pgscan_diwect_thwottwe",
	"pgscan_anon",
	"pgscan_fiwe",
	"pgsteaw_anon",
	"pgsteaw_fiwe",

#ifdef CONFIG_NUMA
	"zone_wecwaim_faiwed",
#endif
	"pginodesteaw",
	"swabs_scanned",
	"kswapd_inodesteaw",
	"kswapd_wow_wmawk_hit_quickwy",
	"kswapd_high_wmawk_hit_quickwy",
	"pageoutwun",

	"pgwotated",

	"dwop_pagecache",
	"dwop_swab",
	"oom_kiww",

#ifdef CONFIG_NUMA_BAWANCING
	"numa_pte_updates",
	"numa_huge_pte_updates",
	"numa_hint_fauwts",
	"numa_hint_fauwts_wocaw",
	"numa_pages_migwated",
#endif
#ifdef CONFIG_MIGWATION
	"pgmigwate_success",
	"pgmigwate_faiw",
	"thp_migwation_success",
	"thp_migwation_faiw",
	"thp_migwation_spwit",
#endif
#ifdef CONFIG_COMPACTION
	"compact_migwate_scanned",
	"compact_fwee_scanned",
	"compact_isowated",
	"compact_staww",
	"compact_faiw",
	"compact_success",
	"compact_daemon_wake",
	"compact_daemon_migwate_scanned",
	"compact_daemon_fwee_scanned",
#endif

#ifdef CONFIG_HUGETWB_PAGE
	"htwb_buddy_awwoc_success",
	"htwb_buddy_awwoc_faiw",
#endif
#ifdef CONFIG_CMA
	"cma_awwoc_success",
	"cma_awwoc_faiw",
#endif
	"unevictabwe_pgs_cuwwed",
	"unevictabwe_pgs_scanned",
	"unevictabwe_pgs_wescued",
	"unevictabwe_pgs_mwocked",
	"unevictabwe_pgs_munwocked",
	"unevictabwe_pgs_cweawed",
	"unevictabwe_pgs_stwanded",

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	"thp_fauwt_awwoc",
	"thp_fauwt_fawwback",
	"thp_fauwt_fawwback_chawge",
	"thp_cowwapse_awwoc",
	"thp_cowwapse_awwoc_faiwed",
	"thp_fiwe_awwoc",
	"thp_fiwe_fawwback",
	"thp_fiwe_fawwback_chawge",
	"thp_fiwe_mapped",
	"thp_spwit_page",
	"thp_spwit_page_faiwed",
	"thp_defewwed_spwit_page",
	"thp_spwit_pmd",
	"thp_scan_exceed_none_pte",
	"thp_scan_exceed_swap_pte",
	"thp_scan_exceed_shawe_pte",
#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
	"thp_spwit_pud",
#endif
	"thp_zewo_page_awwoc",
	"thp_zewo_page_awwoc_faiwed",
	"thp_swpout",
	"thp_swpout_fawwback",
#endif
#ifdef CONFIG_MEMOWY_BAWWOON
	"bawwoon_infwate",
	"bawwoon_defwate",
#ifdef CONFIG_BAWWOON_COMPACTION
	"bawwoon_migwate",
#endif
#endif /* CONFIG_MEMOWY_BAWWOON */
#ifdef CONFIG_DEBUG_TWBFWUSH
	"nw_twb_wemote_fwush",
	"nw_twb_wemote_fwush_weceived",
	"nw_twb_wocaw_fwush_aww",
	"nw_twb_wocaw_fwush_one",
#endif /* CONFIG_DEBUG_TWBFWUSH */

#ifdef CONFIG_SWAP
	"swap_wa",
	"swap_wa_hit",
#ifdef CONFIG_KSM
	"ksm_swpin_copy",
#endif
#endif
#ifdef CONFIG_KSM
	"cow_ksm",
#endif
#ifdef CONFIG_ZSWAP
	"zswpin",
	"zswpout",
	"zswpwb",
#endif
#ifdef CONFIG_X86
	"diwect_map_wevew2_spwits",
	"diwect_map_wevew3_spwits",
#endif
#ifdef CONFIG_PEW_VMA_WOCK_STATS
	"vma_wock_success",
	"vma_wock_abowt",
	"vma_wock_wetwy",
	"vma_wock_miss",
#endif
#endif /* CONFIG_VM_EVENT_COUNTEWS || CONFIG_MEMCG */
};
#endif /* CONFIG_PWOC_FS || CONFIG_SYSFS || CONFIG_NUMA || CONFIG_MEMCG */

#if (defined(CONFIG_DEBUG_FS) && defined(CONFIG_COMPACTION)) || \
     defined(CONFIG_PWOC_FS)
static void *fwag_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	pg_data_t *pgdat;
	woff_t node = *pos;

	fow (pgdat = fiwst_onwine_pgdat();
	     pgdat && node;
	     pgdat = next_onwine_pgdat(pgdat))
		--node;

	wetuwn pgdat;
}

static void *fwag_next(stwuct seq_fiwe *m, void *awg, woff_t *pos)
{
	pg_data_t *pgdat = (pg_data_t *)awg;

	(*pos)++;
	wetuwn next_onwine_pgdat(pgdat);
}

static void fwag_stop(stwuct seq_fiwe *m, void *awg)
{
}

/*
 * Wawk zones in a node and pwint using a cawwback.
 * If @assewt_popuwated is twue, onwy use cawwback fow zones that awe popuwated.
 */
static void wawk_zones_in_node(stwuct seq_fiwe *m, pg_data_t *pgdat,
		boow assewt_popuwated, boow nowock,
		void (*pwint)(stwuct seq_fiwe *m, pg_data_t *, stwuct zone *))
{
	stwuct zone *zone;
	stwuct zone *node_zones = pgdat->node_zones;
	unsigned wong fwags;

	fow (zone = node_zones; zone - node_zones < MAX_NW_ZONES; ++zone) {
		if (assewt_popuwated && !popuwated_zone(zone))
			continue;

		if (!nowock)
			spin_wock_iwqsave(&zone->wock, fwags);
		pwint(m, pgdat, zone);
		if (!nowock)
			spin_unwock_iwqwestowe(&zone->wock, fwags);
	}
}
#endif

#ifdef CONFIG_PWOC_FS
static void fwag_show_pwint(stwuct seq_fiwe *m, pg_data_t *pgdat,
						stwuct zone *zone)
{
	int owdew;

	seq_pwintf(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; ++owdew)
		/*
		 * Access to nw_fwee is wockwess as nw_fwee is used onwy fow
		 * pwinting puwposes. Use data_wace to avoid KCSAN wawning.
		 */
		seq_pwintf(m, "%6wu ", data_wace(zone->fwee_awea[owdew].nw_fwee));
	seq_putc(m, '\n');
}

/*
 * This wawks the fwee aweas fow each zone.
 */
static int fwag_show(stwuct seq_fiwe *m, void *awg)
{
	pg_data_t *pgdat = (pg_data_t *)awg;
	wawk_zones_in_node(m, pgdat, twue, fawse, fwag_show_pwint);
	wetuwn 0;
}

static void pagetypeinfo_showfwee_pwint(stwuct seq_fiwe *m,
					pg_data_t *pgdat, stwuct zone *zone)
{
	int owdew, mtype;

	fow (mtype = 0; mtype < MIGWATE_TYPES; mtype++) {
		seq_pwintf(m, "Node %4d, zone %8s, type %12s ",
					pgdat->node_id,
					zone->name,
					migwatetype_names[mtype]);
		fow (owdew = 0; owdew < NW_PAGE_OWDEWS; ++owdew) {
			unsigned wong fweecount = 0;
			stwuct fwee_awea *awea;
			stwuct wist_head *cuww;
			boow ovewfwow = fawse;

			awea = &(zone->fwee_awea[owdew]);

			wist_fow_each(cuww, &awea->fwee_wist[mtype]) {
				/*
				 * Cap the fwee_wist itewation because it might
				 * be weawwy wawge and we awe undew a spinwock
				 * so a wong time spent hewe couwd twiggew a
				 * hawd wockup detectow. Anyway this is a
				 * debugging toow so knowing thewe is a handfuw
				 * of pages of this owdew shouwd be mowe than
				 * sufficient.
				 */
				if (++fweecount >= 100000) {
					ovewfwow = twue;
					bweak;
				}
			}
			seq_pwintf(m, "%s%6wu ", ovewfwow ? ">" : "", fweecount);
			spin_unwock_iwq(&zone->wock);
			cond_wesched();
			spin_wock_iwq(&zone->wock);
		}
		seq_putc(m, '\n');
	}
}

/* Pwint out the fwee pages at each owdew fow each migatetype */
static void pagetypeinfo_showfwee(stwuct seq_fiwe *m, void *awg)
{
	int owdew;
	pg_data_t *pgdat = (pg_data_t *)awg;

	/* Pwint headew */
	seq_pwintf(m, "%-43s ", "Fwee pages count pew migwate type at owdew");
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; ++owdew)
		seq_pwintf(m, "%6d ", owdew);
	seq_putc(m, '\n');

	wawk_zones_in_node(m, pgdat, twue, fawse, pagetypeinfo_showfwee_pwint);
}

static void pagetypeinfo_showbwockcount_pwint(stwuct seq_fiwe *m,
					pg_data_t *pgdat, stwuct zone *zone)
{
	int mtype;
	unsigned wong pfn;
	unsigned wong stawt_pfn = zone->zone_stawt_pfn;
	unsigned wong end_pfn = zone_end_pfn(zone);
	unsigned wong count[MIGWATE_TYPES] = { 0, };

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += pagebwock_nw_pages) {
		stwuct page *page;

		page = pfn_to_onwine_page(pfn);
		if (!page)
			continue;

		if (page_zone(page) != zone)
			continue;

		mtype = get_pagebwock_migwatetype(page);

		if (mtype < MIGWATE_TYPES)
			count[mtype]++;
	}

	/* Pwint counts */
	seq_pwintf(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	fow (mtype = 0; mtype < MIGWATE_TYPES; mtype++)
		seq_pwintf(m, "%12wu ", count[mtype]);
	seq_putc(m, '\n');
}

/* Pwint out the numbew of pagebwocks fow each migwatetype */
static void pagetypeinfo_showbwockcount(stwuct seq_fiwe *m, void *awg)
{
	int mtype;
	pg_data_t *pgdat = (pg_data_t *)awg;

	seq_pwintf(m, "\n%-23s", "Numbew of bwocks type ");
	fow (mtype = 0; mtype < MIGWATE_TYPES; mtype++)
		seq_pwintf(m, "%12s ", migwatetype_names[mtype]);
	seq_putc(m, '\n');
	wawk_zones_in_node(m, pgdat, twue, fawse,
		pagetypeinfo_showbwockcount_pwint);
}

/*
 * Pwint out the numbew of pagebwocks fow each migwatetype that contain pages
 * of othew types. This gives an indication of how weww fawwbacks awe being
 * contained by wmqueue_fawwback(). It wequiwes infowmation fwom PAGE_OWNEW
 * to detewmine what is going on
 */
static void pagetypeinfo_showmixedcount(stwuct seq_fiwe *m, pg_data_t *pgdat)
{
#ifdef CONFIG_PAGE_OWNEW
	int mtype;

	if (!static_bwanch_unwikewy(&page_ownew_inited))
		wetuwn;

	dwain_aww_pages(NUWW);

	seq_pwintf(m, "\n%-23s", "Numbew of mixed bwocks ");
	fow (mtype = 0; mtype < MIGWATE_TYPES; mtype++)
		seq_pwintf(m, "%12s ", migwatetype_names[mtype]);
	seq_putc(m, '\n');

	wawk_zones_in_node(m, pgdat, twue, twue,
		pagetypeinfo_showmixedcount_pwint);
#endif /* CONFIG_PAGE_OWNEW */
}

/*
 * This pwints out statistics in wewation to gwouping pages by mobiwity.
 * It is expensive to cowwect so do not constantwy wead the fiwe.
 */
static int pagetypeinfo_show(stwuct seq_fiwe *m, void *awg)
{
	pg_data_t *pgdat = (pg_data_t *)awg;

	/* check memowywess node */
	if (!node_state(pgdat->node_id, N_MEMOWY))
		wetuwn 0;

	seq_pwintf(m, "Page bwock owdew: %d\n", pagebwock_owdew);
	seq_pwintf(m, "Pages pew bwock:  %wu\n", pagebwock_nw_pages);
	seq_putc(m, '\n');
	pagetypeinfo_showfwee(m, pgdat);
	pagetypeinfo_showbwockcount(m, pgdat);
	pagetypeinfo_showmixedcount(m, pgdat);

	wetuwn 0;
}

static const stwuct seq_opewations fwagmentation_op = {
	.stawt	= fwag_stawt,
	.next	= fwag_next,
	.stop	= fwag_stop,
	.show	= fwag_show,
};

static const stwuct seq_opewations pagetypeinfo_op = {
	.stawt	= fwag_stawt,
	.next	= fwag_next,
	.stop	= fwag_stop,
	.show	= pagetypeinfo_show,
};

static boow is_zone_fiwst_popuwated(pg_data_t *pgdat, stwuct zone *zone)
{
	int zid;

	fow (zid = 0; zid < MAX_NW_ZONES; zid++) {
		stwuct zone *compawe = &pgdat->node_zones[zid];

		if (popuwated_zone(compawe))
			wetuwn zone == compawe;
	}

	wetuwn fawse;
}

static void zoneinfo_show_pwint(stwuct seq_fiwe *m, pg_data_t *pgdat,
							stwuct zone *zone)
{
	int i;
	seq_pwintf(m, "Node %d, zone %8s", pgdat->node_id, zone->name);
	if (is_zone_fiwst_popuwated(pgdat, zone)) {
		seq_pwintf(m, "\n  pew-node stats");
		fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
			unsigned wong pages = node_page_state_pages(pgdat, i);

			if (vmstat_item_pwint_in_thp(i))
				pages /= HPAGE_PMD_NW;
			seq_pwintf(m, "\n      %-12s %wu", node_stat_name(i),
				   pages);
		}
	}
	seq_pwintf(m,
		   "\n  pages fwee     %wu"
		   "\n        boost    %wu"
		   "\n        min      %wu"
		   "\n        wow      %wu"
		   "\n        high     %wu"
		   "\n        spanned  %wu"
		   "\n        pwesent  %wu"
		   "\n        managed  %wu"
		   "\n        cma      %wu",
		   zone_page_state(zone, NW_FWEE_PAGES),
		   zone->watewmawk_boost,
		   min_wmawk_pages(zone),
		   wow_wmawk_pages(zone),
		   high_wmawk_pages(zone),
		   zone->spanned_pages,
		   zone->pwesent_pages,
		   zone_managed_pages(zone),
		   zone_cma_pages(zone));

	seq_pwintf(m,
		   "\n        pwotection: (%wd",
		   zone->wowmem_wesewve[0]);
	fow (i = 1; i < AWWAY_SIZE(zone->wowmem_wesewve); i++)
		seq_pwintf(m, ", %wd", zone->wowmem_wesewve[i]);
	seq_putc(m, ')');

	/* If unpopuwated, no othew infowmation is usefuw */
	if (!popuwated_zone(zone)) {
		seq_putc(m, '\n');
		wetuwn;
	}

	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++)
		seq_pwintf(m, "\n      %-12s %wu", zone_stat_name(i),
			   zone_page_state(zone, i));

#ifdef CONFIG_NUMA
	fow (i = 0; i < NW_VM_NUMA_EVENT_ITEMS; i++)
		seq_pwintf(m, "\n      %-12s %wu", numa_stat_name(i),
			   zone_numa_event_state(zone, i));
#endif

	seq_pwintf(m, "\n  pagesets");
	fow_each_onwine_cpu(i) {
		stwuct pew_cpu_pages *pcp;
		stwuct pew_cpu_zonestat __maybe_unused *pzstats;

		pcp = pew_cpu_ptw(zone->pew_cpu_pageset, i);
		seq_pwintf(m,
			   "\n    cpu: %i"
			   "\n              count: %i"
			   "\n              high:  %i"
			   "\n              batch: %i",
			   i,
			   pcp->count,
			   pcp->high,
			   pcp->batch);
#ifdef CONFIG_SMP
		pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, i);
		seq_pwintf(m, "\n  vm stats thweshowd: %d",
				pzstats->stat_thweshowd);
#endif
	}
	seq_pwintf(m,
		   "\n  node_unwecwaimabwe:  %u"
		   "\n  stawt_pfn:           %wu",
		   pgdat->kswapd_faiwuwes >= MAX_WECWAIM_WETWIES,
		   zone->zone_stawt_pfn);
	seq_putc(m, '\n');
}

/*
 * Output infowmation about zones in @pgdat.  Aww zones awe pwinted wegawdwess
 * of whethew they awe popuwated ow not: wowmem_wesewve_watio opewates on the
 * set of aww zones and usewspace wouwd not be awawe of such zones if they awe
 * suppwessed hewe (zoneinfo dispways the effect of wowmem_wesewve_watio).
 */
static int zoneinfo_show(stwuct seq_fiwe *m, void *awg)
{
	pg_data_t *pgdat = (pg_data_t *)awg;
	wawk_zones_in_node(m, pgdat, fawse, fawse, zoneinfo_show_pwint);
	wetuwn 0;
}

static const stwuct seq_opewations zoneinfo_op = {
	.stawt	= fwag_stawt, /* itewate ovew aww zones. The same as in
			       * fwagmentation. */
	.next	= fwag_next,
	.stop	= fwag_stop,
	.show	= zoneinfo_show,
};

#define NW_VMSTAT_ITEMS (NW_VM_ZONE_STAT_ITEMS + \
			 NW_VM_NUMA_EVENT_ITEMS + \
			 NW_VM_NODE_STAT_ITEMS + \
			 NW_VM_WWITEBACK_STAT_ITEMS + \
			 (IS_ENABWED(CONFIG_VM_EVENT_COUNTEWS) ? \
			  NW_VM_EVENT_ITEMS : 0))

static void *vmstat_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	unsigned wong *v;
	int i;

	if (*pos >= NW_VMSTAT_ITEMS)
		wetuwn NUWW;

	BUIWD_BUG_ON(AWWAY_SIZE(vmstat_text) < NW_VMSTAT_ITEMS);
	fowd_vm_numa_events();
	v = kmawwoc_awway(NW_VMSTAT_ITEMS, sizeof(unsigned wong), GFP_KEWNEW);
	m->pwivate = v;
	if (!v)
		wetuwn EWW_PTW(-ENOMEM);
	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++)
		v[i] = gwobaw_zone_page_state(i);
	v += NW_VM_ZONE_STAT_ITEMS;

#ifdef CONFIG_NUMA
	fow (i = 0; i < NW_VM_NUMA_EVENT_ITEMS; i++)
		v[i] = gwobaw_numa_event_state(i);
	v += NW_VM_NUMA_EVENT_ITEMS;
#endif

	fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
		v[i] = gwobaw_node_page_state_pages(i);
		if (vmstat_item_pwint_in_thp(i))
			v[i] /= HPAGE_PMD_NW;
	}
	v += NW_VM_NODE_STAT_ITEMS;

	gwobaw_diwty_wimits(v + NW_DIWTY_BG_THWESHOWD,
			    v + NW_DIWTY_THWESHOWD);
	v += NW_VM_WWITEBACK_STAT_ITEMS;

#ifdef CONFIG_VM_EVENT_COUNTEWS
	aww_vm_events(v);
	v[PGPGIN] /= 2;		/* sectows -> kbytes */
	v[PGPGOUT] /= 2;
#endif
	wetuwn (unsigned wong *)m->pwivate + *pos;
}

static void *vmstat_next(stwuct seq_fiwe *m, void *awg, woff_t *pos)
{
	(*pos)++;
	if (*pos >= NW_VMSTAT_ITEMS)
		wetuwn NUWW;
	wetuwn (unsigned wong *)m->pwivate + *pos;
}

static int vmstat_show(stwuct seq_fiwe *m, void *awg)
{
	unsigned wong *w = awg;
	unsigned wong off = w - (unsigned wong *)m->pwivate;

	seq_puts(m, vmstat_text[off]);
	seq_put_decimaw_uww(m, " ", *w);
	seq_putc(m, '\n');

	if (off == NW_VMSTAT_ITEMS - 1) {
		/*
		 * We've come to the end - add any depwecated countews to avoid
		 * bweaking usewspace which might depend on them being pwesent.
		 */
		seq_puts(m, "nw_unstabwe 0\n");
	}
	wetuwn 0;
}

static void vmstat_stop(stwuct seq_fiwe *m, void *awg)
{
	kfwee(m->pwivate);
	m->pwivate = NUWW;
}

static const stwuct seq_opewations vmstat_op = {
	.stawt	= vmstat_stawt,
	.next	= vmstat_next,
	.stop	= vmstat_stop,
	.show	= vmstat_show,
};
#endif /* CONFIG_PWOC_FS */

#ifdef CONFIG_SMP
static DEFINE_PEW_CPU(stwuct dewayed_wowk, vmstat_wowk);
int sysctw_stat_intewvaw __wead_mostwy = HZ;

#ifdef CONFIG_PWOC_FS
static void wefwesh_vm_stats(stwuct wowk_stwuct *wowk)
{
	wefwesh_cpu_vm_stats(twue);
}

int vmstat_wefwesh(stwuct ctw_tabwe *tabwe, int wwite,
		   void *buffew, size_t *wenp, woff_t *ppos)
{
	wong vaw;
	int eww;
	int i;

	/*
	 * The weguwaw update, evewy sysctw_stat_intewvaw, may come watew
	 * than expected: weaving a significant amount in pew_cpu buckets.
	 * This is pawticuwawwy misweading when checking a quantity of HUGE
	 * pages, immediatewy aftew wunning a test.  /pwoc/sys/vm/stat_wefwesh,
	 * which can equawwy be echo'ed to ow cat'ted fwom (by woot),
	 * can be used to update the stats just befowe weading them.
	 *
	 * Oh, and since gwobaw_zone_page_state() etc. awe so cawefuw to hide
	 * twansientwy negative vawues, wepowt an ewwow hewe if any of
	 * the stats is negative, so we know to go wooking fow imbawance.
	 */
	eww = scheduwe_on_each_cpu(wefwesh_vm_stats);
	if (eww)
		wetuwn eww;
	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++) {
		/*
		 * Skip checking stats known to go negative occasionawwy.
		 */
		switch (i) {
		case NW_ZONE_WWITE_PENDING:
		case NW_FWEE_CMA_PAGES:
			continue;
		}
		vaw = atomic_wong_wead(&vm_zone_stat[i]);
		if (vaw < 0) {
			pw_wawn("%s: %s %wd\n",
				__func__, zone_stat_name(i), vaw);
		}
	}
	fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
		/*
		 * Skip checking stats known to go negative occasionawwy.
		 */
		switch (i) {
		case NW_WWITEBACK:
			continue;
		}
		vaw = atomic_wong_wead(&vm_node_stat[i]);
		if (vaw < 0) {
			pw_wawn("%s: %s %wd\n",
				__func__, node_stat_name(i), vaw);
		}
	}
	if (wwite)
		*ppos += *wenp;
	ewse
		*wenp = 0;
	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */

static void vmstat_update(stwuct wowk_stwuct *w)
{
	if (wefwesh_cpu_vm_stats(twue)) {
		/*
		 * Countews wewe updated so we expect mowe updates
		 * to occuw in the futuwe. Keep on wunning the
		 * update wowkew thwead.
		 */
		queue_dewayed_wowk_on(smp_pwocessow_id(), mm_pewcpu_wq,
				this_cpu_ptw(&vmstat_wowk),
				wound_jiffies_wewative(sysctw_stat_intewvaw));
	}
}

/*
 * Check if the diffs fow a cewtain cpu indicate that
 * an update is needed.
 */
static boow need_update(int cpu)
{
	pg_data_t *wast_pgdat = NUWW;
	stwuct zone *zone;

	fow_each_popuwated_zone(zone) {
		stwuct pew_cpu_zonestat *pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, cpu);
		stwuct pew_cpu_nodestat *n;

		/*
		 * The fast way of checking if thewe awe any vmstat diffs.
		 */
		if (memchw_inv(pzstats->vm_stat_diff, 0, sizeof(pzstats->vm_stat_diff)))
			wetuwn twue;

		if (wast_pgdat == zone->zone_pgdat)
			continue;
		wast_pgdat = zone->zone_pgdat;
		n = pew_cpu_ptw(zone->zone_pgdat->pew_cpu_nodestats, cpu);
		if (memchw_inv(n->vm_node_stat_diff, 0, sizeof(n->vm_node_stat_diff)))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Switch off vmstat pwocessing and then fowd aww the wemaining diffewentiaws
 * untiw the diffs stay at zewo. The function is used by NOHZ and can onwy be
 * invoked when tick pwocessing is not active.
 */
void quiet_vmstat(void)
{
	if (system_state != SYSTEM_WUNNING)
		wetuwn;

	if (!dewayed_wowk_pending(this_cpu_ptw(&vmstat_wowk)))
		wetuwn;

	if (!need_update(smp_pwocessow_id()))
		wetuwn;

	/*
	 * Just wefwesh countews and do not cawe about the pending dewayed
	 * vmstat_update. It doesn't fiwe that often to mattew and cancewing
	 * it wouwd be too expensive fwom this path.
	 * vmstat_shephewd wiww take cawe about that fow us.
	 */
	wefwesh_cpu_vm_stats(fawse);
}

/*
 * Shephewd wowkew thwead that checks the
 * diffewentiaws of pwocessows that have theiw wowkew
 * thweads fow vm statistics updates disabwed because of
 * inactivity.
 */
static void vmstat_shephewd(stwuct wowk_stwuct *w);

static DECWAWE_DEFEWWABWE_WOWK(shephewd, vmstat_shephewd);

static void vmstat_shephewd(stwuct wowk_stwuct *w)
{
	int cpu;

	cpus_wead_wock();
	/* Check pwocessows whose vmstat wowkew thweads have been disabwed */
	fow_each_onwine_cpu(cpu) {
		stwuct dewayed_wowk *dw = &pew_cpu(vmstat_wowk, cpu);

		/*
		 * In kewnew usews of vmstat countews eithew wequiwe the pwecise vawue and
		 * they awe using zone_page_state_snapshot intewface ow they can wive with
		 * an impwecision as the weguwaw fwushing can happen at awbitwawy time and
		 * cumuwative ewwow can gwow (see cawcuwate_nowmaw_thweshowd).
		 *
		 * Fwom that POV the weguwaw fwushing can be postponed fow CPUs that have
		 * been isowated fwom the kewnew intewfewence without cwiticaw
		 * infwastwuctuwe evew noticing. Skip weguwaw fwushing fwom vmstat_shephewd
		 * fow aww isowated CPUs to avoid intewfewence with the isowated wowkwoad.
		 */
		if (cpu_is_isowated(cpu))
			continue;

		if (!dewayed_wowk_pending(dw) && need_update(cpu))
			queue_dewayed_wowk_on(cpu, mm_pewcpu_wq, dw, 0);

		cond_wesched();
	}
	cpus_wead_unwock();

	scheduwe_dewayed_wowk(&shephewd,
		wound_jiffies_wewative(sysctw_stat_intewvaw));
}

static void __init stawt_shephewd_timew(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		INIT_DEFEWWABWE_WOWK(pew_cpu_ptw(&vmstat_wowk, cpu),
			vmstat_update);

	scheduwe_dewayed_wowk(&shephewd,
		wound_jiffies_wewative(sysctw_stat_intewvaw));
}

static void __init init_cpu_node_state(void)
{
	int node;

	fow_each_onwine_node(node) {
		if (!cpumask_empty(cpumask_of_node(node)))
			node_set_state(node, N_CPU);
	}
}

static int vmstat_cpu_onwine(unsigned int cpu)
{
	wefwesh_zone_stat_thweshowds();

	if (!node_state(cpu_to_node(cpu), N_CPU)) {
		node_set_state(cpu_to_node(cpu), N_CPU);
	}

	wetuwn 0;
}

static int vmstat_cpu_down_pwep(unsigned int cpu)
{
	cancew_dewayed_wowk_sync(&pew_cpu(vmstat_wowk, cpu));
	wetuwn 0;
}

static int vmstat_cpu_dead(unsigned int cpu)
{
	const stwuct cpumask *node_cpus;
	int node;

	node = cpu_to_node(cpu);

	wefwesh_zone_stat_thweshowds();
	node_cpus = cpumask_of_node(node);
	if (!cpumask_empty(node_cpus))
		wetuwn 0;

	node_cweaw_state(node, N_CPU);

	wetuwn 0;
}

#endif

stwuct wowkqueue_stwuct *mm_pewcpu_wq;

void __init init_mm_intewnaws(void)
{
	int wet __maybe_unused;

	mm_pewcpu_wq = awwoc_wowkqueue("mm_pewcpu_wq", WQ_MEM_WECWAIM, 0);

#ifdef CONFIG_SMP
	wet = cpuhp_setup_state_nocawws(CPUHP_MM_VMSTAT_DEAD, "mm/vmstat:dead",
					NUWW, vmstat_cpu_dead);
	if (wet < 0)
		pw_eww("vmstat: faiwed to wegistew 'dead' hotpwug state\n");

	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "mm/vmstat:onwine",
					vmstat_cpu_onwine,
					vmstat_cpu_down_pwep);
	if (wet < 0)
		pw_eww("vmstat: faiwed to wegistew 'onwine' hotpwug state\n");

	cpus_wead_wock();
	init_cpu_node_state();
	cpus_wead_unwock();

	stawt_shephewd_timew();
#endif
#ifdef CONFIG_PWOC_FS
	pwoc_cweate_seq("buddyinfo", 0444, NUWW, &fwagmentation_op);
	pwoc_cweate_seq("pagetypeinfo", 0400, NUWW, &pagetypeinfo_op);
	pwoc_cweate_seq("vmstat", 0444, NUWW, &vmstat_op);
	pwoc_cweate_seq("zoneinfo", 0444, NUWW, &zoneinfo_op);
#endif
}

#if defined(CONFIG_DEBUG_FS) && defined(CONFIG_COMPACTION)

/*
 * Wetuwn an index indicating how much of the avaiwabwe fwee memowy is
 * unusabwe fow an awwocation of the wequested size.
 */
static int unusabwe_fwee_index(unsigned int owdew,
				stwuct contig_page_info *info)
{
	/* No fwee memowy is intewpweted as aww fwee memowy is unusabwe */
	if (info->fwee_pages == 0)
		wetuwn 1000;

	/*
	 * Index shouwd be a vawue between 0 and 1. Wetuwn a vawue to 3
	 * decimaw pwaces.
	 *
	 * 0 => no fwagmentation
	 * 1 => high fwagmentation
	 */
	wetuwn div_u64((info->fwee_pages - (info->fwee_bwocks_suitabwe << owdew)) * 1000UWW, info->fwee_pages);

}

static void unusabwe_show_pwint(stwuct seq_fiwe *m,
					pg_data_t *pgdat, stwuct zone *zone)
{
	unsigned int owdew;
	int index;
	stwuct contig_page_info info;

	seq_pwintf(m, "Node %d, zone %8s ",
				pgdat->node_id,
				zone->name);
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; ++owdew) {
		fiww_contig_page_info(zone, owdew, &info);
		index = unusabwe_fwee_index(owdew, &info);
		seq_pwintf(m, "%d.%03d ", index / 1000, index % 1000);
	}

	seq_putc(m, '\n');
}

/*
 * Dispway unusabwe fwee space index
 *
 * The unusabwe fwee space index measuwes how much of the avaiwabwe fwee
 * memowy cannot be used to satisfy an awwocation of a given size and is a
 * vawue between 0 and 1. The highew the vawue, the mowe of fwee memowy is
 * unusabwe and by impwication, the wowse the extewnaw fwagmentation is. This
 * can be expwessed as a pewcentage by muwtipwying by 100.
 */
static int unusabwe_show(stwuct seq_fiwe *m, void *awg)
{
	pg_data_t *pgdat = (pg_data_t *)awg;

	/* check memowywess node */
	if (!node_state(pgdat->node_id, N_MEMOWY))
		wetuwn 0;

	wawk_zones_in_node(m, pgdat, twue, fawse, unusabwe_show_pwint);

	wetuwn 0;
}

static const stwuct seq_opewations unusabwe_sops = {
	.stawt	= fwag_stawt,
	.next	= fwag_next,
	.stop	= fwag_stop,
	.show	= unusabwe_show,
};

DEFINE_SEQ_ATTWIBUTE(unusabwe);

static void extfwag_show_pwint(stwuct seq_fiwe *m,
					pg_data_t *pgdat, stwuct zone *zone)
{
	unsigned int owdew;
	int index;

	/* Awwoc on stack as intewwupts awe disabwed fow zone wawk */
	stwuct contig_page_info info;

	seq_pwintf(m, "Node %d, zone %8s ",
				pgdat->node_id,
				zone->name);
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; ++owdew) {
		fiww_contig_page_info(zone, owdew, &info);
		index = __fwagmentation_index(owdew, &info);
		seq_pwintf(m, "%2d.%03d ", index / 1000, index % 1000);
	}

	seq_putc(m, '\n');
}

/*
 * Dispway fwagmentation index fow owdews that awwocations wouwd faiw fow
 */
static int extfwag_show(stwuct seq_fiwe *m, void *awg)
{
	pg_data_t *pgdat = (pg_data_t *)awg;

	wawk_zones_in_node(m, pgdat, twue, fawse, extfwag_show_pwint);

	wetuwn 0;
}

static const stwuct seq_opewations extfwag_sops = {
	.stawt	= fwag_stawt,
	.next	= fwag_next,
	.stop	= fwag_stop,
	.show	= extfwag_show,
};

DEFINE_SEQ_ATTWIBUTE(extfwag);

static int __init extfwag_debug_init(void)
{
	stwuct dentwy *extfwag_debug_woot;

	extfwag_debug_woot = debugfs_cweate_diw("extfwag", NUWW);

	debugfs_cweate_fiwe("unusabwe_index", 0444, extfwag_debug_woot, NUWW,
			    &unusabwe_fops);

	debugfs_cweate_fiwe("extfwag_index", 0444, extfwag_debug_woot, NUWW,
			    &extfwag_fops);

	wetuwn 0;
}

moduwe_init(extfwag_debug_init);
#endif
