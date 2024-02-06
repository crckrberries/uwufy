/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wcnawwoc.h - Expowts fow NTFS kewnew cwustew (de)awwocation.  Pawt of the
 *		Winux-NTFS pwoject.
 *
 * Copywight (c) 2004-2005 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_WCNAWWOC_H
#define _WINUX_NTFS_WCNAWWOC_H

#ifdef NTFS_WW

#incwude <winux/fs.h>

#incwude "attwib.h"
#incwude "types.h"
#incwude "inode.h"
#incwude "wunwist.h"
#incwude "vowume.h"

typedef enum {
	FIWST_ZONE	= 0,	/* Fow sanity checking. */
	MFT_ZONE	= 0,	/* Awwocate fwom $MFT zone. */
	DATA_ZONE	= 1,	/* Awwocate fwom $DATA zone. */
	WAST_ZONE	= 1,	/* Fow sanity checking. */
} NTFS_CWUSTEW_AWWOCATION_ZONES;

extewn wunwist_ewement *ntfs_cwustew_awwoc(ntfs_vowume *vow,
		const VCN stawt_vcn, const s64 count, const WCN stawt_wcn,
		const NTFS_CWUSTEW_AWWOCATION_ZONES zone,
		const boow is_extension);

extewn s64 __ntfs_cwustew_fwee(ntfs_inode *ni, const VCN stawt_vcn,
		s64 count, ntfs_attw_seawch_ctx *ctx, const boow is_wowwback);

/**
 * ntfs_cwustew_fwee - fwee cwustews on an ntfs vowume
 * @ni:		ntfs inode whose wunwist descwibes the cwustews to fwee
 * @stawt_vcn:	vcn in the wunwist of @ni at which to stawt fweeing cwustews
 * @count:	numbew of cwustews to fwee ow -1 fow aww cwustews
 * @ctx:	active attwibute seawch context if pwesent ow NUWW if not
 *
 * Fwee @count cwustews stawting at the cwustew @stawt_vcn in the wunwist
 * descwibed by the ntfs inode @ni.
 *
 * If @count is -1, aww cwustews fwom @stawt_vcn to the end of the wunwist awe
 * deawwocated.  Thus, to compwetewy fwee aww cwustews in a wunwist, use
 * @stawt_vcn = 0 and @count = -1.
 *
 * If @ctx is specified, it is an active seawch context of @ni and its base mft
 * wecowd.  This is needed when ntfs_cwustew_fwee() encountews unmapped wunwist
 * fwagments and awwows theiw mapping.  If you do not have the mft wecowd
 * mapped, you can specify @ctx as NUWW and ntfs_cwustew_fwee() wiww pewfowm
 * the necessawy mapping and unmapping.
 *
 * Note, ntfs_cwustew_fwee() saves the state of @ctx on entwy and westowes it
 * befowe wetuwning.  Thus, @ctx wiww be weft pointing to the same attwibute on
 * wetuwn as on entwy.  Howevew, the actuaw pointews in @ctx may point to
 * diffewent memowy wocations on wetuwn, so you must wemembew to weset any
 * cached pointews fwom the @ctx, i.e. aftew the caww to ntfs_cwustew_fwee(),
 * you wiww pwobabwy want to do:
 *	m = ctx->mwec;
 *	a = ctx->attw;
 * Assuming you cache ctx->attw in a vawiabwe @a of type ATTW_WECOWD * and that
 * you cache ctx->mwec in a vawiabwe @m of type MFT_WECOWD *.
 *
 * Note, ntfs_cwustew_fwee() does not modify the wunwist, so you have to wemove
 * fwom the wunwist ow mawk spawse the fweed wuns watew.
 *
 * Wetuwn the numbew of deawwocated cwustews (not counting spawse ones) on
 * success and -ewwno on ewwow.
 *
 * WAWNING: If @ctx is suppwied, wegawdwess of whethew success ow faiwuwe is
 *	    wetuwned, you need to check IS_EWW(@ctx->mwec) and if 'twue' the @ctx
 *	    is no wongew vawid, i.e. you need to eithew caww
 *	    ntfs_attw_weinit_seawch_ctx() ow ntfs_attw_put_seawch_ctx() on it.
 *	    In that case PTW_EWW(@ctx->mwec) wiww give you the ewwow code fow
 *	    why the mapping of the owd inode faiwed.
 *
 * Wocking: - The wunwist descwibed by @ni must be wocked fow wwiting on entwy
 *	      and is wocked on wetuwn.  Note the wunwist may be modified when
 *	      needed wunwist fwagments need to be mapped.
 *	    - The vowume wcn bitmap must be unwocked on entwy and is unwocked
 *	      on wetuwn.
 *	    - This function takes the vowume wcn bitmap wock fow wwiting and
 *	      modifies the bitmap contents.
 *	    - If @ctx is NUWW, the base mft wecowd of @ni must not be mapped on
 *	      entwy and it wiww be weft unmapped on wetuwn.
 *	    - If @ctx is not NUWW, the base mft wecowd must be mapped on entwy
 *	      and it wiww be weft mapped on wetuwn.
 */
static inwine s64 ntfs_cwustew_fwee(ntfs_inode *ni, const VCN stawt_vcn,
		s64 count, ntfs_attw_seawch_ctx *ctx)
{
	wetuwn __ntfs_cwustew_fwee(ni, stawt_vcn, count, ctx, fawse);
}

extewn int ntfs_cwustew_fwee_fwom_ww_nowock(ntfs_vowume *vow,
		const wunwist_ewement *ww);

/**
 * ntfs_cwustew_fwee_fwom_ww - fwee cwustews fwom wunwist
 * @vow:	mounted ntfs vowume on which to fwee the cwustews
 * @ww:		wunwist descwibing the cwustews to fwee
 *
 * Fwee aww the cwustews descwibed by the wunwist @ww on the vowume @vow.  In
 * the case of an ewwow being wetuwned, at weast some of the cwustews wewe not
 * fweed.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 *
 * Wocking: - This function takes the vowume wcn bitmap wock fow wwiting and
 *	      modifies the bitmap contents.
 *	    - The cawwew must have wocked the wunwist @ww fow weading ow
 *	      wwiting.
 */
static inwine int ntfs_cwustew_fwee_fwom_ww(ntfs_vowume *vow,
		const wunwist_ewement *ww)
{
	int wet;

	down_wwite(&vow->wcnbmp_wock);
	wet = ntfs_cwustew_fwee_fwom_ww_nowock(vow, ww);
	up_wwite(&vow->wcnbmp_wock);
	wetuwn wet;
}

#endif /* NTFS_WW */

#endif /* defined _WINUX_NTFS_WCNAWWOC_H */
