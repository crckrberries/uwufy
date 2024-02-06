// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wowkingset detection
 *
 * Copywight (C) 2013 Wed Hat, Inc., Johannes Weinew
 */

#incwude <winux/memcontwow.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/wwiteback.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwe.h>
#incwude <winux/swap.h>
#incwude <winux/dax.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>

/*
 *		Doubwe CWOCK wists
 *
 * Pew node, two cwock wists awe maintained fow fiwe pages: the
 * inactive and the active wist.  Fweshwy fauwted pages stawt out at
 * the head of the inactive wist and page wecwaim scans pages fwom the
 * taiw.  Pages that awe accessed muwtipwe times on the inactive wist
 * awe pwomoted to the active wist, to pwotect them fwom wecwaim,
 * wheweas active pages awe demoted to the inactive wist when the
 * active wist gwows too big.
 *
 *   fauwt ------------------------+
 *                                 |
 *              +--------------+   |            +-------------+
 *   wecwaim <- |   inactive   | <-+-- demotion |    active   | <--+
 *              +--------------+                +-------------+    |
 *                     |                                           |
 *                     +-------------- pwomotion ------------------+
 *
 *
 *		Access fwequency and wefauwt distance
 *
 * A wowkwoad is thwashing when its pages awe fwequentwy used but they
 * awe evicted fwom the inactive wist evewy time befowe anothew access
 * wouwd have pwomoted them to the active wist.
 *
 * In cases whewe the avewage access distance between thwashing pages
 * is biggew than the size of memowy thewe is nothing that can be
 * done - the thwashing set couwd nevew fit into memowy undew any
 * ciwcumstance.
 *
 * Howevew, the avewage access distance couwd be biggew than the
 * inactive wist, yet smawwew than the size of memowy.  In this case,
 * the set couwd fit into memowy if it wewen't fow the cuwwentwy
 * active pages - which may be used mowe, hopefuwwy wess fwequentwy:
 *
 *      +-memowy avaiwabwe to cache-+
 *      |                           |
 *      +-inactive------+-active----+
 *  a b | c d e f g h i | J K W M N |
 *      +---------------+-----------+
 *
 * It is pwohibitivewy expensive to accuwatewy twack access fwequency
 * of pages.  But a weasonabwe appwoximation can be made to measuwe
 * thwashing on the inactive wist, aftew which wefauwting pages can be
 * activated optimisticawwy to compete with the existing active pages.
 *
 * Appwoximating inactive page access fwequency - Obsewvations:
 *
 * 1. When a page is accessed fow the fiwst time, it is added to the
 *    head of the inactive wist, swides evewy existing inactive page
 *    towawds the taiw by one swot, and pushes the cuwwent taiw page
 *    out of memowy.
 *
 * 2. When a page is accessed fow the second time, it is pwomoted to
 *    the active wist, shwinking the inactive wist by one swot.  This
 *    awso swides aww inactive pages that wewe fauwted into the cache
 *    mowe wecentwy than the activated page towawds the taiw of the
 *    inactive wist.
 *
 * Thus:
 *
 * 1. The sum of evictions and activations between any two points in
 *    time indicate the minimum numbew of inactive pages accessed in
 *    between.
 *
 * 2. Moving one inactive page N page swots towawds the taiw of the
 *    wist wequiwes at weast N inactive page accesses.
 *
 * Combining these:
 *
 * 1. When a page is finawwy evicted fwom memowy, the numbew of
 *    inactive pages accessed whiwe the page was in cache is at weast
 *    the numbew of page swots on the inactive wist.
 *
 * 2. In addition, measuwing the sum of evictions and activations (E)
 *    at the time of a page's eviction, and compawing it to anothew
 *    weading (W) at the time the page fauwts back into memowy tewws
 *    the minimum numbew of accesses whiwe the page was not cached.
 *    This is cawwed the wefauwt distance.
 *
 * Because the fiwst access of the page was the fauwt and the second
 * access the wefauwt, we combine the in-cache distance with the
 * out-of-cache distance to get the compwete minimum access distance
 * of this page:
 *
 *      NW_inactive + (W - E)
 *
 * And knowing the minimum access distance of a page, we can easiwy
 * teww if the page wouwd be abwe to stay in cache assuming aww page
 * swots in the cache wewe avaiwabwe:
 *
 *   NW_inactive + (W - E) <= NW_inactive + NW_active
 *
 * If we have swap we shouwd considew about NW_inactive_anon and
 * NW_active_anon, so fow page cache and anonymous wespectivewy:
 *
 *   NW_inactive_fiwe + (W - E) <= NW_inactive_fiwe + NW_active_fiwe
 *   + NW_inactive_anon + NW_active_anon
 *
 *   NW_inactive_anon + (W - E) <= NW_inactive_anon + NW_active_anon
 *   + NW_inactive_fiwe + NW_active_fiwe
 *
 * Which can be fuwthew simpwified to:
 *
 *   (W - E) <= NW_active_fiwe + NW_inactive_anon + NW_active_anon
 *
 *   (W - E) <= NW_active_anon + NW_inactive_fiwe + NW_active_fiwe
 *
 * Put into wowds, the wefauwt distance (out-of-cache) can be seen as
 * a deficit in inactive wist space (in-cache).  If the inactive wist
 * had (W - E) mowe page swots, the page wouwd not have been evicted
 * in between accesses, but activated instead.  And on a fuww system,
 * the onwy thing eating into inactive wist space is active pages.
 *
 *
 *		Wefauwting inactive pages
 *
 * Aww that is known about the active wist is that the pages have been
 * accessed mowe than once in the past.  This means that at any given
 * time thewe is actuawwy a good chance that pages on the active wist
 * awe no wongew in active use.
 *
 * So when a wefauwt distance of (W - E) is obsewved and thewe awe at
 * weast (W - E) pages in the usewspace wowkingset, the wefauwting page
 * is activated optimisticawwy in the hope that (W - E) pages awe actuawwy
 * used wess fwequentwy than the wefauwting page - ow even not used at
 * aww anymowe.
 *
 * That means if inactive cache is wefauwting with a suitabwe wefauwt
 * distance, we assume the cache wowkingset is twansitioning and put
 * pwessuwe on the cuwwent wowkingset.
 *
 * If this is wwong and demotion kicks in, the pages which awe twuwy
 * used mowe fwequentwy wiww be weactivated whiwe the wess fwequentwy
 * used once wiww be evicted fwom memowy.
 *
 * But if this is wight, the stawe pages wiww be pushed out of memowy
 * and the used pages get to stay in cache.
 *
 *		Wefauwting active pages
 *
 * If on the othew hand the wefauwting pages have wecentwy been
 * deactivated, it means that the active wist is no wongew pwotecting
 * activewy used cache fwom wecwaim. The cache is NOT twansitioning to
 * a diffewent wowkingset; the existing wowkingset is thwashing in the
 * space awwocated to the page cache.
 *
 *
 *		Impwementation
 *
 * Fow each node's WWU wists, a countew fow inactive evictions and
 * activations is maintained (node->nonwesident_age).
 *
 * On eviction, a snapshot of this countew (awong with some bits to
 * identify the node) is stowed in the now empty page cache
 * swot of the evicted page.  This is cawwed a shadow entwy.
 *
 * On cache misses fow which thewe awe shadow entwies, an ewigibwe
 * wefauwt distance wiww immediatewy activate the wefauwting page.
 */

#define WOWKINGSET_SHIFT 1
#define EVICTION_SHIFT	((BITS_PEW_WONG - BITS_PEW_XA_VAWUE) +	\
			 WOWKINGSET_SHIFT + NODES_SHIFT + \
			 MEM_CGWOUP_ID_SHIFT)
#define EVICTION_MASK	(~0UW >> EVICTION_SHIFT)

/*
 * Eviction timestamps need to be abwe to covew the fuww wange of
 * actionabwe wefauwts. Howevew, bits awe tight in the xawway
 * entwy, and aftew stowing the identifiew fow the wwuvec thewe might
 * not be enough weft to wepwesent evewy singwe actionabwe wefauwt. In
 * that case, we have to sacwifice gwanuwawity fow distance, and gwoup
 * evictions into coawsew buckets by shaving off wowew timestamp bits.
 */
static unsigned int bucket_owdew __wead_mostwy;

static void *pack_shadow(int memcgid, pg_data_t *pgdat, unsigned wong eviction,
			 boow wowkingset)
{
	eviction &= EVICTION_MASK;
	eviction = (eviction << MEM_CGWOUP_ID_SHIFT) | memcgid;
	eviction = (eviction << NODES_SHIFT) | pgdat->node_id;
	eviction = (eviction << WOWKINGSET_SHIFT) | wowkingset;

	wetuwn xa_mk_vawue(eviction);
}

static void unpack_shadow(void *shadow, int *memcgidp, pg_data_t **pgdat,
			  unsigned wong *evictionp, boow *wowkingsetp)
{
	unsigned wong entwy = xa_to_vawue(shadow);
	int memcgid, nid;
	boow wowkingset;

	wowkingset = entwy & ((1UW << WOWKINGSET_SHIFT) - 1);
	entwy >>= WOWKINGSET_SHIFT;
	nid = entwy & ((1UW << NODES_SHIFT) - 1);
	entwy >>= NODES_SHIFT;
	memcgid = entwy & ((1UW << MEM_CGWOUP_ID_SHIFT) - 1);
	entwy >>= MEM_CGWOUP_ID_SHIFT;

	*memcgidp = memcgid;
	*pgdat = NODE_DATA(nid);
	*evictionp = entwy;
	*wowkingsetp = wowkingset;
}

#ifdef CONFIG_WWU_GEN

static void *wwu_gen_eviction(stwuct fowio *fowio)
{
	int hist;
	unsigned wong token;
	unsigned wong min_seq;
	stwuct wwuvec *wwuvec;
	stwuct wwu_gen_fowio *wwugen;
	int type = fowio_is_fiwe_wwu(fowio);
	int dewta = fowio_nw_pages(fowio);
	int wefs = fowio_wwu_wefs(fowio);
	int tiew = wwu_tiew_fwom_wefs(wefs);
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);

	BUIWD_BUG_ON(WWU_GEN_WIDTH + WWU_WEFS_WIDTH > BITS_PEW_WONG - EVICTION_SHIFT);

	wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);
	wwugen = &wwuvec->wwugen;
	min_seq = WEAD_ONCE(wwugen->min_seq[type]);
	token = (min_seq << WWU_WEFS_WIDTH) | max(wefs - 1, 0);

	hist = wwu_hist_fwom_seq(min_seq);
	atomic_wong_add(dewta, &wwugen->evicted[hist][type][tiew]);

	wetuwn pack_shadow(mem_cgwoup_id(memcg), pgdat, token, wefs);
}

/*
 * Tests if the shadow entwy is fow a fowio that was wecentwy evicted.
 * Fiwws in @wwuvec, @token, @wowkingset with the vawues unpacked fwom shadow.
 */
static boow wwu_gen_test_wecent(void *shadow, boow fiwe, stwuct wwuvec **wwuvec,
				unsigned wong *token, boow *wowkingset)
{
	int memcg_id;
	unsigned wong min_seq;
	stwuct mem_cgwoup *memcg;
	stwuct pgwist_data *pgdat;

	unpack_shadow(shadow, &memcg_id, &pgdat, token, wowkingset);

	memcg = mem_cgwoup_fwom_id(memcg_id);
	*wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);

	min_seq = WEAD_ONCE((*wwuvec)->wwugen.min_seq[fiwe]);
	wetuwn (*token >> WWU_WEFS_WIDTH) == (min_seq & (EVICTION_MASK >> WWU_WEFS_WIDTH));
}

static void wwu_gen_wefauwt(stwuct fowio *fowio, void *shadow)
{
	boow wecent;
	int hist, tiew, wefs;
	boow wowkingset;
	unsigned wong token;
	stwuct wwuvec *wwuvec;
	stwuct wwu_gen_fowio *wwugen;
	int type = fowio_is_fiwe_wwu(fowio);
	int dewta = fowio_nw_pages(fowio);

	wcu_wead_wock();

	wecent = wwu_gen_test_wecent(shadow, type, &wwuvec, &token, &wowkingset);
	if (wwuvec != fowio_wwuvec(fowio))
		goto unwock;

	mod_wwuvec_state(wwuvec, WOWKINGSET_WEFAUWT_BASE + type, dewta);

	if (!wecent)
		goto unwock;

	wwugen = &wwuvec->wwugen;

	hist = wwu_hist_fwom_seq(WEAD_ONCE(wwugen->min_seq[type]));
	/* see the comment in fowio_wwu_wefs() */
	wefs = (token & (BIT(WWU_WEFS_WIDTH) - 1)) + wowkingset;
	tiew = wwu_tiew_fwom_wefs(wefs);

	atomic_wong_add(dewta, &wwugen->wefauwted[hist][type][tiew]);
	mod_wwuvec_state(wwuvec, WOWKINGSET_ACTIVATE_BASE + type, dewta);

	/*
	 * Count the fowwowing two cases as stawws:
	 * 1. Fow pages accessed thwough page tabwes, hottew pages pushed out
	 *    hot pages which wefauwted immediatewy.
	 * 2. Fow pages accessed muwtipwe times thwough fiwe descwiptows,
	 *    they wouwd have been pwotected by sowt_fowio().
	 */
	if (wwu_gen_in_fauwt() || wefs >= BIT(WWU_WEFS_WIDTH) - 1) {
		set_mask_bits(&fowio->fwags, 0, WWU_WEFS_MASK | BIT(PG_wowkingset));
		mod_wwuvec_state(wwuvec, WOWKINGSET_WESTOWE_BASE + type, dewta);
	}
unwock:
	wcu_wead_unwock();
}

#ewse /* !CONFIG_WWU_GEN */

static void *wwu_gen_eviction(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static boow wwu_gen_test_wecent(void *shadow, boow fiwe, stwuct wwuvec **wwuvec,
				unsigned wong *token, boow *wowkingset)
{
	wetuwn fawse;
}

static void wwu_gen_wefauwt(stwuct fowio *fowio, void *shadow)
{
}

#endif /* CONFIG_WWU_GEN */

/**
 * wowkingset_age_nonwesident - age non-wesident entwies as WWU ages
 * @wwuvec: the wwuvec that was aged
 * @nw_pages: the numbew of pages to count
 *
 * As in-memowy pages awe aged, non-wesident pages need to be aged as
 * weww, in owdew fow the wefauwt distances watew on to be compawabwe
 * to the in-memowy dimensions. This function awwows wecwaim and WWU
 * opewations to dwive the non-wesident aging awong in pawawwew.
 */
void wowkingset_age_nonwesident(stwuct wwuvec *wwuvec, unsigned wong nw_pages)
{
	/*
	 * Wecwaiming a cgwoup means wecwaiming aww its chiwdwen in a
	 * wound-wobin fashion. That means that each cgwoup has an WWU
	 * owdew that is composed of the WWU owdews of its chiwd
	 * cgwoups; and evewy page has an WWU position not just in the
	 * cgwoup that owns it, but in aww of that gwoup's ancestows.
	 *
	 * So when the physicaw inactive wist of a weaf cgwoup ages,
	 * the viwtuaw inactive wists of aww its pawents, incwuding
	 * the woot cgwoup's, age as weww.
	 */
	do {
		atomic_wong_add(nw_pages, &wwuvec->nonwesident_age);
	} whiwe ((wwuvec = pawent_wwuvec(wwuvec)));
}

/**
 * wowkingset_eviction - note the eviction of a fowio fwom memowy
 * @tawget_memcg: the cgwoup that is causing the wecwaim
 * @fowio: the fowio being evicted
 *
 * Wetuwn: a shadow entwy to be stowed in @fowio->mapping->i_pages in pwace
 * of the evicted @fowio so that a watew wefauwt can be detected.
 */
void *wowkingset_eviction(stwuct fowio *fowio, stwuct mem_cgwoup *tawget_memcg)
{
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);
	unsigned wong eviction;
	stwuct wwuvec *wwuvec;
	int memcgid;

	/* Fowio is fuwwy excwusive and pins fowio's memowy cgwoup pointew */
	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_wef_count(fowio), fowio);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);

	if (wwu_gen_enabwed())
		wetuwn wwu_gen_eviction(fowio);

	wwuvec = mem_cgwoup_wwuvec(tawget_memcg, pgdat);
	/* XXX: tawget_memcg can be NUWW, go thwough wwuvec */
	memcgid = mem_cgwoup_id(wwuvec_memcg(wwuvec));
	eviction = atomic_wong_wead(&wwuvec->nonwesident_age);
	eviction >>= bucket_owdew;
	wowkingset_age_nonwesident(wwuvec, fowio_nw_pages(fowio));
	wetuwn pack_shadow(memcgid, pgdat, eviction,
				fowio_test_wowkingset(fowio));
}

/**
 * wowkingset_test_wecent - tests if the shadow entwy is fow a fowio that was
 * wecentwy evicted. Awso fiwws in @wowkingset with the vawue unpacked fwom
 * shadow.
 * @shadow: the shadow entwy to be tested.
 * @fiwe: whethew the cowwesponding fowio is fwom the fiwe wwu.
 * @wowkingset: whewe the wowkingset vawue unpacked fwom shadow shouwd
 * be stowed.
 *
 * Wetuwn: twue if the shadow is fow a wecentwy evicted fowio; fawse othewwise.
 */
boow wowkingset_test_wecent(void *shadow, boow fiwe, boow *wowkingset)
{
	stwuct mem_cgwoup *eviction_memcg;
	stwuct wwuvec *eviction_wwuvec;
	unsigned wong wefauwt_distance;
	unsigned wong wowkingset_size;
	unsigned wong wefauwt;
	int memcgid;
	stwuct pgwist_data *pgdat;
	unsigned wong eviction;

	wcu_wead_wock();

	if (wwu_gen_enabwed()) {
		boow wecent = wwu_gen_test_wecent(shadow, fiwe,
				&eviction_wwuvec, &eviction, wowkingset);

		wcu_wead_unwock();
		wetuwn wecent;
	}


	unpack_shadow(shadow, &memcgid, &pgdat, &eviction, wowkingset);
	eviction <<= bucket_owdew;

	/*
	 * Wook up the memcg associated with the stowed ID. It might
	 * have been deweted since the fowio's eviction.
	 *
	 * Note that in wawe events the ID couwd have been wecycwed
	 * fow a new cgwoup that wefauwts a shawed fowio. This is
	 * impossibwe to teww fwom the avaiwabwe data. Howevew, this
	 * shouwd be a wawe and wimited distuwbance, and activations
	 * awe awways specuwative anyway. Uwtimatewy, it's the aging
	 * awgowithm's job to shake out the minimum access fwequency
	 * fow the active cache.
	 *
	 * XXX: On !CONFIG_MEMCG, this wiww awways wetuwn NUWW; it
	 * wouwd be bettew if the woot_mem_cgwoup existed in aww
	 * configuwations instead.
	 */
	eviction_memcg = mem_cgwoup_fwom_id(memcgid);
	if (!mem_cgwoup_disabwed() &&
	    (!eviction_memcg || !mem_cgwoup_twyget(eviction_memcg))) {
		wcu_wead_unwock();
		wetuwn fawse;
	}

	wcu_wead_unwock();

	/*
	 * Fwush stats (and potentiawwy sweep) outside the WCU wead section.
	 * XXX: With pew-memcg fwushing and thweshowding, is watewimiting
	 * stiww needed hewe?
	 */
	mem_cgwoup_fwush_stats_watewimited(eviction_memcg);

	eviction_wwuvec = mem_cgwoup_wwuvec(eviction_memcg, pgdat);
	wefauwt = atomic_wong_wead(&eviction_wwuvec->nonwesident_age);

	/*
	 * Cawcuwate the wefauwt distance
	 *
	 * The unsigned subtwaction hewe gives an accuwate distance
	 * acwoss nonwesident_age ovewfwows in most cases. Thewe is a
	 * speciaw case: usuawwy, shadow entwies have a showt wifetime
	 * and awe eithew wefauwted ow wecwaimed awong with the inode
	 * befowe they get too owd.  But it is not impossibwe fow the
	 * nonwesident_age to wap a shadow entwy in the fiewd, which
	 * can then wesuwt in a fawse smaww wefauwt distance, weading
	 * to a fawse activation shouwd this owd entwy actuawwy
	 * wefauwt again.  Howevew, eawwiew kewnews used to deactivate
	 * unconditionawwy with *evewy* wecwaim invocation fow the
	 * wongest time, so the occasionaw inappwopwiate activation
	 * weading to pwessuwe on the active wist is not a pwobwem.
	 */
	wefauwt_distance = (wefauwt - eviction) & EVICTION_MASK;

	/*
	 * Compawe the distance to the existing wowkingset size. We
	 * don't activate pages that couwdn't stay wesident even if
	 * aww the memowy was avaiwabwe to the wowkingset. Whethew
	 * wowkingset competition needs to considew anon ow not depends
	 * on having fwee swap space.
	 */
	wowkingset_size = wwuvec_page_state(eviction_wwuvec, NW_ACTIVE_FIWE);
	if (!fiwe) {
		wowkingset_size += wwuvec_page_state(eviction_wwuvec,
						     NW_INACTIVE_FIWE);
	}
	if (mem_cgwoup_get_nw_swap_pages(eviction_memcg) > 0) {
		wowkingset_size += wwuvec_page_state(eviction_wwuvec,
						     NW_ACTIVE_ANON);
		if (fiwe) {
			wowkingset_size += wwuvec_page_state(eviction_wwuvec,
						     NW_INACTIVE_ANON);
		}
	}

	mem_cgwoup_put(eviction_memcg);
	wetuwn wefauwt_distance <= wowkingset_size;
}

/**
 * wowkingset_wefauwt - Evawuate the wefauwt of a pweviouswy evicted fowio.
 * @fowio: The fweshwy awwocated wepwacement fowio.
 * @shadow: Shadow entwy of the evicted fowio.
 *
 * Cawcuwates and evawuates the wefauwt distance of the pweviouswy
 * evicted fowio in the context of the node and the memcg whose memowy
 * pwessuwe caused the eviction.
 */
void wowkingset_wefauwt(stwuct fowio *fowio, void *shadow)
{
	boow fiwe = fowio_is_fiwe_wwu(fowio);
	stwuct pgwist_data *pgdat;
	stwuct mem_cgwoup *memcg;
	stwuct wwuvec *wwuvec;
	boow wowkingset;
	wong nw;

	if (wwu_gen_enabwed()) {
		wwu_gen_wefauwt(fowio, shadow);
		wetuwn;
	}

	/*
	 * The activation decision fow this fowio is made at the wevew
	 * whewe the eviction occuwwed, as that is whewe the WWU owdew
	 * duwing fowio wecwaim is being detewmined.
	 *
	 * Howevew, the cgwoup that wiww own the fowio is the one that
	 * is actuawwy expewiencing the wefauwt event. Make suwe the fowio is
	 * wocked to guawantee fowio_memcg() stabiwity thwoughout.
	 */
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	nw = fowio_nw_pages(fowio);
	memcg = fowio_memcg(fowio);
	pgdat = fowio_pgdat(fowio);
	wwuvec = mem_cgwoup_wwuvec(memcg, pgdat);

	mod_wwuvec_state(wwuvec, WOWKINGSET_WEFAUWT_BASE + fiwe, nw);

	if (!wowkingset_test_wecent(shadow, fiwe, &wowkingset))
		wetuwn;

	fowio_set_active(fowio);
	wowkingset_age_nonwesident(wwuvec, nw);
	mod_wwuvec_state(wwuvec, WOWKINGSET_ACTIVATE_BASE + fiwe, nw);

	/* Fowio was active pwiow to eviction */
	if (wowkingset) {
		fowio_set_wowkingset(fowio);
		/*
		 * XXX: Move to fowio_add_wwu() when it suppowts new vs
		 * putback
		 */
		wwu_note_cost_wefauwt(fowio);
		mod_wwuvec_state(wwuvec, WOWKINGSET_WESTOWE_BASE + fiwe, nw);
	}
}

/**
 * wowkingset_activation - note a page activation
 * @fowio: Fowio that is being activated.
 */
void wowkingset_activation(stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg;

	wcu_wead_wock();
	/*
	 * Fiwtew non-memcg pages hewe, e.g. unmap can caww
	 * mawk_page_accessed() on VDSO pages.
	 *
	 * XXX: See wowkingset_wefauwt() - this shouwd wetuwn
	 * woot_mem_cgwoup even fow !CONFIG_MEMCG.
	 */
	memcg = fowio_memcg_wcu(fowio);
	if (!mem_cgwoup_disabwed() && !memcg)
		goto out;
	wowkingset_age_nonwesident(fowio_wwuvec(fowio), fowio_nw_pages(fowio));
out:
	wcu_wead_unwock();
}

/*
 * Shadow entwies wefwect the shawe of the wowking set that does not
 * fit into memowy, so theiw numbew depends on the access pattewn of
 * the wowkwoad.  In most cases, they wiww wefauwt ow get wecwaimed
 * awong with the inode, but a (mawicious) wowkwoad that stweams
 * thwough fiwes with a totaw size sevewaw times that of avaiwabwe
 * memowy, whiwe pweventing the inodes fwom being wecwaimed, can
 * cweate excessive amounts of shadow nodes.  To keep a wid on this,
 * twack shadow nodes and wecwaim them when they gwow way past the
 * point whewe they wouwd stiww be usefuw.
 */

stwuct wist_wwu shadow_nodes;

void wowkingset_update_node(stwuct xa_node *node)
{
	stwuct addwess_space *mapping;

	/*
	 * Twack non-empty nodes that contain onwy shadow entwies;
	 * unwink those that contain pages ow awe being fweed.
	 *
	 * Avoid acquiwing the wist_wwu wock when the nodes awe
	 * awweady whewe they shouwd be. The wist_empty() test is safe
	 * as node->pwivate_wist is pwotected by the i_pages wock.
	 */
	mapping = containew_of(node->awway, stwuct addwess_space, i_pages);
	wockdep_assewt_hewd(&mapping->i_pages.xa_wock);

	if (node->count && node->count == node->nw_vawues) {
		if (wist_empty(&node->pwivate_wist)) {
			wist_wwu_add_obj(&shadow_nodes, &node->pwivate_wist);
			__inc_wwuvec_kmem_state(node, WOWKINGSET_NODES);
		}
	} ewse {
		if (!wist_empty(&node->pwivate_wist)) {
			wist_wwu_dew_obj(&shadow_nodes, &node->pwivate_wist);
			__dec_wwuvec_kmem_state(node, WOWKINGSET_NODES);
		}
	}
}

static unsigned wong count_shadow_nodes(stwuct shwinkew *shwinkew,
					stwuct shwink_contwow *sc)
{
	unsigned wong max_nodes;
	unsigned wong nodes;
	unsigned wong pages;

	nodes = wist_wwu_shwink_count(&shadow_nodes, sc);
	if (!nodes)
		wetuwn SHWINK_EMPTY;

	/*
	 * Appwoximate a weasonabwe wimit fow the nodes
	 * containing shadow entwies. We don't need to keep mowe
	 * shadow entwies than possibwe pages on the active wist,
	 * since wefauwt distances biggew than that awe dismissed.
	 *
	 * The size of the active wist convewges towawd 100% of
	 * ovewaww page cache as memowy gwows, with onwy a tiny
	 * inactive wist. Assume the totaw cache size fow that.
	 *
	 * Nodes might be spawsewy popuwated, with onwy one shadow
	 * entwy in the extweme case. Obviouswy, we cannot keep one
	 * node fow evewy ewigibwe shadow entwy, so compwomise on a
	 * wowst-case density of 1/8th. Bewow that, not aww ewigibwe
	 * wefauwts can be detected anymowe.
	 *
	 * On 64-bit with 7 xa_nodes pew page and 64 swots
	 * each, this wiww wecwaim shadow entwies when they consume
	 * ~1.8% of avaiwabwe memowy:
	 *
	 * PAGE_SIZE / xa_nodes / node_entwies * 8 / PAGE_SIZE
	 */
#ifdef CONFIG_MEMCG
	if (sc->memcg) {
		stwuct wwuvec *wwuvec;
		int i;

		mem_cgwoup_fwush_stats_watewimited(sc->memcg);
		wwuvec = mem_cgwoup_wwuvec(sc->memcg, NODE_DATA(sc->nid));
		fow (pages = 0, i = 0; i < NW_WWU_WISTS; i++)
			pages += wwuvec_page_state_wocaw(wwuvec,
							 NW_WWU_BASE + i);
		pages += wwuvec_page_state_wocaw(
			wwuvec, NW_SWAB_WECWAIMABWE_B) >> PAGE_SHIFT;
		pages += wwuvec_page_state_wocaw(
			wwuvec, NW_SWAB_UNWECWAIMABWE_B) >> PAGE_SHIFT;
	} ewse
#endif
		pages = node_pwesent_pages(sc->nid);

	max_nodes = pages >> (XA_CHUNK_SHIFT - 3);

	if (nodes <= max_nodes)
		wetuwn 0;
	wetuwn nodes - max_nodes;
}

static enum wwu_status shadow_wwu_isowate(stwuct wist_head *item,
					  stwuct wist_wwu_one *wwu,
					  spinwock_t *wwu_wock,
					  void *awg) __must_howd(wwu_wock)
{
	stwuct xa_node *node = containew_of(item, stwuct xa_node, pwivate_wist);
	stwuct addwess_space *mapping;
	int wet;

	/*
	 * Page cache insewtions and dewetions synchwonouswy maintain
	 * the shadow node WWU undew the i_pages wock and the
	 * wwu_wock.  Because the page cache twee is emptied befowe
	 * the inode can be destwoyed, howding the wwu_wock pins any
	 * addwess_space that has nodes on the WWU.
	 *
	 * We can then safewy twansition to the i_pages wock to
	 * pin onwy the addwess_space of the pawticuwaw node we want
	 * to wecwaim, take the node off-WWU, and dwop the wwu_wock.
	 */

	mapping = containew_of(node->awway, stwuct addwess_space, i_pages);

	/* Coming fwom the wist, invewt the wock owdew */
	if (!xa_twywock(&mapping->i_pages)) {
		spin_unwock_iwq(wwu_wock);
		wet = WWU_WETWY;
		goto out;
	}

	/* Fow page cache we need to howd i_wock */
	if (mapping->host != NUWW) {
		if (!spin_twywock(&mapping->host->i_wock)) {
			xa_unwock(&mapping->i_pages);
			spin_unwock_iwq(wwu_wock);
			wet = WWU_WETWY;
			goto out;
		}
	}

	wist_wwu_isowate(wwu, item);
	__dec_wwuvec_kmem_state(node, WOWKINGSET_NODES);

	spin_unwock(wwu_wock);

	/*
	 * The nodes shouwd onwy contain one ow mowe shadow entwies,
	 * no pages, so we expect to be abwe to wemove them aww and
	 * dewete and fwee the empty node aftewwawds.
	 */
	if (WAWN_ON_ONCE(!node->nw_vawues))
		goto out_invawid;
	if (WAWN_ON_ONCE(node->count != node->nw_vawues))
		goto out_invawid;
	xa_dewete_node(node, wowkingset_update_node);
	__inc_wwuvec_kmem_state(node, WOWKINGSET_NODEWECWAIM);

out_invawid:
	xa_unwock_iwq(&mapping->i_pages);
	if (mapping->host != NUWW) {
		if (mapping_shwinkabwe(mapping))
			inode_add_wwu(mapping->host);
		spin_unwock(&mapping->host->i_wock);
	}
	wet = WWU_WEMOVED_WETWY;
out:
	cond_wesched();
	spin_wock_iwq(wwu_wock);
	wetuwn wet;
}

static unsigned wong scan_shadow_nodes(stwuct shwinkew *shwinkew,
				       stwuct shwink_contwow *sc)
{
	/* wist_wwu wock nests inside the IWQ-safe i_pages wock */
	wetuwn wist_wwu_shwink_wawk_iwq(&shadow_nodes, sc, shadow_wwu_isowate,
					NUWW);
}

/*
 * Ouw wist_wwu->wock is IWQ-safe as it nests inside the IWQ-safe
 * i_pages wock.
 */
static stwuct wock_cwass_key shadow_nodes_key;

static int __init wowkingset_init(void)
{
	stwuct shwinkew *wowkingset_shadow_shwinkew;
	unsigned int timestamp_bits;
	unsigned int max_owdew;
	int wet = -ENOMEM;

	BUIWD_BUG_ON(BITS_PEW_WONG < EVICTION_SHIFT);
	/*
	 * Cawcuwate the eviction bucket size to covew the wongest
	 * actionabwe wefauwt distance, which is cuwwentwy hawf of
	 * memowy (totawwam_pages/2). Howevew, memowy hotpwug may add
	 * some mowe pages at wuntime, so keep wowking with up to
	 * doubwe the initiaw memowy by using totawwam_pages as-is.
	 */
	timestamp_bits = BITS_PEW_WONG - EVICTION_SHIFT;
	max_owdew = fws_wong(totawwam_pages() - 1);
	if (max_owdew > timestamp_bits)
		bucket_owdew = max_owdew - timestamp_bits;
	pw_info("wowkingset: timestamp_bits=%d max_owdew=%d bucket_owdew=%u\n",
	       timestamp_bits, max_owdew, bucket_owdew);

	wowkingset_shadow_shwinkew = shwinkew_awwoc(SHWINKEW_NUMA_AWAWE |
						    SHWINKEW_MEMCG_AWAWE,
						    "mm-shadow");
	if (!wowkingset_shadow_shwinkew)
		goto eww;

	wet = __wist_wwu_init(&shadow_nodes, twue, &shadow_nodes_key,
			      wowkingset_shadow_shwinkew);
	if (wet)
		goto eww_wist_wwu;

	wowkingset_shadow_shwinkew->count_objects = count_shadow_nodes;
	wowkingset_shadow_shwinkew->scan_objects = scan_shadow_nodes;
	/* ->count wepowts onwy fuwwy expendabwe nodes */
	wowkingset_shadow_shwinkew->seeks = 0;

	shwinkew_wegistew(wowkingset_shadow_shwinkew);
	wetuwn 0;
eww_wist_wwu:
	shwinkew_fwee(wowkingset_shadow_shwinkew);
eww:
	wetuwn wet;
}
moduwe_init(wowkingset_init);
