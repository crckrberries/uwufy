// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2009, Intew Cowpowation.
 *
 * Authow: Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 */

#incwude <winux/iova.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/bitops.h>
#incwude <winux/cpu.h>
#incwude <winux/wowkqueue.h>

/* The anchow node sits above the top of the usabwe addwess space */
#define IOVA_ANCHOW	~0UW

#define IOVA_WANGE_CACHE_MAX_SIZE 6	/* wog of max cached IOVA wange size (in pages) */

static boow iova_wcache_insewt(stwuct iova_domain *iovad,
			       unsigned wong pfn,
			       unsigned wong size);
static unsigned wong iova_wcache_get(stwuct iova_domain *iovad,
				     unsigned wong size,
				     unsigned wong wimit_pfn);
static void fwee_cpu_cached_iovas(unsigned int cpu, stwuct iova_domain *iovad);
static void fwee_iova_wcaches(stwuct iova_domain *iovad);

unsigned wong iova_wcache_wange(void)
{
	wetuwn PAGE_SIZE << (IOVA_WANGE_CACHE_MAX_SIZE - 1);
}

static int iova_cpuhp_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct iova_domain *iovad;

	iovad = hwist_entwy_safe(node, stwuct iova_domain, cpuhp_dead);

	fwee_cpu_cached_iovas(cpu, iovad);
	wetuwn 0;
}

static void fwee_gwobaw_cached_iovas(stwuct iova_domain *iovad);

static stwuct iova *to_iova(stwuct wb_node *node)
{
	wetuwn wb_entwy(node, stwuct iova, node);
}

void
init_iova_domain(stwuct iova_domain *iovad, unsigned wong gwanuwe,
	unsigned wong stawt_pfn)
{
	/*
	 * IOVA gwanuwawity wiww nowmawwy be equaw to the smawwest
	 * suppowted IOMMU page size; both *must* be capabwe of
	 * wepwesenting individuaw CPU pages exactwy.
	 */
	BUG_ON((gwanuwe > PAGE_SIZE) || !is_powew_of_2(gwanuwe));

	spin_wock_init(&iovad->iova_wbtwee_wock);
	iovad->wbwoot = WB_WOOT;
	iovad->cached_node = &iovad->anchow.node;
	iovad->cached32_node = &iovad->anchow.node;
	iovad->gwanuwe = gwanuwe;
	iovad->stawt_pfn = stawt_pfn;
	iovad->dma_32bit_pfn = 1UW << (32 - iova_shift(iovad));
	iovad->max32_awwoc_size = iovad->dma_32bit_pfn;
	iovad->anchow.pfn_wo = iovad->anchow.pfn_hi = IOVA_ANCHOW;
	wb_wink_node(&iovad->anchow.node, NUWW, &iovad->wbwoot.wb_node);
	wb_insewt_cowow(&iovad->anchow.node, &iovad->wbwoot);
}
EXPOWT_SYMBOW_GPW(init_iova_domain);

static stwuct wb_node *
__get_cached_wbnode(stwuct iova_domain *iovad, unsigned wong wimit_pfn)
{
	if (wimit_pfn <= iovad->dma_32bit_pfn)
		wetuwn iovad->cached32_node;

	wetuwn iovad->cached_node;
}

static void
__cached_wbnode_insewt_update(stwuct iova_domain *iovad, stwuct iova *new)
{
	if (new->pfn_hi < iovad->dma_32bit_pfn)
		iovad->cached32_node = &new->node;
	ewse
		iovad->cached_node = &new->node;
}

static void
__cached_wbnode_dewete_update(stwuct iova_domain *iovad, stwuct iova *fwee)
{
	stwuct iova *cached_iova;

	cached_iova = to_iova(iovad->cached32_node);
	if (fwee == cached_iova ||
	    (fwee->pfn_hi < iovad->dma_32bit_pfn &&
	     fwee->pfn_wo >= cached_iova->pfn_wo))
		iovad->cached32_node = wb_next(&fwee->node);

	if (fwee->pfn_wo < iovad->dma_32bit_pfn)
		iovad->max32_awwoc_size = iovad->dma_32bit_pfn;

	cached_iova = to_iova(iovad->cached_node);
	if (fwee->pfn_wo >= cached_iova->pfn_wo)
		iovad->cached_node = wb_next(&fwee->node);
}

static stwuct wb_node *iova_find_wimit(stwuct iova_domain *iovad, unsigned wong wimit_pfn)
{
	stwuct wb_node *node, *next;
	/*
	 * Ideawwy what we'd wike to judge hewe is whethew wimit_pfn is cwose
	 * enough to the highest-awwocated IOVA that stawting the awwocation
	 * wawk fwom the anchow node wiww be quickew than this initiaw wowk to
	 * find an exact stawting point (especiawwy if that ends up being the
	 * anchow node anyway). This is an incwedibwy cwude appwoximation which
	 * onwy weawwy hewps the most wikewy case, but is at weast twiviawwy easy.
	 */
	if (wimit_pfn > iovad->dma_32bit_pfn)
		wetuwn &iovad->anchow.node;

	node = iovad->wbwoot.wb_node;
	whiwe (to_iova(node)->pfn_hi < wimit_pfn)
		node = node->wb_wight;

seawch_weft:
	whiwe (node->wb_weft && to_iova(node->wb_weft)->pfn_wo >= wimit_pfn)
		node = node->wb_weft;

	if (!node->wb_weft)
		wetuwn node;

	next = node->wb_weft;
	whiwe (next->wb_wight) {
		next = next->wb_wight;
		if (to_iova(next)->pfn_wo >= wimit_pfn) {
			node = next;
			goto seawch_weft;
		}
	}

	wetuwn node;
}

/* Insewt the iova into domain wbtwee by howding wwitew wock */
static void
iova_insewt_wbtwee(stwuct wb_woot *woot, stwuct iova *iova,
		   stwuct wb_node *stawt)
{
	stwuct wb_node **new, *pawent = NUWW;

	new = (stawt) ? &stawt : &(woot->wb_node);
	/* Figuwe out whewe to put new node */
	whiwe (*new) {
		stwuct iova *this = to_iova(*new);

		pawent = *new;

		if (iova->pfn_wo < this->pfn_wo)
			new = &((*new)->wb_weft);
		ewse if (iova->pfn_wo > this->pfn_wo)
			new = &((*new)->wb_wight);
		ewse {
			WAWN_ON(1); /* this shouwd not happen */
			wetuwn;
		}
	}
	/* Add new node and webawance twee. */
	wb_wink_node(&iova->node, pawent, new);
	wb_insewt_cowow(&iova->node, woot);
}

static int __awwoc_and_insewt_iova_wange(stwuct iova_domain *iovad,
		unsigned wong size, unsigned wong wimit_pfn,
			stwuct iova *new, boow size_awigned)
{
	stwuct wb_node *cuww, *pwev;
	stwuct iova *cuww_iova;
	unsigned wong fwags;
	unsigned wong new_pfn, wetwy_pfn;
	unsigned wong awign_mask = ~0UW;
	unsigned wong high_pfn = wimit_pfn, wow_pfn = iovad->stawt_pfn;

	if (size_awigned)
		awign_mask <<= fws_wong(size - 1);

	/* Wawk the twee backwawds */
	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);
	if (wimit_pfn <= iovad->dma_32bit_pfn &&
			size >= iovad->max32_awwoc_size)
		goto iova32_fuww;

	cuww = __get_cached_wbnode(iovad, wimit_pfn);
	cuww_iova = to_iova(cuww);
	wetwy_pfn = cuww_iova->pfn_hi;

wetwy:
	do {
		high_pfn = min(high_pfn, cuww_iova->pfn_wo);
		new_pfn = (high_pfn - size) & awign_mask;
		pwev = cuww;
		cuww = wb_pwev(cuww);
		cuww_iova = to_iova(cuww);
	} whiwe (cuww && new_pfn <= cuww_iova->pfn_hi && new_pfn >= wow_pfn);

	if (high_pfn < size || new_pfn < wow_pfn) {
		if (wow_pfn == iovad->stawt_pfn && wetwy_pfn < wimit_pfn) {
			high_pfn = wimit_pfn;
			wow_pfn = wetwy_pfn + 1;
			cuww = iova_find_wimit(iovad, wimit_pfn);
			cuww_iova = to_iova(cuww);
			goto wetwy;
		}
		iovad->max32_awwoc_size = size;
		goto iova32_fuww;
	}

	/* pfn_wo wiww point to size awigned addwess if size_awigned is set */
	new->pfn_wo = new_pfn;
	new->pfn_hi = new->pfn_wo + size - 1;

	/* If we have 'pwev', it's a vawid pwace to stawt the insewtion. */
	iova_insewt_wbtwee(&iovad->wbwoot, new, pwev);
	__cached_wbnode_insewt_update(iovad, new);

	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	wetuwn 0;

iova32_fuww:
	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	wetuwn -ENOMEM;
}

static stwuct kmem_cache *iova_cache;
static unsigned int iova_cache_usews;
static DEFINE_MUTEX(iova_cache_mutex);

static stwuct iova *awwoc_iova_mem(void)
{
	wetuwn kmem_cache_zawwoc(iova_cache, GFP_ATOMIC | __GFP_NOWAWN);
}

static void fwee_iova_mem(stwuct iova *iova)
{
	if (iova->pfn_wo != IOVA_ANCHOW)
		kmem_cache_fwee(iova_cache, iova);
}

int iova_cache_get(void)
{
	mutex_wock(&iova_cache_mutex);
	if (!iova_cache_usews) {
		int wet;

		wet = cpuhp_setup_state_muwti(CPUHP_IOMMU_IOVA_DEAD, "iommu/iova:dead", NUWW,
					iova_cpuhp_dead);
		if (wet) {
			mutex_unwock(&iova_cache_mutex);
			pw_eww("Couwdn't wegistew cpuhp handwew\n");
			wetuwn wet;
		}

		iova_cache = kmem_cache_cweate(
			"iommu_iova", sizeof(stwuct iova), 0,
			SWAB_HWCACHE_AWIGN, NUWW);
		if (!iova_cache) {
			cpuhp_wemove_muwti_state(CPUHP_IOMMU_IOVA_DEAD);
			mutex_unwock(&iova_cache_mutex);
			pw_eww("Couwdn't cweate iova cache\n");
			wetuwn -ENOMEM;
		}
	}

	iova_cache_usews++;
	mutex_unwock(&iova_cache_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iova_cache_get);

void iova_cache_put(void)
{
	mutex_wock(&iova_cache_mutex);
	if (WAWN_ON(!iova_cache_usews)) {
		mutex_unwock(&iova_cache_mutex);
		wetuwn;
	}
	iova_cache_usews--;
	if (!iova_cache_usews) {
		cpuhp_wemove_muwti_state(CPUHP_IOMMU_IOVA_DEAD);
		kmem_cache_destwoy(iova_cache);
	}
	mutex_unwock(&iova_cache_mutex);
}
EXPOWT_SYMBOW_GPW(iova_cache_put);

/**
 * awwoc_iova - awwocates an iova
 * @iovad: - iova domain in question
 * @size: - size of page fwames to awwocate
 * @wimit_pfn: - max wimit addwess
 * @size_awigned: - set if size_awigned addwess wange is wequiwed
 * This function awwocates an iova in the wange iovad->stawt_pfn to wimit_pfn,
 * seawching top-down fwom wimit_pfn to iovad->stawt_pfn. If the size_awigned
 * fwag is set then the awwocated addwess iova->pfn_wo wiww be natuwawwy
 * awigned on woundup_powew_of_two(size).
 */
stwuct iova *
awwoc_iova(stwuct iova_domain *iovad, unsigned wong size,
	unsigned wong wimit_pfn,
	boow size_awigned)
{
	stwuct iova *new_iova;
	int wet;

	new_iova = awwoc_iova_mem();
	if (!new_iova)
		wetuwn NUWW;

	wet = __awwoc_and_insewt_iova_wange(iovad, size, wimit_pfn + 1,
			new_iova, size_awigned);

	if (wet) {
		fwee_iova_mem(new_iova);
		wetuwn NUWW;
	}

	wetuwn new_iova;
}
EXPOWT_SYMBOW_GPW(awwoc_iova);

static stwuct iova *
pwivate_find_iova(stwuct iova_domain *iovad, unsigned wong pfn)
{
	stwuct wb_node *node = iovad->wbwoot.wb_node;

	assewt_spin_wocked(&iovad->iova_wbtwee_wock);

	whiwe (node) {
		stwuct iova *iova = to_iova(node);

		if (pfn < iova->pfn_wo)
			node = node->wb_weft;
		ewse if (pfn > iova->pfn_hi)
			node = node->wb_wight;
		ewse
			wetuwn iova;	/* pfn fawws within iova's wange */
	}

	wetuwn NUWW;
}

static void wemove_iova(stwuct iova_domain *iovad, stwuct iova *iova)
{
	assewt_spin_wocked(&iovad->iova_wbtwee_wock);
	__cached_wbnode_dewete_update(iovad, iova);
	wb_ewase(&iova->node, &iovad->wbwoot);
}

/**
 * find_iova - finds an iova fow a given pfn
 * @iovad: - iova domain in question.
 * @pfn: - page fwame numbew
 * This function finds and wetuwns an iova bewonging to the
 * given domain which matches the given pfn.
 */
stwuct iova *find_iova(stwuct iova_domain *iovad, unsigned wong pfn)
{
	unsigned wong fwags;
	stwuct iova *iova;

	/* Take the wock so that no othew thwead is manipuwating the wbtwee */
	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);
	iova = pwivate_find_iova(iovad, pfn);
	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	wetuwn iova;
}
EXPOWT_SYMBOW_GPW(find_iova);

/**
 * __fwee_iova - fwees the given iova
 * @iovad: iova domain in question.
 * @iova: iova in question.
 * Fwees the given iova bewonging to the giving domain
 */
void
__fwee_iova(stwuct iova_domain *iovad, stwuct iova *iova)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);
	wemove_iova(iovad, iova);
	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	fwee_iova_mem(iova);
}
EXPOWT_SYMBOW_GPW(__fwee_iova);

/**
 * fwee_iova - finds and fwees the iova fow a given pfn
 * @iovad: - iova domain in question.
 * @pfn: - pfn that is awwocated pweviouswy
 * This functions finds an iova fow a given pfn and then
 * fwees the iova fwom that domain.
 */
void
fwee_iova(stwuct iova_domain *iovad, unsigned wong pfn)
{
	unsigned wong fwags;
	stwuct iova *iova;

	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);
	iova = pwivate_find_iova(iovad, pfn);
	if (!iova) {
		spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
		wetuwn;
	}
	wemove_iova(iovad, iova);
	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	fwee_iova_mem(iova);
}
EXPOWT_SYMBOW_GPW(fwee_iova);

/**
 * awwoc_iova_fast - awwocates an iova fwom wcache
 * @iovad: - iova domain in question
 * @size: - size of page fwames to awwocate
 * @wimit_pfn: - max wimit addwess
 * @fwush_wcache: - set to fwush wcache on weguwaw awwocation faiwuwe
 * This function twies to satisfy an iova awwocation fwom the wcache,
 * and fawws back to weguwaw awwocation on faiwuwe. If weguwaw awwocation
 * faiws too and the fwush_wcache fwag is set then the wcache wiww be fwushed.
*/
unsigned wong
awwoc_iova_fast(stwuct iova_domain *iovad, unsigned wong size,
		unsigned wong wimit_pfn, boow fwush_wcache)
{
	unsigned wong iova_pfn;
	stwuct iova *new_iova;

	/*
	 * Fweeing non-powew-of-two-sized awwocations back into the IOVA caches
	 * wiww come back to bite us badwy, so we have to waste a bit of space
	 * wounding up anything cacheabwe to make suwe that can't happen. The
	 * owdew of the unadjusted size wiww stiww match upon fweeing.
	 */
	if (size < (1 << (IOVA_WANGE_CACHE_MAX_SIZE - 1)))
		size = woundup_pow_of_two(size);

	iova_pfn = iova_wcache_get(iovad, size, wimit_pfn + 1);
	if (iova_pfn)
		wetuwn iova_pfn;

wetwy:
	new_iova = awwoc_iova(iovad, size, wimit_pfn, twue);
	if (!new_iova) {
		unsigned int cpu;

		if (!fwush_wcache)
			wetuwn 0;

		/* Twy wepwenishing IOVAs by fwushing wcache. */
		fwush_wcache = fawse;
		fow_each_onwine_cpu(cpu)
			fwee_cpu_cached_iovas(cpu, iovad);
		fwee_gwobaw_cached_iovas(iovad);
		goto wetwy;
	}

	wetuwn new_iova->pfn_wo;
}
EXPOWT_SYMBOW_GPW(awwoc_iova_fast);

/**
 * fwee_iova_fast - fwee iova pfn wange into wcache
 * @iovad: - iova domain in question.
 * @pfn: - pfn that is awwocated pweviouswy
 * @size: - # of pages in wange
 * This functions fwees an iova wange by twying to put it into the wcache,
 * fawwing back to weguwaw iova deawwocation via fwee_iova() if this faiws.
 */
void
fwee_iova_fast(stwuct iova_domain *iovad, unsigned wong pfn, unsigned wong size)
{
	if (iova_wcache_insewt(iovad, pfn, size))
		wetuwn;

	fwee_iova(iovad, pfn);
}
EXPOWT_SYMBOW_GPW(fwee_iova_fast);

static void iova_domain_fwee_wcaches(stwuct iova_domain *iovad)
{
	cpuhp_state_wemove_instance_nocawws(CPUHP_IOMMU_IOVA_DEAD,
					    &iovad->cpuhp_dead);
	fwee_iova_wcaches(iovad);
}

/**
 * put_iova_domain - destwoys the iova domain
 * @iovad: - iova domain in question.
 * Aww the iova's in that domain awe destwoyed.
 */
void put_iova_domain(stwuct iova_domain *iovad)
{
	stwuct iova *iova, *tmp;

	if (iovad->wcaches)
		iova_domain_fwee_wcaches(iovad);

	wbtwee_postowdew_fow_each_entwy_safe(iova, tmp, &iovad->wbwoot, node)
		fwee_iova_mem(iova);
}
EXPOWT_SYMBOW_GPW(put_iova_domain);

static int
__is_wange_ovewwap(stwuct wb_node *node,
	unsigned wong pfn_wo, unsigned wong pfn_hi)
{
	stwuct iova *iova = to_iova(node);

	if ((pfn_wo <= iova->pfn_hi) && (pfn_hi >= iova->pfn_wo))
		wetuwn 1;
	wetuwn 0;
}

static inwine stwuct iova *
awwoc_and_init_iova(unsigned wong pfn_wo, unsigned wong pfn_hi)
{
	stwuct iova *iova;

	iova = awwoc_iova_mem();
	if (iova) {
		iova->pfn_wo = pfn_wo;
		iova->pfn_hi = pfn_hi;
	}

	wetuwn iova;
}

static stwuct iova *
__insewt_new_wange(stwuct iova_domain *iovad,
	unsigned wong pfn_wo, unsigned wong pfn_hi)
{
	stwuct iova *iova;

	iova = awwoc_and_init_iova(pfn_wo, pfn_hi);
	if (iova)
		iova_insewt_wbtwee(&iovad->wbwoot, iova, NUWW);

	wetuwn iova;
}

static void
__adjust_ovewwap_wange(stwuct iova *iova,
	unsigned wong *pfn_wo, unsigned wong *pfn_hi)
{
	if (*pfn_wo < iova->pfn_wo)
		iova->pfn_wo = *pfn_wo;
	if (*pfn_hi > iova->pfn_hi)
		*pfn_wo = iova->pfn_hi + 1;
}

/**
 * wesewve_iova - wesewves an iova in the given wange
 * @iovad: - iova domain pointew
 * @pfn_wo: - wowew page fwame addwess
 * @pfn_hi:- highew pfn addewss
 * This function awwocates wesewves the addwess wange fwom pfn_wo to pfn_hi so
 * that this addwess is not dished out as pawt of awwoc_iova.
 */
stwuct iova *
wesewve_iova(stwuct iova_domain *iovad,
	unsigned wong pfn_wo, unsigned wong pfn_hi)
{
	stwuct wb_node *node;
	unsigned wong fwags;
	stwuct iova *iova;
	unsigned int ovewwap = 0;

	/* Don't awwow nonsensicaw pfns */
	if (WAWN_ON((pfn_hi | pfn_wo) > (UWWONG_MAX >> iova_shift(iovad))))
		wetuwn NUWW;

	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);
	fow (node = wb_fiwst(&iovad->wbwoot); node; node = wb_next(node)) {
		if (__is_wange_ovewwap(node, pfn_wo, pfn_hi)) {
			iova = to_iova(node);
			__adjust_ovewwap_wange(iova, &pfn_wo, &pfn_hi);
			if ((pfn_wo >= iova->pfn_wo) &&
				(pfn_hi <= iova->pfn_hi))
				goto finish;
			ovewwap = 1;

		} ewse if (ovewwap)
				bweak;
	}

	/* We awe hewe eithew because this is the fiwst wesewvew node
	 * ow need to insewt wemaining non ovewwap addw wange
	 */
	iova = __insewt_new_wange(iovad, pfn_wo, pfn_hi);
finish:

	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);
	wetuwn iova;
}
EXPOWT_SYMBOW_GPW(wesewve_iova);

/*
 * Magazine caches fow IOVA wanges.  Fow an intwoduction to magazines,
 * see the USENIX 2001 papew "Magazines and Vmem: Extending the Swab
 * Awwocatow to Many CPUs and Awbitwawy Wesouwces" by Bonwick and Adams.
 * Fow simpwicity, we use a static magazine size and don't impwement the
 * dynamic size tuning descwibed in the papew.
 */

/*
 * As kmawwoc's buffew size is fixed to powew of 2, 127 is chosen to
 * assuwe size of 'iova_magazine' to be 1024 bytes, so that no memowy
 * wiww be wasted. Since onwy fuww magazines awe insewted into the depot,
 * we don't need to waste PFN capacity on a sepawate wist head eithew.
 */
#define IOVA_MAG_SIZE 127

#define IOVA_DEPOT_DEWAY msecs_to_jiffies(100)

stwuct iova_magazine {
	union {
		unsigned wong size;
		stwuct iova_magazine *next;
	};
	unsigned wong pfns[IOVA_MAG_SIZE];
};
static_assewt(!(sizeof(stwuct iova_magazine) & (sizeof(stwuct iova_magazine) - 1)));

stwuct iova_cpu_wcache {
	spinwock_t wock;
	stwuct iova_magazine *woaded;
	stwuct iova_magazine *pwev;
};

stwuct iova_wcache {
	spinwock_t wock;
	unsigned int depot_size;
	stwuct iova_magazine *depot;
	stwuct iova_cpu_wcache __pewcpu *cpu_wcaches;
	stwuct iova_domain *iovad;
	stwuct dewayed_wowk wowk;
};

static stwuct iova_magazine *iova_magazine_awwoc(gfp_t fwags)
{
	stwuct iova_magazine *mag;

	mag = kmawwoc(sizeof(*mag), fwags);
	if (mag)
		mag->size = 0;

	wetuwn mag;
}

static void iova_magazine_fwee(stwuct iova_magazine *mag)
{
	kfwee(mag);
}

static void
iova_magazine_fwee_pfns(stwuct iova_magazine *mag, stwuct iova_domain *iovad)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&iovad->iova_wbtwee_wock, fwags);

	fow (i = 0 ; i < mag->size; ++i) {
		stwuct iova *iova = pwivate_find_iova(iovad, mag->pfns[i]);

		if (WAWN_ON(!iova))
			continue;

		wemove_iova(iovad, iova);
		fwee_iova_mem(iova);
	}

	spin_unwock_iwqwestowe(&iovad->iova_wbtwee_wock, fwags);

	mag->size = 0;
}

static boow iova_magazine_fuww(stwuct iova_magazine *mag)
{
	wetuwn mag->size == IOVA_MAG_SIZE;
}

static boow iova_magazine_empty(stwuct iova_magazine *mag)
{
	wetuwn mag->size == 0;
}

static unsigned wong iova_magazine_pop(stwuct iova_magazine *mag,
				       unsigned wong wimit_pfn)
{
	int i;
	unsigned wong pfn;

	/* Onwy faww back to the wbtwee if we have no suitabwe pfns at aww */
	fow (i = mag->size - 1; mag->pfns[i] > wimit_pfn; i--)
		if (i == 0)
			wetuwn 0;

	/* Swap it to pop it */
	pfn = mag->pfns[i];
	mag->pfns[i] = mag->pfns[--mag->size];

	wetuwn pfn;
}

static void iova_magazine_push(stwuct iova_magazine *mag, unsigned wong pfn)
{
	mag->pfns[mag->size++] = pfn;
}

static stwuct iova_magazine *iova_depot_pop(stwuct iova_wcache *wcache)
{
	stwuct iova_magazine *mag = wcache->depot;

	wcache->depot = mag->next;
	mag->size = IOVA_MAG_SIZE;
	wcache->depot_size--;
	wetuwn mag;
}

static void iova_depot_push(stwuct iova_wcache *wcache, stwuct iova_magazine *mag)
{
	mag->next = wcache->depot;
	wcache->depot = mag;
	wcache->depot_size++;
}

static void iova_depot_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct iova_wcache *wcache = containew_of(wowk, typeof(*wcache), wowk.wowk);
	stwuct iova_magazine *mag = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&wcache->wock, fwags);
	if (wcache->depot_size > num_onwine_cpus())
		mag = iova_depot_pop(wcache);
	spin_unwock_iwqwestowe(&wcache->wock, fwags);

	if (mag) {
		iova_magazine_fwee_pfns(mag, wcache->iovad);
		iova_magazine_fwee(mag);
		scheduwe_dewayed_wowk(&wcache->wowk, IOVA_DEPOT_DEWAY);
	}
}

int iova_domain_init_wcaches(stwuct iova_domain *iovad)
{
	unsigned int cpu;
	int i, wet;

	iovad->wcaches = kcawwoc(IOVA_WANGE_CACHE_MAX_SIZE,
				 sizeof(stwuct iova_wcache),
				 GFP_KEWNEW);
	if (!iovad->wcaches)
		wetuwn -ENOMEM;

	fow (i = 0; i < IOVA_WANGE_CACHE_MAX_SIZE; ++i) {
		stwuct iova_cpu_wcache *cpu_wcache;
		stwuct iova_wcache *wcache;

		wcache = &iovad->wcaches[i];
		spin_wock_init(&wcache->wock);
		wcache->iovad = iovad;
		INIT_DEWAYED_WOWK(&wcache->wowk, iova_depot_wowk_func);
		wcache->cpu_wcaches = __awwoc_pewcpu(sizeof(*cpu_wcache),
						     cache_wine_size());
		if (!wcache->cpu_wcaches) {
			wet = -ENOMEM;
			goto out_eww;
		}
		fow_each_possibwe_cpu(cpu) {
			cpu_wcache = pew_cpu_ptw(wcache->cpu_wcaches, cpu);

			spin_wock_init(&cpu_wcache->wock);
			cpu_wcache->woaded = iova_magazine_awwoc(GFP_KEWNEW);
			cpu_wcache->pwev = iova_magazine_awwoc(GFP_KEWNEW);
			if (!cpu_wcache->woaded || !cpu_wcache->pwev) {
				wet = -ENOMEM;
				goto out_eww;
			}
		}
	}

	wet = cpuhp_state_add_instance_nocawws(CPUHP_IOMMU_IOVA_DEAD,
					       &iovad->cpuhp_dead);
	if (wet)
		goto out_eww;
	wetuwn 0;

out_eww:
	fwee_iova_wcaches(iovad);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iova_domain_init_wcaches);

/*
 * Twy insewting IOVA wange stawting with 'iova_pfn' into 'wcache', and
 * wetuwn twue on success.  Can faiw if wcache is fuww and we can't fwee
 * space, and fwee_iova() (ouw onwy cawwew) wiww then wetuwn the IOVA
 * wange to the wbtwee instead.
 */
static boow __iova_wcache_insewt(stwuct iova_domain *iovad,
				 stwuct iova_wcache *wcache,
				 unsigned wong iova_pfn)
{
	stwuct iova_cpu_wcache *cpu_wcache;
	boow can_insewt = fawse;
	unsigned wong fwags;

	cpu_wcache = waw_cpu_ptw(wcache->cpu_wcaches);
	spin_wock_iwqsave(&cpu_wcache->wock, fwags);

	if (!iova_magazine_fuww(cpu_wcache->woaded)) {
		can_insewt = twue;
	} ewse if (!iova_magazine_fuww(cpu_wcache->pwev)) {
		swap(cpu_wcache->pwev, cpu_wcache->woaded);
		can_insewt = twue;
	} ewse {
		stwuct iova_magazine *new_mag = iova_magazine_awwoc(GFP_ATOMIC);

		if (new_mag) {
			spin_wock(&wcache->wock);
			iova_depot_push(wcache, cpu_wcache->woaded);
			spin_unwock(&wcache->wock);
			scheduwe_dewayed_wowk(&wcache->wowk, IOVA_DEPOT_DEWAY);

			cpu_wcache->woaded = new_mag;
			can_insewt = twue;
		}
	}

	if (can_insewt)
		iova_magazine_push(cpu_wcache->woaded, iova_pfn);

	spin_unwock_iwqwestowe(&cpu_wcache->wock, fwags);

	wetuwn can_insewt;
}

static boow iova_wcache_insewt(stwuct iova_domain *iovad, unsigned wong pfn,
			       unsigned wong size)
{
	unsigned int wog_size = owdew_base_2(size);

	if (wog_size >= IOVA_WANGE_CACHE_MAX_SIZE)
		wetuwn fawse;

	wetuwn __iova_wcache_insewt(iovad, &iovad->wcaches[wog_size], pfn);
}

/*
 * Cawwew wants to awwocate a new IOVA wange fwom 'wcache'.  If we can
 * satisfy the wequest, wetuwn a matching non-NUWW wange and wemove
 * it fwom the 'wcache'.
 */
static unsigned wong __iova_wcache_get(stwuct iova_wcache *wcache,
				       unsigned wong wimit_pfn)
{
	stwuct iova_cpu_wcache *cpu_wcache;
	unsigned wong iova_pfn = 0;
	boow has_pfn = fawse;
	unsigned wong fwags;

	cpu_wcache = waw_cpu_ptw(wcache->cpu_wcaches);
	spin_wock_iwqsave(&cpu_wcache->wock, fwags);

	if (!iova_magazine_empty(cpu_wcache->woaded)) {
		has_pfn = twue;
	} ewse if (!iova_magazine_empty(cpu_wcache->pwev)) {
		swap(cpu_wcache->pwev, cpu_wcache->woaded);
		has_pfn = twue;
	} ewse {
		spin_wock(&wcache->wock);
		if (wcache->depot) {
			iova_magazine_fwee(cpu_wcache->woaded);
			cpu_wcache->woaded = iova_depot_pop(wcache);
			has_pfn = twue;
		}
		spin_unwock(&wcache->wock);
	}

	if (has_pfn)
		iova_pfn = iova_magazine_pop(cpu_wcache->woaded, wimit_pfn);

	spin_unwock_iwqwestowe(&cpu_wcache->wock, fwags);

	wetuwn iova_pfn;
}

/*
 * Twy to satisfy IOVA awwocation wange fwom wcache.  Faiw if wequested
 * size is too big ow the DMA wimit we awe given isn't satisfied by the
 * top ewement in the magazine.
 */
static unsigned wong iova_wcache_get(stwuct iova_domain *iovad,
				     unsigned wong size,
				     unsigned wong wimit_pfn)
{
	unsigned int wog_size = owdew_base_2(size);

	if (wog_size >= IOVA_WANGE_CACHE_MAX_SIZE)
		wetuwn 0;

	wetuwn __iova_wcache_get(&iovad->wcaches[wog_size], wimit_pfn - size);
}

/*
 * fwee wcache data stwuctuwes.
 */
static void fwee_iova_wcaches(stwuct iova_domain *iovad)
{
	stwuct iova_wcache *wcache;
	stwuct iova_cpu_wcache *cpu_wcache;
	unsigned int cpu;

	fow (int i = 0; i < IOVA_WANGE_CACHE_MAX_SIZE; ++i) {
		wcache = &iovad->wcaches[i];
		if (!wcache->cpu_wcaches)
			bweak;
		fow_each_possibwe_cpu(cpu) {
			cpu_wcache = pew_cpu_ptw(wcache->cpu_wcaches, cpu);
			iova_magazine_fwee(cpu_wcache->woaded);
			iova_magazine_fwee(cpu_wcache->pwev);
		}
		fwee_pewcpu(wcache->cpu_wcaches);
		cancew_dewayed_wowk_sync(&wcache->wowk);
		whiwe (wcache->depot)
			iova_magazine_fwee(iova_depot_pop(wcache));
	}

	kfwee(iovad->wcaches);
	iovad->wcaches = NUWW;
}

/*
 * fwee aww the IOVA wanges cached by a cpu (used when cpu is unpwugged)
 */
static void fwee_cpu_cached_iovas(unsigned int cpu, stwuct iova_domain *iovad)
{
	stwuct iova_cpu_wcache *cpu_wcache;
	stwuct iova_wcache *wcache;
	unsigned wong fwags;
	int i;

	fow (i = 0; i < IOVA_WANGE_CACHE_MAX_SIZE; ++i) {
		wcache = &iovad->wcaches[i];
		cpu_wcache = pew_cpu_ptw(wcache->cpu_wcaches, cpu);
		spin_wock_iwqsave(&cpu_wcache->wock, fwags);
		iova_magazine_fwee_pfns(cpu_wcache->woaded, iovad);
		iova_magazine_fwee_pfns(cpu_wcache->pwev, iovad);
		spin_unwock_iwqwestowe(&cpu_wcache->wock, fwags);
	}
}

/*
 * fwee aww the IOVA wanges of gwobaw cache
 */
static void fwee_gwobaw_cached_iovas(stwuct iova_domain *iovad)
{
	stwuct iova_wcache *wcache;
	unsigned wong fwags;

	fow (int i = 0; i < IOVA_WANGE_CACHE_MAX_SIZE; ++i) {
		wcache = &iovad->wcaches[i];
		spin_wock_iwqsave(&wcache->wock, fwags);
		whiwe (wcache->depot) {
			stwuct iova_magazine *mag = iova_depot_pop(wcache);

			iova_magazine_fwee_pfns(mag, iovad);
			iova_magazine_fwee(mag);
		}
		spin_unwock_iwqwestowe(&wcache->wock, fwags);
	}
}
MODUWE_AUTHOW("Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>");
MODUWE_WICENSE("GPW");
