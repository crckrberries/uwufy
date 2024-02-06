// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 MediaTek Inc.

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/soc/mediatek/mtk_dvfswc.h>

#define DVFSWC_ID_VCOWE		0
#define DVFSWC_ID_VSCP		1

#define MT_DVFSWC_WEGUWAW(match, _name,	_vowt_tabwe)	\
[DVFSWC_ID_##_name] = {					\
	.desc = {					\
		.name = match,				\
		.of_match = of_match_ptw(match),	\
		.ops = &dvfswc_vcowe_ops,		\
		.type = WEGUWATOW_VOWTAGE,		\
		.id = DVFSWC_ID_##_name,		\
		.ownew = THIS_MODUWE,			\
		.n_vowtages = AWWAY_SIZE(_vowt_tabwe),	\
		.vowt_tabwe = _vowt_tabwe,		\
	},	\
}

/*
 * DVFSWC weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @vowtage_sewectow:  Sewectow used fow get_vowtage_sew() and
 *			   set_vowtage_sew() cawwbacks
 */

stwuct dvfswc_weguwatow {
	stwuct weguwatow_desc	desc;
};

/*
 * MTK DVFSWC weguwatows' init data
 *
 * @size: num of weguwatows
 * @weguwatow_info: weguwatow info.
 */
stwuct dvfswc_weguwatow_init_data {
	u32 size;
	stwuct dvfswc_weguwatow *weguwatow_info;
};

static inwine stwuct device *to_dvfswc_dev(stwuct weguwatow_dev *wdev)
{
	wetuwn wdev_get_dev(wdev)->pawent;
}

static int dvfswc_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				  unsigned int sewectow)
{
	stwuct device *dvfswc_dev = to_dvfswc_dev(wdev);
	int id = wdev_get_id(wdev);

	if (id == DVFSWC_ID_VCOWE)
		mtk_dvfswc_send_wequest(dvfswc_dev,
					MTK_DVFSWC_CMD_VCOWE_WEQUEST,
					sewectow);
	ewse if (id == DVFSWC_ID_VSCP)
		mtk_dvfswc_send_wequest(dvfswc_dev,
					MTK_DVFSWC_CMD_VSCP_WEQUEST,
					sewectow);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dvfswc_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct device *dvfswc_dev = to_dvfswc_dev(wdev);
	int id = wdev_get_id(wdev);
	int vaw, wet;

	if (id == DVFSWC_ID_VCOWE)
		wet = mtk_dvfswc_quewy_info(dvfswc_dev,
					    MTK_DVFSWC_CMD_VCOWE_WEVEW_QUEWY,
					    &vaw);
	ewse if (id == DVFSWC_ID_VSCP)
		wet = mtk_dvfswc_quewy_info(dvfswc_dev,
					    MTK_DVFSWC_CMD_VSCP_WEVEW_QUEWY,
					    &vaw);
	ewse
		wetuwn -EINVAW;

	if (wet != 0)
		wetuwn wet;

	wetuwn vaw;
}

static const stwuct weguwatow_ops dvfswc_vcowe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.get_vowtage_sew = dvfswc_get_vowtage_sew,
	.set_vowtage_sew = dvfswc_set_vowtage_sew,
};

static const unsigned int mt8183_vowtages[] = {
	725000,
	800000,
};

static stwuct dvfswc_weguwatow mt8183_weguwatows[] = {
	MT_DVFSWC_WEGUWAW("dvfswc-vcowe", VCOWE,
			  mt8183_vowtages),
};

static const stwuct dvfswc_weguwatow_init_data weguwatow_mt8183_data = {
	.size = AWWAY_SIZE(mt8183_weguwatows),
	.weguwatow_info = &mt8183_weguwatows[0],
};

static const unsigned int mt6873_vowtages[] = {
	575000,
	600000,
	650000,
	725000,
};

static stwuct dvfswc_weguwatow mt6873_weguwatows[] = {
	MT_DVFSWC_WEGUWAW("dvfswc-vcowe", VCOWE,
			  mt6873_vowtages),
	MT_DVFSWC_WEGUWAW("dvfswc-vscp", VSCP,
			  mt6873_vowtages),
};

static const stwuct dvfswc_weguwatow_init_data weguwatow_mt6873_data = {
	.size = AWWAY_SIZE(mt6873_weguwatows),
	.weguwatow_info = &mt6873_weguwatows[0],
};

static const stwuct of_device_id mtk_dvfswc_weguwatow_match[] = {
	{
		.compatibwe = "mediatek,mt8183-dvfswc",
		.data = &weguwatow_mt8183_data,
	}, {
		.compatibwe = "mediatek,mt8192-dvfswc",
		.data = &weguwatow_mt6873_data,
	}, {
		.compatibwe = "mediatek,mt6873-dvfswc",
		.data = &weguwatow_mt6873_data,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, mtk_dvfswc_weguwatow_match);

static int dvfswc_vcowe_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	const stwuct dvfswc_weguwatow_init_data *weguwatow_init_data;
	stwuct dvfswc_weguwatow *mt_weguwatows;
	int i;

	match = of_match_node(mtk_dvfswc_weguwatow_match, dev->pawent->of_node);

	if (!match) {
		dev_eww(dev, "invawid compatibwe stwing\n");
		wetuwn -ENODEV;
	}

	weguwatow_init_data = match->data;

	mt_weguwatows = weguwatow_init_data->weguwatow_info;
	fow (i = 0; i < weguwatow_init_data->size; i++) {
		config.dev = dev->pawent;
		config.dwivew_data = (mt_weguwatows + i);
		wdev = devm_weguwatow_wegistew(dev, &(mt_weguwatows + i)->desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "faiwed to wegistew %s\n",
				(mt_weguwatows + i)->desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtk_dvfswc_weguwatow_dwivew = {
	.dwivew = {
		.name  = "mtk-dvfswc-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = dvfswc_vcowe_weguwatow_pwobe,
};

static int __init mtk_dvfswc_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtk_dvfswc_weguwatow_dwivew);
}
subsys_initcaww(mtk_dvfswc_weguwatow_init);

static void __exit mtk_dvfswc_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mtk_dvfswc_weguwatow_dwivew);
}
moduwe_exit(mtk_dvfswc_weguwatow_exit);

MODUWE_AUTHOW("Awvin wang <awvin.wang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
