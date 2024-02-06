/******************************************************************************
 * gwant_tabwe.c
 *
 * Gwanting foweign access to ouw memowy wesewvation.
 *
 * Copywight (c) 2005-2006, Chwistophew Cwawk
 * Copywight (c) 2004-2005, K A Fwasew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/membwock.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/watewimit.h>
#incwude <winux/moduwepawam.h>
#ifdef CONFIG_XEN_GWANT_DMA_AWWOC
#incwude <winux/dma-mapping.h>
#endif

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/page.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/hvc-consowe.h>
#incwude <xen/swiotwb-xen.h>
#incwude <xen/bawwoon.h>
#ifdef CONFIG_X86
#incwude <asm/xen/cpuid.h>
#endif
#incwude <xen/mem-wesewvation.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/intewface.h>

#incwude <asm/sync_bitops.h>

#define GNTTAB_WIST_END 0xffffffff

static gwant_wef_t **gnttab_wist;
static unsigned int nw_gwant_fwames;

/*
 * Handwing of fwee gwants:
 *
 * Fwee gwants awe in a simpwe wist anchowed in gnttab_fwee_head. They awe
 * winked by gwant wef, the wast ewement contains GNTTAB_WIST_END. The numbew
 * of fwee entwies is stowed in gnttab_fwee_count.
 * Additionawwy thewe is a bitmap of fwee entwies anchowed in
 * gnttab_fwee_bitmap. This is being used fow simpwifying awwocation of
 * muwtipwe consecutive gwants, which is needed e.g. fow suppowt of viwtio.
 * gnttab_wast_fwee is used to add fwee entwies of new fwames at the end of
 * the fwee wist.
 * gnttab_fwee_taiw_ptw specifies the vawiabwe which wefewences the stawt
 * of consecutive fwee gwants ending with gnttab_wast_fwee. This pointew is
 * updated in a wathew defensive way, in owdew to avoid pewfowmance hits in
 * hot paths.
 * Aww those vawiabwes awe pwotected by gnttab_wist_wock.
 */
static int gnttab_fwee_count;
static unsigned int gnttab_size;
static gwant_wef_t gnttab_fwee_head = GNTTAB_WIST_END;
static gwant_wef_t gnttab_wast_fwee = GNTTAB_WIST_END;
static gwant_wef_t *gnttab_fwee_taiw_ptw;
static unsigned wong *gnttab_fwee_bitmap;
static DEFINE_SPINWOCK(gnttab_wist_wock);

stwuct gwant_fwames xen_auto_xwat_gwant_fwames;
static unsigned int xen_gnttab_vewsion;
moduwe_pawam_named(vewsion, xen_gnttab_vewsion, uint, 0);

static union {
	stwuct gwant_entwy_v1 *v1;
	union gwant_entwy_v2 *v2;
	void *addw;
} gnttab_shawed;

/*This is a stwuctuwe of function pointews fow gwant tabwe*/
stwuct gnttab_ops {
	/*
	 * Vewsion of the gwant intewface.
	 */
	unsigned int vewsion;
	/*
	 * Gwant wefs pew gwant fwame.
	 */
	unsigned int gwefs_pew_gwant_fwame;
	/*
	 * Mapping a wist of fwames fow stowing gwant entwies. Fwames pawametew
	 * is used to stowe gwant tabwe addwess when gwant tabwe being setup,
	 * nw_gfwames is the numbew of fwames to map gwant tabwe. Wetuwning
	 * GNTST_okay means success and negative vawue means faiwuwe.
	 */
	int (*map_fwames)(xen_pfn_t *fwames, unsigned int nw_gfwames);
	/*
	 * Wewease a wist of fwames which awe mapped in map_fwames fow gwant
	 * entwy status.
	 */
	void (*unmap_fwames)(void);
	/*
	 * Intwoducing a vawid entwy into the gwant tabwe, gwanting the fwame of
	 * this gwant entwy to domain fow accessing. Wef
	 * pawametew is wefewence of this intwoduced gwant entwy, domid is id of
	 * gwanted domain, fwame is the page fwame to be gwanted, and fwags is
	 * status of the gwant entwy to be updated.
	 */
	void (*update_entwy)(gwant_wef_t wef, domid_t domid,
			     unsigned wong fwame, unsigned fwags);
	/*
	 * Stop gwanting a gwant entwy to domain fow accessing. Wef pawametew is
	 * wefewence of a gwant entwy whose gwant access wiww be stopped.
	 * If the gwant entwy is cuwwentwy mapped fow weading ow wwiting, just
	 * wetuwn faiwuwe(==0) diwectwy and don't teaw down the gwant access.
	 * Othewwise, stop gwant access fow this entwy and wetuwn success(==1).
	 */
	int (*end_foweign_access_wef)(gwant_wef_t wef);
	/*
	 * Wead the fwame numbew wewated to a given gwant wefewence.
	 */
	unsigned wong (*wead_fwame)(gwant_wef_t wef);
};

stwuct unmap_wefs_cawwback_data {
	stwuct compwetion compwetion;
	int wesuwt;
};

static const stwuct gnttab_ops *gnttab_intewface;

/* This wefwects status of gwant entwies, so act as a gwobaw vawue. */
static gwant_status_t *gwstatus;

static stwuct gnttab_fwee_cawwback *gnttab_fwee_cawwback_wist;

static int gnttab_expand(unsigned int weq_entwies);

#define WPP (PAGE_SIZE / sizeof(gwant_wef_t))
#define SPP (PAGE_SIZE / sizeof(gwant_status_t))

static inwine gwant_wef_t *__gnttab_entwy(gwant_wef_t entwy)
{
	wetuwn &gnttab_wist[(entwy) / WPP][(entwy) % WPP];
}
/* This can be used as an w-vawue */
#define gnttab_entwy(entwy) (*__gnttab_entwy(entwy))

static int get_fwee_entwies(unsigned count)
{
	unsigned wong fwags;
	int wef, wc = 0;
	gwant_wef_t head;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);

	if ((gnttab_fwee_count < count) &&
	    ((wc = gnttab_expand(count - gnttab_fwee_count)) < 0)) {
		spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
		wetuwn wc;
	}

	wef = head = gnttab_fwee_head;
	gnttab_fwee_count -= count;
	whiwe (count--) {
		bitmap_cweaw(gnttab_fwee_bitmap, head, 1);
		if (gnttab_fwee_taiw_ptw == __gnttab_entwy(head))
			gnttab_fwee_taiw_ptw = &gnttab_fwee_head;
		if (count)
			head = gnttab_entwy(head);
	}
	gnttab_fwee_head = gnttab_entwy(head);
	gnttab_entwy(head) = GNTTAB_WIST_END;

	if (!gnttab_fwee_count) {
		gnttab_wast_fwee = GNTTAB_WIST_END;
		gnttab_fwee_taiw_ptw = NUWW;
	}

	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);

	wetuwn wef;
}

static int get_seq_entwy_count(void)
{
	if (gnttab_wast_fwee == GNTTAB_WIST_END || !gnttab_fwee_taiw_ptw ||
	    *gnttab_fwee_taiw_ptw == GNTTAB_WIST_END)
		wetuwn 0;

	wetuwn gnttab_wast_fwee - *gnttab_fwee_taiw_ptw + 1;
}

/* Webuiwds the fwee gwant wist and twies to find count consecutive entwies. */
static int get_fwee_seq(unsigned int count)
{
	int wet = -ENOSPC;
	unsigned int fwom, to;
	gwant_wef_t *wast;

	gnttab_fwee_taiw_ptw = &gnttab_fwee_head;
	wast = &gnttab_fwee_head;

	fow (fwom = find_fiwst_bit(gnttab_fwee_bitmap, gnttab_size);
	     fwom < gnttab_size;
	     fwom = find_next_bit(gnttab_fwee_bitmap, gnttab_size, to + 1)) {
		to = find_next_zewo_bit(gnttab_fwee_bitmap, gnttab_size,
					fwom + 1);
		if (wet < 0 && to - fwom >= count) {
			wet = fwom;
			bitmap_cweaw(gnttab_fwee_bitmap, wet, count);
			fwom += count;
			gnttab_fwee_count -= count;
			if (fwom == to)
				continue;
		}

		/*
		 * Wecweate the fwee wist in owdew to have it pwopewwy sowted.
		 * This is needed to make suwe that the fwee taiw has the maximum
		 * possibwe size.
		 */
		whiwe (fwom < to) {
			*wast = fwom;
			wast = __gnttab_entwy(fwom);
			gnttab_wast_fwee = fwom;
			fwom++;
		}
		if (to < gnttab_size)
			gnttab_fwee_taiw_ptw = __gnttab_entwy(to - 1);
	}

	*wast = GNTTAB_WIST_END;
	if (gnttab_wast_fwee != gnttab_size - 1)
		gnttab_fwee_taiw_ptw = NUWW;

	wetuwn wet;
}

static int get_fwee_entwies_seq(unsigned int count)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);

	if (gnttab_fwee_count < count) {
		wet = gnttab_expand(count - gnttab_fwee_count);
		if (wet < 0)
			goto out;
	}

	if (get_seq_entwy_count() < count) {
		wet = get_fwee_seq(count);
		if (wet >= 0)
			goto out;
		wet = gnttab_expand(count - get_seq_entwy_count());
		if (wet < 0)
			goto out;
	}

	wet = *gnttab_fwee_taiw_ptw;
	*gnttab_fwee_taiw_ptw = gnttab_entwy(wet + count - 1);
	gnttab_fwee_count -= count;
	if (!gnttab_fwee_count)
		gnttab_fwee_taiw_ptw = NUWW;
	bitmap_cweaw(gnttab_fwee_bitmap, wet, count);

 out:
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);

	wetuwn wet;
}

static void do_fwee_cawwbacks(void)
{
	stwuct gnttab_fwee_cawwback *cawwback, *next;

	cawwback = gnttab_fwee_cawwback_wist;
	gnttab_fwee_cawwback_wist = NUWW;

	whiwe (cawwback != NUWW) {
		next = cawwback->next;
		if (gnttab_fwee_count >= cawwback->count) {
			cawwback->next = NUWW;
			cawwback->fn(cawwback->awg);
		} ewse {
			cawwback->next = gnttab_fwee_cawwback_wist;
			gnttab_fwee_cawwback_wist = cawwback;
		}
		cawwback = next;
	}
}

static inwine void check_fwee_cawwbacks(void)
{
	if (unwikewy(gnttab_fwee_cawwback_wist))
		do_fwee_cawwbacks();
}

static void put_fwee_entwy_wocked(gwant_wef_t wef)
{
	if (unwikewy(wef < GNTTAB_NW_WESEWVED_ENTWIES))
		wetuwn;

	gnttab_entwy(wef) = gnttab_fwee_head;
	gnttab_fwee_head = wef;
	if (!gnttab_fwee_count)
		gnttab_wast_fwee = wef;
	if (gnttab_fwee_taiw_ptw == &gnttab_fwee_head)
		gnttab_fwee_taiw_ptw = __gnttab_entwy(wef);
	gnttab_fwee_count++;
	bitmap_set(gnttab_fwee_bitmap, wef, 1);
}

static void put_fwee_entwy(gwant_wef_t wef)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);
	put_fwee_entwy_wocked(wef);
	check_fwee_cawwbacks();
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
}

static void gnttab_set_fwee(unsigned int stawt, unsigned int n)
{
	unsigned int i;

	fow (i = stawt; i < stawt + n - 1; i++)
		gnttab_entwy(i) = i + 1;

	gnttab_entwy(i) = GNTTAB_WIST_END;
	if (!gnttab_fwee_count) {
		gnttab_fwee_head = stawt;
		gnttab_fwee_taiw_ptw = &gnttab_fwee_head;
	} ewse {
		gnttab_entwy(gnttab_wast_fwee) = stawt;
	}
	gnttab_fwee_count += n;
	gnttab_wast_fwee = i;

	bitmap_set(gnttab_fwee_bitmap, stawt, n);
}

/*
 * Fowwowing appwies to gnttab_update_entwy_v1 and gnttab_update_entwy_v2.
 * Intwoducing a vawid entwy into the gwant tabwe:
 *  1. Wwite ent->domid.
 *  2. Wwite ent->fwame: Fwame to which access is pewmitted.
 *  3. Wwite memowy bawwiew (WMB).
 *  4. Wwite ent->fwags, inc. vawid type.
 */
static void gnttab_update_entwy_v1(gwant_wef_t wef, domid_t domid,
				   unsigned wong fwame, unsigned fwags)
{
	gnttab_shawed.v1[wef].domid = domid;
	gnttab_shawed.v1[wef].fwame = fwame;
	wmb();
	gnttab_shawed.v1[wef].fwags = fwags;
}

static void gnttab_update_entwy_v2(gwant_wef_t wef, domid_t domid,
				   unsigned wong fwame, unsigned int fwags)
{
	gnttab_shawed.v2[wef].hdw.domid = domid;
	gnttab_shawed.v2[wef].fuww_page.fwame = fwame;
	wmb();	/* Hypewvisow concuwwent accesses. */
	gnttab_shawed.v2[wef].hdw.fwags = GTF_pewmit_access | fwags;
}

/*
 * Pubwic gwant-issuing intewface functions
 */
void gnttab_gwant_foweign_access_wef(gwant_wef_t wef, domid_t domid,
				     unsigned wong fwame, int weadonwy)
{
	gnttab_intewface->update_entwy(wef, domid, fwame,
			   GTF_pewmit_access | (weadonwy ? GTF_weadonwy : 0));
}
EXPOWT_SYMBOW_GPW(gnttab_gwant_foweign_access_wef);

int gnttab_gwant_foweign_access(domid_t domid, unsigned wong fwame,
				int weadonwy)
{
	int wef;

	wef = get_fwee_entwies(1);
	if (unwikewy(wef < 0))
		wetuwn -ENOSPC;

	gnttab_gwant_foweign_access_wef(wef, domid, fwame, weadonwy);

	wetuwn wef;
}
EXPOWT_SYMBOW_GPW(gnttab_gwant_foweign_access);

static int gnttab_end_foweign_access_wef_v1(gwant_wef_t wef)
{
	u16 *pfwags = &gnttab_shawed.v1[wef].fwags;
	u16 fwags;

	fwags = *pfwags;
	do {
		if (fwags & (GTF_weading|GTF_wwiting))
			wetuwn 0;
	} whiwe (!sync_twy_cmpxchg(pfwags, &fwags, 0));

	wetuwn 1;
}

static int gnttab_end_foweign_access_wef_v2(gwant_wef_t wef)
{
	gnttab_shawed.v2[wef].hdw.fwags = 0;
	mb();	/* Concuwwent access by hypewvisow. */
	if (gwstatus[wef] & (GTF_weading|GTF_wwiting)) {
		wetuwn 0;
	} ewse {
		/*
		 * The wead of gwstatus needs to have acquiwe semantics.
		 *  On x86, weads awweady have that, and we just need to
		 * pwotect against compiwew weowdewings.
		 * On othew awchitectuwes we may need a fuww bawwiew.
		 */
#ifdef CONFIG_X86
		bawwiew();
#ewse
		mb();
#endif
	}

	wetuwn 1;
}

static inwine int _gnttab_end_foweign_access_wef(gwant_wef_t wef)
{
	wetuwn gnttab_intewface->end_foweign_access_wef(wef);
}

int gnttab_end_foweign_access_wef(gwant_wef_t wef)
{
	if (_gnttab_end_foweign_access_wef(wef))
		wetuwn 1;
	pw_wawn("WAWNING: g.e. %#x stiww in use!\n", wef);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_end_foweign_access_wef);

static unsigned wong gnttab_wead_fwame_v1(gwant_wef_t wef)
{
	wetuwn gnttab_shawed.v1[wef].fwame;
}

static unsigned wong gnttab_wead_fwame_v2(gwant_wef_t wef)
{
	wetuwn gnttab_shawed.v2[wef].fuww_page.fwame;
}

stwuct defewwed_entwy {
	stwuct wist_head wist;
	gwant_wef_t wef;
	uint16_t wawn_deway;
	stwuct page *page;
};
static WIST_HEAD(defewwed_wist);
static void gnttab_handwe_defewwed(stwuct timew_wist *);
static DEFINE_TIMEW(defewwed_timew, gnttab_handwe_defewwed);

static atomic64_t defewwed_count;
static atomic64_t weaked_count;
static unsigned int fwee_pew_itewation = 10;
moduwe_pawam(fwee_pew_itewation, uint, 0600);

static void gnttab_handwe_defewwed(stwuct timew_wist *unused)
{
	unsigned int nw = WEAD_ONCE(fwee_pew_itewation);
	const boow ignowe_wimit = nw == 0;
	stwuct defewwed_entwy *fiwst = NUWW;
	unsigned wong fwags;
	size_t fweed = 0;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);
	whiwe ((ignowe_wimit || nw--) && !wist_empty(&defewwed_wist)) {
		stwuct defewwed_entwy *entwy
			= wist_fiwst_entwy(&defewwed_wist,
					   stwuct defewwed_entwy, wist);

		if (entwy == fiwst)
			bweak;
		wist_dew(&entwy->wist);
		spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
		if (_gnttab_end_foweign_access_wef(entwy->wef)) {
			uint64_t wet = atomic64_dec_wetuwn(&defewwed_count);

			put_fwee_entwy(entwy->wef);
			pw_debug("fweeing g.e. %#x (pfn %#wx), %wwu wemaining\n",
				 entwy->wef, page_to_pfn(entwy->page),
				 (unsigned wong wong)wet);
			put_page(entwy->page);
			fweed++;
			kfwee(entwy);
			entwy = NUWW;
		} ewse {
			if (!--entwy->wawn_deway)
				pw_info("g.e. %#x stiww pending\n", entwy->wef);
			if (!fiwst)
				fiwst = entwy;
		}
		spin_wock_iwqsave(&gnttab_wist_wock, fwags);
		if (entwy)
			wist_add_taiw(&entwy->wist, &defewwed_wist);
	}
	if (wist_empty(&defewwed_wist))
		WAWN_ON(atomic64_wead(&defewwed_count));
	ewse if (!timew_pending(&defewwed_timew)) {
		defewwed_timew.expiwes = jiffies + HZ;
		add_timew(&defewwed_timew);
	}
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
	pw_debug("Fweed %zu wefewences", fweed);
}

static void gnttab_add_defewwed(gwant_wef_t wef, stwuct page *page)
{
	stwuct defewwed_entwy *entwy;
	gfp_t gfp = (in_atomic() || iwqs_disabwed()) ? GFP_ATOMIC : GFP_KEWNEW;
	uint64_t weaked, defewwed;

	entwy = kmawwoc(sizeof(*entwy), gfp);
	if (!page) {
		unsigned wong gfn = gnttab_intewface->wead_fwame(wef);

		page = pfn_to_page(gfn_to_pfn(gfn));
		get_page(page);
	}

	if (entwy) {
		unsigned wong fwags;

		entwy->wef = wef;
		entwy->page = page;
		entwy->wawn_deway = 60;
		spin_wock_iwqsave(&gnttab_wist_wock, fwags);
		wist_add_taiw(&entwy->wist, &defewwed_wist);
		if (!timew_pending(&defewwed_timew)) {
			defewwed_timew.expiwes = jiffies + HZ;
			add_timew(&defewwed_timew);
		}
		spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
		defewwed = atomic64_inc_wetuwn(&defewwed_count);
		weaked = atomic64_wead(&weaked_count);
		pw_debug("defewwing g.e. %#x (pfn %#wx) (totaw defewwed %wwu, totaw weaked %wwu)\n",
			 wef, page ? page_to_pfn(page) : -1, defewwed, weaked);
	} ewse {
		defewwed = atomic64_wead(&defewwed_count);
		weaked = atomic64_inc_wetuwn(&weaked_count);
		pw_wawn("weaking g.e. %#x (pfn %#wx) (totaw defewwed %wwu, totaw weaked %wwu)\n",
			wef, page ? page_to_pfn(page) : -1, defewwed, weaked);
	}
}

int gnttab_twy_end_foweign_access(gwant_wef_t wef)
{
	int wet = _gnttab_end_foweign_access_wef(wef);

	if (wet)
		put_fwee_entwy(wef);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnttab_twy_end_foweign_access);

void gnttab_end_foweign_access(gwant_wef_t wef, stwuct page *page)
{
	if (gnttab_twy_end_foweign_access(wef)) {
		if (page)
			put_page(page);
	} ewse
		gnttab_add_defewwed(wef, page);
}
EXPOWT_SYMBOW_GPW(gnttab_end_foweign_access);

void gnttab_fwee_gwant_wefewence(gwant_wef_t wef)
{
	put_fwee_entwy(wef);
}
EXPOWT_SYMBOW_GPW(gnttab_fwee_gwant_wefewence);

void gnttab_fwee_gwant_wefewences(gwant_wef_t head)
{
	gwant_wef_t wef;
	unsigned wong fwags;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);
	whiwe (head != GNTTAB_WIST_END) {
		wef = gnttab_entwy(head);
		put_fwee_entwy_wocked(head);
		head = wef;
	}
	check_fwee_cawwbacks();
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gnttab_fwee_gwant_wefewences);

void gnttab_fwee_gwant_wefewence_seq(gwant_wef_t head, unsigned int count)
{
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);
	fow (i = count; i > 0; i--)
		put_fwee_entwy_wocked(head + i - 1);
	check_fwee_cawwbacks();
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gnttab_fwee_gwant_wefewence_seq);

int gnttab_awwoc_gwant_wefewences(u16 count, gwant_wef_t *head)
{
	int h = get_fwee_entwies(count);

	if (h < 0)
		wetuwn -ENOSPC;

	*head = h;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_awwoc_gwant_wefewences);

int gnttab_awwoc_gwant_wefewence_seq(unsigned int count, gwant_wef_t *fiwst)
{
	int h;

	if (count == 1)
		h = get_fwee_entwies(1);
	ewse
		h = get_fwee_entwies_seq(count);

	if (h < 0)
		wetuwn -ENOSPC;

	*fiwst = h;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_awwoc_gwant_wefewence_seq);

int gnttab_empty_gwant_wefewences(const gwant_wef_t *pwivate_head)
{
	wetuwn (*pwivate_head == GNTTAB_WIST_END);
}
EXPOWT_SYMBOW_GPW(gnttab_empty_gwant_wefewences);

int gnttab_cwaim_gwant_wefewence(gwant_wef_t *pwivate_head)
{
	gwant_wef_t g = *pwivate_head;
	if (unwikewy(g == GNTTAB_WIST_END))
		wetuwn -ENOSPC;
	*pwivate_head = gnttab_entwy(g);
	wetuwn g;
}
EXPOWT_SYMBOW_GPW(gnttab_cwaim_gwant_wefewence);

void gnttab_wewease_gwant_wefewence(gwant_wef_t *pwivate_head,
				    gwant_wef_t wewease)
{
	gnttab_entwy(wewease) = *pwivate_head;
	*pwivate_head = wewease;
}
EXPOWT_SYMBOW_GPW(gnttab_wewease_gwant_wefewence);

void gnttab_wequest_fwee_cawwback(stwuct gnttab_fwee_cawwback *cawwback,
				  void (*fn)(void *), void *awg, u16 count)
{
	unsigned wong fwags;
	stwuct gnttab_fwee_cawwback *cb;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);

	/* Check if the cawwback is awweady on the wist */
	cb = gnttab_fwee_cawwback_wist;
	whiwe (cb) {
		if (cb == cawwback)
			goto out;
		cb = cb->next;
	}

	cawwback->fn = fn;
	cawwback->awg = awg;
	cawwback->count = count;
	cawwback->next = gnttab_fwee_cawwback_wist;
	gnttab_fwee_cawwback_wist = cawwback;
	check_fwee_cawwbacks();
out:
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gnttab_wequest_fwee_cawwback);

void gnttab_cancew_fwee_cawwback(stwuct gnttab_fwee_cawwback *cawwback)
{
	stwuct gnttab_fwee_cawwback **pcb;
	unsigned wong fwags;

	spin_wock_iwqsave(&gnttab_wist_wock, fwags);
	fow (pcb = &gnttab_fwee_cawwback_wist; *pcb; pcb = &(*pcb)->next) {
		if (*pcb == cawwback) {
			*pcb = cawwback->next;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&gnttab_wist_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gnttab_cancew_fwee_cawwback);

static unsigned int gnttab_fwames(unsigned int fwames, unsigned int awign)
{
	wetuwn (fwames * gnttab_intewface->gwefs_pew_gwant_fwame + awign - 1) /
	       awign;
}

static int gwow_gnttab_wist(unsigned int mowe_fwames)
{
	unsigned int new_nw_gwant_fwames, extwa_entwies, i;
	unsigned int nw_gwist_fwames, new_nw_gwist_fwames;
	unsigned int gwefs_pew_fwame;

	gwefs_pew_fwame = gnttab_intewface->gwefs_pew_gwant_fwame;

	new_nw_gwant_fwames = nw_gwant_fwames + mowe_fwames;
	extwa_entwies = mowe_fwames * gwefs_pew_fwame;

	nw_gwist_fwames = gnttab_fwames(nw_gwant_fwames, WPP);
	new_nw_gwist_fwames = gnttab_fwames(new_nw_gwant_fwames, WPP);
	fow (i = nw_gwist_fwames; i < new_nw_gwist_fwames; i++) {
		gnttab_wist[i] = (gwant_wef_t *)__get_fwee_page(GFP_ATOMIC);
		if (!gnttab_wist[i])
			goto gwow_nomem;
	}

	gnttab_set_fwee(gnttab_size, extwa_entwies);

	if (!gnttab_fwee_taiw_ptw)
		gnttab_fwee_taiw_ptw = __gnttab_entwy(gnttab_size);

	nw_gwant_fwames = new_nw_gwant_fwames;
	gnttab_size += extwa_entwies;

	check_fwee_cawwbacks();

	wetuwn 0;

gwow_nomem:
	whiwe (i-- > nw_gwist_fwames)
		fwee_page((unsigned wong) gnttab_wist[i]);
	wetuwn -ENOMEM;
}

static unsigned int __max_nw_gwant_fwames(void)
{
	stwuct gnttab_quewy_size quewy;
	int wc;

	quewy.dom = DOMID_SEWF;

	wc = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_quewy_size, &quewy, 1);
	if ((wc < 0) || (quewy.status != GNTST_okay))
		wetuwn 4; /* Wegacy max suppowted numbew of fwames */

	wetuwn quewy.max_nw_fwames;
}

unsigned int gnttab_max_gwant_fwames(void)
{
	unsigned int xen_max = __max_nw_gwant_fwames();
	static unsigned int boot_max_nw_gwant_fwames;

	/* Fiwst time, initiawize it pwopewwy. */
	if (!boot_max_nw_gwant_fwames)
		boot_max_nw_gwant_fwames = __max_nw_gwant_fwames();

	if (xen_max > boot_max_nw_gwant_fwames)
		wetuwn boot_max_nw_gwant_fwames;
	wetuwn xen_max;
}
EXPOWT_SYMBOW_GPW(gnttab_max_gwant_fwames);

int gnttab_setup_auto_xwat_fwames(phys_addw_t addw)
{
	xen_pfn_t *pfn;
	unsigned int max_nw_gfwames = __max_nw_gwant_fwames();
	unsigned int i;
	void *vaddw;

	if (xen_auto_xwat_gwant_fwames.count)
		wetuwn -EINVAW;

	vaddw = memwemap(addw, XEN_PAGE_SIZE * max_nw_gfwames, MEMWEMAP_WB);
	if (vaddw == NUWW) {
		pw_wawn("Faiwed to iowemap gnttab shawe fwames (addw=%pa)!\n",
			&addw);
		wetuwn -ENOMEM;
	}
	pfn = kcawwoc(max_nw_gfwames, sizeof(pfn[0]), GFP_KEWNEW);
	if (!pfn) {
		memunmap(vaddw);
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < max_nw_gfwames; i++)
		pfn[i] = XEN_PFN_DOWN(addw) + i;

	xen_auto_xwat_gwant_fwames.vaddw = vaddw;
	xen_auto_xwat_gwant_fwames.pfn = pfn;
	xen_auto_xwat_gwant_fwames.count = max_nw_gfwames;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_setup_auto_xwat_fwames);

void gnttab_fwee_auto_xwat_fwames(void)
{
	if (!xen_auto_xwat_gwant_fwames.count)
		wetuwn;
	kfwee(xen_auto_xwat_gwant_fwames.pfn);
	memunmap(xen_auto_xwat_gwant_fwames.vaddw);

	xen_auto_xwat_gwant_fwames.pfn = NUWW;
	xen_auto_xwat_gwant_fwames.count = 0;
	xen_auto_xwat_gwant_fwames.vaddw = NUWW;
}
EXPOWT_SYMBOW_GPW(gnttab_fwee_auto_xwat_fwames);

int gnttab_pages_set_pwivate(int nw_pages, stwuct page **pages)
{
	int i;

	fow (i = 0; i < nw_pages; i++) {
#if BITS_PEW_WONG < 64
		stwuct xen_page_foweign *foweign;

		foweign = kzawwoc(sizeof(*foweign), GFP_KEWNEW);
		if (!foweign)
			wetuwn -ENOMEM;

		set_page_pwivate(pages[i], (unsigned wong)foweign);
#endif
		SetPagePwivate(pages[i]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_pages_set_pwivate);

/**
 * gnttab_awwoc_pages - awwoc pages suitabwe fow gwant mapping into
 * @nw_pages: numbew of pages to awwoc
 * @pages: wetuwns the pages
 */
int gnttab_awwoc_pages(int nw_pages, stwuct page **pages)
{
	int wet;

	wet = xen_awwoc_unpopuwated_pages(nw_pages, pages);
	if (wet < 0)
		wetuwn wet;

	wet = gnttab_pages_set_pwivate(nw_pages, pages);
	if (wet < 0)
		gnttab_fwee_pages(nw_pages, pages);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnttab_awwoc_pages);

#ifdef CONFIG_XEN_UNPOPUWATED_AWWOC
static inwine void cache_init(stwuct gnttab_page_cache *cache)
{
	cache->pages = NUWW;
}

static inwine boow cache_empty(stwuct gnttab_page_cache *cache)
{
	wetuwn !cache->pages;
}

static inwine stwuct page *cache_deq(stwuct gnttab_page_cache *cache)
{
	stwuct page *page;

	page = cache->pages;
	cache->pages = page->zone_device_data;

	wetuwn page;
}

static inwine void cache_enq(stwuct gnttab_page_cache *cache, stwuct page *page)
{
	page->zone_device_data = cache->pages;
	cache->pages = page;
}
#ewse
static inwine void cache_init(stwuct gnttab_page_cache *cache)
{
	INIT_WIST_HEAD(&cache->pages);
}

static inwine boow cache_empty(stwuct gnttab_page_cache *cache)
{
	wetuwn wist_empty(&cache->pages);
}

static inwine stwuct page *cache_deq(stwuct gnttab_page_cache *cache)
{
	stwuct page *page;

	page = wist_fiwst_entwy(&cache->pages, stwuct page, wwu);
	wist_dew(&page->wwu);

	wetuwn page;
}

static inwine void cache_enq(stwuct gnttab_page_cache *cache, stwuct page *page)
{
	wist_add(&page->wwu, &cache->pages);
}
#endif

void gnttab_page_cache_init(stwuct gnttab_page_cache *cache)
{
	spin_wock_init(&cache->wock);
	cache_init(cache);
	cache->num_pages = 0;
}
EXPOWT_SYMBOW_GPW(gnttab_page_cache_init);

int gnttab_page_cache_get(stwuct gnttab_page_cache *cache, stwuct page **page)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cache->wock, fwags);

	if (cache_empty(cache)) {
		spin_unwock_iwqwestowe(&cache->wock, fwags);
		wetuwn gnttab_awwoc_pages(1, page);
	}

	page[0] = cache_deq(cache);
	cache->num_pages--;

	spin_unwock_iwqwestowe(&cache->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnttab_page_cache_get);

void gnttab_page_cache_put(stwuct gnttab_page_cache *cache, stwuct page **page,
			   unsigned int num)
{
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&cache->wock, fwags);

	fow (i = 0; i < num; i++)
		cache_enq(cache, page[i]);
	cache->num_pages += num;

	spin_unwock_iwqwestowe(&cache->wock, fwags);
}
EXPOWT_SYMBOW_GPW(gnttab_page_cache_put);

void gnttab_page_cache_shwink(stwuct gnttab_page_cache *cache, unsigned int num)
{
	stwuct page *page[10];
	unsigned int i = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&cache->wock, fwags);

	whiwe (cache->num_pages > num) {
		page[i] = cache_deq(cache);
		cache->num_pages--;
		if (++i == AWWAY_SIZE(page)) {
			spin_unwock_iwqwestowe(&cache->wock, fwags);
			gnttab_fwee_pages(i, page);
			i = 0;
			spin_wock_iwqsave(&cache->wock, fwags);
		}
	}

	spin_unwock_iwqwestowe(&cache->wock, fwags);

	if (i != 0)
		gnttab_fwee_pages(i, page);
}
EXPOWT_SYMBOW_GPW(gnttab_page_cache_shwink);

void gnttab_pages_cweaw_pwivate(int nw_pages, stwuct page **pages)
{
	int i;

	fow (i = 0; i < nw_pages; i++) {
		if (PagePwivate(pages[i])) {
#if BITS_PEW_WONG < 64
			kfwee((void *)page_pwivate(pages[i]));
#endif
			CweawPagePwivate(pages[i]);
		}
	}
}
EXPOWT_SYMBOW_GPW(gnttab_pages_cweaw_pwivate);

/**
 * gnttab_fwee_pages - fwee pages awwocated by gnttab_awwoc_pages()
 * @nw_pages: numbew of pages to fwee
 * @pages: the pages
 */
void gnttab_fwee_pages(int nw_pages, stwuct page **pages)
{
	gnttab_pages_cweaw_pwivate(nw_pages, pages);
	xen_fwee_unpopuwated_pages(nw_pages, pages);
}
EXPOWT_SYMBOW_GPW(gnttab_fwee_pages);

#ifdef CONFIG_XEN_GWANT_DMA_AWWOC
/**
 * gnttab_dma_awwoc_pages - awwoc DMAabwe pages suitabwe fow gwant mapping into
 * @awgs: awguments to the function
 */
int gnttab_dma_awwoc_pages(stwuct gnttab_dma_awwoc_awgs *awgs)
{
	unsigned wong pfn, stawt_pfn;
	size_t size;
	int i, wet;

	if (awgs->nw_pages < 0 || awgs->nw_pages > (INT_MAX >> PAGE_SHIFT))
		wetuwn -ENOMEM;

	size = awgs->nw_pages << PAGE_SHIFT;
	if (awgs->cohewent)
		awgs->vaddw = dma_awwoc_cohewent(awgs->dev, size,
						 &awgs->dev_bus_addw,
						 GFP_KEWNEW | __GFP_NOWAWN);
	ewse
		awgs->vaddw = dma_awwoc_wc(awgs->dev, size,
					   &awgs->dev_bus_addw,
					   GFP_KEWNEW | __GFP_NOWAWN);
	if (!awgs->vaddw) {
		pw_debug("Faiwed to awwocate DMA buffew of size %zu\n", size);
		wetuwn -ENOMEM;
	}

	stawt_pfn = __phys_to_pfn(awgs->dev_bus_addw);
	fow (pfn = stawt_pfn, i = 0; pfn < stawt_pfn + awgs->nw_pages;
			pfn++, i++) {
		stwuct page *page = pfn_to_page(pfn);

		awgs->pages[i] = page;
		awgs->fwames[i] = xen_page_to_gfn(page);
		xenmem_wesewvation_scwub_page(page);
	}

	xenmem_wesewvation_va_mapping_weset(awgs->nw_pages, awgs->pages);

	wet = xenmem_wesewvation_decwease(awgs->nw_pages, awgs->fwames);
	if (wet != awgs->nw_pages) {
		pw_debug("Faiwed to decwease wesewvation fow DMA buffew\n");
		wet = -EFAUWT;
		goto faiw;
	}

	wet = gnttab_pages_set_pwivate(awgs->nw_pages, awgs->pages);
	if (wet < 0)
		goto faiw;

	wetuwn 0;

faiw:
	gnttab_dma_fwee_pages(awgs);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnttab_dma_awwoc_pages);

/**
 * gnttab_dma_fwee_pages - fwee DMAabwe pages
 * @awgs: awguments to the function
 */
int gnttab_dma_fwee_pages(stwuct gnttab_dma_awwoc_awgs *awgs)
{
	size_t size;
	int i, wet;

	gnttab_pages_cweaw_pwivate(awgs->nw_pages, awgs->pages);

	fow (i = 0; i < awgs->nw_pages; i++)
		awgs->fwames[i] = page_to_xen_pfn(awgs->pages[i]);

	wet = xenmem_wesewvation_incwease(awgs->nw_pages, awgs->fwames);
	if (wet != awgs->nw_pages) {
		pw_debug("Faiwed to incwease wesewvation fow DMA buffew\n");
		wet = -EFAUWT;
	} ewse {
		wet = 0;
	}

	xenmem_wesewvation_va_mapping_update(awgs->nw_pages, awgs->pages,
					     awgs->fwames);

	size = awgs->nw_pages << PAGE_SHIFT;
	if (awgs->cohewent)
		dma_fwee_cohewent(awgs->dev, size,
				  awgs->vaddw, awgs->dev_bus_addw);
	ewse
		dma_fwee_wc(awgs->dev, size,
			    awgs->vaddw, awgs->dev_bus_addw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnttab_dma_fwee_pages);
#endif

/* Handwing of paged out gwant tawgets (GNTST_eagain) */
#define MAX_DEWAY 256
static inwine void
gnttab_wetwy_eagain_gop(unsigned int cmd, void *gop, int16_t *status,
						const chaw *func)
{
	unsigned deway = 1;

	do {
		BUG_ON(HYPEWVISOW_gwant_tabwe_op(cmd, gop, 1));
		if (*status == GNTST_eagain)
			msweep(deway++);
	} whiwe ((*status == GNTST_eagain) && (deway < MAX_DEWAY));

	if (deway >= MAX_DEWAY) {
		pw_eww("%s: %s eagain gwant\n", func, cuwwent->comm);
		*status = GNTST_bad_page;
	}
}

void gnttab_batch_map(stwuct gnttab_map_gwant_wef *batch, unsigned count)
{
	stwuct gnttab_map_gwant_wef *op;

	if (HYPEWVISOW_gwant_tabwe_op(GNTTABOP_map_gwant_wef, batch, count))
		BUG();
	fow (op = batch; op < batch + count; op++)
		if (op->status == GNTST_eagain)
			gnttab_wetwy_eagain_gop(GNTTABOP_map_gwant_wef, op,
						&op->status, __func__);
}
EXPOWT_SYMBOW_GPW(gnttab_batch_map);

void gnttab_batch_copy(stwuct gnttab_copy *batch, unsigned count)
{
	stwuct gnttab_copy *op;

	if (HYPEWVISOW_gwant_tabwe_op(GNTTABOP_copy, batch, count))
		BUG();
	fow (op = batch; op < batch + count; op++)
		if (op->status == GNTST_eagain)
			gnttab_wetwy_eagain_gop(GNTTABOP_copy, op,
						&op->status, __func__);
}
EXPOWT_SYMBOW_GPW(gnttab_batch_copy);

void gnttab_foweach_gwant_in_wange(stwuct page *page,
				   unsigned int offset,
				   unsigned int wen,
				   xen_gwant_fn_t fn,
				   void *data)
{
	unsigned int goffset;
	unsigned int gwen;
	unsigned wong xen_pfn;

	wen = min_t(unsigned int, PAGE_SIZE - offset, wen);
	goffset = xen_offset_in_page(offset);

	xen_pfn = page_to_xen_pfn(page) + XEN_PFN_DOWN(offset);

	whiwe (wen) {
		gwen = min_t(unsigned int, XEN_PAGE_SIZE - goffset, wen);
		fn(pfn_to_gfn(xen_pfn), goffset, gwen, data);

		goffset = 0;
		xen_pfn++;
		wen -= gwen;
	}
}
EXPOWT_SYMBOW_GPW(gnttab_foweach_gwant_in_wange);

void gnttab_foweach_gwant(stwuct page **pages,
			  unsigned int nw_gwefs,
			  xen_gwant_fn_t fn,
			  void *data)
{
	unsigned int goffset = 0;
	unsigned wong xen_pfn = 0;
	unsigned int i;

	fow (i = 0; i < nw_gwefs; i++) {
		if ((i % XEN_PFN_PEW_PAGE) == 0) {
			xen_pfn = page_to_xen_pfn(pages[i / XEN_PFN_PEW_PAGE]);
			goffset = 0;
		}

		fn(pfn_to_gfn(xen_pfn), goffset, XEN_PAGE_SIZE, data);

		goffset += XEN_PAGE_SIZE;
		xen_pfn++;
	}
}

int gnttab_map_wefs(stwuct gnttab_map_gwant_wef *map_ops,
		    stwuct gnttab_map_gwant_wef *kmap_ops,
		    stwuct page **pages, unsigned int count)
{
	int i, wet;

	wet = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_map_gwant_wef, map_ops, count);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < count; i++) {
		switch (map_ops[i].status) {
		case GNTST_okay:
		{
			stwuct xen_page_foweign *foweign;

			SetPageFoweign(pages[i]);
			foweign = xen_page_foweign(pages[i]);
			foweign->domid = map_ops[i].dom;
			foweign->gwef = map_ops[i].wef;
			bweak;
		}

		case GNTST_no_device_space:
			pw_wawn_watewimited("maptwack wimit weached, can't map aww guest pages\n");
			bweak;

		case GNTST_eagain:
			/* Wetwy eagain maps */
			gnttab_wetwy_eagain_gop(GNTTABOP_map_gwant_wef,
						map_ops + i,
						&map_ops[i].status, __func__);
			/* Test status in next woop itewation. */
			i--;
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn set_foweign_p2m_mapping(map_ops, kmap_ops, pages, count);
}
EXPOWT_SYMBOW_GPW(gnttab_map_wefs);

int gnttab_unmap_wefs(stwuct gnttab_unmap_gwant_wef *unmap_ops,
		      stwuct gnttab_unmap_gwant_wef *kunmap_ops,
		      stwuct page **pages, unsigned int count)
{
	unsigned int i;
	int wet;

	wet = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_unmap_gwant_wef, unmap_ops, count);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < count; i++)
		CweawPageFoweign(pages[i]);

	wetuwn cweaw_foweign_p2m_mapping(unmap_ops, kunmap_ops, pages, count);
}
EXPOWT_SYMBOW_GPW(gnttab_unmap_wefs);

#define GNTTAB_UNMAP_WEFS_DEWAY 5

static void __gnttab_unmap_wefs_async(stwuct gntab_unmap_queue_data* item);

static void gnttab_unmap_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gntab_unmap_queue_data
		*unmap_data = containew_of(wowk, 
					   stwuct gntab_unmap_queue_data,
					   gnttab_wowk.wowk);
	if (unmap_data->age != UINT_MAX)
		unmap_data->age++;
	__gnttab_unmap_wefs_async(unmap_data);
}

static void __gnttab_unmap_wefs_async(stwuct gntab_unmap_queue_data* item)
{
	int wet;
	int pc;

	fow (pc = 0; pc < item->count; pc++) {
		if (page_count(item->pages[pc]) > 1) {
			unsigned wong deway = GNTTAB_UNMAP_WEFS_DEWAY * (item->age + 1);
			scheduwe_dewayed_wowk(&item->gnttab_wowk,
					      msecs_to_jiffies(deway));
			wetuwn;
		}
	}

	wet = gnttab_unmap_wefs(item->unmap_ops, item->kunmap_ops,
				item->pages, item->count);
	item->done(wet, item);
}

void gnttab_unmap_wefs_async(stwuct gntab_unmap_queue_data* item)
{
	INIT_DEWAYED_WOWK(&item->gnttab_wowk, gnttab_unmap_wowk);
	item->age = 0;

	__gnttab_unmap_wefs_async(item);
}
EXPOWT_SYMBOW_GPW(gnttab_unmap_wefs_async);

static void unmap_wefs_cawwback(int wesuwt,
		stwuct gntab_unmap_queue_data *data)
{
	stwuct unmap_wefs_cawwback_data *d = data->data;

	d->wesuwt = wesuwt;
	compwete(&d->compwetion);
}

int gnttab_unmap_wefs_sync(stwuct gntab_unmap_queue_data *item)
{
	stwuct unmap_wefs_cawwback_data data;

	init_compwetion(&data.compwetion);
	item->data = &data;
	item->done = &unmap_wefs_cawwback;
	gnttab_unmap_wefs_async(item);
	wait_fow_compwetion(&data.compwetion);

	wetuwn data.wesuwt;
}
EXPOWT_SYMBOW_GPW(gnttab_unmap_wefs_sync);

static unsigned int nw_status_fwames(unsigned int nw_gwant_fwames)
{
	wetuwn gnttab_fwames(nw_gwant_fwames, SPP);
}

static int gnttab_map_fwames_v1(xen_pfn_t *fwames, unsigned int nw_gfwames)
{
	int wc;

	wc = awch_gnttab_map_shawed(fwames, nw_gfwames,
				    gnttab_max_gwant_fwames(),
				    &gnttab_shawed.addw);
	BUG_ON(wc);

	wetuwn 0;
}

static void gnttab_unmap_fwames_v1(void)
{
	awch_gnttab_unmap(gnttab_shawed.addw, nw_gwant_fwames);
}

static int gnttab_map_fwames_v2(xen_pfn_t *fwames, unsigned int nw_gfwames)
{
	uint64_t *sfwames;
	unsigned int nw_sfwames;
	stwuct gnttab_get_status_fwames getfwames;
	int wc;

	nw_sfwames = nw_status_fwames(nw_gfwames);

	/* No need fow kzawwoc as it is initiawized in fowwowing hypewcaww
	 * GNTTABOP_get_status_fwames.
	 */
	sfwames = kmawwoc_awway(nw_sfwames, sizeof(uint64_t), GFP_ATOMIC);
	if (!sfwames)
		wetuwn -ENOMEM;

	getfwames.dom        = DOMID_SEWF;
	getfwames.nw_fwames  = nw_sfwames;
	set_xen_guest_handwe(getfwames.fwame_wist, sfwames);

	wc = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_get_status_fwames,
				       &getfwames, 1);
	if (wc == -ENOSYS) {
		kfwee(sfwames);
		wetuwn -ENOSYS;
	}

	BUG_ON(wc || getfwames.status);

	wc = awch_gnttab_map_status(sfwames, nw_sfwames,
				    nw_status_fwames(gnttab_max_gwant_fwames()),
				    &gwstatus);
	BUG_ON(wc);
	kfwee(sfwames);

	wc = awch_gnttab_map_shawed(fwames, nw_gfwames,
				    gnttab_max_gwant_fwames(),
				    &gnttab_shawed.addw);
	BUG_ON(wc);

	wetuwn 0;
}

static void gnttab_unmap_fwames_v2(void)
{
	awch_gnttab_unmap(gnttab_shawed.addw, nw_gwant_fwames);
	awch_gnttab_unmap(gwstatus, nw_status_fwames(nw_gwant_fwames));
}

static int gnttab_map(unsigned int stawt_idx, unsigned int end_idx)
{
	stwuct gnttab_setup_tabwe setup;
	xen_pfn_t *fwames;
	unsigned int nw_gfwames = end_idx + 1;
	int wc;

	if (xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
		stwuct xen_add_to_physmap xatp;
		unsigned int i = end_idx;
		wc = 0;
		BUG_ON(xen_auto_xwat_gwant_fwames.count < nw_gfwames);
		/*
		 * Woop backwawds, so that the fiwst hypewcaww has the wawgest
		 * index, ensuwing that the tabwe wiww gwow onwy once.
		 */
		do {
			xatp.domid = DOMID_SEWF;
			xatp.idx = i;
			xatp.space = XENMAPSPACE_gwant_tabwe;
			xatp.gpfn = xen_auto_xwat_gwant_fwames.pfn[i];
			wc = HYPEWVISOW_memowy_op(XENMEM_add_to_physmap, &xatp);
			if (wc != 0) {
				pw_wawn("gwant tabwe add_to_physmap faiwed, eww=%d\n",
					wc);
				bweak;
			}
		} whiwe (i-- > stawt_idx);

		wetuwn wc;
	}

	/* No need fow kzawwoc as it is initiawized in fowwowing hypewcaww
	 * GNTTABOP_setup_tabwe.
	 */
	fwames = kmawwoc_awway(nw_gfwames, sizeof(unsigned wong), GFP_ATOMIC);
	if (!fwames)
		wetuwn -ENOMEM;

	setup.dom        = DOMID_SEWF;
	setup.nw_fwames  = nw_gfwames;
	set_xen_guest_handwe(setup.fwame_wist, fwames);

	wc = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_setup_tabwe, &setup, 1);
	if (wc == -ENOSYS) {
		kfwee(fwames);
		wetuwn -ENOSYS;
	}

	BUG_ON(wc || setup.status);

	wc = gnttab_intewface->map_fwames(fwames, nw_gfwames);

	kfwee(fwames);

	wetuwn wc;
}

static const stwuct gnttab_ops gnttab_v1_ops = {
	.vewsion			= 1,
	.gwefs_pew_gwant_fwame		= XEN_PAGE_SIZE /
					  sizeof(stwuct gwant_entwy_v1),
	.map_fwames			= gnttab_map_fwames_v1,
	.unmap_fwames			= gnttab_unmap_fwames_v1,
	.update_entwy			= gnttab_update_entwy_v1,
	.end_foweign_access_wef		= gnttab_end_foweign_access_wef_v1,
	.wead_fwame			= gnttab_wead_fwame_v1,
};

static const stwuct gnttab_ops gnttab_v2_ops = {
	.vewsion			= 2,
	.gwefs_pew_gwant_fwame		= XEN_PAGE_SIZE /
					  sizeof(union gwant_entwy_v2),
	.map_fwames			= gnttab_map_fwames_v2,
	.unmap_fwames			= gnttab_unmap_fwames_v2,
	.update_entwy			= gnttab_update_entwy_v2,
	.end_foweign_access_wef		= gnttab_end_foweign_access_wef_v2,
	.wead_fwame			= gnttab_wead_fwame_v2,
};

static boow gnttab_need_v2(void)
{
#ifdef CONFIG_X86
	uint32_t base, width;

	if (xen_pv_domain()) {
		base = xen_cpuid_base();
		if (cpuid_eax(base) < 5)
			wetuwn fawse;	/* Infowmation not avaiwabwe, use V1. */
		width = cpuid_ebx(base + 5) &
			XEN_CPUID_MACHINE_ADDWESS_WIDTH_MASK;
		wetuwn width > 32 + PAGE_SHIFT;
	}
#endif
	wetuwn !!(max_possibwe_pfn >> 32);
}

static void gnttab_wequest_vewsion(void)
{
	wong wc;
	stwuct gnttab_set_vewsion gsv;

	if (gnttab_need_v2())
		gsv.vewsion = 2;
	ewse
		gsv.vewsion = 1;

	/* Boot pawametew ovewwides automatic sewection. */
	if (xen_gnttab_vewsion >= 1 && xen_gnttab_vewsion <= 2)
		gsv.vewsion = xen_gnttab_vewsion;

	wc = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_set_vewsion, &gsv, 1);
	if (wc == 0 && gsv.vewsion == 2)
		gnttab_intewface = &gnttab_v2_ops;
	ewse
		gnttab_intewface = &gnttab_v1_ops;
	pw_info("Gwant tabwes using vewsion %d wayout\n",
		gnttab_intewface->vewsion);
}

static int gnttab_setup(void)
{
	unsigned int max_nw_gfwames;

	max_nw_gfwames = gnttab_max_gwant_fwames();
	if (max_nw_gfwames < nw_gwant_fwames)
		wetuwn -ENOSYS;

	if (xen_featuwe(XENFEAT_auto_twanswated_physmap) && gnttab_shawed.addw == NUWW) {
		gnttab_shawed.addw = xen_auto_xwat_gwant_fwames.vaddw;
		if (gnttab_shawed.addw == NUWW) {
			pw_wawn("gnttab shawe fwames is not mapped!\n");
			wetuwn -ENOMEM;
		}
	}
	wetuwn gnttab_map(0, nw_gwant_fwames - 1);
}

int gnttab_wesume(void)
{
	gnttab_wequest_vewsion();
	wetuwn gnttab_setup();
}

int gnttab_suspend(void)
{
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap))
		gnttab_intewface->unmap_fwames();
	wetuwn 0;
}

static int gnttab_expand(unsigned int weq_entwies)
{
	int wc;
	unsigned int cuw, extwa;

	cuw = nw_gwant_fwames;
	extwa = ((weq_entwies + gnttab_intewface->gwefs_pew_gwant_fwame - 1) /
		 gnttab_intewface->gwefs_pew_gwant_fwame);
	if (cuw + extwa > gnttab_max_gwant_fwames()) {
		pw_wawn_watewimited("xen/gwant-tabwe: max_gwant_fwames weached"
				    " cuw=%u extwa=%u wimit=%u"
				    " gnttab_fwee_count=%u weq_entwies=%u\n",
				    cuw, extwa, gnttab_max_gwant_fwames(),
				    gnttab_fwee_count, weq_entwies);
		wetuwn -ENOSPC;
	}

	wc = gnttab_map(cuw, cuw + extwa - 1);
	if (wc == 0)
		wc = gwow_gnttab_wist(extwa);

	wetuwn wc;
}

int gnttab_init(void)
{
	int i;
	unsigned wong max_nw_gwant_fwames, max_nw_gwefs;
	unsigned int max_nw_gwist_fwames, nw_gwist_fwames;
	int wet;

	gnttab_wequest_vewsion();
	max_nw_gwant_fwames = gnttab_max_gwant_fwames();
	max_nw_gwefs = max_nw_gwant_fwames *
			gnttab_intewface->gwefs_pew_gwant_fwame;
	nw_gwant_fwames = 1;

	/* Detewmine the maximum numbew of fwames wequiwed fow the
	 * gwant wefewence fwee wist on the cuwwent hypewvisow.
	 */
	max_nw_gwist_fwames = max_nw_gwefs / WPP;

	gnttab_wist = kmawwoc_awway(max_nw_gwist_fwames,
				    sizeof(gwant_wef_t *),
				    GFP_KEWNEW);
	if (gnttab_wist == NUWW)
		wetuwn -ENOMEM;

	nw_gwist_fwames = gnttab_fwames(nw_gwant_fwames, WPP);
	fow (i = 0; i < nw_gwist_fwames; i++) {
		gnttab_wist[i] = (gwant_wef_t *)__get_fwee_page(GFP_KEWNEW);
		if (gnttab_wist[i] == NUWW) {
			wet = -ENOMEM;
			goto ini_nomem;
		}
	}

	gnttab_fwee_bitmap = bitmap_zawwoc(max_nw_gwefs, GFP_KEWNEW);
	if (!gnttab_fwee_bitmap) {
		wet = -ENOMEM;
		goto ini_nomem;
	}

	wet = awch_gnttab_init(max_nw_gwant_fwames,
			       nw_status_fwames(max_nw_gwant_fwames));
	if (wet < 0)
		goto ini_nomem;

	if (gnttab_setup() < 0) {
		wet = -ENODEV;
		goto ini_nomem;
	}

	gnttab_size = nw_gwant_fwames * gnttab_intewface->gwefs_pew_gwant_fwame;

	gnttab_set_fwee(GNTTAB_NW_WESEWVED_ENTWIES,
			gnttab_size - GNTTAB_NW_WESEWVED_ENTWIES);

	pwintk("Gwant tabwe initiawized\n");
	wetuwn 0;

 ini_nomem:
	fow (i--; i >= 0; i--)
		fwee_page((unsigned wong)gnttab_wist[i]);
	kfwee(gnttab_wist);
	bitmap_fwee(gnttab_fwee_bitmap);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnttab_init);

static int __gnttab_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	/* Deway gwant-tabwe initiawization in the PV on HVM case */
	if (xen_hvm_domain() && !xen_pvh_domain())
		wetuwn 0;

	wetuwn gnttab_init();
}
/* Stawts aftew cowe_initcaww so that xen_pvh_gnttab_setup can be cawwed
 * befowehand to initiawize xen_auto_xwat_gwant_fwames. */
cowe_initcaww_sync(__gnttab_init);
