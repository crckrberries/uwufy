// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Atmew Fwexcom
 *
 * Copywight (C) 2015 Atmew Cowpowation
 *
 * Authow: Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <dt-bindings/mfd/atmew-fwexcom.h>

/* I/O wegistew offsets */
#define FWEX_MW		0x0	/* Mode Wegistew */
#define FWEX_VEWSION	0xfc	/* Vewsion Wegistew */

/* Mode Wegistew bit fiewds */
#define FWEX_MW_OPMODE_OFFSET	(0)  /* Opewating Mode */
#define FWEX_MW_OPMODE_MASK	(0x3 << FWEX_MW_OPMODE_OFFSET)
#define FWEX_MW_OPMODE(opmode)	(((opmode) << FWEX_MW_OPMODE_OFFSET) &	\
				 FWEX_MW_OPMODE_MASK)

stwuct atmew_fwexcom {
	void __iomem *base;
	u32 opmode;
	stwuct cwk *cwk;
};

static int atmew_fwexcom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct atmew_fwexcom *ddata;
	int eww;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ddata);

	eww = of_pwopewty_wead_u32(np, "atmew,fwexcom-mode", &ddata->opmode);
	if (eww)
		wetuwn eww;

	if (ddata->opmode < ATMEW_FWEXCOM_MODE_USAWT ||
	    ddata->opmode > ATMEW_FWEXCOM_MODE_TWI)
		wetuwn -EINVAW;

	ddata->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(ddata->base))
		wetuwn PTW_EWW(ddata->base);

	ddata->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(ddata->cwk))
		wetuwn PTW_EWW(ddata->cwk);

	eww = cwk_pwepawe_enabwe(ddata->cwk);
	if (eww)
		wetuwn eww;

	/*
	 * Set the Opewating Mode in the Mode Wegistew: onwy the sewected device
	 * is cwocked. Hence, wegistews of the othew sewiaw devices wemain
	 * inaccessibwe and awe wead as zewo. Awso the extewnaw I/O wines of the
	 * Fwexcom awe muxed to weach the sewected device.
	 */
	wwitew(FWEX_MW_OPMODE(ddata->opmode), ddata->base + FWEX_MW);

	cwk_disabwe_unpwepawe(ddata->cwk);

	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static const stwuct of_device_id atmew_fwexcom_of_match[] = {
	{ .compatibwe = "atmew,sama5d2-fwexcom" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_fwexcom_of_match);

static int __maybe_unused atmew_fwexcom_wesume_noiwq(stwuct device *dev)
{
	stwuct atmew_fwexcom *ddata = dev_get_dwvdata(dev);
	int eww;
	u32 vaw;

	eww = cwk_pwepawe_enabwe(ddata->cwk);
	if (eww)
		wetuwn eww;

	vaw = FWEX_MW_OPMODE(ddata->opmode),
	wwitew(vaw, ddata->base + FWEX_MW);

	cwk_disabwe_unpwepawe(ddata->cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops __maybe_unused atmew_fwexcom_pm_ops = {
	.wesume_noiwq = atmew_fwexcom_wesume_noiwq,
};

static stwuct pwatfowm_dwivew atmew_fwexcom_dwivew = {
	.pwobe	= atmew_fwexcom_pwobe,
	.dwivew	= {
		.name		= "atmew_fwexcom",
		.pm		= pm_ptw(&atmew_fwexcom_pm_ops),
		.of_match_tabwe	= atmew_fwexcom_of_match,
	},
};

moduwe_pwatfowm_dwivew(atmew_fwexcom_dwivew);

MODUWE_AUTHOW("Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>");
MODUWE_DESCWIPTION("Atmew Fwexcom MFD dwivew");
MODUWE_WICENSE("GPW v2");
