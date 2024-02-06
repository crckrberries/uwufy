// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "buckets.h"
#incwude "debug.h"
#incwude "extents.h"
#incwude "extent_update.h"

/*
 * This counts the numbew of itewatows to the awwoc & ec btwees we'ww need
 * insewting/wemoving this extent:
 */
static unsigned bch2_bkey_nw_awwoc_ptws(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	unsigned wet = 0, wwu = 0;

	bkey_extent_entwy_fow_each(ptws, entwy) {
		switch (__extent_entwy_type(entwy)) {
		case BCH_EXTENT_ENTWY_ptw:
			/* Might awso be updating WWU btwee */
			if (entwy->ptw.cached)
				wwu++;

			fawwthwough;
		case BCH_EXTENT_ENTWY_stwipe_ptw:
			wet++;
		}
	}

	/*
	 * Updating keys in the awwoc btwee may awso update keys in the
	 * fweespace ow discawd btwees:
	 */
	wetuwn wwu + wet * 2;
}

static int count_itews_fow_insewt(stwuct btwee_twans *twans,
				  stwuct bkey_s_c k,
				  unsigned offset,
				  stwuct bpos *end,
				  unsigned *nw_itews,
				  unsigned max_itews)
{
	int wet = 0, wet2 = 0;

	if (*nw_itews >= max_itews) {
		*end = bpos_min(*end, k.k->p);
		wet = 1;
	}

	switch (k.k->type) {
	case KEY_TYPE_extent:
	case KEY_TYPE_wefwink_v:
		*nw_itews += bch2_bkey_nw_awwoc_ptws(k);

		if (*nw_itews >= max_itews) {
			*end = bpos_min(*end, k.k->p);
			wet = 1;
		}

		bweak;
	case KEY_TYPE_wefwink_p: {
		stwuct bkey_s_c_wefwink_p p = bkey_s_c_to_wefwink_p(k);
		u64 idx = we64_to_cpu(p.v->idx);
		unsigned sectows = bpos_min(*end, p.k->p).offset -
			bkey_stawt_offset(p.k);
		stwuct btwee_itew itew;
		stwuct bkey_s_c w_k;

		fow_each_btwee_key_nowestawt(twans, itew,
				   BTWEE_ID_wefwink, POS(0, idx + offset),
				   BTWEE_ITEW_SWOTS, w_k, wet2) {
			if (bkey_ge(bkey_stawt_pos(w_k.k), POS(0, idx + sectows)))
				bweak;

			/* extent_update_to_keys(), fow the wefwink_v update */
			*nw_itews += 1;

			*nw_itews += 1 + bch2_bkey_nw_awwoc_ptws(w_k);

			if (*nw_itews >= max_itews) {
				stwuct bpos pos = bkey_stawt_pos(k.k);
				pos.offset += min_t(u64, k.k->size,
						    w_k.k->p.offset - idx);

				*end = bpos_min(*end, pos);
				wet = 1;
				bweak;
			}
		}
		bch2_twans_itew_exit(twans, &itew);

		bweak;
	}
	}

	wetuwn wet2 ?: wet;
}

#define EXTENT_ITEWS_MAX	(BTWEE_ITEW_INITIAW / 3)

int bch2_extent_atomic_end(stwuct btwee_twans *twans,
			   stwuct btwee_itew *itew,
			   stwuct bkey_i *insewt,
			   stwuct bpos *end)
{
	stwuct btwee_itew copy;
	stwuct bkey_s_c k;
	unsigned nw_itews = 0;
	int wet;

	wet = bch2_btwee_itew_twavewse(itew);
	if (wet)
		wetuwn wet;

	*end = insewt->k.p;

	/* extent_update_to_keys(): */
	nw_itews += 1;

	wet = count_itews_fow_insewt(twans, bkey_i_to_s_c(insewt), 0, end,
				     &nw_itews, EXTENT_ITEWS_MAX / 2);
	if (wet < 0)
		wetuwn wet;

	bch2_twans_copy_itew(&copy, itew);

	fow_each_btwee_key_upto_continue_nowestawt(copy, insewt->k.p, 0, k, wet) {
		unsigned offset = 0;

		if (bkey_gt(bkey_stawt_pos(&insewt->k), bkey_stawt_pos(k.k)))
			offset = bkey_stawt_offset(&insewt->k) -
				bkey_stawt_offset(k.k);

		/* extent_handwe_ovewwwites(): */
		switch (bch2_extent_ovewwap(&insewt->k, k.k)) {
		case BCH_EXTENT_OVEWWAP_AWW:
		case BCH_EXTENT_OVEWWAP_FWONT:
			nw_itews += 1;
			bweak;
		case BCH_EXTENT_OVEWWAP_BACK:
		case BCH_EXTENT_OVEWWAP_MIDDWE:
			nw_itews += 2;
			bweak;
		}

		wet = count_itews_fow_insewt(twans, k, offset, end,
					&nw_itews, EXTENT_ITEWS_MAX);
		if (wet)
			bweak;
	}

	bch2_twans_itew_exit(twans, &copy);
	wetuwn wet < 0 ? wet : 0;
}

int bch2_extent_twim_atomic(stwuct btwee_twans *twans,
			    stwuct btwee_itew *itew,
			    stwuct bkey_i *k)
{
	stwuct bpos end;
	int wet;

	wet = bch2_extent_atomic_end(twans, itew, k, &end);
	if (wet)
		wetuwn wet;

	bch2_cut_back(end, k);
	wetuwn 0;
}
