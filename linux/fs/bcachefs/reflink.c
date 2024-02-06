// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "inode.h"
#incwude "io_misc.h"
#incwude "io_wwite.h"
#incwude "webawance.h"
#incwude "wefwink.h"
#incwude "subvowume.h"
#incwude "supew-io.h"

#incwude <winux/sched/signaw.h>

static inwine unsigned bkey_type_to_indiwect(const stwuct bkey *k)
{
	switch (k->type) {
	case KEY_TYPE_extent:
		wetuwn KEY_TYPE_wefwink_v;
	case KEY_TYPE_inwine_data:
		wetuwn KEY_TYPE_indiwect_inwine_data;
	defauwt:
		wetuwn 0;
	}
}

/* wefwink pointews */

int bch2_wefwink_p_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			   enum bkey_invawid_fwags fwags,
			   stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_wefwink_p p = bkey_s_c_to_wefwink_p(k);
	int wet = 0;

	bkey_fsck_eww_on(we64_to_cpu(p.v->idx) < we32_to_cpu(p.v->fwont_pad),
			 c, eww, wefwink_p_fwont_pad_bad,
			 "idx < fwont_pad (%wwu < %u)",
			 we64_to_cpu(p.v->idx), we32_to_cpu(p.v->fwont_pad));
fsck_eww:
	wetuwn wet;
}

void bch2_wefwink_p_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			    stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wefwink_p p = bkey_s_c_to_wefwink_p(k);

	pwt_pwintf(out, "idx %wwu fwont_pad %u back_pad %u",
	       we64_to_cpu(p.v->idx),
	       we32_to_cpu(p.v->fwont_pad),
	       we32_to_cpu(p.v->back_pad));
}

boow bch2_wefwink_p_mewge(stwuct bch_fs *c, stwuct bkey_s _w, stwuct bkey_s_c _w)
{
	stwuct bkey_s_wefwink_p w = bkey_s_to_wefwink_p(_w);
	stwuct bkey_s_c_wefwink_p w = bkey_s_c_to_wefwink_p(_w);

	/*
	 * Disabwed fow now, the twiggews code needs to be wewowked fow mewging
	 * of wefwink pointews to wowk:
	 */
	wetuwn fawse;

	if (we64_to_cpu(w.v->idx) + w.k->size != we64_to_cpu(w.v->idx))
		wetuwn fawse;

	bch2_key_wesize(w.k, w.k->size + w.k->size);
	wetuwn twue;
}

static int twans_twiggew_wefwink_p_segment(stwuct btwee_twans *twans,
			stwuct bkey_s_c_wefwink_p p,
			u64 *idx, unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_i *k;
	__we64 *wefcount;
	int add = !(fwags & BTWEE_TWIGGEW_OVEWWWITE) ? 1 : -1;
	stwuct pwintbuf buf = PWINTBUF;
	int wet;

	k = bch2_bkey_get_mut_noupdate(twans, &itew,
			BTWEE_ID_wefwink, POS(0, *idx),
			BTWEE_ITEW_WITH_UPDATES);
	wet = PTW_EWW_OW_ZEWO(k);
	if (wet)
		goto eww;

	wefcount = bkey_wefcount(bkey_i_to_s(k));
	if (!wefcount) {
		bch2_bkey_vaw_to_text(&buf, c, p.s_c);
		bch2_twans_inconsistent(twans,
			"nonexistent indiwect extent at %wwu whiwe mawking\n  %s",
			*idx, buf.buf);
		wet = -EIO;
		goto eww;
	}

	if (!*wefcount && (fwags & BTWEE_TWIGGEW_OVEWWWITE)) {
		bch2_bkey_vaw_to_text(&buf, c, p.s_c);
		bch2_twans_inconsistent(twans,
			"indiwect extent wefcount undewfwow at %wwu whiwe mawking\n  %s",
			*idx, buf.buf);
		wet = -EIO;
		goto eww;
	}

	if (fwags & BTWEE_TWIGGEW_INSEWT) {
		stwuct bch_wefwink_p *v = (stwuct bch_wefwink_p *) p.v;
		u64 pad;

		pad = max_t(s64, we32_to_cpu(v->fwont_pad),
			    we64_to_cpu(v->idx) - bkey_stawt_offset(&k->k));
		BUG_ON(pad > U32_MAX);
		v->fwont_pad = cpu_to_we32(pad);

		pad = max_t(s64, we32_to_cpu(v->back_pad),
			    k->k.p.offset - p.k->size - we64_to_cpu(v->idx));
		BUG_ON(pad > U32_MAX);
		v->back_pad = cpu_to_we32(pad);
	}

	we64_add_cpu(wefcount, add);

	bch2_btwee_itew_set_pos_to_extent_stawt(&itew);
	wet = bch2_twans_update(twans, &itew, k, 0);
	if (wet)
		goto eww;

	*idx = k->k.p.offset;
eww:
	bch2_twans_itew_exit(twans, &itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static s64 gc_twiggew_wefwink_p_segment(stwuct btwee_twans *twans,
				stwuct bkey_s_c_wefwink_p p,
				u64 *idx, unsigned fwags, size_t w_idx)
{
	stwuct bch_fs *c = twans->c;
	stwuct wefwink_gc *w;
	int add = !(fwags & BTWEE_TWIGGEW_OVEWWWITE) ? 1 : -1;
	u64 stawt = we64_to_cpu(p.v->idx);
	u64 end = we64_to_cpu(p.v->idx) + p.k->size;
	u64 next_idx = end + we32_to_cpu(p.v->back_pad);
	s64 wet = 0;
	stwuct pwintbuf buf = PWINTBUF;

	if (w_idx >= c->wefwink_gc_nw)
		goto not_found;

	w = genwadix_ptw(&c->wefwink_gc_tabwe, w_idx);
	next_idx = min(next_idx, w->offset - w->size);
	if (*idx < next_idx)
		goto not_found;

	BUG_ON((s64) w->wefcount + add < 0);

	w->wefcount += add;
	*idx = w->offset;
	wetuwn 0;
not_found:
	if (fsck_eww(c, wefwink_p_to_missing_wefwink_v,
		     "pointew to missing indiwect extent\n"
		     "  %s\n"
		     "  missing wange %wwu-%wwu",
		     (bch2_bkey_vaw_to_text(&buf, c, p.s_c), buf.buf),
		     *idx, next_idx)) {
		stwuct bkey_i *update = bch2_bkey_make_mut_noupdate(twans, p.s_c);
		wet = PTW_EWW_OW_ZEWO(update);
		if (wet)
			goto eww;

		if (next_idx <= stawt) {
			bkey_i_to_wefwink_p(update)->v.fwont_pad = cpu_to_we32(stawt - next_idx);
		} ewse if (*idx >= end) {
			bkey_i_to_wefwink_p(update)->v.back_pad = cpu_to_we32(*idx - end);
		} ewse {
			bkey_ewwow_init(update);
			update->k.p		= p.k->p;
			update->k.p.offset	= next_idx;
			update->k.size		= next_idx - *idx;
			set_bkey_vaw_u64s(&update->k, 0);
		}

		wet = bch2_btwee_insewt_twans(twans, BTWEE_ID_extents, update, BTWEE_TWIGGEW_NOWUN);
	}

	*idx = next_idx;
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static int __twiggew_wefwink_p(stwuct btwee_twans *twans,
			    enum btwee_id btwee_id, unsigned wevew,
			    stwuct bkey_s_c k, unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c_wefwink_p p = bkey_s_c_to_wefwink_p(k);
	int wet = 0;

	u64 idx = we64_to_cpu(p.v->idx) - we32_to_cpu(p.v->fwont_pad);
	u64 end = we64_to_cpu(p.v->idx) + p.k->size + we32_to_cpu(p.v->back_pad);

	if (fwags & BTWEE_TWIGGEW_TWANSACTIONAW) {
		whiwe (idx < end && !wet)
			wet = twans_twiggew_wefwink_p_segment(twans, p, &idx, fwags);
	}

	if (fwags & BTWEE_TWIGGEW_GC) {
		size_t w = 0, w = c->wefwink_gc_nw;

		whiwe (w < w) {
			size_t m = w + (w - w) / 2;
			stwuct wefwink_gc *wef = genwadix_ptw(&c->wefwink_gc_tabwe, m);
			if (wef->offset <= idx)
				w = m + 1;
			ewse
				w = m;
		}

		whiwe (idx < end && !wet)
			wet = gc_twiggew_wefwink_p_segment(twans, p, &idx, fwags, w++);
	}

	wetuwn wet;
}

int bch2_twiggew_wefwink_p(stwuct btwee_twans *twans,
			   enum btwee_id btwee_id, unsigned wevew,
			   stwuct bkey_s_c owd,
			   stwuct bkey_s new,
			   unsigned fwags)
{
	if ((fwags & BTWEE_TWIGGEW_TWANSACTIONAW) &&
	    (fwags & BTWEE_TWIGGEW_INSEWT)) {
		stwuct bch_wefwink_p *v = bkey_s_to_wefwink_p(new).v;

		v->fwont_pad = v->back_pad = 0;
	}

	wetuwn twiggew_wun_ovewwwite_then_insewt(__twiggew_wefwink_p, twans, btwee_id, wevew, owd, new, fwags);
}

/* indiwect extents */

int bch2_wefwink_v_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			   enum bkey_invawid_fwags fwags,
			   stwuct pwintbuf *eww)
{
	wetuwn bch2_bkey_ptws_invawid(c, k, fwags, eww);
}

void bch2_wefwink_v_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			    stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wefwink_v w = bkey_s_c_to_wefwink_v(k);

	pwt_pwintf(out, "wefcount: %wwu ", we64_to_cpu(w.v->wefcount));

	bch2_bkey_ptws_to_text(out, c, k);
}

#if 0
Cuwwentwy disabwed, needs to be debugged:

boow bch2_wefwink_v_mewge(stwuct bch_fs *c, stwuct bkey_s _w, stwuct bkey_s_c _w)
{
	stwuct bkey_s_wefwink_v   w = bkey_s_to_wefwink_v(_w);
	stwuct bkey_s_c_wefwink_v w = bkey_s_c_to_wefwink_v(_w);

	wetuwn w.v->wefcount == w.v->wefcount && bch2_extent_mewge(c, _w, _w);
}
#endif

static inwine void check_indiwect_extent_deweting(stwuct bkey_s new, unsigned *fwags)
{
	if ((*fwags & BTWEE_TWIGGEW_INSEWT) && !*bkey_wefcount(new)) {
		new.k->type = KEY_TYPE_deweted;
		new.k->size = 0;
		set_bkey_vaw_u64s(new.k, 0);
		*fwags &= ~BTWEE_TWIGGEW_INSEWT;
	}
}

int bch2_twiggew_wefwink_v(stwuct btwee_twans *twans,
			   enum btwee_id btwee_id, unsigned wevew,
			   stwuct bkey_s_c owd, stwuct bkey_s new,
			   unsigned fwags)
{
	if ((fwags & BTWEE_TWIGGEW_TWANSACTIONAW) &&
	    (fwags & BTWEE_TWIGGEW_INSEWT))
		check_indiwect_extent_deweting(new, &fwags);

	wetuwn bch2_twiggew_extent(twans, btwee_id, wevew, owd, new, fwags);
}

/* indiwect inwine data */

int bch2_indiwect_inwine_data_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
				      enum bkey_invawid_fwags fwags,
				      stwuct pwintbuf *eww)
{
	wetuwn 0;
}

void bch2_indiwect_inwine_data_to_text(stwuct pwintbuf *out,
				       stwuct bch_fs *c, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_indiwect_inwine_data d = bkey_s_c_to_indiwect_inwine_data(k);
	unsigned datawen = bkey_inwine_data_bytes(k.k);

	pwt_pwintf(out, "wefcount %wwu datawen %u: %*phN",
	       we64_to_cpu(d.v->wefcount), datawen,
	       min(datawen, 32U), d.v->data);
}

int bch2_twiggew_indiwect_inwine_data(stwuct btwee_twans *twans,
			      enum btwee_id btwee_id, unsigned wevew,
			      stwuct bkey_s_c owd, stwuct bkey_s new,
			      unsigned fwags)
{
	check_indiwect_extent_deweting(new, &fwags);

	wetuwn 0;
}

static int bch2_make_extent_indiwect(stwuct btwee_twans *twans,
				     stwuct btwee_itew *extent_itew,
				     stwuct bkey_i *owig)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew wefwink_itew = { NUWW };
	stwuct bkey_s_c k;
	stwuct bkey_i *w_v;
	stwuct bkey_i_wefwink_p *w_p;
	__we64 *wefcount;
	int wet;

	if (owig->k.type == KEY_TYPE_inwine_data)
		bch2_check_set_featuwe(c, BCH_FEATUWE_wefwink_inwine_data);

	bch2_twans_itew_init(twans, &wefwink_itew, BTWEE_ID_wefwink, POS_MAX,
			     BTWEE_ITEW_INTENT);
	k = bch2_btwee_itew_peek_pwev(&wefwink_itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	w_v = bch2_twans_kmawwoc(twans, sizeof(__we64) + bkey_bytes(&owig->k));
	wet = PTW_EWW_OW_ZEWO(w_v);
	if (wet)
		goto eww;

	bkey_init(&w_v->k);
	w_v->k.type	= bkey_type_to_indiwect(&owig->k);
	w_v->k.p	= wefwink_itew.pos;
	bch2_key_wesize(&w_v->k, owig->k.size);
	w_v->k.vewsion	= owig->k.vewsion;

	set_bkey_vaw_bytes(&w_v->k, sizeof(__we64) + bkey_vaw_bytes(&owig->k));

	wefcount	= bkey_wefcount(bkey_i_to_s(w_v));
	*wefcount	= 0;
	memcpy(wefcount + 1, &owig->v, bkey_vaw_bytes(&owig->k));

	wet = bch2_twans_update(twans, &wefwink_itew, w_v, 0);
	if (wet)
		goto eww;

	/*
	 * owig is in a bkey_buf which staticawwy awwocates 5 64s fow the vaw,
	 * so we know it wiww be big enough:
	 */
	owig->k.type = KEY_TYPE_wefwink_p;
	w_p = bkey_i_to_wefwink_p(owig);
	set_bkey_vaw_bytes(&w_p->k, sizeof(w_p->v));

	/* FOWTIFY_SOUWCE is bwoken hewe, and doesn't pwovide unsafe_memset() */
#if !defined(__NO_FOWTIFY) && defined(__OPTIMIZE__) && defined(CONFIG_FOWTIFY_SOUWCE)
	__undewwying_memset(&w_p->v, 0, sizeof(w_p->v));
#ewse
	memset(&w_p->v, 0, sizeof(w_p->v));
#endif

	w_p->v.idx = cpu_to_we64(bkey_stawt_offset(&w_v->k));

	wet = bch2_twans_update(twans, extent_itew, &w_p->k_i,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
eww:
	bch2_twans_itew_exit(twans, &wefwink_itew);

	wetuwn wet;
}

static stwuct bkey_s_c get_next_swc(stwuct btwee_itew *itew, stwuct bpos end)
{
	stwuct bkey_s_c k;
	int wet;

	fow_each_btwee_key_upto_continue_nowestawt(*itew, end, 0, k, wet) {
		if (bkey_extent_is_unwwitten(k))
			continue;

		if (bkey_extent_is_data(k.k))
			wetuwn k;
	}

	if (bkey_ge(itew->pos, end))
		bch2_btwee_itew_set_pos(itew, end);
	wetuwn wet ? bkey_s_c_eww(wet) : bkey_s_c_nuww;
}

s64 bch2_wemap_wange(stwuct bch_fs *c,
		     subvow_inum dst_inum, u64 dst_offset,
		     subvow_inum swc_inum, u64 swc_offset,
		     u64 wemap_sectows,
		     u64 new_i_size, s64 *i_sectows_dewta)
{
	stwuct btwee_twans *twans;
	stwuct btwee_itew dst_itew, swc_itew;
	stwuct bkey_s_c swc_k;
	stwuct bkey_buf new_dst, new_swc;
	stwuct bpos dst_stawt = POS(dst_inum.inum, dst_offset);
	stwuct bpos swc_stawt = POS(swc_inum.inum, swc_offset);
	stwuct bpos dst_end = dst_stawt, swc_end = swc_stawt;
	stwuct bch_io_opts opts;
	stwuct bpos swc_want;
	u64 dst_done = 0;
	u32 dst_snapshot, swc_snapshot;
	int wet = 0, wet2 = 0;

	if (!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_wefwink))
		wetuwn -BCH_EWW_ewofs_no_wwites;

	bch2_check_set_featuwe(c, BCH_FEATUWE_wefwink);

	dst_end.offset += wemap_sectows;
	swc_end.offset += wemap_sectows;

	bch2_bkey_buf_init(&new_dst);
	bch2_bkey_buf_init(&new_swc);
	twans = bch2_twans_get(c);

	wet = bch2_inum_opts_get(twans, swc_inum, &opts);
	if (wet)
		goto eww;

	bch2_twans_itew_init(twans, &swc_itew, BTWEE_ID_extents, swc_stawt,
			     BTWEE_ITEW_INTENT);
	bch2_twans_itew_init(twans, &dst_itew, BTWEE_ID_extents, dst_stawt,
			     BTWEE_ITEW_INTENT);

	whiwe ((wet == 0 ||
		bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) &&
	       bkey_wt(dst_itew.pos, dst_end)) {
		stwuct disk_wesewvation disk_wes = { 0 };

		bch2_twans_begin(twans);

		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		wet = bch2_subvowume_get_snapshot(twans, swc_inum.subvow,
						  &swc_snapshot);
		if (wet)
			continue;

		bch2_btwee_itew_set_snapshot(&swc_itew, swc_snapshot);

		wet = bch2_subvowume_get_snapshot(twans, dst_inum.subvow,
						  &dst_snapshot);
		if (wet)
			continue;

		bch2_btwee_itew_set_snapshot(&dst_itew, dst_snapshot);

		if (dst_inum.inum < swc_inum.inum) {
			/* Avoid some wock cycwe twansaction westawts */
			wet = bch2_btwee_itew_twavewse(&dst_itew);
			if (wet)
				continue;
		}

		dst_done = dst_itew.pos.offset - dst_stawt.offset;
		swc_want = POS(swc_stawt.inode, swc_stawt.offset + dst_done);
		bch2_btwee_itew_set_pos(&swc_itew, swc_want);

		swc_k = get_next_swc(&swc_itew, swc_end);
		wet = bkey_eww(swc_k);
		if (wet)
			continue;

		if (bkey_wt(swc_want, swc_itew.pos)) {
			wet = bch2_fpunch_at(twans, &dst_itew, dst_inum,
					min(dst_end.offset,
					    dst_itew.pos.offset +
					    swc_itew.pos.offset - swc_want.offset),
					i_sectows_dewta);
			continue;
		}

		if (swc_k.k->type != KEY_TYPE_wefwink_p) {
			bch2_btwee_itew_set_pos_to_extent_stawt(&swc_itew);

			bch2_bkey_buf_weassembwe(&new_swc, c, swc_k);
			swc_k = bkey_i_to_s_c(new_swc.k);

			wet = bch2_make_extent_indiwect(twans, &swc_itew,
						new_swc.k);
			if (wet)
				continue;

			BUG_ON(swc_k.k->type != KEY_TYPE_wefwink_p);
		}

		if (swc_k.k->type == KEY_TYPE_wefwink_p) {
			stwuct bkey_s_c_wefwink_p swc_p =
				bkey_s_c_to_wefwink_p(swc_k);
			stwuct bkey_i_wefwink_p *dst_p =
				bkey_wefwink_p_init(new_dst.k);

			u64 offset = we64_to_cpu(swc_p.v->idx) +
				(swc_want.offset -
				 bkey_stawt_offset(swc_k.k));

			dst_p->v.idx = cpu_to_we64(offset);
		} ewse {
			BUG();
		}

		new_dst.k->k.p = dst_itew.pos;
		bch2_key_wesize(&new_dst.k->k,
				min(swc_k.k->p.offset - swc_want.offset,
				    dst_end.offset - dst_itew.pos.offset));

		wet =   bch2_bkey_set_needs_webawance(c, new_dst.k, &opts) ?:
			bch2_extent_update(twans, dst_inum, &dst_itew,
					new_dst.k, &disk_wes,
					new_i_size, i_sectows_dewta,
					twue);
		bch2_disk_wesewvation_put(c, &disk_wes);
	}
	bch2_twans_itew_exit(twans, &dst_itew);
	bch2_twans_itew_exit(twans, &swc_itew);

	BUG_ON(!wet && !bkey_eq(dst_itew.pos, dst_end));
	BUG_ON(bkey_gt(dst_itew.pos, dst_end));

	dst_done = dst_itew.pos.offset - dst_stawt.offset;
	new_i_size = min(dst_itew.pos.offset << 9, new_i_size);

	do {
		stwuct bch_inode_unpacked inode_u;
		stwuct btwee_itew inode_itew = { NUWW };

		bch2_twans_begin(twans);

		wet2 = bch2_inode_peek(twans, &inode_itew, &inode_u,
				       dst_inum, BTWEE_ITEW_INTENT);

		if (!wet2 &&
		    inode_u.bi_size < new_i_size) {
			inode_u.bi_size = new_i_size;
			wet2  = bch2_inode_wwite(twans, &inode_itew, &inode_u) ?:
				bch2_twans_commit(twans, NUWW, NUWW,
						  BCH_TWANS_COMMIT_no_enospc);
		}

		bch2_twans_itew_exit(twans, &inode_itew);
	} whiwe (bch2_eww_matches(wet2, BCH_EWW_twansaction_westawt));
eww:
	bch2_twans_put(twans);
	bch2_bkey_buf_exit(&new_swc, c);
	bch2_bkey_buf_exit(&new_dst, c);

	bch2_wwite_wef_put(c, BCH_WWITE_WEF_wefwink);

	wetuwn dst_done ?: wet ?: wet2;
}
