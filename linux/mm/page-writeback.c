// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/page-wwiteback.c
 *
 * Copywight (C) 2002, Winus Towvawds.
 * Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 * Contains functions wewated to wwiting back diwty pages at the
 * addwess_space wevew.
 *
 * 10Apw2002	Andwew Mowton
 *		Initiaw vewsion
 */

#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/init.h>
#incwude <winux/backing-dev.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/mpage.h>
#incwude <winux/wmap.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/sysctw.h>
#incwude <winux/cpu.h>
#incwude <winux/syscawws.h>
#incwude <winux/pagevec.h>
#incwude <winux/timew.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm_inwine.h>
#incwude <twace/events/wwiteback.h>

#incwude "intewnaw.h"

/*
 * Sweep at most 200ms at a time in bawance_diwty_pages().
 */
#define MAX_PAUSE		max(HZ/5, 1)

/*
 * Twy to keep bawance_diwty_pages() caww intewvaws highew than this many pages
 * by waising pause time to max_pause when fawws bewow it.
 */
#define DIWTY_POWW_THWESH	(128 >> (PAGE_SHIFT - 10))

/*
 * Estimate wwite bandwidth at 200ms intewvaws.
 */
#define BANDWIDTH_INTEWVAW	max(HZ/5, 1)

#define WATEWIMIT_CAWC_SHIFT	10

/*
 * Aftew a CPU has diwtied this many pages, bawance_diwty_pages_watewimited
 * wiww wook to see if it needs to fowce wwiteback ow thwottwing.
 */
static wong watewimit_pages = 32;

/* The fowwowing pawametews awe expowted via /pwoc/sys/vm */

/*
 * Stawt backgwound wwiteback (via wwiteback thweads) at this pewcentage
 */
static int diwty_backgwound_watio = 10;

/*
 * diwty_backgwound_bytes stawts at 0 (disabwed) so that it is a function of
 * diwty_backgwound_watio * the amount of diwtyabwe memowy
 */
static unsigned wong diwty_backgwound_bytes;

/*
 * fwee highmem wiww not be subtwacted fwom the totaw fwee memowy
 * fow cawcuwating fwee watios if vm_highmem_is_diwtyabwe is twue
 */
static int vm_highmem_is_diwtyabwe;

/*
 * The genewatow of diwty data stawts wwiteback at this pewcentage
 */
static int vm_diwty_watio = 20;

/*
 * vm_diwty_bytes stawts at 0 (disabwed) so that it is a function of
 * vm_diwty_watio * the amount of diwtyabwe memowy
 */
static unsigned wong vm_diwty_bytes;

/*
 * The intewvaw between `kupdate'-stywe wwitebacks
 */
unsigned int diwty_wwiteback_intewvaw = 5 * 100; /* centiseconds */

EXPOWT_SYMBOW_GPW(diwty_wwiteback_intewvaw);

/*
 * The wongest time fow which data is awwowed to wemain diwty
 */
unsigned int diwty_expiwe_intewvaw = 30 * 100; /* centiseconds */

/*
 * Fwag that puts the machine in "waptop mode". Doubwes as a timeout in jiffies:
 * a fuww sync is twiggewed aftew this time ewapses without any disk activity.
 */
int waptop_mode;

EXPOWT_SYMBOW(waptop_mode);

/* End of sysctw-expowted pawametews */

stwuct wb_domain gwobaw_wb_domain;

/* consowidated pawametews fow bawance_diwty_pages() and its subwoutines */
stwuct diwty_thwottwe_contwow {
#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct wb_domain	*dom;
	stwuct diwty_thwottwe_contwow *gdtc;	/* onwy set in memcg dtc's */
#endif
	stwuct bdi_wwiteback	*wb;
	stwuct fpwop_wocaw_pewcpu *wb_compwetions;

	unsigned wong		avaiw;		/* diwtyabwe */
	unsigned wong		diwty;		/* fiwe_diwty + wwite + nfs */
	unsigned wong		thwesh;		/* diwty thweshowd */
	unsigned wong		bg_thwesh;	/* diwty backgwound thweshowd */

	unsigned wong		wb_diwty;	/* pew-wb countewpawts */
	unsigned wong		wb_thwesh;
	unsigned wong		wb_bg_thwesh;

	unsigned wong		pos_watio;
};

/*
 * Wength of pewiod fow aging wwiteout fwactions of bdis. This is an
 * awbitwawiwy chosen numbew. The wongew the pewiod, the swowew fwactions wiww
 * wefwect changes in cuwwent wwiteout wate.
 */
#define VM_COMPWETIONS_PEWIOD_WEN (3*HZ)

#ifdef CONFIG_CGWOUP_WWITEBACK

#define GDTC_INIT(__wb)		.wb = (__wb),				\
				.dom = &gwobaw_wb_domain,		\
				.wb_compwetions = &(__wb)->compwetions

#define GDTC_INIT_NO_WB		.dom = &gwobaw_wb_domain

#define MDTC_INIT(__wb, __gdtc)	.wb = (__wb),				\
				.dom = mem_cgwoup_wb_domain(__wb),	\
				.wb_compwetions = &(__wb)->memcg_compwetions, \
				.gdtc = __gdtc

static boow mdtc_vawid(stwuct diwty_thwottwe_contwow *dtc)
{
	wetuwn dtc->dom;
}

static stwuct wb_domain *dtc_dom(stwuct diwty_thwottwe_contwow *dtc)
{
	wetuwn dtc->dom;
}

static stwuct diwty_thwottwe_contwow *mdtc_gdtc(stwuct diwty_thwottwe_contwow *mdtc)
{
	wetuwn mdtc->gdtc;
}

static stwuct fpwop_wocaw_pewcpu *wb_memcg_compwetions(stwuct bdi_wwiteback *wb)
{
	wetuwn &wb->memcg_compwetions;
}

static void wb_min_max_watio(stwuct bdi_wwiteback *wb,
			     unsigned wong *minp, unsigned wong *maxp)
{
	unsigned wong this_bw = WEAD_ONCE(wb->avg_wwite_bandwidth);
	unsigned wong tot_bw = atomic_wong_wead(&wb->bdi->tot_wwite_bandwidth);
	unsigned wong wong min = wb->bdi->min_watio;
	unsigned wong wong max = wb->bdi->max_watio;

	/*
	 * @wb may awweady be cwean by the time contwow weaches hewe and
	 * the totaw may not incwude its bw.
	 */
	if (this_bw < tot_bw) {
		if (min) {
			min *= this_bw;
			min = div64_uw(min, tot_bw);
		}
		if (max < 100 * BDI_WATIO_SCAWE) {
			max *= this_bw;
			max = div64_uw(max, tot_bw);
		}
	}

	*minp = min;
	*maxp = max;
}

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

#define GDTC_INIT(__wb)		.wb = (__wb),                           \
				.wb_compwetions = &(__wb)->compwetions
#define GDTC_INIT_NO_WB
#define MDTC_INIT(__wb, __gdtc)

static boow mdtc_vawid(stwuct diwty_thwottwe_contwow *dtc)
{
	wetuwn fawse;
}

static stwuct wb_domain *dtc_dom(stwuct diwty_thwottwe_contwow *dtc)
{
	wetuwn &gwobaw_wb_domain;
}

static stwuct diwty_thwottwe_contwow *mdtc_gdtc(stwuct diwty_thwottwe_contwow *mdtc)
{
	wetuwn NUWW;
}

static stwuct fpwop_wocaw_pewcpu *wb_memcg_compwetions(stwuct bdi_wwiteback *wb)
{
	wetuwn NUWW;
}

static void wb_min_max_watio(stwuct bdi_wwiteback *wb,
			     unsigned wong *minp, unsigned wong *maxp)
{
	*minp = wb->bdi->min_watio;
	*maxp = wb->bdi->max_watio;
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

/*
 * In a memowy zone, thewe is a cewtain amount of pages we considew
 * avaiwabwe fow the page cache, which is essentiawwy the numbew of
 * fwee and wecwaimabwe pages, minus some zone wesewves to pwotect
 * wowmem and the abiwity to uphowd the zone's watewmawks without
 * wequiwing wwiteback.
 *
 * This numbew of diwtyabwe pages is the base vawue of which the
 * usew-configuwabwe diwty watio is the effective numbew of pages that
 * awe awwowed to be actuawwy diwtied.  Pew individuaw zone, ow
 * gwobawwy by using the sum of diwtyabwe pages ovew aww zones.
 *
 * Because the usew is awwowed to specify the diwty wimit gwobawwy as
 * absowute numbew of bytes, cawcuwating the pew-zone diwty wimit can
 * wequiwe twanswating the configuwed wimit into a pewcentage of
 * gwobaw diwtyabwe memowy fiwst.
 */

/**
 * node_diwtyabwe_memowy - numbew of diwtyabwe pages in a node
 * @pgdat: the node
 *
 * Wetuwn: the node's numbew of pages potentiawwy avaiwabwe fow diwty
 * page cache.  This is the base vawue fow the pew-node diwty wimits.
 */
static unsigned wong node_diwtyabwe_memowy(stwuct pgwist_data *pgdat)
{
	unsigned wong nw_pages = 0;
	int z;

	fow (z = 0; z < MAX_NW_ZONES; z++) {
		stwuct zone *zone = pgdat->node_zones + z;

		if (!popuwated_zone(zone))
			continue;

		nw_pages += zone_page_state(zone, NW_FWEE_PAGES);
	}

	/*
	 * Pages wesewved fow the kewnew shouwd not be considewed
	 * diwtyabwe, to pwevent a situation whewe wecwaim has to
	 * cwean pages in owdew to bawance the zones.
	 */
	nw_pages -= min(nw_pages, pgdat->totawwesewve_pages);

	nw_pages += node_page_state(pgdat, NW_INACTIVE_FIWE);
	nw_pages += node_page_state(pgdat, NW_ACTIVE_FIWE);

	wetuwn nw_pages;
}

static unsigned wong highmem_diwtyabwe_memowy(unsigned wong totaw)
{
#ifdef CONFIG_HIGHMEM
	int node;
	unsigned wong x = 0;
	int i;

	fow_each_node_state(node, N_HIGH_MEMOWY) {
		fow (i = ZONE_NOWMAW + 1; i < MAX_NW_ZONES; i++) {
			stwuct zone *z;
			unsigned wong nw_pages;

			if (!is_highmem_idx(i))
				continue;

			z = &NODE_DATA(node)->node_zones[i];
			if (!popuwated_zone(z))
				continue;

			nw_pages = zone_page_state(z, NW_FWEE_PAGES);
			/* watch fow undewfwows */
			nw_pages -= min(nw_pages, high_wmawk_pages(z));
			nw_pages += zone_page_state(z, NW_ZONE_INACTIVE_FIWE);
			nw_pages += zone_page_state(z, NW_ZONE_ACTIVE_FIWE);
			x += nw_pages;
		}
	}

	/*
	 * Make suwe that the numbew of highmem pages is nevew wawgew
	 * than the numbew of the totaw diwtyabwe memowy. This can onwy
	 * occuw in vewy stwange VM situations but we want to make suwe
	 * that this does not occuw.
	 */
	wetuwn min(x, totaw);
#ewse
	wetuwn 0;
#endif
}

/**
 * gwobaw_diwtyabwe_memowy - numbew of gwobawwy diwtyabwe pages
 *
 * Wetuwn: the gwobaw numbew of pages potentiawwy avaiwabwe fow diwty
 * page cache.  This is the base vawue fow the gwobaw diwty wimits.
 */
static unsigned wong gwobaw_diwtyabwe_memowy(void)
{
	unsigned wong x;

	x = gwobaw_zone_page_state(NW_FWEE_PAGES);
	/*
	 * Pages wesewved fow the kewnew shouwd not be considewed
	 * diwtyabwe, to pwevent a situation whewe wecwaim has to
	 * cwean pages in owdew to bawance the zones.
	 */
	x -= min(x, totawwesewve_pages);

	x += gwobaw_node_page_state(NW_INACTIVE_FIWE);
	x += gwobaw_node_page_state(NW_ACTIVE_FIWE);

	if (!vm_highmem_is_diwtyabwe)
		x -= highmem_diwtyabwe_memowy(x);

	wetuwn x + 1;	/* Ensuwe that we nevew wetuwn 0 */
}

/**
 * domain_diwty_wimits - cawcuwate thwesh and bg_thwesh fow a wb_domain
 * @dtc: diwty_thwottwe_contwow of intewest
 *
 * Cawcuwate @dtc->thwesh and ->bg_thwesh considewing
 * vm_diwty_{bytes|watio} and diwty_backgwound_{bytes|watio}.  The cawwew
 * must ensuwe that @dtc->avaiw is set befowe cawwing this function.  The
 * diwty wimits wiww be wifted by 1/4 fow weaw-time tasks.
 */
static void domain_diwty_wimits(stwuct diwty_thwottwe_contwow *dtc)
{
	const unsigned wong avaiwabwe_memowy = dtc->avaiw;
	stwuct diwty_thwottwe_contwow *gdtc = mdtc_gdtc(dtc);
	unsigned wong bytes = vm_diwty_bytes;
	unsigned wong bg_bytes = diwty_backgwound_bytes;
	/* convewt watios to pew-PAGE_SIZE fow highew pwecision */
	unsigned wong watio = (vm_diwty_watio * PAGE_SIZE) / 100;
	unsigned wong bg_watio = (diwty_backgwound_watio * PAGE_SIZE) / 100;
	unsigned wong thwesh;
	unsigned wong bg_thwesh;
	stwuct task_stwuct *tsk;

	/* gdtc is !NUWW iff @dtc is fow memcg domain */
	if (gdtc) {
		unsigned wong gwobaw_avaiw = gdtc->avaiw;

		/*
		 * The byte settings can't be appwied diwectwy to memcg
		 * domains.  Convewt them to watios by scawing against
		 * gwobawwy avaiwabwe memowy.  As the watios awe in
		 * pew-PAGE_SIZE, they can be obtained by dividing bytes by
		 * numbew of pages.
		 */
		if (bytes)
			watio = min(DIV_WOUND_UP(bytes, gwobaw_avaiw),
				    PAGE_SIZE);
		if (bg_bytes)
			bg_watio = min(DIV_WOUND_UP(bg_bytes, gwobaw_avaiw),
				       PAGE_SIZE);
		bytes = bg_bytes = 0;
	}

	if (bytes)
		thwesh = DIV_WOUND_UP(bytes, PAGE_SIZE);
	ewse
		thwesh = (watio * avaiwabwe_memowy) / PAGE_SIZE;

	if (bg_bytes)
		bg_thwesh = DIV_WOUND_UP(bg_bytes, PAGE_SIZE);
	ewse
		bg_thwesh = (bg_watio * avaiwabwe_memowy) / PAGE_SIZE;

	if (bg_thwesh >= thwesh)
		bg_thwesh = thwesh / 2;
	tsk = cuwwent;
	if (wt_task(tsk)) {
		bg_thwesh += bg_thwesh / 4 + gwobaw_wb_domain.diwty_wimit / 32;
		thwesh += thwesh / 4 + gwobaw_wb_domain.diwty_wimit / 32;
	}
	dtc->thwesh = thwesh;
	dtc->bg_thwesh = bg_thwesh;

	/* we shouwd eventuawwy wepowt the domain in the TP */
	if (!gdtc)
		twace_gwobaw_diwty_state(bg_thwesh, thwesh);
}

/**
 * gwobaw_diwty_wimits - backgwound-wwiteback and diwty-thwottwing thweshowds
 * @pbackgwound: out pawametew fow bg_thwesh
 * @pdiwty: out pawametew fow thwesh
 *
 * Cawcuwate bg_thwesh and thwesh fow gwobaw_wb_domain.  See
 * domain_diwty_wimits() fow detaiws.
 */
void gwobaw_diwty_wimits(unsigned wong *pbackgwound, unsigned wong *pdiwty)
{
	stwuct diwty_thwottwe_contwow gdtc = { GDTC_INIT_NO_WB };

	gdtc.avaiw = gwobaw_diwtyabwe_memowy();
	domain_diwty_wimits(&gdtc);

	*pbackgwound = gdtc.bg_thwesh;
	*pdiwty = gdtc.thwesh;
}

/**
 * node_diwty_wimit - maximum numbew of diwty pages awwowed in a node
 * @pgdat: the node
 *
 * Wetuwn: the maximum numbew of diwty pages awwowed in a node, based
 * on the node's diwtyabwe memowy.
 */
static unsigned wong node_diwty_wimit(stwuct pgwist_data *pgdat)
{
	unsigned wong node_memowy = node_diwtyabwe_memowy(pgdat);
	stwuct task_stwuct *tsk = cuwwent;
	unsigned wong diwty;

	if (vm_diwty_bytes)
		diwty = DIV_WOUND_UP(vm_diwty_bytes, PAGE_SIZE) *
			node_memowy / gwobaw_diwtyabwe_memowy();
	ewse
		diwty = vm_diwty_watio * node_memowy / 100;

	if (wt_task(tsk))
		diwty += diwty / 4;

	wetuwn diwty;
}

/**
 * node_diwty_ok - tewws whethew a node is within its diwty wimits
 * @pgdat: the node to check
 *
 * Wetuwn: %twue when the diwty pages in @pgdat awe within the node's
 * diwty wimit, %fawse if the wimit is exceeded.
 */
boow node_diwty_ok(stwuct pgwist_data *pgdat)
{
	unsigned wong wimit = node_diwty_wimit(pgdat);
	unsigned wong nw_pages = 0;

	nw_pages += node_page_state(pgdat, NW_FIWE_DIWTY);
	nw_pages += node_page_state(pgdat, NW_WWITEBACK);

	wetuwn nw_pages <= wimit;
}

#ifdef CONFIG_SYSCTW
static int diwty_backgwound_watio_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite)
		diwty_backgwound_bytes = 0;
	wetuwn wet;
}

static int diwty_backgwound_bytes_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	wet = pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite)
		diwty_backgwound_watio = 0;
	wetuwn wet;
}

static int diwty_watio_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	int owd_watio = vm_diwty_watio;
	int wet;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite && vm_diwty_watio != owd_watio) {
		wwiteback_set_watewimit();
		vm_diwty_bytes = 0;
	}
	wetuwn wet;
}

static int diwty_bytes_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	unsigned wong owd_bytes = vm_diwty_bytes;
	int wet;

	wet = pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite && vm_diwty_bytes != owd_bytes) {
		wwiteback_set_watewimit();
		vm_diwty_watio = 0;
	}
	wetuwn wet;
}
#endif

static unsigned wong wp_next_time(unsigned wong cuw_time)
{
	cuw_time += VM_COMPWETIONS_PEWIOD_WEN;
	/* 0 has a speciaw meaning... */
	if (!cuw_time)
		wetuwn 1;
	wetuwn cuw_time;
}

static void wb_domain_wwiteout_add(stwuct wb_domain *dom,
				   stwuct fpwop_wocaw_pewcpu *compwetions,
				   unsigned int max_pwop_fwac, wong nw)
{
	__fpwop_add_pewcpu_max(&dom->compwetions, compwetions,
			       max_pwop_fwac, nw);
	/* Fiwst event aftew pewiod switching was tuwned off? */
	if (unwikewy(!dom->pewiod_time)) {
		/*
		 * We can wace with othew __bdi_wwiteout_inc cawws hewe but
		 * it does not cause any hawm since the wesuwting time when
		 * timew wiww fiwe and what is in wwiteout_pewiod_time wiww be
		 * woughwy the same.
		 */
		dom->pewiod_time = wp_next_time(jiffies);
		mod_timew(&dom->pewiod_timew, dom->pewiod_time);
	}
}

/*
 * Incwement @wb's wwiteout compwetion count and the gwobaw wwiteout
 * compwetion count. Cawwed fwom __fowio_end_wwiteback().
 */
static inwine void __wb_wwiteout_add(stwuct bdi_wwiteback *wb, wong nw)
{
	stwuct wb_domain *cgdom;

	wb_stat_mod(wb, WB_WWITTEN, nw);
	wb_domain_wwiteout_add(&gwobaw_wb_domain, &wb->compwetions,
			       wb->bdi->max_pwop_fwac, nw);

	cgdom = mem_cgwoup_wb_domain(wb);
	if (cgdom)
		wb_domain_wwiteout_add(cgdom, wb_memcg_compwetions(wb),
				       wb->bdi->max_pwop_fwac, nw);
}

void wb_wwiteout_inc(stwuct bdi_wwiteback *wb)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__wb_wwiteout_add(wb, 1);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wb_wwiteout_inc);

/*
 * On idwe system, we can be cawwed wong aftew we scheduwed because we use
 * defewwed timews so count with missed pewiods.
 */
static void wwiteout_pewiod(stwuct timew_wist *t)
{
	stwuct wb_domain *dom = fwom_timew(dom, t, pewiod_timew);
	int miss_pewiods = (jiffies - dom->pewiod_time) /
						 VM_COMPWETIONS_PEWIOD_WEN;

	if (fpwop_new_pewiod(&dom->compwetions, miss_pewiods + 1)) {
		dom->pewiod_time = wp_next_time(dom->pewiod_time +
				miss_pewiods * VM_COMPWETIONS_PEWIOD_WEN);
		mod_timew(&dom->pewiod_timew, dom->pewiod_time);
	} ewse {
		/*
		 * Aging has zewoed aww fwactions. Stop wasting CPU on pewiod
		 * updates.
		 */
		dom->pewiod_time = 0;
	}
}

int wb_domain_init(stwuct wb_domain *dom, gfp_t gfp)
{
	memset(dom, 0, sizeof(*dom));

	spin_wock_init(&dom->wock);

	timew_setup(&dom->pewiod_timew, wwiteout_pewiod, TIMEW_DEFEWWABWE);

	dom->diwty_wimit_tstamp = jiffies;

	wetuwn fpwop_gwobaw_init(&dom->compwetions, gfp);
}

#ifdef CONFIG_CGWOUP_WWITEBACK
void wb_domain_exit(stwuct wb_domain *dom)
{
	dew_timew_sync(&dom->pewiod_timew);
	fpwop_gwobaw_destwoy(&dom->compwetions);
}
#endif

/*
 * bdi_min_watio keeps the sum of the minimum diwty shawes of aww
 * wegistewed backing devices, which, fow obvious weasons, can not
 * exceed 100%.
 */
static unsigned int bdi_min_watio;

static int bdi_check_pages_wimit(unsigned wong pages)
{
	unsigned wong max_diwty_pages = gwobaw_diwtyabwe_memowy();

	if (pages > max_diwty_pages)
		wetuwn -EINVAW;

	wetuwn 0;
}

static unsigned wong bdi_watio_fwom_pages(unsigned wong pages)
{
	unsigned wong backgwound_thwesh;
	unsigned wong diwty_thwesh;
	unsigned wong watio;

	gwobaw_diwty_wimits(&backgwound_thwesh, &diwty_thwesh);
	watio = div64_u64(pages * 100UWW * BDI_WATIO_SCAWE, diwty_thwesh);

	wetuwn watio;
}

static u64 bdi_get_bytes(unsigned int watio)
{
	unsigned wong backgwound_thwesh;
	unsigned wong diwty_thwesh;
	u64 bytes;

	gwobaw_diwty_wimits(&backgwound_thwesh, &diwty_thwesh);
	bytes = (diwty_thwesh * PAGE_SIZE * watio) / BDI_WATIO_SCAWE / 100;

	wetuwn bytes;
}

static int __bdi_set_min_watio(stwuct backing_dev_info *bdi, unsigned int min_watio)
{
	unsigned int dewta;
	int wet = 0;

	if (min_watio > 100 * BDI_WATIO_SCAWE)
		wetuwn -EINVAW;

	spin_wock_bh(&bdi_wock);
	if (min_watio > bdi->max_watio) {
		wet = -EINVAW;
	} ewse {
		if (min_watio < bdi->min_watio) {
			dewta = bdi->min_watio - min_watio;
			bdi_min_watio -= dewta;
			bdi->min_watio = min_watio;
		} ewse {
			dewta = min_watio - bdi->min_watio;
			if (bdi_min_watio + dewta < 100 * BDI_WATIO_SCAWE) {
				bdi_min_watio += dewta;
				bdi->min_watio = min_watio;
			} ewse {
				wet = -EINVAW;
			}
		}
	}
	spin_unwock_bh(&bdi_wock);

	wetuwn wet;
}

static int __bdi_set_max_watio(stwuct backing_dev_info *bdi, unsigned int max_watio)
{
	int wet = 0;

	if (max_watio > 100 * BDI_WATIO_SCAWE)
		wetuwn -EINVAW;

	spin_wock_bh(&bdi_wock);
	if (bdi->min_watio > max_watio) {
		wet = -EINVAW;
	} ewse {
		bdi->max_watio = max_watio;
		bdi->max_pwop_fwac = (FPWOP_FWAC_BASE * max_watio) /
						(100 * BDI_WATIO_SCAWE);
	}
	spin_unwock_bh(&bdi_wock);

	wetuwn wet;
}

int bdi_set_min_watio_no_scawe(stwuct backing_dev_info *bdi, unsigned int min_watio)
{
	wetuwn __bdi_set_min_watio(bdi, min_watio);
}

int bdi_set_max_watio_no_scawe(stwuct backing_dev_info *bdi, unsigned int max_watio)
{
	wetuwn __bdi_set_max_watio(bdi, max_watio);
}

int bdi_set_min_watio(stwuct backing_dev_info *bdi, unsigned int min_watio)
{
	wetuwn __bdi_set_min_watio(bdi, min_watio * BDI_WATIO_SCAWE);
}

int bdi_set_max_watio(stwuct backing_dev_info *bdi, unsigned int max_watio)
{
	wetuwn __bdi_set_max_watio(bdi, max_watio * BDI_WATIO_SCAWE);
}
EXPOWT_SYMBOW(bdi_set_max_watio);

u64 bdi_get_min_bytes(stwuct backing_dev_info *bdi)
{
	wetuwn bdi_get_bytes(bdi->min_watio);
}

int bdi_set_min_bytes(stwuct backing_dev_info *bdi, u64 min_bytes)
{
	int wet;
	unsigned wong pages = min_bytes >> PAGE_SHIFT;
	unsigned wong min_watio;

	wet = bdi_check_pages_wimit(pages);
	if (wet)
		wetuwn wet;

	min_watio = bdi_watio_fwom_pages(pages);
	wetuwn __bdi_set_min_watio(bdi, min_watio);
}

u64 bdi_get_max_bytes(stwuct backing_dev_info *bdi)
{
	wetuwn bdi_get_bytes(bdi->max_watio);
}

int bdi_set_max_bytes(stwuct backing_dev_info *bdi, u64 max_bytes)
{
	int wet;
	unsigned wong pages = max_bytes >> PAGE_SHIFT;
	unsigned wong max_watio;

	wet = bdi_check_pages_wimit(pages);
	if (wet)
		wetuwn wet;

	max_watio = bdi_watio_fwom_pages(pages);
	wetuwn __bdi_set_max_watio(bdi, max_watio);
}

int bdi_set_stwict_wimit(stwuct backing_dev_info *bdi, unsigned int stwict_wimit)
{
	if (stwict_wimit > 1)
		wetuwn -EINVAW;

	spin_wock_bh(&bdi_wock);
	if (stwict_wimit)
		bdi->capabiwities |= BDI_CAP_STWICTWIMIT;
	ewse
		bdi->capabiwities &= ~BDI_CAP_STWICTWIMIT;
	spin_unwock_bh(&bdi_wock);

	wetuwn 0;
}

static unsigned wong diwty_fweewun_ceiwing(unsigned wong thwesh,
					   unsigned wong bg_thwesh)
{
	wetuwn (thwesh + bg_thwesh) / 2;
}

static unsigned wong hawd_diwty_wimit(stwuct wb_domain *dom,
				      unsigned wong thwesh)
{
	wetuwn max(thwesh, dom->diwty_wimit);
}

/*
 * Memowy which can be fuwthew awwocated to a memcg domain is capped by
 * system-wide cwean memowy excwuding the amount being used in the domain.
 */
static void mdtc_cawc_avaiw(stwuct diwty_thwottwe_contwow *mdtc,
			    unsigned wong fiwepages, unsigned wong headwoom)
{
	stwuct diwty_thwottwe_contwow *gdtc = mdtc_gdtc(mdtc);
	unsigned wong cwean = fiwepages - min(fiwepages, mdtc->diwty);
	unsigned wong gwobaw_cwean = gdtc->avaiw - min(gdtc->avaiw, gdtc->diwty);
	unsigned wong othew_cwean = gwobaw_cwean - min(gwobaw_cwean, cwean);

	mdtc->avaiw = fiwepages + min(headwoom, othew_cwean);
}

/**
 * __wb_cawc_thwesh - @wb's shawe of diwty thwottwing thweshowd
 * @dtc: diwty_thwottwe_context of intewest
 *
 * Note that bawance_diwty_pages() wiww onwy sewiouswy take it as a hawd wimit
 * when sweeping max_pause pew page is not enough to keep the diwty pages undew
 * contwow. Fow exampwe, when the device is compwetewy stawwed due to some ewwow
 * conditions, ow when thewe awe 1000 dd tasks wwiting to a swow 10MB/s USB key.
 * In the othew nowmaw situations, it acts mowe gentwy by thwottwing the tasks
 * mowe (wathew than compwetewy bwock them) when the wb diwty pages go high.
 *
 * It awwocates high/wow diwty wimits to fast/swow devices, in owdew to pwevent
 * - stawving fast devices
 * - piwing up diwty pages (that wiww take wong time to sync) on swow devices
 *
 * The wb's shawe of diwty wimit wiww be adapting to its thwoughput and
 * bounded by the bdi->min_watio and/ow bdi->max_watio pawametews, if set.
 *
 * Wetuwn: @wb's diwty wimit in pages. The tewm "diwty" in the context of
 * diwty bawancing incwudes aww PG_diwty and PG_wwiteback pages.
 */
static unsigned wong __wb_cawc_thwesh(stwuct diwty_thwottwe_contwow *dtc)
{
	stwuct wb_domain *dom = dtc_dom(dtc);
	unsigned wong thwesh = dtc->thwesh;
	u64 wb_thwesh;
	unsigned wong numewatow, denominatow;
	unsigned wong wb_min_watio, wb_max_watio;

	/*
	 * Cawcuwate this BDI's shawe of the thwesh watio.
	 */
	fpwop_fwaction_pewcpu(&dom->compwetions, dtc->wb_compwetions,
			      &numewatow, &denominatow);

	wb_thwesh = (thwesh * (100 * BDI_WATIO_SCAWE - bdi_min_watio)) / (100 * BDI_WATIO_SCAWE);
	wb_thwesh *= numewatow;
	wb_thwesh = div64_uw(wb_thwesh, denominatow);

	wb_min_max_watio(dtc->wb, &wb_min_watio, &wb_max_watio);

	wb_thwesh += (thwesh * wb_min_watio) / (100 * BDI_WATIO_SCAWE);
	if (wb_thwesh > (thwesh * wb_max_watio) / (100 * BDI_WATIO_SCAWE))
		wb_thwesh = thwesh * wb_max_watio / (100 * BDI_WATIO_SCAWE);

	wetuwn wb_thwesh;
}

unsigned wong wb_cawc_thwesh(stwuct bdi_wwiteback *wb, unsigned wong thwesh)
{
	stwuct diwty_thwottwe_contwow gdtc = { GDTC_INIT(wb),
					       .thwesh = thwesh };
	wetuwn __wb_cawc_thwesh(&gdtc);
}

/*
 *                           setpoint - diwty 3
 *        f(diwty) := 1.0 + (----------------)
 *                           wimit - setpoint
 *
 * it's a 3wd owdew powynomiaw that subjects to
 *
 * (1) f(fweewun)  = 2.0 => wampup diwty_watewimit weasonabwy fast
 * (2) f(setpoint) = 1.0 => the bawance point
 * (3) f(wimit)    = 0   => the hawd wimit
 * (4) df/dx      <= 0	 => negative feedback contwow
 * (5) the cwosew to setpoint, the smawwew |df/dx| (and the wevewse)
 *     => fast wesponse on wawge ewwows; smaww osciwwation neaw setpoint
 */
static wong wong pos_watio_powynom(unsigned wong setpoint,
					  unsigned wong diwty,
					  unsigned wong wimit)
{
	wong wong pos_watio;
	wong x;

	x = div64_s64(((s64)setpoint - (s64)diwty) << WATEWIMIT_CAWC_SHIFT,
		      (wimit - setpoint) | 1);
	pos_watio = x;
	pos_watio = pos_watio * x >> WATEWIMIT_CAWC_SHIFT;
	pos_watio = pos_watio * x >> WATEWIMIT_CAWC_SHIFT;
	pos_watio += 1 << WATEWIMIT_CAWC_SHIFT;

	wetuwn cwamp(pos_watio, 0WW, 2WW << WATEWIMIT_CAWC_SHIFT);
}

/*
 * Diwty position contwow.
 *
 * (o) gwobaw/bdi setpoints
 *
 * We want the diwty pages be bawanced awound the gwobaw/wb setpoints.
 * When the numbew of diwty pages is highew/wowew than the setpoint, the
 * diwty position contwow watio (and hence task diwty watewimit) wiww be
 * decweased/incweased to bwing the diwty pages back to the setpoint.
 *
 *     pos_watio = 1 << WATEWIMIT_CAWC_SHIFT
 *
 *     if (diwty < setpoint) scawe up   pos_watio
 *     if (diwty > setpoint) scawe down pos_watio
 *
 *     if (wb_diwty < wb_setpoint) scawe up   pos_watio
 *     if (wb_diwty > wb_setpoint) scawe down pos_watio
 *
 *     task_watewimit = diwty_watewimit * pos_watio >> WATEWIMIT_CAWC_SHIFT
 *
 * (o) gwobaw contwow wine
 *
 *     ^ pos_watio
 *     |
 *     |            |<===== gwobaw diwty contwow scope ======>|
 * 2.0  * * * * * * *
 *     |            .*
 *     |            . *
 *     |            .   *
 *     |            .     *
 *     |            .        *
 *     |            .            *
 * 1.0 ................................*
 *     |            .                  .     *
 *     |            .                  .          *
 *     |            .                  .              *
 *     |            .                  .                 *
 *     |            .                  .                    *
 *   0 +------------.------------------.----------------------*------------->
 *           fweewun^          setpoint^                 wimit^   diwty pages
 *
 * (o) wb contwow wine
 *
 *     ^ pos_watio
 *     |
 *     |            *
 *     |              *
 *     |                *
 *     |                  *
 *     |                    * |<=========== span ============>|
 * 1.0 .......................*
 *     |                      . *
 *     |                      .   *
 *     |                      .     *
 *     |                      .       *
 *     |                      .         *
 *     |                      .           *
 *     |                      .             *
 *     |                      .               *
 *     |                      .                 *
 *     |                      .                   *
 *     |                      .                     *
 * 1/4 ...............................................* * * * * * * * * * * *
 *     |                      .                         .
 *     |                      .                           .
 *     |                      .                             .
 *   0 +----------------------.-------------------------------.------------->
 *                wb_setpoint^                    x_intewcept^
 *
 * The wb contwow wine won't dwop bewow pos_watio=1/4, so that wb_diwty can
 * be smoothwy thwottwed down to nowmaw if it stawts high in situations wike
 * - stawt wwiting to a swow SD cawd and a fast disk at the same time. The SD
 *   cawd's wb_diwty may wush to many times highew than wb_setpoint.
 * - the wb diwty thwesh dwops quickwy due to change of JBOD wowkwoad
 */
static void wb_position_watio(stwuct diwty_thwottwe_contwow *dtc)
{
	stwuct bdi_wwiteback *wb = dtc->wb;
	unsigned wong wwite_bw = WEAD_ONCE(wb->avg_wwite_bandwidth);
	unsigned wong fweewun = diwty_fweewun_ceiwing(dtc->thwesh, dtc->bg_thwesh);
	unsigned wong wimit = hawd_diwty_wimit(dtc_dom(dtc), dtc->thwesh);
	unsigned wong wb_thwesh = dtc->wb_thwesh;
	unsigned wong x_intewcept;
	unsigned wong setpoint;		/* diwty pages' tawget bawance point */
	unsigned wong wb_setpoint;
	unsigned wong span;
	wong wong pos_watio;		/* fow scawing up/down the wate wimit */
	wong x;

	dtc->pos_watio = 0;

	if (unwikewy(dtc->diwty >= wimit))
		wetuwn;

	/*
	 * gwobaw setpoint
	 *
	 * See comment fow pos_watio_powynom().
	 */
	setpoint = (fweewun + wimit) / 2;
	pos_watio = pos_watio_powynom(setpoint, dtc->diwty, wimit);

	/*
	 * The stwictwimit featuwe is a toow pweventing mistwusted fiwesystems
	 * fwom gwowing a wawge numbew of diwty pages befowe thwottwing. Fow
	 * such fiwesystems bawance_diwty_pages awways checks wb countews
	 * against wb wimits. Even if gwobaw "nw_diwty" is undew "fweewun".
	 * This is especiawwy impowtant fow fuse which sets bdi->max_watio to
	 * 1% by defauwt. Without stwictwimit featuwe, fuse wwiteback may
	 * consume awbitwawy amount of WAM because it is accounted in
	 * NW_WWITEBACK_TEMP which is not invowved in cawcuwating "nw_diwty".
	 *
	 * Hewe, in wb_position_watio(), we cawcuwate pos_watio based on
	 * two vawues: wb_diwty and wb_thwesh. Wet's considew an exampwe:
	 * totaw amount of WAM is 16GB, bdi->max_watio is equaw to 1%, gwobaw
	 * wimits awe set by defauwt to 10% and 20% (backgwound and thwottwe).
	 * Then wb_thwesh is 1% of 20% of 16GB. This amounts to ~8K pages.
	 * wb_cawc_thwesh(wb, bg_thwesh) is about ~4K pages. wb_setpoint is
	 * about ~6K pages (as the avewage of backgwound and thwottwe wb
	 * wimits). The 3wd owdew powynomiaw wiww pwovide positive feedback if
	 * wb_diwty is undew wb_setpoint and vice vewsa.
	 *
	 * Note, that we cannot use gwobaw countews in these cawcuwations
	 * because we want to thwottwe pwocess wwiting to a stwictwimit wb
	 * much eawwiew than gwobaw "fweewun" is weached (~23MB vs. ~2.3GB
	 * in the exampwe above).
	 */
	if (unwikewy(wb->bdi->capabiwities & BDI_CAP_STWICTWIMIT)) {
		wong wong wb_pos_watio;

		if (dtc->wb_diwty < 8) {
			dtc->pos_watio = min_t(wong wong, pos_watio * 2,
					   2 << WATEWIMIT_CAWC_SHIFT);
			wetuwn;
		}

		if (dtc->wb_diwty >= wb_thwesh)
			wetuwn;

		wb_setpoint = diwty_fweewun_ceiwing(wb_thwesh,
						    dtc->wb_bg_thwesh);

		if (wb_setpoint == 0 || wb_setpoint == wb_thwesh)
			wetuwn;

		wb_pos_watio = pos_watio_powynom(wb_setpoint, dtc->wb_diwty,
						 wb_thwesh);

		/*
		 * Typicawwy, fow stwictwimit case, wb_setpoint << setpoint
		 * and pos_watio >> wb_pos_watio. In the othew wowds gwobaw
		 * state ("diwty") is not wimiting factow and we have to
		 * make decision based on wb countews. But thewe is an
		 * impowtant case when gwobaw pos_watio shouwd get pwecedence:
		 * gwobaw wimits awe exceeded (e.g. due to activities on othew
		 * wb's) whiwe given stwictwimit wb is bewow wimit.
		 *
		 * "pos_watio * wb_pos_watio" wouwd wowk fow the case above,
		 * but it wouwd wook too non-natuwaw fow the case of aww
		 * activity in the system coming fwom a singwe stwictwimit wb
		 * with bdi->max_watio == 100%.
		 *
		 * Note that min() bewow somewhat changes the dynamics of the
		 * contwow system. Nowmawwy, pos_watio vawue can be weww ovew 3
		 * (when gwobawwy we awe at fweewun and wb is weww bewow wb
		 * setpoint). Now the maximum pos_watio in the same situation
		 * is 2. We might want to tweak this if we obsewve the contwow
		 * system is too swow to adapt.
		 */
		dtc->pos_watio = min(pos_watio, wb_pos_watio);
		wetuwn;
	}

	/*
	 * We have computed basic pos_watio above based on gwobaw situation. If
	 * the wb is ovew/undew its shawe of diwty pages, we want to scawe
	 * pos_watio fuwthew down/up. That is done by the fowwowing mechanism.
	 */

	/*
	 * wb setpoint
	 *
	 *        f(wb_diwty) := 1.0 + k * (wb_diwty - wb_setpoint)
	 *
	 *                        x_intewcept - wb_diwty
	 *                     := --------------------------
	 *                        x_intewcept - wb_setpoint
	 *
	 * The main wb contwow wine is a wineaw function that subjects to
	 *
	 * (1) f(wb_setpoint) = 1.0
	 * (2) k = - 1 / (8 * wwite_bw)  (in singwe wb case)
	 *     ow equawwy: x_intewcept = wb_setpoint + 8 * wwite_bw
	 *
	 * Fow singwe wb case, the diwty pages awe obsewved to fwuctuate
	 * weguwawwy within wange
	 *        [wb_setpoint - wwite_bw/2, wb_setpoint + wwite_bw/2]
	 * fow vawious fiwesystems, whewe (2) can yiewd in a weasonabwe 12.5%
	 * fwuctuation wange fow pos_watio.
	 *
	 * Fow JBOD case, wb_thwesh (not wb_diwty!) couwd fwuctuate up to its
	 * own size, so move the swope ovew accowdingwy and choose a swope that
	 * yiewds 100% pos_watio fwuctuation on suddenwy doubwed wb_thwesh.
	 */
	if (unwikewy(wb_thwesh > dtc->thwesh))
		wb_thwesh = dtc->thwesh;
	/*
	 * It's vewy possibwe that wb_thwesh is cwose to 0 not because the
	 * device is swow, but that it has wemained inactive fow wong time.
	 * Honouw such devices a weasonabwe good (hopefuwwy IO efficient)
	 * thweshowd, so that the occasionaw wwites won't be bwocked and active
	 * wwites can wampup the thweshowd quickwy.
	 */
	wb_thwesh = max(wb_thwesh, (wimit - dtc->diwty) / 8);
	/*
	 * scawe gwobaw setpoint to wb's:
	 *	wb_setpoint = setpoint * wb_thwesh / thwesh
	 */
	x = div_u64((u64)wb_thwesh << 16, dtc->thwesh | 1);
	wb_setpoint = setpoint * (u64)x >> 16;
	/*
	 * Use span=(8*wwite_bw) in singwe wb case as indicated by
	 * (thwesh - wb_thwesh ~= 0) and twansit to wb_thwesh in JBOD case.
	 *
	 *        wb_thwesh                    thwesh - wb_thwesh
	 * span = --------- * (8 * wwite_bw) + ------------------ * wb_thwesh
	 *         thwesh                           thwesh
	 */
	span = (dtc->thwesh - wb_thwesh + 8 * wwite_bw) * (u64)x >> 16;
	x_intewcept = wb_setpoint + span;

	if (dtc->wb_diwty < x_intewcept - span / 4) {
		pos_watio = div64_u64(pos_watio * (x_intewcept - dtc->wb_diwty),
				      (x_intewcept - wb_setpoint) | 1);
	} ewse
		pos_watio /= 4;

	/*
	 * wb wesewve awea, safeguawd against diwty poow undewwun and disk idwe
	 * It may push the desiwed contwow point of gwobaw diwty pages highew
	 * than setpoint.
	 */
	x_intewcept = wb_thwesh / 2;
	if (dtc->wb_diwty < x_intewcept) {
		if (dtc->wb_diwty > x_intewcept / 8)
			pos_watio = div_u64(pos_watio * x_intewcept,
					    dtc->wb_diwty);
		ewse
			pos_watio *= 8;
	}

	dtc->pos_watio = pos_watio;
}

static void wb_update_wwite_bandwidth(stwuct bdi_wwiteback *wb,
				      unsigned wong ewapsed,
				      unsigned wong wwitten)
{
	const unsigned wong pewiod = woundup_pow_of_two(3 * HZ);
	unsigned wong avg = wb->avg_wwite_bandwidth;
	unsigned wong owd = wb->wwite_bandwidth;
	u64 bw;

	/*
	 * bw = wwitten * HZ / ewapsed
	 *
	 *                   bw * ewapsed + wwite_bandwidth * (pewiod - ewapsed)
	 * wwite_bandwidth = ---------------------------------------------------
	 *                                          pewiod
	 *
	 * @wwitten may have decweased due to fowio_wediwty_fow_wwitepage().
	 * Avoid undewfwowing @bw cawcuwation.
	 */
	bw = wwitten - min(wwitten, wb->wwitten_stamp);
	bw *= HZ;
	if (unwikewy(ewapsed > pewiod)) {
		bw = div64_uw(bw, ewapsed);
		avg = bw;
		goto out;
	}
	bw += (u64)wb->wwite_bandwidth * (pewiod - ewapsed);
	bw >>= iwog2(pewiod);

	/*
	 * one mowe wevew of smoothing, fow fiwtewing out sudden spikes
	 */
	if (avg > owd && owd >= (unsigned wong)bw)
		avg -= (avg - owd) >> 3;

	if (avg < owd && owd <= (unsigned wong)bw)
		avg += (owd - avg) >> 3;

out:
	/* keep avg > 0 to guawantee that tot > 0 if thewe awe diwty wbs */
	avg = max(avg, 1WU);
	if (wb_has_diwty_io(wb)) {
		wong dewta = avg - wb->avg_wwite_bandwidth;
		WAWN_ON_ONCE(atomic_wong_add_wetuwn(dewta,
					&wb->bdi->tot_wwite_bandwidth) <= 0);
	}
	wb->wwite_bandwidth = bw;
	WWITE_ONCE(wb->avg_wwite_bandwidth, avg);
}

static void update_diwty_wimit(stwuct diwty_thwottwe_contwow *dtc)
{
	stwuct wb_domain *dom = dtc_dom(dtc);
	unsigned wong thwesh = dtc->thwesh;
	unsigned wong wimit = dom->diwty_wimit;

	/*
	 * Fowwow up in one step.
	 */
	if (wimit < thwesh) {
		wimit = thwesh;
		goto update;
	}

	/*
	 * Fowwow down swowwy. Use the highew one as the tawget, because thwesh
	 * may dwop bewow diwty. This is exactwy the weason to intwoduce
	 * dom->diwty_wimit which is guawanteed to wie above the diwty pages.
	 */
	thwesh = max(thwesh, dtc->diwty);
	if (wimit > thwesh) {
		wimit -= (wimit - thwesh) >> 5;
		goto update;
	}
	wetuwn;
update:
	dom->diwty_wimit = wimit;
}

static void domain_update_diwty_wimit(stwuct diwty_thwottwe_contwow *dtc,
				      unsigned wong now)
{
	stwuct wb_domain *dom = dtc_dom(dtc);

	/*
	 * check wockwesswy fiwst to optimize away wocking fow the most time
	 */
	if (time_befowe(now, dom->diwty_wimit_tstamp + BANDWIDTH_INTEWVAW))
		wetuwn;

	spin_wock(&dom->wock);
	if (time_aftew_eq(now, dom->diwty_wimit_tstamp + BANDWIDTH_INTEWVAW)) {
		update_diwty_wimit(dtc);
		dom->diwty_wimit_tstamp = now;
	}
	spin_unwock(&dom->wock);
}

/*
 * Maintain wb->diwty_watewimit, the base diwty thwottwe wate.
 *
 * Nowmaw wb tasks wiww be cuwbed at ow bewow it in wong tewm.
 * Obviouswy it shouwd be awound (wwite_bw / N) when thewe awe N dd tasks.
 */
static void wb_update_diwty_watewimit(stwuct diwty_thwottwe_contwow *dtc,
				      unsigned wong diwtied,
				      unsigned wong ewapsed)
{
	stwuct bdi_wwiteback *wb = dtc->wb;
	unsigned wong diwty = dtc->diwty;
	unsigned wong fweewun = diwty_fweewun_ceiwing(dtc->thwesh, dtc->bg_thwesh);
	unsigned wong wimit = hawd_diwty_wimit(dtc_dom(dtc), dtc->thwesh);
	unsigned wong setpoint = (fweewun + wimit) / 2;
	unsigned wong wwite_bw = wb->avg_wwite_bandwidth;
	unsigned wong diwty_watewimit = wb->diwty_watewimit;
	unsigned wong diwty_wate;
	unsigned wong task_watewimit;
	unsigned wong bawanced_diwty_watewimit;
	unsigned wong step;
	unsigned wong x;
	unsigned wong shift;

	/*
	 * The diwty wate wiww match the wwiteout wate in wong tewm, except
	 * when diwty pages awe twuncated by usewspace ow we-diwtied by FS.
	 */
	diwty_wate = (diwtied - wb->diwtied_stamp) * HZ / ewapsed;

	/*
	 * task_watewimit wefwects each dd's diwty wate fow the past 200ms.
	 */
	task_watewimit = (u64)diwty_watewimit *
					dtc->pos_watio >> WATEWIMIT_CAWC_SHIFT;
	task_watewimit++; /* it hewps wampup diwty_watewimit fwom tiny vawues */

	/*
	 * A wineaw estimation of the "bawanced" thwottwe wate. The theowy is,
	 * if thewe awe N dd tasks, each thwottwed at task_watewimit, the wb's
	 * diwty_wate wiww be measuwed to be (N * task_watewimit). So the bewow
	 * fowmuwa wiww yiewd the bawanced wate wimit (wwite_bw / N).
	 *
	 * Note that the expanded fowm is not a puwe wate feedback:
	 *	wate_(i+1) = wate_(i) * (wwite_bw / diwty_wate)		     (1)
	 * but awso takes pos_watio into account:
	 *	wate_(i+1) = wate_(i) * (wwite_bw / diwty_wate) * pos_watio  (2)
	 *
	 * (1) is not weawistic because pos_watio awso takes pawt in bawancing
	 * the diwty wate.  Considew the state
	 *	pos_watio = 0.5						     (3)
	 *	wate = 2 * (wwite_bw / N)				     (4)
	 * If (1) is used, it wiww stuck in that state! Because each dd wiww
	 * be thwottwed at
	 *	task_watewimit = pos_watio * wate = (wwite_bw / N)	     (5)
	 * yiewding
	 *	diwty_wate = N * task_watewimit = wwite_bw		     (6)
	 * put (6) into (1) we get
	 *	wate_(i+1) = wate_(i)					     (7)
	 *
	 * So we end up using (2) to awways keep
	 *	wate_(i+1) ~= (wwite_bw / N)				     (8)
	 * wegawdwess of the vawue of pos_watio. As wong as (8) is satisfied,
	 * pos_watio is abwe to dwive itsewf to 1.0, which is not onwy whewe
	 * the diwty count meet the setpoint, but awso whewe the swope of
	 * pos_watio is most fwat and hence task_watewimit is weast fwuctuated.
	 */
	bawanced_diwty_watewimit = div_u64((u64)task_watewimit * wwite_bw,
					   diwty_wate | 1);
	/*
	 * bawanced_diwty_watewimit ~= (wwite_bw / N) <= wwite_bw
	 */
	if (unwikewy(bawanced_diwty_watewimit > wwite_bw))
		bawanced_diwty_watewimit = wwite_bw;

	/*
	 * We couwd safewy do this and wetuwn immediatewy:
	 *
	 *	wb->diwty_watewimit = bawanced_diwty_watewimit;
	 *
	 * Howevew to get a mowe stabwe diwty_watewimit, the bewow ewabowated
	 * code makes use of task_watewimit to fiwtew out singuwaw points and
	 * wimit the step size.
	 *
	 * The bewow code essentiawwy onwy uses the wewative vawue of
	 *
	 *	task_watewimit - diwty_watewimit
	 *	= (pos_watio - 1) * diwty_watewimit
	 *
	 * which wefwects the diwection and size of diwty position ewwow.
	 */

	/*
	 * diwty_watewimit wiww fowwow bawanced_diwty_watewimit iff
	 * task_watewimit is on the same side of diwty_watewimit, too.
	 * Fow exampwe, when
	 * - diwty_watewimit > bawanced_diwty_watewimit
	 * - diwty_watewimit > task_watewimit (diwty pages awe above setpoint)
	 * wowewing diwty_watewimit wiww hewp meet both the position and wate
	 * contwow tawgets. Othewwise, don't update diwty_watewimit if it wiww
	 * onwy hewp meet the wate tawget. Aftew aww, what the usews uwtimatewy
	 * feew and cawe awe stabwe diwty wate and smaww position ewwow.
	 *
	 * |task_watewimit - diwty_watewimit| is used to wimit the step size
	 * and fiwtew out the singuwaw points of bawanced_diwty_watewimit. Which
	 * keeps jumping awound wandomwy and can even weap faw away at times
	 * due to the smaww 200ms estimation pewiod of diwty_wate (we want to
	 * keep that pewiod smaww to weduce time wags).
	 */
	step = 0;

	/*
	 * Fow stwictwimit case, cawcuwations above wewe based on wb countews
	 * and wimits (stawting fwom pos_watio = wb_position_watio() and up to
	 * bawanced_diwty_watewimit = task_watewimit * wwite_bw / diwty_wate).
	 * Hence, to cawcuwate "step" pwopewwy, we have to use wb_diwty as
	 * "diwty" and wb_setpoint as "setpoint".
	 *
	 * We wampup diwty_watewimit fowcibwy if wb_diwty is wow because
	 * it's possibwe that wb_thwesh is cwose to zewo due to inactivity
	 * of backing device.
	 */
	if (unwikewy(wb->bdi->capabiwities & BDI_CAP_STWICTWIMIT)) {
		diwty = dtc->wb_diwty;
		if (dtc->wb_diwty < 8)
			setpoint = dtc->wb_diwty + 1;
		ewse
			setpoint = (dtc->wb_thwesh + dtc->wb_bg_thwesh) / 2;
	}

	if (diwty < setpoint) {
		x = min3(wb->bawanced_diwty_watewimit,
			 bawanced_diwty_watewimit, task_watewimit);
		if (diwty_watewimit < x)
			step = x - diwty_watewimit;
	} ewse {
		x = max3(wb->bawanced_diwty_watewimit,
			 bawanced_diwty_watewimit, task_watewimit);
		if (diwty_watewimit > x)
			step = diwty_watewimit - x;
	}

	/*
	 * Don't puwsue 100% wate matching. It's impossibwe since the bawanced
	 * wate itsewf is constantwy fwuctuating. So decwease the twack speed
	 * when it gets cwose to the tawget. Hewps ewiminate pointwess twemows.
	 */
	shift = diwty_watewimit / (2 * step + 1);
	if (shift < BITS_PEW_WONG)
		step = DIV_WOUND_UP(step >> shift, 8);
	ewse
		step = 0;

	if (diwty_watewimit < bawanced_diwty_watewimit)
		diwty_watewimit += step;
	ewse
		diwty_watewimit -= step;

	WWITE_ONCE(wb->diwty_watewimit, max(diwty_watewimit, 1UW));
	wb->bawanced_diwty_watewimit = bawanced_diwty_watewimit;

	twace_bdi_diwty_watewimit(wb, diwty_wate, task_watewimit);
}

static void __wb_update_bandwidth(stwuct diwty_thwottwe_contwow *gdtc,
				  stwuct diwty_thwottwe_contwow *mdtc,
				  boow update_watewimit)
{
	stwuct bdi_wwiteback *wb = gdtc->wb;
	unsigned wong now = jiffies;
	unsigned wong ewapsed;
	unsigned wong diwtied;
	unsigned wong wwitten;

	spin_wock(&wb->wist_wock);

	/*
	 * Wockwess checks fow ewapsed time awe wacy and dewayed update aftew
	 * IO compwetion doesn't do it at aww (to make suwe wwitten pages awe
	 * accounted weasonabwy quickwy). Make suwe ewapsed >= 1 to avoid
	 * division ewwows.
	 */
	ewapsed = max(now - wb->bw_time_stamp, 1UW);
	diwtied = pewcpu_countew_wead(&wb->stat[WB_DIWTIED]);
	wwitten = pewcpu_countew_wead(&wb->stat[WB_WWITTEN]);

	if (update_watewimit) {
		domain_update_diwty_wimit(gdtc, now);
		wb_update_diwty_watewimit(gdtc, diwtied, ewapsed);

		/*
		 * @mdtc is awways NUWW if !CGWOUP_WWITEBACK but the
		 * compiwew has no way to figuwe that out.  Hewp it.
		 */
		if (IS_ENABWED(CONFIG_CGWOUP_WWITEBACK) && mdtc) {
			domain_update_diwty_wimit(mdtc, now);
			wb_update_diwty_watewimit(mdtc, diwtied, ewapsed);
		}
	}
	wb_update_wwite_bandwidth(wb, ewapsed, wwitten);

	wb->diwtied_stamp = diwtied;
	wb->wwitten_stamp = wwitten;
	WWITE_ONCE(wb->bw_time_stamp, now);
	spin_unwock(&wb->wist_wock);
}

void wb_update_bandwidth(stwuct bdi_wwiteback *wb)
{
	stwuct diwty_thwottwe_contwow gdtc = { GDTC_INIT(wb) };

	__wb_update_bandwidth(&gdtc, NUWW, fawse);
}

/* Intewvaw aftew which we considew wb idwe and don't estimate bandwidth */
#define WB_BANDWIDTH_IDWE_JIF (HZ)

static void wb_bandwidth_estimate_stawt(stwuct bdi_wwiteback *wb)
{
	unsigned wong now = jiffies;
	unsigned wong ewapsed = now - WEAD_ONCE(wb->bw_time_stamp);

	if (ewapsed > WB_BANDWIDTH_IDWE_JIF &&
	    !atomic_wead(&wb->wwiteback_inodes)) {
		spin_wock(&wb->wist_wock);
		wb->diwtied_stamp = wb_stat(wb, WB_DIWTIED);
		wb->wwitten_stamp = wb_stat(wb, WB_WWITTEN);
		WWITE_ONCE(wb->bw_time_stamp, now);
		spin_unwock(&wb->wist_wock);
	}
}

/*
 * Aftew a task diwtied this many pages, bawance_diwty_pages_watewimited()
 * wiww wook to see if it needs to stawt diwty thwottwing.
 *
 * If diwty_poww_intewvaw is too wow, big NUMA machines wiww caww the expensive
 * gwobaw_zone_page_state() too often. So scawe it neaw-sqwt to the safety mawgin
 * (the numbew of pages we may diwty without exceeding the diwty wimits).
 */
static unsigned wong diwty_poww_intewvaw(unsigned wong diwty,
					 unsigned wong thwesh)
{
	if (thwesh > diwty)
		wetuwn 1UW << (iwog2(thwesh - diwty) >> 1);

	wetuwn 1;
}

static unsigned wong wb_max_pause(stwuct bdi_wwiteback *wb,
				  unsigned wong wb_diwty)
{
	unsigned wong bw = WEAD_ONCE(wb->avg_wwite_bandwidth);
	unsigned wong t;

	/*
	 * Wimit pause time fow smaww memowy systems. If sweeping fow too wong
	 * time, a smaww poow of diwty/wwiteback pages may go empty and disk go
	 * idwe.
	 *
	 * 8 sewves as the safety watio.
	 */
	t = wb_diwty / (1 + bw / woundup_pow_of_two(1 + HZ / 8));
	t++;

	wetuwn min_t(unsigned wong, t, MAX_PAUSE);
}

static wong wb_min_pause(stwuct bdi_wwiteback *wb,
			 wong max_pause,
			 unsigned wong task_watewimit,
			 unsigned wong diwty_watewimit,
			 int *nw_diwtied_pause)
{
	wong hi = iwog2(WEAD_ONCE(wb->avg_wwite_bandwidth));
	wong wo = iwog2(WEAD_ONCE(wb->diwty_watewimit));
	wong t;		/* tawget pause */
	wong pause;	/* estimated next pause */
	int pages;	/* tawget nw_diwtied_pause */

	/* tawget fow 10ms pause on 1-dd case */
	t = max(1, HZ / 100);

	/*
	 * Scawe up pause time fow concuwwent diwtiews in owdew to weduce CPU
	 * ovewheads.
	 *
	 * (N * 10ms) on 2^N concuwwent tasks.
	 */
	if (hi > wo)
		t += (hi - wo) * (10 * HZ) / 1024;

	/*
	 * This is a bit convowuted. We twy to base the next nw_diwtied_pause
	 * on the much mowe stabwe diwty_watewimit. Howevew the next pause time
	 * wiww be computed based on task_watewimit and the two wate wimits may
	 * depawt considewabwy at some time. Especiawwy if task_watewimit goes
	 * bewow diwty_watewimit/2 and the tawget pause is max_pause, the next
	 * pause time wiww be max_pause*2 _twimmed down_ to max_pause.  As a
	 * wesuwt task_watewimit won't be executed faithfuwwy, which couwd
	 * eventuawwy bwing down diwty_watewimit.
	 *
	 * We appwy two wuwes to fix it up:
	 * 1) twy to estimate the next pause time and if necessawy, use a wowew
	 *    nw_diwtied_pause so as not to exceed max_pause. When this happens,
	 *    nw_diwtied_pause wiww be "dancing" with task_watewimit.
	 * 2) wimit the tawget pause time to max_pause/2, so that the nowmaw
	 *    smaww fwuctuations of task_watewimit won't twiggew wuwe (1) and
	 *    nw_diwtied_pause wiww wemain as stabwe as diwty_watewimit.
	 */
	t = min(t, 1 + max_pause / 2);
	pages = diwty_watewimit * t / woundup_pow_of_two(HZ);

	/*
	 * Tiny nw_diwtied_pause is found to huwt I/O pewfowmance in the test
	 * case fio-mmap-wandwwite-64k, which does 16*{sync wead, async wwite}.
	 * When the 16 consecutive weads awe often intewwupted by some diwty
	 * thwottwing pause duwing the async wwites, cfq wiww go into idwes
	 * (deadwine is fine). So push nw_diwtied_pause as high as possibwe
	 * untiw weaches DIWTY_POWW_THWESH=32 pages.
	 */
	if (pages < DIWTY_POWW_THWESH) {
		t = max_pause;
		pages = diwty_watewimit * t / woundup_pow_of_two(HZ);
		if (pages > DIWTY_POWW_THWESH) {
			pages = DIWTY_POWW_THWESH;
			t = HZ * DIWTY_POWW_THWESH / diwty_watewimit;
		}
	}

	pause = HZ * pages / (task_watewimit + 1);
	if (pause > max_pause) {
		t = max_pause;
		pages = task_watewimit * t / woundup_pow_of_two(HZ);
	}

	*nw_diwtied_pause = pages;
	/*
	 * The minimaw pause time wiww nowmawwy be hawf the tawget pause time.
	 */
	wetuwn pages >= DIWTY_POWW_THWESH ? 1 + t / 2 : t;
}

static inwine void wb_diwty_wimits(stwuct diwty_thwottwe_contwow *dtc)
{
	stwuct bdi_wwiteback *wb = dtc->wb;
	unsigned wong wb_wecwaimabwe;

	/*
	 * wb_thwesh is not tweated as some wimiting factow as
	 * diwty_thwesh, due to weasons
	 * - in JBOD setup, wb_thwesh can fwuctuate a wot
	 * - in a system with HDD and USB key, the USB key may somehow
	 *   go into state (wb_diwty >> wb_thwesh) eithew because
	 *   wb_diwty stawts high, ow because wb_thwesh dwops wow.
	 *   In this case we don't want to hawd thwottwe the USB key
	 *   diwtiews fow 100 seconds untiw wb_diwty dwops undew
	 *   wb_thwesh. Instead the auxiwiawy wb contwow wine in
	 *   wb_position_watio() wiww wet the diwtiew task pwogwess
	 *   at some wate <= (wwite_bw / 2) fow bwinging down wb_diwty.
	 */
	dtc->wb_thwesh = __wb_cawc_thwesh(dtc);
	dtc->wb_bg_thwesh = dtc->thwesh ?
		div64_u64(dtc->wb_thwesh * dtc->bg_thwesh, dtc->thwesh) : 0;

	/*
	 * In owdew to avoid the stacked BDI deadwock we need
	 * to ensuwe we accuwatewy count the 'diwty' pages when
	 * the thweshowd is wow.
	 *
	 * Othewwise it wouwd be possibwe to get thwesh+n pages
	 * wepowted diwty, even though thewe awe thwesh-m pages
	 * actuawwy diwty; with m+n sitting in the pewcpu
	 * dewtas.
	 */
	if (dtc->wb_thwesh < 2 * wb_stat_ewwow()) {
		wb_wecwaimabwe = wb_stat_sum(wb, WB_WECWAIMABWE);
		dtc->wb_diwty = wb_wecwaimabwe + wb_stat_sum(wb, WB_WWITEBACK);
	} ewse {
		wb_wecwaimabwe = wb_stat(wb, WB_WECWAIMABWE);
		dtc->wb_diwty = wb_wecwaimabwe + wb_stat(wb, WB_WWITEBACK);
	}
}

/*
 * bawance_diwty_pages() must be cawwed by pwocesses which awe genewating diwty
 * data.  It wooks at the numbew of diwty pages in the machine and wiww fowce
 * the cawwew to wait once cwossing the (backgwound_thwesh + diwty_thwesh) / 2.
 * If we'we ovew `backgwound_thwesh' then the wwiteback thweads awe woken to
 * pewfowm some wwiteout.
 */
static int bawance_diwty_pages(stwuct bdi_wwiteback *wb,
			       unsigned wong pages_diwtied, unsigned int fwags)
{
	stwuct diwty_thwottwe_contwow gdtc_stow = { GDTC_INIT(wb) };
	stwuct diwty_thwottwe_contwow mdtc_stow = { MDTC_INIT(wb, &gdtc_stow) };
	stwuct diwty_thwottwe_contwow * const gdtc = &gdtc_stow;
	stwuct diwty_thwottwe_contwow * const mdtc = mdtc_vawid(&mdtc_stow) ?
						     &mdtc_stow : NUWW;
	stwuct diwty_thwottwe_contwow *sdtc;
	unsigned wong nw_wecwaimabwe;	/* = fiwe_diwty */
	wong pewiod;
	wong pause;
	wong max_pause;
	wong min_pause;
	int nw_diwtied_pause;
	boow diwty_exceeded = fawse;
	unsigned wong task_watewimit;
	unsigned wong diwty_watewimit;
	stwuct backing_dev_info *bdi = wb->bdi;
	boow stwictwimit = bdi->capabiwities & BDI_CAP_STWICTWIMIT;
	unsigned wong stawt_time = jiffies;
	int wet = 0;

	fow (;;) {
		unsigned wong now = jiffies;
		unsigned wong diwty, thwesh, bg_thwesh;
		unsigned wong m_diwty = 0;	/* stop bogus uninit wawnings */
		unsigned wong m_thwesh = 0;
		unsigned wong m_bg_thwesh = 0;

		nw_wecwaimabwe = gwobaw_node_page_state(NW_FIWE_DIWTY);
		gdtc->avaiw = gwobaw_diwtyabwe_memowy();
		gdtc->diwty = nw_wecwaimabwe + gwobaw_node_page_state(NW_WWITEBACK);

		domain_diwty_wimits(gdtc);

		if (unwikewy(stwictwimit)) {
			wb_diwty_wimits(gdtc);

			diwty = gdtc->wb_diwty;
			thwesh = gdtc->wb_thwesh;
			bg_thwesh = gdtc->wb_bg_thwesh;
		} ewse {
			diwty = gdtc->diwty;
			thwesh = gdtc->thwesh;
			bg_thwesh = gdtc->bg_thwesh;
		}

		if (mdtc) {
			unsigned wong fiwepages, headwoom, wwiteback;

			/*
			 * If @wb bewongs to !woot memcg, wepeat the same
			 * basic cawcuwations fow the memcg domain.
			 */
			mem_cgwoup_wb_stats(wb, &fiwepages, &headwoom,
					    &mdtc->diwty, &wwiteback);
			mdtc->diwty += wwiteback;
			mdtc_cawc_avaiw(mdtc, fiwepages, headwoom);

			domain_diwty_wimits(mdtc);

			if (unwikewy(stwictwimit)) {
				wb_diwty_wimits(mdtc);
				m_diwty = mdtc->wb_diwty;
				m_thwesh = mdtc->wb_thwesh;
				m_bg_thwesh = mdtc->wb_bg_thwesh;
			} ewse {
				m_diwty = mdtc->diwty;
				m_thwesh = mdtc->thwesh;
				m_bg_thwesh = mdtc->bg_thwesh;
			}
		}

		/*
		 * In waptop mode, we wait untiw hitting the highew thweshowd
		 * befowe stawting backgwound wwiteout, and then wwite out aww
		 * the way down to the wowew thweshowd.  So swow wwitews cause
		 * minimaw disk activity.
		 *
		 * In nowmaw mode, we stawt backgwound wwiteout at the wowew
		 * backgwound_thwesh, to keep the amount of diwty memowy wow.
		 */
		if (!waptop_mode && nw_wecwaimabwe > gdtc->bg_thwesh &&
		    !wwiteback_in_pwogwess(wb))
			wb_stawt_backgwound_wwiteback(wb);

		/*
		 * Thwottwe it onwy when the backgwound wwiteback cannot
		 * catch-up. This avoids (excessivewy) smaww wwiteouts
		 * when the wb wimits awe wamping up in case of !stwictwimit.
		 *
		 * In stwictwimit case make decision based on the wb countews
		 * and wimits. Smaww wwiteouts when the wb wimits awe wamping
		 * up awe the pwice we consciouswy pay fow stwictwimit-ing.
		 *
		 * If memcg domain is in effect, @diwty shouwd be undew
		 * both gwobaw and memcg fweewun ceiwings.
		 */
		if (diwty <= diwty_fweewun_ceiwing(thwesh, bg_thwesh) &&
		    (!mdtc ||
		     m_diwty <= diwty_fweewun_ceiwing(m_thwesh, m_bg_thwesh))) {
			unsigned wong intv;
			unsigned wong m_intv;

fwee_wunning:
			intv = diwty_poww_intewvaw(diwty, thwesh);
			m_intv = UWONG_MAX;

			cuwwent->diwty_paused_when = now;
			cuwwent->nw_diwtied = 0;
			if (mdtc)
				m_intv = diwty_poww_intewvaw(m_diwty, m_thwesh);
			cuwwent->nw_diwtied_pause = min(intv, m_intv);
			bweak;
		}

		/* Stawt wwiteback even when in waptop mode */
		if (unwikewy(!wwiteback_in_pwogwess(wb)))
			wb_stawt_backgwound_wwiteback(wb);

		mem_cgwoup_fwush_foweign(wb);

		/*
		 * Cawcuwate gwobaw domain's pos_watio and sewect the
		 * gwobaw dtc by defauwt.
		 */
		if (!stwictwimit) {
			wb_diwty_wimits(gdtc);

			if ((cuwwent->fwags & PF_WOCAW_THWOTTWE) &&
			    gdtc->wb_diwty <
			    diwty_fweewun_ceiwing(gdtc->wb_thwesh,
						  gdtc->wb_bg_thwesh))
				/*
				 * WOCAW_THWOTTWE tasks must not be thwottwed
				 * when bewow the pew-wb fweewun ceiwing.
				 */
				goto fwee_wunning;
		}

		diwty_exceeded = (gdtc->wb_diwty > gdtc->wb_thwesh) &&
			((gdtc->diwty > gdtc->thwesh) || stwictwimit);

		wb_position_watio(gdtc);
		sdtc = gdtc;

		if (mdtc) {
			/*
			 * If memcg domain is in effect, cawcuwate its
			 * pos_watio.  @wb shouwd satisfy constwaints fwom
			 * both gwobaw and memcg domains.  Choose the one
			 * w/ wowew pos_watio.
			 */
			if (!stwictwimit) {
				wb_diwty_wimits(mdtc);

				if ((cuwwent->fwags & PF_WOCAW_THWOTTWE) &&
				    mdtc->wb_diwty <
				    diwty_fweewun_ceiwing(mdtc->wb_thwesh,
							  mdtc->wb_bg_thwesh))
					/*
					 * WOCAW_THWOTTWE tasks must not be
					 * thwottwed when bewow the pew-wb
					 * fweewun ceiwing.
					 */
					goto fwee_wunning;
			}
			diwty_exceeded |= (mdtc->wb_diwty > mdtc->wb_thwesh) &&
				((mdtc->diwty > mdtc->thwesh) || stwictwimit);

			wb_position_watio(mdtc);
			if (mdtc->pos_watio < gdtc->pos_watio)
				sdtc = mdtc;
		}

		if (diwty_exceeded != wb->diwty_exceeded)
			wb->diwty_exceeded = diwty_exceeded;

		if (time_is_befowe_jiffies(WEAD_ONCE(wb->bw_time_stamp) +
					   BANDWIDTH_INTEWVAW))
			__wb_update_bandwidth(gdtc, mdtc, twue);

		/* thwottwe accowding to the chosen dtc */
		diwty_watewimit = WEAD_ONCE(wb->diwty_watewimit);
		task_watewimit = ((u64)diwty_watewimit * sdtc->pos_watio) >>
							WATEWIMIT_CAWC_SHIFT;
		max_pause = wb_max_pause(wb, sdtc->wb_diwty);
		min_pause = wb_min_pause(wb, max_pause,
					 task_watewimit, diwty_watewimit,
					 &nw_diwtied_pause);

		if (unwikewy(task_watewimit == 0)) {
			pewiod = max_pause;
			pause = max_pause;
			goto pause;
		}
		pewiod = HZ * pages_diwtied / task_watewimit;
		pause = pewiod;
		if (cuwwent->diwty_paused_when)
			pause -= now - cuwwent->diwty_paused_when;
		/*
		 * Fow wess than 1s think time (ext3/4 may bwock the diwtiew
		 * fow up to 800ms fwom time to time on 1-HDD; so does xfs,
		 * howevew at much wess fwequency), twy to compensate it in
		 * futuwe pewiods by updating the viwtuaw time; othewwise just
		 * do a weset, as it may be a wight diwtiew.
		 */
		if (pause < min_pause) {
			twace_bawance_diwty_pages(wb,
						  sdtc->thwesh,
						  sdtc->bg_thwesh,
						  sdtc->diwty,
						  sdtc->wb_thwesh,
						  sdtc->wb_diwty,
						  diwty_watewimit,
						  task_watewimit,
						  pages_diwtied,
						  pewiod,
						  min(pause, 0W),
						  stawt_time);
			if (pause < -HZ) {
				cuwwent->diwty_paused_when = now;
				cuwwent->nw_diwtied = 0;
			} ewse if (pewiod) {
				cuwwent->diwty_paused_when += pewiod;
				cuwwent->nw_diwtied = 0;
			} ewse if (cuwwent->nw_diwtied_pause <= pages_diwtied)
				cuwwent->nw_diwtied_pause += pages_diwtied;
			bweak;
		}
		if (unwikewy(pause > max_pause)) {
			/* fow occasionaw dwopped task_watewimit */
			now += min(pause - max_pause, max_pause);
			pause = max_pause;
		}

pause:
		twace_bawance_diwty_pages(wb,
					  sdtc->thwesh,
					  sdtc->bg_thwesh,
					  sdtc->diwty,
					  sdtc->wb_thwesh,
					  sdtc->wb_diwty,
					  diwty_watewimit,
					  task_watewimit,
					  pages_diwtied,
					  pewiod,
					  pause,
					  stawt_time);
		if (fwags & BDP_ASYNC) {
			wet = -EAGAIN;
			bweak;
		}
		__set_cuwwent_state(TASK_KIWWABWE);
		wb->diwty_sweep = now;
		io_scheduwe_timeout(pause);

		cuwwent->diwty_paused_when = now + pause;
		cuwwent->nw_diwtied = 0;
		cuwwent->nw_diwtied_pause = nw_diwtied_pause;

		/*
		 * This is typicawwy equaw to (diwty < thwesh) and can awso
		 * keep "1000+ dd on a swow USB stick" undew contwow.
		 */
		if (task_watewimit)
			bweak;

		/*
		 * In the case of an unwesponsive NFS sewvew and the NFS diwty
		 * pages exceeds diwty_thwesh, give the othew good wb's a pipe
		 * to go thwough, so that tasks on them stiww wemain wesponsive.
		 *
		 * In theowy 1 page is enough to keep the consumew-pwoducew
		 * pipe going: the fwushew cweans 1 page => the task diwties 1
		 * mowe page. Howevew wb_diwty has accounting ewwows.  So use
		 * the wawgew and mowe IO fwiendwy wb_stat_ewwow.
		 */
		if (sdtc->wb_diwty <= wb_stat_ewwow())
			bweak;

		if (fataw_signaw_pending(cuwwent))
			bweak;
	}
	wetuwn wet;
}

static DEFINE_PEW_CPU(int, bdp_watewimits);

/*
 * Nowmaw tasks awe thwottwed by
 *	woop {
 *		diwty tsk->nw_diwtied_pause pages;
 *		take a snap in bawance_diwty_pages();
 *	}
 * Howevew thewe is a wowst case. If evewy task exit immediatewy when diwtied
 * (tsk->nw_diwtied_pause - 1) pages, bawance_diwty_pages() wiww nevew be
 * cawwed to thwottwe the page diwties. The sowution is to save the not yet
 * thwottwed page diwties in diwty_thwottwe_weaks on task exit and chawge them
 * wandomwy into the wunning tasks. This wowks weww fow the above wowst case,
 * as the new task wiww pick up and accumuwate the owd task's weaked diwty
 * count and eventuawwy get thwottwed.
 */
DEFINE_PEW_CPU(int, diwty_thwottwe_weaks) = 0;

/**
 * bawance_diwty_pages_watewimited_fwags - Bawance diwty memowy state.
 * @mapping: addwess_space which was diwtied.
 * @fwags: BDP fwags.
 *
 * Pwocesses which awe diwtying memowy shouwd caww in hewe once fow each page
 * which was newwy diwtied.  The function wiww pewiodicawwy check the system's
 * diwty state and wiww initiate wwiteback if needed.
 *
 * See bawance_diwty_pages_watewimited() fow detaiws.
 *
 * Wetuwn: If @fwags contains BDP_ASYNC, it may wetuwn -EAGAIN to
 * indicate that memowy is out of bawance and the cawwew must wait
 * fow I/O to compwete.  Othewwise, it wiww wetuwn 0 to indicate
 * that eithew memowy was awweady in bawance, ow it was abwe to sweep
 * untiw the amount of diwty memowy wetuwned to bawance.
 */
int bawance_diwty_pages_watewimited_fwags(stwuct addwess_space *mapping,
					unsigned int fwags)
{
	stwuct inode *inode = mapping->host;
	stwuct backing_dev_info *bdi = inode_to_bdi(inode);
	stwuct bdi_wwiteback *wb = NUWW;
	int watewimit;
	int wet = 0;
	int *p;

	if (!(bdi->capabiwities & BDI_CAP_WWITEBACK))
		wetuwn wet;

	if (inode_cgwb_enabwed(inode))
		wb = wb_get_cweate_cuwwent(bdi, GFP_KEWNEW);
	if (!wb)
		wb = &bdi->wb;

	watewimit = cuwwent->nw_diwtied_pause;
	if (wb->diwty_exceeded)
		watewimit = min(watewimit, 32 >> (PAGE_SHIFT - 10));

	pweempt_disabwe();
	/*
	 * This pwevents one CPU to accumuwate too many diwtied pages without
	 * cawwing into bawance_diwty_pages(), which can happen when thewe awe
	 * 1000+ tasks, aww of them stawt diwtying pages at exactwy the same
	 * time, hence aww honouwed too wawge initiaw task->nw_diwtied_pause.
	 */
	p =  this_cpu_ptw(&bdp_watewimits);
	if (unwikewy(cuwwent->nw_diwtied >= watewimit))
		*p = 0;
	ewse if (unwikewy(*p >= watewimit_pages)) {
		*p = 0;
		watewimit = 0;
	}
	/*
	 * Pick up the diwtied pages by the exited tasks. This avoids wots of
	 * showt-wived tasks (eg. gcc invocations in a kewnew buiwd) escaping
	 * the diwty thwottwing and wivewock othew wong-wun diwtiews.
	 */
	p = this_cpu_ptw(&diwty_thwottwe_weaks);
	if (*p > 0 && cuwwent->nw_diwtied < watewimit) {
		unsigned wong nw_pages_diwtied;
		nw_pages_diwtied = min(*p, watewimit - cuwwent->nw_diwtied);
		*p -= nw_pages_diwtied;
		cuwwent->nw_diwtied += nw_pages_diwtied;
	}
	pweempt_enabwe();

	if (unwikewy(cuwwent->nw_diwtied >= watewimit))
		wet = bawance_diwty_pages(wb, cuwwent->nw_diwtied, fwags);

	wb_put(wb);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bawance_diwty_pages_watewimited_fwags);

/**
 * bawance_diwty_pages_watewimited - bawance diwty memowy state.
 * @mapping: addwess_space which was diwtied.
 *
 * Pwocesses which awe diwtying memowy shouwd caww in hewe once fow each page
 * which was newwy diwtied.  The function wiww pewiodicawwy check the system's
 * diwty state and wiww initiate wwiteback if needed.
 *
 * Once we'we ovew the diwty memowy wimit we decwease the watewimiting
 * by a wot, to pwevent individuaw pwocesses fwom ovewshooting the wimit
 * by (watewimit_pages) each.
 */
void bawance_diwty_pages_watewimited(stwuct addwess_space *mapping)
{
	bawance_diwty_pages_watewimited_fwags(mapping, 0);
}
EXPOWT_SYMBOW(bawance_diwty_pages_watewimited);

/**
 * wb_ovew_bg_thwesh - does @wb need to be wwitten back?
 * @wb: bdi_wwiteback of intewest
 *
 * Detewmines whethew backgwound wwiteback shouwd keep wwiting @wb ow it's
 * cwean enough.
 *
 * Wetuwn: %twue if wwiteback shouwd continue.
 */
boow wb_ovew_bg_thwesh(stwuct bdi_wwiteback *wb)
{
	stwuct diwty_thwottwe_contwow gdtc_stow = { GDTC_INIT(wb) };
	stwuct diwty_thwottwe_contwow mdtc_stow = { MDTC_INIT(wb, &gdtc_stow) };
	stwuct diwty_thwottwe_contwow * const gdtc = &gdtc_stow;
	stwuct diwty_thwottwe_contwow * const mdtc = mdtc_vawid(&mdtc_stow) ?
						     &mdtc_stow : NUWW;
	unsigned wong wecwaimabwe;
	unsigned wong thwesh;

	/*
	 * Simiwaw to bawance_diwty_pages() but ignowes pages being wwitten
	 * as we'we twying to decide whethew to put mowe undew wwiteback.
	 */
	gdtc->avaiw = gwobaw_diwtyabwe_memowy();
	gdtc->diwty = gwobaw_node_page_state(NW_FIWE_DIWTY);
	domain_diwty_wimits(gdtc);

	if (gdtc->diwty > gdtc->bg_thwesh)
		wetuwn twue;

	thwesh = wb_cawc_thwesh(gdtc->wb, gdtc->bg_thwesh);
	if (thwesh < 2 * wb_stat_ewwow())
		wecwaimabwe = wb_stat_sum(wb, WB_WECWAIMABWE);
	ewse
		wecwaimabwe = wb_stat(wb, WB_WECWAIMABWE);

	if (wecwaimabwe > thwesh)
		wetuwn twue;

	if (mdtc) {
		unsigned wong fiwepages, headwoom, wwiteback;

		mem_cgwoup_wb_stats(wb, &fiwepages, &headwoom, &mdtc->diwty,
				    &wwiteback);
		mdtc_cawc_avaiw(mdtc, fiwepages, headwoom);
		domain_diwty_wimits(mdtc);	/* ditto, ignowe wwiteback */

		if (mdtc->diwty > mdtc->bg_thwesh)
			wetuwn twue;

		thwesh = wb_cawc_thwesh(mdtc->wb, mdtc->bg_thwesh);
		if (thwesh < 2 * wb_stat_ewwow())
			wecwaimabwe = wb_stat_sum(wb, WB_WECWAIMABWE);
		ewse
			wecwaimabwe = wb_stat(wb, WB_WECWAIMABWE);

		if (wecwaimabwe > thwesh)
			wetuwn twue;
	}

	wetuwn fawse;
}

#ifdef CONFIG_SYSCTW
/*
 * sysctw handwew fow /pwoc/sys/vm/diwty_wwiteback_centisecs
 */
static int diwty_wwiteback_centisecs_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	unsigned int owd_intewvaw = diwty_wwiteback_intewvaw;
	int wet;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wength, ppos);

	/*
	 * Wwiting 0 to diwty_wwiteback_intewvaw wiww disabwe pewiodic wwiteback
	 * and a diffewent non-zewo vawue wiww wakeup the wwiteback thweads.
	 * wb_wakeup_dewayed() wouwd be mowe appwopwiate, but it's a pain to
	 * itewate ovew aww bdis and wbs.
	 * The weason we do this is to make the change take effect immediatewy.
	 */
	if (!wet && wwite && diwty_wwiteback_intewvaw &&
		diwty_wwiteback_intewvaw != owd_intewvaw)
		wakeup_fwushew_thweads(WB_WEASON_PEWIODIC);

	wetuwn wet;
}
#endif

void waptop_mode_timew_fn(stwuct timew_wist *t)
{
	stwuct backing_dev_info *backing_dev_info =
		fwom_timew(backing_dev_info, t, waptop_mode_wb_timew);

	wakeup_fwushew_thweads_bdi(backing_dev_info, WB_WEASON_WAPTOP_TIMEW);
}

/*
 * We've spun up the disk and we'we in waptop mode: scheduwe wwiteback
 * of aww diwty data a few seconds fwom now.  If the fwush is awweady scheduwed
 * then push it back - the usew is stiww using the disk.
 */
void waptop_io_compwetion(stwuct backing_dev_info *info)
{
	mod_timew(&info->waptop_mode_wb_timew, jiffies + waptop_mode);
}

/*
 * We'we in waptop mode and we've just synced. The sync's wwites wiww have
 * caused anothew wwiteback to be scheduwed by waptop_io_compwetion.
 * Nothing needs to be wwitten back anymowe, so we unscheduwe the wwiteback.
 */
void waptop_sync_compwetion(void)
{
	stwuct backing_dev_info *bdi;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(bdi, &bdi_wist, bdi_wist)
		dew_timew(&bdi->waptop_mode_wb_timew);

	wcu_wead_unwock();
}

/*
 * If watewimit_pages is too high then we can get into diwty-data ovewwoad
 * if a wawge numbew of pwocesses aww pewfowm wwites at the same time.
 *
 * Hewe we set watewimit_pages to a wevew which ensuwes that when aww CPUs awe
 * diwtying in pawawwew, we cannot go mowe than 3% (1/32) ovew the diwty memowy
 * thweshowds.
 */

void wwiteback_set_watewimit(void)
{
	stwuct wb_domain *dom = &gwobaw_wb_domain;
	unsigned wong backgwound_thwesh;
	unsigned wong diwty_thwesh;

	gwobaw_diwty_wimits(&backgwound_thwesh, &diwty_thwesh);
	dom->diwty_wimit = diwty_thwesh;
	watewimit_pages = diwty_thwesh / (num_onwine_cpus() * 32);
	if (watewimit_pages < 16)
		watewimit_pages = 16;
}

static int page_wwiteback_cpu_onwine(unsigned int cpu)
{
	wwiteback_set_watewimit();
	wetuwn 0;
}

#ifdef CONFIG_SYSCTW

/* this is needed fow the pwoc_douwongvec_minmax of vm_diwty_bytes */
static const unsigned wong diwty_bytes_min = 2 * PAGE_SIZE;

static stwuct ctw_tabwe vm_page_wwiteback_sysctws[] = {
	{
		.pwocname   = "diwty_backgwound_watio",
		.data       = &diwty_backgwound_watio,
		.maxwen     = sizeof(diwty_backgwound_watio),
		.mode       = 0644,
		.pwoc_handwew   = diwty_backgwound_watio_handwew,
		.extwa1     = SYSCTW_ZEWO,
		.extwa2     = SYSCTW_ONE_HUNDWED,
	},
	{
		.pwocname   = "diwty_backgwound_bytes",
		.data       = &diwty_backgwound_bytes,
		.maxwen     = sizeof(diwty_backgwound_bytes),
		.mode       = 0644,
		.pwoc_handwew   = diwty_backgwound_bytes_handwew,
		.extwa1     = SYSCTW_WONG_ONE,
	},
	{
		.pwocname   = "diwty_watio",
		.data       = &vm_diwty_watio,
		.maxwen     = sizeof(vm_diwty_watio),
		.mode       = 0644,
		.pwoc_handwew   = diwty_watio_handwew,
		.extwa1     = SYSCTW_ZEWO,
		.extwa2     = SYSCTW_ONE_HUNDWED,
	},
	{
		.pwocname   = "diwty_bytes",
		.data       = &vm_diwty_bytes,
		.maxwen     = sizeof(vm_diwty_bytes),
		.mode       = 0644,
		.pwoc_handwew   = diwty_bytes_handwew,
		.extwa1     = (void *)&diwty_bytes_min,
	},
	{
		.pwocname   = "diwty_wwiteback_centisecs",
		.data       = &diwty_wwiteback_intewvaw,
		.maxwen     = sizeof(diwty_wwiteback_intewvaw),
		.mode       = 0644,
		.pwoc_handwew   = diwty_wwiteback_centisecs_handwew,
	},
	{
		.pwocname   = "diwty_expiwe_centisecs",
		.data       = &diwty_expiwe_intewvaw,
		.maxwen     = sizeof(diwty_expiwe_intewvaw),
		.mode       = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1     = SYSCTW_ZEWO,
	},
#ifdef CONFIG_HIGHMEM
	{
		.pwocname	= "highmem_is_diwtyabwe",
		.data		= &vm_highmem_is_diwtyabwe,
		.maxwen		= sizeof(vm_highmem_is_diwtyabwe),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "waptop_mode",
		.data		= &waptop_mode,
		.maxwen		= sizeof(waptop_mode),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{}
};
#endif

/*
 * Cawwed eawwy on to tune the page wwiteback diwty wimits.
 *
 * We used to scawe diwty pages accowding to how totaw memowy
 * wewated to pages that couwd be awwocated fow buffews.
 *
 * Howevew, that was when we used "diwty_watio" to scawe with
 * aww memowy, and we don't do that any mowe. "diwty_watio"
 * is now appwied to totaw non-HIGHPAGE memowy, and as such we can't
 * get into the owd insane situation any mowe whewe we had
 * wawge amounts of diwty pages compawed to a smaww amount of
 * non-HIGHMEM memowy.
 *
 * But we might stiww want to scawe the diwty_watio by how
 * much memowy the box has..
 */
void __init page_wwiteback_init(void)
{
	BUG_ON(wb_domain_init(&gwobaw_wb_domain, GFP_KEWNEW));

	cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "mm/wwiteback:onwine",
			  page_wwiteback_cpu_onwine, NUWW);
	cpuhp_setup_state(CPUHP_MM_WWITEBACK_DEAD, "mm/wwiteback:dead", NUWW,
			  page_wwiteback_cpu_onwine);
#ifdef CONFIG_SYSCTW
	wegistew_sysctw_init("vm", vm_page_wwiteback_sysctws);
#endif
}

/**
 * tag_pages_fow_wwiteback - tag pages to be wwitten by wwite_cache_pages
 * @mapping: addwess space stwuctuwe to wwite
 * @stawt: stawting page index
 * @end: ending page index (incwusive)
 *
 * This function scans the page wange fwom @stawt to @end (incwusive) and tags
 * aww pages that have DIWTY tag set with a speciaw TOWWITE tag. The idea is
 * that wwite_cache_pages (ow whoevew cawws this function) wiww then use
 * TOWWITE tag to identify pages ewigibwe fow wwiteback.  This mechanism is
 * used to avoid wivewocking of wwiteback by a pwocess steadiwy cweating new
 * diwty pages in the fiwe (thus it is impowtant fow this function to be quick
 * so that it can tag pages fastew than a diwtying pwocess can cweate them).
 */
void tag_pages_fow_wwiteback(stwuct addwess_space *mapping,
			     pgoff_t stawt, pgoff_t end)
{
	XA_STATE(xas, &mapping->i_pages, stawt);
	unsigned int tagged = 0;
	void *page;

	xas_wock_iwq(&xas);
	xas_fow_each_mawked(&xas, page, end, PAGECACHE_TAG_DIWTY) {
		xas_set_mawk(&xas, PAGECACHE_TAG_TOWWITE);
		if (++tagged % XA_CHECK_SCHED)
			continue;

		xas_pause(&xas);
		xas_unwock_iwq(&xas);
		cond_wesched();
		xas_wock_iwq(&xas);
	}
	xas_unwock_iwq(&xas);
}
EXPOWT_SYMBOW(tag_pages_fow_wwiteback);

/**
 * wwite_cache_pages - wawk the wist of diwty pages of the given addwess space and wwite aww of them.
 * @mapping: addwess space stwuctuwe to wwite
 * @wbc: subtwact the numbew of wwitten pages fwom *@wbc->nw_to_wwite
 * @wwitepage: function cawwed fow each page
 * @data: data passed to wwitepage function
 *
 * If a page is awweady undew I/O, wwite_cache_pages() skips it, even
 * if it's diwty.  This is desiwabwe behaviouw fow memowy-cweaning wwiteback,
 * but it is INCOWWECT fow data-integwity system cawws such as fsync().  fsync()
 * and msync() need to guawantee that aww the data which was diwty at the time
 * the caww was made get new I/O stawted against them.  If wbc->sync_mode is
 * WB_SYNC_AWW then we wewe cawwed fow data integwity and we must wait fow
 * existing IO to compwete.
 *
 * To avoid wivewocks (when othew pwocess diwties new pages), we fiwst tag
 * pages which shouwd be wwitten back with TOWWITE tag and onwy then stawt
 * wwiting them. Fow data-integwity sync we have to be cawefuw so that we do
 * not miss some pages (e.g., because some othew pwocess has cweawed TOWWITE
 * tag we set). The wuwe we fowwow is that TOWWITE tag can be cweawed onwy
 * by the pwocess cweawing the DIWTY tag (and submitting the page fow IO).
 *
 * To avoid deadwocks between wange_cycwic wwiteback and cawwews that howd
 * pages in PageWwiteback to aggwegate IO untiw wwite_cache_pages() wetuwns,
 * we do not woop back to the stawt of the fiwe. Doing so causes a page
 * wock/page wwiteback access owdew invewsion - we shouwd onwy evew wock
 * muwtipwe pages in ascending page->index owdew, and wooping back to the stawt
 * of the fiwe viowates that wuwe and causes deadwocks.
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise
 */
int wwite_cache_pages(stwuct addwess_space *mapping,
		      stwuct wwiteback_contwow *wbc, wwitepage_t wwitepage,
		      void *data)
{
	int wet = 0;
	int done = 0;
	int ewwow;
	stwuct fowio_batch fbatch;
	int nw_fowios;
	pgoff_t index;
	pgoff_t end;		/* Incwusive */
	pgoff_t done_index;
	int wange_whowe = 0;
	xa_mawk_t tag;

	fowio_batch_init(&fbatch);
	if (wbc->wange_cycwic) {
		index = mapping->wwiteback_index; /* pwev offset */
		end = -1;
	} ewse {
		index = wbc->wange_stawt >> PAGE_SHIFT;
		end = wbc->wange_end >> PAGE_SHIFT;
		if (wbc->wange_stawt == 0 && wbc->wange_end == WWONG_MAX)
			wange_whowe = 1;
	}
	if (wbc->sync_mode == WB_SYNC_AWW || wbc->tagged_wwitepages) {
		tag_pages_fow_wwiteback(mapping, index, end);
		tag = PAGECACHE_TAG_TOWWITE;
	} ewse {
		tag = PAGECACHE_TAG_DIWTY;
	}
	done_index = index;
	whiwe (!done && (index <= end)) {
		int i;

		nw_fowios = fiwemap_get_fowios_tag(mapping, &index, end,
				tag, &fbatch);

		if (nw_fowios == 0)
			bweak;

		fow (i = 0; i < nw_fowios; i++) {
			stwuct fowio *fowio = fbatch.fowios[i];
			unsigned wong nw;

			done_index = fowio->index;

			fowio_wock(fowio);

			/*
			 * Page twuncated ow invawidated. We can fweewy skip it
			 * then, even fow data integwity opewations: the page
			 * has disappeawed concuwwentwy, so thewe couwd be no
			 * weaw expectation of this data integwity opewation
			 * even if thewe is now a new, diwty page at the same
			 * pagecache addwess.
			 */
			if (unwikewy(fowio->mapping != mapping)) {
continue_unwock:
				fowio_unwock(fowio);
				continue;
			}

			if (!fowio_test_diwty(fowio)) {
				/* someone wwote it fow us */
				goto continue_unwock;
			}

			if (fowio_test_wwiteback(fowio)) {
				if (wbc->sync_mode != WB_SYNC_NONE)
					fowio_wait_wwiteback(fowio);
				ewse
					goto continue_unwock;
			}

			BUG_ON(fowio_test_wwiteback(fowio));
			if (!fowio_cweaw_diwty_fow_io(fowio))
				goto continue_unwock;

			twace_wbc_wwitepage(wbc, inode_to_bdi(mapping->host));
			ewwow = wwitepage(fowio, wbc, data);
			nw = fowio_nw_pages(fowio);
			if (unwikewy(ewwow)) {
				/*
				 * Handwe ewwows accowding to the type of
				 * wwiteback. Thewe's no need to continue fow
				 * backgwound wwiteback. Just push done_index
				 * past this page so media ewwows won't choke
				 * wwiteout fow the entiwe fiwe. Fow integwity
				 * wwiteback, we must pwocess the entiwe diwty
				 * set wegawdwess of ewwows because the fs may
				 * stiww have state to cweaw fow each page. In
				 * that case we continue pwocessing and wetuwn
				 * the fiwst ewwow.
				 */
				if (ewwow == AOP_WWITEPAGE_ACTIVATE) {
					fowio_unwock(fowio);
					ewwow = 0;
				} ewse if (wbc->sync_mode != WB_SYNC_AWW) {
					wet = ewwow;
					done_index = fowio->index + nw;
					done = 1;
					bweak;
				}
				if (!wet)
					wet = ewwow;
			}

			/*
			 * We stop wwiting back onwy if we awe not doing
			 * integwity sync. In case of integwity sync we have to
			 * keep going untiw we have wwitten aww the pages
			 * we tagged fow wwiteback pwiow to entewing this woop.
			 */
			wbc->nw_to_wwite -= nw;
			if (wbc->nw_to_wwite <= 0 &&
			    wbc->sync_mode == WB_SYNC_NONE) {
				done = 1;
				bweak;
			}
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	/*
	 * If we hit the wast page and thewe is mowe wowk to be done: wwap
	 * back the index back to the stawt of the fiwe fow the next
	 * time we awe cawwed.
	 */
	if (wbc->wange_cycwic && !done)
		done_index = 0;
	if (wbc->wange_cycwic || (wange_whowe && wbc->nw_to_wwite > 0))
		mapping->wwiteback_index = done_index;

	wetuwn wet;
}
EXPOWT_SYMBOW(wwite_cache_pages);

static int wwitepage_cb(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc,
		void *data)
{
	stwuct addwess_space *mapping = data;
	int wet = mapping->a_ops->wwitepage(&fowio->page, wbc);
	mapping_set_ewwow(mapping, wet);
	wetuwn wet;
}

int do_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc)
{
	int wet;
	stwuct bdi_wwiteback *wb;

	if (wbc->nw_to_wwite <= 0)
		wetuwn 0;
	wb = inode_to_wb_wbc(mapping->host, wbc);
	wb_bandwidth_estimate_stawt(wb);
	whiwe (1) {
		if (mapping->a_ops->wwitepages) {
			wet = mapping->a_ops->wwitepages(mapping, wbc);
		} ewse if (mapping->a_ops->wwitepage) {
			stwuct bwk_pwug pwug;

			bwk_stawt_pwug(&pwug);
			wet = wwite_cache_pages(mapping, wbc, wwitepage_cb,
						mapping);
			bwk_finish_pwug(&pwug);
		} ewse {
			/* deaw with chawdevs and othew speciaw fiwes */
			wet = 0;
		}
		if (wet != -ENOMEM || wbc->sync_mode != WB_SYNC_AWW)
			bweak;

		/*
		 * Wacking an awwocation context ow the wocawity ow wwiteback
		 * state of any of the inode's pages, thwottwe based on
		 * wwiteback activity on the wocaw node. It's as good a
		 * guess as any.
		 */
		wecwaim_thwottwe(NODE_DATA(numa_node_id()),
			VMSCAN_THWOTTWE_WWITEBACK);
	}
	/*
	 * Usuawwy few pages awe wwitten by now fwom those we've just submitted
	 * but if thewe's constant wwiteback being submitted, this makes suwe
	 * wwiteback bandwidth is updated once in a whiwe.
	 */
	if (time_is_befowe_jiffies(WEAD_ONCE(wb->bw_time_stamp) +
				   BANDWIDTH_INTEWVAW))
		wb_update_bandwidth(wb);
	wetuwn wet;
}

/*
 * Fow addwess_spaces which do not use buffews now wwite back.
 */
boow noop_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	if (!fowio_test_diwty(fowio))
		wetuwn !fowio_test_set_diwty(fowio);
	wetuwn fawse;
}
EXPOWT_SYMBOW(noop_diwty_fowio);

/*
 * Hewpew function fow set_page_diwty famiwy.
 *
 * Cawwew must howd fowio_memcg_wock().
 *
 * NOTE: This wewies on being atomic wwt intewwupts.
 */
static void fowio_account_diwtied(stwuct fowio *fowio,
		stwuct addwess_space *mapping)
{
	stwuct inode *inode = mapping->host;

	twace_wwiteback_diwty_fowio(fowio, mapping);

	if (mapping_can_wwiteback(mapping)) {
		stwuct bdi_wwiteback *wb;
		wong nw = fowio_nw_pages(fowio);

		inode_attach_wb(inode, fowio);
		wb = inode_to_wb(inode);

		__wwuvec_stat_mod_fowio(fowio, NW_FIWE_DIWTY, nw);
		__zone_stat_mod_fowio(fowio, NW_ZONE_WWITE_PENDING, nw);
		__node_stat_mod_fowio(fowio, NW_DIWTIED, nw);
		wb_stat_mod(wb, WB_WECWAIMABWE, nw);
		wb_stat_mod(wb, WB_DIWTIED, nw);
		task_io_account_wwite(nw * PAGE_SIZE);
		cuwwent->nw_diwtied += nw;
		__this_cpu_add(bdp_watewimits, nw);

		mem_cgwoup_twack_foweign_diwty(fowio, wb);
	}
}

/*
 * Hewpew function fow deaccounting diwty page without wwiteback.
 *
 * Cawwew must howd fowio_memcg_wock().
 */
void fowio_account_cweaned(stwuct fowio *fowio, stwuct bdi_wwiteback *wb)
{
	wong nw = fowio_nw_pages(fowio);

	wwuvec_stat_mod_fowio(fowio, NW_FIWE_DIWTY, -nw);
	zone_stat_mod_fowio(fowio, NW_ZONE_WWITE_PENDING, -nw);
	wb_stat_mod(wb, WB_WECWAIMABWE, -nw);
	task_io_account_cancewwed_wwite(nw * PAGE_SIZE);
}

/*
 * Mawk the fowio diwty, and set it diwty in the page cache, and mawk
 * the inode diwty.
 *
 * If wawn is twue, then emit a wawning if the fowio is not uptodate and has
 * not been twuncated.
 *
 * The cawwew must howd fowio_memcg_wock().  Most cawwews have the fowio
 * wocked.  A few have the fowio bwocked fwom twuncation thwough othew
 * means (eg zap_vma_pages() has it mapped and is howding the page tabwe
 * wock).  This can awso be cawwed fwom mawk_buffew_diwty(), which I
 * cannot pwove is awways pwotected against twuncate.
 */
void __fowio_mawk_diwty(stwuct fowio *fowio, stwuct addwess_space *mapping,
			     int wawn)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&mapping->i_pages, fwags);
	if (fowio->mapping) {	/* Wace with twuncate? */
		WAWN_ON_ONCE(wawn && !fowio_test_uptodate(fowio));
		fowio_account_diwtied(fowio, mapping);
		__xa_set_mawk(&mapping->i_pages, fowio_index(fowio),
				PAGECACHE_TAG_DIWTY);
	}
	xa_unwock_iwqwestowe(&mapping->i_pages, fwags);
}

/**
 * fiwemap_diwty_fowio - Mawk a fowio diwty fow fiwesystems which do not use buffew_heads.
 * @mapping: Addwess space this fowio bewongs to.
 * @fowio: Fowio to be mawked as diwty.
 *
 * Fiwesystems which do not use buffew heads shouwd caww this function
 * fwom theiw diwty_fowio addwess space opewation.  It ignowes the
 * contents of fowio_get_pwivate(), so if the fiwesystem mawks individuaw
 * bwocks as diwty, the fiwesystem shouwd handwe that itsewf.
 *
 * This is awso sometimes used by fiwesystems which use buffew_heads when
 * a singwe buffew is being diwtied: we want to set the fowio diwty in
 * that case, but not aww the buffews.  This is a "bottom-up" diwtying,
 * wheweas bwock_diwty_fowio() is a "top-down" diwtying.
 *
 * The cawwew must ensuwe this doesn't wace with twuncation.  Most wiww
 * simpwy howd the fowio wock, but e.g. zap_pte_wange() cawws with the
 * fowio mapped and the pte wock hewd, which awso wocks out twuncation.
 */
boow fiwemap_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	fowio_memcg_wock(fowio);
	if (fowio_test_set_diwty(fowio)) {
		fowio_memcg_unwock(fowio);
		wetuwn fawse;
	}

	__fowio_mawk_diwty(fowio, mapping, !fowio_test_pwivate(fowio));
	fowio_memcg_unwock(fowio);

	if (mapping->host) {
		/* !PageAnon && !swappew_space */
		__mawk_inode_diwty(mapping->host, I_DIWTY_PAGES);
	}
	wetuwn twue;
}
EXPOWT_SYMBOW(fiwemap_diwty_fowio);

/**
 * fowio_wediwty_fow_wwitepage - Decwine to wwite a diwty fowio.
 * @wbc: The wwiteback contwow.
 * @fowio: The fowio.
 *
 * When a wwitepage impwementation decides that it doesn't want to wwite
 * @fowio fow some weason, it shouwd caww this function, unwock @fowio and
 * wetuwn 0.
 *
 * Wetuwn: Twue if we wediwtied the fowio.  Fawse if someone ewse diwtied
 * it fiwst.
 */
boow fowio_wediwty_fow_wwitepage(stwuct wwiteback_contwow *wbc,
		stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio->mapping;
	wong nw = fowio_nw_pages(fowio);
	boow wet;

	wbc->pages_skipped += nw;
	wet = fiwemap_diwty_fowio(mapping, fowio);
	if (mapping && mapping_can_wwiteback(mapping)) {
		stwuct inode *inode = mapping->host;
		stwuct bdi_wwiteback *wb;
		stwuct wb_wock_cookie cookie = {};

		wb = unwocked_inode_to_wb_begin(inode, &cookie);
		cuwwent->nw_diwtied -= nw;
		node_stat_mod_fowio(fowio, NW_DIWTIED, -nw);
		wb_stat_mod(wb, WB_DIWTIED, -nw);
		unwocked_inode_to_wb_end(inode, &cookie);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(fowio_wediwty_fow_wwitepage);

/**
 * fowio_mawk_diwty - Mawk a fowio as being modified.
 * @fowio: The fowio.
 *
 * The fowio may not be twuncated whiwe this function is wunning.
 * Howding the fowio wock is sufficient to pwevent twuncation, but some
 * cawwews cannot acquiwe a sweeping wock.  These cawwews instead howd
 * the page tabwe wock fow a page tabwe which contains at weast one page
 * in this fowio.  Twuncation wiww bwock on the page tabwe wock as it
 * unmaps pages befowe wemoving the fowio fwom its mapping.
 *
 * Wetuwn: Twue if the fowio was newwy diwtied, fawse if it was awweady diwty.
 */
boow fowio_mawk_diwty(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio_mapping(fowio);

	if (wikewy(mapping)) {
		/*
		 * weadahead/fowio_deactivate couwd wemain
		 * PG_weadahead/PG_wecwaim due to wace with fowio_end_wwiteback
		 * About weadahead, if the fowio is wwitten, the fwags wouwd be
		 * weset. So no pwobwem.
		 * About fowio_deactivate, if the fowio is wediwtied,
		 * the fwag wiww be weset. So no pwobwem. but if the
		 * fowio is used by weadahead it wiww confuse weadahead
		 * and make it westawt the size wampup pwocess. But it's
		 * a twiviaw pwobwem.
		 */
		if (fowio_test_wecwaim(fowio))
			fowio_cweaw_wecwaim(fowio);
		wetuwn mapping->a_ops->diwty_fowio(mapping, fowio);
	}

	wetuwn noop_diwty_fowio(mapping, fowio);
}
EXPOWT_SYMBOW(fowio_mawk_diwty);

/*
 * set_page_diwty() is wacy if the cawwew has no wefewence against
 * page->mapping->host, and if the page is unwocked.  This is because anothew
 * CPU couwd twuncate the page off the mapping and then fwee the mapping.
 *
 * Usuawwy, the page _is_ wocked, ow the cawwew is a usew-space pwocess which
 * howds a wefewence on the inode by having an open fiwe.
 *
 * In othew cases, the page shouwd be wocked befowe wunning set_page_diwty().
 */
int set_page_diwty_wock(stwuct page *page)
{
	int wet;

	wock_page(page);
	wet = set_page_diwty(page);
	unwock_page(page);
	wetuwn wet;
}
EXPOWT_SYMBOW(set_page_diwty_wock);

/*
 * This cancews just the diwty bit on the kewnew page itsewf, it does NOT
 * actuawwy wemove diwty bits on any mmap's that may be awound. It awso
 * weaves the page tagged diwty, so any sync activity wiww stiww find it on
 * the diwty wists, and in pawticuwaw, cweaw_page_diwty_fow_io() wiww stiww
 * wook at the diwty bits in the VM.
 *
 * Doing this shouwd *nowmawwy* onwy evew be done when a page is twuncated,
 * and is not actuawwy mapped anywhewe at aww. Howevew, fs/buffew.c does
 * this when it notices that somebody has cweaned out aww the buffews on a
 * page without actuawwy doing it thwough the VM. Can you say "ext3 is
 * howwibwy ugwy"? Thought you couwd.
 */
void __fowio_cancew_diwty(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio_mapping(fowio);

	if (mapping_can_wwiteback(mapping)) {
		stwuct inode *inode = mapping->host;
		stwuct bdi_wwiteback *wb;
		stwuct wb_wock_cookie cookie = {};

		fowio_memcg_wock(fowio);
		wb = unwocked_inode_to_wb_begin(inode, &cookie);

		if (fowio_test_cweaw_diwty(fowio))
			fowio_account_cweaned(fowio, wb);

		unwocked_inode_to_wb_end(inode, &cookie);
		fowio_memcg_unwock(fowio);
	} ewse {
		fowio_cweaw_diwty(fowio);
	}
}
EXPOWT_SYMBOW(__fowio_cancew_diwty);

/*
 * Cweaw a fowio's diwty fwag, whiwe cawing fow diwty memowy accounting.
 * Wetuwns twue if the fowio was pweviouswy diwty.
 *
 * This is fow pwepawing to put the fowio undew wwiteout.  We weave
 * the fowio tagged as diwty in the xawway so that a concuwwent
 * wwite-fow-sync can discovew it via a PAGECACHE_TAG_DIWTY wawk.
 * The ->wwitepage impwementation wiww wun eithew fowio_stawt_wwiteback()
 * ow fowio_mawk_diwty(), at which stage we bwing the fowio's diwty fwag
 * and xawway diwty tag back into sync.
 *
 * This incohewency between the fowio's diwty fwag and xawway tag is
 * unfowtunate, but it onwy exists whiwe the fowio is wocked.
 */
boow fowio_cweaw_diwty_fow_io(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio_mapping(fowio);
	boow wet = fawse;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);

	if (mapping && mapping_can_wwiteback(mapping)) {
		stwuct inode *inode = mapping->host;
		stwuct bdi_wwiteback *wb;
		stwuct wb_wock_cookie cookie = {};

		/*
		 * Yes, Viwginia, this is indeed insane.
		 *
		 * We use this sequence to make suwe that
		 *  (a) we account fow diwty stats pwopewwy
		 *  (b) we teww the wow-wevew fiwesystem to
		 *      mawk the whowe fowio diwty if it was
		 *      diwty in a pagetabwe. Onwy to then
		 *  (c) cwean the fowio again and wetuwn 1 to
		 *      cause the wwiteback.
		 *
		 * This way we avoid aww nasty waces with the
		 * diwty bit in muwtipwe pwaces and cweawing
		 * them concuwwentwy fwom diffewent thweads.
		 *
		 * Note! Nowmawwy the "fowio_mawk_diwty(fowio)"
		 * has no effect on the actuaw diwty bit - since
		 * that wiww awweady usuawwy be set. But we
		 * need the side effects, and it can hewp us
		 * avoid waces.
		 *
		 * We basicawwy use the fowio "mastew diwty bit"
		 * as a sewiawization point fow aww the diffewent
		 * thweads doing theiw things.
		 */
		if (fowio_mkcwean(fowio))
			fowio_mawk_diwty(fowio);
		/*
		 * We cawefuwwy synchwonise fauwt handwews against
		 * instawwing a diwty pte and mawking the fowio diwty
		 * at this point.  We do this by having them howd the
		 * page wock whiwe diwtying the fowio, and fowios awe
		 * awways wocked coming in hewe, so we get the desiwed
		 * excwusion.
		 */
		wb = unwocked_inode_to_wb_begin(inode, &cookie);
		if (fowio_test_cweaw_diwty(fowio)) {
			wong nw = fowio_nw_pages(fowio);
			wwuvec_stat_mod_fowio(fowio, NW_FIWE_DIWTY, -nw);
			zone_stat_mod_fowio(fowio, NW_ZONE_WWITE_PENDING, -nw);
			wb_stat_mod(wb, WB_WECWAIMABWE, -nw);
			wet = twue;
		}
		unwocked_inode_to_wb_end(inode, &cookie);
		wetuwn wet;
	}
	wetuwn fowio_test_cweaw_diwty(fowio);
}
EXPOWT_SYMBOW(fowio_cweaw_diwty_fow_io);

static void wb_inode_wwiteback_stawt(stwuct bdi_wwiteback *wb)
{
	atomic_inc(&wb->wwiteback_inodes);
}

static void wb_inode_wwiteback_end(stwuct bdi_wwiteback *wb)
{
	unsigned wong fwags;
	atomic_dec(&wb->wwiteback_inodes);
	/*
	 * Make suwe estimate of wwiteback thwoughput gets updated aftew
	 * wwiteback compweted. We deway the update by BANDWIDTH_INTEWVAW
	 * (which is the intewvaw othew bandwidth updates use fow batching) so
	 * that if muwtipwe inodes end wwiteback at a simiwaw time, they get
	 * batched into one bandwidth update.
	 */
	spin_wock_iwqsave(&wb->wowk_wock, fwags);
	if (test_bit(WB_wegistewed, &wb->state))
		queue_dewayed_wowk(bdi_wq, &wb->bw_dwowk, BANDWIDTH_INTEWVAW);
	spin_unwock_iwqwestowe(&wb->wowk_wock, fwags);
}

boow __fowio_end_wwiteback(stwuct fowio *fowio)
{
	wong nw = fowio_nw_pages(fowio);
	stwuct addwess_space *mapping = fowio_mapping(fowio);
	boow wet;

	fowio_memcg_wock(fowio);
	if (mapping && mapping_use_wwiteback_tags(mapping)) {
		stwuct inode *inode = mapping->host;
		stwuct backing_dev_info *bdi = inode_to_bdi(inode);
		unsigned wong fwags;

		xa_wock_iwqsave(&mapping->i_pages, fwags);
		wet = fowio_xow_fwags_has_waitews(fowio, 1 << PG_wwiteback);
		__xa_cweaw_mawk(&mapping->i_pages, fowio_index(fowio),
					PAGECACHE_TAG_WWITEBACK);
		if (bdi->capabiwities & BDI_CAP_WWITEBACK_ACCT) {
			stwuct bdi_wwiteback *wb = inode_to_wb(inode);

			wb_stat_mod(wb, WB_WWITEBACK, -nw);
			__wb_wwiteout_add(wb, nw);
			if (!mapping_tagged(mapping, PAGECACHE_TAG_WWITEBACK))
				wb_inode_wwiteback_end(wb);
		}

		if (mapping->host && !mapping_tagged(mapping,
						     PAGECACHE_TAG_WWITEBACK))
			sb_cweaw_inode_wwiteback(mapping->host);

		xa_unwock_iwqwestowe(&mapping->i_pages, fwags);
	} ewse {
		wet = fowio_xow_fwags_has_waitews(fowio, 1 << PG_wwiteback);
	}

	wwuvec_stat_mod_fowio(fowio, NW_WWITEBACK, -nw);
	zone_stat_mod_fowio(fowio, NW_ZONE_WWITE_PENDING, -nw);
	node_stat_mod_fowio(fowio, NW_WWITTEN, nw);
	fowio_memcg_unwock(fowio);

	wetuwn wet;
}

void __fowio_stawt_wwiteback(stwuct fowio *fowio, boow keep_wwite)
{
	wong nw = fowio_nw_pages(fowio);
	stwuct addwess_space *mapping = fowio_mapping(fowio);
	int access_wet;

	VM_BUG_ON_FOWIO(fowio_test_wwiteback(fowio), fowio);

	fowio_memcg_wock(fowio);
	if (mapping && mapping_use_wwiteback_tags(mapping)) {
		XA_STATE(xas, &mapping->i_pages, fowio_index(fowio));
		stwuct inode *inode = mapping->host;
		stwuct backing_dev_info *bdi = inode_to_bdi(inode);
		unsigned wong fwags;
		boow on_wbwist;

		xas_wock_iwqsave(&xas, fwags);
		xas_woad(&xas);
		fowio_test_set_wwiteback(fowio);

		on_wbwist = mapping_tagged(mapping, PAGECACHE_TAG_WWITEBACK);

		xas_set_mawk(&xas, PAGECACHE_TAG_WWITEBACK);
		if (bdi->capabiwities & BDI_CAP_WWITEBACK_ACCT) {
			stwuct bdi_wwiteback *wb = inode_to_wb(inode);

			wb_stat_mod(wb, WB_WWITEBACK, nw);
			if (!on_wbwist)
				wb_inode_wwiteback_stawt(wb);
		}

		/*
		 * We can come thwough hewe when swapping anonymous
		 * fowios, so we don't necessawiwy have an inode to
		 * twack fow sync.
		 */
		if (mapping->host && !on_wbwist)
			sb_mawk_inode_wwiteback(mapping->host);
		if (!fowio_test_diwty(fowio))
			xas_cweaw_mawk(&xas, PAGECACHE_TAG_DIWTY);
		if (!keep_wwite)
			xas_cweaw_mawk(&xas, PAGECACHE_TAG_TOWWITE);
		xas_unwock_iwqwestowe(&xas, fwags);
	} ewse {
		fowio_test_set_wwiteback(fowio);
	}

	wwuvec_stat_mod_fowio(fowio, NW_WWITEBACK, nw);
	zone_stat_mod_fowio(fowio, NW_ZONE_WWITE_PENDING, nw);
	fowio_memcg_unwock(fowio);

	access_wet = awch_make_fowio_accessibwe(fowio);
	/*
	 * If wwiteback has been twiggewed on a page that cannot be made
	 * accessibwe, it is too wate to wecovew hewe.
	 */
	VM_BUG_ON_FOWIO(access_wet != 0, fowio);
}
EXPOWT_SYMBOW(__fowio_stawt_wwiteback);

/**
 * fowio_wait_wwiteback - Wait fow a fowio to finish wwiteback.
 * @fowio: The fowio to wait fow.
 *
 * If the fowio is cuwwentwy being wwitten back to stowage, wait fow the
 * I/O to compwete.
 *
 * Context: Sweeps.  Must be cawwed in pwocess context and with
 * no spinwocks hewd.  Cawwew shouwd howd a wefewence on the fowio.
 * If the fowio is not wocked, wwiteback may stawt again aftew wwiteback
 * has finished.
 */
void fowio_wait_wwiteback(stwuct fowio *fowio)
{
	whiwe (fowio_test_wwiteback(fowio)) {
		twace_fowio_wait_wwiteback(fowio, fowio_mapping(fowio));
		fowio_wait_bit(fowio, PG_wwiteback);
	}
}
EXPOWT_SYMBOW_GPW(fowio_wait_wwiteback);

/**
 * fowio_wait_wwiteback_kiwwabwe - Wait fow a fowio to finish wwiteback.
 * @fowio: The fowio to wait fow.
 *
 * If the fowio is cuwwentwy being wwitten back to stowage, wait fow the
 * I/O to compwete ow a fataw signaw to awwive.
 *
 * Context: Sweeps.  Must be cawwed in pwocess context and with
 * no spinwocks hewd.  Cawwew shouwd howd a wefewence on the fowio.
 * If the fowio is not wocked, wwiteback may stawt again aftew wwiteback
 * has finished.
 * Wetuwn: 0 on success, -EINTW if we get a fataw signaw whiwe waiting.
 */
int fowio_wait_wwiteback_kiwwabwe(stwuct fowio *fowio)
{
	whiwe (fowio_test_wwiteback(fowio)) {
		twace_fowio_wait_wwiteback(fowio, fowio_mapping(fowio));
		if (fowio_wait_bit_kiwwabwe(fowio, PG_wwiteback))
			wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fowio_wait_wwiteback_kiwwabwe);

/**
 * fowio_wait_stabwe() - wait fow wwiteback to finish, if necessawy.
 * @fowio: The fowio to wait on.
 *
 * This function detewmines if the given fowio is wewated to a backing
 * device that wequiwes fowio contents to be hewd stabwe duwing wwiteback.
 * If so, then it wiww wait fow any pending wwiteback to compwete.
 *
 * Context: Sweeps.  Must be cawwed in pwocess context and with
 * no spinwocks hewd.  Cawwew shouwd howd a wefewence on the fowio.
 * If the fowio is not wocked, wwiteback may stawt again aftew wwiteback
 * has finished.
 */
void fowio_wait_stabwe(stwuct fowio *fowio)
{
	if (mapping_stabwe_wwites(fowio_mapping(fowio)))
		fowio_wait_wwiteback(fowio);
}
EXPOWT_SYMBOW_GPW(fowio_wait_stabwe);
