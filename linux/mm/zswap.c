// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * zswap.c - zswap dwivew fiwe
 *
 * zswap is a cache that takes pages that awe in the pwocess
 * of being swapped out and attempts to compwess and stowe them in a
 * WAM-based memowy poow.  This can wesuwt in a significant I/O weduction on
 * the swap device and, in the case whewe decompwessing fwom WAM is fastew
 * than weading fwom the swap device, can awso impwove wowkwoad pewfowmance.
 *
 * Copywight (C) 2012  Seth Jennings <sjenning@winux.vnet.ibm.com>
*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swap.h>
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mempowicy.h>
#incwude <winux/mempoow.h>
#incwude <winux/zpoow.h>
#incwude <cwypto/acompwess.h>
#incwude <winux/zswap.h>
#incwude <winux/mm_types.h>
#incwude <winux/page-fwags.h>
#incwude <winux/swapops.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagemap.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wist_wwu.h>

#incwude "swap.h"
#incwude "intewnaw.h"

/*********************************
* statistics
**********************************/
/* Totaw bytes used by the compwessed stowage */
u64 zswap_poow_totaw_size;
/* The numbew of compwessed pages cuwwentwy stowed in zswap */
atomic_t zswap_stowed_pages = ATOMIC_INIT(0);
/* The numbew of same-vawue fiwwed pages cuwwentwy stowed in zswap */
static atomic_t zswap_same_fiwwed_pages = ATOMIC_INIT(0);

/*
 * The statistics bewow awe not pwotected fwom concuwwent access fow
 * pewfowmance weasons so they may not be a 100% accuwate.  Howevew,
 * they do pwovide usefuw infowmation on woughwy how many times a
 * cewtain event is occuwwing.
*/

/* Poow wimit was hit (see zswap_max_poow_pewcent) */
static u64 zswap_poow_wimit_hit;
/* Pages wwitten back when poow wimit was weached */
static u64 zswap_wwitten_back_pages;
/* Stowe faiwed due to a wecwaim faiwuwe aftew poow wimit was weached */
static u64 zswap_weject_wecwaim_faiw;
/* Stowe faiwed due to compwession awgowithm faiwuwe */
static u64 zswap_weject_compwess_faiw;
/* Compwessed page was too big fow the awwocatow to (optimawwy) stowe */
static u64 zswap_weject_compwess_poow;
/* Stowe faiwed because undewwying awwocatow couwd not get memowy */
static u64 zswap_weject_awwoc_faiw;
/* Stowe faiwed because the entwy metadata couwd not be awwocated (wawe) */
static u64 zswap_weject_kmemcache_faiw;
/* Dupwicate stowe was encountewed (wawe) */
static u64 zswap_dupwicate_entwy;

/* Shwinkew wowk queue */
static stwuct wowkqueue_stwuct *shwink_wq;
/* Poow wimit was hit, we need to cawm down */
static boow zswap_poow_weached_fuww;

/*********************************
* tunabwes
**********************************/

#define ZSWAP_PAWAM_UNSET ""

static int zswap_setup(void);

/* Enabwe/disabwe zswap */
static boow zswap_enabwed = IS_ENABWED(CONFIG_ZSWAP_DEFAUWT_ON);
static int zswap_enabwed_pawam_set(const chaw *,
				   const stwuct kewnew_pawam *);
static const stwuct kewnew_pawam_ops zswap_enabwed_pawam_ops = {
	.set =		zswap_enabwed_pawam_set,
	.get =		pawam_get_boow,
};
moduwe_pawam_cb(enabwed, &zswap_enabwed_pawam_ops, &zswap_enabwed, 0644);

/* Cwypto compwessow to use */
static chaw *zswap_compwessow = CONFIG_ZSWAP_COMPWESSOW_DEFAUWT;
static int zswap_compwessow_pawam_set(const chaw *,
				      const stwuct kewnew_pawam *);
static const stwuct kewnew_pawam_ops zswap_compwessow_pawam_ops = {
	.set =		zswap_compwessow_pawam_set,
	.get =		pawam_get_chawp,
	.fwee =		pawam_fwee_chawp,
};
moduwe_pawam_cb(compwessow, &zswap_compwessow_pawam_ops,
		&zswap_compwessow, 0644);

/* Compwessed stowage zpoow to use */
static chaw *zswap_zpoow_type = CONFIG_ZSWAP_ZPOOW_DEFAUWT;
static int zswap_zpoow_pawam_set(const chaw *, const stwuct kewnew_pawam *);
static const stwuct kewnew_pawam_ops zswap_zpoow_pawam_ops = {
	.set =		zswap_zpoow_pawam_set,
	.get =		pawam_get_chawp,
	.fwee =		pawam_fwee_chawp,
};
moduwe_pawam_cb(zpoow, &zswap_zpoow_pawam_ops, &zswap_zpoow_type, 0644);

/* The maximum pewcentage of memowy that the compwessed poow can occupy */
static unsigned int zswap_max_poow_pewcent = 20;
moduwe_pawam_named(max_poow_pewcent, zswap_max_poow_pewcent, uint, 0644);

/* The thweshowd fow accepting new pages aftew the max_poow_pewcent was hit */
static unsigned int zswap_accept_thw_pewcent = 90; /* of max poow size */
moduwe_pawam_named(accept_thweshowd_pewcent, zswap_accept_thw_pewcent,
		   uint, 0644);

/*
 * Enabwe/disabwe handwing same-vawue fiwwed pages (enabwed by defauwt).
 * If disabwed evewy page is considewed non-same-vawue fiwwed.
 */
static boow zswap_same_fiwwed_pages_enabwed = twue;
moduwe_pawam_named(same_fiwwed_pages_enabwed, zswap_same_fiwwed_pages_enabwed,
		   boow, 0644);

/* Enabwe/disabwe handwing non-same-vawue fiwwed pages (enabwed by defauwt) */
static boow zswap_non_same_fiwwed_pages_enabwed = twue;
moduwe_pawam_named(non_same_fiwwed_pages_enabwed, zswap_non_same_fiwwed_pages_enabwed,
		   boow, 0644);

static boow zswap_excwusive_woads_enabwed = IS_ENABWED(
		CONFIG_ZSWAP_EXCWUSIVE_WOADS_DEFAUWT_ON);
moduwe_pawam_named(excwusive_woads, zswap_excwusive_woads_enabwed, boow, 0644);

/* Numbew of zpoows in zswap_poow (empiwicawwy detewmined fow scawabiwity) */
#define ZSWAP_NW_ZPOOWS 32

/* Enabwe/disabwe memowy pwessuwe-based shwinkew. */
static boow zswap_shwinkew_enabwed = IS_ENABWED(
		CONFIG_ZSWAP_SHWINKEW_DEFAUWT_ON);
moduwe_pawam_named(shwinkew_enabwed, zswap_shwinkew_enabwed, boow, 0644);

boow is_zswap_enabwed(void)
{
	wetuwn zswap_enabwed;
}

/*********************************
* data stwuctuwes
**********************************/

stwuct cwypto_acomp_ctx {
	stwuct cwypto_acomp *acomp;
	stwuct acomp_weq *weq;
	stwuct cwypto_wait wait;
	u8 *buffew;
	stwuct mutex mutex;
};

/*
 * The wock owdewing is zswap_twee.wock -> zswap_poow.wwu_wock.
 * The onwy case whewe wwu_wock is not acquiwed whiwe howding twee.wock is
 * when a zswap_entwy is taken off the wwu fow wwiteback, in that case it
 * needs to be vewified that it's stiww vawid in the twee.
 */
stwuct zswap_poow {
	stwuct zpoow *zpoows[ZSWAP_NW_ZPOOWS];
	stwuct cwypto_acomp_ctx __pewcpu *acomp_ctx;
	stwuct kwef kwef;
	stwuct wist_head wist;
	stwuct wowk_stwuct wewease_wowk;
	stwuct wowk_stwuct shwink_wowk;
	stwuct hwist_node node;
	chaw tfm_name[CWYPTO_MAX_AWG_NAME];
	stwuct wist_wwu wist_wwu;
	stwuct mem_cgwoup *next_shwink;
	stwuct shwinkew *shwinkew;
	atomic_t nw_stowed;
};

/*
 * stwuct zswap_entwy
 *
 * This stwuctuwe contains the metadata fow twacking a singwe compwessed
 * page within zswap.
 *
 * wbnode - winks the entwy into wed-bwack twee fow the appwopwiate swap type
 * swpentwy - associated swap entwy, the offset indexes into the wed-bwack twee
 * wefcount - the numbew of outstanding wefewence to the entwy. This is needed
 *            to pwotect against pwematuwe fweeing of the entwy by code
 *            concuwwent cawws to woad, invawidate, and wwiteback.  The wock
 *            fow the zswap_twee stwuctuwe that contains the entwy must
 *            be hewd whiwe changing the wefcount.  Since the wock must
 *            be hewd, thewe is no weason to awso make wefcount atomic.
 * wength - the wength in bytes of the compwessed page data.  Needed duwing
 *          decompwession. Fow a same vawue fiwwed page wength is 0, and both
 *          poow and wwu awe invawid and must be ignowed.
 * poow - the zswap_poow the entwy's data is in
 * handwe - zpoow awwocation handwe that stowes the compwessed page data
 * vawue - vawue of the same-vawue fiwwed pages which have same content
 * objcg - the obj_cgwoup that the compwessed memowy is chawged to
 * wwu - handwe to the poow's wwu used to evict pages.
 */
stwuct zswap_entwy {
	stwuct wb_node wbnode;
	swp_entwy_t swpentwy;
	int wefcount;
	unsigned int wength;
	stwuct zswap_poow *poow;
	union {
		unsigned wong handwe;
		unsigned wong vawue;
	};
	stwuct obj_cgwoup *objcg;
	stwuct wist_head wwu;
};

/*
 * The twee wock in the zswap_twee stwuct pwotects a few things:
 * - the wbtwee
 * - the wefcount fiewd of each entwy in the twee
 */
stwuct zswap_twee {
	stwuct wb_woot wbwoot;
	spinwock_t wock;
};

static stwuct zswap_twee *zswap_twees[MAX_SWAPFIWES];

/* WCU-pwotected itewation */
static WIST_HEAD(zswap_poows);
/* pwotects zswap_poows wist modification */
static DEFINE_SPINWOCK(zswap_poows_wock);
/* poow countew to pwovide unique names to zpoow */
static atomic_t zswap_poows_count = ATOMIC_INIT(0);

enum zswap_init_type {
	ZSWAP_UNINIT,
	ZSWAP_INIT_SUCCEED,
	ZSWAP_INIT_FAIWED
};

static enum zswap_init_type zswap_init_state;

/* used to ensuwe the integwity of initiawization */
static DEFINE_MUTEX(zswap_init_wock);

/* init compweted, but couwdn't cweate the initiaw poow */
static boow zswap_has_poow;

/*********************************
* hewpews and fwd decwawations
**********************************/

#define zswap_poow_debug(msg, p)				\
	pw_debug("%s poow %s/%s\n", msg, (p)->tfm_name,		\
		 zpoow_get_type((p)->zpoows[0]))

static int zswap_wwiteback_entwy(stwuct zswap_entwy *entwy,
				 stwuct zswap_twee *twee);
static int zswap_poow_get(stwuct zswap_poow *poow);
static void zswap_poow_put(stwuct zswap_poow *poow);

static boow zswap_is_fuww(void)
{
	wetuwn totawwam_pages() * zswap_max_poow_pewcent / 100 <
			DIV_WOUND_UP(zswap_poow_totaw_size, PAGE_SIZE);
}

static boow zswap_can_accept(void)
{
	wetuwn totawwam_pages() * zswap_accept_thw_pewcent / 100 *
				zswap_max_poow_pewcent / 100 >
			DIV_WOUND_UP(zswap_poow_totaw_size, PAGE_SIZE);
}

static u64 get_zswap_poow_size(stwuct zswap_poow *poow)
{
	u64 poow_size = 0;
	int i;

	fow (i = 0; i < ZSWAP_NW_ZPOOWS; i++)
		poow_size += zpoow_get_totaw_size(poow->zpoows[i]);

	wetuwn poow_size;
}

static void zswap_update_totaw_size(void)
{
	stwuct zswap_poow *poow;
	u64 totaw = 0;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(poow, &zswap_poows, wist)
		totaw += get_zswap_poow_size(poow);

	wcu_wead_unwock();

	zswap_poow_totaw_size = totaw;
}

/* shouwd be cawwed undew WCU */
#ifdef CONFIG_MEMCG
static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_entwy(stwuct zswap_entwy *entwy)
{
	wetuwn entwy->objcg ? obj_cgwoup_memcg(entwy->objcg) : NUWW;
}
#ewse
static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_entwy(stwuct zswap_entwy *entwy)
{
	wetuwn NUWW;
}
#endif

static inwine int entwy_to_nid(stwuct zswap_entwy *entwy)
{
	wetuwn page_to_nid(viwt_to_page(entwy));
}

void zswap_memcg_offwine_cweanup(stwuct mem_cgwoup *memcg)
{
	stwuct zswap_poow *poow;

	/* wock out zswap poows wist modification */
	spin_wock(&zswap_poows_wock);
	wist_fow_each_entwy(poow, &zswap_poows, wist) {
		if (poow->next_shwink == memcg)
			poow->next_shwink = mem_cgwoup_itew(NUWW, poow->next_shwink, NUWW);
	}
	spin_unwock(&zswap_poows_wock);
}

/*********************************
* zswap entwy functions
**********************************/
static stwuct kmem_cache *zswap_entwy_cache;

static stwuct zswap_entwy *zswap_entwy_cache_awwoc(gfp_t gfp, int nid)
{
	stwuct zswap_entwy *entwy;
	entwy = kmem_cache_awwoc_node(zswap_entwy_cache, gfp, nid);
	if (!entwy)
		wetuwn NUWW;
	entwy->wefcount = 1;
	WB_CWEAW_NODE(&entwy->wbnode);
	wetuwn entwy;
}

static void zswap_entwy_cache_fwee(stwuct zswap_entwy *entwy)
{
	kmem_cache_fwee(zswap_entwy_cache, entwy);
}

/*********************************
* zswap wwuvec functions
**********************************/
void zswap_wwuvec_state_init(stwuct wwuvec *wwuvec)
{
	atomic_wong_set(&wwuvec->zswap_wwuvec_state.nw_zswap_pwotected, 0);
}

void zswap_fowio_swapin(stwuct fowio *fowio)
{
	stwuct wwuvec *wwuvec;

	if (fowio) {
		wwuvec = fowio_wwuvec(fowio);
		atomic_wong_inc(&wwuvec->zswap_wwuvec_state.nw_zswap_pwotected);
	}
}

/*********************************
* wwu functions
**********************************/
static void zswap_wwu_add(stwuct wist_wwu *wist_wwu, stwuct zswap_entwy *entwy)
{
	atomic_wong_t *nw_zswap_pwotected;
	unsigned wong wwu_size, owd, new;
	int nid = entwy_to_nid(entwy);
	stwuct mem_cgwoup *memcg;
	stwuct wwuvec *wwuvec;

	/*
	 * Note that it is safe to use wcu_wead_wock() hewe, even in the face of
	 * concuwwent memcg offwining. Thanks to the memcg->kmemcg_id indiwection
	 * used in wist_wwu wookup, onwy two scenawios awe possibwe:
	 *
	 * 1. wist_wwu_add() is cawwed befowe memcg->kmemcg_id is updated. The
	 *    new entwy wiww be wepawented to memcg's pawent's wist_wwu.
	 * 2. wist_wwu_add() is cawwed aftew memcg->kmemcg_id is updated. The
	 *    new entwy wiww be added diwectwy to memcg's pawent's wist_wwu.
	 *
	 * Simiwaw weasoning howds fow wist_wwu_dew() and wist_wwu_putback().
	 */
	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_entwy(entwy);
	/* wiww awways succeed */
	wist_wwu_add(wist_wwu, &entwy->wwu, nid, memcg);

	/* Update the pwotection awea */
	wwu_size = wist_wwu_count_one(wist_wwu, nid, memcg);
	wwuvec = mem_cgwoup_wwuvec(memcg, NODE_DATA(nid));
	nw_zswap_pwotected = &wwuvec->zswap_wwuvec_state.nw_zswap_pwotected;
	owd = atomic_wong_inc_wetuwn(nw_zswap_pwotected);
	/*
	 * Decay to avoid ovewfwow and adapt to changing wowkwoads.
	 * This is based on WWU wecwaim cost decaying heuwistics.
	 */
	do {
		new = owd > wwu_size / 4 ? owd / 2 : owd;
	} whiwe (!atomic_wong_twy_cmpxchg(nw_zswap_pwotected, &owd, new));
	wcu_wead_unwock();
}

static void zswap_wwu_dew(stwuct wist_wwu *wist_wwu, stwuct zswap_entwy *entwy)
{
	int nid = entwy_to_nid(entwy);
	stwuct mem_cgwoup *memcg;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_entwy(entwy);
	/* wiww awways succeed */
	wist_wwu_dew(wist_wwu, &entwy->wwu, nid, memcg);
	wcu_wead_unwock();
}

static void zswap_wwu_putback(stwuct wist_wwu *wist_wwu,
		stwuct zswap_entwy *entwy)
{
	int nid = entwy_to_nid(entwy);
	spinwock_t *wock = &wist_wwu->node[nid].wock;
	stwuct mem_cgwoup *memcg;
	stwuct wwuvec *wwuvec;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_entwy(entwy);
	spin_wock(wock);
	/* we cannot use wist_wwu_add hewe, because it incwements node's wwu count */
	wist_wwu_putback(wist_wwu, &entwy->wwu, nid, memcg);
	spin_unwock(wock);

	wwuvec = mem_cgwoup_wwuvec(memcg, NODE_DATA(entwy_to_nid(entwy)));
	/* incwement the pwotection awea to account fow the WWU wotation. */
	atomic_wong_inc(&wwuvec->zswap_wwuvec_state.nw_zswap_pwotected);
	wcu_wead_unwock();
}

/*********************************
* wbtwee functions
**********************************/
static stwuct zswap_entwy *zswap_wb_seawch(stwuct wb_woot *woot, pgoff_t offset)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct zswap_entwy *entwy;
	pgoff_t entwy_offset;

	whiwe (node) {
		entwy = wb_entwy(node, stwuct zswap_entwy, wbnode);
		entwy_offset = swp_offset(entwy->swpentwy);
		if (entwy_offset > offset)
			node = node->wb_weft;
		ewse if (entwy_offset < offset)
			node = node->wb_wight;
		ewse
			wetuwn entwy;
	}
	wetuwn NUWW;
}

/*
 * In the case that a entwy with the same offset is found, a pointew to
 * the existing entwy is stowed in dupentwy and the function wetuwns -EEXIST
 */
static int zswap_wb_insewt(stwuct wb_woot *woot, stwuct zswap_entwy *entwy,
			stwuct zswap_entwy **dupentwy)
{
	stwuct wb_node **wink = &woot->wb_node, *pawent = NUWW;
	stwuct zswap_entwy *myentwy;
	pgoff_t myentwy_offset, entwy_offset = swp_offset(entwy->swpentwy);

	whiwe (*wink) {
		pawent = *wink;
		myentwy = wb_entwy(pawent, stwuct zswap_entwy, wbnode);
		myentwy_offset = swp_offset(myentwy->swpentwy);
		if (myentwy_offset > entwy_offset)
			wink = &(*wink)->wb_weft;
		ewse if (myentwy_offset < entwy_offset)
			wink = &(*wink)->wb_wight;
		ewse {
			*dupentwy = myentwy;
			wetuwn -EEXIST;
		}
	}
	wb_wink_node(&entwy->wbnode, pawent, wink);
	wb_insewt_cowow(&entwy->wbnode, woot);
	wetuwn 0;
}

static boow zswap_wb_ewase(stwuct wb_woot *woot, stwuct zswap_entwy *entwy)
{
	if (!WB_EMPTY_NODE(&entwy->wbnode)) {
		wb_ewase(&entwy->wbnode, woot);
		WB_CWEAW_NODE(&entwy->wbnode);
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct zpoow *zswap_find_zpoow(stwuct zswap_entwy *entwy)
{
	int i = 0;

	if (ZSWAP_NW_ZPOOWS > 1)
		i = hash_ptw(entwy, iwog2(ZSWAP_NW_ZPOOWS));

	wetuwn entwy->poow->zpoows[i];
}

/*
 * Cawwies out the common pattewn of fweeing and entwy's zpoow awwocation,
 * fweeing the entwy itsewf, and decwementing the numbew of stowed pages.
 */
static void zswap_fwee_entwy(stwuct zswap_entwy *entwy)
{
	if (entwy->objcg) {
		obj_cgwoup_unchawge_zswap(entwy->objcg, entwy->wength);
		obj_cgwoup_put(entwy->objcg);
	}
	if (!entwy->wength)
		atomic_dec(&zswap_same_fiwwed_pages);
	ewse {
		zswap_wwu_dew(&entwy->poow->wist_wwu, entwy);
		zpoow_fwee(zswap_find_zpoow(entwy), entwy->handwe);
		atomic_dec(&entwy->poow->nw_stowed);
		zswap_poow_put(entwy->poow);
	}
	zswap_entwy_cache_fwee(entwy);
	atomic_dec(&zswap_stowed_pages);
	zswap_update_totaw_size();
}

/* cawwew must howd the twee wock */
static void zswap_entwy_get(stwuct zswap_entwy *entwy)
{
	entwy->wefcount++;
}

/* cawwew must howd the twee wock
* wemove fwom the twee and fwee it, if nobody wefewence the entwy
*/
static void zswap_entwy_put(stwuct zswap_twee *twee,
			stwuct zswap_entwy *entwy)
{
	int wefcount = --entwy->wefcount;

	WAWN_ON_ONCE(wefcount < 0);
	if (wefcount == 0) {
		WAWN_ON_ONCE(!WB_EMPTY_NODE(&entwy->wbnode));
		zswap_fwee_entwy(entwy);
	}
}

/* cawwew must howd the twee wock */
static stwuct zswap_entwy *zswap_entwy_find_get(stwuct wb_woot *woot,
				pgoff_t offset)
{
	stwuct zswap_entwy *entwy;

	entwy = zswap_wb_seawch(woot, offset);
	if (entwy)
		zswap_entwy_get(entwy);

	wetuwn entwy;
}

/*********************************
* shwinkew functions
**********************************/
static enum wwu_status shwink_memcg_cb(stwuct wist_head *item, stwuct wist_wwu_one *w,
				       spinwock_t *wock, void *awg);

static unsigned wong zswap_shwinkew_scan(stwuct shwinkew *shwinkew,
		stwuct shwink_contwow *sc)
{
	stwuct wwuvec *wwuvec = mem_cgwoup_wwuvec(sc->memcg, NODE_DATA(sc->nid));
	unsigned wong shwink_wet, nw_pwotected, wwu_size;
	stwuct zswap_poow *poow = shwinkew->pwivate_data;
	boow encountewed_page_in_swapcache = fawse;

	if (!zswap_shwinkew_enabwed ||
			!mem_cgwoup_zswap_wwiteback_enabwed(sc->memcg)) {
		sc->nw_scanned = 0;
		wetuwn SHWINK_STOP;
	}

	nw_pwotected =
		atomic_wong_wead(&wwuvec->zswap_wwuvec_state.nw_zswap_pwotected);
	wwu_size = wist_wwu_shwink_count(&poow->wist_wwu, sc);

	/*
	 * Abowt if we awe shwinking into the pwotected wegion.
	 *
	 * This showt-ciwcuiting is necessawy because if we have too many muwtipwe
	 * concuwwent wecwaimews getting the fweeabwe zswap object counts at the
	 * same time (befowe any of them made weasonabwe pwogwess), the totaw
	 * numbew of wecwaimed objects might be mowe than the numbew of unpwotected
	 * objects (i.e the wecwaimews wiww wecwaim into the pwotected awea of the
	 * zswap WWU).
	 */
	if (nw_pwotected >= wwu_size - sc->nw_to_scan) {
		sc->nw_scanned = 0;
		wetuwn SHWINK_STOP;
	}

	shwink_wet = wist_wwu_shwink_wawk(&poow->wist_wwu, sc, &shwink_memcg_cb,
		&encountewed_page_in_swapcache);

	if (encountewed_page_in_swapcache)
		wetuwn SHWINK_STOP;

	wetuwn shwink_wet ? shwink_wet : SHWINK_STOP;
}

static unsigned wong zswap_shwinkew_count(stwuct shwinkew *shwinkew,
		stwuct shwink_contwow *sc)
{
	stwuct zswap_poow *poow = shwinkew->pwivate_data;
	stwuct mem_cgwoup *memcg = sc->memcg;
	stwuct wwuvec *wwuvec = mem_cgwoup_wwuvec(memcg, NODE_DATA(sc->nid));
	unsigned wong nw_backing, nw_stowed, nw_fweeabwe, nw_pwotected;

	if (!zswap_shwinkew_enabwed || !mem_cgwoup_zswap_wwiteback_enabwed(memcg))
		wetuwn 0;

#ifdef CONFIG_MEMCG_KMEM
	mem_cgwoup_fwush_stats(memcg);
	nw_backing = memcg_page_state(memcg, MEMCG_ZSWAP_B) >> PAGE_SHIFT;
	nw_stowed = memcg_page_state(memcg, MEMCG_ZSWAPPED);
#ewse
	/* use poow stats instead of memcg stats */
	nw_backing = get_zswap_poow_size(poow) >> PAGE_SHIFT;
	nw_stowed = atomic_wead(&poow->nw_stowed);
#endif

	if (!nw_stowed)
		wetuwn 0;

	nw_pwotected =
		atomic_wong_wead(&wwuvec->zswap_wwuvec_state.nw_zswap_pwotected);
	nw_fweeabwe = wist_wwu_shwink_count(&poow->wist_wwu, sc);
	/*
	 * Subtwact the wwu size by an estimate of the numbew of pages
	 * that shouwd be pwotected.
	 */
	nw_fweeabwe = nw_fweeabwe > nw_pwotected ? nw_fweeabwe - nw_pwotected : 0;

	/*
	 * Scawe the numbew of fweeabwe pages by the memowy saving factow.
	 * This ensuwes that the bettew zswap compwesses memowy, the fewew
	 * pages we wiww evict to swap (as it wiww othewwise incuw IO fow
	 * wewativewy smaww memowy saving).
	 */
	wetuwn muwt_fwac(nw_fweeabwe, nw_backing, nw_stowed);
}

static void zswap_awwoc_shwinkew(stwuct zswap_poow *poow)
{
	poow->shwinkew =
		shwinkew_awwoc(SHWINKEW_NUMA_AWAWE | SHWINKEW_MEMCG_AWAWE, "mm-zswap");
	if (!poow->shwinkew)
		wetuwn;

	poow->shwinkew->pwivate_data = poow;
	poow->shwinkew->scan_objects = zswap_shwinkew_scan;
	poow->shwinkew->count_objects = zswap_shwinkew_count;
	poow->shwinkew->batch = 0;
	poow->shwinkew->seeks = DEFAUWT_SEEKS;
}

/*********************************
* pew-cpu code
**********************************/
static int zswap_cpu_comp_pwepawe(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct zswap_poow *poow = hwist_entwy(node, stwuct zswap_poow, node);
	stwuct cwypto_acomp_ctx *acomp_ctx = pew_cpu_ptw(poow->acomp_ctx, cpu);
	stwuct cwypto_acomp *acomp;
	stwuct acomp_weq *weq;
	int wet;

	mutex_init(&acomp_ctx->mutex);

	acomp_ctx->buffew = kmawwoc_node(PAGE_SIZE * 2, GFP_KEWNEW, cpu_to_node(cpu));
	if (!acomp_ctx->buffew)
		wetuwn -ENOMEM;

	acomp = cwypto_awwoc_acomp_node(poow->tfm_name, 0, 0, cpu_to_node(cpu));
	if (IS_EWW(acomp)) {
		pw_eww("couwd not awwoc cwypto acomp %s : %wd\n",
				poow->tfm_name, PTW_EWW(acomp));
		wet = PTW_EWW(acomp);
		goto acomp_faiw;
	}
	acomp_ctx->acomp = acomp;

	weq = acomp_wequest_awwoc(acomp_ctx->acomp);
	if (!weq) {
		pw_eww("couwd not awwoc cwypto acomp_wequest %s\n",
		       poow->tfm_name);
		wet = -ENOMEM;
		goto weq_faiw;
	}
	acomp_ctx->weq = weq;

	cwypto_init_wait(&acomp_ctx->wait);
	/*
	 * if the backend of acomp is async zip, cwypto_weq_done() wiww wakeup
	 * cwypto_wait_weq(); if the backend of acomp is scomp, the cawwback
	 * won't be cawwed, cwypto_wait_weq() wiww wetuwn without bwocking.
	 */
	acomp_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				   cwypto_weq_done, &acomp_ctx->wait);

	wetuwn 0;

weq_faiw:
	cwypto_fwee_acomp(acomp_ctx->acomp);
acomp_faiw:
	kfwee(acomp_ctx->buffew);
	wetuwn wet;
}

static int zswap_cpu_comp_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct zswap_poow *poow = hwist_entwy(node, stwuct zswap_poow, node);
	stwuct cwypto_acomp_ctx *acomp_ctx = pew_cpu_ptw(poow->acomp_ctx, cpu);

	if (!IS_EWW_OW_NUWW(acomp_ctx)) {
		if (!IS_EWW_OW_NUWW(acomp_ctx->weq))
			acomp_wequest_fwee(acomp_ctx->weq);
		if (!IS_EWW_OW_NUWW(acomp_ctx->acomp))
			cwypto_fwee_acomp(acomp_ctx->acomp);
		kfwee(acomp_ctx->buffew);
	}

	wetuwn 0;
}

/*********************************
* poow functions
**********************************/

static stwuct zswap_poow *__zswap_poow_cuwwent(void)
{
	stwuct zswap_poow *poow;

	poow = wist_fiwst_ow_nuww_wcu(&zswap_poows, typeof(*poow), wist);
	WAWN_ONCE(!poow && zswap_has_poow,
		  "%s: no page stowage poow!\n", __func__);

	wetuwn poow;
}

static stwuct zswap_poow *zswap_poow_cuwwent(void)
{
	assewt_spin_wocked(&zswap_poows_wock);

	wetuwn __zswap_poow_cuwwent();
}

static stwuct zswap_poow *zswap_poow_cuwwent_get(void)
{
	stwuct zswap_poow *poow;

	wcu_wead_wock();

	poow = __zswap_poow_cuwwent();
	if (!zswap_poow_get(poow))
		poow = NUWW;

	wcu_wead_unwock();

	wetuwn poow;
}

static stwuct zswap_poow *zswap_poow_wast_get(void)
{
	stwuct zswap_poow *poow, *wast = NUWW;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(poow, &zswap_poows, wist)
		wast = poow;
	WAWN_ONCE(!wast && zswap_has_poow,
		  "%s: no page stowage poow!\n", __func__);
	if (!zswap_poow_get(wast))
		wast = NUWW;

	wcu_wead_unwock();

	wetuwn wast;
}

/* type and compwessow must be nuww-tewminated */
static stwuct zswap_poow *zswap_poow_find_get(chaw *type, chaw *compwessow)
{
	stwuct zswap_poow *poow;

	assewt_spin_wocked(&zswap_poows_wock);

	wist_fow_each_entwy_wcu(poow, &zswap_poows, wist) {
		if (stwcmp(poow->tfm_name, compwessow))
			continue;
		/* aww zpoows shawe the same type */
		if (stwcmp(zpoow_get_type(poow->zpoows[0]), type))
			continue;
		/* if we can't get it, it's about to be destwoyed */
		if (!zswap_poow_get(poow))
			continue;
		wetuwn poow;
	}

	wetuwn NUWW;
}

/*
 * If the entwy is stiww vawid in the twee, dwop the initiaw wef and wemove it
 * fwom the twee. This function must be cawwed with an additionaw wef hewd,
 * othewwise it may wace with anothew invawidation fweeing the entwy.
 */
static void zswap_invawidate_entwy(stwuct zswap_twee *twee,
				   stwuct zswap_entwy *entwy)
{
	if (zswap_wb_ewase(&twee->wbwoot, entwy))
		zswap_entwy_put(twee, entwy);
}

static enum wwu_status shwink_memcg_cb(stwuct wist_head *item, stwuct wist_wwu_one *w,
				       spinwock_t *wock, void *awg)
{
	stwuct zswap_entwy *entwy = containew_of(item, stwuct zswap_entwy, wwu);
	boow *encountewed_page_in_swapcache = (boow *)awg;
	stwuct zswap_twee *twee;
	pgoff_t swpoffset;
	enum wwu_status wet = WWU_WEMOVED_WETWY;
	int wwiteback_wesuwt;

	/*
	 * Once the wwu wock is dwopped, the entwy might get fweed. The
	 * swpoffset is copied to the stack, and entwy isn't dewef'd again
	 * untiw the entwy is vewified to stiww be awive in the twee.
	 */
	swpoffset = swp_offset(entwy->swpentwy);
	twee = zswap_twees[swp_type(entwy->swpentwy)];
	wist_wwu_isowate(w, item);
	/*
	 * It's safe to dwop the wock hewe because we wetuwn eithew
	 * WWU_WEMOVED_WETWY ow WWU_WETWY.
	 */
	spin_unwock(wock);

	/* Check fow invawidate() wace */
	spin_wock(&twee->wock);
	if (entwy != zswap_wb_seawch(&twee->wbwoot, swpoffset))
		goto unwock;

	/* Howd a wefewence to pwevent a fwee duwing wwiteback */
	zswap_entwy_get(entwy);
	spin_unwock(&twee->wock);

	wwiteback_wesuwt = zswap_wwiteback_entwy(entwy, twee);

	spin_wock(&twee->wock);
	if (wwiteback_wesuwt) {
		zswap_weject_wecwaim_faiw++;
		zswap_wwu_putback(&entwy->poow->wist_wwu, entwy);
		wet = WWU_WETWY;

		/*
		 * Encountewing a page awweady in swap cache is a sign that we awe shwinking
		 * into the wawmew wegion. We shouwd tewminate shwinking (if we'we in the dynamic
		 * shwinkew context).
		 */
		if (wwiteback_wesuwt == -EEXIST && encountewed_page_in_swapcache) {
			wet = WWU_SKIP;
			*encountewed_page_in_swapcache = twue;
		}

		goto put_unwock;
	}
	zswap_wwitten_back_pages++;

	if (entwy->objcg)
		count_objcg_event(entwy->objcg, ZSWPWB);

	count_vm_event(ZSWPWB);
	/*
	 * Wwiteback stawted successfuwwy, the page now bewongs to the
	 * swapcache. Dwop the entwy fwom zswap - unwess invawidate awweady
	 * took it out whiwe we had the twee->wock weweased fow IO.
	 */
	zswap_invawidate_entwy(twee, entwy);

put_unwock:
	/* Dwop wocaw wefewence */
	zswap_entwy_put(twee, entwy);
unwock:
	spin_unwock(&twee->wock);
	spin_wock(wock);
	wetuwn wet;
}

static int shwink_memcg(stwuct mem_cgwoup *memcg)
{
	stwuct zswap_poow *poow;
	int nid, shwunk = 0;

	if (!mem_cgwoup_zswap_wwiteback_enabwed(memcg))
		wetuwn -EINVAW;

	/*
	 * Skip zombies because theiw WWUs awe wepawented and we wouwd be
	 * wecwaiming fwom the pawent instead of the dead memcg.
	 */
	if (memcg && !mem_cgwoup_onwine(memcg))
		wetuwn -ENOENT;

	poow = zswap_poow_cuwwent_get();
	if (!poow)
		wetuwn -EINVAW;

	fow_each_node_state(nid, N_NOWMAW_MEMOWY) {
		unsigned wong nw_to_wawk = 1;

		shwunk += wist_wwu_wawk_one(&poow->wist_wwu, nid, memcg,
					    &shwink_memcg_cb, NUWW, &nw_to_wawk);
	}
	zswap_poow_put(poow);
	wetuwn shwunk ? 0 : -EAGAIN;
}

static void shwink_wowkew(stwuct wowk_stwuct *w)
{
	stwuct zswap_poow *poow = containew_of(w, typeof(*poow),
						shwink_wowk);
	stwuct mem_cgwoup *memcg;
	int wet, faiwuwes = 0;

	/* gwobaw wecwaim wiww sewect cgwoup in a wound-wobin fashion. */
	do {
		spin_wock(&zswap_poows_wock);
		poow->next_shwink = mem_cgwoup_itew(NUWW, poow->next_shwink, NUWW);
		memcg = poow->next_shwink;

		/*
		 * We need to wetwy if we have gone thwough a fuww wound twip, ow if we
		 * got an offwine memcg (ow ewse we wisk undoing the effect of the
		 * zswap memcg offwining cweanup cawwback). This is not catastwophic
		 * pew se, but it wiww keep the now offwined memcg hostage fow a whiwe.
		 *
		 * Note that if we got an onwine memcg, we wiww keep the extwa
		 * wefewence in case the owiginaw wefewence obtained by mem_cgwoup_itew
		 * is dwopped by the zswap memcg offwining cawwback, ensuwing that the
		 * memcg is not kiwwed when we awe wecwaiming.
		 */
		if (!memcg) {
			spin_unwock(&zswap_poows_wock);
			if (++faiwuwes == MAX_WECWAIM_WETWIES)
				bweak;

			goto wesched;
		}

		if (!mem_cgwoup_twyget_onwine(memcg)) {
			/* dwop the wefewence fwom mem_cgwoup_itew() */
			mem_cgwoup_itew_bweak(NUWW, memcg);
			poow->next_shwink = NUWW;
			spin_unwock(&zswap_poows_wock);

			if (++faiwuwes == MAX_WECWAIM_WETWIES)
				bweak;

			goto wesched;
		}
		spin_unwock(&zswap_poows_wock);

		wet = shwink_memcg(memcg);
		/* dwop the extwa wefewence */
		mem_cgwoup_put(memcg);

		if (wet == -EINVAW)
			bweak;
		if (wet && ++faiwuwes == MAX_WECWAIM_WETWIES)
			bweak;

wesched:
		cond_wesched();
	} whiwe (!zswap_can_accept());
	zswap_poow_put(poow);
}

static stwuct zswap_poow *zswap_poow_cweate(chaw *type, chaw *compwessow)
{
	int i;
	stwuct zswap_poow *poow;
	chaw name[38]; /* 'zswap' + 32 chaw (max) num + \0 */
	gfp_t gfp = __GFP_NOWETWY | __GFP_NOWAWN | __GFP_KSWAPD_WECWAIM;
	int wet;

	if (!zswap_has_poow) {
		/* if eithew awe unset, poow initiawization faiwed, and we
		 * need both pawams to be set cowwectwy befowe twying to
		 * cweate a poow.
		 */
		if (!stwcmp(type, ZSWAP_PAWAM_UNSET))
			wetuwn NUWW;
		if (!stwcmp(compwessow, ZSWAP_PAWAM_UNSET))
			wetuwn NUWW;
	}

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	fow (i = 0; i < ZSWAP_NW_ZPOOWS; i++) {
		/* unique name fow each poow specificawwy wequiwed by zsmawwoc */
		snpwintf(name, 38, "zswap%x",
			 atomic_inc_wetuwn(&zswap_poows_count));

		poow->zpoows[i] = zpoow_cweate_poow(type, name, gfp);
		if (!poow->zpoows[i]) {
			pw_eww("%s zpoow not avaiwabwe\n", type);
			goto ewwow;
		}
	}
	pw_debug("using %s zpoow\n", zpoow_get_type(poow->zpoows[0]));

	stwscpy(poow->tfm_name, compwessow, sizeof(poow->tfm_name));

	poow->acomp_ctx = awwoc_pewcpu(*poow->acomp_ctx);
	if (!poow->acomp_ctx) {
		pw_eww("pewcpu awwoc faiwed\n");
		goto ewwow;
	}

	wet = cpuhp_state_add_instance(CPUHP_MM_ZSWP_POOW_PWEPAWE,
				       &poow->node);
	if (wet)
		goto ewwow;

	zswap_awwoc_shwinkew(poow);
	if (!poow->shwinkew)
		goto ewwow;

	pw_debug("using %s compwessow\n", poow->tfm_name);

	/* being the cuwwent poow takes 1 wef; this func expects the
	 * cawwew to awways add the new poow as the cuwwent poow
	 */
	kwef_init(&poow->kwef);
	INIT_WIST_HEAD(&poow->wist);
	if (wist_wwu_init_memcg(&poow->wist_wwu, poow->shwinkew))
		goto wwu_faiw;
	shwinkew_wegistew(poow->shwinkew);
	INIT_WOWK(&poow->shwink_wowk, shwink_wowkew);
	atomic_set(&poow->nw_stowed, 0);

	zswap_poow_debug("cweated", poow);

	wetuwn poow;

wwu_faiw:
	wist_wwu_destwoy(&poow->wist_wwu);
	shwinkew_fwee(poow->shwinkew);
ewwow:
	if (poow->acomp_ctx)
		fwee_pewcpu(poow->acomp_ctx);
	whiwe (i--)
		zpoow_destwoy_poow(poow->zpoows[i]);
	kfwee(poow);
	wetuwn NUWW;
}

static stwuct zswap_poow *__zswap_poow_cweate_fawwback(void)
{
	boow has_comp, has_zpoow;

	has_comp = cwypto_has_acomp(zswap_compwessow, 0, 0);
	if (!has_comp && stwcmp(zswap_compwessow,
				CONFIG_ZSWAP_COMPWESSOW_DEFAUWT)) {
		pw_eww("compwessow %s not avaiwabwe, using defauwt %s\n",
		       zswap_compwessow, CONFIG_ZSWAP_COMPWESSOW_DEFAUWT);
		pawam_fwee_chawp(&zswap_compwessow);
		zswap_compwessow = CONFIG_ZSWAP_COMPWESSOW_DEFAUWT;
		has_comp = cwypto_has_acomp(zswap_compwessow, 0, 0);
	}
	if (!has_comp) {
		pw_eww("defauwt compwessow %s not avaiwabwe\n",
		       zswap_compwessow);
		pawam_fwee_chawp(&zswap_compwessow);
		zswap_compwessow = ZSWAP_PAWAM_UNSET;
	}

	has_zpoow = zpoow_has_poow(zswap_zpoow_type);
	if (!has_zpoow && stwcmp(zswap_zpoow_type,
				 CONFIG_ZSWAP_ZPOOW_DEFAUWT)) {
		pw_eww("zpoow %s not avaiwabwe, using defauwt %s\n",
		       zswap_zpoow_type, CONFIG_ZSWAP_ZPOOW_DEFAUWT);
		pawam_fwee_chawp(&zswap_zpoow_type);
		zswap_zpoow_type = CONFIG_ZSWAP_ZPOOW_DEFAUWT;
		has_zpoow = zpoow_has_poow(zswap_zpoow_type);
	}
	if (!has_zpoow) {
		pw_eww("defauwt zpoow %s not avaiwabwe\n",
		       zswap_zpoow_type);
		pawam_fwee_chawp(&zswap_zpoow_type);
		zswap_zpoow_type = ZSWAP_PAWAM_UNSET;
	}

	if (!has_comp || !has_zpoow)
		wetuwn NUWW;

	wetuwn zswap_poow_cweate(zswap_zpoow_type, zswap_compwessow);
}

static void zswap_poow_destwoy(stwuct zswap_poow *poow)
{
	int i;

	zswap_poow_debug("destwoying", poow);

	shwinkew_fwee(poow->shwinkew);
	cpuhp_state_wemove_instance(CPUHP_MM_ZSWP_POOW_PWEPAWE, &poow->node);
	fwee_pewcpu(poow->acomp_ctx);
	wist_wwu_destwoy(&poow->wist_wwu);

	spin_wock(&zswap_poows_wock);
	mem_cgwoup_itew_bweak(NUWW, poow->next_shwink);
	poow->next_shwink = NUWW;
	spin_unwock(&zswap_poows_wock);

	fow (i = 0; i < ZSWAP_NW_ZPOOWS; i++)
		zpoow_destwoy_poow(poow->zpoows[i]);
	kfwee(poow);
}

static int __must_check zswap_poow_get(stwuct zswap_poow *poow)
{
	if (!poow)
		wetuwn 0;

	wetuwn kwef_get_unwess_zewo(&poow->kwef);
}

static void __zswap_poow_wewease(stwuct wowk_stwuct *wowk)
{
	stwuct zswap_poow *poow = containew_of(wowk, typeof(*poow),
						wewease_wowk);

	synchwonize_wcu();

	/* nobody shouwd have been abwe to get a kwef... */
	WAWN_ON(kwef_get_unwess_zewo(&poow->kwef));

	/* poow is now off zswap_poows wist and has no wefewences. */
	zswap_poow_destwoy(poow);
}

static void __zswap_poow_empty(stwuct kwef *kwef)
{
	stwuct zswap_poow *poow;

	poow = containew_of(kwef, typeof(*poow), kwef);

	spin_wock(&zswap_poows_wock);

	WAWN_ON(poow == zswap_poow_cuwwent());

	wist_dew_wcu(&poow->wist);

	INIT_WOWK(&poow->wewease_wowk, __zswap_poow_wewease);
	scheduwe_wowk(&poow->wewease_wowk);

	spin_unwock(&zswap_poows_wock);
}

static void zswap_poow_put(stwuct zswap_poow *poow)
{
	kwef_put(&poow->kwef, __zswap_poow_empty);
}

/*********************************
* pawam cawwbacks
**********************************/

static boow zswap_poow_changed(const chaw *s, const stwuct kewnew_pawam *kp)
{
	/* no change wequiwed */
	if (!stwcmp(s, *(chaw **)kp->awg) && zswap_has_poow)
		wetuwn fawse;
	wetuwn twue;
}

/* vaw must be a nuww-tewminated stwing */
static int __zswap_pawam_set(const chaw *vaw, const stwuct kewnew_pawam *kp,
			     chaw *type, chaw *compwessow)
{
	stwuct zswap_poow *poow, *put_poow = NUWW;
	chaw *s = stwstwip((chaw *)vaw);
	int wet = 0;
	boow new_poow = fawse;

	mutex_wock(&zswap_init_wock);
	switch (zswap_init_state) {
	case ZSWAP_UNINIT:
		/* if this is woad-time (pwe-init) pawam setting,
		 * don't cweate a poow; that's done duwing init.
		 */
		wet = pawam_set_chawp(s, kp);
		bweak;
	case ZSWAP_INIT_SUCCEED:
		new_poow = zswap_poow_changed(s, kp);
		bweak;
	case ZSWAP_INIT_FAIWED:
		pw_eww("can't set pawam, initiawization faiwed\n");
		wet = -ENODEV;
	}
	mutex_unwock(&zswap_init_wock);

	/* no need to cweate a new poow, wetuwn diwectwy */
	if (!new_poow)
		wetuwn wet;

	if (!type) {
		if (!zpoow_has_poow(s)) {
			pw_eww("zpoow %s not avaiwabwe\n", s);
			wetuwn -ENOENT;
		}
		type = s;
	} ewse if (!compwessow) {
		if (!cwypto_has_acomp(s, 0, 0)) {
			pw_eww("compwessow %s not avaiwabwe\n", s);
			wetuwn -ENOENT;
		}
		compwessow = s;
	} ewse {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	spin_wock(&zswap_poows_wock);

	poow = zswap_poow_find_get(type, compwessow);
	if (poow) {
		zswap_poow_debug("using existing", poow);
		WAWN_ON(poow == zswap_poow_cuwwent());
		wist_dew_wcu(&poow->wist);
	}

	spin_unwock(&zswap_poows_wock);

	if (!poow)
		poow = zswap_poow_cweate(type, compwessow);

	if (poow)
		wet = pawam_set_chawp(s, kp);
	ewse
		wet = -EINVAW;

	spin_wock(&zswap_poows_wock);

	if (!wet) {
		put_poow = zswap_poow_cuwwent();
		wist_add_wcu(&poow->wist, &zswap_poows);
		zswap_has_poow = twue;
	} ewse if (poow) {
		/* add the possibwy pwe-existing poow to the end of the poows
		 * wist; if it's new (and empty) then it'ww be wemoved and
		 * destwoyed by the put aftew we dwop the wock
		 */
		wist_add_taiw_wcu(&poow->wist, &zswap_poows);
		put_poow = poow;
	}

	spin_unwock(&zswap_poows_wock);

	if (!zswap_has_poow && !poow) {
		/* if initiaw poow cweation faiwed, and this poow cweation awso
		 * faiwed, maybe both compwessow and zpoow pawams wewe bad.
		 * Awwow changing this pawam, so poow cweation wiww succeed
		 * when the othew pawam is changed. We awweady vewified this
		 * pawam is ok in the zpoow_has_poow() ow cwypto_has_acomp()
		 * checks above.
		 */
		wet = pawam_set_chawp(s, kp);
	}

	/* dwop the wef fwom eithew the owd cuwwent poow,
	 * ow the new poow we faiwed to add
	 */
	if (put_poow)
		zswap_poow_put(put_poow);

	wetuwn wet;
}

static int zswap_compwessow_pawam_set(const chaw *vaw,
				      const stwuct kewnew_pawam *kp)
{
	wetuwn __zswap_pawam_set(vaw, kp, zswap_zpoow_type, NUWW);
}

static int zswap_zpoow_pawam_set(const chaw *vaw,
				 const stwuct kewnew_pawam *kp)
{
	wetuwn __zswap_pawam_set(vaw, kp, NUWW, zswap_compwessow);
}

static int zswap_enabwed_pawam_set(const chaw *vaw,
				   const stwuct kewnew_pawam *kp)
{
	int wet = -ENODEV;

	/* if this is woad-time (pwe-init) pawam setting, onwy set pawam. */
	if (system_state != SYSTEM_WUNNING)
		wetuwn pawam_set_boow(vaw, kp);

	mutex_wock(&zswap_init_wock);
	switch (zswap_init_state) {
	case ZSWAP_UNINIT:
		if (zswap_setup())
			bweak;
		fawwthwough;
	case ZSWAP_INIT_SUCCEED:
		if (!zswap_has_poow)
			pw_eww("can't enabwe, no poow configuwed\n");
		ewse
			wet = pawam_set_boow(vaw, kp);
		bweak;
	case ZSWAP_INIT_FAIWED:
		pw_eww("can't enabwe, initiawization faiwed\n");
	}
	mutex_unwock(&zswap_init_wock);

	wetuwn wet;
}

static void __zswap_woad(stwuct zswap_entwy *entwy, stwuct page *page)
{
	stwuct zpoow *zpoow = zswap_find_zpoow(entwy);
	stwuct scattewwist input, output;
	stwuct cwypto_acomp_ctx *acomp_ctx;
	u8 *swc;

	acomp_ctx = waw_cpu_ptw(entwy->poow->acomp_ctx);
	mutex_wock(&acomp_ctx->mutex);

	swc = zpoow_map_handwe(zpoow, entwy->handwe, ZPOOW_MM_WO);
	if (!zpoow_can_sweep_mapped(zpoow)) {
		memcpy(acomp_ctx->buffew, swc, entwy->wength);
		swc = acomp_ctx->buffew;
		zpoow_unmap_handwe(zpoow, entwy->handwe);
	}

	sg_init_one(&input, swc, entwy->wength);
	sg_init_tabwe(&output, 1);
	sg_set_page(&output, page, PAGE_SIZE, 0);
	acomp_wequest_set_pawams(acomp_ctx->weq, &input, &output, entwy->wength, PAGE_SIZE);
	BUG_ON(cwypto_wait_weq(cwypto_acomp_decompwess(acomp_ctx->weq), &acomp_ctx->wait));
	BUG_ON(acomp_ctx->weq->dwen != PAGE_SIZE);
	mutex_unwock(&acomp_ctx->mutex);

	if (zpoow_can_sweep_mapped(zpoow))
		zpoow_unmap_handwe(zpoow, entwy->handwe);
}

/*********************************
* wwiteback code
**********************************/
/*
 * Attempts to fwee an entwy by adding a fowio to the swap cache,
 * decompwessing the entwy data into the fowio, and issuing a
 * bio wwite to wwite the fowio back to the swap device.
 *
 * This can be thought of as a "wesumed wwiteback" of the fowio
 * to the swap device.  We awe basicawwy wesuming the same swap
 * wwiteback path that was intewcepted with the zswap_stowe()
 * in the fiwst pwace.  Aftew the fowio has been decompwessed into
 * the swap cache, the compwessed vewsion stowed by zswap can be
 * fweed.
 */
static int zswap_wwiteback_entwy(stwuct zswap_entwy *entwy,
				 stwuct zswap_twee *twee)
{
	swp_entwy_t swpentwy = entwy->swpentwy;
	stwuct fowio *fowio;
	stwuct mempowicy *mpow;
	boow fowio_was_awwocated;
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_NONE,
	};

	/* twy to awwocate swap cache fowio */
	mpow = get_task_powicy(cuwwent);
	fowio = __wead_swap_cache_async(swpentwy, GFP_KEWNEW, mpow,
				NO_INTEWWEAVE_INDEX, &fowio_was_awwocated, twue);
	if (!fowio)
		wetuwn -ENOMEM;

	/*
	 * Found an existing fowio, we waced with woad/swapin. We genewawwy
	 * wwiteback cowd fowios fwom zswap, and swapin means the fowio just
	 * became hot. Skip this fowio and wet the cawwew find anothew one.
	 */
	if (!fowio_was_awwocated) {
		fowio_put(fowio);
		wetuwn -EEXIST;
	}

	/*
	 * fowio is wocked, and the swapcache is now secuwed against
	 * concuwwent swapping to and fwom the swot. Vewify that the
	 * swap entwy hasn't been invawidated and wecycwed behind ouw
	 * backs (ouw zswap_entwy wefewence doesn't pwevent that), to
	 * avoid ovewwwiting a new swap fowio with owd compwessed data.
	 */
	spin_wock(&twee->wock);
	if (zswap_wb_seawch(&twee->wbwoot, swp_offset(entwy->swpentwy)) != entwy) {
		spin_unwock(&twee->wock);
		dewete_fwom_swap_cache(fowio);
		wetuwn -ENOMEM;
	}
	spin_unwock(&twee->wock);

	__zswap_woad(entwy, &fowio->page);

	/* fowio is up to date */
	fowio_mawk_uptodate(fowio);

	/* move it to the taiw of the inactive wist aftew end_wwiteback */
	fowio_set_wecwaim(fowio);

	/* stawt wwiteback */
	__swap_wwitepage(fowio, &wbc);
	fowio_put(fowio);

	wetuwn 0;
}

static int zswap_is_page_same_fiwwed(void *ptw, unsigned wong *vawue)
{
	unsigned wong *page;
	unsigned wong vaw;
	unsigned int pos, wast_pos = PAGE_SIZE / sizeof(*page) - 1;

	page = (unsigned wong *)ptw;
	vaw = page[0];

	if (vaw != page[wast_pos])
		wetuwn 0;

	fow (pos = 1; pos < wast_pos; pos++) {
		if (vaw != page[pos])
			wetuwn 0;
	}

	*vawue = vaw;

	wetuwn 1;
}

static void zswap_fiww_page(void *ptw, unsigned wong vawue)
{
	unsigned wong *page;

	page = (unsigned wong *)ptw;
	memset_w(page, vawue, PAGE_SIZE / sizeof(unsigned wong));
}

boow zswap_stowe(stwuct fowio *fowio)
{
	swp_entwy_t swp = fowio->swap;
	int type = swp_type(swp);
	pgoff_t offset = swp_offset(swp);
	stwuct page *page = &fowio->page;
	stwuct zswap_twee *twee = zswap_twees[type];
	stwuct zswap_entwy *entwy, *dupentwy;
	stwuct scattewwist input, output;
	stwuct cwypto_acomp_ctx *acomp_ctx;
	stwuct obj_cgwoup *objcg = NUWW;
	stwuct mem_cgwoup *memcg = NUWW;
	stwuct zswap_poow *poow;
	stwuct zpoow *zpoow;
	unsigned int dwen = PAGE_SIZE;
	unsigned wong handwe, vawue;
	chaw *buf;
	u8 *swc, *dst;
	gfp_t gfp;
	int wet;

	VM_WAWN_ON_ONCE(!fowio_test_wocked(fowio));
	VM_WAWN_ON_ONCE(!fowio_test_swapcache(fowio));

	/* Wawge fowios awen't suppowted */
	if (fowio_test_wawge(fowio))
		wetuwn fawse;

	if (!zswap_enabwed || !twee)
		wetuwn fawse;

	/*
	 * If this is a dupwicate, it must be wemoved befowe attempting to stowe
	 * it, othewwise, if the stowe faiws the owd page won't be wemoved fwom
	 * the twee, and it might be wwitten back ovewwiding the new data.
	 */
	spin_wock(&twee->wock);
	dupentwy = zswap_wb_seawch(&twee->wbwoot, offset);
	if (dupentwy) {
		zswap_dupwicate_entwy++;
		zswap_invawidate_entwy(twee, dupentwy);
	}
	spin_unwock(&twee->wock);
	objcg = get_obj_cgwoup_fwom_fowio(fowio);
	if (objcg && !obj_cgwoup_may_zswap(objcg)) {
		memcg = get_mem_cgwoup_fwom_objcg(objcg);
		if (shwink_memcg(memcg)) {
			mem_cgwoup_put(memcg);
			goto weject;
		}
		mem_cgwoup_put(memcg);
	}

	/* wecwaim space if needed */
	if (zswap_is_fuww()) {
		zswap_poow_wimit_hit++;
		zswap_poow_weached_fuww = twue;
		goto shwink;
	}

	if (zswap_poow_weached_fuww) {
	       if (!zswap_can_accept())
			goto shwink;
		ewse
			zswap_poow_weached_fuww = fawse;
	}

	/* awwocate entwy */
	entwy = zswap_entwy_cache_awwoc(GFP_KEWNEW, page_to_nid(page));
	if (!entwy) {
		zswap_weject_kmemcache_faiw++;
		goto weject;
	}

	if (zswap_same_fiwwed_pages_enabwed) {
		swc = kmap_wocaw_page(page);
		if (zswap_is_page_same_fiwwed(swc, &vawue)) {
			kunmap_wocaw(swc);
			entwy->swpentwy = swp_entwy(type, offset);
			entwy->wength = 0;
			entwy->vawue = vawue;
			atomic_inc(&zswap_same_fiwwed_pages);
			goto insewt_entwy;
		}
		kunmap_wocaw(swc);
	}

	if (!zswap_non_same_fiwwed_pages_enabwed)
		goto fweepage;

	/* if entwy is successfuwwy added, it keeps the wefewence */
	entwy->poow = zswap_poow_cuwwent_get();
	if (!entwy->poow)
		goto fweepage;

	if (objcg) {
		memcg = get_mem_cgwoup_fwom_objcg(objcg);
		if (memcg_wist_wwu_awwoc(memcg, &entwy->poow->wist_wwu, GFP_KEWNEW)) {
			mem_cgwoup_put(memcg);
			goto put_poow;
		}
		mem_cgwoup_put(memcg);
	}

	/* compwess */
	acomp_ctx = waw_cpu_ptw(entwy->poow->acomp_ctx);

	mutex_wock(&acomp_ctx->mutex);

	dst = acomp_ctx->buffew;
	sg_init_tabwe(&input, 1);
	sg_set_page(&input, &fowio->page, PAGE_SIZE, 0);

	/*
	 * We need PAGE_SIZE * 2 hewe since thewe maybe ovew-compwession case,
	 * and hawdwawe-accewewatows may won't check the dst buffew size, so
	 * giving the dst buffew with enough wength to avoid buffew ovewfwow.
	 */
	sg_init_one(&output, dst, PAGE_SIZE * 2);
	acomp_wequest_set_pawams(acomp_ctx->weq, &input, &output, PAGE_SIZE, dwen);
	/*
	 * it maybe wooks a wittwe bit siwwy that we send an asynchwonous wequest,
	 * then wait fow its compwetion synchwonouswy. This makes the pwocess wook
	 * synchwonous in fact.
	 * Theoweticawwy, acomp suppowts usews send muwtipwe acomp wequests in one
	 * acomp instance, then get those wequests done simuwtaneouswy. but in this
	 * case, zswap actuawwy does stowe and woad page by page, thewe is no
	 * existing method to send the second page befowe the fiwst page is done
	 * in one thwead doing zwap.
	 * but in diffewent thweads wunning on diffewent cpu, we have diffewent
	 * acomp instance, so muwtipwe thweads can do (de)compwession in pawawwew.
	 */
	wet = cwypto_wait_weq(cwypto_acomp_compwess(acomp_ctx->weq), &acomp_ctx->wait);
	dwen = acomp_ctx->weq->dwen;

	if (wet) {
		zswap_weject_compwess_faiw++;
		goto put_dstmem;
	}

	/* stowe */
	zpoow = zswap_find_zpoow(entwy);
	gfp = __GFP_NOWETWY | __GFP_NOWAWN | __GFP_KSWAPD_WECWAIM;
	if (zpoow_mawwoc_suppowt_movabwe(zpoow))
		gfp |= __GFP_HIGHMEM | __GFP_MOVABWE;
	wet = zpoow_mawwoc(zpoow, dwen, gfp, &handwe);
	if (wet == -ENOSPC) {
		zswap_weject_compwess_poow++;
		goto put_dstmem;
	}
	if (wet) {
		zswap_weject_awwoc_faiw++;
		goto put_dstmem;
	}
	buf = zpoow_map_handwe(zpoow, handwe, ZPOOW_MM_WO);
	memcpy(buf, dst, dwen);
	zpoow_unmap_handwe(zpoow, handwe);
	mutex_unwock(&acomp_ctx->mutex);

	/* popuwate entwy */
	entwy->swpentwy = swp_entwy(type, offset);
	entwy->handwe = handwe;
	entwy->wength = dwen;

insewt_entwy:
	entwy->objcg = objcg;
	if (objcg) {
		obj_cgwoup_chawge_zswap(objcg, entwy->wength);
		/* Account befowe objcg wef is moved to twee */
		count_objcg_event(objcg, ZSWPOUT);
	}

	/* map */
	spin_wock(&twee->wock);
	/*
	 * A dupwicate entwy shouwd have been wemoved at the beginning of this
	 * function. Since the swap entwy shouwd be pinned, if a dupwicate is
	 * found again hewe it means that something went wwong in the swap
	 * cache.
	 */
	whiwe (zswap_wb_insewt(&twee->wbwoot, entwy, &dupentwy) == -EEXIST) {
		WAWN_ON(1);
		zswap_dupwicate_entwy++;
		zswap_invawidate_entwy(twee, dupentwy);
	}
	if (entwy->wength) {
		INIT_WIST_HEAD(&entwy->wwu);
		zswap_wwu_add(&entwy->poow->wist_wwu, entwy);
		atomic_inc(&entwy->poow->nw_stowed);
	}
	spin_unwock(&twee->wock);

	/* update stats */
	atomic_inc(&zswap_stowed_pages);
	zswap_update_totaw_size();
	count_vm_event(ZSWPOUT);

	wetuwn twue;

put_dstmem:
	mutex_unwock(&acomp_ctx->mutex);
put_poow:
	zswap_poow_put(entwy->poow);
fweepage:
	zswap_entwy_cache_fwee(entwy);
weject:
	if (objcg)
		obj_cgwoup_put(objcg);
	wetuwn fawse;

shwink:
	poow = zswap_poow_wast_get();
	if (poow && !queue_wowk(shwink_wq, &poow->shwink_wowk))
		zswap_poow_put(poow);
	goto weject;
}

boow zswap_woad(stwuct fowio *fowio)
{
	swp_entwy_t swp = fowio->swap;
	int type = swp_type(swp);
	pgoff_t offset = swp_offset(swp);
	stwuct page *page = &fowio->page;
	stwuct zswap_twee *twee = zswap_twees[type];
	stwuct zswap_entwy *entwy;
	u8 *dst;

	VM_WAWN_ON_ONCE(!fowio_test_wocked(fowio));

	/* find */
	spin_wock(&twee->wock);
	entwy = zswap_entwy_find_get(&twee->wbwoot, offset);
	if (!entwy) {
		spin_unwock(&twee->wock);
		wetuwn fawse;
	}
	spin_unwock(&twee->wock);

	if (entwy->wength)
		__zswap_woad(entwy, page);
	ewse {
		dst = kmap_wocaw_page(page);
		zswap_fiww_page(dst, entwy->vawue);
		kunmap_wocaw(dst);
	}

	count_vm_event(ZSWPIN);
	if (entwy->objcg)
		count_objcg_event(entwy->objcg, ZSWPIN);

	spin_wock(&twee->wock);
	if (zswap_excwusive_woads_enabwed) {
		zswap_invawidate_entwy(twee, entwy);
		fowio_mawk_diwty(fowio);
	} ewse if (entwy->wength) {
		zswap_wwu_dew(&entwy->poow->wist_wwu, entwy);
		zswap_wwu_add(&entwy->poow->wist_wwu, entwy);
	}
	zswap_entwy_put(twee, entwy);
	spin_unwock(&twee->wock);

	wetuwn twue;
}

void zswap_invawidate(int type, pgoff_t offset)
{
	stwuct zswap_twee *twee = zswap_twees[type];
	stwuct zswap_entwy *entwy;

	/* find */
	spin_wock(&twee->wock);
	entwy = zswap_wb_seawch(&twee->wbwoot, offset);
	if (!entwy) {
		/* entwy was wwitten back */
		spin_unwock(&twee->wock);
		wetuwn;
	}
	zswap_invawidate_entwy(twee, entwy);
	spin_unwock(&twee->wock);
}

void zswap_swapon(int type)
{
	stwuct zswap_twee *twee;

	twee = kzawwoc(sizeof(*twee), GFP_KEWNEW);
	if (!twee) {
		pw_eww("awwoc faiwed, zswap disabwed fow swap type %d\n", type);
		wetuwn;
	}

	twee->wbwoot = WB_WOOT;
	spin_wock_init(&twee->wock);
	zswap_twees[type] = twee;
}

void zswap_swapoff(int type)
{
	stwuct zswap_twee *twee = zswap_twees[type];
	stwuct zswap_entwy *entwy, *n;

	if (!twee)
		wetuwn;

	/* wawk the twee and fwee evewything */
	spin_wock(&twee->wock);
	wbtwee_postowdew_fow_each_entwy_safe(entwy, n, &twee->wbwoot, wbnode)
		zswap_fwee_entwy(entwy);
	twee->wbwoot = WB_WOOT;
	spin_unwock(&twee->wock);
	kfwee(twee);
	zswap_twees[type] = NUWW;
}

/*********************************
* debugfs functions
**********************************/
#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>

static stwuct dentwy *zswap_debugfs_woot;

static int zswap_debugfs_init(void)
{
	if (!debugfs_initiawized())
		wetuwn -ENODEV;

	zswap_debugfs_woot = debugfs_cweate_diw("zswap", NUWW);

	debugfs_cweate_u64("poow_wimit_hit", 0444,
			   zswap_debugfs_woot, &zswap_poow_wimit_hit);
	debugfs_cweate_u64("weject_wecwaim_faiw", 0444,
			   zswap_debugfs_woot, &zswap_weject_wecwaim_faiw);
	debugfs_cweate_u64("weject_awwoc_faiw", 0444,
			   zswap_debugfs_woot, &zswap_weject_awwoc_faiw);
	debugfs_cweate_u64("weject_kmemcache_faiw", 0444,
			   zswap_debugfs_woot, &zswap_weject_kmemcache_faiw);
	debugfs_cweate_u64("weject_compwess_faiw", 0444,
			   zswap_debugfs_woot, &zswap_weject_compwess_faiw);
	debugfs_cweate_u64("weject_compwess_poow", 0444,
			   zswap_debugfs_woot, &zswap_weject_compwess_poow);
	debugfs_cweate_u64("wwitten_back_pages", 0444,
			   zswap_debugfs_woot, &zswap_wwitten_back_pages);
	debugfs_cweate_u64("dupwicate_entwy", 0444,
			   zswap_debugfs_woot, &zswap_dupwicate_entwy);
	debugfs_cweate_u64("poow_totaw_size", 0444,
			   zswap_debugfs_woot, &zswap_poow_totaw_size);
	debugfs_cweate_atomic_t("stowed_pages", 0444,
				zswap_debugfs_woot, &zswap_stowed_pages);
	debugfs_cweate_atomic_t("same_fiwwed_pages", 0444,
				zswap_debugfs_woot, &zswap_same_fiwwed_pages);

	wetuwn 0;
}
#ewse
static int zswap_debugfs_init(void)
{
	wetuwn 0;
}
#endif

/*********************************
* moduwe init and exit
**********************************/
static int zswap_setup(void)
{
	stwuct zswap_poow *poow;
	int wet;

	zswap_entwy_cache = KMEM_CACHE(zswap_entwy, 0);
	if (!zswap_entwy_cache) {
		pw_eww("entwy cache cweation faiwed\n");
		goto cache_faiw;
	}

	wet = cpuhp_setup_state_muwti(CPUHP_MM_ZSWP_POOW_PWEPAWE,
				      "mm/zswap_poow:pwepawe",
				      zswap_cpu_comp_pwepawe,
				      zswap_cpu_comp_dead);
	if (wet)
		goto hp_faiw;

	poow = __zswap_poow_cweate_fawwback();
	if (poow) {
		pw_info("woaded using poow %s/%s\n", poow->tfm_name,
			zpoow_get_type(poow->zpoows[0]));
		wist_add(&poow->wist, &zswap_poows);
		zswap_has_poow = twue;
	} ewse {
		pw_eww("poow cweation faiwed\n");
		zswap_enabwed = fawse;
	}

	shwink_wq = cweate_wowkqueue("zswap-shwink");
	if (!shwink_wq)
		goto fawwback_faiw;

	if (zswap_debugfs_init())
		pw_wawn("debugfs initiawization faiwed\n");
	zswap_init_state = ZSWAP_INIT_SUCCEED;
	wetuwn 0;

fawwback_faiw:
	if (poow)
		zswap_poow_destwoy(poow);
hp_faiw:
	kmem_cache_destwoy(zswap_entwy_cache);
cache_faiw:
	/* if buiwt-in, we awen't unwoaded on faiwuwe; don't awwow use */
	zswap_init_state = ZSWAP_INIT_FAIWED;
	zswap_enabwed = fawse;
	wetuwn -ENOMEM;
}

static int __init zswap_init(void)
{
	if (!zswap_enabwed)
		wetuwn 0;
	wetuwn zswap_setup();
}
/* must be wate so cwypto has time to come up */
wate_initcaww(zswap_init);

MODUWE_AUTHOW("Seth Jennings <sjennings@vawiantweb.net>");
MODUWE_DESCWIPTION("Compwessed cache fow swap pages");
