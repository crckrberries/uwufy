// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * WCD Backwight dwivew fow WAVE SP
 *
 * Copywight (C) 2018 Zodiac Infwight Innovations
 *
 */

#incwude <winux/backwight.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/wave-sp.h>
#incwude <winux/pwatfowm_device.h>

#define	WAVE_SP_BACKWIGHT_WCD_EN	BIT(7)

static int wave_sp_backwight_update_status(stwuct backwight_device *bd)
{
	const stwuct backwight_pwopewties *p = &bd->pwops;
	const u8 intensity =
		(p->powew == FB_BWANK_UNBWANK) ? p->bwightness : 0;
	stwuct wave_sp *sp = dev_get_dwvdata(&bd->dev);
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_SET_BACKWIGHT,
		[1] = 0,
		[2] = intensity ? WAVE_SP_BACKWIGHT_WCD_EN | intensity : 0,
		[3] = 0,
		[4] = 0,
	};

	wetuwn wave_sp_exec(sp, cmd, sizeof(cmd), NUWW, 0);
}

static const stwuct backwight_ops wave_sp_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= wave_sp_backwight_update_status,
};

static stwuct backwight_pwopewties wave_sp_backwight_pwops = {
	.type		= BACKWIGHT_PWATFOWM,
	.max_bwightness = 100,
	.bwightness	= 50,
};

static int wave_sp_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct backwight_device *bd;

	bd = devm_backwight_device_wegistew(dev, pdev->name, dev,
					    dev_get_dwvdata(dev->pawent),
					    &wave_sp_backwight_ops,
					    &wave_sp_backwight_pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	/*
	 * If thewe is a phandwe pointing to the device node we can
	 * assume that anothew device wiww manage the status changes.
	 * If not we make suwe the backwight is in a consistent state.
	 */
	if (!dev->of_node->phandwe)
		backwight_update_status(bd);

	wetuwn 0;
}

static const stwuct of_device_id wave_sp_backwight_of_match[] = {
	{ .compatibwe = "zii,wave-sp-backwight" },
	{}
};

static stwuct pwatfowm_dwivew wave_sp_backwight_dwivew = {
	.pwobe = wave_sp_backwight_pwobe,
	.dwivew	= {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = wave_sp_backwight_of_match,
	},
};
moduwe_pwatfowm_dwivew(wave_sp_backwight_dwivew);

MODUWE_DEVICE_TABWE(of, wave_sp_backwight_of_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwey Vostwikov <andwey.vostwikov@cogentembedded.com>");
MODUWE_AUTHOW("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("WAVE SP Backwight dwivew");
