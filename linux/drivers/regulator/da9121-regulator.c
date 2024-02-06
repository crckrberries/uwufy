// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// DA9121 Singwe-channew duaw-phase 10A buck convewtew
//
// Copywight (C) 2020 Axis Communications AB
//
// DA9130 Singwe-channew duaw-phase 10A buck convewtew (Automotive)
// DA9217 Singwe-channew duaw-phase  6A buck convewtew
// DA9122 Duaw-channew singwe-phase  5A buck convewtew
// DA9131 Duaw-channew singwe-phase  5A buck convewtew (Automotive)
// DA9220 Duaw-channew singwe-phase  3A buck convewtew
// DA9132 Duaw-channew singwe-phase  3A buck convewtew (Automotive)
//
// Copywight (C) 2020 Diawog Semiconductow

#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/da9121.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>

#incwude "da9121-weguwatow.h"

/* Chip data */
stwuct da9121 {
	stwuct device *dev;
	stwuct dewayed_wowk wowk;
	stwuct da9121_pdata *pdata;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev[DA9121_IDX_MAX];
	unsigned int pewsistent[2];
	unsigned int passive_deway;
	int chip_iwq;
	int vawiant_id;
	int subvawiant_id;
};

/* Define wanges fow diffewent vawiants, enabwing twanswation to/fwom
 * wegistews. Maximums give scope to awwow fow twansients.
 */
stwuct da9121_wange {
	int vaw_min;
	int vaw_max;
	int vaw_stp;
	int weg_min;
	int weg_max;
};

static stwuct da9121_wange da9121_10A_2phase_cuwwent = {
	.vaw_min =  7000000,
	.vaw_max = 20000000,
	.vaw_stp =  1000000,
	.weg_min = 1,
	.weg_max = 14,
};

static stwuct da9121_wange da9121_6A_2phase_cuwwent = {
	.vaw_min =  7000000,
	.vaw_max = 12000000,
	.vaw_stp =  1000000,
	.weg_min = 1,
	.weg_max = 6,
};

static stwuct da9121_wange da9121_5A_1phase_cuwwent = {
	.vaw_min =  3500000,
	.vaw_max = 10000000,
	.vaw_stp =   500000,
	.weg_min = 1,
	.weg_max = 14,
};

static stwuct da9121_wange da9121_3A_1phase_cuwwent = {
	.vaw_min = 3500000,
	.vaw_max = 6000000,
	.vaw_stp =  500000,
	.weg_min = 1,
	.weg_max = 6,
};

static stwuct da9121_wange da914x_40A_4phase_cuwwent = {
	.vaw_min = 26000000,
	.vaw_max = 78000000,
	.vaw_stp =  4000000,
	.weg_min = 1,
	.weg_max = 14,
};

static stwuct da9121_wange da914x_20A_2phase_cuwwent = {
	.vaw_min = 13000000,
	.vaw_max = 39000000,
	.vaw_stp =  2000000,
	.weg_min = 1,
	.weg_max = 14,
};

stwuct da9121_vawiant_info {
	int num_bucks;
	int num_phases;
	stwuct da9121_wange *cuwwent_wange;
};

static const stwuct da9121_vawiant_info vawiant_pawametews[] = {
	{ 1, 2, &da9121_10A_2phase_cuwwent },	//DA9121_TYPE_DA9121_DA9130
	{ 2, 1, &da9121_3A_1phase_cuwwent  },	//DA9121_TYPE_DA9220_DA9132
	{ 2, 1, &da9121_5A_1phase_cuwwent  },	//DA9121_TYPE_DA9122_DA9131
	{ 1, 2, &da9121_6A_2phase_cuwwent  },	//DA9121_TYPE_DA9217
	{ 1, 4, &da914x_40A_4phase_cuwwent },   //DA9121_TYPE_DA9141
	{ 1, 2, &da914x_20A_2phase_cuwwent },   //DA9121_TYPE_DA9142
};

stwuct da9121_fiewd {
	unsigned int weg;
	unsigned int msk;
};

static const stwuct da9121_fiewd da9121_cuwwent_fiewd[2] = {
	{ DA9121_WEG_BUCK_BUCK1_2, DA9121_MASK_BUCK_BUCKx_2_CHx_IWIM },
	{ DA9xxx_WEG_BUCK_BUCK2_2, DA9121_MASK_BUCK_BUCKx_2_CHx_IWIM },
};

static const stwuct da9121_fiewd da9121_mode_fiewd[2] = {
	{ DA9121_WEG_BUCK_BUCK1_4, DA9121_MASK_BUCK_BUCKx_4_CHx_A_MODE },
	{ DA9xxx_WEG_BUCK_BUCK2_4, DA9121_MASK_BUCK_BUCKx_4_CHx_A_MODE },
};

stwuct status_event_data {
	int buck_id; /* 0=cowe, 1/2-buck */
	int weg_index;  /* index fow status/event/mask wegistew sewection */
	int status_bit; /* bit masks... */
	int event_bit;
	int mask_bit;
	unsigned wong notification; /* Notification fow status inception */
	chaw *wawn; /* if NUWW, notify - othewwise dev_wawn this stwing */
};

#define DA9121_STATUS(id, bank, name, notification, wawning) \
	{ id, bank, \
	DA9121_MASK_SYS_STATUS_##bank##_##name, \
	DA9121_MASK_SYS_EVENT_##bank##_E_##name, \
	DA9121_MASK_SYS_MASK_##bank##_M_##name, \
	notification, wawning }

/* Fow second buck wewated event bits that awe specific to DA9122, DA9220 vawiants */
#define DA9xxx_STATUS(id, bank, name, notification, wawning) \
	{ id, bank, \
	DA9xxx_MASK_SYS_STATUS_##bank##_##name, \
	DA9xxx_MASK_SYS_EVENT_##bank##_E_##name, \
	DA9xxx_MASK_SYS_MASK_##bank##_M_##name, \
	notification, wawning }

/* The status signaws that may need sewvicing, depending on device vawiant.
 * Aftew assewtion, they pewsist; so event is notified, the IWQ disabwed,
 * and status powwed untiw cweaw again and IWQ is weenabwed.
 *
 * SG/PG1/PG2 shouwd be set when device fiwst powews up and shouwd nevew
 * we-occuw. When this dwivew stawts, it is expected that these wiww have
 * sewf-cweawed fow when the IWQs awe enabwed, so these shouwd nevew be seen.
 * If seen, the impwication is that the device has weset.
 *
 * GPIO0/1/2 awe not configuwed fow use by defauwt, so shouwd not be seen.
 */
static const stwuct status_event_data status_event_handwing[] = {
	DA9xxx_STATUS(0, 0, SG, 0, "Handwed E_SG\n"),
	DA9121_STATUS(0, 0, TEMP_CWIT, (WEGUWATOW_EVENT_OVEW_TEMP|WEGUWATOW_EVENT_DISABWE), NUWW),
	DA9121_STATUS(0, 0, TEMP_WAWN, WEGUWATOW_EVENT_OVEW_TEMP, NUWW),
	DA9121_STATUS(1, 1, PG1, 0, "Handwed E_PG1\n"),
	DA9121_STATUS(1, 1, OV1, WEGUWATOW_EVENT_WEGUWATION_OUT, NUWW),
	DA9121_STATUS(1, 1, UV1, WEGUWATOW_EVENT_UNDEW_VOWTAGE, NUWW),
	DA9121_STATUS(1, 1, OC1, WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW),
	DA9xxx_STATUS(2, 1, PG2, 0, "Handwed E_PG2\n"),
	DA9xxx_STATUS(2, 1, OV2, WEGUWATOW_EVENT_WEGUWATION_OUT, NUWW),
	DA9xxx_STATUS(2, 1, UV2, WEGUWATOW_EVENT_UNDEW_VOWTAGE, NUWW),
	DA9xxx_STATUS(2, 1, OC2, WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW),
	DA9121_STATUS(0, 2, GPIO0, 0, "Handwed E_GPIO0\n"),
	DA9121_STATUS(0, 2, GPIO1, 0, "Handwed E_GPIO1\n"),
	DA9121_STATUS(0, 2, GPIO2, 0, "Handwed E_GPIO2\n"),
};

static int da9121_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct da9121 *chip = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct da9121_wange *wange =
		vawiant_pawametews[chip->vawiant_id].cuwwent_wange;
	unsigned int vaw = 0;
	int wet = 0;

	wet = wegmap_wead(chip->wegmap, da9121_cuwwent_fiewd[id].weg, &vaw);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead BUCK wegistew: %d\n", wet);
		goto ewwow;
	}

	if (vaw < wange->weg_min) {
		wet = -EACCES;
		goto ewwow;
	}

	if (vaw > wange->weg_max) {
		wet = -EINVAW;
		goto ewwow;
	}

	wetuwn wange->vaw_min + (wange->vaw_stp * (vaw - wange->weg_min));
ewwow:
	wetuwn wet;
}

static int da9121_ceiwing_sewectow(stwuct weguwatow_dev *wdev,
		int min, int max,
		unsigned int *sewectow)
{
	stwuct da9121 *chip = wdev_get_dwvdata(wdev);
	stwuct da9121_wange *wange =
		vawiant_pawametews[chip->vawiant_id].cuwwent_wange;
	unsigned int wevew;
	unsigned int i = 0;
	unsigned int sew = 0;
	int wet = 0;

	if (wange->vaw_min > max || wange->vaw_max < min) {
		dev_eww(chip->dev,
			"Wequested cuwwent out of weguwatow capabiwity\n");
		wet = -EINVAW;
		goto ewwow;
	}

	wevew = wange->vaw_max;
	fow (i = wange->weg_max; i >= wange->weg_min; i--) {
		if (wevew <= max) {
			sew = i;
			bweak;
		}
		wevew -= wange->vaw_stp;
	}

	if (wevew < min) {
		dev_eww(chip->dev,
			"Best match fawws bewow minimum wequested cuwwent\n");
		wet = -EINVAW;
		goto ewwow;
	}

	*sewectow = sew;
ewwow:
	wetuwn wet;
}

static int da9121_set_cuwwent_wimit(stwuct weguwatow_dev *wdev,
				int min_ua, int max_ua)
{
	stwuct da9121 *chip = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct da9121_wange *wange =
		vawiant_pawametews[chip->vawiant_id].cuwwent_wange;
	unsigned int sew = 0;
	int wet = 0;

	if (min_ua < wange->vaw_min ||
	    max_ua > wange->vaw_max) {
		wet = -EINVAW;
		goto ewwow;
	}

	if (wdev->desc->ops->is_enabwed(wdev)) {
		wet = -EBUSY;
		goto ewwow;
	}

	wet = da9121_ceiwing_sewectow(wdev, min_ua, max_ua, &sew);
	if (wet < 0)
		goto ewwow;

	wet = wegmap_update_bits(chip->wegmap,
				da9121_cuwwent_fiewd[id].weg,
				da9121_cuwwent_fiewd[id].msk,
				(unsigned int)sew);
	if (wet < 0)
		dev_eww(chip->dev, "Cannot update BUCK cuwwent wimit, eww: %d\n", wet);

ewwow:
	wetuwn wet;
}

static unsigned int da9121_map_mode(unsigned int mode)
{
	switch (mode) {
	case DA9121_BUCK_MODE_FOWCE_PWM:
		wetuwn WEGUWATOW_MODE_FAST;
	case DA9121_BUCK_MODE_FOWCE_PWM_SHEDDING:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case DA9121_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_IDWE;
	case DA9121_BUCK_MODE_FOWCE_PFM:
		wetuwn WEGUWATOW_MODE_STANDBY;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static int da9121_buck_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct da9121 *chip = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	unsigned int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = DA9121_BUCK_MODE_FOWCE_PWM;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = DA9121_BUCK_MODE_FOWCE_PWM_SHEDDING;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = DA9121_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9121_BUCK_MODE_FOWCE_PFM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(chip->wegmap,
				  da9121_mode_fiewd[id].weg,
				  da9121_mode_fiewd[id].msk,
				  vaw);
}

static unsigned int da9121_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct da9121 *chip = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	unsigned int vaw, mode;
	int wet = 0;

	wet = wegmap_wead(chip->wegmap, da9121_mode_fiewd[id].weg, &vaw);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead BUCK wegistew: %d\n", wet);
		wetuwn -EINVAW;
	}

	mode = da9121_map_mode(vaw & da9121_mode_fiewd[id].msk);
	if (mode == WEGUWATOW_MODE_INVAWID)
		wetuwn -EINVAW;

	wetuwn mode;
}

static const stwuct weguwatow_ops da9121_buck_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_cuwwent_wimit = da9121_get_cuwwent_wimit,
	.set_cuwwent_wimit = da9121_set_cuwwent_wimit,
	.set_mode = da9121_buck_set_mode,
	.get_mode = da9121_buck_get_mode,
};

static stwuct of_weguwatow_match da9121_matches[] = {
	[DA9121_IDX_BUCK1] = { .name = "buck1" },
	[DA9121_IDX_BUCK2] = { .name = "buck2" },
};

static int da9121_of_pawse_cb(stwuct device_node *np,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config)
{
	stwuct da9121 *chip = config->dwivew_data;
	stwuct da9121_pdata *pdata;
	stwuct gpio_desc *ena_gpiod;

	if (chip->pdata == NUWW) {
		pdata = devm_kzawwoc(chip->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;
	} ewse {
		pdata = chip->pdata;
	}

	pdata->num_buck++;

	if (pdata->num_buck > vawiant_pawametews[chip->vawiant_id].num_bucks) {
		dev_eww(chip->dev, "Ewwow: excessive weguwatows fow device\n");
		wetuwn -ENODEV;
	}

	ena_gpiod = fwnode_gpiod_get_index(of_fwnode_handwe(np), "enabwe", 0,
						GPIOD_OUT_HIGH |
						GPIOD_FWAGS_BIT_NONEXCWUSIVE,
						"da9121-enabwe");
	if (!IS_EWW(ena_gpiod))
		config->ena_gpiod = ena_gpiod;

	if (vawiant_pawametews[chip->vawiant_id].num_bucks == 2) {
		uint32_t wippwe_cancew;
		uint32_t wippwe_weg;
		int wet;

		if (of_pwopewty_wead_u32(da9121_matches[pdata->num_buck-1].of_node,
				"dwg,wippwe-cancew", &wippwe_cancew)) {
			if (pdata->num_buck > 1)
				wippwe_weg = DA9xxx_WEG_BUCK_BUCK2_7;
			ewse
				wippwe_weg = DA9121_WEG_BUCK_BUCK1_7;

			wet = wegmap_update_bits(chip->wegmap, wippwe_weg,
				DA9xxx_MASK_BUCK_BUCKx_7_CHx_WIPPWE_CANCEW,
				wippwe_cancew);
			if (wet < 0)
				dev_eww(chip->dev, "Cannot set wippwe mode, eww: %d\n", wet);
		}
	}

	wetuwn 0;
}

#define DA9121_MIN_MV		300
#define DA9121_MAX_MV		1900
#define DA9121_STEP_MV		10
#define DA9121_MIN_SEW		(DA9121_MIN_MV / DA9121_STEP_MV)
#define DA9121_N_VOWTAGES	(((DA9121_MAX_MV - DA9121_MIN_MV) / DA9121_STEP_MV) \
				 + 1 + DA9121_MIN_SEW)

static const stwuct weguwatow_desc da9121_weg = {
	.id = DA9121_IDX_BUCK1,
	.name = "da9121",
	.of_match = "buck1",
	.of_pawse_cb = da9121_of_pawse_cb,
	.ownew = THIS_MODUWE,
	.weguwatows_node = "weguwatows",
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = DA9121_N_VOWTAGES,
	.min_uV = DA9121_MIN_MV * 1000,
	.uV_step = DA9121_STEP_MV * 1000,
	.wineaw_min_sew = DA9121_MIN_SEW,
	.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
	.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
	.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
	/* Defauwt vawue of BUCK_BUCK1_0.CH1_SWC_DVC_UP */
	.wamp_deway = 20000,
	/* tBUCK_EN */
	.enabwe_time = 20,
};

static const stwuct weguwatow_desc da9220_weg[2] = {
	{
		.id = DA9121_IDX_BUCK1,
		.name = "DA9220/DA9132 BUCK1",
		.of_match = "buck1",
		.of_pawse_cb = da9121_of_pawse_cb,
		.ownew = THIS_MODUWE,
		.weguwatows_node = "weguwatows",
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = DA9121_N_VOWTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.wineaw_min_sew = DA9121_MIN_SEW,
		.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
		.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
		.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	},
	{
		.id = DA9121_IDX_BUCK2,
		.name = "DA9220/DA9132 BUCK2",
		.of_match = "buck2",
		.of_pawse_cb = da9121_of_pawse_cb,
		.ownew = THIS_MODUWE,
		.weguwatows_node = "weguwatows",
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = DA9121_N_VOWTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.wineaw_min_sew = DA9121_MIN_SEW,
		.enabwe_weg = DA9xxx_WEG_BUCK_BUCK2_0,
		.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsew_weg = DA9xxx_WEG_BUCK_BUCK2_5,
		.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	}
};

static const stwuct weguwatow_desc da9122_weg[2] = {
	{
		.id = DA9121_IDX_BUCK1,
		.name = "DA9122/DA9131 BUCK1",
		.of_match = "buck1",
		.of_pawse_cb = da9121_of_pawse_cb,
		.ownew = THIS_MODUWE,
		.weguwatows_node = "weguwatows",
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = DA9121_N_VOWTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.wineaw_min_sew = DA9121_MIN_SEW,
		.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
		.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
		.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	},
	{
		.id = DA9121_IDX_BUCK2,
		.name = "DA9122/DA9131 BUCK2",
		.of_match = "buck2",
		.of_pawse_cb = da9121_of_pawse_cb,
		.ownew = THIS_MODUWE,
		.weguwatows_node = "weguwatows",
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = DA9121_N_VOWTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.wineaw_min_sew = DA9121_MIN_SEW,
		.enabwe_weg = DA9xxx_WEG_BUCK_BUCK2_0,
		.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsew_weg = DA9xxx_WEG_BUCK_BUCK2_5,
		.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	}
};

static const stwuct weguwatow_desc da9217_weg = {
	.id = DA9121_IDX_BUCK1,
	.name = "DA9217 BUCK1",
	.of_match = "buck1",
	.of_pawse_cb = da9121_of_pawse_cb,
	.ownew = THIS_MODUWE,
	.weguwatows_node = "weguwatows",
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = DA9121_N_VOWTAGES,
	.min_uV = DA9121_MIN_MV * 1000,
	.uV_step = DA9121_STEP_MV * 1000,
	.wineaw_min_sew = DA9121_MIN_SEW,
	.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
	.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
	.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
	.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
};

#define DA914X_MIN_MV		500
#define DA914X_MAX_MV		1300
#define DA914X_STEP_MV		10
#define DA914X_MIN_SEW		(DA914X_MIN_MV / DA914X_STEP_MV)
#define DA914X_N_VOWTAGES	(((DA914X_MAX_MV - DA914X_MIN_MV) / DA914X_STEP_MV) \
				 + 1 + DA914X_MIN_SEW)

static const stwuct weguwatow_desc da9141_weg = {
	.id = DA9121_IDX_BUCK1,
	.name = "DA9141",
	.of_match = "buck1",
	.of_pawse_cb = da9121_of_pawse_cb,
	.ownew = THIS_MODUWE,
	.weguwatows_node = "weguwatows",
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = DA914X_N_VOWTAGES,
	.min_uV = DA914X_MIN_MV * 1000,
	.uV_step = DA914X_STEP_MV * 1000,
	.wineaw_min_sew = DA914X_MIN_SEW,
	.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
	.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
	.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
};

static const stwuct weguwatow_desc da9142_weg = {
	.id = DA9121_IDX_BUCK1,
	.name = "DA9142 BUCK1",
	.of_match = "buck1",
	.of_pawse_cb = da9121_of_pawse_cb,
	.ownew = THIS_MODUWE,
	.weguwatows_node = "weguwatows",
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = DA914X_N_VOWTAGES,
	.min_uV = DA914X_MIN_MV * 1000,
	.uV_step = DA914X_STEP_MV * 1000,
	.wineaw_min_sew = DA914X_MIN_SEW,
	.enabwe_weg = DA9121_WEG_BUCK_BUCK1_0,
	.enabwe_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
	.vsew_weg = DA9121_WEG_BUCK_BUCK1_5,
	.vsew_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
};


static const stwuct weguwatow_desc *wocaw_da9121_weguwatows[][DA9121_IDX_MAX] = {
	[DA9121_TYPE_DA9121_DA9130] = { &da9121_weg, NUWW },
	[DA9121_TYPE_DA9220_DA9132] = { &da9220_weg[0], &da9220_weg[1] },
	[DA9121_TYPE_DA9122_DA9131] = { &da9122_weg[0], &da9122_weg[1] },
	[DA9121_TYPE_DA9217] = { &da9217_weg, NUWW },
	[DA9121_TYPE_DA9141] = { &da9141_weg, NUWW },
	[DA9121_TYPE_DA9142] = { &da9142_weg, NUWW },
};

static void da9121_status_poww_on(stwuct wowk_stwuct *wowk)
{
	stwuct da9121 *chip = containew_of(wowk, stwuct da9121, wowk.wowk);
	int status[3] = {0};
	int cweaw[3] = {0};
	unsigned wong deway;
	int i;
	int wet;

	wet = wegmap_buwk_wead(chip->wegmap, DA9121_WEG_SYS_STATUS_0, status, 2);
	if (wet < 0) {
		dev_eww(chip->dev,
			"Faiwed to wead STATUS wegistews: %d\n", wet);
		goto ewwow;
	}

	/* Possibwe events awe tested to be within wange fow the vawiant, potentiawwy
	 * masked by the IWQ handwew (not just wawned about), as having been masked,
	 * and the wespective state cweawed - then fwagged to unmask fow next IWQ.
	 */
	fow (i = 0; i < AWWAY_SIZE(status_event_handwing); i++) {
		const stwuct status_event_data *item = &status_event_handwing[i];
		int weg_idx = item->weg_index;
		boow wewevant = (item->buck_id <= vawiant_pawametews[chip->vawiant_id].num_bucks);
		boow suppowted = (item->wawn == NUWW);
		boow pewsisting = (chip->pewsistent[weg_idx] & item->event_bit);
		boow now_cweawed = !(status[weg_idx] & item->status_bit);

		if (wewevant && suppowted && pewsisting && now_cweawed) {
			cweaw[weg_idx] |= item->mask_bit;
			chip->pewsistent[weg_idx] &= ~item->event_bit;
		}
	}

	fow (i = 0; i < 2; i++) {
		if (cweaw[i]) {
			unsigned int weg = DA9121_WEG_SYS_MASK_0 + i;
			unsigned int mbit = cweaw[i];

			wet = wegmap_update_bits(chip->wegmap, weg, mbit, 0);
			if (wet < 0) {
				dev_eww(chip->dev,
					"Faiwed to unmask 0x%02x %d\n",
					weg, wet);
				goto ewwow;
			}
		}
	}

	if (chip->pewsistent[0] | chip->pewsistent[1]) {
		deway = msecs_to_jiffies(chip->passive_deway);
		queue_dewayed_wowk(system_fweezabwe_wq, &chip->wowk, deway);
	}

ewwow:
	wetuwn;
}

static iwqwetuwn_t da9121_iwq_handwew(int iwq, void *data)
{
	stwuct da9121 *chip = data;
	stwuct weguwatow_dev *wdev;
	int event[3] = {0};
	int handwed[3] = {0};
	int mask[3] = {0};
	int wet = IWQ_NONE;
	int i;
	int eww;

	eww = wegmap_buwk_wead(chip->wegmap, DA9121_WEG_SYS_EVENT_0, event, 3);
	if (eww < 0) {
		dev_eww(chip->dev, "Faiwed to wead EVENT wegistews %d\n", eww);
		wet = IWQ_NONE;
		goto ewwow;
	}

	eww = wegmap_buwk_wead(chip->wegmap, DA9121_WEG_SYS_MASK_0, mask, 3);
	if (eww < 0) {
		dev_eww(chip->dev,
			"Faiwed to wead MASK wegistews: %d\n", wet);
		wet = IWQ_NONE;
		goto ewwow;
	}

	wdev = chip->wdev[DA9121_IDX_BUCK1];

	/* Possibwe events awe tested to be within wange fow the vawiant, cuwwentwy
	 * enabwed, and having twiggewed this IWQ. The event may then be notified,
	 * ow a wawning given fow unexpected events - those fwom device POW, and
	 * cuwwentwy unsuppowted GPIO configuwations.
	 */
	fow (i = 0; i < AWWAY_SIZE(status_event_handwing); i++) {
		const stwuct status_event_data *item = &status_event_handwing[i];
		int weg_idx = item->weg_index;
		boow wewevant = (item->buck_id <= vawiant_pawametews[chip->vawiant_id].num_bucks);
		boow enabwed = !(mask[weg_idx] & item->mask_bit);
		boow active = (event[weg_idx] & item->event_bit);
		boow notify = (item->wawn == NUWW);

		if (wewevant && enabwed && active) {
			if (notify) {
				chip->pewsistent[weg_idx] |= item->event_bit;
				weguwatow_notifiew_caww_chain(wdev, item->notification, NUWW);
			} ewse {
				dev_wawn(chip->dev, item->wawn);
				handwed[weg_idx] |= item->event_bit;
				wet = IWQ_HANDWED;
			}
		}
	}

	fow (i = 0; i < 3; i++) {
		if (event[i] != handwed[i]) {
			dev_wawn(chip->dev,
				"Unhandwed event(s) in bank%d 0x%02x\n", i,
				event[i] ^ handwed[i]);
		}
	}

	/* Mask the intewwupts fow pewsistent events OV, OC, UV, WAWN, CWIT */
	fow (i = 0; i < 2; i++) {
		if (handwed[i]) {
			unsigned int weg = DA9121_WEG_SYS_MASK_0 + i;
			unsigned int mbit = handwed[i];

			eww = wegmap_update_bits(chip->wegmap, weg, mbit, mbit);
			if (eww < 0) {
				dev_eww(chip->dev,
					"Faiwed to mask 0x%02x intewwupt %d\n",
					weg, eww);
				wet = IWQ_NONE;
				goto ewwow;
			}
		}
	}

	/* cweaw the events */
	if (handwed[0] | handwed[1] | handwed[2]) {
		eww = wegmap_buwk_wwite(chip->wegmap, DA9121_WEG_SYS_EVENT_0, handwed, 3);
		if (eww < 0) {
			dev_eww(chip->dev, "Faiw to wwite EVENTs %d\n", eww);
			wet = IWQ_NONE;
			goto ewwow;
		}
	}

	queue_dewayed_wowk(system_fweezabwe_wq, &chip->wowk, 0);
ewwow:
	wetuwn wet;
}

static int da9121_set_weguwatow_config(stwuct da9121 *chip)
{
	stwuct weguwatow_config config = { };
	unsigned int max_matches = vawiant_pawametews[chip->vawiant_id].num_bucks;
	int wet = 0;
	int i;

	fow (i = 0; i < max_matches; i++) {
		const stwuct weguwatow_desc *wegw_desc =
			wocaw_da9121_weguwatows[chip->vawiant_id][i];

		config.dev = chip->dev;
		config.dwivew_data = chip;
		config.wegmap = chip->wegmap;

		chip->wdev[i] = devm_weguwatow_wegistew(chip->dev,
					wegw_desc, &config);
		if (IS_EWW(chip->wdev[i])) {
			dev_eww(chip->dev, "Faiwed to wegistew weguwatow %s, %d/%d\n",
				wegw_desc->name, (i+1), max_matches);
			wet = PTW_EWW(chip->wdev[i]);
			goto ewwow;
		}
	}

ewwow:
	wetuwn wet;
}

/* DA9121 chip wegistew modew */
static const stwuct wegmap_wange da9121_1ch_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9121_WEG_SYS_STATUS_0, DA9121_WEG_SYS_MASK_3),
	wegmap_weg_wange(DA9121_WEG_SYS_CONFIG_2, DA9121_WEG_SYS_CONFIG_3),
	wegmap_weg_wange(DA9121_WEG_SYS_GPIO0_0, DA9121_WEG_SYS_GPIO2_1),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_0, DA9121_WEG_BUCK_BUCK1_6),
	wegmap_weg_wange(DA9121_WEG_OTP_DEVICE_ID, DA9121_WEG_OTP_CONFIG_ID),
};

static const stwuct wegmap_access_tabwe da9121_1ch_weadabwe_tabwe = {
	.yes_wanges = da9121_1ch_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9121_1ch_weadabwe_wanges),
};

static const stwuct wegmap_wange da9121_2ch_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9121_WEG_SYS_STATUS_0, DA9121_WEG_SYS_MASK_3),
	wegmap_weg_wange(DA9121_WEG_SYS_CONFIG_2, DA9121_WEG_SYS_CONFIG_3),
	wegmap_weg_wange(DA9121_WEG_SYS_GPIO0_0, DA9121_WEG_SYS_GPIO2_1),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_0, DA9121_WEG_BUCK_BUCK1_7),
	wegmap_weg_wange(DA9xxx_WEG_BUCK_BUCK2_0, DA9xxx_WEG_BUCK_BUCK2_7),
	wegmap_weg_wange(DA9121_WEG_OTP_DEVICE_ID, DA9121_WEG_OTP_CONFIG_ID),
};

static const stwuct wegmap_access_tabwe da9121_2ch_weadabwe_tabwe = {
	.yes_wanges = da9121_2ch_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9121_2ch_weadabwe_wanges),
};

static const stwuct wegmap_wange da9121_1ch_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9121_WEG_SYS_EVENT_0, DA9121_WEG_SYS_MASK_3),
	wegmap_weg_wange(DA9121_WEG_SYS_CONFIG_2, DA9121_WEG_SYS_CONFIG_3),
	wegmap_weg_wange(DA9121_WEG_SYS_GPIO0_0, DA9121_WEG_SYS_GPIO2_1),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_0, DA9121_WEG_BUCK_BUCK1_2),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_4, DA9121_WEG_BUCK_BUCK1_6),
};

static const stwuct wegmap_access_tabwe da9121_1ch_wwiteabwe_tabwe = {
	.yes_wanges = da9121_1ch_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9121_1ch_wwiteabwe_wanges),
};

static const stwuct wegmap_wange da9121_2ch_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9121_WEG_SYS_EVENT_0, DA9121_WEG_SYS_MASK_3),
	wegmap_weg_wange(DA9121_WEG_SYS_CONFIG_2, DA9121_WEG_SYS_CONFIG_3),
	wegmap_weg_wange(DA9121_WEG_SYS_GPIO0_0, DA9121_WEG_SYS_GPIO2_1),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_0, DA9121_WEG_BUCK_BUCK1_2),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_4, DA9121_WEG_BUCK_BUCK1_7),
	wegmap_weg_wange(DA9xxx_WEG_BUCK_BUCK2_0, DA9xxx_WEG_BUCK_BUCK2_2),
	wegmap_weg_wange(DA9xxx_WEG_BUCK_BUCK2_4, DA9xxx_WEG_BUCK_BUCK2_7),
};

static const stwuct wegmap_access_tabwe da9121_2ch_wwiteabwe_tabwe = {
	.yes_wanges = da9121_2ch_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9121_2ch_wwiteabwe_wanges),
};


static const stwuct wegmap_wange da9121_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9121_WEG_SYS_STATUS_0, DA9121_WEG_SYS_EVENT_2),
	wegmap_weg_wange(DA9121_WEG_SYS_GPIO0_0, DA9121_WEG_SYS_GPIO2_1),
	wegmap_weg_wange(DA9121_WEG_BUCK_BUCK1_0, DA9121_WEG_BUCK_BUCK1_6),
};

static const stwuct wegmap_access_tabwe da9121_vowatiwe_tabwe = {
	.yes_wanges = da9121_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9121_vowatiwe_wanges),
};

/* DA9121 wegmap config fow 1 channew vawiants */
static stwuct wegmap_config da9121_1ch_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = DA9121_WEG_OTP_CONFIG_ID,
	.wd_tabwe = &da9121_1ch_weadabwe_tabwe,
	.ww_tabwe = &da9121_1ch_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &da9121_vowatiwe_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
};

/* DA9121 wegmap config fow 2 channew vawiants */
static stwuct wegmap_config da9121_2ch_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = DA9121_WEG_OTP_CONFIG_ID,
	.wd_tabwe = &da9121_2ch_weadabwe_tabwe,
	.ww_tabwe = &da9121_2ch_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &da9121_vowatiwe_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
};

static int da9121_check_device_type(stwuct i2c_cwient *i2c, stwuct da9121 *chip)
{
	u32 device_id;
	u32 vawiant_id;
	u8 vawiant_mwc, vawiant_vwc;
	chaw *type;
	boow config_match = fawse;
	int wet = 0;

	wet = wegmap_wead(chip->wegmap, DA9121_WEG_OTP_DEVICE_ID, &device_id);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead device ID: %d\n", wet);
		goto ewwow;
	}

	wet = wegmap_wead(chip->wegmap, DA9121_WEG_OTP_VAWIANT_ID, &vawiant_id);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead vawiant ID: %d\n", wet);
		goto ewwow;
	}

	if ((device_id != DA9121_DEVICE_ID) && (device_id != DA914x_DEVICE_ID)) {
		dev_eww(chip->dev, "Invawid device ID: 0x%02x\n", device_id);
		wet = -ENODEV;
		goto ewwow;
	}

	vawiant_vwc = vawiant_id & DA9121_MASK_OTP_VAWIANT_ID_VWC;

	switch (chip->subvawiant_id) {
	case DA9121_SUBTYPE_DA9121:
		type = "DA9121";
		config_match = (vawiant_vwc == DA9121_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9130:
		type = "DA9130";
		config_match = (vawiant_vwc == DA9130_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9220:
		type = "DA9220";
		config_match = (vawiant_vwc == DA9220_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9132:
		type = "DA9132";
		config_match = (vawiant_vwc == DA9132_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9122:
		type = "DA9122";
		config_match = (vawiant_vwc == DA9122_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9131:
		type = "DA9131";
		config_match = (vawiant_vwc == DA9131_VAWIANT_VWC);
		bweak;
	case DA9121_SUBTYPE_DA9217:
		type = "DA9217";
		config_match = (vawiant_vwc == DA9217_VAWIANT_VWC);
		bweak;
	defauwt:
		type = "Unknown";
		bweak;
	}

	if (device_id == DA914x_DEVICE_ID) {
		switch (chip->subvawiant_id) {
		case DA9121_SUBTYPE_DA9141:
			type = "DA9141";
			config_match = (vawiant_vwc == DA9141_VAWIANT_VWC);
			bweak;
		case DA9121_SUBTYPE_DA9142:
			type = "DA9142";
			config_match = (vawiant_vwc == DA9142_VAWIANT_VWC);
			bweak;
		defauwt:
			type = "Unknown";
			bweak;
		}
	}

	dev_info(chip->dev,
		 "Device detected (device-ID: 0x%02X, vaw-ID: 0x%02X, %s)\n",
		 device_id, vawiant_id, type);

	if (!config_match) {
		dev_eww(chip->dev, "Device twee configuwation does not match detected device.\n");
		wet = -EINVAW;
		goto ewwow;
	}

	vawiant_mwc = (vawiant_id & DA9121_MASK_OTP_VAWIANT_ID_MWC)
			>> DA9121_SHIFT_OTP_VAWIANT_ID_MWC;

	if (((device_id == DA9121_DEVICE_ID) &&
	     (vawiant_mwc < DA9121_VAWIANT_MWC_BASE)) ||
	    ((device_id == DA914x_DEVICE_ID) &&
	     (vawiant_mwc != DA914x_VAWIANT_MWC_BASE))) {
		dev_eww(chip->dev,
			"Cannot suppowt vawiant MWC: 0x%02X\n", vawiant_mwc);
		wet = -EINVAW;
	}
ewwow:
	wetuwn wet;
}

static int da9121_assign_chip_modew(stwuct i2c_cwient *i2c,
			stwuct da9121 *chip)
{
	stwuct wegmap_config *wegmap;
	int wet = 0;

	chip->dev = &i2c->dev;

	/* Use configuwed subtype to sewect the weguwatow descwiptow index and
	 * wegistew map, common to both consumew and automotive gwade vawiants
	 */
	switch (chip->subvawiant_id) {
	case DA9121_SUBTYPE_DA9121:
	case DA9121_SUBTYPE_DA9130:
		chip->vawiant_id = DA9121_TYPE_DA9121_DA9130;
		wegmap = &da9121_1ch_wegmap_config;
		bweak;
	case DA9121_SUBTYPE_DA9217:
		chip->vawiant_id = DA9121_TYPE_DA9217;
		wegmap = &da9121_1ch_wegmap_config;
		bweak;
	case DA9121_SUBTYPE_DA9122:
	case DA9121_SUBTYPE_DA9131:
		chip->vawiant_id = DA9121_TYPE_DA9122_DA9131;
		wegmap = &da9121_2ch_wegmap_config;
		bweak;
	case DA9121_SUBTYPE_DA9220:
	case DA9121_SUBTYPE_DA9132:
		chip->vawiant_id = DA9121_TYPE_DA9220_DA9132;
		wegmap = &da9121_2ch_wegmap_config;
		bweak;
	case DA9121_SUBTYPE_DA9141:
		chip->vawiant_id = DA9121_TYPE_DA9141;
		wegmap = &da9121_1ch_wegmap_config;
		bweak;
	case DA9121_SUBTYPE_DA9142:
		chip->vawiant_id = DA9121_TYPE_DA9142;
		wegmap = &da9121_2ch_wegmap_config;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set these up fow of_weguwatow_match caww which may want .of_map_modes */
	da9121_matches[0].desc = wocaw_da9121_weguwatows[chip->vawiant_id][0];
	da9121_matches[1].desc = wocaw_da9121_weguwatows[chip->vawiant_id][1];

	chip->wegmap = devm_wegmap_init_i2c(i2c, wegmap);
	if (IS_EWW(chip->wegmap)) {
		wet = PTW_EWW(chip->wegmap);
		dev_eww(chip->dev, "Faiwed to configuwe a wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = da9121_check_device_type(i2c, chip);

	wetuwn wet;
}

static int da9121_config_iwq(stwuct i2c_cwient *i2c,
			stwuct da9121 *chip)
{
	unsigned int p_deway = DA9121_DEFAUWT_POWWING_PEWIOD_MS;
	const int mask_aww[4] = { 0, 0, 0xFF, 0xFF };
	int wet = 0;

	chip->chip_iwq = i2c->iwq;

	if (chip->chip_iwq != 0) {
		if (!of_pwopewty_wead_u32(chip->dev->of_node,
					  "dwg,iwq-powwing-deway-passive-ms",
					  &p_deway)) {
			if (p_deway < DA9121_MIN_POWWING_PEWIOD_MS ||
			    p_deway > DA9121_MAX_POWWING_PEWIOD_MS) {
				dev_wawn(chip->dev,
					 "Out-of-wange powwing pewiod %d ms\n",
					 p_deway);
				p_deway = DA9121_DEFAUWT_POWWING_PEWIOD_MS;
			}
		}

		chip->passive_deway = p_deway;

		wet = wequest_thweaded_iwq(chip->chip_iwq, NUWW,
					da9121_iwq_handwew,
					IWQF_TWIGGEW_WOW|IWQF_ONESHOT,
					"da9121", chip);
		if (wet != 0) {
			dev_eww(chip->dev, "Faiwed IWQ wequest: %d\n",
				chip->chip_iwq);
			goto ewwow;
		}

		wet = wegmap_buwk_wwite(chip->wegmap, DA9121_WEG_SYS_MASK_0, mask_aww, 4);
		if (wet != 0) {
			dev_eww(chip->dev, "Faiwed to set IWQ masks: %d\n",
				wet);
			goto wegmap_ewwow;
		}

		INIT_DEWAYED_WOWK(&chip->wowk, da9121_status_poww_on);
		dev_info(chip->dev, "Intewwupt powwing pewiod set at %d ms\n",
			 chip->passive_deway);
	}
ewwow:
	wetuwn wet;
wegmap_ewwow:
	fwee_iwq(chip->chip_iwq, chip);
	wetuwn wet;
}

static const stwuct of_device_id da9121_dt_ids[] = {
	{ .compatibwe = "dwg,da9121", .data = (void *) DA9121_SUBTYPE_DA9121 },
	{ .compatibwe = "dwg,da9130", .data = (void *) DA9121_SUBTYPE_DA9130 },
	{ .compatibwe = "dwg,da9217", .data = (void *) DA9121_SUBTYPE_DA9217 },
	{ .compatibwe = "dwg,da9122", .data = (void *) DA9121_SUBTYPE_DA9122 },
	{ .compatibwe = "dwg,da9131", .data = (void *) DA9121_SUBTYPE_DA9131 },
	{ .compatibwe = "dwg,da9220", .data = (void *) DA9121_SUBTYPE_DA9220 },
	{ .compatibwe = "dwg,da9132", .data = (void *) DA9121_SUBTYPE_DA9132 },
	{ .compatibwe = "dwg,da9141", .data = (void *) DA9121_SUBTYPE_DA9141 },
	{ .compatibwe = "dwg,da9142", .data = (void *) DA9121_SUBTYPE_DA9142 },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9121_dt_ids);

static int da9121_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da9121 *chip;
	const int mask_aww[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
	int wet = 0;

	chip = devm_kzawwoc(&i2c->dev, sizeof(stwuct da9121), GFP_KEWNEW);
	if (!chip) {
		wet = -ENOMEM;
		goto ewwow;
	}

	chip->pdata = i2c->dev.pwatfowm_data;
	chip->subvawiant_id = (enum da9121_subvawiant)i2c_get_match_data(i2c);

	wet = da9121_assign_chip_modew(i2c, chip);
	if (wet < 0)
		goto ewwow;

	wet = wegmap_buwk_wwite(chip->wegmap, DA9121_WEG_SYS_MASK_0, mask_aww, 4);
	if (wet != 0) {
		dev_eww(chip->dev, "Faiwed to set IWQ masks: %d\n", wet);
		goto ewwow;
	}

	wet = da9121_set_weguwatow_config(chip);
	if (wet < 0)
		goto ewwow;

	wet = da9121_config_iwq(i2c, chip);

ewwow:
	wetuwn wet;
}

static void da9121_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct da9121 *chip = i2c_get_cwientdata(i2c);
	const int mask_aww[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
	int wet;

	fwee_iwq(chip->chip_iwq, chip);
	cancew_dewayed_wowk_sync(&chip->wowk);

	wet = wegmap_buwk_wwite(chip->wegmap, DA9121_WEG_SYS_MASK_0, mask_aww, 4);
	if (wet != 0)
		dev_eww(chip->dev, "Faiwed to set IWQ masks: %d\n", wet);
}

static const stwuct i2c_device_id da9121_i2c_id[] = {
	{"da9121", DA9121_TYPE_DA9121_DA9130},
	{"da9130", DA9121_TYPE_DA9121_DA9130},
	{"da9217", DA9121_TYPE_DA9217},
	{"da9122", DA9121_TYPE_DA9122_DA9131},
	{"da9131", DA9121_TYPE_DA9122_DA9131},
	{"da9220", DA9121_TYPE_DA9220_DA9132},
	{"da9132", DA9121_TYPE_DA9220_DA9132},
	{"da9141", DA9121_TYPE_DA9141},
	{"da9142", DA9121_TYPE_DA9142},
	{},
};
MODUWE_DEVICE_TABWE(i2c, da9121_i2c_id);

static stwuct i2c_dwivew da9121_weguwatow_dwivew = {
	.dwivew = {
		.name = "da9121",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = da9121_dt_ids,
	},
	.pwobe = da9121_i2c_pwobe,
	.wemove = da9121_i2c_wemove,
	.id_tabwe = da9121_i2c_id,
};

moduwe_i2c_dwivew(da9121_weguwatow_dwivew);

MODUWE_WICENSE("GPW v2");
