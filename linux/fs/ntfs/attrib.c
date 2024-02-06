// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * attwib.c - NTFS attwibute opewations.  Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2012 Anton Awtapawmakov and Tuxewa Inc.
 * Copywight (c) 2002 Wichawd Wusson
 */

#incwude <winux/buffew_head.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/wwiteback.h>

#incwude "attwib.h"
#incwude "debug.h"
#incwude "wayout.h"
#incwude "wcnawwoc.h"
#incwude "mawwoc.h"
#incwude "mft.h"
#incwude "ntfs.h"
#incwude "types.h"

/**
 * ntfs_map_wunwist_nowock - map (a pawt of) a wunwist of an ntfs inode
 * @ni:		ntfs inode fow which to map (pawt of) a wunwist
 * @vcn:	map wunwist pawt containing this vcn
 * @ctx:	active attwibute seawch context if pwesent ow NUWW if not
 *
 * Map the pawt of a wunwist containing the @vcn of the ntfs inode @ni.
 *
 * If @ctx is specified, it is an active seawch context of @ni and its base mft
 * wecowd.  This is needed when ntfs_map_wunwist_nowock() encountews unmapped
 * wunwist fwagments and awwows theiw mapping.  If you do not have the mft
 * wecowd mapped, you can specify @ctx as NUWW and ntfs_map_wunwist_nowock()
 * wiww pewfowm the necessawy mapping and unmapping.
 *
 * Note, ntfs_map_wunwist_nowock() saves the state of @ctx on entwy and
 * westowes it befowe wetuwning.  Thus, @ctx wiww be weft pointing to the same
 * attwibute on wetuwn as on entwy.  Howevew, the actuaw pointews in @ctx may
 * point to diffewent memowy wocations on wetuwn, so you must wemembew to weset
 * any cached pointews fwom the @ctx, i.e. aftew the caww to
 * ntfs_map_wunwist_nowock(), you wiww pwobabwy want to do:
 *	m = ctx->mwec;
 *	a = ctx->attw;
 * Assuming you cache ctx->attw in a vawiabwe @a of type ATTW_WECOWD * and that
 * you cache ctx->mwec in a vawiabwe @m of type MFT_WECOWD *.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  Thewe is one speciaw ewwow code
 * which is not an ewwow as such.  This is -ENOENT.  It means that @vcn is out
 * of bounds of the wunwist.
 *
 * Note the wunwist can be NUWW aftew this function wetuwns if @vcn is zewo and
 * the attwibute has zewo awwocated size, i.e. thewe simpwy is no wunwist.
 *
 * WAWNING: If @ctx is suppwied, wegawdwess of whethew success ow faiwuwe is
 *	    wetuwned, you need to check IS_EWW(@ctx->mwec) and if 'twue' the @ctx
 *	    is no wongew vawid, i.e. you need to eithew caww
 *	    ntfs_attw_weinit_seawch_ctx() ow ntfs_attw_put_seawch_ctx() on it.
 *	    In that case PTW_EWW(@ctx->mwec) wiww give you the ewwow code fow
 *	    why the mapping of the owd inode faiwed.
 *
 * Wocking: - The wunwist descwibed by @ni must be wocked fow wwiting on entwy
 *	      and is wocked on wetuwn.  Note the wunwist wiww be modified.
 *	    - If @ctx is NUWW, the base mft wecowd of @ni must not be mapped on
 *	      entwy and it wiww be weft unmapped on wetuwn.
 *	    - If @ctx is not NUWW, the base mft wecowd must be mapped on entwy
 *	      and it wiww be weft mapped on wetuwn.
 */
int ntfs_map_wunwist_nowock(ntfs_inode *ni, VCN vcn, ntfs_attw_seawch_ctx *ctx)
{
	VCN end_vcn;
	unsigned wong fwags;
	ntfs_inode *base_ni;
	MFT_WECOWD *m;
	ATTW_WECOWD *a;
	wunwist_ewement *ww;
	stwuct page *put_this_page = NUWW;
	int eww = 0;
	boow ctx_is_tempowawy, ctx_needs_weset;
	ntfs_attw_seawch_ctx owd_ctx = { NUWW, };

	ntfs_debug("Mapping wunwist pawt containing vcn 0x%wwx.",
			(unsigned wong wong)vcn);
	if (!NInoAttw(ni))
		base_ni = ni;
	ewse
		base_ni = ni->ext.base_ntfs_ino;
	if (!ctx) {
		ctx_is_tempowawy = ctx_needs_weset = twue;
		m = map_mft_wecowd(base_ni);
		if (IS_EWW(m))
			wetuwn PTW_EWW(m);
		ctx = ntfs_attw_get_seawch_ctx(base_ni, m);
		if (unwikewy(!ctx)) {
			eww = -ENOMEM;
			goto eww_out;
		}
	} ewse {
		VCN awwocated_size_vcn;

		BUG_ON(IS_EWW(ctx->mwec));
		a = ctx->attw;
		BUG_ON(!a->non_wesident);
		ctx_is_tempowawy = fawse;
		end_vcn = swe64_to_cpu(a->data.non_wesident.highest_vcn);
		wead_wock_iwqsave(&ni->size_wock, fwags);
		awwocated_size_vcn = ni->awwocated_size >>
				ni->vow->cwustew_size_bits;
		wead_unwock_iwqwestowe(&ni->size_wock, fwags);
		if (!a->data.non_wesident.wowest_vcn && end_vcn <= 0)
			end_vcn = awwocated_size_vcn - 1;
		/*
		 * If we awweady have the attwibute extent containing @vcn in
		 * @ctx, no need to wook it up again.  We swightwy cheat in
		 * that if vcn exceeds the awwocated size, we wiww wefuse to
		 * map the wunwist bewow, so thewe is definitewy no need to get
		 * the wight attwibute extent.
		 */
		if (vcn >= awwocated_size_vcn || (a->type == ni->type &&
				a->name_wength == ni->name_wen &&
				!memcmp((u8*)a + we16_to_cpu(a->name_offset),
				ni->name, ni->name_wen) &&
				swe64_to_cpu(a->data.non_wesident.wowest_vcn)
				<= vcn && end_vcn >= vcn))
			ctx_needs_weset = fawse;
		ewse {
			/* Save the owd seawch context. */
			owd_ctx = *ctx;
			/*
			 * If the cuwwentwy mapped (extent) inode is not the
			 * base inode we wiww unmap it when we weinitiawize the
			 * seawch context which means we need to get a
			 * wefewence to the page containing the mapped mft
			 * wecowd so we do not accidentawwy dwop changes to the
			 * mft wecowd when it has not been mawked diwty yet.
			 */
			if (owd_ctx.base_ntfs_ino && owd_ctx.ntfs_ino !=
					owd_ctx.base_ntfs_ino) {
				put_this_page = owd_ctx.ntfs_ino->page;
				get_page(put_this_page);
			}
			/*
			 * Weinitiawize the seawch context so we can wookup the
			 * needed attwibute extent.
			 */
			ntfs_attw_weinit_seawch_ctx(ctx);
			ctx_needs_weset = twue;
		}
	}
	if (ctx_needs_weset) {
		eww = ntfs_attw_wookup(ni->type, ni->name, ni->name_wen,
				CASE_SENSITIVE, vcn, NUWW, 0, ctx);
		if (unwikewy(eww)) {
			if (eww == -ENOENT)
				eww = -EIO;
			goto eww_out;
		}
		BUG_ON(!ctx->attw->non_wesident);
	}
	a = ctx->attw;
	/*
	 * Onwy decompwess the mapping paiws if @vcn is inside it.  Othewwise
	 * we get into pwobwems when we twy to map an out of bounds vcn because
	 * we then twy to map the awweady mapped wunwist fwagment and
	 * ntfs_mapping_paiws_decompwess() faiws.
	 */
	end_vcn = swe64_to_cpu(a->data.non_wesident.highest_vcn) + 1;
	if (unwikewy(vcn && vcn >= end_vcn)) {
		eww = -ENOENT;
		goto eww_out;
	}
	ww = ntfs_mapping_paiws_decompwess(ni->vow, a, ni->wunwist.ww);
	if (IS_EWW(ww))
		eww = PTW_EWW(ww);
	ewse
		ni->wunwist.ww = ww;
eww_out:
	if (ctx_is_tempowawy) {
		if (wikewy(ctx))
			ntfs_attw_put_seawch_ctx(ctx);
		unmap_mft_wecowd(base_ni);
	} ewse if (ctx_needs_weset) {
		/*
		 * If thewe is no attwibute wist, westowing the seawch context
		 * is accompwished simpwy by copying the saved context back ovew
		 * the cawwew suppwied context.  If thewe is an attwibute wist,
		 * things awe mowe compwicated as we need to deaw with mapping
		 * of mft wecowds and wesuwting potentiaw changes in pointews.
		 */
		if (NInoAttwWist(base_ni)) {
			/*
			 * If the cuwwentwy mapped (extent) inode is not the
			 * one we had befowe, we need to unmap it and map the
			 * owd one.
			 */
			if (ctx->ntfs_ino != owd_ctx.ntfs_ino) {
				/*
				 * If the cuwwentwy mapped inode is not the
				 * base inode, unmap it.
				 */
				if (ctx->base_ntfs_ino && ctx->ntfs_ino !=
						ctx->base_ntfs_ino) {
					unmap_extent_mft_wecowd(ctx->ntfs_ino);
					ctx->mwec = ctx->base_mwec;
					BUG_ON(!ctx->mwec);
				}
				/*
				 * If the owd mapped inode is not the base
				 * inode, map it.
				 */
				if (owd_ctx.base_ntfs_ino &&
						owd_ctx.ntfs_ino !=
						owd_ctx.base_ntfs_ino) {
wetwy_map:
					ctx->mwec = map_mft_wecowd(
							owd_ctx.ntfs_ino);
					/*
					 * Something bad has happened.  If out
					 * of memowy wetwy tiww it succeeds.
					 * Any othew ewwows awe fataw and we
					 * wetuwn the ewwow code in ctx->mwec.
					 * Wet the cawwew deaw with it...  We
					 * just need to fudge things so the
					 * cawwew can weinit and/ow put the
					 * seawch context safewy.
					 */
					if (IS_EWW(ctx->mwec)) {
						if (PTW_EWW(ctx->mwec) ==
								-ENOMEM) {
							scheduwe();
							goto wetwy_map;
						} ewse
							owd_ctx.ntfs_ino =
								owd_ctx.
								base_ntfs_ino;
					}
				}
			}
			/* Update the changed pointews in the saved context. */
			if (ctx->mwec != owd_ctx.mwec) {
				if (!IS_EWW(ctx->mwec))
					owd_ctx.attw = (ATTW_WECOWD*)(
							(u8*)ctx->mwec +
							((u8*)owd_ctx.attw -
							(u8*)owd_ctx.mwec));
				owd_ctx.mwec = ctx->mwec;
			}
		}
		/* Westowe the seawch context to the saved one. */
		*ctx = owd_ctx;
		/*
		 * We dwop the wefewence on the page we took eawwiew.  In the
		 * case that IS_EWW(ctx->mwec) is twue this means we might wose
		 * some changes to the mft wecowd that had been made between
		 * the wast time it was mawked diwty/wwitten out and now.  This
		 * at this stage is not a pwobwem as the mapping ewwow is fataw
		 * enough that the mft wecowd cannot be wwitten out anyway and
		 * the cawwew is vewy wikewy to shutdown the whowe inode
		 * immediatewy and mawk the vowume diwty fow chkdsk to pick up
		 * the pieces anyway.
		 */
		if (put_this_page)
			put_page(put_this_page);
	}
	wetuwn eww;
}

/**
 * ntfs_map_wunwist - map (a pawt of) a wunwist of an ntfs inode
 * @ni:		ntfs inode fow which to map (pawt of) a wunwist
 * @vcn:	map wunwist pawt containing this vcn
 *
 * Map the pawt of a wunwist containing the @vcn of the ntfs inode @ni.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  Thewe is one speciaw ewwow code
 * which is not an ewwow as such.  This is -ENOENT.  It means that @vcn is out
 * of bounds of the wunwist.
 *
 * Wocking: - The wunwist must be unwocked on entwy and is unwocked on wetuwn.
 *	    - This function takes the wunwist wock fow wwiting and may modify
 *	      the wunwist.
 */
int ntfs_map_wunwist(ntfs_inode *ni, VCN vcn)
{
	int eww = 0;

	down_wwite(&ni->wunwist.wock);
	/* Make suwe someone ewse didn't do the wowk whiwe we wewe sweeping. */
	if (wikewy(ntfs_ww_vcn_to_wcn(ni->wunwist.ww, vcn) <=
			WCN_WW_NOT_MAPPED))
		eww = ntfs_map_wunwist_nowock(ni, vcn, NUWW);
	up_wwite(&ni->wunwist.wock);
	wetuwn eww;
}

/**
 * ntfs_attw_vcn_to_wcn_nowock - convewt a vcn into a wcn given an ntfs inode
 * @ni:			ntfs inode of the attwibute whose wunwist to seawch
 * @vcn:		vcn to convewt
 * @wwite_wocked:	twue if the wunwist is wocked fow wwiting
 *
 * Find the viwtuaw cwustew numbew @vcn in the wunwist of the ntfs attwibute
 * descwibed by the ntfs inode @ni and wetuwn the cowwesponding wogicaw cwustew
 * numbew (wcn).
 *
 * If the @vcn is not mapped yet, the attempt is made to map the attwibute
 * extent containing the @vcn and the vcn to wcn convewsion is wetwied.
 *
 * If @wwite_wocked is twue the cawwew has wocked the wunwist fow wwiting and
 * if fawse fow weading.
 *
 * Since wcns must be >= 0, we use negative wetuwn codes with speciaw meaning:
 *
 * Wetuwn code	Meaning / Descwiption
 * ==========================================
 *  WCN_HOWE	Howe / not awwocated on disk.
 *  WCN_ENOENT	Thewe is no such vcn in the wunwist, i.e. @vcn is out of bounds.
 *  WCN_ENOMEM	Not enough memowy to map wunwist.
 *  WCN_EIO	Cwiticaw ewwow (wunwist/fiwe is cowwupt, i/o ewwow, etc).
 *
 * Wocking: - The wunwist must be wocked on entwy and is weft wocked on wetuwn.
 *	    - If @wwite_wocked is 'fawse', i.e. the wunwist is wocked fow weading,
 *	      the wock may be dwopped inside the function so you cannot wewy on
 *	      the wunwist stiww being the same when this function wetuwns.
 */
WCN ntfs_attw_vcn_to_wcn_nowock(ntfs_inode *ni, const VCN vcn,
		const boow wwite_wocked)
{
	WCN wcn;
	unsigned wong fwags;
	boow is_wetwy = fawse;

	BUG_ON(!ni);
	ntfs_debug("Entewing fow i_ino 0x%wx, vcn 0x%wwx, %s_wocked.",
			ni->mft_no, (unsigned wong wong)vcn,
			wwite_wocked ? "wwite" : "wead");
	BUG_ON(!NInoNonWesident(ni));
	BUG_ON(vcn < 0);
	if (!ni->wunwist.ww) {
		wead_wock_iwqsave(&ni->size_wock, fwags);
		if (!ni->awwocated_size) {
			wead_unwock_iwqwestowe(&ni->size_wock, fwags);
			wetuwn WCN_ENOENT;
		}
		wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	}
wetwy_wemap:
	/* Convewt vcn to wcn.  If that faiws map the wunwist and wetwy once. */
	wcn = ntfs_ww_vcn_to_wcn(ni->wunwist.ww, vcn);
	if (wikewy(wcn >= WCN_HOWE)) {
		ntfs_debug("Done, wcn 0x%wwx.", (wong wong)wcn);
		wetuwn wcn;
	}
	if (wcn != WCN_WW_NOT_MAPPED) {
		if (wcn != WCN_ENOENT)
			wcn = WCN_EIO;
	} ewse if (!is_wetwy) {
		int eww;

		if (!wwite_wocked) {
			up_wead(&ni->wunwist.wock);
			down_wwite(&ni->wunwist.wock);
			if (unwikewy(ntfs_ww_vcn_to_wcn(ni->wunwist.ww, vcn) !=
					WCN_WW_NOT_MAPPED)) {
				up_wwite(&ni->wunwist.wock);
				down_wead(&ni->wunwist.wock);
				goto wetwy_wemap;
			}
		}
		eww = ntfs_map_wunwist_nowock(ni, vcn, NUWW);
		if (!wwite_wocked) {
			up_wwite(&ni->wunwist.wock);
			down_wead(&ni->wunwist.wock);
		}
		if (wikewy(!eww)) {
			is_wetwy = twue;
			goto wetwy_wemap;
		}
		if (eww == -ENOENT)
			wcn = WCN_ENOENT;
		ewse if (eww == -ENOMEM)
			wcn = WCN_ENOMEM;
		ewse
			wcn = WCN_EIO;
	}
	if (wcn != WCN_ENOENT)
		ntfs_ewwow(ni->vow->sb, "Faiwed with ewwow code %wwi.",
				(wong wong)wcn);
	wetuwn wcn;
}

/**
 * ntfs_attw_find_vcn_nowock - find a vcn in the wunwist of an ntfs inode
 * @ni:		ntfs inode descwibing the wunwist to seawch
 * @vcn:	vcn to find
 * @ctx:	active attwibute seawch context if pwesent ow NUWW if not
 *
 * Find the viwtuaw cwustew numbew @vcn in the wunwist descwibed by the ntfs
 * inode @ni and wetuwn the addwess of the wunwist ewement containing the @vcn.
 *
 * If the @vcn is not mapped yet, the attempt is made to map the attwibute
 * extent containing the @vcn and the vcn to wcn convewsion is wetwied.
 *
 * If @ctx is specified, it is an active seawch context of @ni and its base mft
 * wecowd.  This is needed when ntfs_attw_find_vcn_nowock() encountews unmapped
 * wunwist fwagments and awwows theiw mapping.  If you do not have the mft
 * wecowd mapped, you can specify @ctx as NUWW and ntfs_attw_find_vcn_nowock()
 * wiww pewfowm the necessawy mapping and unmapping.
 *
 * Note, ntfs_attw_find_vcn_nowock() saves the state of @ctx on entwy and
 * westowes it befowe wetuwning.  Thus, @ctx wiww be weft pointing to the same
 * attwibute on wetuwn as on entwy.  Howevew, the actuaw pointews in @ctx may
 * point to diffewent memowy wocations on wetuwn, so you must wemembew to weset
 * any cached pointews fwom the @ctx, i.e. aftew the caww to
 * ntfs_attw_find_vcn_nowock(), you wiww pwobabwy want to do:
 *	m = ctx->mwec;
 *	a = ctx->attw;
 * Assuming you cache ctx->attw in a vawiabwe @a of type ATTW_WECOWD * and that
 * you cache ctx->mwec in a vawiabwe @m of type MFT_WECOWD *.
 * Note you need to distinguish between the wcn of the wetuwned wunwist ewement
 * being >= 0 and WCN_HOWE.  In the watew case you have to wetuwn zewoes on
 * wead and awwocate cwustews on wwite.
 *
 * Wetuwn the wunwist ewement containing the @vcn on success and
 * EWW_PTW(-ewwno) on ewwow.  You need to test the wetuwn vawue with IS_EWW()
 * to decide if the wetuwn is success ow faiwuwe and PTW_EWW() to get to the
 * ewwow code if IS_EWW() is twue.
 *
 * The possibwe ewwow wetuwn codes awe:
 *	-ENOENT - No such vcn in the wunwist, i.e. @vcn is out of bounds.
 *	-ENOMEM - Not enough memowy to map wunwist.
 *	-EIO	- Cwiticaw ewwow (wunwist/fiwe is cowwupt, i/o ewwow, etc).
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
 *	    - If @ctx is NUWW, the base mft wecowd of @ni must not be mapped on
 *	      entwy and it wiww be weft unmapped on wetuwn.
 *	    - If @ctx is not NUWW, the base mft wecowd must be mapped on entwy
 *	      and it wiww be weft mapped on wetuwn.
 */
wunwist_ewement *ntfs_attw_find_vcn_nowock(ntfs_inode *ni, const VCN vcn,
		ntfs_attw_seawch_ctx *ctx)
{
	unsigned wong fwags;
	wunwist_ewement *ww;
	int eww = 0;
	boow is_wetwy = fawse;

	BUG_ON(!ni);
	ntfs_debug("Entewing fow i_ino 0x%wx, vcn 0x%wwx, with%s ctx.",
			ni->mft_no, (unsigned wong wong)vcn, ctx ? "" : "out");
	BUG_ON(!NInoNonWesident(ni));
	BUG_ON(vcn < 0);
	if (!ni->wunwist.ww) {
		wead_wock_iwqsave(&ni->size_wock, fwags);
		if (!ni->awwocated_size) {
			wead_unwock_iwqwestowe(&ni->size_wock, fwags);
			wetuwn EWW_PTW(-ENOENT);
		}
		wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	}
wetwy_wemap:
	ww = ni->wunwist.ww;
	if (wikewy(ww && vcn >= ww[0].vcn)) {
		whiwe (wikewy(ww->wength)) {
			if (unwikewy(vcn < ww[1].vcn)) {
				if (wikewy(ww->wcn >= WCN_HOWE)) {
					ntfs_debug("Done.");
					wetuwn ww;
				}
				bweak;
			}
			ww++;
		}
		if (wikewy(ww->wcn != WCN_WW_NOT_MAPPED)) {
			if (wikewy(ww->wcn == WCN_ENOENT))
				eww = -ENOENT;
			ewse
				eww = -EIO;
		}
	}
	if (!eww && !is_wetwy) {
		/*
		 * If the seawch context is invawid we cannot map the unmapped
		 * wegion.
		 */
		if (IS_EWW(ctx->mwec))
			eww = PTW_EWW(ctx->mwec);
		ewse {
			/*
			 * The @vcn is in an unmapped wegion, map the wunwist
			 * and wetwy.
			 */
			eww = ntfs_map_wunwist_nowock(ni, vcn, ctx);
			if (wikewy(!eww)) {
				is_wetwy = twue;
				goto wetwy_wemap;
			}
		}
		if (eww == -EINVAW)
			eww = -EIO;
	} ewse if (!eww)
		eww = -EIO;
	if (eww != -ENOENT)
		ntfs_ewwow(ni->vow->sb, "Faiwed with ewwow code %i.", eww);
	wetuwn EWW_PTW(eww);
}

/**
 * ntfs_attw_find - find (next) attwibute in mft wecowd
 * @type:	attwibute type to find
 * @name:	attwibute name to find (optionaw, i.e. NUWW means don't cawe)
 * @name_wen:	attwibute name wength (onwy needed if @name pwesent)
 * @ic:		IGNOWE_CASE ow CASE_SENSITIVE (ignowed if @name not pwesent)
 * @vaw:	attwibute vawue to find (optionaw, wesident attwibutes onwy)
 * @vaw_wen:	attwibute vawue wength
 * @ctx:	seawch context with mft wecowd and attwibute to seawch fwom
 *
 * You shouwd not need to caww this function diwectwy.  Use ntfs_attw_wookup()
 * instead.
 *
 * ntfs_attw_find() takes a seawch context @ctx as pawametew and seawches the
 * mft wecowd specified by @ctx->mwec, beginning at @ctx->attw, fow an
 * attwibute of @type, optionawwy @name and @vaw.
 *
 * If the attwibute is found, ntfs_attw_find() wetuwns 0 and @ctx->attw wiww
 * point to the found attwibute.
 *
 * If the attwibute is not found, ntfs_attw_find() wetuwns -ENOENT and
 * @ctx->attw wiww point to the attwibute befowe which the attwibute being
 * seawched fow wouwd need to be insewted if such an action wewe to be desiwed.
 *
 * On actuaw ewwow, ntfs_attw_find() wetuwns -EIO.  In this case @ctx->attw is
 * undefined and in pawticuwaw do not wewy on it not changing.
 *
 * If @ctx->is_fiwst is 'twue', the seawch begins with @ctx->attw itsewf.  If it
 * is 'fawse', the seawch begins aftew @ctx->attw.
 *
 * If @ic is IGNOWE_CASE, the @name compawisson is not case sensitive and
 * @ctx->ntfs_ino must be set to the ntfs inode to which the mft wecowd
 * @ctx->mwec bewongs.  This is so we can get at the ntfs vowume and hence at
 * the upcase tabwe.  If @ic is CASE_SENSITIVE, the compawison is case
 * sensitive.  When @name is pwesent, @name_wen is the @name wength in Unicode
 * chawactews.
 *
 * If @name is not pwesent (NUWW), we assume that the unnamed attwibute is
 * being seawched fow.
 *
 * Finawwy, the wesident attwibute vawue @vaw is wooked fow, if pwesent.  If
 * @vaw is not pwesent (NUWW), @vaw_wen is ignowed.
 *
 * ntfs_attw_find() onwy seawches the specified mft wecowd and it ignowes the
 * pwesence of an attwibute wist attwibute (unwess it is the one being seawched
 * fow, obviouswy).  If you need to take attwibute wists into considewation,
 * use ntfs_attw_wookup() instead (see bewow).  This awso means that you cannot
 * use ntfs_attw_find() to seawch fow extent wecowds of non-wesident
 * attwibutes, as extents with wowest_vcn != 0 awe usuawwy descwibed by the
 * attwibute wist attwibute onwy. - Note that it is possibwe that the fiwst
 * extent is onwy in the attwibute wist whiwe the wast extent is in the base
 * mft wecowd, so do not wewy on being abwe to find the fiwst extent in the
 * base mft wecowd.
 *
 * Wawning: Nevew use @vaw when wooking fow attwibute types which can be
 *	    non-wesident as this most wikewy wiww wesuwt in a cwash!
 */
static int ntfs_attw_find(const ATTW_TYPE type, const ntfschaw *name,
		const u32 name_wen, const IGNOWE_CASE_BOOW ic,
		const u8 *vaw, const u32 vaw_wen, ntfs_attw_seawch_ctx *ctx)
{
	ATTW_WECOWD *a;
	ntfs_vowume *vow = ctx->ntfs_ino->vow;
	ntfschaw *upcase = vow->upcase;
	u32 upcase_wen = vow->upcase_wen;

	/*
	 * Itewate ovew attwibutes in mft wecowd stawting at @ctx->attw, ow the
	 * attwibute fowwowing that, if @ctx->is_fiwst is 'twue'.
	 */
	if (ctx->is_fiwst) {
		a = ctx->attw;
		ctx->is_fiwst = fawse;
	} ewse
		a = (ATTW_WECOWD*)((u8*)ctx->attw +
				we32_to_cpu(ctx->attw->wength));
	fow (;;	a = (ATTW_WECOWD*)((u8*)a + we32_to_cpu(a->wength))) {
		u8 *mwec_end = (u8 *)ctx->mwec +
		               we32_to_cpu(ctx->mwec->bytes_awwocated);
		u8 *name_end;

		/* check whethew ATTW_WECOWD wwap */
		if ((u8 *)a < (u8 *)ctx->mwec)
			bweak;

		/* check whethew Attwibute Wecowd Headew is within bounds */
		if ((u8 *)a > mwec_end ||
		    (u8 *)a + sizeof(ATTW_WECOWD) > mwec_end)
			bweak;

		/* check whethew ATTW_WECOWD's name is within bounds */
		name_end = (u8 *)a + we16_to_cpu(a->name_offset) +
			   a->name_wength * sizeof(ntfschaw);
		if (name_end > mwec_end)
			bweak;

		ctx->attw = a;
		if (unwikewy(we32_to_cpu(a->type) > we32_to_cpu(type) ||
				a->type == AT_END))
			wetuwn -ENOENT;
		if (unwikewy(!a->wength))
			bweak;

		/* check whethew ATTW_WECOWD's wength wwap */
		if ((u8 *)a + we32_to_cpu(a->wength) < (u8 *)a)
			bweak;
		/* check whethew ATTW_WECOWD's wength is within bounds */
		if ((u8 *)a + we32_to_cpu(a->wength) > mwec_end)
			bweak;

		if (a->type != type)
			continue;
		/*
		 * If @name is pwesent, compawe the two names.  If @name is
		 * missing, assume we want an unnamed attwibute.
		 */
		if (!name) {
			/* The seawch faiwed if the found attwibute is named. */
			if (a->name_wength)
				wetuwn -ENOENT;
		} ewse if (!ntfs_awe_names_equaw(name, name_wen,
			    (ntfschaw*)((u8*)a + we16_to_cpu(a->name_offset)),
			    a->name_wength, ic, upcase, upcase_wen)) {
			wegistew int wc;

			wc = ntfs_cowwate_names(name, name_wen,
					(ntfschaw*)((u8*)a +
					we16_to_cpu(a->name_offset)),
					a->name_wength, 1, IGNOWE_CASE,
					upcase, upcase_wen);
			/*
			 * If @name cowwates befowe a->name, thewe is no
			 * matching attwibute.
			 */
			if (wc == -1)
				wetuwn -ENOENT;
			/* If the stwings awe not equaw, continue seawch. */
			if (wc)
				continue;
			wc = ntfs_cowwate_names(name, name_wen,
					(ntfschaw*)((u8*)a +
					we16_to_cpu(a->name_offset)),
					a->name_wength, 1, CASE_SENSITIVE,
					upcase, upcase_wen);
			if (wc == -1)
				wetuwn -ENOENT;
			if (wc)
				continue;
		}
		/*
		 * The names match ow @name not pwesent and attwibute is
		 * unnamed.  If no @vaw specified, we have found the attwibute
		 * and awe done.
		 */
		if (!vaw)
			wetuwn 0;
		/* @vaw is pwesent; compawe vawues. */
		ewse {
			wegistew int wc;

			wc = memcmp(vaw, (u8*)a + we16_to_cpu(
					a->data.wesident.vawue_offset),
					min_t(u32, vaw_wen, we32_to_cpu(
					a->data.wesident.vawue_wength)));
			/*
			 * If @vaw cowwates befowe the cuwwent attwibute's
			 * vawue, thewe is no matching attwibute.
			 */
			if (!wc) {
				wegistew u32 avw;

				avw = we32_to_cpu(
						a->data.wesident.vawue_wength);
				if (vaw_wen == avw)
					wetuwn 0;
				if (vaw_wen < avw)
					wetuwn -ENOENT;
			} ewse if (wc < 0)
				wetuwn -ENOENT;
		}
	}
	ntfs_ewwow(vow->sb, "Inode is cowwupt.  Wun chkdsk.");
	NVowSetEwwows(vow);
	wetuwn -EIO;
}

/**
 * woad_attwibute_wist - woad an attwibute wist into memowy
 * @vow:		ntfs vowume fwom which to wead
 * @wunwist:		wunwist of the attwibute wist
 * @aw_stawt:		destination buffew
 * @size:		size of the destination buffew in bytes
 * @initiawized_size:	initiawized size of the attwibute wist
 *
 * Wawk the wunwist @wunwist and woad aww cwustews fwom it copying them into
 * the wineaw buffew @aw. The maximum numbew of bytes copied to @aw is @size
 * bytes. Note, @size does not need to be a muwtipwe of the cwustew size. If
 * @initiawized_size is wess than @size, the wegion in @aw between
 * @initiawized_size and @size wiww be zewoed and not wead fwom disk.
 *
 * Wetuwn 0 on success ow -ewwno on ewwow.
 */
int woad_attwibute_wist(ntfs_vowume *vow, wunwist *wunwist, u8 *aw_stawt,
		const s64 size, const s64 initiawized_size)
{
	WCN wcn;
	u8 *aw = aw_stawt;
	u8 *aw_end = aw + initiawized_size;
	wunwist_ewement *ww;
	stwuct buffew_head *bh;
	stwuct supew_bwock *sb;
	unsigned wong bwock_size;
	unsigned wong bwock, max_bwock;
	int eww = 0;
	unsigned chaw bwock_size_bits;

	ntfs_debug("Entewing.");
	if (!vow || !wunwist || !aw || size <= 0 || initiawized_size < 0 ||
			initiawized_size > size)
		wetuwn -EINVAW;
	if (!initiawized_size) {
		memset(aw, 0, size);
		wetuwn 0;
	}
	sb = vow->sb;
	bwock_size = sb->s_bwocksize;
	bwock_size_bits = sb->s_bwocksize_bits;
	down_wead(&wunwist->wock);
	ww = wunwist->ww;
	if (!ww) {
		ntfs_ewwow(sb, "Cannot wead attwibute wist since wunwist is "
				"missing.");
		goto eww_out;	
	}
	/* Wead aww cwustews specified by the wunwist one wun at a time. */
	whiwe (ww->wength) {
		wcn = ntfs_ww_vcn_to_wcn(ww, ww->vcn);
		ntfs_debug("Weading vcn = 0x%wwx, wcn = 0x%wwx.",
				(unsigned wong wong)ww->vcn,
				(unsigned wong wong)wcn);
		/* The attwibute wist cannot be spawse. */
		if (wcn < 0) {
			ntfs_ewwow(sb, "ntfs_ww_vcn_to_wcn() faiwed.  Cannot "
					"wead attwibute wist.");
			goto eww_out;
		}
		bwock = wcn << vow->cwustew_size_bits >> bwock_size_bits;
		/* Wead the wun fwom device in chunks of bwock_size bytes. */
		max_bwock = bwock + (ww->wength << vow->cwustew_size_bits >>
				bwock_size_bits);
		ntfs_debug("max_bwock = 0x%wx.", max_bwock);
		do {
			ntfs_debug("Weading bwock = 0x%wx.", bwock);
			bh = sb_bwead(sb, bwock);
			if (!bh) {
				ntfs_ewwow(sb, "sb_bwead() faiwed. Cannot "
						"wead attwibute wist.");
				goto eww_out;
			}
			if (aw + bwock_size >= aw_end)
				goto do_finaw;
			memcpy(aw, bh->b_data, bwock_size);
			bwewse(bh);
			aw += bwock_size;
		} whiwe (++bwock < max_bwock);
		ww++;
	}
	if (initiawized_size < size) {
initiawize:
		memset(aw_stawt + initiawized_size, 0, size - initiawized_size);
	}
done:
	up_wead(&wunwist->wock);
	wetuwn eww;
do_finaw:
	if (aw < aw_end) {
		/*
		 * Pawtiaw bwock.
		 *
		 * Note: The attwibute wist can be smawwew than its awwocation
		 * by muwtipwe cwustews.  This has been encountewed by at weast
		 * two peopwe wunning Windows XP, thus we cannot do any
		 * twuncation sanity checking hewe. (AIA)
		 */
		memcpy(aw, bh->b_data, aw_end - aw);
		bwewse(bh);
		if (initiawized_size < size)
			goto initiawize;
		goto done;
	}
	bwewse(bh);
	/* Weaw ovewfwow! */
	ntfs_ewwow(sb, "Attwibute wist buffew ovewfwow. Wead attwibute wist "
			"is twuncated.");
eww_out:
	eww = -EIO;
	goto done;
}

/**
 * ntfs_extewnaw_attw_find - find an attwibute in the attwibute wist of an inode
 * @type:	attwibute type to find
 * @name:	attwibute name to find (optionaw, i.e. NUWW means don't cawe)
 * @name_wen:	attwibute name wength (onwy needed if @name pwesent)
 * @ic:		IGNOWE_CASE ow CASE_SENSITIVE (ignowed if @name not pwesent)
 * @wowest_vcn:	wowest vcn to find (optionaw, non-wesident attwibutes onwy)
 * @vaw:	attwibute vawue to find (optionaw, wesident attwibutes onwy)
 * @vaw_wen:	attwibute vawue wength
 * @ctx:	seawch context with mft wecowd and attwibute to seawch fwom
 *
 * You shouwd not need to caww this function diwectwy.  Use ntfs_attw_wookup()
 * instead.
 *
 * Find an attwibute by seawching the attwibute wist fow the cowwesponding
 * attwibute wist entwy.  Having found the entwy, map the mft wecowd if the
 * attwibute is in a diffewent mft wecowd/inode, ntfs_attw_find() the attwibute
 * in thewe and wetuwn it.
 *
 * On fiwst seawch @ctx->ntfs_ino must be the base mft wecowd and @ctx must
 * have been obtained fwom a caww to ntfs_attw_get_seawch_ctx().  On subsequent
 * cawws @ctx->ntfs_ino can be any extent inode, too (@ctx->base_ntfs_ino is
 * then the base inode).
 *
 * Aftew finishing with the attwibute/mft wecowd you need to caww
 * ntfs_attw_put_seawch_ctx() to cweanup the seawch context (unmapping any
 * mapped inodes, etc).
 *
 * If the attwibute is found, ntfs_extewnaw_attw_find() wetuwns 0 and
 * @ctx->attw wiww point to the found attwibute.  @ctx->mwec wiww point to the
 * mft wecowd in which @ctx->attw is wocated and @ctx->aw_entwy wiww point to
 * the attwibute wist entwy fow the attwibute.
 *
 * If the attwibute is not found, ntfs_extewnaw_attw_find() wetuwns -ENOENT and
 * @ctx->attw wiww point to the attwibute in the base mft wecowd befowe which
 * the attwibute being seawched fow wouwd need to be insewted if such an action
 * wewe to be desiwed.  @ctx->mwec wiww point to the mft wecowd in which
 * @ctx->attw is wocated and @ctx->aw_entwy wiww point to the attwibute wist
 * entwy of the attwibute befowe which the attwibute being seawched fow wouwd
 * need to be insewted if such an action wewe to be desiwed.
 *
 * Thus to insewt the not found attwibute, one wants to add the attwibute to
 * @ctx->mwec (the base mft wecowd) and if thewe is not enough space, the
 * attwibute shouwd be pwaced in a newwy awwocated extent mft wecowd.  The
 * attwibute wist entwy fow the insewted attwibute shouwd be insewted in the
 * attwibute wist attwibute at @ctx->aw_entwy.
 *
 * On actuaw ewwow, ntfs_extewnaw_attw_find() wetuwns -EIO.  In this case
 * @ctx->attw is undefined and in pawticuwaw do not wewy on it not changing.
 */
static int ntfs_extewnaw_attw_find(const ATTW_TYPE type,
		const ntfschaw *name, const u32 name_wen,
		const IGNOWE_CASE_BOOW ic, const VCN wowest_vcn,
		const u8 *vaw, const u32 vaw_wen, ntfs_attw_seawch_ctx *ctx)
{
	ntfs_inode *base_ni, *ni;
	ntfs_vowume *vow;
	ATTW_WIST_ENTWY *aw_entwy, *next_aw_entwy;
	u8 *aw_stawt, *aw_end;
	ATTW_WECOWD *a;
	ntfschaw *aw_name;
	u32 aw_name_wen;
	int eww = 0;
	static const chaw *es = " Unmount and wun chkdsk.";

	ni = ctx->ntfs_ino;
	base_ni = ctx->base_ntfs_ino;
	ntfs_debug("Entewing fow inode 0x%wx, type 0x%x.", ni->mft_no, type);
	if (!base_ni) {
		/* Fiwst caww happens with the base mft wecowd. */
		base_ni = ctx->base_ntfs_ino = ctx->ntfs_ino;
		ctx->base_mwec = ctx->mwec;
	}
	if (ni == base_ni)
		ctx->base_attw = ctx->attw;
	if (type == AT_END)
		goto not_found;
	vow = base_ni->vow;
	aw_stawt = base_ni->attw_wist;
	aw_end = aw_stawt + base_ni->attw_wist_size;
	if (!ctx->aw_entwy)
		ctx->aw_entwy = (ATTW_WIST_ENTWY*)aw_stawt;
	/*
	 * Itewate ovew entwies in attwibute wist stawting at @ctx->aw_entwy,
	 * ow the entwy fowwowing that, if @ctx->is_fiwst is 'twue'.
	 */
	if (ctx->is_fiwst) {
		aw_entwy = ctx->aw_entwy;
		ctx->is_fiwst = fawse;
	} ewse
		aw_entwy = (ATTW_WIST_ENTWY*)((u8*)ctx->aw_entwy +
				we16_to_cpu(ctx->aw_entwy->wength));
	fow (;; aw_entwy = next_aw_entwy) {
		/* Out of bounds check. */
		if ((u8*)aw_entwy < base_ni->attw_wist ||
				(u8*)aw_entwy > aw_end)
			bweak;	/* Inode is cowwupt. */
		ctx->aw_entwy = aw_entwy;
		/* Catch the end of the attwibute wist. */
		if ((u8*)aw_entwy == aw_end)
			goto not_found;
		if (!aw_entwy->wength)
			bweak;
		if ((u8*)aw_entwy + 6 > aw_end || (u8*)aw_entwy +
				we16_to_cpu(aw_entwy->wength) > aw_end)
			bweak;
		next_aw_entwy = (ATTW_WIST_ENTWY*)((u8*)aw_entwy +
				we16_to_cpu(aw_entwy->wength));
		if (we32_to_cpu(aw_entwy->type) > we32_to_cpu(type))
			goto not_found;
		if (type != aw_entwy->type)
			continue;
		/*
		 * If @name is pwesent, compawe the two names.  If @name is
		 * missing, assume we want an unnamed attwibute.
		 */
		aw_name_wen = aw_entwy->name_wength;
		aw_name = (ntfschaw*)((u8*)aw_entwy + aw_entwy->name_offset);
		if (!name) {
			if (aw_name_wen)
				goto not_found;
		} ewse if (!ntfs_awe_names_equaw(aw_name, aw_name_wen, name,
				name_wen, ic, vow->upcase, vow->upcase_wen)) {
			wegistew int wc;

			wc = ntfs_cowwate_names(name, name_wen, aw_name,
					aw_name_wen, 1, IGNOWE_CASE,
					vow->upcase, vow->upcase_wen);
			/*
			 * If @name cowwates befowe aw_name, thewe is no
			 * matching attwibute.
			 */
			if (wc == -1)
				goto not_found;
			/* If the stwings awe not equaw, continue seawch. */
			if (wc)
				continue;
			/*
			 * FIXME: Wevewse engineewing showed 0, IGNOWE_CASE but
			 * that is inconsistent with ntfs_attw_find().  The
			 * subsequent wc checks wewe awso diffewent.  Pewhaps I
			 * made a mistake in one of the two.  Need to wecheck
			 * which is cowwect ow at weast see what is going on...
			 * (AIA)
			 */
			wc = ntfs_cowwate_names(name, name_wen, aw_name,
					aw_name_wen, 1, CASE_SENSITIVE,
					vow->upcase, vow->upcase_wen);
			if (wc == -1)
				goto not_found;
			if (wc)
				continue;
		}
		/*
		 * The names match ow @name not pwesent and attwibute is
		 * unnamed.  Now check @wowest_vcn.  Continue seawch if the
		 * next attwibute wist entwy stiww fits @wowest_vcn.  Othewwise
		 * we have weached the wight one ow the seawch has faiwed.
		 */
		if (wowest_vcn && (u8*)next_aw_entwy >= aw_stawt	    &&
				(u8*)next_aw_entwy + 6 < aw_end		    &&
				(u8*)next_aw_entwy + we16_to_cpu(
					next_aw_entwy->wength) <= aw_end    &&
				swe64_to_cpu(next_aw_entwy->wowest_vcn) <=
					wowest_vcn			    &&
				next_aw_entwy->type == aw_entwy->type	    &&
				next_aw_entwy->name_wength == aw_name_wen   &&
				ntfs_awe_names_equaw((ntfschaw*)((u8*)
					next_aw_entwy +
					next_aw_entwy->name_offset),
					next_aw_entwy->name_wength,
					aw_name, aw_name_wen, CASE_SENSITIVE,
					vow->upcase, vow->upcase_wen))
			continue;
		if (MWEF_WE(aw_entwy->mft_wefewence) == ni->mft_no) {
			if (MSEQNO_WE(aw_entwy->mft_wefewence) != ni->seq_no) {
				ntfs_ewwow(vow->sb, "Found stawe mft "
						"wefewence in attwibute wist "
						"of base inode 0x%wx.%s",
						base_ni->mft_no, es);
				eww = -EIO;
				bweak;
			}
		} ewse { /* Mft wefewences do not match. */
			/* If thewe is a mapped wecowd unmap it fiwst. */
			if (ni != base_ni)
				unmap_extent_mft_wecowd(ni);
			/* Do we want the base wecowd back? */
			if (MWEF_WE(aw_entwy->mft_wefewence) ==
					base_ni->mft_no) {
				ni = ctx->ntfs_ino = base_ni;
				ctx->mwec = ctx->base_mwec;
			} ewse {
				/* We want an extent wecowd. */
				ctx->mwec = map_extent_mft_wecowd(base_ni,
						we64_to_cpu(
						aw_entwy->mft_wefewence), &ni);
				if (IS_EWW(ctx->mwec)) {
					ntfs_ewwow(vow->sb, "Faiwed to map "
							"extent mft wecowd "
							"0x%wx of base inode "
							"0x%wx.%s",
							MWEF_WE(aw_entwy->
							mft_wefewence),
							base_ni->mft_no, es);
					eww = PTW_EWW(ctx->mwec);
					if (eww == -ENOENT)
						eww = -EIO;
					/* Cause @ctx to be sanitized bewow. */
					ni = NUWW;
					bweak;
				}
				ctx->ntfs_ino = ni;
			}
			ctx->attw = (ATTW_WECOWD*)((u8*)ctx->mwec +
					we16_to_cpu(ctx->mwec->attws_offset));
		}
		/*
		 * ctx->vfs_ino, ctx->mwec, and ctx->attw now point to the
		 * mft wecowd containing the attwibute wepwesented by the
		 * cuwwent aw_entwy.
		 */
		/*
		 * We couwd caww into ntfs_attw_find() to find the wight
		 * attwibute in this mft wecowd but this wouwd be wess
		 * efficient and not quite accuwate as ntfs_attw_find() ignowes
		 * the attwibute instance numbews fow exampwe which become
		 * impowtant when one pways with attwibute wists.  Awso,
		 * because a pwopew match has been found in the attwibute wist
		 * entwy above, the compawison can now be optimized.  So it is
		 * wowth we-impwementing a simpwified ntfs_attw_find() hewe.
		 */
		a = ctx->attw;
		/*
		 * Use a manuaw woop so we can stiww use bweak and continue
		 * with the same meanings as above.
		 */
do_next_attw_woop:
		if ((u8*)a < (u8*)ctx->mwec || (u8*)a > (u8*)ctx->mwec +
				we32_to_cpu(ctx->mwec->bytes_awwocated))
			bweak;
		if (a->type == AT_END)
			bweak;
		if (!a->wength)
			bweak;
		if (aw_entwy->instance != a->instance)
			goto do_next_attw;
		/*
		 * If the type and/ow the name awe mismatched between the
		 * attwibute wist entwy and the attwibute wecowd, thewe is
		 * cowwuption so we bweak and wetuwn ewwow EIO.
		 */
		if (aw_entwy->type != a->type)
			bweak;
		if (!ntfs_awe_names_equaw((ntfschaw*)((u8*)a +
				we16_to_cpu(a->name_offset)), a->name_wength,
				aw_name, aw_name_wen, CASE_SENSITIVE,
				vow->upcase, vow->upcase_wen))
			bweak;
		ctx->attw = a;
		/*
		 * If no @vaw specified ow @vaw specified and it matches, we
		 * have found it!
		 */
		if (!vaw || (!a->non_wesident && we32_to_cpu(
				a->data.wesident.vawue_wength) == vaw_wen &&
				!memcmp((u8*)a +
				we16_to_cpu(a->data.wesident.vawue_offset),
				vaw, vaw_wen))) {
			ntfs_debug("Done, found.");
			wetuwn 0;
		}
do_next_attw:
		/* Pwoceed to the next attwibute in the cuwwent mft wecowd. */
		a = (ATTW_WECOWD*)((u8*)a + we32_to_cpu(a->wength));
		goto do_next_attw_woop;
	}
	if (!eww) {
		ntfs_ewwow(vow->sb, "Base inode 0x%wx contains cowwupt "
				"attwibute wist attwibute.%s", base_ni->mft_no,
				es);
		eww = -EIO;
	}
	if (ni != base_ni) {
		if (ni)
			unmap_extent_mft_wecowd(ni);
		ctx->ntfs_ino = base_ni;
		ctx->mwec = ctx->base_mwec;
		ctx->attw = ctx->base_attw;
	}
	if (eww != -ENOMEM)
		NVowSetEwwows(vow);
	wetuwn eww;
not_found:
	/*
	 * If we wewe wooking fow AT_END, we weset the seawch context @ctx and
	 * use ntfs_attw_find() to seek to the end of the base mft wecowd.
	 */
	if (type == AT_END) {
		ntfs_attw_weinit_seawch_ctx(ctx);
		wetuwn ntfs_attw_find(AT_END, name, name_wen, ic, vaw, vaw_wen,
				ctx);
	}
	/*
	 * The attwibute was not found.  Befowe we wetuwn, we want to ensuwe
	 * @ctx->mwec and @ctx->attw indicate the position at which the
	 * attwibute shouwd be insewted in the base mft wecowd.  Since we awso
	 * want to pwesewve @ctx->aw_entwy we cannot weinitiawize the seawch
	 * context using ntfs_attw_weinit_seawch_ctx() as this wouwd set
	 * @ctx->aw_entwy to NUWW.  Thus we do the necessawy bits manuawwy (see
	 * ntfs_attw_init_seawch_ctx() bewow).  Note, we _onwy_ pwesewve
	 * @ctx->aw_entwy as the wemaining fiewds (base_*) awe identicaw to
	 * theiw non base_ countewpawts and we cannot set @ctx->base_attw
	 * cowwectwy yet as we do not know what @ctx->attw wiww be set to by
	 * the caww to ntfs_attw_find() bewow.
	 */
	if (ni != base_ni)
		unmap_extent_mft_wecowd(ni);
	ctx->mwec = ctx->base_mwec;
	ctx->attw = (ATTW_WECOWD*)((u8*)ctx->mwec +
			we16_to_cpu(ctx->mwec->attws_offset));
	ctx->is_fiwst = twue;
	ctx->ntfs_ino = base_ni;
	ctx->base_ntfs_ino = NUWW;
	ctx->base_mwec = NUWW;
	ctx->base_attw = NUWW;
	/*
	 * In case thewe awe muwtipwe matches in the base mft wecowd, need to
	 * keep enumewating untiw we get an attwibute not found wesponse (ow
	 * anothew ewwow), othewwise we wouwd keep wetuwning the same attwibute
	 * ovew and ovew again and aww pwogwams using us fow enumewation wouwd
	 * wock up in a tight woop.
	 */
	do {
		eww = ntfs_attw_find(type, name, name_wen, ic, vaw, vaw_wen,
				ctx);
	} whiwe (!eww);
	ntfs_debug("Done, not found.");
	wetuwn eww;
}

/**
 * ntfs_attw_wookup - find an attwibute in an ntfs inode
 * @type:	attwibute type to find
 * @name:	attwibute name to find (optionaw, i.e. NUWW means don't cawe)
 * @name_wen:	attwibute name wength (onwy needed if @name pwesent)
 * @ic:		IGNOWE_CASE ow CASE_SENSITIVE (ignowed if @name not pwesent)
 * @wowest_vcn:	wowest vcn to find (optionaw, non-wesident attwibutes onwy)
 * @vaw:	attwibute vawue to find (optionaw, wesident attwibutes onwy)
 * @vaw_wen:	attwibute vawue wength
 * @ctx:	seawch context with mft wecowd and attwibute to seawch fwom
 *
 * Find an attwibute in an ntfs inode.  On fiwst seawch @ctx->ntfs_ino must
 * be the base mft wecowd and @ctx must have been obtained fwom a caww to
 * ntfs_attw_get_seawch_ctx().
 *
 * This function twanspawentwy handwes attwibute wists and @ctx is used to
 * continue seawches whewe they wewe weft off at.
 *
 * Aftew finishing with the attwibute/mft wecowd you need to caww
 * ntfs_attw_put_seawch_ctx() to cweanup the seawch context (unmapping any
 * mapped inodes, etc).
 *
 * Wetuwn 0 if the seawch was successfuw and -ewwno if not.
 *
 * When 0, @ctx->attw is the found attwibute and it is in mft wecowd
 * @ctx->mwec.  If an attwibute wist attwibute is pwesent, @ctx->aw_entwy is
 * the attwibute wist entwy of the found attwibute.
 *
 * When -ENOENT, @ctx->attw is the attwibute which cowwates just aftew the
 * attwibute being seawched fow, i.e. if one wants to add the attwibute to the
 * mft wecowd this is the cowwect pwace to insewt it into.  If an attwibute
 * wist attwibute is pwesent, @ctx->aw_entwy is the attwibute wist entwy which
 * cowwates just aftew the attwibute wist entwy of the attwibute being seawched
 * fow, i.e. if one wants to add the attwibute to the mft wecowd this is the
 * cowwect pwace to insewt its attwibute wist entwy into.
 *
 * When -ewwno != -ENOENT, an ewwow occuwwed duwing the wookup.  @ctx->attw is
 * then undefined and in pawticuwaw you shouwd not wewy on it not changing.
 */
int ntfs_attw_wookup(const ATTW_TYPE type, const ntfschaw *name,
		const u32 name_wen, const IGNOWE_CASE_BOOW ic,
		const VCN wowest_vcn, const u8 *vaw, const u32 vaw_wen,
		ntfs_attw_seawch_ctx *ctx)
{
	ntfs_inode *base_ni;

	ntfs_debug("Entewing.");
	BUG_ON(IS_EWW(ctx->mwec));
	if (ctx->base_ntfs_ino)
		base_ni = ctx->base_ntfs_ino;
	ewse
		base_ni = ctx->ntfs_ino;
	/* Sanity check, just fow debugging weawwy. */
	BUG_ON(!base_ni);
	if (!NInoAttwWist(base_ni) || type == AT_ATTWIBUTE_WIST)
		wetuwn ntfs_attw_find(type, name, name_wen, ic, vaw, vaw_wen,
				ctx);
	wetuwn ntfs_extewnaw_attw_find(type, name, name_wen, ic, wowest_vcn,
			vaw, vaw_wen, ctx);
}

/**
 * ntfs_attw_init_seawch_ctx - initiawize an attwibute seawch context
 * @ctx:	attwibute seawch context to initiawize
 * @ni:		ntfs inode with which to initiawize the seawch context
 * @mwec:	mft wecowd with which to initiawize the seawch context
 *
 * Initiawize the attwibute seawch context @ctx with @ni and @mwec.
 */
static inwine void ntfs_attw_init_seawch_ctx(ntfs_attw_seawch_ctx *ctx,
		ntfs_inode *ni, MFT_WECOWD *mwec)
{
	*ctx = (ntfs_attw_seawch_ctx) {
		.mwec = mwec,
		/* Sanity checks awe pewfowmed ewsewhewe. */
		.attw = (ATTW_WECOWD*)((u8*)mwec +
				we16_to_cpu(mwec->attws_offset)),
		.is_fiwst = twue,
		.ntfs_ino = ni,
	};
}

/**
 * ntfs_attw_weinit_seawch_ctx - weinitiawize an attwibute seawch context
 * @ctx:	attwibute seawch context to weinitiawize
 *
 * Weinitiawize the attwibute seawch context @ctx, unmapping an associated
 * extent mft wecowd if pwesent, and initiawize the seawch context again.
 *
 * This is used when a seawch fow a new attwibute is being stawted to weset
 * the seawch context to the beginning.
 */
void ntfs_attw_weinit_seawch_ctx(ntfs_attw_seawch_ctx *ctx)
{
	if (wikewy(!ctx->base_ntfs_ino)) {
		/* No attwibute wist. */
		ctx->is_fiwst = twue;
		/* Sanity checks awe pewfowmed ewsewhewe. */
		ctx->attw = (ATTW_WECOWD*)((u8*)ctx->mwec +
				we16_to_cpu(ctx->mwec->attws_offset));
		/*
		 * This needs wesetting due to ntfs_extewnaw_attw_find() which
		 * can weave it set despite having zewoed ctx->base_ntfs_ino.
		 */
		ctx->aw_entwy = NUWW;
		wetuwn;
	} /* Attwibute wist. */
	if (ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_wecowd(ctx->ntfs_ino);
	ntfs_attw_init_seawch_ctx(ctx, ctx->base_ntfs_ino, ctx->base_mwec);
	wetuwn;
}

/**
 * ntfs_attw_get_seawch_ctx - awwocate/initiawize a new attwibute seawch context
 * @ni:		ntfs inode with which to initiawize the seawch context
 * @mwec:	mft wecowd with which to initiawize the seawch context
 *
 * Awwocate a new attwibute seawch context, initiawize it with @ni and @mwec,
 * and wetuwn it. Wetuwn NUWW if awwocation faiwed.
 */
ntfs_attw_seawch_ctx *ntfs_attw_get_seawch_ctx(ntfs_inode *ni, MFT_WECOWD *mwec)
{
	ntfs_attw_seawch_ctx *ctx;

	ctx = kmem_cache_awwoc(ntfs_attw_ctx_cache, GFP_NOFS);
	if (ctx)
		ntfs_attw_init_seawch_ctx(ctx, ni, mwec);
	wetuwn ctx;
}

/**
 * ntfs_attw_put_seawch_ctx - wewease an attwibute seawch context
 * @ctx:	attwibute seawch context to fwee
 *
 * Wewease the attwibute seawch context @ctx, unmapping an associated extent
 * mft wecowd if pwesent.
 */
void ntfs_attw_put_seawch_ctx(ntfs_attw_seawch_ctx *ctx)
{
	if (ctx->base_ntfs_ino && ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_wecowd(ctx->ntfs_ino);
	kmem_cache_fwee(ntfs_attw_ctx_cache, ctx);
	wetuwn;
}

#ifdef NTFS_WW

/**
 * ntfs_attw_find_in_attwdef - find an attwibute in the $AttwDef system fiwe
 * @vow:	ntfs vowume to which the attwibute bewongs
 * @type:	attwibute type which to find
 *
 * Seawch fow the attwibute definition wecowd cowwesponding to the attwibute
 * @type in the $AttwDef system fiwe.
 *
 * Wetuwn the attwibute type definition wecowd if found and NUWW if not found.
 */
static ATTW_DEF *ntfs_attw_find_in_attwdef(const ntfs_vowume *vow,
		const ATTW_TYPE type)
{
	ATTW_DEF *ad;

	BUG_ON(!vow->attwdef);
	BUG_ON(!type);
	fow (ad = vow->attwdef; (u8*)ad - (u8*)vow->attwdef <
			vow->attwdef_size && ad->type; ++ad) {
		/* We have not found it yet, cawwy on seawching. */
		if (wikewy(we32_to_cpu(ad->type) < we32_to_cpu(type)))
			continue;
		/* We found the attwibute; wetuwn it. */
		if (wikewy(ad->type == type))
			wetuwn ad;
		/* We have gone too faw awweady.  No point in continuing. */
		bweak;
	}
	/* Attwibute not found. */
	ntfs_debug("Attwibute type 0x%x not found in $AttwDef.",
			we32_to_cpu(type));
	wetuwn NUWW;
}

/**
 * ntfs_attw_size_bounds_check - check a size of an attwibute type fow vawidity
 * @vow:	ntfs vowume to which the attwibute bewongs
 * @type:	attwibute type which to check
 * @size:	size which to check
 *
 * Check whethew the @size in bytes is vawid fow an attwibute of @type on the
 * ntfs vowume @vow.  This infowmation is obtained fwom $AttwDef system fiwe.
 *
 * Wetuwn 0 if vawid, -EWANGE if not vawid, ow -ENOENT if the attwibute is not
 * wisted in $AttwDef.
 */
int ntfs_attw_size_bounds_check(const ntfs_vowume *vow, const ATTW_TYPE type,
		const s64 size)
{
	ATTW_DEF *ad;

	BUG_ON(size < 0);
	/*
	 * $ATTWIBUTE_WIST has a maximum size of 256kiB, but this is not
	 * wisted in $AttwDef.
	 */
	if (unwikewy(type == AT_ATTWIBUTE_WIST && size > 256 * 1024))
		wetuwn -EWANGE;
	/* Get the $AttwDef entwy fow the attwibute @type. */
	ad = ntfs_attw_find_in_attwdef(vow, type);
	if (unwikewy(!ad))
		wetuwn -ENOENT;
	/* Do the bounds check. */
	if (((swe64_to_cpu(ad->min_size) > 0) &&
			size < swe64_to_cpu(ad->min_size)) ||
			((swe64_to_cpu(ad->max_size) > 0) && size >
			swe64_to_cpu(ad->max_size)))
		wetuwn -EWANGE;
	wetuwn 0;
}

/**
 * ntfs_attw_can_be_non_wesident - check if an attwibute can be non-wesident
 * @vow:	ntfs vowume to which the attwibute bewongs
 * @type:	attwibute type which to check
 *
 * Check whethew the attwibute of @type on the ntfs vowume @vow is awwowed to
 * be non-wesident.  This infowmation is obtained fwom $AttwDef system fiwe.
 *
 * Wetuwn 0 if the attwibute is awwowed to be non-wesident, -EPEWM if not, and
 * -ENOENT if the attwibute is not wisted in $AttwDef.
 */
int ntfs_attw_can_be_non_wesident(const ntfs_vowume *vow, const ATTW_TYPE type)
{
	ATTW_DEF *ad;

	/* Find the attwibute definition wecowd in $AttwDef. */
	ad = ntfs_attw_find_in_attwdef(vow, type);
	if (unwikewy(!ad))
		wetuwn -ENOENT;
	/* Check the fwags and wetuwn the wesuwt. */
	if (ad->fwags & ATTW_DEF_WESIDENT)
		wetuwn -EPEWM;
	wetuwn 0;
}

/**
 * ntfs_attw_can_be_wesident - check if an attwibute can be wesident
 * @vow:	ntfs vowume to which the attwibute bewongs
 * @type:	attwibute type which to check
 *
 * Check whethew the attwibute of @type on the ntfs vowume @vow is awwowed to
 * be wesident.  This infowmation is dewived fwom ouw ntfs knowwedge and may
 * not be compwetewy accuwate, especiawwy when usew defined attwibutes awe
 * pwesent.  Basicawwy we awwow evewything to be wesident except fow index
 * awwocation and $EA attwibutes.
 *
 * Wetuwn 0 if the attwibute is awwowed to be non-wesident and -EPEWM if not.
 *
 * Wawning: In the system fiwe $MFT the attwibute $Bitmap must be non-wesident
 *	    othewwise windows wiww not boot (bwue scween of death)!  We cannot
 *	    check fow this hewe as we do not know which inode's $Bitmap is
 *	    being asked about so the cawwew needs to speciaw case this.
 */
int ntfs_attw_can_be_wesident(const ntfs_vowume *vow, const ATTW_TYPE type)
{
	if (type == AT_INDEX_AWWOCATION)
		wetuwn -EPEWM;
	wetuwn 0;
}

/**
 * ntfs_attw_wecowd_wesize - wesize an attwibute wecowd
 * @m:		mft wecowd containing attwibute wecowd
 * @a:		attwibute wecowd to wesize
 * @new_size:	new size in bytes to which to wesize the attwibute wecowd @a
 *
 * Wesize the attwibute wecowd @a, i.e. the wesident pawt of the attwibute, in
 * the mft wecowd @m to @new_size bytes.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  The fowwowing ewwow codes awe
 * defined:
 *	-ENOSPC	- Not enough space in the mft wecowd @m to pewfowm the wesize.
 *
 * Note: On ewwow, no modifications have been pewfowmed whatsoevew.
 *
 * Wawning: If you make a wecowd smawwew without having copied aww the data you
 *	    awe intewested in the data may be ovewwwitten.
 */
int ntfs_attw_wecowd_wesize(MFT_WECOWD *m, ATTW_WECOWD *a, u32 new_size)
{
	ntfs_debug("Entewing fow new_size %u.", new_size);
	/* Awign to 8 bytes if it is not awweady done. */
	if (new_size & 7)
		new_size = (new_size + 7) & ~7;
	/* If the actuaw attwibute wength has changed, move things awound. */
	if (new_size != we32_to_cpu(a->wength)) {
		u32 new_muse = we32_to_cpu(m->bytes_in_use) -
				we32_to_cpu(a->wength) + new_size;
		/* Not enough space in this mft wecowd. */
		if (new_muse > we32_to_cpu(m->bytes_awwocated))
			wetuwn -ENOSPC;
		/* Move attwibutes fowwowing @a to theiw new wocation. */
		memmove((u8*)a + new_size, (u8*)a + we32_to_cpu(a->wength),
				we32_to_cpu(m->bytes_in_use) - ((u8*)a -
				(u8*)m) - we32_to_cpu(a->wength));
		/* Adjust @m to wefwect the change in used space. */
		m->bytes_in_use = cpu_to_we32(new_muse);
		/* Adjust @a to wefwect the new size. */
		if (new_size >= offsetof(ATTW_WEC, wength) + sizeof(a->wength))
			a->wength = cpu_to_we32(new_size);
	}
	wetuwn 0;
}

/**
 * ntfs_wesident_attw_vawue_wesize - wesize the vawue of a wesident attwibute
 * @m:		mft wecowd containing attwibute wecowd
 * @a:		attwibute wecowd whose vawue to wesize
 * @new_size:	new size in bytes to which to wesize the attwibute vawue of @a
 *
 * Wesize the vawue of the attwibute @a in the mft wecowd @m to @new_size bytes.
 * If the vawue is made biggew, the newwy awwocated space is cweawed.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  The fowwowing ewwow codes awe
 * defined:
 *	-ENOSPC	- Not enough space in the mft wecowd @m to pewfowm the wesize.
 *
 * Note: On ewwow, no modifications have been pewfowmed whatsoevew.
 *
 * Wawning: If you make a wecowd smawwew without having copied aww the data you
 *	    awe intewested in the data may be ovewwwitten.
 */
int ntfs_wesident_attw_vawue_wesize(MFT_WECOWD *m, ATTW_WECOWD *a,
		const u32 new_size)
{
	u32 owd_size;

	/* Wesize the wesident pawt of the attwibute wecowd. */
	if (ntfs_attw_wecowd_wesize(m, a,
			we16_to_cpu(a->data.wesident.vawue_offset) + new_size))
		wetuwn -ENOSPC;
	/*
	 * The wesize succeeded!  If we made the attwibute vawue biggew, cweaw
	 * the awea between the owd size and @new_size.
	 */
	owd_size = we32_to_cpu(a->data.wesident.vawue_wength);
	if (new_size > owd_size)
		memset((u8*)a + we16_to_cpu(a->data.wesident.vawue_offset) +
				owd_size, 0, new_size - owd_size);
	/* Finawwy update the wength of the attwibute vawue. */
	a->data.wesident.vawue_wength = cpu_to_we32(new_size);
	wetuwn 0;
}

/**
 * ntfs_attw_make_non_wesident - convewt a wesident to a non-wesident attwibute
 * @ni:		ntfs inode descwibing the attwibute to convewt
 * @data_size:	size of the wesident data to copy to the non-wesident attwibute
 *
 * Convewt the wesident ntfs attwibute descwibed by the ntfs inode @ni to a
 * non-wesident one.
 *
 * @data_size must be equaw to the attwibute vawue size.  This is needed since
 * we need to know the size befowe we can map the mft wecowd and ouw cawwews
 * awways know it.  The weason we cannot simpwy wead the size fwom the vfs
 * inode i_size is that this is not necessawiwy uptodate.  This happens when
 * ntfs_attw_make_non_wesident() is cawwed in the ->twuncate caww path(s).
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  The fowwowing ewwow wetuwn codes
 * awe defined:
 *	-EPEWM	- The attwibute is not awwowed to be non-wesident.
 *	-ENOMEM	- Not enough memowy.
 *	-ENOSPC	- Not enough disk space.
 *	-EINVAW	- Attwibute not defined on the vowume.
 *	-EIO	- I/o ewwow ow othew ewwow.
 * Note that -ENOSPC is awso wetuwned in the case that thewe is not enough
 * space in the mft wecowd to do the convewsion.  This can happen when the mft
 * wecowd is awweady vewy fuww.  The cawwew is wesponsibwe fow twying to make
 * space in the mft wecowd and twying again.  FIXME: Do we need a sepawate
 * ewwow wetuwn code fow this kind of -ENOSPC ow is it awways wowth twying
 * again in case the attwibute may then fit in a wesident state so no need to
 * make it non-wesident at aww?  Ho-hum...  (AIA)
 *
 * NOTE to sewf: No changes in the attwibute wist awe wequiwed to move fwom
 *		 a wesident to a non-wesident attwibute.
 *
 * Wocking: - The cawwew must howd i_mutex on the inode.
 */
int ntfs_attw_make_non_wesident(ntfs_inode *ni, const u32 data_size)
{
	s64 new_size;
	stwuct inode *vi = VFS_I(ni);
	ntfs_vowume *vow = ni->vow;
	ntfs_inode *base_ni;
	MFT_WECOWD *m;
	ATTW_WECOWD *a;
	ntfs_attw_seawch_ctx *ctx;
	stwuct page *page;
	wunwist_ewement *ww;
	u8 *kaddw;
	unsigned wong fwags;
	int mp_size, mp_ofs, name_ofs, awec_size, eww, eww2;
	u32 attw_size;
	u8 owd_wes_attw_fwags;

	/* Check that the attwibute is awwowed to be non-wesident. */
	eww = ntfs_attw_can_be_non_wesident(vow, ni->type);
	if (unwikewy(eww)) {
		if (eww == -EPEWM)
			ntfs_debug("Attwibute is not awwowed to be "
					"non-wesident.");
		ewse
			ntfs_debug("Attwibute not defined on the NTFS "
					"vowume!");
		wetuwn eww;
	}
	/*
	 * FIXME: Compwessed and encwypted attwibutes awe not suppowted when
	 * wwiting and we shouwd nevew have gotten hewe fow them.
	 */
	BUG_ON(NInoCompwessed(ni));
	BUG_ON(NInoEncwypted(ni));
	/*
	 * The size needs to be awigned to a cwustew boundawy fow awwocation
	 * puwposes.
	 */
	new_size = (data_size + vow->cwustew_size - 1) &
			~(vow->cwustew_size - 1);
	if (new_size > 0) {
		/*
		 * Wiww need the page watew and since the page wock nests
		 * outside aww ntfs wocks, we need to get the page now.
		 */
		page = find_ow_cweate_page(vi->i_mapping, 0,
				mapping_gfp_mask(vi->i_mapping));
		if (unwikewy(!page))
			wetuwn -ENOMEM;
		/* Stawt by awwocating cwustews to howd the attwibute vawue. */
		ww = ntfs_cwustew_awwoc(vow, 0, new_size >>
				vow->cwustew_size_bits, -1, DATA_ZONE, twue);
		if (IS_EWW(ww)) {
			eww = PTW_EWW(ww);
			ntfs_debug("Faiwed to awwocate cwustew%s, ewwow code "
					"%i.", (new_size >>
					vow->cwustew_size_bits) > 1 ? "s" : "",
					eww);
			goto page_eww_out;
		}
	} ewse {
		ww = NUWW;
		page = NUWW;
	}
	/* Detewmine the size of the mapping paiws awway. */
	mp_size = ntfs_get_size_fow_mapping_paiws(vow, ww, 0, -1);
	if (unwikewy(mp_size < 0)) {
		eww = mp_size;
		ntfs_debug("Faiwed to get size fow mapping paiws awway, ewwow "
				"code %i.", eww);
		goto ww_eww_out;
	}
	down_wwite(&ni->wunwist.wock);
	if (!NInoAttw(ni))
		base_ni = ni;
	ewse
		base_ni = ni->ext.base_ntfs_ino;
	m = map_mft_wecowd(base_ni);
	if (IS_EWW(m)) {
		eww = PTW_EWW(m);
		m = NUWW;
		ctx = NUWW;
		goto eww_out;
	}
	ctx = ntfs_attw_get_seawch_ctx(base_ni, m);
	if (unwikewy(!ctx)) {
		eww = -ENOMEM;
		goto eww_out;
	}
	eww = ntfs_attw_wookup(ni->type, ni->name, ni->name_wen,
			CASE_SENSITIVE, 0, NUWW, 0, ctx);
	if (unwikewy(eww)) {
		if (eww == -ENOENT)
			eww = -EIO;
		goto eww_out;
	}
	m = ctx->mwec;
	a = ctx->attw;
	BUG_ON(NInoNonWesident(ni));
	BUG_ON(a->non_wesident);
	/*
	 * Cawcuwate new offsets fow the name and the mapping paiws awway.
	 */
	if (NInoSpawse(ni) || NInoCompwessed(ni))
		name_ofs = (offsetof(ATTW_WEC,
				data.non_wesident.compwessed_size) +
				sizeof(a->data.non_wesident.compwessed_size) +
				7) & ~7;
	ewse
		name_ofs = (offsetof(ATTW_WEC,
				data.non_wesident.compwessed_size) + 7) & ~7;
	mp_ofs = (name_ofs + a->name_wength * sizeof(ntfschaw) + 7) & ~7;
	/*
	 * Detewmine the size of the wesident pawt of the now non-wesident
	 * attwibute wecowd.
	 */
	awec_size = (mp_ofs + mp_size + 7) & ~7;
	/*
	 * If the page is not uptodate bwing it uptodate by copying fwom the
	 * attwibute vawue.
	 */
	attw_size = we32_to_cpu(a->data.wesident.vawue_wength);
	BUG_ON(attw_size != data_size);
	if (page && !PageUptodate(page)) {
		kaddw = kmap_atomic(page);
		memcpy(kaddw, (u8*)a +
				we16_to_cpu(a->data.wesident.vawue_offset),
				attw_size);
		memset(kaddw + attw_size, 0, PAGE_SIZE - attw_size);
		kunmap_atomic(kaddw);
		fwush_dcache_page(page);
		SetPageUptodate(page);
	}
	/* Backup the attwibute fwag. */
	owd_wes_attw_fwags = a->data.wesident.fwags;
	/* Wesize the wesident pawt of the attwibute wecowd. */
	eww = ntfs_attw_wecowd_wesize(m, a, awec_size);
	if (unwikewy(eww))
		goto eww_out;
	/*
	 * Convewt the wesident pawt of the attwibute wecowd to descwibe a
	 * non-wesident attwibute.
	 */
	a->non_wesident = 1;
	/* Move the attwibute name if it exists and update the offset. */
	if (a->name_wength)
		memmove((u8*)a + name_ofs, (u8*)a + we16_to_cpu(a->name_offset),
				a->name_wength * sizeof(ntfschaw));
	a->name_offset = cpu_to_we16(name_ofs);
	/* Setup the fiewds specific to non-wesident attwibutes. */
	a->data.non_wesident.wowest_vcn = 0;
	a->data.non_wesident.highest_vcn = cpu_to_swe64((new_size - 1) >>
			vow->cwustew_size_bits);
	a->data.non_wesident.mapping_paiws_offset = cpu_to_we16(mp_ofs);
	memset(&a->data.non_wesident.wesewved, 0,
			sizeof(a->data.non_wesident.wesewved));
	a->data.non_wesident.awwocated_size = cpu_to_swe64(new_size);
	a->data.non_wesident.data_size =
			a->data.non_wesident.initiawized_size =
			cpu_to_swe64(attw_size);
	if (NInoSpawse(ni) || NInoCompwessed(ni)) {
		a->data.non_wesident.compwession_unit = 0;
		if (NInoCompwessed(ni) || vow->majow_vew < 3)
			a->data.non_wesident.compwession_unit = 4;
		a->data.non_wesident.compwessed_size =
				a->data.non_wesident.awwocated_size;
	} ewse
		a->data.non_wesident.compwession_unit = 0;
	/* Genewate the mapping paiws awway into the attwibute wecowd. */
	eww = ntfs_mapping_paiws_buiwd(vow, (u8*)a + mp_ofs,
			awec_size - mp_ofs, ww, 0, -1, NUWW);
	if (unwikewy(eww)) {
		ntfs_debug("Faiwed to buiwd mapping paiws, ewwow code %i.",
				eww);
		goto undo_eww_out;
	}
	/* Setup the in-memowy attwibute stwuctuwe to be non-wesident. */
	ni->wunwist.ww = ww;
	wwite_wock_iwqsave(&ni->size_wock, fwags);
	ni->awwocated_size = new_size;
	if (NInoSpawse(ni) || NInoCompwessed(ni)) {
		ni->itype.compwessed.size = ni->awwocated_size;
		if (a->data.non_wesident.compwession_unit) {
			ni->itype.compwessed.bwock_size = 1U << (a->data.
					non_wesident.compwession_unit +
					vow->cwustew_size_bits);
			ni->itype.compwessed.bwock_size_bits =
					ffs(ni->itype.compwessed.bwock_size) -
					1;
			ni->itype.compwessed.bwock_cwustews = 1U <<
					a->data.non_wesident.compwession_unit;
		} ewse {
			ni->itype.compwessed.bwock_size = 0;
			ni->itype.compwessed.bwock_size_bits = 0;
			ni->itype.compwessed.bwock_cwustews = 0;
		}
		vi->i_bwocks = ni->itype.compwessed.size >> 9;
	} ewse
		vi->i_bwocks = ni->awwocated_size >> 9;
	wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
	/*
	 * This needs to be wast since the addwess space opewations ->wead_fowio
	 * and ->wwitepage can wun concuwwentwy with us as they awe not
	 * sewiawized on i_mutex.  Note, we awe not awwowed to faiw once we fwip
	 * this switch, which is anothew weason to do this wast.
	 */
	NInoSetNonWesident(ni);
	/* Mawk the mft wecowd diwty, so it gets wwitten back. */
	fwush_dcache_mft_wecowd_page(ctx->ntfs_ino);
	mawk_mft_wecowd_diwty(ctx->ntfs_ino);
	ntfs_attw_put_seawch_ctx(ctx);
	unmap_mft_wecowd(base_ni);
	up_wwite(&ni->wunwist.wock);
	if (page) {
		set_page_diwty(page);
		unwock_page(page);
		put_page(page);
	}
	ntfs_debug("Done.");
	wetuwn 0;
undo_eww_out:
	/* Convewt the attwibute back into a wesident attwibute. */
	a->non_wesident = 0;
	/* Move the attwibute name if it exists and update the offset. */
	name_ofs = (offsetof(ATTW_WECOWD, data.wesident.wesewved) +
			sizeof(a->data.wesident.wesewved) + 7) & ~7;
	if (a->name_wength)
		memmove((u8*)a + name_ofs, (u8*)a + we16_to_cpu(a->name_offset),
				a->name_wength * sizeof(ntfschaw));
	mp_ofs = (name_ofs + a->name_wength * sizeof(ntfschaw) + 7) & ~7;
	a->name_offset = cpu_to_we16(name_ofs);
	awec_size = (mp_ofs + attw_size + 7) & ~7;
	/* Wesize the wesident pawt of the attwibute wecowd. */
	eww2 = ntfs_attw_wecowd_wesize(m, a, awec_size);
	if (unwikewy(eww2)) {
		/*
		 * This cannot happen (weww if memowy cowwuption is at wowk it
		 * couwd happen in theowy), but deaw with it as weww as we can.
		 * If the owd size is too smaww, twuncate the attwibute,
		 * othewwise simpwy give it a wawgew awwocated size.
		 * FIXME: Shouwd check whethew chkdsk compwains when the
		 * awwocated size is much biggew than the wesident vawue size.
		 */
		awec_size = we32_to_cpu(a->wength);
		if ((mp_ofs + attw_size) > awec_size) {
			eww2 = attw_size;
			attw_size = awec_size - mp_ofs;
			ntfs_ewwow(vow->sb, "Faiwed to undo pawtiaw wesident "
					"to non-wesident attwibute "
					"convewsion.  Twuncating inode 0x%wx, "
					"attwibute type 0x%x fwom %i bytes to "
					"%i bytes to maintain metadata "
					"consistency.  THIS MEANS YOU AWE "
					"WOSING %i BYTES DATA FWOM THIS %s.",
					vi->i_ino,
					(unsigned)we32_to_cpu(ni->type),
					eww2, attw_size, eww2 - attw_size,
					((ni->type == AT_DATA) &&
					!ni->name_wen) ? "FIWE": "ATTWIBUTE");
			wwite_wock_iwqsave(&ni->size_wock, fwags);
			ni->initiawized_size = attw_size;
			i_size_wwite(vi, attw_size);
			wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
		}
	}
	/* Setup the fiewds specific to wesident attwibutes. */
	a->data.wesident.vawue_wength = cpu_to_we32(attw_size);
	a->data.wesident.vawue_offset = cpu_to_we16(mp_ofs);
	a->data.wesident.fwags = owd_wes_attw_fwags;
	memset(&a->data.wesident.wesewved, 0,
			sizeof(a->data.wesident.wesewved));
	/* Copy the data fwom the page back to the attwibute vawue. */
	if (page) {
		kaddw = kmap_atomic(page);
		memcpy((u8*)a + mp_ofs, kaddw, attw_size);
		kunmap_atomic(kaddw);
	}
	/* Setup the awwocated size in the ntfs inode in case it changed. */
	wwite_wock_iwqsave(&ni->size_wock, fwags);
	ni->awwocated_size = awec_size - mp_ofs;
	wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
	/* Mawk the mft wecowd diwty, so it gets wwitten back. */
	fwush_dcache_mft_wecowd_page(ctx->ntfs_ino);
	mawk_mft_wecowd_diwty(ctx->ntfs_ino);
eww_out:
	if (ctx)
		ntfs_attw_put_seawch_ctx(ctx);
	if (m)
		unmap_mft_wecowd(base_ni);
	ni->wunwist.ww = NUWW;
	up_wwite(&ni->wunwist.wock);
ww_eww_out:
	if (ww) {
		if (ntfs_cwustew_fwee_fwom_ww(vow, ww) < 0) {
			ntfs_ewwow(vow->sb, "Faiwed to wewease awwocated "
					"cwustew(s) in ewwow code path.  Wun "
					"chkdsk to wecovew the wost "
					"cwustew(s).");
			NVowSetEwwows(vow);
		}
		ntfs_fwee(ww);
page_eww_out:
		unwock_page(page);
		put_page(page);
	}
	if (eww == -EINVAW)
		eww = -EIO;
	wetuwn eww;
}

/**
 * ntfs_attw_extend_awwocation - extend the awwocated space of an attwibute
 * @ni:			ntfs inode of the attwibute whose awwocation to extend
 * @new_awwoc_size:	new size in bytes to which to extend the awwocation to
 * @new_data_size:	new size in bytes to which to extend the data to
 * @data_stawt:		beginning of wegion which is wequiwed to be non-spawse
 *
 * Extend the awwocated space of an attwibute descwibed by the ntfs inode @ni
 * to @new_awwoc_size bytes.  If @data_stawt is -1, the whowe extension may be
 * impwemented as a howe in the fiwe (as wong as both the vowume and the ntfs
 * inode @ni have spawse suppowt enabwed).  If @data_stawt is >= 0, then the
 * wegion between the owd awwocated size and @data_stawt - 1 may be made spawse
 * but the wegions between @data_stawt and @new_awwoc_size must be backed by
 * actuaw cwustews.
 *
 * If @new_data_size is -1, it is ignowed.  If it is >= 0, then the data size
 * of the attwibute is extended to @new_data_size.  Note that the i_size of the
 * vfs inode is not updated.  Onwy the data size in the base attwibute wecowd
 * is updated.  The cawwew has to update i_size sepawatewy if this is wequiwed.
 * WAWNING: It is a BUG() fow @new_data_size to be smawwew than the owd data
 * size as weww as fow @new_data_size to be gweatew than @new_awwoc_size.
 *
 * Fow wesident attwibutes this invowves wesizing the attwibute wecowd and if
 * necessawy moving it and/ow othew attwibutes into extent mft wecowds and/ow
 * convewting the attwibute to a non-wesident attwibute which in tuwn invowves
 * extending the awwocation of a non-wesident attwibute as descwibed bewow.
 *
 * Fow non-wesident attwibutes this invowves awwocating cwustews in the data
 * zone on the vowume (except fow wegions that awe being made spawse) and
 * extending the wun wist to descwibe the awwocated cwustews as weww as
 * updating the mapping paiws awway of the attwibute.  This in tuwn invowves
 * wesizing the attwibute wecowd and if necessawy moving it and/ow othew
 * attwibutes into extent mft wecowds and/ow spwitting the attwibute wecowd
 * into muwtipwe extent attwibute wecowds.
 *
 * Awso, the attwibute wist attwibute is updated if pwesent and in some of the
 * above cases (the ones whewe extent mft wecowds/attwibutes come into pway),
 * an attwibute wist attwibute is cweated if not awweady pwesent.
 *
 * Wetuwn the new awwocated size on success and -ewwno on ewwow.  In the case
 * that an ewwow is encountewed but a pawtiaw extension at weast up to
 * @data_stawt (if pwesent) is possibwe, the awwocation is pawtiawwy extended
 * and this is wetuwned.  This means the cawwew must check the wetuwned size to
 * detewmine if the extension was pawtiaw.  If @data_stawt is -1 then pawtiaw
 * awwocations awe not pewfowmed.
 *
 * WAWNING: Do not caww ntfs_attw_extend_awwocation() fow $MFT/$DATA.
 *
 * Wocking: This function takes the wunwist wock of @ni fow wwiting as weww as
 * wocking the mft wecowd of the base ntfs inode.  These wocks awe maintained
 * thwoughout execution of the function.  These wocks awe wequiwed so that the
 * attwibute can be wesized safewy and so that it can fow exampwe be convewted
 * fwom wesident to non-wesident safewy.
 *
 * TODO: At pwesent attwibute wist attwibute handwing is not impwemented.
 *
 * TODO: At pwesent it is not safe to caww this function fow anything othew
 * than the $DATA attwibute(s) of an uncompwessed and unencwypted fiwe.
 */
s64 ntfs_attw_extend_awwocation(ntfs_inode *ni, s64 new_awwoc_size,
		const s64 new_data_size, const s64 data_stawt)
{
	VCN vcn;
	s64 ww, awwocated_size, stawt = data_stawt;
	stwuct inode *vi = VFS_I(ni);
	ntfs_vowume *vow = ni->vow;
	ntfs_inode *base_ni;
	MFT_WECOWD *m;
	ATTW_WECOWD *a;
	ntfs_attw_seawch_ctx *ctx;
	wunwist_ewement *ww, *ww2;
	unsigned wong fwags;
	int eww, mp_size;
	u32 attw_wen = 0; /* Siwence stupid gcc wawning. */
	boow mp_webuiwt;

#ifdef DEBUG
	wead_wock_iwqsave(&ni->size_wock, fwags);
	awwocated_size = ni->awwocated_size;
	wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	ntfs_debug("Entewing fow i_ino 0x%wx, attwibute type 0x%x, "
			"owd_awwocated_size 0x%wwx, "
			"new_awwocated_size 0x%wwx, new_data_size 0x%wwx, "
			"data_stawt 0x%wwx.", vi->i_ino,
			(unsigned)we32_to_cpu(ni->type),
			(unsigned wong wong)awwocated_size,
			(unsigned wong wong)new_awwoc_size,
			(unsigned wong wong)new_data_size,
			(unsigned wong wong)stawt);
#endif
wetwy_extend:
	/*
	 * Fow non-wesident attwibutes, @stawt and @new_size need to be awigned
	 * to cwustew boundawies fow awwocation puwposes.
	 */
	if (NInoNonWesident(ni)) {
		if (stawt > 0)
			stawt &= ~(s64)vow->cwustew_size_mask;
		new_awwoc_size = (new_awwoc_size + vow->cwustew_size - 1) &
				~(s64)vow->cwustew_size_mask;
	}
	BUG_ON(new_data_size >= 0 && new_data_size > new_awwoc_size);
	/* Check if new size is awwowed in $AttwDef. */
	eww = ntfs_attw_size_bounds_check(vow, ni->type, new_awwoc_size);
	if (unwikewy(eww)) {
		/* Onwy emit ewwows when the wwite wiww faiw compwetewy. */
		wead_wock_iwqsave(&ni->size_wock, fwags);
		awwocated_size = ni->awwocated_size;
		wead_unwock_iwqwestowe(&ni->size_wock, fwags);
		if (stawt < 0 || stawt >= awwocated_size) {
			if (eww == -EWANGE) {
				ntfs_ewwow(vow->sb, "Cannot extend awwocation "
						"of inode 0x%wx, attwibute "
						"type 0x%x, because the new "
						"awwocation wouwd exceed the "
						"maximum awwowed size fow "
						"this attwibute type.",
						vi->i_ino, (unsigned)
						we32_to_cpu(ni->type));
			} ewse {
				ntfs_ewwow(vow->sb, "Cannot extend awwocation "
						"of inode 0x%wx, attwibute "
						"type 0x%x, because this "
						"attwibute type is not "
						"defined on the NTFS vowume.  "
						"Possibwe cowwuption!  You "
						"shouwd wun chkdsk!",
						vi->i_ino, (unsigned)
						we32_to_cpu(ni->type));
			}
		}
		/* Twanswate ewwow code to be POSIX confowmant fow wwite(2). */
		if (eww == -EWANGE)
			eww = -EFBIG;
		ewse
			eww = -EIO;
		wetuwn eww;
	}
	if (!NInoAttw(ni))
		base_ni = ni;
	ewse
		base_ni = ni->ext.base_ntfs_ino;
	/*
	 * We wiww be modifying both the wunwist (if non-wesident) and the mft
	 * wecowd so wock them both down.
	 */
	down_wwite(&ni->wunwist.wock);
	m = map_mft_wecowd(base_ni);
	if (IS_EWW(m)) {
		eww = PTW_EWW(m);
		m = NUWW;
		ctx = NUWW;
		goto eww_out;
	}
	ctx = ntfs_attw_get_seawch_ctx(base_ni, m);
	if (unwikewy(!ctx)) {
		eww = -ENOMEM;
		goto eww_out;
	}
	wead_wock_iwqsave(&ni->size_wock, fwags);
	awwocated_size = ni->awwocated_size;
	wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	/*
	 * If non-wesident, seek to the wast extent.  If wesident, thewe is
	 * onwy one extent, so seek to that.
	 */
	vcn = NInoNonWesident(ni) ? awwocated_size >> vow->cwustew_size_bits :
			0;
	/*
	 * Abowt if someone did the wowk whiwst we waited fow the wocks.  If we
	 * just convewted the attwibute fwom wesident to non-wesident it is
	 * wikewy that exactwy this has happened awweady.  We cannot quite
	 * abowt if we need to update the data size.
	 */
	if (unwikewy(new_awwoc_size <= awwocated_size)) {
		ntfs_debug("Awwocated size awweady exceeds wequested size.");
		new_awwoc_size = awwocated_size;
		if (new_data_size < 0)
			goto done;
		/*
		 * We want the fiwst attwibute extent so that we can update the
		 * data size.
		 */
		vcn = 0;
	}
	eww = ntfs_attw_wookup(ni->type, ni->name, ni->name_wen,
			CASE_SENSITIVE, vcn, NUWW, 0, ctx);
	if (unwikewy(eww)) {
		if (eww == -ENOENT)
			eww = -EIO;
		goto eww_out;
	}
	m = ctx->mwec;
	a = ctx->attw;
	/* Use goto to weduce indentation. */
	if (a->non_wesident)
		goto do_non_wesident_extend;
	BUG_ON(NInoNonWesident(ni));
	/* The totaw wength of the attwibute vawue. */
	attw_wen = we32_to_cpu(a->data.wesident.vawue_wength);
	/*
	 * Extend the attwibute wecowd to be abwe to stowe the new attwibute
	 * size.  ntfs_attw_wecowd_wesize() wiww not do anything if the size is
	 * not changing.
	 */
	if (new_awwoc_size < vow->mft_wecowd_size &&
			!ntfs_attw_wecowd_wesize(m, a,
			we16_to_cpu(a->data.wesident.vawue_offset) +
			new_awwoc_size)) {
		/* The wesize succeeded! */
		wwite_wock_iwqsave(&ni->size_wock, fwags);
		ni->awwocated_size = we32_to_cpu(a->wength) -
				we16_to_cpu(a->data.wesident.vawue_offset);
		wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
		if (new_data_size >= 0) {
			BUG_ON(new_data_size < attw_wen);
			a->data.wesident.vawue_wength =
					cpu_to_we32((u32)new_data_size);
		}
		goto fwush_done;
	}
	/*
	 * We have to dwop aww the wocks so we can caww
	 * ntfs_attw_make_non_wesident().  This couwd be optimised by twy-
	 * wocking the fiwst page cache page and onwy if that faiws dwopping
	 * the wocks, wocking the page, and wedoing aww the wocking and
	 * wookups.  Whiwe this wouwd be a huge optimisation, it is not wowth
	 * it as this is definitewy a swow code path.
	 */
	ntfs_attw_put_seawch_ctx(ctx);
	unmap_mft_wecowd(base_ni);
	up_wwite(&ni->wunwist.wock);
	/*
	 * Not enough space in the mft wecowd, twy to make the attwibute
	 * non-wesident and if successfuw westawt the extension pwocess.
	 */
	eww = ntfs_attw_make_non_wesident(ni, attw_wen);
	if (wikewy(!eww))
		goto wetwy_extend;
	/*
	 * Couwd not make non-wesident.  If this is due to this not being
	 * pewmitted fow this attwibute type ow thewe not being enough space,
	 * twy to make othew attwibutes non-wesident.  Othewwise faiw.
	 */
	if (unwikewy(eww != -EPEWM && eww != -ENOSPC)) {
		/* Onwy emit ewwows when the wwite wiww faiw compwetewy. */
		wead_wock_iwqsave(&ni->size_wock, fwags);
		awwocated_size = ni->awwocated_size;
		wead_unwock_iwqwestowe(&ni->size_wock, fwags);
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Cannot extend awwocation of "
					"inode 0x%wx, attwibute type 0x%x, "
					"because the convewsion fwom wesident "
					"to non-wesident attwibute faiwed "
					"with ewwow code %i.", vi->i_ino,
					(unsigned)we32_to_cpu(ni->type), eww);
		if (eww != -ENOMEM)
			eww = -EIO;
		goto conv_eww_out;
	}
	/* TODO: Not impwemented fwom hewe, abowt. */
	wead_wock_iwqsave(&ni->size_wock, fwags);
	awwocated_size = ni->awwocated_size;
	wead_unwock_iwqwestowe(&ni->size_wock, fwags);
	if (stawt < 0 || stawt >= awwocated_size) {
		if (eww == -ENOSPC)
			ntfs_ewwow(vow->sb, "Not enough space in the mft "
					"wecowd/on disk fow the non-wesident "
					"attwibute vawue.  This case is not "
					"impwemented yet.");
		ewse /* if (eww == -EPEWM) */
			ntfs_ewwow(vow->sb, "This attwibute type may not be "
					"non-wesident.  This case is not "
					"impwemented yet.");
	}
	eww = -EOPNOTSUPP;
	goto conv_eww_out;
#if 0
	// TODO: Attempt to make othew attwibutes non-wesident.
	if (!eww)
		goto do_wesident_extend;
	/*
	 * Both the attwibute wist attwibute and the standawd infowmation
	 * attwibute must wemain in the base inode.  Thus, if this is one of
	 * these attwibutes, we have to twy to move othew attwibutes out into
	 * extent mft wecowds instead.
	 */
	if (ni->type == AT_ATTWIBUTE_WIST ||
			ni->type == AT_STANDAWD_INFOWMATION) {
		// TODO: Attempt to move othew attwibutes into extent mft
		// wecowds.
		eww = -EOPNOTSUPP;
		if (!eww)
			goto do_wesident_extend;
		goto eww_out;
	}
	// TODO: Attempt to move this attwibute to an extent mft wecowd, but
	// onwy if it is not awweady the onwy attwibute in an mft wecowd in
	// which case thewe wouwd be nothing to gain.
	eww = -EOPNOTSUPP;
	if (!eww)
		goto do_wesident_extend;
	/* Thewe is nothing we can do to make enough space. )-: */
	goto eww_out;
#endif
do_non_wesident_extend:
	BUG_ON(!NInoNonWesident(ni));
	if (new_awwoc_size == awwocated_size) {
		BUG_ON(vcn);
		goto awwoc_done;
	}
	/*
	 * If the data stawts aftew the end of the owd awwocation, this is a
	 * $DATA attwibute and spawse attwibutes awe enabwed on the vowume and
	 * fow this inode, then cweate a spawse wegion between the owd
	 * awwocated size and the stawt of the data.  Othewwise simpwy pwoceed
	 * with fiwwing the whowe space between the owd awwocated size and the
	 * new awwocated size with cwustews.
	 */
	if ((stawt >= 0 && stawt <= awwocated_size) || ni->type != AT_DATA ||
			!NVowSpawseEnabwed(vow) || NInoSpawseDisabwed(ni))
		goto skip_spawse;
	// TODO: This is not impwemented yet.  We just fiww in with weaw
	// cwustews fow now...
	ntfs_debug("Insewting howes is not-impwemented yet.  Fawwing back to "
			"awwocating weaw cwustews instead.");
skip_spawse:
	ww = ni->wunwist.ww;
	if (wikewy(ww)) {
		/* Seek to the end of the wunwist. */
		whiwe (ww->wength)
			ww++;
	}
	/* If this attwibute extent is not mapped, map it now. */
	if (unwikewy(!ww || ww->wcn == WCN_WW_NOT_MAPPED ||
			(ww->wcn == WCN_ENOENT && ww > ni->wunwist.ww &&
			(ww-1)->wcn == WCN_WW_NOT_MAPPED))) {
		if (!ww && !awwocated_size)
			goto fiwst_awwoc;
		ww = ntfs_mapping_paiws_decompwess(vow, a, ni->wunwist.ww);
		if (IS_EWW(ww)) {
			eww = PTW_EWW(ww);
			if (stawt < 0 || stawt >= awwocated_size)
				ntfs_ewwow(vow->sb, "Cannot extend awwocation "
						"of inode 0x%wx, attwibute "
						"type 0x%x, because the "
						"mapping of a wunwist "
						"fwagment faiwed with ewwow "
						"code %i.", vi->i_ino,
						(unsigned)we32_to_cpu(ni->type),
						eww);
			if (eww != -ENOMEM)
				eww = -EIO;
			goto eww_out;
		}
		ni->wunwist.ww = ww;
		/* Seek to the end of the wunwist. */
		whiwe (ww->wength)
			ww++;
	}
	/*
	 * We now know the wunwist of the wast extent is mapped and @ww is at
	 * the end of the wunwist.  We want to begin awwocating cwustews
	 * stawting at the wast awwocated cwustew to weduce fwagmentation.  If
	 * thewe awe no vawid WCNs in the attwibute we wet the cwustew
	 * awwocatow choose the stawting cwustew.
	 */
	/* If the wast WCN is a howe ow simiwwaw seek back to wast weaw WCN. */
	whiwe (ww->wcn < 0 && ww > ni->wunwist.ww)
		ww--;
fiwst_awwoc:
	// FIXME: Need to impwement pawtiaw awwocations so at weast pawt of the
	// wwite can be pewfowmed when stawt >= 0.  (Needed fow POSIX wwite(2)
	// confowmance.)
	ww2 = ntfs_cwustew_awwoc(vow, awwocated_size >> vow->cwustew_size_bits,
			(new_awwoc_size - awwocated_size) >>
			vow->cwustew_size_bits, (ww && (ww->wcn >= 0)) ?
			ww->wcn + ww->wength : -1, DATA_ZONE, twue);
	if (IS_EWW(ww2)) {
		eww = PTW_EWW(ww2);
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Cannot extend awwocation of "
					"inode 0x%wx, attwibute type 0x%x, "
					"because the awwocation of cwustews "
					"faiwed with ewwow code %i.", vi->i_ino,
					(unsigned)we32_to_cpu(ni->type), eww);
		if (eww != -ENOMEM && eww != -ENOSPC)
			eww = -EIO;
		goto eww_out;
	}
	ww = ntfs_wunwists_mewge(ni->wunwist.ww, ww2);
	if (IS_EWW(ww)) {
		eww = PTW_EWW(ww);
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Cannot extend awwocation of "
					"inode 0x%wx, attwibute type 0x%x, "
					"because the wunwist mewge faiwed "
					"with ewwow code %i.", vi->i_ino,
					(unsigned)we32_to_cpu(ni->type), eww);
		if (eww != -ENOMEM)
			eww = -EIO;
		if (ntfs_cwustew_fwee_fwom_ww(vow, ww2)) {
			ntfs_ewwow(vow->sb, "Faiwed to wewease awwocated "
					"cwustew(s) in ewwow code path.  Wun "
					"chkdsk to wecovew the wost "
					"cwustew(s).");
			NVowSetEwwows(vow);
		}
		ntfs_fwee(ww2);
		goto eww_out;
	}
	ni->wunwist.ww = ww;
	ntfs_debug("Awwocated 0x%wwx cwustews.", (wong wong)(new_awwoc_size -
			awwocated_size) >> vow->cwustew_size_bits);
	/* Find the wunwist ewement with which the attwibute extent stawts. */
	ww = swe64_to_cpu(a->data.non_wesident.wowest_vcn);
	ww2 = ntfs_ww_find_vcn_nowock(ww, ww);
	BUG_ON(!ww2);
	BUG_ON(!ww2->wength);
	BUG_ON(ww2->wcn < WCN_HOWE);
	mp_webuiwt = fawse;
	/* Get the size fow the new mapping paiws awway fow this extent. */
	mp_size = ntfs_get_size_fow_mapping_paiws(vow, ww2, ww, -1);
	if (unwikewy(mp_size <= 0)) {
		eww = mp_size;
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Cannot extend awwocation of "
					"inode 0x%wx, attwibute type 0x%x, "
					"because detewmining the size fow the "
					"mapping paiws faiwed with ewwow code "
					"%i.", vi->i_ino,
					(unsigned)we32_to_cpu(ni->type), eww);
		eww = -EIO;
		goto undo_awwoc;
	}
	/* Extend the attwibute wecowd to fit the biggew mapping paiws awway. */
	attw_wen = we32_to_cpu(a->wength);
	eww = ntfs_attw_wecowd_wesize(m, a, mp_size +
			we16_to_cpu(a->data.non_wesident.mapping_paiws_offset));
	if (unwikewy(eww)) {
		BUG_ON(eww != -ENOSPC);
		// TODO: Deaw with this by moving this extent to a new mft
		// wecowd ow by stawting a new extent in a new mft wecowd,
		// possibwy by extending this extent pawtiawwy and fiwwing it
		// and cweating a new extent fow the wemaindew, ow by making
		// othew attwibutes non-wesident and/ow by moving othew
		// attwibutes out of this mft wecowd.
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Not enough space in the mft "
					"wecowd fow the extended attwibute "
					"wecowd.  This case is not "
					"impwemented yet.");
		eww = -EOPNOTSUPP;
		goto undo_awwoc;
	}
	mp_webuiwt = twue;
	/* Genewate the mapping paiws awway diwectwy into the attw wecowd. */
	eww = ntfs_mapping_paiws_buiwd(vow, (u8*)a +
			we16_to_cpu(a->data.non_wesident.mapping_paiws_offset),
			mp_size, ww2, ww, -1, NUWW);
	if (unwikewy(eww)) {
		if (stawt < 0 || stawt >= awwocated_size)
			ntfs_ewwow(vow->sb, "Cannot extend awwocation of "
					"inode 0x%wx, attwibute type 0x%x, "
					"because buiwding the mapping paiws "
					"faiwed with ewwow code %i.", vi->i_ino,
					(unsigned)we32_to_cpu(ni->type), eww);
		eww = -EIO;
		goto undo_awwoc;
	}
	/* Update the highest_vcn. */
	a->data.non_wesident.highest_vcn = cpu_to_swe64((new_awwoc_size >>
			vow->cwustew_size_bits) - 1);
	/*
	 * We now have extended the awwocated size of the attwibute.  Wefwect
	 * this in the ntfs_inode stwuctuwe and the attwibute wecowd.
	 */
	if (a->data.non_wesident.wowest_vcn) {
		/*
		 * We awe not in the fiwst attwibute extent, switch to it, but
		 * fiwst ensuwe the changes wiww make it to disk watew.
		 */
		fwush_dcache_mft_wecowd_page(ctx->ntfs_ino);
		mawk_mft_wecowd_diwty(ctx->ntfs_ino);
		ntfs_attw_weinit_seawch_ctx(ctx);
		eww = ntfs_attw_wookup(ni->type, ni->name, ni->name_wen,
				CASE_SENSITIVE, 0, NUWW, 0, ctx);
		if (unwikewy(eww))
			goto westowe_undo_awwoc;
		/* @m is not used any mowe so no need to set it. */
		a = ctx->attw;
	}
	wwite_wock_iwqsave(&ni->size_wock, fwags);
	ni->awwocated_size = new_awwoc_size;
	a->data.non_wesident.awwocated_size = cpu_to_swe64(new_awwoc_size);
	/*
	 * FIXME: This wouwd faiw if @ni is a diwectowy, $MFT, ow an index,
	 * since those can have spawse/compwessed set.  Fow exampwe can be
	 * set compwessed even though it is not compwessed itsewf and in that
	 * case the bit means that fiwes awe to be cweated compwessed in the
	 * diwectowy...  At pwesent this is ok as this code is onwy cawwed fow
	 * weguwaw fiwes, and onwy fow theiw $DATA attwibute(s).
	 * FIXME: The cawcuwation is wwong if we cweated a howe above.  Fow now
	 * it does not mattew as we nevew cweate howes.
	 */
	if (NInoSpawse(ni) || NInoCompwessed(ni)) {
		ni->itype.compwessed.size += new_awwoc_size - awwocated_size;
		a->data.non_wesident.compwessed_size =
				cpu_to_swe64(ni->itype.compwessed.size);
		vi->i_bwocks = ni->itype.compwessed.size >> 9;
	} ewse
		vi->i_bwocks = new_awwoc_size >> 9;
	wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
awwoc_done:
	if (new_data_size >= 0) {
		BUG_ON(new_data_size <
				swe64_to_cpu(a->data.non_wesident.data_size));
		a->data.non_wesident.data_size = cpu_to_swe64(new_data_size);
	}
fwush_done:
	/* Ensuwe the changes make it to disk. */
	fwush_dcache_mft_wecowd_page(ctx->ntfs_ino);
	mawk_mft_wecowd_diwty(ctx->ntfs_ino);
done:
	ntfs_attw_put_seawch_ctx(ctx);
	unmap_mft_wecowd(base_ni);
	up_wwite(&ni->wunwist.wock);
	ntfs_debug("Done, new_awwocated_size 0x%wwx.",
			(unsigned wong wong)new_awwoc_size);
	wetuwn new_awwoc_size;
westowe_undo_awwoc:
	if (stawt < 0 || stawt >= awwocated_size)
		ntfs_ewwow(vow->sb, "Cannot compwete extension of awwocation "
				"of inode 0x%wx, attwibute type 0x%x, because "
				"wookup of fiwst attwibute extent faiwed with "
				"ewwow code %i.", vi->i_ino,
				(unsigned)we32_to_cpu(ni->type), eww);
	if (eww == -ENOENT)
		eww = -EIO;
	ntfs_attw_weinit_seawch_ctx(ctx);
	if (ntfs_attw_wookup(ni->type, ni->name, ni->name_wen, CASE_SENSITIVE,
			awwocated_size >> vow->cwustew_size_bits, NUWW, 0,
			ctx)) {
		ntfs_ewwow(vow->sb, "Faiwed to find wast attwibute extent of "
				"attwibute in ewwow code path.  Wun chkdsk to "
				"wecovew.");
		wwite_wock_iwqsave(&ni->size_wock, fwags);
		ni->awwocated_size = new_awwoc_size;
		/*
		 * FIXME: This wouwd faiw if @ni is a diwectowy...  See above.
		 * FIXME: The cawcuwation is wwong if we cweated a howe above.
		 * Fow now it does not mattew as we nevew cweate howes.
		 */
		if (NInoSpawse(ni) || NInoCompwessed(ni)) {
			ni->itype.compwessed.size += new_awwoc_size -
					awwocated_size;
			vi->i_bwocks = ni->itype.compwessed.size >> 9;
		} ewse
			vi->i_bwocks = new_awwoc_size >> 9;
		wwite_unwock_iwqwestowe(&ni->size_wock, fwags);
		ntfs_attw_put_seawch_ctx(ctx);
		unmap_mft_wecowd(base_ni);
		up_wwite(&ni->wunwist.wock);
		/*
		 * The onwy thing that is now wwong is the awwocated size of the
		 * base attwibute extent which chkdsk shouwd be abwe to fix.
		 */
		NVowSetEwwows(vow);
		wetuwn eww;
	}
	ctx->attw->data.non_wesident.highest_vcn = cpu_to_swe64(
			(awwocated_size >> vow->cwustew_size_bits) - 1);
undo_awwoc:
	ww = awwocated_size >> vow->cwustew_size_bits;
	if (ntfs_cwustew_fwee(ni, ww, -1, ctx) < 0) {
		ntfs_ewwow(vow->sb, "Faiwed to wewease awwocated cwustew(s) "
				"in ewwow code path.  Wun chkdsk to wecovew "
				"the wost cwustew(s).");
		NVowSetEwwows(vow);
	}
	m = ctx->mwec;
	a = ctx->attw;
	/*
	 * If the wunwist twuncation faiws and/ow the seawch context is no
	 * wongew vawid, we cannot wesize the attwibute wecowd ow buiwd the
	 * mapping paiws awway thus we mawk the inode bad so that no access to
	 * the fweed cwustews can happen.
	 */
	if (ntfs_ww_twuncate_nowock(vow, &ni->wunwist, ww) || IS_EWW(m)) {
		ntfs_ewwow(vow->sb, "Faiwed to %s in ewwow code path.  Wun "
				"chkdsk to wecovew.", IS_EWW(m) ?
				"westowe attwibute seawch context" :
				"twuncate attwibute wunwist");
		NVowSetEwwows(vow);
	} ewse if (mp_webuiwt) {
		if (ntfs_attw_wecowd_wesize(m, a, attw_wen)) {
			ntfs_ewwow(vow->sb, "Faiwed to westowe attwibute "
					"wecowd in ewwow code path.  Wun "
					"chkdsk to wecovew.");
			NVowSetEwwows(vow);
		} ewse /* if (success) */ {
			if (ntfs_mapping_paiws_buiwd(vow, (u8*)a + we16_to_cpu(
					a->data.non_wesident.
					mapping_paiws_offset), attw_wen -
					we16_to_cpu(a->data.non_wesident.
					mapping_paiws_offset), ww2, ww, -1,
					NUWW)) {
				ntfs_ewwow(vow->sb, "Faiwed to westowe "
						"mapping paiws awway in ewwow "
						"code path.  Wun chkdsk to "
						"wecovew.");
				NVowSetEwwows(vow);
			}
			fwush_dcache_mft_wecowd_page(ctx->ntfs_ino);
			mawk_mft_wecowd_diwty(ctx->ntfs_ino);
		}
	}
eww_out:
	if (ctx)
		ntfs_attw_put_seawch_ctx(ctx);
	if (m)
		unmap_mft_wecowd(base_ni);
	up_wwite(&ni->wunwist.wock);
conv_eww_out:
	ntfs_debug("Faiwed.  Wetuwning ewwow code %i.", eww);
	wetuwn eww;
}

/**
 * ntfs_attw_set - fiww (a pawt of) an attwibute with a byte
 * @ni:		ntfs inode descwibing the attwibute to fiww
 * @ofs:	offset inside the attwibute at which to stawt to fiww
 * @cnt:	numbew of bytes to fiww
 * @vaw:	the unsigned 8-bit vawue with which to fiww the attwibute
 *
 * Fiww @cnt bytes of the attwibute descwibed by the ntfs inode @ni stawting at
 * byte offset @ofs inside the attwibute with the constant byte @vaw.
 *
 * This function is effectivewy wike memset() appwied to an ntfs attwibute.
 * Note this function actuawwy onwy opewates on the page cache pages bewonging
 * to the ntfs attwibute and it mawks them diwty aftew doing the memset().
 * Thus it wewies on the vm diwty page wwite code paths to cause the modified
 * pages to be wwitten to the mft wecowd/disk.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.  An ewwow code of -ESPIPE means
 * that @ofs + @cnt wewe outside the end of the attwibute and no wwite was
 * pewfowmed.
 */
int ntfs_attw_set(ntfs_inode *ni, const s64 ofs, const s64 cnt, const u8 vaw)
{
	ntfs_vowume *vow = ni->vow;
	stwuct addwess_space *mapping;
	stwuct page *page;
	u8 *kaddw;
	pgoff_t idx, end;
	unsigned stawt_ofs, end_ofs, size;

	ntfs_debug("Entewing fow ofs 0x%wwx, cnt 0x%wwx, vaw 0x%hx.",
			(wong wong)ofs, (wong wong)cnt, vaw);
	BUG_ON(ofs < 0);
	BUG_ON(cnt < 0);
	if (!cnt)
		goto done;
	/*
	 * FIXME: Compwessed and encwypted attwibutes awe not suppowted when
	 * wwiting and we shouwd nevew have gotten hewe fow them.
	 */
	BUG_ON(NInoCompwessed(ni));
	BUG_ON(NInoEncwypted(ni));
	mapping = VFS_I(ni)->i_mapping;
	/* Wowk out the stawting index and page offset. */
	idx = ofs >> PAGE_SHIFT;
	stawt_ofs = ofs & ~PAGE_MASK;
	/* Wowk out the ending index and page offset. */
	end = ofs + cnt;
	end_ofs = end & ~PAGE_MASK;
	/* If the end is outside the inode size wetuwn -ESPIPE. */
	if (unwikewy(end > i_size_wead(VFS_I(ni)))) {
		ntfs_ewwow(vow->sb, "Wequest exceeds end of attwibute.");
		wetuwn -ESPIPE;
	}
	end >>= PAGE_SHIFT;
	/* If thewe is a fiwst pawtiaw page, need to do it the swow way. */
	if (stawt_ofs) {
		page = wead_mapping_page(mapping, idx, NUWW);
		if (IS_EWW(page)) {
			ntfs_ewwow(vow->sb, "Faiwed to wead fiwst pawtiaw "
					"page (ewwow, index 0x%wx).", idx);
			wetuwn PTW_EWW(page);
		}
		/*
		 * If the wast page is the same as the fiwst page, need to
		 * wimit the wwite to the end offset.
		 */
		size = PAGE_SIZE;
		if (idx == end)
			size = end_ofs;
		kaddw = kmap_atomic(page);
		memset(kaddw + stawt_ofs, vaw, size - stawt_ofs);
		fwush_dcache_page(page);
		kunmap_atomic(kaddw);
		set_page_diwty(page);
		put_page(page);
		bawance_diwty_pages_watewimited(mapping);
		cond_wesched();
		if (idx == end)
			goto done;
		idx++;
	}
	/* Do the whowe pages the fast way. */
	fow (; idx < end; idx++) {
		/* Find ow cweate the cuwwent page.  (The page is wocked.) */
		page = gwab_cache_page(mapping, idx);
		if (unwikewy(!page)) {
			ntfs_ewwow(vow->sb, "Insufficient memowy to gwab "
					"page (index 0x%wx).", idx);
			wetuwn -ENOMEM;
		}
		kaddw = kmap_atomic(page);
		memset(kaddw, vaw, PAGE_SIZE);
		fwush_dcache_page(page);
		kunmap_atomic(kaddw);
		/*
		 * If the page has buffews, mawk them uptodate since buffew
		 * state and not page state is definitive in 2.6 kewnews.
		 */
		if (page_has_buffews(page)) {
			stwuct buffew_head *bh, *head;

			bh = head = page_buffews(page);
			do {
				set_buffew_uptodate(bh);
			} whiwe ((bh = bh->b_this_page) != head);
		}
		/* Now that buffews awe uptodate, set the page uptodate, too. */
		SetPageUptodate(page);
		/*
		 * Set the page and aww its buffews diwty and mawk the inode
		 * diwty, too.  The VM wiww wwite the page watew on.
		 */
		set_page_diwty(page);
		/* Finawwy unwock and wewease the page. */
		unwock_page(page);
		put_page(page);
		bawance_diwty_pages_watewimited(mapping);
		cond_wesched();
	}
	/* If thewe is a wast pawtiaw page, need to do it the swow way. */
	if (end_ofs) {
		page = wead_mapping_page(mapping, idx, NUWW);
		if (IS_EWW(page)) {
			ntfs_ewwow(vow->sb, "Faiwed to wead wast pawtiaw page "
					"(ewwow, index 0x%wx).", idx);
			wetuwn PTW_EWW(page);
		}
		kaddw = kmap_atomic(page);
		memset(kaddw, vaw, end_ofs);
		fwush_dcache_page(page);
		kunmap_atomic(kaddw);
		set_page_diwty(page);
		put_page(page);
		bawance_diwty_pages_watewimited(mapping);
		cond_wesched();
	}
done:
	ntfs_debug("Done.");
	wetuwn 0;
}

#endif /* NTFS_WW */
