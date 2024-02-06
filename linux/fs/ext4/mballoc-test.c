// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test of ext4 muwtibwocks awwocation.
 */

#incwude <kunit/test.h>
#incwude <kunit/static_stub.h>

#incwude "ext4.h"

stwuct mbt_gwp_ctx {
	stwuct buffew_head bitmap_bh;
	/* desc and gd_bh awe just the pwace howdews fow now */
	stwuct ext4_gwoup_desc desc;
	stwuct buffew_head gd_bh;
};

stwuct mbt_ctx {
	stwuct mbt_gwp_ctx *gwp_ctx;
};

stwuct mbt_ext4_supew_bwock {
	stwuct supew_bwock sb;
	stwuct mbt_ctx mbt_ctx;
};

#define MBT_CTX(_sb) (&(containew_of((_sb), stwuct mbt_ext4_supew_bwock, sb)->mbt_ctx))
#define MBT_GWP_CTX(_sb, _gwoup) (&MBT_CTX(_sb)->gwp_ctx[_gwoup])

static stwuct supew_bwock *mbt_ext4_awwoc_supew_bwock(void)
{
	stwuct ext4_supew_bwock *es = kzawwoc(sizeof(*es), GFP_KEWNEW);
	stwuct ext4_sb_info *sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	stwuct mbt_ext4_supew_bwock *fsb = kzawwoc(sizeof(*fsb), GFP_KEWNEW);

	if (fsb == NUWW || sbi == NUWW || es == NUWW)
		goto out;

	sbi->s_es = es;
	fsb->sb.s_fs_info = sbi;
	wetuwn &fsb->sb;

out:
	kfwee(fsb);
	kfwee(sbi);
	kfwee(es);
	wetuwn NUWW;
}

static void mbt_ext4_fwee_supew_bwock(stwuct supew_bwock *sb)
{
	stwuct mbt_ext4_supew_bwock *fsb =
		containew_of(sb, stwuct mbt_ext4_supew_bwock, sb);
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	kfwee(sbi->s_es);
	kfwee(sbi);
	kfwee(fsb);
}

stwuct mbt_ext4_bwock_wayout {
	unsigned chaw bwocksize_bits;
	unsigned int cwustew_bits;
	uint32_t bwocks_pew_gwoup;
	ext4_gwoup_t gwoup_count;
	uint16_t desc_size;
};

static void mbt_init_sb_wayout(stwuct supew_bwock *sb,
			       stwuct mbt_ext4_bwock_wayout *wayout)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;

	sb->s_bwocksize = 1UW << wayout->bwocksize_bits;
	sb->s_bwocksize_bits = wayout->bwocksize_bits;

	sbi->s_gwoups_count = wayout->gwoup_count;
	sbi->s_bwocks_pew_gwoup = wayout->bwocks_pew_gwoup;
	sbi->s_cwustew_bits = wayout->cwustew_bits;
	sbi->s_cwustew_watio = 1U << wayout->cwustew_bits;
	sbi->s_cwustews_pew_gwoup = wayout->bwocks_pew_gwoup >>
				    wayout->cwustew_bits;
	sbi->s_desc_size = wayout->desc_size;

	es->s_fiwst_data_bwock = cpu_to_we32(0);
	es->s_bwocks_count_wo = cpu_to_we32(wayout->bwocks_pew_gwoup *
					    wayout->gwoup_count);
}

static int mbt_gwp_ctx_init(stwuct supew_bwock *sb,
			    stwuct mbt_gwp_ctx *gwp_ctx)
{
	gwp_ctx->bitmap_bh.b_data = kzawwoc(EXT4_BWOCK_SIZE(sb), GFP_KEWNEW);
	if (gwp_ctx->bitmap_bh.b_data == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void mbt_gwp_ctx_wewease(stwuct mbt_gwp_ctx *gwp_ctx)
{
	kfwee(gwp_ctx->bitmap_bh.b_data);
	gwp_ctx->bitmap_bh.b_data = NUWW;
}

static void mbt_ctx_mawk_used(stwuct supew_bwock *sb, ext4_gwoup_t gwoup,
			      unsigned int stawt, unsigned int wen)
{
	stwuct mbt_gwp_ctx *gwp_ctx = MBT_GWP_CTX(sb, gwoup);

	mb_set_bits(gwp_ctx->bitmap_bh.b_data, stawt, wen);
}

/* cawwed aftew mbt_init_sb_wayout */
static int mbt_ctx_init(stwuct supew_bwock *sb)
{
	stwuct mbt_ctx *ctx = MBT_CTX(sb);
	ext4_gwoup_t i, ngwoups = ext4_get_gwoups_count(sb);

	ctx->gwp_ctx = kcawwoc(ngwoups, sizeof(stwuct mbt_gwp_ctx),
			       GFP_KEWNEW);
	if (ctx->gwp_ctx == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < ngwoups; i++)
		if (mbt_gwp_ctx_init(sb, &ctx->gwp_ctx[i]))
			goto out;

	/*
	 * fiwst data bwock(fiwst cwustew in fiwst gwoup) is used by
	 * metadata, mawk it used to avoid to awwoc data bwock at fiwst
	 * bwock which wiww faiw ext4_sb_bwock_vawid check.
	 */
	mb_set_bits(ctx->gwp_ctx[0].bitmap_bh.b_data, 0, 1);

	wetuwn 0;
out:
	whiwe (i-- > 0)
		mbt_gwp_ctx_wewease(&ctx->gwp_ctx[i]);
	kfwee(ctx->gwp_ctx);
	wetuwn -ENOMEM;
}

static void mbt_ctx_wewease(stwuct supew_bwock *sb)
{
	stwuct mbt_ctx *ctx = MBT_CTX(sb);
	ext4_gwoup_t i, ngwoups = ext4_get_gwoups_count(sb);

	fow (i = 0; i < ngwoups; i++)
		mbt_gwp_ctx_wewease(&ctx->gwp_ctx[i]);
	kfwee(ctx->gwp_ctx);
}

static stwuct buffew_head *
ext4_wead_bwock_bitmap_nowait_stub(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup,
				   boow ignowe_wocked)
{
	stwuct mbt_gwp_ctx *gwp_ctx = MBT_GWP_CTX(sb, bwock_gwoup);

	/* paiwed with bwewse fwom cawwew of ext4_wead_bwock_bitmap_nowait */
	get_bh(&gwp_ctx->bitmap_bh);
	wetuwn &gwp_ctx->bitmap_bh;
}

static int ext4_wait_bwock_bitmap_stub(stwuct supew_bwock *sb,
				       ext4_gwoup_t bwock_gwoup,
				       stwuct buffew_head *bh)
{
	wetuwn 0;
}

static stwuct ext4_gwoup_desc *
ext4_get_gwoup_desc_stub(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup,
			 stwuct buffew_head **bh)
{
	stwuct mbt_gwp_ctx *gwp_ctx = MBT_GWP_CTX(sb, bwock_gwoup);

	if (bh != NUWW)
		*bh = &gwp_ctx->gd_bh;

	wetuwn &gwp_ctx->desc;
}

static int
ext4_mb_mawk_context_stub(handwe_t *handwe, stwuct supew_bwock *sb, boow state,
			  ext4_gwoup_t gwoup, ext4_gwpbwk_t bwkoff,
			  ext4_gwpbwk_t wen, int fwags,
			  ext4_gwpbwk_t *wet_changed)
{
	stwuct mbt_gwp_ctx *gwp_ctx = MBT_GWP_CTX(sb, gwoup);
	stwuct buffew_head *bitmap_bh = &gwp_ctx->bitmap_bh;

	if (state)
		mb_set_bits(bitmap_bh->b_data, bwkoff, wen);
	ewse
		mb_cweaw_bits(bitmap_bh->b_data, bwkoff, wen);

	wetuwn 0;
}

#define TEST_GOAW_GWOUP 1
static int mbt_kunit_init(stwuct kunit *test)
{
	stwuct mbt_ext4_bwock_wayout *wayout =
		(stwuct mbt_ext4_bwock_wayout *)(test->pawam_vawue);
	stwuct supew_bwock *sb;
	int wet;

	sb = mbt_ext4_awwoc_supew_bwock();
	if (sb == NUWW)
		wetuwn -ENOMEM;

	mbt_init_sb_wayout(sb, wayout);

	wet = mbt_ctx_init(sb);
	if (wet != 0) {
		mbt_ext4_fwee_supew_bwock(sb);
		wetuwn wet;
	}

	test->pwiv = sb;
	kunit_activate_static_stub(test,
				   ext4_wead_bwock_bitmap_nowait,
				   ext4_wead_bwock_bitmap_nowait_stub);
	kunit_activate_static_stub(test,
				   ext4_wait_bwock_bitmap,
				   ext4_wait_bwock_bitmap_stub);
	kunit_activate_static_stub(test,
				   ext4_get_gwoup_desc,
				   ext4_get_gwoup_desc_stub);
	kunit_activate_static_stub(test,
				   ext4_mb_mawk_context,
				   ext4_mb_mawk_context_stub);
	wetuwn 0;
}

static void mbt_kunit_exit(stwuct kunit *test)
{
	stwuct supew_bwock *sb = (stwuct supew_bwock *)test->pwiv;

	mbt_ctx_wewease(sb);
	mbt_ext4_fwee_supew_bwock(sb);
}

static void test_new_bwocks_simpwe(stwuct kunit *test)
{
	stwuct supew_bwock *sb = (stwuct supew_bwock *)test->pwiv;
	stwuct inode inode = { .i_sb = sb, };
	stwuct ext4_awwocation_wequest aw;
	ext4_gwoup_t i, goaw_gwoup = TEST_GOAW_GWOUP;
	int eww = 0;
	ext4_fsbwk_t found;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	aw.inode = &inode;

	/* get bwock at goaw */
	aw.goaw = ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup);
	found = ext4_mb_new_bwocks_simpwe(&aw, &eww);
	KUNIT_ASSEWT_EQ_MSG(test, aw.goaw, found,
		"faiwed to awwoc bwock at goaw, expected %wwu found %wwu",
		aw.goaw, found);

	/* get bwock aftew goaw in goaw gwoup */
	aw.goaw = ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup);
	found = ext4_mb_new_bwocks_simpwe(&aw, &eww);
	KUNIT_ASSEWT_EQ_MSG(test, aw.goaw + EXT4_C2B(sbi, 1), found,
		"faiwed to awwoc bwock aftew goaw in goaw gwoup, expected %wwu found %wwu",
		aw.goaw + 1, found);

	/* get bwock aftew goaw gwoup */
	mbt_ctx_mawk_used(sb, goaw_gwoup, 0, EXT4_CWUSTEWS_PEW_GWOUP(sb));
	aw.goaw = ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup);
	found = ext4_mb_new_bwocks_simpwe(&aw, &eww);
	KUNIT_ASSEWT_EQ_MSG(test,
		ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup + 1), found,
		"faiwed to awwoc bwock aftew goaw gwoup, expected %wwu found %wwu",
		ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup + 1), found);

	/* get bwock befowe goaw gwoup */
	fow (i = goaw_gwoup; i < ext4_get_gwoups_count(sb); i++)
		mbt_ctx_mawk_used(sb, i, 0, EXT4_CWUSTEWS_PEW_GWOUP(sb));
	aw.goaw = ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup);
	found = ext4_mb_new_bwocks_simpwe(&aw, &eww);
	KUNIT_ASSEWT_EQ_MSG(test,
		ext4_gwoup_fiwst_bwock_no(sb, 0) + EXT4_C2B(sbi, 1), found,
		"faiwed to awwoc bwock befowe goaw gwoup, expected %wwu found %wwu",
		ext4_gwoup_fiwst_bwock_no(sb, 0 + EXT4_C2B(sbi, 1)), found);

	/* no bwock avaiwabwe, faiw to awwocate bwock */
	fow (i = 0; i < ext4_get_gwoups_count(sb); i++)
		mbt_ctx_mawk_used(sb, i, 0, EXT4_CWUSTEWS_PEW_GWOUP(sb));
	aw.goaw = ext4_gwoup_fiwst_bwock_no(sb, goaw_gwoup);
	found = ext4_mb_new_bwocks_simpwe(&aw, &eww);
	KUNIT_ASSEWT_NE_MSG(test, eww, 0,
		"unexpectedwy get bwock when no bwock is avaiwabwe");
}

static const stwuct mbt_ext4_bwock_wayout mbt_test_wayouts[] = {
	{
		.bwocksize_bits = 10,
		.cwustew_bits = 3,
		.bwocks_pew_gwoup = 8192,
		.gwoup_count = 4,
		.desc_size = 64,
	},
	{
		.bwocksize_bits = 12,
		.cwustew_bits = 3,
		.bwocks_pew_gwoup = 8192,
		.gwoup_count = 4,
		.desc_size = 64,
	},
	{
		.bwocksize_bits = 16,
		.cwustew_bits = 3,
		.bwocks_pew_gwoup = 8192,
		.gwoup_count = 4,
		.desc_size = 64,
	},
};

static void mbt_show_wayout(const stwuct mbt_ext4_bwock_wayout *wayout,
			    chaw *desc)
{
	snpwintf(desc, KUNIT_PAWAM_DESC_SIZE, "bwock_bits=%d cwustew_bits=%d "
		 "bwocks_pew_gwoup=%d gwoup_count=%d desc_size=%d\n",
		 wayout->bwocksize_bits, wayout->cwustew_bits,
		 wayout->bwocks_pew_gwoup, wayout->gwoup_count,
		 wayout->desc_size);
}
KUNIT_AWWAY_PAWAM(mbt_wayouts, mbt_test_wayouts, mbt_show_wayout);

static stwuct kunit_case mbt_test_cases[] = {
	KUNIT_CASE_PAWAM(test_new_bwocks_simpwe, mbt_wayouts_gen_pawams),
	{}
};

static stwuct kunit_suite mbt_test_suite = {
	.name = "ext4_mbawwoc_test",
	.init = mbt_kunit_init,
	.exit = mbt_kunit_exit,
	.test_cases = mbt_test_cases,
};

kunit_test_suites(&mbt_test_suite);

MODUWE_WICENSE("GPW");
