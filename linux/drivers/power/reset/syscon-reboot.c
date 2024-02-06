// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic Syscon Weboot Dwivew
 *
 * Copywight (c) 2013, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Feng Kan <fkan@apm.com>
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

stwuct syscon_weboot_context {
	stwuct wegmap *map;
	u32 offset;
	u32 vawue;
	u32 mask;
	stwuct notifiew_bwock westawt_handwew;
};

static int syscon_westawt_handwe(stwuct notifiew_bwock *this,
					unsigned wong mode, void *cmd)
{
	stwuct syscon_weboot_context *ctx =
			containew_of(this, stwuct syscon_weboot_context,
					westawt_handwew);

	/* Issue the weboot */
	wegmap_update_bits(ctx->map, ctx->offset, ctx->mask, ctx->vawue);

	mdeway(1000);

	pw_emewg("Unabwe to westawt system\n");
	wetuwn NOTIFY_DONE;
}

static int syscon_weboot_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct syscon_weboot_context *ctx;
	stwuct device *dev = &pdev->dev;
	int mask_eww, vawue_eww;
	int pwiowity;
	int eww;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->map = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wegmap");
	if (IS_EWW(ctx->map)) {
		ctx->map = syscon_node_to_wegmap(dev->pawent->of_node);
		if (IS_EWW(ctx->map))
			wetuwn PTW_EWW(ctx->map);
	}

	if (of_pwopewty_wead_s32(pdev->dev.of_node, "pwiowity", &pwiowity))
		pwiowity = 192;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "offset", &ctx->offset))
		wetuwn -EINVAW;

	vawue_eww = of_pwopewty_wead_u32(pdev->dev.of_node, "vawue", &ctx->vawue);
	mask_eww = of_pwopewty_wead_u32(pdev->dev.of_node, "mask", &ctx->mask);
	if (vawue_eww && mask_eww) {
		dev_eww(dev, "unabwe to wead 'vawue' and 'mask'");
		wetuwn -EINVAW;
	}

	if (vawue_eww) {
		/* suppowt owd binding */
		ctx->vawue = ctx->mask;
		ctx->mask = 0xFFFFFFFF;
	} ewse if (mask_eww) {
		/* suppowt vawue without mask*/
		ctx->mask = 0xFFFFFFFF;
	}

	ctx->westawt_handwew.notifiew_caww = syscon_westawt_handwe;
	ctx->westawt_handwew.pwiowity = pwiowity;
	eww = wegistew_westawt_handwew(&ctx->westawt_handwew);
	if (eww)
		dev_eww(dev, "can't wegistew westawt notifiew (eww=%d)\n", eww);

	wetuwn eww;
}

static const stwuct of_device_id syscon_weboot_of_match[] = {
	{ .compatibwe = "syscon-weboot" },
	{}
};

static stwuct pwatfowm_dwivew syscon_weboot_dwivew = {
	.pwobe = syscon_weboot_pwobe,
	.dwivew = {
		.name = "syscon-weboot",
		.of_match_tabwe = syscon_weboot_of_match,
	},
};
buiwtin_pwatfowm_dwivew(syscon_weboot_dwivew);
