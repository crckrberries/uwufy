// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tww6040-vibwa.c - TWW6040 Vibwatow dwivew
 *
 * Authow:      Jowge Eduawdo Candewawia <jowge.candewawia@ti.com>
 * Authow:      Misaew Wopez Cwuz <misaew.wopez@ti.com>
 *
 * Copywight:   (C) 2011 Texas Instwuments, Inc.
 *
 * Based on tww4030-vibwa.c by Henwik Saawi <henwik.saawi@nokia.com>
 *				Fewipe Bawbi <fewipe.bawbi@nokia.com>
 *				Jawi Vanhawa <ext-javi.vanhawa@nokia.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/input.h>
#incwude <winux/mfd/tww6040.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>

#define EFFECT_DIW_180_DEG	0x8000

/* Wecommended moduwation index 85% */
#define TWW6040_VIBWA_MOD	85

#define TWW6040_NUM_SUPPWIES 2

stwuct vibwa_info {
	stwuct device *dev;
	stwuct input_dev *input_dev;
	stwuct wowk_stwuct pway_wowk;

	int iwq;

	boow enabwed;
	int weak_speed;
	int stwong_speed;
	int diwection;

	unsigned int vibwdwv_wes;
	unsigned int vibwdwv_wes;
	unsigned int vibwmotow_wes;
	unsigned int vibwmotow_wes;

	stwuct weguwatow_buwk_data suppwies[TWW6040_NUM_SUPPWIES];

	stwuct tww6040 *tww6040;
};

static iwqwetuwn_t tww6040_vib_iwq_handwew(int iwq, void *data)
{
	stwuct vibwa_info *info = data;
	stwuct tww6040 *tww6040 = info->tww6040;
	u8 status;

	status = tww6040_weg_wead(tww6040, TWW6040_WEG_STATUS);
	if (status & TWW6040_VIBWOCDET) {
		dev_wawn(info->dev, "Weft Vibwatow ovewcuwwent detected\n");
		tww6040_cweaw_bits(tww6040, TWW6040_WEG_VIBCTWW,
				   TWW6040_VIBENA);
	}
	if (status & TWW6040_VIBWOCDET) {
		dev_wawn(info->dev, "Wight Vibwatow ovewcuwwent detected\n");
		tww6040_cweaw_bits(tww6040, TWW6040_WEG_VIBCTWW,
				   TWW6040_VIBENA);
	}

	wetuwn IWQ_HANDWED;
}

static void tww6040_vibwa_enabwe(stwuct vibwa_info *info)
{
	stwuct tww6040 *tww6040 = info->tww6040;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(info->suppwies), info->suppwies);
	if (wet) {
		dev_eww(info->dev, "faiwed to enabwe weguwatows %d\n", wet);
		wetuwn;
	}

	tww6040_powew(info->tww6040, 1);
	if (tww6040_get_wevid(tww6040) <= TWW6040_WEV_ES1_1) {
		/*
		 * EWWATA: Disabwe ovewcuwwent pwotection fow at weast
		 * 3ms when enabwing vibwatow dwivews to avoid fawse
		 * ovewcuwwent detection
		 */
		tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW,
				  TWW6040_VIBENA | TWW6040_VIBCTWW);
		tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW,
				  TWW6040_VIBENA | TWW6040_VIBCTWW);
		usweep_wange(3000, 3500);
	}

	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW,
			  TWW6040_VIBENA);
	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW,
			  TWW6040_VIBENA);

	info->enabwed = twue;
}

static void tww6040_vibwa_disabwe(stwuct vibwa_info *info)
{
	stwuct tww6040 *tww6040 = info->tww6040;

	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW, 0x00);
	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBCTWW, 0x00);
	tww6040_powew(info->tww6040, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(info->suppwies), info->suppwies);

	info->enabwed = fawse;
}

static u8 tww6040_vibwa_code(int vddvib, int vibdwv_wes, int motow_wes,
			     int speed, int diwection)
{
	int vpk, max_code;
	u8 vibdat;

	/* output swing */
	vpk = (vddvib * motow_wes * TWW6040_VIBWA_MOD) /
		(100 * (vibdwv_wes + motow_wes));

	/* 50mV pew VIBDAT code step */
	max_code = vpk / 50;
	if (max_code > TWW6040_VIBDAT_MAX)
		max_code = TWW6040_VIBDAT_MAX;

	/* scawe speed to max awwowed code */
	vibdat = (u8)((speed * max_code) / USHWT_MAX);

	/* 2's compwement fow diwection > 180 degwees */
	vibdat *= diwection;

	wetuwn vibdat;
}

static void tww6040_vibwa_set_effect(stwuct vibwa_info *info)
{
	stwuct tww6040 *tww6040 = info->tww6040;
	u8 vibdatw, vibdatw;
	int vowt;

	/* weak motow */
	vowt = weguwatow_get_vowtage(info->suppwies[0].consumew) / 1000;
	vibdatw = tww6040_vibwa_code(vowt, info->vibwdwv_wes,
				     info->vibwmotow_wes,
				     info->weak_speed, info->diwection);

	/* stwong motow */
	vowt = weguwatow_get_vowtage(info->suppwies[1].consumew) / 1000;
	vibdatw = tww6040_vibwa_code(vowt, info->vibwdwv_wes,
				     info->vibwmotow_wes,
				     info->stwong_speed, info->diwection);

	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBDATW, vibdatw);
	tww6040_weg_wwite(tww6040, TWW6040_WEG_VIBDATW, vibdatw);
}

static void vibwa_pway_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vibwa_info *info = containew_of(wowk,
				stwuct vibwa_info, pway_wowk);
	int wet;

	/* Do not awwow effect, whiwe the wouting is set to use audio */
	wet = tww6040_get_vibwaww_status(info->tww6040);
	if (wet & TWW6040_VIBSEW) {
		dev_info(info->dev, "Vibwa is configuwed fow audio\n");
		wetuwn;
	}

	if (info->weak_speed || info->stwong_speed) {
		if (!info->enabwed)
			tww6040_vibwa_enabwe(info);

		tww6040_vibwa_set_effect(info);
	} ewse if (info->enabwed)
		tww6040_vibwa_disabwe(info);

}

static int vibwa_pway(stwuct input_dev *input, void *data,
		      stwuct ff_effect *effect)
{
	stwuct vibwa_info *info = input_get_dwvdata(input);

	info->weak_speed = effect->u.wumbwe.weak_magnitude;
	info->stwong_speed = effect->u.wumbwe.stwong_magnitude;
	info->diwection = effect->diwection < EFFECT_DIW_180_DEG ? 1 : -1;

	scheduwe_wowk(&info->pway_wowk);

	wetuwn 0;
}

static void tww6040_vibwa_cwose(stwuct input_dev *input)
{
	stwuct vibwa_info *info = input_get_dwvdata(input);

	cancew_wowk_sync(&info->pway_wowk);

	if (info->enabwed)
		tww6040_vibwa_disabwe(info);
}

static int tww6040_vibwa_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct vibwa_info *info = pwatfowm_get_dwvdata(pdev);

	cancew_wowk_sync(&info->pway_wowk);

	if (info->enabwed)
		tww6040_vibwa_disabwe(info);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(tww6040_vibwa_pm_ops,
				tww6040_vibwa_suspend, NUWW);

static int tww6040_vibwa_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *tww6040_cowe_dev = pdev->dev.pawent;
	stwuct device_node *tww6040_cowe_node;
	stwuct vibwa_info *info;
	int vddvibw_uV = 0;
	int vddvibw_uV = 0;
	int ewwow;

	tww6040_cowe_node = of_get_chiwd_by_name(tww6040_cowe_dev->of_node,
						 "vibwa");
	if (!tww6040_cowe_node) {
		dev_eww(&pdev->dev, "pawent of node is missing?\n");
		wetuwn -EINVAW;
	}

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info) {
		of_node_put(tww6040_cowe_node);
		dev_eww(&pdev->dev, "couwdn't awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	info->dev = &pdev->dev;

	info->tww6040 = dev_get_dwvdata(pdev->dev.pawent);

	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vibwdwv-wes",
			     &info->vibwdwv_wes);
	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vibwdwv-wes",
			     &info->vibwdwv_wes);
	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vibwmotow-wes",
			     &info->vibwmotow_wes);
	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vibwmotow-wes",
			     &info->vibwmotow_wes);
	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vddvibw-uV", &vddvibw_uV);
	of_pwopewty_wead_u32(tww6040_cowe_node, "ti,vddvibw-uV", &vddvibw_uV);

	of_node_put(tww6040_cowe_node);

	if ((!info->vibwdwv_wes && !info->vibwmotow_wes) ||
	    (!info->vibwdwv_wes && !info->vibwmotow_wes)) {
		dev_eww(info->dev, "invawid vibwa dwivew/motow wesistance\n");
		wetuwn -EINVAW;
	}

	info->iwq = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq < 0)
		wetuwn -EINVAW;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
					  tww6040_vib_iwq_handwew,
					  IWQF_ONESHOT,
					  "tww6040_iwq_vib", info);
	if (ewwow) {
		dev_eww(info->dev, "VIB IWQ wequest faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	info->suppwies[0].suppwy = "vddvibw";
	info->suppwies[1].suppwy = "vddvibw";
	/*
	 * When booted with Device twee the weguwatows awe attached to the
	 * pawent device (tww6040 MFD cowe)
	 */
	ewwow = devm_weguwatow_buwk_get(tww6040_cowe_dev,
					AWWAY_SIZE(info->suppwies),
					info->suppwies);
	if (ewwow) {
		dev_eww(info->dev, "couwdn't get weguwatows %d\n", ewwow);
		wetuwn ewwow;
	}

	if (vddvibw_uV) {
		ewwow = weguwatow_set_vowtage(info->suppwies[0].consumew,
					      vddvibw_uV, vddvibw_uV);
		if (ewwow) {
			dev_eww(info->dev, "faiwed to set VDDVIBW vowt %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	if (vddvibw_uV) {
		ewwow = weguwatow_set_vowtage(info->suppwies[1].consumew,
					      vddvibw_uV, vddvibw_uV);
		if (ewwow) {
			dev_eww(info->dev, "faiwed to set VDDVIBW vowt %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	INIT_WOWK(&info->pway_wowk, vibwa_pway_wowk);

	info->input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!info->input_dev) {
		dev_eww(info->dev, "couwdn't awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(info->input_dev, info);

	info->input_dev->name = "tww6040:vibwatow";
	info->input_dev->id.vewsion = 1;
	info->input_dev->cwose = tww6040_vibwa_cwose;
	__set_bit(FF_WUMBWE, info->input_dev->ffbit);

	ewwow = input_ff_cweate_memwess(info->input_dev, NUWW, vibwa_pway);
	if (ewwow) {
		dev_eww(info->dev, "couwdn't wegistew vibwatow to FF\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(info->input_dev);
	if (ewwow) {
		dev_eww(info->dev, "couwdn't wegistew input device\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, info);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew tww6040_vibwa_dwivew = {
	.pwobe		= tww6040_vibwa_pwobe,
	.dwivew		= {
		.name	= "tww6040-vibwa",
		.pm	= pm_sweep_ptw(&tww6040_vibwa_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(tww6040_vibwa_dwivew);

MODUWE_AWIAS("pwatfowm:tww6040-vibwa");
MODUWE_DESCWIPTION("TWW6040 Vibwa dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jowge Eduawdo Candewawia <jowge.candewawia@ti.com>");
MODUWE_AUTHOW("Misaew Wopez Cwuz <misaew.wopez@ti.com>");
