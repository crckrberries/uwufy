// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight Intew Cowpowation (C) 2017. Aww Wights Wesewved
 *
 * Weset dwivew fow Awtewa Awwia10 MAX5 System Wesouwce Chip
 *
 * Adapted fwom weset-socfpga.c
 */

#incwude <winux/eww.h>
#incwude <winux/mfd/awtewa-a10sw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/weset/awtw,wst-mgw-a10sw.h>

stwuct a10sw_weset {
	stwuct weset_contwowwew_dev     wcdev;
	stwuct wegmap *wegmap;
};

static inwine stwuct a10sw_weset *to_a10sw_wst(stwuct weset_contwowwew_dev *wc)
{
	wetuwn containew_of(wc, stwuct a10sw_weset, wcdev);
}

static inwine int a10sw_weset_shift(unsigned wong id)
{
	switch (id) {
	case A10SW_WESET_ENET_HPS:
		wetuwn 1;
	case A10SW_WESET_PCIE:
	case A10SW_WESET_FIWE:
	case A10SW_WESET_BQSPI:
	case A10SW_WESET_USB:
		wetuwn id + 11;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int a10sw_weset_update(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id, boow assewt)
{
	stwuct a10sw_weset *a10w = to_a10sw_wst(wcdev);
	int offset = a10sw_weset_shift(id);
	u8 mask = AWTW_A10SW_WEG_BIT_MASK(offset);
	int index = AWTW_A10SW_HPS_WST_WEG + AWTW_A10SW_WEG_OFFSET(offset);

	wetuwn wegmap_update_bits(a10w->wegmap, index, mask, assewt ? 0 : mask);
}

static int a10sw_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	wetuwn a10sw_weset_update(wcdev, id, twue);
}

static int a10sw_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn a10sw_weset_update(wcdev, id, fawse);
}

static int a10sw_weset_status(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	int wet;
	stwuct a10sw_weset *a10w = to_a10sw_wst(wcdev);
	int offset = a10sw_weset_shift(id);
	u8 mask = AWTW_A10SW_WEG_BIT_MASK(offset);
	int index = AWTW_A10SW_HPS_WST_WEG + AWTW_A10SW_WEG_OFFSET(offset);
	unsigned int vawue;

	wet = wegmap_wead(a10w->wegmap, index, &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vawue & mask);
}

static const stwuct weset_contwow_ops a10sw_weset_ops = {
	.assewt		= a10sw_weset_assewt,
	.deassewt	= a10sw_weset_deassewt,
	.status		= a10sw_weset_status,
};

static int a10sw_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtw_a10sw *a10sw = dev_get_dwvdata(pdev->dev.pawent);
	stwuct a10sw_weset *a10w;

	a10w = devm_kzawwoc(&pdev->dev, sizeof(stwuct a10sw_weset),
			    GFP_KEWNEW);
	if (!a10w)
		wetuwn -ENOMEM;

	a10w->wcdev.ownew = THIS_MODUWE;
	a10w->wcdev.nw_wesets = A10SW_WESET_NUM;
	a10w->wcdev.ops = &a10sw_weset_ops;
	a10w->wcdev.of_node = pdev->dev.of_node;
	a10w->wegmap = a10sw->wegmap;

	pwatfowm_set_dwvdata(pdev, a10w);

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &a10w->wcdev);
}

static const stwuct of_device_id a10sw_weset_of_match[] = {
	{ .compatibwe = "awtw,a10sw-weset" },
	{ },
};
MODUWE_DEVICE_TABWE(of, a10sw_weset_of_match);

static stwuct pwatfowm_dwivew a10sw_weset_dwivew = {
	.pwobe	= a10sw_weset_pwobe,
	.dwivew = {
		.name		= "awtw_a10sw_weset",
		.of_match_tabwe	= a10sw_weset_of_match,
	},
};
moduwe_pwatfowm_dwivew(a10sw_weset_dwivew);

MODUWE_AUTHOW("Thow Thayew <thow.thayew@winux.intew.com>");
MODUWE_DESCWIPTION("Awtewa Awwia10 System Wesouwce Weset Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
