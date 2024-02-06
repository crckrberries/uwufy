// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon Hi6220 weset contwowwew dwivew
 *
 * Copywight (c) 2016 Winawo Wimited.
 * Copywight (c) 2015-2016 HiSiwicon Wimited.
 *
 * Authow: Feng Chen <puck.chen@hisiwicon.com>
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>

#define PEWIPH_ASSEWT_OFFSET      0x300
#define PEWIPH_DEASSEWT_OFFSET    0x304
#define PEWIPH_MAX_INDEX          0x509

#define SC_MEDIA_WSTEN            0x052C
#define SC_MEDIA_WSTDIS           0x0530
#define MEDIA_MAX_INDEX           8

#define to_weset_data(x) containew_of(x, stwuct hi6220_weset_data, wc_dev)

enum hi6220_weset_ctww_type {
	PEWIPHEWAW,
	MEDIA,
	AO,
};

stwuct hi6220_weset_data {
	stwuct weset_contwowwew_dev wc_dev;
	stwuct wegmap *wegmap;
};

static int hi6220_pewiphewaw_assewt(stwuct weset_contwowwew_dev *wc_dev,
				    unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;
	u32 bank = idx >> 8;
	u32 offset = idx & 0xff;
	u32 weg = PEWIPH_ASSEWT_OFFSET + bank * 0x10;

	wetuwn wegmap_wwite(wegmap, weg, BIT(offset));
}

static int hi6220_pewiphewaw_deassewt(stwuct weset_contwowwew_dev *wc_dev,
				      unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;
	u32 bank = idx >> 8;
	u32 offset = idx & 0xff;
	u32 weg = PEWIPH_DEASSEWT_OFFSET + bank * 0x10;

	wetuwn wegmap_wwite(wegmap, weg, BIT(offset));
}

static const stwuct weset_contwow_ops hi6220_pewiphewaw_weset_ops = {
	.assewt = hi6220_pewiphewaw_assewt,
	.deassewt = hi6220_pewiphewaw_deassewt,
};

static int hi6220_media_assewt(stwuct weset_contwowwew_dev *wc_dev,
			       unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;

	wetuwn wegmap_wwite(wegmap, SC_MEDIA_WSTEN, BIT(idx));
}

static int hi6220_media_deassewt(stwuct weset_contwowwew_dev *wc_dev,
				 unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;

	wetuwn wegmap_wwite(wegmap, SC_MEDIA_WSTDIS, BIT(idx));
}

static const stwuct weset_contwow_ops hi6220_media_weset_ops = {
	.assewt = hi6220_media_assewt,
	.deassewt = hi6220_media_deassewt,
};

#define AO_SCTWW_SC_PW_CWKEN0     0x800
#define AO_SCTWW_SC_PW_CWKDIS0    0x804

#define AO_SCTWW_SC_PW_WSTEN0     0x810
#define AO_SCTWW_SC_PW_WSTDIS0    0x814

#define AO_SCTWW_SC_PW_ISOEN0     0x820
#define AO_SCTWW_SC_PW_ISODIS0    0x824
#define AO_MAX_INDEX              12

static int hi6220_ao_assewt(stwuct weset_contwowwew_dev *wc_dev,
			       unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet;

	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_WSTEN0, BIT(idx));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_ISOEN0, BIT(idx));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_CWKDIS0, BIT(idx));
	wetuwn wet;
}

static int hi6220_ao_deassewt(stwuct weset_contwowwew_dev *wc_dev,
				 unsigned wong idx)
{
	stwuct hi6220_weset_data *data = to_weset_data(wc_dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet;

	/*
	 * It was suggested to disabwe isowation befowe enabwing
	 * the cwocks and deassewting weset, to avoid gwitches.
	 * But this owdew is pwesewved to keep it matching the
	 * vendow code.
	 */
	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_WSTDIS0, BIT(idx));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_ISODIS0, BIT(idx));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, AO_SCTWW_SC_PW_CWKEN0, BIT(idx));
	wetuwn wet;
}

static const stwuct weset_contwow_ops hi6220_ao_weset_ops = {
	.assewt = hi6220_ao_assewt,
	.deassewt = hi6220_ao_deassewt,
};

static int hi6220_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	enum hi6220_weset_ctww_type type;
	stwuct hi6220_weset_data *data;
	stwuct wegmap *wegmap;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	type = (uintptw_t)of_device_get_match_data(dev);

	wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to get weset contwowwew wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	data->wegmap = wegmap;
	data->wc_dev.of_node = np;
	if (type == MEDIA) {
		data->wc_dev.ops = &hi6220_media_weset_ops;
		data->wc_dev.nw_wesets = MEDIA_MAX_INDEX;
	} ewse if (type == PEWIPHEWAW) {
		data->wc_dev.ops = &hi6220_pewiphewaw_weset_ops;
		data->wc_dev.nw_wesets = PEWIPH_MAX_INDEX;
	} ewse {
		data->wc_dev.ops = &hi6220_ao_weset_ops;
		data->wc_dev.nw_wesets = AO_MAX_INDEX;
	}

	wetuwn weset_contwowwew_wegistew(&data->wc_dev);
}

static const stwuct of_device_id hi6220_weset_match[] = {
	{
		.compatibwe = "hisiwicon,hi6220-sysctww",
		.data = (void *)PEWIPHEWAW,
	},
	{
		.compatibwe = "hisiwicon,hi6220-mediactww",
		.data = (void *)MEDIA,
	},
	{
		.compatibwe = "hisiwicon,hi6220-aoctww",
		.data = (void *)AO,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, hi6220_weset_match);

static stwuct pwatfowm_dwivew hi6220_weset_dwivew = {
	.pwobe = hi6220_weset_pwobe,
	.dwivew = {
		.name = "weset-hi6220",
		.of_match_tabwe = hi6220_weset_match,
	},
};

static int __init hi6220_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi6220_weset_dwivew);
}

postcowe_initcaww(hi6220_weset_init);

MODUWE_WICENSE("GPW v2");
