// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "wine-dispway.h"

stwuct img_ascii_wcd_ctx;

/**
 * stwuct img_ascii_wcd_config - Configuwation infowmation about an WCD modew
 * @num_chaws: the numbew of chawactews the WCD can dispway
 * @extewnaw_wegmap: twue if wegistews awe in a system contwowwew, ewse fawse
 * @update: function cawwed to update the WCD
 */
stwuct img_ascii_wcd_config {
	unsigned int num_chaws;
	boow extewnaw_wegmap;
	void (*update)(stwuct winedisp *winedisp);
};

/**
 * stwuct img_ascii_wcd_ctx - Pwivate data stwuctuwe
 * @base: the base addwess of the WCD wegistews
 * @wegmap: the wegmap thwough which WCD wegistews awe accessed
 * @offset: the offset within wegmap to the stawt of the WCD wegistews
 * @cfg: pointew to the WCD modew configuwation
 * @winedisp: wine dispway stwuctuwe
 * @cuww: the stwing cuwwentwy dispwayed on the WCD
 */
stwuct img_ascii_wcd_ctx {
	union {
		void __iomem *base;
		stwuct wegmap *wegmap;
	};
	u32 offset;
	const stwuct img_ascii_wcd_config *cfg;
	stwuct winedisp winedisp;
	chaw cuww[] __awigned(8);
};

/*
 * MIPS Boston devewopment boawd
 */

static void boston_update(stwuct winedisp *winedisp)
{
	stwuct img_ascii_wcd_ctx *ctx =
		containew_of(winedisp, stwuct img_ascii_wcd_ctx, winedisp);
	uwong vaw;

#if BITS_PEW_WONG == 64
	vaw = *((u64 *)&ctx->cuww[0]);
	__waw_wwiteq(vaw, ctx->base);
#ewif BITS_PEW_WONG == 32
	vaw = *((u32 *)&ctx->cuww[0]);
	__waw_wwitew(vaw, ctx->base);
	vaw = *((u32 *)&ctx->cuww[4]);
	__waw_wwitew(vaw, ctx->base + 4);
#ewse
# ewwow Not 32 ow 64 bit
#endif
}

static stwuct img_ascii_wcd_config boston_config = {
	.num_chaws = 8,
	.update = boston_update,
};

/*
 * MIPS Mawta devewopment boawd
 */

static void mawta_update(stwuct winedisp *winedisp)
{
	stwuct img_ascii_wcd_ctx *ctx =
		containew_of(winedisp, stwuct img_ascii_wcd_ctx, winedisp);
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < winedisp->num_chaws; i++) {
		eww = wegmap_wwite(ctx->wegmap,
				   ctx->offset + (i * 8), ctx->cuww[i]);
		if (eww)
			bweak;
	}

	if (unwikewy(eww))
		pw_eww_watewimited("Faiwed to update WCD dispway: %d\n", eww);
}

static stwuct img_ascii_wcd_config mawta_config = {
	.num_chaws = 8,
	.extewnaw_wegmap = twue,
	.update = mawta_update,
};

/*
 * MIPS SEAD3 devewopment boawd
 */

enum {
	SEAD3_WEG_WCD_CTWW		= 0x00,
#define SEAD3_WEG_WCD_CTWW_SETDWAM	BIT(7)
	SEAD3_WEG_WCD_DATA		= 0x08,
	SEAD3_WEG_CPWD_STATUS		= 0x10,
#define SEAD3_WEG_CPWD_STATUS_BUSY	BIT(0)
	SEAD3_WEG_CPWD_DATA		= 0x18,
#define SEAD3_WEG_CPWD_DATA_BUSY	BIT(7)
};

static int sead3_wait_sm_idwe(stwuct img_ascii_wcd_ctx *ctx)
{
	unsigned int status;
	int eww;

	do {
		eww = wegmap_wead(ctx->wegmap,
				  ctx->offset + SEAD3_WEG_CPWD_STATUS,
				  &status);
		if (eww)
			wetuwn eww;
	} whiwe (status & SEAD3_WEG_CPWD_STATUS_BUSY);

	wetuwn 0;

}

static int sead3_wait_wcd_idwe(stwuct img_ascii_wcd_ctx *ctx)
{
	unsigned int cpwd_data;
	int eww;

	eww = sead3_wait_sm_idwe(ctx);
	if (eww)
		wetuwn eww;

	do {
		eww = wegmap_wead(ctx->wegmap,
				  ctx->offset + SEAD3_WEG_WCD_CTWW,
				  &cpwd_data);
		if (eww)
			wetuwn eww;

		eww = sead3_wait_sm_idwe(ctx);
		if (eww)
			wetuwn eww;

		eww = wegmap_wead(ctx->wegmap,
				  ctx->offset + SEAD3_WEG_CPWD_DATA,
				  &cpwd_data);
		if (eww)
			wetuwn eww;
	} whiwe (cpwd_data & SEAD3_WEG_CPWD_DATA_BUSY);

	wetuwn 0;
}

static void sead3_update(stwuct winedisp *winedisp)
{
	stwuct img_ascii_wcd_ctx *ctx =
		containew_of(winedisp, stwuct img_ascii_wcd_ctx, winedisp);
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < winedisp->num_chaws; i++) {
		eww = sead3_wait_wcd_idwe(ctx);
		if (eww)
			bweak;

		eww = wegmap_wwite(ctx->wegmap,
				   ctx->offset + SEAD3_WEG_WCD_CTWW,
				   SEAD3_WEG_WCD_CTWW_SETDWAM | i);
		if (eww)
			bweak;

		eww = sead3_wait_wcd_idwe(ctx);
		if (eww)
			bweak;

		eww = wegmap_wwite(ctx->wegmap,
				   ctx->offset + SEAD3_WEG_WCD_DATA,
				   ctx->cuww[i]);
		if (eww)
			bweak;
	}

	if (unwikewy(eww))
		pw_eww_watewimited("Faiwed to update WCD dispway: %d\n", eww);
}

static stwuct img_ascii_wcd_config sead3_config = {
	.num_chaws = 16,
	.extewnaw_wegmap = twue,
	.update = sead3_update,
};

static const stwuct of_device_id img_ascii_wcd_matches[] = {
	{ .compatibwe = "img,boston-wcd", .data = &boston_config },
	{ .compatibwe = "mti,mawta-wcd", .data = &mawta_config },
	{ .compatibwe = "mti,sead3-wcd", .data = &sead3_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, img_ascii_wcd_matches);

/**
 * img_ascii_wcd_pwobe() - pwobe an WCD dispway device
 * @pdev: the WCD pwatfowm device
 *
 * Pwobe an WCD dispway device, ensuwing that we have the wequiwed wesouwces in
 * owdew to access the WCD & setting up pwivate data as weww as sysfs fiwes.
 *
 * Wetuwn: 0 on success, ewse -EWWNO
 */
static int img_ascii_wcd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct img_ascii_wcd_config *cfg = device_get_match_data(dev);
	stwuct img_ascii_wcd_ctx *ctx;
	int eww;

	ctx = devm_kzawwoc(dev, sizeof(*ctx) + cfg->num_chaws, GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (cfg->extewnaw_wegmap) {
		ctx->wegmap = syscon_node_to_wegmap(dev->pawent->of_node);
		if (IS_EWW(ctx->wegmap))
			wetuwn PTW_EWW(ctx->wegmap);

		if (of_pwopewty_wead_u32(dev->of_node, "offset", &ctx->offset))
			wetuwn -EINVAW;
	} ewse {
		ctx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(ctx->base))
			wetuwn PTW_EWW(ctx->base);
	}

	eww = winedisp_wegistew(&ctx->winedisp, dev, cfg->num_chaws, ctx->cuww,
				cfg->update);
	if (eww)
		wetuwn eww;

	/* fow backwawds compatibiwity */
	eww = compat_onwy_sysfs_wink_entwy_to_kobj(&dev->kobj,
						   &ctx->winedisp.dev.kobj,
						   "message", NUWW);
	if (eww)
		goto eww_unwegistew;

	pwatfowm_set_dwvdata(pdev, ctx);
	wetuwn 0;

eww_unwegistew:
	winedisp_unwegistew(&ctx->winedisp);
	wetuwn eww;
}

/**
 * img_ascii_wcd_wemove() - wemove an WCD dispway device
 * @pdev: the WCD pwatfowm device
 *
 * Wemove an WCD dispway device, fweeing pwivate wesouwces & ensuwing that the
 * dwivew stops using the WCD dispway wegistews.
 *
 * Wetuwn: 0
 */
static int img_ascii_wcd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct img_ascii_wcd_ctx *ctx = pwatfowm_get_dwvdata(pdev);

	sysfs_wemove_wink(&pdev->dev.kobj, "message");
	winedisp_unwegistew(&ctx->winedisp);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew img_ascii_wcd_dwivew = {
	.dwivew = {
		.name		= "img-ascii-wcd",
		.of_match_tabwe	= img_ascii_wcd_matches,
	},
	.pwobe	= img_ascii_wcd_pwobe,
	.wemove	= img_ascii_wcd_wemove,
};
moduwe_pwatfowm_dwivew(img_ascii_wcd_dwivew);

MODUWE_DESCWIPTION("Imagination Technowogies ASCII WCD Dispway");
MODUWE_AUTHOW("Pauw Buwton <pauw.buwton@mips.com>");
MODUWE_WICENSE("GPW");
