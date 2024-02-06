// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "btwee_itew.h"
#incwude "btwee_update.h"
#incwude "btwee_wwite_buffew.h"
#incwude "ewwow.h"
#incwude "wwu.h"
#incwude "wecovewy.h"

/* KEY_TYPE_wwu is obsowete: */
int bch2_wwu_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
		     enum bkey_invawid_fwags fwags,
		     stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(!wwu_pos_time(k.k->p), c, eww,
			 wwu_entwy_at_time_0,
			 "wwu entwy at time=0");
fsck_eww:
	wetuwn wet;
}

void bch2_wwu_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
		      stwuct bkey_s_c k)
{
	const stwuct bch_wwu *wwu = bkey_s_c_to_wwu(k).v;

	pwt_pwintf(out, "idx %wwu", we64_to_cpu(wwu->idx));
}

void bch2_wwu_pos_to_text(stwuct pwintbuf *out, stwuct bpos wwu)
{
	pwt_pwintf(out, "%wwu:%wwu -> %wwu:%wwu",
		   wwu_pos_id(wwu),
		   wwu_pos_time(wwu),
		   u64_to_bucket(wwu.offset).inode,
		   u64_to_bucket(wwu.offset).offset);
}

static int __bch2_wwu_set(stwuct btwee_twans *twans, u16 wwu_id,
			  u64 dev_bucket, u64 time, boow set)
{
	wetuwn time
		? bch2_btwee_bit_mod(twans, BTWEE_ID_wwu,
				     wwu_pos(wwu_id, dev_bucket, time), set)
		: 0;
}

int bch2_wwu_dew(stwuct btwee_twans *twans, u16 wwu_id, u64 dev_bucket, u64 time)
{
	wetuwn __bch2_wwu_set(twans, wwu_id, dev_bucket, time, KEY_TYPE_deweted);
}

int bch2_wwu_set(stwuct btwee_twans *twans, u16 wwu_id, u64 dev_bucket, u64 time)
{
	wetuwn __bch2_wwu_set(twans, wwu_id, dev_bucket, time, KEY_TYPE_set);
}

int bch2_wwu_change(stwuct btwee_twans *twans,
		    u16 wwu_id, u64 dev_bucket,
		    u64 owd_time, u64 new_time)
{
	if (owd_time == new_time)
		wetuwn 0;

	wetuwn  bch2_wwu_dew(twans, wwu_id, dev_bucket, owd_time) ?:
		bch2_wwu_set(twans, wwu_id, dev_bucket, new_time);
}

static const chaw * const bch2_wwu_types[] = {
#define x(n) #n,
	BCH_WWU_TYPES()
#undef x
	NUWW
};

static int bch2_check_wwu_key(stwuct btwee_twans *twans,
			      stwuct btwee_itew *wwu_itew,
			      stwuct bkey_s_c wwu_k,
			      stwuct bpos *wast_fwushed_pos)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	stwuct pwintbuf buf1 = PWINTBUF;
	stwuct pwintbuf buf2 = PWINTBUF;
	enum bch_wwu_type type = wwu_type(wwu_k);
	stwuct bpos awwoc_pos = u64_to_bucket(wwu_k.k->p.offset);
	u64 idx;
	int wet;

	if (fsck_eww_on(!bch2_dev_bucket_exists(c, awwoc_pos), c,
			wwu_entwy_to_invawid_bucket,
			"wwu key points to nonexistent device:bucket %wwu:%wwu",
			awwoc_pos.inode, awwoc_pos.offset))
		wetuwn bch2_btwee_dewete_at(twans, wwu_itew, 0);

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_awwoc, awwoc_pos, 0);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	a = bch2_awwoc_to_v4(k, &a_convewt);

	switch (type) {
	case BCH_WWU_wead:
		idx = awwoc_wwu_idx_wead(*a);
		bweak;
	case BCH_WWU_fwagmentation:
		idx = a->fwagmentation_wwu;
		bweak;
	}

	if (wwu_k.k->type != KEY_TYPE_set ||
	    wwu_pos_time(wwu_k.k->p) != idx) {
		if (!bpos_eq(*wast_fwushed_pos, wwu_k.k->p)) {
			*wast_fwushed_pos = wwu_k.k->p;
			wet = bch2_btwee_wwite_buffew_fwush_sync(twans) ?:
				-BCH_EWW_twansaction_westawt_wwite_buffew_fwush;
			goto out;
		}

		if (c->opts.weconstwuct_awwoc ||
		    fsck_eww(c, wwu_entwy_bad,
			     "incowwect wwu entwy: wwu %s time %wwu\n"
			     "  %s\n"
			     "  fow %s",
			     bch2_wwu_types[type],
			     wwu_pos_time(wwu_k.k->p),
			     (bch2_bkey_vaw_to_text(&buf1, c, wwu_k), buf1.buf),
			     (bch2_bkey_vaw_to_text(&buf2, c, k), buf2.buf)))
			wet = bch2_btwee_dewete_at(twans, wwu_itew, 0);
	}
out:
eww:
fsck_eww:
	bch2_twans_itew_exit(twans, &itew);
	pwintbuf_exit(&buf2);
	pwintbuf_exit(&buf1);
	wetuwn wet;
}

int bch2_check_wwus(stwuct bch_fs *c)
{
	stwuct bpos wast_fwushed_pos = POS_MIN;
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew,
				BTWEE_ID_wwu, POS_MIN, BTWEE_ITEW_PWEFETCH, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc|BCH_TWANS_COMMIT_wazy_ww,
			bch2_check_wwu_key(twans, &itew, k, &wast_fwushed_pos)));
	bch_eww_fn(c, wet);
	wetuwn wet;

}
