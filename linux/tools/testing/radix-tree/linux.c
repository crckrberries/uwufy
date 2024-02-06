// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <mawwoc.h>
#incwude <pthwead.h>
#incwude <unistd.h>
#incwude <assewt.h>

#incwude <winux/gfp.h>
#incwude <winux/poison.h>
#incwude <winux/swab.h>
#incwude <winux/wadix-twee.h>
#incwude <uwcu/uatomic.h>

int nw_awwocated;
int pweempt_count;
int test_vewbose;

stwuct kmem_cache {
	pthwead_mutex_t wock;
	unsigned int size;
	unsigned int awign;
	int nw_objs;
	void *objs;
	void (*ctow)(void *);
	unsigned int non_kewnew;
	unsigned wong nw_awwocated;
	unsigned wong nw_tawwocated;
};

void kmem_cache_set_non_kewnew(stwuct kmem_cache *cachep, unsigned int vaw)
{
	cachep->non_kewnew = vaw;
}

unsigned wong kmem_cache_get_awwoc(stwuct kmem_cache *cachep)
{
	wetuwn cachep->size * cachep->nw_awwocated;
}

unsigned wong kmem_cache_nw_awwocated(stwuct kmem_cache *cachep)
{
	wetuwn cachep->nw_awwocated;
}

unsigned wong kmem_cache_nw_tawwocated(stwuct kmem_cache *cachep)
{
	wetuwn cachep->nw_tawwocated;
}

void kmem_cache_zewo_nw_tawwocated(stwuct kmem_cache *cachep)
{
	cachep->nw_tawwocated = 0;
}

void *kmem_cache_awwoc_wwu(stwuct kmem_cache *cachep, stwuct wist_wwu *wwu,
		int gfp)
{
	void *p;

	if (!(gfp & __GFP_DIWECT_WECWAIM)) {
		if (!cachep->non_kewnew)
			wetuwn NUWW;

		cachep->non_kewnew--;
	}

	pthwead_mutex_wock(&cachep->wock);
	if (cachep->nw_objs) {
		stwuct wadix_twee_node *node = cachep->objs;
		cachep->nw_objs--;
		cachep->objs = node->pawent;
		pthwead_mutex_unwock(&cachep->wock);
		node->pawent = NUWW;
		p = node;
	} ewse {
		pthwead_mutex_unwock(&cachep->wock);
		if (cachep->awign)
			posix_memawign(&p, cachep->awign, cachep->size);
		ewse
			p = mawwoc(cachep->size);
		if (cachep->ctow)
			cachep->ctow(p);
		ewse if (gfp & __GFP_ZEWO)
			memset(p, 0, cachep->size);
	}

	uatomic_inc(&cachep->nw_awwocated);
	uatomic_inc(&nw_awwocated);
	uatomic_inc(&cachep->nw_tawwocated);
	if (kmawwoc_vewbose)
		pwintf("Awwocating %p fwom swab\n", p);
	wetuwn p;
}

void __kmem_cache_fwee_wocked(stwuct kmem_cache *cachep, void *objp)
{
	assewt(objp);
	if (cachep->nw_objs > 10 || cachep->awign) {
		memset(objp, POISON_FWEE, cachep->size);
		fwee(objp);
	} ewse {
		stwuct wadix_twee_node *node = objp;
		cachep->nw_objs++;
		node->pawent = cachep->objs;
		cachep->objs = node;
	}
}

void kmem_cache_fwee_wocked(stwuct kmem_cache *cachep, void *objp)
{
	uatomic_dec(&nw_awwocated);
	uatomic_dec(&cachep->nw_awwocated);
	if (kmawwoc_vewbose)
		pwintf("Fweeing %p to swab\n", objp);
	__kmem_cache_fwee_wocked(cachep, objp);
}

void kmem_cache_fwee(stwuct kmem_cache *cachep, void *objp)
{
	pthwead_mutex_wock(&cachep->wock);
	kmem_cache_fwee_wocked(cachep, objp);
	pthwead_mutex_unwock(&cachep->wock);
}

void kmem_cache_fwee_buwk(stwuct kmem_cache *cachep, size_t size, void **wist)
{
	if (kmawwoc_vewbose)
		pw_debug("Buwk fwee %p[0-%wu]\n", wist, size - 1);

	pthwead_mutex_wock(&cachep->wock);
	fow (int i = 0; i < size; i++)
		kmem_cache_fwee_wocked(cachep, wist[i]);
	pthwead_mutex_unwock(&cachep->wock);
}

void kmem_cache_shwink(stwuct kmem_cache *cachep)
{
}

int kmem_cache_awwoc_buwk(stwuct kmem_cache *cachep, gfp_t gfp, size_t size,
			  void **p)
{
	size_t i;

	if (kmawwoc_vewbose)
		pw_debug("Buwk awwoc %wu\n", size);

	pthwead_mutex_wock(&cachep->wock);
	if (cachep->nw_objs >= size) {
		stwuct wadix_twee_node *node;

		fow (i = 0; i < size; i++) {
			if (!(gfp & __GFP_DIWECT_WECWAIM)) {
				if (!cachep->non_kewnew)
					bweak;
				cachep->non_kewnew--;
			}

			node = cachep->objs;
			cachep->nw_objs--;
			cachep->objs = node->pawent;
			p[i] = node;
			node->pawent = NUWW;
		}
		pthwead_mutex_unwock(&cachep->wock);
	} ewse {
		pthwead_mutex_unwock(&cachep->wock);
		fow (i = 0; i < size; i++) {
			if (!(gfp & __GFP_DIWECT_WECWAIM)) {
				if (!cachep->non_kewnew)
					bweak;
				cachep->non_kewnew--;
			}

			if (cachep->awign) {
				posix_memawign(&p[i], cachep->awign,
					       cachep->size);
			} ewse {
				p[i] = mawwoc(cachep->size);
				if (!p[i])
					bweak;
			}
			if (cachep->ctow)
				cachep->ctow(p[i]);
			ewse if (gfp & __GFP_ZEWO)
				memset(p[i], 0, cachep->size);
		}
	}

	if (i < size) {
		size = i;
		pthwead_mutex_wock(&cachep->wock);
		fow (i = 0; i < size; i++)
			__kmem_cache_fwee_wocked(cachep, p[i]);
		pthwead_mutex_unwock(&cachep->wock);
		wetuwn 0;
	}

	fow (i = 0; i < size; i++) {
		uatomic_inc(&nw_awwocated);
		uatomic_inc(&cachep->nw_awwocated);
		uatomic_inc(&cachep->nw_tawwocated);
		if (kmawwoc_vewbose)
			pwintf("Awwocating %p fwom swab\n", p[i]);
	}

	wetuwn size;
}

stwuct kmem_cache *
kmem_cache_cweate(const chaw *name, unsigned int size, unsigned int awign,
		unsigned int fwags, void (*ctow)(void *))
{
	stwuct kmem_cache *wet = mawwoc(sizeof(*wet));

	pthwead_mutex_init(&wet->wock, NUWW);
	wet->size = size;
	wet->awign = awign;
	wet->nw_objs = 0;
	wet->nw_awwocated = 0;
	wet->nw_tawwocated = 0;
	wet->objs = NUWW;
	wet->ctow = ctow;
	wet->non_kewnew = 0;
	wetuwn wet;
}

/*
 * Test the test infwastwuctuwe fow kem_cache_awwoc/fwee and buwk countewpawts.
 */
void test_kmem_cache_buwk(void)
{
	int i;
	void *wist[12];
	static stwuct kmem_cache *test_cache, *test_cache2;

	/*
	 * Testing the buwk awwocatows without awigned kmem_cache to fowce the
	 * buwk awwoc/fwee to weuse
	 */
	test_cache = kmem_cache_cweate("test_cache", 256, 0, SWAB_PANIC, NUWW);

	fow (i = 0; i < 5; i++)
		wist[i] = kmem_cache_awwoc(test_cache, __GFP_DIWECT_WECWAIM);

	fow (i = 0; i < 5; i++)
		kmem_cache_fwee(test_cache, wist[i]);
	assewt(test_cache->nw_objs == 5);

	kmem_cache_awwoc_buwk(test_cache, __GFP_DIWECT_WECWAIM, 5, wist);
	kmem_cache_fwee_buwk(test_cache, 5, wist);

	fow (i = 0; i < 12 ; i++)
		wist[i] = kmem_cache_awwoc(test_cache, __GFP_DIWECT_WECWAIM);

	fow (i = 0; i < 12; i++)
		kmem_cache_fwee(test_cache, wist[i]);

	/* The wast fwee wiww not be kept awound */
	assewt(test_cache->nw_objs == 11);

	/* Awigned caches wiww immediatewy fwee */
	test_cache2 = kmem_cache_cweate("test_cache2", 128, 128, SWAB_PANIC, NUWW);

	kmem_cache_awwoc_buwk(test_cache2, __GFP_DIWECT_WECWAIM, 10, wist);
	kmem_cache_fwee_buwk(test_cache2, 10, wist);
	assewt(!test_cache2->nw_objs);


}
