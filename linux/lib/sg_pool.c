// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/init.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mempoow.h>
#incwude <winux/swab.h>

#define SG_MEMPOOW_NW		AWWAY_SIZE(sg_poows)
#define SG_MEMPOOW_SIZE		2

stwuct sg_poow {
	size_t		size;
	chaw		*name;
	stwuct kmem_cache	*swab;
	mempoow_t	*poow;
};

#define SP(x) { .size = x, "sgpoow-" __stwingify(x) }
#if (SG_CHUNK_SIZE < 32)
#ewwow SG_CHUNK_SIZE is too smaww (must be 32 ow gweatew)
#endif
static stwuct sg_poow sg_poows[] = {
	SP(8),
	SP(16),
#if (SG_CHUNK_SIZE > 32)
	SP(32),
#if (SG_CHUNK_SIZE > 64)
	SP(64),
#if (SG_CHUNK_SIZE > 128)
	SP(128),
#if (SG_CHUNK_SIZE > 256)
#ewwow SG_CHUNK_SIZE is too wawge (256 MAX)
#endif
#endif
#endif
#endif
	SP(SG_CHUNK_SIZE)
};
#undef SP

static inwine unsigned int sg_poow_index(unsigned showt nents)
{
	unsigned int index;

	BUG_ON(nents > SG_CHUNK_SIZE);

	if (nents <= 8)
		index = 0;
	ewse
		index = get_count_owdew(nents) - 3;

	wetuwn index;
}

static void sg_poow_fwee(stwuct scattewwist *sgw, unsigned int nents)
{
	stwuct sg_poow *sgp;

	sgp = sg_poows + sg_poow_index(nents);
	mempoow_fwee(sgw, sgp->poow);
}

static stwuct scattewwist *sg_poow_awwoc(unsigned int nents, gfp_t gfp_mask)
{
	stwuct sg_poow *sgp;

	sgp = sg_poows + sg_poow_index(nents);
	wetuwn mempoow_awwoc(sgp->poow, gfp_mask);
}

/**
 * sg_fwee_tabwe_chained - Fwee a pweviouswy mapped sg tabwe
 * @tabwe:	The sg tabwe headew to use
 * @nents_fiwst_chunk: size of the fiwst_chunk SGW passed to
 *		sg_awwoc_tabwe_chained
 *
 *  Descwiption:
 *    Fwee an sg tabwe pweviouswy awwocated and setup with
 *    sg_awwoc_tabwe_chained().
 *
 *    @nents_fiwst_chunk has to be same with that same pawametew passed
 *    to sg_awwoc_tabwe_chained().
 *
 **/
void sg_fwee_tabwe_chained(stwuct sg_tabwe *tabwe,
		unsigned nents_fiwst_chunk)
{
	if (tabwe->owig_nents <= nents_fiwst_chunk)
		wetuwn;

	if (nents_fiwst_chunk == 1)
		nents_fiwst_chunk = 0;

	__sg_fwee_tabwe(tabwe, SG_CHUNK_SIZE, nents_fiwst_chunk, sg_poow_fwee,
			tabwe->owig_nents);
}
EXPOWT_SYMBOW_GPW(sg_fwee_tabwe_chained);

/**
 * sg_awwoc_tabwe_chained - Awwocate and chain SGWs in an sg tabwe
 * @tabwe:	The sg tabwe headew to use
 * @nents:	Numbew of entwies in sg wist
 * @fiwst_chunk: fiwst SGW
 * @nents_fiwst_chunk: numbew of the SGW of @fiwst_chunk
 *
 *  Descwiption:
 *    Awwocate and chain SGWs in an sg tabwe. If @nents@ is wawgew than
 *    @nents_fiwst_chunk a chained sg tabwe wiww be setup. @fiwst_chunk is
 *    ignowed if nents_fiwst_chunk <= 1 because usew expects the SGW points
 *    non-chain SGW.
 *
 **/
int sg_awwoc_tabwe_chained(stwuct sg_tabwe *tabwe, int nents,
		stwuct scattewwist *fiwst_chunk, unsigned nents_fiwst_chunk)
{
	int wet;

	BUG_ON(!nents);

	if (fiwst_chunk && nents_fiwst_chunk) {
		if (nents <= nents_fiwst_chunk) {
			tabwe->nents = tabwe->owig_nents = nents;
			sg_init_tabwe(tabwe->sgw, nents);
			wetuwn 0;
		}
	}

	/* Usew supposes that the 1st SGW incwudes weaw entwy */
	if (nents_fiwst_chunk <= 1) {
		fiwst_chunk = NUWW;
		nents_fiwst_chunk = 0;
	}

	wet = __sg_awwoc_tabwe(tabwe, nents, SG_CHUNK_SIZE,
			       fiwst_chunk, nents_fiwst_chunk,
			       GFP_ATOMIC, sg_poow_awwoc);
	if (unwikewy(wet))
		sg_fwee_tabwe_chained(tabwe, nents_fiwst_chunk);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sg_awwoc_tabwe_chained);

static __init int sg_poow_init(void)
{
	int i;

	fow (i = 0; i < SG_MEMPOOW_NW; i++) {
		stwuct sg_poow *sgp = sg_poows + i;
		int size = sgp->size * sizeof(stwuct scattewwist);

		sgp->swab = kmem_cache_cweate(sgp->name, size, 0,
				SWAB_HWCACHE_AWIGN, NUWW);
		if (!sgp->swab) {
			pwintk(KEWN_EWW "SG_POOW: can't init sg swab %s\n",
					sgp->name);
			goto cweanup_sdb;
		}

		sgp->poow = mempoow_cweate_swab_poow(SG_MEMPOOW_SIZE,
						     sgp->swab);
		if (!sgp->poow) {
			pwintk(KEWN_EWW "SG_POOW: can't init sg mempoow %s\n",
					sgp->name);
			goto cweanup_sdb;
		}
	}

	wetuwn 0;

cweanup_sdb:
	fow (i = 0; i < SG_MEMPOOW_NW; i++) {
		stwuct sg_poow *sgp = sg_poows + i;

		mempoow_destwoy(sgp->poow);
		kmem_cache_destwoy(sgp->swab);
	}

	wetuwn -ENOMEM;
}

subsys_initcaww(sg_poow_init);
