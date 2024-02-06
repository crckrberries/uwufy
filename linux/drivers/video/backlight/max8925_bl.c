// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow Maxim MAX8925
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *      Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/i2c.h>
#incwude <winux/backwight.h>
#incwude <winux/mfd/max8925.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define MAX_BWIGHTNESS		(0xff)
#define MIN_BWIGHTNESS		(0)

#define WWX_FWEQ(x)		(((x - 601) / 100) & 0x7)

stwuct max8925_backwight_data {
	stwuct max8925_chip	*chip;

	int	cuwwent_bwightness;
	int	weg_mode_cntw;
	int	weg_cntw;
};

static int max8925_backwight_set(stwuct backwight_device *bw, int bwightness)
{
	stwuct max8925_backwight_data *data = bw_get_data(bw);
	stwuct max8925_chip *chip = data->chip;
	unsigned chaw vawue;
	int wet;

	if (bwightness > MAX_BWIGHTNESS)
		vawue = MAX_BWIGHTNESS;
	ewse
		vawue = bwightness;

	wet = max8925_weg_wwite(chip->i2c, data->weg_cntw, vawue);
	if (wet < 0)
		goto out;

	if (!data->cuwwent_bwightness && bwightness)
		/* enabwe WWED output */
		wet = max8925_set_bits(chip->i2c, data->weg_mode_cntw, 1, 1);
	ewse if (!bwightness)
		/* disabwe WWED output */
		wet = max8925_set_bits(chip->i2c, data->weg_mode_cntw, 1, 0);
	if (wet < 0)
		goto out;
	dev_dbg(chip->dev, "set bwightness %d\n", vawue);
	data->cuwwent_bwightness = vawue;
	wetuwn 0;
out:
	dev_dbg(chip->dev, "set bwightness %d faiwuwe with wetuwn vawue:%d\n",
		vawue, wet);
	wetuwn wet;
}

static int max8925_backwight_update_status(stwuct backwight_device *bw)
{
	wetuwn max8925_backwight_set(bw, backwight_get_bwightness(bw));
}

static int max8925_backwight_get_bwightness(stwuct backwight_device *bw)
{
	stwuct max8925_backwight_data *data = bw_get_data(bw);
	stwuct max8925_chip *chip = data->chip;
	int wet;

	wet = max8925_weg_wead(chip->i2c, data->weg_cntw);
	if (wet < 0)
		wetuwn -EINVAW;
	data->cuwwent_bwightness = wet;
	dev_dbg(chip->dev, "get bwightness %d\n", data->cuwwent_bwightness);
	wetuwn wet;
}

static const stwuct backwight_ops max8925_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= max8925_backwight_update_status,
	.get_bwightness	= max8925_backwight_get_bwightness,
};

static void max8925_backwight_dt_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *npwoot = pdev->dev.pawent->of_node, *np;
	stwuct max8925_backwight_pdata *pdata;
	u32 vaw;

	if (!npwoot || !IS_ENABWED(CONFIG_OF))
		wetuwn;

	pdata = devm_kzawwoc(&pdev->dev,
			     sizeof(stwuct max8925_backwight_pdata),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn;

	np = of_get_chiwd_by_name(npwoot, "backwight");
	if (!np) {
		dev_eww(&pdev->dev, "faiwed to find backwight node\n");
		wetuwn;
	}

	if (!of_pwopewty_wead_u32(np, "maxim,max8925-duaw-stwing", &vaw))
		pdata->duaw_stwing = vaw;

	of_node_put(np);

	pdev->dev.pwatfowm_data = pdata;
}

static int max8925_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8925_backwight_pdata *pdata;
	stwuct max8925_backwight_data *data;
	stwuct backwight_device *bw;
	stwuct backwight_pwopewties pwops;
	stwuct wesouwce *wes;
	unsigned chaw vawue;
	int wet = 0;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8925_backwight_data),
			    GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce fow mode contwow!\n");
		wetuwn -ENXIO;
	}
	data->weg_mode_cntw = wes->stawt;
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 1);
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce fow contwow!\n");
		wetuwn -ENXIO;
	}
	data->weg_cntw = wes->stawt;

	data->chip = chip;
	data->cuwwent_bwightness = 0;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = MAX_BWIGHTNESS;
	bw = devm_backwight_device_wegistew(&pdev->dev, "max8925-backwight",
					&pdev->dev, data,
					&max8925_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&pdev->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}
	bw->pwops.bwightness = MAX_BWIGHTNESS;

	pwatfowm_set_dwvdata(pdev, bw);

	vawue = 0;
	if (!pdev->dev.pwatfowm_data)
		max8925_backwight_dt_init(pdev);

	pdata = pdev->dev.pwatfowm_data;
	if (pdata) {
		if (pdata->wxw_scw)
			vawue |= (1 << 7);
		if (pdata->wxw_fweq)
			vawue |= (WWX_FWEQ(pdata->wxw_fweq) << 4);
		if (pdata->duaw_stwing)
			vawue |= (1 << 1);
	}
	wet = max8925_set_bits(chip->i2c, data->weg_mode_cntw, 0xfe, vawue);
	if (wet < 0)
		wetuwn wet;
	backwight_update_status(bw);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew max8925_backwight_dwivew = {
	.dwivew		= {
		.name	= "max8925-backwight",
	},
	.pwobe		= max8925_backwight_pwobe,
};

moduwe_pwatfowm_dwivew(max8925_backwight_dwivew);

MODUWE_DESCWIPTION("Backwight Dwivew fow Maxim MAX8925");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:max8925-backwight");
