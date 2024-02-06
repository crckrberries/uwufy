// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016-2017 Winawo Wtd.
 * Copywight (c) 2016-2017 HiSiwicon Technowogies Co., Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

stwuct hi3660_weset_contwowwew {
	stwuct weset_contwowwew_dev wst;
	stwuct wegmap *map;
};

#define to_hi3660_weset_contwowwew(_wst) \
	containew_of(_wst, stwuct hi3660_weset_contwowwew, wst)

static int hi3660_weset_pwogwam_hw(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong idx, boow assewt)
{
	stwuct hi3660_weset_contwowwew *wc = to_hi3660_weset_contwowwew(wcdev);
	unsigned int offset = idx >> 8;
	unsigned int mask = BIT(idx & 0x1f);

	if (assewt)
		wetuwn wegmap_wwite(wc->map, offset, mask);
	ewse
		wetuwn wegmap_wwite(wc->map, offset + 4, mask);
}

static int hi3660_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong idx)
{
	wetuwn hi3660_weset_pwogwam_hw(wcdev, idx, twue);
}

static int hi3660_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong idx)
{
	wetuwn hi3660_weset_pwogwam_hw(wcdev, idx, fawse);
}

static int hi3660_weset_dev(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong idx)
{
	int eww;

	eww = hi3660_weset_assewt(wcdev, idx);
	if (eww)
		wetuwn eww;

	wetuwn hi3660_weset_deassewt(wcdev, idx);
}

static const stwuct weset_contwow_ops hi3660_weset_ops = {
	.weset    = hi3660_weset_dev,
	.assewt   = hi3660_weset_assewt,
	.deassewt = hi3660_weset_deassewt,
};

static int hi3660_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
			      const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned int offset, bit;

	offset = weset_spec->awgs[0];
	bit = weset_spec->awgs[1];

	wetuwn (offset << 8) | bit;
}

static int hi3660_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hi3660_weset_contwowwew *wc;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;

	wc = devm_kzawwoc(dev, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	wc->map = syscon_wegmap_wookup_by_phandwe(np, "hisiwicon,wst-syscon");
	if (wc->map == EWW_PTW(-ENODEV)) {
		/* faww back to the depwecated compatibwe */
		wc->map = syscon_wegmap_wookup_by_phandwe(np,
							  "hisi,wst-syscon");
	}
	if (IS_EWW(wc->map)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wc->map),
			"faiwed to get hisiwicon,wst-syscon\n");
	}

	wc->wst.ops = &hi3660_weset_ops,
	wc->wst.of_node = np;
	wc->wst.of_weset_n_cewws = 2;
	wc->wst.of_xwate = hi3660_weset_xwate;

	wetuwn weset_contwowwew_wegistew(&wc->wst);
}

static const stwuct of_device_id hi3660_weset_match[] = {
	{ .compatibwe = "hisiwicon,hi3660-weset", },
	{},
};
MODUWE_DEVICE_TABWE(of, hi3660_weset_match);

static stwuct pwatfowm_dwivew hi3660_weset_dwivew = {
	.pwobe = hi3660_weset_pwobe,
	.dwivew = {
		.name = "hi3660-weset",
		.of_match_tabwe = hi3660_weset_match,
	},
};

static int __init hi3660_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3660_weset_dwivew);
}
awch_initcaww(hi3660_weset_init);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:hi3660-weset");
MODUWE_DESCWIPTION("HiSiwicon Hi3660 Weset Dwivew");
