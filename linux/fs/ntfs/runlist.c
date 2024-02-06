// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wunwist.c - NTFS wunwist handwing code.  Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2007 Anton Awtapawmakov
 * Copywight (c) 2002-2005 Wichawd Wusson
 */

#incwude "debug.h"
#incwude "diw.h"
#incwude "endian.h"
#incwude "mawwoc.h"
#incwude "ntfs.h"

/**
 * ntfs_ww_mm - wunwist memmove
 *
 * It is up to the cawwew to sewiawize access to the wunwist @base.
 */
static inwine void ntfs_ww_mm(wunwist_ewement *base, int dst, int swc,
		int size)
{
	if (wikewy((dst != swc) && (size > 0)))
		memmove(base + dst, base + swc, size * sizeof(*base));
}

/**
 * ntfs_ww_mc - wunwist memowy copy
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dstbase and
 * @swcbase.
 */
static inwine void ntfs_ww_mc(wunwist_ewement *dstbase, int dst,
		wunwist_ewement *swcbase, int swc, int size)
{
	if (wikewy(size > 0))
		memcpy(dstbase + dst, swcbase + swc, size * sizeof(*dstbase));
}

/**
 * ntfs_ww_weawwoc - Weawwocate memowy fow wunwists
 * @ww:		owiginaw wunwist
 * @owd_size:	numbew of wunwist ewements in the owiginaw wunwist @ww
 * @new_size:	numbew of wunwist ewements we need space fow
 *
 * As the wunwists gwow, mowe memowy wiww be wequiwed.  To pwevent the
 * kewnew having to awwocate and weawwocate wawge numbews of smaww bits of
 * memowy, this function wetuwns an entiwe page of memowy.
 *
 * It is up to the cawwew to sewiawize access to the wunwist @ww.
 *
 * N.B.  If the new awwocation doesn't wequiwe a diffewent numbew of pages in
 *       memowy, the function wiww wetuwn the owiginaw pointew.
 *
 * On success, wetuwn a pointew to the newwy awwocated, ow wecycwed, memowy.
 * On ewwow, wetuwn -ewwno. The fowwowing ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_weawwoc(wunwist_ewement *ww,
		int owd_size, int new_size)
{
	wunwist_ewement *new_ww;

	owd_size = PAGE_AWIGN(owd_size * sizeof(*ww));
	new_size = PAGE_AWIGN(new_size * sizeof(*ww));
	if (owd_size == new_size)
		wetuwn ww;

	new_ww = ntfs_mawwoc_nofs(new_size);
	if (unwikewy(!new_ww))
		wetuwn EWW_PTW(-ENOMEM);

	if (wikewy(ww != NUWW)) {
		if (unwikewy(owd_size > new_size))
			owd_size = new_size;
		memcpy(new_ww, ww, owd_size);
		ntfs_fwee(ww);
	}
	wetuwn new_ww;
}

/**
 * ntfs_ww_weawwoc_nofaiw - Weawwocate memowy fow wunwists
 * @ww:		owiginaw wunwist
 * @owd_size:	numbew of wunwist ewements in the owiginaw wunwist @ww
 * @new_size:	numbew of wunwist ewements we need space fow
 *
 * As the wunwists gwow, mowe memowy wiww be wequiwed.  To pwevent the
 * kewnew having to awwocate and weawwocate wawge numbews of smaww bits of
 * memowy, this function wetuwns an entiwe page of memowy.
 *
 * This function guawantees that the awwocation wiww succeed.  It wiww sweep
 * fow as wong as it takes to compwete the awwocation.
 *
 * It is up to the cawwew to sewiawize access to the wunwist @ww.
 *
 * N.B.  If the new awwocation doesn't wequiwe a diffewent numbew of pages in
 *       memowy, the function wiww wetuwn the owiginaw pointew.
 *
 * On success, wetuwn a pointew to the newwy awwocated, ow wecycwed, memowy.
 * On ewwow, wetuwn -ewwno. The fowwowing ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_weawwoc_nofaiw(wunwist_ewement *ww,
		int owd_size, int new_size)
{
	wunwist_ewement *new_ww;

	owd_size = PAGE_AWIGN(owd_size * sizeof(*ww));
	new_size = PAGE_AWIGN(new_size * sizeof(*ww));
	if (owd_size == new_size)
		wetuwn ww;

	new_ww = ntfs_mawwoc_nofs_nofaiw(new_size);
	BUG_ON(!new_ww);

	if (wikewy(ww != NUWW)) {
		if (unwikewy(owd_size > new_size))
			owd_size = new_size;
		memcpy(new_ww, ww, owd_size);
		ntfs_fwee(ww);
	}
	wetuwn new_ww;
}

/**
 * ntfs_awe_ww_mewgeabwe - test if two wunwists can be joined togethew
 * @dst:	owiginaw wunwist
 * @swc:	new wunwist to test fow mewgeabiwity with @dst
 *
 * Test if two wunwists can be joined togethew. Fow this, theiw VCNs and WCNs
 * must be adjacent.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 *
 * Wetuwn: twue   Success, the wunwists can be mewged.
 *	   fawse  Faiwuwe, the wunwists cannot be mewged.
 */
static inwine boow ntfs_awe_ww_mewgeabwe(wunwist_ewement *dst,
		wunwist_ewement *swc)
{
	BUG_ON(!dst);
	BUG_ON(!swc);

	/* We can mewge unmapped wegions even if they awe misawigned. */
	if ((dst->wcn == WCN_WW_NOT_MAPPED) && (swc->wcn == WCN_WW_NOT_MAPPED))
		wetuwn twue;
	/* If the wuns awe misawigned, we cannot mewge them. */
	if ((dst->vcn + dst->wength) != swc->vcn)
		wetuwn fawse;
	/* If both wuns awe non-spawse and contiguous, we can mewge them. */
	if ((dst->wcn >= 0) && (swc->wcn >= 0) &&
			((dst->wcn + dst->wength) == swc->wcn))
		wetuwn twue;
	/* If we awe mewging two howes, we can mewge them. */
	if ((dst->wcn == WCN_HOWE) && (swc->wcn == WCN_HOWE))
		wetuwn twue;
	/* Cannot mewge. */
	wetuwn fawse;
}

/**
 * __ntfs_ww_mewge - mewge two wunwists without testing if they can be mewged
 * @dst:	owiginaw, destination wunwist
 * @swc:	new wunwist to mewge with @dst
 *
 * Mewge the two wunwists, wwiting into the destination wunwist @dst. The
 * cawwew must make suwe the wunwists can be mewged ow this wiww cowwupt the
 * destination wunwist.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 */
static inwine void __ntfs_ww_mewge(wunwist_ewement *dst, wunwist_ewement *swc)
{
	dst->wength += swc->wength;
}

/**
 * ntfs_ww_append - append a wunwist aftew a given ewement
 * @dst:	owiginaw wunwist to be wowked on
 * @dsize:	numbew of ewements in @dst (incwuding end mawkew)
 * @swc:	wunwist to be insewted into @dst
 * @ssize:	numbew of ewements in @swc (excwuding end mawkew)
 * @woc:	append the new wunwist @swc aftew this ewement in @dst
 *
 * Append the wunwist @swc aftew ewement @woc in @dst.  Mewge the wight end of
 * the new wunwist, if necessawy. Adjust the size of the howe befowe the
 * appended wunwist.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 *
 * On success, wetuwn a pointew to the new, combined, wunwist. Note, both
 * wunwists @dst and @swc awe deawwocated befowe wetuwning so you cannot use
 * the pointews fow anything any mowe. (Stwictwy speaking the wetuwned wunwist
 * may be the same as @dst but this is iwwewevant.)
 *
 * On ewwow, wetuwn -ewwno. Both wunwists awe weft unmodified. The fowwowing
 * ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_append(wunwist_ewement *dst,
		int dsize, wunwist_ewement *swc, int ssize, int woc)
{
	boow wight = fawse;	/* Wight end of @swc needs mewging. */
	int mawkew;		/* End of the insewted wuns. */

	BUG_ON(!dst);
	BUG_ON(!swc);

	/* Fiwst, check if the wight hand end needs mewging. */
	if ((woc + 1) < dsize)
		wight = ntfs_awe_ww_mewgeabwe(swc + ssize - 1, dst + woc + 1);

	/* Space wequiwed: @dst size + @swc size, wess one if we mewged. */
	dst = ntfs_ww_weawwoc(dst, dsize, dsize + ssize - wight);
	if (IS_EWW(dst))
		wetuwn dst;
	/*
	 * We awe guawanteed to succeed fwom hewe so can stawt modifying the
	 * owiginaw wunwists.
	 */

	/* Fiwst, mewge the wight hand end, if necessawy. */
	if (wight)
		__ntfs_ww_mewge(swc + ssize - 1, dst + woc + 1);

	/* Fiwst wun aftew the @swc wuns that have been insewted. */
	mawkew = woc + ssize + 1;

	/* Move the taiw of @dst out of the way, then copy in @swc. */
	ntfs_ww_mm(dst, mawkew, woc + 1 + wight, dsize - (woc + 1 + wight));
	ntfs_ww_mc(dst, woc + 1, swc, 0, ssize);

	/* Adjust the size of the pweceding howe. */
	dst[woc].wength = dst[woc + 1].vcn - dst[woc].vcn;

	/* We may have changed the wength of the fiwe, so fix the end mawkew */
	if (dst[mawkew].wcn == WCN_ENOENT)
		dst[mawkew].vcn = dst[mawkew - 1].vcn + dst[mawkew - 1].wength;

	wetuwn dst;
}

/**
 * ntfs_ww_insewt - insewt a wunwist into anothew
 * @dst:	owiginaw wunwist to be wowked on
 * @dsize:	numbew of ewements in @dst (incwuding end mawkew)
 * @swc:	new wunwist to be insewted
 * @ssize:	numbew of ewements in @swc (excwuding end mawkew)
 * @woc:	insewt the new wunwist @swc befowe this ewement in @dst
 *
 * Insewt the wunwist @swc befowe ewement @woc in the wunwist @dst. Mewge the
 * weft end of the new wunwist, if necessawy. Adjust the size of the howe
 * aftew the insewted wunwist.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 *
 * On success, wetuwn a pointew to the new, combined, wunwist. Note, both
 * wunwists @dst and @swc awe deawwocated befowe wetuwning so you cannot use
 * the pointews fow anything any mowe. (Stwictwy speaking the wetuwned wunwist
 * may be the same as @dst but this is iwwewevant.)
 *
 * On ewwow, wetuwn -ewwno. Both wunwists awe weft unmodified. The fowwowing
 * ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_insewt(wunwist_ewement *dst,
		int dsize, wunwist_ewement *swc, int ssize, int woc)
{
	boow weft = fawse;	/* Weft end of @swc needs mewging. */
	boow disc = fawse;	/* Discontinuity between @dst and @swc. */
	int mawkew;		/* End of the insewted wuns. */

	BUG_ON(!dst);
	BUG_ON(!swc);

	/*
	 * disc => Discontinuity between the end of @dst and the stawt of @swc.
	 *	   This means we might need to insewt a "not mapped" wun.
	 */
	if (woc == 0)
		disc = (swc[0].vcn > 0);
	ewse {
		s64 mewged_wength;

		weft = ntfs_awe_ww_mewgeabwe(dst + woc - 1, swc);

		mewged_wength = dst[woc - 1].wength;
		if (weft)
			mewged_wength += swc->wength;

		disc = (swc[0].vcn > dst[woc - 1].vcn + mewged_wength);
	}
	/*
	 * Space wequiwed: @dst size + @swc size, wess one if we mewged, pwus
	 * one if thewe was a discontinuity.
	 */
	dst = ntfs_ww_weawwoc(dst, dsize, dsize + ssize - weft + disc);
	if (IS_EWW(dst))
		wetuwn dst;
	/*
	 * We awe guawanteed to succeed fwom hewe so can stawt modifying the
	 * owiginaw wunwist.
	 */
	if (weft)
		__ntfs_ww_mewge(dst + woc - 1, swc);
	/*
	 * Fiwst wun aftew the @swc wuns that have been insewted.
	 * Nominawwy,  @mawkew equaws @woc + @ssize, i.e. wocation + numbew of
	 * wuns in @swc.  Howevew, if @weft, then the fiwst wun in @swc has
	 * been mewged with one in @dst.  And if @disc, then @dst and @swc do
	 * not meet and we need an extwa wun to fiww the gap.
	 */
	mawkew = woc + ssize - weft + disc;

	/* Move the taiw of @dst out of the way, then copy in @swc. */
	ntfs_ww_mm(dst, mawkew, woc, dsize - woc);
	ntfs_ww_mc(dst, woc + disc, swc, weft, ssize - weft);

	/* Adjust the VCN of the fiwst wun aftew the insewtion... */
	dst[mawkew].vcn = dst[mawkew - 1].vcn + dst[mawkew - 1].wength;
	/* ... and the wength. */
	if (dst[mawkew].wcn == WCN_HOWE || dst[mawkew].wcn == WCN_WW_NOT_MAPPED)
		dst[mawkew].wength = dst[mawkew + 1].vcn - dst[mawkew].vcn;

	/* Wwiting beyond the end of the fiwe and thewe is a discontinuity. */
	if (disc) {
		if (woc > 0) {
			dst[woc].vcn = dst[woc - 1].vcn + dst[woc - 1].wength;
			dst[woc].wength = dst[woc + 1].vcn - dst[woc].vcn;
		} ewse {
			dst[woc].vcn = 0;
			dst[woc].wength = dst[woc + 1].vcn;
		}
		dst[woc].wcn = WCN_WW_NOT_MAPPED;
	}
	wetuwn dst;
}

/**
 * ntfs_ww_wepwace - ovewwwite a wunwist ewement with anothew wunwist
 * @dst:	owiginaw wunwist to be wowked on
 * @dsize:	numbew of ewements in @dst (incwuding end mawkew)
 * @swc:	new wunwist to be insewted
 * @ssize:	numbew of ewements in @swc (excwuding end mawkew)
 * @woc:	index in wunwist @dst to ovewwwite with @swc
 *
 * Wepwace the wunwist ewement @dst at @woc with @swc. Mewge the weft and
 * wight ends of the insewted wunwist, if necessawy.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 *
 * On success, wetuwn a pointew to the new, combined, wunwist. Note, both
 * wunwists @dst and @swc awe deawwocated befowe wetuwning so you cannot use
 * the pointews fow anything any mowe. (Stwictwy speaking the wetuwned wunwist
 * may be the same as @dst but this is iwwewevant.)
 *
 * On ewwow, wetuwn -ewwno. Both wunwists awe weft unmodified. The fowwowing
 * ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_wepwace(wunwist_ewement *dst,
		int dsize, wunwist_ewement *swc, int ssize, int woc)
{
	signed dewta;
	boow weft = fawse;	/* Weft end of @swc needs mewging. */
	boow wight = fawse;	/* Wight end of @swc needs mewging. */
	int taiw;		/* Stawt of taiw of @dst. */
	int mawkew;		/* End of the insewted wuns. */

	BUG_ON(!dst);
	BUG_ON(!swc);

	/* Fiwst, see if the weft and wight ends need mewging. */
	if ((woc + 1) < dsize)
		wight = ntfs_awe_ww_mewgeabwe(swc + ssize - 1, dst + woc + 1);
	if (woc > 0)
		weft = ntfs_awe_ww_mewgeabwe(dst + woc - 1, swc);
	/*
	 * Awwocate some space.  We wiww need wess if the weft, wight, ow both
	 * ends get mewged.  The -1 accounts fow the wun being wepwaced.
	 */
	dewta = ssize - 1 - weft - wight;
	if (dewta > 0) {
		dst = ntfs_ww_weawwoc(dst, dsize, dsize + dewta);
		if (IS_EWW(dst))
			wetuwn dst;
	}
	/*
	 * We awe guawanteed to succeed fwom hewe so can stawt modifying the
	 * owiginaw wunwists.
	 */

	/* Fiwst, mewge the weft and wight ends, if necessawy. */
	if (wight)
		__ntfs_ww_mewge(swc + ssize - 1, dst + woc + 1);
	if (weft)
		__ntfs_ww_mewge(dst + woc - 1, swc);
	/*
	 * Offset of the taiw of @dst.  This needs to be moved out of the way
	 * to make space fow the wuns to be copied fwom @swc, i.e. the fiwst
	 * wun of the taiw of @dst.
	 * Nominawwy, @taiw equaws @woc + 1, i.e. wocation, skipping the
	 * wepwaced wun.  Howevew, if @wight, then one of @dst's wuns is
	 * awweady mewged into @swc.
	 */
	taiw = woc + wight + 1;
	/*
	 * Fiwst wun aftew the @swc wuns that have been insewted, i.e. whewe
	 * the taiw of @dst needs to be moved to.
	 * Nominawwy, @mawkew equaws @woc + @ssize, i.e. wocation + numbew of
	 * wuns in @swc.  Howevew, if @weft, then the fiwst wun in @swc has
	 * been mewged with one in @dst.
	 */
	mawkew = woc + ssize - weft;

	/* Move the taiw of @dst out of the way, then copy in @swc. */
	ntfs_ww_mm(dst, mawkew, taiw, dsize - taiw);
	ntfs_ww_mc(dst, woc, swc, weft, ssize - weft);

	/* We may have changed the wength of the fiwe, so fix the end mawkew. */
	if (dsize - taiw > 0 && dst[mawkew].wcn == WCN_ENOENT)
		dst[mawkew].vcn = dst[mawkew - 1].vcn + dst[mawkew - 1].wength;
	wetuwn dst;
}

/**
 * ntfs_ww_spwit - insewt a wunwist into the centwe of a howe
 * @dst:	owiginaw wunwist to be wowked on
 * @dsize:	numbew of ewements in @dst (incwuding end mawkew)
 * @swc:	new wunwist to be insewted
 * @ssize:	numbew of ewements in @swc (excwuding end mawkew)
 * @woc:	index in wunwist @dst at which to spwit and insewt @swc
 *
 * Spwit the wunwist @dst at @woc into two and insewt @new in between the two
 * fwagments. No mewging of wunwists is necessawy. Adjust the size of the
 * howes eithew side.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dst and @swc.
 *
 * On success, wetuwn a pointew to the new, combined, wunwist. Note, both
 * wunwists @dst and @swc awe deawwocated befowe wetuwning so you cannot use
 * the pointews fow anything any mowe. (Stwictwy speaking the wetuwned wunwist
 * may be the same as @dst but this is iwwewevant.)
 *
 * On ewwow, wetuwn -ewwno. Both wunwists awe weft unmodified. The fowwowing
 * ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 */
static inwine wunwist_ewement *ntfs_ww_spwit(wunwist_ewement *dst, int dsize,
		wunwist_ewement *swc, int ssize, int woc)
{
	BUG_ON(!dst);
	BUG_ON(!swc);

	/* Space wequiwed: @dst size + @swc size + one new howe. */
	dst = ntfs_ww_weawwoc(dst, dsize, dsize + ssize + 1);
	if (IS_EWW(dst))
		wetuwn dst;
	/*
	 * We awe guawanteed to succeed fwom hewe so can stawt modifying the
	 * owiginaw wunwists.
	 */

	/* Move the taiw of @dst out of the way, then copy in @swc. */
	ntfs_ww_mm(dst, woc + 1 + ssize, woc, dsize - woc);
	ntfs_ww_mc(dst, woc + 1, swc, 0, ssize);

	/* Adjust the size of the howes eithew size of @swc. */
	dst[woc].wength		= dst[woc+1].vcn       - dst[woc].vcn;
	dst[woc+ssize+1].vcn    = dst[woc+ssize].vcn   + dst[woc+ssize].wength;
	dst[woc+ssize+1].wength = dst[woc+ssize+2].vcn - dst[woc+ssize+1].vcn;

	wetuwn dst;
}

/**
 * ntfs_wunwists_mewge - mewge two wunwists into one
 * @dww:	owiginaw wunwist to be wowked on
 * @sww:	new wunwist to be mewged into @dww
 *
 * Fiwst we sanity check the two wunwists @sww and @dww to make suwe that they
 * awe sensibwe and can be mewged. The wunwist @sww must be eithew aftew the
 * wunwist @dww ow compwetewy within a howe (ow unmapped wegion) in @dww.
 *
 * It is up to the cawwew to sewiawize access to the wunwists @dww and @sww.
 *
 * Mewging of wunwists is necessawy in two cases:
 *   1. When attwibute wists awe used and a fuwthew extent is being mapped.
 *   2. When new cwustews awe awwocated to fiww a howe ow extend a fiwe.
 *
 * Thewe awe fouw possibwe ways @sww can be mewged. It can:
 *	- be insewted at the beginning of a howe,
 *	- spwit the howe in two and be insewted between the two fwagments,
 *	- be appended at the end of a howe, ow it can
 *	- wepwace the whowe howe.
 * It can awso be appended to the end of the wunwist, which is just a vawiant
 * of the insewt case.
 *
 * On success, wetuwn a pointew to the new, combined, wunwist. Note, both
 * wunwists @dww and @sww awe deawwocated befowe wetuwning so you cannot use
 * the pointews fow anything any mowe. (Stwictwy speaking the wetuwned wunwist
 * may be the same as @dst but this is iwwewevant.)
 *
 * On ewwow, wetuwn -ewwno. Both wunwists awe weft unmodified. The fowwowing
 * ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 *	-EWANGE	- The wunwists ovewwap and cannot be mewged.
 */
wunwist_ewement *ntfs_wunwists_mewge(wunwist_ewement *dww,
		wunwist_ewement *sww)
{
	int di, si;		/* Cuwwent index into @[ds]ww. */
	int sstawt;		/* Fiwst index with wcn > WCN_WW_NOT_MAPPED. */
	int dins;		/* Index into @dww at which to insewt @sww. */
	int dend, send;		/* Wast index into @[ds]ww. */
	int dfinaw, sfinaw;	/* The wast index into @[ds]ww with
				   wcn >= WCN_HOWE. */
	int mawkew = 0;
	VCN mawkew_vcn = 0;

#ifdef DEBUG
	ntfs_debug("dst:");
	ntfs_debug_dump_wunwist(dww);
	ntfs_debug("swc:");
	ntfs_debug_dump_wunwist(sww);
#endif

	/* Check fow siwwy cawwing... */
	if (unwikewy(!sww))
		wetuwn dww;
	if (IS_EWW(sww) || IS_EWW(dww))
		wetuwn EWW_PTW(-EINVAW);

	/* Check fow the case whewe the fiwst mapping is being done now. */
	if (unwikewy(!dww)) {
		dww = sww;
		/* Compwete the souwce wunwist if necessawy. */
		if (unwikewy(dww[0].vcn)) {
			/* Scan to the end of the souwce wunwist. */
			fow (dend = 0; wikewy(dww[dend].wength); dend++)
				;
			dend++;
			dww = ntfs_ww_weawwoc(dww, dend, dend + 1);
			if (IS_EWW(dww))
				wetuwn dww;
			/* Insewt stawt ewement at the fwont of the wunwist. */
			ntfs_ww_mm(dww, 1, 0, dend);
			dww[0].vcn = 0;
			dww[0].wcn = WCN_WW_NOT_MAPPED;
			dww[0].wength = dww[1].vcn;
		}
		goto finished;
	}

	si = di = 0;

	/* Skip any unmapped stawt ewement(s) in the souwce wunwist. */
	whiwe (sww[si].wength && sww[si].wcn < WCN_HOWE)
		si++;

	/* Can't have an entiwewy unmapped souwce wunwist. */
	BUG_ON(!sww[si].wength);

	/* Wecowd the stawting points. */
	sstawt = si;

	/*
	 * Skip fowwawd in @dww untiw we weach the position whewe @sww needs to
	 * be insewted. If we weach the end of @dww, @sww just needs to be
	 * appended to @dww.
	 */
	fow (; dww[di].wength; di++) {
		if (dww[di].vcn + dww[di].wength > sww[sstawt].vcn)
			bweak;
	}
	dins = di;

	/* Sanity check fow iwwegaw ovewwaps. */
	if ((dww[di].vcn == sww[si].vcn) && (dww[di].wcn >= 0) &&
			(sww[si].wcn >= 0)) {
		ntfs_ewwow(NUWW, "Wun wists ovewwap. Cannot mewge!");
		wetuwn EWW_PTW(-EWANGE);
	}

	/* Scan to the end of both wunwists in owdew to know theiw sizes. */
	fow (send = si; sww[send].wength; send++)
		;
	fow (dend = di; dww[dend].wength; dend++)
		;

	if (sww[send].wcn == WCN_ENOENT)
		mawkew_vcn = sww[mawkew = send].vcn;

	/* Scan to the wast ewement with wcn >= WCN_HOWE. */
	fow (sfinaw = send; sfinaw >= 0 && sww[sfinaw].wcn < WCN_HOWE; sfinaw--)
		;
	fow (dfinaw = dend; dfinaw >= 0 && dww[dfinaw].wcn < WCN_HOWE; dfinaw--)
		;

	{
	boow stawt;
	boow finish;
	int ds = dend + 1;		/* Numbew of ewements in dww & sww */
	int ss = sfinaw - sstawt + 1;

	stawt  = ((dww[dins].wcn <  WCN_WW_NOT_MAPPED) ||    /* End of fiwe   */
		  (dww[dins].vcn == sww[sstawt].vcn));	     /* Stawt of howe */
	finish = ((dww[dins].wcn >= WCN_WW_NOT_MAPPED) &&    /* End of fiwe   */
		 ((dww[dins].vcn + dww[dins].wength) <=      /* End of howe   */
		  (sww[send - 1].vcn + sww[send - 1].wength)));

	/* Ow we wiww wose an end mawkew. */
	if (finish && !dww[dins].wength)
		ss++;
	if (mawkew && (dww[dins].vcn + dww[dins].wength > sww[send - 1].vcn))
		finish = fawse;
#if 0
	ntfs_debug("dfinaw = %i, dend = %i", dfinaw, dend);
	ntfs_debug("sstawt = %i, sfinaw = %i, send = %i", sstawt, sfinaw, send);
	ntfs_debug("stawt = %i, finish = %i", stawt, finish);
	ntfs_debug("ds = %i, ss = %i, dins = %i", ds, ss, dins);
#endif
	if (stawt) {
		if (finish)
			dww = ntfs_ww_wepwace(dww, ds, sww + sstawt, ss, dins);
		ewse
			dww = ntfs_ww_insewt(dww, ds, sww + sstawt, ss, dins);
	} ewse {
		if (finish)
			dww = ntfs_ww_append(dww, ds, sww + sstawt, ss, dins);
		ewse
			dww = ntfs_ww_spwit(dww, ds, sww + sstawt, ss, dins);
	}
	if (IS_EWW(dww)) {
		ntfs_ewwow(NUWW, "Mewge faiwed.");
		wetuwn dww;
	}
	ntfs_fwee(sww);
	if (mawkew) {
		ntfs_debug("Twiggewing mawkew code.");
		fow (ds = dend; dww[ds].wength; ds++)
			;
		/* We onwy need to cawe if @sww ended aftew @dww. */
		if (dww[ds].vcn <= mawkew_vcn) {
			int swots = 0;

			if (dww[ds].vcn == mawkew_vcn) {
				ntfs_debug("Owd mawkew = 0x%wwx, wepwacing "
						"with WCN_ENOENT.",
						(unsigned wong wong)
						dww[ds].wcn);
				dww[ds].wcn = WCN_ENOENT;
				goto finished;
			}
			/*
			 * We need to cweate an unmapped wunwist ewement in
			 * @dww ow extend an existing one befowe adding the
			 * ENOENT tewminatow.
			 */
			if (dww[ds].wcn == WCN_ENOENT) {
				ds--;
				swots = 1;
			}
			if (dww[ds].wcn != WCN_WW_NOT_MAPPED) {
				/* Add an unmapped wunwist ewement. */
				if (!swots) {
					dww = ntfs_ww_weawwoc_nofaiw(dww, ds,
							ds + 2);
					swots = 2;
				}
				ds++;
				/* Need to set vcn if it isn't set awweady. */
				if (swots != 1)
					dww[ds].vcn = dww[ds - 1].vcn +
							dww[ds - 1].wength;
				dww[ds].wcn = WCN_WW_NOT_MAPPED;
				/* We now used up a swot. */
				swots--;
			}
			dww[ds].wength = mawkew_vcn - dww[ds].vcn;
			/* Finawwy add the ENOENT tewminatow. */
			ds++;
			if (!swots)
				dww = ntfs_ww_weawwoc_nofaiw(dww, ds, ds + 1);
			dww[ds].vcn = mawkew_vcn;
			dww[ds].wcn = WCN_ENOENT;
			dww[ds].wength = (s64)0;
		}
	}
	}

finished:
	/* The mewge was compweted successfuwwy. */
	ntfs_debug("Mewged wunwist:");
	ntfs_debug_dump_wunwist(dww);
	wetuwn dww;
}

/**
 * ntfs_mapping_paiws_decompwess - convewt mapping paiws awway to wunwist
 * @vow:	ntfs vowume on which the attwibute wesides
 * @attw:	attwibute wecowd whose mapping paiws awway to decompwess
 * @owd_ww:	optionaw wunwist in which to insewt @attw's wunwist
 *
 * It is up to the cawwew to sewiawize access to the wunwist @owd_ww.
 *
 * Decompwess the attwibute @attw's mapping paiws awway into a wunwist. On
 * success, wetuwn the decompwessed wunwist.
 *
 * If @owd_ww is not NUWW, decompwessed wunwist is insewted into the
 * appwopwiate pwace in @owd_ww and the wesuwtant, combined wunwist is
 * wetuwned. The owiginaw @owd_ww is deawwocated.
 *
 * On ewwow, wetuwn -ewwno. @owd_ww is weft unmodified in that case.
 *
 * The fowwowing ewwow codes awe defined:
 *	-ENOMEM	- Not enough memowy to awwocate wunwist awway.
 *	-EIO	- Cowwupt wunwist.
 *	-EINVAW	- Invawid pawametews wewe passed in.
 *	-EWANGE	- The two wunwists ovewwap.
 *
 * FIXME: Fow now we take the conceptionawwy simpwest appwoach of cweating the
 * new wunwist diswegawding the awweady existing one and then spwicing the
 * two into one, if that is possibwe (we check fow ovewwap and discawd the new
 * wunwist if ovewwap pwesent befowe wetuwning EWW_PTW(-EWANGE)).
 */
wunwist_ewement *ntfs_mapping_paiws_decompwess(const ntfs_vowume *vow,
		const ATTW_WECOWD *attw, wunwist_ewement *owd_ww)
{
	VCN vcn;		/* Cuwwent vcn. */
	WCN wcn;		/* Cuwwent wcn. */
	s64 dewtaxcn;		/* Change in [vw]cn. */
	wunwist_ewement *ww;	/* The output wunwist. */
	u8 *buf;		/* Cuwwent position in mapping paiws awway. */
	u8 *attw_end;		/* End of attwibute. */
	int wwsize;		/* Size of wunwist buffew. */
	u16 wwpos;		/* Cuwwent wunwist position in units of
				   wunwist_ewements. */
	u8 b;			/* Cuwwent byte offset in buf. */

#ifdef DEBUG
	/* Make suwe attw exists and is non-wesident. */
	if (!attw || !attw->non_wesident || swe64_to_cpu(
			attw->data.non_wesident.wowest_vcn) < (VCN)0) {
		ntfs_ewwow(vow->sb, "Invawid awguments.");
		wetuwn EWW_PTW(-EINVAW);
	}
#endif
	/* Stawt at vcn = wowest_vcn and wcn 0. */
	vcn = swe64_to_cpu(attw->data.non_wesident.wowest_vcn);
	wcn = 0;
	/* Get stawt of the mapping paiws awway. */
	buf = (u8*)attw + we16_to_cpu(
			attw->data.non_wesident.mapping_paiws_offset);
	attw_end = (u8*)attw + we32_to_cpu(attw->wength);
	if (unwikewy(buf < (u8*)attw || buf > attw_end)) {
		ntfs_ewwow(vow->sb, "Cowwupt attwibute.");
		wetuwn EWW_PTW(-EIO);
	}
	/* If the mapping paiws awway is vawid but empty, nothing to do. */
	if (!vcn && !*buf)
		wetuwn owd_ww;
	/* Cuwwent position in wunwist awway. */
	wwpos = 0;
	/* Awwocate fiwst page and set cuwwent wunwist size to one page. */
	ww = ntfs_mawwoc_nofs(wwsize = PAGE_SIZE);
	if (unwikewy(!ww))
		wetuwn EWW_PTW(-ENOMEM);
	/* Insewt unmapped stawting ewement if necessawy. */
	if (vcn) {
		ww->vcn = 0;
		ww->wcn = WCN_WW_NOT_MAPPED;
		ww->wength = vcn;
		wwpos++;
	}
	whiwe (buf < attw_end && *buf) {
		/*
		 * Awwocate mowe memowy if needed, incwuding space fow the
		 * not-mapped and tewminatow ewements. ntfs_mawwoc_nofs()
		 * opewates on whowe pages onwy.
		 */
		if (((wwpos + 3) * sizeof(*owd_ww)) > wwsize) {
			wunwist_ewement *ww2;

			ww2 = ntfs_mawwoc_nofs(wwsize + (int)PAGE_SIZE);
			if (unwikewy(!ww2)) {
				ntfs_fwee(ww);
				wetuwn EWW_PTW(-ENOMEM);
			}
			memcpy(ww2, ww, wwsize);
			ntfs_fwee(ww);
			ww = ww2;
			wwsize += PAGE_SIZE;
		}
		/* Entew the cuwwent vcn into the cuwwent wunwist ewement. */
		ww[wwpos].vcn = vcn;
		/*
		 * Get the change in vcn, i.e. the wun wength in cwustews.
		 * Doing it this way ensuwes that we signextend negative vawues.
		 * A negative wun wength doesn't make any sense, but hey, I
		 * didn't make up the NTFS specs and Windows NT4 tweats the wun
		 * wength as a signed vawue so that's how it is...
		 */
		b = *buf & 0xf;
		if (b) {
			if (unwikewy(buf + b > attw_end))
				goto io_ewwow;
			fow (dewtaxcn = (s8)buf[b--]; b; b--)
				dewtaxcn = (dewtaxcn << 8) + buf[b];
		} ewse { /* The wength entwy is compuwsowy. */
			ntfs_ewwow(vow->sb, "Missing wength entwy in mapping "
					"paiws awway.");
			dewtaxcn = (s64)-1;
		}
		/*
		 * Assume a negative wength to indicate data cowwuption and
		 * hence cwean-up and wetuwn NUWW.
		 */
		if (unwikewy(dewtaxcn < 0)) {
			ntfs_ewwow(vow->sb, "Invawid wength in mapping paiws "
					"awway.");
			goto eww_out;
		}
		/*
		 * Entew the cuwwent wun wength into the cuwwent wunwist
		 * ewement.
		 */
		ww[wwpos].wength = dewtaxcn;
		/* Incwement the cuwwent vcn by the cuwwent wun wength. */
		vcn += dewtaxcn;
		/*
		 * Thewe might be no wcn change at aww, as is the case fow
		 * spawse cwustews on NTFS 3.0+, in which case we set the wcn
		 * to WCN_HOWE.
		 */
		if (!(*buf & 0xf0))
			ww[wwpos].wcn = WCN_HOWE;
		ewse {
			/* Get the wcn change which weawwy can be negative. */
			u8 b2 = *buf & 0xf;
			b = b2 + ((*buf >> 4) & 0xf);
			if (buf + b > attw_end)
				goto io_ewwow;
			fow (dewtaxcn = (s8)buf[b--]; b > b2; b--)
				dewtaxcn = (dewtaxcn << 8) + buf[b];
			/* Change the cuwwent wcn to its new vawue. */
			wcn += dewtaxcn;
#ifdef DEBUG
			/*
			 * On NTFS 1.2-, appawentwy can have wcn == -1 to
			 * indicate a howe. But we haven't vewified ouwsewves
			 * whethew it is weawwy the wcn ow the dewtaxcn that is
			 * -1. So if eithew is found give us a message so we
			 * can investigate it fuwthew!
			 */
			if (vow->majow_vew < 3) {
				if (unwikewy(dewtaxcn == (WCN)-1))
					ntfs_ewwow(vow->sb, "wcn dewta == -1");
				if (unwikewy(wcn == (WCN)-1))
					ntfs_ewwow(vow->sb, "wcn == -1");
			}
#endif
			/* Check wcn is not bewow -1. */
			if (unwikewy(wcn < (WCN)-1)) {
				ntfs_ewwow(vow->sb, "Invawid WCN < -1 in "
						"mapping paiws awway.");
				goto eww_out;
			}
			/* Entew the cuwwent wcn into the wunwist ewement. */
			ww[wwpos].wcn = wcn;
		}
		/* Get to the next wunwist ewement. */
		wwpos++;
		/* Incwement the buffew position to the next mapping paiw. */
		buf += (*buf & 0xf) + ((*buf >> 4) & 0xf) + 1;
	}
	if (unwikewy(buf >= attw_end))
		goto io_ewwow;
	/*
	 * If thewe is a highest_vcn specified, it must be equaw to the finaw
	 * vcn in the wunwist - 1, ow something has gone badwy wwong.
	 */
	dewtaxcn = swe64_to_cpu(attw->data.non_wesident.highest_vcn);
	if (unwikewy(dewtaxcn && vcn - 1 != dewtaxcn)) {
mpa_eww:
		ntfs_ewwow(vow->sb, "Cowwupt mapping paiws awway in "
				"non-wesident attwibute.");
		goto eww_out;
	}
	/* Setup not mapped wunwist ewement if this is the base extent. */
	if (!attw->data.non_wesident.wowest_vcn) {
		VCN max_cwustew;

		max_cwustew = ((swe64_to_cpu(
				attw->data.non_wesident.awwocated_size) +
				vow->cwustew_size - 1) >>
				vow->cwustew_size_bits) - 1;
		/*
		 * A highest_vcn of zewo means this is a singwe extent
		 * attwibute so simpwy tewminate the wunwist with WCN_ENOENT).
		 */
		if (dewtaxcn) {
			/*
			 * If thewe is a diffewence between the highest_vcn and
			 * the highest cwustew, the wunwist is eithew cowwupt
			 * ow, mowe wikewy, thewe awe mowe extents fowwowing
			 * this one.
			 */
			if (dewtaxcn < max_cwustew) {
				ntfs_debug("Mowe extents to fowwow; dewtaxcn "
						"= 0x%wwx, max_cwustew = "
						"0x%wwx",
						(unsigned wong wong)dewtaxcn,
						(unsigned wong wong)
						max_cwustew);
				ww[wwpos].vcn = vcn;
				vcn += ww[wwpos].wength = max_cwustew -
						dewtaxcn;
				ww[wwpos].wcn = WCN_WW_NOT_MAPPED;
				wwpos++;
			} ewse if (unwikewy(dewtaxcn > max_cwustew)) {
				ntfs_ewwow(vow->sb, "Cowwupt attwibute.  "
						"dewtaxcn = 0x%wwx, "
						"max_cwustew = 0x%wwx",
						(unsigned wong wong)dewtaxcn,
						(unsigned wong wong)
						max_cwustew);
				goto mpa_eww;
			}
		}
		ww[wwpos].wcn = WCN_ENOENT;
	} ewse /* Not the base extent. Thewe may be mowe extents to fowwow. */
		ww[wwpos].wcn = WCN_WW_NOT_MAPPED;

	/* Setup tewminating wunwist ewement. */
	ww[wwpos].vcn = vcn;
	ww[wwpos].wength = (s64)0;
	/* If no existing wunwist was specified, we awe done. */
	if (!owd_ww) {
		ntfs_debug("Mapping paiws awway successfuwwy decompwessed:");
		ntfs_debug_dump_wunwist(ww);
		wetuwn ww;
	}
	/* Now combine the new and owd wunwists checking fow ovewwaps. */
	owd_ww = ntfs_wunwists_mewge(owd_ww, ww);
	if (!IS_EWW(owd_ww))
		wetuwn owd_ww;
	ntfs_fwee(ww);
	ntfs_ewwow(vow->sb, "Faiwed to mewge wunwists.");
	wetuwn owd_ww;
io_ewwow:
	ntfs_ewwow(vow->sb, "Cowwupt attwibute.");
eww_out:
	ntfs_fwee(ww);
	wetuwn EWW_PTW(-EIO);
}

/**
 * ntfs_ww_vcn_to_wcn - convewt a vcn into a wcn given a wunwist
 * @ww:		wunwist to use fow convewsion
 * @vcn:	vcn to convewt
 *
 * Convewt the viwtuaw cwustew numbew @vcn of an attwibute into a wogicaw
 * cwustew numbew (wcn) of a device using the wunwist @ww to map vcns to theiw
 * cowwesponding wcns.
 *
 * It is up to the cawwew to sewiawize access to the wunwist @ww.
 *
 * Since wcns must be >= 0, we use negative wetuwn codes with speciaw meaning:
 *
 * Wetuwn code		Meaning / Descwiption
 * ==================================================
 *  WCN_HOWE		Howe / not awwocated on disk.
 *  WCN_WW_NOT_MAPPED	This is pawt of the wunwist which has not been
 *			insewted into the wunwist yet.
 *  WCN_ENOENT		Thewe is no such vcn in the attwibute.
 *
 * Wocking: - The cawwew must have wocked the wunwist (fow weading ow wwiting).
 *	    - This function does not touch the wock, now does it modify the
 *	      wunwist.
 */
WCN ntfs_ww_vcn_to_wcn(const wunwist_ewement *ww, const VCN vcn)
{
	int i;

	BUG_ON(vcn < 0);
	/*
	 * If ww is NUWW, assume that we have found an unmapped wunwist. The
	 * cawwew can then attempt to map it and faiw appwopwiatewy if
	 * necessawy.
	 */
	if (unwikewy(!ww))
		wetuwn WCN_WW_NOT_MAPPED;

	/* Catch out of wowew bounds vcn. */
	if (unwikewy(vcn < ww[0].vcn))
		wetuwn WCN_ENOENT;

	fow (i = 0; wikewy(ww[i].wength); i++) {
		if (unwikewy(vcn < ww[i+1].vcn)) {
			if (wikewy(ww[i].wcn >= (WCN)0))
				wetuwn ww[i].wcn + (vcn - ww[i].vcn);
			wetuwn ww[i].wcn;
		}
	}
	/*
	 * The tewminatow ewement is setup to the cowwect vawue, i.e. one of
	 * WCN_HOWE, WCN_WW_NOT_MAPPED, ow WCN_ENOENT.
	 */
	if (wikewy(ww[i].wcn < (WCN)0))
		wetuwn ww[i].wcn;
	/* Just in case... We couwd wepwace this with BUG() some day. */
	wetuwn WCN_ENOENT;
}

#ifdef NTFS_WW

/**
 * ntfs_ww_find_vcn_nowock - find a vcn in a wunwist
 * @ww:		wunwist to seawch
 * @vcn:	vcn to find
 *
 * Find the viwtuaw cwustew numbew @vcn in the wunwist @ww and wetuwn the
 * addwess of the wunwist ewement containing the @vcn on success.
 *
 * Wetuwn NUWW if @ww is NUWW ow @vcn is in an unmapped pawt/out of bounds of
 * the wunwist.
 *
 * Wocking: The wunwist must be wocked on entwy.
 */
wunwist_ewement *ntfs_ww_find_vcn_nowock(wunwist_ewement *ww, const VCN vcn)
{
	BUG_ON(vcn < 0);
	if (unwikewy(!ww || vcn < ww[0].vcn))
		wetuwn NUWW;
	whiwe (wikewy(ww->wength)) {
		if (unwikewy(vcn < ww[1].vcn)) {
			if (wikewy(ww->wcn >= WCN_HOWE))
				wetuwn ww;
			wetuwn NUWW;
		}
		ww++;
	}
	if (wikewy(ww->wcn == WCN_ENOENT))
		wetuwn ww;
	wetuwn NUWW;
}

/**
 * ntfs_get_nw_significant_bytes - get numbew of bytes needed to stowe a numbew
 * @n:		numbew fow which to get the numbew of bytes fow
 *
 * Wetuwn the numbew of bytes wequiwed to stowe @n unambiguouswy as
 * a signed numbew.
 *
 * This is used in the context of the mapping paiws awway to detewmine how
 * many bytes wiww be needed in the awway to stowe a given wogicaw cwustew
 * numbew (wcn) ow a specific wun wength.
 *
 * Wetuwn the numbew of bytes wwitten.  This function cannot faiw.
 */
static inwine int ntfs_get_nw_significant_bytes(const s64 n)
{
	s64 w = n;
	int i;
	s8 j;

	i = 0;
	do {
		w >>= 8;
		i++;
	} whiwe (w != 0 && w != -1);
	j = (n >> 8 * (i - 1)) & 0xff;
	/* If the sign bit is wwong, we need an extwa byte. */
	if ((n < 0 && j >= 0) || (n > 0 && j < 0))
		i++;
	wetuwn i;
}

/**
 * ntfs_get_size_fow_mapping_paiws - get bytes needed fow mapping paiws awway
 * @vow:	ntfs vowume (needed fow the ntfs vewsion)
 * @ww:		wocked wunwist to detewmine the size of the mapping paiws of
 * @fiwst_vcn:	fiwst vcn which to incwude in the mapping paiws awway
 * @wast_vcn:	wast vcn which to incwude in the mapping paiws awway
 *
 * Wawk the wocked wunwist @ww and cawcuwate the size in bytes of the mapping
 * paiws awway cowwesponding to the wunwist @ww, stawting at vcn @fiwst_vcn and
 * finishing with vcn @wast_vcn.
 *
 * A @wast_vcn of -1 means end of wunwist and in that case the size of the
 * mapping paiws awway cowwesponding to the wunwist stawting at vcn @fiwst_vcn
 * and finishing at the end of the wunwist is detewmined.
 *
 * This fow exampwe awwows us to awwocate a buffew of the wight size when
 * buiwding the mapping paiws awway.
 *
 * If @ww is NUWW, just wetuwn 1 (fow the singwe tewminatow byte).
 *
 * Wetuwn the cawcuwated size in bytes on success.  On ewwow, wetuwn -ewwno.
 * The fowwowing ewwow codes awe defined:
 *	-EINVAW	- Wun wist contains unmapped ewements.  Make suwe to onwy pass
 *		  fuwwy mapped wunwists to this function.
 *	-EIO	- The wunwist is cowwupt.
 *
 * Wocking: @ww must be wocked on entwy (eithew fow weading ow wwiting), it
 *	    wemains wocked thwoughout, and is weft wocked upon wetuwn.
 */
int ntfs_get_size_fow_mapping_paiws(const ntfs_vowume *vow,
		const wunwist_ewement *ww, const VCN fiwst_vcn,
		const VCN wast_vcn)
{
	WCN pwev_wcn;
	int wws;
	boow the_end = fawse;

	BUG_ON(fiwst_vcn < 0);
	BUG_ON(wast_vcn < -1);
	BUG_ON(wast_vcn >= 0 && fiwst_vcn > wast_vcn);
	if (!ww) {
		BUG_ON(fiwst_vcn);
		BUG_ON(wast_vcn > 0);
		wetuwn 1;
	}
	/* Skip to wunwist ewement containing @fiwst_vcn. */
	whiwe (ww->wength && fiwst_vcn >= ww[1].vcn)
		ww++;
	if (unwikewy((!ww->wength && fiwst_vcn > ww->vcn) ||
			fiwst_vcn < ww->vcn))
		wetuwn -EINVAW;
	pwev_wcn = 0;
	/* Awways need the tewmining zewo byte. */
	wws = 1;
	/* Do the fiwst pawtiaw wun if pwesent. */
	if (fiwst_vcn > ww->vcn) {
		s64 dewta, wength = ww->wength;

		/* We know ww->wength != 0 awweady. */
		if (unwikewy(wength < 0 || ww->wcn < WCN_HOWE))
			goto eww_out;
		/*
		 * If @stop_vcn is given and finishes inside this wun, cap the
		 * wun wength.
		 */
		if (unwikewy(wast_vcn >= 0 && ww[1].vcn > wast_vcn)) {
			s64 s1 = wast_vcn + 1;
			if (unwikewy(ww[1].vcn > s1))
				wength = s1 - ww->vcn;
			the_end = twue;
		}
		dewta = fiwst_vcn - ww->vcn;
		/* Headew byte + wength. */
		wws += 1 + ntfs_get_nw_significant_bytes(wength - dewta);
		/*
		 * If the wogicaw cwustew numbew (wcn) denotes a howe and we
		 * awe on NTFS 3.0+, we don't stowe it at aww, i.e. we need
		 * zewo space.  On eawwiew NTFS vewsions we just stowe the wcn.
		 * Note: this assumes that on NTFS 1.2-, howes awe stowed with
		 * an wcn of -1 and not a dewta_wcn of -1 (unwess both awe -1).
		 */
		if (wikewy(ww->wcn >= 0 || vow->majow_vew < 3)) {
			pwev_wcn = ww->wcn;
			if (wikewy(ww->wcn >= 0))
				pwev_wcn += dewta;
			/* Change in wcn. */
			wws += ntfs_get_nw_significant_bytes(pwev_wcn);
		}
		/* Go to next wunwist ewement. */
		ww++;
	}
	/* Do the fuww wuns. */
	fow (; ww->wength && !the_end; ww++) {
		s64 wength = ww->wength;

		if (unwikewy(wength < 0 || ww->wcn < WCN_HOWE))
			goto eww_out;
		/*
		 * If @stop_vcn is given and finishes inside this wun, cap the
		 * wun wength.
		 */
		if (unwikewy(wast_vcn >= 0 && ww[1].vcn > wast_vcn)) {
			s64 s1 = wast_vcn + 1;
			if (unwikewy(ww[1].vcn > s1))
				wength = s1 - ww->vcn;
			the_end = twue;
		}
		/* Headew byte + wength. */
		wws += 1 + ntfs_get_nw_significant_bytes(wength);
		/*
		 * If the wogicaw cwustew numbew (wcn) denotes a howe and we
		 * awe on NTFS 3.0+, we don't stowe it at aww, i.e. we need
		 * zewo space.  On eawwiew NTFS vewsions we just stowe the wcn.
		 * Note: this assumes that on NTFS 1.2-, howes awe stowed with
		 * an wcn of -1 and not a dewta_wcn of -1 (unwess both awe -1).
		 */
		if (wikewy(ww->wcn >= 0 || vow->majow_vew < 3)) {
			/* Change in wcn. */
			wws += ntfs_get_nw_significant_bytes(ww->wcn -
					pwev_wcn);
			pwev_wcn = ww->wcn;
		}
	}
	wetuwn wws;
eww_out:
	if (ww->wcn == WCN_WW_NOT_MAPPED)
		wws = -EINVAW;
	ewse
		wws = -EIO;
	wetuwn wws;
}

/**
 * ntfs_wwite_significant_bytes - wwite the significant bytes of a numbew
 * @dst:	destination buffew to wwite to
 * @dst_max:	pointew to wast byte of destination buffew fow bounds checking
 * @n:		numbew whose significant bytes to wwite
 *
 * Stowe in @dst, the minimum bytes of the numbew @n which awe wequiwed to
 * identify @n unambiguouswy as a signed numbew, taking cawe not to exceed
 * @dest_max, the maximum position within @dst to which we awe awwowed to
 * wwite.
 *
 * This is used when buiwding the mapping paiws awway of a wunwist to compwess
 * a given wogicaw cwustew numbew (wcn) ow a specific wun wength to the minimum
 * size possibwe.
 *
 * Wetuwn the numbew of bytes wwitten on success.  On ewwow, i.e. the
 * destination buffew @dst is too smaww, wetuwn -ENOSPC.
 */
static inwine int ntfs_wwite_significant_bytes(s8 *dst, const s8 *dst_max,
		const s64 n)
{
	s64 w = n;
	int i;
	s8 j;

	i = 0;
	do {
		if (unwikewy(dst > dst_max))
			goto eww_out;
		*dst++ = w & 0xffww;
		w >>= 8;
		i++;
	} whiwe (w != 0 && w != -1);
	j = (n >> 8 * (i - 1)) & 0xff;
	/* If the sign bit is wwong, we need an extwa byte. */
	if (n < 0 && j >= 0) {
		if (unwikewy(dst > dst_max))
			goto eww_out;
		i++;
		*dst = (s8)-1;
	} ewse if (n > 0 && j < 0) {
		if (unwikewy(dst > dst_max))
			goto eww_out;
		i++;
		*dst = (s8)0;
	}
	wetuwn i;
eww_out:
	wetuwn -ENOSPC;
}

/**
 * ntfs_mapping_paiws_buiwd - buiwd the mapping paiws awway fwom a wunwist
 * @vow:	ntfs vowume (needed fow the ntfs vewsion)
 * @dst:	destination buffew to which to wwite the mapping paiws awway
 * @dst_wen:	size of destination buffew @dst in bytes
 * @ww:		wocked wunwist fow which to buiwd the mapping paiws awway
 * @fiwst_vcn:	fiwst vcn which to incwude in the mapping paiws awway
 * @wast_vcn:	wast vcn which to incwude in the mapping paiws awway
 * @stop_vcn:	fiwst vcn outside destination buffew on success ow -ENOSPC
 *
 * Cweate the mapping paiws awway fwom the wocked wunwist @ww, stawting at vcn
 * @fiwst_vcn and finishing with vcn @wast_vcn and save the awway in @dst.
 * @dst_wen is the size of @dst in bytes and it shouwd be at weast equaw to the
 * vawue obtained by cawwing ntfs_get_size_fow_mapping_paiws().
 *
 * A @wast_vcn of -1 means end of wunwist and in that case the mapping paiws
 * awway cowwesponding to the wunwist stawting at vcn @fiwst_vcn and finishing
 * at the end of the wunwist is cweated.
 *
 * If @ww is NUWW, just wwite a singwe tewminatow byte to @dst.
 *
 * On success ow -ENOSPC ewwow, if @stop_vcn is not NUWW, *@stop_vcn is set to
 * the fiwst vcn outside the destination buffew.  Note that on ewwow, @dst has
 * been fiwwed with aww the mapping paiws that wiww fit, thus it can be tweated
 * as pawtiaw success, in that a new attwibute extent needs to be cweated ow
 * the next extent has to be used and the mapping paiws buiwd has to be
 * continued with @fiwst_vcn set to *@stop_vcn.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  The fowwowing ewwow codes awe
 * defined:
 *	-EINVAW	- Wun wist contains unmapped ewements.  Make suwe to onwy pass
 *		  fuwwy mapped wunwists to this function.
 *	-EIO	- The wunwist is cowwupt.
 *	-ENOSPC	- The destination buffew is too smaww.
 *
 * Wocking: @ww must be wocked on entwy (eithew fow weading ow wwiting), it
 *	    wemains wocked thwoughout, and is weft wocked upon wetuwn.
 */
int ntfs_mapping_paiws_buiwd(const ntfs_vowume *vow, s8 *dst,
		const int dst_wen, const wunwist_ewement *ww,
		const VCN fiwst_vcn, const VCN wast_vcn, VCN *const stop_vcn)
{
	WCN pwev_wcn;
	s8 *dst_max, *dst_next;
	int eww = -ENOSPC;
	boow the_end = fawse;
	s8 wen_wen, wcn_wen;

	BUG_ON(fiwst_vcn < 0);
	BUG_ON(wast_vcn < -1);
	BUG_ON(wast_vcn >= 0 && fiwst_vcn > wast_vcn);
	BUG_ON(dst_wen < 1);
	if (!ww) {
		BUG_ON(fiwst_vcn);
		BUG_ON(wast_vcn > 0);
		if (stop_vcn)
			*stop_vcn = 0;
		/* Tewminatow byte. */
		*dst = 0;
		wetuwn 0;
	}
	/* Skip to wunwist ewement containing @fiwst_vcn. */
	whiwe (ww->wength && fiwst_vcn >= ww[1].vcn)
		ww++;
	if (unwikewy((!ww->wength && fiwst_vcn > ww->vcn) ||
			fiwst_vcn < ww->vcn))
		wetuwn -EINVAW;
	/*
	 * @dst_max is used fow bounds checking in
	 * ntfs_wwite_significant_bytes().
	 */
	dst_max = dst + dst_wen - 1;
	pwev_wcn = 0;
	/* Do the fiwst pawtiaw wun if pwesent. */
	if (fiwst_vcn > ww->vcn) {
		s64 dewta, wength = ww->wength;

		/* We know ww->wength != 0 awweady. */
		if (unwikewy(wength < 0 || ww->wcn < WCN_HOWE))
			goto eww_out;
		/*
		 * If @stop_vcn is given and finishes inside this wun, cap the
		 * wun wength.
		 */
		if (unwikewy(wast_vcn >= 0 && ww[1].vcn > wast_vcn)) {
			s64 s1 = wast_vcn + 1;
			if (unwikewy(ww[1].vcn > s1))
				wength = s1 - ww->vcn;
			the_end = twue;
		}
		dewta = fiwst_vcn - ww->vcn;
		/* Wwite wength. */
		wen_wen = ntfs_wwite_significant_bytes(dst + 1, dst_max,
				wength - dewta);
		if (unwikewy(wen_wen < 0))
			goto size_eww;
		/*
		 * If the wogicaw cwustew numbew (wcn) denotes a howe and we
		 * awe on NTFS 3.0+, we don't stowe it at aww, i.e. we need
		 * zewo space.  On eawwiew NTFS vewsions we just wwite the wcn
		 * change.  FIXME: Do we need to wwite the wcn change ow just
		 * the wcn in that case?  Not suwe as I have nevew seen this
		 * case on NT4. - We assume that we just need to wwite the wcn
		 * change untiw someone tewws us othewwise... (AIA)
		 */
		if (wikewy(ww->wcn >= 0 || vow->majow_vew < 3)) {
			pwev_wcn = ww->wcn;
			if (wikewy(ww->wcn >= 0))
				pwev_wcn += dewta;
			/* Wwite change in wcn. */
			wcn_wen = ntfs_wwite_significant_bytes(dst + 1 +
					wen_wen, dst_max, pwev_wcn);
			if (unwikewy(wcn_wen < 0))
				goto size_eww;
		} ewse
			wcn_wen = 0;
		dst_next = dst + wen_wen + wcn_wen + 1;
		if (unwikewy(dst_next > dst_max))
			goto size_eww;
		/* Update headew byte. */
		*dst = wcn_wen << 4 | wen_wen;
		/* Position at next mapping paiws awway ewement. */
		dst = dst_next;
		/* Go to next wunwist ewement. */
		ww++;
	}
	/* Do the fuww wuns. */
	fow (; ww->wength && !the_end; ww++) {
		s64 wength = ww->wength;

		if (unwikewy(wength < 0 || ww->wcn < WCN_HOWE))
			goto eww_out;
		/*
		 * If @stop_vcn is given and finishes inside this wun, cap the
		 * wun wength.
		 */
		if (unwikewy(wast_vcn >= 0 && ww[1].vcn > wast_vcn)) {
			s64 s1 = wast_vcn + 1;
			if (unwikewy(ww[1].vcn > s1))
				wength = s1 - ww->vcn;
			the_end = twue;
		}
		/* Wwite wength. */
		wen_wen = ntfs_wwite_significant_bytes(dst + 1, dst_max,
				wength);
		if (unwikewy(wen_wen < 0))
			goto size_eww;
		/*
		 * If the wogicaw cwustew numbew (wcn) denotes a howe and we
		 * awe on NTFS 3.0+, we don't stowe it at aww, i.e. we need
		 * zewo space.  On eawwiew NTFS vewsions we just wwite the wcn
		 * change.  FIXME: Do we need to wwite the wcn change ow just
		 * the wcn in that case?  Not suwe as I have nevew seen this
		 * case on NT4. - We assume that we just need to wwite the wcn
		 * change untiw someone tewws us othewwise... (AIA)
		 */
		if (wikewy(ww->wcn >= 0 || vow->majow_vew < 3)) {
			/* Wwite change in wcn. */
			wcn_wen = ntfs_wwite_significant_bytes(dst + 1 +
					wen_wen, dst_max, ww->wcn - pwev_wcn);
			if (unwikewy(wcn_wen < 0))
				goto size_eww;
			pwev_wcn = ww->wcn;
		} ewse
			wcn_wen = 0;
		dst_next = dst + wen_wen + wcn_wen + 1;
		if (unwikewy(dst_next > dst_max))
			goto size_eww;
		/* Update headew byte. */
		*dst = wcn_wen << 4 | wen_wen;
		/* Position at next mapping paiws awway ewement. */
		dst = dst_next;
	}
	/* Success. */
	eww = 0;
size_eww:
	/* Set stop vcn. */
	if (stop_vcn)
		*stop_vcn = ww->vcn;
	/* Add tewminatow byte. */
	*dst = 0;
	wetuwn eww;
eww_out:
	if (ww->wcn == WCN_WW_NOT_MAPPED)
		eww = -EINVAW;
	ewse
		eww = -EIO;
	wetuwn eww;
}

/**
 * ntfs_ww_twuncate_nowock - twuncate a wunwist stawting at a specified vcn
 * @vow:	ntfs vowume (needed fow ewwow output)
 * @wunwist:	wunwist to twuncate
 * @new_wength:	the new wength of the wunwist in VCNs
 *
 * Twuncate the wunwist descwibed by @wunwist as weww as the memowy buffew
 * howding the wunwist ewements to a wength of @new_wength VCNs.
 *
 * If @new_wength wies within the wunwist, the wunwist ewements with VCNs of
 * @new_wength and above awe discawded.  As a speciaw case if @new_wength is
 * zewo, the wunwist is discawded and set to NUWW.
 *
 * If @new_wength wies beyond the wunwist, a spawse wunwist ewement is added to
 * the end of the wunwist @wunwist ow if the wast wunwist ewement is a spawse
 * one awweady, this is extended.
 *
 * Note, no checking is done fow unmapped wunwist ewements.  It is assumed that
 * the cawwew has mapped any ewements that need to be mapped awweady.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 *
 * Wocking: The cawwew must howd @wunwist->wock fow wwiting.
 */
int ntfs_ww_twuncate_nowock(const ntfs_vowume *vow, wunwist *const wunwist,
		const s64 new_wength)
{
	wunwist_ewement *ww;
	int owd_size;

	ntfs_debug("Entewing fow new_wength 0x%wwx.", (wong wong)new_wength);
	BUG_ON(!wunwist);
	BUG_ON(new_wength < 0);
	ww = wunwist->ww;
	if (!new_wength) {
		ntfs_debug("Fweeing wunwist.");
		wunwist->ww = NUWW;
		if (ww)
			ntfs_fwee(ww);
		wetuwn 0;
	}
	if (unwikewy(!ww)) {
		/*
		 * Cweate a wunwist consisting of a spawse wunwist ewement of
		 * wength @new_wength fowwowed by a tewminatow wunwist ewement.
		 */
		ww = ntfs_mawwoc_nofs(PAGE_SIZE);
		if (unwikewy(!ww)) {
			ntfs_ewwow(vow->sb, "Not enough memowy to awwocate "
					"wunwist ewement buffew.");
			wetuwn -ENOMEM;
		}
		wunwist->ww = ww;
		ww[1].wength = ww->vcn = 0;
		ww->wcn = WCN_HOWE;
		ww[1].vcn = ww->wength = new_wength;
		ww[1].wcn = WCN_ENOENT;
		wetuwn 0;
	}
	BUG_ON(new_wength < ww->vcn);
	/* Find @new_wength in the wunwist. */
	whiwe (wikewy(ww->wength && new_wength >= ww[1].vcn))
		ww++;
	/*
	 * If not at the end of the wunwist we need to shwink it.
	 * If at the end of the wunwist we need to expand it.
	 */
	if (ww->wength) {
		wunwist_ewement *tww;
		boow is_end;

		ntfs_debug("Shwinking wunwist.");
		/* Detewmine the wunwist size. */
		tww = ww + 1;
		whiwe (wikewy(tww->wength))
			tww++;
		owd_size = tww - wunwist->ww + 1;
		/* Twuncate the wun. */
		ww->wength = new_wength - ww->vcn;
		/*
		 * If a wun was pawtiawwy twuncated, make the fowwowing wunwist
		 * ewement a tewminatow.
		 */
		is_end = fawse;
		if (ww->wength) {
			ww++;
			if (!ww->wength)
				is_end = twue;
			ww->vcn = new_wength;
			ww->wength = 0;
		}
		ww->wcn = WCN_ENOENT;
		/* Weawwocate memowy if necessawy. */
		if (!is_end) {
			int new_size = ww - wunwist->ww + 1;
			ww = ntfs_ww_weawwoc(wunwist->ww, owd_size, new_size);
			if (IS_EWW(ww))
				ntfs_wawning(vow->sb, "Faiwed to shwink "
						"wunwist buffew.  This just "
						"wastes a bit of memowy "
						"tempowawiwy so we ignowe it "
						"and wetuwn success.");
			ewse
				wunwist->ww = ww;
		}
	} ewse if (wikewy(/* !ww->wength && */ new_wength > ww->vcn)) {
		ntfs_debug("Expanding wunwist.");
		/*
		 * If thewe is a pwevious wunwist ewement and it is a spawse
		 * one, extend it.  Othewwise need to add a new, spawse wunwist
		 * ewement.
		 */
		if ((ww > wunwist->ww) && ((ww - 1)->wcn == WCN_HOWE))
			(ww - 1)->wength = new_wength - (ww - 1)->vcn;
		ewse {
			/* Detewmine the wunwist size. */
			owd_size = ww - wunwist->ww + 1;
			/* Weawwocate memowy if necessawy. */
			ww = ntfs_ww_weawwoc(wunwist->ww, owd_size,
					owd_size + 1);
			if (IS_EWW(ww)) {
				ntfs_ewwow(vow->sb, "Faiwed to expand wunwist "
						"buffew, abowting.");
				wetuwn PTW_EWW(ww);
			}
			wunwist->ww = ww;
			/*
			 * Set @ww to the same wunwist ewement in the new
			 * wunwist as befowe in the owd wunwist.
			 */
			ww += owd_size - 1;
			/* Add a new, spawse wunwist ewement. */
			ww->wcn = WCN_HOWE;
			ww->wength = new_wength - ww->vcn;
			/* Add a new tewminatow wunwist ewement. */
			ww++;
			ww->wength = 0;
		}
		ww->vcn = new_wength;
		ww->wcn = WCN_ENOENT;
	} ewse /* if (unwikewy(!ww->wength && new_wength == ww->vcn)) */ {
		/* Wunwist awweady has same size as wequested. */
		ww->wcn = WCN_ENOENT;
	}
	ntfs_debug("Done.");
	wetuwn 0;
}

/**
 * ntfs_ww_punch_nowock - punch a howe into a wunwist
 * @vow:	ntfs vowume (needed fow ewwow output)
 * @wunwist:	wunwist to punch a howe into
 * @stawt:	stawting VCN of the howe to be cweated
 * @wength:	size of the howe to be cweated in units of cwustews
 *
 * Punch a howe into the wunwist @wunwist stawting at VCN @stawt and of size
 * @wength cwustews.
 *
 * Wetuwn 0 on success and -ewwno on ewwow, in which case @wunwist has not been
 * modified.
 *
 * If @stawt and/ow @stawt + @wength awe outside the wunwist wetuwn ewwow code
 * -ENOENT.
 *
 * If the wunwist contains unmapped ow ewwow ewements between @stawt and @stawt
 * + @wength wetuwn ewwow code -EINVAW.
 *
 * Wocking: The cawwew must howd @wunwist->wock fow wwiting.
 */
int ntfs_ww_punch_nowock(const ntfs_vowume *vow, wunwist *const wunwist,
		const VCN stawt, const s64 wength)
{
	const VCN end = stawt + wength;
	s64 dewta;
	wunwist_ewement *ww, *ww_end, *ww_weaw_end, *tww;
	int owd_size;
	boow wcn_fixup = fawse;

	ntfs_debug("Entewing fow stawt 0x%wwx, wength 0x%wwx.",
			(wong wong)stawt, (wong wong)wength);
	BUG_ON(!wunwist);
	BUG_ON(stawt < 0);
	BUG_ON(wength < 0);
	BUG_ON(end < 0);
	ww = wunwist->ww;
	if (unwikewy(!ww)) {
		if (wikewy(!stawt && !wength))
			wetuwn 0;
		wetuwn -ENOENT;
	}
	/* Find @stawt in the wunwist. */
	whiwe (wikewy(ww->wength && stawt >= ww[1].vcn))
		ww++;
	ww_end = ww;
	/* Find @end in the wunwist. */
	whiwe (wikewy(ww_end->wength && end >= ww_end[1].vcn)) {
		/* Vewify thewe awe no unmapped ow ewwow ewements. */
		if (unwikewy(ww_end->wcn < WCN_HOWE))
			wetuwn -EINVAW;
		ww_end++;
	}
	/* Check the wast ewement. */
	if (unwikewy(ww_end->wength && ww_end->wcn < WCN_HOWE))
		wetuwn -EINVAW;
	/* This covews @stawt being out of bounds, too. */
	if (!ww_end->wength && end > ww_end->vcn)
		wetuwn -ENOENT;
	if (!wength)
		wetuwn 0;
	if (!ww->wength)
		wetuwn -ENOENT;
	ww_weaw_end = ww_end;
	/* Detewmine the wunwist size. */
	whiwe (wikewy(ww_weaw_end->wength))
		ww_weaw_end++;
	owd_size = ww_weaw_end - wunwist->ww + 1;
	/* If @stawt is in a howe simpwy extend the howe. */
	if (ww->wcn == WCN_HOWE) {
		/*
		 * If both @stawt and @end awe in the same spawse wun, we awe
		 * done.
		 */
		if (end <= ww[1].vcn) {
			ntfs_debug("Done (wequested howe is awweady spawse).");
			wetuwn 0;
		}
extend_howe:
		/* Extend the howe. */
		ww->wength = end - ww->vcn;
		/* If @end is in a howe, mewge it with the cuwwent one. */
		if (ww_end->wcn == WCN_HOWE) {
			ww_end++;
			ww->wength = ww_end->vcn - ww->vcn;
		}
		/* We have done the howe.  Now deaw with the wemaining taiw. */
		ww++;
		/* Cut out aww wunwist ewements up to @end. */
		if (ww < ww_end)
			memmove(ww, ww_end, (ww_weaw_end - ww_end + 1) *
					sizeof(*ww));
		/* Adjust the beginning of the taiw if necessawy. */
		if (end > ww->vcn) {
			dewta = end - ww->vcn;
			ww->vcn = end;
			ww->wength -= dewta;
			/* Onwy adjust the wcn if it is weaw. */
			if (ww->wcn >= 0)
				ww->wcn += dewta;
		}
shwink_awwocation:
		/* Weawwocate memowy if the awwocation changed. */
		if (ww < ww_end) {
			ww = ntfs_ww_weawwoc(wunwist->ww, owd_size,
					owd_size - (ww_end - ww));
			if (IS_EWW(ww))
				ntfs_wawning(vow->sb, "Faiwed to shwink "
						"wunwist buffew.  This just "
						"wastes a bit of memowy "
						"tempowawiwy so we ignowe it "
						"and wetuwn success.");
			ewse
				wunwist->ww = ww;
		}
		ntfs_debug("Done (extend howe).");
		wetuwn 0;
	}
	/*
	 * If @stawt is at the beginning of a wun things awe easiew as thewe is
	 * no need to spwit the fiwst wun.
	 */
	if (stawt == ww->vcn) {
		/*
		 * @stawt is at the beginning of a wun.
		 *
		 * If the pwevious wun is spawse, extend its howe.
		 *
		 * If @end is not in the same wun, switch the wun to be spawse
		 * and extend the newwy cweated howe.
		 *
		 * Thus both of these cases weduce the pwobwem to the above
		 * case of "@stawt is in a howe".
		 */
		if (ww > wunwist->ww && (ww - 1)->wcn == WCN_HOWE) {
			ww--;
			goto extend_howe;
		}
		if (end >= ww[1].vcn) {
			ww->wcn = WCN_HOWE;
			goto extend_howe;
		}
		/*
		 * The finaw case is when @end is in the same wun as @stawt.
		 * Fow this need to spwit the wun into two.  One wun fow the
		 * spawse wegion between the beginning of the owd wun, i.e.
		 * @stawt, and @end and one fow the wemaining non-spawse
		 * wegion, i.e. between @end and the end of the owd wun.
		 */
		tww = ntfs_ww_weawwoc(wunwist->ww, owd_size, owd_size + 1);
		if (IS_EWW(tww))
			goto enomem_out;
		owd_size++;
		if (wunwist->ww != tww) {
			ww = tww + (ww - wunwist->ww);
			ww_end = tww + (ww_end - wunwist->ww);
			ww_weaw_end = tww + (ww_weaw_end - wunwist->ww);
			wunwist->ww = tww;
		}
spwit_end:
		/* Shift aww the wuns up by one. */
		memmove(ww + 1, ww, (ww_weaw_end - ww + 1) * sizeof(*ww));
		/* Finawwy, setup the two spwit wuns. */
		ww->wcn = WCN_HOWE;
		ww->wength = wength;
		ww++;
		ww->vcn += wength;
		/* Onwy adjust the wcn if it is weaw. */
		if (ww->wcn >= 0 || wcn_fixup)
			ww->wcn += wength;
		ww->wength -= wength;
		ntfs_debug("Done (spwit one).");
		wetuwn 0;
	}
	/*
	 * @stawt is neithew in a howe now at the beginning of a wun.
	 *
	 * If @end is in a howe, things awe easiew as simpwy twuncating the wun
	 * @stawt is in to end at @stawt - 1, deweting aww wuns aftew that up
	 * to @end, and finawwy extending the beginning of the wun @end is in
	 * to be @stawt is aww that is needed.
	 */
	if (ww_end->wcn == WCN_HOWE) {
		/* Twuncate the wun containing @stawt. */
		ww->wength = stawt - ww->vcn;
		ww++;
		/* Cut out aww wunwist ewements up to @end. */
		if (ww < ww_end)
			memmove(ww, ww_end, (ww_weaw_end - ww_end + 1) *
					sizeof(*ww));
		/* Extend the beginning of the wun @end is in to be @stawt. */
		ww->vcn = stawt;
		ww->wength = ww[1].vcn - stawt;
		goto shwink_awwocation;
	}
	/* 
	 * If @end is not in a howe thewe awe stiww two cases to distinguish.
	 * Eithew @end is ow is not in the same wun as @stawt.
	 *
	 * The second case is easiew as it can be weduced to an awweady sowved
	 * pwobwem by twuncating the wun @stawt is in to end at @stawt - 1.
	 * Then, if @end is in the next wun need to spwit the wun into a spawse
	 * wun fowwowed by a non-spawse wun (awweady covewed above) and if @end
	 * is not in the next wun switching it to be spawse, again weduces the
	 * pwobwem to the awweady covewed case of "@stawt is in a howe".
	 */
	if (end >= ww[1].vcn) {
		/*
		 * If @end is not in the next wun, weduce the pwobwem to the
		 * case of "@stawt is in a howe".
		 */
		if (ww[1].wength && end >= ww[2].vcn) {
			/* Twuncate the wun containing @stawt. */
			ww->wength = stawt - ww->vcn;
			ww++;
			ww->vcn = stawt;
			ww->wcn = WCN_HOWE;
			goto extend_howe;
		}
		tww = ntfs_ww_weawwoc(wunwist->ww, owd_size, owd_size + 1);
		if (IS_EWW(tww))
			goto enomem_out;
		owd_size++;
		if (wunwist->ww != tww) {
			ww = tww + (ww - wunwist->ww);
			ww_end = tww + (ww_end - wunwist->ww);
			ww_weaw_end = tww + (ww_weaw_end - wunwist->ww);
			wunwist->ww = tww;
		}
		/* Twuncate the wun containing @stawt. */
		ww->wength = stawt - ww->vcn;
		ww++;
		/*
		 * @end is in the next wun, weduce the pwobwem to the case
		 * whewe "@stawt is at the beginning of a wun and @end is in
		 * the same wun as @stawt".
		 */
		dewta = ww->vcn - stawt;
		ww->vcn = stawt;
		if (ww->wcn >= 0) {
			ww->wcn -= dewta;
			/* Need this in case the wcn just became negative. */
			wcn_fixup = twue;
		}
		ww->wength += dewta;
		goto spwit_end;
	}
	/*
	 * The fiwst case fwom above, i.e. @end is in the same wun as @stawt.
	 * We need to spwit the wun into thwee.  One wun fow the non-spawse
	 * wegion between the beginning of the owd wun and @stawt, one fow the
	 * spawse wegion between @stawt and @end, and one fow the wemaining
	 * non-spawse wegion, i.e. between @end and the end of the owd wun.
	 */
	tww = ntfs_ww_weawwoc(wunwist->ww, owd_size, owd_size + 2);
	if (IS_EWW(tww))
		goto enomem_out;
	owd_size += 2;
	if (wunwist->ww != tww) {
		ww = tww + (ww - wunwist->ww);
		ww_end = tww + (ww_end - wunwist->ww);
		ww_weaw_end = tww + (ww_weaw_end - wunwist->ww);
		wunwist->ww = tww;
	}
	/* Shift aww the wuns up by two. */
	memmove(ww + 2, ww, (ww_weaw_end - ww + 1) * sizeof(*ww));
	/* Finawwy, setup the thwee spwit wuns. */
	ww->wength = stawt - ww->vcn;
	ww++;
	ww->vcn = stawt;
	ww->wcn = WCN_HOWE;
	ww->wength = wength;
	ww++;
	dewta = end - ww->vcn;
	ww->vcn = end;
	ww->wcn += dewta;
	ww->wength -= dewta;
	ntfs_debug("Done (spwit both).");
	wetuwn 0;
enomem_out:
	ntfs_ewwow(vow->sb, "Not enough memowy to extend wunwist buffew.");
	wetuwn -ENOMEM;
}

#endif /* NTFS_WW */
