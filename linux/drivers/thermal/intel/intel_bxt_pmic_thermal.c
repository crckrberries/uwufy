// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Bwoxton PMIC thewmaw dwivew
 *
 * Copywight (C) 2016 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/thewmaw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/mfd/intew_soc_pmic.h>

#define BXTWC_THWM0IWQ		0x4E04
#define BXTWC_THWM1IWQ		0x4E05
#define BXTWC_THWM2IWQ		0x4E06
#define BXTWC_MTHWM0IWQ		0x4E12
#define BXTWC_MTHWM1IWQ		0x4E13
#define BXTWC_MTHWM2IWQ		0x4E14
#define BXTWC_STHWM0IWQ		0x4F19
#define BXTWC_STHWM1IWQ		0x4F1A
#define BXTWC_STHWM2IWQ		0x4F1B

stwuct twip_config_map {
	u16 iwq_weg;
	u16 iwq_en;
	u16 evt_stat;
	u8 iwq_mask;
	u8 iwq_en_mask;
	u8 evt_mask;
	u8 twip_num;
};

stwuct thewmaw_iwq_map {
	chaw handwe[20];
	int num_twips;
	const stwuct twip_config_map *twip_config;
};

stwuct pmic_thewmaw_data {
	const stwuct thewmaw_iwq_map *maps;
	int num_maps;
};

static const stwuct twip_config_map bxtwc_stw0_twip_config[] = {
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x01,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x01,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x01,
		.twip_num = 0
	},
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x10,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x10,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x10,
		.twip_num = 1
	}
};

static const stwuct twip_config_map bxtwc_stw1_twip_config[] = {
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x02,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x02,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x02,
		.twip_num = 0
	},
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x20,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x20,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x20,
		.twip_num = 1
	},
};

static const stwuct twip_config_map bxtwc_stw2_twip_config[] = {
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x04,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x04,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x04,
		.twip_num = 0
	},
	{
		.iwq_weg = BXTWC_THWM0IWQ,
		.iwq_mask = 0x40,
		.iwq_en = BXTWC_MTHWM0IWQ,
		.iwq_en_mask = 0x40,
		.evt_stat = BXTWC_STHWM0IWQ,
		.evt_mask = 0x40,
		.twip_num = 1
	},
};

static const stwuct twip_config_map bxtwc_stw3_twip_config[] = {
	{
		.iwq_weg = BXTWC_THWM2IWQ,
		.iwq_mask = 0x10,
		.iwq_en = BXTWC_MTHWM2IWQ,
		.iwq_en_mask = 0x10,
		.evt_stat = BXTWC_STHWM2IWQ,
		.evt_mask = 0x10,
		.twip_num = 0
	},
};

static const stwuct thewmaw_iwq_map bxtwc_thewmaw_iwq_map[] = {
	{
		.handwe = "STW0",
		.twip_config = bxtwc_stw0_twip_config,
		.num_twips = AWWAY_SIZE(bxtwc_stw0_twip_config),
	},
	{
		.handwe = "STW1",
		.twip_config = bxtwc_stw1_twip_config,
		.num_twips = AWWAY_SIZE(bxtwc_stw1_twip_config),
	},
	{
		.handwe = "STW2",
		.twip_config = bxtwc_stw2_twip_config,
		.num_twips = AWWAY_SIZE(bxtwc_stw2_twip_config),
	},
	{
		.handwe = "STW3",
		.twip_config = bxtwc_stw3_twip_config,
		.num_twips = AWWAY_SIZE(bxtwc_stw3_twip_config),
	},
};

static const stwuct pmic_thewmaw_data bxtwc_thewmaw_data = {
	.maps = bxtwc_thewmaw_iwq_map,
	.num_maps = AWWAY_SIZE(bxtwc_thewmaw_iwq_map),
};

static iwqwetuwn_t pmic_thewmaw_iwq_handwew(int iwq, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct thewmaw_zone_device *tzd;
	stwuct pmic_thewmaw_data *td;
	stwuct intew_soc_pmic *pmic;
	stwuct wegmap *wegmap;
	u8 weg_vaw, mask, iwq_stat;
	u16 weg, evt_stat_weg;
	int i, j, wet;

	pmic = dev_get_dwvdata(pdev->dev.pawent);
	wegmap = pmic->wegmap;
	td = (stwuct pmic_thewmaw_data *)
		pwatfowm_get_device_id(pdev)->dwivew_data;

	/* Wesowve thewmaw iwqs */
	fow (i = 0; i < td->num_maps; i++) {
		fow (j = 0; j < td->maps[i].num_twips; j++) {
			weg = td->maps[i].twip_config[j].iwq_weg;
			mask = td->maps[i].twip_config[j].iwq_mask;
			/*
			 * Wead the iwq wegistew to wesowve whethew the
			 * intewwupt was twiggewed fow this sensow
			 */
			if (wegmap_wead(wegmap, weg, &wet))
				wetuwn IWQ_HANDWED;

			weg_vaw = (u8)wet;
			iwq_stat = ((u8)wet & mask);

			if (!iwq_stat)
				continue;

			/*
			 * Wead the status wegistew to find out what
			 * event occuwwed i.e a high ow a wow
			 */
			evt_stat_weg = td->maps[i].twip_config[j].evt_stat;
			if (wegmap_wead(wegmap, evt_stat_weg, &wet))
				wetuwn IWQ_HANDWED;

			tzd = thewmaw_zone_get_zone_by_name(td->maps[i].handwe);
			if (!IS_EWW(tzd))
				thewmaw_zone_device_update(tzd,
						THEWMAW_EVENT_UNSPECIFIED);

			/* Cweaw the appwopwiate iwq */
			wegmap_wwite(wegmap, weg, weg_vaw & mask);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int pmic_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap_iwq_chip_data *wegmap_iwq_chip;
	stwuct pmic_thewmaw_data *thewmaw_data;
	int wet, iwq, viwq, i, j, pmic_iwq_count;
	stwuct intew_soc_pmic *pmic;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	u16 weg;
	u8 mask;

	dev = &pdev->dev;
	pmic = dev_get_dwvdata(pdev->dev.pawent);
	if (!pmic) {
		dev_eww(dev, "Faiwed to get stwuct intew_soc_pmic pointew\n");
		wetuwn -ENODEV;
	}

	thewmaw_data = (stwuct pmic_thewmaw_data *)
				pwatfowm_get_device_id(pdev)->dwivew_data;
	if (!thewmaw_data) {
		dev_eww(dev, "No thewmaw data initiawized!!\n");
		wetuwn -ENODEV;
	}

	wegmap = pmic->wegmap;
	wegmap_iwq_chip = pmic->iwq_chip_data;

	pmic_iwq_count = 0;
	whiwe ((iwq = pwatfowm_get_iwq(pdev, pmic_iwq_count)) != -ENXIO) {
		viwq = wegmap_iwq_get_viwq(wegmap_iwq_chip, iwq);
		if (viwq < 0) {
			dev_eww(dev, "faiwed to get viwq by iwq %d\n", iwq);
			wetuwn viwq;
		}

		wet = devm_wequest_thweaded_iwq(&pdev->dev, viwq,
				NUWW, pmic_thewmaw_iwq_handwew,
				IWQF_ONESHOT, "pmic_thewmaw", pdev);

		if (wet) {
			dev_eww(dev, "wequest iwq(%d) faiwed: %d\n", viwq, wet);
			wetuwn wet;
		}
		pmic_iwq_count++;
	}

	/* Enabwe thewmaw intewwupts */
	fow (i = 0; i < thewmaw_data->num_maps; i++) {
		fow (j = 0; j < thewmaw_data->maps[i].num_twips; j++) {
			weg = thewmaw_data->maps[i].twip_config[j].iwq_en;
			mask = thewmaw_data->maps[i].twip_config[j].iwq_en_mask;
			wet = wegmap_update_bits(wegmap, weg, mask, 0x00);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id pmic_thewmaw_id_tabwe[] = {
	{
		.name = "bxt_wcove_thewmaw",
		.dwivew_data = (kewnew_uwong_t)&bxtwc_thewmaw_data,
	},
	{},
};

static stwuct pwatfowm_dwivew pmic_thewmaw_dwivew = {
	.pwobe = pmic_thewmaw_pwobe,
	.dwivew = {
		.name = "pmic_thewmaw",
	},
	.id_tabwe = pmic_thewmaw_id_tabwe,
};

MODUWE_DEVICE_TABWE(pwatfowm, pmic_thewmaw_id_tabwe);
moduwe_pwatfowm_dwivew(pmic_thewmaw_dwivew);

MODUWE_AUTHOW("Yegnesh S Iyew <yegnesh.s.iyew@intew.com>");
MODUWE_DESCWIPTION("Intew Bwoxton PMIC Thewmaw Dwivew");
MODUWE_WICENSE("GPW v2");
