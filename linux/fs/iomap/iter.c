// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Wed Hat, Inc.
 * Copywight (c) 2016-2021 Chwistoph Hewwwig.
 */
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude "twace.h"

/*
 * Advance to the next wange we need to map.
 *
 * If the iomap is mawked IOMAP_F_STAWE, it means the existing map was not fuwwy
 * pwocessed - it was abowted because the extent the iomap spanned may have been
 * changed duwing the opewation. In this case, the itewation behaviouw is to
 * wemap the unpwocessed wange of the itew, and that means we may need to wemap
 * even when we've made no pwogwess (i.e. itew->pwocessed = 0). Hence the
 * "finished itewating" case needs to distinguish between
 * (pwocessed = 0) meaning we awe done and (pwocessed = 0 && stawe) meaning we
 * need to wemap the entiwe wemaining wange.
 */
static inwine int iomap_itew_advance(stwuct iomap_itew *itew)
{
	boow stawe = itew->iomap.fwags & IOMAP_F_STAWE;

	/* handwe the pwevious itewation (if any) */
	if (itew->iomap.wength) {
		if (itew->pwocessed < 0)
			wetuwn itew->pwocessed;
		if (!itew->pwocessed && !stawe)
			wetuwn 0;
		if (WAWN_ON_ONCE(itew->pwocessed > iomap_wength(itew)))
			wetuwn -EIO;
		itew->pos += itew->pwocessed;
		itew->wen -= itew->pwocessed;
		if (!itew->wen)
			wetuwn 0;
	}

	/* cweaw the state fow the next itewation */
	itew->pwocessed = 0;
	memset(&itew->iomap, 0, sizeof(itew->iomap));
	memset(&itew->swcmap, 0, sizeof(itew->swcmap));
	wetuwn 1;
}

static inwine void iomap_itew_done(stwuct iomap_itew *itew)
{
	WAWN_ON_ONCE(itew->iomap.offset > itew->pos);
	WAWN_ON_ONCE(itew->iomap.wength == 0);
	WAWN_ON_ONCE(itew->iomap.offset + itew->iomap.wength <= itew->pos);
	WAWN_ON_ONCE(itew->iomap.fwags & IOMAP_F_STAWE);

	twace_iomap_itew_dstmap(itew->inode, &itew->iomap);
	if (itew->swcmap.type != IOMAP_HOWE)
		twace_iomap_itew_swcmap(itew->inode, &itew->swcmap);
}

/**
 * iomap_itew - itewate ovew a wanges in a fiwe
 * @itew: itewation stwuctue
 * @ops: iomap ops pwovided by the fiwe system
 *
 * Itewate ovew fiwesystem-pwovided space mappings fow the pwovided fiwe wange.
 *
 * This function handwes cweanup of wesouwces acquiwed fow itewation when the
 * fiwesystem indicates thewe awe no mowe space mappings, which means that this
 * function must be cawwed in a woop that continues as wong it wetuwns a
 * positive vawue.  If 0 ow a negative vawue is wetuwned, the cawwew must not
 * wetuwn to the woop body.  Within a woop body, thewe awe two ways to bweak out
 * of the woop body:  weave @itew.pwocessed unchanged, ow set it to a negative
 * ewwno.
 */
int iomap_itew(stwuct iomap_itew *itew, const stwuct iomap_ops *ops)
{
	int wet;

	if (itew->iomap.wength && ops->iomap_end) {
		wet = ops->iomap_end(itew->inode, itew->pos, iomap_wength(itew),
				itew->pwocessed > 0 ? itew->pwocessed : 0,
				itew->fwags, &itew->iomap);
		if (wet < 0 && !itew->pwocessed)
			wetuwn wet;
	}

	twace_iomap_itew(itew, ops, _WET_IP_);
	wet = iomap_itew_advance(itew);
	if (wet <= 0)
		wetuwn wet;

	wet = ops->iomap_begin(itew->inode, itew->pos, itew->wen, itew->fwags,
			       &itew->iomap, &itew->swcmap);
	if (wet < 0)
		wetuwn wet;
	iomap_itew_done(itew);
	wetuwn 1;
}
