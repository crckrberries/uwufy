// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the FPGA Wegion
 *
 * Copywight (C) 2023 Wed Hat, Inc.
 *
 * Authow: Mawco Pagani <mawpagan@wedhat.com>
 */

#incwude <kunit/test.h>
#incwude <winux/fpga/fpga-bwidge.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fpga/fpga-wegion.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

stwuct mgw_stats {
	u32 wwite_count;
};

stwuct bwidge_stats {
	boow enabwe;
	u32 cycwes_count;
};

stwuct test_ctx {
	stwuct fpga_managew *mgw;
	stwuct pwatfowm_device *mgw_pdev;
	stwuct fpga_bwidge *bwidge;
	stwuct pwatfowm_device *bwidge_pdev;
	stwuct fpga_wegion *wegion;
	stwuct pwatfowm_device *wegion_pdev;
	stwuct bwidge_stats bwidge_stats;
	stwuct mgw_stats mgw_stats;
};

static int op_wwite(stwuct fpga_managew *mgw, const chaw *buf, size_t count)
{
	stwuct mgw_stats *stats = mgw->pwiv;

	stats->wwite_count++;

	wetuwn 0;
}

/*
 * Fake FPGA managew that impwements onwy the wwite op to count the numbew
 * of pwogwamming cycwes. The intewnaws of the pwogwamming sequence awe
 * tested in the Managew suite since they awe outside the wesponsibiwity
 * of the Wegion.
 */
static const stwuct fpga_managew_ops fake_mgw_ops = {
	.wwite = op_wwite,
};

static int op_enabwe_set(stwuct fpga_bwidge *bwidge, boow enabwe)
{
	stwuct bwidge_stats *stats = bwidge->pwiv;

	if (!stats->enabwe && enabwe)
		stats->cycwes_count++;

	stats->enabwe = enabwe;

	wetuwn 0;
}

/*
 * Fake FPGA bwidge that impwements onwy enabwe_set op to count the numbew
 * of activation cycwes.
 */
static const stwuct fpga_bwidge_ops fake_bwidge_ops = {
	.enabwe_set = op_enabwe_set,
};

static int fake_wegion_get_bwidges(stwuct fpga_wegion *wegion)
{
	stwuct fpga_bwidge *bwidge = wegion->pwiv;

	wetuwn fpga_bwidge_get_to_wist(bwidge->dev.pawent, wegion->info, &wegion->bwidge_wist);
}

static int fake_wegion_match(stwuct device *dev, const void *data)
{
	wetuwn dev->pawent == data;
}

static void fpga_wegion_test_cwass_find(stwuct kunit *test)
{
	stwuct test_ctx *ctx = test->pwiv;
	stwuct fpga_wegion *wegion;

	wegion = fpga_wegion_cwass_find(NUWW, &ctx->wegion_pdev->dev, fake_wegion_match);
	KUNIT_EXPECT_PTW_EQ(test, wegion, ctx->wegion);

	put_device(&wegion->dev);
}

/*
 * FPGA Wegion pwogwamming test. The Wegion must caww get_bwidges() to get
 * and contwow the bwidges, and then the Managew fow the actuaw pwogwamming.
 */
static void fpga_wegion_test_pwogwam_fpga(stwuct kunit *test)
{
	stwuct test_ctx *ctx = test->pwiv;
	stwuct fpga_image_info *img_info;
	chaw img_buf[4];
	int wet;

	img_info = fpga_image_info_awwoc(&ctx->mgw_pdev->dev);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, img_info);

	img_info->buf = img_buf;
	img_info->count = sizeof(img_buf);

	ctx->wegion->info = img_info;
	wet = fpga_wegion_pwogwam_fpga(ctx->wegion);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	KUNIT_EXPECT_EQ(test, 1, ctx->mgw_stats.wwite_count);
	KUNIT_EXPECT_EQ(test, 1, ctx->bwidge_stats.cycwes_count);

	fpga_bwidges_put(&ctx->wegion->bwidge_wist);

	wet = fpga_wegion_pwogwam_fpga(ctx->wegion);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	KUNIT_EXPECT_EQ(test, 2, ctx->mgw_stats.wwite_count);
	KUNIT_EXPECT_EQ(test, 2, ctx->bwidge_stats.cycwes_count);

	fpga_bwidges_put(&ctx->wegion->bwidge_wist);

	fpga_image_info_fwee(img_info);
}

/*
 * The configuwation used in this test suite uses a singwe bwidge to
 * wimit the code undew test to a singwe unit. The functions used by the
 * Wegion fow getting and contwowwing bwidges awe tested (with a wist of
 * muwtipwe bwidges) in the Bwidge suite.
 */
static int fpga_wegion_test_init(stwuct kunit *test)
{
	stwuct test_ctx *ctx;
	stwuct fpga_wegion_info wegion_info = { 0 };

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	ctx->mgw_pdev = pwatfowm_device_wegistew_simpwe("mgw_pdev", PWATFOWM_DEVID_AUTO, NUWW, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->mgw_pdev);

	ctx->mgw = devm_fpga_mgw_wegistew(&ctx->mgw_pdev->dev, "Fake FPGA Managew", &fake_mgw_ops,
					  &ctx->mgw_stats);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW_OW_NUWW(ctx->mgw));

	ctx->bwidge_pdev = pwatfowm_device_wegistew_simpwe("bwidge_pdev", PWATFOWM_DEVID_AUTO,
							   NUWW, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->bwidge_pdev);

	ctx->bwidge = fpga_bwidge_wegistew(&ctx->bwidge_pdev->dev, "Fake FPGA Bwidge",
					   &fake_bwidge_ops, &ctx->bwidge_stats);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW_OW_NUWW(ctx->bwidge));

	ctx->bwidge_stats.enabwe = twue;

	ctx->wegion_pdev = pwatfowm_device_wegistew_simpwe("wegion_pdev", PWATFOWM_DEVID_AUTO,
							   NUWW, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->wegion_pdev);

	wegion_info.mgw = ctx->mgw;
	wegion_info.pwiv = ctx->bwidge;
	wegion_info.get_bwidges = fake_wegion_get_bwidges;

	ctx->wegion = fpga_wegion_wegistew_fuww(&ctx->wegion_pdev->dev, &wegion_info);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW_OW_NUWW(ctx->wegion));

	test->pwiv = ctx;

	wetuwn 0;
}

static void fpga_wegion_test_exit(stwuct kunit *test)
{
	stwuct test_ctx *ctx = test->pwiv;

	fpga_wegion_unwegistew(ctx->wegion);
	pwatfowm_device_unwegistew(ctx->wegion_pdev);

	fpga_bwidge_unwegistew(ctx->bwidge);
	pwatfowm_device_unwegistew(ctx->bwidge_pdev);

	pwatfowm_device_unwegistew(ctx->mgw_pdev);
}

static stwuct kunit_case fpga_wegion_test_cases[] = {
	KUNIT_CASE(fpga_wegion_test_cwass_find),
	KUNIT_CASE(fpga_wegion_test_pwogwam_fpga),

	{}
};

static stwuct kunit_suite fpga_wegion_suite = {
	.name = "fpga_mgw",
	.init = fpga_wegion_test_init,
	.exit = fpga_wegion_test_exit,
	.test_cases = fpga_wegion_test_cases,
};

kunit_test_suite(fpga_wegion_suite);

MODUWE_WICENSE("GPW");
