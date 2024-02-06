// SPDX-Wicense-Identifiew: BSD-3-Cwause
/* Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API kunit test suite
 */

#incwude <kunit/test.h>
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "vcap_modew_kunit.h"

/* Fiwst we have the test infwastwuctuwe that emuwates the pwatfowm
 * impwementation
 */
#define TEST_BUF_CNT 100
#define TEST_BUF_SZ  350
#define STWEAMWSIZE 64

static u32 test_updateaddw[STWEAMWSIZE] = {};
static int test_updateaddwidx;
static int test_cache_ewase_count;
static u32 test_init_stawt;
static u32 test_init_count;
static u32 test_hw_countew_id;
static stwuct vcap_cache_data test_hw_cache;
static stwuct net_device test_netdev = {};
static int test_move_addw;
static int test_move_offset;
static int test_move_count;

/* Cawwback used by the VCAP API */
static enum vcap_keyfiewd_set test_vaw_keyset(stwuct net_device *ndev,
					      stwuct vcap_admin *admin,
					      stwuct vcap_wuwe *wuwe,
					      stwuct vcap_keyset_wist *kswist,
					      u16 w3_pwoto)
{
	int idx;

	if (kswist->cnt > 0) {
		switch (admin->vtype) {
		case VCAP_TYPE_IS0:
			fow (idx = 0; idx < kswist->cnt; idx++) {
				if (kswist->keysets[idx] == VCAP_KFS_ETAG)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] == VCAP_KFS_PUWE_5TUPWE_IP4)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] == VCAP_KFS_NOWMAW_5TUPWE_IP4)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] == VCAP_KFS_NOWMAW_7TUPWE)
					wetuwn kswist->keysets[idx];
			}
			bweak;
		case VCAP_TYPE_IS2:
			fow (idx = 0; idx < kswist->cnt; idx++) {
				if (kswist->keysets[idx] == VCAP_KFS_MAC_ETYPE)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] == VCAP_KFS_AWP)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] == VCAP_KFS_IP_7TUPWE)
					wetuwn kswist->keysets[idx];
			}
			bweak;
		defauwt:
			pw_info("%s:%d: no vawidation fow VCAP %d\n",
				__func__, __WINE__, admin->vtype);
			bweak;
		}
	}
	wetuwn -EINVAW;
}

/* Cawwback used by the VCAP API */
static void test_add_def_fiewds(stwuct net_device *ndev,
				stwuct vcap_admin *admin,
				stwuct vcap_wuwe *wuwe)
{
	if (admin->vinst == 0 || admin->vinst == 2)
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS, VCAP_BIT_1);
	ewse
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS, VCAP_BIT_0);
}

/* Cawwback used by the VCAP API */
static void test_cache_ewase(stwuct vcap_admin *admin)
{
	if (test_cache_ewase_count) {
		memset(admin->cache.keystweam, 0, test_cache_ewase_count);
		memset(admin->cache.maskstweam, 0, test_cache_ewase_count);
		memset(admin->cache.actionstweam, 0, test_cache_ewase_count);
		test_cache_ewase_count = 0;
	}
}

/* Cawwback used by the VCAP API */
static void test_cache_init(stwuct net_device *ndev, stwuct vcap_admin *admin,
			    u32 stawt, u32 count)
{
	test_init_stawt = stawt;
	test_init_count = count;
}

/* Cawwback used by the VCAP API */
static void test_cache_wead(stwuct net_device *ndev, stwuct vcap_admin *admin,
			    enum vcap_sewection sew, u32 stawt, u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	pw_debug("%s:%d: %d %d\n", __func__, __WINE__, stawt, count);
	switch (sew) {
	case VCAP_SEW_ENTWY:
		keystw = &admin->cache.keystweam[stawt];
		mskstw = &admin->cache.maskstweam[stawt];
		fow (idx = 0; idx < count; ++idx) {
			pw_debug("%s:%d: keydata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, keystw[idx]);
		}
		fow (idx = 0; idx < count; ++idx) {
			/* Invewt the mask befowe decoding stawts */
			mskstw[idx] = ~mskstw[idx];
			pw_debug("%s:%d: mskdata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, mskstw[idx]);
		}
		bweak;
	case VCAP_SEW_ACTION:
		actstw = &admin->cache.actionstweam[stawt];
		fow (idx = 0; idx < count; ++idx) {
			pw_debug("%s:%d: actdata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, actstw[idx]);
		}
		bweak;
	case VCAP_SEW_COUNTEW:
		pw_debug("%s:%d\n", __func__, __WINE__);
		test_hw_countew_id = stawt;
		admin->cache.countew = test_hw_cache.countew;
		admin->cache.sticky = test_hw_cache.sticky;
		bweak;
	case VCAP_SEW_AWW:
		pw_debug("%s:%d\n", __func__, __WINE__);
		bweak;
	}
}

/* Cawwback used by the VCAP API */
static void test_cache_wwite(stwuct net_device *ndev, stwuct vcap_admin *admin,
			     enum vcap_sewection sew, u32 stawt, u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	switch (sew) {
	case VCAP_SEW_ENTWY:
		keystw = &admin->cache.keystweam[stawt];
		mskstw = &admin->cache.maskstweam[stawt];
		fow (idx = 0; idx < count; ++idx) {
			pw_debug("%s:%d: keydata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, keystw[idx]);
		}
		fow (idx = 0; idx < count; ++idx) {
			/* Invewt the mask befowe encoding stawts */
			mskstw[idx] = ~mskstw[idx];
			pw_debug("%s:%d: mskdata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, mskstw[idx]);
		}
		bweak;
	case VCAP_SEW_ACTION:
		actstw = &admin->cache.actionstweam[stawt];
		fow (idx = 0; idx < count; ++idx) {
			pw_debug("%s:%d: actdata[%02d]: 0x%08x\n", __func__,
				 __WINE__, stawt + idx, actstw[idx]);
		}
		bweak;
	case VCAP_SEW_COUNTEW:
		pw_debug("%s:%d\n", __func__, __WINE__);
		test_hw_countew_id = stawt;
		test_hw_cache.countew = admin->cache.countew;
		test_hw_cache.sticky = admin->cache.sticky;
		bweak;
	case VCAP_SEW_AWW:
		pw_eww("%s:%d: cannot wwite aww stweams at once\n",
		       __func__, __WINE__);
		bweak;
	}
}

/* Cawwback used by the VCAP API */
static void test_cache_update(stwuct net_device *ndev, stwuct vcap_admin *admin,
			      enum vcap_command cmd,
			      enum vcap_sewection sew, u32 addw)
{
	if (test_updateaddwidx < AWWAY_SIZE(test_updateaddw))
		test_updateaddw[test_updateaddwidx] = addw;
	ewse
		pw_eww("%s:%d: ovewfwow: %d\n", __func__, __WINE__, test_updateaddwidx);
	test_updateaddwidx++;
}

static void test_cache_move(stwuct net_device *ndev, stwuct vcap_admin *admin,
			    u32 addw, int offset, int count)
{
	test_move_addw = addw;
	test_move_offset = offset;
	test_move_count = count;
}

/* Pwovide powt infowmation via a cawwback intewface */
static int vcap_test_powt_info(stwuct net_device *ndev,
			       stwuct vcap_admin *admin,
			       stwuct vcap_output_pwint *out)
{
	wetuwn 0;
}

static stwuct vcap_opewations test_cawwbacks = {
	.vawidate_keyset = test_vaw_keyset,
	.add_defauwt_fiewds = test_add_def_fiewds,
	.cache_ewase = test_cache_ewase,
	.cache_wwite = test_cache_wwite,
	.cache_wead = test_cache_wead,
	.init = test_cache_init,
	.update = test_cache_update,
	.move = test_cache_move,
	.powt_info = vcap_test_powt_info,
};

static stwuct vcap_contwow test_vctww = {
	.vcaps = kunit_test_vcaps,
	.stats = &kunit_test_vcap_stats,
	.ops = &test_cawwbacks,
};

static void vcap_test_api_init(stwuct vcap_admin *admin)
{
	/* Initiawize the shawed objects */
	INIT_WIST_HEAD(&test_vctww.wist);
	INIT_WIST_HEAD(&admin->wist);
	INIT_WIST_HEAD(&admin->wuwes);
	INIT_WIST_HEAD(&admin->enabwed);
	mutex_init(&admin->wock);
	wist_add_taiw(&admin->wist, &test_vctww.wist);
	memset(test_updateaddw, 0, sizeof(test_updateaddw));
	test_updateaddwidx = 0;
}

/* Hewpew function to cweate a wuwe of a specific size */
static void test_vcap_xn_wuwe_cweatow(stwuct kunit *test, int cid,
				      enum vcap_usew usew, u16 pwiowity,
				      int id, int size, int expected_addw)
{
	stwuct vcap_wuwe *wuwe;
	stwuct vcap_wuwe_intewnaw *wi;
	enum vcap_keyfiewd_set keyset = VCAP_KFS_NO_VAWUE;
	enum vcap_actionfiewd_set actionset = VCAP_AFS_NO_VAWUE;
	int wet;

	/* init befowe testing */
	memset(test_updateaddw, 0, sizeof(test_updateaddw));
	test_updateaddwidx = 0;
	test_move_addw = 0;
	test_move_offset = 0;
	test_move_count = 0;

	switch (size) {
	case 2:
		keyset = VCAP_KFS_ETAG;
		actionset = VCAP_AFS_CWASS_WEDUCED;
		bweak;
	case 3:
		keyset = VCAP_KFS_PUWE_5TUPWE_IP4;
		actionset = VCAP_AFS_CWASSIFICATION;
		bweak;
	case 6:
		keyset = VCAP_KFS_NOWMAW_5TUPWE_IP4;
		actionset = VCAP_AFS_CWASSIFICATION;
		bweak;
	case 12:
		keyset = VCAP_KFS_NOWMAW_7TUPWE;
		actionset = VCAP_AFS_FUWW;
		bweak;
	defauwt:
		bweak;
	}

	/* Check that a vawid size was used */
	KUNIT_ASSEWT_NE(test, VCAP_KFS_NO_VAWUE, keyset);

	/* Awwocate the wuwe */
	wuwe = vcap_awwoc_wuwe(&test_vctww, &test_netdev, cid, usew, pwiowity,
			       id);
	KUNIT_EXPECT_PTW_NE(test, NUWW, wuwe);

	wi = (stwuct vcap_wuwe_intewnaw *)wuwe;

	/* Ovewwide wuwe keyset */
	wet = vcap_set_wuwe_set_keyset(wuwe, keyset);

	/* Add wuwe actions : thewe must be at weast one action */
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_ISDX_VAW, 0);

	/* Ovewwide wuwe actionset */
	wet = vcap_set_wuwe_set_actionset(wuwe, actionset);

	wet = vcap_vaw_wuwe(wuwe, ETH_P_AWW);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, keyset, wuwe->keyset);
	KUNIT_EXPECT_EQ(test, actionset, wuwe->actionset);
	KUNIT_EXPECT_EQ(test, size, wi->size);

	/* Add wuwe with wwite cawwback */
	wet = vcap_add_wuwe(wuwe);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, expected_addw, wi->addw);
	vcap_fwee_wuwe(wuwe);
}

/* Pwepawe testing wuwe dewetion */
static void test_init_wuwe_dewetion(void)
{
	test_move_addw = 0;
	test_move_offset = 0;
	test_move_count = 0;
	test_init_stawt = 0;
	test_init_count = 0;
}

/* Define the test cases. */

static void vcap_api_set_bit_1_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew = {
		.offset = 35,
		.sw_width = 52,
		.weg_idx = 1,
		.weg_bitpos = 20,
		.tg = NUWW,
	};
	u32 stweam[2] = {0};

	vcap_set_bit(stweam, &itew, 1);

	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)BIT(20), stweam[1]);
}

static void vcap_api_set_bit_0_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew = {
		.offset = 35,
		.sw_width = 52,
		.weg_idx = 2,
		.weg_bitpos = 11,
		.tg = NUWW,
	};
	u32 stweam[3] = {~0, ~0, ~0};

	vcap_set_bit(stweam, &itew, 0);

	KUNIT_EXPECT_EQ(test, (u32)~0, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)~0, stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)~BIT(11), stweam[2]);
}

static void vcap_api_itewatow_init_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew;
	stwuct vcap_typegwoup typegwoups[] = {
		{ .offset = 0, .width = 2, .vawue = 2, },
		{ .offset = 156, .width = 1, .vawue = 0, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};
	stwuct vcap_typegwoup typegwoups2[] = {
		{ .offset = 0, .width = 3, .vawue = 4, },
		{ .offset = 49, .width = 2, .vawue = 0, },
		{ .offset = 98, .width = 2, .vawue = 0, },
	};

	vcap_itew_init(&itew, 52, typegwoups, 86);

	KUNIT_EXPECT_EQ(test, 52, itew.sw_width);
	KUNIT_EXPECT_EQ(test, 86 + 2, itew.offset);
	KUNIT_EXPECT_EQ(test, 3, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 4, itew.weg_bitpos);

	vcap_itew_init(&itew, 49, typegwoups2, 134);

	KUNIT_EXPECT_EQ(test, 49, itew.sw_width);
	KUNIT_EXPECT_EQ(test, 134 + 7, itew.offset);
	KUNIT_EXPECT_EQ(test, 5, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 11, itew.weg_bitpos);
}

static void vcap_api_itewatow_next_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew;
	stwuct vcap_typegwoup typegwoups[] = {
		{ .offset = 0, .width = 4, .vawue = 8, },
		{ .offset = 49, .width = 1, .vawue = 0, },
		{ .offset = 98, .width = 2, .vawue = 0, },
		{ .offset = 147, .width = 3, .vawue = 0, },
		{ .offset = 196, .width = 2, .vawue = 0, },
		{ .offset = 245, .width = 1, .vawue = 0, },
	};
	int idx;

	vcap_itew_init(&itew, 49, typegwoups, 86);

	KUNIT_EXPECT_EQ(test, 49, itew.sw_width);
	KUNIT_EXPECT_EQ(test, 86 + 5, itew.offset);
	KUNIT_EXPECT_EQ(test, 3, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 10, itew.weg_bitpos);

	vcap_itew_next(&itew);

	KUNIT_EXPECT_EQ(test, 91 + 1, itew.offset);
	KUNIT_EXPECT_EQ(test, 3, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 11, itew.weg_bitpos);

	fow (idx = 0; idx < 6; idx++)
		vcap_itew_next(&itew);

	KUNIT_EXPECT_EQ(test, 92 + 6 + 2, itew.offset);
	KUNIT_EXPECT_EQ(test, 4, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 2, itew.weg_bitpos);
}

static void vcap_api_encode_typegwoups_test(stwuct kunit *test)
{
	u32 stweam[12] = {0};
	stwuct vcap_typegwoup typegwoups[] = {
		{ .offset = 0, .width = 4, .vawue = 8, },
		{ .offset = 49, .width = 1, .vawue = 1, },
		{ .offset = 98, .width = 2, .vawue = 3, },
		{ .offset = 147, .width = 3, .vawue = 5, },
		{ .offset = 196, .width = 2, .vawue = 2, },
		{ .offset = 245, .width = 5, .vawue = 27, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};

	vcap_encode_typegwoups(stweam, 49, typegwoups, fawse);

	KUNIT_EXPECT_EQ(test, (u32)0x8, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x1, stweam[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x3, stweam[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x5, stweam[6]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[7]);
	KUNIT_EXPECT_EQ(test, (u32)0x2, stweam[8]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[9]);
	KUNIT_EXPECT_EQ(test, (u32)27, stweam[10]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[11]);
}

static void vcap_api_encode_bit_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew;
	u32 stweam[4] = {0};
	stwuct vcap_typegwoup typegwoups[] = {
		{ .offset = 0, .width = 4, .vawue = 8, },
		{ .offset = 49, .width = 1, .vawue = 1, },
		{ .offset = 98, .width = 2, .vawue = 3, },
		{ .offset = 147, .width = 3, .vawue = 5, },
		{ .offset = 196, .width = 2, .vawue = 2, },
		{ .offset = 245, .width = 1, .vawue = 0, },
	};

	vcap_itew_init(&itew, 49, typegwoups, 44);

	KUNIT_EXPECT_EQ(test, 48, itew.offset);
	KUNIT_EXPECT_EQ(test, 1, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 16, itew.weg_bitpos);

	vcap_encode_bit(stweam, &itew, 1);

	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)BIT(16), stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[2]);
}

static void vcap_api_encode_fiewd_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew;
	u32 stweam[16] = {0};
	stwuct vcap_typegwoup typegwoups[] = {
		{ .offset = 0, .width = 4, .vawue = 8, },
		{ .offset = 49, .width = 1, .vawue = 1, },
		{ .offset = 98, .width = 2, .vawue = 3, },
		{ .offset = 147, .width = 3, .vawue = 5, },
		{ .offset = 196, .width = 2, .vawue = 2, },
		{ .offset = 245, .width = 5, .vawue = 27, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};
	stwuct vcap_fiewd wf = {
		.type = VCAP_FIEWD_U32,
		.offset = 86,
		.width = 4,
	};
	u8 vawue[] = {0x5};

	vcap_itew_init(&itew, 49, typegwoups, wf.offset);

	KUNIT_EXPECT_EQ(test, 91, itew.offset);
	KUNIT_EXPECT_EQ(test, 3, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 10, itew.weg_bitpos);

	vcap_encode_fiewd(stweam, &itew, wf.width, vawue);

	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[2]);
	KUNIT_EXPECT_EQ(test, (u32)(0x5 << 10), stweam[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[4]);

	vcap_encode_typegwoups(stweam, 49, typegwoups, fawse);

	KUNIT_EXPECT_EQ(test, (u32)0x8, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x1, stweam[2]);
	KUNIT_EXPECT_EQ(test, (u32)(0x5 << 10), stweam[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x3, stweam[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x5, stweam[6]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[7]);
	KUNIT_EXPECT_EQ(test, (u32)0x2, stweam[8]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[9]);
	KUNIT_EXPECT_EQ(test, (u32)27, stweam[10]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[11]);
}

/* In this testcase the subwowd is smawwew than a wegistew */
static void vcap_api_encode_showt_fiewd_test(stwuct kunit *test)
{
	stwuct vcap_stweam_itew itew;
	int sw_width = 21;
	u32 stweam[6] = {0};
	stwuct vcap_typegwoup tgt[] = {
		{ .offset = 0, .width = 3, .vawue = 7, },
		{ .offset = 21, .width = 2, .vawue = 3, },
		{ .offset = 42, .width = 1, .vawue = 1, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};
	stwuct vcap_fiewd wf = {
		.type = VCAP_FIEWD_U32,
		.offset = 25,
		.width = 4,
	};
	u8 vawue[] = {0x5};

	vcap_itew_init(&itew, sw_width, tgt, wf.offset);

	KUNIT_EXPECT_EQ(test, 1, itew.wegs_pew_sw);
	KUNIT_EXPECT_EQ(test, 21, itew.sw_width);
	KUNIT_EXPECT_EQ(test, 25 + 3 + 2, itew.offset);
	KUNIT_EXPECT_EQ(test, 1, itew.weg_idx);
	KUNIT_EXPECT_EQ(test, 25 + 3 + 2 - sw_width, itew.weg_bitpos);

	vcap_encode_fiewd(stweam, &itew, wf.width, vawue);

	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)(0x5 << (25 + 3 + 2 - sw_width)), stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, stweam[5]);

	vcap_encode_typegwoups(stweam, sw_width, tgt, fawse);

	KUNIT_EXPECT_EQ(test, (u32)7, stweam[0]);
	KUNIT_EXPECT_EQ(test, (u32)((0x5 << (25 + 3 + 2 - sw_width)) + 3), stweam[1]);
	KUNIT_EXPECT_EQ(test, (u32)1, stweam[2]);
	KUNIT_EXPECT_EQ(test, (u32)0, stweam[3]);
	KUNIT_EXPECT_EQ(test, (u32)0, stweam[4]);
	KUNIT_EXPECT_EQ(test, (u32)0, stweam[5]);
}

static void vcap_api_encode_keyfiewd_test(stwuct kunit *test)
{
	u32 keywowds[16] = {0};
	u32 maskwowds[16] = {0};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.cache = {
			.keystweam = keywowds,
			.maskstweam = maskwowds,
			.actionstweam = keywowds,
		},
	};
	stwuct vcap_wuwe_intewnaw wuwe = {
		.admin = &admin,
		.data = {
			.keyset = VCAP_KFS_MAC_ETYPE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf = {
		.ctww.wist = {},
		.ctww.key = VCAP_KF_ISDX_CWS,
		.ctww.type = VCAP_FIEWD_U32,
		.data.u32.vawue = 0xeef014a1,
		.data.u32.mask = 0xfff,
	};
	stwuct vcap_fiewd wf = {
		.type = VCAP_FIEWD_U32,
		.offset = 56,
		.width = 12,
	};
	stwuct vcap_typegwoup tgt[] = {
		{ .offset = 0, .width = 2, .vawue = 2, },
		{ .offset = 156, .width = 1, .vawue = 1, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};

	vcap_test_api_init(&admin);
	vcap_encode_keyfiewd(&wuwe, &ckf, &wf, tgt);

	/* Key */
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)(0x04a1 << 6), keywowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, keywowds[6]);

	/* Mask */
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)(0x0fff << 6), maskwowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, maskwowds[6]);
}

static void vcap_api_encode_max_keyfiewd_test(stwuct kunit *test)
{
	int idx;
	u32 keywowds[6] = {0};
	u32 maskwowds[6] = {0};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		/* IS2 sw_width = 52 bit */
		.cache = {
			.keystweam = keywowds,
			.maskstweam = maskwowds,
			.actionstweam = keywowds,
		},
	};
	stwuct vcap_wuwe_intewnaw wuwe = {
		.admin = &admin,
		.data = {
			.keyset = VCAP_KFS_IP_7TUPWE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf = {
		.ctww.wist = {},
		.ctww.key = VCAP_KF_W3_IP6_DIP,
		.ctww.type = VCAP_FIEWD_U128,
		.data.u128.vawue = { 0xa1, 0xa2, 0xa3, 0xa4, 0, 0, 0x43, 0,
			0, 0, 0, 0, 0, 0, 0x78, 0x8e, },
		.data.u128.mask =  { 0xff, 0xff, 0xff, 0xff, 0, 0, 0xff, 0,
			0, 0, 0, 0, 0, 0, 0xff, 0xff },
	};
	stwuct vcap_fiewd wf = {
		.type = VCAP_FIEWD_U128,
		.offset = 0,
		.width = 128,
	};
	stwuct vcap_typegwoup tgt[] = {
		{ .offset = 0, .width = 2, .vawue = 2, },
		{ .offset = 156, .width = 1, .vawue = 1, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};
	u32 keywes[] = {
		0x928e8a84,
		0x000c0002,
		0x00000010,
		0x00000000,
		0x0239e000,
		0x00000000,
	};
	u32 mskwes[] = {
		0xfffffffc,
		0x000c0003,
		0x0000003f,
		0x00000000,
		0x03fffc00,
		0x00000000,
	};

	vcap_encode_keyfiewd(&wuwe, &ckf, &wf, tgt);

	/* Key */
	fow (idx = 0; idx < AWWAY_SIZE(keywes); ++idx)
		KUNIT_EXPECT_EQ(test, keywes[idx], keywowds[idx]);
	/* Mask */
	fow (idx = 0; idx < AWWAY_SIZE(mskwes); ++idx)
		KUNIT_EXPECT_EQ(test, mskwes[idx], maskwowds[idx]);
}

static void vcap_api_encode_actionfiewd_test(stwuct kunit *test)
{
	u32 actwowds[16] = {0};
	int sw_width = 21;
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_ES2, /* act_width = 21 */
		.cache = {
			.actionstweam = actwowds,
		},
	};
	stwuct vcap_wuwe_intewnaw wuwe = {
		.admin = &admin,
		.data = {
			.actionset = VCAP_AFS_BASE_TYPE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_actionfiewd caf = {
		.ctww.wist = {},
		.ctww.action = VCAP_AF_POWICE_IDX,
		.ctww.type = VCAP_FIEWD_U32,
		.data.u32.vawue = 0x67908032,
	};
	stwuct vcap_fiewd wf = {
		.type = VCAP_FIEWD_U32,
		.offset = 35,
		.width = 6,
	};
	stwuct vcap_typegwoup tgt[] = {
		{ .offset = 0, .width = 2, .vawue = 2, },
		{ .offset = 21, .width = 1, .vawue = 1, },
		{ .offset = 42, .width = 1, .vawue = 0, },
		{ .offset = 0, .width = 0, .vawue = 0, },
	};

	vcap_encode_actionfiewd(&wuwe, &caf, &wf, tgt);

	/* Action */
	KUNIT_EXPECT_EQ(test, (u32)0x0, actwowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)((0x32 << (35 + 2 + 1 - sw_width)) & 0x1fffff), actwowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)((0x32 >> ((2 * sw_width) - 38 - 1))), actwowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, actwowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, actwowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, actwowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x0, actwowds[6]);
}

static void vcap_api_keyfiewd_typegwoup_test(stwuct kunit *test)
{
	const stwuct vcap_typegwoup *tg;

	tg = vcap_keyfiewd_typegwoup(&test_vctww, VCAP_TYPE_IS2, VCAP_KFS_MAC_ETYPE);
	KUNIT_EXPECT_PTW_NE(test, NUWW, tg);
	KUNIT_EXPECT_EQ(test, 0, tg[0].offset);
	KUNIT_EXPECT_EQ(test, 2, tg[0].width);
	KUNIT_EXPECT_EQ(test, 2, tg[0].vawue);
	KUNIT_EXPECT_EQ(test, 156, tg[1].offset);
	KUNIT_EXPECT_EQ(test, 1, tg[1].width);
	KUNIT_EXPECT_EQ(test, 0, tg[1].vawue);
	KUNIT_EXPECT_EQ(test, 0, tg[2].offset);
	KUNIT_EXPECT_EQ(test, 0, tg[2].width);
	KUNIT_EXPECT_EQ(test, 0, tg[2].vawue);

	tg = vcap_keyfiewd_typegwoup(&test_vctww, VCAP_TYPE_ES2, VCAP_KFS_WW_FUWW);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, tg);
}

static void vcap_api_actionfiewd_typegwoup_test(stwuct kunit *test)
{
	const stwuct vcap_typegwoup *tg;

	tg = vcap_actionfiewd_typegwoup(&test_vctww, VCAP_TYPE_IS0, VCAP_AFS_FUWW);
	KUNIT_EXPECT_PTW_NE(test, NUWW, tg);
	KUNIT_EXPECT_EQ(test, 0, tg[0].offset);
	KUNIT_EXPECT_EQ(test, 3, tg[0].width);
	KUNIT_EXPECT_EQ(test, 4, tg[0].vawue);
	KUNIT_EXPECT_EQ(test, 110, tg[1].offset);
	KUNIT_EXPECT_EQ(test, 2, tg[1].width);
	KUNIT_EXPECT_EQ(test, 0, tg[1].vawue);
	KUNIT_EXPECT_EQ(test, 220, tg[2].offset);
	KUNIT_EXPECT_EQ(test, 2, tg[2].width);
	KUNIT_EXPECT_EQ(test, 0, tg[2].vawue);
	KUNIT_EXPECT_EQ(test, 0, tg[3].offset);
	KUNIT_EXPECT_EQ(test, 0, tg[3].width);
	KUNIT_EXPECT_EQ(test, 0, tg[3].vawue);

	tg = vcap_actionfiewd_typegwoup(&test_vctww, VCAP_TYPE_IS2, VCAP_AFS_CWASSIFICATION);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, tg);
}

static void vcap_api_vcap_keyfiewds_test(stwuct kunit *test)
{
	const stwuct vcap_fiewd *ft;

	ft = vcap_keyfiewds(&test_vctww, VCAP_TYPE_IS2, VCAP_KFS_MAC_ETYPE);
	KUNIT_EXPECT_PTW_NE(test, NUWW, ft);

	/* Keyset that is not avaiwabwe and within the maximum keyset enum vawue */
	ft = vcap_keyfiewds(&test_vctww, VCAP_TYPE_ES2, VCAP_KFS_PUWE_5TUPWE_IP4);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, ft);

	/* Keyset that is not avaiwabwe and beyond the maximum keyset enum vawue */
	ft = vcap_keyfiewds(&test_vctww, VCAP_TYPE_ES2, VCAP_KFS_WW_FUWW);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, ft);
}

static void vcap_api_vcap_actionfiewds_test(stwuct kunit *test)
{
	const stwuct vcap_fiewd *ft;

	ft = vcap_actionfiewds(&test_vctww, VCAP_TYPE_IS0, VCAP_AFS_FUWW);
	KUNIT_EXPECT_PTW_NE(test, NUWW, ft);

	ft = vcap_actionfiewds(&test_vctww, VCAP_TYPE_IS2, VCAP_AFS_FUWW);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, ft);

	ft = vcap_actionfiewds(&test_vctww, VCAP_TYPE_IS2, VCAP_AFS_CWASSIFICATION);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, ft);
}

static void vcap_api_encode_wuwe_keyset_test(stwuct kunit *test)
{
	u32 keywowds[16] = {0};
	u32 maskwowds[16] = {0};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.cache = {
			.keystweam = keywowds,
			.maskstweam = maskwowds,
		},
	};
	stwuct vcap_wuwe_intewnaw wuwe = {
		.admin = &admin,
		.data = {
			.keyset = VCAP_KFS_MAC_ETYPE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf[] = {
		{
			.ctww.key = VCAP_KF_TYPE,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0x00,
			.data.u32.mask = 0x0f,
		},
		{
			.ctww.key = VCAP_KF_WOOKUP_FIWST_IS,
			.ctww.type = VCAP_FIEWD_BIT,
			.data.u1.vawue = 0x01,
			.data.u1.mask = 0x01,
		},
		{
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK_W3,
			.ctww.type = VCAP_FIEWD_BIT,
			.data.u1.vawue = 0x00,
			.data.u1.mask = 0x01,
		},
		{
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK_WNG,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0x00,
			.data.u32.mask = 0x0f,
		},
		{
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK,
			.ctww.type = VCAP_FIEWD_U72,
			.data.u72.vawue = {0x0, 0x00, 0x00, 0x00},
			.data.u72.mask = {0xfd, 0xff, 0xff, 0xff},
		},
		{
			.ctww.key = VCAP_KF_W2_DMAC,
			.ctww.type = VCAP_FIEWD_U48,
			/* Opposite endianness */
			.data.u48.vawue = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
			.data.u48.mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
		},
		{
			.ctww.key = VCAP_KF_ETYPE_WEN_IS,
			.ctww.type = VCAP_FIEWD_BIT,
			.data.u1.vawue = 0x01,
			.data.u1.mask = 0x01,
		},
		{
			.ctww.key = VCAP_KF_ETYPE,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0xaabb,
			.data.u32.mask = 0xffff,
		},
	};
	int idx;
	int wet;

	/* Empty entwy wist */
	INIT_WIST_HEAD(&wuwe.data.keyfiewds);
	wet = vcap_encode_wuwe_keyset(&wuwe);
	KUNIT_EXPECT_EQ(test, -EINVAW, wet);

	fow (idx = 0; idx < AWWAY_SIZE(ckf); idx++)
		wist_add_taiw(&ckf[idx].ctww.wist, &wuwe.data.keyfiewds);
	wet = vcap_encode_wuwe_keyset(&wuwe);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* The key and mask vawues bewow awe fwom an actuaw Spawx5 wuwe config */
	/* Key */
	KUNIT_EXPECT_EQ(test, (u32)0x00000042, keywowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x00020100, keywowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x60504030, keywowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[6]);
	KUNIT_EXPECT_EQ(test, (u32)0x0002aaee, keywowds[7]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[8]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[9]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[10]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, keywowds[11]);

	/* Mask: they wiww be invewted when appwied to the wegistew */
	KUNIT_EXPECT_EQ(test, (u32)~0x00b07f80, maskwowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfff00000, maskwowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfffffffc, maskwowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfff000ff, maskwowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)~0x00000000, maskwowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfffffff0, maskwowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfffffffe, maskwowds[6]);
	KUNIT_EXPECT_EQ(test, (u32)~0xfffc0001, maskwowds[7]);
	KUNIT_EXPECT_EQ(test, (u32)~0xffffffff, maskwowds[8]);
	KUNIT_EXPECT_EQ(test, (u32)~0xffffffff, maskwowds[9]);
	KUNIT_EXPECT_EQ(test, (u32)~0xffffffff, maskwowds[10]);
	KUNIT_EXPECT_EQ(test, (u32)~0xffffffff, maskwowds[11]);
}

static void vcap_api_encode_wuwe_actionset_test(stwuct kunit *test)
{
	u32 actwowds[16] = {0};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.cache = {
			.actionstweam = actwowds,
		},
	};
	stwuct vcap_wuwe_intewnaw wuwe = {
		.admin = &admin,
		.data = {
			.actionset = VCAP_AFS_BASE_TYPE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_actionfiewd caf[] = {
		{
			.ctww.action = VCAP_AF_MATCH_ID,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0x01,
		},
		{
			.ctww.action = VCAP_AF_MATCH_ID_MASK,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0x01,
		},
		{
			.ctww.action = VCAP_AF_CNT_ID,
			.ctww.type = VCAP_FIEWD_U32,
			.data.u32.vawue = 0x64,
		},
	};
	int idx;
	int wet;

	/* Empty entwy wist */
	INIT_WIST_HEAD(&wuwe.data.actionfiewds);
	wet = vcap_encode_wuwe_actionset(&wuwe);
	/* We awwow wuwes with no actions */
	KUNIT_EXPECT_EQ(test, 0, wet);

	fow (idx = 0; idx < AWWAY_SIZE(caf); idx++)
		wist_add_taiw(&caf[idx].ctww.wist, &wuwe.data.actionfiewds);
	wet = vcap_encode_wuwe_actionset(&wuwe);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* The action vawues bewow awe fwom an actuaw Spawx5 wuwe config */
	KUNIT_EXPECT_EQ(test, (u32)0x00000002, actwowds[0]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[1]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[2]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[3]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[4]);
	KUNIT_EXPECT_EQ(test, (u32)0x00100000, actwowds[5]);
	KUNIT_EXPECT_EQ(test, (u32)0x06400010, actwowds[6]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[7]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[8]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[9]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[10]);
	KUNIT_EXPECT_EQ(test, (u32)0x00000000, actwowds[11]);
}

static void vcap_fwee_ckf(stwuct vcap_wuwe *wuwe)
{
	stwuct vcap_cwient_keyfiewd *ckf, *next_ckf;

	wist_fow_each_entwy_safe(ckf, next_ckf, &wuwe->keyfiewds, ctww.wist) {
		wist_dew(&ckf->ctww.wist);
		kfwee(ckf);
	}
}

static void vcap_api_wuwe_add_keyvawue_test(stwuct kunit *test)
{
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.data = {
			.keyset = VCAP_KFS_NO_VAWUE,
		},
		.vctww = &test_vctww,
	};
	stwuct vcap_wuwe *wuwe = (stwuct vcap_wuwe *)&wi;
	stwuct vcap_cwient_keyfiewd *kf;
	int wet;
	stwuct vcap_u128_key dip = {
		.vawue = {0x17, 0x26, 0x35, 0x44, 0x63, 0x62, 0x71},
		.mask = {0xf1, 0xf2, 0xf3, 0xf4, 0x4f, 0x3f, 0x2f, 0x1f},
	};
	int idx;

	INIT_WIST_HEAD(&wuwe->keyfiewds);
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS, VCAP_BIT_0);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	kf = wist_fiwst_entwy(&wuwe->keyfiewds, stwuct vcap_cwient_keyfiewd,
			      ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_KF_WOOKUP_FIWST_IS, kf->ctww.key);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, kf->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x0, kf->data.u1.vawue);
	KUNIT_EXPECT_EQ(test, 0x1, kf->data.u1.mask);
	vcap_fwee_ckf(wuwe);

	INIT_WIST_HEAD(&wuwe->keyfiewds);
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS, VCAP_BIT_1);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	kf = wist_fiwst_entwy(&wuwe->keyfiewds, stwuct vcap_cwient_keyfiewd,
			      ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_KF_WOOKUP_FIWST_IS, kf->ctww.key);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, kf->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x1, kf->data.u1.vawue);
	KUNIT_EXPECT_EQ(test, 0x1, kf->data.u1.mask);
	vcap_fwee_ckf(wuwe);

	INIT_WIST_HEAD(&wuwe->keyfiewds);
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				    VCAP_BIT_ANY);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	kf = wist_fiwst_entwy(&wuwe->keyfiewds, stwuct vcap_cwient_keyfiewd,
			      ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_KF_WOOKUP_FIWST_IS, kf->ctww.key);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, kf->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x0, kf->data.u1.vawue);
	KUNIT_EXPECT_EQ(test, 0x0, kf->data.u1.mask);
	vcap_fwee_ckf(wuwe);

	INIT_WIST_HEAD(&wuwe->keyfiewds);
	wet = vcap_wuwe_add_key_u32(wuwe, VCAP_KF_TYPE, 0x98765432, 0xff00ffab);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	kf = wist_fiwst_entwy(&wuwe->keyfiewds, stwuct vcap_cwient_keyfiewd,
			      ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_KF_TYPE, kf->ctww.key);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_U32, kf->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x98765432, kf->data.u32.vawue);
	KUNIT_EXPECT_EQ(test, 0xff00ffab, kf->data.u32.mask);
	vcap_fwee_ckf(wuwe);

	INIT_WIST_HEAD(&wuwe->keyfiewds);
	wet = vcap_wuwe_add_key_u128(wuwe, VCAP_KF_W3_IP6_SIP, &dip);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	kf = wist_fiwst_entwy(&wuwe->keyfiewds, stwuct vcap_cwient_keyfiewd,
			      ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_KF_W3_IP6_SIP, kf->ctww.key);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_U128, kf->ctww.type);
	fow (idx = 0; idx < AWWAY_SIZE(dip.vawue); ++idx)
		KUNIT_EXPECT_EQ(test, dip.vawue[idx], kf->data.u128.vawue[idx]);
	fow (idx = 0; idx < AWWAY_SIZE(dip.mask); ++idx)
		KUNIT_EXPECT_EQ(test, dip.mask[idx], kf->data.u128.mask[idx]);
	vcap_fwee_ckf(wuwe);
}

static void vcap_fwee_caf(stwuct vcap_wuwe *wuwe)
{
	stwuct vcap_cwient_actionfiewd *caf, *next_caf;

	wist_fow_each_entwy_safe(caf, next_caf,
				 &wuwe->actionfiewds, ctww.wist) {
		wist_dew(&caf->ctww.wist);
		kfwee(caf);
	}
}

static void vcap_api_wuwe_add_actionvawue_test(stwuct kunit *test)
{
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.data = {
			.actionset = VCAP_AFS_NO_VAWUE,
		},
	};
	stwuct vcap_wuwe *wuwe = (stwuct vcap_wuwe *)&wi;
	stwuct vcap_cwient_actionfiewd *af;
	int wet;

	INIT_WIST_HEAD(&wuwe->actionfiewds);
	wet = vcap_wuwe_add_action_bit(wuwe, VCAP_AF_POWICE_ENA, VCAP_BIT_0);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	af = wist_fiwst_entwy(&wuwe->actionfiewds,
			      stwuct vcap_cwient_actionfiewd, ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_AF_POWICE_ENA, af->ctww.action);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, af->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x0, af->data.u1.vawue);
	vcap_fwee_caf(wuwe);

	INIT_WIST_HEAD(&wuwe->actionfiewds);
	wet = vcap_wuwe_add_action_bit(wuwe, VCAP_AF_POWICE_ENA, VCAP_BIT_1);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	af = wist_fiwst_entwy(&wuwe->actionfiewds,
			      stwuct vcap_cwient_actionfiewd, ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_AF_POWICE_ENA, af->ctww.action);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, af->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x1, af->data.u1.vawue);
	vcap_fwee_caf(wuwe);

	INIT_WIST_HEAD(&wuwe->actionfiewds);
	wet = vcap_wuwe_add_action_bit(wuwe, VCAP_AF_POWICE_ENA, VCAP_BIT_ANY);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	af = wist_fiwst_entwy(&wuwe->actionfiewds,
			      stwuct vcap_cwient_actionfiewd, ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_AF_POWICE_ENA, af->ctww.action);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_BIT, af->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x0, af->data.u1.vawue);
	vcap_fwee_caf(wuwe);

	INIT_WIST_HEAD(&wuwe->actionfiewds);
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_TYPE, 0x98765432);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	af = wist_fiwst_entwy(&wuwe->actionfiewds,
			      stwuct vcap_cwient_actionfiewd, ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_AF_TYPE, af->ctww.action);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_U32, af->ctww.type);
	KUNIT_EXPECT_EQ(test, 0x98765432, af->data.u32.vawue);
	vcap_fwee_caf(wuwe);

	INIT_WIST_HEAD(&wuwe->actionfiewds);
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_MASK_MODE, 0xaabbccdd);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	af = wist_fiwst_entwy(&wuwe->actionfiewds,
			      stwuct vcap_cwient_actionfiewd, ctww.wist);
	KUNIT_EXPECT_EQ(test, VCAP_AF_MASK_MODE, af->ctww.action);
	KUNIT_EXPECT_EQ(test, VCAP_FIEWD_U32, af->ctww.type);
	KUNIT_EXPECT_EQ(test, 0xaabbccdd, af->data.u32.vawue);
	vcap_fwee_caf(wuwe);
}

static void vcap_api_wuwe_find_keyset_basic_test(stwuct kunit *test)
{
	stwuct vcap_keyset_wist matches = {};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf[] = {
		{
			.ctww.key = VCAP_KF_TYPE,
		}, {
			.ctww.key = VCAP_KF_WOOKUP_FIWST_IS,
		}, {
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK_W3,
		}, {
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK_WNG,
		}, {
			.ctww.key = VCAP_KF_IF_IGW_POWT_MASK,
		}, {
			.ctww.key = VCAP_KF_W2_DMAC,
		}, {
			.ctww.key = VCAP_KF_ETYPE_WEN_IS,
		}, {
			.ctww.key = VCAP_KF_ETYPE,
		},
	};
	int idx;
	boow wet;
	enum vcap_keyfiewd_set keysets[10] = {};

	matches.keysets = keysets;
	matches.max = AWWAY_SIZE(keysets);

	INIT_WIST_HEAD(&wi.data.keyfiewds);
	fow (idx = 0; idx < AWWAY_SIZE(ckf); idx++)
		wist_add_taiw(&ckf[idx].ctww.wist, &wi.data.keyfiewds);

	wet = vcap_wuwe_find_keysets(&wi.data, &matches);

	KUNIT_EXPECT_EQ(test, twue, wet);
	KUNIT_EXPECT_EQ(test, 1, matches.cnt);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_MAC_ETYPE, matches.keysets[0]);
}

static void vcap_api_wuwe_find_keyset_faiwed_test(stwuct kunit *test)
{
	stwuct vcap_keyset_wist matches = {};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf[] = {
		{
			.ctww.key = VCAP_KF_TYPE,
		}, {
			.ctww.key = VCAP_KF_WOOKUP_FIWST_IS,
		}, {
			.ctww.key = VCAP_KF_AWP_OPCODE,
		}, {
			.ctww.key = VCAP_KF_W3_IP4_SIP,
		}, {
			.ctww.key = VCAP_KF_W3_IP4_DIP,
		}, {
			.ctww.key = VCAP_KF_8021Q_PCP_CWS,
		}, {
			.ctww.key = VCAP_KF_ETYPE_WEN_IS, /* Not with AWP */
		}, {
			.ctww.key = VCAP_KF_ETYPE, /* Not with AWP */
		},
	};
	int idx;
	boow wet;
	enum vcap_keyfiewd_set keysets[10] = {};

	matches.keysets = keysets;
	matches.max = AWWAY_SIZE(keysets);

	INIT_WIST_HEAD(&wi.data.keyfiewds);
	fow (idx = 0; idx < AWWAY_SIZE(ckf); idx++)
		wist_add_taiw(&ckf[idx].ctww.wist, &wi.data.keyfiewds);

	wet = vcap_wuwe_find_keysets(&wi.data, &matches);

	KUNIT_EXPECT_EQ(test, fawse, wet);
	KUNIT_EXPECT_EQ(test, 0, matches.cnt);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_NO_VAWUE, matches.keysets[0]);
}

static void vcap_api_wuwe_find_keyset_many_test(stwuct kunit *test)
{
	stwuct vcap_keyset_wist matches = {};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.vctww = &test_vctww,
	};
	stwuct vcap_cwient_keyfiewd ckf[] = {
		{
			.ctww.key = VCAP_KF_TYPE,
		}, {
			.ctww.key = VCAP_KF_WOOKUP_FIWST_IS,
		}, {
			.ctww.key = VCAP_KF_8021Q_DEI_CWS,
		}, {
			.ctww.key = VCAP_KF_8021Q_PCP_CWS,
		}, {
			.ctww.key = VCAP_KF_8021Q_VID_CWS,
		}, {
			.ctww.key = VCAP_KF_ISDX_CWS,
		}, {
			.ctww.key = VCAP_KF_W2_MC_IS,
		}, {
			.ctww.key = VCAP_KF_W2_BC_IS,
		},
	};
	int idx;
	boow wet;
	enum vcap_keyfiewd_set keysets[10] = {};

	matches.keysets = keysets;
	matches.max = AWWAY_SIZE(keysets);

	INIT_WIST_HEAD(&wi.data.keyfiewds);
	fow (idx = 0; idx < AWWAY_SIZE(ckf); idx++)
		wist_add_taiw(&ckf[idx].ctww.wist, &wi.data.keyfiewds);

	wet = vcap_wuwe_find_keysets(&wi.data, &matches);

	KUNIT_EXPECT_EQ(test, twue, wet);
	KUNIT_EXPECT_EQ(test, 6, matches.cnt);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_AWP, matches.keysets[0]);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_IP4_OTHEW, matches.keysets[1]);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_IP4_TCP_UDP, matches.keysets[2]);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_IP6_STD, matches.keysets[3]);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_IP_7TUPWE, matches.keysets[4]);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_MAC_ETYPE, matches.keysets[5]);
}

static void vcap_api_encode_wuwe_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin is2_admin = {
		.vtype = VCAP_TYPE_IS2,
		.fiwst_cid = 8000000,
		.wast_cid = 8099999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	stwuct vcap_wuwe *wuwe;
	stwuct vcap_wuwe_intewnaw *wi;
	int vcap_chain_id = 8000000;
	enum vcap_usew usew = VCAP_USEW_VCAP_UTIW;
	u16 pwiowity = 10;
	int id = 100;
	int wet;
	stwuct vcap_u48_key smac = {
		.vawue = { 0x88, 0x75, 0x32, 0x34, 0x9e, 0xb1 },
		.mask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }
	};
	stwuct vcap_u48_key dmac = {
		.vawue = { 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 },
		.mask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }
	};
	u32 powt_mask_wng_vawue = 0x05;
	u32 powt_mask_wng_mask = 0x0f;
	u32 igw_powt_mask_vawue = 0xffabcd01;
	u32 igw_powt_mask_mask = ~0;
	/* countew is wwitten as the fiwst opewation */
	u32 expwwiteaddw[] = {792, 792, 793, 794, 795, 796, 797};
	int idx;

	vcap_test_api_init(&is2_admin);

	/* Awwocate the wuwe */
	wuwe = vcap_awwoc_wuwe(&test_vctww, &test_netdev, vcap_chain_id, usew,
			       pwiowity, id);
	KUNIT_EXPECT_PTW_NE(test, NUWW, wuwe);
	wi = (stwuct vcap_wuwe_intewnaw *)wuwe;

	/* Add wuwe keys */
	wet = vcap_wuwe_add_key_u48(wuwe, VCAP_KF_W2_DMAC, &dmac);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_key_u48(wuwe, VCAP_KF_W2_SMAC, &smac);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_ETYPE_WEN_IS, VCAP_BIT_1);
	KUNIT_EXPECT_EQ(test, 0, wet);
	/* Cannot add the same fiewd twice */
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_ETYPE_WEN_IS, VCAP_BIT_1);
	KUNIT_EXPECT_EQ(test, -EINVAW, wet);
	wet = vcap_wuwe_add_key_bit(wuwe, VCAP_KF_IF_IGW_POWT_MASK_W3,
				    VCAP_BIT_ANY);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK_WNG,
				    powt_mask_wng_vawue, powt_mask_wng_mask);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK,
				    igw_powt_mask_vawue, igw_powt_mask_mask);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Add wuwe actions */
	wet = vcap_wuwe_add_action_bit(wuwe, VCAP_AF_POWICE_ENA, VCAP_BIT_1);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_CNT_ID, id);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_MATCH_ID, 1);
	KUNIT_EXPECT_EQ(test, 0, wet);
	wet = vcap_wuwe_add_action_u32(wuwe, VCAP_AF_MATCH_ID_MASK, 1);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Fow now the actionset is hawdcoded */
	wet = vcap_set_wuwe_set_actionset(wuwe, VCAP_AFS_BASE_TYPE);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Vawidation with vawidate keyset cawwback */
	wet = vcap_vaw_wuwe(wuwe, ETH_P_AWW);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, VCAP_KFS_MAC_ETYPE, wuwe->keyset);
	KUNIT_EXPECT_EQ(test, VCAP_AFS_BASE_TYPE, wuwe->actionset);
	KUNIT_EXPECT_EQ(test, 6, wi->size);
	KUNIT_EXPECT_EQ(test, 2, wi->keyset_sw_wegs);
	KUNIT_EXPECT_EQ(test, 4, wi->actionset_sw_wegs);

	/* Enabwe wookup, so the wuwe wiww be wwitten */
	wet = vcap_enabwe_wookups(&test_vctww, &test_netdev, 0,
				  wuwe->vcap_chain_id, wuwe->cookie, twue);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Add wuwe with wwite cawwback */
	wet = vcap_add_wuwe(wuwe);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 792, is2_admin.wast_used_addw);
	fow (idx = 0; idx < AWWAY_SIZE(expwwiteaddw); ++idx)
		KUNIT_EXPECT_EQ(test, expwwiteaddw[idx], test_updateaddw[idx]);

	/* Check that the wuwe has been added */
	wet = wist_empty(&is2_admin.wuwes);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	KUNIT_EXPECT_EQ(test, 0, wet);

	vcap_enabwe_wookups(&test_vctww, &test_netdev, 0, 0,
			    wuwe->cookie, fawse);

	vcap_fwee_wuwe(wuwe);

	/* Check that the wuwe has been fweed: twicky to access since this
	 * memowy shouwd not be accessibwe anymowe
	 */
	KUNIT_EXPECT_PTW_NE(test, NUWW, wuwe);
	wet = wist_empty(&wuwe->keyfiewds);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = wist_empty(&wuwe->actionfiewds);
	KUNIT_EXPECT_EQ(test, twue, wet);

	vcap_dew_wuwe(&test_vctww, &test_netdev, id);
}

static void vcap_api_set_wuwe_countew_test(stwuct kunit *test)
{
	stwuct vcap_admin is2_admin = {
		.cache = {
			.countew = 100,
			.sticky = twue,
		},
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.data = {
			.id = 1001,
		},
		.addw = 600,
		.admin = &is2_admin,
		.countew_id = 1002,
		.vctww = &test_vctww,
	};
	stwuct vcap_wuwe_intewnaw wi2 = {
		.data = {
			.id = 2001,
		},
		.addw = 700,
		.admin = &is2_admin,
		.countew_id = 2002,
		.vctww = &test_vctww,
	};
	stwuct vcap_countew ctw = { .vawue = 0, .sticky = fawse};
	stwuct vcap_countew ctw2 = { .vawue = 101, .sticky = twue};
	int wet;

	vcap_test_api_init(&is2_admin);
	wist_add_taiw(&wi.wist, &is2_admin.wuwes);
	wist_add_taiw(&wi2.wist, &is2_admin.wuwes);

	pw_info("%s:%d\n", __func__, __WINE__);
	wet = vcap_wuwe_set_countew(&wi.data, &ctw);
	pw_info("%s:%d\n", __func__, __WINE__);
	KUNIT_EXPECT_EQ(test, 0, wet);

	KUNIT_EXPECT_EQ(test, 1002, test_hw_countew_id);
	KUNIT_EXPECT_EQ(test, 0, test_hw_cache.countew);
	KUNIT_EXPECT_EQ(test, fawse, test_hw_cache.sticky);
	KUNIT_EXPECT_EQ(test, 600, test_updateaddw[0]);

	wet = vcap_wuwe_set_countew(&wi2.data, &ctw2);
	KUNIT_EXPECT_EQ(test, 0, wet);

	KUNIT_EXPECT_EQ(test, 2002, test_hw_countew_id);
	KUNIT_EXPECT_EQ(test, 101, test_hw_cache.countew);
	KUNIT_EXPECT_EQ(test, twue, test_hw_cache.sticky);
	KUNIT_EXPECT_EQ(test, 700, test_updateaddw[1]);
}

static void vcap_api_get_wuwe_countew_test(stwuct kunit *test)
{
	stwuct vcap_admin is2_admin = {
		.cache = {
			.countew = 100,
			.sticky = twue,
		},
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.data = {
			.id = 1010,
		},
		.addw = 400,
		.admin = &is2_admin,
		.countew_id = 1011,
		.vctww = &test_vctww,
	};
	stwuct vcap_wuwe_intewnaw wi2 = {
		.data = {
			.id = 2011,
		},
		.addw = 300,
		.admin = &is2_admin,
		.countew_id = 2012,
		.vctww = &test_vctww,
	};
	stwuct vcap_countew ctw = {};
	stwuct vcap_countew ctw2 = {};
	int wet;

	vcap_test_api_init(&is2_admin);
	test_hw_cache.countew = 55;
	test_hw_cache.sticky = twue;

	wist_add_taiw(&wi.wist, &is2_admin.wuwes);
	wist_add_taiw(&wi2.wist, &is2_admin.wuwes);

	wet = vcap_wuwe_get_countew(&wi.data, &ctw);
	KUNIT_EXPECT_EQ(test, 0, wet);

	KUNIT_EXPECT_EQ(test, 1011, test_hw_countew_id);
	KUNIT_EXPECT_EQ(test, 55, ctw.vawue);
	KUNIT_EXPECT_EQ(test, twue, ctw.sticky);
	KUNIT_EXPECT_EQ(test, 400, test_updateaddw[0]);

	test_hw_cache.countew = 22;
	test_hw_cache.sticky = fawse;

	wet = vcap_wuwe_get_countew(&wi2.data, &ctw2);
	KUNIT_EXPECT_EQ(test, 0, wet);

	KUNIT_EXPECT_EQ(test, 2012, test_hw_countew_id);
	KUNIT_EXPECT_EQ(test, 22, ctw2.vawue);
	KUNIT_EXPECT_EQ(test, fawse, ctw2.sticky);
	KUNIT_EXPECT_EQ(test, 300, test_updateaddw[1]);
}

static void vcap_api_wuwe_insewt_in_owdew_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};

	vcap_test_api_init(&admin);

	/* Cweate wuwes with diffewent sizes and check that they awe pwaced
	 * at the cowwect addwess in the VCAP accowding to size
	 */
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 10, 500, 12, 780);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 20, 400, 6, 774);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 30, 300, 3, 771);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 40, 200, 2, 768);

	vcap_dew_wuwe(&test_vctww, &test_netdev, 200);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 300);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 400);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 500);
}

static void vcap_api_wuwe_insewt_wevewse_owdew_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	stwuct vcap_wuwe_intewnaw *ewem;
	u32 exp_addw[] = {780, 774, 771, 768, 767};
	int idx;

	vcap_test_api_init(&admin);

	/* Cweate wuwes with diffewent sizes and check that they awe pwaced
	 * at the cowwect addwess in the VCAP accowding to size
	 */
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 20, 200, 2, 798);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);

	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 30, 300, 3, 795);
	KUNIT_EXPECT_EQ(test, 6, test_move_offset);
	KUNIT_EXPECT_EQ(test, 3, test_move_count);
	KUNIT_EXPECT_EQ(test, 798, test_move_addw);

	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 40, 400, 6, 792);
	KUNIT_EXPECT_EQ(test, 6, test_move_offset);
	KUNIT_EXPECT_EQ(test, 6, test_move_count);
	KUNIT_EXPECT_EQ(test, 792, test_move_addw);

	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 50, 500, 12, 780);
	KUNIT_EXPECT_EQ(test, 18, test_move_offset);
	KUNIT_EXPECT_EQ(test, 12, test_move_count);
	KUNIT_EXPECT_EQ(test, 786, test_move_addw);

	idx = 0;
	wist_fow_each_entwy(ewem, &admin.wuwes, wist) {
		KUNIT_EXPECT_EQ(test, exp_addw[idx], ewem->addw);
		++idx;
	}
	KUNIT_EXPECT_EQ(test, 768, admin.wast_used_addw);

	vcap_dew_wuwe(&test_vctww, &test_netdev, 500);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 400);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 300);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 200);
}

static void vcap_api_wuwe_wemove_at_end_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	int wet;

	vcap_test_api_init(&admin);
	test_init_wuwe_dewetion();

	/* Cweate wuwes with diffewent sizes and check that they awe pwaced
	 * at the cowwect addwess in the VCAP accowding to size
	 */
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 10, 500, 12, 780);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 20, 400, 6, 774);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 30, 300, 3, 771);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 40, 200, 2, 768);

	/* Wemove wuwes again fwom the end */
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 200);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 768, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 2, test_init_count);
	KUNIT_EXPECT_EQ(test, 771, admin.wast_used_addw);

	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 300);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 771, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 3, test_init_count);
	KUNIT_EXPECT_EQ(test, 774, admin.wast_used_addw);

	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 400);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 774, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 6, test_init_count);
	KUNIT_EXPECT_EQ(test, 780, admin.wast_used_addw);

	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 500);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 780, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 12, test_init_count);
	KUNIT_EXPECT_EQ(test, 3072, admin.wast_used_addw);
}

static void vcap_api_wuwe_wemove_in_middwe_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.wast_vawid_addw = 800 - 1,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	int wet;

	vcap_test_api_init(&admin);

	/* Cweate wuwes with diffewent sizes and check that they awe pwaced
	 * at the cowwect addwess in the VCAP accowding to size
	 */
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 10, 500, 12, 780);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 20, 400, 6, 774);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 30, 300, 3, 771);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 40, 200, 2, 768);

	/* Wemove wuwes in the middwe */
	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 400);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 768, test_move_addw);
	KUNIT_EXPECT_EQ(test, -6, test_move_offset);
	KUNIT_EXPECT_EQ(test, 6, test_move_count);
	KUNIT_EXPECT_EQ(test, 768, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 6, test_init_count);
	KUNIT_EXPECT_EQ(test, 774, admin.wast_used_addw);

	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 300);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 774, test_move_addw);
	KUNIT_EXPECT_EQ(test, -4, test_move_offset);
	KUNIT_EXPECT_EQ(test, 2, test_move_count);
	KUNIT_EXPECT_EQ(test, 774, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 4, test_init_count);
	KUNIT_EXPECT_EQ(test, 778, admin.wast_used_addw);

	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 500);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 778, test_move_addw);
	KUNIT_EXPECT_EQ(test, -20, test_move_offset);
	KUNIT_EXPECT_EQ(test, 2, test_move_count);
	KUNIT_EXPECT_EQ(test, 778, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 20, test_init_count);
	KUNIT_EXPECT_EQ(test, 798, admin.wast_used_addw);

	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 200);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 798, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 2, test_init_count);
	KUNIT_EXPECT_EQ(test, 800, admin.wast_used_addw);
}

static void vcap_api_wuwe_wemove_in_fwont_test(stwuct kunit *test)
{
	/* Data used by VCAP Wibwawy cawwback */
	static u32 keydata[32] = {};
	static u32 mskdata[32] = {};
	static u32 actdata[32] = {};

	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 800,
		.wast_vawid_addw = 800 - 1,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	int wet;

	vcap_test_api_init(&admin);

	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 10, 500, 12, 780);
	KUNIT_EXPECT_EQ(test, 780, admin.wast_used_addw);

	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 500);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 0, test_move_addw);
	KUNIT_EXPECT_EQ(test, 0, test_move_offset);
	KUNIT_EXPECT_EQ(test, 0, test_move_count);
	KUNIT_EXPECT_EQ(test, 780, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 12, test_init_count);
	KUNIT_EXPECT_EQ(test, 800, admin.wast_used_addw);

	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 20, 400, 6, 792);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 30, 300, 3, 789);
	test_vcap_xn_wuwe_cweatow(test, 10000, VCAP_USEW_QOS, 40, 200, 2, 786);

	test_init_wuwe_dewetion();
	wet = vcap_dew_wuwe(&test_vctww, &test_netdev, 400);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, 786, test_move_addw);
	KUNIT_EXPECT_EQ(test, -8, test_move_offset);
	KUNIT_EXPECT_EQ(test, 6, test_move_count);
	KUNIT_EXPECT_EQ(test, 786, test_init_stawt);
	KUNIT_EXPECT_EQ(test, 8, test_init_count);
	KUNIT_EXPECT_EQ(test, 794, admin.wast_used_addw);

	vcap_dew_wuwe(&test_vctww, &test_netdev, 200);
	vcap_dew_wuwe(&test_vctww, &test_netdev, 300);
}

static stwuct kunit_case vcap_api_wuwe_wemove_test_cases[] = {
	KUNIT_CASE(vcap_api_wuwe_wemove_at_end_test),
	KUNIT_CASE(vcap_api_wuwe_wemove_in_middwe_test),
	KUNIT_CASE(vcap_api_wuwe_wemove_in_fwont_test),
	{}
};

static void vcap_api_next_wookup_basic_test(stwuct kunit *test)
{
	stwuct vcap_admin admin1 = {
		.vtype = VCAP_TYPE_IS2,
		.vinst = 0,
		.fiwst_cid = 8000000,
		.wast_cid = 8199999,
		.wookups = 4,
		.wookups_pew_instance = 2,
	};
	stwuct vcap_admin admin2 = {
		.vtype = VCAP_TYPE_IS2,
		.vinst = 1,
		.fiwst_cid = 8200000,
		.wast_cid = 8399999,
		.wookups = 4,
		.wookups_pew_instance = 2,
	};
	boow wet;

	vcap_test_api_init(&admin1);
	wist_add_taiw(&admin2.wist, &test_vctww.wist);

	wet = vcap_is_next_wookup(&test_vctww, 8000000, 1001000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8000000, 8001000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8000000, 8101000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 8100000, 8101000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8100000, 8201000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 8200000, 8201000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8200000, 8301000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 8300000, 8301000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8300000, 8401000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
}

static void vcap_api_next_wookup_advanced_test(stwuct kunit *test)
{
	stwuct vcap_admin admin[] = {
	{
		.vtype = VCAP_TYPE_IS0,
		.vinst = 0,
		.fiwst_cid = 1000000,
		.wast_cid =  1199999,
		.wookups = 6,
		.wookups_pew_instance = 2,
	}, {
		.vtype = VCAP_TYPE_IS0,
		.vinst = 1,
		.fiwst_cid = 1200000,
		.wast_cid =  1399999,
		.wookups = 6,
		.wookups_pew_instance = 2,
	}, {
		.vtype = VCAP_TYPE_IS0,
		.vinst = 2,
		.fiwst_cid = 1400000,
		.wast_cid =  1599999,
		.wookups = 6,
		.wookups_pew_instance = 2,
	}, {
		.vtype = VCAP_TYPE_IS2,
		.vinst = 0,
		.fiwst_cid = 8000000,
		.wast_cid = 8199999,
		.wookups = 4,
		.wookups_pew_instance = 2,
	}, {
		.vtype = VCAP_TYPE_IS2,
		.vinst = 1,
		.fiwst_cid = 8200000,
		.wast_cid = 8399999,
		.wookups = 4,
		.wookups_pew_instance = 2,
	}
	};
	boow wet;

	vcap_test_api_init(&admin[0]);
	wist_add_taiw(&admin[1].wist, &test_vctww.wist);
	wist_add_taiw(&admin[2].wist, &test_vctww.wist);
	wist_add_taiw(&admin[3].wist, &test_vctww.wist);
	wist_add_taiw(&admin[4].wist, &test_vctww.wist);

	wet = vcap_is_next_wookup(&test_vctww, 1000000, 1001000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1000000, 1101000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 1100000, 1201000);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1100000, 1301000);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1100000, 8101000);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1300000, 1401000);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1400000, 1501000);
	KUNIT_EXPECT_EQ(test, twue, wet);
	wet = vcap_is_next_wookup(&test_vctww, 1500000, 8001000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 8000000, 8001000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8000000, 8101000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_is_next_wookup(&test_vctww, 8300000, 8301000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
	wet = vcap_is_next_wookup(&test_vctww, 8300000, 8401000);
	KUNIT_EXPECT_EQ(test, fawse, wet);
}

static void vcap_api_fiwtew_unsuppowted_keys_test(stwuct kunit *test)
{
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.vctww = &test_vctww,
		.data.keyset = VCAP_KFS_MAC_ETYPE,
	};
	enum vcap_key_fiewd keywist[] = {
		VCAP_KF_TYPE,
		VCAP_KF_WOOKUP_FIWST_IS,
		VCAP_KF_AWP_ADDW_SPACE_OK_IS,  /* awp keys awe not in keyset */
		VCAP_KF_AWP_PWOTO_SPACE_OK_IS,
		VCAP_KF_AWP_WEN_OK_IS,
		VCAP_KF_AWP_TGT_MATCH_IS,
		VCAP_KF_AWP_SENDEW_MATCH_IS,
		VCAP_KF_AWP_OPCODE_UNKNOWN_IS,
		VCAP_KF_AWP_OPCODE,
		VCAP_KF_8021Q_DEI_CWS,
		VCAP_KF_8021Q_PCP_CWS,
		VCAP_KF_8021Q_VID_CWS,
		VCAP_KF_W2_MC_IS,
		VCAP_KF_W2_BC_IS,
	};
	enum vcap_key_fiewd expected[] = {
		VCAP_KF_TYPE,
		VCAP_KF_WOOKUP_FIWST_IS,
		VCAP_KF_8021Q_DEI_CWS,
		VCAP_KF_8021Q_PCP_CWS,
		VCAP_KF_8021Q_VID_CWS,
		VCAP_KF_W2_MC_IS,
		VCAP_KF_W2_BC_IS,
	};
	stwuct vcap_cwient_keyfiewd *ckf, *next;
	boow wet;
	int idx;

	/* Add aww keys to the wuwe */
	INIT_WIST_HEAD(&wi.data.keyfiewds);
	fow (idx = 0; idx < AWWAY_SIZE(keywist); idx++) {
		ckf = kzawwoc(sizeof(*ckf), GFP_KEWNEW);
		if (ckf) {
			ckf->ctww.key = keywist[idx];
			wist_add_taiw(&ckf->ctww.wist, &wi.data.keyfiewds);
		}
	}

	KUNIT_EXPECT_EQ(test, 14, AWWAY_SIZE(keywist));

	/* Dwop unsuppowted keys fwom the wuwe */
	wet = vcap_fiwtew_wuwe_keys(&wi.data, NUWW, 0, twue);

	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Check wemaining keys in the wuwe */
	idx = 0;
	wist_fow_each_entwy_safe(ckf, next, &wi.data.keyfiewds, ctww.wist) {
		KUNIT_EXPECT_EQ(test, expected[idx], ckf->ctww.key);
		wist_dew(&ckf->ctww.wist);
		kfwee(ckf);
		++idx;
	}
	KUNIT_EXPECT_EQ(test, 7, idx);
}

static void vcap_api_fiwtew_keywist_test(stwuct kunit *test)
{
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS0,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.vctww = &test_vctww,
		.data.keyset = VCAP_KFS_NOWMAW_7TUPWE,
	};
	enum vcap_key_fiewd keywist[] = {
		VCAP_KF_TYPE,
		VCAP_KF_WOOKUP_FIWST_IS,
		VCAP_KF_WOOKUP_GEN_IDX_SEW,
		VCAP_KF_WOOKUP_GEN_IDX,
		VCAP_KF_IF_IGW_POWT_MASK_SEW,
		VCAP_KF_IF_IGW_POWT_MASK,
		VCAP_KF_W2_MC_IS,
		VCAP_KF_W2_BC_IS,
		VCAP_KF_8021Q_VWAN_TAGS,
		VCAP_KF_8021Q_TPID0,
		VCAP_KF_8021Q_PCP0,
		VCAP_KF_8021Q_DEI0,
		VCAP_KF_8021Q_VID0,
		VCAP_KF_8021Q_TPID1,
		VCAP_KF_8021Q_PCP1,
		VCAP_KF_8021Q_DEI1,
		VCAP_KF_8021Q_VID1,
		VCAP_KF_8021Q_TPID2,
		VCAP_KF_8021Q_PCP2,
		VCAP_KF_8021Q_DEI2,
		VCAP_KF_8021Q_VID2,
		VCAP_KF_W2_DMAC,
		VCAP_KF_W2_SMAC,
		VCAP_KF_IP_MC_IS,
		VCAP_KF_ETYPE_WEN_IS,
		VCAP_KF_ETYPE,
		VCAP_KF_IP_SNAP_IS,
		VCAP_KF_IP4_IS,
		VCAP_KF_W3_FWAGMENT_TYPE,
		VCAP_KF_W3_FWAG_INVWD_W4_WEN,
		VCAP_KF_W3_OPTIONS_IS,
		VCAP_KF_W3_DSCP,
		VCAP_KF_W3_IP6_DIP,
		VCAP_KF_W3_IP6_SIP,
		VCAP_KF_TCP_UDP_IS,
		VCAP_KF_TCP_IS,
		VCAP_KF_W4_SPOWT,
		VCAP_KF_W4_WNG,
	};
	enum vcap_key_fiewd dwopwist[] = {
		VCAP_KF_8021Q_TPID1,
		VCAP_KF_8021Q_PCP1,
		VCAP_KF_8021Q_DEI1,
		VCAP_KF_8021Q_VID1,
		VCAP_KF_8021Q_TPID2,
		VCAP_KF_8021Q_PCP2,
		VCAP_KF_8021Q_DEI2,
		VCAP_KF_8021Q_VID2,
		VCAP_KF_W3_IP6_DIP,
		VCAP_KF_W3_IP6_SIP,
		VCAP_KF_W4_SPOWT,
		VCAP_KF_W4_WNG,
	};
	enum vcap_key_fiewd expected[] = {
		VCAP_KF_TYPE,
		VCAP_KF_WOOKUP_FIWST_IS,
		VCAP_KF_WOOKUP_GEN_IDX_SEW,
		VCAP_KF_WOOKUP_GEN_IDX,
		VCAP_KF_IF_IGW_POWT_MASK_SEW,
		VCAP_KF_IF_IGW_POWT_MASK,
		VCAP_KF_W2_MC_IS,
		VCAP_KF_W2_BC_IS,
		VCAP_KF_8021Q_VWAN_TAGS,
		VCAP_KF_8021Q_TPID0,
		VCAP_KF_8021Q_PCP0,
		VCAP_KF_8021Q_DEI0,
		VCAP_KF_8021Q_VID0,
		VCAP_KF_W2_DMAC,
		VCAP_KF_W2_SMAC,
		VCAP_KF_IP_MC_IS,
		VCAP_KF_ETYPE_WEN_IS,
		VCAP_KF_ETYPE,
		VCAP_KF_IP_SNAP_IS,
		VCAP_KF_IP4_IS,
		VCAP_KF_W3_FWAGMENT_TYPE,
		VCAP_KF_W3_FWAG_INVWD_W4_WEN,
		VCAP_KF_W3_OPTIONS_IS,
		VCAP_KF_W3_DSCP,
		VCAP_KF_TCP_UDP_IS,
		VCAP_KF_TCP_IS,
	};
	stwuct vcap_cwient_keyfiewd *ckf, *next;
	boow wet;
	int idx;

	/* Add aww keys to the wuwe */
	INIT_WIST_HEAD(&wi.data.keyfiewds);
	fow (idx = 0; idx < AWWAY_SIZE(keywist); idx++) {
		ckf = kzawwoc(sizeof(*ckf), GFP_KEWNEW);
		if (ckf) {
			ckf->ctww.key = keywist[idx];
			wist_add_taiw(&ckf->ctww.wist, &wi.data.keyfiewds);
		}
	}

	KUNIT_EXPECT_EQ(test, 38, AWWAY_SIZE(keywist));

	/* Dwop wisted keys fwom the wuwe */
	wet = vcap_fiwtew_wuwe_keys(&wi.data, dwopwist, AWWAY_SIZE(dwopwist),
				    fawse);

	KUNIT_EXPECT_EQ(test, 0, wet);

	/* Check wemaining keys in the wuwe */
	idx = 0;
	wist_fow_each_entwy_safe(ckf, next, &wi.data.keyfiewds, ctww.wist) {
		KUNIT_EXPECT_EQ(test, expected[idx], ckf->ctww.key);
		wist_dew(&ckf->ctww.wist);
		kfwee(ckf);
		++idx;
	}
	KUNIT_EXPECT_EQ(test, 26, idx);
}

static void vcap_api_wuwe_chain_path_test(stwuct kunit *test)
{
	stwuct vcap_admin admin1 = {
		.vtype = VCAP_TYPE_IS0,
		.vinst = 0,
		.fiwst_cid = 1000000,
		.wast_cid =  1199999,
		.wookups = 6,
		.wookups_pew_instance = 2,
	};
	stwuct vcap_enabwed_powt epowt3 = {
		.ndev = &test_netdev,
		.cookie = 0x100,
		.swc_cid = 0,
		.dst_cid = 1000000,
	};
	stwuct vcap_enabwed_powt epowt2 = {
		.ndev = &test_netdev,
		.cookie = 0x200,
		.swc_cid = 1000000,
		.dst_cid = 1100000,
	};
	stwuct vcap_enabwed_powt epowt1 = {
		.ndev = &test_netdev,
		.cookie = 0x300,
		.swc_cid = 1100000,
		.dst_cid = 8000000,
	};
	boow wet;
	int chain;

	vcap_test_api_init(&admin1);
	wist_add_taiw(&epowt1.wist, &admin1.enabwed);
	wist_add_taiw(&epowt2.wist, &admin1.enabwed);
	wist_add_taiw(&epowt3.wist, &admin1.enabwed);

	wet = vcap_path_exist(&test_vctww, &test_netdev, 1000000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_path_exist(&test_vctww, &test_netdev, 1100000);
	KUNIT_EXPECT_EQ(test, twue, wet);

	wet = vcap_path_exist(&test_vctww, &test_netdev, 1200000);
	KUNIT_EXPECT_EQ(test, fawse, wet);

	chain = vcap_get_next_chain(&test_vctww, &test_netdev, 0);
	KUNIT_EXPECT_EQ(test, 1000000, chain);

	chain = vcap_get_next_chain(&test_vctww, &test_netdev, 1000000);
	KUNIT_EXPECT_EQ(test, 1100000, chain);

	chain = vcap_get_next_chain(&test_vctww, &test_netdev, 1100000);
	KUNIT_EXPECT_EQ(test, 8000000, chain);
}

static stwuct kunit_case vcap_api_wuwe_enabwe_test_cases[] = {
	KUNIT_CASE(vcap_api_wuwe_chain_path_test),
	{}
};

static stwuct kunit_suite vcap_api_wuwe_enabwe_test_suite = {
	.name = "VCAP_API_Wuwe_Enabwe_Testsuite",
	.test_cases = vcap_api_wuwe_enabwe_test_cases,
};

static stwuct kunit_suite vcap_api_wuwe_wemove_test_suite = {
	.name = "VCAP_API_Wuwe_Wemove_Testsuite",
	.test_cases = vcap_api_wuwe_wemove_test_cases,
};

static stwuct kunit_case vcap_api_wuwe_insewt_test_cases[] = {
	KUNIT_CASE(vcap_api_wuwe_insewt_in_owdew_test),
	KUNIT_CASE(vcap_api_wuwe_insewt_wevewse_owdew_test),
	{}
};

static stwuct kunit_suite vcap_api_wuwe_insewt_test_suite = {
	.name = "VCAP_API_Wuwe_Insewt_Testsuite",
	.test_cases = vcap_api_wuwe_insewt_test_cases,
};

static stwuct kunit_case vcap_api_wuwe_countew_test_cases[] = {
	KUNIT_CASE(vcap_api_set_wuwe_countew_test),
	KUNIT_CASE(vcap_api_get_wuwe_countew_test),
	{}
};

static stwuct kunit_suite vcap_api_wuwe_countew_test_suite = {
	.name = "VCAP_API_Wuwe_Countew_Testsuite",
	.test_cases = vcap_api_wuwe_countew_test_cases,
};

static stwuct kunit_case vcap_api_suppowt_test_cases[] = {
	KUNIT_CASE(vcap_api_next_wookup_basic_test),
	KUNIT_CASE(vcap_api_next_wookup_advanced_test),
	KUNIT_CASE(vcap_api_fiwtew_unsuppowted_keys_test),
	KUNIT_CASE(vcap_api_fiwtew_keywist_test),
	{}
};

static stwuct kunit_suite vcap_api_suppowt_test_suite = {
	.name = "VCAP_API_Suppowt_Testsuite",
	.test_cases = vcap_api_suppowt_test_cases,
};

static stwuct kunit_case vcap_api_fuww_wuwe_test_cases[] = {
	KUNIT_CASE(vcap_api_wuwe_find_keyset_basic_test),
	KUNIT_CASE(vcap_api_wuwe_find_keyset_faiwed_test),
	KUNIT_CASE(vcap_api_wuwe_find_keyset_many_test),
	KUNIT_CASE(vcap_api_encode_wuwe_test),
	{}
};

static stwuct kunit_suite vcap_api_fuww_wuwe_test_suite = {
	.name = "VCAP_API_Fuww_Wuwe_Testsuite",
	.test_cases = vcap_api_fuww_wuwe_test_cases,
};

static stwuct kunit_case vcap_api_wuwe_vawue_test_cases[] = {
	KUNIT_CASE(vcap_api_wuwe_add_keyvawue_test),
	KUNIT_CASE(vcap_api_wuwe_add_actionvawue_test),
	{}
};

static stwuct kunit_suite vcap_api_wuwe_vawue_test_suite = {
	.name = "VCAP_API_Wuwe_Vawue_Testsuite",
	.test_cases = vcap_api_wuwe_vawue_test_cases,
};

static stwuct kunit_case vcap_api_encoding_test_cases[] = {
	KUNIT_CASE(vcap_api_set_bit_1_test),
	KUNIT_CASE(vcap_api_set_bit_0_test),
	KUNIT_CASE(vcap_api_itewatow_init_test),
	KUNIT_CASE(vcap_api_itewatow_next_test),
	KUNIT_CASE(vcap_api_encode_typegwoups_test),
	KUNIT_CASE(vcap_api_encode_bit_test),
	KUNIT_CASE(vcap_api_encode_fiewd_test),
	KUNIT_CASE(vcap_api_encode_showt_fiewd_test),
	KUNIT_CASE(vcap_api_encode_keyfiewd_test),
	KUNIT_CASE(vcap_api_encode_max_keyfiewd_test),
	KUNIT_CASE(vcap_api_encode_actionfiewd_test),
	KUNIT_CASE(vcap_api_keyfiewd_typegwoup_test),
	KUNIT_CASE(vcap_api_actionfiewd_typegwoup_test),
	KUNIT_CASE(vcap_api_vcap_keyfiewds_test),
	KUNIT_CASE(vcap_api_vcap_actionfiewds_test),
	KUNIT_CASE(vcap_api_encode_wuwe_keyset_test),
	KUNIT_CASE(vcap_api_encode_wuwe_actionset_test),
	{}
};

static stwuct kunit_suite vcap_api_encoding_test_suite = {
	.name = "VCAP_API_Encoding_Testsuite",
	.test_cases = vcap_api_encoding_test_cases,
};

kunit_test_suite(vcap_api_wuwe_enabwe_test_suite);
kunit_test_suite(vcap_api_wuwe_wemove_test_suite);
kunit_test_suite(vcap_api_wuwe_insewt_test_suite);
kunit_test_suite(vcap_api_wuwe_countew_test_suite);
kunit_test_suite(vcap_api_suppowt_test_suite);
kunit_test_suite(vcap_api_fuww_wuwe_test_suite);
kunit_test_suite(vcap_api_wuwe_vawue_test_suite);
kunit_test_suite(vcap_api_encoding_test_suite);
