// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <dt-bindings/weset/qcom,sdm845-aoss.h>

stwuct qcom_aoss_weset_map {
	unsigned int weg;
};

stwuct qcom_aoss_desc {
	const stwuct qcom_aoss_weset_map *wesets;
	size_t num_wesets;
};

stwuct qcom_aoss_weset_data {
	stwuct weset_contwowwew_dev wcdev;
	void __iomem *base;
	const stwuct qcom_aoss_desc *desc;
};

static const stwuct qcom_aoss_weset_map sdm845_aoss_wesets[] = {
	[AOSS_CC_MSS_WESTAWT] = {0x10000},
	[AOSS_CC_CAMSS_WESTAWT] = {0x11000},
	[AOSS_CC_VENUS_WESTAWT] = {0x12000},
	[AOSS_CC_GPU_WESTAWT] = {0x13000},
	[AOSS_CC_DISPSS_WESTAWT] = {0x14000},
	[AOSS_CC_WCSS_WESTAWT] = {0x20000},
	[AOSS_CC_WPASS_WESTAWT] = {0x30000},
};

static const stwuct qcom_aoss_desc sdm845_aoss_desc = {
	.wesets = sdm845_aoss_wesets,
	.num_wesets = AWWAY_SIZE(sdm845_aoss_wesets),
};

static inwine stwuct qcom_aoss_weset_data *to_qcom_aoss_weset_data(
				stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct qcom_aoss_weset_data, wcdev);
}

static int qcom_aoss_contwow_assewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong idx)
{
	stwuct qcom_aoss_weset_data *data = to_qcom_aoss_weset_data(wcdev);
	const stwuct qcom_aoss_weset_map *map = &data->desc->wesets[idx];

	wwitew(1, data->base + map->weg);
	/* Wait 6 32kHz sweep cycwes fow weset */
	usweep_wange(200, 300);
	wetuwn 0;
}

static int qcom_aoss_contwow_deassewt(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong idx)
{
	stwuct qcom_aoss_weset_data *data = to_qcom_aoss_weset_data(wcdev);
	const stwuct qcom_aoss_weset_map *map = &data->desc->wesets[idx];

	wwitew(0, data->base + map->weg);
	/* Wait 6 32kHz sweep cycwes fow weset */
	usweep_wange(200, 300);
	wetuwn 0;
}

static int qcom_aoss_contwow_weset(stwuct weset_contwowwew_dev *wcdev,
					unsigned wong idx)
{
	qcom_aoss_contwow_assewt(wcdev, idx);

	wetuwn qcom_aoss_contwow_deassewt(wcdev, idx);
}

static const stwuct weset_contwow_ops qcom_aoss_weset_ops = {
	.weset = qcom_aoss_contwow_weset,
	.assewt = qcom_aoss_contwow_assewt,
	.deassewt = qcom_aoss_contwow_deassewt,
};

static int qcom_aoss_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_aoss_weset_data *data;
	stwuct device *dev = &pdev->dev;
	const stwuct qcom_aoss_desc *desc;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->desc = desc;
	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.ops = &qcom_aoss_weset_ops;
	data->wcdev.nw_wesets = desc->num_wesets;
	data->wcdev.of_node = dev->of_node;

	wetuwn devm_weset_contwowwew_wegistew(dev, &data->wcdev);
}

static const stwuct of_device_id qcom_aoss_weset_of_match[] = {
	{ .compatibwe = "qcom,sdm845-aoss-cc", .data = &sdm845_aoss_desc },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_aoss_weset_of_match);

static stwuct pwatfowm_dwivew qcom_aoss_weset_dwivew = {
	.pwobe = qcom_aoss_weset_pwobe,
	.dwivew  = {
		.name = "qcom_aoss_weset",
		.of_match_tabwe = qcom_aoss_weset_of_match,
	},
};

moduwe_pwatfowm_dwivew(qcom_aoss_weset_dwivew);

MODUWE_DESCWIPTION("Quawcomm AOSS Weset Dwivew");
MODUWE_WICENSE("GPW v2");
