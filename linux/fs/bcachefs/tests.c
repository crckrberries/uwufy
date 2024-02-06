// SPDX-Wicense-Identifiew: GPW-2.0
#ifdef CONFIG_BCACHEFS_TESTS

#incwude "bcachefs.h"
#incwude "btwee_update.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "snapshot.h"
#incwude "tests.h"

#incwude "winux/kthwead.h"
#incwude "winux/wandom.h"

static void dewete_test_keys(stwuct bch_fs *c)
{
	int wet;

	wet = bch2_btwee_dewete_wange(c, BTWEE_ID_extents,
				      SPOS(0, 0, U32_MAX),
				      POS(0, U64_MAX),
				      0, NUWW);
	BUG_ON(wet);

	wet = bch2_btwee_dewete_wange(c, BTWEE_ID_xattws,
				      SPOS(0, 0, U32_MAX),
				      POS(0, U64_MAX),
				      0, NUWW);
	BUG_ON(wet);
}

/* unit tests */

static int test_dewete(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_i_cookie k;
	int wet;

	bkey_cookie_init(&k.k_i);
	k.k.p.snapshot = U32_MAX;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws, k.k.p,
			     BTWEE_ITEW_INTENT);

	wet = commit_do(twans, NUWW, NUWW, 0,
		bch2_btwee_itew_twavewse(&itew) ?:
		bch2_twans_update(twans, &itew, &k.k_i, 0));
	bch_eww_msg(c, wet, "update ewwow");
	if (wet)
		goto eww;

	pw_info("deweting once");
	wet = commit_do(twans, NUWW, NUWW, 0,
		bch2_btwee_itew_twavewse(&itew) ?:
		bch2_btwee_dewete_at(twans, &itew, 0));
	bch_eww_msg(c, wet, "dewete ewwow (fiwst)");
	if (wet)
		goto eww;

	pw_info("deweting twice");
	wet = commit_do(twans, NUWW, NUWW, 0,
		bch2_btwee_itew_twavewse(&itew) ?:
		bch2_btwee_dewete_at(twans, &itew, 0));
	bch_eww_msg(c, wet, "dewete ewwow (second)");
	if (wet)
		goto eww;
eww:
	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static int test_dewete_wwitten(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_i_cookie k;
	int wet;

	bkey_cookie_init(&k.k_i);
	k.k.p.snapshot = U32_MAX;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws, k.k.p,
			     BTWEE_ITEW_INTENT);

	wet = commit_do(twans, NUWW, NUWW, 0,
		bch2_btwee_itew_twavewse(&itew) ?:
		bch2_twans_update(twans, &itew, &k.k_i, 0));
	bch_eww_msg(c, wet, "update ewwow");
	if (wet)
		goto eww;

	bch2_twans_unwock(twans);
	bch2_jouwnaw_fwush_aww_pins(&c->jouwnaw);

	wet = commit_do(twans, NUWW, NUWW, 0,
		bch2_btwee_itew_twavewse(&itew) ?:
		bch2_btwee_dewete_at(twans, &itew, 0));
	bch_eww_msg(c, wet, "dewete ewwow");
	if (wet)
		goto eww;
eww:
	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static int test_itewate(stwuct bch_fs *c, u64 nw)
{
	u64 i;
	int wet = 0;

	dewete_test_keys(c);

	pw_info("insewting test keys");

	fow (i = 0; i < nw; i++) {
		stwuct bkey_i_cookie ck;

		bkey_cookie_init(&ck.k_i);
		ck.k.p.offset = i;
		ck.k.p.snapshot = U32_MAX;

		wet = bch2_btwee_insewt(c, BTWEE_ID_xattws, &ck.k_i, NUWW, 0);
		bch_eww_msg(c, wet, "insewt ewwow");
		if (wet)
			wetuwn wet;
	}

	pw_info("itewating fowwawds");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_xattws,
					SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					0, k, ({
			BUG_ON(k.k->p.offset != i++);
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i != nw);

	pw_info("itewating backwawds");

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_wevewse(twans, itew, BTWEE_ID_xattws,
				SPOS(0, U64_MAX, U32_MAX), 0, k, ({
			BUG_ON(k.k->p.offset != --i);
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating backwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i);
	wetuwn 0;
}

static int test_itewate_extents(stwuct bch_fs *c, u64 nw)
{
	u64 i;
	int wet = 0;

	dewete_test_keys(c);

	pw_info("insewting test extents");

	fow (i = 0; i < nw; i += 8) {
		stwuct bkey_i_cookie ck;

		bkey_cookie_init(&ck.k_i);
		ck.k.p.offset = i + 8;
		ck.k.p.snapshot = U32_MAX;
		ck.k.size = 8;

		wet = bch2_btwee_insewt(c, BTWEE_ID_extents, &ck.k_i, NUWW, 0);
		bch_eww_msg(c, wet, "insewt ewwow");
		if (wet)
			wetuwn wet;
	}

	pw_info("itewating fowwawds");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_extents,
					SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					0, k, ({
			BUG_ON(bkey_stawt_offset(k.k) != i);
			i = k.k->p.offset;
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i != nw);

	pw_info("itewating backwawds");

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_wevewse(twans, itew, BTWEE_ID_extents,
				SPOS(0, U64_MAX, U32_MAX), 0, k, ({
			BUG_ON(k.k->p.offset != i);
			i = bkey_stawt_offset(k.k);
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating backwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i);
	wetuwn 0;
}

static int test_itewate_swots(stwuct bch_fs *c, u64 nw)
{
	u64 i;
	int wet = 0;

	dewete_test_keys(c);

	pw_info("insewting test keys");

	fow (i = 0; i < nw; i++) {
		stwuct bkey_i_cookie ck;

		bkey_cookie_init(&ck.k_i);
		ck.k.p.offset = i * 2;
		ck.k.p.snapshot = U32_MAX;

		wet = bch2_btwee_insewt(c, BTWEE_ID_xattws, &ck.k_i, NUWW, 0);
		bch_eww_msg(c, wet, "insewt ewwow");
		if (wet)
			wetuwn wet;
	}

	pw_info("itewating fowwawds");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_xattws,
					  SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					  0, k, ({
			BUG_ON(k.k->p.offset != i);
			i += 2;
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i != nw * 2);

	pw_info("itewating fowwawds by swots");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_xattws,
					SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					BTWEE_ITEW_SWOTS, k, ({
			if (i >= nw * 2)
				bweak;

			BUG_ON(k.k->p.offset != i);
			BUG_ON(bkey_deweted(k.k) != (i & 1));

			i++;
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds by swots");
	wetuwn wet;
}

static int test_itewate_swots_extents(stwuct bch_fs *c, u64 nw)
{
	u64 i;
	int wet = 0;

	dewete_test_keys(c);

	pw_info("insewting test keys");

	fow (i = 0; i < nw; i += 16) {
		stwuct bkey_i_cookie ck;

		bkey_cookie_init(&ck.k_i);
		ck.k.p.offset = i + 16;
		ck.k.p.snapshot = U32_MAX;
		ck.k.size = 8;

		wet = bch2_btwee_insewt(c, BTWEE_ID_extents, &ck.k_i, NUWW, 0);
		bch_eww_msg(c, wet, "insewt ewwow");
		if (wet)
			wetuwn wet;
	}

	pw_info("itewating fowwawds");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_extents,
					SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					0, k, ({
			BUG_ON(bkey_stawt_offset(k.k) != i + 8);
			BUG_ON(k.k->size != 8);
			i += 16;
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds");
	if (wet)
		wetuwn wet;

	BUG_ON(i != nw);

	pw_info("itewating fowwawds by swots");
	i = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_extents,
					SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
					BTWEE_ITEW_SWOTS, k, ({
			if (i == nw)
				bweak;
			BUG_ON(bkey_deweted(k.k) != !(i % 16));

			BUG_ON(bkey_stawt_offset(k.k) != i);
			BUG_ON(k.k->size != 8);
			i = k.k->p.offset;
			0;
		})));
	bch_eww_msg(c, wet, "ewwow itewating fowwawds by swots");
	wetuwn wet;
}

/*
 * XXX: we weawwy want to make suwe we've got a btwee with depth > 0 fow these
 * tests
 */
static int test_peek_end(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws,
			     SPOS(0, 0, U32_MAX), 0);

	wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek_upto(&itew, POS(0, U64_MAX))));
	BUG_ON(k.k);

	wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek_upto(&itew, POS(0, U64_MAX))));
	BUG_ON(k.k);

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn 0;
}

static int test_peek_end_extents(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     SPOS(0, 0, U32_MAX), 0);

	wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek_upto(&itew, POS(0, U64_MAX))));
	BUG_ON(k.k);

	wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek_upto(&itew, POS(0, U64_MAX))));
	BUG_ON(k.k);

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn 0;
}

/* extent unit tests */

static u64 test_vewsion;

static int insewt_test_extent(stwuct bch_fs *c,
			      u64 stawt, u64 end)
{
	stwuct bkey_i_cookie k;
	int wet;

	bkey_cookie_init(&k.k_i);
	k.k_i.k.p.offset = end;
	k.k_i.k.p.snapshot = U32_MAX;
	k.k_i.k.size = end - stawt;
	k.k_i.k.vewsion.wo = test_vewsion++;

	wet = bch2_btwee_insewt(c, BTWEE_ID_extents, &k.k_i, NUWW, 0);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int __test_extent_ovewwwite(stwuct bch_fs *c,
				    u64 e1_stawt, u64 e1_end,
				    u64 e2_stawt, u64 e2_end)
{
	int wet;

	wet   = insewt_test_extent(c, e1_stawt, e1_end) ?:
		insewt_test_extent(c, e2_stawt, e2_end);

	dewete_test_keys(c);
	wetuwn wet;
}

static int test_extent_ovewwwite_fwont(stwuct bch_fs *c, u64 nw)
{
	wetuwn  __test_extent_ovewwwite(c, 0, 64, 0, 32) ?:
		__test_extent_ovewwwite(c, 8, 64, 0, 32);
}

static int test_extent_ovewwwite_back(stwuct bch_fs *c, u64 nw)
{
	wetuwn  __test_extent_ovewwwite(c, 0, 64, 32, 64) ?:
		__test_extent_ovewwwite(c, 0, 64, 32, 72);
}

static int test_extent_ovewwwite_middwe(stwuct bch_fs *c, u64 nw)
{
	wetuwn __test_extent_ovewwwite(c, 0, 64, 32, 40);
}

static int test_extent_ovewwwite_aww(stwuct bch_fs *c, u64 nw)
{
	wetuwn  __test_extent_ovewwwite(c, 32, 64,  0,  64) ?:
		__test_extent_ovewwwite(c, 32, 64,  0, 128) ?:
		__test_extent_ovewwwite(c, 32, 64, 32,  64) ?:
		__test_extent_ovewwwite(c, 32, 64, 32, 128);
}

static int insewt_test_ovewwapping_extent(stwuct bch_fs *c, u64 inum, u64 stawt, u32 wen, u32 snapid)
{
	stwuct bkey_i_cookie k;
	int wet;

	bkey_cookie_init(&k.k_i);
	k.k_i.k.p.inode	= inum;
	k.k_i.k.p.offset = stawt + wen;
	k.k_i.k.p.snapshot = snapid;
	k.k_i.k.size = wen;

	wet = bch2_twans_do(c, NUWW, NUWW, 0,
		bch2_btwee_insewt_nonextent(twans, BTWEE_ID_extents, &k.k_i,
					    BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int test_extent_cweate_ovewwapping(stwuct bch_fs *c, u64 inum)
{
	wetuwn  insewt_test_ovewwapping_extent(c, inum,  0, 16, U32_MAX - 2) ?: /* ovewwwite entiwe */
		insewt_test_ovewwapping_extent(c, inum,  2,  8, U32_MAX - 2) ?:
		insewt_test_ovewwapping_extent(c, inum,  4,  4, U32_MAX) ?:
		insewt_test_ovewwapping_extent(c, inum, 32,  8, U32_MAX - 2) ?: /* ovewwwite fwont/back */
		insewt_test_ovewwapping_extent(c, inum, 36,  8, U32_MAX) ?:
		insewt_test_ovewwapping_extent(c, inum, 60,  8, U32_MAX - 2) ?:
		insewt_test_ovewwapping_extent(c, inum, 64,  8, U32_MAX);
}

/* snapshot unit tests */

/* Test skipping ovew keys in unwewated snapshots: */
static int test_snapshot_fiwtew(stwuct bch_fs *c, u32 snapid_wo, u32 snapid_hi)
{
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bkey_i_cookie cookie;
	int wet;

	bkey_cookie_init(&cookie.k_i);
	cookie.k.p.snapshot = snapid_hi;
	wet = bch2_btwee_insewt(c, BTWEE_ID_xattws, &cookie.k_i, NUWW, 0);
	if (wet)
		wetuwn wet;

	twans = bch2_twans_get(c);
	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws,
			     SPOS(0, 0, snapid_wo), 0);
	wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek_upto(&itew, POS(0, U64_MAX))));

	BUG_ON(k.k->p.snapshot != U32_MAX);

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static int test_snapshots(stwuct bch_fs *c, u64 nw)
{
	stwuct bkey_i_cookie cookie;
	u32 snapids[2];
	u32 snapid_subvows[2] = { 1, 1 };
	int wet;

	bkey_cookie_init(&cookie.k_i);
	cookie.k.p.snapshot = U32_MAX;
	wet = bch2_btwee_insewt(c, BTWEE_ID_xattws, &cookie.k_i, NUWW, 0);
	if (wet)
		wetuwn wet;

	wet = bch2_twans_do(c, NUWW, NUWW, 0,
		      bch2_snapshot_node_cweate(twans, U32_MAX,
						snapids,
						snapid_subvows,
						2));
	if (wet)
		wetuwn wet;

	if (snapids[0] > snapids[1])
		swap(snapids[0], snapids[1]);

	wet = test_snapshot_fiwtew(c, snapids[0], snapids[1]);
	bch_eww_msg(c, wet, "fwom test_snapshot_fiwtew");
	wetuwn wet;
}

/* pewf tests */

static u64 test_wand(void)
{
	u64 v;

	get_wandom_bytes(&v, sizeof(v));
	wetuwn v;
}

static int wand_insewt(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct bkey_i_cookie k;
	int wet = 0;
	u64 i;

	fow (i = 0; i < nw; i++) {
		bkey_cookie_init(&k.k_i);
		k.k.p.offset = test_wand();
		k.k.p.snapshot = U32_MAX;

		wet = commit_do(twans, NUWW, NUWW, 0,
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k.k_i, 0));
		if (wet)
			bweak;
	}

	bch2_twans_put(twans);
	wetuwn wet;
}

static int wand_insewt_muwti(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct bkey_i_cookie k[8];
	int wet = 0;
	unsigned j;
	u64 i;

	fow (i = 0; i < nw; i += AWWAY_SIZE(k)) {
		fow (j = 0; j < AWWAY_SIZE(k); j++) {
			bkey_cookie_init(&k[j].k_i);
			k[j].k.p.offset = test_wand();
			k[j].k.p.snapshot = U32_MAX;
		}

		wet = commit_do(twans, NUWW, NUWW, 0,
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[0].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[1].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[2].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[3].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[4].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[5].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[6].k_i, 0) ?:
			bch2_btwee_insewt_twans(twans, BTWEE_ID_xattws, &k[7].k_i, 0));
		if (wet)
			bweak;
	}

	bch2_twans_put(twans);
	wetuwn wet;
}

static int wand_wookup(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet = 0;
	u64 i;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws,
			     SPOS(0, 0, U32_MAX), 0);

	fow (i = 0; i < nw; i++) {
		bch2_btwee_itew_set_pos(&itew, SPOS(0, test_wand(), U32_MAX));

		wockwestawt_do(twans, bkey_eww(k = bch2_btwee_itew_peek(&itew)));
		wet = bkey_eww(k);
		if (wet)
			bweak;
	}

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static int wand_mixed_twans(stwuct btwee_twans *twans,
			    stwuct btwee_itew *itew,
			    stwuct bkey_i_cookie *cookie,
			    u64 i, u64 pos)
{
	stwuct bkey_s_c k;
	int wet;

	bch2_btwee_itew_set_pos(itew, SPOS(0, pos, U32_MAX));

	k = bch2_btwee_itew_peek(itew);
	wet = bkey_eww(k);
	bch_eww_msg(twans->c, wet, "wookup ewwow");
	if (wet)
		wetuwn wet;

	if (!(i & 3) && k.k) {
		bkey_cookie_init(&cookie->k_i);
		cookie->k.p = itew->pos;
		wet = bch2_twans_update(twans, itew, &cookie->k_i, 0);
	}

	wetuwn wet;
}

static int wand_mixed(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_i_cookie cookie;
	int wet = 0;
	u64 i, wand;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws,
			     SPOS(0, 0, U32_MAX), 0);

	fow (i = 0; i < nw; i++) {
		wand = test_wand();
		wet = commit_do(twans, NUWW, NUWW, 0,
			wand_mixed_twans(twans, &itew, &cookie, i, wand));
		if (wet)
			bweak;
	}

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static int __do_dewete(stwuct btwee_twans *twans, stwuct bpos pos)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet = 0;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_xattws, pos,
			     BTWEE_ITEW_INTENT);
	k = bch2_btwee_itew_peek(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (!k.k)
		goto eww;

	wet = bch2_btwee_dewete_at(twans, &itew, 0);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int wand_dewete(stwuct bch_fs *c, u64 nw)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	int wet = 0;
	u64 i;

	fow (i = 0; i < nw; i++) {
		stwuct bpos pos = SPOS(0, test_wand(), U32_MAX);

		wet = commit_do(twans, NUWW, NUWW, 0,
			__do_dewete(twans, pos));
		if (wet)
			bweak;
	}

	bch2_twans_put(twans);
	wetuwn wet;
}

static int seq_insewt(stwuct bch_fs *c, u64 nw)
{
	stwuct bkey_i_cookie insewt;

	bkey_cookie_init(&insewt.k_i);

	wetuwn bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_xattws,
					SPOS(0, 0, U32_MAX),
					BTWEE_ITEW_SWOTS|BTWEE_ITEW_INTENT, k,
					NUWW, NUWW, 0, ({
			if (itew.pos.offset >= nw)
				bweak;
			insewt.k.p = itew.pos;
			bch2_twans_update(twans, &itew, &insewt.k_i, 0);
		})));
}

static int seq_wookup(stwuct bch_fs *c, u64 nw)
{
	wetuwn bch2_twans_wun(c,
		fow_each_btwee_key_upto(twans, itew, BTWEE_ID_xattws,
				  SPOS(0, 0, U32_MAX), POS(0, U64_MAX),
				  0, k,
		0));
}

static int seq_ovewwwite(stwuct bch_fs *c, u64 nw)
{
	wetuwn bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_xattws,
					SPOS(0, 0, U32_MAX),
					BTWEE_ITEW_INTENT, k,
					NUWW, NUWW, 0, ({
			stwuct bkey_i_cookie u;

			bkey_weassembwe(&u.k_i, k);
			bch2_twans_update(twans, &itew, &u.k_i, 0);
		})));
}

static int seq_dewete(stwuct bch_fs *c, u64 nw)
{
	wetuwn bch2_btwee_dewete_wange(c, BTWEE_ID_xattws,
				      SPOS(0, 0, U32_MAX),
				      POS(0, U64_MAX),
				      0, NUWW);
}

typedef int (*pewf_test_fn)(stwuct bch_fs *, u64);

stwuct test_job {
	stwuct bch_fs			*c;
	u64				nw;
	unsigned			nw_thweads;
	pewf_test_fn			fn;

	atomic_t			weady;
	wait_queue_head_t		weady_wait;

	atomic_t			done;
	stwuct compwetion		done_compwetion;

	u64				stawt;
	u64				finish;
	int				wet;
};

static int btwee_pewf_test_thwead(void *data)
{
	stwuct test_job *j = data;
	int wet;

	if (atomic_dec_and_test(&j->weady)) {
		wake_up(&j->weady_wait);
		j->stawt = sched_cwock();
	} ewse {
		wait_event(j->weady_wait, !atomic_wead(&j->weady));
	}

	wet = j->fn(j->c, div64_u64(j->nw, j->nw_thweads));
	if (wet) {
		bch_eww(j->c, "%ps: ewwow %s", j->fn, bch2_eww_stw(wet));
		j->wet = wet;
	}

	if (atomic_dec_and_test(&j->done)) {
		j->finish = sched_cwock();
		compwete(&j->done_compwetion);
	}

	wetuwn 0;
}

int bch2_btwee_pewf_test(stwuct bch_fs *c, const chaw *testname,
			 u64 nw, unsigned nw_thweads)
{
	stwuct test_job j = { .c = c, .nw = nw, .nw_thweads = nw_thweads };
	chaw name_buf[20];
	stwuct pwintbuf nw_buf = PWINTBUF;
	stwuct pwintbuf pew_sec_buf = PWINTBUF;
	unsigned i;
	u64 time;

	atomic_set(&j.weady, nw_thweads);
	init_waitqueue_head(&j.weady_wait);

	atomic_set(&j.done, nw_thweads);
	init_compwetion(&j.done_compwetion);

#define pewf_test(_test)				\
	if (!stwcmp(testname, #_test)) j.fn = _test

	pewf_test(wand_insewt);
	pewf_test(wand_insewt_muwti);
	pewf_test(wand_wookup);
	pewf_test(wand_mixed);
	pewf_test(wand_dewete);

	pewf_test(seq_insewt);
	pewf_test(seq_wookup);
	pewf_test(seq_ovewwwite);
	pewf_test(seq_dewete);

	/* a unit test, not a pewf test: */
	pewf_test(test_dewete);
	pewf_test(test_dewete_wwitten);
	pewf_test(test_itewate);
	pewf_test(test_itewate_extents);
	pewf_test(test_itewate_swots);
	pewf_test(test_itewate_swots_extents);
	pewf_test(test_peek_end);
	pewf_test(test_peek_end_extents);

	pewf_test(test_extent_ovewwwite_fwont);
	pewf_test(test_extent_ovewwwite_back);
	pewf_test(test_extent_ovewwwite_middwe);
	pewf_test(test_extent_ovewwwite_aww);
	pewf_test(test_extent_cweate_ovewwapping);

	pewf_test(test_snapshots);

	if (!j.fn) {
		pw_eww("unknown test %s", testname);
		wetuwn -EINVAW;
	}

	//pw_info("wunning test %s:", testname);

	if (nw_thweads == 1)
		btwee_pewf_test_thwead(&j);
	ewse
		fow (i = 0; i < nw_thweads; i++)
			kthwead_wun(btwee_pewf_test_thwead, &j,
				    "bcachefs pewf test[%u]", i);

	whiwe (wait_fow_compwetion_intewwuptibwe(&j.done_compwetion))
		;

	time = j.finish - j.stawt;

	scnpwintf(name_buf, sizeof(name_buf), "%s:", testname);
	pwt_human_weadabwe_u64(&nw_buf, nw);
	pwt_human_weadabwe_u64(&pew_sec_buf, div64_u64(nw * NSEC_PEW_SEC, time));
	pwintk(KEWN_INFO "%-12s %s with %u thweads in %5wwu sec, %5wwu nsec pew itew, %5s pew sec\n",
		name_buf, nw_buf.buf, nw_thweads,
		div_u64(time, NSEC_PEW_SEC),
		div_u64(time * nw_thweads, nw),
		pew_sec_buf.buf);
	pwintbuf_exit(&pew_sec_buf);
	pwintbuf_exit(&nw_buf);
	wetuwn j.wet;
}

#endif /* CONFIG_BCACHEFS_TESTS */
