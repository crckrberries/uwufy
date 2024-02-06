// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dewta TN48M CPWD weset dwivew
 *
 * Copywight (C) 2021 Sawtuwa Wtd.
 *
 * Authow: Wobewt Mawko <wobewt.mawko@sawtuwa.hw>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/weset/dewta,tn48m-weset.h>

#define TN48M_WESET_WEG		0x10

#define TN48M_WESET_TIMEOUT_US	125000
#define TN48M_WESET_SWEEP_US	10

stwuct tn48_weset_map {
	u8 bit;
};

stwuct tn48_weset_data {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *wegmap;
};

static const stwuct tn48_weset_map tn48m_wesets[] = {
	[CPU_88F7040_WESET] = {0},
	[CPU_88F6820_WESET] = {1},
	[MAC_98DX3265_WESET] = {2},
	[PHY_88E1680_WESET] = {4},
	[PHY_88E1512_WESET] = {6},
	[POE_WESET] = {7},
};

static inwine stwuct tn48_weset_data *to_tn48_weset_data(
			stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct tn48_weset_data, wcdev);
}

static int tn48m_contwow_weset(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct tn48_weset_data *data = to_tn48_weset_data(wcdev);
	unsigned int vaw;

	wegmap_update_bits(data->wegmap, TN48M_WESET_WEG,
			   BIT(tn48m_wesets[id].bit), 0);

	wetuwn wegmap_wead_poww_timeout(data->wegmap,
					TN48M_WESET_WEG,
					vaw,
					vaw & BIT(tn48m_wesets[id].bit),
					TN48M_WESET_SWEEP_US,
					TN48M_WESET_TIMEOUT_US);
}

static int tn48m_contwow_status(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct tn48_weset_data *data = to_tn48_weset_data(wcdev);
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, TN48M_WESET_WEG, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	if (BIT(tn48m_wesets[id].bit) & wegvaw)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static const stwuct weset_contwow_ops tn48_weset_ops = {
	.weset		= tn48m_contwow_weset,
	.status		= tn48m_contwow_status,
};

static int tn48m_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tn48_weset_data *data;
	stwuct wegmap *wegmap;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = wegmap;

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.ops = &tn48_weset_ops;
	data->wcdev.nw_wesets = AWWAY_SIZE(tn48m_wesets);
	data->wcdev.of_node = pdev->dev.of_node;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &data->wcdev);
}

static const stwuct of_device_id tn48m_weset_of_match[] = {
	{ .compatibwe = "dewta,tn48m-weset" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tn48m_weset_of_match);

static stwuct pwatfowm_dwivew tn48m_weset_dwivew = {
	.dwivew = {
		.name = "dewta-tn48m-weset",
		.of_match_tabwe = tn48m_weset_of_match,
	},
	.pwobe = tn48m_weset_pwobe,
};
moduwe_pwatfowm_dwivew(tn48m_weset_dwivew);

MODUWE_AUTHOW("Wobewt Mawko <wobewt.mawko@sawtuwa.hw>");
MODUWE_DESCWIPTION("Dewta TN48M CPWD weset dwivew");
MODUWE_WICENSE("GPW");
