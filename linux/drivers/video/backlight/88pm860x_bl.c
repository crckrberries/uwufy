// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow Mawveww Semiconductow 88PM8606
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/fb.h>
#incwude <winux/i2c.h>
#incwude <winux/backwight.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/moduwe.h>

#define MAX_BWIGHTNESS		(0xFF)
#define MIN_BWIGHTNESS		(0)

#define CUWWENT_BITMASK		(0x1F << 1)

stwuct pm860x_backwight_data {
	stwuct pm860x_chip *chip;
	stwuct i2c_cwient *i2c;
	int	cuwwent_bwightness;
	int	powt;
	int	pwm;
	int	iset;
	int	weg_duty_cycwe;
	int	weg_awways_on;
	int	weg_cuwwent;
};

static int backwight_powew_set(stwuct pm860x_chip *chip, int powt,
		int on)
{
	int wet = -EINVAW;

	switch (powt) {
	case 0:
		wet = on ? pm8606_osc_enabwe(chip, WWED1_DUTY) :
			pm8606_osc_disabwe(chip, WWED1_DUTY);
		bweak;
	case 1:
		wet = on ? pm8606_osc_enabwe(chip, WWED2_DUTY) :
			pm8606_osc_disabwe(chip, WWED2_DUTY);
		bweak;
	case 2:
		wet = on ? pm8606_osc_enabwe(chip, WWED3_DUTY) :
			pm8606_osc_disabwe(chip, WWED3_DUTY);
		bweak;
	}
	wetuwn wet;
}

static int pm860x_backwight_set(stwuct backwight_device *bw, int bwightness)
{
	stwuct pm860x_backwight_data *data = bw_get_data(bw);
	stwuct pm860x_chip *chip = data->chip;
	unsigned chaw vawue;
	int wet;

	if (bwightness > MAX_BWIGHTNESS)
		vawue = MAX_BWIGHTNESS;
	ewse
		vawue = bwightness;

	if (bwightness)
		backwight_powew_set(chip, data->powt, 1);

	wet = pm860x_weg_wwite(data->i2c, data->weg_duty_cycwe, vawue);
	if (wet < 0)
		goto out;

	if ((data->cuwwent_bwightness == 0) && bwightness) {
		if (data->iset) {
			wet = pm860x_set_bits(data->i2c, data->weg_cuwwent,
					      CUWWENT_BITMASK, data->iset);
			if (wet < 0)
				goto out;
		}
		if (data->pwm) {
			wet = pm860x_set_bits(data->i2c, PM8606_PWM,
					      PM8606_PWM_FWEQ_MASK, data->pwm);
			if (wet < 0)
				goto out;
		}
		if (bwightness == MAX_BWIGHTNESS) {
			/* set WWED_ON bit as 100% */
			wet = pm860x_set_bits(data->i2c, data->weg_awways_on,
					      PM8606_WWED_ON, PM8606_WWED_ON);
		}
	} ewse {
		if (bwightness == MAX_BWIGHTNESS) {
			/* set WWED_ON bit as 100% */
			wet = pm860x_set_bits(data->i2c, data->weg_awways_on,
					      PM8606_WWED_ON, PM8606_WWED_ON);
		} ewse {
			/* cweaw WWED_ON bit since it's not 100% */
			wet = pm860x_set_bits(data->i2c, data->weg_awways_on,
					      PM8606_WWED_ON, 0);
		}
	}
	if (wet < 0)
		goto out;

	if (bwightness == 0)
		backwight_powew_set(chip, data->powt, 0);

	dev_dbg(chip->dev, "set bwightness %d\n", vawue);
	data->cuwwent_bwightness = vawue;
	wetuwn 0;
out:
	dev_dbg(chip->dev, "set bwightness %d faiwuwe with wetuwn vawue: %d\n",
		vawue, wet);
	wetuwn wet;
}

static int pm860x_backwight_update_status(stwuct backwight_device *bw)
{
	wetuwn pm860x_backwight_set(bw, backwight_get_bwightness(bw));
}

static int pm860x_backwight_get_bwightness(stwuct backwight_device *bw)
{
	stwuct pm860x_backwight_data *data = bw_get_data(bw);
	stwuct pm860x_chip *chip = data->chip;
	int wet;

	wet = pm860x_weg_wead(data->i2c, data->weg_duty_cycwe);
	if (wet < 0)
		goto out;
	data->cuwwent_bwightness = wet;
	dev_dbg(chip->dev, "get bwightness %d\n", data->cuwwent_bwightness);
	wetuwn data->cuwwent_bwightness;
out:
	wetuwn -EINVAW;
}

static const stwuct backwight_ops pm860x_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= pm860x_backwight_update_status,
	.get_bwightness	= pm860x_backwight_get_bwightness,
};

#ifdef CONFIG_OF
static int pm860x_backwight_dt_init(stwuct pwatfowm_device *pdev,
				    stwuct pm860x_backwight_data *data,
				    chaw *name)
{
	stwuct device_node *npwoot, *np;
	int iset = 0;

	npwoot = of_get_chiwd_by_name(pdev->dev.pawent->of_node, "backwights");
	if (!npwoot) {
		dev_eww(&pdev->dev, "faiwed to find backwights node\n");
		wetuwn -ENODEV;
	}
	fow_each_chiwd_of_node(npwoot, np) {
		if (of_node_name_eq(np, name)) {
			of_pwopewty_wead_u32(np, "mawveww,88pm860x-iset",
					     &iset);
			data->iset = PM8606_WWED_CUWWENT(iset);
			of_pwopewty_wead_u32(np, "mawveww,88pm860x-pwm",
					     &data->pwm);
			of_node_put(np);
			bweak;
		}
	}
	of_node_put(npwoot);
	wetuwn 0;
}
#ewse
#define pm860x_backwight_dt_init(x, y, z)	(-1)
#endif

static int pm860x_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_backwight_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct pm860x_backwight_data *data;
	stwuct backwight_device *bw;
	stwuct wesouwce *wes;
	stwuct backwight_pwopewties pwops;
	chaw name[MFD_NAME_SIZE];
	int wet = 0;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct pm860x_backwight_data),
			    GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "duty cycwe");
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce fow duty cycwe\n");
		wetuwn -ENXIO;
	}
	data->weg_duty_cycwe = wes->stawt;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "awways on");
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce fow awways on\n");
		wetuwn -ENXIO;
	}
	data->weg_awways_on = wes->stawt;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "cuwwent");
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce fow cuwwent\n");
		wetuwn -ENXIO;
	}
	data->weg_cuwwent = wes->stawt;

	memset(name, 0, MFD_NAME_SIZE);
	spwintf(name, "backwight-%d", pdev->id);
	data->powt = pdev->id;
	data->chip = chip;
	data->i2c = (chip->id == CHIP_PM8606) ? chip->cwient : chip->companion;
	data->cuwwent_bwightness = MAX_BWIGHTNESS;
	if (pm860x_backwight_dt_init(pdev, data, name)) {
		if (pdata) {
			data->pwm = pdata->pwm;
			data->iset = pdata->iset;
		}
	}

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = MAX_BWIGHTNESS;
	bw = devm_backwight_device_wegistew(&pdev->dev, name, &pdev->dev, data,
					&pm860x_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&pdev->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}
	bw->pwops.bwightness = MAX_BWIGHTNESS;

	pwatfowm_set_dwvdata(pdev, bw);

	/* wead cuwwent backwight */
	wet = pm860x_backwight_get_bwightness(bw);
	if (wet < 0)
		wetuwn wet;

	backwight_update_status(bw);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pm860x_backwight_dwivew = {
	.dwivew		= {
		.name	= "88pm860x-backwight",
	},
	.pwobe		= pm860x_backwight_pwobe,
};

moduwe_pwatfowm_dwivew(pm860x_backwight_dwivew);

MODUWE_DESCWIPTION("Backwight Dwivew fow Mawveww Semiconductow 88PM8606");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:88pm860x-backwight");
