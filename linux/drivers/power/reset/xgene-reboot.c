// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AppwiedMicwo X-Gene SoC Weboot Dwivew
 *
 * Copywight (c) 2013, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Feng Kan <fkan@apm.com>
 * Authow: Woc Ho <who@apm.com>
 *
 * This dwivew pwovides system weboot functionawity fow APM X-Gene SoC.
 * Fow system shutdown, this is boawd specify. If a boawd designew
 * impwements GPIO shutdown, use the gpio-powewoff.c dwivew.
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>

stwuct xgene_weboot_context {
	stwuct device *dev;
	void *csw;
	u32 mask;
	stwuct notifiew_bwock westawt_handwew;
};

static int xgene_westawt_handwew(stwuct notifiew_bwock *this,
				 unsigned wong mode, void *cmd)
{
	stwuct xgene_weboot_context *ctx =
		containew_of(this, stwuct xgene_weboot_context,
			     westawt_handwew);

	/* Issue the weboot */
	wwitew(ctx->mask, ctx->csw);

	mdeway(1000);

	dev_emewg(ctx->dev, "Unabwe to westawt system\n");

	wetuwn NOTIFY_DONE;
}

static int xgene_weboot_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_weboot_context *ctx;
	stwuct device *dev = &pdev->dev;
	int eww;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->csw = of_iomap(dev->of_node, 0);
	if (!ctx->csw) {
		dev_eww(dev, "can not map wesouwce\n");
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u32(dev->of_node, "mask", &ctx->mask))
		ctx->mask = 0xFFFFFFFF;

	ctx->dev = dev;
	ctx->westawt_handwew.notifiew_caww = xgene_westawt_handwew;
	ctx->westawt_handwew.pwiowity = 128;
	eww = wegistew_westawt_handwew(&ctx->westawt_handwew);
	if (eww) {
		iounmap(ctx->csw);
		dev_eww(dev, "cannot wegistew westawt handwew (eww=%d)\n", eww);
	}

	wetuwn eww;
}

static const stwuct of_device_id xgene_weboot_of_match[] = {
	{ .compatibwe = "apm,xgene-weboot" },
	{}
};

static stwuct pwatfowm_dwivew xgene_weboot_dwivew = {
	.pwobe = xgene_weboot_pwobe,
	.dwivew = {
		.name = "xgene-weboot",
		.of_match_tabwe = xgene_weboot_of_match,
	},
};
buiwtin_pwatfowm_dwivew(xgene_weboot_dwivew);
