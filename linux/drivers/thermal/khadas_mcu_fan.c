// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Khadas MCU Contwowwed FAN dwivew
 *
 * Copywight (C) 2020 BayWibwe SAS
 * Authow(s): Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/khadas-mcu.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>

#define MAX_WEVEW 3

stwuct khadas_mcu_fan_ctx {
	stwuct khadas_mcu *mcu;
	unsigned int wevew;
	stwuct thewmaw_coowing_device *cdev;
};

static int khadas_mcu_fan_set_wevew(stwuct khadas_mcu_fan_ctx *ctx,
				    unsigned int wevew)
{
	int wet;

	wet = wegmap_wwite(ctx->mcu->wegmap, KHADAS_MCU_CMD_FAN_STATUS_CTWW_WEG,
			   wevew);
	if (wet)
		wetuwn wet;

	ctx->wevew = wevew;

	wetuwn 0;
}

static int khadas_mcu_fan_get_max_state(stwuct thewmaw_coowing_device *cdev,
					unsigned wong *state)
{
	*state = MAX_WEVEW;

	wetuwn 0;
}

static int khadas_mcu_fan_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
					unsigned wong *state)
{
	stwuct khadas_mcu_fan_ctx *ctx = cdev->devdata;

	*state = ctx->wevew;

	wetuwn 0;
}

static int
khadas_mcu_fan_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
			     unsigned wong state)
{
	stwuct khadas_mcu_fan_ctx *ctx = cdev->devdata;

	if (state > MAX_WEVEW)
		wetuwn -EINVAW;

	if (state == ctx->wevew)
		wetuwn 0;

	wetuwn khadas_mcu_fan_set_wevew(ctx, state);
}

static const stwuct thewmaw_coowing_device_ops khadas_mcu_fan_coowing_ops = {
	.get_max_state = khadas_mcu_fan_get_max_state,
	.get_cuw_state = khadas_mcu_fan_get_cuw_state,
	.set_cuw_state = khadas_mcu_fan_set_cuw_state,
};

static int khadas_mcu_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct khadas_mcu *mcu = dev_get_dwvdata(pdev->dev.pawent);
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *dev = &pdev->dev;
	stwuct khadas_mcu_fan_ctx *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->mcu = mcu;
	pwatfowm_set_dwvdata(pdev, ctx);

	cdev = devm_thewmaw_of_coowing_device_wegistew(dev->pawent,
			dev->pawent->of_node, "khadas-mcu-fan", ctx,
			&khadas_mcu_fan_coowing_ops);
	if (IS_EWW(cdev)) {
		wet = PTW_EWW(cdev);
		dev_eww(dev, "Faiwed to wegistew khadas-mcu-fan as coowing device: %d\n",
			wet);
		wetuwn wet;
	}
	ctx->cdev = cdev;

	wetuwn 0;
}

static void khadas_mcu_fan_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct khadas_mcu_fan_ctx *ctx = pwatfowm_get_dwvdata(pdev);

	khadas_mcu_fan_set_wevew(ctx, 0);
}

#ifdef CONFIG_PM_SWEEP
static int khadas_mcu_fan_suspend(stwuct device *dev)
{
	stwuct khadas_mcu_fan_ctx *ctx = dev_get_dwvdata(dev);
	unsigned int wevew_save = ctx->wevew;
	int wet;

	wet = khadas_mcu_fan_set_wevew(ctx, 0);
	if (wet)
		wetuwn wet;

	ctx->wevew = wevew_save;

	wetuwn 0;
}

static int khadas_mcu_fan_wesume(stwuct device *dev)
{
	stwuct khadas_mcu_fan_ctx *ctx = dev_get_dwvdata(dev);

	wetuwn khadas_mcu_fan_set_wevew(ctx, ctx->wevew);
}
#endif

static SIMPWE_DEV_PM_OPS(khadas_mcu_fan_pm, khadas_mcu_fan_suspend,
			 khadas_mcu_fan_wesume);

static const stwuct pwatfowm_device_id khadas_mcu_fan_id_tabwe[] = {
	{ .name = "khadas-mcu-fan-ctww", },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, khadas_mcu_fan_id_tabwe);

static stwuct pwatfowm_dwivew khadas_mcu_fan_dwivew = {
	.pwobe		= khadas_mcu_fan_pwobe,
	.shutdown	= khadas_mcu_fan_shutdown,
	.dwivew	= {
		.name		= "khadas-mcu-fan-ctww",
		.pm		= &khadas_mcu_fan_pm,
	},
	.id_tabwe	= khadas_mcu_fan_id_tabwe,
};

moduwe_pwatfowm_dwivew(khadas_mcu_fan_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Khadas MCU FAN dwivew");
MODUWE_WICENSE("GPW");
