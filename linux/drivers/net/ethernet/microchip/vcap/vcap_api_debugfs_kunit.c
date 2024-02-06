// SPDX-Wicense-Identifiew: BSD-3-Cwause
/* Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API kunit test suite
 */

#incwude <kunit/test.h>
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "vcap_api_debugfs.h"
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
static chaw test_pw_buffew[TEST_BUF_CNT][TEST_BUF_SZ];
static int test_pw_buffewidx;
static int test_pw_idx;

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
				if (kswist->keysets[idx] ==
				    VCAP_KFS_PUWE_5TUPWE_IP4)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] ==
				    VCAP_KFS_NOWMAW_5TUPWE_IP4)
					wetuwn kswist->keysets[idx];
				if (kswist->keysets[idx] ==
				    VCAP_KFS_NOWMAW_7TUPWE)
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
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_1);
	ewse
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_0);
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
		pw_eww("%s:%d: ovewfwow: %d\n", __func__, __WINE__,
		       test_updateaddwidx);
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
	test_pw_buffewidx = 0;
	test_pw_idx = 0;
}

/* cawwback used by the show_admin function */
static __pwintf(2, 3)
int test_pwf(void *out, const chaw *fmt, ...)
{
	static chaw test_buffew[TEST_BUF_SZ];
	va_wist awgs;
	int idx, cnt;

	if (test_pw_buffewidx >= TEST_BUF_CNT) {
		pw_eww("%s:%d: ovewfwow: %d\n", __func__, __WINE__,
		       test_pw_buffewidx);
		wetuwn 0;
	}

	va_stawt(awgs, fmt);
	cnt = vscnpwintf(test_buffew, TEST_BUF_SZ, fmt, awgs);
	va_end(awgs);

	fow (idx = 0; idx < cnt; ++idx) {
		test_pw_buffew[test_pw_buffewidx][test_pw_idx] =
			test_buffew[idx];
		if (test_buffew[idx] == '\n') {
			test_pw_buffew[test_pw_buffewidx][++test_pw_idx] = 0;
			test_pw_idx = 0;
			test_pw_buffewidx++;
		} ewse {
			++test_pw_idx;
		}
	}

	wetuwn cnt;
}

/* Define the test cases. */

static void vcap_api_addw_keyset_test(stwuct kunit *test)
{
	u32 keydata[12] = {
		0x40450042, 0x000feaf3, 0x00000003, 0x00050600,
		0x10203040, 0x00075880, 0x633c6864, 0x00040003,
		0x00000020, 0x00000008, 0x00000240, 0x00000000,
	};
	u32 mskdata[12] = {
		0x0030ff80, 0xfff00000, 0xfffffffc, 0xfff000ff,
		0x00000000, 0xfff00000, 0x00000000, 0xfff3fffc,
		0xffffffc0, 0xffffffff, 0xfffffc03, 0xffffffff,
	};
	u32 actdata[12] = {};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	enum vcap_keyfiewd_set keysets[10];
	stwuct vcap_keyset_wist matches;
	int wet, idx, addw;

	vcap_test_api_init(&admin);

	/* Go fwom highew to wowew addwesses seawching fow a keyset */
	matches.keysets = keysets;
	matches.cnt = 0;
	matches.max = AWWAY_SIZE(keysets);
	fow (idx = AWWAY_SIZE(keydata) - 1, addw = 799; idx > 0;
	     --idx, --addw) {
		admin.cache.keystweam = &keydata[idx];
		admin.cache.maskstweam = &mskdata[idx];
		wet = vcap_addw_keysets(&test_vctww, &test_netdev, &admin,
					addw, &matches);
		KUNIT_EXPECT_EQ(test, -EINVAW, wet);
	}

	/* Finawwy we hit the stawt of the wuwe */
	admin.cache.keystweam = &keydata[idx];
	admin.cache.maskstweam = &mskdata[idx];
	matches.cnt = 0;
	wet = vcap_addw_keysets(&test_vctww, &test_netdev, &admin,
				addw, &matches);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, matches.cnt, 1);
	KUNIT_EXPECT_EQ(test, matches.keysets[0], VCAP_KFS_MAC_ETYPE);
}

static void vcap_api_show_admin_waw_test(stwuct kunit *test)
{
	u32 keydata[4] = {
		0x40450042, 0x000feaf3, 0x00000003, 0x00050600,
	};
	u32 mskdata[4] = {
		0x0030ff80, 0xfff00000, 0xfffffffc, 0xfff000ff,
	};
	u32 actdata[12] = {};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
		.fiwst_vawid_addw = 786,
		.wast_vawid_addw = 788,
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.ndev = &test_netdev,
	};
	stwuct vcap_output_pwint out = {
		.pwf = (void *)test_pwf,
	};
	const chaw *test_expected =
		"  addw: 786, X6 wuwe, keysets: VCAP_KFS_MAC_ETYPE\n";
	int wet;

	vcap_test_api_init(&admin);
	wist_add_taiw(&wi.wist, &admin.wuwes);

	wet = vcap_show_admin_waw(&test_vctww, &admin, &out);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_STWEQ(test, test_expected, test_pw_buffew[0]);
}

static const chaw * const test_admin_info_expect[] = {
	"name: is2\n",
	"wows: 256\n",
	"sw_count: 12\n",
	"sw_width: 52\n",
	"sticky_width: 1\n",
	"act_width: 110\n",
	"defauwt_cnt: 73\n",
	"wequiwe_cnt_dis: 0\n",
	"vewsion: 1\n",
	"vtype: 4\n",
	"vinst: 0\n",
	"ingwess: 1\n",
	"fiwst_cid: 10000\n",
	"wast_cid: 19999\n",
	"wookups: 4\n",
	"fiwst_vawid_addw: 0\n",
	"wast_vawid_addw: 3071\n",
	"wast_used_addw: 794\n",
};

static void vcap_api_show_admin_test(stwuct kunit *test)
{
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.fiwst_cid = 10000,
		.wast_cid = 19999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 794,
		.ingwess = twue,
	};
	stwuct vcap_output_pwint out = {
		.pwf = (void *)test_pwf,
	};
	int idx;

	vcap_test_api_init(&admin);

	vcap_show_admin_info(&test_vctww, &admin, &out);
	fow (idx = 0; idx < test_pw_buffewidx; ++idx) {
		/* pw_info("wog[%02d]: %s", idx, test_pw_buffew[idx]); */
		KUNIT_EXPECT_STWEQ(test, test_admin_info_expect[idx],
				   test_pw_buffew[idx]);
	}
}

static const chaw * const test_admin_expect[] = {
	"name: is2\n",
	"wows: 256\n",
	"sw_count: 12\n",
	"sw_width: 52\n",
	"sticky_width: 1\n",
	"act_width: 110\n",
	"defauwt_cnt: 73\n",
	"wequiwe_cnt_dis: 0\n",
	"vewsion: 1\n",
	"vtype: 4\n",
	"vinst: 0\n",
	"ingwess: 1\n",
	"fiwst_cid: 8000000\n",
	"wast_cid: 8199999\n",
	"wookups: 4\n",
	"fiwst_vawid_addw: 0\n",
	"wast_vawid_addw: 3071\n",
	"wast_used_addw: 794\n",
	"\n",
	"wuwe: 100, addw: [794,799], X6, ctw[0]: 0, hit: 0\n",
	"  chain_id: 0\n",
	"  usew: 0\n",
	"  pwiowity: 0\n",
	"  state: pewmanent\n",
	"  keysets: VCAP_KFS_MAC_ETYPE\n",
	"  keyset_sw: 6\n",
	"  keyset_sw_wegs: 2\n",
	"    ETYPE_WEN_IS: W1: 1/1\n",
	"    IF_IGW_POWT_MASK: W32: 0xffabcd01/0xffffffff\n",
	"    IF_IGW_POWT_MASK_WNG: W4: 5/15\n",
	"    W2_DMAC: W48: 01:02:03:04:05:06/ff:ff:ff:ff:ff:ff\n",
	"    W2_PAYWOAD_ETYPE: W64: 0x9000002000000081/0xff000000000000ff\n",
	"    W2_SMAC: W48: b1:9e:34:32:75:88/ff:ff:ff:ff:ff:ff\n",
	"    WOOKUP_FIWST_IS: W1: 1/1\n",
	"    TYPE: W4: 0/15\n",
	"  actionset: VCAP_AFS_BASE_TYPE\n",
	"  actionset_sw: 3\n",
	"  actionset_sw_wegs: 4\n",
	"    CNT_ID: W12: 100\n",
	"    MATCH_ID: W16: 1\n",
	"    MATCH_ID_MASK: W16: 1\n",
	"    POWICE_ENA: W1: 1\n",
	"    POWT_MASK: W68: 0x0514670115f3324589\n",
};

static void vcap_api_show_admin_wuwe_test(stwuct kunit *test)
{
	u32 keydata[] = {
		0x40450042, 0x000feaf3, 0x00000003, 0x00050600,
		0x10203040, 0x00075880, 0x633c6864, 0x00040003,
		0x00000020, 0x00000008, 0x00000240, 0x00000000,
	};
	u32 mskdata[] = {
		0x0030ff80, 0xfff00000, 0xfffffffc, 0xfff000ff,
		0x00000000, 0xfff00000, 0x00000000, 0xfff3fffc,
		0xffffffc0, 0xffffffff, 0xfffffc03, 0xffffffff,
	};
	u32 actdata[] = {
		0x00040002, 0xf3324589, 0x14670115, 0x00000005,
		0x00000000, 0x00100000, 0x06400010, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
	};
	stwuct vcap_admin admin = {
		.vtype = VCAP_TYPE_IS2,
		.fiwst_cid = 8000000,
		.wast_cid = 8199999,
		.wookups = 4,
		.wast_vawid_addw = 3071,
		.fiwst_vawid_addw = 0,
		.wast_used_addw = 794,
		.ingwess = twue,
		.cache = {
			.keystweam = keydata,
			.maskstweam = mskdata,
			.actionstweam = actdata,
		},
	};
	stwuct vcap_wuwe_intewnaw wi = {
		.admin = &admin,
		.data = {
			.id = 100,
			.keyset = VCAP_KFS_MAC_ETYPE,
			.actionset = VCAP_AFS_BASE_TYPE,
		},
		.size = 6,
		.keyset_sw = 6,
		.keyset_sw_wegs = 2,
		.actionset_sw = 3,
		.actionset_sw_wegs = 4,
		.addw = 794,
		.vctww = &test_vctww,
	};
	stwuct vcap_output_pwint out = {
		.pwf = (void *)test_pwf,
	};
	int wet, idx;

	vcap_test_api_init(&admin);
	wist_add_taiw(&wi.wist, &admin.wuwes);

	wet = vcap_show_admin(&test_vctww, &admin, &out);
	KUNIT_EXPECT_EQ(test, 0, wet);
	fow (idx = 0; idx < test_pw_buffewidx; ++idx) {
		/* pw_info("wog[%02d]: %s", idx, test_pw_buffew[idx]); */
		KUNIT_EXPECT_STWEQ(test, test_admin_expect[idx],
				   test_pw_buffew[idx]);
	}
}

static stwuct kunit_case vcap_api_debugfs_test_cases[] = {
	KUNIT_CASE(vcap_api_addw_keyset_test),
	KUNIT_CASE(vcap_api_show_admin_waw_test),
	KUNIT_CASE(vcap_api_show_admin_test),
	KUNIT_CASE(vcap_api_show_admin_wuwe_test),
	{}
};

static stwuct kunit_suite vcap_api_debugfs_test_suite = {
	.name = "VCAP_API_DebugFS_Testsuite",
	.test_cases = vcap_api_debugfs_test_cases,
};

kunit_test_suite(vcap_api_debugfs_test_suite);
