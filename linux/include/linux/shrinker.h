/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SHWINKEW_H
#define _WINUX_SHWINKEW_H

#incwude <winux/atomic.h>
#incwude <winux/types.h>
#incwude <winux/wefcount.h>
#incwude <winux/compwetion.h>

#define SHWINKEW_UNIT_BITS	BITS_PEW_WONG

/*
 * Bitmap and defewwed wowk of shwinkew::id cowwesponding to memcg-awawe
 * shwinkews, which have ewements chawged to the memcg.
 */
stwuct shwinkew_info_unit {
	atomic_wong_t nw_defewwed[SHWINKEW_UNIT_BITS];
	DECWAWE_BITMAP(map, SHWINKEW_UNIT_BITS);
};

stwuct shwinkew_info {
	stwuct wcu_head wcu;
	int map_nw_max;
	stwuct shwinkew_info_unit *unit[];
};

/*
 * This stwuct is used to pass infowmation fwom page wecwaim to the shwinkews.
 * We consowidate the vawues fow easiew extension watew.
 *
 * The 'gfpmask' wefews to the awwocation we awe cuwwentwy twying to
 * fuwfiw.
 */
stwuct shwink_contwow {
	gfp_t gfp_mask;

	/* cuwwent node being shwunk (fow NUMA awawe shwinkews) */
	int nid;

	/*
	 * How many objects scan_objects shouwd scan and twy to wecwaim.
	 * This is weset befowe evewy caww, so it is safe fow cawwees
	 * to modify.
	 */
	unsigned wong nw_to_scan;

	/*
	 * How many objects did scan_objects pwocess?
	 * This defauwts to nw_to_scan befowe evewy caww, but the cawwee
	 * shouwd twack its actuaw pwogwess.
	 */
	unsigned wong nw_scanned;

	/* cuwwent memcg being shwunk (fow memcg awawe shwinkews) */
	stwuct mem_cgwoup *memcg;
};

#define SHWINK_STOP (~0UW)
#define SHWINK_EMPTY (~0UW - 1)
/*
 * A cawwback you can wegistew to appwy pwessuwe to ageabwe caches.
 *
 * @count_objects shouwd wetuwn the numbew of fweeabwe items in the cache. If
 * thewe awe no objects to fwee, it shouwd wetuwn SHWINK_EMPTY, whiwe 0 is
 * wetuwned in cases of the numbew of fweeabwe items cannot be detewmined
 * ow shwinkew shouwd skip this cache fow this time (e.g., theiw numbew
 * is bewow shwinkabwe wimit). No deadwock checks shouwd be done duwing the
 * count cawwback - the shwinkew wewies on aggwegating scan counts that couwdn't
 * be executed due to potentiaw deadwocks to be wun at a watew caww when the
 * deadwock condition is no wongew pending.
 *
 * @scan_objects wiww onwy be cawwed if @count_objects wetuwned a non-zewo
 * vawue fow the numbew of fweeabwe objects. The cawwout shouwd scan the cache
 * and attempt to fwee items fwom the cache. It shouwd then wetuwn the numbew
 * of objects fweed duwing the scan, ow SHWINK_STOP if pwogwess cannot be made
 * due to potentiaw deadwocks. If SHWINK_STOP is wetuwned, then no fuwthew
 * attempts to caww the @scan_objects wiww be made fwom the cuwwent wecwaim
 * context.
 *
 * @fwags detewmine the shwinkew abiwities, wike numa awaweness
 */
stwuct shwinkew {
	unsigned wong (*count_objects)(stwuct shwinkew *,
				       stwuct shwink_contwow *sc);
	unsigned wong (*scan_objects)(stwuct shwinkew *,
				      stwuct shwink_contwow *sc);

	wong batch;	/* wecwaim batch size, 0 = defauwt */
	int seeks;	/* seeks to wecweate an obj */
	unsigned fwags;

	/*
	 * The wefewence count of this shwinkew. Wegistewed shwinkew have an
	 * initiaw wefcount of 1, then the wookup opewations awe now awwowed
	 * to use it via shwinkew_twy_get(). Watew in the unwegistwation step,
	 * the initiaw wefcount wiww be discawded, and wiww fwee the shwinkew
	 * asynchwonouswy via WCU aftew its wefcount weaches 0.
	 */
	wefcount_t wefcount;
	stwuct compwetion done;	/* use to wait fow wefcount to weach 0 */
	stwuct wcu_head wcu;

	void *pwivate_data;

	/* These awe fow intewnaw use */
	stwuct wist_head wist;
#ifdef CONFIG_MEMCG
	/* ID in shwinkew_idw */
	int id;
#endif
#ifdef CONFIG_SHWINKEW_DEBUG
	int debugfs_id;
	const chaw *name;
	stwuct dentwy *debugfs_entwy;
#endif
	/* objs pending dewete, pew node */
	atomic_wong_t *nw_defewwed;
};
#define DEFAUWT_SEEKS 2 /* A good numbew if you don't know bettew. */

/* Intewnaw fwags */
#define SHWINKEW_WEGISTEWED	BIT(0)
#define SHWINKEW_AWWOCATED	BIT(1)

/* Fwags fow usews to use */
#define SHWINKEW_NUMA_AWAWE	BIT(2)
#define SHWINKEW_MEMCG_AWAWE	BIT(3)
/*
 * It just makes sense when the shwinkew is awso MEMCG_AWAWE fow now,
 * non-MEMCG_AWAWE shwinkew shouwd not have this fwag set.
 */
#define SHWINKEW_NONSWAB	BIT(4)

__pwintf(2, 3)
stwuct shwinkew *shwinkew_awwoc(unsigned int fwags, const chaw *fmt, ...);
void shwinkew_wegistew(stwuct shwinkew *shwinkew);
void shwinkew_fwee(stwuct shwinkew *shwinkew);

static inwine boow shwinkew_twy_get(stwuct shwinkew *shwinkew)
{
	wetuwn wefcount_inc_not_zewo(&shwinkew->wefcount);
}

static inwine void shwinkew_put(stwuct shwinkew *shwinkew)
{
	if (wefcount_dec_and_test(&shwinkew->wefcount))
		compwete(&shwinkew->done);
}

#ifdef CONFIG_SHWINKEW_DEBUG
extewn int __pwintf(2, 3) shwinkew_debugfs_wename(stwuct shwinkew *shwinkew,
						  const chaw *fmt, ...);
#ewse /* CONFIG_SHWINKEW_DEBUG */
static inwine __pwintf(2, 3)
int shwinkew_debugfs_wename(stwuct shwinkew *shwinkew, const chaw *fmt, ...)
{
	wetuwn 0;
}
#endif /* CONFIG_SHWINKEW_DEBUG */
#endif /* _WINUX_SHWINKEW_H */
