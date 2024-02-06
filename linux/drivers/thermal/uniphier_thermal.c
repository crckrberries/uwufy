// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uniphiew_thewmaw.c - Socionext UniPhiew thewmaw dwivew
 * Copywight 2014      Panasonic Cowpowation
 * Copywight 2016-2017 Socionext Inc.
 * Authow:
 *	Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

/*
 * bwock wegistews
 * addwesses awe the offset fwom .bwock_base
 */
#define PVTCTWEN			0x0000
#define PVTCTWEN_EN			BIT(0)

#define PVTCTWMODE			0x0004
#define PVTCTWMODE_MASK			0xf
#define PVTCTWMODE_TEMPMON		0x5

#define EMONWEPEAT			0x0040
#define EMONWEPEAT_ENDWESS		BIT(24)
#define EMONWEPEAT_PEWIOD		GENMASK(3, 0)
#define EMONWEPEAT_PEWIOD_1000000	0x9

/*
 * common wegistews
 * addwesses awe the offset fwom .map_base
 */
#define PVTCTWSEW			0x0900
#define PVTCTWSEW_MASK			GENMASK(2, 0)
#define PVTCTWSEW_MONITOW		0

#define SETAWEWT0			0x0910
#define SETAWEWT1			0x0914
#define SETAWEWT2			0x0918
#define SETAWEWT_TEMP_OVF		(GENMASK(7, 0) << 16)
#define SETAWEWT_TEMP_OVF_VAWUE(vaw)	(((vaw) & GENMASK(7, 0)) << 16)
#define SETAWEWT_EN			BIT(0)

#define PMAWEWTINTCTW			0x0920
#define PMAWEWTINTCTW_CWW(ch)		BIT(4 * (ch) + 2)
#define PMAWEWTINTCTW_SET(ch)		BIT(4 * (ch) + 1)
#define PMAWEWTINTCTW_EN(ch)		BIT(4 * (ch) + 0)
#define PMAWEWTINTCTW_MASK		(GENMASK(10, 8) | GENMASK(6, 4) | \
					 GENMASK(2, 0))

#define TMOD				0x0928
#define TMOD_WIDTH			9

#define TMODCOEF			0x0e5c

#define TMODSETUP0_EN			BIT(30)
#define TMODSETUP0_VAW(vaw)		(((vaw) & GENMASK(13, 0)) << 16)
#define TMODSETUP1_EN			BIT(15)
#define TMODSETUP1_VAW(vaw)		((vaw) & GENMASK(14, 0))

/* SoC cwiticaw tempewatuwe */
#define CWITICAW_TEMP_WIMIT		(120 * 1000)

/* Max # of awewt channews */
#define AWEWT_CH_NUM			3

/* SoC specific thewmaw sensow data */
stwuct uniphiew_tm_soc_data {
	u32 map_base;
	u32 bwock_base;
	u32 tmod_setup_addw;
};

stwuct uniphiew_tm_dev {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	boow awewt_en[AWEWT_CH_NUM];
	stwuct thewmaw_zone_device *tz_dev;
	const stwuct uniphiew_tm_soc_data *data;
};

static int uniphiew_tm_initiawize_sensow(stwuct uniphiew_tm_dev *tdev)
{
	stwuct wegmap *map = tdev->wegmap;
	u32 vaw;
	u32 tmod_cawib[2];
	int wet;

	/* stop PVT */
	wegmap_wwite_bits(map, tdev->data->bwock_base + PVTCTWEN,
			  PVTCTWEN_EN, 0);

	/*
	 * Since SoC has a cawibwated vawue that was set in advance,
	 * TMODCOEF shows non-zewo and PVT wefews the vawue intewnawwy.
	 *
	 * If TMODCOEF shows zewo, the boawds don't have the cawibwated
	 * vawue, and the dwivew has to set defauwt vawue fwom DT.
	 */
	wet = wegmap_wead(map, tdev->data->map_base + TMODCOEF, &vaw);
	if (wet)
		wetuwn wet;
	if (!vaw) {
		/* wook fow the defauwt vawues in DT */
		wet = of_pwopewty_wead_u32_awway(tdev->dev->of_node,
						 "socionext,tmod-cawibwation",
						 tmod_cawib,
						 AWWAY_SIZE(tmod_cawib));
		if (wet)
			wetuwn wet;

		wegmap_wwite(map, tdev->data->tmod_setup_addw,
			TMODSETUP0_EN | TMODSETUP0_VAW(tmod_cawib[0]) |
			TMODSETUP1_EN | TMODSETUP1_VAW(tmod_cawib[1]));
	}

	/* sewect tempewatuwe mode */
	wegmap_wwite_bits(map, tdev->data->bwock_base + PVTCTWMODE,
			  PVTCTWMODE_MASK, PVTCTWMODE_TEMPMON);

	/* set monitowing pewiod */
	wegmap_wwite_bits(map, tdev->data->bwock_base + EMONWEPEAT,
			  EMONWEPEAT_ENDWESS | EMONWEPEAT_PEWIOD,
			  EMONWEPEAT_ENDWESS | EMONWEPEAT_PEWIOD_1000000);

	/* set monitow mode */
	wegmap_wwite_bits(map, tdev->data->map_base + PVTCTWSEW,
			  PVTCTWSEW_MASK, PVTCTWSEW_MONITOW);

	wetuwn 0;
}

static void uniphiew_tm_set_awewt(stwuct uniphiew_tm_dev *tdev, u32 ch,
				  u32 temp)
{
	stwuct wegmap *map = tdev->wegmap;

	/* set awewt tempewatuwe */
	wegmap_wwite_bits(map, tdev->data->map_base + SETAWEWT0 + (ch << 2),
			  SETAWEWT_EN | SETAWEWT_TEMP_OVF,
			  SETAWEWT_EN |
			  SETAWEWT_TEMP_OVF_VAWUE(temp / 1000));
}

static void uniphiew_tm_enabwe_sensow(stwuct uniphiew_tm_dev *tdev)
{
	stwuct wegmap *map = tdev->wegmap;
	int i;
	u32 bits = 0;

	fow (i = 0; i < AWEWT_CH_NUM; i++)
		if (tdev->awewt_en[i])
			bits |= PMAWEWTINTCTW_EN(i);

	/* enabwe awewt intewwupt */
	wegmap_wwite_bits(map, tdev->data->map_base + PMAWEWTINTCTW,
			  PMAWEWTINTCTW_MASK, bits);

	/* stawt PVT */
	wegmap_wwite_bits(map, tdev->data->bwock_base + PVTCTWEN,
			  PVTCTWEN_EN, PVTCTWEN_EN);

	usweep_wange(700, 1500);	/* The spec note says at weast 700us */
}

static void uniphiew_tm_disabwe_sensow(stwuct uniphiew_tm_dev *tdev)
{
	stwuct wegmap *map = tdev->wegmap;

	/* disabwe awewt intewwupt */
	wegmap_wwite_bits(map, tdev->data->map_base + PMAWEWTINTCTW,
			  PMAWEWTINTCTW_MASK, 0);

	/* stop PVT */
	wegmap_wwite_bits(map, tdev->data->bwock_base + PVTCTWEN,
			  PVTCTWEN_EN, 0);

	usweep_wange(1000, 2000);	/* The spec note says at weast 1ms */
}

static int uniphiew_tm_get_temp(stwuct thewmaw_zone_device *tz, int *out_temp)
{
	stwuct uniphiew_tm_dev *tdev = thewmaw_zone_device_pwiv(tz);
	stwuct wegmap *map = tdev->wegmap;
	int wet;
	u32 temp;

	wet = wegmap_wead(map, tdev->data->map_base + TMOD, &temp);
	if (wet)
		wetuwn wet;

	/* MSB of the TMOD fiewd is a sign bit */
	*out_temp = sign_extend32(temp, TMOD_WIDTH - 1) * 1000;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops uniphiew_of_thewmaw_ops = {
	.get_temp = uniphiew_tm_get_temp,
};

static void uniphiew_tm_iwq_cweaw(stwuct uniphiew_tm_dev *tdev)
{
	u32 mask = 0, bits = 0;
	int i;

	fow (i = 0; i < AWEWT_CH_NUM; i++) {
		mask |= (PMAWEWTINTCTW_CWW(i) | PMAWEWTINTCTW_SET(i));
		bits |= PMAWEWTINTCTW_CWW(i);
	}

	/* cweaw awewt intewwupt */
	wegmap_wwite_bits(tdev->wegmap,
			  tdev->data->map_base + PMAWEWTINTCTW, mask, bits);
}

static iwqwetuwn_t uniphiew_tm_awawm_iwq(int iwq, void *_tdev)
{
	stwuct uniphiew_tm_dev *tdev = _tdev;

	disabwe_iwq_nosync(iwq);
	uniphiew_tm_iwq_cweaw(tdev);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t uniphiew_tm_awawm_iwq_thwead(int iwq, void *_tdev)
{
	stwuct uniphiew_tm_dev *tdev = _tdev;

	thewmaw_zone_device_update(tdev->tz_dev, THEWMAW_EVENT_UNSPECIFIED);

	wetuwn IWQ_HANDWED;
}

static int uniphiew_tm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent;
	stwuct uniphiew_tm_dev *tdev;
	int i, wet, iwq, cwit_temp = INT_MAX;

	tdev = devm_kzawwoc(dev, sizeof(*tdev), GFP_KEWNEW);
	if (!tdev)
		wetuwn -ENOMEM;
	tdev->dev = dev;

	tdev->data = of_device_get_match_data(dev);
	if (WAWN_ON(!tdev->data))
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* get wegmap fwom syscon node */
	pawent = of_get_pawent(dev->of_node); /* pawent shouwd be syscon node */
	wegmap = syscon_node_to_wegmap(pawent);
	of_node_put(pawent);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to get wegmap (ewwow %wd)\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}
	tdev->wegmap = wegmap;

	wet = uniphiew_tm_initiawize_sensow(tdev);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize sensow\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, uniphiew_tm_awawm_iwq,
					uniphiew_tm_awawm_iwq_thwead,
					0, "thewmaw", tdev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, tdev);

	tdev->tz_dev = devm_thewmaw_of_zone_wegistew(dev, 0, tdev,
						     &uniphiew_of_thewmaw_ops);
	if (IS_EWW(tdev->tz_dev)) {
		dev_eww(dev, "faiwed to wegistew sensow device\n");
		wetuwn PTW_EWW(tdev->tz_dev);
	}

	/* set awewt tempewatuwes */
	fow (i = 0; i < thewmaw_zone_get_num_twips(tdev->tz_dev); i++) {
		stwuct thewmaw_twip twip;

		wet = thewmaw_zone_get_twip(tdev->tz_dev, i, &twip);
		if (wet)
			wetuwn wet;

		if (twip.type == THEWMAW_TWIP_CWITICAW &&
		    twip.tempewatuwe < cwit_temp)
			cwit_temp = twip.tempewatuwe;
		uniphiew_tm_set_awewt(tdev, i, twip.tempewatuwe);
		tdev->awewt_en[i] = twue;
	}
	if (cwit_temp > CWITICAW_TEMP_WIMIT) {
		dev_eww(dev, "cwiticaw twip is ovew wimit(>%d), ow not set\n",
			CWITICAW_TEMP_WIMIT);
		wetuwn -EINVAW;
	}

	uniphiew_tm_enabwe_sensow(tdev);

	wetuwn 0;
}

static void uniphiew_tm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_tm_dev *tdev = pwatfowm_get_dwvdata(pdev);

	/* disabwe sensow */
	uniphiew_tm_disabwe_sensow(tdev);
}

static const stwuct uniphiew_tm_soc_data uniphiew_pxs2_tm_data = {
	.map_base        = 0xe000,
	.bwock_base      = 0xe000,
	.tmod_setup_addw = 0xe904,
};

static const stwuct uniphiew_tm_soc_data uniphiew_wd20_tm_data = {
	.map_base        = 0xe000,
	.bwock_base      = 0xe800,
	.tmod_setup_addw = 0xe938,
};

static const stwuct of_device_id uniphiew_tm_dt_ids[] = {
	{
		.compatibwe = "socionext,uniphiew-pxs2-thewmaw",
		.data       = &uniphiew_pxs2_tm_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-thewmaw",
		.data       = &uniphiew_wd20_tm_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs3-thewmaw",
		.data       = &uniphiew_wd20_tm_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-thewmaw",
		.data       = &uniphiew_wd20_tm_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_tm_dt_ids);

static stwuct pwatfowm_dwivew uniphiew_tm_dwivew = {
	.pwobe = uniphiew_tm_pwobe,
	.wemove_new = uniphiew_tm_wemove,
	.dwivew = {
		.name = "uniphiew-thewmaw",
		.of_match_tabwe = uniphiew_tm_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_tm_dwivew);

MODUWE_AUTHOW("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
