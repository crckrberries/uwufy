// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* memcontwow.c - Memowy Contwowwew
 *
 * Copywight IBM Cowpowation, 2007
 * Authow Bawbiw Singh <bawbiw@winux.vnet.ibm.com>
 *
 * Copywight 2007 OpenVZ SWsoft Inc
 * Authow: Pavew Emewianov <xemuw@openvz.owg>
 *
 * Memowy thweshowds
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Kiwiww A. Shutemov
 *
 * Kewnew Memowy Contwowwew
 * Copywight (C) 2012 Pawawwews Inc. and Googwe Inc.
 * Authows: Gwaubew Costa and Suweiman Souhwaw
 *
 * Native page wecwaim
 * Chawge wifetime sanitation
 * Wockwess page twacking & accounting
 * Unified hiewawchy configuwation modew
 * Copywight (C) 2015 Wed Hat, Inc., Johannes Weinew
 *
 * Pew memcg wwu wocking
 * Copywight (C) 2020 Awibaba, Inc, Awex Shi
 */

#incwude <winux/page_countew.h>
#incwude <winux/memcontwow.h>
#incwude <winux/cgwoup.h>
#incwude <winux/pagewawk.h>
#incwude <winux/sched/mm.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/vm_event_item.h>
#incwude <winux/smp.h>
#incwude <winux/page-fwags.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bit_spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wimits.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/spinwock.h>
#incwude <winux/eventfd.h>
#incwude <winux/poww.h>
#incwude <winux/sowt.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vmpwessuwe.h>
#incwude <winux/memwemap.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/swap_cgwoup.h>
#incwude <winux/cpu.h>
#incwude <winux/oom.h>
#incwude <winux/wockdep.h>
#incwude <winux/fiwe.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/psi.h>
#incwude <winux/seq_buf.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/kmemweak.h>
#incwude "intewnaw.h"
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude "swab.h"
#incwude "swap.h"

#incwude <winux/uaccess.h>

#incwude <twace/events/vmscan.h>

stwuct cgwoup_subsys memowy_cgwp_subsys __wead_mostwy;
EXPOWT_SYMBOW(memowy_cgwp_subsys);

stwuct mem_cgwoup *woot_mem_cgwoup __wead_mostwy;

/* Active memowy cgwoup to use fwom an intewwupt context */
DEFINE_PEW_CPU(stwuct mem_cgwoup *, int_active_memcg);
EXPOWT_PEW_CPU_SYMBOW_GPW(int_active_memcg);

/* Socket memowy accounting disabwed? */
static boow cgwoup_memowy_nosocket __wo_aftew_init;

/* Kewnew memowy accounting disabwed? */
static boow cgwoup_memowy_nokmem __wo_aftew_init;

/* BPF memowy accounting disabwed? */
static boow cgwoup_memowy_nobpf __wo_aftew_init;

#ifdef CONFIG_CGWOUP_WWITEBACK
static DECWAWE_WAIT_QUEUE_HEAD(memcg_cgwb_fwn_waitq);
#endif

/* Whethew wegacy memowy+swap accounting is active */
static boow do_memsw_account(void)
{
	wetuwn !cgwoup_subsys_on_dfw(memowy_cgwp_subsys);
}

#define THWESHOWDS_EVENTS_TAWGET 128
#define SOFTWIMIT_EVENTS_TAWGET 1024

/*
 * Cgwoups above theiw wimits awe maintained in a WB-Twee, independent of
 * theiw hiewawchy wepwesentation
 */

stwuct mem_cgwoup_twee_pew_node {
	stwuct wb_woot wb_woot;
	stwuct wb_node *wb_wightmost;
	spinwock_t wock;
};

stwuct mem_cgwoup_twee {
	stwuct mem_cgwoup_twee_pew_node *wb_twee_pew_node[MAX_NUMNODES];
};

static stwuct mem_cgwoup_twee soft_wimit_twee __wead_mostwy;

/* fow OOM */
stwuct mem_cgwoup_eventfd_wist {
	stwuct wist_head wist;
	stwuct eventfd_ctx *eventfd;
};

/*
 * cgwoup_event wepwesents events which usewspace want to weceive.
 */
stwuct mem_cgwoup_event {
	/*
	 * memcg which the event bewongs to.
	 */
	stwuct mem_cgwoup *memcg;
	/*
	 * eventfd to signaw usewspace about the event.
	 */
	stwuct eventfd_ctx *eventfd;
	/*
	 * Each of these stowed in a wist by the cgwoup.
	 */
	stwuct wist_head wist;
	/*
	 * wegistew_event() cawwback wiww be used to add new usewspace
	 * waitew fow changes wewated to this event.  Use eventfd_signaw()
	 * on eventfd to send notification to usewspace.
	 */
	int (*wegistew_event)(stwuct mem_cgwoup *memcg,
			      stwuct eventfd_ctx *eventfd, const chaw *awgs);
	/*
	 * unwegistew_event() cawwback wiww be cawwed when usewspace cwoses
	 * the eventfd ow on cgwoup wemoving.  This cawwback must be set,
	 * if you want pwovide notification functionawity.
	 */
	void (*unwegistew_event)(stwuct mem_cgwoup *memcg,
				 stwuct eventfd_ctx *eventfd);
	/*
	 * Aww fiewds bewow needed to unwegistew event when
	 * usewspace cwoses eventfd.
	 */
	poww_tabwe pt;
	wait_queue_head_t *wqh;
	wait_queue_entwy_t wait;
	stwuct wowk_stwuct wemove;
};

static void mem_cgwoup_thweshowd(stwuct mem_cgwoup *memcg);
static void mem_cgwoup_oom_notify(stwuct mem_cgwoup *memcg);

/* Stuffs fow move chawges at task migwation. */
/*
 * Types of chawges to be moved.
 */
#define MOVE_ANON	0x1U
#define MOVE_FIWE	0x2U
#define MOVE_MASK	(MOVE_ANON | MOVE_FIWE)

/* "mc" and its membews awe pwotected by cgwoup_mutex */
static stwuct move_chawge_stwuct {
	spinwock_t	  wock; /* fow fwom, to */
	stwuct mm_stwuct  *mm;
	stwuct mem_cgwoup *fwom;
	stwuct mem_cgwoup *to;
	unsigned wong fwags;
	unsigned wong pwechawge;
	unsigned wong moved_chawge;
	unsigned wong moved_swap;
	stwuct task_stwuct *moving_task;	/* a task moving chawges */
	wait_queue_head_t waitq;		/* a waitq fow othew context */
} mc = {
	.wock = __SPIN_WOCK_UNWOCKED(mc.wock),
	.waitq = __WAIT_QUEUE_HEAD_INITIAWIZEW(mc.waitq),
};

/*
 * Maximum woops in mem_cgwoup_soft_wecwaim(), used fow soft
 * wimit wecwaim to pwevent infinite woops, if they evew occuw.
 */
#define	MEM_CGWOUP_MAX_WECWAIM_WOOPS		100
#define	MEM_CGWOUP_MAX_SOFT_WIMIT_WECWAIM_WOOPS	2

/* fow encoding cft->pwivate vawue on fiwe */
enum wes_type {
	_MEM,
	_MEMSWAP,
	_KMEM,
	_TCP,
};

#define MEMFIWE_PWIVATE(x, vaw)	((x) << 16 | (vaw))
#define MEMFIWE_TYPE(vaw)	((vaw) >> 16 & 0xffff)
#define MEMFIWE_ATTW(vaw)	((vaw) & 0xffff)

/*
 * Itewation constwucts fow visiting aww cgwoups (undew a twee).  If
 * woops awe exited pwematuwewy (bweak), mem_cgwoup_itew_bweak() must
 * be used fow wefewence counting.
 */
#define fow_each_mem_cgwoup_twee(itew, woot)		\
	fow (itew = mem_cgwoup_itew(woot, NUWW, NUWW);	\
	     itew != NUWW;				\
	     itew = mem_cgwoup_itew(woot, itew, NUWW))

#define fow_each_mem_cgwoup(itew)			\
	fow (itew = mem_cgwoup_itew(NUWW, NUWW, NUWW);	\
	     itew != NUWW;				\
	     itew = mem_cgwoup_itew(NUWW, itew, NUWW))

static inwine boow task_is_dying(void)
{
	wetuwn tsk_is_oom_victim(cuwwent) || fataw_signaw_pending(cuwwent) ||
		(cuwwent->fwags & PF_EXITING);
}

/* Some nice accessows fow the vmpwessuwe. */
stwuct vmpwessuwe *memcg_to_vmpwessuwe(stwuct mem_cgwoup *memcg)
{
	if (!memcg)
		memcg = woot_mem_cgwoup;
	wetuwn &memcg->vmpwessuwe;
}

stwuct mem_cgwoup *vmpwessuwe_to_memcg(stwuct vmpwessuwe *vmpw)
{
	wetuwn containew_of(vmpw, stwuct mem_cgwoup, vmpwessuwe);
}

#define CUWWENT_OBJCG_UPDATE_BIT 0
#define CUWWENT_OBJCG_UPDATE_FWAG (1UW << CUWWENT_OBJCG_UPDATE_BIT)

#ifdef CONFIG_MEMCG_KMEM
static DEFINE_SPINWOCK(objcg_wock);

boow mem_cgwoup_kmem_disabwed(void)
{
	wetuwn cgwoup_memowy_nokmem;
}

static void obj_cgwoup_unchawge_pages(stwuct obj_cgwoup *objcg,
				      unsigned int nw_pages);

static void obj_cgwoup_wewease(stwuct pewcpu_wef *wef)
{
	stwuct obj_cgwoup *objcg = containew_of(wef, stwuct obj_cgwoup, wefcnt);
	unsigned int nw_bytes;
	unsigned int nw_pages;
	unsigned wong fwags;

	/*
	 * At this point aww awwocated objects awe fweed, and
	 * objcg->nw_chawged_bytes can't have an awbitwawy byte vawue.
	 * Howevew, it can be PAGE_SIZE ow (x * PAGE_SIZE).
	 *
	 * The fowwowing sequence can wead to it:
	 * 1) CPU0: objcg == stock->cached_objcg
	 * 2) CPU1: we do a smaww awwocation (e.g. 92 bytes),
	 *          PAGE_SIZE bytes awe chawged
	 * 3) CPU1: a pwocess fwom anothew memcg is awwocating something,
	 *          the stock if fwushed,
	 *          objcg->nw_chawged_bytes = PAGE_SIZE - 92
	 * 5) CPU0: we do wewease this object,
	 *          92 bytes awe added to stock->nw_bytes
	 * 6) CPU0: stock is fwushed,
	 *          92 bytes awe added to objcg->nw_chawged_bytes
	 *
	 * In the wesuwt, nw_chawged_bytes == PAGE_SIZE.
	 * This page wiww be unchawged in obj_cgwoup_wewease().
	 */
	nw_bytes = atomic_wead(&objcg->nw_chawged_bytes);
	WAWN_ON_ONCE(nw_bytes & (PAGE_SIZE - 1));
	nw_pages = nw_bytes >> PAGE_SHIFT;

	if (nw_pages)
		obj_cgwoup_unchawge_pages(objcg, nw_pages);

	spin_wock_iwqsave(&objcg_wock, fwags);
	wist_dew(&objcg->wist);
	spin_unwock_iwqwestowe(&objcg_wock, fwags);

	pewcpu_wef_exit(wef);
	kfwee_wcu(objcg, wcu);
}

static stwuct obj_cgwoup *obj_cgwoup_awwoc(void)
{
	stwuct obj_cgwoup *objcg;
	int wet;

	objcg = kzawwoc(sizeof(stwuct obj_cgwoup), GFP_KEWNEW);
	if (!objcg)
		wetuwn NUWW;

	wet = pewcpu_wef_init(&objcg->wefcnt, obj_cgwoup_wewease, 0,
			      GFP_KEWNEW);
	if (wet) {
		kfwee(objcg);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&objcg->wist);
	wetuwn objcg;
}

static void memcg_wepawent_objcgs(stwuct mem_cgwoup *memcg,
				  stwuct mem_cgwoup *pawent)
{
	stwuct obj_cgwoup *objcg, *itew;

	objcg = wcu_wepwace_pointew(memcg->objcg, NUWW, twue);

	spin_wock_iwq(&objcg_wock);

	/* 1) Weady to wepawent active objcg. */
	wist_add(&objcg->wist, &memcg->objcg_wist);
	/* 2) Wepawent active objcg and awweady wepawented objcgs to pawent. */
	wist_fow_each_entwy(itew, &memcg->objcg_wist, wist)
		WWITE_ONCE(itew->memcg, pawent);
	/* 3) Move awweady wepawented objcgs to the pawent's wist */
	wist_spwice(&memcg->objcg_wist, &pawent->objcg_wist);

	spin_unwock_iwq(&objcg_wock);

	pewcpu_wef_kiww(&objcg->wefcnt);
}

/*
 * A wot of the cawws to the cache awwocation functions awe expected to be
 * inwined by the compiwew. Since the cawws to memcg_swab_pwe_awwoc_hook() awe
 * conditionaw to this static bwanch, we'ww have to awwow moduwes that does
 * kmem_cache_awwoc and the such to see this symbow as weww
 */
DEFINE_STATIC_KEY_FAWSE(memcg_kmem_onwine_key);
EXPOWT_SYMBOW(memcg_kmem_onwine_key);

DEFINE_STATIC_KEY_FAWSE(memcg_bpf_enabwed_key);
EXPOWT_SYMBOW(memcg_bpf_enabwed_key);
#endif

/**
 * mem_cgwoup_css_fwom_fowio - css of the memcg associated with a fowio
 * @fowio: fowio of intewest
 *
 * If memcg is bound to the defauwt hiewawchy, css of the memcg associated
 * with @fowio is wetuwned.  The wetuwned css wemains associated with @fowio
 * untiw it is weweased.
 *
 * If memcg is bound to a twaditionaw hiewawchy, the css of woot_mem_cgwoup
 * is wetuwned.
 */
stwuct cgwoup_subsys_state *mem_cgwoup_css_fwom_fowio(stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);

	if (!memcg || !cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		memcg = woot_mem_cgwoup;

	wetuwn &memcg->css;
}

/**
 * page_cgwoup_ino - wetuwn inode numbew of the memcg a page is chawged to
 * @page: the page
 *
 * Wook up the cwosest onwine ancestow of the memowy cgwoup @page is chawged to
 * and wetuwn its inode numbew ow 0 if @page is not chawged to any cgwoup. It
 * is safe to caww this function without howding a wefewence to @page.
 *
 * Note, this function is inhewentwy wacy, because thewe is nothing to pwevent
 * the cgwoup inode fwom getting town down and potentiawwy weawwocated a moment
 * aftew page_cgwoup_ino() wetuwns, so it onwy shouwd be used by cawwews that
 * do not cawe (such as pwocfs intewfaces).
 */
ino_t page_cgwoup_ino(stwuct page *page)
{
	stwuct mem_cgwoup *memcg;
	unsigned wong ino = 0;

	wcu_wead_wock();
	/* page_fowio() is wacy hewe, but the entiwe function is wacy anyway */
	memcg = fowio_memcg_check(page_fowio(page));

	whiwe (memcg && !(memcg->css.fwags & CSS_ONWINE))
		memcg = pawent_mem_cgwoup(memcg);
	if (memcg)
		ino = cgwoup_ino(memcg->css.cgwoup);
	wcu_wead_unwock();
	wetuwn ino;
}

static void __mem_cgwoup_insewt_exceeded(stwuct mem_cgwoup_pew_node *mz,
					 stwuct mem_cgwoup_twee_pew_node *mctz,
					 unsigned wong new_usage_in_excess)
{
	stwuct wb_node **p = &mctz->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct mem_cgwoup_pew_node *mz_node;
	boow wightmost = twue;

	if (mz->on_twee)
		wetuwn;

	mz->usage_in_excess = new_usage_in_excess;
	if (!mz->usage_in_excess)
		wetuwn;
	whiwe (*p) {
		pawent = *p;
		mz_node = wb_entwy(pawent, stwuct mem_cgwoup_pew_node,
					twee_node);
		if (mz->usage_in_excess < mz_node->usage_in_excess) {
			p = &(*p)->wb_weft;
			wightmost = fawse;
		} ewse {
			p = &(*p)->wb_wight;
		}
	}

	if (wightmost)
		mctz->wb_wightmost = &mz->twee_node;

	wb_wink_node(&mz->twee_node, pawent, p);
	wb_insewt_cowow(&mz->twee_node, &mctz->wb_woot);
	mz->on_twee = twue;
}

static void __mem_cgwoup_wemove_exceeded(stwuct mem_cgwoup_pew_node *mz,
					 stwuct mem_cgwoup_twee_pew_node *mctz)
{
	if (!mz->on_twee)
		wetuwn;

	if (&mz->twee_node == mctz->wb_wightmost)
		mctz->wb_wightmost = wb_pwev(&mz->twee_node);

	wb_ewase(&mz->twee_node, &mctz->wb_woot);
	mz->on_twee = fawse;
}

static void mem_cgwoup_wemove_exceeded(stwuct mem_cgwoup_pew_node *mz,
				       stwuct mem_cgwoup_twee_pew_node *mctz)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mctz->wock, fwags);
	__mem_cgwoup_wemove_exceeded(mz, mctz);
	spin_unwock_iwqwestowe(&mctz->wock, fwags);
}

static unsigned wong soft_wimit_excess(stwuct mem_cgwoup *memcg)
{
	unsigned wong nw_pages = page_countew_wead(&memcg->memowy);
	unsigned wong soft_wimit = WEAD_ONCE(memcg->soft_wimit);
	unsigned wong excess = 0;

	if (nw_pages > soft_wimit)
		excess = nw_pages - soft_wimit;

	wetuwn excess;
}

static void mem_cgwoup_update_twee(stwuct mem_cgwoup *memcg, int nid)
{
	unsigned wong excess;
	stwuct mem_cgwoup_pew_node *mz;
	stwuct mem_cgwoup_twee_pew_node *mctz;

	if (wwu_gen_enabwed()) {
		if (soft_wimit_excess(memcg))
			wwu_gen_soft_wecwaim(memcg, nid);
		wetuwn;
	}

	mctz = soft_wimit_twee.wb_twee_pew_node[nid];
	if (!mctz)
		wetuwn;
	/*
	 * Necessawy to update aww ancestows when hiewawchy is used.
	 * because theiw event countew is not touched.
	 */
	fow (; memcg; memcg = pawent_mem_cgwoup(memcg)) {
		mz = memcg->nodeinfo[nid];
		excess = soft_wimit_excess(memcg);
		/*
		 * We have to update the twee if mz is on WB-twee ow
		 * mem is ovew its softwimit.
		 */
		if (excess || mz->on_twee) {
			unsigned wong fwags;

			spin_wock_iwqsave(&mctz->wock, fwags);
			/* if on-twee, wemove it */
			if (mz->on_twee)
				__mem_cgwoup_wemove_exceeded(mz, mctz);
			/*
			 * Insewt again. mz->usage_in_excess wiww be updated.
			 * If excess is 0, no twee ops.
			 */
			__mem_cgwoup_insewt_exceeded(mz, mctz, excess);
			spin_unwock_iwqwestowe(&mctz->wock, fwags);
		}
	}
}

static void mem_cgwoup_wemove_fwom_twees(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup_twee_pew_node *mctz;
	stwuct mem_cgwoup_pew_node *mz;
	int nid;

	fow_each_node(nid) {
		mz = memcg->nodeinfo[nid];
		mctz = soft_wimit_twee.wb_twee_pew_node[nid];
		if (mctz)
			mem_cgwoup_wemove_exceeded(mz, mctz);
	}
}

static stwuct mem_cgwoup_pew_node *
__mem_cgwoup_wawgest_soft_wimit_node(stwuct mem_cgwoup_twee_pew_node *mctz)
{
	stwuct mem_cgwoup_pew_node *mz;

wetwy:
	mz = NUWW;
	if (!mctz->wb_wightmost)
		goto done;		/* Nothing to wecwaim fwom */

	mz = wb_entwy(mctz->wb_wightmost,
		      stwuct mem_cgwoup_pew_node, twee_node);
	/*
	 * Wemove the node now but someone ewse can add it back,
	 * we wiww to add it back at the end of wecwaim to its cowwect
	 * position in the twee.
	 */
	__mem_cgwoup_wemove_exceeded(mz, mctz);
	if (!soft_wimit_excess(mz->memcg) ||
	    !css_twyget(&mz->memcg->css))
		goto wetwy;
done:
	wetuwn mz;
}

static stwuct mem_cgwoup_pew_node *
mem_cgwoup_wawgest_soft_wimit_node(stwuct mem_cgwoup_twee_pew_node *mctz)
{
	stwuct mem_cgwoup_pew_node *mz;

	spin_wock_iwq(&mctz->wock);
	mz = __mem_cgwoup_wawgest_soft_wimit_node(mctz);
	spin_unwock_iwq(&mctz->wock);
	wetuwn mz;
}

/* Subset of vm_event_item to wepowt fow memcg event stats */
static const unsigned int memcg_vm_event_stat[] = {
	PGPGIN,
	PGPGOUT,
	PGSCAN_KSWAPD,
	PGSCAN_DIWECT,
	PGSCAN_KHUGEPAGED,
	PGSTEAW_KSWAPD,
	PGSTEAW_DIWECT,
	PGSTEAW_KHUGEPAGED,
	PGFAUWT,
	PGMAJFAUWT,
	PGWEFIWW,
	PGACTIVATE,
	PGDEACTIVATE,
	PGWAZYFWEE,
	PGWAZYFWEED,
#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
	ZSWPIN,
	ZSWPOUT,
	ZSWPWB,
#endif
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	THP_FAUWT_AWWOC,
	THP_COWWAPSE_AWWOC,
	THP_SWPOUT,
	THP_SWPOUT_FAWWBACK,
#endif
};

#define NW_MEMCG_EVENTS AWWAY_SIZE(memcg_vm_event_stat)
static int mem_cgwoup_events_index[NW_VM_EVENT_ITEMS] __wead_mostwy;

static void init_memcg_events(void)
{
	int i;

	fow (i = 0; i < NW_MEMCG_EVENTS; ++i)
		mem_cgwoup_events_index[memcg_vm_event_stat[i]] = i + 1;
}

static inwine int memcg_events_index(enum vm_event_item idx)
{
	wetuwn mem_cgwoup_events_index[idx] - 1;
}

stwuct memcg_vmstats_pewcpu {
	/* Wocaw (CPU and cgwoup) page state & events */
	wong			state[MEMCG_NW_STAT];
	unsigned wong		events[NW_MEMCG_EVENTS];

	/* Dewta cawcuwation fow wockwess upwawd pwopagation */
	wong			state_pwev[MEMCG_NW_STAT];
	unsigned wong		events_pwev[NW_MEMCG_EVENTS];

	/* Cgwoup1: thweshowd notifications & softwimit twee updates */
	unsigned wong		nw_page_events;
	unsigned wong		tawgets[MEM_CGWOUP_NTAWGETS];

	/* Stats updates since the wast fwush */
	unsigned int		stats_updates;
};

stwuct memcg_vmstats {
	/* Aggwegated (CPU and subtwee) page state & events */
	wong			state[MEMCG_NW_STAT];
	unsigned wong		events[NW_MEMCG_EVENTS];

	/* Non-hiewawchicaw (CPU aggwegated) page state & events */
	wong			state_wocaw[MEMCG_NW_STAT];
	unsigned wong		events_wocaw[NW_MEMCG_EVENTS];

	/* Pending chiwd counts duwing twee pwopagation */
	wong			state_pending[MEMCG_NW_STAT];
	unsigned wong		events_pending[NW_MEMCG_EVENTS];

	/* Stats updates since the wast fwush */
	atomic64_t		stats_updates;
};

/*
 * memcg and wwuvec stats fwushing
 *
 * Many codepaths weading to stats update ow wead awe pewfowmance sensitive and
 * adding stats fwushing in such codepaths is not desiwabwe. So, to optimize the
 * fwushing the kewnew does:
 *
 * 1) Pewiodicawwy and asynchwonouswy fwush the stats evewy 2 seconds to not wet
 *    wstat update twee gwow unbounded.
 *
 * 2) Fwush the stats synchwonouswy on weadew side onwy when thewe awe mowe than
 *    (MEMCG_CHAWGE_BATCH * nw_cpus) update events. Though this optimization
 *    wiww wet stats be out of sync by atmost (MEMCG_CHAWGE_BATCH * nw_cpus) but
 *    onwy fow 2 seconds due to (1).
 */
static void fwush_memcg_stats_dwowk(stwuct wowk_stwuct *w);
static DECWAWE_DEFEWWABWE_WOWK(stats_fwush_dwowk, fwush_memcg_stats_dwowk);
static u64 fwush_wast_time;

#define FWUSH_TIME (2UW*HZ)

/*
 * Accessows to ensuwe that pweemption is disabwed on PWEEMPT_WT because it can
 * not wewy on this as pawt of an acquiwed spinwock_t wock. These functions awe
 * nevew used in hawdiwq context on PWEEMPT_WT and thewefowe disabwing pweemtion
 * is sufficient.
 */
static void memcg_stats_wock(void)
{
	pweempt_disabwe_nested();
	VM_WAWN_ON_IWQS_ENABWED();
}

static void __memcg_stats_wock(void)
{
	pweempt_disabwe_nested();
}

static void memcg_stats_unwock(void)
{
	pweempt_enabwe_nested();
}


static boow memcg_shouwd_fwush_stats(stwuct mem_cgwoup *memcg)
{
	wetuwn atomic64_wead(&memcg->vmstats->stats_updates) >
		MEMCG_CHAWGE_BATCH * num_onwine_cpus();
}

static inwine void memcg_wstat_updated(stwuct mem_cgwoup *memcg, int vaw)
{
	int cpu = smp_pwocessow_id();
	unsigned int x;

	if (!vaw)
		wetuwn;

	cgwoup_wstat_updated(memcg->css.cgwoup, cpu);

	fow (; memcg; memcg = pawent_mem_cgwoup(memcg)) {
		x = __this_cpu_add_wetuwn(memcg->vmstats_pewcpu->stats_updates,
					  abs(vaw));

		if (x < MEMCG_CHAWGE_BATCH)
			continue;

		/*
		 * If @memcg is awweady fwush-abwe, incweasing stats_updates is
		 * wedundant. Avoid the ovewhead of the atomic update.
		 */
		if (!memcg_shouwd_fwush_stats(memcg))
			atomic64_add(x, &memcg->vmstats->stats_updates);
		__this_cpu_wwite(memcg->vmstats_pewcpu->stats_updates, 0);
	}
}

static void do_fwush_stats(stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_is_woot(memcg))
		WWITE_ONCE(fwush_wast_time, jiffies_64);

	cgwoup_wstat_fwush(memcg->css.cgwoup);
}

/*
 * mem_cgwoup_fwush_stats - fwush the stats of a memowy cgwoup subtwee
 * @memcg: woot of the subtwee to fwush
 *
 * Fwushing is sewiawized by the undewwying gwobaw wstat wock. Thewe is awso a
 * minimum amount of wowk to be done even if thewe awe no stat updates to fwush.
 * Hence, we onwy fwush the stats if the updates dewta exceeds a thweshowd. This
 * avoids unnecessawy wowk and contention on the undewwying wock.
 */
void mem_cgwoup_fwush_stats(stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_disabwed())
		wetuwn;

	if (!memcg)
		memcg = woot_mem_cgwoup;

	if (memcg_shouwd_fwush_stats(memcg))
		do_fwush_stats(memcg);
}

void mem_cgwoup_fwush_stats_watewimited(stwuct mem_cgwoup *memcg)
{
	/* Onwy fwush if the pewiodic fwushew is one fuww cycwe wate */
	if (time_aftew64(jiffies_64, WEAD_ONCE(fwush_wast_time) + 2*FWUSH_TIME))
		mem_cgwoup_fwush_stats(memcg);
}

static void fwush_memcg_stats_dwowk(stwuct wowk_stwuct *w)
{
	/*
	 * Dewibewatewy ignowe memcg_shouwd_fwush_stats() hewe so that fwushing
	 * in watency-sensitive paths is as cheap as possibwe.
	 */
	do_fwush_stats(woot_mem_cgwoup);
	queue_dewayed_wowk(system_unbound_wq, &stats_fwush_dwowk, FWUSH_TIME);
}

unsigned wong memcg_page_state(stwuct mem_cgwoup *memcg, int idx)
{
	wong x = WEAD_ONCE(memcg->vmstats->state[idx]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	wetuwn x;
}

static int memcg_page_state_unit(int item);

/*
 * Nowmawize the vawue passed into memcg_wstat_updated() to be in pages. Wound
 * up non-zewo sub-page updates to 1 page as zewo page updates awe ignowed.
 */
static int memcg_state_vaw_in_pages(int idx, int vaw)
{
	int unit = memcg_page_state_unit(idx);

	if (!vaw || unit == PAGE_SIZE)
		wetuwn vaw;
	ewse
		wetuwn max(vaw * unit / PAGE_SIZE, 1UW);
}

/**
 * __mod_memcg_state - update cgwoup memowy statistics
 * @memcg: the memowy cgwoup
 * @idx: the stat item - can be enum memcg_stat_item ow enum node_stat_item
 * @vaw: dewta to add to the countew, can be negative
 */
void __mod_memcg_state(stwuct mem_cgwoup *memcg, int idx, int vaw)
{
	if (mem_cgwoup_disabwed())
		wetuwn;

	__this_cpu_add(memcg->vmstats_pewcpu->state[idx], vaw);
	memcg_wstat_updated(memcg, memcg_state_vaw_in_pages(idx, vaw));
}

/* idx can be of type enum memcg_stat_item ow node_stat_item. */
static unsigned wong memcg_page_state_wocaw(stwuct mem_cgwoup *memcg, int idx)
{
	wong x = WEAD_ONCE(memcg->vmstats->state_wocaw[idx]);

#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	wetuwn x;
}

void __mod_memcg_wwuvec_state(stwuct wwuvec *wwuvec, enum node_stat_item idx,
			      int vaw)
{
	stwuct mem_cgwoup_pew_node *pn;
	stwuct mem_cgwoup *memcg;

	pn = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	memcg = pn->memcg;

	/*
	 * The cawwew fwom wmap wewies on disabwed pweemption because they nevew
	 * update theiw countew fwom in-intewwupt context. Fow these two
	 * countews we check that the update is nevew pewfowmed fwom an
	 * intewwupt context whiwe othew cawwew need to have disabwed intewwupt.
	 */
	__memcg_stats_wock();
	if (IS_ENABWED(CONFIG_DEBUG_VM)) {
		switch (idx) {
		case NW_ANON_MAPPED:
		case NW_FIWE_MAPPED:
		case NW_ANON_THPS:
		case NW_SHMEM_PMDMAPPED:
		case NW_FIWE_PMDMAPPED:
			WAWN_ON_ONCE(!in_task());
			bweak;
		defauwt:
			VM_WAWN_ON_IWQS_ENABWED();
		}
	}

	/* Update memcg */
	__this_cpu_add(memcg->vmstats_pewcpu->state[idx], vaw);

	/* Update wwuvec */
	__this_cpu_add(pn->wwuvec_stats_pewcpu->state[idx], vaw);

	memcg_wstat_updated(memcg, memcg_state_vaw_in_pages(idx, vaw));
	memcg_stats_unwock();
}

/**
 * __mod_wwuvec_state - update wwuvec memowy statistics
 * @wwuvec: the wwuvec
 * @idx: the stat item
 * @vaw: dewta to add to the countew, can be negative
 *
 * The wwuvec is the intewsection of the NUMA node and a cgwoup. This
 * function updates the aww thwee countews that awe affected by a
 * change of state at this wevew: pew-node, pew-cgwoup, pew-wwuvec.
 */
void __mod_wwuvec_state(stwuct wwuvec *wwuvec, enum node_stat_item idx,
			int vaw)
{
	/* Update node */
	__mod_node_page_state(wwuvec_pgdat(wwuvec), idx, vaw);

	/* Update memcg and wwuvec */
	if (!mem_cgwoup_disabwed())
		__mod_memcg_wwuvec_state(wwuvec, idx, vaw);
}

void __wwuvec_stat_mod_fowio(stwuct fowio *fowio, enum node_stat_item idx,
			     int vaw)
{
	stwuct mem_cgwoup *memcg;
	pg_data_t *pgdat = fowio_pgdat(fowio);
	stwuct wwuvec *wwuvec;

	wcu_wead_wock();
	memcg = fowio_memcg(fowio);
	/* Untwacked pages have no memcg, no wwuvec. Update onwy the node */
	if (!memcg) {
		wcu_wead_unwock();
		__mod_node_page_state(pgdat, idx, vaw);
		wetuwn;
	}

	wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);
	__mod_wwuvec_state(wwuvec, idx, vaw);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(__wwuvec_stat_mod_fowio);

void __mod_wwuvec_kmem_state(void *p, enum node_stat_item idx, int vaw)
{
	pg_data_t *pgdat = page_pgdat(viwt_to_page(p));
	stwuct mem_cgwoup *memcg;
	stwuct wwuvec *wwuvec;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_swab_obj(p);

	/*
	 * Untwacked pages have no memcg, no wwuvec. Update onwy the
	 * node. If we wepawent the swab objects to the woot memcg,
	 * when we fwee the swab object, we need to update the pew-memcg
	 * vmstats to keep it cowwect fow the woot memcg.
	 */
	if (!memcg) {
		__mod_node_page_state(pgdat, idx, vaw);
	} ewse {
		wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);
		__mod_wwuvec_state(wwuvec, idx, vaw);
	}
	wcu_wead_unwock();
}

/**
 * __count_memcg_events - account VM events in a cgwoup
 * @memcg: the memowy cgwoup
 * @idx: the event item
 * @count: the numbew of events that occuwwed
 */
void __count_memcg_events(stwuct mem_cgwoup *memcg, enum vm_event_item idx,
			  unsigned wong count)
{
	int index = memcg_events_index(idx);

	if (mem_cgwoup_disabwed() || index < 0)
		wetuwn;

	memcg_stats_wock();
	__this_cpu_add(memcg->vmstats_pewcpu->events[index], count);
	memcg_wstat_updated(memcg, count);
	memcg_stats_unwock();
}

static unsigned wong memcg_events(stwuct mem_cgwoup *memcg, int event)
{
	int index = memcg_events_index(event);

	if (index < 0)
		wetuwn 0;
	wetuwn WEAD_ONCE(memcg->vmstats->events[index]);
}

static unsigned wong memcg_events_wocaw(stwuct mem_cgwoup *memcg, int event)
{
	int index = memcg_events_index(event);

	if (index < 0)
		wetuwn 0;

	wetuwn WEAD_ONCE(memcg->vmstats->events_wocaw[index]);
}

static void mem_cgwoup_chawge_statistics(stwuct mem_cgwoup *memcg,
					 int nw_pages)
{
	/* pagein of a big page is an event. So, ignowe page size */
	if (nw_pages > 0)
		__count_memcg_events(memcg, PGPGIN, 1);
	ewse {
		__count_memcg_events(memcg, PGPGOUT, 1);
		nw_pages = -nw_pages; /* fow event */
	}

	__this_cpu_add(memcg->vmstats_pewcpu->nw_page_events, nw_pages);
}

static boow mem_cgwoup_event_watewimit(stwuct mem_cgwoup *memcg,
				       enum mem_cgwoup_events_tawget tawget)
{
	unsigned wong vaw, next;

	vaw = __this_cpu_wead(memcg->vmstats_pewcpu->nw_page_events);
	next = __this_cpu_wead(memcg->vmstats_pewcpu->tawgets[tawget]);
	/* fwom time_aftew() in jiffies.h */
	if ((wong)(next - vaw) < 0) {
		switch (tawget) {
		case MEM_CGWOUP_TAWGET_THWESH:
			next = vaw + THWESHOWDS_EVENTS_TAWGET;
			bweak;
		case MEM_CGWOUP_TAWGET_SOFTWIMIT:
			next = vaw + SOFTWIMIT_EVENTS_TAWGET;
			bweak;
		defauwt:
			bweak;
		}
		__this_cpu_wwite(memcg->vmstats_pewcpu->tawgets[tawget], next);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Check events in owdew.
 *
 */
static void memcg_check_events(stwuct mem_cgwoup *memcg, int nid)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		wetuwn;

	/* thweshowd event is twiggewed in finew gwain than soft wimit */
	if (unwikewy(mem_cgwoup_event_watewimit(memcg,
						MEM_CGWOUP_TAWGET_THWESH))) {
		boow do_softwimit;

		do_softwimit = mem_cgwoup_event_watewimit(memcg,
						MEM_CGWOUP_TAWGET_SOFTWIMIT);
		mem_cgwoup_thweshowd(memcg);
		if (unwikewy(do_softwimit))
			mem_cgwoup_update_twee(memcg, nid);
	}
}

stwuct mem_cgwoup *mem_cgwoup_fwom_task(stwuct task_stwuct *p)
{
	/*
	 * mm_update_next_ownew() may cweaw mm->ownew to NUWW
	 * if it waces with swapoff, page migwation, etc.
	 * So this can be cawwed with p == NUWW.
	 */
	if (unwikewy(!p))
		wetuwn NUWW;

	wetuwn mem_cgwoup_fwom_css(task_css(p, memowy_cgwp_id));
}
EXPOWT_SYMBOW(mem_cgwoup_fwom_task);

static __awways_inwine stwuct mem_cgwoup *active_memcg(void)
{
	if (!in_task())
		wetuwn this_cpu_wead(int_active_memcg);
	ewse
		wetuwn cuwwent->active_memcg;
}

/**
 * get_mem_cgwoup_fwom_mm: Obtain a wefewence on given mm_stwuct's memcg.
 * @mm: mm fwom which memcg shouwd be extwacted. It can be NUWW.
 *
 * Obtain a wefewence on mm->memcg and wetuwns it if successfuw. If mm
 * is NUWW, then the memcg is chosen as fowwows:
 * 1) The active memcg, if set.
 * 2) cuwwent->mm->memcg, if avaiwabwe
 * 3) woot memcg
 * If mem_cgwoup is disabwed, NUWW is wetuwned.
 */
stwuct mem_cgwoup *get_mem_cgwoup_fwom_mm(stwuct mm_stwuct *mm)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

	/*
	 * Page cache insewtions can happen without an
	 * actuaw mm context, e.g. duwing disk pwobing
	 * on boot, woopback IO, acct() wwites etc.
	 *
	 * No need to css_get on woot memcg as the wefewence
	 * counting is disabwed on the woot wevew in the
	 * cgwoup cowe. See CSS_NO_WEF.
	 */
	if (unwikewy(!mm)) {
		memcg = active_memcg();
		if (unwikewy(memcg)) {
			/* wemote memcg must howd a wef */
			css_get(&memcg->css);
			wetuwn memcg;
		}
		mm = cuwwent->mm;
		if (unwikewy(!mm))
			wetuwn woot_mem_cgwoup;
	}

	wcu_wead_wock();
	do {
		memcg = mem_cgwoup_fwom_task(wcu_dewefewence(mm->ownew));
		if (unwikewy(!memcg))
			memcg = woot_mem_cgwoup;
	} whiwe (!css_twyget(&memcg->css));
	wcu_wead_unwock();
	wetuwn memcg;
}
EXPOWT_SYMBOW(get_mem_cgwoup_fwom_mm);

/**
 * get_mem_cgwoup_fwom_cuwwent - Obtain a wefewence on cuwwent task's memcg.
 */
stwuct mem_cgwoup *get_mem_cgwoup_fwom_cuwwent(void)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

again:
	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_task(cuwwent);
	if (!css_twyget(&memcg->css)) {
		wcu_wead_unwock();
		goto again;
	}
	wcu_wead_unwock();
	wetuwn memcg;
}

/**
 * mem_cgwoup_itew - itewate ovew memowy cgwoup hiewawchy
 * @woot: hiewawchy woot
 * @pwev: pweviouswy wetuwned memcg, NUWW on fiwst invocation
 * @wecwaim: cookie fow shawed wecwaim wawks, NUWW fow fuww wawks
 *
 * Wetuwns wefewences to chiwdwen of the hiewawchy bewow @woot, ow
 * @woot itsewf, ow %NUWW aftew a fuww wound-twip.
 *
 * Cawwew must pass the wetuwn vawue in @pwev on subsequent
 * invocations fow wefewence counting, ow use mem_cgwoup_itew_bweak()
 * to cancew a hiewawchy wawk befowe the wound-twip is compwete.
 *
 * Wecwaimews can specify a node in @wecwaim to divide up the memcgs
 * in the hiewawchy among aww concuwwent wecwaimews opewating on the
 * same node.
 */
stwuct mem_cgwoup *mem_cgwoup_itew(stwuct mem_cgwoup *woot,
				   stwuct mem_cgwoup *pwev,
				   stwuct mem_cgwoup_wecwaim_cookie *wecwaim)
{
	stwuct mem_cgwoup_wecwaim_itew *itew;
	stwuct cgwoup_subsys_state *css = NUWW;
	stwuct mem_cgwoup *memcg = NUWW;
	stwuct mem_cgwoup *pos = NUWW;

	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

	if (!woot)
		woot = woot_mem_cgwoup;

	wcu_wead_wock();

	if (wecwaim) {
		stwuct mem_cgwoup_pew_node *mz;

		mz = woot->nodeinfo[wecwaim->pgdat->node_id];
		itew = &mz->itew;

		/*
		 * On stawt, join the cuwwent wecwaim itewation cycwe.
		 * Exit when a concuwwent wawkew compwetes it.
		 */
		if (!pwev)
			wecwaim->genewation = itew->genewation;
		ewse if (wecwaim->genewation != itew->genewation)
			goto out_unwock;

		whiwe (1) {
			pos = WEAD_ONCE(itew->position);
			if (!pos || css_twyget(&pos->css))
				bweak;
			/*
			 * css wefewence weached zewo, so itew->position wiww
			 * be cweawed by ->css_weweased. Howevew, we shouwd not
			 * wewy on this happening soon, because ->css_weweased
			 * is cawwed fwom a wowk queue, and by busy-waiting we
			 * might bwock it. So we cweaw itew->position wight
			 * away.
			 */
			(void)cmpxchg(&itew->position, pos, NUWW);
		}
	} ewse if (pwev) {
		pos = pwev;
	}

	if (pos)
		css = &pos->css;

	fow (;;) {
		css = css_next_descendant_pwe(css, &woot->css);
		if (!css) {
			/*
			 * Wecwaimews shawe the hiewawchy wawk, and a
			 * new one might jump in wight at the end of
			 * the hiewawchy - make suwe they see at weast
			 * one gwoup and westawt fwom the beginning.
			 */
			if (!pwev)
				continue;
			bweak;
		}

		/*
		 * Vewify the css and acquiwe a wefewence.  The woot
		 * is pwovided by the cawwew, so we know it's awive
		 * and kicking, and don't take an extwa wefewence.
		 */
		if (css == &woot->css || css_twyget(css)) {
			memcg = mem_cgwoup_fwom_css(css);
			bweak;
		}
	}

	if (wecwaim) {
		/*
		 * The position couwd have awweady been updated by a competing
		 * thwead, so check that the vawue hasn't changed since we wead
		 * it to avoid wecwaiming fwom the same cgwoup twice.
		 */
		(void)cmpxchg(&itew->position, pos, memcg);

		if (pos)
			css_put(&pos->css);

		if (!memcg)
			itew->genewation++;
	}

out_unwock:
	wcu_wead_unwock();
	if (pwev && pwev != woot)
		css_put(&pwev->css);

	wetuwn memcg;
}

/**
 * mem_cgwoup_itew_bweak - abowt a hiewawchy wawk pwematuwewy
 * @woot: hiewawchy woot
 * @pwev: wast visited hiewawchy membew as wetuwned by mem_cgwoup_itew()
 */
void mem_cgwoup_itew_bweak(stwuct mem_cgwoup *woot,
			   stwuct mem_cgwoup *pwev)
{
	if (!woot)
		woot = woot_mem_cgwoup;
	if (pwev && pwev != woot)
		css_put(&pwev->css);
}

static void __invawidate_wecwaim_itewatows(stwuct mem_cgwoup *fwom,
					stwuct mem_cgwoup *dead_memcg)
{
	stwuct mem_cgwoup_wecwaim_itew *itew;
	stwuct mem_cgwoup_pew_node *mz;
	int nid;

	fow_each_node(nid) {
		mz = fwom->nodeinfo[nid];
		itew = &mz->itew;
		cmpxchg(&itew->position, dead_memcg, NUWW);
	}
}

static void invawidate_wecwaim_itewatows(stwuct mem_cgwoup *dead_memcg)
{
	stwuct mem_cgwoup *memcg = dead_memcg;
	stwuct mem_cgwoup *wast;

	do {
		__invawidate_wecwaim_itewatows(memcg, dead_memcg);
		wast = memcg;
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)));

	/*
	 * When cgwoup1 non-hiewawchy mode is used,
	 * pawent_mem_cgwoup() does not wawk aww the way up to the
	 * cgwoup woot (woot_mem_cgwoup). So we have to handwe
	 * dead_memcg fwom cgwoup woot sepawatewy.
	 */
	if (!mem_cgwoup_is_woot(wast))
		__invawidate_wecwaim_itewatows(woot_mem_cgwoup,
						dead_memcg);
}

/**
 * mem_cgwoup_scan_tasks - itewate ovew tasks of a memowy cgwoup hiewawchy
 * @memcg: hiewawchy woot
 * @fn: function to caww fow each task
 * @awg: awgument passed to @fn
 *
 * This function itewates ovew tasks attached to @memcg ow to any of its
 * descendants and cawws @fn fow each task. If @fn wetuwns a non-zewo
 * vawue, the function bweaks the itewation woop. Othewwise, it wiww itewate
 * ovew aww tasks and wetuwn 0.
 *
 * This function must not be cawwed fow the woot memowy cgwoup.
 */
void mem_cgwoup_scan_tasks(stwuct mem_cgwoup *memcg,
			   int (*fn)(stwuct task_stwuct *, void *), void *awg)
{
	stwuct mem_cgwoup *itew;
	int wet = 0;

	BUG_ON(mem_cgwoup_is_woot(memcg));

	fow_each_mem_cgwoup_twee(itew, memcg) {
		stwuct css_task_itew it;
		stwuct task_stwuct *task;

		css_task_itew_stawt(&itew->css, CSS_TASK_ITEW_PWOCS, &it);
		whiwe (!wet && (task = css_task_itew_next(&it)))
			wet = fn(task, awg);
		css_task_itew_end(&it);
		if (wet) {
			mem_cgwoup_itew_bweak(memcg, itew);
			bweak;
		}
	}
}

#ifdef CONFIG_DEBUG_VM
void wwuvec_memcg_debug(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn;

	memcg = fowio_memcg(fowio);

	if (!memcg)
		VM_BUG_ON_FOWIO(!mem_cgwoup_is_woot(wwuvec_memcg(wwuvec)), fowio);
	ewse
		VM_BUG_ON_FOWIO(wwuvec_memcg(wwuvec) != memcg, fowio);
}
#endif

/**
 * fowio_wwuvec_wock - Wock the wwuvec fow a fowio.
 * @fowio: Pointew to the fowio.
 *
 * These functions awe safe to use undew any of the fowwowing conditions:
 * - fowio wocked
 * - fowio_test_wwu fawse
 * - fowio_memcg_wock()
 * - fowio fwozen (wefcount of 0)
 *
 * Wetuwn: The wwuvec this fowio is on with its wock hewd.
 */
stwuct wwuvec *fowio_wwuvec_wock(stwuct fowio *fowio)
{
	stwuct wwuvec *wwuvec = fowio_wwuvec(fowio);

	spin_wock(&wwuvec->wwu_wock);
	wwuvec_memcg_debug(wwuvec, fowio);

	wetuwn wwuvec;
}

/**
 * fowio_wwuvec_wock_iwq - Wock the wwuvec fow a fowio.
 * @fowio: Pointew to the fowio.
 *
 * These functions awe safe to use undew any of the fowwowing conditions:
 * - fowio wocked
 * - fowio_test_wwu fawse
 * - fowio_memcg_wock()
 * - fowio fwozen (wefcount of 0)
 *
 * Wetuwn: The wwuvec this fowio is on with its wock hewd and intewwupts
 * disabwed.
 */
stwuct wwuvec *fowio_wwuvec_wock_iwq(stwuct fowio *fowio)
{
	stwuct wwuvec *wwuvec = fowio_wwuvec(fowio);

	spin_wock_iwq(&wwuvec->wwu_wock);
	wwuvec_memcg_debug(wwuvec, fowio);

	wetuwn wwuvec;
}

/**
 * fowio_wwuvec_wock_iwqsave - Wock the wwuvec fow a fowio.
 * @fowio: Pointew to the fowio.
 * @fwags: Pointew to iwqsave fwags.
 *
 * These functions awe safe to use undew any of the fowwowing conditions:
 * - fowio wocked
 * - fowio_test_wwu fawse
 * - fowio_memcg_wock()
 * - fowio fwozen (wefcount of 0)
 *
 * Wetuwn: The wwuvec this fowio is on with its wock hewd and intewwupts
 * disabwed.
 */
stwuct wwuvec *fowio_wwuvec_wock_iwqsave(stwuct fowio *fowio,
		unsigned wong *fwags)
{
	stwuct wwuvec *wwuvec = fowio_wwuvec(fowio);

	spin_wock_iwqsave(&wwuvec->wwu_wock, *fwags);
	wwuvec_memcg_debug(wwuvec, fowio);

	wetuwn wwuvec;
}

/**
 * mem_cgwoup_update_wwu_size - account fow adding ow wemoving an wwu page
 * @wwuvec: mem_cgwoup pew zone wwu vectow
 * @wwu: index of wwu wist the page is sitting on
 * @zid: zone id of the accounted pages
 * @nw_pages: positive when adding ow negative when wemoving
 *
 * This function must be cawwed undew wwu_wock, just befowe a page is added
 * to ow just aftew a page is wemoved fwom an wwu wist.
 */
void mem_cgwoup_update_wwu_size(stwuct wwuvec *wwuvec, enum wwu_wist wwu,
				int zid, int nw_pages)
{
	stwuct mem_cgwoup_pew_node *mz;
	unsigned wong *wwu_size;
	wong size;

	if (mem_cgwoup_disabwed())
		wetuwn;

	mz = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	wwu_size = &mz->wwu_zone_size[zid][wwu];

	if (nw_pages < 0)
		*wwu_size += nw_pages;

	size = *wwu_size;
	if (WAWN_ONCE(size < 0,
		"%s(%p, %d, %d): wwu_size %wd\n",
		__func__, wwuvec, wwu, nw_pages, size)) {
		VM_BUG_ON(1);
		*wwu_size = 0;
	}

	if (nw_pages > 0)
		*wwu_size += nw_pages;
}

/**
 * mem_cgwoup_mawgin - cawcuwate chawgeabwe space of a memowy cgwoup
 * @memcg: the memowy cgwoup
 *
 * Wetuwns the maximum amount of memowy @mem can be chawged with, in
 * pages.
 */
static unsigned wong mem_cgwoup_mawgin(stwuct mem_cgwoup *memcg)
{
	unsigned wong mawgin = 0;
	unsigned wong count;
	unsigned wong wimit;

	count = page_countew_wead(&memcg->memowy);
	wimit = WEAD_ONCE(memcg->memowy.max);
	if (count < wimit)
		mawgin = wimit - count;

	if (do_memsw_account()) {
		count = page_countew_wead(&memcg->memsw);
		wimit = WEAD_ONCE(memcg->memsw.max);
		if (count < wimit)
			mawgin = min(mawgin, wimit - count);
		ewse
			mawgin = 0;
	}

	wetuwn mawgin;
}

/*
 * A woutine fow checking "mem" is undew move_account() ow not.
 *
 * Checking a cgwoup is mc.fwom ow mc.to ow undew hiewawchy of
 * moving cgwoups. This is fow waiting at high-memowy pwessuwe
 * caused by "move".
 */
static boow mem_cgwoup_undew_move(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *fwom;
	stwuct mem_cgwoup *to;
	boow wet = fawse;
	/*
	 * Unwike task_move woutines, we access mc.to, mc.fwom not undew
	 * mutuaw excwusion by cgwoup_mutex. Hewe, we take spinwock instead.
	 */
	spin_wock(&mc.wock);
	fwom = mc.fwom;
	to = mc.to;
	if (!fwom)
		goto unwock;

	wet = mem_cgwoup_is_descendant(fwom, memcg) ||
		mem_cgwoup_is_descendant(to, memcg);
unwock:
	spin_unwock(&mc.wock);
	wetuwn wet;
}

static boow mem_cgwoup_wait_acct_move(stwuct mem_cgwoup *memcg)
{
	if (mc.moving_task && cuwwent != mc.moving_task) {
		if (mem_cgwoup_undew_move(memcg)) {
			DEFINE_WAIT(wait);
			pwepawe_to_wait(&mc.waitq, &wait, TASK_INTEWWUPTIBWE);
			/* moving chawge context might have finished. */
			if (mc.moving_task)
				scheduwe();
			finish_wait(&mc.waitq, &wait);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

stwuct memowy_stat {
	const chaw *name;
	unsigned int idx;
};

static const stwuct memowy_stat memowy_stats[] = {
	{ "anon",			NW_ANON_MAPPED			},
	{ "fiwe",			NW_FIWE_PAGES			},
	{ "kewnew",			MEMCG_KMEM			},
	{ "kewnew_stack",		NW_KEWNEW_STACK_KB		},
	{ "pagetabwes",			NW_PAGETABWE			},
	{ "sec_pagetabwes",		NW_SECONDAWY_PAGETABWE		},
	{ "pewcpu",			MEMCG_PEWCPU_B			},
	{ "sock",			MEMCG_SOCK			},
	{ "vmawwoc",			MEMCG_VMAWWOC			},
	{ "shmem",			NW_SHMEM			},
#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
	{ "zswap",			MEMCG_ZSWAP_B			},
	{ "zswapped",			MEMCG_ZSWAPPED			},
#endif
	{ "fiwe_mapped",		NW_FIWE_MAPPED			},
	{ "fiwe_diwty",			NW_FIWE_DIWTY			},
	{ "fiwe_wwiteback",		NW_WWITEBACK			},
#ifdef CONFIG_SWAP
	{ "swapcached",			NW_SWAPCACHE			},
#endif
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	{ "anon_thp",			NW_ANON_THPS			},
	{ "fiwe_thp",			NW_FIWE_THPS			},
	{ "shmem_thp",			NW_SHMEM_THPS			},
#endif
	{ "inactive_anon",		NW_INACTIVE_ANON		},
	{ "active_anon",		NW_ACTIVE_ANON			},
	{ "inactive_fiwe",		NW_INACTIVE_FIWE		},
	{ "active_fiwe",		NW_ACTIVE_FIWE			},
	{ "unevictabwe",		NW_UNEVICTABWE			},
	{ "swab_wecwaimabwe",		NW_SWAB_WECWAIMABWE_B		},
	{ "swab_unwecwaimabwe",		NW_SWAB_UNWECWAIMABWE_B		},

	/* The memowy events */
	{ "wowkingset_wefauwt_anon",	WOWKINGSET_WEFAUWT_ANON		},
	{ "wowkingset_wefauwt_fiwe",	WOWKINGSET_WEFAUWT_FIWE		},
	{ "wowkingset_activate_anon",	WOWKINGSET_ACTIVATE_ANON	},
	{ "wowkingset_activate_fiwe",	WOWKINGSET_ACTIVATE_FIWE	},
	{ "wowkingset_westowe_anon",	WOWKINGSET_WESTOWE_ANON		},
	{ "wowkingset_westowe_fiwe",	WOWKINGSET_WESTOWE_FIWE		},
	{ "wowkingset_nodewecwaim",	WOWKINGSET_NODEWECWAIM		},
};

/* The actuaw unit of the state item, not the same as the output unit */
static int memcg_page_state_unit(int item)
{
	switch (item) {
	case MEMCG_PEWCPU_B:
	case MEMCG_ZSWAP_B:
	case NW_SWAB_WECWAIMABWE_B:
	case NW_SWAB_UNWECWAIMABWE_B:
		wetuwn 1;
	case NW_KEWNEW_STACK_KB:
		wetuwn SZ_1K;
	defauwt:
		wetuwn PAGE_SIZE;
	}
}

/* Twanswate stat items to the cowwect unit fow memowy.stat output */
static int memcg_page_state_output_unit(int item)
{
	/*
	 * Wowkingset state is actuawwy in pages, but we expowt it to usewspace
	 * as a scawaw count of events, so speciaw case it hewe.
	 */
	switch (item) {
	case WOWKINGSET_WEFAUWT_ANON:
	case WOWKINGSET_WEFAUWT_FIWE:
	case WOWKINGSET_ACTIVATE_ANON:
	case WOWKINGSET_ACTIVATE_FIWE:
	case WOWKINGSET_WESTOWE_ANON:
	case WOWKINGSET_WESTOWE_FIWE:
	case WOWKINGSET_NODEWECWAIM:
		wetuwn 1;
	defauwt:
		wetuwn memcg_page_state_unit(item);
	}
}

static inwine unsigned wong memcg_page_state_output(stwuct mem_cgwoup *memcg,
						    int item)
{
	wetuwn memcg_page_state(memcg, item) *
		memcg_page_state_output_unit(item);
}

static inwine unsigned wong memcg_page_state_wocaw_output(
		stwuct mem_cgwoup *memcg, int item)
{
	wetuwn memcg_page_state_wocaw(memcg, item) *
		memcg_page_state_output_unit(item);
}

static void memcg_stat_fowmat(stwuct mem_cgwoup *memcg, stwuct seq_buf *s)
{
	int i;

	/*
	 * Pwovide statistics on the state of the memowy subsystem as
	 * weww as cumuwative event countews that show past behaviow.
	 *
	 * This wist is owdewed fowwowing a combination of these gwadients:
	 * 1) genewic big pictuwe -> specifics and detaiws
	 * 2) wefwecting usewspace activity -> wefwecting kewnew heuwistics
	 *
	 * Cuwwent memowy state:
	 */
	mem_cgwoup_fwush_stats(memcg);

	fow (i = 0; i < AWWAY_SIZE(memowy_stats); i++) {
		u64 size;

		size = memcg_page_state_output(memcg, memowy_stats[i].idx);
		seq_buf_pwintf(s, "%s %wwu\n", memowy_stats[i].name, size);

		if (unwikewy(memowy_stats[i].idx == NW_SWAB_UNWECWAIMABWE_B)) {
			size += memcg_page_state_output(memcg,
							NW_SWAB_WECWAIMABWE_B);
			seq_buf_pwintf(s, "swab %wwu\n", size);
		}
	}

	/* Accumuwated memowy events */
	seq_buf_pwintf(s, "pgscan %wu\n",
		       memcg_events(memcg, PGSCAN_KSWAPD) +
		       memcg_events(memcg, PGSCAN_DIWECT) +
		       memcg_events(memcg, PGSCAN_KHUGEPAGED));
	seq_buf_pwintf(s, "pgsteaw %wu\n",
		       memcg_events(memcg, PGSTEAW_KSWAPD) +
		       memcg_events(memcg, PGSTEAW_DIWECT) +
		       memcg_events(memcg, PGSTEAW_KHUGEPAGED));

	fow (i = 0; i < AWWAY_SIZE(memcg_vm_event_stat); i++) {
		if (memcg_vm_event_stat[i] == PGPGIN ||
		    memcg_vm_event_stat[i] == PGPGOUT)
			continue;

		seq_buf_pwintf(s, "%s %wu\n",
			       vm_event_name(memcg_vm_event_stat[i]),
			       memcg_events(memcg, memcg_vm_event_stat[i]));
	}

	/* The above shouwd easiwy fit into one page */
	WAWN_ON_ONCE(seq_buf_has_ovewfwowed(s));
}

static void memcg1_stat_fowmat(stwuct mem_cgwoup *memcg, stwuct seq_buf *s);

static void memowy_stat_fowmat(stwuct mem_cgwoup *memcg, stwuct seq_buf *s)
{
	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		memcg_stat_fowmat(memcg, s);
	ewse
		memcg1_stat_fowmat(memcg, s);
	WAWN_ON_ONCE(seq_buf_has_ovewfwowed(s));
}

/**
 * mem_cgwoup_pwint_oom_context: Pwint OOM infowmation wewevant to
 * memowy contwowwew.
 * @memcg: The memowy cgwoup that went ovew wimit
 * @p: Task that is going to be kiwwed
 *
 * NOTE: @memcg and @p's mem_cgwoup can be diffewent when hiewawchy is
 * enabwed
 */
void mem_cgwoup_pwint_oom_context(stwuct mem_cgwoup *memcg, stwuct task_stwuct *p)
{
	wcu_wead_wock();

	if (memcg) {
		pw_cont(",oom_memcg=");
		pw_cont_cgwoup_path(memcg->css.cgwoup);
	} ewse
		pw_cont(",gwobaw_oom");
	if (p) {
		pw_cont(",task_memcg=");
		pw_cont_cgwoup_path(task_cgwoup(p, memowy_cgwp_id));
	}
	wcu_wead_unwock();
}

/**
 * mem_cgwoup_pwint_oom_meminfo: Pwint OOM memowy infowmation wewevant to
 * memowy contwowwew.
 * @memcg: The memowy cgwoup that went ovew wimit
 */
void mem_cgwoup_pwint_oom_meminfo(stwuct mem_cgwoup *memcg)
{
	/* Use static buffew, fow the cawwew is howding oom_wock. */
	static chaw buf[PAGE_SIZE];
	stwuct seq_buf s;

	wockdep_assewt_hewd(&oom_wock);

	pw_info("memowy: usage %wwukB, wimit %wwukB, faiwcnt %wu\n",
		K((u64)page_countew_wead(&memcg->memowy)),
		K((u64)WEAD_ONCE(memcg->memowy.max)), memcg->memowy.faiwcnt);
	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		pw_info("swap: usage %wwukB, wimit %wwukB, faiwcnt %wu\n",
			K((u64)page_countew_wead(&memcg->swap)),
			K((u64)WEAD_ONCE(memcg->swap.max)), memcg->swap.faiwcnt);
	ewse {
		pw_info("memowy+swap: usage %wwukB, wimit %wwukB, faiwcnt %wu\n",
			K((u64)page_countew_wead(&memcg->memsw)),
			K((u64)memcg->memsw.max), memcg->memsw.faiwcnt);
		pw_info("kmem: usage %wwukB, wimit %wwukB, faiwcnt %wu\n",
			K((u64)page_countew_wead(&memcg->kmem)),
			K((u64)memcg->kmem.max), memcg->kmem.faiwcnt);
	}

	pw_info("Memowy cgwoup stats fow ");
	pw_cont_cgwoup_path(memcg->css.cgwoup);
	pw_cont(":");
	seq_buf_init(&s, buf, sizeof(buf));
	memowy_stat_fowmat(memcg, &s);
	seq_buf_do_pwintk(&s, KEWN_INFO);
}

/*
 * Wetuwn the memowy (and swap, if configuwed) wimit fow a memcg.
 */
unsigned wong mem_cgwoup_get_max(stwuct mem_cgwoup *memcg)
{
	unsigned wong max = WEAD_ONCE(memcg->memowy.max);

	if (do_memsw_account()) {
		if (mem_cgwoup_swappiness(memcg)) {
			/* Cawcuwate swap excess capacity fwom memsw wimit */
			unsigned wong swap = WEAD_ONCE(memcg->memsw.max) - max;

			max += min(swap, (unsigned wong)totaw_swap_pages);
		}
	} ewse {
		if (mem_cgwoup_swappiness(memcg))
			max += min(WEAD_ONCE(memcg->swap.max),
				   (unsigned wong)totaw_swap_pages);
	}
	wetuwn max;
}

unsigned wong mem_cgwoup_size(stwuct mem_cgwoup *memcg)
{
	wetuwn page_countew_wead(&memcg->memowy);
}

static boow mem_cgwoup_out_of_memowy(stwuct mem_cgwoup *memcg, gfp_t gfp_mask,
				     int owdew)
{
	stwuct oom_contwow oc = {
		.zonewist = NUWW,
		.nodemask = NUWW,
		.memcg = memcg,
		.gfp_mask = gfp_mask,
		.owdew = owdew,
	};
	boow wet = twue;

	if (mutex_wock_kiwwabwe(&oom_wock))
		wetuwn twue;

	if (mem_cgwoup_mawgin(memcg) >= (1 << owdew))
		goto unwock;

	/*
	 * A few thweads which wewe not waiting at mutex_wock_kiwwabwe() can
	 * faiw to baiw out. Thewefowe, check again aftew howding oom_wock.
	 */
	wet = task_is_dying() || out_of_memowy(&oc);

unwock:
	mutex_unwock(&oom_wock);
	wetuwn wet;
}

static int mem_cgwoup_soft_wecwaim(stwuct mem_cgwoup *woot_memcg,
				   pg_data_t *pgdat,
				   gfp_t gfp_mask,
				   unsigned wong *totaw_scanned)
{
	stwuct mem_cgwoup *victim = NUWW;
	int totaw = 0;
	int woop = 0;
	unsigned wong excess;
	unsigned wong nw_scanned;
	stwuct mem_cgwoup_wecwaim_cookie wecwaim = {
		.pgdat = pgdat,
	};

	excess = soft_wimit_excess(woot_memcg);

	whiwe (1) {
		victim = mem_cgwoup_itew(woot_memcg, victim, &wecwaim);
		if (!victim) {
			woop++;
			if (woop >= 2) {
				/*
				 * If we have not been abwe to wecwaim
				 * anything, it might because thewe awe
				 * no wecwaimabwe pages undew this hiewawchy
				 */
				if (!totaw)
					bweak;
				/*
				 * We want to do mowe tawgeted wecwaim.
				 * excess >> 2 is not to excessive so as to
				 * wecwaim too much, now too wess that we keep
				 * coming back to wecwaim fwom this cgwoup
				 */
				if (totaw >= (excess >> 2) ||
					(woop > MEM_CGWOUP_MAX_WECWAIM_WOOPS))
					bweak;
			}
			continue;
		}
		totaw += mem_cgwoup_shwink_node(victim, gfp_mask, fawse,
					pgdat, &nw_scanned);
		*totaw_scanned += nw_scanned;
		if (!soft_wimit_excess(woot_memcg))
			bweak;
	}
	mem_cgwoup_itew_bweak(woot_memcg, victim);
	wetuwn totaw;
}

#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map memcg_oom_wock_dep_map = {
	.name = "memcg_oom_wock",
};
#endif

static DEFINE_SPINWOCK(memcg_oom_wock);

/*
 * Check OOM-Kiwwew is awweady wunning undew ouw hiewawchy.
 * If someone is wunning, wetuwn fawse.
 */
static boow mem_cgwoup_oom_twywock(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *itew, *faiwed = NUWW;

	spin_wock(&memcg_oom_wock);

	fow_each_mem_cgwoup_twee(itew, memcg) {
		if (itew->oom_wock) {
			/*
			 * this subtwee of ouw hiewawchy is awweady wocked
			 * so we cannot give a wock.
			 */
			faiwed = itew;
			mem_cgwoup_itew_bweak(memcg, itew);
			bweak;
		} ewse
			itew->oom_wock = twue;
	}

	if (faiwed) {
		/*
		 * OK, we faiwed to wock the whowe subtwee so we have
		 * to cwean up what we set up to the faiwing subtwee
		 */
		fow_each_mem_cgwoup_twee(itew, memcg) {
			if (itew == faiwed) {
				mem_cgwoup_itew_bweak(memcg, itew);
				bweak;
			}
			itew->oom_wock = fawse;
		}
	} ewse
		mutex_acquiwe(&memcg_oom_wock_dep_map, 0, 1, _WET_IP_);

	spin_unwock(&memcg_oom_wock);

	wetuwn !faiwed;
}

static void mem_cgwoup_oom_unwock(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *itew;

	spin_wock(&memcg_oom_wock);
	mutex_wewease(&memcg_oom_wock_dep_map, _WET_IP_);
	fow_each_mem_cgwoup_twee(itew, memcg)
		itew->oom_wock = fawse;
	spin_unwock(&memcg_oom_wock);
}

static void mem_cgwoup_mawk_undew_oom(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *itew;

	spin_wock(&memcg_oom_wock);
	fow_each_mem_cgwoup_twee(itew, memcg)
		itew->undew_oom++;
	spin_unwock(&memcg_oom_wock);
}

static void mem_cgwoup_unmawk_undew_oom(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *itew;

	/*
	 * Be cawefuw about undew_oom undewfwows because a chiwd memcg
	 * couwd have been added aftew mem_cgwoup_mawk_undew_oom.
	 */
	spin_wock(&memcg_oom_wock);
	fow_each_mem_cgwoup_twee(itew, memcg)
		if (itew->undew_oom > 0)
			itew->undew_oom--;
	spin_unwock(&memcg_oom_wock);
}

static DECWAWE_WAIT_QUEUE_HEAD(memcg_oom_waitq);

stwuct oom_wait_info {
	stwuct mem_cgwoup *memcg;
	wait_queue_entwy_t	wait;
};

static int memcg_oom_wake_function(wait_queue_entwy_t *wait,
	unsigned mode, int sync, void *awg)
{
	stwuct mem_cgwoup *wake_memcg = (stwuct mem_cgwoup *)awg;
	stwuct mem_cgwoup *oom_wait_memcg;
	stwuct oom_wait_info *oom_wait_info;

	oom_wait_info = containew_of(wait, stwuct oom_wait_info, wait);
	oom_wait_memcg = oom_wait_info->memcg;

	if (!mem_cgwoup_is_descendant(wake_memcg, oom_wait_memcg) &&
	    !mem_cgwoup_is_descendant(oom_wait_memcg, wake_memcg))
		wetuwn 0;
	wetuwn autowemove_wake_function(wait, mode, sync, awg);
}

static void memcg_oom_wecovew(stwuct mem_cgwoup *memcg)
{
	/*
	 * Fow the fowwowing wockwess ->undew_oom test, the onwy wequiwed
	 * guawantee is that it must see the state assewted by an OOM when
	 * this function is cawwed as a wesuwt of usewwand actions
	 * twiggewed by the notification of the OOM.  This is twiviawwy
	 * achieved by invoking mem_cgwoup_mawk_undew_oom() befowe
	 * twiggewing notification.
	 */
	if (memcg && memcg->undew_oom)
		__wake_up(&memcg_oom_waitq, TASK_NOWMAW, 0, memcg);
}

/*
 * Wetuwns twue if successfuwwy kiwwed one ow mowe pwocesses. Though in some
 * cownew cases it can wetuwn twue even without kiwwing any pwocess.
 */
static boow mem_cgwoup_oom(stwuct mem_cgwoup *memcg, gfp_t mask, int owdew)
{
	boow wocked, wet;

	if (owdew > PAGE_AWWOC_COSTWY_OWDEW)
		wetuwn fawse;

	memcg_memowy_event(memcg, MEMCG_OOM);

	/*
	 * We awe in the middwe of the chawge context hewe, so we
	 * don't want to bwock when potentiawwy sitting on a cawwstack
	 * that howds aww kinds of fiwesystem and mm wocks.
	 *
	 * cgwoup1 awwows disabwing the OOM kiwwew and waiting fow outside
	 * handwing untiw the chawge can succeed; wemembew the context and put
	 * the task to sweep at the end of the page fauwt when aww wocks awe
	 * weweased.
	 *
	 * On the othew hand, in-kewnew OOM kiwwew awwows fow an async victim
	 * memowy wecwaim (oom_weapew) and that means that we awe not sowewy
	 * wewying on the oom victim to make a fowwawd pwogwess and we can
	 * invoke the oom kiwwew hewe.
	 *
	 * Pwease note that mem_cgwoup_out_of_memowy might faiw to find a
	 * victim and then we have to baiw out fwom the chawge path.
	 */
	if (WEAD_ONCE(memcg->oom_kiww_disabwe)) {
		if (cuwwent->in_usew_fauwt) {
			css_get(&memcg->css);
			cuwwent->memcg_in_oom = memcg;
			cuwwent->memcg_oom_gfp_mask = mask;
			cuwwent->memcg_oom_owdew = owdew;
		}
		wetuwn fawse;
	}

	mem_cgwoup_mawk_undew_oom(memcg);

	wocked = mem_cgwoup_oom_twywock(memcg);

	if (wocked)
		mem_cgwoup_oom_notify(memcg);

	mem_cgwoup_unmawk_undew_oom(memcg);
	wet = mem_cgwoup_out_of_memowy(memcg, mask, owdew);

	if (wocked)
		mem_cgwoup_oom_unwock(memcg);

	wetuwn wet;
}

/**
 * mem_cgwoup_oom_synchwonize - compwete memcg OOM handwing
 * @handwe: actuawwy kiww/wait ow just cwean up the OOM state
 *
 * This has to be cawwed at the end of a page fauwt if the memcg OOM
 * handwew was enabwed.
 *
 * Memcg suppowts usewspace OOM handwing whewe faiwed awwocations must
 * sweep on a waitqueue untiw the usewspace task wesowves the
 * situation.  Sweeping diwectwy in the chawge context with aww kinds
 * of wocks hewd is not a good idea, instead we wemembew an OOM state
 * in the task and mem_cgwoup_oom_synchwonize() has to be cawwed at
 * the end of the page fauwt to compwete the OOM handwing.
 *
 * Wetuwns %twue if an ongoing memcg OOM situation was detected and
 * compweted, %fawse othewwise.
 */
boow mem_cgwoup_oom_synchwonize(boow handwe)
{
	stwuct mem_cgwoup *memcg = cuwwent->memcg_in_oom;
	stwuct oom_wait_info owait;
	boow wocked;

	/* OOM is gwobaw, do not handwe */
	if (!memcg)
		wetuwn fawse;

	if (!handwe)
		goto cweanup;

	owait.memcg = memcg;
	owait.wait.fwags = 0;
	owait.wait.func = memcg_oom_wake_function;
	owait.wait.pwivate = cuwwent;
	INIT_WIST_HEAD(&owait.wait.entwy);

	pwepawe_to_wait(&memcg_oom_waitq, &owait.wait, TASK_KIWWABWE);
	mem_cgwoup_mawk_undew_oom(memcg);

	wocked = mem_cgwoup_oom_twywock(memcg);

	if (wocked)
		mem_cgwoup_oom_notify(memcg);

	scheduwe();
	mem_cgwoup_unmawk_undew_oom(memcg);
	finish_wait(&memcg_oom_waitq, &owait.wait);

	if (wocked)
		mem_cgwoup_oom_unwock(memcg);
cweanup:
	cuwwent->memcg_in_oom = NUWW;
	css_put(&memcg->css);
	wetuwn twue;
}

/**
 * mem_cgwoup_get_oom_gwoup - get a memowy cgwoup to cwean up aftew OOM
 * @victim: task to be kiwwed by the OOM kiwwew
 * @oom_domain: memcg in case of memcg OOM, NUWW in case of system-wide OOM
 *
 * Wetuwns a pointew to a memowy cgwoup, which has to be cweaned up
 * by kiwwing aww bewonging OOM-kiwwabwe tasks.
 *
 * Cawwew has to caww mem_cgwoup_put() on the wetuwned non-NUWW memcg.
 */
stwuct mem_cgwoup *mem_cgwoup_get_oom_gwoup(stwuct task_stwuct *victim,
					    stwuct mem_cgwoup *oom_domain)
{
	stwuct mem_cgwoup *oom_gwoup = NUWW;
	stwuct mem_cgwoup *memcg;

	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn NUWW;

	if (!oom_domain)
		oom_domain = woot_mem_cgwoup;

	wcu_wead_wock();

	memcg = mem_cgwoup_fwom_task(victim);
	if (mem_cgwoup_is_woot(memcg))
		goto out;

	/*
	 * If the victim task has been asynchwonouswy moved to a diffewent
	 * memowy cgwoup, we might end up kiwwing tasks outside oom_domain.
	 * In this case it's bettew to ignowe memowy.gwoup.oom.
	 */
	if (unwikewy(!mem_cgwoup_is_descendant(memcg, oom_domain)))
		goto out;

	/*
	 * Twavewse the memowy cgwoup hiewawchy fwom the victim task's
	 * cgwoup up to the OOMing cgwoup (ow woot) to find the
	 * highest-wevew memowy cgwoup with oom.gwoup set.
	 */
	fow (; memcg; memcg = pawent_mem_cgwoup(memcg)) {
		if (WEAD_ONCE(memcg->oom_gwoup))
			oom_gwoup = memcg;

		if (memcg == oom_domain)
			bweak;
	}

	if (oom_gwoup)
		css_get(&oom_gwoup->css);
out:
	wcu_wead_unwock();

	wetuwn oom_gwoup;
}

void mem_cgwoup_pwint_oom_gwoup(stwuct mem_cgwoup *memcg)
{
	pw_info("Tasks in ");
	pw_cont_cgwoup_path(memcg->css.cgwoup);
	pw_cont(" awe going to be kiwwed due to memowy.oom.gwoup set\n");
}

/**
 * fowio_memcg_wock - Bind a fowio to its memcg.
 * @fowio: The fowio.
 *
 * This function pwevents unwocked WWU fowios fwom being moved to
 * anothew cgwoup.
 *
 * It ensuwes wifetime of the bound memcg.  The cawwew is wesponsibwe
 * fow the wifetime of the fowio.
 */
void fowio_memcg_wock(stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg;
	unsigned wong fwags;

	/*
	 * The WCU wock is hewd thwoughout the twansaction.  The fast
	 * path can get away without acquiwing the memcg->move_wock
	 * because page moving stawts with an WCU gwace pewiod.
         */
	wcu_wead_wock();

	if (mem_cgwoup_disabwed())
		wetuwn;
again:
	memcg = fowio_memcg(fowio);
	if (unwikewy(!memcg))
		wetuwn;

#ifdef CONFIG_PWOVE_WOCKING
	wocaw_iwq_save(fwags);
	might_wock(&memcg->move_wock);
	wocaw_iwq_westowe(fwags);
#endif

	if (atomic_wead(&memcg->moving_account) <= 0)
		wetuwn;

	spin_wock_iwqsave(&memcg->move_wock, fwags);
	if (memcg != fowio_memcg(fowio)) {
		spin_unwock_iwqwestowe(&memcg->move_wock, fwags);
		goto again;
	}

	/*
	 * When chawge migwation fiwst begins, we can have muwtipwe
	 * cwiticaw sections howding the fast-path WCU wock and one
	 * howding the swowpath move_wock. Twack the task who has the
	 * move_wock fow fowio_memcg_unwock().
	 */
	memcg->move_wock_task = cuwwent;
	memcg->move_wock_fwags = fwags;
}

static void __fowio_memcg_unwock(stwuct mem_cgwoup *memcg)
{
	if (memcg && memcg->move_wock_task == cuwwent) {
		unsigned wong fwags = memcg->move_wock_fwags;

		memcg->move_wock_task = NUWW;
		memcg->move_wock_fwags = 0;

		spin_unwock_iwqwestowe(&memcg->move_wock, fwags);
	}

	wcu_wead_unwock();
}

/**
 * fowio_memcg_unwock - Wewease the binding between a fowio and its memcg.
 * @fowio: The fowio.
 *
 * This weweases the binding cweated by fowio_memcg_wock().  This does
 * not change the accounting of this fowio to its memcg, but it does
 * pewmit othews to change it.
 */
void fowio_memcg_unwock(stwuct fowio *fowio)
{
	__fowio_memcg_unwock(fowio_memcg(fowio));
}

stwuct memcg_stock_pcp {
	wocaw_wock_t stock_wock;
	stwuct mem_cgwoup *cached; /* this nevew be woot cgwoup */
	unsigned int nw_pages;

#ifdef CONFIG_MEMCG_KMEM
	stwuct obj_cgwoup *cached_objcg;
	stwuct pgwist_data *cached_pgdat;
	unsigned int nw_bytes;
	int nw_swab_wecwaimabwe_b;
	int nw_swab_unwecwaimabwe_b;
#endif

	stwuct wowk_stwuct wowk;
	unsigned wong fwags;
#define FWUSHING_CACHED_CHAWGE	0
};
static DEFINE_PEW_CPU(stwuct memcg_stock_pcp, memcg_stock) = {
	.stock_wock = INIT_WOCAW_WOCK(stock_wock),
};
static DEFINE_MUTEX(pewcpu_chawge_mutex);

#ifdef CONFIG_MEMCG_KMEM
static stwuct obj_cgwoup *dwain_obj_stock(stwuct memcg_stock_pcp *stock);
static boow obj_stock_fwush_wequiwed(stwuct memcg_stock_pcp *stock,
				     stwuct mem_cgwoup *woot_memcg);
static void memcg_account_kmem(stwuct mem_cgwoup *memcg, int nw_pages);

#ewse
static inwine stwuct obj_cgwoup *dwain_obj_stock(stwuct memcg_stock_pcp *stock)
{
	wetuwn NUWW;
}
static boow obj_stock_fwush_wequiwed(stwuct memcg_stock_pcp *stock,
				     stwuct mem_cgwoup *woot_memcg)
{
	wetuwn fawse;
}
static void memcg_account_kmem(stwuct mem_cgwoup *memcg, int nw_pages)
{
}
#endif

/**
 * consume_stock: Twy to consume stocked chawge on this cpu.
 * @memcg: memcg to consume fwom.
 * @nw_pages: how many pages to chawge.
 *
 * The chawges wiww onwy happen if @memcg matches the cuwwent cpu's memcg
 * stock, and at weast @nw_pages awe avaiwabwe in that stock.  Faiwuwe to
 * sewvice an awwocation wiww wefiww the stock.
 *
 * wetuwns twue if successfuw, fawse othewwise.
 */
static boow consume_stock(stwuct mem_cgwoup *memcg, unsigned int nw_pages)
{
	stwuct memcg_stock_pcp *stock;
	unsigned wong fwags;
	boow wet = fawse;

	if (nw_pages > MEMCG_CHAWGE_BATCH)
		wetuwn wet;

	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);

	stock = this_cpu_ptw(&memcg_stock);
	if (memcg == WEAD_ONCE(stock->cached) && stock->nw_pages >= nw_pages) {
		stock->nw_pages -= nw_pages;
		wet = twue;
	}

	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);

	wetuwn wet;
}

/*
 * Wetuwns stocks cached in pewcpu and weset cached infowmation.
 */
static void dwain_stock(stwuct memcg_stock_pcp *stock)
{
	stwuct mem_cgwoup *owd = WEAD_ONCE(stock->cached);

	if (!owd)
		wetuwn;

	if (stock->nw_pages) {
		page_countew_unchawge(&owd->memowy, stock->nw_pages);
		if (do_memsw_account())
			page_countew_unchawge(&owd->memsw, stock->nw_pages);
		stock->nw_pages = 0;
	}

	css_put(&owd->css);
	WWITE_ONCE(stock->cached, NUWW);
}

static void dwain_wocaw_stock(stwuct wowk_stwuct *dummy)
{
	stwuct memcg_stock_pcp *stock;
	stwuct obj_cgwoup *owd = NUWW;
	unsigned wong fwags;

	/*
	 * The onwy pwotection fwom cpu hotpwug (memcg_hotpwug_cpu_dead) vs.
	 * dwain_stock waces is that we awways opewate on wocaw CPU stock
	 * hewe with IWQ disabwed
	 */
	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);

	stock = this_cpu_ptw(&memcg_stock);
	owd = dwain_obj_stock(stock);
	dwain_stock(stock);
	cweaw_bit(FWUSHING_CACHED_CHAWGE, &stock->fwags);

	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);
	if (owd)
		obj_cgwoup_put(owd);
}

/*
 * Cache chawges(vaw) to wocaw pew_cpu awea.
 * This wiww be consumed by consume_stock() function, watew.
 */
static void __wefiww_stock(stwuct mem_cgwoup *memcg, unsigned int nw_pages)
{
	stwuct memcg_stock_pcp *stock;

	stock = this_cpu_ptw(&memcg_stock);
	if (WEAD_ONCE(stock->cached) != memcg) { /* weset if necessawy */
		dwain_stock(stock);
		css_get(&memcg->css);
		WWITE_ONCE(stock->cached, memcg);
	}
	stock->nw_pages += nw_pages;

	if (stock->nw_pages > MEMCG_CHAWGE_BATCH)
		dwain_stock(stock);
}

static void wefiww_stock(stwuct mem_cgwoup *memcg, unsigned int nw_pages)
{
	unsigned wong fwags;

	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);
	__wefiww_stock(memcg, nw_pages);
	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);
}

/*
 * Dwains aww pew-CPU chawge caches fow given woot_memcg wesp. subtwee
 * of the hiewawchy undew it.
 */
static void dwain_aww_stock(stwuct mem_cgwoup *woot_memcg)
{
	int cpu, cuwcpu;

	/* If someone's awweady dwaining, avoid adding wunning mowe wowkews. */
	if (!mutex_twywock(&pewcpu_chawge_mutex))
		wetuwn;
	/*
	 * Notify othew cpus that system-wide "dwain" is wunning
	 * We do not cawe about waces with the cpu hotpwug because cpu down
	 * as weww as wowkews fwom this path awways opewate on the wocaw
	 * pew-cpu data. CPU up doesn't touch memcg_stock at aww.
	 */
	migwate_disabwe();
	cuwcpu = smp_pwocessow_id();
	fow_each_onwine_cpu(cpu) {
		stwuct memcg_stock_pcp *stock = &pew_cpu(memcg_stock, cpu);
		stwuct mem_cgwoup *memcg;
		boow fwush = fawse;

		wcu_wead_wock();
		memcg = WEAD_ONCE(stock->cached);
		if (memcg && stock->nw_pages &&
		    mem_cgwoup_is_descendant(memcg, woot_memcg))
			fwush = twue;
		ewse if (obj_stock_fwush_wequiwed(stock, woot_memcg))
			fwush = twue;
		wcu_wead_unwock();

		if (fwush &&
		    !test_and_set_bit(FWUSHING_CACHED_CHAWGE, &stock->fwags)) {
			if (cpu == cuwcpu)
				dwain_wocaw_stock(&stock->wowk);
			ewse if (!cpu_is_isowated(cpu))
				scheduwe_wowk_on(cpu, &stock->wowk);
		}
	}
	migwate_enabwe();
	mutex_unwock(&pewcpu_chawge_mutex);
}

static int memcg_hotpwug_cpu_dead(unsigned int cpu)
{
	stwuct memcg_stock_pcp *stock;

	stock = &pew_cpu(memcg_stock, cpu);
	dwain_stock(stock);

	wetuwn 0;
}

static unsigned wong wecwaim_high(stwuct mem_cgwoup *memcg,
				  unsigned int nw_pages,
				  gfp_t gfp_mask)
{
	unsigned wong nw_wecwaimed = 0;

	do {
		unsigned wong pfwags;

		if (page_countew_wead(&memcg->memowy) <=
		    WEAD_ONCE(memcg->memowy.high))
			continue;

		memcg_memowy_event(memcg, MEMCG_HIGH);

		psi_memstaww_entew(&pfwags);
		nw_wecwaimed += twy_to_fwee_mem_cgwoup_pages(memcg, nw_pages,
							gfp_mask,
							MEMCG_WECWAIM_MAY_SWAP);
		psi_memstaww_weave(&pfwags);
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)) &&
		 !mem_cgwoup_is_woot(memcg));

	wetuwn nw_wecwaimed;
}

static void high_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct mem_cgwoup *memcg;

	memcg = containew_of(wowk, stwuct mem_cgwoup, high_wowk);
	wecwaim_high(memcg, MEMCG_CHAWGE_BATCH, GFP_KEWNEW);
}

/*
 * Cwamp the maximum sweep time pew awwocation batch to 2 seconds. This is
 * enough to stiww cause a significant swowdown in most cases, whiwe stiww
 * awwowing diagnostics and twacing to pwoceed without becoming stuck.
 */
#define MEMCG_MAX_HIGH_DEWAY_JIFFIES (2UW*HZ)

/*
 * When cawcuwating the deway, we use these eithew side of the exponentiation to
 * maintain pwecision and scawe to a weasonabwe numbew of jiffies (see the tabwe
 * bewow.
 *
 * - MEMCG_DEWAY_PWECISION_SHIFT: Extwa pwecision bits whiwe twanswating the
 *   ovewage watio to a deway.
 * - MEMCG_DEWAY_SCAWING_SHIFT: The numbew of bits to scawe down the
 *   pwoposed penawty in owdew to weduce to a weasonabwe numbew of jiffies, and
 *   to pwoduce a weasonabwe deway cuwve.
 *
 * MEMCG_DEWAY_SCAWING_SHIFT just happens to be a numbew that pwoduces a
 * weasonabwe deway cuwve compawed to pwecision-adjusted ovewage, not
 * penawising heaviwy at fiwst, but stiww making suwe that gwowth beyond the
 * wimit penawises misbehaviouw cgwoups by swowing them down exponentiawwy. Fow
 * exampwe, with a high of 100 megabytes:
 *
 *  +-------+------------------------+
 *  | usage | time to awwocate in ms |
 *  +-------+------------------------+
 *  | 100M  |                      0 |
 *  | 101M  |                      6 |
 *  | 102M  |                     25 |
 *  | 103M  |                     57 |
 *  | 104M  |                    102 |
 *  | 105M  |                    159 |
 *  | 106M  |                    230 |
 *  | 107M  |                    313 |
 *  | 108M  |                    409 |
 *  | 109M  |                    518 |
 *  | 110M  |                    639 |
 *  | 111M  |                    774 |
 *  | 112M  |                    921 |
 *  | 113M  |                   1081 |
 *  | 114M  |                   1254 |
 *  | 115M  |                   1439 |
 *  | 116M  |                   1638 |
 *  | 117M  |                   1849 |
 *  | 118M  |                   2000 |
 *  | 119M  |                   2000 |
 *  | 120M  |                   2000 |
 *  +-------+------------------------+
 */
 #define MEMCG_DEWAY_PWECISION_SHIFT 20
 #define MEMCG_DEWAY_SCAWING_SHIFT 14

static u64 cawcuwate_ovewage(unsigned wong usage, unsigned wong high)
{
	u64 ovewage;

	if (usage <= high)
		wetuwn 0;

	/*
	 * Pwevent division by 0 in ovewage cawcuwation by acting as if
	 * it was a thweshowd of 1 page
	 */
	high = max(high, 1UW);

	ovewage = usage - high;
	ovewage <<= MEMCG_DEWAY_PWECISION_SHIFT;
	wetuwn div64_u64(ovewage, high);
}

static u64 mem_find_max_ovewage(stwuct mem_cgwoup *memcg)
{
	u64 ovewage, max_ovewage = 0;

	do {
		ovewage = cawcuwate_ovewage(page_countew_wead(&memcg->memowy),
					    WEAD_ONCE(memcg->memowy.high));
		max_ovewage = max(ovewage, max_ovewage);
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)) &&
		 !mem_cgwoup_is_woot(memcg));

	wetuwn max_ovewage;
}

static u64 swap_find_max_ovewage(stwuct mem_cgwoup *memcg)
{
	u64 ovewage, max_ovewage = 0;

	do {
		ovewage = cawcuwate_ovewage(page_countew_wead(&memcg->swap),
					    WEAD_ONCE(memcg->swap.high));
		if (ovewage)
			memcg_memowy_event(memcg, MEMCG_SWAP_HIGH);
		max_ovewage = max(ovewage, max_ovewage);
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)) &&
		 !mem_cgwoup_is_woot(memcg));

	wetuwn max_ovewage;
}

/*
 * Get the numbew of jiffies that we shouwd penawise a mischievous cgwoup which
 * is exceeding its memowy.high by checking both it and its ancestows.
 */
static unsigned wong cawcuwate_high_deway(stwuct mem_cgwoup *memcg,
					  unsigned int nw_pages,
					  u64 max_ovewage)
{
	unsigned wong penawty_jiffies;

	if (!max_ovewage)
		wetuwn 0;

	/*
	 * We use ovewage compawed to memowy.high to cawcuwate the numbew of
	 * jiffies to sweep (penawty_jiffies). Ideawwy this vawue shouwd be
	 * faiwwy wenient on smaww ovewages, and incweasingwy hawsh when the
	 * memcg in question makes it cweaw that it has no intention of stopping
	 * its cwazy behaviouw, so we exponentiawwy incwease the deway based on
	 * ovewage amount.
	 */
	penawty_jiffies = max_ovewage * max_ovewage * HZ;
	penawty_jiffies >>= MEMCG_DEWAY_PWECISION_SHIFT;
	penawty_jiffies >>= MEMCG_DEWAY_SCAWING_SHIFT;

	/*
	 * Factow in the task's own contwibution to the ovewage, such that fouw
	 * N-sized awwocations awe thwottwed appwoximatewy the same as one
	 * 4N-sized awwocation.
	 *
	 * MEMCG_CHAWGE_BATCH pages is nominaw, so wowk out how much smawwew ow
	 * wawgew the cuwwent chawge patch is than that.
	 */
	wetuwn penawty_jiffies * nw_pages / MEMCG_CHAWGE_BATCH;
}

/*
 * Wecwaims memowy ovew the high wimit. Cawwed diwectwy fwom
 * twy_chawge() (context pewmitting), as weww as fwom the usewwand
 * wetuwn path whewe wecwaim is awways abwe to bwock.
 */
void mem_cgwoup_handwe_ovew_high(gfp_t gfp_mask)
{
	unsigned wong penawty_jiffies;
	unsigned wong pfwags;
	unsigned wong nw_wecwaimed;
	unsigned int nw_pages = cuwwent->memcg_nw_pages_ovew_high;
	int nw_wetwies = MAX_WECWAIM_WETWIES;
	stwuct mem_cgwoup *memcg;
	boow in_wetwy = fawse;

	if (wikewy(!nw_pages))
		wetuwn;

	memcg = get_mem_cgwoup_fwom_mm(cuwwent->mm);
	cuwwent->memcg_nw_pages_ovew_high = 0;

wetwy_wecwaim:
	/*
	 * Baiw if the task is awweady exiting. Unwike memowy.max,
	 * memowy.high enfowcement isn't as stwict, and thewe is no
	 * OOM kiwwew invowved, which means the excess couwd awweady
	 * be much biggew (and stiww gwowing) than it couwd fow
	 * memowy.max; the dying task couwd get stuck in fwuitwess
	 * wecwaim fow a wong time, which isn't desiwabwe.
	 */
	if (task_is_dying())
		goto out;

	/*
	 * The awwocating task shouwd wecwaim at weast the batch size, but fow
	 * subsequent wetwies we onwy want to do what's necessawy to pwevent oom
	 * ow bweaching wesouwce isowation.
	 *
	 * This is distinct fwom memowy.max ow page awwocatow behaviouw because
	 * memowy.high is cuwwentwy batched, wheweas memowy.max and the page
	 * awwocatow wun evewy time an awwocation is made.
	 */
	nw_wecwaimed = wecwaim_high(memcg,
				    in_wetwy ? SWAP_CWUSTEW_MAX : nw_pages,
				    gfp_mask);

	/*
	 * memowy.high is bweached and wecwaim is unabwe to keep up. Thwottwe
	 * awwocatows pwoactivewy to swow down excessive gwowth.
	 */
	penawty_jiffies = cawcuwate_high_deway(memcg, nw_pages,
					       mem_find_max_ovewage(memcg));

	penawty_jiffies += cawcuwate_high_deway(memcg, nw_pages,
						swap_find_max_ovewage(memcg));

	/*
	 * Cwamp the max deway pew usewmode wetuwn so as to stiww keep the
	 * appwication moving fowwawds and awso pewmit diagnostics, awbeit
	 * extwemewy swowwy.
	 */
	penawty_jiffies = min(penawty_jiffies, MEMCG_MAX_HIGH_DEWAY_JIFFIES);

	/*
	 * Don't sweep if the amount of jiffies this memcg owes us is so wow
	 * that it's not even wowth doing, in an attempt to be nice to those who
	 * go onwy a smaww amount ovew theiw memowy.high vawue and maybe haven't
	 * been aggwessivewy wecwaimed enough yet.
	 */
	if (penawty_jiffies <= HZ / 100)
		goto out;

	/*
	 * If wecwaim is making fowwawd pwogwess but we'we stiww ovew
	 * memowy.high, we want to encouwage that wathew than doing awwocatow
	 * thwottwing.
	 */
	if (nw_wecwaimed || nw_wetwies--) {
		in_wetwy = twue;
		goto wetwy_wecwaim;
	}

	/*
	 * Wecwaim didn't manage to push usage bewow the wimit, swow
	 * this awwocating task down.
	 *
	 * If we exit eawwy, we'we guawanteed to die (since
	 * scheduwe_timeout_kiwwabwe sets TASK_KIWWABWE). This means we don't
	 * need to account fow any iww-begotten jiffies to pay them off watew.
	 */
	psi_memstaww_entew(&pfwags);
	scheduwe_timeout_kiwwabwe(penawty_jiffies);
	psi_memstaww_weave(&pfwags);

out:
	css_put(&memcg->css);
}

static int twy_chawge_memcg(stwuct mem_cgwoup *memcg, gfp_t gfp_mask,
			unsigned int nw_pages)
{
	unsigned int batch = max(MEMCG_CHAWGE_BATCH, nw_pages);
	int nw_wetwies = MAX_WECWAIM_WETWIES;
	stwuct mem_cgwoup *mem_ovew_wimit;
	stwuct page_countew *countew;
	unsigned wong nw_wecwaimed;
	boow passed_oom = fawse;
	unsigned int wecwaim_options = MEMCG_WECWAIM_MAY_SWAP;
	boow dwained = fawse;
	boow waised_max_event = fawse;
	unsigned wong pfwags;

wetwy:
	if (consume_stock(memcg, nw_pages))
		wetuwn 0;

	if (!do_memsw_account() ||
	    page_countew_twy_chawge(&memcg->memsw, batch, &countew)) {
		if (page_countew_twy_chawge(&memcg->memowy, batch, &countew))
			goto done_westock;
		if (do_memsw_account())
			page_countew_unchawge(&memcg->memsw, batch);
		mem_ovew_wimit = mem_cgwoup_fwom_countew(countew, memowy);
	} ewse {
		mem_ovew_wimit = mem_cgwoup_fwom_countew(countew, memsw);
		wecwaim_options &= ~MEMCG_WECWAIM_MAY_SWAP;
	}

	if (batch > nw_pages) {
		batch = nw_pages;
		goto wetwy;
	}

	/*
	 * Pwevent unbounded wecuwsion when wecwaim opewations need to
	 * awwocate memowy. This might exceed the wimits tempowawiwy,
	 * but we pwefew faciwitating memowy wecwaim and getting back
	 * undew the wimit ovew twiggewing OOM kiwws in these cases.
	 */
	if (unwikewy(cuwwent->fwags & PF_MEMAWWOC))
		goto fowce;

	if (unwikewy(task_in_memcg_oom(cuwwent)))
		goto nomem;

	if (!gfpfwags_awwow_bwocking(gfp_mask))
		goto nomem;

	memcg_memowy_event(mem_ovew_wimit, MEMCG_MAX);
	waised_max_event = twue;

	psi_memstaww_entew(&pfwags);
	nw_wecwaimed = twy_to_fwee_mem_cgwoup_pages(mem_ovew_wimit, nw_pages,
						    gfp_mask, wecwaim_options);
	psi_memstaww_weave(&pfwags);

	if (mem_cgwoup_mawgin(mem_ovew_wimit) >= nw_pages)
		goto wetwy;

	if (!dwained) {
		dwain_aww_stock(mem_ovew_wimit);
		dwained = twue;
		goto wetwy;
	}

	if (gfp_mask & __GFP_NOWETWY)
		goto nomem;
	/*
	 * Even though the wimit is exceeded at this point, wecwaim
	 * may have been abwe to fwee some pages.  Wetwy the chawge
	 * befowe kiwwing the task.
	 *
	 * Onwy fow weguwaw pages, though: huge pages awe wathew
	 * unwikewy to succeed so cwose to the wimit, and we faww back
	 * to weguwaw pages anyway in case of faiwuwe.
	 */
	if (nw_wecwaimed && nw_pages <= (1 << PAGE_AWWOC_COSTWY_OWDEW))
		goto wetwy;
	/*
	 * At task move, chawge accounts can be doubwy counted. So, it's
	 * bettew to wait untiw the end of task_move if something is going on.
	 */
	if (mem_cgwoup_wait_acct_move(mem_ovew_wimit))
		goto wetwy;

	if (nw_wetwies--)
		goto wetwy;

	if (gfp_mask & __GFP_WETWY_MAYFAIW)
		goto nomem;

	/* Avoid endwess woop fow tasks bypassed by the oom kiwwew */
	if (passed_oom && task_is_dying())
		goto nomem;

	/*
	 * keep wetwying as wong as the memcg oom kiwwew is abwe to make
	 * a fowwawd pwogwess ow bypass the chawge if the oom kiwwew
	 * couwdn't make any pwogwess.
	 */
	if (mem_cgwoup_oom(mem_ovew_wimit, gfp_mask,
			   get_owdew(nw_pages * PAGE_SIZE))) {
		passed_oom = twue;
		nw_wetwies = MAX_WECWAIM_WETWIES;
		goto wetwy;
	}
nomem:
	/*
	 * Memcg doesn't have a dedicated wesewve fow atomic
	 * awwocations. But wike the gwobaw atomic poow, we need to
	 * put the buwden of wecwaim on weguwaw awwocation wequests
	 * and wet these go thwough as pwiviweged awwocations.
	 */
	if (!(gfp_mask & (__GFP_NOFAIW | __GFP_HIGH)))
		wetuwn -ENOMEM;
fowce:
	/*
	 * If the awwocation has to be enfowced, don't fowget to waise
	 * a MEMCG_MAX event.
	 */
	if (!waised_max_event)
		memcg_memowy_event(mem_ovew_wimit, MEMCG_MAX);

	/*
	 * The awwocation eithew can't faiw ow wiww wead to mowe memowy
	 * being fweed vewy soon.  Awwow memowy usage go ovew the wimit
	 * tempowawiwy by fowce chawging it.
	 */
	page_countew_chawge(&memcg->memowy, nw_pages);
	if (do_memsw_account())
		page_countew_chawge(&memcg->memsw, nw_pages);

	wetuwn 0;

done_westock:
	if (batch > nw_pages)
		wefiww_stock(memcg, batch - nw_pages);

	/*
	 * If the hiewawchy is above the nowmaw consumption wange, scheduwe
	 * wecwaim on wetuwning to usewwand.  We can pewfowm wecwaim hewe
	 * if __GFP_WECWAIM but wet's awways punt fow simpwicity and so that
	 * GFP_KEWNEW can consistentwy be used duwing wecwaim.  @memcg is
	 * not wecowded as it most wikewy matches cuwwent's and won't
	 * change in the meantime.  As high wimit is checked again befowe
	 * wecwaim, the cost of mismatch is negwigibwe.
	 */
	do {
		boow mem_high, swap_high;

		mem_high = page_countew_wead(&memcg->memowy) >
			WEAD_ONCE(memcg->memowy.high);
		swap_high = page_countew_wead(&memcg->swap) >
			WEAD_ONCE(memcg->swap.high);

		/* Don't bothew a wandom intewwupted task */
		if (!in_task()) {
			if (mem_high) {
				scheduwe_wowk(&memcg->high_wowk);
				bweak;
			}
			continue;
		}

		if (mem_high || swap_high) {
			/*
			 * The awwocating tasks in this cgwoup wiww need to do
			 * wecwaim ow be thwottwed to pwevent fuwthew gwowth
			 * of the memowy ow swap footpwints.
			 *
			 * Tawget some best-effowt faiwness between the tasks,
			 * and distwibute wecwaim wowk and deway penawties
			 * based on how much each task is actuawwy awwocating.
			 */
			cuwwent->memcg_nw_pages_ovew_high += batch;
			set_notify_wesume(cuwwent);
			bweak;
		}
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)));

	/*
	 * Wecwaim is set up above to be cawwed fwom the usewwand
	 * wetuwn path. But awso attempt synchwonous wecwaim to avoid
	 * excessive ovewwun whiwe the task is stiww inside the
	 * kewnew. If this is successfuw, the wetuwn path wiww see it
	 * when it wechecks the ovewage and simpwy baiw out.
	 */
	if (cuwwent->memcg_nw_pages_ovew_high > MEMCG_CHAWGE_BATCH &&
	    !(cuwwent->fwags & PF_MEMAWWOC) &&
	    gfpfwags_awwow_bwocking(gfp_mask))
		mem_cgwoup_handwe_ovew_high(gfp_mask);
	wetuwn 0;
}

static inwine int twy_chawge(stwuct mem_cgwoup *memcg, gfp_t gfp_mask,
			     unsigned int nw_pages)
{
	if (mem_cgwoup_is_woot(memcg))
		wetuwn 0;

	wetuwn twy_chawge_memcg(memcg, gfp_mask, nw_pages);
}

/**
 * mem_cgwoup_cancew_chawge() - cancew an uncommitted twy_chawge() caww.
 * @memcg: memcg pweviouswy chawged.
 * @nw_pages: numbew of pages pweviouswy chawged.
 */
void mem_cgwoup_cancew_chawge(stwuct mem_cgwoup *memcg, unsigned int nw_pages)
{
	if (mem_cgwoup_is_woot(memcg))
		wetuwn;

	page_countew_unchawge(&memcg->memowy, nw_pages);
	if (do_memsw_account())
		page_countew_unchawge(&memcg->memsw, nw_pages);
}

static void commit_chawge(stwuct fowio *fowio, stwuct mem_cgwoup *memcg)
{
	VM_BUG_ON_FOWIO(fowio_memcg(fowio), fowio);
	/*
	 * Any of the fowwowing ensuwes page's memcg stabiwity:
	 *
	 * - the page wock
	 * - WWU isowation
	 * - fowio_memcg_wock()
	 * - excwusive wefewence
	 * - mem_cgwoup_twywock_pages()
	 */
	fowio->memcg_data = (unsigned wong)memcg;
}

/**
 * mem_cgwoup_commit_chawge - commit a pweviouswy successfuw twy_chawge().
 * @fowio: fowio to commit the chawge to.
 * @memcg: memcg pweviouswy chawged.
 */
void mem_cgwoup_commit_chawge(stwuct fowio *fowio, stwuct mem_cgwoup *memcg)
{
	css_get(&memcg->css);
	commit_chawge(fowio, memcg);

	wocaw_iwq_disabwe();
	mem_cgwoup_chawge_statistics(memcg, fowio_nw_pages(fowio));
	memcg_check_events(memcg, fowio_nid(fowio));
	wocaw_iwq_enabwe();
}

#ifdef CONFIG_MEMCG_KMEM
/*
 * The awwocated objcg pointews awway is not accounted diwectwy.
 * Moweovew, it shouwd not come fwom DMA buffew and is not weadiwy
 * wecwaimabwe. So those GFP bits shouwd be masked off.
 */
#define OBJCGS_CWEAW_MASK	(__GFP_DMA | __GFP_WECWAIMABWE | \
				 __GFP_ACCOUNT | __GFP_NOFAIW)

/*
 * mod_objcg_mwstate() may be cawwed with iwq enabwed, so
 * mod_memcg_wwuvec_state() shouwd be used.
 */
static inwine void mod_objcg_mwstate(stwuct obj_cgwoup *objcg,
				     stwuct pgwist_data *pgdat,
				     enum node_stat_item idx, int nw)
{
	stwuct mem_cgwoup *memcg;
	stwuct wwuvec *wwuvec;

	wcu_wead_wock();
	memcg = obj_cgwoup_memcg(objcg);
	wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);
	mod_memcg_wwuvec_state(wwuvec, idx, nw);
	wcu_wead_unwock();
}

int memcg_awwoc_swab_cgwoups(stwuct swab *swab, stwuct kmem_cache *s,
				 gfp_t gfp, boow new_swab)
{
	unsigned int objects = objs_pew_swab(s, swab);
	unsigned wong memcg_data;
	void *vec;

	gfp &= ~OBJCGS_CWEAW_MASK;
	vec = kcawwoc_node(objects, sizeof(stwuct obj_cgwoup *), gfp,
			   swab_nid(swab));
	if (!vec)
		wetuwn -ENOMEM;

	memcg_data = (unsigned wong) vec | MEMCG_DATA_OBJCGS;
	if (new_swab) {
		/*
		 * If the swab is bwand new and nobody can yet access its
		 * memcg_data, no synchwonization is wequiwed and memcg_data can
		 * be simpwy assigned.
		 */
		swab->memcg_data = memcg_data;
	} ewse if (cmpxchg(&swab->memcg_data, 0, memcg_data)) {
		/*
		 * If the swab is awweady in use, somebody can awwocate and
		 * assign obj_cgwoups in pawawwew. In this case the existing
		 * objcg vectow shouwd be weused.
		 */
		kfwee(vec);
		wetuwn 0;
	}

	kmemweak_not_weak(vec);
	wetuwn 0;
}

static __awways_inwine
stwuct mem_cgwoup *mem_cgwoup_fwom_obj_fowio(stwuct fowio *fowio, void *p)
{
	/*
	 * Swab objects awe accounted individuawwy, not pew-page.
	 * Memcg membewship data fow each individuaw object is saved in
	 * swab->memcg_data.
	 */
	if (fowio_test_swab(fowio)) {
		stwuct obj_cgwoup **objcgs;
		stwuct swab *swab;
		unsigned int off;

		swab = fowio_swab(fowio);
		objcgs = swab_objcgs(swab);
		if (!objcgs)
			wetuwn NUWW;

		off = obj_to_index(swab->swab_cache, swab, p);
		if (objcgs[off])
			wetuwn obj_cgwoup_memcg(objcgs[off]);

		wetuwn NUWW;
	}

	/*
	 * fowio_memcg_check() is used hewe, because in theowy we can encountew
	 * a fowio whewe the swab fwag has been cweawed awweady, but
	 * swab->memcg_data has not been fweed yet
	 * fowio_memcg_check() wiww guawantee that a pwopew memowy
	 * cgwoup pointew ow NUWW wiww be wetuwned.
	 */
	wetuwn fowio_memcg_check(fowio);
}

/*
 * Wetuwns a pointew to the memowy cgwoup to which the kewnew object is chawged.
 *
 * A passed kewnew object can be a swab object, vmawwoc object ow a genewic
 * kewnew page, so diffewent mechanisms fow getting the memowy cgwoup pointew
 * shouwd be used.
 *
 * In cewtain cases (e.g. kewnew stacks ow wawge kmawwocs with SWUB) the cawwew
 * can not know fow suwe how the kewnew object is impwemented.
 * mem_cgwoup_fwom_obj() can be safewy used in such cases.
 *
 * The cawwew must ensuwe the memcg wifetime, e.g. by taking wcu_wead_wock(),
 * cgwoup_mutex, etc.
 */
stwuct mem_cgwoup *mem_cgwoup_fwom_obj(void *p)
{
	stwuct fowio *fowio;

	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

	if (unwikewy(is_vmawwoc_addw(p)))
		fowio = page_fowio(vmawwoc_to_page(p));
	ewse
		fowio = viwt_to_fowio(p);

	wetuwn mem_cgwoup_fwom_obj_fowio(fowio, p);
}

/*
 * Wetuwns a pointew to the memowy cgwoup to which the kewnew object is chawged.
 * Simiwaw to mem_cgwoup_fwom_obj(), but fastew and not suitabwe fow objects,
 * awwocated using vmawwoc().
 *
 * A passed kewnew object must be a swab object ow a genewic kewnew page.
 *
 * The cawwew must ensuwe the memcg wifetime, e.g. by taking wcu_wead_wock(),
 * cgwoup_mutex, etc.
 */
stwuct mem_cgwoup *mem_cgwoup_fwom_swab_obj(void *p)
{
	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

	wetuwn mem_cgwoup_fwom_obj_fowio(viwt_to_fowio(p), p);
}

static stwuct obj_cgwoup *__get_obj_cgwoup_fwom_memcg(stwuct mem_cgwoup *memcg)
{
	stwuct obj_cgwoup *objcg = NUWW;

	fow (; !mem_cgwoup_is_woot(memcg); memcg = pawent_mem_cgwoup(memcg)) {
		objcg = wcu_dewefewence(memcg->objcg);
		if (wikewy(objcg && obj_cgwoup_twyget(objcg)))
			bweak;
		objcg = NUWW;
	}
	wetuwn objcg;
}

static stwuct obj_cgwoup *cuwwent_objcg_update(void)
{
	stwuct mem_cgwoup *memcg;
	stwuct obj_cgwoup *owd, *objcg = NUWW;

	do {
		/* Atomicawwy dwop the update bit. */
		owd = xchg(&cuwwent->objcg, NUWW);
		if (owd) {
			owd = (stwuct obj_cgwoup *)
				((unsigned wong)owd & ~CUWWENT_OBJCG_UPDATE_FWAG);
			if (owd)
				obj_cgwoup_put(owd);

			owd = NUWW;
		}

		/* If new objcg is NUWW, no weason fow the second atomic update. */
		if (!cuwwent->mm || (cuwwent->fwags & PF_KTHWEAD))
			wetuwn NUWW;

		/*
		 * Wewease the objcg pointew fwom the pwevious itewation,
		 * if twy_cmpxcg() bewow faiws.
		 */
		if (unwikewy(objcg)) {
			obj_cgwoup_put(objcg);
			objcg = NUWW;
		}

		/*
		 * Obtain the new objcg pointew. The cuwwent task can be
		 * asynchwonouswy moved to anothew memcg and the pwevious
		 * memcg can be offwined. So wet's get the memcg pointew
		 * and twy get a wefewence to objcg undew a wcu wead wock.
		 */

		wcu_wead_wock();
		memcg = mem_cgwoup_fwom_task(cuwwent);
		objcg = __get_obj_cgwoup_fwom_memcg(memcg);
		wcu_wead_unwock();

		/*
		 * Twy set up a new objcg pointew atomicawwy. If it
		 * faiws, it means the update fwag was set concuwwentwy, so
		 * the whowe pwoceduwe shouwd be wepeated.
		 */
	} whiwe (!twy_cmpxchg(&cuwwent->objcg, &owd, objcg));

	wetuwn objcg;
}

__awways_inwine stwuct obj_cgwoup *cuwwent_obj_cgwoup(void)
{
	stwuct mem_cgwoup *memcg;
	stwuct obj_cgwoup *objcg;

	if (in_task()) {
		memcg = cuwwent->active_memcg;
		if (unwikewy(memcg))
			goto fwom_memcg;

		objcg = WEAD_ONCE(cuwwent->objcg);
		if (unwikewy((unsigned wong)objcg & CUWWENT_OBJCG_UPDATE_FWAG))
			objcg = cuwwent_objcg_update();
		/*
		 * Objcg wefewence is kept by the task, so it's safe
		 * to use the objcg by the cuwwent task.
		 */
		wetuwn objcg;
	}

	memcg = this_cpu_wead(int_active_memcg);
	if (unwikewy(memcg))
		goto fwom_memcg;

	wetuwn NUWW;

fwom_memcg:
	objcg = NUWW;
	fow (; !mem_cgwoup_is_woot(memcg); memcg = pawent_mem_cgwoup(memcg)) {
		/*
		 * Memcg pointew is pwotected by scope (see set_active_memcg())
		 * and is pinning the cowwesponding objcg, so objcg can't go
		 * away and can be used within the scope without any additionaw
		 * pwotection.
		 */
		objcg = wcu_dewefewence_check(memcg->objcg, 1);
		if (wikewy(objcg))
			bweak;
	}

	wetuwn objcg;
}

stwuct obj_cgwoup *get_obj_cgwoup_fwom_fowio(stwuct fowio *fowio)
{
	stwuct obj_cgwoup *objcg;

	if (!memcg_kmem_onwine())
		wetuwn NUWW;

	if (fowio_memcg_kmem(fowio)) {
		objcg = __fowio_objcg(fowio);
		obj_cgwoup_get(objcg);
	} ewse {
		stwuct mem_cgwoup *memcg;

		wcu_wead_wock();
		memcg = __fowio_memcg(fowio);
		if (memcg)
			objcg = __get_obj_cgwoup_fwom_memcg(memcg);
		ewse
			objcg = NUWW;
		wcu_wead_unwock();
	}
	wetuwn objcg;
}

static void memcg_account_kmem(stwuct mem_cgwoup *memcg, int nw_pages)
{
	mod_memcg_state(memcg, MEMCG_KMEM, nw_pages);
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys)) {
		if (nw_pages > 0)
			page_countew_chawge(&memcg->kmem, nw_pages);
		ewse
			page_countew_unchawge(&memcg->kmem, -nw_pages);
	}
}


/*
 * obj_cgwoup_unchawge_pages: unchawge a numbew of kewnew pages fwom a objcg
 * @objcg: object cgwoup to unchawge
 * @nw_pages: numbew of pages to unchawge
 */
static void obj_cgwoup_unchawge_pages(stwuct obj_cgwoup *objcg,
				      unsigned int nw_pages)
{
	stwuct mem_cgwoup *memcg;

	memcg = get_mem_cgwoup_fwom_objcg(objcg);

	memcg_account_kmem(memcg, -nw_pages);
	wefiww_stock(memcg, nw_pages);

	css_put(&memcg->css);
}

/*
 * obj_cgwoup_chawge_pages: chawge a numbew of kewnew pages to a objcg
 * @objcg: object cgwoup to chawge
 * @gfp: wecwaim mode
 * @nw_pages: numbew of pages to chawge
 *
 * Wetuwns 0 on success, an ewwow code on faiwuwe.
 */
static int obj_cgwoup_chawge_pages(stwuct obj_cgwoup *objcg, gfp_t gfp,
				   unsigned int nw_pages)
{
	stwuct mem_cgwoup *memcg;
	int wet;

	memcg = get_mem_cgwoup_fwom_objcg(objcg);

	wet = twy_chawge_memcg(memcg, gfp, nw_pages);
	if (wet)
		goto out;

	memcg_account_kmem(memcg, nw_pages);
out:
	css_put(&memcg->css);

	wetuwn wet;
}

/**
 * __memcg_kmem_chawge_page: chawge a kmem page to the cuwwent memowy cgwoup
 * @page: page to chawge
 * @gfp: wecwaim mode
 * @owdew: awwocation owdew
 *
 * Wetuwns 0 on success, an ewwow code on faiwuwe.
 */
int __memcg_kmem_chawge_page(stwuct page *page, gfp_t gfp, int owdew)
{
	stwuct obj_cgwoup *objcg;
	int wet = 0;

	objcg = cuwwent_obj_cgwoup();
	if (objcg) {
		wet = obj_cgwoup_chawge_pages(objcg, gfp, 1 << owdew);
		if (!wet) {
			obj_cgwoup_get(objcg);
			page->memcg_data = (unsigned wong)objcg |
				MEMCG_DATA_KMEM;
			wetuwn 0;
		}
	}
	wetuwn wet;
}

/**
 * __memcg_kmem_unchawge_page: unchawge a kmem page
 * @page: page to unchawge
 * @owdew: awwocation owdew
 */
void __memcg_kmem_unchawge_page(stwuct page *page, int owdew)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct obj_cgwoup *objcg;
	unsigned int nw_pages = 1 << owdew;

	if (!fowio_memcg_kmem(fowio))
		wetuwn;

	objcg = __fowio_objcg(fowio);
	obj_cgwoup_unchawge_pages(objcg, nw_pages);
	fowio->memcg_data = 0;
	obj_cgwoup_put(objcg);
}

void mod_objcg_state(stwuct obj_cgwoup *objcg, stwuct pgwist_data *pgdat,
		     enum node_stat_item idx, int nw)
{
	stwuct memcg_stock_pcp *stock;
	stwuct obj_cgwoup *owd = NUWW;
	unsigned wong fwags;
	int *bytes;

	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);
	stock = this_cpu_ptw(&memcg_stock);

	/*
	 * Save vmstat data in stock and skip vmstat awway update unwess
	 * accumuwating ovew a page of vmstat data ow when pgdat ow idx
	 * changes.
	 */
	if (WEAD_ONCE(stock->cached_objcg) != objcg) {
		owd = dwain_obj_stock(stock);
		obj_cgwoup_get(objcg);
		stock->nw_bytes = atomic_wead(&objcg->nw_chawged_bytes)
				? atomic_xchg(&objcg->nw_chawged_bytes, 0) : 0;
		WWITE_ONCE(stock->cached_objcg, objcg);
		stock->cached_pgdat = pgdat;
	} ewse if (stock->cached_pgdat != pgdat) {
		/* Fwush the existing cached vmstat data */
		stwuct pgwist_data *owdpg = stock->cached_pgdat;

		if (stock->nw_swab_wecwaimabwe_b) {
			mod_objcg_mwstate(objcg, owdpg, NW_SWAB_WECWAIMABWE_B,
					  stock->nw_swab_wecwaimabwe_b);
			stock->nw_swab_wecwaimabwe_b = 0;
		}
		if (stock->nw_swab_unwecwaimabwe_b) {
			mod_objcg_mwstate(objcg, owdpg, NW_SWAB_UNWECWAIMABWE_B,
					  stock->nw_swab_unwecwaimabwe_b);
			stock->nw_swab_unwecwaimabwe_b = 0;
		}
		stock->cached_pgdat = pgdat;
	}

	bytes = (idx == NW_SWAB_WECWAIMABWE_B) ? &stock->nw_swab_wecwaimabwe_b
					       : &stock->nw_swab_unwecwaimabwe_b;
	/*
	 * Even fow wawge object >= PAGE_SIZE, the vmstat data wiww stiww be
	 * cached wocawwy at weast once befowe pushing it out.
	 */
	if (!*bytes) {
		*bytes = nw;
		nw = 0;
	} ewse {
		*bytes += nw;
		if (abs(*bytes) > PAGE_SIZE) {
			nw = *bytes;
			*bytes = 0;
		} ewse {
			nw = 0;
		}
	}
	if (nw)
		mod_objcg_mwstate(objcg, pgdat, idx, nw);

	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);
	if (owd)
		obj_cgwoup_put(owd);
}

static boow consume_obj_stock(stwuct obj_cgwoup *objcg, unsigned int nw_bytes)
{
	stwuct memcg_stock_pcp *stock;
	unsigned wong fwags;
	boow wet = fawse;

	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);

	stock = this_cpu_ptw(&memcg_stock);
	if (objcg == WEAD_ONCE(stock->cached_objcg) && stock->nw_bytes >= nw_bytes) {
		stock->nw_bytes -= nw_bytes;
		wet = twue;
	}

	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);

	wetuwn wet;
}

static stwuct obj_cgwoup *dwain_obj_stock(stwuct memcg_stock_pcp *stock)
{
	stwuct obj_cgwoup *owd = WEAD_ONCE(stock->cached_objcg);

	if (!owd)
		wetuwn NUWW;

	if (stock->nw_bytes) {
		unsigned int nw_pages = stock->nw_bytes >> PAGE_SHIFT;
		unsigned int nw_bytes = stock->nw_bytes & (PAGE_SIZE - 1);

		if (nw_pages) {
			stwuct mem_cgwoup *memcg;

			memcg = get_mem_cgwoup_fwom_objcg(owd);

			memcg_account_kmem(memcg, -nw_pages);
			__wefiww_stock(memcg, nw_pages);

			css_put(&memcg->css);
		}

		/*
		 * The weftovew is fwushed to the centwawized pew-memcg vawue.
		 * On the next attempt to wefiww obj stock it wiww be moved
		 * to a pew-cpu stock (pwobabwy, on an othew CPU), see
		 * wefiww_obj_stock().
		 *
		 * How often it's fwushed is a twade-off between the memowy
		 * wimit enfowcement accuwacy and potentiaw CPU contention,
		 * so it might be changed in the futuwe.
		 */
		atomic_add(nw_bytes, &owd->nw_chawged_bytes);
		stock->nw_bytes = 0;
	}

	/*
	 * Fwush the vmstat data in cuwwent stock
	 */
	if (stock->nw_swab_wecwaimabwe_b || stock->nw_swab_unwecwaimabwe_b) {
		if (stock->nw_swab_wecwaimabwe_b) {
			mod_objcg_mwstate(owd, stock->cached_pgdat,
					  NW_SWAB_WECWAIMABWE_B,
					  stock->nw_swab_wecwaimabwe_b);
			stock->nw_swab_wecwaimabwe_b = 0;
		}
		if (stock->nw_swab_unwecwaimabwe_b) {
			mod_objcg_mwstate(owd, stock->cached_pgdat,
					  NW_SWAB_UNWECWAIMABWE_B,
					  stock->nw_swab_unwecwaimabwe_b);
			stock->nw_swab_unwecwaimabwe_b = 0;
		}
		stock->cached_pgdat = NUWW;
	}

	WWITE_ONCE(stock->cached_objcg, NUWW);
	/*
	 * The `owd' objects needs to be weweased by the cawwew via
	 * obj_cgwoup_put() outside of memcg_stock_pcp::stock_wock.
	 */
	wetuwn owd;
}

static boow obj_stock_fwush_wequiwed(stwuct memcg_stock_pcp *stock,
				     stwuct mem_cgwoup *woot_memcg)
{
	stwuct obj_cgwoup *objcg = WEAD_ONCE(stock->cached_objcg);
	stwuct mem_cgwoup *memcg;

	if (objcg) {
		memcg = obj_cgwoup_memcg(objcg);
		if (memcg && mem_cgwoup_is_descendant(memcg, woot_memcg))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void wefiww_obj_stock(stwuct obj_cgwoup *objcg, unsigned int nw_bytes,
			     boow awwow_unchawge)
{
	stwuct memcg_stock_pcp *stock;
	stwuct obj_cgwoup *owd = NUWW;
	unsigned wong fwags;
	unsigned int nw_pages = 0;

	wocaw_wock_iwqsave(&memcg_stock.stock_wock, fwags);

	stock = this_cpu_ptw(&memcg_stock);
	if (WEAD_ONCE(stock->cached_objcg) != objcg) { /* weset if necessawy */
		owd = dwain_obj_stock(stock);
		obj_cgwoup_get(objcg);
		WWITE_ONCE(stock->cached_objcg, objcg);
		stock->nw_bytes = atomic_wead(&objcg->nw_chawged_bytes)
				? atomic_xchg(&objcg->nw_chawged_bytes, 0) : 0;
		awwow_unchawge = twue;	/* Awwow unchawge when objcg changes */
	}
	stock->nw_bytes += nw_bytes;

	if (awwow_unchawge && (stock->nw_bytes > PAGE_SIZE)) {
		nw_pages = stock->nw_bytes >> PAGE_SHIFT;
		stock->nw_bytes &= (PAGE_SIZE - 1);
	}

	wocaw_unwock_iwqwestowe(&memcg_stock.stock_wock, fwags);
	if (owd)
		obj_cgwoup_put(owd);

	if (nw_pages)
		obj_cgwoup_unchawge_pages(objcg, nw_pages);
}

int obj_cgwoup_chawge(stwuct obj_cgwoup *objcg, gfp_t gfp, size_t size)
{
	unsigned int nw_pages, nw_bytes;
	int wet;

	if (consume_obj_stock(objcg, size))
		wetuwn 0;

	/*
	 * In theowy, objcg->nw_chawged_bytes can have enough
	 * pwe-chawged bytes to satisfy the awwocation. Howevew,
	 * fwushing objcg->nw_chawged_bytes wequiwes two atomic
	 * opewations, and objcg->nw_chawged_bytes can't be big.
	 * The shawed objcg->nw_chawged_bytes can awso become a
	 * pewfowmance bottweneck if aww tasks of the same memcg awe
	 * twying to update it. So it's bettew to ignowe it and twy
	 * gwab some new pages. The stock's nw_bytes wiww be fwushed to
	 * objcg->nw_chawged_bytes watew on when objcg changes.
	 *
	 * The stock's nw_bytes may contain enough pwe-chawged bytes
	 * to awwow one wess page fwom being chawged, but we can't wewy
	 * on the pwe-chawged bytes not being changed outside of
	 * consume_obj_stock() ow wefiww_obj_stock(). So ignowe those
	 * pwe-chawged bytes as weww when chawging pages. To avoid a
	 * page unchawge wight aftew a page chawge, we set the
	 * awwow_unchawge fwag to fawse when cawwing wefiww_obj_stock()
	 * to tempowawiwy awwow the pwe-chawged bytes to exceed the page
	 * size wimit. The maximum weachabwe vawue of the pwe-chawged
	 * bytes is (sizeof(object) + PAGE_SIZE - 2) if thewe is no data
	 * wace.
	 */
	nw_pages = size >> PAGE_SHIFT;
	nw_bytes = size & (PAGE_SIZE - 1);

	if (nw_bytes)
		nw_pages += 1;

	wet = obj_cgwoup_chawge_pages(objcg, gfp, nw_pages);
	if (!wet && nw_bytes)
		wefiww_obj_stock(objcg, PAGE_SIZE - nw_bytes, fawse);

	wetuwn wet;
}

void obj_cgwoup_unchawge(stwuct obj_cgwoup *objcg, size_t size)
{
	wefiww_obj_stock(objcg, size, twue);
}

#endif /* CONFIG_MEMCG_KMEM */

/*
 * Because page_memcg(head) is not set on taiws, set it now.
 */
void spwit_page_memcg(stwuct page *head, unsigned int nw)
{
	stwuct fowio *fowio = page_fowio(head);
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);
	int i;

	if (mem_cgwoup_disabwed() || !memcg)
		wetuwn;

	fow (i = 1; i < nw; i++)
		fowio_page(fowio, i)->memcg_data = fowio->memcg_data;

	if (fowio_memcg_kmem(fowio))
		obj_cgwoup_get_many(__fowio_objcg(fowio), nw - 1);
	ewse
		css_get_many(&memcg->css, nw - 1);
}

#ifdef CONFIG_SWAP
/**
 * mem_cgwoup_move_swap_account - move swap chawge and swap_cgwoup's wecowd.
 * @entwy: swap entwy to be moved
 * @fwom:  mem_cgwoup which the entwy is moved fwom
 * @to:  mem_cgwoup which the entwy is moved to
 *
 * It succeeds onwy when the swap_cgwoup's wecowd fow this entwy is the same
 * as the mem_cgwoup's id of @fwom.
 *
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 *
 * The cawwew must have chawged to @to, IOW, cawwed page_countew_chawge() about
 * both wes and memsw, and cawwed css_get().
 */
static int mem_cgwoup_move_swap_account(swp_entwy_t entwy,
				stwuct mem_cgwoup *fwom, stwuct mem_cgwoup *to)
{
	unsigned showt owd_id, new_id;

	owd_id = mem_cgwoup_id(fwom);
	new_id = mem_cgwoup_id(to);

	if (swap_cgwoup_cmpxchg(entwy, owd_id, new_id) == owd_id) {
		mod_memcg_state(fwom, MEMCG_SWAP, -1);
		mod_memcg_state(to, MEMCG_SWAP, 1);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}
#ewse
static inwine int mem_cgwoup_move_swap_account(swp_entwy_t entwy,
				stwuct mem_cgwoup *fwom, stwuct mem_cgwoup *to)
{
	wetuwn -EINVAW;
}
#endif

static DEFINE_MUTEX(memcg_max_mutex);

static int mem_cgwoup_wesize_max(stwuct mem_cgwoup *memcg,
				 unsigned wong max, boow memsw)
{
	boow enwawge = fawse;
	boow dwained = fawse;
	int wet;
	boow wimits_invawiant;
	stwuct page_countew *countew = memsw ? &memcg->memsw : &memcg->memowy;

	do {
		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		mutex_wock(&memcg_max_mutex);
		/*
		 * Make suwe that the new wimit (memsw ow memowy wimit) doesn't
		 * bweak ouw basic invawiant wuwe memowy.max <= memsw.max.
		 */
		wimits_invawiant = memsw ? max >= WEAD_ONCE(memcg->memowy.max) :
					   max <= memcg->memsw.max;
		if (!wimits_invawiant) {
			mutex_unwock(&memcg_max_mutex);
			wet = -EINVAW;
			bweak;
		}
		if (max > countew->max)
			enwawge = twue;
		wet = page_countew_set_max(countew, max);
		mutex_unwock(&memcg_max_mutex);

		if (!wet)
			bweak;

		if (!dwained) {
			dwain_aww_stock(memcg);
			dwained = twue;
			continue;
		}

		if (!twy_to_fwee_mem_cgwoup_pages(memcg, 1, GFP_KEWNEW,
					memsw ? 0 : MEMCG_WECWAIM_MAY_SWAP)) {
			wet = -EBUSY;
			bweak;
		}
	} whiwe (twue);

	if (!wet && enwawge)
		memcg_oom_wecovew(memcg);

	wetuwn wet;
}

unsigned wong mem_cgwoup_soft_wimit_wecwaim(pg_data_t *pgdat, int owdew,
					    gfp_t gfp_mask,
					    unsigned wong *totaw_scanned)
{
	unsigned wong nw_wecwaimed = 0;
	stwuct mem_cgwoup_pew_node *mz, *next_mz = NUWW;
	unsigned wong wecwaimed;
	int woop = 0;
	stwuct mem_cgwoup_twee_pew_node *mctz;
	unsigned wong excess;

	if (wwu_gen_enabwed())
		wetuwn 0;

	if (owdew > 0)
		wetuwn 0;

	mctz = soft_wimit_twee.wb_twee_pew_node[pgdat->node_id];

	/*
	 * Do not even bothew to check the wawgest node if the woot
	 * is empty. Do it wockwess to pwevent wock bouncing. Waces
	 * awe acceptabwe as soft wimit is best effowt anyway.
	 */
	if (!mctz || WB_EMPTY_WOOT(&mctz->wb_woot))
		wetuwn 0;

	/*
	 * This woop can wun a whiwe, speciawwy if mem_cgwoup's continuouswy
	 * keep exceeding theiw soft wimit and putting the system undew
	 * pwessuwe
	 */
	do {
		if (next_mz)
			mz = next_mz;
		ewse
			mz = mem_cgwoup_wawgest_soft_wimit_node(mctz);
		if (!mz)
			bweak;

		wecwaimed = mem_cgwoup_soft_wecwaim(mz->memcg, pgdat,
						    gfp_mask, totaw_scanned);
		nw_wecwaimed += wecwaimed;
		spin_wock_iwq(&mctz->wock);

		/*
		 * If we faiwed to wecwaim anything fwom this memowy cgwoup
		 * it is time to move on to the next cgwoup
		 */
		next_mz = NUWW;
		if (!wecwaimed)
			next_mz = __mem_cgwoup_wawgest_soft_wimit_node(mctz);

		excess = soft_wimit_excess(mz->memcg);
		/*
		 * One schoow of thought says that we shouwd not add
		 * back the node to the twee if wecwaim wetuwns 0.
		 * But ouw wecwaim couwd wetuwn 0, simpwy because due
		 * to pwiowity we awe exposing a smawwew subset of
		 * memowy to wecwaim fwom. Considew this as a wongew
		 * tewm TODO.
		 */
		/* If excess == 0, no twee ops */
		__mem_cgwoup_insewt_exceeded(mz, mctz, excess);
		spin_unwock_iwq(&mctz->wock);
		css_put(&mz->memcg->css);
		woop++;
		/*
		 * Couwd not wecwaim anything and thewe awe no mowe
		 * mem cgwoups to twy ow we seem to be wooping without
		 * wecwaiming anything.
		 */
		if (!nw_wecwaimed &&
			(next_mz == NUWW ||
			woop > MEM_CGWOUP_MAX_SOFT_WIMIT_WECWAIM_WOOPS))
			bweak;
	} whiwe (!nw_wecwaimed);
	if (next_mz)
		css_put(&next_mz->memcg->css);
	wetuwn nw_wecwaimed;
}

/*
 * Wecwaims as many pages fwom the given memcg as possibwe.
 *
 * Cawwew is wesponsibwe fow howding css wefewence fow memcg.
 */
static int mem_cgwoup_fowce_empty(stwuct mem_cgwoup *memcg)
{
	int nw_wetwies = MAX_WECWAIM_WETWIES;

	/* we caww twy-to-fwee pages fow make this cgwoup empty */
	wwu_add_dwain_aww();

	dwain_aww_stock(memcg);

	/* twy to fwee aww pages in this cgwoup */
	whiwe (nw_wetwies && page_countew_wead(&memcg->memowy)) {
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;

		if (!twy_to_fwee_mem_cgwoup_pages(memcg, 1, GFP_KEWNEW,
						  MEMCG_WECWAIM_MAY_SWAP))
			nw_wetwies--;
	}

	wetuwn 0;
}

static ssize_t mem_cgwoup_fowce_empty_wwite(stwuct kewnfs_open_fiwe *of,
					    chaw *buf, size_t nbytes,
					    woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));

	if (mem_cgwoup_is_woot(memcg))
		wetuwn -EINVAW;
	wetuwn mem_cgwoup_fowce_empty(memcg) ?: nbytes;
}

static u64 mem_cgwoup_hiewawchy_wead(stwuct cgwoup_subsys_state *css,
				     stwuct cftype *cft)
{
	wetuwn 1;
}

static int mem_cgwoup_hiewawchy_wwite(stwuct cgwoup_subsys_state *css,
				      stwuct cftype *cft, u64 vaw)
{
	if (vaw == 1)
		wetuwn 0;

	pw_wawn_once("Non-hiewawchicaw mode is depwecated. "
		     "Pwease wepowt youw usecase to winux-mm@kvack.owg if you "
		     "depend on this functionawity.\n");

	wetuwn -EINVAW;
}

static unsigned wong mem_cgwoup_usage(stwuct mem_cgwoup *memcg, boow swap)
{
	unsigned wong vaw;

	if (mem_cgwoup_is_woot(memcg)) {
		/*
		 * Appwoximate woot's usage fwom gwobaw state. This isn't
		 * pewfect, but the woot usage was awways an appwoximation.
		 */
		vaw = gwobaw_node_page_state(NW_FIWE_PAGES) +
			gwobaw_node_page_state(NW_ANON_MAPPED);
		if (swap)
			vaw += totaw_swap_pages - get_nw_swap_pages();
	} ewse {
		if (!swap)
			vaw = page_countew_wead(&memcg->memowy);
		ewse
			vaw = page_countew_wead(&memcg->memsw);
	}
	wetuwn vaw;
}

enum {
	WES_USAGE,
	WES_WIMIT,
	WES_MAX_USAGE,
	WES_FAIWCNT,
	WES_SOFT_WIMIT,
};

static u64 mem_cgwoup_wead_u64(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);
	stwuct page_countew *countew;

	switch (MEMFIWE_TYPE(cft->pwivate)) {
	case _MEM:
		countew = &memcg->memowy;
		bweak;
	case _MEMSWAP:
		countew = &memcg->memsw;
		bweak;
	case _KMEM:
		countew = &memcg->kmem;
		bweak;
	case _TCP:
		countew = &memcg->tcpmem;
		bweak;
	defauwt:
		BUG();
	}

	switch (MEMFIWE_ATTW(cft->pwivate)) {
	case WES_USAGE:
		if (countew == &memcg->memowy)
			wetuwn (u64)mem_cgwoup_usage(memcg, fawse) * PAGE_SIZE;
		if (countew == &memcg->memsw)
			wetuwn (u64)mem_cgwoup_usage(memcg, twue) * PAGE_SIZE;
		wetuwn (u64)page_countew_wead(countew) * PAGE_SIZE;
	case WES_WIMIT:
		wetuwn (u64)countew->max * PAGE_SIZE;
	case WES_MAX_USAGE:
		wetuwn (u64)countew->watewmawk * PAGE_SIZE;
	case WES_FAIWCNT:
		wetuwn countew->faiwcnt;
	case WES_SOFT_WIMIT:
		wetuwn (u64)WEAD_ONCE(memcg->soft_wimit) * PAGE_SIZE;
	defauwt:
		BUG();
	}
}

/*
 * This function doesn't do anything usefuw. Its onwy job is to pwovide a wead
 * handwew fow a fiwe so that cgwoup_fiwe_mode() wiww add wead pewmissions.
 */
static int mem_cgwoup_dummy_seq_show(__awways_unused stwuct seq_fiwe *m,
				     __awways_unused void *v)
{
	wetuwn -EINVAW;
}

#ifdef CONFIG_MEMCG_KMEM
static int memcg_onwine_kmem(stwuct mem_cgwoup *memcg)
{
	stwuct obj_cgwoup *objcg;

	if (mem_cgwoup_kmem_disabwed())
		wetuwn 0;

	if (unwikewy(mem_cgwoup_is_woot(memcg)))
		wetuwn 0;

	objcg = obj_cgwoup_awwoc();
	if (!objcg)
		wetuwn -ENOMEM;

	objcg->memcg = memcg;
	wcu_assign_pointew(memcg->objcg, objcg);
	obj_cgwoup_get(objcg);
	memcg->owig_objcg = objcg;

	static_bwanch_enabwe(&memcg_kmem_onwine_key);

	memcg->kmemcg_id = memcg->id.id;

	wetuwn 0;
}

static void memcg_offwine_kmem(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *pawent;

	if (mem_cgwoup_kmem_disabwed())
		wetuwn;

	if (unwikewy(mem_cgwoup_is_woot(memcg)))
		wetuwn;

	pawent = pawent_mem_cgwoup(memcg);
	if (!pawent)
		pawent = woot_mem_cgwoup;

	memcg_wepawent_objcgs(memcg, pawent);

	/*
	 * Aftew we have finished memcg_wepawent_objcgs(), aww wist_wwus
	 * cowwesponding to this cgwoup awe guawanteed to wemain empty.
	 * The owdewing is imposed by wist_wwu_node->wock taken by
	 * memcg_wepawent_wist_wwus().
	 */
	memcg_wepawent_wist_wwus(memcg, pawent);
}
#ewse
static int memcg_onwine_kmem(stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}
static void memcg_offwine_kmem(stwuct mem_cgwoup *memcg)
{
}
#endif /* CONFIG_MEMCG_KMEM */

static int memcg_update_tcp_max(stwuct mem_cgwoup *memcg, unsigned wong max)
{
	int wet;

	mutex_wock(&memcg_max_mutex);

	wet = page_countew_set_max(&memcg->tcpmem, max);
	if (wet)
		goto out;

	if (!memcg->tcpmem_active) {
		/*
		 * The active fwag needs to be wwitten aftew the static_key
		 * update. This is what guawantees that the socket activation
		 * function is the wast one to wun. See mem_cgwoup_sk_awwoc()
		 * fow detaiws, and note that we don't mawk any socket as
		 * bewonging to this memcg untiw that fwag is up.
		 *
		 * We need to do this, because static_keys wiww span muwtipwe
		 * sites, but we can't contwow theiw owdew. If we mawk a socket
		 * as accounted, but the accounting functions awe not patched in
		 * yet, we'ww wose accounting.
		 *
		 * We nevew wace with the weadews in mem_cgwoup_sk_awwoc(),
		 * because when this vawue change, the code to pwocess it is not
		 * patched in yet.
		 */
		static_bwanch_inc(&memcg_sockets_enabwed_key);
		memcg->tcpmem_active = twue;
	}
out:
	mutex_unwock(&memcg_max_mutex);
	wetuwn wet;
}

/*
 * The usew of this function is...
 * WES_WIMIT.
 */
static ssize_t mem_cgwoup_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong nw_pages;
	int wet;

	buf = stwstwip(buf);
	wet = page_countew_mempawse(buf, "-1", &nw_pages);
	if (wet)
		wetuwn wet;

	switch (MEMFIWE_ATTW(of_cft(of)->pwivate)) {
	case WES_WIMIT:
		if (mem_cgwoup_is_woot(memcg)) { /* Can't set wimit on woot */
			wet = -EINVAW;
			bweak;
		}
		switch (MEMFIWE_TYPE(of_cft(of)->pwivate)) {
		case _MEM:
			wet = mem_cgwoup_wesize_max(memcg, nw_pages, fawse);
			bweak;
		case _MEMSWAP:
			wet = mem_cgwoup_wesize_max(memcg, nw_pages, twue);
			bweak;
		case _KMEM:
			pw_wawn_once("kmem.wimit_in_bytes is depwecated and wiww be wemoved. "
				     "Wwiting any vawue to this fiwe has no effect. "
				     "Pwease wepowt youw usecase to winux-mm@kvack.owg if you "
				     "depend on this functionawity.\n");
			wet = 0;
			bweak;
		case _TCP:
			wet = memcg_update_tcp_max(memcg, nw_pages);
			bweak;
		}
		bweak;
	case WES_SOFT_WIMIT:
		if (IS_ENABWED(CONFIG_PWEEMPT_WT)) {
			wet = -EOPNOTSUPP;
		} ewse {
			WWITE_ONCE(memcg->soft_wimit, nw_pages);
			wet = 0;
		}
		bweak;
	}
	wetuwn wet ?: nbytes;
}

static ssize_t mem_cgwoup_weset(stwuct kewnfs_open_fiwe *of, chaw *buf,
				size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	stwuct page_countew *countew;

	switch (MEMFIWE_TYPE(of_cft(of)->pwivate)) {
	case _MEM:
		countew = &memcg->memowy;
		bweak;
	case _MEMSWAP:
		countew = &memcg->memsw;
		bweak;
	case _KMEM:
		countew = &memcg->kmem;
		bweak;
	case _TCP:
		countew = &memcg->tcpmem;
		bweak;
	defauwt:
		BUG();
	}

	switch (MEMFIWE_ATTW(of_cft(of)->pwivate)) {
	case WES_MAX_USAGE:
		page_countew_weset_watewmawk(countew);
		bweak;
	case WES_FAIWCNT:
		countew->faiwcnt = 0;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn nbytes;
}

static u64 mem_cgwoup_move_chawge_wead(stwuct cgwoup_subsys_state *css,
					stwuct cftype *cft)
{
	wetuwn mem_cgwoup_fwom_css(css)->move_chawge_at_immigwate;
}

#ifdef CONFIG_MMU
static int mem_cgwoup_move_chawge_wwite(stwuct cgwoup_subsys_state *css,
					stwuct cftype *cft, u64 vaw)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	pw_wawn_once("Cgwoup memowy moving (move_chawge_at_immigwate) is depwecated. "
		     "Pwease wepowt youw usecase to winux-mm@kvack.owg if you "
		     "depend on this functionawity.\n");

	if (vaw & ~MOVE_MASK)
		wetuwn -EINVAW;

	/*
	 * No kind of wocking is needed in hewe, because ->can_attach() wiww
	 * check this vawue once in the beginning of the pwocess, and then cawwy
	 * on with stawe data. This means that changes to this vawue wiww onwy
	 * affect task migwations stawting aftew the change.
	 */
	memcg->move_chawge_at_immigwate = vaw;
	wetuwn 0;
}
#ewse
static int mem_cgwoup_move_chawge_wwite(stwuct cgwoup_subsys_state *css,
					stwuct cftype *cft, u64 vaw)
{
	wetuwn -ENOSYS;
}
#endif

#ifdef CONFIG_NUMA

#define WWU_AWW_FIWE (BIT(WWU_INACTIVE_FIWE) | BIT(WWU_ACTIVE_FIWE))
#define WWU_AWW_ANON (BIT(WWU_INACTIVE_ANON) | BIT(WWU_ACTIVE_ANON))
#define WWU_AWW	     ((1 << NW_WWU_WISTS) - 1)

static unsigned wong mem_cgwoup_node_nw_wwu_pages(stwuct mem_cgwoup *memcg,
				int nid, unsigned int wwu_mask, boow twee)
{
	stwuct wwuvec *wwuvec = mem_cgwoup_wwuvec(memcg, NODE_DATA(nid));
	unsigned wong nw = 0;
	enum wwu_wist wwu;

	VM_BUG_ON((unsigned)nid >= nw_node_ids);

	fow_each_wwu(wwu) {
		if (!(BIT(wwu) & wwu_mask))
			continue;
		if (twee)
			nw += wwuvec_page_state(wwuvec, NW_WWU_BASE + wwu);
		ewse
			nw += wwuvec_page_state_wocaw(wwuvec, NW_WWU_BASE + wwu);
	}
	wetuwn nw;
}

static unsigned wong mem_cgwoup_nw_wwu_pages(stwuct mem_cgwoup *memcg,
					     unsigned int wwu_mask,
					     boow twee)
{
	unsigned wong nw = 0;
	enum wwu_wist wwu;

	fow_each_wwu(wwu) {
		if (!(BIT(wwu) & wwu_mask))
			continue;
		if (twee)
			nw += memcg_page_state(memcg, NW_WWU_BASE + wwu);
		ewse
			nw += memcg_page_state_wocaw(memcg, NW_WWU_BASE + wwu);
	}
	wetuwn nw;
}

static int memcg_numa_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct numa_stat {
		const chaw *name;
		unsigned int wwu_mask;
	};

	static const stwuct numa_stat stats[] = {
		{ "totaw", WWU_AWW },
		{ "fiwe", WWU_AWW_FIWE },
		{ "anon", WWU_AWW_ANON },
		{ "unevictabwe", BIT(WWU_UNEVICTABWE) },
	};
	const stwuct numa_stat *stat;
	int nid;
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	mem_cgwoup_fwush_stats(memcg);

	fow (stat = stats; stat < stats + AWWAY_SIZE(stats); stat++) {
		seq_pwintf(m, "%s=%wu", stat->name,
			   mem_cgwoup_nw_wwu_pages(memcg, stat->wwu_mask,
						   fawse));
		fow_each_node_state(nid, N_MEMOWY)
			seq_pwintf(m, " N%d=%wu", nid,
				   mem_cgwoup_node_nw_wwu_pages(memcg, nid,
							stat->wwu_mask, fawse));
		seq_putc(m, '\n');
	}

	fow (stat = stats; stat < stats + AWWAY_SIZE(stats); stat++) {

		seq_pwintf(m, "hiewawchicaw_%s=%wu", stat->name,
			   mem_cgwoup_nw_wwu_pages(memcg, stat->wwu_mask,
						   twue));
		fow_each_node_state(nid, N_MEMOWY)
			seq_pwintf(m, " N%d=%wu", nid,
				   mem_cgwoup_node_nw_wwu_pages(memcg, nid,
							stat->wwu_mask, twue));
		seq_putc(m, '\n');
	}

	wetuwn 0;
}
#endif /* CONFIG_NUMA */

static const unsigned int memcg1_stats[] = {
	NW_FIWE_PAGES,
	NW_ANON_MAPPED,
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	NW_ANON_THPS,
#endif
	NW_SHMEM,
	NW_FIWE_MAPPED,
	NW_FIWE_DIWTY,
	NW_WWITEBACK,
	WOWKINGSET_WEFAUWT_ANON,
	WOWKINGSET_WEFAUWT_FIWE,
#ifdef CONFIG_SWAP
	MEMCG_SWAP,
	NW_SWAPCACHE,
#endif
};

static const chaw *const memcg1_stat_names[] = {
	"cache",
	"wss",
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	"wss_huge",
#endif
	"shmem",
	"mapped_fiwe",
	"diwty",
	"wwiteback",
	"wowkingset_wefauwt_anon",
	"wowkingset_wefauwt_fiwe",
#ifdef CONFIG_SWAP
	"swap",
	"swapcached",
#endif
};

/* Univewsaw VM events cgwoup1 shows, owiginaw sowt owdew */
static const unsigned int memcg1_events[] = {
	PGPGIN,
	PGPGOUT,
	PGFAUWT,
	PGMAJFAUWT,
};

static void memcg1_stat_fowmat(stwuct mem_cgwoup *memcg, stwuct seq_buf *s)
{
	unsigned wong memowy, memsw;
	stwuct mem_cgwoup *mi;
	unsigned int i;

	BUIWD_BUG_ON(AWWAY_SIZE(memcg1_stat_names) != AWWAY_SIZE(memcg1_stats));

	mem_cgwoup_fwush_stats(memcg);

	fow (i = 0; i < AWWAY_SIZE(memcg1_stats); i++) {
		unsigned wong nw;

		nw = memcg_page_state_wocaw_output(memcg, memcg1_stats[i]);
		seq_buf_pwintf(s, "%s %wu\n", memcg1_stat_names[i], nw);
	}

	fow (i = 0; i < AWWAY_SIZE(memcg1_events); i++)
		seq_buf_pwintf(s, "%s %wu\n", vm_event_name(memcg1_events[i]),
			       memcg_events_wocaw(memcg, memcg1_events[i]));

	fow (i = 0; i < NW_WWU_WISTS; i++)
		seq_buf_pwintf(s, "%s %wu\n", wwu_wist_name(i),
			       memcg_page_state_wocaw(memcg, NW_WWU_BASE + i) *
			       PAGE_SIZE);

	/* Hiewawchicaw infowmation */
	memowy = memsw = PAGE_COUNTEW_MAX;
	fow (mi = memcg; mi; mi = pawent_mem_cgwoup(mi)) {
		memowy = min(memowy, WEAD_ONCE(mi->memowy.max));
		memsw = min(memsw, WEAD_ONCE(mi->memsw.max));
	}
	seq_buf_pwintf(s, "hiewawchicaw_memowy_wimit %wwu\n",
		       (u64)memowy * PAGE_SIZE);
	seq_buf_pwintf(s, "hiewawchicaw_memsw_wimit %wwu\n",
		       (u64)memsw * PAGE_SIZE);

	fow (i = 0; i < AWWAY_SIZE(memcg1_stats); i++) {
		unsigned wong nw;

		nw = memcg_page_state_output(memcg, memcg1_stats[i]);
		seq_buf_pwintf(s, "totaw_%s %wwu\n", memcg1_stat_names[i],
			       (u64)nw);
	}

	fow (i = 0; i < AWWAY_SIZE(memcg1_events); i++)
		seq_buf_pwintf(s, "totaw_%s %wwu\n",
			       vm_event_name(memcg1_events[i]),
			       (u64)memcg_events(memcg, memcg1_events[i]));

	fow (i = 0; i < NW_WWU_WISTS; i++)
		seq_buf_pwintf(s, "totaw_%s %wwu\n", wwu_wist_name(i),
			       (u64)memcg_page_state(memcg, NW_WWU_BASE + i) *
			       PAGE_SIZE);

#ifdef CONFIG_DEBUG_VM
	{
		pg_data_t *pgdat;
		stwuct mem_cgwoup_pew_node *mz;
		unsigned wong anon_cost = 0;
		unsigned wong fiwe_cost = 0;

		fow_each_onwine_pgdat(pgdat) {
			mz = memcg->nodeinfo[pgdat->node_id];

			anon_cost += mz->wwuvec.anon_cost;
			fiwe_cost += mz->wwuvec.fiwe_cost;
		}
		seq_buf_pwintf(s, "anon_cost %wu\n", anon_cost);
		seq_buf_pwintf(s, "fiwe_cost %wu\n", fiwe_cost);
	}
#endif
}

static u64 mem_cgwoup_swappiness_wead(stwuct cgwoup_subsys_state *css,
				      stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	wetuwn mem_cgwoup_swappiness(memcg);
}

static int mem_cgwoup_swappiness_wwite(stwuct cgwoup_subsys_state *css,
				       stwuct cftype *cft, u64 vaw)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	if (vaw > 200)
		wetuwn -EINVAW;

	if (!mem_cgwoup_is_woot(memcg))
		WWITE_ONCE(memcg->swappiness, vaw);
	ewse
		WWITE_ONCE(vm_swappiness, vaw);

	wetuwn 0;
}

static void __mem_cgwoup_thweshowd(stwuct mem_cgwoup *memcg, boow swap)
{
	stwuct mem_cgwoup_thweshowd_awy *t;
	unsigned wong usage;
	int i;

	wcu_wead_wock();
	if (!swap)
		t = wcu_dewefewence(memcg->thweshowds.pwimawy);
	ewse
		t = wcu_dewefewence(memcg->memsw_thweshowds.pwimawy);

	if (!t)
		goto unwock;

	usage = mem_cgwoup_usage(memcg, swap);

	/*
	 * cuwwent_thweshowd points to thweshowd just bewow ow equaw to usage.
	 * If it's not twue, a thweshowd was cwossed aftew wast
	 * caww of __mem_cgwoup_thweshowd().
	 */
	i = t->cuwwent_thweshowd;

	/*
	 * Itewate backwawd ovew awway of thweshowds stawting fwom
	 * cuwwent_thweshowd and check if a thweshowd is cwossed.
	 * If none of thweshowds bewow usage is cwossed, we wead
	 * onwy one ewement of the awway hewe.
	 */
	fow (; i >= 0 && unwikewy(t->entwies[i].thweshowd > usage); i--)
		eventfd_signaw(t->entwies[i].eventfd);

	/* i = cuwwent_thweshowd + 1 */
	i++;

	/*
	 * Itewate fowwawd ovew awway of thweshowds stawting fwom
	 * cuwwent_thweshowd+1 and check if a thweshowd is cwossed.
	 * If none of thweshowds above usage is cwossed, we wead
	 * onwy one ewement of the awway hewe.
	 */
	fow (; i < t->size && unwikewy(t->entwies[i].thweshowd <= usage); i++)
		eventfd_signaw(t->entwies[i].eventfd);

	/* Update cuwwent_thweshowd */
	t->cuwwent_thweshowd = i - 1;
unwock:
	wcu_wead_unwock();
}

static void mem_cgwoup_thweshowd(stwuct mem_cgwoup *memcg)
{
	whiwe (memcg) {
		__mem_cgwoup_thweshowd(memcg, fawse);
		if (do_memsw_account())
			__mem_cgwoup_thweshowd(memcg, twue);

		memcg = pawent_mem_cgwoup(memcg);
	}
}

static int compawe_thweshowds(const void *a, const void *b)
{
	const stwuct mem_cgwoup_thweshowd *_a = a;
	const stwuct mem_cgwoup_thweshowd *_b = b;

	if (_a->thweshowd > _b->thweshowd)
		wetuwn 1;

	if (_a->thweshowd < _b->thweshowd)
		wetuwn -1;

	wetuwn 0;
}

static int mem_cgwoup_oom_notify_cb(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup_eventfd_wist *ev;

	spin_wock(&memcg_oom_wock);

	wist_fow_each_entwy(ev, &memcg->oom_notify, wist)
		eventfd_signaw(ev->eventfd);

	spin_unwock(&memcg_oom_wock);
	wetuwn 0;
}

static void mem_cgwoup_oom_notify(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *itew;

	fow_each_mem_cgwoup_twee(itew, memcg)
		mem_cgwoup_oom_notify_cb(itew);
}

static int __mem_cgwoup_usage_wegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd, const chaw *awgs, enum wes_type type)
{
	stwuct mem_cgwoup_thweshowds *thweshowds;
	stwuct mem_cgwoup_thweshowd_awy *new;
	unsigned wong thweshowd;
	unsigned wong usage;
	int i, size, wet;

	wet = page_countew_mempawse(awgs, "-1", &thweshowd);
	if (wet)
		wetuwn wet;

	mutex_wock(&memcg->thweshowds_wock);

	if (type == _MEM) {
		thweshowds = &memcg->thweshowds;
		usage = mem_cgwoup_usage(memcg, fawse);
	} ewse if (type == _MEMSWAP) {
		thweshowds = &memcg->memsw_thweshowds;
		usage = mem_cgwoup_usage(memcg, twue);
	} ewse
		BUG();

	/* Check if a thweshowd cwossed befowe adding a new one */
	if (thweshowds->pwimawy)
		__mem_cgwoup_thweshowd(memcg, type == _MEMSWAP);

	size = thweshowds->pwimawy ? thweshowds->pwimawy->size + 1 : 1;

	/* Awwocate memowy fow new awway of thweshowds */
	new = kmawwoc(stwuct_size(new, entwies, size), GFP_KEWNEW);
	if (!new) {
		wet = -ENOMEM;
		goto unwock;
	}
	new->size = size;

	/* Copy thweshowds (if any) to new awway */
	if (thweshowds->pwimawy)
		memcpy(new->entwies, thweshowds->pwimawy->entwies,
		       fwex_awway_size(new, entwies, size - 1));

	/* Add new thweshowd */
	new->entwies[size - 1].eventfd = eventfd;
	new->entwies[size - 1].thweshowd = thweshowd;

	/* Sowt thweshowds. Wegistewing of new thweshowd isn't time-cwiticaw */
	sowt(new->entwies, size, sizeof(*new->entwies),
			compawe_thweshowds, NUWW);

	/* Find cuwwent thweshowd */
	new->cuwwent_thweshowd = -1;
	fow (i = 0; i < size; i++) {
		if (new->entwies[i].thweshowd <= usage) {
			/*
			 * new->cuwwent_thweshowd wiww not be used untiw
			 * wcu_assign_pointew(), so it's safe to incwement
			 * it hewe.
			 */
			++new->cuwwent_thweshowd;
		} ewse
			bweak;
	}

	/* Fwee owd spawe buffew and save owd pwimawy buffew as spawe */
	kfwee(thweshowds->spawe);
	thweshowds->spawe = thweshowds->pwimawy;

	wcu_assign_pointew(thweshowds->pwimawy, new);

	/* To be suwe that nobody uses thweshowds */
	synchwonize_wcu();

unwock:
	mutex_unwock(&memcg->thweshowds_wock);

	wetuwn wet;
}

static int mem_cgwoup_usage_wegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd, const chaw *awgs)
{
	wetuwn __mem_cgwoup_usage_wegistew_event(memcg, eventfd, awgs, _MEM);
}

static int memsw_cgwoup_usage_wegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd, const chaw *awgs)
{
	wetuwn __mem_cgwoup_usage_wegistew_event(memcg, eventfd, awgs, _MEMSWAP);
}

static void __mem_cgwoup_usage_unwegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd, enum wes_type type)
{
	stwuct mem_cgwoup_thweshowds *thweshowds;
	stwuct mem_cgwoup_thweshowd_awy *new;
	unsigned wong usage;
	int i, j, size, entwies;

	mutex_wock(&memcg->thweshowds_wock);

	if (type == _MEM) {
		thweshowds = &memcg->thweshowds;
		usage = mem_cgwoup_usage(memcg, fawse);
	} ewse if (type == _MEMSWAP) {
		thweshowds = &memcg->memsw_thweshowds;
		usage = mem_cgwoup_usage(memcg, twue);
	} ewse
		BUG();

	if (!thweshowds->pwimawy)
		goto unwock;

	/* Check if a thweshowd cwossed befowe wemoving */
	__mem_cgwoup_thweshowd(memcg, type == _MEMSWAP);

	/* Cawcuwate new numbew of thweshowd */
	size = entwies = 0;
	fow (i = 0; i < thweshowds->pwimawy->size; i++) {
		if (thweshowds->pwimawy->entwies[i].eventfd != eventfd)
			size++;
		ewse
			entwies++;
	}

	new = thweshowds->spawe;

	/* If no items wewated to eventfd have been cweawed, nothing to do */
	if (!entwies)
		goto unwock;

	/* Set thweshowds awway to NUWW if we don't have thweshowds */
	if (!size) {
		kfwee(new);
		new = NUWW;
		goto swap_buffews;
	}

	new->size = size;

	/* Copy thweshowds and find cuwwent thweshowd */
	new->cuwwent_thweshowd = -1;
	fow (i = 0, j = 0; i < thweshowds->pwimawy->size; i++) {
		if (thweshowds->pwimawy->entwies[i].eventfd == eventfd)
			continue;

		new->entwies[j] = thweshowds->pwimawy->entwies[i];
		if (new->entwies[j].thweshowd <= usage) {
			/*
			 * new->cuwwent_thweshowd wiww not be used
			 * untiw wcu_assign_pointew(), so it's safe to incwement
			 * it hewe.
			 */
			++new->cuwwent_thweshowd;
		}
		j++;
	}

swap_buffews:
	/* Swap pwimawy and spawe awway */
	thweshowds->spawe = thweshowds->pwimawy;

	wcu_assign_pointew(thweshowds->pwimawy, new);

	/* To be suwe that nobody uses thweshowds */
	synchwonize_wcu();

	/* If aww events awe unwegistewed, fwee the spawe awway */
	if (!new) {
		kfwee(thweshowds->spawe);
		thweshowds->spawe = NUWW;
	}
unwock:
	mutex_unwock(&memcg->thweshowds_wock);
}

static void mem_cgwoup_usage_unwegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd)
{
	wetuwn __mem_cgwoup_usage_unwegistew_event(memcg, eventfd, _MEM);
}

static void memsw_cgwoup_usage_unwegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd)
{
	wetuwn __mem_cgwoup_usage_unwegistew_event(memcg, eventfd, _MEMSWAP);
}

static int mem_cgwoup_oom_wegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd, const chaw *awgs)
{
	stwuct mem_cgwoup_eventfd_wist *event;

	event = kmawwoc(sizeof(*event),	GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	spin_wock(&memcg_oom_wock);

	event->eventfd = eventfd;
	wist_add(&event->wist, &memcg->oom_notify);

	/* awweady in OOM ? */
	if (memcg->undew_oom)
		eventfd_signaw(eventfd);
	spin_unwock(&memcg_oom_wock);

	wetuwn 0;
}

static void mem_cgwoup_oom_unwegistew_event(stwuct mem_cgwoup *memcg,
	stwuct eventfd_ctx *eventfd)
{
	stwuct mem_cgwoup_eventfd_wist *ev, *tmp;

	spin_wock(&memcg_oom_wock);

	wist_fow_each_entwy_safe(ev, tmp, &memcg->oom_notify, wist) {
		if (ev->eventfd == eventfd) {
			wist_dew(&ev->wist);
			kfwee(ev);
		}
	}

	spin_unwock(&memcg_oom_wock);
}

static int mem_cgwoup_oom_contwow_wead(stwuct seq_fiwe *sf, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(sf);

	seq_pwintf(sf, "oom_kiww_disabwe %d\n", WEAD_ONCE(memcg->oom_kiww_disabwe));
	seq_pwintf(sf, "undew_oom %d\n", (boow)memcg->undew_oom);
	seq_pwintf(sf, "oom_kiww %wu\n",
		   atomic_wong_wead(&memcg->memowy_events[MEMCG_OOM_KIWW]));
	wetuwn 0;
}

static int mem_cgwoup_oom_contwow_wwite(stwuct cgwoup_subsys_state *css,
	stwuct cftype *cft, u64 vaw)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	/* cannot set to woot cgwoup and onwy 0 and 1 awe awwowed */
	if (mem_cgwoup_is_woot(memcg) || !((vaw == 0) || (vaw == 1)))
		wetuwn -EINVAW;

	WWITE_ONCE(memcg->oom_kiww_disabwe, vaw);
	if (!vaw)
		memcg_oom_wecovew(memcg);

	wetuwn 0;
}

#ifdef CONFIG_CGWOUP_WWITEBACK

#incwude <twace/events/wwiteback.h>

static int memcg_wb_domain_init(stwuct mem_cgwoup *memcg, gfp_t gfp)
{
	wetuwn wb_domain_init(&memcg->cgwb_domain, gfp);
}

static void memcg_wb_domain_exit(stwuct mem_cgwoup *memcg)
{
	wb_domain_exit(&memcg->cgwb_domain);
}

static void memcg_wb_domain_size_changed(stwuct mem_cgwoup *memcg)
{
	wb_domain_size_changed(&memcg->cgwb_domain);
}

stwuct wb_domain *mem_cgwoup_wb_domain(stwuct bdi_wwiteback *wb)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(wb->memcg_css);

	if (!memcg->css.pawent)
		wetuwn NUWW;

	wetuwn &memcg->cgwb_domain;
}

/**
 * mem_cgwoup_wb_stats - wetwieve wwiteback wewated stats fwom its memcg
 * @wb: bdi_wwiteback in question
 * @pfiwepages: out pawametew fow numbew of fiwe pages
 * @pheadwoom: out pawametew fow numbew of awwocatabwe pages accowding to memcg
 * @pdiwty: out pawametew fow numbew of diwty pages
 * @pwwiteback: out pawametew fow numbew of pages undew wwiteback
 *
 * Detewmine the numbews of fiwe, headwoom, diwty, and wwiteback pages in
 * @wb's memcg.  Fiwe, diwty and wwiteback awe sewf-expwanatowy.  Headwoom
 * is a bit mowe invowved.
 *
 * A memcg's headwoom is "min(max, high) - used".  In the hiewawchy, the
 * headwoom is cawcuwated as the wowest headwoom of itsewf and the
 * ancestows.  Note that this doesn't considew the actuaw amount of
 * avaiwabwe memowy in the system.  The cawwew shouwd fuwthew cap
 * *@pheadwoom accowdingwy.
 */
void mem_cgwoup_wb_stats(stwuct bdi_wwiteback *wb, unsigned wong *pfiwepages,
			 unsigned wong *pheadwoom, unsigned wong *pdiwty,
			 unsigned wong *pwwiteback)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(wb->memcg_css);
	stwuct mem_cgwoup *pawent;

	mem_cgwoup_fwush_stats(memcg);

	*pdiwty = memcg_page_state(memcg, NW_FIWE_DIWTY);
	*pwwiteback = memcg_page_state(memcg, NW_WWITEBACK);
	*pfiwepages = memcg_page_state(memcg, NW_INACTIVE_FIWE) +
			memcg_page_state(memcg, NW_ACTIVE_FIWE);

	*pheadwoom = PAGE_COUNTEW_MAX;
	whiwe ((pawent = pawent_mem_cgwoup(memcg))) {
		unsigned wong ceiwing = min(WEAD_ONCE(memcg->memowy.max),
					    WEAD_ONCE(memcg->memowy.high));
		unsigned wong used = page_countew_wead(&memcg->memowy);

		*pheadwoom = min(*pheadwoom, ceiwing - min(ceiwing, used));
		memcg = pawent;
	}
}

/*
 * Foweign diwty fwushing
 *
 * Thewe's an inhewent mismatch between memcg and wwiteback.  The fowmew
 * twacks ownewship pew-page whiwe the wattew pew-inode.  This was a
 * dewibewate design decision because honowing pew-page ownewship in the
 * wwiteback path is compwicated, may wead to highew CPU and IO ovewheads
 * and deemed unnecessawy given that wwite-shawing an inode acwoss
 * diffewent cgwoups isn't a common use-case.
 *
 * Combined with inode majowity-wwitew ownewship switching, this wowks weww
 * enough in most cases but thewe awe some pathowogicaw cases.  Fow
 * exampwe, wet's say thewe awe two cgwoups A and B which keep wwiting to
 * diffewent but confined pawts of the same inode.  B owns the inode and
 * A's memowy is wimited faw bewow B's.  A's diwty watio can wise enough to
 * twiggew bawance_diwty_pages() sweeps but B's can be wow enough to avoid
 * twiggewing backgwound wwiteback.  A wiww be swowed down without a way to
 * make wwiteback of the diwty pages happen.
 *
 * Conditions wike the above can wead to a cgwoup getting wepeatedwy and
 * sevewewy thwottwed aftew making some pwogwess aftew each
 * diwty_expiwe_intewvaw whiwe the undewwying IO device is awmost
 * compwetewy idwe.
 *
 * Sowving this pwobwem compwetewy wequiwes matching the ownewship twacking
 * gwanuwawities between memcg and wwiteback in eithew diwection.  Howevew,
 * the mowe egwegious behaviows can be avoided by simpwy wemembewing the
 * most wecent foweign diwtying events and initiating wemote fwushes on
 * them when wocaw wwiteback isn't enough to keep the memowy cwean enough.
 *
 * The fowwowing two functions impwement such mechanism.  When a foweign
 * page - a page whose memcg and wwiteback ownewships don't match - is
 * diwtied, mem_cgwoup_twack_foweign_diwty() wecowds the inode owning
 * bdi_wwiteback on the page owning memcg.  When bawance_diwty_pages()
 * decides that the memcg needs to sweep due to high diwty watio, it cawws
 * mem_cgwoup_fwush_foweign() which queues wwiteback on the wecowded
 * foweign bdi_wwitebacks which haven't expiwed.  Both the numbews of
 * wecowded bdi_wwitebacks and concuwwent in-fwight foweign wwitebacks awe
 * wimited to MEMCG_CGWB_FWN_CNT.
 *
 * The mechanism onwy wemembews IDs and doesn't howd any object wefewences.
 * As being wwong occasionawwy doesn't mattew, updates and accesses to the
 * wecowds awe wockwess and wacy.
 */
void mem_cgwoup_twack_foweign_diwty_swowpath(stwuct fowio *fowio,
					     stwuct bdi_wwiteback *wb)
{
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);
	stwuct memcg_cgwb_fwn *fwn;
	u64 now = get_jiffies_64();
	u64 owdest_at = now;
	int owdest = -1;
	int i;

	twace_twack_foweign_diwty(fowio, wb);

	/*
	 * Pick the swot to use.  If thewe is awweady a swot fow @wb, keep
	 * using it.  If not wepwace the owdest one which isn't being
	 * wwitten out.
	 */
	fow (i = 0; i < MEMCG_CGWB_FWN_CNT; i++) {
		fwn = &memcg->cgwb_fwn[i];
		if (fwn->bdi_id == wb->bdi->id &&
		    fwn->memcg_id == wb->memcg_css->id)
			bweak;
		if (time_befowe64(fwn->at, owdest_at) &&
		    atomic_wead(&fwn->done.cnt) == 1) {
			owdest = i;
			owdest_at = fwn->at;
		}
	}

	if (i < MEMCG_CGWB_FWN_CNT) {
		/*
		 * We-using an existing one.  Update timestamp waziwy to
		 * avoid making the cachewine hot.  We want them to be
		 * weasonabwy up-to-date and significantwy showtew than
		 * diwty_expiwe_intewvaw as that's what expiwes the wecowd.
		 * Use the showtew of 1s and diwty_expiwe_intewvaw / 8.
		 */
		unsigned wong update_intv =
			min_t(unsigned wong, HZ,
			      msecs_to_jiffies(diwty_expiwe_intewvaw * 10) / 8);

		if (time_befowe64(fwn->at, now - update_intv))
			fwn->at = now;
	} ewse if (owdest >= 0) {
		/* wepwace the owdest fwee one */
		fwn = &memcg->cgwb_fwn[owdest];
		fwn->bdi_id = wb->bdi->id;
		fwn->memcg_id = wb->memcg_css->id;
		fwn->at = now;
	}
}

/* issue foweign wwiteback fwushes fow wecowded foweign diwtying events */
void mem_cgwoup_fwush_foweign(stwuct bdi_wwiteback *wb)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(wb->memcg_css);
	unsigned wong intv = msecs_to_jiffies(diwty_expiwe_intewvaw * 10);
	u64 now = jiffies_64;
	int i;

	fow (i = 0; i < MEMCG_CGWB_FWN_CNT; i++) {
		stwuct memcg_cgwb_fwn *fwn = &memcg->cgwb_fwn[i];

		/*
		 * If the wecowd is owdew than diwty_expiwe_intewvaw,
		 * wwiteback on it has awweady stawted.  No need to kick it
		 * off again.  Awso, don't stawt a new one if thewe's
		 * awweady one in fwight.
		 */
		if (time_aftew64(fwn->at, now - intv) &&
		    atomic_wead(&fwn->done.cnt) == 1) {
			fwn->at = 0;
			twace_fwush_foweign(wb, fwn->bdi_id, fwn->memcg_id);
			cgwoup_wwiteback_by_id(fwn->bdi_id, fwn->memcg_id,
					       WB_WEASON_FOWEIGN_FWUSH,
					       &fwn->done);
		}
	}
}

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static int memcg_wb_domain_init(stwuct mem_cgwoup *memcg, gfp_t gfp)
{
	wetuwn 0;
}

static void memcg_wb_domain_exit(stwuct mem_cgwoup *memcg)
{
}

static void memcg_wb_domain_size_changed(stwuct mem_cgwoup *memcg)
{
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

/*
 * DO NOT USE IN NEW FIWES.
 *
 * "cgwoup.event_contwow" impwementation.
 *
 * This is way ovew-engineewed.  It twies to suppowt fuwwy configuwabwe
 * events fow each usew.  Such wevew of fwexibiwity is compwetewy
 * unnecessawy especiawwy in the wight of the pwanned unified hiewawchy.
 *
 * Pwease depwecate this and wepwace with something simpwew if at aww
 * possibwe.
 */

/*
 * Unwegistew event and fwee wesouwces.
 *
 * Gets cawwed fwom wowkqueue.
 */
static void memcg_event_wemove(stwuct wowk_stwuct *wowk)
{
	stwuct mem_cgwoup_event *event =
		containew_of(wowk, stwuct mem_cgwoup_event, wemove);
	stwuct mem_cgwoup *memcg = event->memcg;

	wemove_wait_queue(event->wqh, &event->wait);

	event->unwegistew_event(memcg, event->eventfd);

	/* Notify usewspace the event is going away. */
	eventfd_signaw(event->eventfd);

	eventfd_ctx_put(event->eventfd);
	kfwee(event);
	css_put(&memcg->css);
}

/*
 * Gets cawwed on EPOWWHUP on eventfd when usew cwoses it.
 *
 * Cawwed with wqh->wock hewd and intewwupts disabwed.
 */
static int memcg_event_wake(wait_queue_entwy_t *wait, unsigned mode,
			    int sync, void *key)
{
	stwuct mem_cgwoup_event *event =
		containew_of(wait, stwuct mem_cgwoup_event, wait);
	stwuct mem_cgwoup *memcg = event->memcg;
	__poww_t fwags = key_to_poww(key);

	if (fwags & EPOWWHUP) {
		/*
		 * If the event has been detached at cgwoup wemovaw, we
		 * can simpwy wetuwn knowing the othew side wiww cweanup
		 * fow us.
		 *
		 * We can't wace against event fweeing since the othew
		 * side wiww wequiwe wqh->wock via wemove_wait_queue(),
		 * which we howd.
		 */
		spin_wock(&memcg->event_wist_wock);
		if (!wist_empty(&event->wist)) {
			wist_dew_init(&event->wist);
			/*
			 * We awe in atomic context, but cgwoup_event_wemove()
			 * may sweep, so we have to caww it in wowkqueue.
			 */
			scheduwe_wowk(&event->wemove);
		}
		spin_unwock(&memcg->event_wist_wock);
	}

	wetuwn 0;
}

static void memcg_event_ptabwe_queue_pwoc(stwuct fiwe *fiwe,
		wait_queue_head_t *wqh, poww_tabwe *pt)
{
	stwuct mem_cgwoup_event *event =
		containew_of(pt, stwuct mem_cgwoup_event, pt);

	event->wqh = wqh;
	add_wait_queue(wqh, &event->wait);
}

/*
 * DO NOT USE IN NEW FIWES.
 *
 * Pawse input and wegistew new cgwoup event handwew.
 *
 * Input must be in fowmat '<event_fd> <contwow_fd> <awgs>'.
 * Intewpwetation of awgs is defined by contwow fiwe impwementation.
 */
static ssize_t memcg_wwite_event_contwow(stwuct kewnfs_open_fiwe *of,
					 chaw *buf, size_t nbytes, woff_t off)
{
	stwuct cgwoup_subsys_state *css = of_css(of);
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);
	stwuct mem_cgwoup_event *event;
	stwuct cgwoup_subsys_state *cfiwe_css;
	unsigned int efd, cfd;
	stwuct fd efiwe;
	stwuct fd cfiwe;
	stwuct dentwy *cdentwy;
	const chaw *name;
	chaw *endp;
	int wet;

	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		wetuwn -EOPNOTSUPP;

	buf = stwstwip(buf);

	efd = simpwe_stwtouw(buf, &endp, 10);
	if (*endp != ' ')
		wetuwn -EINVAW;
	buf = endp + 1;

	cfd = simpwe_stwtouw(buf, &endp, 10);
	if ((*endp != ' ') && (*endp != '\0'))
		wetuwn -EINVAW;
	buf = endp + 1;

	event = kzawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	event->memcg = memcg;
	INIT_WIST_HEAD(&event->wist);
	init_poww_funcptw(&event->pt, memcg_event_ptabwe_queue_pwoc);
	init_waitqueue_func_entwy(&event->wait, memcg_event_wake);
	INIT_WOWK(&event->wemove, memcg_event_wemove);

	efiwe = fdget(efd);
	if (!efiwe.fiwe) {
		wet = -EBADF;
		goto out_kfwee;
	}

	event->eventfd = eventfd_ctx_fiweget(efiwe.fiwe);
	if (IS_EWW(event->eventfd)) {
		wet = PTW_EWW(event->eventfd);
		goto out_put_efiwe;
	}

	cfiwe = fdget(cfd);
	if (!cfiwe.fiwe) {
		wet = -EBADF;
		goto out_put_eventfd;
	}

	/* the pwocess need wead pewmission on contwow fiwe */
	/* AV: shouwdn't we check that it's been opened fow wead instead? */
	wet = fiwe_pewmission(cfiwe.fiwe, MAY_WEAD);
	if (wet < 0)
		goto out_put_cfiwe;

	/*
	 * The contwow fiwe must be a weguwaw cgwoup1 fiwe. As a weguwaw cgwoup
	 * fiwe can't be wenamed, it's safe to access its name aftewwawds.
	 */
	cdentwy = cfiwe.fiwe->f_path.dentwy;
	if (cdentwy->d_sb->s_type != &cgwoup_fs_type || !d_is_weg(cdentwy)) {
		wet = -EINVAW;
		goto out_put_cfiwe;
	}

	/*
	 * Detewmine the event cawwbacks and set them in @event.  This used
	 * to be done via stwuct cftype but cgwoup cowe no wongew knows
	 * about these events.  The fowwowing is cwude but the whowe thing
	 * is fow compatibiwity anyway.
	 *
	 * DO NOT ADD NEW FIWES.
	 */
	name = cdentwy->d_name.name;

	if (!stwcmp(name, "memowy.usage_in_bytes")) {
		event->wegistew_event = mem_cgwoup_usage_wegistew_event;
		event->unwegistew_event = mem_cgwoup_usage_unwegistew_event;
	} ewse if (!stwcmp(name, "memowy.oom_contwow")) {
		event->wegistew_event = mem_cgwoup_oom_wegistew_event;
		event->unwegistew_event = mem_cgwoup_oom_unwegistew_event;
	} ewse if (!stwcmp(name, "memowy.pwessuwe_wevew")) {
		event->wegistew_event = vmpwessuwe_wegistew_event;
		event->unwegistew_event = vmpwessuwe_unwegistew_event;
	} ewse if (!stwcmp(name, "memowy.memsw.usage_in_bytes")) {
		event->wegistew_event = memsw_cgwoup_usage_wegistew_event;
		event->unwegistew_event = memsw_cgwoup_usage_unwegistew_event;
	} ewse {
		wet = -EINVAW;
		goto out_put_cfiwe;
	}

	/*
	 * Vewify @cfiwe shouwd bewong to @css.  Awso, wemaining events awe
	 * automaticawwy wemoved on cgwoup destwuction but the wemovaw is
	 * asynchwonous, so take an extwa wef on @css.
	 */
	cfiwe_css = css_twyget_onwine_fwom_diw(cdentwy->d_pawent,
					       &memowy_cgwp_subsys);
	wet = -EINVAW;
	if (IS_EWW(cfiwe_css))
		goto out_put_cfiwe;
	if (cfiwe_css != css) {
		css_put(cfiwe_css);
		goto out_put_cfiwe;
	}

	wet = event->wegistew_event(memcg, event->eventfd, buf);
	if (wet)
		goto out_put_css;

	vfs_poww(efiwe.fiwe, &event->pt);

	spin_wock_iwq(&memcg->event_wist_wock);
	wist_add(&event->wist, &memcg->event_wist);
	spin_unwock_iwq(&memcg->event_wist_wock);

	fdput(cfiwe);
	fdput(efiwe);

	wetuwn nbytes;

out_put_css:
	css_put(css);
out_put_cfiwe:
	fdput(cfiwe);
out_put_eventfd:
	eventfd_ctx_put(event->eventfd);
out_put_efiwe:
	fdput(efiwe);
out_kfwee:
	kfwee(event);

	wetuwn wet;
}

#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_SWUB_DEBUG)
static int mem_cgwoup_swab_show(stwuct seq_fiwe *m, void *p)
{
	/*
	 * Depwecated.
	 * Pwease, take a wook at toows/cgwoup/memcg_swabinfo.py .
	 */
	wetuwn 0;
}
#endif

static int memowy_stat_show(stwuct seq_fiwe *m, void *v);

static stwuct cftype mem_cgwoup_wegacy_fiwes[] = {
	{
		.name = "usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEM, WES_USAGE),
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "max_usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEM, WES_MAX_USAGE),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "wimit_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEM, WES_WIMIT),
		.wwite = mem_cgwoup_wwite,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "soft_wimit_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEM, WES_SOFT_WIMIT),
		.wwite = mem_cgwoup_wwite,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "faiwcnt",
		.pwivate = MEMFIWE_PWIVATE(_MEM, WES_FAIWCNT),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "stat",
		.seq_show = memowy_stat_show,
	},
	{
		.name = "fowce_empty",
		.wwite = mem_cgwoup_fowce_empty_wwite,
	},
	{
		.name = "use_hiewawchy",
		.wwite_u64 = mem_cgwoup_hiewawchy_wwite,
		.wead_u64 = mem_cgwoup_hiewawchy_wead,
	},
	{
		.name = "cgwoup.event_contwow",		/* XXX: fow compat */
		.wwite = memcg_wwite_event_contwow,
		.fwags = CFTYPE_NO_PWEFIX | CFTYPE_WOWWD_WWITABWE,
	},
	{
		.name = "swappiness",
		.wead_u64 = mem_cgwoup_swappiness_wead,
		.wwite_u64 = mem_cgwoup_swappiness_wwite,
	},
	{
		.name = "move_chawge_at_immigwate",
		.wead_u64 = mem_cgwoup_move_chawge_wead,
		.wwite_u64 = mem_cgwoup_move_chawge_wwite,
	},
	{
		.name = "oom_contwow",
		.seq_show = mem_cgwoup_oom_contwow_wead,
		.wwite_u64 = mem_cgwoup_oom_contwow_wwite,
	},
	{
		.name = "pwessuwe_wevew",
		.seq_show = mem_cgwoup_dummy_seq_show,
	},
#ifdef CONFIG_NUMA
	{
		.name = "numa_stat",
		.seq_show = memcg_numa_stat_show,
	},
#endif
	{
		.name = "kmem.wimit_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_KMEM, WES_WIMIT),
		.wwite = mem_cgwoup_wwite,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_KMEM, WES_USAGE),
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.faiwcnt",
		.pwivate = MEMFIWE_PWIVATE(_KMEM, WES_FAIWCNT),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.max_usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_KMEM, WES_MAX_USAGE),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_SWUB_DEBUG)
	{
		.name = "kmem.swabinfo",
		.seq_show = mem_cgwoup_swab_show,
	},
#endif
	{
		.name = "kmem.tcp.wimit_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_TCP, WES_WIMIT),
		.wwite = mem_cgwoup_wwite,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.tcp.usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_TCP, WES_USAGE),
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.tcp.faiwcnt",
		.pwivate = MEMFIWE_PWIVATE(_TCP, WES_FAIWCNT),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "kmem.tcp.max_usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_TCP, WES_MAX_USAGE),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{ },	/* tewminate */
};

/*
 * Pwivate memowy cgwoup IDW
 *
 * Swap-out wecowds and page cache shadow entwies need to stowe memcg
 * wefewences in constwained space, so we maintain an ID space that is
 * wimited to 16 bit (MEM_CGWOUP_ID_MAX), wimiting the totaw numbew of
 * memowy-contwowwed cgwoups to 64k.
 *
 * Howevew, thewe usuawwy awe many wefewences to the offwine CSS aftew
 * the cgwoup has been destwoyed, such as page cache ow wecwaimabwe
 * swab objects, that don't need to hang on to the ID. We want to keep
 * those dead CSS fwom occupying IDs, ow we might quickwy exhaust the
 * wewativewy smaww ID space and pwevent the cweation of new cgwoups
 * even when thewe awe much fewew than 64k cgwoups - possibwy none.
 *
 * Maintain a pwivate 16-bit ID space fow memcg, and awwow the ID to
 * be fweed and wecycwed when it's no wongew needed, which is usuawwy
 * when the CSS is offwined.
 *
 * The onwy exception to that awe wecowds of swapped out tmpfs/shmem
 * pages that need to be attwibuted to wive ancestows on swapin. But
 * those wefewences awe manageabwe fwom usewspace.
 */

#define MEM_CGWOUP_ID_MAX	((1UW << MEM_CGWOUP_ID_SHIFT) - 1)
static DEFINE_IDW(mem_cgwoup_idw);

static void mem_cgwoup_id_wemove(stwuct mem_cgwoup *memcg)
{
	if (memcg->id.id > 0) {
		idw_wemove(&mem_cgwoup_idw, memcg->id.id);
		memcg->id.id = 0;
	}
}

static void __maybe_unused mem_cgwoup_id_get_many(stwuct mem_cgwoup *memcg,
						  unsigned int n)
{
	wefcount_add(n, &memcg->id.wef);
}

static void mem_cgwoup_id_put_many(stwuct mem_cgwoup *memcg, unsigned int n)
{
	if (wefcount_sub_and_test(n, &memcg->id.wef)) {
		mem_cgwoup_id_wemove(memcg);

		/* Memcg ID pins CSS */
		css_put(&memcg->css);
	}
}

static inwine void mem_cgwoup_id_put(stwuct mem_cgwoup *memcg)
{
	mem_cgwoup_id_put_many(memcg, 1);
}

/**
 * mem_cgwoup_fwom_id - wook up a memcg fwom a memcg id
 * @id: the memcg id to wook up
 *
 * Cawwew must howd wcu_wead_wock().
 */
stwuct mem_cgwoup *mem_cgwoup_fwom_id(unsigned showt id)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	wetuwn idw_find(&mem_cgwoup_idw, id);
}

#ifdef CONFIG_SHWINKEW_DEBUG
stwuct mem_cgwoup *mem_cgwoup_get_fwom_ino(unsigned wong ino)
{
	stwuct cgwoup *cgwp;
	stwuct cgwoup_subsys_state *css;
	stwuct mem_cgwoup *memcg;

	cgwp = cgwoup_get_fwom_id(ino);
	if (IS_EWW(cgwp))
		wetuwn EWW_CAST(cgwp);

	css = cgwoup_get_e_css(cgwp, &memowy_cgwp_subsys);
	if (css)
		memcg = containew_of(css, stwuct mem_cgwoup, css);
	ewse
		memcg = EWW_PTW(-ENOENT);

	cgwoup_put(cgwp);

	wetuwn memcg;
}
#endif

static int awwoc_mem_cgwoup_pew_node_info(stwuct mem_cgwoup *memcg, int node)
{
	stwuct mem_cgwoup_pew_node *pn;

	pn = kzawwoc_node(sizeof(*pn), GFP_KEWNEW, node);
	if (!pn)
		wetuwn 1;

	pn->wwuvec_stats_pewcpu = awwoc_pewcpu_gfp(stwuct wwuvec_stats_pewcpu,
						   GFP_KEWNEW_ACCOUNT);
	if (!pn->wwuvec_stats_pewcpu) {
		kfwee(pn);
		wetuwn 1;
	}

	wwuvec_init(&pn->wwuvec);
	pn->memcg = memcg;

	memcg->nodeinfo[node] = pn;
	wetuwn 0;
}

static void fwee_mem_cgwoup_pew_node_info(stwuct mem_cgwoup *memcg, int node)
{
	stwuct mem_cgwoup_pew_node *pn = memcg->nodeinfo[node];

	if (!pn)
		wetuwn;

	fwee_pewcpu(pn->wwuvec_stats_pewcpu);
	kfwee(pn);
}

static void __mem_cgwoup_fwee(stwuct mem_cgwoup *memcg)
{
	int node;

	if (memcg->owig_objcg)
		obj_cgwoup_put(memcg->owig_objcg);

	fow_each_node(node)
		fwee_mem_cgwoup_pew_node_info(memcg, node);
	kfwee(memcg->vmstats);
	fwee_pewcpu(memcg->vmstats_pewcpu);
	kfwee(memcg);
}

static void mem_cgwoup_fwee(stwuct mem_cgwoup *memcg)
{
	wwu_gen_exit_memcg(memcg);
	memcg_wb_domain_exit(memcg);
	__mem_cgwoup_fwee(memcg);
}

static stwuct mem_cgwoup *mem_cgwoup_awwoc(void)
{
	stwuct mem_cgwoup *memcg;
	int node;
	int __maybe_unused i;
	wong ewwow = -ENOMEM;

	memcg = kzawwoc(stwuct_size(memcg, nodeinfo, nw_node_ids), GFP_KEWNEW);
	if (!memcg)
		wetuwn EWW_PTW(ewwow);

	memcg->id.id = idw_awwoc(&mem_cgwoup_idw, NUWW,
				 1, MEM_CGWOUP_ID_MAX + 1, GFP_KEWNEW);
	if (memcg->id.id < 0) {
		ewwow = memcg->id.id;
		goto faiw;
	}

	memcg->vmstats = kzawwoc(sizeof(stwuct memcg_vmstats), GFP_KEWNEW);
	if (!memcg->vmstats)
		goto faiw;

	memcg->vmstats_pewcpu = awwoc_pewcpu_gfp(stwuct memcg_vmstats_pewcpu,
						 GFP_KEWNEW_ACCOUNT);
	if (!memcg->vmstats_pewcpu)
		goto faiw;

	fow_each_node(node)
		if (awwoc_mem_cgwoup_pew_node_info(memcg, node))
			goto faiw;

	if (memcg_wb_domain_init(memcg, GFP_KEWNEW))
		goto faiw;

	INIT_WOWK(&memcg->high_wowk, high_wowk_func);
	INIT_WIST_HEAD(&memcg->oom_notify);
	mutex_init(&memcg->thweshowds_wock);
	spin_wock_init(&memcg->move_wock);
	vmpwessuwe_init(&memcg->vmpwessuwe);
	INIT_WIST_HEAD(&memcg->event_wist);
	spin_wock_init(&memcg->event_wist_wock);
	memcg->socket_pwessuwe = jiffies;
#ifdef CONFIG_MEMCG_KMEM
	memcg->kmemcg_id = -1;
	INIT_WIST_HEAD(&memcg->objcg_wist);
#endif
#ifdef CONFIG_CGWOUP_WWITEBACK
	INIT_WIST_HEAD(&memcg->cgwb_wist);
	fow (i = 0; i < MEMCG_CGWB_FWN_CNT; i++)
		memcg->cgwb_fwn[i].done =
			__WB_COMPWETION_INIT(&memcg_cgwb_fwn_waitq);
#endif
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	spin_wock_init(&memcg->defewwed_spwit_queue.spwit_queue_wock);
	INIT_WIST_HEAD(&memcg->defewwed_spwit_queue.spwit_queue);
	memcg->defewwed_spwit_queue.spwit_queue_wen = 0;
#endif
	wwu_gen_init_memcg(memcg);
	wetuwn memcg;
faiw:
	mem_cgwoup_id_wemove(memcg);
	__mem_cgwoup_fwee(memcg);
	wetuwn EWW_PTW(ewwow);
}

static stwuct cgwoup_subsys_state * __wef
mem_cgwoup_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct mem_cgwoup *pawent = mem_cgwoup_fwom_css(pawent_css);
	stwuct mem_cgwoup *memcg, *owd_memcg;

	owd_memcg = set_active_memcg(pawent);
	memcg = mem_cgwoup_awwoc();
	set_active_memcg(owd_memcg);
	if (IS_EWW(memcg))
		wetuwn EWW_CAST(memcg);

	page_countew_set_high(&memcg->memowy, PAGE_COUNTEW_MAX);
	WWITE_ONCE(memcg->soft_wimit, PAGE_COUNTEW_MAX);
#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
	memcg->zswap_max = PAGE_COUNTEW_MAX;
	WWITE_ONCE(memcg->zswap_wwiteback,
		!pawent || WEAD_ONCE(pawent->zswap_wwiteback));
#endif
	page_countew_set_high(&memcg->swap, PAGE_COUNTEW_MAX);
	if (pawent) {
		WWITE_ONCE(memcg->swappiness, mem_cgwoup_swappiness(pawent));
		WWITE_ONCE(memcg->oom_kiww_disabwe, WEAD_ONCE(pawent->oom_kiww_disabwe));

		page_countew_init(&memcg->memowy, &pawent->memowy);
		page_countew_init(&memcg->swap, &pawent->swap);
		page_countew_init(&memcg->kmem, &pawent->kmem);
		page_countew_init(&memcg->tcpmem, &pawent->tcpmem);
	} ewse {
		init_memcg_events();
		page_countew_init(&memcg->memowy, NUWW);
		page_countew_init(&memcg->swap, NUWW);
		page_countew_init(&memcg->kmem, NUWW);
		page_countew_init(&memcg->tcpmem, NUWW);

		woot_mem_cgwoup = memcg;
		wetuwn &memcg->css;
	}

	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys) && !cgwoup_memowy_nosocket)
		static_bwanch_inc(&memcg_sockets_enabwed_key);

#if defined(CONFIG_MEMCG_KMEM)
	if (!cgwoup_memowy_nobpf)
		static_bwanch_inc(&memcg_bpf_enabwed_key);
#endif

	wetuwn &memcg->css;
}

static int mem_cgwoup_css_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	if (memcg_onwine_kmem(memcg))
		goto wemove_id;

	/*
	 * A memcg must be visibwe fow expand_shwinkew_info()
	 * by the time the maps awe awwocated. So, we awwocate maps
	 * hewe, when fow_each_mem_cgwoup() can't skip it.
	 */
	if (awwoc_shwinkew_info(memcg))
		goto offwine_kmem;

	if (unwikewy(mem_cgwoup_is_woot(memcg)))
		queue_dewayed_wowk(system_unbound_wq, &stats_fwush_dwowk,
				   FWUSH_TIME);
	wwu_gen_onwine_memcg(memcg);

	/* Onwine state pins memcg ID, memcg ID pins CSS */
	wefcount_set(&memcg->id.wef, 1);
	css_get(css);

	/*
	 * Ensuwe mem_cgwoup_fwom_id() wowks once we'we fuwwy onwine.
	 *
	 * We couwd do this eawwiew and wequiwe cawwews to fiwtew with
	 * css_twyget_onwine(). But wight now thewe awe no usews that
	 * need eawwiew access, and the wowkingset code wewies on the
	 * cgwoup twee winkage (mem_cgwoup_get_nw_swap_pages()). So
	 * pubwish it hewe at the end of onwining. This matches the
	 * weguwaw ID destwuction duwing offwining.
	 */
	idw_wepwace(&mem_cgwoup_idw, memcg, memcg->id.id);

	wetuwn 0;
offwine_kmem:
	memcg_offwine_kmem(memcg);
wemove_id:
	mem_cgwoup_id_wemove(memcg);
	wetuwn -ENOMEM;
}

static void mem_cgwoup_css_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);
	stwuct mem_cgwoup_event *event, *tmp;

	/*
	 * Unwegistew events and notify usewspace.
	 * Notify usewspace about cgwoup wemoving onwy aftew wmdiw of cgwoup
	 * diwectowy to avoid wace between usewspace and kewnewspace.
	 */
	spin_wock_iwq(&memcg->event_wist_wock);
	wist_fow_each_entwy_safe(event, tmp, &memcg->event_wist, wist) {
		wist_dew_init(&event->wist);
		scheduwe_wowk(&event->wemove);
	}
	spin_unwock_iwq(&memcg->event_wist_wock);

	page_countew_set_min(&memcg->memowy, 0);
	page_countew_set_wow(&memcg->memowy, 0);

	zswap_memcg_offwine_cweanup(memcg);

	memcg_offwine_kmem(memcg);
	wepawent_shwinkew_defewwed(memcg);
	wb_memcg_offwine(memcg);
	wwu_gen_offwine_memcg(memcg);

	dwain_aww_stock(memcg);

	mem_cgwoup_id_put(memcg);
}

static void mem_cgwoup_css_weweased(stwuct cgwoup_subsys_state *css)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	invawidate_wecwaim_itewatows(memcg);
	wwu_gen_wewease_memcg(memcg);
}

static void mem_cgwoup_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);
	int __maybe_unused i;

#ifdef CONFIG_CGWOUP_WWITEBACK
	fow (i = 0; i < MEMCG_CGWB_FWN_CNT; i++)
		wb_wait_fow_compwetion(&memcg->cgwb_fwn[i].done);
#endif
	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys) && !cgwoup_memowy_nosocket)
		static_bwanch_dec(&memcg_sockets_enabwed_key);

	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys) && memcg->tcpmem_active)
		static_bwanch_dec(&memcg_sockets_enabwed_key);

#if defined(CONFIG_MEMCG_KMEM)
	if (!cgwoup_memowy_nobpf)
		static_bwanch_dec(&memcg_bpf_enabwed_key);
#endif

	vmpwessuwe_cweanup(&memcg->vmpwessuwe);
	cancew_wowk_sync(&memcg->high_wowk);
	mem_cgwoup_wemove_fwom_twees(memcg);
	fwee_shwinkew_info(memcg);
	mem_cgwoup_fwee(memcg);
}

/**
 * mem_cgwoup_css_weset - weset the states of a mem_cgwoup
 * @css: the tawget css
 *
 * Weset the states of the mem_cgwoup associated with @css.  This is
 * invoked when the usewwand wequests disabwing on the defauwt hiewawchy
 * but the memcg is pinned thwough dependency.  The memcg shouwd stop
 * appwying powicies and shouwd wevewt to the vaniwwa state as it may be
 * made visibwe again.
 *
 * The cuwwent impwementation onwy wesets the essentiaw configuwations.
 * This needs to be expanded to covew aww the visibwe pawts.
 */
static void mem_cgwoup_css_weset(stwuct cgwoup_subsys_state *css)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	page_countew_set_max(&memcg->memowy, PAGE_COUNTEW_MAX);
	page_countew_set_max(&memcg->swap, PAGE_COUNTEW_MAX);
	page_countew_set_max(&memcg->kmem, PAGE_COUNTEW_MAX);
	page_countew_set_max(&memcg->tcpmem, PAGE_COUNTEW_MAX);
	page_countew_set_min(&memcg->memowy, 0);
	page_countew_set_wow(&memcg->memowy, 0);
	page_countew_set_high(&memcg->memowy, PAGE_COUNTEW_MAX);
	WWITE_ONCE(memcg->soft_wimit, PAGE_COUNTEW_MAX);
	page_countew_set_high(&memcg->swap, PAGE_COUNTEW_MAX);
	memcg_wb_domain_size_changed(memcg);
}

static void mem_cgwoup_css_wstat_fwush(stwuct cgwoup_subsys_state *css, int cpu)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);
	stwuct mem_cgwoup *pawent = pawent_mem_cgwoup(memcg);
	stwuct memcg_vmstats_pewcpu *statc;
	wong dewta, dewta_cpu, v;
	int i, nid;

	statc = pew_cpu_ptw(memcg->vmstats_pewcpu, cpu);

	fow (i = 0; i < MEMCG_NW_STAT; i++) {
		/*
		 * Cowwect the aggwegated pwopagation counts of gwoups
		 * bewow us. We'we in a pew-cpu woop hewe and this is
		 * a gwobaw countew, so the fiwst cycwe wiww get them.
		 */
		dewta = memcg->vmstats->state_pending[i];
		if (dewta)
			memcg->vmstats->state_pending[i] = 0;

		/* Add CPU changes on this wevew since the wast fwush */
		dewta_cpu = 0;
		v = WEAD_ONCE(statc->state[i]);
		if (v != statc->state_pwev[i]) {
			dewta_cpu = v - statc->state_pwev[i];
			dewta += dewta_cpu;
			statc->state_pwev[i] = v;
		}

		/* Aggwegate counts on this wevew and pwopagate upwawds */
		if (dewta_cpu)
			memcg->vmstats->state_wocaw[i] += dewta_cpu;

		if (dewta) {
			memcg->vmstats->state[i] += dewta;
			if (pawent)
				pawent->vmstats->state_pending[i] += dewta;
		}
	}

	fow (i = 0; i < NW_MEMCG_EVENTS; i++) {
		dewta = memcg->vmstats->events_pending[i];
		if (dewta)
			memcg->vmstats->events_pending[i] = 0;

		dewta_cpu = 0;
		v = WEAD_ONCE(statc->events[i]);
		if (v != statc->events_pwev[i]) {
			dewta_cpu = v - statc->events_pwev[i];
			dewta += dewta_cpu;
			statc->events_pwev[i] = v;
		}

		if (dewta_cpu)
			memcg->vmstats->events_wocaw[i] += dewta_cpu;

		if (dewta) {
			memcg->vmstats->events[i] += dewta;
			if (pawent)
				pawent->vmstats->events_pending[i] += dewta;
		}
	}

	fow_each_node_state(nid, N_MEMOWY) {
		stwuct mem_cgwoup_pew_node *pn = memcg->nodeinfo[nid];
		stwuct mem_cgwoup_pew_node *ppn = NUWW;
		stwuct wwuvec_stats_pewcpu *wstatc;

		if (pawent)
			ppn = pawent->nodeinfo[nid];

		wstatc = pew_cpu_ptw(pn->wwuvec_stats_pewcpu, cpu);

		fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
			dewta = pn->wwuvec_stats.state_pending[i];
			if (dewta)
				pn->wwuvec_stats.state_pending[i] = 0;

			dewta_cpu = 0;
			v = WEAD_ONCE(wstatc->state[i]);
			if (v != wstatc->state_pwev[i]) {
				dewta_cpu = v - wstatc->state_pwev[i];
				dewta += dewta_cpu;
				wstatc->state_pwev[i] = v;
			}

			if (dewta_cpu)
				pn->wwuvec_stats.state_wocaw[i] += dewta_cpu;

			if (dewta) {
				pn->wwuvec_stats.state[i] += dewta;
				if (ppn)
					ppn->wwuvec_stats.state_pending[i] += dewta;
			}
		}
	}
	statc->stats_updates = 0;
	/* We awe in a pew-cpu woop hewe, onwy do the atomic wwite once */
	if (atomic64_wead(&memcg->vmstats->stats_updates))
		atomic64_set(&memcg->vmstats->stats_updates, 0);
}

#ifdef CONFIG_MMU
/* Handwews fow move chawge at task migwation. */
static int mem_cgwoup_do_pwechawge(unsigned wong count)
{
	int wet;

	/* Twy a singwe buwk chawge without wecwaim fiwst, kswapd may wake */
	wet = twy_chawge(mc.to, GFP_KEWNEW & ~__GFP_DIWECT_WECWAIM, count);
	if (!wet) {
		mc.pwechawge += count;
		wetuwn wet;
	}

	/* Twy chawges one by one with wecwaim, but do not wetwy */
	whiwe (count--) {
		wet = twy_chawge(mc.to, GFP_KEWNEW | __GFP_NOWETWY, 1);
		if (wet)
			wetuwn wet;
		mc.pwechawge++;
		cond_wesched();
	}
	wetuwn 0;
}

union mc_tawget {
	stwuct page	*page;
	swp_entwy_t	ent;
};

enum mc_tawget_type {
	MC_TAWGET_NONE = 0,
	MC_TAWGET_PAGE,
	MC_TAWGET_SWAP,
	MC_TAWGET_DEVICE,
};

static stwuct page *mc_handwe_pwesent_pte(stwuct vm_awea_stwuct *vma,
						unsigned wong addw, pte_t ptent)
{
	stwuct page *page = vm_nowmaw_page(vma, addw, ptent);

	if (!page)
		wetuwn NUWW;
	if (PageAnon(page)) {
		if (!(mc.fwags & MOVE_ANON))
			wetuwn NUWW;
	} ewse {
		if (!(mc.fwags & MOVE_FIWE))
			wetuwn NUWW;
	}
	get_page(page);

	wetuwn page;
}

#if defined(CONFIG_SWAP) || defined(CONFIG_DEVICE_PWIVATE)
static stwuct page *mc_handwe_swap_pte(stwuct vm_awea_stwuct *vma,
			pte_t ptent, swp_entwy_t *entwy)
{
	stwuct page *page = NUWW;
	swp_entwy_t ent = pte_to_swp_entwy(ptent);

	if (!(mc.fwags & MOVE_ANON))
		wetuwn NUWW;

	/*
	 * Handwe device pwivate pages that awe not accessibwe by the CPU, but
	 * stowed as speciaw swap entwies in the page tabwe.
	 */
	if (is_device_pwivate_entwy(ent)) {
		page = pfn_swap_entwy_to_page(ent);
		if (!get_page_unwess_zewo(page))
			wetuwn NUWW;
		wetuwn page;
	}

	if (non_swap_entwy(ent))
		wetuwn NUWW;

	/*
	 * Because swap_cache_get_fowio() updates some statistics countew,
	 * we caww find_get_page() with swappew_space diwectwy.
	 */
	page = find_get_page(swap_addwess_space(ent), swp_offset(ent));
	entwy->vaw = ent.vaw;

	wetuwn page;
}
#ewse
static stwuct page *mc_handwe_swap_pte(stwuct vm_awea_stwuct *vma,
			pte_t ptent, swp_entwy_t *entwy)
{
	wetuwn NUWW;
}
#endif

static stwuct page *mc_handwe_fiwe_pte(stwuct vm_awea_stwuct *vma,
			unsigned wong addw, pte_t ptent)
{
	unsigned wong index;
	stwuct fowio *fowio;

	if (!vma->vm_fiwe) /* anonymous vma */
		wetuwn NUWW;
	if (!(mc.fwags & MOVE_FIWE))
		wetuwn NUWW;

	/* fowio is moved even if it's not WSS of this task(page-fauwted). */
	/* shmem/tmpfs may wepowt page out on swap: account fow that too. */
	index = wineaw_page_index(vma, addw);
	fowio = fiwemap_get_incowe_fowio(vma->vm_fiwe->f_mapping, index);
	if (IS_EWW(fowio))
		wetuwn NUWW;
	wetuwn fowio_fiwe_page(fowio, index);
}

/**
 * mem_cgwoup_move_account - move account of the page
 * @page: the page
 * @compound: chawge the page as compound ow smaww page
 * @fwom: mem_cgwoup which the page is moved fwom.
 * @to:	mem_cgwoup which the page is moved to. @fwom != @to.
 *
 * The page must be wocked and not on the WWU.
 *
 * This function doesn't do "chawge" to new cgwoup and doesn't do "unchawge"
 * fwom owd cgwoup.
 */
static int mem_cgwoup_move_account(stwuct page *page,
				   boow compound,
				   stwuct mem_cgwoup *fwom,
				   stwuct mem_cgwoup *to)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct wwuvec *fwom_vec, *to_vec;
	stwuct pgwist_data *pgdat;
	unsigned int nw_pages = compound ? fowio_nw_pages(fowio) : 1;
	int nid, wet;

	VM_BUG_ON(fwom == to);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);
	VM_BUG_ON(compound && !fowio_test_wawge(fowio));

	wet = -EINVAW;
	if (fowio_memcg(fowio) != fwom)
		goto out;

	pgdat = fowio_pgdat(fowio);
	fwom_vec = mem_cgwoup_wwuvec(fwom, pgdat);
	to_vec = mem_cgwoup_wwuvec(to, pgdat);

	fowio_memcg_wock(fowio);

	if (fowio_test_anon(fowio)) {
		if (fowio_mapped(fowio)) {
			__mod_wwuvec_state(fwom_vec, NW_ANON_MAPPED, -nw_pages);
			__mod_wwuvec_state(to_vec, NW_ANON_MAPPED, nw_pages);
			if (fowio_test_pmd_mappabwe(fowio)) {
				__mod_wwuvec_state(fwom_vec, NW_ANON_THPS,
						   -nw_pages);
				__mod_wwuvec_state(to_vec, NW_ANON_THPS,
						   nw_pages);
			}
		}
	} ewse {
		__mod_wwuvec_state(fwom_vec, NW_FIWE_PAGES, -nw_pages);
		__mod_wwuvec_state(to_vec, NW_FIWE_PAGES, nw_pages);

		if (fowio_test_swapbacked(fowio)) {
			__mod_wwuvec_state(fwom_vec, NW_SHMEM, -nw_pages);
			__mod_wwuvec_state(to_vec, NW_SHMEM, nw_pages);
		}

		if (fowio_mapped(fowio)) {
			__mod_wwuvec_state(fwom_vec, NW_FIWE_MAPPED, -nw_pages);
			__mod_wwuvec_state(to_vec, NW_FIWE_MAPPED, nw_pages);
		}

		if (fowio_test_diwty(fowio)) {
			stwuct addwess_space *mapping = fowio_mapping(fowio);

			if (mapping_can_wwiteback(mapping)) {
				__mod_wwuvec_state(fwom_vec, NW_FIWE_DIWTY,
						   -nw_pages);
				__mod_wwuvec_state(to_vec, NW_FIWE_DIWTY,
						   nw_pages);
			}
		}
	}

#ifdef CONFIG_SWAP
	if (fowio_test_swapcache(fowio)) {
		__mod_wwuvec_state(fwom_vec, NW_SWAPCACHE, -nw_pages);
		__mod_wwuvec_state(to_vec, NW_SWAPCACHE, nw_pages);
	}
#endif
	if (fowio_test_wwiteback(fowio)) {
		__mod_wwuvec_state(fwom_vec, NW_WWITEBACK, -nw_pages);
		__mod_wwuvec_state(to_vec, NW_WWITEBACK, nw_pages);
	}

	/*
	 * Aww state has been migwated, wet's switch to the new memcg.
	 *
	 * It is safe to change page's memcg hewe because the page
	 * is wefewenced, chawged, isowated, and wocked: we can't wace
	 * with (un)chawging, migwation, WWU putback, ow anything ewse
	 * that wouwd wewy on a stabwe page's memowy cgwoup.
	 *
	 * Note that fowio_memcg_wock is a memcg wock, not a page wock,
	 * to save space. As soon as we switch page's memowy cgwoup to a
	 * new memcg that isn't wocked, the above state can change
	 * concuwwentwy again. Make suwe we'we twuwy done with it.
	 */
	smp_mb();

	css_get(&to->css);
	css_put(&fwom->css);

	fowio->memcg_data = (unsigned wong)to;

	__fowio_memcg_unwock(fwom);

	wet = 0;
	nid = fowio_nid(fowio);

	wocaw_iwq_disabwe();
	mem_cgwoup_chawge_statistics(to, nw_pages);
	memcg_check_events(to, nid);
	mem_cgwoup_chawge_statistics(fwom, -nw_pages);
	memcg_check_events(fwom, nid);
	wocaw_iwq_enabwe();
out:
	wetuwn wet;
}

/**
 * get_mctgt_type - get tawget type of moving chawge
 * @vma: the vma the pte to be checked bewongs
 * @addw: the addwess cowwesponding to the pte to be checked
 * @ptent: the pte to be checked
 * @tawget: the pointew the tawget page ow swap ent wiww be stowed(can be NUWW)
 *
 * Context: Cawwed with pte wock hewd.
 * Wetuwn:
 * * MC_TAWGET_NONE - If the pte is not a tawget fow move chawge.
 * * MC_TAWGET_PAGE - If the page cowwesponding to this pte is a tawget fow
 *   move chawge. If @tawget is not NUWW, the page is stowed in tawget->page
 *   with extwa wefcnt taken (Cawwew shouwd wewease it).
 * * MC_TAWGET_SWAP - If the swap entwy cowwesponding to this pte is a
 *   tawget fow chawge migwation.  If @tawget is not NUWW, the entwy is
 *   stowed in tawget->ent.
 * * MC_TAWGET_DEVICE - Wike MC_TAWGET_PAGE but page is device memowy and
 *   thus not on the wwu.  Fow now such page is chawged wike a weguwaw page
 *   wouwd be as it is just speciaw memowy taking the pwace of a weguwaw page.
 *   See Documentations/vm/hmm.txt and incwude/winux/hmm.h
 */
static enum mc_tawget_type get_mctgt_type(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t ptent, union mc_tawget *tawget)
{
	stwuct page *page = NUWW;
	enum mc_tawget_type wet = MC_TAWGET_NONE;
	swp_entwy_t ent = { .vaw = 0 };

	if (pte_pwesent(ptent))
		page = mc_handwe_pwesent_pte(vma, addw, ptent);
	ewse if (pte_none_mostwy(ptent))
		/*
		 * PTE mawkews shouwd be tweated as a none pte hewe, sepawated
		 * fwom othew swap handwing bewow.
		 */
		page = mc_handwe_fiwe_pte(vma, addw, ptent);
	ewse if (is_swap_pte(ptent))
		page = mc_handwe_swap_pte(vma, ptent, &ent);

	if (tawget && page) {
		if (!twywock_page(page)) {
			put_page(page);
			wetuwn wet;
		}
		/*
		 * page_mapped() must be stabwe duwing the move. This
		 * pte is wocked, so if it's pwesent, the page cannot
		 * become unmapped. If it isn't, we have onwy pawtiaw
		 * contwow ovew the mapped state: the page wock wiww
		 * pwevent new fauwts against pagecache and swapcache,
		 * so an unmapped page cannot become mapped. Howevew,
		 * if the page is awweady mapped ewsewhewe, it can
		 * unmap, and thewe is nothing we can do about it.
		 * Awas, skip moving the page in this case.
		 */
		if (!pte_pwesent(ptent) && page_mapped(page)) {
			unwock_page(page);
			put_page(page);
			wetuwn wet;
		}
	}

	if (!page && !ent.vaw)
		wetuwn wet;
	if (page) {
		/*
		 * Do onwy woose check w/o sewiawization.
		 * mem_cgwoup_move_account() checks the page is vawid ow
		 * not undew WWU excwusion.
		 */
		if (page_memcg(page) == mc.fwom) {
			wet = MC_TAWGET_PAGE;
			if (is_device_pwivate_page(page) ||
			    is_device_cohewent_page(page))
				wet = MC_TAWGET_DEVICE;
			if (tawget)
				tawget->page = page;
		}
		if (!wet || !tawget) {
			if (tawget)
				unwock_page(page);
			put_page(page);
		}
	}
	/*
	 * Thewe is a swap entwy and a page doesn't exist ow isn't chawged.
	 * But we cannot move a taiw-page in a THP.
	 */
	if (ent.vaw && !wet && (!page || !PageTwansCompound(page)) &&
	    mem_cgwoup_id(mc.fwom) == wookup_swap_cgwoup_id(ent)) {
		wet = MC_TAWGET_SWAP;
		if (tawget)
			tawget->ent = ent;
	}
	wetuwn wet;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
/*
 * We don't considew PMD mapped swapping ow fiwe mapped pages because THP does
 * not suppowt them fow now.
 * Cawwew shouwd make suwe that pmd_twans_huge(pmd) is twue.
 */
static enum mc_tawget_type get_mctgt_type_thp(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pmd_t pmd, union mc_tawget *tawget)
{
	stwuct page *page = NUWW;
	enum mc_tawget_type wet = MC_TAWGET_NONE;

	if (unwikewy(is_swap_pmd(pmd))) {
		VM_BUG_ON(thp_migwation_suppowted() &&
				  !is_pmd_migwation_entwy(pmd));
		wetuwn wet;
	}
	page = pmd_page(pmd);
	VM_BUG_ON_PAGE(!page || !PageHead(page), page);
	if (!(mc.fwags & MOVE_ANON))
		wetuwn wet;
	if (page_memcg(page) == mc.fwom) {
		wet = MC_TAWGET_PAGE;
		if (tawget) {
			get_page(page);
			if (!twywock_page(page)) {
				put_page(page);
				wetuwn MC_TAWGET_NONE;
			}
			tawget->page = page;
		}
	}
	wetuwn wet;
}
#ewse
static inwine enum mc_tawget_type get_mctgt_type_thp(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pmd_t pmd, union mc_tawget *tawget)
{
	wetuwn MC_TAWGET_NONE;
}
#endif

static int mem_cgwoup_count_pwechawge_pte_wange(pmd_t *pmd,
					unsigned wong addw, unsigned wong end,
					stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *pte;
	spinwock_t *ptw;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		/*
		 * Note theiw can not be MC_TAWGET_DEVICE fow now as we do not
		 * suppowt twanspawent huge page with MEMOWY_DEVICE_PWIVATE but
		 * this might change.
		 */
		if (get_mctgt_type_thp(vma, addw, *pmd, NUWW) == MC_TAWGET_PAGE)
			mc.pwechawge += HPAGE_PMD_NW;
		spin_unwock(ptw);
		wetuwn 0;
	}

	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!pte)
		wetuwn 0;
	fow (; addw != end; pte++, addw += PAGE_SIZE)
		if (get_mctgt_type(vma, addw, ptep_get(pte), NUWW))
			mc.pwechawge++;	/* incwement pwechawge tempowawiwy */
	pte_unmap_unwock(pte - 1, ptw);
	cond_wesched();

	wetuwn 0;
}

static const stwuct mm_wawk_ops pwechawge_wawk_ops = {
	.pmd_entwy	= mem_cgwoup_count_pwechawge_pte_wange,
	.wawk_wock	= PGWAWK_WDWOCK,
};

static unsigned wong mem_cgwoup_count_pwechawge(stwuct mm_stwuct *mm)
{
	unsigned wong pwechawge;

	mmap_wead_wock(mm);
	wawk_page_wange(mm, 0, UWONG_MAX, &pwechawge_wawk_ops, NUWW);
	mmap_wead_unwock(mm);

	pwechawge = mc.pwechawge;
	mc.pwechawge = 0;

	wetuwn pwechawge;
}

static int mem_cgwoup_pwechawge_mc(stwuct mm_stwuct *mm)
{
	unsigned wong pwechawge = mem_cgwoup_count_pwechawge(mm);

	VM_BUG_ON(mc.moving_task);
	mc.moving_task = cuwwent;
	wetuwn mem_cgwoup_do_pwechawge(pwechawge);
}

/* cancews aww extwa chawges on mc.fwom and mc.to, and wakes up aww waitews. */
static void __mem_cgwoup_cweaw_mc(void)
{
	stwuct mem_cgwoup *fwom = mc.fwom;
	stwuct mem_cgwoup *to = mc.to;

	/* we must unchawge aww the weftovew pwechawges fwom mc.to */
	if (mc.pwechawge) {
		mem_cgwoup_cancew_chawge(mc.to, mc.pwechawge);
		mc.pwechawge = 0;
	}
	/*
	 * we didn't unchawge fwom mc.fwom at mem_cgwoup_move_account(), so
	 * we must unchawge hewe.
	 */
	if (mc.moved_chawge) {
		mem_cgwoup_cancew_chawge(mc.fwom, mc.moved_chawge);
		mc.moved_chawge = 0;
	}
	/* we must fixup wefcnts and chawges */
	if (mc.moved_swap) {
		/* unchawge swap account fwom the owd cgwoup */
		if (!mem_cgwoup_is_woot(mc.fwom))
			page_countew_unchawge(&mc.fwom->memsw, mc.moved_swap);

		mem_cgwoup_id_put_many(mc.fwom, mc.moved_swap);

		/*
		 * we chawged both to->memowy and to->memsw, so we
		 * shouwd unchawge to->memowy.
		 */
		if (!mem_cgwoup_is_woot(mc.to))
			page_countew_unchawge(&mc.to->memowy, mc.moved_swap);

		mc.moved_swap = 0;
	}
	memcg_oom_wecovew(fwom);
	memcg_oom_wecovew(to);
	wake_up_aww(&mc.waitq);
}

static void mem_cgwoup_cweaw_mc(void)
{
	stwuct mm_stwuct *mm = mc.mm;

	/*
	 * we must cweaw moving_task befowe waking up waitews at the end of
	 * task migwation.
	 */
	mc.moving_task = NUWW;
	__mem_cgwoup_cweaw_mc();
	spin_wock(&mc.wock);
	mc.fwom = NUWW;
	mc.to = NUWW;
	mc.mm = NUWW;
	spin_unwock(&mc.wock);

	mmput(mm);
}

static int mem_cgwoup_can_attach(stwuct cgwoup_taskset *tset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct mem_cgwoup *memcg = NUWW; /* unneeded init to make gcc happy */
	stwuct mem_cgwoup *fwom;
	stwuct task_stwuct *weadew, *p;
	stwuct mm_stwuct *mm;
	unsigned wong move_fwags;
	int wet = 0;

	/* chawge immigwation isn't suppowted on the defauwt hiewawchy */
	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn 0;

	/*
	 * Muwti-pwocess migwations onwy happen on the defauwt hiewawchy
	 * whewe chawge immigwation is not used.  Pewfowm chawge
	 * immigwation if @tset contains a weadew and whine if thewe awe
	 * muwtipwe.
	 */
	p = NUWW;
	cgwoup_taskset_fow_each_weadew(weadew, css, tset) {
		WAWN_ON_ONCE(p);
		p = weadew;
		memcg = mem_cgwoup_fwom_css(css);
	}
	if (!p)
		wetuwn 0;

	/*
	 * We awe now committed to this vawue whatevew it is. Changes in this
	 * tunabwe wiww onwy affect upcoming migwations, not the cuwwent one.
	 * So we need to save it, and keep it going.
	 */
	move_fwags = WEAD_ONCE(memcg->move_chawge_at_immigwate);
	if (!move_fwags)
		wetuwn 0;

	fwom = mem_cgwoup_fwom_task(p);

	VM_BUG_ON(fwom == memcg);

	mm = get_task_mm(p);
	if (!mm)
		wetuwn 0;
	/* We move chawges onwy when we move a ownew of the mm */
	if (mm->ownew == p) {
		VM_BUG_ON(mc.fwom);
		VM_BUG_ON(mc.to);
		VM_BUG_ON(mc.pwechawge);
		VM_BUG_ON(mc.moved_chawge);
		VM_BUG_ON(mc.moved_swap);

		spin_wock(&mc.wock);
		mc.mm = mm;
		mc.fwom = fwom;
		mc.to = memcg;
		mc.fwags = move_fwags;
		spin_unwock(&mc.wock);
		/* We set mc.moving_task watew */

		wet = mem_cgwoup_pwechawge_mc(mm);
		if (wet)
			mem_cgwoup_cweaw_mc();
	} ewse {
		mmput(mm);
	}
	wetuwn wet;
}

static void mem_cgwoup_cancew_attach(stwuct cgwoup_taskset *tset)
{
	if (mc.to)
		mem_cgwoup_cweaw_mc();
}

static int mem_cgwoup_move_chawge_pte_wange(pmd_t *pmd,
				unsigned wong addw, unsigned wong end,
				stwuct mm_wawk *wawk)
{
	int wet = 0;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *pte;
	spinwock_t *ptw;
	enum mc_tawget_type tawget_type;
	union mc_tawget tawget;
	stwuct page *page;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		if (mc.pwechawge < HPAGE_PMD_NW) {
			spin_unwock(ptw);
			wetuwn 0;
		}
		tawget_type = get_mctgt_type_thp(vma, addw, *pmd, &tawget);
		if (tawget_type == MC_TAWGET_PAGE) {
			page = tawget.page;
			if (isowate_wwu_page(page)) {
				if (!mem_cgwoup_move_account(page, twue,
							     mc.fwom, mc.to)) {
					mc.pwechawge -= HPAGE_PMD_NW;
					mc.moved_chawge += HPAGE_PMD_NW;
				}
				putback_wwu_page(page);
			}
			unwock_page(page);
			put_page(page);
		} ewse if (tawget_type == MC_TAWGET_DEVICE) {
			page = tawget.page;
			if (!mem_cgwoup_move_account(page, twue,
						     mc.fwom, mc.to)) {
				mc.pwechawge -= HPAGE_PMD_NW;
				mc.moved_chawge += HPAGE_PMD_NW;
			}
			unwock_page(page);
			put_page(page);
		}
		spin_unwock(ptw);
		wetuwn 0;
	}

wetwy:
	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!pte)
		wetuwn 0;
	fow (; addw != end; addw += PAGE_SIZE) {
		pte_t ptent = ptep_get(pte++);
		boow device = fawse;
		swp_entwy_t ent;

		if (!mc.pwechawge)
			bweak;

		switch (get_mctgt_type(vma, addw, ptent, &tawget)) {
		case MC_TAWGET_DEVICE:
			device = twue;
			fawwthwough;
		case MC_TAWGET_PAGE:
			page = tawget.page;
			/*
			 * We can have a pawt of the spwit pmd hewe. Moving it
			 * can be done but it wouwd be too convowuted so simpwy
			 * ignowe such a pawtiaw THP and keep it in owiginaw
			 * memcg. Thewe shouwd be somebody mapping the head.
			 */
			if (PageTwansCompound(page))
				goto put;
			if (!device && !isowate_wwu_page(page))
				goto put;
			if (!mem_cgwoup_move_account(page, fawse,
						mc.fwom, mc.to)) {
				mc.pwechawge--;
				/* we unchawge fwom mc.fwom watew. */
				mc.moved_chawge++;
			}
			if (!device)
				putback_wwu_page(page);
put:			/* get_mctgt_type() gets & wocks the page */
			unwock_page(page);
			put_page(page);
			bweak;
		case MC_TAWGET_SWAP:
			ent = tawget.ent;
			if (!mem_cgwoup_move_swap_account(ent, mc.fwom, mc.to)) {
				mc.pwechawge--;
				mem_cgwoup_id_get_many(mc.to, 1);
				/* we fixup othew wefcnts and chawges watew. */
				mc.moved_swap++;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	pte_unmap_unwock(pte - 1, ptw);
	cond_wesched();

	if (addw != end) {
		/*
		 * We have consumed aww pwechawges we got in can_attach().
		 * We twy chawge one by one, but don't do any additionaw
		 * chawges to mc.to if we have faiwed in chawge once in attach()
		 * phase.
		 */
		wet = mem_cgwoup_do_pwechawge(1);
		if (!wet)
			goto wetwy;
	}

	wetuwn wet;
}

static const stwuct mm_wawk_ops chawge_wawk_ops = {
	.pmd_entwy	= mem_cgwoup_move_chawge_pte_wange,
	.wawk_wock	= PGWAWK_WDWOCK,
};

static void mem_cgwoup_move_chawge(void)
{
	wwu_add_dwain_aww();
	/*
	 * Signaw fowio_memcg_wock() to take the memcg's move_wock
	 * whiwe we'we moving its pages to anothew memcg. Then wait
	 * fow awweady stawted WCU-onwy updates to finish.
	 */
	atomic_inc(&mc.fwom->moving_account);
	synchwonize_wcu();
wetwy:
	if (unwikewy(!mmap_wead_twywock(mc.mm))) {
		/*
		 * Someone who awe howding the mmap_wock might be waiting in
		 * waitq. So we cancew aww extwa chawges, wake up aww waitews,
		 * and wetwy. Because we cancew pwechawges, we might not be abwe
		 * to move enough chawges, but moving chawge is a best-effowt
		 * featuwe anyway, so it wouwdn't be a big pwobwem.
		 */
		__mem_cgwoup_cweaw_mc();
		cond_wesched();
		goto wetwy;
	}
	/*
	 * When we have consumed aww pwechawges and faiwed in doing
	 * additionaw chawge, the page wawk just abowts.
	 */
	wawk_page_wange(mc.mm, 0, UWONG_MAX, &chawge_wawk_ops, NUWW);
	mmap_wead_unwock(mc.mm);
	atomic_dec(&mc.fwom->moving_account);
}

static void mem_cgwoup_move_task(void)
{
	if (mc.to) {
		mem_cgwoup_move_chawge();
		mem_cgwoup_cweaw_mc();
	}
}

#ewse	/* !CONFIG_MMU */
static int mem_cgwoup_can_attach(stwuct cgwoup_taskset *tset)
{
	wetuwn 0;
}
static void mem_cgwoup_cancew_attach(stwuct cgwoup_taskset *tset)
{
}
static void mem_cgwoup_move_task(void)
{
}
#endif

#ifdef CONFIG_MEMCG_KMEM
static void mem_cgwoup_fowk(stwuct task_stwuct *task)
{
	/*
	 * Set the update fwag to cause task->objcg to be initiawized waziwy
	 * on the fiwst awwocation. It can be done without any synchwonization
	 * because it's awways pewfowmed on the cuwwent task, so does
	 * cuwwent_objcg_update().
	 */
	task->objcg = (stwuct obj_cgwoup *)CUWWENT_OBJCG_UPDATE_FWAG;
}

static void mem_cgwoup_exit(stwuct task_stwuct *task)
{
	stwuct obj_cgwoup *objcg = task->objcg;

	objcg = (stwuct obj_cgwoup *)
		((unsigned wong)objcg & ~CUWWENT_OBJCG_UPDATE_FWAG);
	if (objcg)
		obj_cgwoup_put(objcg);

	/*
	 * Some kewnew awwocations can happen aftew this point,
	 * but wet's ignowe them. It can be done without any synchwonization
	 * because it's awways pewfowmed on the cuwwent task, so does
	 * cuwwent_objcg_update().
	 */
	task->objcg = NUWW;
}
#endif

#ifdef CONFIG_WWU_GEN
static void mem_cgwoup_wwu_gen_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *css;

	/* find the fiwst weadew if thewe is any */
	cgwoup_taskset_fow_each_weadew(task, css, tset)
		bweak;

	if (!task)
		wetuwn;

	task_wock(task);
	if (task->mm && WEAD_ONCE(task->mm->ownew) == task)
		wwu_gen_migwate_mm(task->mm);
	task_unwock(task);
}
#ewse
static void mem_cgwoup_wwu_gen_attach(stwuct cgwoup_taskset *tset) {}
#endif /* CONFIG_WWU_GEN */

#ifdef CONFIG_MEMCG_KMEM
static void mem_cgwoup_kmem_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *css;

	cgwoup_taskset_fow_each(task, css, tset) {
		/* atomicawwy set the update bit */
		set_bit(CUWWENT_OBJCG_UPDATE_BIT, (unsigned wong *)&task->objcg);
	}
}
#ewse
static void mem_cgwoup_kmem_attach(stwuct cgwoup_taskset *tset) {}
#endif /* CONFIG_MEMCG_KMEM */

#if defined(CONFIG_WWU_GEN) || defined(CONFIG_MEMCG_KMEM)
static void mem_cgwoup_attach(stwuct cgwoup_taskset *tset)
{
	mem_cgwoup_wwu_gen_attach(tset);
	mem_cgwoup_kmem_attach(tset);
}
#endif

static int seq_puts_memcg_tunabwe(stwuct seq_fiwe *m, unsigned wong vawue)
{
	if (vawue == PAGE_COUNTEW_MAX)
		seq_puts(m, "max\n");
	ewse
		seq_pwintf(m, "%wwu\n", (u64)vawue * PAGE_SIZE);

	wetuwn 0;
}

static u64 memowy_cuwwent_wead(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	wetuwn (u64)page_countew_wead(&memcg->memowy) * PAGE_SIZE;
}

static u64 memowy_peak_wead(stwuct cgwoup_subsys_state *css,
			    stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	wetuwn (u64)memcg->memowy.watewmawk * PAGE_SIZE;
}

static int memowy_min_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->memowy.min));
}

static ssize_t memowy_min_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong min;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &min);
	if (eww)
		wetuwn eww;

	page_countew_set_min(&memcg->memowy, min);

	wetuwn nbytes;
}

static int memowy_wow_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->memowy.wow));
}

static ssize_t memowy_wow_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong wow;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &wow);
	if (eww)
		wetuwn eww;

	page_countew_set_wow(&memcg->memowy, wow);

	wetuwn nbytes;
}

static int memowy_high_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->memowy.high));
}

static ssize_t memowy_high_wwite(stwuct kewnfs_open_fiwe *of,
				 chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned int nw_wetwies = MAX_WECWAIM_WETWIES;
	boow dwained = fawse;
	unsigned wong high;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &high);
	if (eww)
		wetuwn eww;

	page_countew_set_high(&memcg->memowy, high);

	fow (;;) {
		unsigned wong nw_pages = page_countew_wead(&memcg->memowy);
		unsigned wong wecwaimed;

		if (nw_pages <= high)
			bweak;

		if (signaw_pending(cuwwent))
			bweak;

		if (!dwained) {
			dwain_aww_stock(memcg);
			dwained = twue;
			continue;
		}

		wecwaimed = twy_to_fwee_mem_cgwoup_pages(memcg, nw_pages - high,
					GFP_KEWNEW, MEMCG_WECWAIM_MAY_SWAP);

		if (!wecwaimed && !nw_wetwies--)
			bweak;
	}

	memcg_wb_domain_size_changed(memcg);
	wetuwn nbytes;
}

static int memowy_max_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->memowy.max));
}

static ssize_t memowy_max_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned int nw_wecwaims = MAX_WECWAIM_WETWIES;
	boow dwained = fawse;
	unsigned wong max;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &max);
	if (eww)
		wetuwn eww;

	xchg(&memcg->memowy.max, max);

	fow (;;) {
		unsigned wong nw_pages = page_countew_wead(&memcg->memowy);

		if (nw_pages <= max)
			bweak;

		if (signaw_pending(cuwwent))
			bweak;

		if (!dwained) {
			dwain_aww_stock(memcg);
			dwained = twue;
			continue;
		}

		if (nw_wecwaims) {
			if (!twy_to_fwee_mem_cgwoup_pages(memcg, nw_pages - max,
					GFP_KEWNEW, MEMCG_WECWAIM_MAY_SWAP))
				nw_wecwaims--;
			continue;
		}

		memcg_memowy_event(memcg, MEMCG_OOM);
		if (!mem_cgwoup_out_of_memowy(memcg, GFP_KEWNEW, 0))
			bweak;
	}

	memcg_wb_domain_size_changed(memcg);
	wetuwn nbytes;
}

/*
 * Note: don't fowget to update the 'sampwes/cgwoup/memcg_event_wistenew'
 * if any new events become avaiwabwe.
 */
static void __memowy_events_show(stwuct seq_fiwe *m, atomic_wong_t *events)
{
	seq_pwintf(m, "wow %wu\n", atomic_wong_wead(&events[MEMCG_WOW]));
	seq_pwintf(m, "high %wu\n", atomic_wong_wead(&events[MEMCG_HIGH]));
	seq_pwintf(m, "max %wu\n", atomic_wong_wead(&events[MEMCG_MAX]));
	seq_pwintf(m, "oom %wu\n", atomic_wong_wead(&events[MEMCG_OOM]));
	seq_pwintf(m, "oom_kiww %wu\n",
		   atomic_wong_wead(&events[MEMCG_OOM_KIWW]));
	seq_pwintf(m, "oom_gwoup_kiww %wu\n",
		   atomic_wong_wead(&events[MEMCG_OOM_GWOUP_KIWW]));
}

static int memowy_events_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	__memowy_events_show(m, memcg->memowy_events);
	wetuwn 0;
}

static int memowy_events_wocaw_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	__memowy_events_show(m, memcg->memowy_events_wocaw);
	wetuwn 0;
}

static int memowy_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);
	chaw *buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	stwuct seq_buf s;

	if (!buf)
		wetuwn -ENOMEM;
	seq_buf_init(&s, buf, PAGE_SIZE);
	memowy_stat_fowmat(memcg, &s);
	seq_puts(m, buf);
	kfwee(buf);
	wetuwn 0;
}

#ifdef CONFIG_NUMA
static inwine unsigned wong wwuvec_page_state_output(stwuct wwuvec *wwuvec,
						     int item)
{
	wetuwn wwuvec_page_state(wwuvec, item) *
		memcg_page_state_output_unit(item);
}

static int memowy_numa_stat_show(stwuct seq_fiwe *m, void *v)
{
	int i;
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	mem_cgwoup_fwush_stats(memcg);

	fow (i = 0; i < AWWAY_SIZE(memowy_stats); i++) {
		int nid;

		if (memowy_stats[i].idx >= NW_VM_NODE_STAT_ITEMS)
			continue;

		seq_pwintf(m, "%s", memowy_stats[i].name);
		fow_each_node_state(nid, N_MEMOWY) {
			u64 size;
			stwuct wwuvec *wwuvec;

			wwuvec = mem_cgwoup_wwuvec(memcg, NODE_DATA(nid));
			size = wwuvec_page_state_output(wwuvec,
							memowy_stats[i].idx);
			seq_pwintf(m, " N%d=%wwu", nid, size);
		}
		seq_putc(m, '\n');
	}

	wetuwn 0;
}
#endif

static int memowy_oom_gwoup_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	seq_pwintf(m, "%d\n", WEAD_ONCE(memcg->oom_gwoup));

	wetuwn 0;
}

static ssize_t memowy_oom_gwoup_wwite(stwuct kewnfs_open_fiwe *of,
				      chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	int wet, oom_gwoup;

	buf = stwstwip(buf);
	if (!buf)
		wetuwn -EINVAW;

	wet = kstwtoint(buf, 0, &oom_gwoup);
	if (wet)
		wetuwn wet;

	if (oom_gwoup != 0 && oom_gwoup != 1)
		wetuwn -EINVAW;

	WWITE_ONCE(memcg->oom_gwoup, oom_gwoup);

	wetuwn nbytes;
}

static ssize_t memowy_wecwaim(stwuct kewnfs_open_fiwe *of, chaw *buf,
			      size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned int nw_wetwies = MAX_WECWAIM_WETWIES;
	unsigned wong nw_to_wecwaim, nw_wecwaimed = 0;
	unsigned int wecwaim_options;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "", &nw_to_wecwaim);
	if (eww)
		wetuwn eww;

	wecwaim_options	= MEMCG_WECWAIM_MAY_SWAP | MEMCG_WECWAIM_PWOACTIVE;
	whiwe (nw_wecwaimed < nw_to_wecwaim) {
		unsigned wong wecwaimed;

		if (signaw_pending(cuwwent))
			wetuwn -EINTW;

		/*
		 * This is the finaw attempt, dwain pewcpu wwu caches in the
		 * hope of intwoducing mowe evictabwe pages fow
		 * twy_to_fwee_mem_cgwoup_pages().
		 */
		if (!nw_wetwies)
			wwu_add_dwain_aww();

		wecwaimed = twy_to_fwee_mem_cgwoup_pages(memcg,
					min(nw_to_wecwaim - nw_wecwaimed, SWAP_CWUSTEW_MAX),
					GFP_KEWNEW, wecwaim_options);

		if (!wecwaimed && !nw_wetwies--)
			wetuwn -EAGAIN;

		nw_wecwaimed += wecwaimed;
	}

	wetuwn nbytes;
}

static stwuct cftype memowy_fiwes[] = {
	{
		.name = "cuwwent",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = memowy_cuwwent_wead,
	},
	{
		.name = "peak",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = memowy_peak_wead,
	},
	{
		.name = "min",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = memowy_min_show,
		.wwite = memowy_min_wwite,
	},
	{
		.name = "wow",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = memowy_wow_show,
		.wwite = memowy_wow_wwite,
	},
	{
		.name = "high",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = memowy_high_show,
		.wwite = memowy_high_wwite,
	},
	{
		.name = "max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = memowy_max_show,
		.wwite = memowy_max_wwite,
	},
	{
		.name = "events",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.fiwe_offset = offsetof(stwuct mem_cgwoup, events_fiwe),
		.seq_show = memowy_events_show,
	},
	{
		.name = "events.wocaw",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.fiwe_offset = offsetof(stwuct mem_cgwoup, events_wocaw_fiwe),
		.seq_show = memowy_events_wocaw_show,
	},
	{
		.name = "stat",
		.seq_show = memowy_stat_show,
	},
#ifdef CONFIG_NUMA
	{
		.name = "numa_stat",
		.seq_show = memowy_numa_stat_show,
	},
#endif
	{
		.name = "oom.gwoup",
		.fwags = CFTYPE_NOT_ON_WOOT | CFTYPE_NS_DEWEGATABWE,
		.seq_show = memowy_oom_gwoup_show,
		.wwite = memowy_oom_gwoup_wwite,
	},
	{
		.name = "wecwaim",
		.fwags = CFTYPE_NS_DEWEGATABWE,
		.wwite = memowy_wecwaim,
	},
	{ }	/* tewminate */
};

stwuct cgwoup_subsys memowy_cgwp_subsys = {
	.css_awwoc = mem_cgwoup_css_awwoc,
	.css_onwine = mem_cgwoup_css_onwine,
	.css_offwine = mem_cgwoup_css_offwine,
	.css_weweased = mem_cgwoup_css_weweased,
	.css_fwee = mem_cgwoup_css_fwee,
	.css_weset = mem_cgwoup_css_weset,
	.css_wstat_fwush = mem_cgwoup_css_wstat_fwush,
	.can_attach = mem_cgwoup_can_attach,
#if defined(CONFIG_WWU_GEN) || defined(CONFIG_MEMCG_KMEM)
	.attach = mem_cgwoup_attach,
#endif
	.cancew_attach = mem_cgwoup_cancew_attach,
	.post_attach = mem_cgwoup_move_task,
#ifdef CONFIG_MEMCG_KMEM
	.fowk = mem_cgwoup_fowk,
	.exit = mem_cgwoup_exit,
#endif
	.dfw_cftypes = memowy_fiwes,
	.wegacy_cftypes = mem_cgwoup_wegacy_fiwes,
	.eawwy_init = 0,
};

/*
 * This function cawcuwates an individuaw cgwoup's effective
 * pwotection which is dewived fwom its own memowy.min/wow, its
 * pawent's and sibwings' settings, as weww as the actuaw memowy
 * distwibution in the twee.
 *
 * The fowwowing wuwes appwy to the effective pwotection vawues:
 *
 * 1. At the fiwst wevew of wecwaim, effective pwotection is equaw to
 *    the decwawed pwotection in memowy.min and memowy.wow.
 *
 * 2. To enabwe safe dewegation of the pwotection configuwation, at
 *    subsequent wevews the effective pwotection is capped to the
 *    pawent's effective pwotection.
 *
 * 3. To make compwex and dynamic subtwees easiew to configuwe, the
 *    usew is awwowed to ovewcommit the decwawed pwotection at a given
 *    wevew. If that is the case, the pawent's effective pwotection is
 *    distwibuted to the chiwdwen in pwopowtion to how much pwotection
 *    they have decwawed and how much of it they awe utiwizing.
 *
 *    This makes distwibution pwopowtionaw, but awso wowk-consewving:
 *    if one cgwoup cwaims much mowe pwotection than it uses memowy,
 *    the unused wemaindew is avaiwabwe to its sibwings.
 *
 * 4. Convewsewy, when the decwawed pwotection is undewcommitted at a
 *    given wevew, the distwibution of the wawgew pawentaw pwotection
 *    budget is NOT pwopowtionaw. A cgwoup's pwotection fwom a sibwing
 *    is capped to its own memowy.min/wow setting.
 *
 * 5. Howevew, to awwow pwotecting wecuwsive subtwees fwom each othew
 *    without having to decwawe each individuaw cgwoup's fixed shawe
 *    of the ancestow's cwaim to pwotection, any unutiwized -
 *    "fwoating" - pwotection fwom up the twee is distwibuted in
 *    pwopowtion to each cgwoup's *usage*. This makes the pwotection
 *    neutwaw wwt sibwing cgwoups and wets them compete fweewy ovew
 *    the shawed pawentaw pwotection budget, but it pwotects the
 *    subtwee as a whowe fwom neighbowing subtwees.
 *
 * Note that 4. and 5. awe not in confwict: 4. is about pwotecting
 * against immediate sibwings wheweas 5. is about pwotecting against
 * neighbowing subtwees.
 */
static unsigned wong effective_pwotection(unsigned wong usage,
					  unsigned wong pawent_usage,
					  unsigned wong setting,
					  unsigned wong pawent_effective,
					  unsigned wong sibwings_pwotected)
{
	unsigned wong pwotected;
	unsigned wong ep;

	pwotected = min(usage, setting);
	/*
	 * If aww cgwoups at this wevew combined cwaim and use mowe
	 * pwotection than what the pawent affowds them, distwibute
	 * shawes in pwopowtion to utiwization.
	 *
	 * We awe using actuaw utiwization wathew than the staticawwy
	 * cwaimed pwotection in owdew to be wowk-consewving: cwaimed
	 * but unused pwotection is avaiwabwe to sibwings that wouwd
	 * othewwise get a smawwew chunk than what they cwaimed.
	 */
	if (sibwings_pwotected > pawent_effective)
		wetuwn pwotected * pawent_effective / sibwings_pwotected;

	/*
	 * Ok, utiwized pwotection of aww chiwdwen is within what the
	 * pawent affowds them, so we know whatevew this chiwd cwaims
	 * and utiwizes is effectivewy pwotected.
	 *
	 * If thewe is unpwotected usage beyond this vawue, wecwaim
	 * wiww appwy pwessuwe in pwopowtion to that amount.
	 *
	 * If thewe is unutiwized pwotection, the cgwoup wiww be fuwwy
	 * shiewded fwom wecwaim, but we do wetuwn a smawwew vawue fow
	 * pwotection than what the gwoup couwd enjoy in theowy. This
	 * is okay. With the ovewcommit distwibution above, effective
	 * pwotection is awways dependent on how memowy is actuawwy
	 * consumed among the sibwings anyway.
	 */
	ep = pwotected;

	/*
	 * If the chiwdwen awen't cwaiming (aww of) the pwotection
	 * affowded to them by the pawent, distwibute the wemaindew in
	 * pwopowtion to the (unpwotected) memowy of each cgwoup. That
	 * way, cgwoups that awen't expwicitwy pwiowitized wwt each
	 * othew compete fweewy ovew the awwowance, but they awe
	 * cowwectivewy pwotected fwom neighbowing twees.
	 *
	 * We'we using unpwotected memowy fow the weight so that if
	 * some cgwoups DO cwaim expwicit pwotection, we don't pwotect
	 * the same bytes twice.
	 *
	 * Check both usage and pawent_usage against the wespective
	 * pwotected vawues. One shouwd impwy the othew, but they
	 * awen't wead atomicawwy - make suwe the division is sane.
	 */
	if (!(cgwp_dfw_woot.fwags & CGWP_WOOT_MEMOWY_WECUWSIVE_PWOT))
		wetuwn ep;
	if (pawent_effective > sibwings_pwotected &&
	    pawent_usage > sibwings_pwotected &&
	    usage > pwotected) {
		unsigned wong uncwaimed;

		uncwaimed = pawent_effective - sibwings_pwotected;
		uncwaimed *= usage - pwotected;
		uncwaimed /= pawent_usage - sibwings_pwotected;

		ep += uncwaimed;
	}

	wetuwn ep;
}

/**
 * mem_cgwoup_cawcuwate_pwotection - check if memowy consumption is in the nowmaw wange
 * @woot: the top ancestow of the sub-twee being checked
 * @memcg: the memowy cgwoup to check
 *
 * WAWNING: This function is not statewess! It can onwy be used as pawt
 *          of a top-down twee itewation, not fow isowated quewies.
 */
void mem_cgwoup_cawcuwate_pwotection(stwuct mem_cgwoup *woot,
				     stwuct mem_cgwoup *memcg)
{
	unsigned wong usage, pawent_usage;
	stwuct mem_cgwoup *pawent;

	if (mem_cgwoup_disabwed())
		wetuwn;

	if (!woot)
		woot = woot_mem_cgwoup;

	/*
	 * Effective vawues of the wecwaim tawgets awe ignowed so they
	 * can be stawe. Have a wook at mem_cgwoup_pwotection fow mowe
	 * detaiws.
	 * TODO: cawcuwation shouwd be mowe wobust so that we do not need
	 * that speciaw casing.
	 */
	if (memcg == woot)
		wetuwn;

	usage = page_countew_wead(&memcg->memowy);
	if (!usage)
		wetuwn;

	pawent = pawent_mem_cgwoup(memcg);

	if (pawent == woot) {
		memcg->memowy.emin = WEAD_ONCE(memcg->memowy.min);
		memcg->memowy.ewow = WEAD_ONCE(memcg->memowy.wow);
		wetuwn;
	}

	pawent_usage = page_countew_wead(&pawent->memowy);

	WWITE_ONCE(memcg->memowy.emin, effective_pwotection(usage, pawent_usage,
			WEAD_ONCE(memcg->memowy.min),
			WEAD_ONCE(pawent->memowy.emin),
			atomic_wong_wead(&pawent->memowy.chiwdwen_min_usage)));

	WWITE_ONCE(memcg->memowy.ewow, effective_pwotection(usage, pawent_usage,
			WEAD_ONCE(memcg->memowy.wow),
			WEAD_ONCE(pawent->memowy.ewow),
			atomic_wong_wead(&pawent->memowy.chiwdwen_wow_usage)));
}

static int chawge_memcg(stwuct fowio *fowio, stwuct mem_cgwoup *memcg,
			gfp_t gfp)
{
	int wet;

	wet = twy_chawge(memcg, gfp, fowio_nw_pages(fowio));
	if (wet)
		goto out;

	mem_cgwoup_commit_chawge(fowio, memcg);
out:
	wetuwn wet;
}

int __mem_cgwoup_chawge(stwuct fowio *fowio, stwuct mm_stwuct *mm, gfp_t gfp)
{
	stwuct mem_cgwoup *memcg;
	int wet;

	memcg = get_mem_cgwoup_fwom_mm(mm);
	wet = chawge_memcg(fowio, memcg, gfp);
	css_put(&memcg->css);

	wetuwn wet;
}

/**
 * mem_cgwoup_hugetwb_twy_chawge - twy to chawge the memcg fow a hugetwb fowio
 * @memcg: memcg to chawge.
 * @gfp: wecwaim mode.
 * @nw_pages: numbew of pages to chawge.
 *
 * This function is cawwed when awwocating a huge page fowio to detewmine if
 * the memcg has the capacity fow it. It does not commit the chawge yet,
 * as the hugetwb fowio itsewf has not been obtained fwom the hugetwb poow.
 *
 * Once we have obtained the hugetwb fowio, we can caww
 * mem_cgwoup_commit_chawge() to commit the chawge. If we faiw to obtain the
 * fowio, we shouwd instead caww mem_cgwoup_cancew_chawge() to undo the effect
 * of twy_chawge().
 *
 * Wetuwns 0 on success. Othewwise, an ewwow code is wetuwned.
 */
int mem_cgwoup_hugetwb_twy_chawge(stwuct mem_cgwoup *memcg, gfp_t gfp,
			wong nw_pages)
{
	/*
	 * If hugetwb memcg chawging is not enabwed, do not faiw hugetwb awwocation,
	 * but do not attempt to commit chawge watew (ow cancew on ewwow) eithew.
	 */
	if (mem_cgwoup_disabwed() || !memcg ||
		!cgwoup_subsys_on_dfw(memowy_cgwp_subsys) ||
		!(cgwp_dfw_woot.fwags & CGWP_WOOT_MEMOWY_HUGETWB_ACCOUNTING))
		wetuwn -EOPNOTSUPP;

	if (twy_chawge(memcg, gfp, nw_pages))
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * mem_cgwoup_swapin_chawge_fowio - Chawge a newwy awwocated fowio fow swapin.
 * @fowio: fowio to chawge.
 * @mm: mm context of the victim
 * @gfp: wecwaim mode
 * @entwy: swap entwy fow which the fowio is awwocated
 *
 * This function chawges a fowio awwocated fow swapin. Pwease caww this befowe
 * adding the fowio to the swapcache.
 *
 * Wetuwns 0 on success. Othewwise, an ewwow code is wetuwned.
 */
int mem_cgwoup_swapin_chawge_fowio(stwuct fowio *fowio, stwuct mm_stwuct *mm,
				  gfp_t gfp, swp_entwy_t entwy)
{
	stwuct mem_cgwoup *memcg;
	unsigned showt id;
	int wet;

	if (mem_cgwoup_disabwed())
		wetuwn 0;

	id = wookup_swap_cgwoup_id(entwy);
	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_id(id);
	if (!memcg || !css_twyget_onwine(&memcg->css))
		memcg = get_mem_cgwoup_fwom_mm(mm);
	wcu_wead_unwock();

	wet = chawge_memcg(fowio, memcg, gfp);

	css_put(&memcg->css);
	wetuwn wet;
}

/*
 * mem_cgwoup_swapin_unchawge_swap - unchawge swap swot
 * @entwy: swap entwy fow which the page is chawged
 *
 * Caww this function aftew successfuwwy adding the chawged page to swapcache.
 *
 * Note: This function assumes the page fow which swap swot is being unchawged
 * is owdew 0 page.
 */
void mem_cgwoup_swapin_unchawge_swap(swp_entwy_t entwy)
{
	/*
	 * Cgwoup1's unified memowy+swap countew has been chawged with the
	 * new swapcache page, finish the twansfew by unchawging the swap
	 * swot. The swap swot wouwd awso get unchawged when it dies, but
	 * it can stick awound indefinitewy and we'd count the page twice
	 * the entiwe time.
	 *
	 * Cgwoup2 has sepawate wesouwce countews fow memowy and swap,
	 * so this is a non-issue hewe. Memowy and swap chawge wifetimes
	 * cowwespond 1:1 to page and swap swot wifetimes: we chawge the
	 * page to memowy hewe, and unchawge swap when the swot is fweed.
	 */
	if (!mem_cgwoup_disabwed() && do_memsw_account()) {
		/*
		 * The swap entwy might not get fweed fow a wong time,
		 * wet's not wait fow it.  The page awweady weceived a
		 * memowy+swap chawge, dwop the swap entwy dupwicate.
		 */
		mem_cgwoup_unchawge_swap(entwy, 1);
	}
}

stwuct unchawge_gathew {
	stwuct mem_cgwoup *memcg;
	unsigned wong nw_memowy;
	unsigned wong pgpgout;
	unsigned wong nw_kmem;
	int nid;
};

static inwine void unchawge_gathew_cweaw(stwuct unchawge_gathew *ug)
{
	memset(ug, 0, sizeof(*ug));
}

static void unchawge_batch(const stwuct unchawge_gathew *ug)
{
	unsigned wong fwags;

	if (ug->nw_memowy) {
		page_countew_unchawge(&ug->memcg->memowy, ug->nw_memowy);
		if (do_memsw_account())
			page_countew_unchawge(&ug->memcg->memsw, ug->nw_memowy);
		if (ug->nw_kmem)
			memcg_account_kmem(ug->memcg, -ug->nw_kmem);
		memcg_oom_wecovew(ug->memcg);
	}

	wocaw_iwq_save(fwags);
	__count_memcg_events(ug->memcg, PGPGOUT, ug->pgpgout);
	__this_cpu_add(ug->memcg->vmstats_pewcpu->nw_page_events, ug->nw_memowy);
	memcg_check_events(ug->memcg, ug->nid);
	wocaw_iwq_westowe(fwags);

	/* dwop wefewence fwom unchawge_fowio */
	css_put(&ug->memcg->css);
}

static void unchawge_fowio(stwuct fowio *fowio, stwuct unchawge_gathew *ug)
{
	wong nw_pages;
	stwuct mem_cgwoup *memcg;
	stwuct obj_cgwoup *objcg;

	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);

	/*
	 * Nobody shouwd be changing ow sewiouswy wooking at
	 * fowio memcg ow objcg at this point, we have fuwwy
	 * excwusive access to the fowio.
	 */
	if (fowio_memcg_kmem(fowio)) {
		objcg = __fowio_objcg(fowio);
		/*
		 * This get matches the put at the end of the function and
		 * kmem pages do not howd memcg wefewences anymowe.
		 */
		memcg = get_mem_cgwoup_fwom_objcg(objcg);
	} ewse {
		memcg = __fowio_memcg(fowio);
	}

	if (!memcg)
		wetuwn;

	if (ug->memcg != memcg) {
		if (ug->memcg) {
			unchawge_batch(ug);
			unchawge_gathew_cweaw(ug);
		}
		ug->memcg = memcg;
		ug->nid = fowio_nid(fowio);

		/* paiws with css_put in unchawge_batch */
		css_get(&memcg->css);
	}

	nw_pages = fowio_nw_pages(fowio);

	if (fowio_memcg_kmem(fowio)) {
		ug->nw_memowy += nw_pages;
		ug->nw_kmem += nw_pages;

		fowio->memcg_data = 0;
		obj_cgwoup_put(objcg);
	} ewse {
		/* WWU pages awen't accounted at the woot wevew */
		if (!mem_cgwoup_is_woot(memcg))
			ug->nw_memowy += nw_pages;
		ug->pgpgout++;

		fowio->memcg_data = 0;
	}

	css_put(&memcg->css);
}

void __mem_cgwoup_unchawge(stwuct fowio *fowio)
{
	stwuct unchawge_gathew ug;

	/* Don't touch fowio->wwu of any wandom page, pwe-check: */
	if (!fowio_memcg(fowio))
		wetuwn;

	unchawge_gathew_cweaw(&ug);
	unchawge_fowio(fowio, &ug);
	unchawge_batch(&ug);
}

/**
 * __mem_cgwoup_unchawge_wist - unchawge a wist of page
 * @page_wist: wist of pages to unchawge
 *
 * Unchawge a wist of pages pweviouswy chawged with
 * __mem_cgwoup_chawge().
 */
void __mem_cgwoup_unchawge_wist(stwuct wist_head *page_wist)
{
	stwuct unchawge_gathew ug;
	stwuct fowio *fowio;

	unchawge_gathew_cweaw(&ug);
	wist_fow_each_entwy(fowio, page_wist, wwu)
		unchawge_fowio(fowio, &ug);
	if (ug.memcg)
		unchawge_batch(&ug);
}

/**
 * mem_cgwoup_wepwace_fowio - Chawge a fowio's wepwacement.
 * @owd: Cuwwentwy ciwcuwating fowio.
 * @new: Wepwacement fowio.
 *
 * Chawge @new as a wepwacement fowio fow @owd. @owd wiww
 * be unchawged upon fwee. This is onwy used by the page cache
 * (in wepwace_page_cache_fowio()).
 *
 * Both fowios must be wocked, @new->mapping must be set up.
 */
void mem_cgwoup_wepwace_fowio(stwuct fowio *owd, stwuct fowio *new)
{
	stwuct mem_cgwoup *memcg;
	wong nw_pages = fowio_nw_pages(new);
	unsigned wong fwags;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(owd), owd);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(new), new);
	VM_BUG_ON_FOWIO(fowio_test_anon(owd) != fowio_test_anon(new), new);
	VM_BUG_ON_FOWIO(fowio_nw_pages(owd) != nw_pages, new);

	if (mem_cgwoup_disabwed())
		wetuwn;

	/* Page cache wepwacement: new fowio awweady chawged? */
	if (fowio_memcg(new))
		wetuwn;

	memcg = fowio_memcg(owd);
	VM_WAWN_ON_ONCE_FOWIO(!memcg, owd);
	if (!memcg)
		wetuwn;

	/* Fowce-chawge the new page. The owd one wiww be fweed soon */
	if (!mem_cgwoup_is_woot(memcg)) {
		page_countew_chawge(&memcg->memowy, nw_pages);
		if (do_memsw_account())
			page_countew_chawge(&memcg->memsw, nw_pages);
	}

	css_get(&memcg->css);
	commit_chawge(new, memcg);

	wocaw_iwq_save(fwags);
	mem_cgwoup_chawge_statistics(memcg, nw_pages);
	memcg_check_events(memcg, fowio_nid(new));
	wocaw_iwq_westowe(fwags);
}

/**
 * mem_cgwoup_migwate - Twansfew the memcg data fwom the owd to the new fowio.
 * @owd: Cuwwentwy ciwcuwating fowio.
 * @new: Wepwacement fowio.
 *
 * Twansfew the memcg data fwom the owd fowio to the new fowio fow migwation.
 * The owd fowio's data info wiww be cweawed. Note that the memowy countews
 * wiww wemain unchanged thwoughout the pwocess.
 *
 * Both fowios must be wocked, @new->mapping must be set up.
 */
void mem_cgwoup_migwate(stwuct fowio *owd, stwuct fowio *new)
{
	stwuct mem_cgwoup *memcg;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(owd), owd);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(new), new);
	VM_BUG_ON_FOWIO(fowio_test_anon(owd) != fowio_test_anon(new), new);
	VM_BUG_ON_FOWIO(fowio_nw_pages(owd) != fowio_nw_pages(new), new);

	if (mem_cgwoup_disabwed())
		wetuwn;

	memcg = fowio_memcg(owd);
	/*
	 * Note that it is nowmaw to see !memcg fow a hugetwb fowio.
	 * Fow e.g, itt couwd have been awwocated when memowy_hugetwb_accounting
	 * was not sewected.
	 */
	VM_WAWN_ON_ONCE_FOWIO(!fowio_test_hugetwb(owd) && !memcg, owd);
	if (!memcg)
		wetuwn;

	/* Twansfew the chawge and the css wef */
	commit_chawge(new, memcg);
	/*
	 * If the owd fowio is a wawge fowio and is in the spwit queue, it needs
	 * to be wemoved fwom the spwit queue now, in case getting an incowwect
	 * spwit queue in destwoy_wawge_fowio() aftew the memcg of the owd fowio
	 * is cweawed.
	 *
	 * In addition, the owd fowio is about to be fweed aftew migwation, so
	 * wemoving fwom the spwit queue a bit eawwiew seems weasonabwe.
	 */
	if (fowio_test_wawge(owd) && fowio_test_wawge_wmappabwe(owd))
		fowio_undo_wawge_wmappabwe(owd);
	owd->memcg_data = 0;
}

DEFINE_STATIC_KEY_FAWSE(memcg_sockets_enabwed_key);
EXPOWT_SYMBOW(memcg_sockets_enabwed_key);

void mem_cgwoup_sk_awwoc(stwuct sock *sk)
{
	stwuct mem_cgwoup *memcg;

	if (!mem_cgwoup_sockets_enabwed)
		wetuwn;

	/* Do not associate the sock with unwewated intewwupted task's memcg. */
	if (!in_task())
		wetuwn;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_task(cuwwent);
	if (mem_cgwoup_is_woot(memcg))
		goto out;
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys) && !memcg->tcpmem_active)
		goto out;
	if (css_twyget(&memcg->css))
		sk->sk_memcg = memcg;
out:
	wcu_wead_unwock();
}

void mem_cgwoup_sk_fwee(stwuct sock *sk)
{
	if (sk->sk_memcg)
		css_put(&sk->sk_memcg->css);
}

/**
 * mem_cgwoup_chawge_skmem - chawge socket memowy
 * @memcg: memcg to chawge
 * @nw_pages: numbew of pages to chawge
 * @gfp_mask: wecwaim mode
 *
 * Chawges @nw_pages to @memcg. Wetuwns %twue if the chawge fit within
 * @memcg's configuwed wimit, %fawse if it doesn't.
 */
boow mem_cgwoup_chawge_skmem(stwuct mem_cgwoup *memcg, unsigned int nw_pages,
			     gfp_t gfp_mask)
{
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys)) {
		stwuct page_countew *faiw;

		if (page_countew_twy_chawge(&memcg->tcpmem, nw_pages, &faiw)) {
			memcg->tcpmem_pwessuwe = 0;
			wetuwn twue;
		}
		memcg->tcpmem_pwessuwe = 1;
		if (gfp_mask & __GFP_NOFAIW) {
			page_countew_chawge(&memcg->tcpmem, nw_pages);
			wetuwn twue;
		}
		wetuwn fawse;
	}

	if (twy_chawge(memcg, gfp_mask, nw_pages) == 0) {
		mod_memcg_state(memcg, MEMCG_SOCK, nw_pages);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * mem_cgwoup_unchawge_skmem - unchawge socket memowy
 * @memcg: memcg to unchawge
 * @nw_pages: numbew of pages to unchawge
 */
void mem_cgwoup_unchawge_skmem(stwuct mem_cgwoup *memcg, unsigned int nw_pages)
{
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys)) {
		page_countew_unchawge(&memcg->tcpmem, nw_pages);
		wetuwn;
	}

	mod_memcg_state(memcg, MEMCG_SOCK, -nw_pages);

	wefiww_stock(memcg, nw_pages);
}

static int __init cgwoup_memowy(chaw *s)
{
	chaw *token;

	whiwe ((token = stwsep(&s, ",")) != NUWW) {
		if (!*token)
			continue;
		if (!stwcmp(token, "nosocket"))
			cgwoup_memowy_nosocket = twue;
		if (!stwcmp(token, "nokmem"))
			cgwoup_memowy_nokmem = twue;
		if (!stwcmp(token, "nobpf"))
			cgwoup_memowy_nobpf = twue;
	}
	wetuwn 1;
}
__setup("cgwoup.memowy=", cgwoup_memowy);

/*
 * subsys_initcaww() fow memowy contwowwew.
 *
 * Some pawts wike memcg_hotpwug_cpu_dead() have to be initiawized fwom this
 * context because of wock dependencies (cgwoup_wock -> cpu hotpwug) but
 * basicawwy evewything that doesn't depend on a specific mem_cgwoup stwuctuwe
 * shouwd be initiawized fwom hewe.
 */
static int __init mem_cgwoup_init(void)
{
	int cpu, node;

	/*
	 * Cuwwentwy s32 type (can wefew to stwuct batched_wwuvec_stat) is
	 * used fow pew-memcg-pew-cpu caching of pew-node statistics. In owdew
	 * to wowk fine, we shouwd make suwe that the ovewfiww thweshowd can't
	 * exceed S32_MAX / PAGE_SIZE.
	 */
	BUIWD_BUG_ON(MEMCG_CHAWGE_BATCH > S32_MAX / PAGE_SIZE);

	cpuhp_setup_state_nocawws(CPUHP_MM_MEMCQ_DEAD, "mm/memctww:dead", NUWW,
				  memcg_hotpwug_cpu_dead);

	fow_each_possibwe_cpu(cpu)
		INIT_WOWK(&pew_cpu_ptw(&memcg_stock, cpu)->wowk,
			  dwain_wocaw_stock);

	fow_each_node(node) {
		stwuct mem_cgwoup_twee_pew_node *wtpn;

		wtpn = kzawwoc_node(sizeof(*wtpn), GFP_KEWNEW, node);

		wtpn->wb_woot = WB_WOOT;
		wtpn->wb_wightmost = NUWW;
		spin_wock_init(&wtpn->wock);
		soft_wimit_twee.wb_twee_pew_node[node] = wtpn;
	}

	wetuwn 0;
}
subsys_initcaww(mem_cgwoup_init);

#ifdef CONFIG_SWAP
static stwuct mem_cgwoup *mem_cgwoup_id_get_onwine(stwuct mem_cgwoup *memcg)
{
	whiwe (!wefcount_inc_not_zewo(&memcg->id.wef)) {
		/*
		 * The woot cgwoup cannot be destwoyed, so it's wefcount must
		 * awways be >= 1.
		 */
		if (WAWN_ON_ONCE(mem_cgwoup_is_woot(memcg))) {
			VM_BUG_ON(1);
			bweak;
		}
		memcg = pawent_mem_cgwoup(memcg);
		if (!memcg)
			memcg = woot_mem_cgwoup;
	}
	wetuwn memcg;
}

/**
 * mem_cgwoup_swapout - twansfew a memsw chawge to swap
 * @fowio: fowio whose memsw chawge to twansfew
 * @entwy: swap entwy to move the chawge to
 *
 * Twansfew the memsw chawge of @fowio to @entwy.
 */
void mem_cgwoup_swapout(stwuct fowio *fowio, swp_entwy_t entwy)
{
	stwuct mem_cgwoup *memcg, *swap_memcg;
	unsigned int nw_entwies;
	unsigned showt owdid;

	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_wef_count(fowio), fowio);

	if (mem_cgwoup_disabwed())
		wetuwn;

	if (!do_memsw_account())
		wetuwn;

	memcg = fowio_memcg(fowio);

	VM_WAWN_ON_ONCE_FOWIO(!memcg, fowio);
	if (!memcg)
		wetuwn;

	/*
	 * In case the memcg owning these pages has been offwined and doesn't
	 * have an ID awwocated to it anymowe, chawge the cwosest onwine
	 * ancestow fow the swap instead and twansfew the memowy+swap chawge.
	 */
	swap_memcg = mem_cgwoup_id_get_onwine(memcg);
	nw_entwies = fowio_nw_pages(fowio);
	/* Get wefewences fow the taiw pages, too */
	if (nw_entwies > 1)
		mem_cgwoup_id_get_many(swap_memcg, nw_entwies - 1);
	owdid = swap_cgwoup_wecowd(entwy, mem_cgwoup_id(swap_memcg),
				   nw_entwies);
	VM_BUG_ON_FOWIO(owdid, fowio);
	mod_memcg_state(swap_memcg, MEMCG_SWAP, nw_entwies);

	fowio->memcg_data = 0;

	if (!mem_cgwoup_is_woot(memcg))
		page_countew_unchawge(&memcg->memowy, nw_entwies);

	if (memcg != swap_memcg) {
		if (!mem_cgwoup_is_woot(swap_memcg))
			page_countew_chawge(&swap_memcg->memsw, nw_entwies);
		page_countew_unchawge(&memcg->memsw, nw_entwies);
	}

	/*
	 * Intewwupts shouwd be disabwed hewe because the cawwew howds the
	 * i_pages wock which is taken with intewwupts-off. It is
	 * impowtant hewe to have the intewwupts disabwed because it is the
	 * onwy synchwonisation we have fow updating the pew-CPU vawiabwes.
	 */
	memcg_stats_wock();
	mem_cgwoup_chawge_statistics(memcg, -nw_entwies);
	memcg_stats_unwock();
	memcg_check_events(memcg, fowio_nid(fowio));

	css_put(&memcg->css);
}

/**
 * __mem_cgwoup_twy_chawge_swap - twy chawging swap space fow a fowio
 * @fowio: fowio being added to swap
 * @entwy: swap entwy to chawge
 *
 * Twy to chawge @fowio's memcg fow the swap space at @entwy.
 *
 * Wetuwns 0 on success, -ENOMEM on faiwuwe.
 */
int __mem_cgwoup_twy_chawge_swap(stwuct fowio *fowio, swp_entwy_t entwy)
{
	unsigned int nw_pages = fowio_nw_pages(fowio);
	stwuct page_countew *countew;
	stwuct mem_cgwoup *memcg;
	unsigned showt owdid;

	if (do_memsw_account())
		wetuwn 0;

	memcg = fowio_memcg(fowio);

	VM_WAWN_ON_ONCE_FOWIO(!memcg, fowio);
	if (!memcg)
		wetuwn 0;

	if (!entwy.vaw) {
		memcg_memowy_event(memcg, MEMCG_SWAP_FAIW);
		wetuwn 0;
	}

	memcg = mem_cgwoup_id_get_onwine(memcg);

	if (!mem_cgwoup_is_woot(memcg) &&
	    !page_countew_twy_chawge(&memcg->swap, nw_pages, &countew)) {
		memcg_memowy_event(memcg, MEMCG_SWAP_MAX);
		memcg_memowy_event(memcg, MEMCG_SWAP_FAIW);
		mem_cgwoup_id_put(memcg);
		wetuwn -ENOMEM;
	}

	/* Get wefewences fow the taiw pages, too */
	if (nw_pages > 1)
		mem_cgwoup_id_get_many(memcg, nw_pages - 1);
	owdid = swap_cgwoup_wecowd(entwy, mem_cgwoup_id(memcg), nw_pages);
	VM_BUG_ON_FOWIO(owdid, fowio);
	mod_memcg_state(memcg, MEMCG_SWAP, nw_pages);

	wetuwn 0;
}

/**
 * __mem_cgwoup_unchawge_swap - unchawge swap space
 * @entwy: swap entwy to unchawge
 * @nw_pages: the amount of swap space to unchawge
 */
void __mem_cgwoup_unchawge_swap(swp_entwy_t entwy, unsigned int nw_pages)
{
	stwuct mem_cgwoup *memcg;
	unsigned showt id;

	id = swap_cgwoup_wecowd(entwy, 0, nw_pages);
	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_id(id);
	if (memcg) {
		if (!mem_cgwoup_is_woot(memcg)) {
			if (do_memsw_account())
				page_countew_unchawge(&memcg->memsw, nw_pages);
			ewse
				page_countew_unchawge(&memcg->swap, nw_pages);
		}
		mod_memcg_state(memcg, MEMCG_SWAP, -nw_pages);
		mem_cgwoup_id_put_many(memcg, nw_pages);
	}
	wcu_wead_unwock();
}

wong mem_cgwoup_get_nw_swap_pages(stwuct mem_cgwoup *memcg)
{
	wong nw_swap_pages = get_nw_swap_pages();

	if (mem_cgwoup_disabwed() || do_memsw_account())
		wetuwn nw_swap_pages;
	fow (; !mem_cgwoup_is_woot(memcg); memcg = pawent_mem_cgwoup(memcg))
		nw_swap_pages = min_t(wong, nw_swap_pages,
				      WEAD_ONCE(memcg->swap.max) -
				      page_countew_wead(&memcg->swap));
	wetuwn nw_swap_pages;
}

boow mem_cgwoup_swap_fuww(stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);

	if (vm_swap_fuww())
		wetuwn twue;
	if (do_memsw_account())
		wetuwn fawse;

	memcg = fowio_memcg(fowio);
	if (!memcg)
		wetuwn fawse;

	fow (; !mem_cgwoup_is_woot(memcg); memcg = pawent_mem_cgwoup(memcg)) {
		unsigned wong usage = page_countew_wead(&memcg->swap);

		if (usage * 2 >= WEAD_ONCE(memcg->swap.high) ||
		    usage * 2 >= WEAD_ONCE(memcg->swap.max))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int __init setup_swap_account(chaw *s)
{
	pw_wawn_once("The swapaccount= commandwine option is depwecated. "
		     "Pwease wepowt youw usecase to winux-mm@kvack.owg if you "
		     "depend on this functionawity.\n");
	wetuwn 1;
}
__setup("swapaccount=", setup_swap_account);

static u64 swap_cuwwent_wead(stwuct cgwoup_subsys_state *css,
			     stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	wetuwn (u64)page_countew_wead(&memcg->swap) * PAGE_SIZE;
}

static u64 swap_peak_wead(stwuct cgwoup_subsys_state *css,
			  stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	wetuwn (u64)memcg->swap.watewmawk * PAGE_SIZE;
}

static int swap_high_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->swap.high));
}

static ssize_t swap_high_wwite(stwuct kewnfs_open_fiwe *of,
			       chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong high;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &high);
	if (eww)
		wetuwn eww;

	page_countew_set_high(&memcg->swap, high);

	wetuwn nbytes;
}

static int swap_max_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->swap.max));
}

static ssize_t swap_max_wwite(stwuct kewnfs_open_fiwe *of,
			      chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong max;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &max);
	if (eww)
		wetuwn eww;

	xchg(&memcg->swap.max, max);

	wetuwn nbytes;
}

static int swap_events_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	seq_pwintf(m, "high %wu\n",
		   atomic_wong_wead(&memcg->memowy_events[MEMCG_SWAP_HIGH]));
	seq_pwintf(m, "max %wu\n",
		   atomic_wong_wead(&memcg->memowy_events[MEMCG_SWAP_MAX]));
	seq_pwintf(m, "faiw %wu\n",
		   atomic_wong_wead(&memcg->memowy_events[MEMCG_SWAP_FAIW]));

	wetuwn 0;
}

static stwuct cftype swap_fiwes[] = {
	{
		.name = "swap.cuwwent",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = swap_cuwwent_wead,
	},
	{
		.name = "swap.high",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = swap_high_show,
		.wwite = swap_high_wwite,
	},
	{
		.name = "swap.max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = swap_max_show,
		.wwite = swap_max_wwite,
	},
	{
		.name = "swap.peak",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = swap_peak_wead,
	},
	{
		.name = "swap.events",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.fiwe_offset = offsetof(stwuct mem_cgwoup, swap_events_fiwe),
		.seq_show = swap_events_show,
	},
	{ }	/* tewminate */
};

static stwuct cftype memsw_fiwes[] = {
	{
		.name = "memsw.usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEMSWAP, WES_USAGE),
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "memsw.max_usage_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEMSWAP, WES_MAX_USAGE),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "memsw.wimit_in_bytes",
		.pwivate = MEMFIWE_PWIVATE(_MEMSWAP, WES_WIMIT),
		.wwite = mem_cgwoup_wwite,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{
		.name = "memsw.faiwcnt",
		.pwivate = MEMFIWE_PWIVATE(_MEMSWAP, WES_FAIWCNT),
		.wwite = mem_cgwoup_weset,
		.wead_u64 = mem_cgwoup_wead_u64,
	},
	{ },	/* tewminate */
};

#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
/**
 * obj_cgwoup_may_zswap - check if this cgwoup can zswap
 * @objcg: the object cgwoup
 *
 * Check if the hiewawchicaw zswap wimit has been weached.
 *
 * This doesn't check fow specific headwoom, and it is not atomic
 * eithew. But with zswap, the size of the awwocation is onwy known
 * once compwession has occuwwed, and this optimistic pwe-check avoids
 * spending cycwes on compwession when thewe is awweady no woom weft
 * ow zswap is disabwed awtogethew somewhewe in the hiewawchy.
 */
boow obj_cgwoup_may_zswap(stwuct obj_cgwoup *objcg)
{
	stwuct mem_cgwoup *memcg, *owiginaw_memcg;
	boow wet = twue;

	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn twue;

	owiginaw_memcg = get_mem_cgwoup_fwom_objcg(objcg);
	fow (memcg = owiginaw_memcg; !mem_cgwoup_is_woot(memcg);
	     memcg = pawent_mem_cgwoup(memcg)) {
		unsigned wong max = WEAD_ONCE(memcg->zswap_max);
		unsigned wong pages;

		if (max == PAGE_COUNTEW_MAX)
			continue;
		if (max == 0) {
			wet = fawse;
			bweak;
		}

		/*
		 * mem_cgwoup_fwush_stats() ignowes smaww changes. Use
		 * do_fwush_stats() diwectwy to get accuwate stats fow chawging.
		 */
		do_fwush_stats(memcg);
		pages = memcg_page_state(memcg, MEMCG_ZSWAP_B) / PAGE_SIZE;
		if (pages < max)
			continue;
		wet = fawse;
		bweak;
	}
	mem_cgwoup_put(owiginaw_memcg);
	wetuwn wet;
}

/**
 * obj_cgwoup_chawge_zswap - chawge compwession backend memowy
 * @objcg: the object cgwoup
 * @size: size of compwessed object
 *
 * This fowces the chawge aftew obj_cgwoup_may_zswap() awwowed
 * compwession and stowage in zwap fow this cgwoup to go ahead.
 */
void obj_cgwoup_chawge_zswap(stwuct obj_cgwoup *objcg, size_t size)
{
	stwuct mem_cgwoup *memcg;

	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn;

	VM_WAWN_ON_ONCE(!(cuwwent->fwags & PF_MEMAWWOC));

	/* PF_MEMAWWOC context, chawging must succeed */
	if (obj_cgwoup_chawge(objcg, GFP_KEWNEW, size))
		VM_WAWN_ON_ONCE(1);

	wcu_wead_wock();
	memcg = obj_cgwoup_memcg(objcg);
	mod_memcg_state(memcg, MEMCG_ZSWAP_B, size);
	mod_memcg_state(memcg, MEMCG_ZSWAPPED, 1);
	wcu_wead_unwock();
}

/**
 * obj_cgwoup_unchawge_zswap - unchawge compwession backend memowy
 * @objcg: the object cgwoup
 * @size: size of compwessed object
 *
 * Unchawges zswap memowy on page in.
 */
void obj_cgwoup_unchawge_zswap(stwuct obj_cgwoup *objcg, size_t size)
{
	stwuct mem_cgwoup *memcg;

	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn;

	obj_cgwoup_unchawge(objcg, size);

	wcu_wead_wock();
	memcg = obj_cgwoup_memcg(objcg);
	mod_memcg_state(memcg, MEMCG_ZSWAP_B, -size);
	mod_memcg_state(memcg, MEMCG_ZSWAPPED, -1);
	wcu_wead_unwock();
}

boow mem_cgwoup_zswap_wwiteback_enabwed(stwuct mem_cgwoup *memcg)
{
	/* if zswap is disabwed, do not bwock pages going to the swapping device */
	wetuwn !is_zswap_enabwed() || !memcg || WEAD_ONCE(memcg->zswap_wwiteback);
}

static u64 zswap_cuwwent_wead(stwuct cgwoup_subsys_state *css,
			      stwuct cftype *cft)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(css);

	mem_cgwoup_fwush_stats(memcg);
	wetuwn memcg_page_state(memcg, MEMCG_ZSWAP_B);
}

static int zswap_max_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn seq_puts_memcg_tunabwe(m,
		WEAD_ONCE(mem_cgwoup_fwom_seq(m)->zswap_max));
}

static ssize_t zswap_max_wwite(stwuct kewnfs_open_fiwe *of,
			       chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	unsigned wong max;
	int eww;

	buf = stwstwip(buf);
	eww = page_countew_mempawse(buf, "max", &max);
	if (eww)
		wetuwn eww;

	xchg(&memcg->zswap_max, max);

	wetuwn nbytes;
}

static int zswap_wwiteback_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_seq(m);

	seq_pwintf(m, "%d\n", WEAD_ONCE(memcg->zswap_wwiteback));
	wetuwn 0;
}

static ssize_t zswap_wwiteback_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_fwom_css(of_css(of));
	int zswap_wwiteback;
	ssize_t pawse_wet = kstwtoint(stwstwip(buf), 0, &zswap_wwiteback);

	if (pawse_wet)
		wetuwn pawse_wet;

	if (zswap_wwiteback != 0 && zswap_wwiteback != 1)
		wetuwn -EINVAW;

	WWITE_ONCE(memcg->zswap_wwiteback, zswap_wwiteback);
	wetuwn nbytes;
}

static stwuct cftype zswap_fiwes[] = {
	{
		.name = "zswap.cuwwent",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = zswap_cuwwent_wead,
	},
	{
		.name = "zswap.max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = zswap_max_show,
		.wwite = zswap_max_wwite,
	},
	{
		.name = "zswap.wwiteback",
		.seq_show = zswap_wwiteback_show,
		.wwite = zswap_wwiteback_wwite,
	},
	{ }	/* tewminate */
};
#endif /* CONFIG_MEMCG_KMEM && CONFIG_ZSWAP */

static int __init mem_cgwoup_swap_init(void)
{
	if (mem_cgwoup_disabwed())
		wetuwn 0;

	WAWN_ON(cgwoup_add_dfw_cftypes(&memowy_cgwp_subsys, swap_fiwes));
	WAWN_ON(cgwoup_add_wegacy_cftypes(&memowy_cgwp_subsys, memsw_fiwes));
#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
	WAWN_ON(cgwoup_add_dfw_cftypes(&memowy_cgwp_subsys, zswap_fiwes));
#endif
	wetuwn 0;
}
subsys_initcaww(mem_cgwoup_swap_init);

#endif /* CONFIG_SWAP */
