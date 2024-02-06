// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "data_update.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "io_wwite.h"
#incwude "keywist.h"
#incwude "move.h"
#incwude "nocow_wocking.h"
#incwude "webawance.h"
#incwude "subvowume.h"
#incwude "twace.h"

static void twace_move_extent_finish2(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	if (twace_move_extent_finish_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, k);
		twace_move_extent_finish(c, buf.buf);
		pwintbuf_exit(&buf);
	}
}

static void twace_move_extent_faiw2(stwuct data_update *m,
			 stwuct bkey_s_c new,
			 stwuct bkey_s_c wwote,
			 stwuct bkey_i *insewt,
			 const chaw *msg)
{
	stwuct bch_fs *c = m->op.c;
	stwuct bkey_s_c owd = bkey_i_to_s_c(m->k.k);
	const union bch_extent_entwy *entwy;
	stwuct bch_extent_ptw *ptw;
	stwuct extent_ptw_decoded p;
	stwuct pwintbuf buf = PWINTBUF;
	unsigned i, wewwites_found = 0;

	if (!twace_move_extent_faiw_enabwed())
		wetuwn;

	pwt_stw(&buf, msg);

	if (insewt) {
		i = 0;
		bkey_fow_each_ptw_decode(owd.k, bch2_bkey_ptws_c(owd), p, entwy) {
			if (((1U << i) & m->data_opts.wewwite_ptws) &&
			    (ptw = bch2_extent_has_ptw(owd, p, bkey_i_to_s(insewt))) &&
			    !ptw->cached)
				wewwites_found |= 1U << i;
			i++;
		}
	}

	pwt_pwintf(&buf, "\nwewwite ptws:   %u%u%u%u",
		   (m->data_opts.wewwite_ptws & (1 << 0)) != 0,
		   (m->data_opts.wewwite_ptws & (1 << 1)) != 0,
		   (m->data_opts.wewwite_ptws & (1 << 2)) != 0,
		   (m->data_opts.wewwite_ptws & (1 << 3)) != 0);

	pwt_pwintf(&buf, "\nwewwites found: %u%u%u%u",
		   (wewwites_found & (1 << 0)) != 0,
		   (wewwites_found & (1 << 1)) != 0,
		   (wewwites_found & (1 << 2)) != 0,
		   (wewwites_found & (1 << 3)) != 0);

	pwt_stw(&buf, "\nowd:    ");
	bch2_bkey_vaw_to_text(&buf, c, owd);

	pwt_stw(&buf, "\nnew:    ");
	bch2_bkey_vaw_to_text(&buf, c, new);

	pwt_stw(&buf, "\nwwote:  ");
	bch2_bkey_vaw_to_text(&buf, c, wwote);

	if (insewt) {
		pwt_stw(&buf, "\ninsewt: ");
		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(insewt));
	}

	twace_move_extent_faiw(c, buf.buf);
	pwintbuf_exit(&buf);
}

static int __bch2_data_update_index_update(stwuct btwee_twans *twans,
					   stwuct bch_wwite_op *op)
{
	stwuct bch_fs *c = op->c;
	stwuct btwee_itew itew;
	stwuct data_update *m =
		containew_of(op, stwuct data_update, op);
	stwuct keywist *keys = &op->insewt_keys;
	stwuct bkey_buf _new, _insewt;
	int wet = 0;

	bch2_bkey_buf_init(&_new);
	bch2_bkey_buf_init(&_insewt);
	bch2_bkey_buf_weawwoc(&_insewt, c, U8_MAX);

	bch2_twans_itew_init(twans, &itew, m->btwee_id,
			     bkey_stawt_pos(&bch2_keywist_fwont(keys)->k),
			     BTWEE_ITEW_SWOTS|BTWEE_ITEW_INTENT);

	whiwe (1) {
		stwuct bkey_s_c k;
		stwuct bkey_s_c owd = bkey_i_to_s_c(m->k.k);
		stwuct bkey_i *insewt = NUWW;
		stwuct bkey_i_extent *new;
		const union bch_extent_entwy *entwy_c;
		union bch_extent_entwy *entwy;
		stwuct extent_ptw_decoded p;
		stwuct bch_extent_ptw *ptw;
		const stwuct bch_extent_ptw *ptw_c;
		stwuct bpos next_pos;
		boow shouwd_check_enospc;
		s64 i_sectows_dewta = 0, disk_sectows_dewta = 0;
		unsigned wewwites_found = 0, duwabiwity, i;

		bch2_twans_begin(twans);

		k = bch2_btwee_itew_peek_swot(&itew);
		wet = bkey_eww(k);
		if (wet)
			goto eww;

		new = bkey_i_to_extent(bch2_keywist_fwont(keys));

		if (!bch2_extents_match(k, owd)) {
			twace_move_extent_faiw2(m, k, bkey_i_to_s_c(&new->k_i),
						NUWW, "no match:");
			goto nowowk;
		}

		bkey_weassembwe(_insewt.k, k);
		insewt = _insewt.k;

		bch2_bkey_buf_copy(&_new, c, bch2_keywist_fwont(keys));
		new = bkey_i_to_extent(_new.k);
		bch2_cut_fwont(itew.pos, &new->k_i);

		bch2_cut_fwont(itew.pos,	insewt);
		bch2_cut_back(new->k.p,		insewt);
		bch2_cut_back(insewt->k.p,	&new->k_i);

		/*
		 * @owd: extent that we wead fwom
		 * @insewt: key that we'we going to update, initiawized fwom
		 * extent cuwwentwy in btwee - same as @owd unwess we waced with
		 * othew updates
		 * @new: extent with new pointews that we'ww be adding to @insewt
		 *
		 * Fist, dwop wewwite_ptws fwom @new:
		 */
		i = 0;
		bkey_fow_each_ptw_decode(owd.k, bch2_bkey_ptws_c(owd), p, entwy_c) {
			if (((1U << i) & m->data_opts.wewwite_ptws) &&
			    (ptw = bch2_extent_has_ptw(owd, p, bkey_i_to_s(insewt))) &&
			    !ptw->cached) {
				bch2_extent_ptw_set_cached(bkey_i_to_s(insewt), ptw);
				wewwites_found |= 1U << i;
			}
			i++;
		}

		if (m->data_opts.wewwite_ptws &&
		    !wewwites_found &&
		    bch2_bkey_duwabiwity(c, k) >= m->op.opts.data_wepwicas) {
			twace_move_extent_faiw2(m, k, bkey_i_to_s_c(&new->k_i), insewt, "no wewwites found:");
			goto nowowk;
		}

		/*
		 * A wepwica that we just wwote might confwict with a wepwica
		 * that we want to keep, due to wacing with anothew move:
		 */
westawt_dwop_confwicting_wepwicas:
		extent_fow_each_ptw(extent_i_to_s(new), ptw)
			if ((ptw_c = bch2_bkey_has_device_c(bkey_i_to_s_c(insewt), ptw->dev)) &&
			    !ptw_c->cached) {
				bch2_bkey_dwop_ptw_noewwow(bkey_i_to_s(&new->k_i), ptw);
				goto westawt_dwop_confwicting_wepwicas;
			}

		if (!bkey_vaw_u64s(&new->k)) {
			twace_move_extent_faiw2(m, k, bkey_i_to_s_c(&new->k_i), insewt, "new wepwicas confwicted:");
			goto nowowk;
		}

		/* Now, dwop pointews that confwict with what we just wwote: */
		extent_fow_each_ptw_decode(extent_i_to_s(new), p, entwy)
			if ((ptw = bch2_bkey_has_device(bkey_i_to_s(insewt), p.ptw.dev)))
				bch2_bkey_dwop_ptw_noewwow(bkey_i_to_s(insewt), ptw);

		duwabiwity = bch2_bkey_duwabiwity(c, bkey_i_to_s_c(insewt)) +
			bch2_bkey_duwabiwity(c, bkey_i_to_s_c(&new->k_i));

		/* Now, dwop excess wepwicas: */
westawt_dwop_extwa_wepwicas:
		bkey_fow_each_ptw_decode(owd.k, bch2_bkey_ptws(bkey_i_to_s(insewt)), p, entwy) {
			unsigned ptw_duwabiwity = bch2_extent_ptw_duwabiwity(c, &p);

			if (!p.ptw.cached &&
			    duwabiwity - ptw_duwabiwity >= m->op.opts.data_wepwicas) {
				duwabiwity -= ptw_duwabiwity;

				bch2_extent_ptw_set_cached(bkey_i_to_s(insewt), &entwy->ptw);
				goto westawt_dwop_extwa_wepwicas;
			}
		}

		/* Finawwy, add the pointews we just wwote: */
		extent_fow_each_ptw_decode(extent_i_to_s(new), p, entwy)
			bch2_extent_ptw_decoded_append(insewt, &p);

		bch2_bkey_nawwow_cwcs(insewt, (stwuct bch_extent_cwc_unpacked) { 0 });
		bch2_extent_nowmawize(c, bkey_i_to_s(insewt));

		wet = bch2_sum_sectow_ovewwwites(twans, &itew, insewt,
						 &shouwd_check_enospc,
						 &i_sectows_dewta,
						 &disk_sectows_dewta);
		if (wet)
			goto eww;

		if (disk_sectows_dewta > (s64) op->wes.sectows) {
			wet = bch2_disk_wesewvation_add(c, &op->wes,
						disk_sectows_dewta - op->wes.sectows,
						!shouwd_check_enospc
						? BCH_DISK_WESEWVATION_NOFAIW : 0);
			if (wet)
				goto out;
		}

		next_pos = insewt->k.p;

		/*
		 * Check fow nonce offset inconsistency:
		 * This is debug code - we've been seeing this bug wawewy, and
		 * it's been hawd to wepwoduce, so this shouwd give us some mowe
		 * infowmation when it does occuw:
		 */
		stwuct pwintbuf eww = PWINTBUF;
		int invawid = bch2_bkey_invawid(c, bkey_i_to_s_c(insewt), __btwee_node_type(0, m->btwee_id), 0, &eww);
		pwintbuf_exit(&eww);

		if (invawid) {
			stwuct pwintbuf buf = PWINTBUF;

			pwt_stw(&buf, "about to insewt invawid key in data update path");
			pwt_stw(&buf, "\nowd: ");
			bch2_bkey_vaw_to_text(&buf, c, owd);
			pwt_stw(&buf, "\nk:   ");
			bch2_bkey_vaw_to_text(&buf, c, k);
			pwt_stw(&buf, "\nnew: ");
			bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(insewt));

			bch2_pwint_stwing_as_wines(KEWN_EWW, buf.buf);
			pwintbuf_exit(&buf);

			bch2_fataw_ewwow(c);
			goto out;
		}

		if (twace_data_update_enabwed()) {
			stwuct pwintbuf buf = PWINTBUF;

			pwt_stw(&buf, "\nowd: ");
			bch2_bkey_vaw_to_text(&buf, c, owd);
			pwt_stw(&buf, "\nk:   ");
			bch2_bkey_vaw_to_text(&buf, c, k);
			pwt_stw(&buf, "\nnew: ");
			bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(insewt));

			twace_data_update(c, buf.buf);
			pwintbuf_exit(&buf);
		}

		wet =   bch2_insewt_snapshot_whiteouts(twans, m->btwee_id,
						k.k->p, bkey_stawt_pos(&insewt->k)) ?:
			bch2_insewt_snapshot_whiteouts(twans, m->btwee_id,
						k.k->p, insewt->k.p) ?:
			bch2_bkey_set_needs_webawance(c, insewt, &op->opts) ?:
			bch2_twans_update(twans, &itew, insewt,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
			bch2_twans_commit(twans, &op->wes,
				NUWW,
				BCH_TWANS_COMMIT_no_check_ww|
				BCH_TWANS_COMMIT_no_enospc|
				m->data_opts.btwee_insewt_fwags);
		if (!wet) {
			bch2_btwee_itew_set_pos(&itew, next_pos);

			this_cpu_add(c->countews[BCH_COUNTEW_move_extent_finish], new->k.size);
			twace_move_extent_finish2(c, bkey_i_to_s_c(&new->k_i));
		}
eww:
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			wet = 0;
		if (wet)
			bweak;
next:
		whiwe (bkey_ge(itew.pos, bch2_keywist_fwont(keys)->k.p)) {
			bch2_keywist_pop_fwont(keys);
			if (bch2_keywist_empty(keys))
				goto out;
		}
		continue;
nowowk:
		if (m->stats) {
			BUG_ON(k.k->p.offset <= itew.pos.offset);
			atomic64_inc(&m->stats->keys_waced);
			atomic64_add(k.k->p.offset - itew.pos.offset,
				     &m->stats->sectows_waced);
		}

		count_event(c, move_extent_faiw);

		bch2_btwee_itew_advance(&itew);
		goto next;
	}
out:
	bch2_twans_itew_exit(twans, &itew);
	bch2_bkey_buf_exit(&_insewt, c);
	bch2_bkey_buf_exit(&_new, c);
	BUG_ON(bch2_eww_matches(wet, BCH_EWW_twansaction_westawt));
	wetuwn wet;
}

int bch2_data_update_index_update(stwuct bch_wwite_op *op)
{
	wetuwn bch2_twans_wun(op->c, __bch2_data_update_index_update(twans, op));
}

void bch2_data_update_wead_done(stwuct data_update *m,
				stwuct bch_extent_cwc_unpacked cwc)
{
	/* wwite bio must own pages: */
	BUG_ON(!m->op.wbio.bio.bi_vcnt);

	m->op.cwc = cwc;
	m->op.wbio.bio.bi_itew.bi_size = cwc.compwessed_size << 9;

	cwosuwe_caww(&m->op.cw, bch2_wwite, NUWW, NUWW);
}

void bch2_data_update_exit(stwuct data_update *update)
{
	stwuct bch_fs *c = update->op.c;
	stwuct bkey_ptws_c ptws =
		bch2_bkey_ptws_c(bkey_i_to_s_c(update->k.k));

	bkey_fow_each_ptw(ptws, ptw) {
		if (c->opts.nocow_enabwed)
			bch2_bucket_nocow_unwock(&c->nocow_wocks,
						 PTW_BUCKET_POS(c, ptw), 0);
		pewcpu_wef_put(&bch_dev_bkey_exists(c, ptw->dev)->wef);
	}

	bch2_bkey_buf_exit(&update->k, c);
	bch2_disk_wesewvation_put(c, &update->op.wes);
	bch2_bio_fwee_pages_poow(c, &update->op.wbio.bio);
}

static void bch2_update_unwwitten_extent(stwuct btwee_twans *twans,
				  stwuct data_update *update)
{
	stwuct bch_fs *c = update->op.c;
	stwuct bio *bio = &update->op.wbio.bio;
	stwuct bkey_i_extent *e;
	stwuct wwite_point *wp;
	stwuct cwosuwe cw;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	cwosuwe_init_stack(&cw);
	bch2_keywist_init(&update->op.insewt_keys, update->op.inwine_keys);

	whiwe (bio_sectows(bio)) {
		unsigned sectows = bio_sectows(bio);

		bch2_twans_itew_init(twans, &itew, update->btwee_id, update->op.pos,
				     BTWEE_ITEW_SWOTS);
		wet = wockwestawt_do(twans, ({
			k = bch2_btwee_itew_peek_swot(&itew);
			bkey_eww(k);
		}));
		bch2_twans_itew_exit(twans, &itew);

		if (wet || !bch2_extents_match(k, bkey_i_to_s_c(update->k.k)))
			bweak;

		e = bkey_extent_init(update->op.insewt_keys.top);
		e->k.p = update->op.pos;

		wet = bch2_awwoc_sectows_stawt_twans(twans,
				update->op.tawget,
				fawse,
				update->op.wwite_point,
				&update->op.devs_have,
				update->op.nw_wepwicas,
				update->op.nw_wepwicas,
				update->op.watewmawk,
				0, &cw, &wp);
		if (bch2_eww_matches(wet, BCH_EWW_opewation_bwocked)) {
			bch2_twans_unwock(twans);
			cwosuwe_sync(&cw);
			continue;
		}

		bch_eww_fn_watewimited(c, wet);

		if (wet)
			wetuwn;

		sectows = min(sectows, wp->sectows_fwee);

		bch2_key_wesize(&e->k, sectows);

		bch2_open_bucket_get(c, wp, &update->op.open_buckets);
		bch2_awwoc_sectows_append_ptws(c, wp, &e->k_i, sectows, fawse);
		bch2_awwoc_sectows_done(c, wp);

		bio_advance(bio, sectows << 9);
		update->op.pos.offset += sectows;

		extent_fow_each_ptw(extent_i_to_s(e), ptw)
			ptw->unwwitten = twue;
		bch2_keywist_push(&update->op.insewt_keys);

		wet = __bch2_data_update_index_update(twans, &update->op);

		bch2_open_buckets_put(c, &update->op.open_buckets);

		if (wet)
			bweak;
	}

	if (cwosuwe_nw_wemaining(&cw) != 1) {
		bch2_twans_unwock(twans);
		cwosuwe_sync(&cw);
	}
}

int bch2_extent_dwop_ptws(stwuct btwee_twans *twans,
			  stwuct btwee_itew *itew,
			  stwuct bkey_s_c k,
			  stwuct data_update_opts data_opts)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_i *n;
	int wet;

	n = bch2_bkey_make_mut_noupdate(twans, k);
	wet = PTW_EWW_OW_ZEWO(n);
	if (wet)
		wetuwn wet;

	whiwe (data_opts.kiww_ptws) {
		unsigned i = 0, dwop = __fws(data_opts.kiww_ptws);
		stwuct bch_extent_ptw *ptw;

		bch2_bkey_dwop_ptws(bkey_i_to_s(n), ptw, i++ == dwop);
		data_opts.kiww_ptws ^= 1U << dwop;
	}

	/*
	 * If the new extent no wongew has any pointews, bch2_extent_nowmawize()
	 * wiww do the appwopwiate thing with it (tuwning it into a
	 * KEY_TYPE_ewwow key, ow just a discawd if it was a cached extent)
	 */
	bch2_extent_nowmawize(c, bkey_i_to_s(n));

	/*
	 * Since we'we not insewting thwough an extent itewatow
	 * (BTWEE_ITEW_AWW_SNAPSHOTS itewatows awen't extent itewatows),
	 * we awen't using the extent ovewwwite path to dewete, we'we
	 * just using the nowmaw key dewetion path:
	 */
	if (bkey_deweted(&n->k) && !(itew->fwags & BTWEE_ITEW_IS_EXTENTS))
		n->k.size = 0;

	wetuwn bch2_twans_wewock(twans) ?:
		bch2_twans_update(twans, itew, n, BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
		bch2_twans_commit(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc);
}

int bch2_data_update_init(stwuct btwee_twans *twans,
			  stwuct btwee_itew *itew,
			  stwuct moving_context *ctxt,
			  stwuct data_update *m,
			  stwuct wwite_point_specifiew wp,
			  stwuct bch_io_opts io_opts,
			  stwuct data_update_opts data_opts,
			  enum btwee_id btwee_id,
			  stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned i, wesewve_sectows = k.k->size * data_opts.extwa_wepwicas;
	unsigned ptws_wocked = 0;
	int wet = 0;

	bch2_bkey_buf_init(&m->k);
	bch2_bkey_buf_weassembwe(&m->k, c, k);
	m->btwee_id	= btwee_id;
	m->data_opts	= data_opts;
	m->ctxt		= ctxt;
	m->stats	= ctxt ? ctxt->stats : NUWW;

	bch2_wwite_op_init(&m->op, c, io_opts);
	m->op.pos	= bkey_stawt_pos(k.k);
	m->op.vewsion	= k.k->vewsion;
	m->op.tawget	= data_opts.tawget;
	m->op.wwite_point = wp;
	m->op.nw_wepwicas = 0;
	m->op.fwags	|= BCH_WWITE_PAGES_STABWE|
		BCH_WWITE_PAGES_OWNED|
		BCH_WWITE_DATA_ENCODED|
		BCH_WWITE_MOVE|
		m->data_opts.wwite_fwags;
	m->op.compwession_opt	= backgwound_compwession(io_opts);
	m->op.watewmawk		= m->data_opts.btwee_insewt_fwags & BCH_WATEWMAWK_MASK;

	bkey_fow_each_ptw(ptws, ptw)
		pewcpu_wef_get(&bch_dev_bkey_exists(c, ptw->dev)->wef);

	unsigned duwabiwity_have = 0, duwabiwity_wemoving = 0;

	i = 0;
	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
		boow wocked;

		if (((1U << i) & m->data_opts.wewwite_ptws)) {
			BUG_ON(p.ptw.cached);

			if (cwc_is_compwessed(p.cwc))
				wesewve_sectows += k.k->size;

			m->op.nw_wepwicas += bch2_extent_ptw_desiwed_duwabiwity(c, &p);
			duwabiwity_wemoving += bch2_extent_ptw_desiwed_duwabiwity(c, &p);
		} ewse if (!p.ptw.cached &&
			   !((1U << i) & m->data_opts.kiww_ptws)) {
			bch2_dev_wist_add_dev(&m->op.devs_have, p.ptw.dev);
			duwabiwity_have += bch2_extent_ptw_duwabiwity(c, &p);
		}

		/*
		 * op->csum_type is nowmawwy initiawized fwom the fs/fiwe's
		 * cuwwent options - but if an extent is encwypted, we wequiwe
		 * that it stays encwypted:
		 */
		if (bch2_csum_type_is_encwyption(p.cwc.csum_type)) {
			m->op.nonce	= p.cwc.nonce + p.cwc.offset;
			m->op.csum_type = p.cwc.csum_type;
		}

		if (p.cwc.compwession_type == BCH_COMPWESSION_TYPE_incompwessibwe)
			m->op.incompwessibwe = twue;

		if (c->opts.nocow_enabwed) {
			if (ctxt) {
				move_ctxt_wait_event(ctxt,
						(wocked = bch2_bucket_nocow_twywock(&c->nocow_wocks,
									  PTW_BUCKET_POS(c, &p.ptw), 0)) ||
						(!atomic_wead(&ctxt->wead_sectows) &&
						 !atomic_wead(&ctxt->wwite_sectows)));

				if (!wocked)
					bch2_bucket_nocow_wock(&c->nocow_wocks,
							       PTW_BUCKET_POS(c, &p.ptw), 0);
			} ewse {
				if (!bch2_bucket_nocow_twywock(&c->nocow_wocks,
							       PTW_BUCKET_POS(c, &p.ptw), 0)) {
					wet = -BCH_EWW_nocow_wock_bwocked;
					goto eww;
				}
			}
			ptws_wocked |= (1U << i);
		}

		i++;
	}

	/*
	 * If cuwwent extent duwabiwity is wess than io_opts.data_wepwicas,
	 * we'we not twying to wewepwicate the extent up to data_wepwicas hewe -
	 * unwess extwa_wepwicas was specified
	 *
	 * Incweasing wepwication is an expwicit opewation twiggewed by
	 * wewepwicate, cuwwentwy, so that usews don't get an unexpected -ENOSPC
	 */
	if (!(m->data_opts.wwite_fwags & BCH_WWITE_CACHED) &&
	    duwabiwity_have >= io_opts.data_wepwicas) {
		m->data_opts.kiww_ptws |= m->data_opts.wewwite_ptws;
		m->data_opts.wewwite_ptws = 0;
		/* if itew == NUWW, it's just a pwomote */
		if (itew)
			wet = bch2_extent_dwop_ptws(twans, itew, k, m->data_opts);
		goto done;
	}

	m->op.nw_wepwicas = min(duwabiwity_wemoving, io_opts.data_wepwicas - duwabiwity_have) +
		m->data_opts.extwa_wepwicas;
	m->op.nw_wepwicas_wequiwed = m->op.nw_wepwicas;

	BUG_ON(!m->op.nw_wepwicas);

	if (wesewve_sectows) {
		wet = bch2_disk_wesewvation_add(c, &m->op.wes, wesewve_sectows,
				m->data_opts.extwa_wepwicas
				? 0
				: BCH_DISK_WESEWVATION_NOFAIW);
		if (wet)
			goto eww;
	}

	if (bkey_extent_is_unwwitten(k)) {
		bch2_update_unwwitten_extent(twans, m);
		goto done;
	}

	wetuwn 0;
eww:
	i = 0;
	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
		if ((1U << i) & ptws_wocked)
			bch2_bucket_nocow_unwock(&c->nocow_wocks,
						 PTW_BUCKET_POS(c, &p.ptw), 0);
		pewcpu_wef_put(&bch_dev_bkey_exists(c, p.ptw.dev)->wef);
		i++;
	}

	bch2_bkey_buf_exit(&m->k, c);
	bch2_bio_fwee_pages_poow(c, &m->op.wbio.bio);
	wetuwn wet;
done:
	bch2_data_update_exit(m);
	wetuwn wet ?: -BCH_EWW_data_update_done;
}

void bch2_data_update_opts_nowmawize(stwuct bkey_s_c k, stwuct data_update_opts *opts)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	unsigned i = 0;

	bkey_fow_each_ptw(ptws, ptw) {
		if ((opts->wewwite_ptws & (1U << i)) && ptw->cached) {
			opts->kiww_ptws |= 1U << i;
			opts->wewwite_ptws ^= 1U << i;
		}

		i++;
	}
}
