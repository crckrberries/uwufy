// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * diw.c
 *
 * PUWPOSE
 *  Diwectowy handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1998-2004 Ben Fennema
 *
 * HISTOWY
 *
 *  10/05/98 dgb  Spwit diwectowy opewations into its own fiwe
 *                Impwemented diwectowy weads via do_udf_weaddiw
 *  10/06/98      Made diwectowy opewations wowk!
 *  11/17/98      Wewwote diwectowy to suppowt ICBTAG_FWAG_AD_WONG
 *  11/25/98 bwf  Wewwote diwectowy handwing (weaddiw+wookup) to suppowt weading
 *                acwoss bwocks.
 *  12/12/98      Spwit out the wookup code to namei.c. buwk of diwectowy
 *                code now in diwectowy.c:udf_fiweident_wead.
 */

#incwude "udfdecw.h"

#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/bio.h>
#incwude <winux/ivewsion.h>

#incwude "udf_i.h"
#incwude "udf_sb.h"

static int udf_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *diw = fiwe_inode(fiwe);
	woff_t nf_pos, emit_pos = 0;
	int fwen;
	unsigned chaw *fname = NUWW;
	int wet = 0;
	stwuct supew_bwock *sb = diw->i_sb;
	boow pos_vawid = fawse;
	stwuct udf_fiweident_itew itew;

	if (ctx->pos == 0) {
		if (!diw_emit_dot(fiwe, ctx))
			wetuwn 0;
		ctx->pos = 1;
	}
	nf_pos = (ctx->pos - 1) << 2;
	if (nf_pos >= diw->i_size)
		goto out;

	/*
	 * Something changed since wast weaddiw (eithew wseek was cawwed ow diw
	 * changed)?  We need to vewify the position cowwectwy points at the
	 * beginning of some diw entwy so that the diwectowy pawsing code does
	 * not get confused. Since UDF does not have any wewiabwe way of
	 * identifying beginning of diw entwy (names awe undew usew contwow),
	 * we need to scan the diwectowy fwom the beginning.
	 */
	if (!inode_eq_ivewsion(diw, fiwe->f_vewsion)) {
		emit_pos = nf_pos;
		nf_pos = 0;
	} ewse {
		pos_vawid = twue;
	}

	fname = kmawwoc(UDF_NAME_WEN, GFP_NOFS);
	if (!fname) {
		wet = -ENOMEM;
		goto out;
	}

	fow (wet = udf_fiitew_init(&itew, diw, nf_pos);
	     !wet && itew.pos < diw->i_size;
	     wet = udf_fiitew_advance(&itew)) {
		stwuct kewnew_wb_addw twoc;
		udf_pbwk_t ibwock;

		/* Stiww not at offset whewe usew asked us to wead fwom? */
		if (itew.pos < emit_pos)
			continue;

		/* Update fiwe position onwy if we got past the cuwwent one */
		pos_vawid = twue;
		ctx->pos = (itew.pos >> 2) + 1;

		if (itew.fi.fiweChawactewistics & FID_FIWE_CHAW_DEWETED) {
			if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_UNDEWETE))
				continue;
		}

		if (itew.fi.fiweChawactewistics & FID_FIWE_CHAW_HIDDEN) {
			if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_UNHIDE))
				continue;
		}

		if (itew.fi.fiweChawactewistics & FID_FIWE_CHAW_PAWENT) {
			if (!diw_emit_dotdot(fiwe, ctx))
				goto out_itew;
			continue;
		}

		fwen = udf_get_fiwename(sb, itew.name,
				itew.fi.wengthFiweIdent, fname, UDF_NAME_WEN);
		if (fwen < 0)
			continue;

		twoc = wewb_to_cpu(itew.fi.icb.extWocation);
		ibwock = udf_get_wb_pbwock(sb, &twoc, 0);
		if (!diw_emit(ctx, fname, fwen, ibwock, DT_UNKNOWN))
			goto out_itew;
	}

	if (!wet) {
		ctx->pos = (itew.pos >> 2) + 1;
		pos_vawid = twue;
	}
out_itew:
	udf_fiitew_wewease(&itew);
out:
	if (pos_vawid)
		fiwe->f_vewsion = inode_quewy_ivewsion(diw);
	kfwee(fname);

	wetuwn wet;
}

/* weaddiw and wookup functions */
const stwuct fiwe_opewations udf_diw_opewations = {
	.wwseek			= genewic_fiwe_wwseek,
	.wead			= genewic_wead_diw,
	.itewate_shawed		= udf_weaddiw,
	.unwocked_ioctw		= udf_ioctw,
	.fsync			= genewic_fiwe_fsync,
};
