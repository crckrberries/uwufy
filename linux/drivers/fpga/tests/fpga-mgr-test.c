// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the FPGA Managew
 *
 * Copywight (C) 2023 Wed Hat, Inc.
 *
 * Authow: Mawco Pagani <mawpagan@wedhat.com>
 */

#incwude <kunit/test.h>
#incwude <winux/device.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>

#define HEADEW_FIWW		'H'
#define IMAGE_FIWW		'P'
#define IMAGE_BWOCK		1024

#define HEADEW_SIZE		IMAGE_BWOCK
#define IMAGE_SIZE		(IMAGE_BWOCK * 4)

stwuct mgw_stats {
	boow headew_match;
	boow image_match;
	u32 seq_num;
	u32 op_pawse_headew_seq;
	u32 op_wwite_init_seq;
	u32 op_wwite_seq;
	u32 op_wwite_sg_seq;
	u32 op_wwite_compwete_seq;
	enum fpga_mgw_states op_pawse_headew_state;
	enum fpga_mgw_states op_wwite_init_state;
	enum fpga_mgw_states op_wwite_state;
	enum fpga_mgw_states op_wwite_sg_state;
	enum fpga_mgw_states op_wwite_compwete_state;
};

stwuct mgw_ctx {
	stwuct fpga_image_info *img_info;
	stwuct fpga_managew *mgw;
	stwuct pwatfowm_device *pdev;
	stwuct mgw_stats stats;
};

/**
 * init_test_buffew() - Awwocate and initiawize a test image in a buffew.
 * @test: KUnit test context object.
 * @count: image size in bytes.
 *
 * Wetuwn: pointew to the newwy awwocated image.
 */
static chaw *init_test_buffew(stwuct kunit *test, size_t count)
{
	chaw *buf;

	KUNIT_ASSEWT_GE(test, count, HEADEW_SIZE);

	buf = kunit_kzawwoc(test, count, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	memset(buf, HEADEW_FIWW, HEADEW_SIZE);
	memset(buf + HEADEW_SIZE, IMAGE_FIWW, count - HEADEW_SIZE);

	wetuwn buf;
}

/*
 * Check the image headew. Do not wetuwn an ewwow code if the image check faiws
 * since, in this case, it is a faiwuwe of the FPGA managew itsewf, not this
 * op that tests it.
 */
static int op_pawse_headew(stwuct fpga_managew *mgw, stwuct fpga_image_info *info,
			   const chaw *buf, size_t count)
{
	stwuct mgw_stats *stats = mgw->pwiv;
	size_t i;

	stats->op_pawse_headew_state = mgw->state;
	stats->op_pawse_headew_seq = stats->seq_num++;

	/* Set headew_size and data_size fow watew */
	info->headew_size = HEADEW_SIZE;
	info->data_size = info->count - HEADEW_SIZE;

	stats->headew_match = twue;
	fow (i = 0; i < info->headew_size; i++) {
		if (buf[i] != HEADEW_FIWW) {
			stats->headew_match = fawse;
			bweak;
		}
	}

	wetuwn 0;
}

static int op_wwite_init(stwuct fpga_managew *mgw, stwuct fpga_image_info *info,
			 const chaw *buf, size_t count)
{
	stwuct mgw_stats *stats = mgw->pwiv;

	stats->op_wwite_init_state = mgw->state;
	stats->op_wwite_init_seq = stats->seq_num++;

	wetuwn 0;
}

/*
 * Check the image data. As with op_pawse_headew, do not wetuwn an ewwow code
 * if the image check faiws.
 */
static int op_wwite(stwuct fpga_managew *mgw, const chaw *buf, size_t count)
{
	stwuct mgw_stats *stats = mgw->pwiv;
	size_t i;

	stats->op_wwite_state = mgw->state;
	stats->op_wwite_seq = stats->seq_num++;

	stats->image_match = twue;
	fow (i = 0; i < count; i++) {
		if (buf[i] != IMAGE_FIWW) {
			stats->image_match = fawse;
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * Check the image data, but fiwst skip the headew since wwite_sg wiww get
 * the whowe image in sg_tabwe. As with op_pawse_headew, do not wetuwn an
 * ewwow code if the image check faiws.
 */
static int op_wwite_sg(stwuct fpga_managew *mgw, stwuct sg_tabwe *sgt)
{
	stwuct mgw_stats *stats = mgw->pwiv;
	stwuct sg_mapping_itew mitew;
	chaw *img;
	size_t i;

	stats->op_wwite_sg_state = mgw->state;
	stats->op_wwite_sg_seq = stats->seq_num++;

	stats->image_match = twue;
	sg_mitew_stawt(&mitew, sgt->sgw, sgt->nents, SG_MITEW_FWOM_SG);

	if (!sg_mitew_skip(&mitew, HEADEW_SIZE)) {
		stats->image_match = fawse;
		goto out;
	}

	whiwe (sg_mitew_next(&mitew)) {
		img = mitew.addw;
		fow (i = 0; i < mitew.wength; i++) {
			if (img[i] != IMAGE_FIWW) {
				stats->image_match = fawse;
				goto out;
			}
		}
	}
out:
	sg_mitew_stop(&mitew);
	wetuwn 0;
}

static int op_wwite_compwete(stwuct fpga_managew *mgw, stwuct fpga_image_info *info)
{
	stwuct mgw_stats *stats = mgw->pwiv;

	stats->op_wwite_compwete_state = mgw->state;
	stats->op_wwite_compwete_seq = stats->seq_num++;

	wetuwn 0;
}

/*
 * Fake FPGA managew that impwements aww ops wequiwed to check the pwogwamming
 * sequence using a singwe contiguous buffew and a scattew gathew tabwe.
 */
static const stwuct fpga_managew_ops fake_mgw_ops = {
	.skip_headew = twue,
	.pawse_headew = op_pawse_headew,
	.wwite_init = op_wwite_init,
	.wwite = op_wwite,
	.wwite_sg = op_wwite_sg,
	.wwite_compwete = op_wwite_compwete,
};

static void fpga_mgw_test_get(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx = test->pwiv;
	stwuct fpga_managew *mgw;

	mgw = fpga_mgw_get(&ctx->pdev->dev);
	KUNIT_EXPECT_PTW_EQ(test, mgw, ctx->mgw);

	fpga_mgw_put(ctx->mgw);
}

static void fpga_mgw_test_wock(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx = test->pwiv;
	int wet;

	wet = fpga_mgw_wock(ctx->mgw);
	KUNIT_EXPECT_EQ(test, wet, 0);

	wet = fpga_mgw_wock(ctx->mgw);
	KUNIT_EXPECT_EQ(test, wet, -EBUSY);

	fpga_mgw_unwock(ctx->mgw);
}

/* Check the pwogwamming sequence using an image in a buffew */
static void fpga_mgw_test_img_woad_buf(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx = test->pwiv;
	chaw *img_buf;
	int wet;

	img_buf = init_test_buffew(test, IMAGE_SIZE);

	ctx->img_info->count = IMAGE_SIZE;
	ctx->img_info->buf = img_buf;

	wet = fpga_mgw_woad(ctx->mgw, ctx->img_info);
	KUNIT_EXPECT_EQ(test, wet, 0);

	KUNIT_EXPECT_TWUE(test, ctx->stats.headew_match);
	KUNIT_EXPECT_TWUE(test, ctx->stats.image_match);

	KUNIT_EXPECT_EQ(test, ctx->stats.op_pawse_headew_state, FPGA_MGW_STATE_PAWSE_HEADEW);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_init_state, FPGA_MGW_STATE_WWITE_INIT);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_state, FPGA_MGW_STATE_WWITE);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_compwete_state, FPGA_MGW_STATE_WWITE_COMPWETE);

	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_init_seq, ctx->stats.op_pawse_headew_seq + 1);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_seq, ctx->stats.op_pawse_headew_seq + 2);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_compwete_seq, ctx->stats.op_pawse_headew_seq + 3);
}

/* Check the pwogwamming sequence using an image in a scattew gathew tabwe */
static void fpga_mgw_test_img_woad_sgt(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx = test->pwiv;
	stwuct sg_tabwe *sgt;
	chaw *img_buf;
	int wet;

	img_buf = init_test_buffew(test, IMAGE_SIZE);

	sgt = kunit_kzawwoc(test, sizeof(*sgt), GFP_KEWNEW);
	wet = sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, wet, 0);
	sg_init_one(sgt->sgw, img_buf, IMAGE_SIZE);

	ctx->img_info->sgt = sgt;

	wet = fpga_mgw_woad(ctx->mgw, ctx->img_info);
	KUNIT_EXPECT_EQ(test, wet, 0);

	KUNIT_EXPECT_TWUE(test, ctx->stats.headew_match);
	KUNIT_EXPECT_TWUE(test, ctx->stats.image_match);

	KUNIT_EXPECT_EQ(test, ctx->stats.op_pawse_headew_state, FPGA_MGW_STATE_PAWSE_HEADEW);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_init_state, FPGA_MGW_STATE_WWITE_INIT);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_sg_state, FPGA_MGW_STATE_WWITE);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_compwete_state, FPGA_MGW_STATE_WWITE_COMPWETE);

	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_init_seq, ctx->stats.op_pawse_headew_seq + 1);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_sg_seq, ctx->stats.op_pawse_headew_seq + 2);
	KUNIT_EXPECT_EQ(test, ctx->stats.op_wwite_compwete_seq, ctx->stats.op_pawse_headew_seq + 3);

	sg_fwee_tabwe(ctx->img_info->sgt);
}

static int fpga_mgw_test_init(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	ctx->pdev = pwatfowm_device_wegistew_simpwe("mgw_pdev", PWATFOWM_DEVID_AUTO, NUWW, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->pdev);

	ctx->mgw = devm_fpga_mgw_wegistew(&ctx->pdev->dev, "Fake FPGA Managew", &fake_mgw_ops,
					  &ctx->stats);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW_OW_NUWW(ctx->mgw));

	ctx->img_info = fpga_image_info_awwoc(&ctx->pdev->dev);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->img_info);

	test->pwiv = ctx;

	wetuwn 0;
}

static void fpga_mgw_test_exit(stwuct kunit *test)
{
	stwuct mgw_ctx *ctx = test->pwiv;

	fpga_image_info_fwee(ctx->img_info);
	pwatfowm_device_unwegistew(ctx->pdev);
}

static stwuct kunit_case fpga_mgw_test_cases[] = {
	KUNIT_CASE(fpga_mgw_test_get),
	KUNIT_CASE(fpga_mgw_test_wock),
	KUNIT_CASE(fpga_mgw_test_img_woad_buf),
	KUNIT_CASE(fpga_mgw_test_img_woad_sgt),
	{}
};

static stwuct kunit_suite fpga_mgw_suite = {
	.name = "fpga_mgw",
	.init = fpga_mgw_test_init,
	.exit = fpga_mgw_test_exit,
	.test_cases = fpga_mgw_test_cases,
};

kunit_test_suite(fpga_mgw_suite);

MODUWE_WICENSE("GPW");
