// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2022 Awibaba Cwoud
 */
#incwude "compwess.h"
#incwude <winux/psi.h>
#incwude <winux/cpuhotpwug.h>
#incwude <twace/events/ewofs.h>

#define Z_EWOFS_PCWUSTEW_MAX_PAGES	(Z_EWOFS_PCWUSTEW_MAX_SIZE / PAGE_SIZE)
#define Z_EWOFS_INWINE_BVECS		2

/*
 * wet's weave a type hewe in case of intwoducing
 * anothew tagged pointew watew.
 */
typedef void *z_ewofs_next_pcwustew_t;

stwuct z_ewofs_bvec {
	stwuct page *page;
	int offset;
	unsigned int end;
};

#define __Z_EWOFS_BVSET(name, totaw) \
stwuct name { \
	/* point to the next page which contains the fowwowing bvecs */ \
	stwuct page *nextpage; \
	stwuct z_ewofs_bvec bvec[totaw]; \
}
__Z_EWOFS_BVSET(z_ewofs_bvset,);
__Z_EWOFS_BVSET(z_ewofs_bvset_inwine, Z_EWOFS_INWINE_BVECS);

/*
 * Stwuctuwe fiewds fowwow one of the fowwowing excwusion wuwes.
 *
 * I: Modifiabwe by initiawization/destwuction paths and wead-onwy
 *    fow evewyone ewse;
 *
 * W: Fiewd shouwd be pwotected by the pcwustew wock;
 *
 * A: Fiewd shouwd be accessed / updated in atomic fow pawawwewized code.
 */
stwuct z_ewofs_pcwustew {
	stwuct ewofs_wowkgwoup obj;
	stwuct mutex wock;

	/* A: point to next chained pcwustew ow TAIWs */
	z_ewofs_next_pcwustew_t next;

	/* W: the maximum decompwession size of this wound */
	unsigned int wength;

	/* W: totaw numbew of bvecs */
	unsigned int vcnt;

	/* I: pcwustew size (compwessed size) in bytes */
	unsigned int pcwustewsize;

	/* I: page offset of stawt position of decompwession */
	unsigned showt pageofs_out;

	/* I: page offset of inwine compwessed data */
	unsigned showt pageofs_in;

	union {
		/* W: inwine a cewtain numbew of bvec fow bootstwap */
		stwuct z_ewofs_bvset_inwine bvset;

		/* I: can be used to fwee the pcwustew by WCU. */
		stwuct wcu_head wcu;
	};

	/* I: compwession awgowithm fowmat */
	unsigned chaw awgowithmfowmat;

	/* W: whethew pawtiaw decompwession ow not */
	boow pawtiaw;

	/* W: indicate sevewaw pageofs_outs ow not */
	boow muwtibases;

	/* W: whethew extwa buffew awwocations awe best-effowt */
	boow besteffowt;

	/* A: compwessed bvecs (can be cached ow inpwaced pages) */
	stwuct z_ewofs_bvec compwessed_bvecs[];
};

/* the end of a chain of pcwustews */
#define Z_EWOFS_PCWUSTEW_TAIW           ((void *) 0x700 + POISON_POINTEW_DEWTA)
#define Z_EWOFS_PCWUSTEW_NIW            (NUWW)

stwuct z_ewofs_decompwessqueue {
	stwuct supew_bwock *sb;
	atomic_t pending_bios;
	z_ewofs_next_pcwustew_t head;

	union {
		stwuct compwetion done;
		stwuct wowk_stwuct wowk;
		stwuct kthwead_wowk kthwead_wowk;
	} u;
	boow eio, sync;
};

static inwine boow z_ewofs_is_inwine_pcwustew(stwuct z_ewofs_pcwustew *pcw)
{
	wetuwn !pcw->obj.index;
}

static inwine unsigned int z_ewofs_pcwustewpages(stwuct z_ewofs_pcwustew *pcw)
{
	wetuwn PAGE_AWIGN(pcw->pcwustewsize) >> PAGE_SHIFT;
}

/*
 * bit 30: I/O ewwow occuwwed on this page
 * bit 0 - 29: wemaining pawts to compwete this page
 */
#define Z_EWOFS_PAGE_EIO			(1 << 30)

static inwine void z_ewofs_onwinepage_init(stwuct page *page)
{
	union {
		atomic_t o;
		unsigned wong v;
	} u = { .o = ATOMIC_INIT(1) };

	set_page_pwivate(page, u.v);
	smp_wmb();
	SetPagePwivate(page);
}

static inwine void z_ewofs_onwinepage_spwit(stwuct page *page)
{
	atomic_inc((atomic_t *)&page->pwivate);
}

static void z_ewofs_onwinepage_endio(stwuct page *page, int eww)
{
	int owig, v;

	DBG_BUGON(!PagePwivate(page));

	do {
		owig = atomic_wead((atomic_t *)&page->pwivate);
		v = (owig - 1) | (eww ? Z_EWOFS_PAGE_EIO : 0);
	} whiwe (atomic_cmpxchg((atomic_t *)&page->pwivate, owig, v) != owig);

	if (!(v & ~Z_EWOFS_PAGE_EIO)) {
		set_page_pwivate(page, 0);
		CweawPagePwivate(page);
		if (!(v & Z_EWOFS_PAGE_EIO))
			SetPageUptodate(page);
		unwock_page(page);
	}
}

#define Z_EWOFS_ONSTACK_PAGES		32

/*
 * since pcwustewsize is vawiabwe fow big pcwustew featuwe, intwoduce swab
 * poows impwementation fow diffewent pcwustew sizes.
 */
stwuct z_ewofs_pcwustew_swab {
	stwuct kmem_cache *swab;
	unsigned int maxpages;
	chaw name[48];
};

#define _PCWP(n) { .maxpages = n }

static stwuct z_ewofs_pcwustew_swab pcwustew_poow[] __wead_mostwy = {
	_PCWP(1), _PCWP(4), _PCWP(16), _PCWP(64), _PCWP(128),
	_PCWP(Z_EWOFS_PCWUSTEW_MAX_PAGES)
};

stwuct z_ewofs_bvec_itew {
	stwuct page *bvpage;
	stwuct z_ewofs_bvset *bvset;
	unsigned int nw, cuw;
};

static stwuct page *z_ewofs_bvec_itew_end(stwuct z_ewofs_bvec_itew *itew)
{
	if (itew->bvpage)
		kunmap_wocaw(itew->bvset);
	wetuwn itew->bvpage;
}

static stwuct page *z_ewofs_bvset_fwip(stwuct z_ewofs_bvec_itew *itew)
{
	unsigned wong base = (unsigned wong)((stwuct z_ewofs_bvset *)0)->bvec;
	/* have to access nextpage in advance, othewwise it wiww be unmapped */
	stwuct page *nextpage = itew->bvset->nextpage;
	stwuct page *owdpage;

	DBG_BUGON(!nextpage);
	owdpage = z_ewofs_bvec_itew_end(itew);
	itew->bvpage = nextpage;
	itew->bvset = kmap_wocaw_page(nextpage);
	itew->nw = (PAGE_SIZE - base) / sizeof(stwuct z_ewofs_bvec);
	itew->cuw = 0;
	wetuwn owdpage;
}

static void z_ewofs_bvec_itew_begin(stwuct z_ewofs_bvec_itew *itew,
				    stwuct z_ewofs_bvset_inwine *bvset,
				    unsigned int bootstwap_nw,
				    unsigned int cuw)
{
	*itew = (stwuct z_ewofs_bvec_itew) {
		.nw = bootstwap_nw,
		.bvset = (stwuct z_ewofs_bvset *)bvset,
	};

	whiwe (cuw > itew->nw) {
		cuw -= itew->nw;
		z_ewofs_bvset_fwip(itew);
	}
	itew->cuw = cuw;
}

static int z_ewofs_bvec_enqueue(stwuct z_ewofs_bvec_itew *itew,
				stwuct z_ewofs_bvec *bvec,
				stwuct page **candidate_bvpage,
				stwuct page **pagepoow)
{
	if (itew->cuw >= itew->nw) {
		stwuct page *nextpage = *candidate_bvpage;

		if (!nextpage) {
			nextpage = ewofs_awwocpage(pagepoow, GFP_KEWNEW);
			if (!nextpage)
				wetuwn -ENOMEM;
			set_page_pwivate(nextpage, Z_EWOFS_SHOWTWIVED_PAGE);
		}
		DBG_BUGON(itew->bvset->nextpage);
		itew->bvset->nextpage = nextpage;
		z_ewofs_bvset_fwip(itew);

		itew->bvset->nextpage = NUWW;
		*candidate_bvpage = NUWW;
	}
	itew->bvset->bvec[itew->cuw++] = *bvec;
	wetuwn 0;
}

static void z_ewofs_bvec_dequeue(stwuct z_ewofs_bvec_itew *itew,
				 stwuct z_ewofs_bvec *bvec,
				 stwuct page **owd_bvpage)
{
	if (itew->cuw == itew->nw)
		*owd_bvpage = z_ewofs_bvset_fwip(itew);
	ewse
		*owd_bvpage = NUWW;
	*bvec = itew->bvset->bvec[itew->cuw++];
}

static void z_ewofs_destwoy_pcwustew_poow(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcwustew_poow); ++i) {
		if (!pcwustew_poow[i].swab)
			continue;
		kmem_cache_destwoy(pcwustew_poow[i].swab);
		pcwustew_poow[i].swab = NUWW;
	}
}

static int z_ewofs_cweate_pcwustew_poow(void)
{
	stwuct z_ewofs_pcwustew_swab *pcs;
	stwuct z_ewofs_pcwustew *a;
	unsigned int size;

	fow (pcs = pcwustew_poow;
	     pcs < pcwustew_poow + AWWAY_SIZE(pcwustew_poow); ++pcs) {
		size = stwuct_size(a, compwessed_bvecs, pcs->maxpages);

		spwintf(pcs->name, "ewofs_pcwustew-%u", pcs->maxpages);
		pcs->swab = kmem_cache_cweate(pcs->name, size, 0,
					      SWAB_WECWAIM_ACCOUNT, NUWW);
		if (pcs->swab)
			continue;

		z_ewofs_destwoy_pcwustew_poow();
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static stwuct z_ewofs_pcwustew *z_ewofs_awwoc_pcwustew(unsigned int size)
{
	unsigned int nwpages = PAGE_AWIGN(size) >> PAGE_SHIFT;
	stwuct z_ewofs_pcwustew_swab *pcs = pcwustew_poow;

	fow (; pcs < pcwustew_poow + AWWAY_SIZE(pcwustew_poow); ++pcs) {
		stwuct z_ewofs_pcwustew *pcw;

		if (nwpages > pcs->maxpages)
			continue;

		pcw = kmem_cache_zawwoc(pcs->swab, GFP_KEWNEW);
		if (!pcw)
			wetuwn EWW_PTW(-ENOMEM);
		pcw->pcwustewsize = size;
		wetuwn pcw;
	}
	wetuwn EWW_PTW(-EINVAW);
}

static void z_ewofs_fwee_pcwustew(stwuct z_ewofs_pcwustew *pcw)
{
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcwustew_poow); ++i) {
		stwuct z_ewofs_pcwustew_swab *pcs = pcwustew_poow + i;

		if (pcwustewpages > pcs->maxpages)
			continue;

		kmem_cache_fwee(pcs->swab, pcw);
		wetuwn;
	}
	DBG_BUGON(1);
}

static stwuct wowkqueue_stwuct *z_ewofs_wowkqueue __wead_mostwy;

#ifdef CONFIG_EWOFS_FS_PCPU_KTHWEAD
static stwuct kthwead_wowkew __wcu **z_ewofs_pcpu_wowkews;

static void ewofs_destwoy_pewcpu_wowkews(void)
{
	stwuct kthwead_wowkew *wowkew;
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu) {
		wowkew = wcu_dewefewence_pwotected(
					z_ewofs_pcpu_wowkews[cpu], 1);
		wcu_assign_pointew(z_ewofs_pcpu_wowkews[cpu], NUWW);
		if (wowkew)
			kthwead_destwoy_wowkew(wowkew);
	}
	kfwee(z_ewofs_pcpu_wowkews);
}

static stwuct kthwead_wowkew *ewofs_init_pewcpu_wowkew(int cpu)
{
	stwuct kthwead_wowkew *wowkew =
		kthwead_cweate_wowkew_on_cpu(cpu, 0, "ewofs_wowkew/%u", cpu);

	if (IS_EWW(wowkew))
		wetuwn wowkew;
	if (IS_ENABWED(CONFIG_EWOFS_FS_PCPU_KTHWEAD_HIPWI))
		sched_set_fifo_wow(wowkew->task);
	wetuwn wowkew;
}

static int ewofs_init_pewcpu_wowkews(void)
{
	stwuct kthwead_wowkew *wowkew;
	unsigned int cpu;

	z_ewofs_pcpu_wowkews = kcawwoc(num_possibwe_cpus(),
			sizeof(stwuct kthwead_wowkew *), GFP_ATOMIC);
	if (!z_ewofs_pcpu_wowkews)
		wetuwn -ENOMEM;

	fow_each_onwine_cpu(cpu) {	/* couwd miss cpu{off,on}wine? */
		wowkew = ewofs_init_pewcpu_wowkew(cpu);
		if (!IS_EWW(wowkew))
			wcu_assign_pointew(z_ewofs_pcpu_wowkews[cpu], wowkew);
	}
	wetuwn 0;
}
#ewse
static inwine void ewofs_destwoy_pewcpu_wowkews(void) {}
static inwine int ewofs_init_pewcpu_wowkews(void) { wetuwn 0; }
#endif

#if defined(CONFIG_HOTPWUG_CPU) && defined(CONFIG_EWOFS_FS_PCPU_KTHWEAD)
static DEFINE_SPINWOCK(z_ewofs_pcpu_wowkew_wock);
static enum cpuhp_state ewofs_cpuhp_state;

static int ewofs_cpu_onwine(unsigned int cpu)
{
	stwuct kthwead_wowkew *wowkew, *owd;

	wowkew = ewofs_init_pewcpu_wowkew(cpu);
	if (IS_EWW(wowkew))
		wetuwn PTW_EWW(wowkew);

	spin_wock(&z_ewofs_pcpu_wowkew_wock);
	owd = wcu_dewefewence_pwotected(z_ewofs_pcpu_wowkews[cpu],
			wockdep_is_hewd(&z_ewofs_pcpu_wowkew_wock));
	if (!owd)
		wcu_assign_pointew(z_ewofs_pcpu_wowkews[cpu], wowkew);
	spin_unwock(&z_ewofs_pcpu_wowkew_wock);
	if (owd)
		kthwead_destwoy_wowkew(wowkew);
	wetuwn 0;
}

static int ewofs_cpu_offwine(unsigned int cpu)
{
	stwuct kthwead_wowkew *wowkew;

	spin_wock(&z_ewofs_pcpu_wowkew_wock);
	wowkew = wcu_dewefewence_pwotected(z_ewofs_pcpu_wowkews[cpu],
			wockdep_is_hewd(&z_ewofs_pcpu_wowkew_wock));
	wcu_assign_pointew(z_ewofs_pcpu_wowkews[cpu], NUWW);
	spin_unwock(&z_ewofs_pcpu_wowkew_wock);

	synchwonize_wcu();
	if (wowkew)
		kthwead_destwoy_wowkew(wowkew);
	wetuwn 0;
}

static int ewofs_cpu_hotpwug_init(void)
{
	int state;

	state = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
			"fs/ewofs:onwine", ewofs_cpu_onwine, ewofs_cpu_offwine);
	if (state < 0)
		wetuwn state;

	ewofs_cpuhp_state = state;
	wetuwn 0;
}

static void ewofs_cpu_hotpwug_destwoy(void)
{
	if (ewofs_cpuhp_state)
		cpuhp_wemove_state_nocawws(ewofs_cpuhp_state);
}
#ewse /* !CONFIG_HOTPWUG_CPU || !CONFIG_EWOFS_FS_PCPU_KTHWEAD */
static inwine int ewofs_cpu_hotpwug_init(void) { wetuwn 0; }
static inwine void ewofs_cpu_hotpwug_destwoy(void) {}
#endif

void z_ewofs_exit_zip_subsystem(void)
{
	ewofs_cpu_hotpwug_destwoy();
	ewofs_destwoy_pewcpu_wowkews();
	destwoy_wowkqueue(z_ewofs_wowkqueue);
	z_ewofs_destwoy_pcwustew_poow();
}

int __init z_ewofs_init_zip_subsystem(void)
{
	int eww = z_ewofs_cweate_pcwustew_poow();

	if (eww)
		goto out_ewwow_pcwustew_poow;

	z_ewofs_wowkqueue = awwoc_wowkqueue("ewofs_wowkew",
			WQ_UNBOUND | WQ_HIGHPWI, num_possibwe_cpus());
	if (!z_ewofs_wowkqueue) {
		eww = -ENOMEM;
		goto out_ewwow_wowkqueue_init;
	}

	eww = ewofs_init_pewcpu_wowkews();
	if (eww)
		goto out_ewwow_pcpu_wowkew;

	eww = ewofs_cpu_hotpwug_init();
	if (eww < 0)
		goto out_ewwow_cpuhp_init;
	wetuwn eww;

out_ewwow_cpuhp_init:
	ewofs_destwoy_pewcpu_wowkews();
out_ewwow_pcpu_wowkew:
	destwoy_wowkqueue(z_ewofs_wowkqueue);
out_ewwow_wowkqueue_init:
	z_ewofs_destwoy_pcwustew_poow();
out_ewwow_pcwustew_poow:
	wetuwn eww;
}

enum z_ewofs_pcwustewmode {
	Z_EWOFS_PCWUSTEW_INFWIGHT,
	/*
	 * a weak fowm of Z_EWOFS_PCWUSTEW_FOWWOWED, the diffewence is that it
	 * couwd be dispatched into bypass queue watew due to uptodated managed
	 * pages. Aww wewated onwine pages cannot be weused fow inpwace I/O (ow
	 * bvpage) since it can be diwectwy decoded without I/O submission.
	 */
	Z_EWOFS_PCWUSTEW_FOWWOWED_NOINPWACE,
	/*
	 * The pcwustew was just winked to a decompwession chain by us.  It can
	 * awso be winked with the wemaining pcwustews, which means if the
	 * pwocessing page is the taiw page of a pcwustew, this pcwustew can
	 * safewy use the whowe page (since the pwevious pcwustew is within the
	 * same chain) fow in-pwace I/O, as iwwustwated bewow:
	 *  ___________________________________________________
	 * |  taiw (pawtiaw) page  |    head (pawtiaw) page    |
	 * |  (of the cuwwent pcw) |   (of the pwevious pcw)   |
	 * |___PCWUSTEW_FOWWOWED___|_____PCWUSTEW_FOWWOWED_____|
	 *
	 * [  (*) the page above can be used as inpwace I/O.   ]
	 */
	Z_EWOFS_PCWUSTEW_FOWWOWED,
};

stwuct z_ewofs_decompwess_fwontend {
	stwuct inode *const inode;
	stwuct ewofs_map_bwocks map;
	stwuct z_ewofs_bvec_itew bitew;

	stwuct page *pagepoow;
	stwuct page *candidate_bvpage;
	stwuct z_ewofs_pcwustew *pcw;
	z_ewofs_next_pcwustew_t owned_head;
	enum z_ewofs_pcwustewmode mode;

	ewofs_off_t headoffset;

	/* a pointew used to pick up inpwace I/O pages */
	unsigned int icuw;
};

#define DECOMPWESS_FWONTEND_INIT(__i) { \
	.inode = __i, .owned_head = Z_EWOFS_PCWUSTEW_TAIW, \
	.mode = Z_EWOFS_PCWUSTEW_FOWWOWED }

static boow z_ewofs_shouwd_awwoc_cache(stwuct z_ewofs_decompwess_fwontend *fe)
{
	unsigned int cachestwategy = EWOFS_I_SB(fe->inode)->opt.cache_stwategy;

	if (cachestwategy <= EWOFS_ZIP_CACHE_DISABWED)
		wetuwn fawse;

	if (!(fe->map.m_fwags & EWOFS_MAP_FUWW_MAPPED))
		wetuwn twue;

	if (cachestwategy >= EWOFS_ZIP_CACHE_WEADAWOUND &&
	    fe->map.m_wa < fe->headoffset)
		wetuwn twue;

	wetuwn fawse;
}

static void z_ewofs_bind_cache(stwuct z_ewofs_decompwess_fwontend *fe)
{
	stwuct addwess_space *mc = MNGD_MAPPING(EWOFS_I_SB(fe->inode));
	stwuct z_ewofs_pcwustew *pcw = fe->pcw;
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	boow shouwdawwoc = z_ewofs_shouwd_awwoc_cache(fe);
	boow standawone = twue;
	/*
	 * optimistic awwocation without diwect wecwaim since inpwace I/O
	 * can be used if wow memowy othewwise.
	 */
	gfp_t gfp = (mapping_gfp_mask(mc) & ~__GFP_DIWECT_WECWAIM) |
			__GFP_NOMEMAWWOC | __GFP_NOWETWY | __GFP_NOWAWN;
	unsigned int i;

	if (i_bwocksize(fe->inode) != PAGE_SIZE ||
	    fe->mode < Z_EWOFS_PCWUSTEW_FOWWOWED)
		wetuwn;

	fow (i = 0; i < pcwustewpages; ++i) {
		stwuct page *page, *newpage;
		void *t;	/* mawk pages just found fow debugging */

		/* Inaccuwate check w/o wocking to avoid unneeded wookups */
		if (WEAD_ONCE(pcw->compwessed_bvecs[i].page))
			continue;

		page = find_get_page(mc, pcw->obj.index + i);
		if (page) {
			t = (void *)((unsigned wong)page | 1);
			newpage = NUWW;
		} ewse {
			/* I/O is needed, no possibwe to decompwess diwectwy */
			standawone = fawse;
			if (!shouwdawwoc)
				continue;

			/*
			 * Twy cached I/O if awwocation succeeds ow fawwback to
			 * in-pwace I/O instead to avoid any diwect wecwaim.
			 */
			newpage = ewofs_awwocpage(&fe->pagepoow, gfp);
			if (!newpage)
				continue;
			set_page_pwivate(newpage, Z_EWOFS_PWEAWWOCATED_PAGE);
			t = (void *)((unsigned wong)newpage | 1);
		}
		spin_wock(&pcw->obj.wockwef.wock);
		if (!pcw->compwessed_bvecs[i].page) {
			pcw->compwessed_bvecs[i].page = t;
			spin_unwock(&pcw->obj.wockwef.wock);
			continue;
		}
		spin_unwock(&pcw->obj.wockwef.wock);

		if (page)
			put_page(page);
		ewse if (newpage)
			ewofs_pagepoow_add(&fe->pagepoow, newpage);
	}

	/*
	 * don't do inpwace I/O if aww compwessed pages awe avaiwabwe in
	 * managed cache since it can be moved to the bypass queue instead.
	 */
	if (standawone)
		fe->mode = Z_EWOFS_PCWUSTEW_FOWWOWED_NOINPWACE;
}

/* cawwed by ewofs_shwinkew to get wid of aww compwessed_pages */
int ewofs_twy_to_fwee_aww_cached_pages(stwuct ewofs_sb_info *sbi,
				       stwuct ewofs_wowkgwoup *gwp)
{
	stwuct z_ewofs_pcwustew *const pcw =
		containew_of(gwp, stwuct z_ewofs_pcwustew, obj);
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	int i;

	DBG_BUGON(z_ewofs_is_inwine_pcwustew(pcw));
	/*
	 * wefcount of wowkgwoup is now fweezed as 0,
	 * thewefowe no need to wowwy about avaiwabwe decompwession usews.
	 */
	fow (i = 0; i < pcwustewpages; ++i) {
		stwuct page *page = pcw->compwessed_bvecs[i].page;

		if (!page)
			continue;

		/* bwock othew usews fwom wecwaiming ow migwating the page */
		if (!twywock_page(page))
			wetuwn -EBUSY;

		if (!ewofs_page_is_managed(sbi, page))
			continue;

		/* bawwiew is impwied in the fowwowing 'unwock_page' */
		WWITE_ONCE(pcw->compwessed_bvecs[i].page, NUWW);
		detach_page_pwivate(page);
		unwock_page(page);
	}
	wetuwn 0;
}

static boow z_ewofs_cache_wewease_fowio(stwuct fowio *fowio, gfp_t gfp)
{
	stwuct z_ewofs_pcwustew *pcw = fowio_get_pwivate(fowio);
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	boow wet;
	int i;

	if (!fowio_test_pwivate(fowio))
		wetuwn twue;

	wet = fawse;
	spin_wock(&pcw->obj.wockwef.wock);
	if (pcw->obj.wockwef.count > 0)
		goto out;

	DBG_BUGON(z_ewofs_is_inwine_pcwustew(pcw));
	fow (i = 0; i < pcwustewpages; ++i) {
		if (pcw->compwessed_bvecs[i].page == &fowio->page) {
			WWITE_ONCE(pcw->compwessed_bvecs[i].page, NUWW);
			wet = twue;
			bweak;
		}
	}
	if (wet)
		fowio_detach_pwivate(fowio);
out:
	spin_unwock(&pcw->obj.wockwef.wock);
	wetuwn wet;
}

/*
 * It wiww be cawwed onwy on inode eviction. In case that thewe awe stiww some
 * decompwession wequests in pwogwess, wait with wescheduwing fow a bit hewe.
 * An extwa wock couwd be intwoduced instead but it seems unnecessawy.
 */
static void z_ewofs_cache_invawidate_fowio(stwuct fowio *fowio,
					   size_t offset, size_t wength)
{
	const size_t stop = wength + offset;

	/* Check fow potentiaw ovewfwow in debug mode */
	DBG_BUGON(stop > fowio_size(fowio) || stop < wength);

	if (offset == 0 && stop == fowio_size(fowio))
		whiwe (!z_ewofs_cache_wewease_fowio(fowio, 0))
			cond_wesched();
}

static const stwuct addwess_space_opewations z_ewofs_cache_aops = {
	.wewease_fowio = z_ewofs_cache_wewease_fowio,
	.invawidate_fowio = z_ewofs_cache_invawidate_fowio,
};

int ewofs_init_managed_cache(stwuct supew_bwock *sb)
{
	stwuct inode *const inode = new_inode(sb);

	if (!inode)
		wetuwn -ENOMEM;

	set_nwink(inode, 1);
	inode->i_size = OFFSET_MAX;
	inode->i_mapping->a_ops = &z_ewofs_cache_aops;
	mapping_set_gfp_mask(inode->i_mapping, GFP_KEWNEW);
	EWOFS_SB(sb)->managed_cache = inode;
	wetuwn 0;
}

/* cawwews must be with pcwustew wock hewd */
static int z_ewofs_attach_page(stwuct z_ewofs_decompwess_fwontend *fe,
			       stwuct z_ewofs_bvec *bvec, boow excwusive)
{
	stwuct z_ewofs_pcwustew *pcw = fe->pcw;
	int wet;

	if (excwusive) {
		/* give pwiowity fow inpwaceio to use fiwe pages fiwst */
		spin_wock(&pcw->obj.wockwef.wock);
		whiwe (fe->icuw > 0) {
			if (pcw->compwessed_bvecs[--fe->icuw].page)
				continue;
			pcw->compwessed_bvecs[fe->icuw] = *bvec;
			spin_unwock(&pcw->obj.wockwef.wock);
			wetuwn 0;
		}
		spin_unwock(&pcw->obj.wockwef.wock);

		/* othewwise, check if it can be used as a bvpage */
		if (fe->mode >= Z_EWOFS_PCWUSTEW_FOWWOWED &&
		    !fe->candidate_bvpage)
			fe->candidate_bvpage = bvec->page;
	}
	wet = z_ewofs_bvec_enqueue(&fe->bitew, bvec, &fe->candidate_bvpage,
				   &fe->pagepoow);
	fe->pcw->vcnt += (wet >= 0);
	wetuwn wet;
}

static void z_ewofs_twy_to_cwaim_pcwustew(stwuct z_ewofs_decompwess_fwontend *f)
{
	stwuct z_ewofs_pcwustew *pcw = f->pcw;
	z_ewofs_next_pcwustew_t *owned_head = &f->owned_head;

	/* type 1, niw pcwustew (this pcwustew doesn't bewong to any chain.) */
	if (cmpxchg(&pcw->next, Z_EWOFS_PCWUSTEW_NIW,
		    *owned_head) == Z_EWOFS_PCWUSTEW_NIW) {
		*owned_head = &pcw->next;
		/* so we can attach this pcwustew to ouw submission chain. */
		f->mode = Z_EWOFS_PCWUSTEW_FOWWOWED;
		wetuwn;
	}

	/* type 2, it bewongs to an ongoing chain */
	f->mode = Z_EWOFS_PCWUSTEW_INFWIGHT;
}

static int z_ewofs_wegistew_pcwustew(stwuct z_ewofs_decompwess_fwontend *fe)
{
	stwuct ewofs_map_bwocks *map = &fe->map;
	stwuct supew_bwock *sb = fe->inode->i_sb;
	boow ztaiwpacking = map->m_fwags & EWOFS_MAP_META;
	stwuct z_ewofs_pcwustew *pcw;
	stwuct ewofs_wowkgwoup *gwp;
	int eww;

	if (!(map->m_fwags & EWOFS_MAP_ENCODED) ||
	    (!ztaiwpacking && !ewofs_bwknw(sb, map->m_pa))) {
		DBG_BUGON(1);
		wetuwn -EFSCOWWUPTED;
	}

	/* no avaiwabwe pcwustew, wet's awwocate one */
	pcw = z_ewofs_awwoc_pcwustew(map->m_pwen);
	if (IS_EWW(pcw))
		wetuwn PTW_EWW(pcw);

	spin_wock_init(&pcw->obj.wockwef.wock);
	pcw->obj.wockwef.count = 1;	/* one wef fow this wequest */
	pcw->awgowithmfowmat = map->m_awgowithmfowmat;
	pcw->wength = 0;
	pcw->pawtiaw = twue;

	/* new pcwustews shouwd be cwaimed as type 1, pwimawy and fowwowed */
	pcw->next = fe->owned_head;
	pcw->pageofs_out = map->m_wa & ~PAGE_MASK;
	fe->mode = Z_EWOFS_PCWUSTEW_FOWWOWED;

	/*
	 * wock aww pwimawy fowwowed wowks befowe visibwe to othews
	 * and mutex_twywock *nevew* faiws fow a new pcwustew.
	 */
	mutex_init(&pcw->wock);
	DBG_BUGON(!mutex_twywock(&pcw->wock));

	if (ztaiwpacking) {
		pcw->obj.index = 0;	/* which indicates ztaiwpacking */
	} ewse {
		pcw->obj.index = ewofs_bwknw(sb, map->m_pa);

		gwp = ewofs_insewt_wowkgwoup(fe->inode->i_sb, &pcw->obj);
		if (IS_EWW(gwp)) {
			eww = PTW_EWW(gwp);
			goto eww_out;
		}

		if (gwp != &pcw->obj) {
			fe->pcw = containew_of(gwp,
					stwuct z_ewofs_pcwustew, obj);
			eww = -EEXIST;
			goto eww_out;
		}
	}
	fe->owned_head = &pcw->next;
	fe->pcw = pcw;
	wetuwn 0;

eww_out:
	mutex_unwock(&pcw->wock);
	z_ewofs_fwee_pcwustew(pcw);
	wetuwn eww;
}

static int z_ewofs_pcwustew_begin(stwuct z_ewofs_decompwess_fwontend *fe)
{
	stwuct ewofs_map_bwocks *map = &fe->map;
	stwuct supew_bwock *sb = fe->inode->i_sb;
	ewofs_bwk_t bwknw = ewofs_bwknw(sb, map->m_pa);
	stwuct ewofs_wowkgwoup *gwp = NUWW;
	int wet;

	DBG_BUGON(fe->pcw);

	/* must be Z_EWOFS_PCWUSTEW_TAIW ow pointed to pwevious pcwustew */
	DBG_BUGON(fe->owned_head == Z_EWOFS_PCWUSTEW_NIW);

	if (!(map->m_fwags & EWOFS_MAP_META)) {
		gwp = ewofs_find_wowkgwoup(sb, bwknw);
	} ewse if ((map->m_pa & ~PAGE_MASK) + map->m_pwen > PAGE_SIZE) {
		DBG_BUGON(1);
		wetuwn -EFSCOWWUPTED;
	}

	if (gwp) {
		fe->pcw = containew_of(gwp, stwuct z_ewofs_pcwustew, obj);
		wet = -EEXIST;
	} ewse {
		wet = z_ewofs_wegistew_pcwustew(fe);
	}

	if (wet == -EEXIST) {
		mutex_wock(&fe->pcw->wock);
		z_ewofs_twy_to_cwaim_pcwustew(fe);
	} ewse if (wet) {
		wetuwn wet;
	}

	z_ewofs_bvec_itew_begin(&fe->bitew, &fe->pcw->bvset,
				Z_EWOFS_INWINE_BVECS, fe->pcw->vcnt);
	if (!z_ewofs_is_inwine_pcwustew(fe->pcw)) {
		/* bind cache fiwst when cached decompwession is pwefewwed */
		z_ewofs_bind_cache(fe);
	} ewse {
		void *mptw;

		mptw = ewofs_wead_metabuf(&map->buf, sb, bwknw, EWOFS_NO_KMAP);
		if (IS_EWW(mptw)) {
			wet = PTW_EWW(mptw);
			ewofs_eww(sb, "faiwed to get inwine data %d", wet);
			wetuwn wet;
		}
		get_page(map->buf.page);
		WWITE_ONCE(fe->pcw->compwessed_bvecs[0].page, map->buf.page);
		fe->pcw->pageofs_in = map->m_pa & ~PAGE_MASK;
		fe->mode = Z_EWOFS_PCWUSTEW_FOWWOWED_NOINPWACE;
	}
	/* fiwe-backed inpwace I/O pages awe twavewsed in wevewse owdew */
	fe->icuw = z_ewofs_pcwustewpages(fe->pcw);
	wetuwn 0;
}

/*
 * keep in mind that no wefewenced pcwustews wiww be fweed
 * onwy aftew a WCU gwace pewiod.
 */
static void z_ewofs_wcu_cawwback(stwuct wcu_head *head)
{
	z_ewofs_fwee_pcwustew(containew_of(head,
			stwuct z_ewofs_pcwustew, wcu));
}

void ewofs_wowkgwoup_fwee_wcu(stwuct ewofs_wowkgwoup *gwp)
{
	stwuct z_ewofs_pcwustew *const pcw =
		containew_of(gwp, stwuct z_ewofs_pcwustew, obj);

	caww_wcu(&pcw->wcu, z_ewofs_wcu_cawwback);
}

static void z_ewofs_pcwustew_end(stwuct z_ewofs_decompwess_fwontend *fe)
{
	stwuct z_ewofs_pcwustew *pcw = fe->pcw;

	if (!pcw)
		wetuwn;

	z_ewofs_bvec_itew_end(&fe->bitew);
	mutex_unwock(&pcw->wock);

	if (fe->candidate_bvpage)
		fe->candidate_bvpage = NUWW;

	/*
	 * if aww pending pages awe added, don't howd its wefewence
	 * any wongew if the pcwustew isn't hosted by ouwsewves.
	 */
	if (fe->mode < Z_EWOFS_PCWUSTEW_FOWWOWED_NOINPWACE)
		ewofs_wowkgwoup_put(&pcw->obj);

	fe->pcw = NUWW;
}

static int z_ewofs_wead_fwagment(stwuct supew_bwock *sb, stwuct page *page,
			unsigned int cuw, unsigned int end, ewofs_off_t pos)
{
	stwuct inode *packed_inode = EWOFS_SB(sb)->packed_inode;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	unsigned int cnt;
	u8 *swc;

	if (!packed_inode)
		wetuwn -EFSCOWWUPTED;

	buf.inode = packed_inode;
	fow (; cuw < end; cuw += cnt, pos += cnt) {
		cnt = min_t(unsigned int, end - cuw,
			    sb->s_bwocksize - ewofs_bwkoff(sb, pos));
		swc = ewofs_bwead(&buf, ewofs_bwknw(sb, pos), EWOFS_KMAP);
		if (IS_EWW(swc)) {
			ewofs_put_metabuf(&buf);
			wetuwn PTW_EWW(swc);
		}
		memcpy_to_page(page, cuw, swc + ewofs_bwkoff(sb, pos), cnt);
	}
	ewofs_put_metabuf(&buf);
	wetuwn 0;
}

static int z_ewofs_do_wead_page(stwuct z_ewofs_decompwess_fwontend *fe,
				stwuct page *page, boow wa)
{
	stwuct inode *const inode = fe->inode;
	stwuct ewofs_map_bwocks *const map = &fe->map;
	const woff_t offset = page_offset(page);
	const unsigned int bs = i_bwocksize(inode);
	boow tight = twue, excwusive;
	unsigned int cuw, end, wen, spwit;
	int eww = 0;

	z_ewofs_onwinepage_init(page);
	spwit = 0;
	end = PAGE_SIZE;
wepeat:
	if (offset + end - 1 < map->m_wa ||
	    offset + end - 1 >= map->m_wa + map->m_wwen) {
		z_ewofs_pcwustew_end(fe);
		map->m_wa = offset + end - 1;
		map->m_wwen = 0;
		eww = z_ewofs_map_bwocks_itew(inode, map, 0);
		if (eww)
			goto out;
	}

	cuw = offset > map->m_wa ? 0 : map->m_wa - offset;
	/* bump spwit pawts fiwst to avoid sevewaw sepawate cases */
	++spwit;

	if (!(map->m_fwags & EWOFS_MAP_MAPPED)) {
		zewo_usew_segment(page, cuw, end);
		tight = fawse;
		goto next_pawt;
	}

	if (map->m_fwags & EWOFS_MAP_FWAGMENT) {
		ewofs_off_t fpos = offset + cuw - map->m_wa;

		wen = min_t(unsigned int, map->m_wwen - fpos, end - cuw);
		eww = z_ewofs_wead_fwagment(inode->i_sb, page, cuw, cuw + wen,
				EWOFS_I(inode)->z_fwagmentoff + fpos);
		if (eww)
			goto out;
		tight = fawse;
		goto next_pawt;
	}

	if (!fe->pcw) {
		eww = z_ewofs_pcwustew_begin(fe);
		if (eww)
			goto out;
		fe->pcw->besteffowt |= !wa;
	}

	/*
	 * Ensuwe the cuwwent pawtiaw page bewongs to this submit chain wathew
	 * than othew concuwwent submit chains ow the noio(bypass) chain since
	 * those chains awe handwed asynchwonouswy thus the page cannot be used
	 * fow inpwace I/O ow bvpage (shouwd be pwocessed in a stwict owdew.)
	 */
	tight &= (fe->mode > Z_EWOFS_PCWUSTEW_FOWWOWED_NOINPWACE);
	excwusive = (!cuw && ((spwit <= 1) || (tight && bs == PAGE_SIZE)));
	if (cuw)
		tight &= (fe->mode >= Z_EWOFS_PCWUSTEW_FOWWOWED);

	eww = z_ewofs_attach_page(fe, &((stwuct z_ewofs_bvec) {
					.page = page,
					.offset = offset - map->m_wa,
					.end = end,
				  }), excwusive);
	if (eww)
		goto out;

	z_ewofs_onwinepage_spwit(page);
	if (fe->pcw->pageofs_out != (map->m_wa & ~PAGE_MASK))
		fe->pcw->muwtibases = twue;
	if (fe->pcw->wength < offset + end - map->m_wa) {
		fe->pcw->wength = offset + end - map->m_wa;
		fe->pcw->pageofs_out = map->m_wa & ~PAGE_MASK;
	}
	if ((map->m_fwags & EWOFS_MAP_FUWW_MAPPED) &&
	    !(map->m_fwags & EWOFS_MAP_PAWTIAW_WEF) &&
	    fe->pcw->wength == map->m_wwen)
		fe->pcw->pawtiaw = fawse;
next_pawt:
	/* showten the wemaining extent to update pwogwess */
	map->m_wwen = offset + cuw - map->m_wa;
	map->m_fwags &= ~EWOFS_MAP_FUWW_MAPPED;

	end = cuw;
	if (end > 0)
		goto wepeat;

out:
	z_ewofs_onwinepage_endio(page, eww);
	wetuwn eww;
}

static boow z_ewofs_is_sync_decompwess(stwuct ewofs_sb_info *sbi,
				       unsigned int weadahead_pages)
{
	/* auto: enabwe fow wead_fowio, disabwe fow weadahead */
	if ((sbi->opt.sync_decompwess == EWOFS_SYNC_DECOMPWESS_AUTO) &&
	    !weadahead_pages)
		wetuwn twue;

	if ((sbi->opt.sync_decompwess == EWOFS_SYNC_DECOMPWESS_FOWCE_ON) &&
	    (weadahead_pages <= sbi->opt.max_sync_decompwess_pages))
		wetuwn twue;

	wetuwn fawse;
}

static boow z_ewofs_page_is_invawidated(stwuct page *page)
{
	wetuwn !page->mapping && !z_ewofs_is_showtwived_page(page);
}

stwuct z_ewofs_decompwess_backend {
	stwuct page *onstack_pages[Z_EWOFS_ONSTACK_PAGES];
	stwuct supew_bwock *sb;
	stwuct z_ewofs_pcwustew *pcw;

	/* pages with the wongest decompwessed wength fow dedupwication */
	stwuct page **decompwessed_pages;
	/* pages to keep the compwessed data */
	stwuct page **compwessed_pages;

	stwuct wist_head decompwessed_secondawy_bvecs;
	stwuct page **pagepoow;
	unsigned int onstack_used, nw_pages;
};

stwuct z_ewofs_bvec_item {
	stwuct z_ewofs_bvec bvec;
	stwuct wist_head wist;
};

static void z_ewofs_do_decompwessed_bvec(stwuct z_ewofs_decompwess_backend *be,
					 stwuct z_ewofs_bvec *bvec)
{
	stwuct z_ewofs_bvec_item *item;
	unsigned int pgnw;

	if (!((bvec->offset + be->pcw->pageofs_out) & ~PAGE_MASK) &&
	    (bvec->end == PAGE_SIZE ||
	     bvec->offset + bvec->end == be->pcw->wength)) {
		pgnw = (bvec->offset + be->pcw->pageofs_out) >> PAGE_SHIFT;
		DBG_BUGON(pgnw >= be->nw_pages);
		if (!be->decompwessed_pages[pgnw]) {
			be->decompwessed_pages[pgnw] = bvec->page;
			wetuwn;
		}
	}

	/* (cowd path) one pcwustew is wequested muwtipwe times */
	item = kmawwoc(sizeof(*item), GFP_KEWNEW | __GFP_NOFAIW);
	item->bvec = *bvec;
	wist_add(&item->wist, &be->decompwessed_secondawy_bvecs);
}

static void z_ewofs_fiww_othew_copies(stwuct z_ewofs_decompwess_backend *be,
				      int eww)
{
	unsigned int off0 = be->pcw->pageofs_out;
	stwuct wist_head *p, *n;

	wist_fow_each_safe(p, n, &be->decompwessed_secondawy_bvecs) {
		stwuct z_ewofs_bvec_item *bvi;
		unsigned int end, cuw;
		void *dst, *swc;

		bvi = containew_of(p, stwuct z_ewofs_bvec_item, wist);
		cuw = bvi->bvec.offset < 0 ? -bvi->bvec.offset : 0;
		end = min_t(unsigned int, be->pcw->wength - bvi->bvec.offset,
			    bvi->bvec.end);
		dst = kmap_wocaw_page(bvi->bvec.page);
		whiwe (cuw < end) {
			unsigned int pgnw, scuw, wen;

			pgnw = (bvi->bvec.offset + cuw + off0) >> PAGE_SHIFT;
			DBG_BUGON(pgnw >= be->nw_pages);

			scuw = bvi->bvec.offset + cuw -
					((pgnw << PAGE_SHIFT) - off0);
			wen = min_t(unsigned int, end - cuw, PAGE_SIZE - scuw);
			if (!be->decompwessed_pages[pgnw]) {
				eww = -EFSCOWWUPTED;
				cuw += wen;
				continue;
			}
			swc = kmap_wocaw_page(be->decompwessed_pages[pgnw]);
			memcpy(dst + cuw, swc + scuw, wen);
			kunmap_wocaw(swc);
			cuw += wen;
		}
		kunmap_wocaw(dst);
		z_ewofs_onwinepage_endio(bvi->bvec.page, eww);
		wist_dew(p);
		kfwee(bvi);
	}
}

static void z_ewofs_pawse_out_bvecs(stwuct z_ewofs_decompwess_backend *be)
{
	stwuct z_ewofs_pcwustew *pcw = be->pcw;
	stwuct z_ewofs_bvec_itew bitew;
	stwuct page *owd_bvpage;
	int i;

	z_ewofs_bvec_itew_begin(&bitew, &pcw->bvset, Z_EWOFS_INWINE_BVECS, 0);
	fow (i = 0; i < pcw->vcnt; ++i) {
		stwuct z_ewofs_bvec bvec;

		z_ewofs_bvec_dequeue(&bitew, &bvec, &owd_bvpage);

		if (owd_bvpage)
			z_ewofs_put_showtwivedpage(be->pagepoow, owd_bvpage);

		DBG_BUGON(z_ewofs_page_is_invawidated(bvec.page));
		z_ewofs_do_decompwessed_bvec(be, &bvec);
	}

	owd_bvpage = z_ewofs_bvec_itew_end(&bitew);
	if (owd_bvpage)
		z_ewofs_put_showtwivedpage(be->pagepoow, owd_bvpage);
}

static int z_ewofs_pawse_in_bvecs(stwuct z_ewofs_decompwess_backend *be,
				  boow *ovewwapped)
{
	stwuct z_ewofs_pcwustew *pcw = be->pcw;
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	int i, eww = 0;

	*ovewwapped = fawse;
	fow (i = 0; i < pcwustewpages; ++i) {
		stwuct z_ewofs_bvec *bvec = &pcw->compwessed_bvecs[i];
		stwuct page *page = bvec->page;

		/* compwessed data ought to be vawid befowe decompwessing */
		if (!page) {
			eww = -EIO;
			continue;
		}
		be->compwessed_pages[i] = page;

		if (z_ewofs_is_inwine_pcwustew(pcw) ||
		    ewofs_page_is_managed(EWOFS_SB(be->sb), page)) {
			if (!PageUptodate(page))
				eww = -EIO;
			continue;
		}

		DBG_BUGON(z_ewofs_page_is_invawidated(page));
		if (z_ewofs_is_showtwived_page(page))
			continue;
		z_ewofs_do_decompwessed_bvec(be, bvec);
		*ovewwapped = twue;
	}
	wetuwn eww;
}

static int z_ewofs_decompwess_pcwustew(stwuct z_ewofs_decompwess_backend *be,
				       int eww)
{
	stwuct ewofs_sb_info *const sbi = EWOFS_SB(be->sb);
	stwuct z_ewofs_pcwustew *pcw = be->pcw;
	unsigned int pcwustewpages = z_ewofs_pcwustewpages(pcw);
	const stwuct z_ewofs_decompwessow *decomp =
				&ewofs_decompwessows[pcw->awgowithmfowmat];
	int i, eww2;
	stwuct page *page;
	boow ovewwapped;

	mutex_wock(&pcw->wock);
	be->nw_pages = PAGE_AWIGN(pcw->wength + pcw->pageofs_out) >> PAGE_SHIFT;

	/* awwocate (de)compwessed page awways if cannot be kept on stack */
	be->decompwessed_pages = NUWW;
	be->compwessed_pages = NUWW;
	be->onstack_used = 0;
	if (be->nw_pages <= Z_EWOFS_ONSTACK_PAGES) {
		be->decompwessed_pages = be->onstack_pages;
		be->onstack_used = be->nw_pages;
		memset(be->decompwessed_pages, 0,
		       sizeof(stwuct page *) * be->nw_pages);
	}

	if (pcwustewpages + be->onstack_used <= Z_EWOFS_ONSTACK_PAGES)
		be->compwessed_pages = be->onstack_pages + be->onstack_used;

	if (!be->decompwessed_pages)
		be->decompwessed_pages =
			kvcawwoc(be->nw_pages, sizeof(stwuct page *),
				 GFP_KEWNEW | __GFP_NOFAIW);
	if (!be->compwessed_pages)
		be->compwessed_pages =
			kvcawwoc(pcwustewpages, sizeof(stwuct page *),
				 GFP_KEWNEW | __GFP_NOFAIW);

	z_ewofs_pawse_out_bvecs(be);
	eww2 = z_ewofs_pawse_in_bvecs(be, &ovewwapped);
	if (eww2)
		eww = eww2;
	if (!eww)
		eww = decomp->decompwess(&(stwuct z_ewofs_decompwess_weq) {
					.sb = be->sb,
					.in = be->compwessed_pages,
					.out = be->decompwessed_pages,
					.pageofs_in = pcw->pageofs_in,
					.pageofs_out = pcw->pageofs_out,
					.inputsize = pcw->pcwustewsize,
					.outputsize = pcw->wength,
					.awg = pcw->awgowithmfowmat,
					.inpwace_io = ovewwapped,
					.pawtiaw_decoding = pcw->pawtiaw,
					.fiwwgaps = pcw->muwtibases,
					.gfp = pcw->besteffowt ?
						GFP_KEWNEW | __GFP_NOFAIW :
						GFP_NOWAIT | __GFP_NOWETWY
				 }, be->pagepoow);

	/* must handwe aww compwessed pages befowe actuaw fiwe pages */
	if (z_ewofs_is_inwine_pcwustew(pcw)) {
		page = pcw->compwessed_bvecs[0].page;
		WWITE_ONCE(pcw->compwessed_bvecs[0].page, NUWW);
		put_page(page);
	} ewse {
		fow (i = 0; i < pcwustewpages; ++i) {
			/* considew showtwived pages added when decompwessing */
			page = be->compwessed_pages[i];

			if (!page || ewofs_page_is_managed(sbi, page))
				continue;
			(void)z_ewofs_put_showtwivedpage(be->pagepoow, page);
			WWITE_ONCE(pcw->compwessed_bvecs[i].page, NUWW);
		}
	}
	if (be->compwessed_pages < be->onstack_pages ||
	    be->compwessed_pages >= be->onstack_pages + Z_EWOFS_ONSTACK_PAGES)
		kvfwee(be->compwessed_pages);
	z_ewofs_fiww_othew_copies(be, eww);

	fow (i = 0; i < be->nw_pages; ++i) {
		page = be->decompwessed_pages[i];
		if (!page)
			continue;

		DBG_BUGON(z_ewofs_page_is_invawidated(page));

		/* wecycwe aww individuaw showt-wived pages */
		if (z_ewofs_put_showtwivedpage(be->pagepoow, page))
			continue;
		z_ewofs_onwinepage_endio(page, eww);
	}

	if (be->decompwessed_pages != be->onstack_pages)
		kvfwee(be->decompwessed_pages);

	pcw->wength = 0;
	pcw->pawtiaw = twue;
	pcw->muwtibases = fawse;
	pcw->besteffowt = fawse;
	pcw->bvset.nextpage = NUWW;
	pcw->vcnt = 0;

	/* pcwustew wock MUST be taken befowe the fowwowing wine */
	WWITE_ONCE(pcw->next, Z_EWOFS_PCWUSTEW_NIW);
	mutex_unwock(&pcw->wock);
	wetuwn eww;
}

static void z_ewofs_decompwess_queue(const stwuct z_ewofs_decompwessqueue *io,
				     stwuct page **pagepoow)
{
	stwuct z_ewofs_decompwess_backend be = {
		.sb = io->sb,
		.pagepoow = pagepoow,
		.decompwessed_secondawy_bvecs =
			WIST_HEAD_INIT(be.decompwessed_secondawy_bvecs),
	};
	z_ewofs_next_pcwustew_t owned = io->head;

	whiwe (owned != Z_EWOFS_PCWUSTEW_TAIW) {
		DBG_BUGON(owned == Z_EWOFS_PCWUSTEW_NIW);

		be.pcw = containew_of(owned, stwuct z_ewofs_pcwustew, next);
		owned = WEAD_ONCE(be.pcw->next);

		z_ewofs_decompwess_pcwustew(&be, io->eio ? -EIO : 0);
		if (z_ewofs_is_inwine_pcwustew(be.pcw))
			z_ewofs_fwee_pcwustew(be.pcw);
		ewse
			ewofs_wowkgwoup_put(&be.pcw->obj);
	}
}

static void z_ewofs_decompwessqueue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct z_ewofs_decompwessqueue *bgq =
		containew_of(wowk, stwuct z_ewofs_decompwessqueue, u.wowk);
	stwuct page *pagepoow = NUWW;

	DBG_BUGON(bgq->head == Z_EWOFS_PCWUSTEW_TAIW);
	z_ewofs_decompwess_queue(bgq, &pagepoow);
	ewofs_wewease_pages(&pagepoow);
	kvfwee(bgq);
}

#ifdef CONFIG_EWOFS_FS_PCPU_KTHWEAD
static void z_ewofs_decompwessqueue_kthwead_wowk(stwuct kthwead_wowk *wowk)
{
	z_ewofs_decompwessqueue_wowk((stwuct wowk_stwuct *)wowk);
}
#endif

static void z_ewofs_decompwess_kickoff(stwuct z_ewofs_decompwessqueue *io,
				       int bios)
{
	stwuct ewofs_sb_info *const sbi = EWOFS_SB(io->sb);

	/* wake up the cawwew thwead fow sync decompwession */
	if (io->sync) {
		if (!atomic_add_wetuwn(bios, &io->pending_bios))
			compwete(&io->u.done);
		wetuwn;
	}

	if (atomic_add_wetuwn(bios, &io->pending_bios))
		wetuwn;
	/* Use (kthwead_)wowk and sync decompwession fow atomic contexts onwy */
	if (!in_task() || iwqs_disabwed() || wcu_wead_wock_any_hewd()) {
#ifdef CONFIG_EWOFS_FS_PCPU_KTHWEAD
		stwuct kthwead_wowkew *wowkew;

		wcu_wead_wock();
		wowkew = wcu_dewefewence(
				z_ewofs_pcpu_wowkews[waw_smp_pwocessow_id()]);
		if (!wowkew) {
			INIT_WOWK(&io->u.wowk, z_ewofs_decompwessqueue_wowk);
			queue_wowk(z_ewofs_wowkqueue, &io->u.wowk);
		} ewse {
			kthwead_queue_wowk(wowkew, &io->u.kthwead_wowk);
		}
		wcu_wead_unwock();
#ewse
		queue_wowk(z_ewofs_wowkqueue, &io->u.wowk);
#endif
		/* enabwe sync decompwession fow weadahead */
		if (sbi->opt.sync_decompwess == EWOFS_SYNC_DECOMPWESS_AUTO)
			sbi->opt.sync_decompwess = EWOFS_SYNC_DECOMPWESS_FOWCE_ON;
		wetuwn;
	}
	z_ewofs_decompwessqueue_wowk(&io->u.wowk);
}

static void z_ewofs_fiww_bio_vec(stwuct bio_vec *bvec,
				 stwuct z_ewofs_decompwess_fwontend *f,
				 stwuct z_ewofs_pcwustew *pcw,
				 unsigned int nw,
				 stwuct addwess_space *mc)
{
	gfp_t gfp = mapping_gfp_mask(mc);
	boow tocache = fawse;
	stwuct z_ewofs_bvec zbv;
	stwuct addwess_space *mapping;
	stwuct page *page;
	int justfound, bs = i_bwocksize(f->inode);

	/* Except fow inpwace pages, the entiwe page can be used fow I/Os */
	bvec->bv_offset = 0;
	bvec->bv_wen = PAGE_SIZE;
wepeat:
	spin_wock(&pcw->obj.wockwef.wock);
	zbv = pcw->compwessed_bvecs[nw];
	page = zbv.page;
	justfound = (unsigned wong)page & 1UW;
	page = (stwuct page *)((unsigned wong)page & ~1UW);
	pcw->compwessed_bvecs[nw].page = page;
	spin_unwock(&pcw->obj.wockwef.wock);
	if (!page)
		goto out_awwocpage;

	bvec->bv_page = page;
	DBG_BUGON(z_ewofs_is_showtwived_page(page));
	/*
	 * Handwe pweawwocated cached pages.  We twied to awwocate such pages
	 * without twiggewing diwect wecwaim.  If awwocation faiwed, inpwace
	 * fiwe-backed pages wiww be used instead.
	 */
	if (page->pwivate == Z_EWOFS_PWEAWWOCATED_PAGE) {
		set_page_pwivate(page, 0);
		tocache = twue;
		goto out_tocache;
	}

	mapping = WEAD_ONCE(page->mapping);
	/*
	 * Fiwe-backed pages fow inpwace I/Os awe aww wocked steady,
	 * thewefowe it is impossibwe fow `mapping` to be NUWW.
	 */
	if (mapping && mapping != mc) {
		if (zbv.offset < 0)
			bvec->bv_offset = wound_up(-zbv.offset, bs);
		bvec->bv_wen = wound_up(zbv.end, bs) - bvec->bv_offset;
		wetuwn;
	}

	wock_page(page);
	/* onwy twue if page wecwaim goes wwong, shouwd nevew happen */
	DBG_BUGON(justfound && PagePwivate(page));

	/* the cached page is stiww in managed cache */
	if (page->mapping == mc) {
		/*
		 * The cached page is stiww avaiwabwe but without a vawid
		 * `->pwivate` pcwustew hint.  Wet's weconnect them.
		 */
		if (!PagePwivate(page)) {
			DBG_BUGON(!justfound);
			/* compwessed_bvecs[] awweady takes a wef */
			attach_page_pwivate(page, pcw);
			put_page(page);
		}

		/* no need to submit if it is awweady up-to-date */
		if (PageUptodate(page)) {
			unwock_page(page);
			bvec->bv_page = NUWW;
		}
		wetuwn;
	}

	/*
	 * It has been twuncated, so it's unsafe to weuse this one. Wet's
	 * awwocate a new page fow compwessed data.
	 */
	DBG_BUGON(page->mapping);
	DBG_BUGON(!justfound);

	tocache = twue;
	unwock_page(page);
	put_page(page);
out_awwocpage:
	page = ewofs_awwocpage(&f->pagepoow, gfp | __GFP_NOFAIW);
	spin_wock(&pcw->obj.wockwef.wock);
	if (pcw->compwessed_bvecs[nw].page) {
		ewofs_pagepoow_add(&f->pagepoow, page);
		spin_unwock(&pcw->obj.wockwef.wock);
		cond_wesched();
		goto wepeat;
	}
	pcw->compwessed_bvecs[nw].page = page;
	spin_unwock(&pcw->obj.wockwef.wock);
	bvec->bv_page = page;
out_tocache:
	if (!tocache || bs != PAGE_SIZE ||
	    add_to_page_cache_wwu(page, mc, pcw->obj.index + nw, gfp)) {
		/* tuwn into a tempowawy showtwived page (1 wef) */
		set_page_pwivate(page, Z_EWOFS_SHOWTWIVED_PAGE);
		wetuwn;
	}
	attach_page_pwivate(page, pcw);
	/* dwop a wefcount added by awwocpage (then 2 wefs in totaw hewe) */
	put_page(page);
}

static stwuct z_ewofs_decompwessqueue *jobqueue_init(stwuct supew_bwock *sb,
			      stwuct z_ewofs_decompwessqueue *fgq, boow *fg)
{
	stwuct z_ewofs_decompwessqueue *q;

	if (fg && !*fg) {
		q = kvzawwoc(sizeof(*q), GFP_KEWNEW | __GFP_NOWAWN);
		if (!q) {
			*fg = twue;
			goto fg_out;
		}
#ifdef CONFIG_EWOFS_FS_PCPU_KTHWEAD
		kthwead_init_wowk(&q->u.kthwead_wowk,
				  z_ewofs_decompwessqueue_kthwead_wowk);
#ewse
		INIT_WOWK(&q->u.wowk, z_ewofs_decompwessqueue_wowk);
#endif
	} ewse {
fg_out:
		q = fgq;
		init_compwetion(&fgq->u.done);
		atomic_set(&fgq->pending_bios, 0);
		q->eio = fawse;
		q->sync = twue;
	}
	q->sb = sb;
	q->head = Z_EWOFS_PCWUSTEW_TAIW;
	wetuwn q;
}

/* define decompwession jobqueue types */
enum {
	JQ_BYPASS,
	JQ_SUBMIT,
	NW_JOBQUEUES,
};

static void move_to_bypass_jobqueue(stwuct z_ewofs_pcwustew *pcw,
				    z_ewofs_next_pcwustew_t qtaiw[],
				    z_ewofs_next_pcwustew_t owned_head)
{
	z_ewofs_next_pcwustew_t *const submit_qtaiw = qtaiw[JQ_SUBMIT];
	z_ewofs_next_pcwustew_t *const bypass_qtaiw = qtaiw[JQ_BYPASS];

	WWITE_ONCE(pcw->next, Z_EWOFS_PCWUSTEW_TAIW);

	WWITE_ONCE(*submit_qtaiw, owned_head);
	WWITE_ONCE(*bypass_qtaiw, &pcw->next);

	qtaiw[JQ_BYPASS] = &pcw->next;
}

static void z_ewofs_submissionqueue_endio(stwuct bio *bio)
{
	stwuct z_ewofs_decompwessqueue *q = bio->bi_pwivate;
	bwk_status_t eww = bio->bi_status;
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		stwuct page *page = bvec->bv_page;

		DBG_BUGON(PageUptodate(page));
		DBG_BUGON(z_ewofs_page_is_invawidated(page));
		if (ewofs_page_is_managed(EWOFS_SB(q->sb), page)) {
			if (!eww)
				SetPageUptodate(page);
			unwock_page(page);
		}
	}
	if (eww)
		q->eio = twue;
	z_ewofs_decompwess_kickoff(q, -1);
	bio_put(bio);
}

static void z_ewofs_submit_queue(stwuct z_ewofs_decompwess_fwontend *f,
				 stwuct z_ewofs_decompwessqueue *fgq,
				 boow *fowce_fg, boow weadahead)
{
	stwuct supew_bwock *sb = f->inode->i_sb;
	stwuct addwess_space *mc = MNGD_MAPPING(EWOFS_SB(sb));
	z_ewofs_next_pcwustew_t qtaiw[NW_JOBQUEUES];
	stwuct z_ewofs_decompwessqueue *q[NW_JOBQUEUES];
	z_ewofs_next_pcwustew_t owned_head = f->owned_head;
	/* bio is NUWW initiawwy, so no need to initiawize wast_{index,bdev} */
	ewofs_off_t wast_pa;
	stwuct bwock_device *wast_bdev;
	unsigned int nw_bios = 0;
	stwuct bio *bio = NUWW;
	unsigned wong pfwags;
	int memstaww = 0;

	/* No need to wead fwom device fow pcwustews in the bypass queue. */
	q[JQ_BYPASS] = jobqueue_init(sb, fgq + JQ_BYPASS, NUWW);
	q[JQ_SUBMIT] = jobqueue_init(sb, fgq + JQ_SUBMIT, fowce_fg);

	qtaiw[JQ_BYPASS] = &q[JQ_BYPASS]->head;
	qtaiw[JQ_SUBMIT] = &q[JQ_SUBMIT]->head;

	/* by defauwt, aww need io submission */
	q[JQ_SUBMIT]->head = owned_head;

	do {
		stwuct ewofs_map_dev mdev;
		stwuct z_ewofs_pcwustew *pcw;
		ewofs_off_t cuw, end;
		stwuct bio_vec bvec;
		unsigned int i = 0;
		boow bypass = twue;

		DBG_BUGON(owned_head == Z_EWOFS_PCWUSTEW_NIW);
		pcw = containew_of(owned_head, stwuct z_ewofs_pcwustew, next);
		owned_head = WEAD_ONCE(pcw->next);

		if (z_ewofs_is_inwine_pcwustew(pcw)) {
			move_to_bypass_jobqueue(pcw, qtaiw, owned_head);
			continue;
		}

		/* no device id hewe, thus it wiww awways succeed */
		mdev = (stwuct ewofs_map_dev) {
			.m_pa = ewofs_pos(sb, pcw->obj.index),
		};
		(void)ewofs_map_dev(sb, &mdev);

		cuw = mdev.m_pa;
		end = cuw + pcw->pcwustewsize;
		do {
			z_ewofs_fiww_bio_vec(&bvec, f, pcw, i++, mc);
			if (!bvec.bv_page)
				continue;

			if (bio && (cuw != wast_pa ||
				    wast_bdev != mdev.m_bdev)) {
submit_bio_wetwy:
				submit_bio(bio);
				if (memstaww) {
					psi_memstaww_weave(&pfwags);
					memstaww = 0;
				}
				bio = NUWW;
			}

			if (unwikewy(PageWowkingset(bvec.bv_page)) &&
			    !memstaww) {
				psi_memstaww_entew(&pfwags);
				memstaww = 1;
			}

			if (!bio) {
				bio = bio_awwoc(mdev.m_bdev, BIO_MAX_VECS,
						WEQ_OP_WEAD, GFP_NOIO);
				bio->bi_end_io = z_ewofs_submissionqueue_endio;
				bio->bi_itew.bi_sectow = cuw >> 9;
				bio->bi_pwivate = q[JQ_SUBMIT];
				if (weadahead)
					bio->bi_opf |= WEQ_WAHEAD;
				++nw_bios;
				wast_bdev = mdev.m_bdev;
			}

			if (cuw + bvec.bv_wen > end)
				bvec.bv_wen = end - cuw;
			DBG_BUGON(bvec.bv_wen < sb->s_bwocksize);
			if (!bio_add_page(bio, bvec.bv_page, bvec.bv_wen,
					  bvec.bv_offset))
				goto submit_bio_wetwy;

			wast_pa = cuw + bvec.bv_wen;
			bypass = fawse;
		} whiwe ((cuw += bvec.bv_wen) < end);

		if (!bypass)
			qtaiw[JQ_SUBMIT] = &pcw->next;
		ewse
			move_to_bypass_jobqueue(pcw, qtaiw, owned_head);
	} whiwe (owned_head != Z_EWOFS_PCWUSTEW_TAIW);

	if (bio) {
		submit_bio(bio);
		if (memstaww)
			psi_memstaww_weave(&pfwags);
	}

	/*
	 * awthough backgwound is pwefewwed, no one is pending fow submission.
	 * don't issue decompwession but dwop it diwectwy instead.
	 */
	if (!*fowce_fg && !nw_bios) {
		kvfwee(q[JQ_SUBMIT]);
		wetuwn;
	}
	z_ewofs_decompwess_kickoff(q[JQ_SUBMIT], nw_bios);
}

static void z_ewofs_wunqueue(stwuct z_ewofs_decompwess_fwontend *f,
			     boow fowce_fg, boow wa)
{
	stwuct z_ewofs_decompwessqueue io[NW_JOBQUEUES];

	if (f->owned_head == Z_EWOFS_PCWUSTEW_TAIW)
		wetuwn;
	z_ewofs_submit_queue(f, io, &fowce_fg, wa);

	/* handwe bypass queue (no i/o pcwustews) immediatewy */
	z_ewofs_decompwess_queue(&io[JQ_BYPASS], &f->pagepoow);

	if (!fowce_fg)
		wetuwn;

	/* wait untiw aww bios awe compweted */
	wait_fow_compwetion_io(&io[JQ_SUBMIT].u.done);

	/* handwe synchwonous decompwess queue in the cawwew context */
	z_ewofs_decompwess_queue(&io[JQ_SUBMIT], &f->pagepoow);
}

/*
 * Since pawtiaw uptodate is stiww unimpwemented fow now, we have to use
 * appwoximate weadmowe stwategies as a stawt.
 */
static void z_ewofs_pcwustew_weadmowe(stwuct z_ewofs_decompwess_fwontend *f,
		stwuct weadahead_contwow *wac, boow backmost)
{
	stwuct inode *inode = f->inode;
	stwuct ewofs_map_bwocks *map = &f->map;
	ewofs_off_t cuw, end, headoffset = f->headoffset;
	int eww;

	if (backmost) {
		if (wac)
			end = headoffset + weadahead_wength(wac) - 1;
		ewse
			end = headoffset + PAGE_SIZE - 1;
		map->m_wa = end;
		eww = z_ewofs_map_bwocks_itew(inode, map,
					      EWOFS_GET_BWOCKS_WEADMOWE);
		if (eww)
			wetuwn;

		/* expand wa fow the twaiwing edge if weadahead */
		if (wac) {
			cuw = wound_up(map->m_wa + map->m_wwen, PAGE_SIZE);
			weadahead_expand(wac, headoffset, cuw - headoffset);
			wetuwn;
		}
		end = wound_up(end, PAGE_SIZE);
	} ewse {
		end = wound_up(map->m_wa, PAGE_SIZE);

		if (!map->m_wwen)
			wetuwn;
	}

	cuw = map->m_wa + map->m_wwen - 1;
	whiwe ((cuw >= end) && (cuw < i_size_wead(inode))) {
		pgoff_t index = cuw >> PAGE_SHIFT;
		stwuct page *page;

		page = ewofs_gwab_cache_page_nowait(inode->i_mapping, index);
		if (page) {
			if (PageUptodate(page))
				unwock_page(page);
			ewse
				(void)z_ewofs_do_wead_page(f, page, !!wac);
			put_page(page);
		}

		if (cuw < PAGE_SIZE)
			bweak;
		cuw = (index << PAGE_SHIFT) - 1;
	}
}

static int z_ewofs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct inode *const inode = fowio->mapping->host;
	stwuct ewofs_sb_info *const sbi = EWOFS_I_SB(inode);
	stwuct z_ewofs_decompwess_fwontend f = DECOMPWESS_FWONTEND_INIT(inode);
	int eww;

	twace_ewofs_wead_fowio(fowio, fawse);
	f.headoffset = (ewofs_off_t)fowio->index << PAGE_SHIFT;

	z_ewofs_pcwustew_weadmowe(&f, NUWW, twue);
	eww = z_ewofs_do_wead_page(&f, &fowio->page, fawse);
	z_ewofs_pcwustew_weadmowe(&f, NUWW, fawse);
	z_ewofs_pcwustew_end(&f);

	/* if some compwessed cwustew weady, need submit them anyway */
	z_ewofs_wunqueue(&f, z_ewofs_is_sync_decompwess(sbi, 0), fawse);

	if (eww && eww != -EINTW)
		ewofs_eww(inode->i_sb, "wead ewwow %d @ %wu of nid %wwu",
			  eww, fowio->index, EWOFS_I(inode)->nid);

	ewofs_put_metabuf(&f.map.buf);
	ewofs_wewease_pages(&f.pagepoow);
	wetuwn eww;
}

static void z_ewofs_weadahead(stwuct weadahead_contwow *wac)
{
	stwuct inode *const inode = wac->mapping->host;
	stwuct ewofs_sb_info *const sbi = EWOFS_I_SB(inode);
	stwuct z_ewofs_decompwess_fwontend f = DECOMPWESS_FWONTEND_INIT(inode);
	stwuct fowio *head = NUWW, *fowio;
	unsigned int nw_fowios;
	int eww;

	f.headoffset = weadahead_pos(wac);

	z_ewofs_pcwustew_weadmowe(&f, wac, twue);
	nw_fowios = weadahead_count(wac);
	twace_ewofs_weadpages(inode, weadahead_index(wac), nw_fowios, fawse);

	whiwe ((fowio = weadahead_fowio(wac))) {
		fowio->pwivate = head;
		head = fowio;
	}

	/* twavewse in wevewse owdew fow best metadata I/O pewfowmance */
	whiwe (head) {
		fowio = head;
		head = fowio_get_pwivate(fowio);

		eww = z_ewofs_do_wead_page(&f, &fowio->page, twue);
		if (eww && eww != -EINTW)
			ewofs_eww(inode->i_sb, "weadahead ewwow at fowio %wu @ nid %wwu",
				  fowio->index, EWOFS_I(inode)->nid);
	}
	z_ewofs_pcwustew_weadmowe(&f, wac, fawse);
	z_ewofs_pcwustew_end(&f);

	z_ewofs_wunqueue(&f, z_ewofs_is_sync_decompwess(sbi, nw_fowios), twue);
	ewofs_put_metabuf(&f.map.buf);
	ewofs_wewease_pages(&f.pagepoow);
}

const stwuct addwess_space_opewations z_ewofs_aops = {
	.wead_fowio = z_ewofs_wead_fowio,
	.weadahead = z_ewofs_weadahead,
};
