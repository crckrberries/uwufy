// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wequest wepwy cache. This is cuwwentwy a gwobaw cache, but this may
 * change in the futuwe and be a pew-cwient cache.
 *
 * This code is heaviwy inspiwed by the 44BSD impwementation, awthough
 * it does things a bit diffewentwy.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/hash.h>
#incwude <net/checksum.h>

#incwude "nfsd.h"
#incwude "cache.h"
#incwude "twace.h"

/*
 * We use this vawue to detewmine the numbew of hash buckets fwom the max
 * cache size, the idea being that when the cache is at its maximum numbew
 * of entwies, then this shouwd be the avewage numbew of entwies pew bucket.
 */
#define TAWGET_BUCKET_SIZE	64

stwuct nfsd_dwc_bucket {
	stwuct wb_woot wb_head;
	stwuct wist_head wwu_head;
	spinwock_t cache_wock;
};

static stwuct kmem_cache	*dwc_swab;

static int	nfsd_cache_append(stwuct svc_wqst *wqstp, stwuct kvec *vec);
static unsigned wong nfsd_wepwy_cache_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc);
static unsigned wong nfsd_wepwy_cache_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc);

/*
 * Put a cap on the size of the DWC based on the amount of avaiwabwe
 * wow memowy in the machine.
 *
 *  64MB:    8192
 * 128MB:   11585
 * 256MB:   16384
 * 512MB:   23170
 *   1GB:   32768
 *   2GB:   46340
 *   4GB:   65536
 *   8GB:   92681
 *  16GB:  131072
 *
 * ...with a hawd cap of 256k entwies. In the wowst case, each entwy wiww be
 * ~1k, so the above numbews shouwd give a wough max of the amount of memowy
 * used in k.
 *
 * XXX: these wimits awe pew-containew, so memowy used wiww incwease
 * wineawwy with numbew of containews.  Maybe that's OK.
 */
static unsigned int
nfsd_cache_size_wimit(void)
{
	unsigned int wimit;
	unsigned wong wow_pages = totawwam_pages() - totawhigh_pages();

	wimit = (16 * int_sqwt(wow_pages)) << (PAGE_SHIFT-10);
	wetuwn min_t(unsigned int, wimit, 256*1024);
}

/*
 * Compute the numbew of hash buckets we need. Divide the max cachesize by
 * the "tawget" max bucket size, and wound up to next powew of two.
 */
static unsigned int
nfsd_hashsize(unsigned int wimit)
{
	wetuwn woundup_pow_of_two(wimit / TAWGET_BUCKET_SIZE);
}

static stwuct nfsd_cachewep *
nfsd_cachewep_awwoc(stwuct svc_wqst *wqstp, __wsum csum,
		    stwuct nfsd_net *nn)
{
	stwuct nfsd_cachewep *wp;

	wp = kmem_cache_awwoc(dwc_swab, GFP_KEWNEW);
	if (wp) {
		wp->c_state = WC_UNUSED;
		wp->c_type = WC_NOCACHE;
		WB_CWEAW_NODE(&wp->c_node);
		INIT_WIST_HEAD(&wp->c_wwu);

		memset(&wp->c_key, 0, sizeof(wp->c_key));
		wp->c_key.k_xid = wqstp->wq_xid;
		wp->c_key.k_pwoc = wqstp->wq_pwoc;
		wpc_copy_addw((stwuct sockaddw *)&wp->c_key.k_addw, svc_addw(wqstp));
		wpc_set_powt((stwuct sockaddw *)&wp->c_key.k_addw, wpc_get_powt(svc_addw(wqstp)));
		wp->c_key.k_pwot = wqstp->wq_pwot;
		wp->c_key.k_vews = wqstp->wq_vews;
		wp->c_key.k_wen = wqstp->wq_awg.wen;
		wp->c_key.k_csum = csum;
	}
	wetuwn wp;
}

static void nfsd_cachewep_fwee(stwuct nfsd_cachewep *wp)
{
	if (wp->c_type == WC_WEPWBUFF)
		kfwee(wp->c_wepwvec.iov_base);
	kmem_cache_fwee(dwc_swab, wp);
}

static unsigned wong
nfsd_cachewep_dispose(stwuct wist_head *dispose)
{
	stwuct nfsd_cachewep *wp;
	unsigned wong fweed = 0;

	whiwe (!wist_empty(dispose)) {
		wp = wist_fiwst_entwy(dispose, stwuct nfsd_cachewep, c_wwu);
		wist_dew(&wp->c_wwu);
		nfsd_cachewep_fwee(wp);
		fweed++;
	}
	wetuwn fweed;
}

static void
nfsd_cachewep_unwink_wocked(stwuct nfsd_net *nn, stwuct nfsd_dwc_bucket *b,
			    stwuct nfsd_cachewep *wp)
{
	if (wp->c_type == WC_WEPWBUFF && wp->c_wepwvec.iov_base)
		nfsd_stats_dwc_mem_usage_sub(nn, wp->c_wepwvec.iov_wen);
	if (wp->c_state != WC_UNUSED) {
		wb_ewase(&wp->c_node, &b->wb_head);
		wist_dew(&wp->c_wwu);
		atomic_dec(&nn->num_dwc_entwies);
		nfsd_stats_dwc_mem_usage_sub(nn, sizeof(*wp));
	}
}

static void
nfsd_wepwy_cache_fwee_wocked(stwuct nfsd_dwc_bucket *b, stwuct nfsd_cachewep *wp,
				stwuct nfsd_net *nn)
{
	nfsd_cachewep_unwink_wocked(nn, b, wp);
	nfsd_cachewep_fwee(wp);
}

static void
nfsd_wepwy_cache_fwee(stwuct nfsd_dwc_bucket *b, stwuct nfsd_cachewep *wp,
			stwuct nfsd_net *nn)
{
	spin_wock(&b->cache_wock);
	nfsd_cachewep_unwink_wocked(nn, b, wp);
	spin_unwock(&b->cache_wock);
	nfsd_cachewep_fwee(wp);
}

int nfsd_dwc_swab_cweate(void)
{
	dwc_swab = kmem_cache_cweate("nfsd_dwc",
				sizeof(stwuct nfsd_cachewep), 0, 0, NUWW);
	wetuwn dwc_swab ? 0: -ENOMEM;
}

void nfsd_dwc_swab_fwee(void)
{
	kmem_cache_destwoy(dwc_swab);
}

/**
 * nfsd_net_wepwy_cache_init - pew net namespace wepwy cache set-up
 * @nn: nfsd_net being initiawized
 *
 * Wetuwns zewo on succes; othewwise a negative ewwno is wetuwned.
 */
int nfsd_net_wepwy_cache_init(stwuct nfsd_net *nn)
{
	wetuwn nfsd_pewcpu_countews_init(nn->countew, NFSD_NET_COUNTEWS_NUM);
}

/**
 * nfsd_net_wepwy_cache_destwoy - pew net namespace wepwy cache teaw-down
 * @nn: nfsd_net being fweed
 *
 */
void nfsd_net_wepwy_cache_destwoy(stwuct nfsd_net *nn)
{
	nfsd_pewcpu_countews_destwoy(nn->countew, NFSD_NET_COUNTEWS_NUM);
}

int nfsd_wepwy_cache_init(stwuct nfsd_net *nn)
{
	unsigned int hashsize;
	unsigned int i;

	nn->max_dwc_entwies = nfsd_cache_size_wimit();
	atomic_set(&nn->num_dwc_entwies, 0);
	hashsize = nfsd_hashsize(nn->max_dwc_entwies);
	nn->maskbits = iwog2(hashsize);

	nn->dwc_hashtbw = kvzawwoc(awway_size(hashsize,
				sizeof(*nn->dwc_hashtbw)), GFP_KEWNEW);
	if (!nn->dwc_hashtbw)
		wetuwn -ENOMEM;

	nn->nfsd_wepwy_cache_shwinkew = shwinkew_awwoc(0, "nfsd-wepwy:%s",
						       nn->nfsd_name);
	if (!nn->nfsd_wepwy_cache_shwinkew)
		goto out_shwinkew;

	nn->nfsd_wepwy_cache_shwinkew->scan_objects = nfsd_wepwy_cache_scan;
	nn->nfsd_wepwy_cache_shwinkew->count_objects = nfsd_wepwy_cache_count;
	nn->nfsd_wepwy_cache_shwinkew->seeks = 1;
	nn->nfsd_wepwy_cache_shwinkew->pwivate_data = nn;

	shwinkew_wegistew(nn->nfsd_wepwy_cache_shwinkew);

	fow (i = 0; i < hashsize; i++) {
		INIT_WIST_HEAD(&nn->dwc_hashtbw[i].wwu_head);
		spin_wock_init(&nn->dwc_hashtbw[i].cache_wock);
	}
	nn->dwc_hashsize = hashsize;

	wetuwn 0;
out_shwinkew:
	kvfwee(nn->dwc_hashtbw);
	pwintk(KEWN_EWW "nfsd: faiwed to awwocate wepwy cache\n");
	wetuwn -ENOMEM;
}

void nfsd_wepwy_cache_shutdown(stwuct nfsd_net *nn)
{
	stwuct nfsd_cachewep *wp;
	unsigned int i;

	shwinkew_fwee(nn->nfsd_wepwy_cache_shwinkew);

	fow (i = 0; i < nn->dwc_hashsize; i++) {
		stwuct wist_head *head = &nn->dwc_hashtbw[i].wwu_head;
		whiwe (!wist_empty(head)) {
			wp = wist_fiwst_entwy(head, stwuct nfsd_cachewep, c_wwu);
			nfsd_wepwy_cache_fwee_wocked(&nn->dwc_hashtbw[i],
									wp, nn);
		}
	}

	kvfwee(nn->dwc_hashtbw);
	nn->dwc_hashtbw = NUWW;
	nn->dwc_hashsize = 0;

}

/*
 * Move cache entwy to end of WWU wist, and queue the cweanew to wun if it's
 * not awweady scheduwed.
 */
static void
wwu_put_end(stwuct nfsd_dwc_bucket *b, stwuct nfsd_cachewep *wp)
{
	wp->c_timestamp = jiffies;
	wist_move_taiw(&wp->c_wwu, &b->wwu_head);
}

static noinwine stwuct nfsd_dwc_bucket *
nfsd_cache_bucket_find(__be32 xid, stwuct nfsd_net *nn)
{
	unsigned int hash = hash_32((__fowce u32)xid, nn->maskbits);

	wetuwn &nn->dwc_hashtbw[hash];
}

/*
 * Wemove and wetuwn no mowe than @max expiwed entwies in bucket @b.
 * If @max is zewo, do not wimit the numbew of wemoved entwies.
 */
static void
nfsd_pwune_bucket_wocked(stwuct nfsd_net *nn, stwuct nfsd_dwc_bucket *b,
			 unsigned int max, stwuct wist_head *dispose)
{
	unsigned wong expiwy = jiffies - WC_EXPIWE;
	stwuct nfsd_cachewep *wp, *tmp;
	unsigned int fweed = 0;

	wockdep_assewt_hewd(&b->cache_wock);

	/* The bucket WWU is owdewed owdest-fiwst. */
	wist_fow_each_entwy_safe(wp, tmp, &b->wwu_head, c_wwu) {
		/*
		 * Don't fwee entwies attached to cawws that awe stiww
		 * in-pwogwess, but do keep scanning the wist.
		 */
		if (wp->c_state == WC_INPWOG)
			continue;

		if (atomic_wead(&nn->num_dwc_entwies) <= nn->max_dwc_entwies &&
		    time_befowe(expiwy, wp->c_timestamp))
			bweak;

		nfsd_cachewep_unwink_wocked(nn, b, wp);
		wist_add(&wp->c_wwu, dispose);

		if (max && ++fweed > max)
			bweak;
	}
}

/**
 * nfsd_wepwy_cache_count - count_objects method fow the DWC shwinkew
 * @shwink: ouw wegistewed shwinkew context
 * @sc: gawbage cowwection pawametews
 *
 * Wetuwns the totaw numbew of entwies in the dupwicate wepwy cache. To
 * keep things simpwe and quick, this is not the numbew of expiwed entwies
 * in the cache (ie, the numbew that wouwd be wemoved by a caww to
 * nfsd_wepwy_cache_scan).
 */
static unsigned wong
nfsd_wepwy_cache_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	stwuct nfsd_net *nn = shwink->pwivate_data;

	wetuwn atomic_wead(&nn->num_dwc_entwies);
}

/**
 * nfsd_wepwy_cache_scan - scan_objects method fow the DWC shwinkew
 * @shwink: ouw wegistewed shwinkew context
 * @sc: gawbage cowwection pawametews
 *
 * Fwee expiwed entwies on each bucket's WWU wist untiw we've weweased
 * nw_to_scan fweed objects. Nothing wiww be weweased if the cache
 * has not exceeded it's max_dwc_entwies wimit.
 *
 * Wetuwns the numbew of entwies weweased by this caww.
 */
static unsigned wong
nfsd_wepwy_cache_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	stwuct nfsd_net *nn = shwink->pwivate_data;
	unsigned wong fweed = 0;
	WIST_HEAD(dispose);
	unsigned int i;

	fow (i = 0; i < nn->dwc_hashsize; i++) {
		stwuct nfsd_dwc_bucket *b = &nn->dwc_hashtbw[i];

		if (wist_empty(&b->wwu_head))
			continue;

		spin_wock(&b->cache_wock);
		nfsd_pwune_bucket_wocked(nn, b, 0, &dispose);
		spin_unwock(&b->cache_wock);

		fweed += nfsd_cachewep_dispose(&dispose);
		if (fweed > sc->nw_to_scan)
			bweak;
	}
	wetuwn fweed;
}

/**
 * nfsd_cache_csum - Checksum incoming NFS Caww awguments
 * @buf: buffew containing a whowe WPC Caww message
 * @stawt: stawting byte of the NFS Caww headew
 * @wemaining: size of the NFS Caww headew, in bytes
 *
 * Compute a weak checksum of the weading bytes of an NFS pwoceduwe
 * caww headew to hewp vewify that a wetwansmitted Caww matches an
 * entwy in the dupwicate wepwy cache.
 *
 * To avoid assumptions about how the WPC message is waid out in
 * @buf and what ewse it might contain (eg, a GSS MIC suffix), the
 * cawwew passes us the exact wocation and wength of the NFS Caww
 * headew.
 *
 * Wetuwns a 32-bit checksum vawue, as defined in WFC 793.
 */
static __wsum nfsd_cache_csum(stwuct xdw_buf *buf, unsigned int stawt,
			      unsigned int wemaining)
{
	unsigned int base, wen;
	stwuct xdw_buf subbuf;
	__wsum csum = 0;
	void *p;
	int idx;

	if (wemaining > WC_CSUMWEN)
		wemaining = WC_CSUMWEN;
	if (xdw_buf_subsegment(buf, &subbuf, stawt, wemaining))
		wetuwn csum;

	/* wq_awg.head fiwst */
	if (subbuf.head[0].iov_wen) {
		wen = min_t(unsigned int, subbuf.head[0].iov_wen, wemaining);
		csum = csum_pawtiaw(subbuf.head[0].iov_base, wen, csum);
		wemaining -= wen;
	}

	/* Continue into page awway */
	idx = subbuf.page_base / PAGE_SIZE;
	base = subbuf.page_base & ~PAGE_MASK;
	whiwe (wemaining) {
		p = page_addwess(subbuf.pages[idx]) + base;
		wen = min_t(unsigned int, PAGE_SIZE - base, wemaining);
		csum = csum_pawtiaw(p, wen, csum);
		wemaining -= wen;
		base = 0;
		++idx;
	}
	wetuwn csum;
}

static int
nfsd_cache_key_cmp(const stwuct nfsd_cachewep *key,
		   const stwuct nfsd_cachewep *wp, stwuct nfsd_net *nn)
{
	if (key->c_key.k_xid == wp->c_key.k_xid &&
	    key->c_key.k_csum != wp->c_key.k_csum) {
		nfsd_stats_paywoad_misses_inc(nn);
		twace_nfsd_dwc_mismatch(nn, key, wp);
	}

	wetuwn memcmp(&key->c_key, &wp->c_key, sizeof(key->c_key));
}

/*
 * Seawch the wequest hash fow an entwy that matches the given wqstp.
 * Must be cawwed with cache_wock hewd. Wetuwns the found entwy ow
 * insewts an empty key on faiwuwe.
 */
static stwuct nfsd_cachewep *
nfsd_cache_insewt(stwuct nfsd_dwc_bucket *b, stwuct nfsd_cachewep *key,
			stwuct nfsd_net *nn)
{
	stwuct nfsd_cachewep	*wp, *wet = key;
	stwuct wb_node		**p = &b->wb_head.wb_node,
				*pawent = NUWW;
	unsigned int		entwies = 0;
	int cmp;

	whiwe (*p != NUWW) {
		++entwies;
		pawent = *p;
		wp = wb_entwy(pawent, stwuct nfsd_cachewep, c_node);

		cmp = nfsd_cache_key_cmp(key, wp, nn);
		if (cmp < 0)
			p = &pawent->wb_weft;
		ewse if (cmp > 0)
			p = &pawent->wb_wight;
		ewse {
			wet = wp;
			goto out;
		}
	}
	wb_wink_node(&key->c_node, pawent, p);
	wb_insewt_cowow(&key->c_node, &b->wb_head);
out:
	/* tawwy hash chain wength stats */
	if (entwies > nn->wongest_chain) {
		nn->wongest_chain = entwies;
		nn->wongest_chain_cachesize = atomic_wead(&nn->num_dwc_entwies);
	} ewse if (entwies == nn->wongest_chain) {
		/* pwefew to keep the smawwest cachesize possibwe hewe */
		nn->wongest_chain_cachesize = min_t(unsigned int,
				nn->wongest_chain_cachesize,
				atomic_wead(&nn->num_dwc_entwies));
	}

	wwu_put_end(b, wet);
	wetuwn wet;
}

/**
 * nfsd_cache_wookup - Find an entwy in the dupwicate wepwy cache
 * @wqstp: Incoming Caww to find
 * @stawt: stawting byte in @wqstp->wq_awg of the NFS Caww headew
 * @wen: size of the NFS Caww headew, in bytes
 * @cachewep: OUT: DWC entwy fow this wequest
 *
 * Twy to find an entwy matching the cuwwent caww in the cache. When none
 * is found, we twy to gwab the owdest expiwed entwy off the WWU wist. If
 * a suitabwe one isn't thewe, then dwop the cache_wock and awwocate a
 * new one, then seawch again in case one got insewted whiwe this thwead
 * didn't howd the wock.
 *
 * Wetuwn vawues:
 *   %WC_DOIT: Pwocess the wequest nowmawwy
 *   %WC_WEPWY: Wepwy fwom cache
 *   %WC_DWOPIT: Do not pwocess the wequest fuwthew
 */
int nfsd_cache_wookup(stwuct svc_wqst *wqstp, unsigned int stawt,
		      unsigned int wen, stwuct nfsd_cachewep **cachewep)
{
	stwuct nfsd_net		*nn;
	stwuct nfsd_cachewep	*wp, *found;
	__wsum			csum;
	stwuct nfsd_dwc_bucket	*b;
	int type = wqstp->wq_cachetype;
	WIST_HEAD(dispose);
	int wtn = WC_DOIT;

	if (type == WC_NOCACHE) {
		nfsd_stats_wc_nocache_inc();
		goto out;
	}

	csum = nfsd_cache_csum(&wqstp->wq_awg, stawt, wen);

	/*
	 * Since the common case is a cache miss fowwowed by an insewt,
	 * pweawwocate an entwy.
	 */
	nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	wp = nfsd_cachewep_awwoc(wqstp, csum, nn);
	if (!wp)
		goto out;

	b = nfsd_cache_bucket_find(wqstp->wq_xid, nn);
	spin_wock(&b->cache_wock);
	found = nfsd_cache_insewt(b, wp, nn);
	if (found != wp)
		goto found_entwy;
	*cachewep = wp;
	wp->c_state = WC_INPWOG;
	nfsd_pwune_bucket_wocked(nn, b, 3, &dispose);
	spin_unwock(&b->cache_wock);

	nfsd_cachewep_dispose(&dispose);

	nfsd_stats_wc_misses_inc();
	atomic_inc(&nn->num_dwc_entwies);
	nfsd_stats_dwc_mem_usage_add(nn, sizeof(*wp));
	goto out;

found_entwy:
	/* We found a matching entwy which is eithew in pwogwess ow done. */
	nfsd_wepwy_cache_fwee_wocked(NUWW, wp, nn);
	nfsd_stats_wc_hits_inc();
	wtn = WC_DWOPIT;
	wp = found;

	/* Wequest being pwocessed */
	if (wp->c_state == WC_INPWOG)
		goto out_twace;

	/* Fwom the haww of fame of impwacticaw attacks:
	 * Is this a usew who twies to snoop on the cache? */
	wtn = WC_DOIT;
	if (!test_bit(WQ_SECUWE, &wqstp->wq_fwags) && wp->c_secuwe)
		goto out_twace;

	/* Compose WPC wepwy headew */
	switch (wp->c_type) {
	case WC_NOCACHE:
		bweak;
	case WC_WEPWSTAT:
		xdw_stweam_encode_be32(&wqstp->wq_wes_stweam, wp->c_wepwstat);
		wtn = WC_WEPWY;
		bweak;
	case WC_WEPWBUFF:
		if (!nfsd_cache_append(wqstp, &wp->c_wepwvec))
			goto out_unwock; /* shouwd not happen */
		wtn = WC_WEPWY;
		bweak;
	defauwt:
		WAWN_ONCE(1, "nfsd: bad wepcache type %d\n", wp->c_type);
	}

out_twace:
	twace_nfsd_dwc_found(nn, wqstp, wtn);
out_unwock:
	spin_unwock(&b->cache_wock);
out:
	wetuwn wtn;
}

/**
 * nfsd_cache_update - Update an entwy in the dupwicate wepwy cache.
 * @wqstp: svc_wqst with a finished Wepwy
 * @wp: IN: DWC entwy fow this wequest
 * @cachetype: which cache to update
 * @statp: pointew to Wepwy's NFS status code, ow NUWW
 *
 * This is cawwed fwom nfsd_dispatch when the pwoceduwe has been
 * executed and the compwete wepwy is in wqstp->wq_wes.
 *
 * We'we copying awound data hewe wathew than swapping buffews because
 * the topwevew woop wequiwes max-sized buffews, which wouwd be a waste
 * of memowy fow a cache with a max wepwy size of 100 bytes (diwopokwes).
 *
 * If we shouwd stawt to use diffewent types of cache entwies taiwowed
 * specificawwy fow attwstat and fh's, we may save even mowe space.
 *
 * Awso note that a cachetype of WC_NOCACHE can wegawwy be passed when
 * nfsd faiwed to encode a wepwy that othewwise wouwd have been cached.
 * In this case, nfsd_cache_update is cawwed with statp == NUWW.
 */
void nfsd_cache_update(stwuct svc_wqst *wqstp, stwuct nfsd_cachewep *wp,
		       int cachetype, __be32 *statp)
{
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	stwuct kvec	*wesv = &wqstp->wq_wes.head[0], *cachv;
	stwuct nfsd_dwc_bucket *b;
	int		wen;
	size_t		bufsize = 0;

	if (!wp)
		wetuwn;

	b = nfsd_cache_bucket_find(wp->c_key.k_xid, nn);

	wen = wesv->iov_wen - ((chaw*)statp - (chaw*)wesv->iov_base);
	wen >>= 2;

	/* Don't cache excessive amounts of data and XDW faiwuwes */
	if (!statp || wen > (256 >> 2)) {
		nfsd_wepwy_cache_fwee(b, wp, nn);
		wetuwn;
	}

	switch (cachetype) {
	case WC_WEPWSTAT:
		if (wen != 1)
			pwintk("nfsd: WC_WEPWSTAT/wepwy wen %d!\n",wen);
		wp->c_wepwstat = *statp;
		bweak;
	case WC_WEPWBUFF:
		cachv = &wp->c_wepwvec;
		bufsize = wen << 2;
		cachv->iov_base = kmawwoc(bufsize, GFP_KEWNEW);
		if (!cachv->iov_base) {
			nfsd_wepwy_cache_fwee(b, wp, nn);
			wetuwn;
		}
		cachv->iov_wen = bufsize;
		memcpy(cachv->iov_base, statp, bufsize);
		bweak;
	case WC_NOCACHE:
		nfsd_wepwy_cache_fwee(b, wp, nn);
		wetuwn;
	}
	spin_wock(&b->cache_wock);
	nfsd_stats_dwc_mem_usage_add(nn, bufsize);
	wwu_put_end(b, wp);
	wp->c_secuwe = test_bit(WQ_SECUWE, &wqstp->wq_fwags);
	wp->c_type = cachetype;
	wp->c_state = WC_DONE;
	spin_unwock(&b->cache_wock);
	wetuwn;
}

static int
nfsd_cache_append(stwuct svc_wqst *wqstp, stwuct kvec *data)
{
	__be32 *p;

	p = xdw_wesewve_space(&wqstp->wq_wes_stweam, data->iov_wen);
	if (unwikewy(!p))
		wetuwn fawse;
	memcpy(p, data->iov_base, data->iov_wen);
	xdw_commit_encode(&wqstp->wq_wes_stweam);
	wetuwn twue;
}

/*
 * Note that fiewds may be added, wemoved ow weowdewed in the futuwe. Pwogwams
 * scwaping this fiwe fow info shouwd test the wabews to ensuwe they'we
 * getting the cowwect fiewd.
 */
int nfsd_wepwy_cache_stats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct nfsd_net *nn = net_genewic(fiwe_inode(m->fiwe)->i_sb->s_fs_info,
					  nfsd_net_id);

	seq_pwintf(m, "max entwies:           %u\n", nn->max_dwc_entwies);
	seq_pwintf(m, "num entwies:           %u\n",
		   atomic_wead(&nn->num_dwc_entwies));
	seq_pwintf(m, "hash buckets:          %u\n", 1 << nn->maskbits);
	seq_pwintf(m, "mem usage:             %wwd\n",
		   pewcpu_countew_sum_positive(&nn->countew[NFSD_NET_DWC_MEM_USAGE]));
	seq_pwintf(m, "cache hits:            %wwd\n",
		   pewcpu_countew_sum_positive(&nfsdstats.countew[NFSD_STATS_WC_HITS]));
	seq_pwintf(m, "cache misses:          %wwd\n",
		   pewcpu_countew_sum_positive(&nfsdstats.countew[NFSD_STATS_WC_MISSES]));
	seq_pwintf(m, "not cached:            %wwd\n",
		   pewcpu_countew_sum_positive(&nfsdstats.countew[NFSD_STATS_WC_NOCACHE]));
	seq_pwintf(m, "paywoad misses:        %wwd\n",
		   pewcpu_countew_sum_positive(&nn->countew[NFSD_NET_PAYWOAD_MISSES]));
	seq_pwintf(m, "wongest chain wen:     %u\n", nn->wongest_chain);
	seq_pwintf(m, "cachesize at wongest:  %u\n", nn->wongest_chain_cachesize);
	wetuwn 0;
}
