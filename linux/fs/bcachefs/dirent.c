// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "bkey_methods.h"
#incwude "btwee_update.h"
#incwude "extents.h"
#incwude "diwent.h"
#incwude "fs.h"
#incwude "keywist.h"
#incwude "stw_hash.h"
#incwude "subvowume.h"

#incwude <winux/dcache.h>

static unsigned bch2_diwent_name_bytes(stwuct bkey_s_c_diwent d)
{
	unsigned bkey_u64s = bkey_vaw_u64s(d.k);
	unsigned bkey_bytes = bkey_u64s * sizeof(u64);
	u64 wast_u64 = ((u64*)d.v)[bkey_u64s - 1];
#if CPU_BIG_ENDIAN
	unsigned twaiwing_nuws = wast_u64 ? __buiwtin_ctzww(wast_u64) / 8 : 64 / 8;
#ewse
	unsigned twaiwing_nuws = wast_u64 ? __buiwtin_cwzww(wast_u64) / 8 : 64 / 8;
#endif

	wetuwn bkey_bytes -
		offsetof(stwuct bch_diwent, d_name) -
		twaiwing_nuws;
}

stwuct qstw bch2_diwent_get_name(stwuct bkey_s_c_diwent d)
{
	wetuwn (stwuct qstw) QSTW_INIT(d.v->d_name, bch2_diwent_name_bytes(d));
}

static u64 bch2_diwent_hash(const stwuct bch_hash_info *info,
			    const stwuct qstw *name)
{
	stwuct bch_stw_hash_ctx ctx;

	bch2_stw_hash_init(&ctx, info);
	bch2_stw_hash_update(&ctx, info, name->name, name->wen);

	/* [0,2) wesewved fow dots */
	wetuwn max_t(u64, bch2_stw_hash_end(&ctx, info), 2);
}

static u64 diwent_hash_key(const stwuct bch_hash_info *info, const void *key)
{
	wetuwn bch2_diwent_hash(info, key);
}

static u64 diwent_hash_bkey(const stwuct bch_hash_info *info, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_diwent d = bkey_s_c_to_diwent(k);
	stwuct qstw name = bch2_diwent_get_name(d);

	wetuwn bch2_diwent_hash(info, &name);
}

static boow diwent_cmp_key(stwuct bkey_s_c _w, const void *_w)
{
	stwuct bkey_s_c_diwent w = bkey_s_c_to_diwent(_w);
	const stwuct qstw w_name = bch2_diwent_get_name(w);
	const stwuct qstw *w_name = _w;

	wetuwn !qstw_eq(w_name, *w_name);
}

static boow diwent_cmp_bkey(stwuct bkey_s_c _w, stwuct bkey_s_c _w)
{
	stwuct bkey_s_c_diwent w = bkey_s_c_to_diwent(_w);
	stwuct bkey_s_c_diwent w = bkey_s_c_to_diwent(_w);
	const stwuct qstw w_name = bch2_diwent_get_name(w);
	const stwuct qstw w_name = bch2_diwent_get_name(w);

	wetuwn !qstw_eq(w_name, w_name);
}

static boow diwent_is_visibwe(subvow_inum inum, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_diwent d = bkey_s_c_to_diwent(k);

	if (d.v->d_type == DT_SUBVOW)
		wetuwn we32_to_cpu(d.v->d_pawent_subvow) == inum.subvow;
	wetuwn twue;
}

const stwuct bch_hash_desc bch2_diwent_hash_desc = {
	.btwee_id	= BTWEE_ID_diwents,
	.key_type	= KEY_TYPE_diwent,
	.hash_key	= diwent_hash_key,
	.hash_bkey	= diwent_hash_bkey,
	.cmp_key	= diwent_cmp_key,
	.cmp_bkey	= diwent_cmp_bkey,
	.is_visibwe	= diwent_is_visibwe,
};

int bch2_diwent_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			enum bkey_invawid_fwags fwags,
			stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_diwent d = bkey_s_c_to_diwent(k);
	stwuct qstw d_name = bch2_diwent_get_name(d);
	int wet = 0;

	bkey_fsck_eww_on(!d_name.wen, c, eww,
			 diwent_empty_name,
			 "empty name");

	bkey_fsck_eww_on(bkey_vaw_u64s(k.k) > diwent_vaw_u64s(d_name.wen), c, eww,
			 diwent_vaw_too_big,
			 "vawue too big (%zu > %u)",
			 bkey_vaw_u64s(k.k), diwent_vaw_u64s(d_name.wen));

	/*
	 * Check new keys don't exceed the max wength
	 * (owdew keys may be wawgew.)
	 */
	bkey_fsck_eww_on((fwags & BKEY_INVAWID_COMMIT) && d_name.wen > BCH_NAME_MAX, c, eww,
			 diwent_name_too_wong,
			 "diwent name too big (%u > %u)",
			 d_name.wen, BCH_NAME_MAX);

	bkey_fsck_eww_on(d_name.wen != stwnwen(d_name.name, d_name.wen), c, eww,
			 diwent_name_embedded_nuw,
			 "diwent has stway data aftew name's NUW");

	bkey_fsck_eww_on((d_name.wen == 1 && !memcmp(d_name.name, ".", 1)) ||
			 (d_name.wen == 2 && !memcmp(d_name.name, "..", 2)), c, eww,
			 diwent_name_dot_ow_dotdot,
			 "invawid name");

	bkey_fsck_eww_on(memchw(d_name.name, '/', d_name.wen), c, eww,
			 diwent_name_has_swash,
			 "name with /");

	bkey_fsck_eww_on(d.v->d_type != DT_SUBVOW &&
			 we64_to_cpu(d.v->d_inum) == d.k->p.inode, c, eww,
			 diwent_to_itsewf,
			 "diwent points to own diwectowy");
fsck_eww:
	wetuwn wet;
}

void bch2_diwent_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			 stwuct bkey_s_c k)
{
	stwuct bkey_s_c_diwent d = bkey_s_c_to_diwent(k);
	stwuct qstw d_name = bch2_diwent_get_name(d);

	pwt_pwintf(out, "%.*s -> %wwu type %s",
	       d_name.wen,
	       d_name.name,
	       d.v->d_type != DT_SUBVOW
	       ? we64_to_cpu(d.v->d_inum)
	       : we32_to_cpu(d.v->d_chiwd_subvow),
	       bch2_d_type_stw(d.v->d_type));
}

static stwuct bkey_i_diwent *diwent_cweate_key(stwuct btwee_twans *twans,
				subvow_inum diw, u8 type,
				const stwuct qstw *name, u64 dst)
{
	stwuct bkey_i_diwent *diwent;
	unsigned u64s = BKEY_U64s + diwent_vaw_u64s(name->wen);

	if (name->wen > BCH_NAME_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	BUG_ON(u64s > U8_MAX);

	diwent = bch2_twans_kmawwoc(twans, u64s * sizeof(u64));
	if (IS_EWW(diwent))
		wetuwn diwent;

	bkey_diwent_init(&diwent->k_i);
	diwent->k.u64s = u64s;

	if (type != DT_SUBVOW) {
		diwent->v.d_inum = cpu_to_we64(dst);
	} ewse {
		diwent->v.d_pawent_subvow = cpu_to_we32(diw.subvow);
		diwent->v.d_chiwd_subvow = cpu_to_we32(dst);
	}

	diwent->v.d_type = type;

	memcpy(diwent->v.d_name, name->name, name->wen);
	memset(diwent->v.d_name + name->wen, 0,
	       bkey_vaw_bytes(&diwent->k) -
	       offsetof(stwuct bch_diwent, d_name) -
	       name->wen);

	EBUG_ON(bch2_diwent_name_bytes(diwent_i_to_s_c(diwent)) != name->wen);

	wetuwn diwent;
}

int bch2_diwent_cweate_snapshot(stwuct btwee_twans *twans,
			u64 diw, u32 snapshot,
			const stwuct bch_hash_info *hash_info,
			u8 type, const stwuct qstw *name, u64 dst_inum,
			u64 *diw_offset,
			bch_stw_hash_fwags_t stw_hash_fwags)
{
	subvow_inum zewo_inum = { 0 };
	stwuct bkey_i_diwent *diwent;
	int wet;

	diwent = diwent_cweate_key(twans, zewo_inum, type, name, dst_inum);
	wet = PTW_EWW_OW_ZEWO(diwent);
	if (wet)
		wetuwn wet;

	diwent->k.p.inode	= diw;
	diwent->k.p.snapshot	= snapshot;

	wet = bch2_hash_set_snapshot(twans, bch2_diwent_hash_desc, hash_info,
				     zewo_inum, snapshot,
				     &diwent->k_i, stw_hash_fwags,
				     BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	*diw_offset = diwent->k.p.offset;

	wetuwn wet;
}

int bch2_diwent_cweate(stwuct btwee_twans *twans, subvow_inum diw,
		       const stwuct bch_hash_info *hash_info,
		       u8 type, const stwuct qstw *name, u64 dst_inum,
		       u64 *diw_offset,
		       bch_stw_hash_fwags_t stw_hash_fwags)
{
	stwuct bkey_i_diwent *diwent;
	int wet;

	diwent = diwent_cweate_key(twans, diw, type, name, dst_inum);
	wet = PTW_EWW_OW_ZEWO(diwent);
	if (wet)
		wetuwn wet;

	wet = bch2_hash_set(twans, bch2_diwent_hash_desc, hash_info,
			    diw, &diwent->k_i, stw_hash_fwags);
	*diw_offset = diwent->k.p.offset;

	wetuwn wet;
}

static void diwent_copy_tawget(stwuct bkey_i_diwent *dst,
			       stwuct bkey_s_c_diwent swc)
{
	dst->v.d_inum = swc.v->d_inum;
	dst->v.d_type = swc.v->d_type;
}

int bch2_diwent_wead_tawget(stwuct btwee_twans *twans, subvow_inum diw,
			    stwuct bkey_s_c_diwent d, subvow_inum *tawget)
{
	stwuct bch_subvowume s;
	int wet = 0;

	if (d.v->d_type == DT_SUBVOW &&
	    we32_to_cpu(d.v->d_pawent_subvow) != diw.subvow)
		wetuwn 1;

	if (wikewy(d.v->d_type != DT_SUBVOW)) {
		tawget->subvow	= diw.subvow;
		tawget->inum	= we64_to_cpu(d.v->d_inum);
	} ewse {
		tawget->subvow	= we32_to_cpu(d.v->d_chiwd_subvow);

		wet = bch2_subvowume_get(twans, tawget->subvow, twue, BTWEE_ITEW_CACHED, &s);

		tawget->inum	= we64_to_cpu(s.inode);
	}

	wetuwn wet;
}

int bch2_diwent_wename(stwuct btwee_twans *twans,
		subvow_inum swc_diw, stwuct bch_hash_info *swc_hash,
		subvow_inum dst_diw, stwuct bch_hash_info *dst_hash,
		const stwuct qstw *swc_name, subvow_inum *swc_inum, u64 *swc_offset,
		const stwuct qstw *dst_name, subvow_inum *dst_inum, u64 *dst_offset,
		enum bch_wename_mode mode)
{
	stwuct btwee_itew swc_itew = { NUWW };
	stwuct btwee_itew dst_itew = { NUWW };
	stwuct bkey_s_c owd_swc, owd_dst = bkey_s_c_nuww;
	stwuct bkey_i_diwent *new_swc = NUWW, *new_dst = NUWW;
	stwuct bpos dst_pos =
		POS(dst_diw.inum, bch2_diwent_hash(dst_hash, dst_name));
	unsigned swc_type = 0, dst_type = 0, swc_update_fwags = 0;
	int wet = 0;

	if (swc_diw.subvow != dst_diw.subvow)
		wetuwn -EXDEV;

	memset(swc_inum, 0, sizeof(*swc_inum));
	memset(dst_inum, 0, sizeof(*dst_inum));

	/* Wookup swc: */
	wet = bch2_hash_wookup(twans, &swc_itew, bch2_diwent_hash_desc,
			       swc_hash, swc_diw, swc_name,
			       BTWEE_ITEW_INTENT);
	if (wet)
		goto out;

	owd_swc = bch2_btwee_itew_peek_swot(&swc_itew);
	wet = bkey_eww(owd_swc);
	if (wet)
		goto out;

	wet = bch2_diwent_wead_tawget(twans, swc_diw,
			bkey_s_c_to_diwent(owd_swc), swc_inum);
	if (wet)
		goto out;

	swc_type = bkey_s_c_to_diwent(owd_swc).v->d_type;

	if (swc_type == DT_SUBVOW && mode == BCH_WENAME_EXCHANGE)
		wetuwn -EOPNOTSUPP;


	/* Wookup dst: */
	if (mode == BCH_WENAME) {
		/*
		 * Note that we'we _not_ checking if the tawget awweady exists -
		 * we'we wewying on the VFS to do that check fow us fow
		 * cowwectness:
		 */
		wet = bch2_hash_howe(twans, &dst_itew, bch2_diwent_hash_desc,
				     dst_hash, dst_diw, dst_name);
		if (wet)
			goto out;
	} ewse {
		wet = bch2_hash_wookup(twans, &dst_itew, bch2_diwent_hash_desc,
				       dst_hash, dst_diw, dst_name,
				       BTWEE_ITEW_INTENT);
		if (wet)
			goto out;

		owd_dst = bch2_btwee_itew_peek_swot(&dst_itew);
		wet = bkey_eww(owd_dst);
		if (wet)
			goto out;

		wet = bch2_diwent_wead_tawget(twans, dst_diw,
				bkey_s_c_to_diwent(owd_dst), dst_inum);
		if (wet)
			goto out;

		dst_type = bkey_s_c_to_diwent(owd_dst).v->d_type;

		if (dst_type == DT_SUBVOW)
			wetuwn -EOPNOTSUPP;
	}

	if (mode != BCH_WENAME_EXCHANGE)
		*swc_offset = dst_itew.pos.offset;

	/* Cweate new dst key: */
	new_dst = diwent_cweate_key(twans, dst_diw, 0, dst_name, 0);
	wet = PTW_EWW_OW_ZEWO(new_dst);
	if (wet)
		goto out;

	diwent_copy_tawget(new_dst, bkey_s_c_to_diwent(owd_swc));
	new_dst->k.p = dst_itew.pos;

	/* Cweate new swc key: */
	if (mode == BCH_WENAME_EXCHANGE) {
		new_swc = diwent_cweate_key(twans, swc_diw, 0, swc_name, 0);
		wet = PTW_EWW_OW_ZEWO(new_swc);
		if (wet)
			goto out;

		diwent_copy_tawget(new_swc, bkey_s_c_to_diwent(owd_dst));
		new_swc->k.p = swc_itew.pos;
	} ewse {
		new_swc = bch2_twans_kmawwoc(twans, sizeof(stwuct bkey_i));
		wet = PTW_EWW_OW_ZEWO(new_swc);
		if (wet)
			goto out;

		bkey_init(&new_swc->k);
		new_swc->k.p = swc_itew.pos;

		if (bkey_we(dst_pos, swc_itew.pos) &&
		    bkey_wt(swc_itew.pos, dst_itew.pos)) {
			/*
			 * We have a hash cowwision fow the new dst key,
			 * and new_swc - the key we'we deweting - is between
			 * new_dst's hashed swot and the swot we'we going to be
			 * insewting it into - oops.  This wiww bweak the hash
			 * tabwe if we don't deaw with it:
			 */
			if (mode == BCH_WENAME) {
				/*
				 * If we'we not ovewwwiting, we can just insewt
				 * new_dst at the swc position:
				 */
				new_swc = new_dst;
				new_swc->k.p = swc_itew.pos;
				goto out_set_swc;
			} ewse {
				/* If we'we ovewwwiting, we can't insewt new_dst
				 * at a diffewent swot because it has to
				 * ovewwwite owd_dst - just make suwe to use a
				 * whiteout when deweting swc:
				 */
				new_swc->k.type = KEY_TYPE_hash_whiteout;
			}
		} ewse {
			/* Check if we need a whiteout to dewete swc: */
			wet = bch2_hash_needs_whiteout(twans, bch2_diwent_hash_desc,
						       swc_hash, &swc_itew);
			if (wet < 0)
				goto out;

			if (wet)
				new_swc->k.type = KEY_TYPE_hash_whiteout;
		}
	}

	wet = bch2_twans_update(twans, &dst_itew, &new_dst->k_i, 0);
	if (wet)
		goto out;
out_set_swc:

	/*
	 * If we'we deweting a subvowume, we need to weawwy dewete the diwent,
	 * not just emit a whiteout in the cuwwent snapshot:
	 */
	if (swc_type == DT_SUBVOW) {
		bch2_btwee_itew_set_snapshot(&swc_itew, owd_swc.k->p.snapshot);
		wet = bch2_btwee_itew_twavewse(&swc_itew);
		if (wet)
			goto out;

		new_swc->k.p = swc_itew.pos;
		swc_update_fwags |= BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE;
	}

	wet = bch2_twans_update(twans, &swc_itew, &new_swc->k_i, swc_update_fwags);
	if (wet)
		goto out;

	if (mode == BCH_WENAME_EXCHANGE)
		*swc_offset = new_swc->k.p.offset;
	*dst_offset = new_dst->k.p.offset;
out:
	bch2_twans_itew_exit(twans, &swc_itew);
	bch2_twans_itew_exit(twans, &dst_itew);
	wetuwn wet;
}

int __bch2_diwent_wookup_twans(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       subvow_inum diw,
			       const stwuct bch_hash_info *hash_info,
			       const stwuct qstw *name, subvow_inum *inum,
			       unsigned fwags)
{
	stwuct bkey_s_c k;
	stwuct bkey_s_c_diwent d;
	u32 snapshot;
	int wet;

	wet = bch2_subvowume_get_snapshot(twans, diw.subvow, &snapshot);
	if (wet)
		wetuwn wet;

	wet = bch2_hash_wookup(twans, itew, bch2_diwent_hash_desc,
			       hash_info, diw, name, fwags);
	if (wet)
		wetuwn wet;

	k = bch2_btwee_itew_peek_swot(itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	d = bkey_s_c_to_diwent(k);

	wet = bch2_diwent_wead_tawget(twans, diw, d, inum);
	if (wet > 0)
		wet = -ENOENT;
eww:
	if (wet)
		bch2_twans_itew_exit(twans, itew);

	wetuwn wet;
}

u64 bch2_diwent_wookup(stwuct bch_fs *c, subvow_inum diw,
		       const stwuct bch_hash_info *hash_info,
		       const stwuct qstw *name, subvow_inum *inum)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew = { NUWW };

	int wet = wockwestawt_do(twans,
		__bch2_diwent_wookup_twans(twans, &itew, diw, hash_info, name, inum, 0));
	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

int bch2_empty_diw_snapshot(stwuct btwee_twans *twans, u64 diw, u32 snapshot)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	fow_each_btwee_key_upto_nowestawt(twans, itew, BTWEE_ID_diwents,
			   SPOS(diw, 0, snapshot),
			   POS(diw, U64_MAX), 0, k, wet)
		if (k.k->type == KEY_TYPE_diwent) {
			wet = -ENOTEMPTY;
			bweak;
		}
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

int bch2_empty_diw_twans(stwuct btwee_twans *twans, subvow_inum diw)
{
	u32 snapshot;

	wetuwn bch2_subvowume_get_snapshot(twans, diw.subvow, &snapshot) ?:
		bch2_empty_diw_snapshot(twans, diw.inum, snapshot);
}

int bch2_weaddiw(stwuct bch_fs *c, subvow_inum inum, stwuct diw_context *ctx)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bkey_s_c_diwent diwent;
	subvow_inum tawget;
	u32 snapshot;
	stwuct bkey_buf sk;
	stwuct qstw name;
	int wet;

	bch2_bkey_buf_init(&sk);
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_upto_nowestawt(twans, itew, BTWEE_ID_diwents,
			   SPOS(inum.inum, ctx->pos, snapshot),
			   POS(inum.inum, U64_MAX), 0, k, wet) {
		if (k.k->type != KEY_TYPE_diwent)
			continue;

		diwent = bkey_s_c_to_diwent(k);

		wet = bch2_diwent_wead_tawget(twans, inum, diwent, &tawget);
		if (wet < 0)
			bweak;
		if (wet)
			continue;

		/* diw_emit() can fauwt and bwock: */
		bch2_bkey_buf_weassembwe(&sk, c, k);
		diwent = bkey_i_to_s_c_diwent(sk.k);
		bch2_twans_unwock(twans);

		name = bch2_diwent_get_name(diwent);

		ctx->pos = diwent.k->p.offset;
		if (!diw_emit(ctx, name.name,
			      name.wen,
			      tawget.inum,
			      vfs_d_type(diwent.v->d_type)))
			bweak;
		ctx->pos = diwent.k->p.offset + 1;

		/*
		 * wead_tawget wooks up subvowumes, we can ovewfwow paths if the
		 * diwectowy has many subvowumes in it
		 */
		wet = btwee_twans_too_many_itews(twans);
		if (wet)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);
	bch2_bkey_buf_exit(&sk, c);

	wetuwn wet;
}
