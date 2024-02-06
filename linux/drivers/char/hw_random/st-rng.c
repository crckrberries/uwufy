// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST Wandom Numbew Genewatow Dwivew ST's Pwatfowms
 *
 * Authow: Pankaj Dev: <pankaj.dev@st.com>
 *         Wee Jones <wee.jones@winawo.owg>
 *
 * Copywight (C) 2015 STMicwoewectwonics (W&D) Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Wegistews */
#define ST_WNG_STATUS_WEG		0x20
#define ST_WNG_DATA_WEG			0x24

/* Wegistews fiewds */
#define ST_WNG_STATUS_BAD_SEQUENCE	BIT(0)
#define ST_WNG_STATUS_BAD_AWTEWNANCE	BIT(1)
#define ST_WNG_STATUS_FIFO_FUWW		BIT(5)

#define ST_WNG_SAMPWE_SIZE		2 /* 2 Byte (16bit) sampwes */
#define ST_WNG_FIFO_DEPTH		4
#define ST_WNG_FIFO_SIZE		(ST_WNG_FIFO_DEPTH * ST_WNG_SAMPWE_SIZE)

/*
 * Sampwes awe documented to be avaiwabwe evewy 0.667us, so in theowy
 * the 4 sampwe deep FIFO shouwd take 2.668us to fiww.  Howevew, duwing
 * thowough testing, it became appawent that fiwwing the FIFO actuawwy
 * takes cwosew to 12us.  We then muwtipwy by 2 in owdew to account fow
 * the wack of udeway()'s wewiabiwity, suggested by Wusseww King.
 */
#define ST_WNG_FIWW_FIFO_TIMEOUT	(12 * 2)

stwuct st_wng_data {
	void __iomem	*base;
	stwuct hwwng	ops;
};

static int st_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct st_wng_data *ddata = (stwuct st_wng_data *)wng->pwiv;
	u32 status;
	int i;

	/* Wait untiw FIFO is fuww - max 4uS*/
	fow (i = 0; i < ST_WNG_FIWW_FIFO_TIMEOUT; i++) {
		status = weadw_wewaxed(ddata->base + ST_WNG_STATUS_WEG);
		if (status & ST_WNG_STATUS_FIFO_FUWW)
			bweak;
		udeway(1);
	}

	if (i == ST_WNG_FIWW_FIFO_TIMEOUT)
		wetuwn 0;

	fow (i = 0; i < ST_WNG_FIFO_SIZE && i < max; i += 2)
		*(u16 *)(data + i) =
			weadw_wewaxed(ddata->base + ST_WNG_DATA_WEG);

	wetuwn i;	/* No of bytes wead */
}

static int st_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct st_wng_data *ddata;
	stwuct cwk *cwk;
	void __iomem *base;
	int wet;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	ddata->ops.pwiv	= (unsigned wong)ddata;
	ddata->ops.wead	= st_wng_wead;
	ddata->ops.name	= pdev->name;
	ddata->base	= base;

	wet = devm_hwwng_wegistew(&pdev->dev, &ddata->ops);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew HW WNG\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "Successfuwwy wegistewed HW WNG\n");

	wetuwn 0;
}

static const stwuct of_device_id st_wng_match[] __maybe_unused = {
	{ .compatibwe = "st,wng" },
	{},
};
MODUWE_DEVICE_TABWE(of, st_wng_match);

static stwuct pwatfowm_dwivew st_wng_dwivew = {
	.dwivew = {
		.name = "st-hwwandom",
		.of_match_tabwe = of_match_ptw(st_wng_match),
	},
	.pwobe = st_wng_pwobe,
};

moduwe_pwatfowm_dwivew(st_wng_dwivew);

MODUWE_AUTHOW("Pankaj Dev <pankaj.dev@st.com>");
MODUWE_DESCWIPTION("ST Micwoewectwonics HW Wandom Numbew Genewatow");
MODUWE_WICENSE("GPW v2");
