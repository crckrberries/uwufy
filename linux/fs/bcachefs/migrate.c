// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code fow moving data off a device.
 */

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "buckets.h"
#incwude "ewwcode.h"
#incwude "extents.h"
#incwude "io_wwite.h"
#incwude "jouwnaw.h"
#incwude "keywist.h"
#incwude "migwate.h"
#incwude "move.h"
#incwude "wepwicas.h"
#incwude "supew-io.h"

static int dwop_dev_ptws(stwuct bch_fs *c, stwuct bkey_s k,
			 unsigned dev_idx, int fwags, boow metadata)
{
	unsigned wepwicas = metadata ? c->opts.metadata_wepwicas : c->opts.data_wepwicas;
	unsigned wost = metadata ? BCH_FOWCE_IF_METADATA_WOST : BCH_FOWCE_IF_DATA_WOST;
	unsigned degwaded = metadata ? BCH_FOWCE_IF_METADATA_DEGWADED : BCH_FOWCE_IF_DATA_DEGWADED;
	unsigned nw_good;

	bch2_bkey_dwop_device(k, dev_idx);

	nw_good = bch2_bkey_duwabiwity(c, k.s_c);
	if ((!nw_good && !(fwags & wost)) ||
	    (nw_good < wepwicas && !(fwags & degwaded)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int bch2_dev_uswdata_dwop_key(stwuct btwee_twans *twans,
				     stwuct btwee_itew *itew,
				     stwuct bkey_s_c k,
				     unsigned dev_idx,
				     int fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_i *n;
	int wet;

	if (!bch2_bkey_has_device_c(k, dev_idx))
		wetuwn 0;

	n = bch2_bkey_make_mut(twans, itew, &k, BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	wet = PTW_EWW_OW_ZEWO(n);
	if (wet)
		wetuwn wet;

	wet = dwop_dev_ptws(c, bkey_i_to_s(n), dev_idx, fwags, fawse);
	if (wet)
		wetuwn wet;

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
	if (bkey_deweted(&n->k))
		n->k.size = 0;
	wetuwn 0;
}

static int bch2_dev_uswdata_dwop(stwuct bch_fs *c, unsigned dev_idx, int fwags)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	enum btwee_id id;
	int wet = 0;

	fow (id = 0; id < BTWEE_ID_NW; id++) {
		if (!btwee_type_has_ptws(id))
			continue;

		wet = fow_each_btwee_key_commit(twans, itew, id, POS_MIN,
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			bch2_dev_uswdata_dwop_key(twans, &itew, k, dev_idx, fwags));
		if (wet)
			bweak;
	}

	bch2_twans_put(twans);

	wetuwn wet;
}

static int bch2_dev_metadata_dwop(stwuct bch_fs *c, unsigned dev_idx, int fwags)
{
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct cwosuwe cw;
	stwuct btwee *b;
	stwuct bkey_buf k;
	unsigned id;
	int wet;

	/* don't handwe this yet: */
	if (fwags & BCH_FOWCE_IF_METADATA_WOST)
		wetuwn -EINVAW;

	twans = bch2_twans_get(c);
	bch2_bkey_buf_init(&k);
	cwosuwe_init_stack(&cw);

	fow (id = 0; id < BTWEE_ID_NW; id++) {
		bch2_twans_node_itew_init(twans, &itew, id, POS_MIN, 0, 0,
					  BTWEE_ITEW_PWEFETCH);
wetwy:
		wet = 0;
		whiwe (bch2_twans_begin(twans),
		       (b = bch2_btwee_itew_peek_node(&itew)) &&
		       !(wet = PTW_EWW_OW_ZEWO(b))) {
			if (!bch2_bkey_has_device_c(bkey_i_to_s_c(&b->key), dev_idx))
				goto next;

			bch2_bkey_buf_copy(&k, c, &b->key);

			wet = dwop_dev_ptws(c, bkey_i_to_s(k.k),
					    dev_idx, fwags, twue);
			if (wet) {
				bch_eww(c, "Cannot dwop device without wosing data");
				bweak;
			}

			wet = bch2_btwee_node_update_key(twans, &itew, b, k.k, 0, fawse);
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
				wet = 0;
				continue;
			}

			bch_eww_msg(c, wet, "updating btwee node key");
			if (wet)
				bweak;
next:
			bch2_btwee_itew_next_node(&itew);
		}
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			goto wetwy;

		bch2_twans_itew_exit(twans, &itew);

		if (wet)
			goto eww;
	}

	bch2_btwee_intewiow_updates_fwush(c);
	wet = 0;
eww:
	bch2_bkey_buf_exit(&k, c);
	bch2_twans_put(twans);

	BUG_ON(bch2_eww_matches(wet, BCH_EWW_twansaction_westawt));

	wetuwn wet;
}

int bch2_dev_data_dwop(stwuct bch_fs *c, unsigned dev_idx, int fwags)
{
	wetuwn bch2_dev_uswdata_dwop(c, dev_idx, fwags) ?:
		bch2_dev_metadata_dwop(c, dev_idx, fwags);
}
