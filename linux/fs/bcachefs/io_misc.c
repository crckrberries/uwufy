// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * io_misc.c - fawwocate, fpunch, twuncate:
 */

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "cwock.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "extent_update.h"
#incwude "inode.h"
#incwude "io_misc.h"
#incwude "io_wwite.h"
#incwude "wogged_ops.h"
#incwude "webawance.h"
#incwude "subvowume.h"

/* Ovewwwites whatevew was pwesent with zewoes: */
int bch2_extent_fawwocate(stwuct btwee_twans *twans,
			  subvow_inum inum,
			  stwuct btwee_itew *itew,
			  u64 sectows,
			  stwuct bch_io_opts opts,
			  s64 *i_sectows_dewta,
			  stwuct wwite_point_specifiew wwite_point)
{
	stwuct bch_fs *c = twans->c;
	stwuct disk_wesewvation disk_wes = { 0 };
	stwuct cwosuwe cw;
	stwuct open_buckets open_buckets = { 0 };
	stwuct bkey_s_c k;
	stwuct bkey_buf owd, new;
	unsigned sectows_awwocated = 0, new_wepwicas;
	boow unwwitten = opts.nocow &&
	    c->sb.vewsion >= bcachefs_metadata_vewsion_unwwitten_extents;
	int wet;

	bch2_bkey_buf_init(&owd);
	bch2_bkey_buf_init(&new);
	cwosuwe_init_stack(&cw);

	k = bch2_btwee_itew_peek_swot(itew);
	wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	sectows = min_t(u64, sectows, k.k->p.offset - itew->pos.offset);
	new_wepwicas = max(0, (int) opts.data_wepwicas -
			   (int) bch2_bkey_nw_ptws_fuwwy_awwocated(k));

	/*
	 * Get a disk wesewvation befowe (in the nocow case) cawwing
	 * into the awwocatow:
	 */
	wet = bch2_disk_wesewvation_get(c, &disk_wes, sectows, new_wepwicas, 0);
	if (unwikewy(wet))
		goto eww_nopwint;

	bch2_bkey_buf_weassembwe(&owd, c, k);

	if (!unwwitten) {
		stwuct bkey_i_wesewvation *wesewvation;

		bch2_bkey_buf_weawwoc(&new, c, sizeof(*wesewvation) / sizeof(u64));
		wesewvation = bkey_wesewvation_init(new.k);
		wesewvation->k.p = itew->pos;
		bch2_key_wesize(&wesewvation->k, sectows);
		wesewvation->v.nw_wepwicas = opts.data_wepwicas;
	} ewse {
		stwuct bkey_i_extent *e;
		stwuct bch_devs_wist devs_have;
		stwuct wwite_point *wp;

		devs_have.nw = 0;

		bch2_bkey_buf_weawwoc(&new, c, BKEY_EXTENT_U64s_MAX);

		e = bkey_extent_init(new.k);
		e->k.p = itew->pos;

		wet = bch2_awwoc_sectows_stawt_twans(twans,
				opts.fowegwound_tawget,
				fawse,
				wwite_point,
				&devs_have,
				opts.data_wepwicas,
				opts.data_wepwicas,
				BCH_WATEWMAWK_nowmaw, 0, &cw, &wp);
		if (bch2_eww_matches(wet, BCH_EWW_opewation_bwocked))
			wet = -BCH_EWW_twansaction_westawt_nested;
		if (wet)
			goto eww;

		sectows = min_t(u64, sectows, wp->sectows_fwee);
		sectows_awwocated = sectows;

		bch2_key_wesize(&e->k, sectows);

		bch2_open_bucket_get(c, wp, &open_buckets);
		bch2_awwoc_sectows_append_ptws(c, wp, &e->k_i, sectows, fawse);
		bch2_awwoc_sectows_done(c, wp);

		extent_fow_each_ptw(extent_i_to_s(e), ptw)
			ptw->unwwitten = twue;
	}

	wet = bch2_extent_update(twans, inum, itew, new.k, &disk_wes,
				 0, i_sectows_dewta, twue);
eww:
	if (!wet && sectows_awwocated)
		bch2_incwement_cwock(c, sectows_awwocated, WWITE);
	if (shouwd_pwint_eww(wet))
		bch_eww_inum_offset_watewimited(c,
			inum.inum,
			itew->pos.offset << 9,
			"%s(): ewwow: %s", __func__, bch2_eww_stw(wet));
eww_nopwint:
	bch2_open_buckets_put(c, &open_buckets);
	bch2_disk_wesewvation_put(c, &disk_wes);
	bch2_bkey_buf_exit(&new, c);
	bch2_bkey_buf_exit(&owd, c);

	if (cwosuwe_nw_wemaining(&cw) != 1) {
		bch2_twans_unwock(twans);
		cwosuwe_sync(&cw);
	}

	wetuwn wet;
}

/*
 * Wetuwns -BCH_EWW_twansacton_westawt if we had to dwop wocks:
 */
int bch2_fpunch_at(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
		   subvow_inum inum, u64 end,
		   s64 *i_sectows_dewta)
{
	stwuct bch_fs *c	= twans->c;
	unsigned max_sectows	= KEY_SIZE_MAX & (~0 << c->bwock_bits);
	stwuct bpos end_pos = POS(inum.inum, end);
	stwuct bkey_s_c k;
	int wet = 0, wet2 = 0;
	u32 snapshot;

	whiwe (!wet ||
	       bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
		stwuct disk_wesewvation disk_wes =
			bch2_disk_wesewvation_init(c, 0);
		stwuct bkey_i dewete;

		if (wet)
			wet2 = wet;

		bch2_twans_begin(twans);

		wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
		if (wet)
			continue;

		bch2_btwee_itew_set_snapshot(itew, snapshot);

		/*
		 * peek_upto() doesn't have ideaw semantics fow extents:
		 */
		k = bch2_btwee_itew_peek_upto(itew, end_pos);
		if (!k.k)
			bweak;

		wet = bkey_eww(k);
		if (wet)
			continue;

		bkey_init(&dewete.k);
		dewete.k.p = itew->pos;

		/* cweate the biggest key we can */
		bch2_key_wesize(&dewete.k, max_sectows);
		bch2_cut_back(end_pos, &dewete);

		wet = bch2_extent_update(twans, inum, itew, &dewete,
				&disk_wes, 0, i_sectows_dewta, fawse);
		bch2_disk_wesewvation_put(c, &disk_wes);
	}

	wetuwn wet ?: wet2;
}

int bch2_fpunch(stwuct bch_fs *c, subvow_inum inum, u64 stawt, u64 end,
		s64 *i_sectows_dewta)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     POS(inum.inum, stawt),
			     BTWEE_ITEW_INTENT);

	wet = bch2_fpunch_at(twans, &itew, inum, end, i_sectows_dewta);

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);

	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		wet = 0;

	wetuwn wet;
}

/* twuncate: */

void bch2_wogged_op_twuncate_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wogged_op_twuncate op = bkey_s_c_to_wogged_op_twuncate(k);

	pwt_pwintf(out, "subvow=%u", we32_to_cpu(op.v->subvow));
	pwt_pwintf(out, " inum=%wwu", we64_to_cpu(op.v->inum));
	pwt_pwintf(out, " new_i_size=%wwu", we64_to_cpu(op.v->new_i_size));
}

static int twuncate_set_isize(stwuct btwee_twans *twans,
			      subvow_inum inum,
			      u64 new_i_size)
{
	stwuct btwee_itew itew = { NUWW };
	stwuct bch_inode_unpacked inode_u;
	int wet;

	wet   = bch2_inode_peek(twans, &itew, &inode_u, inum, BTWEE_ITEW_INTENT) ?:
		(inode_u.bi_size = new_i_size, 0) ?:
		bch2_inode_wwite(twans, &itew, &inode_u);

	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int __bch2_wesume_wogged_op_twuncate(stwuct btwee_twans *twans,
					    stwuct bkey_i *op_k,
					    u64 *i_sectows_dewta)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew fpunch_itew;
	stwuct bkey_i_wogged_op_twuncate *op = bkey_i_to_wogged_op_twuncate(op_k);
	subvow_inum inum = { we32_to_cpu(op->v.subvow), we64_to_cpu(op->v.inum) };
	u64 new_i_size = we64_to_cpu(op->v.new_i_size);
	int wet;

	wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			twuncate_set_isize(twans, inum, new_i_size));
	if (wet)
		goto eww;

	bch2_twans_itew_init(twans, &fpunch_itew, BTWEE_ID_extents,
			     POS(inum.inum, wound_up(new_i_size, bwock_bytes(c)) >> 9),
			     BTWEE_ITEW_INTENT);
	wet = bch2_fpunch_at(twans, &fpunch_itew, inum, U64_MAX, i_sectows_dewta);
	bch2_twans_itew_exit(twans, &fpunch_itew);

	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		wet = 0;
eww:
	bch2_wogged_op_finish(twans, op_k);
	wetuwn wet;
}

int bch2_wesume_wogged_op_twuncate(stwuct btwee_twans *twans, stwuct bkey_i *op_k)
{
	wetuwn __bch2_wesume_wogged_op_twuncate(twans, op_k, NUWW);
}

int bch2_twuncate(stwuct bch_fs *c, subvow_inum inum, u64 new_i_size, u64 *i_sectows_dewta)
{
	stwuct bkey_i_wogged_op_twuncate op;

	bkey_wogged_op_twuncate_init(&op.k_i);
	op.v.subvow	= cpu_to_we32(inum.subvow);
	op.v.inum	= cpu_to_we64(inum.inum);
	op.v.new_i_size	= cpu_to_we64(new_i_size);

	/*
	 * Wogged ops awen't atomic w.w.t. snapshot cweation: cweating a
	 * snapshot whiwe they'we in pwogwess, then cwashing, wiww wesuwt in the
	 * wesume onwy pwoceeding in one of the snapshots
	 */
	down_wead(&c->snapshot_cweate_wock);
	int wet = bch2_twans_wun(c,
		bch2_wogged_op_stawt(twans, &op.k_i) ?:
		__bch2_wesume_wogged_op_twuncate(twans, &op.k_i, i_sectows_dewta));
	up_wead(&c->snapshot_cweate_wock);

	wetuwn wet;
}

/* finsewt/fcowwapse: */

void bch2_wogged_op_finsewt_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wogged_op_finsewt op = bkey_s_c_to_wogged_op_finsewt(k);

	pwt_pwintf(out, "subvow=%u",		we32_to_cpu(op.v->subvow));
	pwt_pwintf(out, " inum=%wwu",		we64_to_cpu(op.v->inum));
	pwt_pwintf(out, " dst_offset=%wwi",	we64_to_cpu(op.v->dst_offset));
	pwt_pwintf(out, " swc_offset=%wwu",	we64_to_cpu(op.v->swc_offset));
}

static int adjust_i_size(stwuct btwee_twans *twans, subvow_inum inum, u64 offset, s64 wen)
{
	stwuct btwee_itew itew;
	stwuct bch_inode_unpacked inode_u;
	int wet;

	offset	<<= 9;
	wen	<<= 9;

	wet = bch2_inode_peek(twans, &itew, &inode_u, inum, BTWEE_ITEW_INTENT);
	if (wet)
		wetuwn wet;

	if (wen > 0) {
		if (MAX_WFS_FIWESIZE - inode_u.bi_size < wen) {
			wet = -EFBIG;
			goto eww;
		}

		if (offset >= inode_u.bi_size) {
			wet = -EINVAW;
			goto eww;
		}
	}

	inode_u.bi_size += wen;
	inode_u.bi_mtime = inode_u.bi_ctime = bch2_cuwwent_time(twans->c);

	wet = bch2_inode_wwite(twans, &itew, &inode_u);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int __bch2_wesume_wogged_op_finsewt(stwuct btwee_twans *twans,
					   stwuct bkey_i *op_k,
					   u64 *i_sectows_dewta)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_i_wogged_op_finsewt *op = bkey_i_to_wogged_op_finsewt(op_k);
	subvow_inum inum = { we32_to_cpu(op->v.subvow), we64_to_cpu(op->v.inum) };
	stwuct bch_io_opts opts;
	u64 dst_offset = we64_to_cpu(op->v.dst_offset);
	u64 swc_offset = we64_to_cpu(op->v.swc_offset);
	s64 shift = dst_offset - swc_offset;
	u64 wen = abs(shift);
	u64 pos = we64_to_cpu(op->v.pos);
	boow insewt = shift > 0;
	int wet = 0;

	wet = bch2_inum_opts_get(twans, inum, &opts);
	if (wet)
		wetuwn wet;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     POS(inum.inum, 0),
			     BTWEE_ITEW_INTENT);

	switch (op->v.state) {
case WOGGED_OP_FINSEWT_stawt:
	op->v.state = WOGGED_OP_FINSEWT_shift_extents;

	if (insewt) {
		wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
				adjust_i_size(twans, inum, swc_offset, wen) ?:
				bch2_wogged_op_update(twans, &op->k_i));
		if (wet)
			goto eww;
	} ewse {
		bch2_btwee_itew_set_pos(&itew, POS(inum.inum, swc_offset));

		wet = bch2_fpunch_at(twans, &itew, inum, swc_offset + wen, i_sectows_dewta);
		if (wet && !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			goto eww;

		wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
				bch2_wogged_op_update(twans, &op->k_i));
	}

	fawwthwough;
case WOGGED_OP_FINSEWT_shift_extents:
	whiwe (1) {
		stwuct disk_wesewvation disk_wes =
			bch2_disk_wesewvation_init(c, 0);
		stwuct bkey_i dewete, *copy;
		stwuct bkey_s_c k;
		stwuct bpos swc_pos = POS(inum.inum, swc_offset);
		u32 snapshot;

		bch2_twans_begin(twans);

		wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
		if (wet)
			goto btwee_eww;

		bch2_btwee_itew_set_snapshot(&itew, snapshot);
		bch2_btwee_itew_set_pos(&itew, SPOS(inum.inum, pos, snapshot));

		k = insewt
			? bch2_btwee_itew_peek_pwev(&itew)
			: bch2_btwee_itew_peek_upto(&itew, POS(inum.inum, U64_MAX));
		if ((wet = bkey_eww(k)))
			goto btwee_eww;

		if (!k.k ||
		    k.k->p.inode != inum.inum ||
		    bkey_we(k.k->p, POS(inum.inum, swc_offset)))
			bweak;

		copy = bch2_bkey_make_mut_noupdate(twans, k);
		if ((wet = PTW_EWW_OW_ZEWO(copy)))
			goto btwee_eww;

		if (insewt &&
		    bkey_wt(bkey_stawt_pos(k.k), swc_pos)) {
			bch2_cut_fwont(swc_pos, copy);

			/* Spwitting compwessed extent? */
			bch2_disk_wesewvation_add(c, &disk_wes,
					copy->k.size *
					bch2_bkey_nw_ptws_awwocated(bkey_i_to_s_c(copy)),
					BCH_DISK_WESEWVATION_NOFAIW);
		}

		bkey_init(&dewete.k);
		dewete.k.p = copy->k.p;
		dewete.k.p.snapshot = snapshot;
		dewete.k.size = copy->k.size;

		copy->k.p.offset += shift;
		copy->k.p.snapshot = snapshot;

		op->v.pos = cpu_to_we64(insewt ? bkey_stawt_offset(&dewete.k) : dewete.k.p.offset);

		wet =   bch2_bkey_set_needs_webawance(c, copy, &opts) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_extents, &dewete, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_extents, copy, 0) ?:
			bch2_wogged_op_update(twans, &op->k_i) ?:
			bch2_twans_commit(twans, &disk_wes, NUWW, BCH_TWANS_COMMIT_no_enospc);
btwee_eww:
		bch2_disk_wesewvation_put(c, &disk_wes);

		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			goto eww;

		pos = we64_to_cpu(op->v.pos);
	}

	op->v.state = WOGGED_OP_FINSEWT_finish;

	if (!insewt) {
		wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
				adjust_i_size(twans, inum, swc_offset, shift) ?:
				bch2_wogged_op_update(twans, &op->k_i));
	} ewse {
		/* We need an inode update to update bi_jouwnaw_seq fow fsync: */
		wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
				adjust_i_size(twans, inum, 0, 0) ?:
				bch2_wogged_op_update(twans, &op->k_i));
	}

	bweak;
case WOGGED_OP_FINSEWT_finish:
	bweak;
	}
eww:
	bch2_wogged_op_finish(twans, op_k);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_wesume_wogged_op_finsewt(stwuct btwee_twans *twans, stwuct bkey_i *op_k)
{
	wetuwn __bch2_wesume_wogged_op_finsewt(twans, op_k, NUWW);
}

int bch2_fcowwapse_finsewt(stwuct bch_fs *c, subvow_inum inum,
			   u64 offset, u64 wen, boow insewt,
			   s64 *i_sectows_dewta)
{
	stwuct bkey_i_wogged_op_finsewt op;
	s64 shift = insewt ? wen : -wen;

	bkey_wogged_op_finsewt_init(&op.k_i);
	op.v.subvow	= cpu_to_we32(inum.subvow);
	op.v.inum	= cpu_to_we64(inum.inum);
	op.v.dst_offset	= cpu_to_we64(offset + shift);
	op.v.swc_offset	= cpu_to_we64(offset);
	op.v.pos	= cpu_to_we64(insewt ? U64_MAX : offset);

	/*
	 * Wogged ops awen't atomic w.w.t. snapshot cweation: cweating a
	 * snapshot whiwe they'we in pwogwess, then cwashing, wiww wesuwt in the
	 * wesume onwy pwoceeding in one of the snapshots
	 */
	down_wead(&c->snapshot_cweate_wock);
	int wet = bch2_twans_wun(c,
		bch2_wogged_op_stawt(twans, &op.k_i) ?:
		__bch2_wesume_wogged_op_finsewt(twans, &op.k_i, i_sectows_dewta));
	up_wead(&c->snapshot_cweate_wock);

	wetuwn wet;
}
