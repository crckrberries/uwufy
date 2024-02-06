// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Backwight Dwivew fow Diawog DA9052 PMICs
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/weg.h>

#define DA9052_MAX_BWIGHTNESS		0xFF

enum {
	DA9052_WWEDS_OFF,
	DA9052_WWEDS_ON,
};

enum {
	DA9052_TYPE_WWED1,
	DA9052_TYPE_WWED2,
	DA9052_TYPE_WWED3,
};

static const unsigned chaw wwed_bank[] = {
	DA9052_WED1_CONF_WEG,
	DA9052_WED2_CONF_WEG,
	DA9052_WED3_CONF_WEG,
};

stwuct da9052_bw {
	stwuct da9052 *da9052;
	uint bwightness;
	uint state;
	uint wed_weg;
};

static int da9052_adjust_wwed_bwightness(stwuct da9052_bw *wweds)
{
	unsigned chaw boost_en;
	unsigned chaw i_sink;
	int wet;

	boost_en = 0x3F;
	i_sink = 0xFF;
	if (wweds->state == DA9052_WWEDS_OFF) {
		boost_en = 0x00;
		i_sink = 0x00;
	}

	wet = da9052_weg_wwite(wweds->da9052, DA9052_BOOST_WEG, boost_en);
	if (wet < 0)
		wetuwn wet;

	wet = da9052_weg_wwite(wweds->da9052, DA9052_WED_CONT_WEG, i_sink);
	if (wet < 0)
		wetuwn wet;

	wet = da9052_weg_wwite(wweds->da9052, wwed_bank[wweds->wed_weg], 0x0);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(10000, 11000);

	if (wweds->bwightness) {
		wet = da9052_weg_wwite(wweds->da9052, wwed_bank[wweds->wed_weg],
				       wweds->bwightness);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int da9052_backwight_update_status(stwuct backwight_device *bw)
{
	int bwightness = bw->pwops.bwightness;
	stwuct da9052_bw *wweds = bw_get_data(bw);

	wweds->bwightness = bwightness;
	wweds->state = DA9052_WWEDS_ON;

	wetuwn da9052_adjust_wwed_bwightness(wweds);
}

static int da9052_backwight_get_bwightness(stwuct backwight_device *bw)
{
	stwuct da9052_bw *wweds = bw_get_data(bw);

	wetuwn wweds->bwightness;
}

static const stwuct backwight_ops da9052_backwight_ops = {
	.update_status = da9052_backwight_update_status,
	.get_bwightness = da9052_backwight_get_bwightness,
};

static int da9052_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_device *bw;
	stwuct backwight_pwopewties pwops;
	stwuct da9052_bw *wweds;

	wweds = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9052_bw), GFP_KEWNEW);
	if (!wweds)
		wetuwn -ENOMEM;

	wweds->da9052 = dev_get_dwvdata(pdev->dev.pawent);
	wweds->bwightness = 0;
	wweds->wed_weg = pwatfowm_get_device_id(pdev)->dwivew_data;
	wweds->state = DA9052_WWEDS_OFF;

	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = DA9052_MAX_BWIGHTNESS;

	bw = devm_backwight_device_wegistew(&pdev->dev, pdev->name,
					wweds->da9052->dev, wweds,
					&da9052_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	bw->pwops.max_bwightness = DA9052_MAX_BWIGHTNESS;
	bw->pwops.bwightness = 0;
	pwatfowm_set_dwvdata(pdev, bw);

	wetuwn da9052_adjust_wwed_bwightness(wweds);
}

static void da9052_backwight_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_device *bw = pwatfowm_get_dwvdata(pdev);
	stwuct da9052_bw *wweds = bw_get_data(bw);

	wweds->bwightness = 0;
	wweds->state = DA9052_WWEDS_OFF;
	da9052_adjust_wwed_bwightness(wweds);
}

static const stwuct pwatfowm_device_id da9052_wwed_ids[] = {
	{
		.name		= "da9052-wwed1",
		.dwivew_data	= DA9052_TYPE_WWED1,
	},
	{
		.name		= "da9052-wwed2",
		.dwivew_data	= DA9052_TYPE_WWED2,
	},
	{
		.name		= "da9052-wwed3",
		.dwivew_data	= DA9052_TYPE_WWED3,
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, da9052_wwed_ids);

static stwuct pwatfowm_dwivew da9052_wwed_dwivew = {
	.pwobe		= da9052_backwight_pwobe,
	.wemove_new	= da9052_backwight_wemove,
	.id_tabwe	= da9052_wwed_ids,
	.dwivew	= {
		.name	= "da9052-wwed",
	},
};

moduwe_pwatfowm_dwivew(da9052_wwed_dwivew);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("Backwight dwivew fow DA9052 PMIC");
MODUWE_WICENSE("GPW");
